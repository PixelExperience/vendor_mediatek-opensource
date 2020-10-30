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

/*******************************************************************************
 *
 * Filename:
 * ---------
 * sph_coeff_lpbk_default.h
 *
 * Project:
 * --------
 *   ALPS
 *
 * Description:
 * ------------
 * This file is the header of audio customization related function or definition.
 *
 * Author:
 * -------
 * Tina Tsai
 *
 ****************************************************************************/
#ifndef SPH_COEFF_LPBK_DEFAULT_H
#define SPH_COEFF_LPBK_DEFAULT_H

#define DEFAULT_SPEECH_LPBK_NORMAL_MODE_PARA \
   96,   253,  16388,     31,   57351,     799,   400,     64, \
   80,  4325,      611,       0,   20488,      0,     0,  8192

#define DEFAULT_SPEECH_LPBK_EARPHONE_MODE_PARA \
    0,        189,  10756,      31,   57351,     31,   400,     64, \
    80,  4325,    611,     0, 20488,     0,     0,     0

#define DEFAULT_SPEECH_LPBK_LOUDSPK_MODE_PARA \
    96,   224,  5256,    31, 57351, 24607,   400,   132, \
    84,  4325,    611,     0, 20488,     0,     0,     0

#endif
