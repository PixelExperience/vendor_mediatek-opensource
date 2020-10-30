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
 *   CFG_META_FILE.h
 *
 * Project:
 * --------
 *   DUMA
 *
 * Description:
 * ------------
 *    header file of META CFG file
 *
 * Author:
 * -------
 *   MTK80306(Ning Feng)
 *
 *
 *
 *******************************************************************************/


#ifndef _CFG_META_FILE_H
#define _CFG_META_FILE_H


///define meta nvram record
typedef struct
{
    char cComPort[20];
    char cLogPort[20];
    unsigned int iCombps;
    unsigned int iLogbps;
    unsigned int bLogEnable;

} META_CFG_Struct;

//buad rate define
#define BUD_4800      4800
#define BUD_9600      9600
#define BUD_19200     19200
#define BUD_38400     38400
#define BUD_57600     57600
#define BUD_115200    115200
#define BUD_230400    230400
#define BUD_460800    460800
#define BUD_921600    921600

///please define it according to your module
#define CFG_FILE_META_REC_SIZE    sizeof(META_CFG_Struct)
#define CFG_FILE_META_REC_TOTAL   1

#endif


