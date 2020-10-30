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

#ifndef AUDIO_CUSTOMIZATION_COMMON_H
#define AUDIO_CUSTOMIZATION_COMMON_H


/***************************************************
*adjust boot animation volume. the volume range is from 0 to 1.
*****************************************************/
#ifdef BOOT_ANIMATION_VOLUME
#undef BOOT_ANIMATION_VOLUME
#endif
#define BOOT_ANIMATION_VOLUME       (0.25)

/***************************************************
*(1)->Use Ref Mic as main mic; (0)->Use original main mic.
*****************************************************/
#ifdef USE_REFMIC_IN_LOUDSPK
#undef USE_REFMIC_IN_LOUDSPK
#endif
#define USE_REFMIC_IN_LOUDSPK       (0)

/****************************************************
* Define this will enable audio compensation filter for loudspeaker
*Please see ACF Document for detail.
*****************************************************/
#ifdef ENABLE_AUDIO_COMPENSATION_FILTER
#undef ENABLE_AUDIO_COMPENSATION_FILTER
#endif
#define ENABLE_AUDIO_COMPENSATION_FILTER




/***************************************************
* Define this will enable headphone compensation filter.
*Please see HCF Document for detail.
*****************************************************/
#ifdef ENABLE_HEADPHONE_COMPENSATION_FILTER
#undef ENABLE_HEADPHONE_COMPENSATION_FILTER
#endif

#ifdef HEADPHONE_COMPENSATION_FLT_MODE
#undef HEADPHONE_COMPENSATION_FLT_MODE
#endif
#define HEADPHONE_COMPENSATION_FLT_MODE (4)


/***************************************************
*Define this will enable SW stereo to mono on LCH & RCH
*If not define this, HW stereo to mono (only LCH) will be applied.
*****************************************************/
#ifdef ENABLE_AUDIO_SW_STEREO_TO_MONO
#undef ENABLE_AUDIO_SW_STEREO_TO_MONO
#endif
#define ENABLE_AUDIO_SW_STEREO_TO_MONO


/***************************************************
*Define this will enable high samplerate record.
*****************************************************/
#ifdef ENABLE_HIGH_SAMPLERATE_RECORD
#undef ENABLE_HIGH_SAMPLERATE_RECORD
#endif
#define ENABLE_HIGH_SAMPLERATE_RECORD


/****************************************************
* WARNING: this macro is now obsolete, please change
* the property value ro.camera.sound.forced=1 to take effect.
*the property is defined in alps\mediatek\config\YOUR_PROJECT
*\system.prop.
*****************************************************/
//#define FORCE_CAMERA_SHUTTER_SOUND_AUDIBLE


/****************************************************
* Define this  , speaker output will not do stero to mono,
*keep in stereo format,because stereo output can apply
*on more than 1 speaker.
*****************************************************/
//#define ENABLE_STEREO_SPEAKER


/****************************************************
* Define this will enable Voice  to use  VoiceBuffer
*when using speaker and headphone in incall mode.
*****************************************************/
//#define ALL_USING_VOICEBUFFER_INCALL


/****************************************************
*Define this, audioflinger will use first active stream samplerate
*as hardware setting. it is only used for verifying hardware
*****************************************************/
//#define AUDIO_HQA_SUPPORT

/****************************************************
* Define this  , Audio Policy will apply ro.camera.sound.forced setting in mediatek/config/project_name/system.prop
* (Add this optionn because JB2 load is invalid
*****************************************************/
//#define ENABLE_CAMERA_SOUND_FORCED_SET

#ifdef AUDIO_DROP_FRAME_COUNT_NORMAL
#undef AUDIO_DROP_FRAME_COUNT_NORMAL
#endif
#define AUDIO_DROP_FRAME_COUNT_NORMAL 5
#ifdef AUDIO_DROP_FRAME_COUNT_RECORD
#undef AUDIO_DROP_FRAME_COUNT_RECORD
#endif
#define AUDIO_DROP_FRAME_COUNT_RECORD 5
#ifdef AUDIO_DROP_FRAME_COUNT_CTS
#undef AUDIO_DROP_FRAME_COUNT_CTS
#endif
#define AUDIO_DROP_FRAME_COUNT_CTS 5

/***************************************************
*(0)->copyright is asserted; (1)->no copyright is asserted.
*****************************************************/
#ifdef CHANNEL_STATUS_COPY_BIT
#undef CHANNEL_STATUS_COPY_BIT
#endif
#define CHANNEL_STATUS_COPY_BIT (1)

/***************************************************
*Specify category code (1 byte).
*****************************************************/
#ifdef CHANNEL_STATUS_CATEGORY_CODE
#undef CHANNEL_STATUS_CATEGORY_CODE
#endif
#define CHANNEL_STATUS_CATEGORY_CODE  (0x00)


/****************************************************
*Define this, HD Rec will use this for default param if no mode is set
*****************************************************/
#ifdef DEFAULT_HDRecordEnhanceParas
#undef DEFAULT_HDRecordEnhanceParas
#endif
#define DEFAULT_HDRecordEnhanceParas \
	0, 479, 16388, 36892, 37124, 8192,  768, 0,  4048, 2245, 611, 0, 0, 0, 0, 8192


/****************************************************
*Define MagiLoudness_TE_mode
*bit 0 earpiece DRC2.0  on=> bits 0 = 1
*bit 1 headset  DRC2.0  on=> bits 1 = 1
*bit 2 speaker  DRC2.0  on=> bits 2 = 1
*****************************************************/
#ifdef MagiLoudness_TE_mode
#undef MagiLoudness_TE_mode
#endif
#define MagiLoudness_TE_mode (0x0)


#ifdef DEFAULT_HDRecordCompenFilter
#undef DEFAULT_HDRecordCompenFilter
#endif
#define DEFAULT_HDRecordCompenFilter \
    32767,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
        0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
        0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
        0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
        0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
        0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
        0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
        0,     0,     0,     0,     0,     0,     0,     0,     0,     0, \
        0,     0,     0,     0,     0,     0,     0,     0,     0,     0
#endif
