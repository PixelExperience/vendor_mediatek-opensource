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

#include <android/log.h>

#ifndef PROPERTY_VALUE_MAX
#define PROPERTY_VALUE_MAX  128
#endif


//----------------debug log define-----------------//
#define LOGV(...) do{ __android_log_print(ANDROID_LOG_VERBOSE, "ccci_lib", __VA_ARGS__); }while(0)

#define LOGD(...) do{ __android_log_print(ANDROID_LOG_DEBUG, "ccci_lib", __VA_ARGS__); }while(0)

#define LOGI(...) do{ __android_log_print(ANDROID_LOG_INFO, "ccci_lib", __VA_ARGS__); }while(0)

#define LOGW(...) do{ __android_log_print(ANDROID_LOG_WARN, "ccci_lib", __VA_ARGS__); }while(0)

#define LOGE(...) do{ __android_log_print(ANDROID_LOG_ERROR, "ccci_lib", __VA_ARGS__); }while(0)

int query_prj_cfg_setting_platform(char name[], char val[], int size);
void AB_image_get(char *buf);

