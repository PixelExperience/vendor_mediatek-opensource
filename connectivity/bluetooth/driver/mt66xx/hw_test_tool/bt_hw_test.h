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

#ifndef __BT_HW_TEST_H__
#define __BT_HW_TEST_H__

#include <stdbool.h>
#include <cutils/properties.h>
#ifndef FALSE
#define FALSE     0
#endif
#ifndef TRUE
#define TRUE      1
#endif
#ifndef BOOL
#define BOOL      bool
#endif

typedef unsigned char UCHAR;
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;

#define UNUSED_ATTR __attribute__((unused))

/* LOG_TAG must be defined before log.h */
#define LOG_TAG         "BT_HW_TEST "
#include <log/log.h>

#define BT_HW_TEST_DEBUG     1
#define ERR(f, ...)     ALOGE("%s: " f, __FUNCTION__, ##__VA_ARGS__)
#define WAN(f, ...)     ALOGW("%s: " f, __FUNCTION__, ##__VA_ARGS__)
#if BT_HW_TEST_DEBUG
#define DBG(f, ...)     ALOGD("%s: " f, __FUNCTION__, ##__VA_ARGS__)
#define TRC(f)          ALOGW("%s #%d", __FUNCTION__, __LINE__)
#else
#define DBG(...)        ((void)0)
#define TRC(f)          ((void)0)
#endif


#ifndef BIT
#define BIT(n)                          ((UINT8) 1 << (n))
#endif /* BIT */

#ifndef BITS
/* bits range: for example BITS(0,3) = 0x0F
 *   ==>  (BIT(m)-1)   = 0x00     ~(BIT(m)-1)   => 0xFF
 *   ==>  (BIT(n+1)-1) = 0x0F
 */

#define BITS(m, n)                       (~(BIT(m)-1) & ((BIT(n) - 1) | BIT(n)))
#endif /* BIT */

/*
* Exported Function Declaration
*/
#ifdef __cplusplus
extern "C"
{
#endif
BOOL HW_TEST_BT_init(void);
void HW_TEST_BT_deinit(void);
BOOL HW_TEST_BT_reset(void);
BOOL HW_TEST_BT_PDN_UT(UINT8 pdn_length);
BOOL HW_TEST_BT_PDN_SET_CLOCK(UINT8 clk_rate);
void * HW_TEST_BT_PDN_LOOP(void *ptr);

BOOL HW_TEST_BT_TxOnlyTest_start(
  UINT8 tx_pattern,
  UINT8 hopping,
  int channel,
  UINT8 packet_type,
  UINT32 packet_len
);

BOOL HW_TEST_BT_TxOnlyTest_end(void);

BOOL HW_TEST_BT_NonSignalRx_start(
  UINT8 rx_pattern,
  int channel,
  UINT8 packet_type,
  UINT32 tester_addr
);

BOOL HW_TEST_BT_NonSignalRx_end(
  UINT32 *pu4RxPktCount,
  float  *pftPktErrRate,
  UINT32 *pu4RxByteCount,
  float  *pftBitErrRate
);

BOOL HW_TEST_BT_TestMode_enter(int power);
BOOL HW_TEST_BT_TestMode_exit(void);

typedef void (*FUNC_CB)(char *info);
typedef struct {
    FUNC_CB info_cb;
    UINT8 pdn_length;
    UINT16 pdn_interval_ms;
}pdn_arg_struct;

BOOL HW_TEST_BT_Inquiry(FUNC_CB info_cb);

BOOL HW_TEST_BT_LE_Tx_start(UINT8 tx_pattern, int channel);
BOOL HW_TEST_BT_LE_Enhanced_Tx_start(int channel, UINT32 payload_len, UINT8 pattern, UINT8 phy_rate);
BOOL HW_TEST_BT_LE_Tx_end(void);

BOOL HW_TEST_BT_LE_Rx_start(int channel);
BOOL HW_TEST_BT_LE_Enhanced_Rx_start(int channel, UINT8 phy_rate, UINT8 index);
BOOL HW_TEST_BT_LE_Rx_end(UINT16 *pu2RxPktCount);


#ifdef __cplusplus
}
#endif

#endif
