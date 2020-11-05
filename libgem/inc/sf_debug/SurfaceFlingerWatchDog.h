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

#ifndef ANDROID_SF_WATCHDOG
#define ANDROID_SF_WATCHDOG

#include <stdint.h>
#include <sys/types.h>
#include <utils/String8.h>
#include <system/window.h>

#include "ui_ext/SWWatchDog.h"
#include "sf_debug/SurfaceFlingerWatchDogAPI.h"

namespace android {

class WDNotify;
class RTTDumper;

class SFWatchDog : public SFWatchDogAPI {
public:
    SFWatchDog();
    ~SFWatchDog();

    /**
     * Hide SWWatchDog::setAnchor/delAnchor.
     * Because SFWatchDog only support to set one anchor at a time.
     * @param  msg The meesage want to pass to onTimeout.
     * @return     Success or Fail
     */
    bool setAnchor(const String8& msg);
    bool delAnchor();

    /**
     * Set Watchdog Suspend/Resume, and kick aee wdt
     */
    void setSuspend();
    void setResume();

    /**
     * Set the WatchDog timeout threshold.
     * It will only effect the anchor which create by this SWWatchDog in the future.
     * @param threshold The anchor timeout threshold, unit: ms
     */
    void setThreshold(const SWWatchDog::msecs_t& threshold);

private:
    friend class WDNotify;
    void getProperty();

    // process WDT notify
    void onSetAnchor(const SWWatchDog::anchor_id_t& id, const pid_t& tid, const nsecs_t& anchorTime,
                     const String8& msg);
    void onDelAnchor(const SWWatchDog::anchor_id_t& id, const pid_t& tid, const nsecs_t& anchorTime,
                     const String8& msg, const nsecs_t& now);
    void onTimeout(  const SWWatchDog::anchor_id_t& id, const pid_t& tid, const nsecs_t& anchorTime,
                     const String8& msg, const nsecs_t& now);
    void onTick(const nsecs_t& now);

    volatile bool mShowLog;
    uint32_t mUpdateCount;
    SWWatchDog::msecs_t mTimer;
    SWWatchDog::msecs_t mThreshold;
    bool mTimeout;
    anchor_id_t mID;
    mutable Mutex mAEELock;
    bool mFreshAnchor;
    mutable Mutex mFreshAnchorLock;
    sp<RTTDumper> mRTTDumper;
};

};  // namespace android

#endif  //ANDROID_SF_WATCHDOG
