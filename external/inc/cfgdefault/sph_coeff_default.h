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

/*******************************************************************************
 *
 * Filename:
 * ---------
 * sph_coeff_default.h
 *
 * Project:
 * --------
 *   ALPS
 *
 * Description:
 * ------------
 * default value of speech parameters in NVRAM
 *
 * Author:
 * -------
 * Tina Tsai
 *
 *******************************************************************************/
#ifndef SPEECH_COEFF_DEFAULT_H
#define SPEECH_COEFF_DEFAULT_H

#ifndef FALSE
  #define FALSE 0
#endif

#define BT_SYNC_DELAY  86

#if defined(__MTK_DUAL_MIC_SUPPORT__)
  #ifndef MTK_INTERNAL
    #define SPEECH_MODE_PARA13 (371)
    #define SPEECH_MODE_PARA14 (23)
    #define SPEECH_MODE_PARA03 (29)
    #define SPEECH_MODE_PARA08 (400)
  #else
    #define SPEECH_MODE_PARA13 (0)
    #define SPEECH_MODE_PARA14 (0)
    #define SPEECH_MODE_PARA03 (31)
    #define SPEECH_MODE_PARA08 (80)
  #endif
#else
  #define SPEECH_MODE_PARA13 (0)
  #define SPEECH_MODE_PARA14 (0)
  #define SPEECH_MODE_PARA03 (31)
  #define SPEECH_MODE_PARA08 (80)
#endif

#if (defined(__NXP_SMARTPA_SUPPORT__) || defined(__MTK_SPEAKER_MONITOR_SUPPORT__))
  #define MANUAL_CLIPPING (1 << 15)
  #define NXP_DELAY_REF   (1 << 6)
  #define PRE_CLIPPING_LEVEL 32767
#else
  #define MANUAL_CLIPPING (0 << 15)
  #define NXP_DELAY_REF   (0 << 6)
  #define PRE_CLIPPING_LEVEL 10752
#endif

#define DEFAULT_SPEECH_NORMAL_MODE_PARA \
   96, 253, 16388, SPEECH_MODE_PARA03, 57351, 799, 400, 64, \
   SPEECH_MODE_PARA08, 4325, 611, 0, 20488, 0|SPEECH_MODE_PARA13, 0|SPEECH_MODE_PARA14, 8192

#define DEFAULT_SPEECH_EARPHONE_MODE_PARA \
    0, 189, 10756, 31, 57351, 31, 400, 64, \
    80, 4325, 611, 0, 20488, 0, 0, 0

#define DEFAULT_SPEECH_BT_EARPHONE_MODE_PARA \
     0, 253, 10756, 31, 53263, 31, 400, 0, \
    80, 4325, 16995, 0, 20488, 0, 0, BT_SYNC_DELAY

#define DEFAULT_SPEECH_LOUDSPK_MODE_PARA \
    96|MANUAL_CLIPPING , 224, 5256, 31, 57351, 24607, 400, 132, \
    84, 4325, 611, 0, 20488|NXP_DELAY_REF, 0, 0, 0

#define DEFAULT_SPEECH_CARKIT_MODE_PARA \
     0, 479, 10756, 1052, 53258, 28, 400, 0, \
    80, 4325, 16995, 0, 20488, 0, 0, BT_SYNC_DELAY

#define DEFAULT_SPEECH_BT_CORDLESS_MODE_PARA \
     0, 479, 10756, 28, 53255, 31, 400, 0, \
    4048, 4325, 611, 0, 20488, 0, 0, BT_SYNC_DELAY

#define DEFAULT_SPEECH_AUX1_MODE_PARA \
    0, 0, 0, 0, 0, 0, 0, 0, \
    0, 0, 0, 0, 0, 0, 0, 0

#define DEFAULT_SPEECH_AUX2_MODE_PARA \
    0, 0, 0, 0, 0, 0, 0, 0, \
    0, 0, 0, 0, 0, 0, 0, 0

#define DEFAULT_SPEECH_VOICE_TRACKING_MODE_PARA \
    96|MANUAL_CLIPPING , 224, 5256, 31, 57351, 24607, 400, 132, \
    84, 4325, 611, 0, 8200|NXP_DELAY_REF, 883, 23, 0

