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

#ifndef ANDROID_UTILITY_VPU_H
#define ANDROID_UTILITY_VPU_H

extern int vpu_init(int power_on_init);
extern int mdla_init(int power_on_init);
extern int setVpuFreqMin_core_0(int value, void *scn);
extern int setVpuFreqMax_core_0(int value, void *scn);
extern int setVpuFreqMin_core_1(int value, void *scn);
extern int setVpuFreqMax_core_1(int value, void *scn);
extern int setMdlaFreqMin(int value, void *scn);
extern int setMdlaFreqMax(int value, void *scn);

#endif // ANDROID_UTILITY_VPU_H
