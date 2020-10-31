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

//#include "nvram_agent.h"
#include "libnvram.h"
#include "libnvram_log.h"
#include <iostream>


#include <cutils/properties.h>
#include <vendor/mediatek/hardware/nvram/1.1/INvram.h>
#include <log/log.h>
#include <hidl/LegacySupport.h>

int
main(void)
{
    int ret = 0;
using vendor::mediatek::hardware::nvram::V1_1::INvram;
using android::hardware::defaultPassthroughServiceImplementation;
    try {
    NVRAM_LOG("Nvram hidle service is now ready");
      ret =defaultPassthroughServiceImplementation<INvram>();
    } catch (const std::__1::system_error & e) {
      NVRAM_LOG("Nvram hidle service error");
    }
    return ret;
}

