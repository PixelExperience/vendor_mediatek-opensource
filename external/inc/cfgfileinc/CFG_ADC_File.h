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
 *   CFG_ADC_File.h
 *
 * Project:
 * --------
 *   DUMA
 *
 * Description:
 * ------------
 *    header file of ADC CFG file
 *
 * Author:
 * -------
 *   MTK80198(Chunlei Wang)
 *
 *
 *
 *******************************************************************************/


#ifndef _CFG_AUXADC_FILE_H
#define _CFG_AUXADC_FILE_H



// the record structure define of adc nvram file
typedef struct
{
    int Slop[9];
    int Offset[9];
    int cal;
}AUXADC_CFG_Struct;

///please define it according to your module
#define CFG_FILE_AUXADC_REC_SIZE    sizeof(AUXADC_CFG_Struct)
#define CFG_FILE_AUXADC_REC_TOTAL   1


#endif


