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

#ifndef ANDROID_UTILITY_THERMAL_H
#define ANDROID_UTILITY_THERMAL_H

#include <string>

using namespace std;

#define MAX_CONF_NAME   (18)

enum thermal_error{
    TS_ERR_NO_FILE_EXIST = -3,  /*< file is not exist */
    TS_ERR_NO_INIT = -2,        /*< not initialized */
    TS_ERR_NO_LOAD = -1,        /*< unnecessary to load conf */
    TS_ERR_UNKNOW
};

typedef struct {
    int policy_count;
    int policy_active;
} thermal_policy_manager_type;

typedef struct {
    char conf_name[MAX_CONF_NAME];
    int perf_used;
} thermal_conf_type;

extern int load_thm_api_start(int idx, void *scn);
extern int load_thm_api_stop(int idx, void *scn);
extern int reset_thermal_policy(int power_on_init);

#endif // ANDROID_UTILITY_THERMAL_H
