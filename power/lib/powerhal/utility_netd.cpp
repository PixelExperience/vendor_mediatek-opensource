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

#define LOG_TAG "libPowerHal"

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/wireless.h>
#include <utils/Log.h>
#include <errno.h>
#include <cutils/properties.h>

#include "utility_netd.h"
#include "perfservice.h"

#include <vendor/mediatek/hardware/netdagent/1.0/INetdagent.h>

#define MAX_NETD_IP_FILTER_COUNT   (3)
#define MAX_NETD_IP_FILTER_LEN     (256)

using android::hardware::Return;
using android::hardware::hidl_string;
using vendor::mediatek::hardware::netdagent::V1_0::INetdagent;

static int nIpFilterCurIdx = 0;
static char **pIpFilterTbl = NULL;
static int lastFgBoostPid = -1;

/* NETD agent */
static int NetdAgentCmd( char *argv)
{
    hidl_string hidl_cmd;
    string temp_cmd;

    temp_cmd = argv;
    temp_cmd += " ";

    fprintf(stderr, "%s\n", temp_cmd.c_str());

    android::sp<INetdagent> gNetdagentService;
    //get Netdagent HIDL service
    gNetdagentService = INetdagent::tryGetService();
    if (gNetdagentService == nullptr) {
        ALOGE("get %s service failed\n", INetdagent::descriptor);
        return -1;
    }

    hidl_cmd = temp_cmd;
    Return<bool> ret = gNetdagentService->dispatchNetdagentCmd(hidl_cmd);
    if(!ret.isOk()) {
        ALOGE("dispatchNetdagentCmd is not ok\n");
        return -1;
    }

    if(ret == false) {
        ALOGE("dispatchNetdagentCmd failed\n");
        return -1;
    }
    return 0;
}

extern int netd_reset(int power_on_init)
{
    int ret = 0, i;
    char cmd[256];

    if(power_on_init != 1) {
        memset(cmd, 0, 256) ;
        sprintf(cmd,"netdagent firewall priority_clear_uid_all");
        if (NetdAgentCmd(cmd) <0) {
            ALOGE("clear uid fail \n") ;
            ret = -1;
        }

        memset(cmd, 0, 256) ;
        sprintf(cmd,"netdagent firewall priority_clear_toup_all");
        if (NetdAgentCmd(cmd) <0) {
            ALOGE("clear toup fail \n") ;
            ret = -1;
        }
    }

    /* netd ip filter table */
    if((pIpFilterTbl = (char**)malloc(sizeof(char*) * MAX_NETD_IP_FILTER_COUNT)) == NULL) {
        ALOGE("Can't allocate memory");
        return 0;
    }
    for (i=0; i < MAX_NETD_IP_FILTER_COUNT; i++) {
        if((pIpFilterTbl[i] = (char*)malloc(sizeof(char) * MAX_NETD_IP_FILTER_LEN)) == NULL) {
            ALOGE("Can't allocate memory");
            return 0;
        }
        strncpy(pIpFilterTbl[i], "NULL", MAX_NETD_IP_FILTER_LEN-1);
    }
    nIpFilterCurIdx = 0;
    return ret;
}

extern "C"
int netd_set_priority_uid(int uid, void *scn)
{
    char cmd[128];
    memset(cmd ,0,128) ;
    char value[PROPERTY_VALUE_MAX] = "\0";
    int prop_value = 1;

    property_get("persist.vendor.powerhal.PERF_RES_NET_NETD_BOOST_UID", value, "1");
    prop_value = atoi(value);
    ALOGD("persist.vendor.powerhal.PERF_RES_NET_NETD_BOOST_UID:%d", prop_value);

    ALOGV("netd_set_priority_uid: %p", scn);
    if(uid == 1) {
        getForegroundInfo(NULL, NULL, &uid);
        lastFgBoostPid = uid;
    }

    // return directly if prop is set to 0
    if (prop_value == 0)
        return 0;

    sprintf(cmd,"netdagent firewall priority_set_uid %d",uid);
    if (NetdAgentCmd(cmd) < 0) {
        ALOGE("SetPriorityWithUID fail\n") ;
        return -1 ;
    }
    ALOGI("Set packet Priority UID(%d)\n", uid);
    return 0;
}

