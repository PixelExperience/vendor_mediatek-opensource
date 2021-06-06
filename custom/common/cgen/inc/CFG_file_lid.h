/*
 * Copyright (C) 2021 The Android Open Source Project
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

#ifndef CFG_FILE_LID_H
#define CFG_FILE_LID_H



#define VER_LID(lid) lid##_VERNO lid
#define VER(lid)  lid##_VERNO


/* the definition of file LID */
typedef enum
{
	AP_CFG_FILE_VER_INFO_LID,
	AP_CFG_RDEB_FILE_BT_ADDR_LID,
//	AP_CFG_RDEB_FILE_WIFI_LID,
	AP_CFG_RDCL_FILE_AUXADC_LID,
	AP_CFG_RDCL_CAMERA_PARA_LID,
	AP_CFG_RDCL_CAMERA_3A_LID,
	AP_CFG_RDCL_CAMERA_SHADING_LID,
	AP_CFG_RDCL_CAMERA_DEFECT_LID,
	AP_CFG_RDCL_CAMERA_SENSOR_LID,  //10
	AP_CFG_RDCL_CAMERA_LENS_LID,
	AP_CFG_RDCL_UART_LID,
	//AP_CFG_RDCL_UUID_LID,
	//AP_CFG_RDCL_SIM_LID,
	AP_CFG_RDCL_FACTORY_LID,
    AP_CFG_RDCL_BWCS_LID,
    AP_CFG_RDCL_HWMON_ACC_LID,
    AP_CFG_RDCL_HWMON_GYRO_LID,
//    AP_CFG_RDEB_WIFI_CUSTOM_LID,
    AP_CFG_RDEB_OMADM_USB_LID,
	AP_CFG_RDCL_FILE_VOICE_RECOGNIZE_PARAM_LID,
	AP_CFG_RDCL_FILE_AUDIO_AUDENH_CONTROL_OPTION_PAR_LID,
	AP_CFG_RDCL_FILE_AUDIO_VOIP_PAR_LID,
	AP_CFG_RDCL_HWMON_PS_LID,
	AP_CFG_FILE_MDTYPE_LID,
	AP_CFG_FILE_EXT_MDTYPE_LID,
	AP_CFG_RDCL_FILE_SDIO_LID,
	AP_CFG_RDCL_CAMERA_VERSION_LID,
	AP_CFG_RDCL_CAMERA_FEATURE_LID,
	AP_CFG_RDCL_CAMERA_GEOMETRY_LID,
	AP_CFG_RDCL_FILE_MD_SBP_LID,
    AP_CFG_RDCL_CAMERA_SHADING2_LID,
    AP_CFG_RDCL_CAMERA_SHADING3_LID,
    AP_CFG_RDCL_CAMERA_SHADING4_LID,
    AP_CFG_RDCL_CAMERA_SHADING5_LID,
    AP_CFG_RDCL_CAMERA_SHADING6_LID,
    AP_CFG_RDCL_CAMERA_SHADING7_LID,
    AP_CFG_RDCL_CAMERA_SHADING8_LID,
    AP_CFG_RDCL_CAMERA_SHADING9_LID,
    AP_CFG_RDCL_CAMERA_SHADING10_LID,
    AP_CFG_RDCL_CAMERA_SHADING11_LID,
    AP_CFG_RDCL_CAMERA_SHADING12_LID,
    AP_CFG_RDCL_CAMERA_PLINE_LID,
    AP_CFG_RDCL_CAMERA_PLINE2_LID,
    AP_CFG_RDCL_CAMERA_PLINE3_LID,
    AP_CFG_RDCL_CAMERA_PLINE4_LID,
    AP_CFG_RDCL_CAMERA_PLINE5_LID,
    AP_CFG_RDCL_CAMERA_PLINE6_LID,
    AP_CFG_RDCL_CAMERA_PLINE7_LID,
    AP_CFG_RDCL_CAMERA_PLINE8_LID,
    AP_CFG_RDCL_CAMERA_PLINE9_LID,
    AP_CFG_RDCL_CAMERA_PLINE10_LID,
    AP_CFG_RDCL_CAMERA_PLINE11_LID,
    AP_CFG_RDCL_CAMERA_PLINE12_LID,
    AP_CFG_RDCL_CAMERA_AF_LID,
    AP_CFG_RDCL_CAMERA_FLASH_CALIBRATION_LID,


	AP_CFG_CUSTOM_BEGIN_LID,  ///Max LID.
}CFG_FILE_LID;
/*
int iCustomBeginLID=AP_CFG_CUSTOM_BEGIN_LID;
extern int iCustomBeginLID;
int iFileVerInfoLID=AP_CFG_FILE_VER_INFO_LID;
extern int iFileVerInfoLID;
int iFileBTAddrLID=AP_CFG_RDEB_FILE_BT_ADDR_LID;
extern int iFileBTAddrLID;

#if 0
int iFileWIFILID=AP_CFG_RDEB_FILE_WIFI_LID;
extern int iFileWIFILID;
int iFileCustomWIFILID=AP_CFG_RDEB_WIFI_CUSTOM_LID;
extern int iFileCustomWIFILID;
#endif

int iFileAuxADCLID=AP_CFG_RDCL_FILE_AUXADC_LID;
extern int iFileAuxADCLID;
*/
////if file num changed, the define of CFG_FILE_VER_FILE_REC_TOTAL should be changed too  ///
#define CFG_FILE_VER_FILE_REC_TOTAL   936

