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

#ifndef __BT_DRV_IF_H__
#define __BT_DRV_IF_H__

typedef enum {
  BT_COLD_OP_GET_ADDR = 0,
  BT_HOT_OP_SET_FWASSERT,
  BT_AUDIO_OP_GET_CONFIG
} BT_OP;

/* Audio config related defination */
typedef enum {
  PCM = 0,         // PCM 4 pins interface
  I2S,             // I2S interface
  MERGE_INTERFACE, // PCM & I2S merge interface
  CVSD_REMOVAL     // SOC consys
} AUDIO_IF;

typedef enum {
  SYNC_8K = 0,
  SYNC_16K
} SYNC_CLK;        // DAIBT sample rate

typedef enum {
  SHORT_FRAME = 0,
  LONG_FRAME
} SYNC_FORMAT;     // DAIBT sync

typedef struct {
  AUDIO_IF           hw_if;
  SYNC_CLK           sample_rate;
  SYNC_FORMAT        sync_format;
  unsigned int       bit_len; // bit-length of sync frame in long frame sync
} AUDIO_CONFIG;

/* Information carring for all OPs (In/Out) */
typedef union {
  unsigned char      addr[7];
  struct {
    int              fd;
    int              reason;
  } assert;
  AUDIO_CONFIG       audio_conf;
} BT_INFO;

typedef struct {
  BT_OP              op;
  BT_INFO            param;
} BT_REQ;

typedef struct {
  unsigned char      status;
  BT_INFO            param;
} BT_RESULT;

typedef void (*rx_callback)();



int mtk_bt_enable(int flag, rx_callback func_cb);
int mtk_bt_disable(int bt_fd);
int mtk_bt_write(int bt_fd, unsigned char *buffer, unsigned short length);
int mtk_bt_read(int bt_fd, unsigned char *buffer, unsigned short length);
void mtk_bt_op(BT_REQ req, BT_RESULT *result);

#endif
