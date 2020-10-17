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

enum class MtkCusPowerHintInternal : uint32_t {
    MTK_CUS_AUDIO_LATENCY_DL = 0u, // 0
    MTK_CUS_AUDIO_LATENCY_UL = 1u, // 1
    MTK_CUS_AUDIO_POWER_DL = 2u, // 2
    MTK_CUS_AUDIO_DISABLE_WIFI_POWER_SAVE = 3u, //3
    MTK_CUS_HINT_NUM = 4u, // 4
};
