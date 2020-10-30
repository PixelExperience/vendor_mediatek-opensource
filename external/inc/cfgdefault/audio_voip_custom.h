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

#ifndef AUDIO_VOIP_CUSTOM_H
#define AUDIO_VOIP_CUSTOM_H

/****************************************************
* Define default AP side VOIP parameters
*****************************************************/

//VoIP speech parameters common part
#define DEFAULT_VOIP_SPEECH_COMMON_PARAM  \
    0,  55997,  31000,    10752,      32769,      0,      0,      0, \
    0,      0,      0,      0


#ifdef __MTK_DUAL_MIC_SUPPORT__
#ifdef __MTK_VOIP_NORMAL_DMNR__
#define VOIP_SPEECH_MODE_PARA13 (371)
#define VOIP_SPEECH_MODE_PARA14 (23)
#define VOIP_SPEECH_MODE_PARA03 (29)
#define VOIP_SPEECH_MODE_PARA08 (400)
#else
#define VOIP_SPEECH_MODE_PARA13 (0)
#define VOIP_SPEECH_MODE_PARA14 (0)
#define VOIP_SPEECH_MODE_PARA03 (31)
#define VOIP_SPEECH_MODE_PARA08 (80)
#endif
#else
#define VOIP_SPEECH_MODE_PARA13 (0)
#define VOIP_SPEECH_MODE_PARA14 (0)
#define VOIP_SPEECH_MODE_PARA03 (31)
#define VOIP_SPEECH_MODE_PARA08 (80)
#endif

#ifdef __MTK_DUAL_MIC_SUPPORT__
#ifdef __MTK_VOIP_HANDSFREE_DMNR__
#define VOIP_SPEECH_SPK_MODE_PARA13 (307)
#define VOIP_SPEECH_SPK_MODE_PARA14 (31)
#define VOIP_SPEECH_SPK_MODE_PARA03 (29)
#define VOIP_SPEECH_SPK_MODE_PARA08 (400)      
#else
#define VOIP_SPEECH_SPK_MODE_PARA13 (0)
#define VOIP_SPEECH_SPK_MODE_PARA14 (0)
#define VOIP_SPEECH_SPK_MODE_PARA03 (29)
#define VOIP_SPEECH_SPK_MODE_PARA08 (276)  
#endif    
#else
#define VOIP_SPEECH_SPK_MODE_PARA13 (0)
#define VOIP_SPEECH_SPK_MODE_PARA14 (0)
#define VOIP_SPEECH_SPK_MODE_PARA03 (29)
#define VOIP_SPEECH_SPK_MODE_PARA08 (276)
#endif


//VoIP speech parameter different part
//1. normal mode
//2.loud speaker mode
//3. headset mode
//4.BT mode
#define DEFAULT_VOIP_SPEECH_MODE_PARAM \
    {128,   253, 6212,    VOIP_SPEECH_MODE_PARA03, 57351,   31,    0,    32, \
    VOIP_SPEECH_MODE_PARA08,  197,  611,     0, 13066,   0|VOIP_SPEECH_MODE_PARA13,    0|VOIP_SPEECH_MODE_PARA14,   0}, \
    \
    {192,   224,  2218,    VOIP_SPEECH_SPK_MODE_PARA03, 57351, 24607,    0,     4, \
    VOIP_SPEECH_SPK_MODE_PARA08,  197,   611,     0, 13066,     VOIP_SPEECH_SPK_MODE_PARA13,     VOIP_SPEECH_SPK_MODE_PARA14,     0}, \
    \
    {0,   189,  8196,    31, 57351,    31,      0,    64, \
    80,  197,   611,     0, 13066,     0,     0,     0}, \
    \
    {0,   253,  8196,    31, 53255,    31,      0,     0, \
    80,  197,   611,     0, 13066,    0,     0,      0}

//VoIP FIR parameter
//1. normal mode
//2.loud speaker mode
//3. headset mode
//4.BT mode
#define DEFAULT_VOIP_IN_FIR_PARAM \
    {32767,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0},  \
    \
    {32767,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0},  \
    \
    {32767,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0},  \
    \
    {32767,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0}

//VoIP FIR parameter
//1. normal mode
//2.loud speaker mode
//3. headset mode
//4.BT mode
#define DEFAULT_VOIP_OUT_FIR_PARAM \
    {32767,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0},  \
    \
    {32767,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0},  \
    \
    {32767,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0},  \
    \
    {32767,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0}

#endif
