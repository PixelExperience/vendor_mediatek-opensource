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
#include "utility_sys.h"

/* variable */
static int cpu_prefer_support = 0;


/* function */
int initTaskPreferCpu(int power_on)
{
    struct stat stat_buf;

    ALOGV("cpu_prefer_init: %d", power_on);
    cpu_prefer_support = (0 == stat(PATH_TASK_PREFER_CPU, &stat_buf)) ? 1 : 0;
    return 0;
}

int setTaskPreferCpu_big(int tid, void *scn)
{
    char str[64];
    if(!cpu_prefer_support)
        return -1;

    ALOGI("setTaskPreferCpu_big:%d", tid);
    snprintf(str, sizeof(str)-1, "%d 1", tid);
    set_value(PATH_TASK_PREFER_CPU, str);
    return 0;
}

int unsetTaskPreferCpu_big(int tid, void *scn)
{
    char str[64];
    if(!cpu_prefer_support)
        return -1;

    ALOGI("unsetTaskPreferCpu_big:%d", tid);
    snprintf(str, sizeof(str)-1, "%d 0", tid);
    set_value(PATH_TASK_PREFER_CPU, str);
    return 0;
}

int setTaskPreferCpu_little(int tid, void *scn)
{
    char str[64];
    if(!cpu_prefer_support)
        return -1;

    ALOGI("setTaskPreferCpu_little:%d", tid);
    snprintf(str, sizeof(str)-1, "%d 2", tid);
    set_value(PATH_TASK_PREFER_CPU, str);
    return 0;
}

int unsetTaskPreferCpu_little(int tid, void *scn)
{
    char str[64];
    if(!cpu_prefer_support)
        return -1;

    ALOGI("unsetTaskPreferCpu_little:%d", tid);
    snprintf(str, sizeof(str)-1, "%d 0", tid);
    set_value(PATH_TASK_PREFER_CPU, str);
    return 0;
}
