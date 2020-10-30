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

#ifndef _CFG_FG_D_H
#define _CFG_FG_D_H
ap_nvram_fg_config_struct stFGConfigDefault =
{
    /* dsp_dev[20]: if chip detector say it's not 3332 use /dev/stpfg,else use /ttyMT1 */
    {'/','d','e','v','/','s','t','p','f','g','d',0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
    /* nvram_car_tune_value: */
    119
};
#endif /* _CFG_FG_D_H */
