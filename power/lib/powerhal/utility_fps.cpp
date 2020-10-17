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

#define LOG_TAG "libPowerHal"

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <utils/Log.h>
#include <errno.h>
#include <sys/stat.h>

#include "common.h"
#include "utility_fps.h"

#define FSTB_FPS_LEN    32

#define PATH_CFP_UP_LOADING       "/proc/perfmgr/boost_ctrl/cpu_ctrl/cfp_up_loading"
#define PATH_CFP_DOWN_LOADING     "/proc/perfmgr/boost_ctrl/cpu_ctrl/cfp_down_loading"

/* variable */
static int fstb_support = 0;
static char pFstbDefaultFps[FSTB_FPS_LEN];
static char pFstbDefaultSoftFps[FSTB_FPS_LEN];
static int fps_high_now = -1;
static int fps_low_now = -1;
static int fps_soft_high_now = -1;
static int fps_soft_low_now = -1;
static int cpu_up_loading_now = -1;
static int cpu_down_loading_now = -1;

/* static function */
static void init_fstb(void)
{
    char line[256];
    FILE* file = fopen(PATH_FSTB_LIST_FILE, "r");

    if (file) {
        while (fgets(line, sizeof(line), file)) {
            set_value(PATH_FSTB_LIST, line);
            ALOGI("%s %s", __func__, line);
        }
        fclose(file);
    }
}

static void init_fteh(void)
{
    char line[256];
    FILE* file = fopen(PATH_FTEH_LIST_FILE, "r");

    if (file) {
        while (fgets(line, sizeof(line), file)) {
            set_value(PATH_FTEH_LIST, line);
            ALOGI("%s %s", __func__, line);
        }
        fclose(file);
    }
}

static void setFstbFps(int fps_high, int fps_low)
{
    char fstb_fps[FSTB_FPS_LEN] = "";
    if (fstb_support) {
        if (fps_high == -1 && fps_low == -1) {
            ALOGV("set fstb_fps: %s", pFstbDefaultFps);
            set_value(PATH_FSTB_FPS, pFstbDefaultFps);
        } else {
            sprintf(fstb_fps, "1 %d-%d", fps_high_now, fps_low_now);
            ALOGV("set fstb_fps: %s", fstb_fps);
            set_value(PATH_FSTB_FPS, fstb_fps);
        }
   }
}

static void setFstbSoftFps(int fps_high, int fps_low)
{
    char fstb_fps[FSTB_FPS_LEN] = "";
    if (fstb_support) {
        if (fps_high == -1 && fps_low == -1) {
            ALOGV("set fstb_fps: %s", pFstbDefaultSoftFps);
            set_value(PATH_FSTB_SOFT_FPS, pFstbDefaultSoftFps);
        } else {
            sprintf(fstb_fps, "1 %d-%d", fps_high, fps_low);
            ALOGV("set fstb_fps: %s", fstb_fps);
            set_value(PATH_FSTB_SOFT_FPS, fstb_fps);
        }
   }
}

static void setCfpLoading(int up_loading, int down_loading)
{
    int cur_up, cur_down;
    static int cfpSupport = -1, nDefaultCfpUpLoading, nDefaultCfpDownLoading;
    struct stat stat_buf;

    if (up_loading != -1 && down_loading != -1 && up_loading < down_loading) {
        ALOGE("setCfpLoading wrong input:%d, %d", up_loading, down_loading);
        return;
    }

    if (cfpSupport == -1) {
        if (0 == stat(PATH_CFP_UP_LOADING, &stat_buf)) {
            cfpSupport = 1;
            nDefaultCfpUpLoading = get_int_value(PATH_CFP_UP_LOADING);
            nDefaultCfpDownLoading = get_int_value(PATH_CFP_DOWN_LOADING);
        }
        else {
            cfpSupport = 0;
        }
    }

    if (up_loading == -1)
        up_loading = nDefaultCfpUpLoading;
    if (down_loading == -1)
        down_loading = nDefaultCfpDownLoading;

    if (cfpSupport) {
        ALOGI("set cfp loading: %d %d", up_loading, down_loading);
        cur_up = get_int_value(PATH_CFP_UP_LOADING);
        cur_down = get_int_value(PATH_CFP_DOWN_LOADING);

        if (up_loading >= cur_up) {
            set_value(PATH_CFP_UP_LOADING, up_loading);
            set_value(PATH_CFP_DOWN_LOADING, down_loading);
        } else {
            set_value(PATH_CFP_DOWN_LOADING, down_loading);
            set_value(PATH_CFP_UP_LOADING, up_loading);
        }
    }
}

/* function */
int fstb_init(int power_on)
{
    struct stat stat_buf;
    char str2[FSTB_FPS_LEN];

    ALOGV("fstb_init: %d", power_on);
    fstb_support = (0 == stat(PATH_FSTB_SOFT_FPS, &stat_buf)) ? 1 : 0;

    if(fstb_support) {
        get_str_value(PATH_FSTB_FPS, str2, sizeof(str2)-1);
        strncpy(pFstbDefaultFps, str2, FSTB_FPS_LEN - 1);
        get_str_value(PATH_FSTB_SOFT_FPS, str2, sizeof(str2)-1);
        strncpy(pFstbDefaultSoftFps, str2, FSTB_FPS_LEN - 1);
        ALOGI("pFstbDefaultFps:%s", pFstbDefaultFps);
        if (0 == stat(PATH_FSTB_LIST, &stat_buf))
            init_fstb();
        if (0 == stat(PATH_FTEH_LIST, &stat_buf))
            init_fteh();
    }
    return 0;
}

int setFstbFpsHigh(int fps_high, void *scn)
{
    ALOGV("setFstbFpsHigh: %p", scn);
    fps_high_now = fps_high;
    setFstbFps(fps_high_now, fps_low_now);
    return 0;
}

int setFstbFpsLow(int fps_low, void *scn)
{
    ALOGV("setFstbFpsLow: %p", scn);
    fps_low_now = fps_low;
    setFstbFps(fps_high_now, fps_low_now);
    return 0;
}

int setFstbSoftFpsHigh(int fps_high, void *scn)
{
    ALOGV("setFstbSoftFpsHigh: %p", scn);
    fps_soft_high_now = fps_high;
    setFstbSoftFps(fps_soft_high_now, fps_soft_low_now);
    return 0;
}

int setFstbSoftFpsLow(int fps_low, void *scn)
{
    ALOGV("setFstbSoftFpsLow: %p", scn);
    fps_soft_low_now = fps_low;
    setFstbSoftFps(fps_soft_high_now, fps_soft_low_now);
    return 0;
}

int setCfpUpLoading(int up_loading, void *scn)
{
    ALOGV("setCfpUpLoading: %p", scn);
    cpu_up_loading_now = up_loading;
    setCfpLoading(cpu_up_loading_now, cpu_down_loading_now);
    return 0;
}

int setCfpDownLoading(int down_loading, void *scn)
{
    ALOGV("setCfpDownLoading: %p", scn);
    cpu_down_loading_now = down_loading;
    setCfpLoading(cpu_up_loading_now, cpu_down_loading_now);
    return 0;
}
