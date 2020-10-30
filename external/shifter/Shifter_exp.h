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

#ifndef __SHIFTER_EXP_H__
#define __SHIFTER_EXP_H__

// Notice: All the buffer pointers are required to be
//         four-byte-aligned to avoid the potential on-target process error !!!

typedef enum {
    SHFTR_IN_Q1P15_OUT_Q1P31 =  0,  // 16-bit Q1.15 input, 32-bit Q1.31 output
    SHFTR_IN_Q1P31_OUT_Q1P15 =  1,  // 32-bit Q1.31 input, 16-bit Q1.15 output
    SHFTR_IN_Q9P23_OUT_Q1P31 =  2,  // 32-bit Q9.23 input, 32-bit Q1.31 output
    SHFTR_IN_Q1P31_OUT_Q9P23 =  3,  // 32-bit Q1.31 input, 32-bit Q9.23 output
    SHFTR_IN_Q1P15_OUT_Q9P23 =  4,  // 16-bit Q1.15 input, 32-bit Q9.23 output
    SHFTR_IN_Q9P23_OUT_Q1P15 =  5,  // 32-bit Q9.23 input, 16-bit Q1.15 output
    SHFTR_IN_Q1P15_OUT_Q1P23 =  6,  // 16-bit Q1.15 input, 24-bit Q1.23 output
    SHFTR_IN_Q1P23_OUT_Q1P15 =  7,  // 24-bit Q1.23 input, 16-bit Q1.15 output
    SHFTR_IN_Q1P31_OUT_Q1P23 =  8,  // 32-bit Q1.31 input, 24-bit Q1.23 output
    SHFTR_IN_Q1P23_OUT_Q1P31 =  9,  // 24-bit Q1.23 input, 32-bit Q1.31 output
    SHFTR_IN_Q9P23_OUT_Q1P23 = 10,  // 32-bit Q9.23 input, 24-bit Q1.23 output
    SHFTR_IN_Q1P23_OUT_Q9P23 = 11   // 24-bit Q1.23 input, 32-bit Q9.23 output
} SHFTR_PCM_FORMAT;

/*
    Process 16-bit / 24-bit / 32-bit data from input buffer to output buffer
    Return value      < 0  : Error
                             -1 => PCM_Format incorrect enumerator
                             -2 => p_in_buf incorrect byte alignment
                             -3 => p_ou_buf incorrect byte alignment
                      >= 0 : Normal
    p_in_buf      [I] Pointer to the input PCM buffer
                      For stereo input, the layout of LR is L/R/L/R...
    p_in_byte_cnt [I] Valid input buffer size in bytes
                  [O] Consumed input buffer size in bytes
    p_ou_buf      [I] Pointer to the output PCM buffer
                      For stereo output, the layout of LR is L/R/L/R...
    p_ou_byte_cnt [I] Available output buffer size in bytes
                  [O] Produced output buffer size in bytes
    PCM_Format    [I] Input / output PCM format
                      0  (SHFTR_IN_Q1P15_OUT_Q1P31):
                          16-bit Q1.15 input, 32-bit Q1.31 output
                      1  (SHFTR_IN_Q1P31_OUT_Q1P15):
                          32-bit Q1.31 input, 16-bit Q1.15 output
                      2  (SHFTR_IN_Q9P23_OUT_Q1P31):
                          32-bit Q9.23 input, 32-bit Q1.31 output
                      3  (SHFTR_IN_Q1P31_OUT_Q9P23):
                          32-bit Q1.31 input, 32-bit Q9.23 output
                      4  (SHFTR_IN_Q1P15_OUT_Q9P23):
                          16-bit Q1.15 input, 32-bit Q9.23 output
                      5  (SHFTR_IN_Q9P23_OUT_Q1P15):
                          32-bit Q9.23 input, 16-bit Q1.15 output
                      6  (SHFTR_IN_Q1P15_OUT_Q1P23):
                          16-bit Q1.15 input, 24-bit Q1.23 output
                      7  (SHFTR_IN_Q1P23_OUT_Q1P15):
                          24-bit Q1.23 input, 16-bit Q1.15 output
                      8  (SHFTR_IN_Q1P31_OUT_Q1P23):
                          32-bit Q1.31 input, 24-bit Q1.23 output
                      9  (SHFTR_IN_Q1P23_OUT_Q1P31):
                          24-bit Q1.23 input, 32-bit Q1.31 output
                      10 (SHFTR_IN_Q9P23_OUT_Q1P23):
                          32-bit Q9.23 input, 24-bit Q1.23 output
                      11 (SHFTR_IN_Q1P23_OUT_Q9P23):
                          24-bit Q1.23 input, 32-bit Q9.23 output

    Note:
    Support N-in-N-out
*/
int Shifter_Process(    void *p_in_buf,
                        unsigned int *p_in_byte_cnt,
                        void *p_ou_buf,
                        unsigned int *p_ou_byte_cnt,
                        unsigned int PCM_Format);

#endif // __SHIFTER_EXP_H__
