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
*                E X T E R N A L   R E F E R E N C E S
******************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <pthread.h>
#include <utils/Log.h>
#include <unistd.h>
#include "AudioMTKHeadsetMessager.h"

/*****************************************************************************
*                          C O N S T A N T S
******************************************************************************
*/
#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "AudioHeadSetMessager"

#ifdef ENABLE_LOG_AUDIOHEADSETMESSAGER
#define LOG_AudioHeadSetMessager ALOGD
#else
#define LOG_AudioHeadSetMessager ALOGV
#endif

namespace android {

/*****************************************************************************
*                   G L O B A L      V A R I A B L E
******************************************************************************
*/
static int HeadsetFd = -1;
#define BUF_LEN 1
static char rbuf[BUF_LEN] = {'\0'};
static char stringStatusHeadset[BUF_LEN]  = {'1'};
static char stringStatusEarphone[BUF_LEN] = {'2'};

AudioMTKHeadSetMessager *AudioMTKHeadSetMessager::UniqueHeadsetInstance = 0;

/*****************************************************************************
*                        F U N C T I O N   D E F I N I T I O N
******************************************************************************
*/
AudioMTKHeadSetMessager *AudioMTKHeadSetMessager::getInstance() {
    if (UniqueHeadsetInstance == 0) {
        ALOGD("+UniqueDigitalInstance\n");
        UniqueHeadsetInstance = new AudioMTKHeadSetMessager();
        ALOGD("-UniqueDigitalInstance\n");
    }
    return UniqueHeadsetInstance;
}

bool AudioMTKHeadSetMessager::SetHeadInit() {
    LOG_AudioHeadSetMessager("SetHeadInit");
    int ret = 0;
    if (HeadsetFd < 0) {
        // open headset device
        HeadsetFd = open(HEADSET_PATH, O_RDONLY);
        if (HeadsetFd < 0) {
            ALOGE("open %s error fd = %d", HEADSET_PATH, HeadsetFd);
            return false;
        }
    }
    ret = ::ioctl(HeadsetFd, ACCDET_INIT, 0);
    return true;
}

AudioMTKHeadSetMessager::AudioMTKHeadSetMessager() {
    LOG_AudioHeadSetMessager("AudioHeadSetMessager Contructor");
    if (HeadsetFd >= 0) {
        // open headset device
        ::close(HeadsetFd);
        HeadsetFd = -1;
    }
    hHeadsetReadThread = 0;
}

void AudioMTKHeadSetMessager::SetHeadSetState(int state) {
    LOG_AudioHeadSetMessager("SetHeadSetState state = %d", state);
    int ret = 0;
    if (HeadsetFd <= 0) {
        // open headset device
        HeadsetFd = open(HEADSET_PATH, O_RDONLY);
        if (HeadsetFd < 0) {
            ALOGE("open %s error fd = %d", HEADSET_PATH, HeadsetFd);
            return;
        }
    }
    ret = ::ioctl(HeadsetFd, SET_CALL_STATE, state);
}

bool AudioMTKHeadSetMessager::Get_headset_info(void) {
    int headstatusFd = -1;
    headstatusFd = open(YUSUHEADSET_STAUTS_PATH, O_RDONLY, 0);

    if (headstatusFd < 0) {
        ALOGE("open %s error fd = %d", YUSUHEADSET_STAUTS_PATH, headstatusFd);
        return false;
    }

    if (::read(headstatusFd, rbuf, BUF_LEN) == -1) {
        ALOGD("Get_headset_info Can't read headset");
        ::close(headstatusFd);
        return false;
    }

    ALOGD("%s => %c", YUSUHEADSET_STAUTS_PATH, rbuf[0]);

    if (!strncmp(stringStatusHeadset, rbuf, BUF_LEN)) {
        ::close(headstatusFd);
        return true;
    } else if (!strncmp(stringStatusEarphone, rbuf, BUF_LEN)) {
        ::close(headstatusFd);
        return true;
    } else {
        ::close(headstatusFd);
        return false;
    }
}


bool AudioMTKHeadSetMessager::isHeadsetPlugged() {
    int headstatusFd = open(YUSUHEADSET_STAUTS_PATH, O_RDONLY, 0);

    if (headstatusFd < 0) {
        ALOGE("open %s error fd = %d", YUSUHEADSET_STAUTS_PATH, headstatusFd);
        return false;
    }

    if (::read(headstatusFd, rbuf, BUF_LEN) == -1) {
        ALOGD("Get_headset_info Can't read headset");
        ::close(headstatusFd);
        return false;
    }

    ALOGD("%s => %c", YUSUHEADSET_STAUTS_PATH, rbuf[0]);

    if (!strncmp(stringStatusHeadset, rbuf, BUF_LEN)) {
        ::close(headstatusFd);
        return true;
    } else {
        ::close(headstatusFd);
        return false;
    }
}

bool AudioMTKHeadSetMessager::isEarphonePlugged() {
    int headstatusFd = open(YUSUHEADSET_STAUTS_PATH, O_RDONLY, 0);

    if (headstatusFd < 0) {
        ALOGE("open %s error fd = %d", YUSUHEADSET_STAUTS_PATH, headstatusFd);
        return false;
    }

    if (::read(headstatusFd, rbuf, BUF_LEN) == -1) {
        ALOGD("Get_headset_info Can't read headset");
        ::close(headstatusFd);
        return false;
    }

    ALOGD("%s => %c", YUSUHEADSET_STAUTS_PATH, rbuf[0]);

    if (!strncmp(stringStatusEarphone, rbuf, BUF_LEN)) {
        ::close(headstatusFd);
        return true;
    } else {
        ::close(headstatusFd);
        return false;
    }
}

}


