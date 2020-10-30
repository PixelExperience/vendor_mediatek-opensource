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
 * audio_volume_custom_default.h
 *
 * Project:
 * --------
 *   ALPS
 *
 * Description:
 * ------------
 * This file is the header of audio customization related parameters or definition.
 *
 * Author:
 * -------
 * Chipeng chang
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by CC/CQ. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * $Revision:$
 * $Modtime:$
 * $Log:$
 *
 *
 *
 *
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by CC/CQ. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/
#ifndef AUDIO_VOLUME_CUSTOM_DEFAULT_H
#define AUDIO_VOLUME_CUSTOM_DEFAULT_H

#define AUD_VOLUME_RING \
     {0,32,64,96,128,160,192},\
     {136, 160, 184, 204, 220, 236, 255},\
     {136, 160, 184, 204, 220, 236, 255}

#define AUD_VOLUME_KEY \
     {108, 132, 156, 180, 204, 228, 252},\
     {108, 132, 156, 180, 204, 228, 252},\
     {108, 132, 156, 180, 204, 228, 252}

#define AUD_VOLUME_MIC \
     {64, 255, 255, 148, 200, 200, 160},\
     {225, 192, 192, 160, 216, 208, 172},     \
     {255, 208, 208, 180, 255, 208, 172}

#define AUD_VOLUME_FMR \
     {0,43,85,128,171,213,255},\
     {20, 52, 84, 116, 148, 184, 220},\
     {52, 84, 120, 148, 180, 216, 255}

#define AUD_VOLUME_SPH \
     {40,52,64,76,88,100,112},\
     {40,52,64,76,88,100,112},\
     {40, 52, 64, 76, 88, 100, 112}

#define AUD_VOLUME_SID \
     {0,0,16,0,0,0,0},\
     {0,0,32,0,0,0,0},\
     {0,0,0,0,0,0,0}

#define AUD_VOLUME_MEDIA \
     {132, 148, 148, 148, 128, 148, 120},\
     {88, 116, 144, 172, 200, 228, 255},\
     {124, 144, 164, 184, 204, 224, 255}

#define AUD_VOLUME_MATV \
     {0,43,85,128,171,213,255},\
     {88, 116, 144, 172, 200, 228, 255},\
     {124, 144, 164, 184, 204, 224, 255}

#endif
