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
 * AudioCustParam.h
 *
 * Project:
 * --------
 *   Android
 *
 * Description:
 * ------------
 *   This file implements custom parameter setting.
 *
 * Author:
 * -------
 *   HP Cheng (mtk01752)
 *
 *******************************************************************************/

#ifndef _AUDIO_CUST_PARAM_H_
#define _AUDIO_CUST_PARAM_H_


/*=============================================================================
 *                              Include Files
 *===========================================================================*/
#include <utils/String8.h>
#include "CFG_AUDIO_File.h"


extern "C"
{

    typedef enum
    {
        SUPPORT_WB_SPEECH = 0x1,
        SUPPORT_DUAL_MIC = 0x2,
        SUPPORT_HD_RECORD = 0x4,
        SUPPORT_HD_48K_REC = 0x8,
        SUPPORT_DMNR_3_0 = 0x10,
        SUPPORT_DMNR_AT_MODEM = 0x20,
        SUPPORT_VOIP_ENHANCE = 0x40,
        SUPPORT_WIFI_ONLY = 0x80,
        SUPPORT_3G_DATA = 0x100,
        SUPPORT_NO_RECEIVER = 0x200,
        SUPPORT_ASR = 0x400,
        SUPPORT_VOIP_NORMAL_DMNR = 0x800,
        SUPPORT_VOIP_HANDSFREE_DMNR = 0x1000,
        SUPPORT_INCALL_NORMAL_DMNR = 0x2000,
        SUPPORT_INCALL_HANDSFREE_DMNR = 0x4000,
        SUPPORT_VOICE_UNLOCK = 0x8000,
        SUPPORT_DMNR_COMPLEX_ARCH = 0x10000,
        SUPPORT_GET_FO_VALUE = 0x20000,
        SUPPORT_SPEAKER_MONITOR = 0x40000,
        SUPPORT_BESLOUDNESS_V5 = 0x80000,
        SUPPORT_MAGI_CONFERENCE = 0x100000,
        SUPPORT_HAC = 0x200000,
        SUPPORT_SPEECH_LPBK = 0x400000,
        SUPPORT_BT_GAIN_TABLE = 0x800000,
        SUPPORT_AUDIO_BT_NREC_WO_ENH = 0x1000000,
        SUPPORT_AUDIO_SKIP_FM_MATV_VOL_TUNING = 0x2000000,
        SUPPORT_HFP = 0x4000000,
        SUPPORT_AUDIO_LAYERED_PARAM = 0x8000000,
        PHASE_OUT_HEADPHONE_COMPENSATION_FILTER = 0x10000000,
        FEATURE_SUPPORT_INFO_LIST_END
    } FeatureSupportInfo;


    /*=============================================================================
     *                              Class definition
     *===========================================================================*/

    int getNumMicSupport(void);

    uint32_t   QueryFeatureSupportInfo(void);

    // NB speech parameters
    // NB speech parameters
    int            GetNBSpeechParamFromNVRam(AUDIO_CUSTOM_PARAM_STRUCT *pSphParamNB);
    int            SetNBSpeechParamToNVRam(AUDIO_CUSTOM_PARAM_STRUCT *pSphParamNB);

    // Dual mic speech parameters
    int            GetDualMicSpeechParamFromNVRam(AUDIO_CUSTOM_EXTRA_PARAM_STRUCT *pSphParamDualMic);
    int            SetDualMicSpeechParamToNVRam(AUDIO_CUSTOM_EXTRA_PARAM_STRUCT *pSphParamDualMic);

    // WB speech parameters
    int            GetWBSpeechParamFromNVRam(AUDIO_CUSTOM_WB_PARAM_STRUCT *pSphParamWB);
    int            SetWBSpeechParamToNVRam(AUDIO_CUSTOM_WB_PARAM_STRUCT *pSphParamWB);

    // Med param parameter
    int            GetMedParamFromNV(AUDIO_PARAM_MED_STRUCT *pPara);
    int            SetMedParamToNV(AUDIO_PARAM_MED_STRUCT *pPara);

    // VolumeVer1 parameter
    int            GetVolumeVer1ParamFromNV(AUDIO_VER1_CUSTOM_VOLUME_STRUCT *pPara);
    int            SetVolumeVer1ParamToNV(AUDIO_VER1_CUSTOM_VOLUME_STRUCT *pPara);

    // Audio Custom Paramete
    int            GetAudioCustomParamFromNV(AUDIO_VOLUME_CUSTOM_STRUCT *pPara);
    int            SetAudioCustomParamToNV(AUDIO_VOLUME_CUSTOM_STRUCT *pPara);

    // AudioGainTable Parameter
    int            GetAudioGainTableParamFromNV(AUDIO_GAIN_TABLE_STRUCT *pPara);
    int            SetAudioGainTableParamToNV(AUDIO_GAIN_TABLE_STRUCT *pPara);

    // Audio HD record parameters
    int            GetHdRecordParamFromNV(AUDIO_HD_RECORD_PARAM_STRUCT *pPara);
    int            SetHdRecordParamToNV(AUDIO_HD_RECORD_PARAM_STRUCT *pPara);

    //  Audio HD record scene table
    int            GetHdRecordSceneTableFromNV(AUDIO_HD_RECORD_SCENE_TABLE_STRUCT *pPara);
    int            SetHdRecordSceneTableToNV(AUDIO_HD_RECORD_SCENE_TABLE_STRUCT *pPara);

    // Audio VoIP Parameters
    int            GetAudioVoIPParamFromNV(AUDIO_VOIP_PARAM_STRUCT *pPara);
    int            SetAudioVoIPParamToNV(AUDIO_VOIP_PARAM_STRUCT *pPara);

    // Audio HFP Parameters
    int            GetAudioHFPParamFromNV(AUDIO_HFP_PARAM_STRUCT *pPara);
    int            SetAudioHFPParamToNV(AUDIO_HFP_PARAM_STRUCT *pPara);

    // MagiConference Call parameters
    int            GetMagiConSpeechParamFromNVRam(AUDIO_CUSTOM_MAGI_CONFERENCE_STRUCT *pSphParamMagiCon);
    int            SetMagiConSpeechParamToNVRam(AUDIO_CUSTOM_MAGI_CONFERENCE_STRUCT *pSphParamMagiCon);

    // HAC parameters
    int            GetHACSpeechParamFromNVRam(AUDIO_CUSTOM_HAC_PARAM_STRUCT *pSphParamHAC);
    int            SetHACSpeechParamToNVRam(AUDIO_CUSTOM_HAC_PARAM_STRUCT *pSphParamHAC);

    // Speech Loopback parameters
    int            GetNBSpeechLpbkParamFromNVRam(AUDIO_CUSTOM_SPEECH_LPBK_PARAM_STRUCT *pSphParamNBLpbk);
    int            SetNBSpeechLpbkParamToNVRam(AUDIO_CUSTOM_SPEECH_LPBK_PARAM_STRUCT *pSphParamNBLpbk);

    // BT Gain parameter
    int            GetAudioBTGainParamFromNV(AUDIO_BT_GAIN_STRUCT *pParaBT);
    int            SetAudioBTGainParamToNV(AUDIO_BT_GAIN_STRUCT *pParaBT);

}

#endif




