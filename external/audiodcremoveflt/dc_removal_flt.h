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
 * Dc_Remove_fit.h
 *
 * Project:
 * --------
 * SWIP
 *
 * Description:
 * ------------
 * DC_Remove_fit Common header file.
 *
 * Author:
 * -------
 * Chipeng Chang
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * $Revision$
 * $Modtime$
 * $Log$
 *
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/
#ifndef __DC_REMOVE_FLT_H__
#define __DC_REMOVE_FLT_H__

#ifndef NULL
#define NULL    0
#endif

#ifndef ASSERT
#define ASSERT(x)
#endif

typedef void DCRemove_Handle;

//============================================================//
// Get buffer size for DC Removal Engine
// internal_buf_size_in_bytes   output  internal buffer size in bytes
//============================================================//
void DCR_GetBufferSize (
    unsigned int *internal_buf_size_in_bytes);

//============================================================//
// Open DC Removal Engine
// p_internal_buf   input   pointer to the internal buffer
// channel          input   channel number (1 or 2)
// sampling_rate    input   sampling rate (unit: Hz)
// working_mode     input   working mode
// return                   handle of the SWIP engine
//============================================================//
DCRemove_Handle *DCR_Open (
    signed char *p_internal_buf,
    unsigned int channel,
    unsigned int sampling_rate,
    unsigned int working_mode);

//============================================================//
// Process DC Removal Filter for Q1.15 Format PCM Data
// p_handle         input   handle of the SWIP engine
// p_in_buf         input   pointer to the input buffer
// p_in_byte_cnt    input   available input byte count
//                  output  remained input byte count
// p_ou_buf         input   pointer to the output buffer
// p_ou_byte_cnt    input   available output byte count
//                  output  produced output byte count
// return                   produced output byte count
//============================================================//
unsigned int DCR_Process (
    DCRemove_Handle *p_handle,
    short *p_in_buf,
    unsigned int *p_in_byte_cnt,
    short *p_ou_buf,
    unsigned int *p_ou_byte_cnt);

//============================================================//
// Process DC Removal Filter for Q1.31 Format PCM Data
// p_handle         input   handle of the SWIP engine
// p_in_buf         input   pointer to the input buffer
// p_in_byte_cnt    input   available input byte count
//                  output  remained input byte count
// p_ou_buf         input   pointer to the output buffer
// p_ou_byte_cnt    input   available output byte count
//                  output  produced output byte count
// return                   produced output byte count
//============================================================//
unsigned int DCR_Process_24(
    DCRemove_Handle *p_handle,
    int *p_in_buf,
    unsigned int *p_in_byte_cnt,
    int *p_ou_buf,
    unsigned int *p_ou_byte_cnt);

//============================================================//
// Process DC Removal Filter for Q1.31 Format PCM Data
// p_handle         input   handle of the SWIP engine
// p_in_buf         input   pointer to the input buffer
// p_in_byte_cnt    input   available input byte count
//                  output  remained input byte count
// p_ou_buf         input   pointer to the output buffer
// p_ou_byte_cnt    input   available output byte count
//                  output  produced output byte count
// return                   produced output byte count
//============================================================//
unsigned int DCR_Process_24_High_Precision(
    DCRemove_Handle *p_handle,
    int *p_in_buf,
    unsigned int *p_in_byte_cnt,
    int *p_ou_buf,
    unsigned int *p_ou_byte_cnt);

//============================================================//
// Close DC Removal Engine
// p_handle         input   handle of the SWIP engine
//============================================================//
void DCR_Close(DCRemove_Handle *p_handle);

//============================================================//
// Re-configurate DC Removal Engine
// p_handle         input   handle of the SWIP engine
// channel          input   channel number (1 or 2)
// sampling_rate    input   sampling rate (unit: Hz)
// working_mode     input   working mode
// return                   handle of the SWIP engine
//============================================================//
DCRemove_Handle *DCR_ReConfig(
    DCRemove_Handle *p_handle,
    unsigned int channel,
    unsigned int sampling_rate,
    unsigned int working_mode);

#endif
