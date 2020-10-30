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
 * AudioCustEncryptClient.h
 *
 * Project:
 * --------
 *   Android
 *
 * Description:
 * ------------
 *   This file a client for AudioCustEncrypt
 *
 * Author:
 * -------
 *   Tina Tsai
 *
 *******************************************************************************/
#ifndef _AUDIO_CUST_ENCRYPT_CLIENT_H_
#define _AUDIO_CUST_ENCRYPT_CLIENT_H_
#include <dlfcn.h>
#include "AudioUtility.h"
#include <AudioLock.h>

#include <utils/Log.h>
#include <utils/String8.h>
#include "AudioCustEncrypt.h"

namespace android {

class AudioCustEncryptClient {
public:
    virtual ~AudioCustEncryptClient();

    static AudioCustEncryptClient *GetInstance(void);

    int (*Initial)(void);
    int (*EncryptProcess)(char *TargetBuf, char *SourceBuf, uint16_t SourceByte);
    int (*DecryptProcess)(char *TargetBuf, char *SourceBuf, uint16_t SourceByte);

protected:
    AudioCustEncryptClient();

    AudioLock mMutex;

private:
    void Init(void);
    void Deinit(void);
    static AudioCustEncryptClient *mAudioCustEncryptClient; // singleton

    void          *handle;
    short acpOpsInited;
};

}

#endif
