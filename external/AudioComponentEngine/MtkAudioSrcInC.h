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

#ifndef __MTK_AUDIO_SRC_INC_EXP_H__
#define __MTK_AUDIO_SRC_INC_EXP_H__

#include "Blisrc_exp.h"
#include "MtkAudioComponentEngineCommon.h"

typedef struct MtkAudioSrcInC {
    int (*SetParameter)(struct MtkAudioSrcInC *self, uint32_t paramID, void *param);
    int (*GetParameter)(struct MtkAudioSrcInC *self, uint32_t paramID, void *param);
    int (*Reset)(struct MtkAudioSrcInC *self);
    int (*open)(struct MtkAudioSrcInC *self, uint32_t input_SR, uint32_t input_channel_num, uint32_t output_SR, uint32_t output_channel_num, SRC_PCM_FORMAT format);
    int (*close)(struct MtkAudioSrcInC *self);
    int (*Process)(struct MtkAudioSrcInC *self,
                   void *pInputBuffer,   /* Input, pointer to input buffer */
                   uint32_t *InputSampleCount,        /* Input, length(byte) of input buffer */
                   /* Output, length(byte) left in the input buffer after conversion */
                   void *pOutputBuffer,                        /* Input, pointer to output buffer */
                   uint32_t *OutputSampleCount);

    int (*MultiChannel_Open)(struct MtkAudioSrcInC *self, uint32_t input_SR, uint32_t input_channel_num, uint32_t output_SR, uint32_t output_channel_num, SRC_PCM_FORMAT format);
    int (*MultiChannel_ResetBuffer)(struct MtkAudioSrcInC *self);
    int (*MultiChannel_Process)(struct MtkAudioSrcInC *self,
                                void *pInputBuffer,   /* Input, pointer to input buffer */
                                uint32_t *InputSampleCount,        /* Input, length(byte) of input buffer */
                                /* Output, length(byte) left in the input buffer after conversion */
                                void *pOutputBuffer,               /* Input, pointer to output buffer */
                                uint32_t *OutputSampleCount);      /* Input, length(byte) of output buffer */
    /* Output, output data length(byte) */

    uint32_t mTempBufSize; // in byte
    uint32_t mInternalBufSize; // in byte
    char *mpTempBuf;
    char *mpInternalBuf;
    Blisrc_Param mBlisrcParam;
    Blisrc_Handle *mBlisrcHandler;
    int mState;
    int compensated;
} MtkAudioSrcInC;

void InitMtkAudioSrcInC(struct MtkAudioSrcInC *self);

#endif // __MTK_AUDIO_SRC_INC_EXP_H__
