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

#include "utility_consys.h"
#include "perfservice.h"

using namespace std;

/* data type */
#define WIFI_EVENT_GAS           (1 << 4)
#define WIFI_EVENT_NETWORK       (1 << 11)
#define WIFI_EVENT_SMART_PREDICT (1 << 13)

#define WIFI_IF_NAME            "wlan0"
#define PRIV_CMD_OID            15
#define SIOCIWFIRSTPRIV         0x8BE0
#define IOCTL_SET_STRUCT        (SIOCIWFIRSTPRIV + 8)
#define OID_CUSTOM_GAMING_MODE  0xFFA0CC00

#define WIFI_POWER_PATH "/dev/wmtWifi"

typedef struct _NDIS_TRANSPORT_STRUCT {
    uint32_t    ndisOidCmd;
    uint32_t    inNdisOidlength;
    uint32_t    outNdisOidLength;
    uint32_t    ndisOidContent[4];
} NDIS_TRANSPORT_STRUCT, *P_NDIS_TRANSPORT_STRUCT;

/* function */

static int ioctl_iw_ext(int skfd, int request, struct iwreq *pwrq)
{
    if(skfd > 0) {
        /* Set device name */
        strncpy(pwrq->ifr_name, WIFI_IF_NAME, (IFNAMSIZ - 1));
        /* Do the request */
        return(ioctl(skfd, request, pwrq));
    }
    else {
        return -1;
    }
}

/* WIFI low latency */
static int wifi_sent_event(int set, uint32_t events)
{
    int retval = 0;
    int devfd = -1, sz = 0, devret = 0;
    char str[64];
    int skfd = -1;
    struct iwreq wrq;
    NDIS_TRANSPORT_STRUCT rNdisStruct;
    static uint32_t wifiDrvSettig = 0;

    if(set == 1) {
        wifiDrvSettig |= events;
    } else if(set == 0) {
        wifiDrvSettig &= (~events);
    } else if(set == -1) {
        wifiDrvSettig = 0; // reset all events
    } else {
        ALOGE("wifi_sent_event: unknown set cmd:%d", set);
        return -1;
    }

    ALOGI("wifi_sent_event: set:%d, events:%x, setting:%x", set, events, wifiDrvSettig);

    /* write WIFI_POWER_PATH */
    devfd = open(WIFI_POWER_PATH, O_WRONLY);
    if (devfd < 0) {
        ALOGE("Open %s failed. %s(%d)", WIFI_POWER_PATH, strerror(errno), errno);
        devret = -1;
    } else {
        snprintf(str, sizeof(str)-1, "LLM 0x%x", wifiDrvSettig);
        sz = write(devfd, &str, strlen(str));
        if (sz < 0) {
            ALOGE("Write %s failed. %s(%d)", WIFI_POWER_PATH, strerror(errno), errno);
            devret = -1;
        }
        close(devfd);
    }

    /* set wifi driver */
    if ((skfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
        char *err_str = strerror(errno);
        ALOGI("wifi_sent_event socket error : %d, %s\n", errno, err_str);
        return -1;
    }

    /* zeroize */
    memset(&wrq, 0, sizeof(struct iwreq));

    rNdisStruct.ndisOidContent[0] = wifiDrvSettig;
    rNdisStruct.ndisOidCmd = OID_CUSTOM_GAMING_MODE;
    rNdisStruct.inNdisOidlength = sizeof(int);
    rNdisStruct.outNdisOidLength = 0;

    wrq.u.data.pointer = &rNdisStruct;
    wrq.u.data.length = sizeof(NDIS_TRANSPORT_STRUCT);
    wrq.u.data.flags = PRIV_CMD_OID;

    retval = ioctl_iw_ext(skfd, IOCTL_SET_STRUCT, &wrq);
    if(retval < 0) {
        char *err_str = strerror(errno);
        ALOGI("wifi_sent_event ioctl_iw_ext error : %d, %s\n", errno, err_str);
    }

    close(skfd);
    return (retval < 0 || devret < 0) ? -1 : 0;
}

int wifi_reset(int power_on_init)
{
    if(power_on_init == 1) // powerhal first init
        return 0;

    wifi_sent_event(-1, 0);
    return 0;
}

/* Public API */
int wifi_low_latency(int enable, void *scn)
{
    static int last_status = 0;
    int events = (WIFI_EVENT_GAS | WIFI_EVENT_NETWORK);
    int ret = 0;

    ALOGV("wifi_low_latency: %p", scn);
    ALOGI("wifi_low_latency: last:%d, enable:%d", last_status, enable);

    if (last_status != enable) {
        if(enable)
            ret = wifi_sent_event(1, events);
        else
            ret = wifi_sent_event(0, events);

        if(ret < 0)
            ALOGI("wifi_low_latency: wifi_sent_event err");

        last_status = enable;
    }

    return 0;
}

/* Public API */
int wifi_smart_predict(int enable, void *scn)
{
    static int last_status = 0;
    int events = WIFI_EVENT_SMART_PREDICT;
    int ret = 0;

    ALOGV("wifi_smart_predict: %p", scn);
    ALOGI("wifi_smart_predict: last:%d, enable:%d", last_status, enable);

    if (last_status != enable) {
        if(enable)
            ret = wifi_sent_event(1, events);
        else
            ret = wifi_sent_event(0, events);

        if(ret < 0)
            ALOGI("wifi_predict: wifi_sent_event err");

        last_status = enable;
    }
    return 0;
}
