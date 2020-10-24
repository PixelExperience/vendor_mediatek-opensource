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
#include <pthread.h>

#include "bt_mtk.h"


/**************************************************************************
 *                  G L O B A L   V A R I A B L E S                       *
***************************************************************************/

extern BT_INIT_VAR_T btinit[1];
extern BT_INIT_CB_T btinit_ctrl;

/**************************************************************************
 *                          F U N C T I O N S                             *
***************************************************************************/

extern VOID *GORM_FW_Init_Thread(VOID *ptr);
extern VOID notify_thread_exit(VOID);

BOOL BT_InitDevice(UINT32 chipId, PUCHAR pucNvRamData)
{
    LOG_DBG("BT_InitDevice\n");

    memset(btinit, 0, sizeof(BT_INIT_VAR_T));
    btinit_ctrl.worker_thread_running = FALSE;
    pthread_mutexattr_init(&btinit_ctrl.attr);
    pthread_mutexattr_settype(&btinit_ctrl.attr, PTHREAD_MUTEX_ERRORCHECK);
    pthread_mutex_init(&btinit_ctrl.mutex, &btinit_ctrl.attr);
    pthread_condattr_init(&btinit_ctrl.condattr);
    pthread_condattr_setclock(&btinit_ctrl.condattr, CLOCK_MONOTONIC);
    pthread_cond_init(&btinit_ctrl.cond, &btinit_ctrl.condattr);

    btinit->chip_id = chipId;
    /* Copy configuration data */
    memcpy(btinit->bt_nvram.raw, pucNvRamData, sizeof(ap_nvram_btradio_struct));

    if (pthread_create(&btinit_ctrl.worker_thread, NULL, \
          GORM_FW_Init_Thread, NULL) != 0) {
        LOG_ERR("Create FW init thread fails\n");
        return FALSE;
    }
    else {
        btinit_ctrl.worker_thread_running = TRUE;
        return TRUE;
    }
}

BOOL BT_DeinitDevice(VOID)
{
    LOG_DBG("BT_DeinitDevice\n");
    /* Do nothing on combo chip */
    return TRUE;
}

VOID BT_Cleanup(VOID)
{
    /* Cancel any remaining running thread */
    if (btinit_ctrl.worker_thread_running)
        notify_thread_exit();

    /*
     * Since Android M, pthread_exit only frees mapped space (including pthread_internal_t and thread stack)
     * for detached thread; for joinable thread, it is left for the pthread_join caller to clean up.
     *
     * The thread type is specified when thread create, default joinable for new thread if not set attribute with
     * PTHREAD_CREATE_DETATCHED, or not call pthread_detach before thread exit.
     */
    /* Always do pthread_join no matter the target thread has exited or not */
    pthread_join(btinit_ctrl.worker_thread, NULL);

    pthread_mutexattr_destroy(&btinit_ctrl.attr);
    pthread_mutex_destroy(&btinit_ctrl.mutex);
    pthread_condattr_destroy(&btinit_ctrl.condattr);
    pthread_cond_destroy(&btinit_ctrl.cond);

    return;
}
