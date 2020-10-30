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

#ifndef AUDIO_TASK_H
#define AUDIO_TASK_H

#include <stdint.h>

enum {
    /* scene for library */
    TASK_SCENE_PHONE_CALL           = 0,
    TASK_SCENE_VOICE_ULTRASOUND     = 1,
    TASK_SCENE_PLAYBACK_MP3         = 2,
    TASK_SCENE_RECORD               = 3,
    TASK_SCENE_VOIP                 = 4,
    TASK_SCENE_SPEAKER_PROTECTION   = 5,
    TASK_SCENE_VOW                  = 6,
    TASK_SCENE_PRIMARY              = 7,
    TASK_SCENE_DEEPBUFFER           = 8,
    TASK_SCENE_AUDPLAYBACK          = 9,
    TASK_SCENE_CAPTURE_UL1          = 10,
    TASK_SCENE_A2DP                 = 11,
    TASK_SCENE_DATAPROVIDER         = 12,
    TASK_SCENE_CALL_FINAL           = 13,
    TASK_SCENE_KTV                  = 14,

    /* control for driver */
    TASK_SCENE_AUD_DAEMON,
    TASK_SCENE_AUDIO_CONTROLLER_HIFI3_A,
    TASK_SCENE_AUDIO_CONTROLLER_HIFI3_B,
    TASK_SCENE_AUDIO_CONTROLLER_CM4,
    TASK_SCENE_SIZE,
    TASK_SCENE_INVALID
};


enum {
    TASK_SCENE_OFFLOAD_MP3,
    TASK_SCENE_OFFLOAD_AAC
};

typedef uint8_t task_offload_scene_t;

#endif /* end of AUDIO_TASK_H */

