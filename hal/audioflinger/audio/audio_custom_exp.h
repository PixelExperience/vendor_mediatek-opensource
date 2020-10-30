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
 * audio_custom_exp.h
 *
 * Project:
 * --------
 *   ALPS
 *
 * Description:
 * ------------
 * This file is the header of audio customization related function or definition.
 *
 * Author:
 * -------
 * ChiPeng
 *
***********************************************************************************/

#ifndef AUDIO_CUSTOM_EXP_H
#define AUDIO_CUSTOM_EXP_H

#include "Audio_Customization_Common.h"

/*********************************************************************************
*Common definitations  are  defined  in below  file 
*alps\mediatek\custom\common\hal\audioflinger\Audio_Customization_Common.h.
*if  some of  common definitations are not need, the specific customer  can mark the definitation in
* Audio_Customization_Common.h or  can undefine  the definitations in this file,just like:
*#undef ENABLE_AUDIO_COMPENSATION_FILTER
***********************************************************************************/
#ifdef ENABLE_HEADPHONE_COMPENSATION_FILTER
#undef ENABLE_HEADPHONE_COMPENSATION_FILTER
#endif

/*****************************************************************
** refine volume
*****************************************************************/
#ifdef DEVICE_MAX_VOLUME
#undef DEVICE_MAX_VOLUME
#endif
#define DEVICE_MAX_VOLUME       (8)
#ifdef DEVICE_VOICE_MAX_VOLUME
#undef DEVICE_VOICE_MAX_VOLUME
#endif
#define DEVICE_VOICE_MAX_VOLUME (8)
#ifdef DEVICE_AMP_MAX_VOLUME
#undef DEVICE_AMP_MAX_VOLUME
#endif
#define DEVICE_AMP_MAX_VOLUME   (15)
#ifdef DEVICE_MIN_VOLUME
#undef DEVICE_MIN_VOLUME
#endif
#define DEVICE_MIN_VOLUME       (-4)
#ifdef DEVICE_VOICE_MIN_VOLUME
#undef DEVICE_VOICE_MIN_VOLUME
#endif
#define DEVICE_VOICE_MIN_VOLUME (-4)
#ifdef DEVICE_AMP_MIN_VOLUME
#undef DEVICE_AMP_MIN_VOLUME
#endif
#define DEVICE_AMP_MIN_VOLUME   (6)
#ifdef DEVICE_VOLUME_RANGE
#undef DEVICE_VOLUME_RANGE
#endif
#define DEVICE_VOLUME_RANGE     (64)
#ifdef DEVICE_VOLUME_STEP
#undef DEVICE_VOLUME_STEP
#endif
#define DEVICE_VOLUME_STEP      (256)

/******************************************************************
** define Vibration SPK Default Center Freq and RMS
******************************************************************/
#ifdef VIBSPK_MV_RMS
#undef VIBSPK_MV_RMS
#endif
#define VIBSPK_MV_RMS           (350) //280~560, 70 per step
#ifdef VIBSPK_DEFAULT_FREQ
#undef VIBSPK_DEFAULT_FREQ
#endif
#define VIBSPK_DEFAULT_FREQ     (156) //141~330 Hz

/******************************************************************
** define using which flag
******************************************************************/
#ifdef USING_CLASSD_AMP
#undef USING_CLASSD_AMP
#endif
#define USING_CLASSD_AMP                // define using which flag
//#define USING_CLASSAB_AMP

/******************************************************************
** define chip delay for NXP
******************************************************************/
#ifdef CHIP_DELAY
#undef CHIP_DELAY
#endif
#define CHIP_DELAY				(22)

/***************************************************
* Define phonmic and headset mic mode.
typedef enum
{
    AUDIO_MIC_MODE_ACC = 1,
    AUDIO_MIC_MODE_DCC = 2,
    AUDIO_MIC_MODE_DMIC = 3,
    AUDIO_MIC_MODE_DMIC_LP = 4,
    AUDIO_MIC_MODE_DCCECMDIFF = 5,
    AUDIO_MIC_MODE_DCCECMSINGLE = 6,
} AUDIO_MIC_MODE;
*****************************************************/
#ifdef PHONE_MIC_MODE
#undef PHONE_MIC_MODE
#endif
#define PHONE_MIC_MODE (2)
#ifdef HEADSET_MIC_MODE
#undef HEADSET_MIC_MODE
#endif
#define HEADSET_MIC_MODE (2)
#ifdef MAIN_REF_MIC_INVERSE
#undef MAIN_REF_MIC_INVERSE
#endif
#define MAIN_REF_MIC_INVERSE 1

#endif

