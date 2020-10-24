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

#include "bt_vendor_lib.h"
#include "bt_mtk.h"

//===============        I N T E R F A C E S      =======================

int mtk_bt_init(const bt_vendor_callbacks_t* p_cb, UNUSED_ATTR unsigned char *local_bdaddr)
{
    LOG_TRC();

    store_bdaddr(local_bdaddr);

    set_callbacks(p_cb);
    return 0;
}

int mtk_bt_op(bt_vendor_opcode_t opcode, void *param)
{
    int ret = 0;

    switch(opcode)
    {
      case BT_VND_OP_POWER_CTRL:
        LOG_DBG("BT_VND_OP_POWER_CTRL %d\n", *((int*)param));
        /* DO NOTHING on combo chip */
        break;

      case BT_VND_OP_USERIAL_OPEN:
        LOG_DBG("BT_VND_OP_USERIAL_OPEN\n");

        ((int*)param)[0] = init_uart();
        ret = 1; /* CMD/EVT/ACL-In/ACL-Out via the same fd */
        break;

      case BT_VND_OP_USERIAL_CLOSE:
        LOG_DBG("BT_VND_OP_USERIAL_CLOSE\n");
        close_uart();
        break;

      case BT_VND_OP_FW_CFG:
        LOG_DBG("BT_VND_OP_FW_CFG\n");
        ret = mtk_fw_cfg();
        break;

      case BT_VND_OP_SCO_CFG: /* never called since Android O */
        LOG_DBG("BT_VND_OP_SCO_CFG\n");
        break;

      case BT_VND_OP_GET_LPM_IDLE_TIMEOUT:
        LOG_DBG("BT_VND_OP_GET_LPM_IDLE_TIMEOUT\n");
        *((uint32_t*)param) = 5000; //ms
        break;

      case BT_VND_OP_LPM_SET_MODE:
        LOG_DBG("BT_VND_OP_LPM_SET_MODE %d\n", *((uint8_t*)param));
        break;

      case BT_VND_OP_LPM_WAKE_SET_STATE:
        LOG_DBG("BT_VND_OP_LPM_WAKE_SET_STATE\n");
        break;

      case BT_VND_OP_EPILOG:
        LOG_DBG("BT_VND_OP_EPILOG\n");
        ret = mtk_prepare_off();
        break;

#if 0 /* MTK specific vendor opcode, deprecated since Android O */
      case BT_VND_OP_SET_FW_ASSERT:
        LOG_DBG("BT_VND_OP_SET_FW_ASSERT 0x%08x\n", *((uint32_t*)param));
        ret = mtk_set_fw_assert(*((uint32_t*)param));
        break;

      case BT_VND_OP_SET_PSM_CONTRL:
        LOG_DBG(" BT_VND_OP_SET_PSM_CONTRL, setting: %d\n", *((bool*)param));
        ret = mtk_set_psm_control(*((bool*)param));
        break;
#endif

      default:
        LOG_DBG("Unknown operation %d\n", opcode);
        ret = -1;
        break;
    }

    return ret;
}

void mtk_bt_cleanup()
{
    LOG_TRC();
    clean_callbacks();
    clean_resource();
    return;
}

const bt_vendor_interface_t BLUETOOTH_VENDOR_LIB_INTERFACE = {
    sizeof(bt_vendor_interface_t),
    mtk_bt_init,
    mtk_bt_op,
    mtk_bt_cleanup
};
