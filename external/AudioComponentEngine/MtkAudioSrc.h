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

/*
* Description:
*   This file implements Mtk Audio Ssampl Rate Converter
*/

#ifndef __MTK_AUDIO_SRC_EXP_H__
#define __MTK_AUDIO_SRC_EXP_H__

#include <utils/threads.h>
#include "MtkAudioComponent.h"
extern "C" {
#include "Blisrc_exp.h"
}
namespace android {

class MtkAudioSrc : public MtkAudioSrcBase {
public:
    MtkAudioSrc();
    MtkAudioSrc(uint32_t input_SR, uint32_t input_channel_num, uint32_t output_SR, uint32_t output_channel_num, SRC_PCM_FORMAT format);
    virtual ACE_ERRID setParameter(uint32_t paramID, void *param);
    virtual ACE_ERRID getParameter(uint32_t paramID, void *param);
    virtual ACE_ERRID open(void);
    virtual ACE_ERRID close(void);
    virtual ACE_ERRID resetBuffer(void);
    virtual ACE_ERRID process(void *pInputBuffer,   /* Input, pointer to input buffer */
                              uint32_t *InputSampleCount,        /* Input, length(byte) of input buffer */
                              /* Output, length(byte) left in the input buffer after conversion */
                              void *pOutputBuffer,               /* Input, pointer to output buffer */
                              uint32_t *OutputSampleCount);      /* Input, length(byte) of output buffer */
    /* Output, output data length(byte) */

    virtual ACE_ERRID multiChannelOpen(void);
    virtual ACE_ERRID multiChannelResetBuffer(void);
    virtual ACE_ERRID multiChannelProcess(void *pInputBuffer,   /* Input, pointer to input buffer */
                                          uint32_t *InputSampleCount,        /* Input, length(byte) of input buffer */
                                          /* Output, length(byte) left in the input buffer after conversion */
                                          void *pOutputBuffer,               /* Input, pointer to output buffer */
                                          uint32_t *OutputSampleCount);      /* Input, length(byte) of output buffer */
    /* Output, output data length(byte) */
    virtual ~MtkAudioSrc();
private:
    ACE_STATE mState;
    uint32_t mTempBufSize; // in byte
    uint32_t mInternalBufSize; // in byte
    char *mpTempBuf;
    char *mpInternalBuf;
    Blisrc_Param mBlisrcParam;
    Blisrc_Handle *mBlisrcHandler;
    Mutex mLock;
};

}; // namespace android

#endif // __MTK_AUDIO_SRC_EXP_H__
