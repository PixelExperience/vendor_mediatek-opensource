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
#include "utility_vpu.h"

#define VPU_CORE_MAX    2
#define VPU_BOOST_MAX   100
#define MDLA_BOOST_MAX  100

#define PATH_VPU_BOOST_CTRL   "/sys/kernel/debug/vpu/power"
#define PATH_MDLA_BOOST_CTRL  "/sys/kernel/debug/mdla/power"

static int vpu_min_now[VPU_CORE_MAX];
static int vpu_max_now[VPU_CORE_MAX];
static int mdla_min_now;
static int mdla_max_now;


static void setVPUboost(int core, int boost_h, int boost_l)
{
    static int vpu_support = -1;
    struct stat stat_buf;
    char str[256], buf[256];

    if (vpu_support == -1) {
        vpu_support = (0 == stat(PATH_VPU_BOOST_CTRL, &stat_buf)) ? 1 : 0;
    }

    if (vpu_support != 1)
        return;

    ALOGI("set vpu_boost: %d %d %d", core, boost_l, boost_h);

    boost_h = (boost_h == -1) ? VPU_BOOST_MAX : boost_h;
    boost_l = (boost_l == -1) ? 0 : boost_l;

    /* check ceiling must higher than floor*/
    if (boost_h < boost_l) {
        boost_h = boost_l;
        ALOGI("update set vpu_boost: %d %d %d", core, boost_l, boost_h);
    }

    str[0] = '\0';
    sprintf(buf, "power_hal %d %d %d ", core+1, boost_l, boost_h);
    strncat(str, buf, strlen(buf));
    str[strlen(str)-1] = '\0';
    ALOGV("set vpu_boost: %s", str);
    set_value(PATH_VPU_BOOST_CTRL, str);
}

static void setMDLAboost(int boost_h, int boost_l)
{
    static int mdla_support = -1;
    struct stat stat_buf;
    char str[256], buf[256];

    if (mdla_support == -1) {
        mdla_support = (0 == stat(PATH_VPU_BOOST_CTRL, &stat_buf)) ? 1 : 0;
    }

    if (mdla_support != 1)
        return;

    ALOGI("set mdla_boost: %d  %d", boost_l, boost_h);

    boost_h = (boost_h == -1) ? MDLA_BOOST_MAX : boost_h;
    boost_l = (boost_l == -1) ? 0 : boost_l;

      /* check ceiling must higher than floor*/
    if (boost_h < boost_l) {
        boost_h = boost_l;
        ALOGI("update set mdla_boost: %d %d", boost_l, boost_h);
    }
    str[0] = '\0';
    sprintf(buf, "power_hal %d %d ", boost_l, boost_h);
    strncat(str, buf, strlen(buf));
    str[strlen(str)-1] = '\0';
    ALOGV("set mdla_boost: %s", str);
    set_value(PATH_MDLA_BOOST_CTRL, str);
}

int vpu_init(int poweron_init)
{
    int i;
    ALOGV("vpu_init: %d", poweron_init);

    for(i=0; i<VPU_CORE_MAX; i++) {
        vpu_min_now[i] = -1;
        vpu_max_now[i] = -1;
    }
    return 0;
}

int mdla_init(int poweron_init)
{
    ALOGV("mdla_init: %d", poweron_init);
    mdla_min_now = mdla_max_now = -1;
    return 0;
}

int setVpuFreqMin_core_0(int value, void *scn)
{
    ALOGV("setVpuFreqMin_core_0: %p", scn);
    vpu_min_now[0] = value;
    setVPUboost(0, vpu_max_now[0], vpu_min_now[0]);
    return 0;
}

int setVpuFreqMax_core_0(int value, void *scn)
{
    ALOGV("setVpuFreqMax_core_0: %p", scn);
    vpu_max_now[0] = value;
    setVPUboost(0, vpu_max_now[0], vpu_min_now[0]);
    return 0;
}

int setVpuFreqMin_core_1(int value, void *scn)
{
    ALOGV("setVpuFreqMin_core_1: %p", scn);
    vpu_min_now[1] = value;
    setVPUboost(1, vpu_max_now[1], vpu_min_now[1]);
    return 0;
}

int setVpuFreqMax_core_1(int value, void *scn)
{
    ALOGV("setVpuFreqMax_core_1: %p", scn);
    vpu_max_now[1] = value;
    setVPUboost(1, vpu_max_now[1], vpu_min_now[1]);
    return 0;
}

int setMdlaFreqMin(int value, void *scn)
{
    ALOGV("setMdlaFreqMin: %p", scn);
    mdla_min_now = value;
    setMDLAboost(mdla_max_now, mdla_min_now);
    return 0;
}

int setMdlaFreqMax(int value, void *scn)
{
    ALOGV("setMdlaFreqMax: %p", scn);
    mdla_max_now = value;
    setMDLAboost(mdla_max_now, mdla_min_now);
    return 0;
}
