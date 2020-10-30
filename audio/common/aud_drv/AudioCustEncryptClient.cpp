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
 * AudioCustEncryptClient.cpp
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
#include "AudioCustEncryptClient.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "AudioCustEncryptClient"

namespace android {

/*==============================================================================
 *                     Implementation
 *============================================================================*/

AudioCustEncryptClient *AudioCustEncryptClient::mAudioCustEncryptClient = NULL;
AudioCustEncryptClient *AudioCustEncryptClient::GetInstance() {
    static Mutex mGetInstanceLock;
    Mutex::Autolock _l(mGetInstanceLock);

    if (mAudioCustEncryptClient == NULL) {
        mAudioCustEncryptClient = new AudioCustEncryptClient();
    }
    ASSERT(mAudioCustEncryptClient != NULL);
    return mAudioCustEncryptClient;
}

AudioCustEncryptClient::AudioCustEncryptClient() {
    ALOGD("%s()", __FUNCTION__);
    acpOpsInited = 0;
    Init();
}

AudioCustEncryptClient::~AudioCustEncryptClient() {
    ALOGD("%s()", __FUNCTION__);
    Deinit();
}

void AudioCustEncryptClient::Init(void) {
    const char *error;
    const char *funName = NULL;
    ALOGD("%s(), acpOpsInited(%d)", __FUNCTION__, acpOpsInited);

    if (acpOpsInited == 0) {
        ALOGD("%s(), init AcpOps struct", __FUNCTION__);

        /* dlopen */
        handle = dlopen("libaudiocustencrypt.so", RTLD_LAZY);
        if (handle == NULL) {
            ALOGE("%s(), dlopen fail! (%s)\n", __FUNCTION__, dlerror());
        } else {
            dlerror();    /* Clear any existing error */
            /* dlsym */
            funName = "Initial";
            ALOGD("%s(), dlsym %s", __FUNCTION__, funName);
            Initial = (int (*)(void)) dlsym(handle, funName);
            error = dlerror();
            if (error != NULL) {
                ALOGE("%s(), dlsym %s fail. (%s)\n", __FUNCTION__, funName, error);
            }

            funName = "EncryptProcess";
            ALOGD("%s(), dlsym %s", __FUNCTION__, funName);
            EncryptProcess = (int (*)(char *TargetBuf, char *SourceBuf, uint16_t SourceByte)) dlsym(handle, funName);
            error = dlerror();
            if (error != NULL) {
                ALOGE("%s(), dlsym %s fail. (%s)\n", __FUNCTION__, funName, error);
            }

            funName = "DecryptProcess";
            ALOGD("%s(), dlsym %s", __FUNCTION__, funName);
            DecryptProcess = (int (*)(char *TargetBuf, char *SourceBuf, uint16_t SourceByte)) dlsym(handle, funName);
            error = dlerror();
            if (error != NULL) {
                ALOGE("%s(), dlsym %s fail. (%s)\n", __FUNCTION__, funName, error);
            }

            acpOpsInited = 1;
        }
    }

    ALOGD("-%s(), acpOpsInited(%d)", __FUNCTION__, acpOpsInited);
}

void AudioCustEncryptClient::Deinit() {
    ALOGD("+%s(), acpOpsInited (%d)\n", __FUNCTION__, acpOpsInited);
    if (acpOpsInited != 0) {
        dlclose(handle);
        acpOpsInited = 0;
    }
    ALOGD("-%s(), acpOpsInited (%d)\n", __FUNCTION__, acpOpsInited);
}


}
