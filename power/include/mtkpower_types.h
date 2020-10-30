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

#ifndef __MTKPOWER_TYPES_H__
#define __MTKPOWER_TYPES_H__

enum {
    MTKPOWER_CMD_GET_CLUSTER_NUM             = 1,
    MTKPOWER_CMD_GET_CLUSTER_CPU_NUM         = 2,
    MTKPOWER_CMD_GET_CLUSTER_CPU_FREQ_MIN    = 3,
    MTKPOWER_CMD_GET_CLUSTER_CPU_FREQ_MAX    = 4,
    MTKPOWER_CMD_GET_GPU_FREQ_COUNT          = 5,
    MTKPOWER_CMD_GET_FOREGROUND_PID          = 6,
    MTKPOWER_CMD_GET_FOREGROUND_TYPE         = 7,

    MTKPOWER_CMD_GET_CPU_TOPOLOGY            = 20,
    MTKPOWER_CMD_GET_LOAD_TRACKING           = 21,

    MTKPOWER_CMD_GET_RILD_CAP                = 40,
    MTKPOWER_CMD_GET_TIME_TO_LAST_TOUCH      = 41,

    MTKPOWER_CMD_GET_LAUNCH_TIME_COLD              = 100,
    MTKPOWER_CMD_GET_LAUNCH_TIME_WARM              = 101,
    MTKPOWER_CMD_GET_POWER_HINT_HOLD_TIME          = 102,
    MTKPOWER_CMD_GET_POWER_HINT_EXT_HINT           = 103,
    MTKPOWER_CMD_GET_POWER_HINT_EXT_HINT_HOLD_TIME = 104,
    MTKPOWER_CMD_GET_POWER_SCN_TYPE                = 105,

    MTKPOWER_CMD_GET_DEBUG_SET_LVL           = 200,
    MTKPOWER_CMD_GET_DEBUG_DUMP_ALL          = 201,
    MTKPOWER_CMD_GET_POWERHAL_ONOFF          = 202,
};

enum {
    MTKPOWER_STATE_PAUSED    = 0,
    MTKPOWER_STATE_RESUMED   = 1,
    MTKPOWER_STATE_DESTORYED = 2,
    MTKPOWER_STATE_DEAD      = 3,
    MTKPOWER_STATE_STOPPED   = 4,
};

enum {
    MTKPOWER_SCREEN_OFF_DISABLE      = 0,
    MTKPOWER_SCREEN_OFF_ENABLE       = 1,
    MTKPOWER_SCREEN_OFF_WAIT_RESTORE = 2,
};

enum {
    MTKPOWER_DISP_MODE_DEFAULT = 0,
    MTKPOWER_DISP_MODE_EN      = 1,
    MTKPOWER_DISP_MODE_NUM     = 2,
};

#endif // __MTKPOWER_TYPES_H__
