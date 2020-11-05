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

#ifndef ANDROID_SF_WATCHDOGAPI
#define ANDROID_SF_WATCHDOGAPI

#include <stdint.h>
#include <sys/types.h>
#include <utils/String8.h>

#include "ui_ext/SWWatchDog.h"


namespace android {

class SFWatchDogAPI : public SWWatchDog {
public:
    SFWatchDogAPI() {}
    virtual ~SFWatchDogAPI() {}

    /**
     * Hide SWWatchDog::setAnchor/delAnchor.
     * Because SFWatchDog only support to set one anchor at a time.
     * @param  msg The meesage want to pass to onTimeout.
     * @return     Success or Fail
     */
    virtual bool setAnchor(const String8& /*msg*/);
    virtual bool delAnchor();

    /**
     * Set Watchdog Suspend/Resume, and kick aee wdt
     */
    virtual void setSuspend();
    virtual void setResume();

    /**
     * Set the WatchDog timeout threshold.
     * It will only effect the anchor which create by this SWWatchDog in the future.
     * @param threshold The anchor timeout threshold, unit: ms
     */
    virtual void setThreshold(const SWWatchDog::msecs_t& /*threshold*/);
};

extern "C"
{
    SFWatchDogAPI *createInstance();
}

};  // namespace android

#endif  //ANDROID_SF_WATCHDOGAPI
