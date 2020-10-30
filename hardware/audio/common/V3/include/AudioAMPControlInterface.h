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

#ifndef __AUDIO_AMP_CONTROL_INTERFACE_H__
#define __AUDIO_AMP_CONTROL_INTERFACE_H__

namespace android {

enum AUDIO_AMP_CONTROL_COMMAND {
    AUD_AMP_GET_CTRP_NUM,
    AUD_AMP_GET_CTRP_BITS,
    AUD_AMP_GET_CTRP_TABLE,
    AUD_AMP_GET_REGISTER,
    AUD_AMP_SET_REGISTER,
    AUD_AMP_SET_AMPGAIN,  // gain is use for low 24bits as external amp , device should base on control point set to AMPLL_CON0_REG
    AUD_AMP_GET_AMPGAIN,
    AUD_AMP_SET_MODE,
    NUM_AUD_AMP_CONTROL_COMMAND
};

typedef struct {
    unsigned long int   command;
    unsigned long int   param1;
    unsigned long int   param2;
} AMP_Control;

class AudioAMPControlInterface {
public:
    AudioAMPControlInterface() {}
    virtual ~AudioAMPControlInterface() {}
    //open/close device
    virtual bool setSpeaker(bool on) = 0;
    virtual bool setHeadphone(bool on) = 0;
    virtual bool setReceiver(bool on) = 0;
    virtual status_t setVolume(void *points, int num, int device) = 0;
    //set mode to amp
    virtual void setMode(audio_mode_t mode) = 0;
    // for set and get parameters , for command1 and command 2 , use to command
    // and data is used for comamnd need to carry a lots of command.
    virtual status_t setParameters(int command1, int command2, unsigned int data) = 0;
    virtual status_t getParameters(int command1, int command2, void *data) = 0;
};

class AudioDeviceManger {
public:
    static AudioAMPControlInterface *createInstance();
private:
    static AudioAMPControlInterface *mInstance;
};

}

#endif

