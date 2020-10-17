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
 * command table extend
 */

enum class MtkPowerCmdInternal : uint32_t {
   CMD_SET_FROM_JUMP = 141, // shell align with vendor::mediatek::hardware::power::V2_1::MtkPowerCmd::CMD_SET_END_JUMP_2_1
   CMD_SET_F2FS_UFS_BOOST,
   CMD_SET_F2FS_EMMC_BOOST,
   CMD_SET_BLKDEV_READAHEAD,
   CMD_SET_FPSGO_GPU_BLOCK_BOOST,
   CMD_SET_FBT_BOOST_TA,
   CMD_SET_SCHEDPLUS_DOWN_THROTTLE_NS,
   CMD_SET_SCHEDPLUS_SYNC_FLAG,
   CMD_SET_GED_MARGIN_MODE,
   CMD_SET_FPSGO_MARGIN_MODE,
   CMD_SET_EARA_THERMAL_ENABLE, // 151
   CMD_SET_FBT_RESCUE_F,
   CMD_SET_FBT_RESCUE_PERCENT,
   CMD_SET_FBT_ULTRA_RESCUE,
   CMD_SET_FBT_DEQTIME_BOUND,
   CMD_SET_TOUCH_OPP,
   CMD_SET_TOUCH_DURATION,
   CMD_SET_TOUCH_ACTIVE_TIME,
   CMD_SET_SCHEDPLUS_UP_THROTTLE_NS,
   CMD_SET_FBT_SHORT_RESCUE_NS,
   CMD_SET_FBT_MIN_RESCUE_PERCENT, // 161
   CMD_SET_GED_TIMER_BASE_DVFS_MARGIN,
   CMD_SET_GED_LOADING_BASE_DVFS_STEP,
   CMD_SET_GED_CWAITG,
   CMD_SET_FPSGO_MARGIN_MODE_DBNC_A,
   CMD_SET_FPSGO_MARGIN_MODE_DBNC_B,
   CMD_SET_UNUSE_167,
   CMD_SET_UNUSE_168,
   CMD_SET_UNUSE_169,
   CMD_SET_UNUSE_170,
   CMD_SET_WIFI_SMART_PREDICT, // 171
   CMD_SET_UX_PREDICT_LOW_LATENCY,
   CMD_SET_SCN_TIMEOUT,
   CMD_SET_APP_CRASH,
   CMD_SET_CERT_PID,
   CMD_SET_CFP_ENABLE,
   CMD_SET_CFP_POLLING_MS,
   CMD_SET_CFP_UP_LOADING,
   CMD_SET_CFP_DOWN_LOADING,
   CMD_SET_CFP_UP_TIME,
   CMD_SET_CFP_DOWN_TIME, // 181
   CMD_SET_CFP_UP_OPP,
   CMD_SET_CFP_DOWN_OPP,
};
