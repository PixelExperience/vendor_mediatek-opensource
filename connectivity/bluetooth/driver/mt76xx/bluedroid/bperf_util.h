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

#ifndef __BT_BPERF_IF_H__
#define __BT_BPERF_IF_H__

#include "os_dep.h"

#define NONECOLOR       "\033[m"
#define GRAY            "\033[1;30m"
#define RED             "\033[0;31m"
#define LIGHT_RED       "\033[1;31m"
#define GREEN           "\033[0;32m"
#define LIGHT_GREEN     "\033[1;32m"
#define BROWN           "\033[0;33m"
#define YELLOW          "\033[1;33m"
#define BLUE            "\033[0;34m"
#define LIGHT_BLUE      "\033[1;34m"
#define PURPLE          "\033[0;35m"
#define LIGHT_PURPLE    "\033[1;35m"
#define CYAN            "\033[0;36m"
#define LIGHT_CYAN      "\033[1;36m"
#define LIGHT_WHITE     "\033[1;37m"

enum{
    BPERF_STATE_UNKNOWN,
    BPERF_STATE_THREAD_RUNNING,
    BPERF_STATE_THREAD_STOPPED
};

enum{
    BPERF_DATA_TYPE_HOGP,
    BPERF_DATA_TYPE_HID,
    BPERF_DATA_TYPE_A2DP,
    BPERF_DATA_TYPE_VOICE,
    BPERF_DATA_TYPE_UNKNOWN
};

struct bperf_event {
    unsigned short id;
    unsigned int time;
    unsigned int buf_len;
};

void bperf_notify_data(const uint8_t *buf, const unsigned int buf_len);
void bperf_init();
void bperf_uninit();
#endif