extern "C"
int netd_clear_priority_uid(int uid, void *scn)
{
    char cmd[128];
    memset(cmd ,0,128) ;

    ALOGV("netd_clear_priority_uid: %p", scn);
    if(uid == 1 && lastFgBoostPid != -1) {
        uid = lastFgBoostPid;
        lastFgBoostPid = -1;
    }

    sprintf(cmd,"netdagent firewall priority_clear_uid %d" ,uid);
    if (NetdAgentCmd(cmd) < 0){
        ALOGE("ClearPriorityWithUID fail\n") ;
        return -1 ;
    }
    ALOGI("Clear packet Priority UID(%d)\n", uid) ;
    return 0;
}

static int SetDupPacketLink(const char *linkInfo)
{
    char cmd[256];
    memset(cmd, 0, 256) ;
    sprintf(cmd,"netdagent firewall priority_set_toup %s",linkInfo);

    if (NetdAgentCmd(cmd) < 0) {
        ALOGE("SetDupPacketLink fail \n") ;
        return -1 ;
    }
    ALOGD("SetDupPacketLink(%s)\n",linkInfo) ;

    return 0;
}

static int ClearDupPacketLink(const char *linkInfo)
{
    char cmd[256];
    memset(cmd, 0, 256) ;
    sprintf(cmd,"netdagent firewall priority_clear_toup %s",linkInfo);

    if (NetdAgentCmd(cmd) < 0) {
        ALOGE(" ClearDupPacketLink fail \n") ;
        return -1 ;
    }
    ALOGD("ClearDupPacketLink(%s)\n",linkInfo) ;

    return 0;
}

int deleteAllDupPackerLink(void)
{
    int i;

    for(i=0; i<MAX_NETD_IP_FILTER_COUNT; i++) {
        if(strcmp(pIpFilterTbl[i], "NULL") != 0) {
            if(ClearDupPacketLink(pIpFilterTbl[i]) < 0) {
                return -1;
            }
            strncpy(pIpFilterTbl[i], "NULL", MAX_NETD_IP_FILTER_LEN-1);
        }
    }
    nIpFilterCurIdx = 0;
    return 0;
}

int SetOnePacketLink(const char *linkInfo)
{
    if(strcmp(pIpFilterTbl[nIpFilterCurIdx], "NULL") != 0) {
        ClearDupPacketLink(pIpFilterTbl[nIpFilterCurIdx]);
    }

    if(SetDupPacketLink(linkInfo) < 0) {
        return -1;
    }

    strncpy(pIpFilterTbl[nIpFilterCurIdx], linkInfo, MAX_NETD_IP_FILTER_LEN-1);
    nIpFilterCurIdx = (nIpFilterCurIdx+1) % MAX_NETD_IP_FILTER_COUNT;
    return 0;
}

int SetDupPacketMultiLink(const char *linkInfo)
{
    char linkStr[256];
    char *str, *saveptr = NULL;
    int i, count = 0;

    /* always delete all first */
    if(deleteAllDupPackerLink() < 0)
        return -1;

    /* format: MULTI count IP_pair_1 IP_pair_2 IP_pair_3 */
    strncpy(linkStr, linkInfo, sizeof(linkStr)-1);
    str = strtok_r(linkStr, "\t", &saveptr); /* "MULTI"  */
    str = strtok_r(NULL, "\t", &saveptr);    /* count    */
    count = atoi(str);

    /* check count */
    if(count > MAX_NETD_IP_FILTER_COUNT)
        return -1;

    /* set all ip pair */
    for(i=0; i<count; i++) {
        str = strtok_r(NULL, "\t", &saveptr);
        if(SetDupPacketLink(str) < 0) {
            return -1;
        }
        strncpy(pIpFilterTbl[nIpFilterCurIdx], str, MAX_NETD_IP_FILTER_LEN-1);
        nIpFilterCurIdx = (nIpFilterCurIdx+1) % MAX_NETD_IP_FILTER_COUNT;
    }
    return 0;
}