/* verno of data items */
/* ver file version */
/* md type file version*/
#define AP_CFG_FILE_MDTYPE_LID_VERNO			"000"
#define AP_CFG_FILE_EXT_MDTYPE_LID_VERNO			"000"
#define AP_CFG_FILE_VER_INFO_LID_VERNO				"000"
/* BT file version */
#define AP_CFG_RDEB_FILE_BT_ADDR_LID_VERNO			"002"
/* WIFI file version */
//#define AP_CFG_RDEB_FILE_WIFI_LID_VERNO				"000"
/* WIFI MAC addr file version */
//#define AP_CFG_RDCL_FILE_WIFI_ADDR_LID_VERNO		"000"
/* ADC file version */
#define AP_CFG_RDCL_FILE_AUXADC_LID_VERNO			"000"

/* camera nvram files */
#define AP_CFG_RDCL_CAMERA_PARA_LID_VERNO			"000"
#define AP_CFG_RDCL_CAMERA_3A_LID_VERNO				"000"
#define AP_CFG_RDCL_CAMERA_SHADING_LID_VERNO		"000"
#define AP_CFG_RDCL_CAMERA_DEFECT_LID_VERNO			"000"
#define AP_CFG_RDCL_CAMERA_SENSOR_LID_VERNO			"000"
#define AP_CFG_RDCL_CAMERA_LENS_LID_VERNO			"000"
#define AP_CFG_RDCL_CAMERA_VERSION_LID_VERNO        "000"
#define AP_CFG_RDCL_CAMERA_FEATURE_LID_VERNO        "000"
#define AP_CFG_RDCL_CAMERA_GEOMETRY_LID_VERNO        "000"
#define AP_CFG_RDCL_CAMERA_PLINE_LID_VERNO        "000"
#define AP_CFG_RDCL_CAMERA_AF_LID_VERNO        "000"
#define AP_CFG_RDCL_CAMERA_FLASH_CALIBRATION_LID_VERNO        "000"

#define AP_CFG_RDCL_UART_LID_VERNO                  "000"

#define AP_CFG_RDCL_UUID_LID_VERNO                  "000"

#define AP_CFG_RDCL_SIM_LID_VERNO                   "000"

/* For the factory mode info. used */
#define AP_CFG_RDCL_FACTORY_LID_VERNO               "000"

#define AP_CFG_RDCL_BWCS_LID_VERNO				    "000"

#define AP_CFG_RDCL_HWMON_ACC_LID_VERNO             "000"
#define AP_CFG_RDCL_HWMON_GYRO_LID_VERNO					"000"
#define AP_CFG_RDCL_HWMON_PS_LID_VERNO					"000"
//#define AP_CFG_RDEB_WIFI_CUSTOM_LID_VERNO				"000"
#define AP_CFG_RDEB_OMADM_USB_LID_VERNO				"000"
#define AP_CFG_RDCL_FILE_VOICE_RECOGNIZE_PARAM_LID_VERNO "000"

/* audio audenh control custom file version*/
#define AP_CFG_RDCL_FILE_AUDIO_AUDENH_CONTROL_OPTION_PAR_LID_VERNO "000"

//audio VoIP params custom file version
#define AP_CFG_RDCL_FILE_AUDIO_VOIP_PAR_LID_VERNO "000"
/* SDIO file version */
#define AP_CFG_RDCL_FILE_SDIO_LID_VERNO            "001"

/* MD SBP fle version */
#define AP_CFG_RDCL_FILE_MD_SBP_LID_VERNO         "001"

#endif /* CFG_FILE_LID_H */
