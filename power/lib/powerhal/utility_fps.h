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

#ifndef ANDROID_UTILITY_FPS_H
#define ANDROID_UTILITY_FPS_H

#define PATH_FSTB_FPS             "/sys/kernel/debug/fpsgo/fstb/fstb_level"
#define PATH_FSTB_SOFT_FPS        "/sys/kernel/debug/fpsgo/fstb/fstb_soft_level"
#define PATH_FSTB_LIST            "/sys/kernel/debug/fpsgo/fstb/fstb_fps_list"
#define PATH_FSTB_LIST_FILE       "/vendor/etc/fstb.cfg"
#define PATH_FTEH_LIST            "/sys/kernel/debug/fpsgo/fstb/fstb_fteh_list"
#define PATH_FTEH_LIST_FILE       "/vendor/etc/fteh.cfg"

extern int fstb_init(int power_on_init);
extern int setFstbFpsHigh(int fps_high, void *scn);
extern int setFstbFpsLow(int fps_low, void *scn);
extern int setFstbSoftFpsHigh(int fps_high, void *scn);
extern int setFstbSoftFpsLow(int fps_low, void *scn);
extern int setCfpUpLoading(int up_loading, void *scn);
extern int setCfpDownLoading(int down_loading, void *scn);

#endif // ANDROID_UTILITY_FPS_H
