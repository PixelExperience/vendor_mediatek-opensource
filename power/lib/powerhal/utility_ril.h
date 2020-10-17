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

#ifndef _RIL_UTILITY_
#define _RIL_UTILITY_

#ifdef __cplusplus
extern "C" {
#endif

int socketConnect();
int socketDisconnect(int sock);
int sendData(int socket, int argCount, char** data);
int notify_rild_game_event(int gameMode, int lowLatencyMode);
int update_packet(const char * packet);
int notify_rild_opt_info(int lowLatencyMode, int period);
int reset_rild_opt_info(int power_on_init);
int notify_rild_opt_update(int lowLatencyMode, void *scn);
int notify_rild_app_status(int pid, int status);
int query_capability(int pid, const char* featureName);
int notify_rild_cert_pid_set(int pid, void *scn);
int notify_rild_cert_pid_reset(int pid, void *scn);
int notify_rild_crash_pid_set(int pid, void *scn);
int notify_rild_crash_pid_reset(int pid, void *scn);
int notify_rild_weak_sig_opt_set(int enable, void *scn);

#ifdef __cplusplus
}
#endif

#endif  /* _RIL_UTILITY_ */
