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
 *   CFG_FACTORY_FILE.h
 *
 * Project:
 * --------
 *   YUSU
 *
 * Description:
 * ------------
 *   Hheader file of FACTORY CFG file
 *
 * Author:
 * -------
 *   MTK02528(Koshi Chiu)
 *
 *
 *
 *******************************************************************************/


#ifndef _CFG_FACTORY_FILE_H
#define _CFG_FACTORY_FILE_H


///define meta nvram record
typedef struct
{
//    UINT32 rf_calabrated;
      unsigned int rf_calabrated;
} FACTORY_CFG_Struct;

//please define it according to your module
#define CFG_FILE_FACTORY_REC_SIZE    sizeof(FACTORY_CFG_Struct)
#define CFG_FILE_FACTORY_REC_TOTAL   1

#endif