#define DEFAULT_SPEECH_HAC_MODE_PARA \
   96, 253, 16388, SPEECH_MODE_PARA03, 57351, 799, 400, 64, \
   SPEECH_MODE_PARA08, 4325, 611, 0, 20488, 0|SPEECH_MODE_PARA13, 0|SPEECH_MODE_PARA14, 8192
#define DEFAULT_SPEECH_COMMON_PARA \
    0, 55997, 31000, PRE_CLIPPING_LEVEL, 32769, 0, 0, 0, \
    0, 0, 0, 0

#define DEFAULT_SPEECH_VOL_PARA \
    0, 0, 0, 0

#define DEFAULT_AUDIO_DEBUG_INFO \
    0, 0, 0, 0, 0, 0, 0, 0, \
    0, 0, 0, 0, 0, 0, 0, 0

#define DEFAULT_VM_SUPPORT  FALSE

#define DEFAULT_AUTO_VM     FALSE

#define MICBAIS     1900

#define DEFAULT_WB_SPEECH_NORMAL_MODE_PARA \
    96, 253, 16388, SPEECH_MODE_PARA03, 57607, 799, 400, 64, \
    SPEECH_MODE_PARA08, 4325, 611, 0, 16392, 0|SPEECH_MODE_PARA13, 0|SPEECH_MODE_PARA14, 8192

#define DEFAULT_WB_SPEECH_EARPHONE_MODE_PARA \
     0, 189, 10756, 31, 57607, 31, 400, 64, \
    80, 4325, 611, 0, 16392, 0, 0, 0

#define DEFAULT_WB_SPEECH_BT_EARPHONE_MODE_PARA \
     0, 253, 10756, 31, 53519, 31, 400, 0, \
    80, 4325, 16995, 0, 16392, 0, 0, BT_SYNC_DELAY

#define DEFAULT_WB_SPEECH_LOUDSPK_MODE_PARA \
    96|MANUAL_CLIPPING, 224, 5256, 31, 57607, 24607, 400, 132, \
    84, 4325, 611, 0, 16392|NXP_DELAY_REF, 0, 0, 0

#define DEFAULT_WB_SPEECH_CARKIT_MODE_PARA \
     0, 479, 10756, 1052, 53514, 28, 400, 0, \
    80, 4325, 16995, 0, 16392, 0, 0, BT_SYNC_DELAY

#define DEFAULT_WB_SPEECH_BT_CORDLESS_MODE_PARA \
     0, 479, 10756, 28, 53511, 31, 400, 0, \
    4048, 4325, 611, 0, 16392, 0, 0, BT_SYNC_DELAY

#define DEFAULT_WB_SPEECH_AUX1_MODE_PARA \
    96, 224, 5256, 31, 57607, 0, 400, 0, 4112, 4325, 11, 0, 0, 0, 0, 0

#define DEFAULT_WB_SPEECH_AUX2_MODE_PARA \
    0, 0, 0, 0, 0, 0, 0, 0, \
    0, 0, 0, 0, 0, 0, 0, 0

#define DEFAULT_WB_SPEECH_VOICE_TRACKING_MODE_PARA \
    96|MANUAL_CLIPPING, 224, 5256, 31, 57607, 24607, 400, 132, \
    84, 4325, 611, 0, 8200|NXP_DELAY_REF, 883, 23, 0

#define DEFAULT_WB_SPEECH_HAC_MODE_PARA \
    96, 253, 16388, SPEECH_MODE_PARA03, 57607, 799, 400, 64, \
    SPEECH_MODE_PARA08, 4325, 611, 0, 16392, 0|SPEECH_MODE_PARA13, 0|SPEECH_MODE_PARA14, 8192

/* The Bluetooth PCM digital volume */
/* default_bt_pcm_in_vol : uplink, only for enlarge volume,
                           0x100 : 0dB  gain
                           0x200 : 6dB  gain
                           0x300 : 9dB  gain
                           0x400 : 12dB gain
                           0x800 : 18dB gain
                           0xF00 : 24dB gain             */
#define DEFAULT_BT_PCM_IN_VOL        0x100
/* default_bt_pcm_out_vol : downlink gain,
                           0x1000 : 0dB; maximum 0x7FFF  */
#define DEFAULT_BT_PCM_OUT_VOL       0x1000


#endif
