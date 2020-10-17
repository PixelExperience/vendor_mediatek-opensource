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

#ifndef _UX_UTILITY_
#define _UX_UTILITY_

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * Typedef
 *****************************************************************************/

typedef int (*power_notify_ux_game_event)(int, int);
typedef int (*power_notify_AppState)(const char*, const char*, uint32_t);

typedef enum {
    GAME_EVENT_LOW_LATENCY = 0,
    GAME_EVENT_IDLE,
} UxGameState;

typedef enum {
    GAME_MODE_NO_UPDATE = -1,
    GAME_MODE_NONE = 0,
    GAME_MODE_LOADING,
    GAME_MODE_IN_MATCH,
    GAME_MODE_IDLE,
    GAME_MODE_BATTLE,
    GAME_MODE_BOOST,
} SdkGameMode;

typedef enum {
    CMD_AGGRESSIVE_MODE = 0,
    CMD_PREDICT_MODE,
} CmdMode;

void notifyCmdMode(int mode); //predict or fix
void notify_APPState(const char *packname, int32_t uid);
void notifyForegroundApp(const char *packname, int32_t uid);
int notifyLowLatencyMode(int LowLatencyMode, void *scn);
int resetUtilityUx(int power_on_init);

#ifdef __cplusplus
}
#endif

#endif  /* _UX_UTILITY_ */
