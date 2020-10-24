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

#ifndef _BT_MTK_H
#define _BT_MTK_H

#include "bt_hci_bdroid.h"
#include "bt_vendor_lib.h"
#include "os_dep.h"


#define HCI_CMD_MAX_SIZE        251


/***********   Structure Definitions   ***********/

typedef enum {
  CMD_SUCCESS,
  CMD_FAIL,
  CMD_PENDING,
} HCI_CMD_STATUS_T;

typedef BOOL (*HCI_CMD_FUNC_T) (HC_BT_HDR *);
typedef struct {
  HCI_CMD_FUNC_T command_func;
} HCI_SEQ_T;

typedef INT32 (*SETUP_UART_PARAM_T)(UINT32 u4Baud, UINT32 u4FlowControl);

typedef struct {
  UINT32 chip_id;
  UINT32 bt_baud;
  UINT32 host_baud;
  UINT32 flow_ctrl;
  SETUP_UART_PARAM_T host_uart_cback;
  PUCHAR patch_ext_data;
  UINT32 patch_ext_len;
  UINT32 patch_ext_offset;
  PUCHAR patch_data;
  UINT32 patch_len;
  UINT32 patch_offset;
  HCI_SEQ_T *cur_script;
} BT_INIT_VAR_T;

/* Thread control block for Controller initialize */
typedef struct {
  pthread_t worker_thread;
  pthread_mutex_t mutex;
  pthread_mutexattr_t attr;
  pthread_cond_t cond;
  BOOL worker_thread_running;
} BT_INIT_CB_T;

typedef enum {
  BT_HCI_CMD = 0x01,
  BT_ACL,
  BT_SCO,
  BT_HCI_EVENT
} BT_HDR_T;

/***********   Function Declaration   ***********/
void set_callbacks(const bt_vendor_callbacks_t* p_cb);
void clean_callbacks(void);
int init_uart(void);
void close_uart(void);
int mtk_prepare_off(void);
void clean_resource(void);
void vendor_fw_cfg(void);
void vendor_op_lmp_set_mode(void);

#endif
