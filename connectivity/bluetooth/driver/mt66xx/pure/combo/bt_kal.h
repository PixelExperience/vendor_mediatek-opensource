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

#ifndef _BT_KAL_H
#define _BT_KAL_H

#include "os_dep.h"


#define HCI_CMD_PARM_LEN   256
#define MAX_EVENT_SIZE     256

/* I/O attributes for read/write behavior */
#define WR_INTERRUPTIBLE 0x0001
#define RD_INTERRUPTIBLE 0x0002


/*
* Structure Definitions
*/

typedef struct _HCI_CMD_T {
  UINT16 opCode;  /* HCI command OpCode */
  UINT8  len;     /* Length of the command parameters */
  UINT8  parms[HCI_CMD_PARM_LEN];
} HCI_CMD_T;

typedef struct _HCI_EVENT_T {
  UINT8 event;    /* HCI event type */
  UINT8 len;      /* Length of the event parameters */
  UINT8 *parms;   /* Event specific parameters */
} HCI_EVENT_T;

typedef enum _ENUM_BT_STATUS_T {
  BT_STATUS_SUCCESS = 0,
  BT_STATUS_FAILED,
  BT_STATUS_PENDING,
  BT_STATUS_BUSY,
  BT_STATUS_NO_RESOURCES,
  BT_STATUS_NOT_FOUND,
  BT_STATUS_DEVICE_NOT_FOUND,
  BT_STATUS_CONNECTION_FAILED,
  BT_STATUS_TIMEOUT,
  BT_STATUS_NO_CONNECTION,
  BT_STATUS_INVALID_PARM,
  BT_STATUS_IN_PROGRESS,
  BT_STATUS_RESTRICTED,
  BT_STATUS_INVALID_TYPE,
  BT_STATUS_HCI_INIT_ERR,
  BT_STATUS_NOT_SUPPORTED,
  BT_STATUS_IN_USE,
  BT_STATUS_SDP_CONT_STATE,
  BT_STATUS_CANCELLED,
  BT_STATUS_NOSERVICES,
  BT_STATUS_SCO_REJECT,
  BT_STATUS_CHIP_REASON,
  BT_STATUS_BLOCK_LIST,
  BT_STATUS_SCATTERNET_REJECT
} ENUM_BT_STATUS_T;


/*
* Function Declaration
*/

typedef INT32 (*SETUP_UART_PARAM_T)(INT32 comPort, UINT32 u4Baud, UINT32 u4FlowControl);

BOOL BT_SendHciCommand(INT32 comPort, HCI_CMD_T *pHciCommand);

BOOL BT_ReadExpectedEvent(
  INT32   comPort,
  UINT8*  pEventPacket,
  UINT32  u4MaxBufSz,
  UINT32* pu4PktLen,
  UINT8   ucExpectedEventCode,
  BOOL    fCheckCompleteOpCode,
  UINT16  u2ExpectedOpCode,
  BOOL    fCheckCommandStatus,
  UINT8   ucExpectedStatus
);

int bt_send_data(int fd, unsigned char *buf, unsigned int len);
int bt_receive_data(int fd, unsigned char *buf, unsigned int len);

#endif
