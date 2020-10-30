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

/*****************************************************************************
 *
 * Filename:
 * ---------
 *   CFG_file_info_custom.h
 *
 * Project:
 * --------
 *   YuSu
 *
 * Description:
 * ------------
 *   Configuration File List for Customer
 *
 *
 * Author:
 * -------
 *   Nick Huang (mtk02183)
 *
 ****************************************************************************/

#ifndef __CFG_FILE_INFO_CUSTOM_H__
#define __CFG_FILE_INFO_CUSTOM_H__

#include "CFG_file_public.h"
#include "CFG_file_lid.h"
#include "cfgdefault/inc/Custom_NvRam_LID.h"
#include "cfgfileinc/CFG_AUDIO_File.h"
#include "cfgdefault/CFG_Audio_Default.h"
#include "cfgfileinc/CFG_GPS_File.h"
#include "cfgdefault/CFG_GPS_Default.h"
#include "cfgfileinc/CFG_Wifi_File.h"
#include "cfgdefault/CFG_WIFI_Default.h"
#include "cfgfileinc/CFG_PRODUCT_INFO_File.h"
#include "cfgdefault/CFG_PRODUCT_INFO_Default.h"
#include "cfgfileinc/CFG_FG_File.h"
#include "cfgdefault/CFG_FG_Default.h"
#include "cfgfileinc/CFG_SMARTPA_CALIB_File.h"
#include "cfgdefault/CFG_SMARTPA_CALIB_Default.h"
#include <stdio.h>
#ifdef __cplusplus
extern "C"
{
#endif

    const TCFG_FILE g_akCFG_File_Custom[]=
    {
        {
            "/mnt/vendor/nvdata/media/Audio_Sph",       VER(AP_CFG_RDCL_FILE_AUDIO_LID),         CFG_FILE_SPEECH_REC_SIZE,
            CFG_FILE_SPEECH_REC_TOTAL,                   SIGNLE_DEFUALT_REC,                                   (char *)&speech_custom_default, DataReset , NULL
        },

        {
            "/mnt/vendor/nvdata/APCFG/APRDEB/GPS",         VER(AP_CFG_CUSTOM_FILE_GPS_LID),	           CFG_FILE_GPS_CONFIG_SIZE,
            CFG_FILE_GPS_CONFIG_TOTAL,                  SIGNLE_DEFUALT_REC,                (char *)&stGPSConfigDefault, DataReset , NULL
        },

        {
            "/mnt/vendor/nvdata/media/Audio_CompFlt",       VER(AP_CFG_RDCL_FILE_AUDIO_COMPFLT_LID),         CFG_FILE_AUDIO_COMPFLT_REC_SIZE,
            CFG_FILE_AUDIO_COMPFLT_REC_TOTAL,                   SIGNLE_DEFUALT_REC,                (char *)&audio_custom_default, DataReset , NULL
        },

        {
            "/mnt/vendor/nvdata/media/Audio_Effect",       VER(AP_CFG_RDCL_FILE_AUDIO_EFFECT_LID),         CFG_FILE_AUDIO_EFFECT_REC_SIZE,
            CFG_FILE_AUDIO_EFFECT_REC_TOTAL,                   SIGNLE_DEFUALT_REC,                (char *)&audio_effect_custom_default, DataReset , NULL
        },

        {
            "/mnt/vendor/nvdata/APCFG/APRDEB/WIFI",	    	VER(AP_CFG_RDEB_FILE_WIFI_LID),		    CFG_FILE_WIFI_REC_SIZE,
            CFG_FILE_WIFI_REC_TOTAL,		    	SIGNLE_DEFUALT_REC,				    (char *)&stWifiCfgDefault, DataReset , NULL
        },

        {
            "/mnt/vendor/nvdata/APCFG/APRDEB/WIFI_CUSTOM",	VER(AP_CFG_RDEB_WIFI_CUSTOM_LID),	CFG_FILE_WIFI_CUSTOM_REC_SIZE,
            CFG_FILE_WIFI_CUSTOM_REC_TOTAL,		    SIGNLE_DEFUALT_REC,				    (char *)&stWifiCustomDefault, DataReset , NULL
        },

        {
            "/mnt/vendor/nvdata/media/Audio_Sph_Med",       VER(AP_CFG_RDCL_FILE_AUDIO_PARAM_MED_LID),         CFG_FILE_AUDIO_PARAM_MED_REC_SIZE,
            CFG_FILE_AUDIO_PARAM_MED_REC_TOTAL,                   SIGNLE_DEFUALT_REC,                (char *)&audio_param_med_default, DataReset , NULL
        },

        {
            "/mnt/vendor/nvdata/media/Audio_Vol_custom",       VER(AP_CFG_RDCL_FILE_AUDIO_VOLUME_CUSTOM_LID),         CFG_FILE_AUDIO_VOLUME_CUSTOM_REC_SIZE,
            CFG_FILE_AUDIO_VOLUME_CUSTOM_REC_TOTAL,           SIGNLE_DEFUALT_REC,                (char *)&audio_volume_custom_default, DataReset , NULL
        },

        {
            "/mnt/vendor/nvdata/media/Sph_Dual_Mic",       VER(AP_CFG_RDCL_FILE_DUAL_MIC_CUSTOM_LID),         CFG_FILE_SPEECH_DUAL_MIC_SIZE,
            CFG_FILE_SPEECH_DUAL_MIC_TOTAL,           SIGNLE_DEFUALT_REC,                (char *)&dual_mic_custom_default, DataReset , NULL
        },

        {
            "/mnt/vendor/nvdata/media/Audio_Wb_Sph",       VER(AP_CFG_RDCL_FILE_AUDIO_WB_PARAM_LID),         CFG_FILE_WB_SPEECH_REC_SIZE,
            CFG_FILE_WB_SPEECH_REC_TOTAL,                   SIGNLE_DEFUALT_REC,                                   (char *)&wb_speech_custom_default, DataReset , NULL
        },

        {
            "/mnt/vendor/nvdata/APCFG/APRDEB/PRODUCT_INFO",       VER(AP_CFG_REEB_PRODUCT_INFO_LID),         CFG_FILE_PRODUCT_INFO_SIZE,
            CFG_FILE_PRODUCT_INFO_TOTAL,                   SIGNLE_DEFUALT_REC,                                   (char *)&stPRODUCT_INFOConfigDefault,DataReset, NULL
        },

        {
            "/mnt/vendor/nvdata/media/Headphone_CompFlt",       VER(AP_CFG_RDCL_FILE_HEADPHONE_COMPFLT_LID),         CFG_FILE_AUDIO_COMPFLT_REC_SIZE,
            CFG_FILE_HEADPHONE_COMPFLT_REC_TOTAL,                   SIGNLE_DEFUALT_REC,                (char *)&audio_hcf_custom_default, DataReset , NULL
        },

        { "/mnt/vendor/nvdata/media/Audio_gain_table",   VER(AP_CFG_RDCL_FILE_AUDIO_GAIN_TABLE_LID), CFG_FILE_AUDIO_GAIN_TABLE_CUSTOM_REC_SIZE,
            CFG_FILE_AUDIO_GAIN_TABLE_CUSTOM_REC_TOTAL, SIGNLE_DEFUALT_REC  ,	 (char *)&Gain_control_table_default, DataReset , NULL
        },

        {
            "/mnt/vendor/nvdata/media/Audio_ver1_Vol_custom",       VER(AP_CFG_RDCL_FILE_AUDIO_VER1_VOLUME_CUSTOM_LID),         CFG_FILE_AUDIO_VER1_VOLUME_CUSTOM_REC_SIZE,
            CFG_FILE_AUDIO_VER1_VOLUME_CUSTOM_REC_TOTAL,           SIGNLE_DEFUALT_REC,                (char *)&audio_ver1_custom_default, DataReset , NULL
        },
        
        { "/mnt/vendor/nvdata/media/Audio_Hd_Record_Param",   VER(AP_CFG_RDCL_FILE_AUDIO_HD_REC_PAR_LID), CFG_FILE_AUDIO_HD_REC_PAR_SIZE,
            CFG_FILE_AUDIO_HD_REC_PAR_TOTAL, SIGNLE_DEFUALT_REC  ,    (char *)&Hd_Recrod_Par_default, DataReset , NULL
        },
        
        { "/mnt/vendor/nvdata/media/Audio_Hd_Record_Scene_Table",   VER(AP_CFG_RDCL_FILE_AUDIO_HD_REC_SCENE_LID), CFG_FILE_AUDIO_HD_REC_SCENE_TABLE_SIZE,
            CFG_FILE_AUDIO_HD_REC_SCENE_TABLE_TOTAL, SIGNLE_DEFUALT_REC  ,    (char *)&Hd_Recrod_Scene_Table_default, DataReset , NULL
        },
        
        { "/mnt/vendor/nvdata/media/Audio_Buffer_DC_Calibration_Param",   VER(AP_CFG_RDCL_FILE_AUDIO_BUFFER_DC_CALIBRATION_PAR_LID), CFG_FILE_AUDIO_BUFFER_DC_CALIBRATION_PAR_SIZE,
            CFG_FILE_AUDIO_BUFFER_DC_CALIBRATION_PAR_TOTAL, SIGNLE_DEFUALT_REC  ,    (char *)&Audio_Buffer_DC_Calibration_Par_default, DataReset , NULL
        },
        { "/mnt/vendor/nvdata/media/VibSpk_CompFlt",   VER(AP_CFG_RDCL_FILE_VIBSPK_COMPFLT_LID), CFG_FILE_AUDIO_COMPFLT_REC_SIZE,
            CFG_FILE_VIBSPK_COMPFLT_REC_TOTAL, SIGNLE_DEFUALT_REC  ,    (char *)&audio_vibspk_custom_default, DataReset , NULL
        },
        { "/mnt/vendor/nvdata/media/MusicDRC_CompFlt",   VER(AP_CFG_RDCL_FILE_AUDIO_MUSIC_DRC_LID), CFG_FILE_AUDIO_COMPFLT_REC_SIZE,
            CFG_FILE_MUSICDRC_COMPFLT_REC_TOTAL, SIGNLE_DEFUALT_REC  ,    (char *)&audio_musicdrc_custom_default, DataReset , NULL
        },
        { "/mnt/vendor/nvdata/media/RingToneDRC_CompFlt",   VER(AP_CFG_RDCL_FILE_AUDIO_RINGTONE_DRC_LID), CFG_FILE_AUDIO_COMPFLT_REC_SIZE,
            CFG_FILE_RINGTONEDRC_COMPFLT_REC_TOTAL, SIGNLE_DEFUALT_REC  ,    (char *)&audio_ringtonedrc_custom_default, DataReset , NULL
        },
        { "/mnt/vendor/nvdata/media/Audio_MAGI_CONFERENCE",   VER(AP_CFG_RDCL_FILE_AUDIO_MAGI_CONFERENCE_LID), CFG_FILE_SPEECH_MAGI_CONFERENCE_SIZE,
            CFG_FILE_SPEECH_MAGI_CONFERENCE_TOTAL, SIGNLE_DEFUALT_REC  ,    (char *)&speech_magi_conference_custom_default, DataReset , NULL
        },
        { "/mnt/vendor/nvdata/media/Audio_HAC_Param",   VER(AP_CFG_RDCL_FILE_AUDIO_HAC_PARAM_LID), CFG_FILE_SPEECH_HAC_PARAM_SIZE,
            CFG_FILE_SPEECH_HAC_PARAM_TOTAL, SIGNLE_DEFUALT_REC  ,    (char *)&speech_hac_param_custom_default, DataReset , NULL
        },
        { "/mnt/vendor/nvdata/media/Audio_Sph_Lpbk",   VER(AP_CFG_RDCL_FILE_AUDIO_SPEECH_LPBK_PARAM_LID), CFG_FILE_SPEECH_LPBK_PARAM_SIZE,
            CFG_FILE_SPEECH_LPBK_PARAM_TOTAL, SIGNLE_DEFUALT_REC  ,    (char *)&speech_lpbk_param_custom_default, DataReset , NULL
        },
        { "/mnt/vendor/nvdata/media/Audio_BT_Gain",   VER(AP_CFG_RDCL_FILE_AUDIO_BT_GAIN_CUSTOM_LID), CFG_FILE_AUDIO_BT_GAIN_CUSTOM_SIZE,
            CFG_FILE_AUDIO_BT_GAIN_CUSTOM_TOTAL, SIGNLE_DEFUALT_REC  ,    (char *)&bt_gain_control_default, DataReset , NULL
        },
        { "/mnt/vendor/nvdata/media/AUDIO_FUNC_SWITCH_Param",   VER(AP_CFG_RDCL_FILE_AUDIO_FUNC_SWITCH_PARAM_LID), CFG_FILE_AUDIO_FUNC_SWITCH_PARAM_SIZE,
            CFG_FILE_AUDIO_FUNC_SWITCH_PARAM_TOTAL, SIGNLE_DEFUALT_REC  ,    (char *)&audio_func_swtich_param_custom_default, DataReset , NULL
        },
        {
            "/mnt/vendor/nvdata/APCFG/APRDCL/FG",         VER(AP_CFG_CUSTOM_FILE_FUEL_GAUGE_LID),	           CFG_FILE_FG_CONFIG_SIZE,
            CFG_FILE_FG_CONFIG_TOTAL,                  SIGNLE_DEFUALT_REC,                (char *)&stFGConfigDefault, DataReset , NULL
        },
        { "/mnt/vendor/nvdata/APCFG/APRDCL/smartpa_calib", VER(AP_CFG_CUSTOM_FILE_SMARTPA_CALIB_LID), CFG_FILE_SMARTPA_CALIB_CONFIG_SIZE,
            CFG_FILE_SMARTPA_CALIB_CONFIG_TOTAL, SIGNLE_DEFUALT_REC, (char *)&smartpa_calib_ConfigDefault, DataReset, NULL
        },
    };

    int iNvRamFileMaxLID=AP_CFG_CUSTOM_FILE_MAX_LID;
    extern int iNvRamFileMaxLID;
    const unsigned int g_i4CFG_File_Custom_Count = sizeof(g_akCFG_File_Custom)/sizeof(TCFG_FILE);

    extern const TCFG_FILE g_akCFG_File_Custom[];

    extern const unsigned int g_i4CFG_File_Custom_Count;

    int iFileWIFILID=AP_CFG_RDEB_FILE_WIFI_LID;
    extern int iFileWIFILID;
    int iFileCustomWIFILID=AP_CFG_RDEB_WIFI_CUSTOM_LID;
    extern int iFileCustomWIFILID;
    int iFilePRODUCT_INFOLID=AP_CFG_REEB_PRODUCT_INFO_LID;
    extern int iFilePRODUCT_INFOLID;

#ifdef __cplusplus
}
#endif

#endif
