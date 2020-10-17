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

#ifndef ANDROID_PERFSERVICE_H
#define ANDROID_PERFSERVICE_H

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cutils/compiler.h>
#include <utils/threads.h>
#include "perfservice_types.h"

using namespace android;
using namespace std;

#define CFG_TBL_INVALID_VALUE (-123456)

enum {
    SETSYS_MANAGEMENT_PREDICT  = 1,
    SETSYS_SPORTS_APK          = 2,
    SETSYS_FOREGROUND_SPORTS   = 3,
    SETSYS_MANAGEMENT_PERIODIC = 4,
    SETSYS_INTERNET_STATUS     = 5,
    SETSYS_NETD_STATUS         = 6,
    SETSYS_PREDICT_INFO        = 7,
    SETSYS_NETD_DUPLICATE_PACKET_LINK = 8,
};

enum {
    INDEX_SYSTEM_APK     = 0,
    INDEX_USER_SPECIFIED = 1,
    INDEX_GAME_MODE      = 2,
    INDEX_ARM_NATIVE_LIB = 3,
    INDEX_HPS            = 4,
    INDEX_VCORE          = 5,
    INDEX_TLP            = 6,
    INDEX_NUM            = 7,
    // others
    INDEX_APP_RUNNING = 8,
    INDEX_NATIVE_RUNNING = 9,
};

enum {
    APK_BENCHMARK     = 0,
    APK_GAME          = 1,
    APK_NOT_BENCHMARK = 2,
    APK_OTHERS        = 3,
};

struct xml_activity {
    char cmd[128];
    char actName[128];
    char packName[128];
    int param1;
    int param2;
    int param3;
    int param4;
};

struct xml_gift {
    char packName[128];
    char **AttrName;
    char **AttrValue;
};

typedef struct tScnConTable {
    string  cmdName;
    int     cmdID;
    int     legacyCmdID;
    string  entry;
    int     defaultVal;
    int     curVal;
    string  comp;
    int     maxVal;
    int     minVal;
    int     resetVal; // value to reset this entry
    int     isValid;
    int     normalVal;
    int     sportVal;
    int     ignore;
    string  prefix;
} tScnConTable;

enum {
    ONESHOT       = 0,
    BIGGEST       = 1,
    SMALLEST      = 2,
};

typedef int (*rsc_set)(int, void*);
typedef int (*rsc_unset)(int, void*);
typedef int (*rsc_init)(int);

typedef struct tRscConfig {
    int     cmdID; // -1 : final entry
    string  cmdName;
    int     comp;
    int     maxVal;
    int     minVal;
    int     defaultVal;
    int     normalVal;
    int     sportVal;
    int     force_update; // always trigger update lock
    rsc_set   set_func;
    rsc_unset unset_func;
    rsc_init  init_func;
} tRscConfig;

typedef struct tRscCtlEntry {
    int     curVal;
    int     log;
    int     isValid;
    int     resetVal; // value to reset this entry
} tRscCtlEntry;

void switchNormalAndSportMode(int mode);
int cmdSetting(int icmd, char *scmd, tScnNode *scenario, int param_1);
void Scn_cmdSetting(char *cmd, int scn, int param_1);
int getForegroundInfo(char **pPackName, int *pPid, int *pUid);

/* smart detect */
int smart_init(void);
int smart_table_init(void);
int smart_table_init_flag(void);
int smart_reset(const char *pack, int pid);
int smart_check_pack_existed(int type, const char *pack, int uid, int fromUid);
int smart_set_benchmark_mode(int benchmark);
int smart_add_pack(const char *pack);
int smart_add_benchmark(void);
int smart_add_specific_benchmark(const char *pack);
int smart_add_game(void);

int loadConTable(const char *file_name);
#endif // ANDROID_PERFSERVICE_H
