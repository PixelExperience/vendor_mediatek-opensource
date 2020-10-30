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
 *   CFG_HWMON_FILE.h
 *
 * Project:
 * --------
 *   YUSU
 *
 * Description:
 * ------------
 *   Hheader file of HWMON(all HW sensor) CFG file
 *
 * Author:
 * -------
 *   MTK02404(MingHsien Hsieh)
 *
 *******************************************************************************/

#ifndef _CFG_HWMON_FILE_H
#define _CFG_HWMON_FILE_H
/********************************************************************************
 * Accelerometer
 *******************************************************************************/
#define C_HWMON_ACC_AXES    3
/*-----------------------------------------------------------------------------*/
typedef struct
{
    int offset[C_HWMON_ACC_AXES];
} NVRAM_HWMON_ACC_STRUCT;
/*-----------------------------------------------------------------------------*/
#define CFG_FILE_HWMON_ACC_REC_SIZE    sizeof(NVRAM_HWMON_ACC_STRUCT)
#define CFG_FILE_HWMON_ACC_REC_TOTAL   1
/*-----------------------------------------------------------------------------*/

/********************************************************************************
 * Gyroscope
 *******************************************************************************/
#define C_HWMON_GYRO_AXES    3
/*-----------------------------------------------------------------------------*/
typedef struct
{
    int offset[C_HWMON_GYRO_AXES];
} NVRAM_HWMON_GYRO_STRUCT;
/*-----------------------------------------------------------------------------*/
#define CFG_FILE_HWMON_GYRO_REC_SIZE    sizeof(NVRAM_HWMON_GYRO_STRUCT)
#define CFG_FILE_HWMON_GYRO_REC_TOTAL   1
/*-----------------------------------------------------------------------------*/
/********************************************************************************
 * ALSPS
 *******************************************************************************/
#define C_HWMON_ALSPS_AXES    3
/*-----------------------------------------------------------------------------*/
typedef struct
{
    int ps_cali[C_HWMON_ALSPS_AXES];
} NVRAM_HWMON_PS_STRUCT;
/*-----------------------------------------------------------------------------*/
#define CFG_FILE_HWMON_PS_REC_SIZE    sizeof(NVRAM_HWMON_PS_STRUCT)
#define CFG_FILE_HWMON_PS_REC_TOTAL   1
/*-----------------------------------------------------------------------------*/

#endif


