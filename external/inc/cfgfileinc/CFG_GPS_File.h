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
 *   cfg_gps_file.h
 *
 * Project:
 * --------
 *   YuSu
 *
 * Description:
 * ------------
 *    header file of main function
 *
 * Author:
 * -------
 *   Mike Chang(MTK02063)
 *
 *------------------------------------------------------------------------------
 * $Revision:$
 * $Modtime:$
 * $Log:$
 *
 * 06 24 2010 yunchang.chang
 * [ALPS00002677][Need Patch] [Volunteer Patch] ALPS.10X.W10.26 Volunteer patch for GPS customization use NVRam 
 * .
 *
 *******************************************************************************/



#ifndef _CFG_GPS_FILE_H
#define _CFG_GPS_FILE_H


// the record structure define of bt nvram file
typedef struct
{
    char dsp_dev[20];
    unsigned char gps_if_type;
    
    unsigned int gps_tcxo_hz;
    unsigned int gps_tcxo_ppb;
    unsigned char gps_tcxo_type;
    
    unsigned char gps_lna_mode;
    
    unsigned char gps_sbas_mode;
    unsigned int C0;
    unsigned int C1;
    unsigned int initU;
    unsigned int lastU;
} ap_nvram_gps_config_struct;


//the record size and number of bt nvram file
#define CFG_FILE_GPS_CONFIG_SIZE    sizeof(ap_nvram_gps_config_struct)
#define CFG_FILE_GPS_CONFIG_TOTAL   1

#endif /* _CFG_GPS_FILE_H */
