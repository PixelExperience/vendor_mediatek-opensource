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

#ifndef _UTILITY_NETD_H
#define _UTILITY_NETD_H

#ifdef __cplusplus
extern "C" {
#endif

extern int netd_set_priority_uid(int uid, void *scn);
extern int netd_clear_priority_uid(int uid, void *scn);
extern int netd_reset(int power_on_init);
extern int deleteAllDupPackerLink(void);
extern int SetOnePacketLink(const char *linkInfo);
extern int SetDupPacketMultiLink(const char *linkInfo);

#ifdef __cplusplus
}
#endif

#endif // _UTILITY_NETD_H
