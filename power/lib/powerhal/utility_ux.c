/* Copyright (C) 2020 The Evolution X Project
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
 * Include
 *****************************************************************************/
#include <dlfcn.h>
#include "utility_ux.h"
#include "utility_netd.h"
#include <utils/Log.h>

/*****************************************************************************
 * ux_utility
 *****************************************************************************/
#undef LOG_TAG
#define LOG_TAG "UxUtility"
#define UX_RIL_PATH "libnwk_opt_halwrap_vendor.so"
void* sDlOpHandler = NULL;
void* func = NULL;

static int (*UxGameEvent)(int, int) = NULL;
static int (*notifyAppState)(const char*, const char*, uint32_t) = NULL;
static bool initlib = false;

static void initUxLibrary() {
    if (initlib) return;
    initlib = true;
    sDlOpHandler = dlopen(UX_RIL_PATH, RTLD_NOW);
    if (sDlOpHandler == NULL) {
        ALOGE("[%s] dlopen failed in %s: %s",
                __FUNCTION__, UX_RIL_PATH, dlerror());
        return;
    }
    func = dlsym(sDlOpHandler, "NwkOptHal_wrap_switch_game_mode_S");
    UxGameEvent = (power_notify_ux_game_event)(func);
    const char* dlsym_error = dlerror();

    if (UxGameEvent == NULL) {
        ALOGE("UxGameEvent error: %s", dlsym_error);
        return;
    }
    dlerror();
    func = dlsym(sDlOpHandler, "NwkOptHal_Wrap_notifyAppState_S");
    notifyAppState = (power_notify_AppState)(func);
    dlsym_error = dlerror();

    if (notifyAppState == NULL) {
        ALOGE("notifyAppState error: %s", dlsym_error);
        return;
    }

    // reset errors
    dlerror();

    ALOGD("[%s] completed", __FUNCTION__);
}

static int notifyUxGameEvent(int mode) {
    initUxLibrary();
    if (UxGameEvent == NULL) {
        ALOGE("notifyUxGameEvent error = NULL");
        return -1;
    }
    return UxGameEvent(mode, -1);
}

static void notifyNetdBoostUid(int enable, int uid) /* -1: don't care */
{
    static int netd_boost = -1;
    static int boost_uid = -1;
    int last_boost_uid = -1;

    ALOGD("notifyNetdBoostUid enable:%d -> %d, uid:%d -> %d",
        netd_boost, enable, boost_uid, uid);

    if (enable != -1 && enable != netd_boost) { /* -1: don't care */
        netd_boost = enable;

        if (netd_boost == 1) {
            if (boost_uid != -1) {
                netd_set_priority_uid(boost_uid, NULL);
            }
        } else {
            if (boost_uid != -1) {
                netd_clear_priority_uid(boost_uid, NULL);
            }
        }
    }

    if (uid != -1 && uid != boost_uid) { /* -1: don't care */
        last_boost_uid = boost_uid;
        boost_uid = uid;

        if (netd_boost == 1) {
            if (last_boost_uid != -1) {
                netd_clear_priority_uid(last_boost_uid, NULL);
            }

            if (boost_uid != -1) {
                netd_set_priority_uid(boost_uid, NULL);
            }
        }
    }
}

void notify_APPState(const char *packname, int32_t uid) {
    initUxLibrary();
    if (notifyAppState == NULL) {
        ALOGE("notifyAppState error = NULL");
        return;
    }
    notifyAppState(packname, NULL, uid);
    ALOGI("notifyAppState pack:%s, uid:%d", packname, uid);
}

void notifyForegroundApp(const char *packname, int32_t uid) {
    initUxLibrary();
    if (notifyAppState == NULL) {
        ALOGE("notifyAppState error = NULL");
        return;
    }
    notifyAppState(NULL, packname, uid);
    notifyNetdBoostUid(-1, uid);
    ALOGI("notifyForegroundApp pack:%s, uid:%d", packname, uid);
}

int notifyLowLatencyMode(int lowLatencyMode, void *scn) {
    ALOGV("notifyLowLatencyMode: %p", scn);
    if (lowLatencyMode == -1) return 0;
    if (lowLatencyMode == 1) {
        notifyUxGameEvent(GAME_EVENT_LOW_LATENCY);
        notifyNetdBoostUid(1, -1);
    } else if (lowLatencyMode == 0) {
        notifyUxGameEvent(GAME_EVENT_IDLE);
        notifyNetdBoostUid(0, -1);
    }
    ALOGD("notifyUxLatencyMode latency:%d", lowLatencyMode);
    return 0;
}

int resetUtilityUx(int poweron_init)
{
    if(poweron_init != 1) {
        notifyLowLatencyMode(0, NULL);
    }
    return 0;
}

void notifyCmdMode(int mode) {
    notifyUxGameEvent(mode | 0x10);
}
