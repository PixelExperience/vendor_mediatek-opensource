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

#ifndef __rtt_h
#define __rtt_h

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <unwind.h>

#ifdef __cplusplus
extern "C" {
#endif

// RTT Exported Functions
extern int rtt_is_ready(int block);
extern int rtt_dump_backtrace(pid_t pid, pid_t tid, const char* file_path,int fd);
extern int rtt_dump_all_backtrace(pid_t pid, const char* file_path,int fd);
extern int rtt_dump_all_backtrace_by_name(const char *ps_name, const char *file_path,int fd);
extern int rtt_dump_process_name_to_pid(const char *proc_name);
extern int rtt_dump_all_backtrace_JBT_by_name(const char *ps_name, const char *file_path,int fd);



/*
 * Get the caller backtrace
 *   max_cnt: call stack frames maximum count
 *   paddrs : arrays to save the frame address
 * Return
 *   total stack frame count could unwinded by the interface
 */
extern unsigned rtt_get_caller_backtrace(unsigned max_cnt, intptr_t* paddrs);

/*
 * Print the caller backtrace
 *   tag: use the logcat tag to dump the result
 */
extern void rtt_dump_caller_backtrace(const char* tag);

extern int rtt_is_java_process(pid_t pid);

/*
 * Get the system average load
 *   min_1  : last 1 minutes system average load
 *   min_5  : last 5 minutes system average load
 *   min_15 : last 15 minutes system average load
 * Return
 *   0: success
 *   fail otherwise
 */
extern int rtt_get_loadavg(double* min_1, double* min_5, double* min_15);

/*
 * Get the system uptime from booting to now
 * Return
 *   seconds from boot time to now
 */
extern double rtt_get_uptime();

/*
 * Get the system time. Include RTC and uptime
 *   to_screen : whether dump to Android log (0: disable)
 *   uptime    : whether to get the up time (0: disable)
 *   out       : whether write the result to the buffer (NULL: disable)
 *   len       : lenght of the out buffer
 * Return
 *   0: success
 *   fail otherwise
 */
extern int rtt_get_system_time(int to_screen, int uptime, char* out,
    unsigned int len);

#ifdef __cplusplus
}
#endif

#endif
