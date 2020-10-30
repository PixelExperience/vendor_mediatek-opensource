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

#ifndef _AUDIO_HEADSET_MESSAGE_H_
#define _AUDIO_HEADSET_MESSAGE_H_

/*****************************************************************************
*                E X T E R N A L   R E F E R E N C E S
******************************************************************************
*/
#include <sys/ioctl.h>

/*****************************************************************************
*                          C O N S T A N T S
******************************************************************************
*/

#define ACCDET_IOC_MAGIC 'A'
#define ACCDET_INIT       _IO(ACCDET_IOC_MAGIC,0)  // call wehn first time
#define SET_CALL_STATE    _IO(ACCDET_IOC_MAGIC,1)  // when state is changing , tell headset driver.
#define GET_BUTTON_STATUS _IO(ACCDET_IOC_MAGIC,2)  // ioctl to get hook button state.

static const char *HEADSET_PATH = "/dev/accdet";
static const char *YUSUHEADSET_STAUTS_PATH = "/sys/bus/platform/drivers/Accdet_Driver/state";

namespace android {

/*****************************************************************************
*                        F U N C T I O N   D E F I N I T I O N
******************************************************************************
*/
class AudioMTKHeadSetMessager {
public:
    static AudioMTKHeadSetMessager *getInstance();
    bool Get_headset_info(void);

    bool isEarphonePlugged(); // w/o headset mic
    bool isHeadsetPlugged();  // w   headset mic

    bool SetHeadInit(void);
    void SetHeadSetState(int state);

private:
    static AudioMTKHeadSetMessager *UniqueHeadsetInstance;
    // private constructor
    AudioMTKHeadSetMessager();
    AudioMTKHeadSetMessager(const AudioMTKHeadSetMessager &);             // intentionally undefined
    AudioMTKHeadSetMessager &operator=(const AudioMTKHeadSetMessager &);  // intentionally undefined

    pthread_t hHeadsetReadThread;
};

}; // namespace android

#endif

