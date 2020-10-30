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

#ifndef __MTKPOWER_HINT_H__
#define __MTKPOWER_HINT_H__

/* IMtkPower::mtkPowerHint */
enum {
    MTKPOWER_HINT_BASE                  = 30,
    MTKPOWER_HINT_PROCESS_CREATE        = 31,
    MTKPOWER_HINT_PACK_SWITCH           = 32,
    MTKPOWER_HINT_ACT_SWITCH            = 33,
    MTKPOWER_HINT_GAME_LAUNCH           = 34,
    MTKPOWER_HINT_APP_ROTATE            = 35,
    MTKPOWER_HINT_APP_TOUCH             = 36,
    //MTKPOWER_HINT_FRAME_UPDATE          = 37, // no user
    MTKPOWER_HINT_GAMING                = 38,
    MTKPOWER_HINT_GALLERY_BOOST         = 39,
    MTKPOWER_HINT_GALLERY_STEREO_BOOST  = 40,
    MTKPOWER_HINT_SPORTS                = 41,
    MTKPOWER_HINT_TEST_MODE             = 42,
    MTKPOWER_HINT_WFD                   = 43,
    MTKPOWER_HINT_PMS_INSTALL           = 44,
    MTKPOWER_HINT_EXT_LAUNCH            = 45,
    MTKPOWER_HINT_WHITELIST_LAUNCH      = 46,
    MTKPOWER_HINT_WIPHY_SPEED_DL        = 47,
    MTKPOWER_HINT_SDN                   = 48,
    MTKPOWER_HINT_NUM                   = 49,
};

enum{
    MTKPOWER_HINT_ALWAYS_ENABLE = 0x0FFFFFFF,
};

#endif // __MTKPOWER_HINT_H__
