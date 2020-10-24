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



/**MTK BT specific operations OPCODE  */
typedef enum {
/*  [operation]
 *      Return audio configuration for BT SCO on current chipset
 *  [input param]
 *      A pointer to union type with content of BT_INFO.
 *      Typecasting conversion: (BT_INFO *) param.
 *  [return]
 *      0 - default, don't care.
 *  [callback]
 *      None.
 */
    BT_MTK_OP_AUDIO_GET_CONFIG,
  /* Audio config related information */
} bt_mtk_opcode_t;

typedef enum {
  PCM = 0,          // PCM 4 pins interface
  I2S,              // I2S interface
  MERGE_INTERFACE,  // PCM & I2S merge interface
  CVSD_REMOVAL      // SOC consys
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
  unsigned int       bit_len;  // bit-length of sync frame in long frame sync
} AUDIO_CONFIG;

/* Information carring for all OPs (In/Out) */
typedef union {
  AUDIO_CONFIG       audio_conf;
} BT_INFO;


/* For BT_AUDIO_GET_CONFIG */
struct audio_t {
  unsigned int chip_id;
  AUDIO_CONFIG audio_conf;
};

/********************************************************************************
** Function Declaration
*/


int mtk_bt_op(bt_mtk_opcode_t opcode, void *param);




#endif
