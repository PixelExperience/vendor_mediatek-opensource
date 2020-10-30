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

#ifndef __MTK_AUDIO_BIT_CONVERTERC_EXP_H__
#define __MTK_AUDIO_BIT_CONVERTERC_EXP_H__

#include "Shifter_exp.h"
#include "Limiter_exp.h"
#include "MtkAudioComponentEngineCommon.h"


typedef struct MtkAudioBitConverterC {
    int (*open)(struct MtkAudioBitConverterC *self, uint32_t sampling_rate, uint32_t channel_num, BCV_PCM_FORMAT format);
    int (*close)(struct MtkAudioBitConverterC *self);
    int (*SetParameter)(struct MtkAudioBitConverterC *self, uint32_t paramID, void *param);
    int (*GetParameter)(struct MtkAudioBitConverterC *self, uint32_t paramID, void *param);
    int (*Reset)(struct MtkAudioBitConverterC *self);
    int (*Process)(struct MtkAudioBitConverterC *self,
                   void *pInputBuffer,   /* Input, pointer to input buffer */
                   uint32_t *InputSampleCount,        /* Input, length(byte) of input buffer */
                   /* Output, length(byte) left in the input buffer after conversion */
                   void *pOutputBuffer,                        /* Input, pointer to output buffer */
                   uint32_t *OutputSampleCount);

    uint32_t mPcmFormat;
    uint32_t mChannelNum;
    uint32_t mSampleRate;
    char *mpTempBuf;
    char *mpInternalBuf;
    uint32_t mTempBufSize; // in byte
    uint32_t mInternalBufSize; // in byte
    Limiter_InitParam mLimiterInitPar;
    Limiter_Handle *mLimiterHandler;
    int mState;
} MtkAudioBitConverterC;

void InitMtkAudioBitConverterC(struct MtkAudioBitConverterC *self);

#endif // __MTK_AUDIO_BIT_CONVERTERC_EXP_H__
