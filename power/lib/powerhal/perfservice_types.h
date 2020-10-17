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

#ifndef ANDROID_PERFSERVICE_TYPES_H
#define ANDROID_PERFSERVICE_TYPES_H

#define PACK_NAME_MAX   128
#define CLASS_NAME_MAX  128
#define CLUSTER_MAX     8
#define COMM_NAME_SIZE  64
#define FIELD_SIZE      64


/* Scenarios, MUST align with PerfService.java */
enum {
    STATE_PAUSED    = 0,
    STATE_RESUMED   = 1,
    STATE_DESTORYED = 2,
    STATE_DEAD      = 3,
    STATE_STOPPED   = 4,
    STATE_NUM       = 5,
};

typedef struct tScnNode{
    int  handle_idx;
    int  scn_type;
    int  scn_state;
    char pack_name[PACK_NAME_MAX];
    char act_name[CLASS_NAME_MAX];
    int  scn_core_total;
    int  scn_core_min[CLUSTER_MAX];
    int  scn_core_max[CLUSTER_MAX];
    int  scn_freq_min[CLUSTER_MAX];
    int  scn_freq_max[CLUSTER_MAX];
    int  scn_gpu_freq;
    int  scn_gpu_freq_max;    // upper bound
    int  hint_hold_time;
    int  ext_hint;
    int  ext_hint_hold_time;
    int  launch_time_cold;
    int  launch_time_warm;
    int  screen_off_action;
    int  scn_valid;  // valid of pre-defined scenario
    int  scn_app_crash;  // valid of pre-defined scenario
    int  pid;
    int  tid;
    int  scn_rsc[FIELD_SIZE];
    int  scn_prev_rsc[FIELD_SIZE];
    int  scn_param[FIELD_SIZE];
    int  scn_freq_hard_min[CLUSTER_MAX];
    int  scn_freq_hard_max[CLUSTER_MAX];
    char comm[COMM_NAME_SIZE];
    int  lock_duration;
    int  lock_rsc_size;
    int  *lock_rsc_list;
}tScnNode;

enum {
    SCREEN_OFF_DISABLE      = 0,
    SCREEN_OFF_ENABLE       = 1,
    SCREEN_OFF_WAIT_RESTORE = 2,
};

enum {
    DISPLAY_TYPE_GAME   = 0,
    DISPLAY_TYPE_OTHERS = 1,
    DISPLAY_TYPE_NO_TOUCH_BOOST = 2,
};

enum {
    NOTIFY_USER_TYPE_PID = 0,
    NOTIFY_USER_TYPE_FRAME_UPDATE = 1,
    NOTIFY_USER_TYPE_DISPLAY_TYPE = 2,
    NOTIFY_USER_TYPE_SCENARIO_ON  = 3,
    NOTIFY_USER_TYPE_SCENARIO_OFF = 4,
    NOTIFY_USER_TYPE_CORE_ONLINE  = 5,
    NOTIFY_USER_TYPE_PERF_MODE    = 6,
    NOTIFY_USER_TYPE_OTHERS       = 7,
    NOTIFY_USER_TYPE_DETECT       = 8,
};

enum {
    PERF_MODE_IGNORE = -1,
    PERF_MODE_NORMAL = 0,
    PERF_MODE_SPORTS = 1,
    PERF_MODE_USER_SETTING = 2,
};

enum {
    PPM_MODE_LOW_POWER   = 0,
    PPM_MODE_JUST_MAKE   = 1,
    PPM_MODE_PERFORMANCE = 2,
    PPM_MODE_NUM         = 3,
};

enum {
    DCM_MODE_NORMAL   = 0,
    DCM_MODE_SPORTS   = 1,
    DCM_MODE_NUM      = 2,
};

enum {
    DCS_2_CHANNEL = 0,
    DCS_4_CHANNEL = 1,
    DCS_MODE_NUM  = 2,
};

enum {
    PPM_HICA_VAR_SPORTS = 0,
    PPM_HICA_VAR_NORMAL = 1,
    PPM_HICA_VAR_NUM    = 2,
};

enum {
    DFPS_MODE_DEFAULT = 0,
    DFPS_MODE_FRR,
    DFPS_MODE_ARR,
    DFPS_MODE_INTERNAL_SW,
    DFPS_MODE_MAXIMUM,
};

#endif // ANDROID_PERFSERVICE_H
