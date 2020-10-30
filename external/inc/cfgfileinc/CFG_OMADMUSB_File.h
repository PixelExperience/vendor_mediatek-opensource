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
 *   CFG_OMADMUSB_File.h
 *
 * Project:
 * --------
 *   YUSU
 *
 * Description:
 * ------------
 *    header file of OMADMUSB CFG file
 *
 * Author:
 * -------
 *   MTK80863(Hao Lin)
 *
 *
 *
 *******************************************************************************/


#ifndef _CFG_OMADMUSB_FILE_H
#define _CFG_OMADMUSB_FILE_H



// the record structure define of OMADM USB nvram file
typedef struct
{
    int iIsEnable;
    int iUsb;
    int iAdb;
    int iRndis;
}OMADMUSB_CFG_Struct;

///please define it according to your module
#define CFG_FILE_OMADMUSB_REC_SIZE    sizeof(OMADMUSB_CFG_Struct)
#define CFG_FILE_OMADMUSB_REC_TOTAL   1


#endif


