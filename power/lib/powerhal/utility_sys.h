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

#ifndef ANDROID_UTILITY_SYS_H
#define ANDROID_UTILITY_SYS_H

#define PATH_TASK_PREFER_CPU   "/sys/devices/system/cpu/sched/cpu_prefer"

extern int initTaskPreferCpu(int power_on);
extern int setTaskPreferCpu_big(int tid, void *scn);
extern int unsetTaskPreferCpu_big(int tid, void *scn);
extern int setTaskPreferCpu_little(int tid, void *scn);
extern int unsetTaskPreferCpu_little(int tid, void *scn);

#endif // ANDROID_UTILITY_FPS_H
