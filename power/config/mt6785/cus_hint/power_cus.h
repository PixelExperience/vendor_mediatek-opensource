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

/*
 * customized hint config table
 */

#include <power_cus_types.h>
#include "mtkperf_resource.h"

struct tCusConfig cusHintConfigImpl[] = {
   /* example
    * {HINT, resource_size*2 , {resorce_list}},
    */

    // MTK_CUS_AUDIO_LATENCY_DL
    {(int)MtkCusPowerHintInternal::MTK_CUS_AUDIO_LATENCY_DL, 4, {PERF_RES_CPUCORE_MIN_CLUSTER_0, 2, PERF_RES_POWERHAL_SCREEN_OFF_STATE, 1}},

    // MTK_CUS_AUDIO_LATENCY_UL
    {(int)MtkCusPowerHintInternal::MTK_CUS_AUDIO_LATENCY_UL, 4, {PERF_RES_CPUCORE_MIN_CLUSTER_0, 2, PERF_RES_POWERHAL_SCREEN_OFF_STATE, 1}},

    // MTK_CUS_AUDIO_Power_DL
    {(int)MtkCusPowerHintInternal::MTK_CUS_AUDIO_POWER_DL,  4, {PERF_RES_CPUFREQ_MIN_CLUSTER_0, 800000, PERF_RES_POWERHAL_SCREEN_OFF_STATE, 1}},

    // MTK_CUS_AUDIO_DISABLE_WIFI_POWER_SAVE
    {(int)MtkCusPowerHintInternal::MTK_CUS_AUDIO_DISABLE_WIFI_POWER_SAVE, 4, {PERF_RES_NET_WIFI_CAM, 1, PERF_RES_POWERHAL_SCREEN_OFF_STATE, 1}},

    {-1, 0, {0}},
};
