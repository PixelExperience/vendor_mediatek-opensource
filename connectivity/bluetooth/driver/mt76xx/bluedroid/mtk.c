/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#if defined(MTK_LINUX)
//#include "osi/include/properties.h"
#else
#include <cutils/properties.h>
#endif
#include "bt_mtk.h"

/**************************************************************************
 *                  G L O B A L   V A R I A B L E S                       *
***************************************************************************/

bt_vendor_callbacks_t *bt_vnd_cbacks = NULL;
static int  bt_fd = -1;

/**************************************************************************
 *              F U N C T I O N   D E C L A R A T I O N S                 *
***************************************************************************/

extern VOID BT_Cleanup(VOID);

/**************************************************************************
 *                          F U N C T I O N S                             *
***************************************************************************/

static BOOL is_memzero(unsigned char *buf, int size)
{
    int i;
    for (i = 0; i < size; i++) {
        if (*(buf+i) != 0) return FALSE;
    }
    return TRUE;
}

/* Register callback functions to libbt-hci.so */
void set_callbacks(const bt_vendor_callbacks_t *p_cb)
{
    bt_vnd_cbacks = (bt_vendor_callbacks_t*)p_cb;
}

/* Cleanup callback functions previously registered */
void clean_callbacks(void)
{
    bt_vnd_cbacks = NULL;
}

/* Initialize UART port */
int init_uart(void)
{
    LOG_TRC();
    int index = 0;
    int retry_cnt = 10;

    for (index = 0; index < retry_cnt; index++) {
        bt_fd = open("/dev/stpbt", O_RDWR | O_NOCTTY | O_NONBLOCK | O_CLOEXEC);
        if (bt_fd < 0)
            LOG_ERR("Can't open serial port, errno = %d\n", errno);
        else
            return bt_fd;

        sleep(1);
    }

    return -1;
}

/* Close UART port previously opened */
void close_uart(void)
{
    if (bt_fd >= 0) close(bt_fd);
    bt_fd = -1;
}

/* Vendor FW Config, do nothing and then callback */
void vendor_fw_cfg(void)
{
    if (bt_vnd_cbacks) {
        bt_vnd_cbacks->fwcfg_cb(BT_VND_OP_RESULT_SUCCESS);
    }
}

void vendor_op_lmp_set_mode(void)
{
    if (bt_vnd_cbacks) {
        bt_vnd_cbacks->lpm_cb(BT_VND_OP_RESULT_SUCCESS);
    }
}

/* MTK specific deinitialize process */
int mtk_prepare_off(void)
{
    /*
    * On KK, BlueDroid adds BT_VND_OP_EPILOG procedure when BT disable:
    *   - 1. BT_VND_OP_EPILOG;
    *   - 2. In vendor epilog_cb, send EXIT event to bt_hc_worker_thread;
    *   - 3. Wait for bt_hc_worker_thread exit;
    *   - 4. userial close;
    *   - 5. vendor cleanup;
    *   - 6. Set power off.
    * On L, the disable flow is modified as below:
    *   - 1. userial Rx thread exit;
    *   - 2. BT_VND_OP_EPILOG;
    *   - 3. Write reactor->event_fd to trigger bt_hc_worker_thread exit
    *        (not wait to vendor epilog_cb and do nothing in epilog_cb);
    *   - 4. Wait for bt_hc_worker_thread exit;
    *   - 5. userial close;
    *   - 6. Set power off;
    *   - 7. vendor cleanup.
    *
    * It seems BlueDroid does not expect Tx/Rx interaction with chip during
    * BT_VND_OP_EPILOG procedure, and also does not need to do it in a new
    * thread context (NE may occur in __pthread_start if bt_hc_worker_thread
    * has already exited).
    * So BT_VND_OP_EPILOG procedure may be not for chip deinitialization,
    * do nothing, just notify success.
    *
    * [FIXME!!]How to do if chip deinit is needed?
    */
    //return (BT_DeinitDevice() == TRUE ? 0 : -1);
    if (bt_vnd_cbacks) {
        bt_vnd_cbacks->epilog_cb(BT_VND_OP_RESULT_SUCCESS);
    }
    return 0;
}

/* Cleanup driver resources, e.g thread exit */
void clean_resource(void)
{
    BT_Cleanup();
}
