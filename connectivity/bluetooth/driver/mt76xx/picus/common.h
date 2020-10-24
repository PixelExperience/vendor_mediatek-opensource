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

#ifndef _COMMON_H_
#define _COMMON_H_

/* --------------------------------------------------------------------------- */
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <endian.h>
#include <sys/stat.h>

/* --------------------------------------------------------------------------- */
#ifndef UNUSED
#define UNUSED(x) (void)(x)
#endif

/* --------------------------------------------------------------------------- */
/* This device node only for read firmware log */
#define CUST_BT_FWLOG_PORT  "/dev/stpbtfwlog"
/* Picus log default PATH is /data/misc/bluedroid/dump_0.picus */
/* FW dump default PATH is /data/misc/bluedroid/fw_dump.picus */
#define DEFAULT_PATH "/data/misc/bluedroid"
#define DUMP_PICUS_NAME_PREFIX "dump_"
#define DUMP_PICUS_NAME_EXT ".picus"
#define FW_DUMP_PICUS_NAME "fw_dump"


#define RETRY_COUNT         20
#define FW_LOG_SWITCH_SIZE  20 * 1024 * 1024
#define MT_TIMEOUT_VALUE    1000
#define IOC_MAGIC           0xb0
#define PICUS_EVENT_LEN     3
#define PICUS_ACL_LEN       4

/* add get chip id(ex:7668...) */
#define IOCTL_GET_CHIP_ID                           _IOWR('H', 1, int)
/* add for BT Tool, change ALTERNATE_SETTING for SCO */
#define IOCTL_CHANGE_ALTERNATE_SETTING_INTERFACE    _IOWR(IOC_MAGIC, 2, unsigned long)

#define HCE_CONNECTION_COMPLETE         0x03
#define HCE_COMMAND_COMPLETE            0x0E

/* --------------------------------------------------------------------------- */
typedef enum _MT_DEBUG_LEVEL
{
    MT_DEBUG_SHOW,      // debug off, priority highest
    MT_DEBUG_ERROR,     // only show eror
    MT_DEBUG_WARN,
    MT_DEBUG_TRACE,
    MT_DEBUG_DEEPTRACE,
    MT_DEBUG_HCITRACE,
} MT_DEBUG_LEVEL;

typedef enum _MT_API_RESULT
{
    MT_RESULT_FAIL = -1,
    MT_RESULT_SUCCESS,
} MMT_API_RESULT;

typedef enum {
    DATA_TYPE_COMMAND = 1,
    DATA_TYPE_ACL     = 2,
    DATA_TYPE_SCO     = 3,
    DATA_TYPE_EVENT   = 4
} serial_data_type_t;

/* --------------------------------------------------------------------------- */
void DBGPRINT(int level, const char *format, ...);

#endif /* _COMMON_H_ */
