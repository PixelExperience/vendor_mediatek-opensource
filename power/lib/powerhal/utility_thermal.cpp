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
#include <sys/resource.h>
#include <sys/stat.h>
#include <dirent.h>
#include <ctype.h>
#include <cutils/properties.h>
#include <utils/Log.h>
#include <utils/RefBase.h>
#include <dlfcn.h>
#include <string.h>

#include "utility_thermal.h"

using namespace std;

#define MAX_POLICY      (23) /* 3 for PowerHAL and 20 for specific scenarios. */
#if defined (__LP64__) ||  defined (_LP64)
#define THM_LIB_FULL_NAME  "/vendor/lib64/libmtcloader.so"
#else
#define THM_LIB_FULL_NAME  "/vendor/lib/libmtcloader.so"
#endif

static int load_thm_api(int idx, bool start);

thermal_conf_type g_perf_tc[MAX_POLICY] = {
    [0] = {.conf_name = "thermal_sp",.perf_used = 0},
    [1] = {.conf_name = "thermal_vr",.perf_used = 0},
    [2] = {.conf_name = "thermal_vrsp",.perf_used = 0},
    [3] = {.conf_name = "thermal_policy_00",.perf_used = 0},
    [4] = {.conf_name = "thermal_policy_01",.perf_used = 0},
    [5] = {.conf_name = "thermal_policy_02",.perf_used = 0},
    [6] = {.conf_name = "thermal_policy_03",.perf_used = 0},
    [7] = {.conf_name = "thermal_policy_04",.perf_used = 0},
    [8] = {.conf_name = "thermal_policy_05",.perf_used = 0},
    [9] = {.conf_name = "thermal_policy_06",.perf_used = 0},
    [10] = {.conf_name = "thermal_policy_07",.perf_used = 0},
    [11] = {.conf_name = "thermal_policy_08",.perf_used = 0},
    [12] = {.conf_name = "thermal_policy_09",.perf_used = 0},
    [13] = {.conf_name = "thermal_policy_10",.perf_used = 0},
    [14] = {.conf_name = "thermal_policy_11",.perf_used = 0},
    [15] = {.conf_name = "thermal_policy_12",.perf_used = 0},
    [16] = {.conf_name = "thermal_policy_13",.perf_used = 0},
    [17] = {.conf_name = "thermal_policy_14",.perf_used = 0},
    [18] = {.conf_name = "thermal_policy_15",.perf_used = 0},
    [19] = {.conf_name = "thermal_policy_16",.perf_used = 0},
    [20] = {.conf_name = "thermal_policy_17",.perf_used = 0},
    [21] = {.conf_name = "thermal_policy_18",.perf_used = 0},
    [22] = {.conf_name = "thermal_policy_19",.perf_used = 0}
};

static thermal_policy_manager_type g_tpm;
static int thm_get_next_conf(char *conf_name, int enable)
{
    int i, found = 0;
    int ret = TS_ERR_NO_LOAD;

    if (strnlen(conf_name, MAX_CONF_NAME + 1) > MAX_CONF_NAME)
        return TS_ERR_NO_FILE_EXIST;



    if (enable) { /* enable policy */
    for (i = 0; i < MAX_POLICY; i++) {
            if (!strcmp(conf_name, g_perf_tc[i].conf_name)) {
                ALOGI("[Perfsevice]thm_get_next_conf enable %s.\n", g_perf_tc[i].conf_name);
                g_perf_tc[i].perf_used++;
                g_tpm.policy_count++;
                if (i > g_tpm.policy_active || ((g_tpm.policy_active == i) && (i == 0))) {
                    g_tpm.policy_active = i;
                    ret = i;
                    return ret;
                }
            }
        }
    } else { /* disable policy */
        for (i = 0; i < MAX_POLICY; i++) {
            if (!strcmp(conf_name, g_perf_tc[i].conf_name)) {
                    if (g_perf_tc[i].perf_used > 0) {
                        g_perf_tc[i].perf_used--;
                    if (g_tpm.policy_count > 0)
                        g_tpm.policy_count--;

                    ALOGI("[Perfsevice]thm_get_next_conf disable %s.\n", g_perf_tc[i].conf_name);
                }
                found = 1;
                break;
            }
        }
        if (found) {
            if (0 == g_tpm.policy_count)
                g_tpm.policy_active = -1;

            for (i = MAX_POLICY-1; i >= 0; i--) {
                if (g_perf_tc[i].perf_used > 0) {
                    ret = i;
                    g_tpm.policy_active = i;
                    break;
                }
            }
        } else {
            return ret;
        }
    }

    return ret;
}

static int thm_load_thm_data(void)
{
    int ret = -1;
    char value[PROPERTY_VALUE_MAX];

    ret = property_get("vendor.thermal.manager.data.perf", value, "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0");
    sscanf(value,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
        &g_perf_tc[0].perf_used, &g_perf_tc[1].perf_used, &g_perf_tc[2].perf_used, &g_perf_tc[3].perf_used, &g_perf_tc[4].perf_used,
        &g_perf_tc[5].perf_used, &g_perf_tc[6].perf_used, &g_perf_tc[7].perf_used, &g_perf_tc[8].perf_used, &g_perf_tc[9].perf_used,
        &g_perf_tc[10].perf_used, &g_perf_tc[11].perf_used, &g_perf_tc[12].perf_used, &g_perf_tc[13].perf_used,&g_perf_tc[14].perf_used,
        &g_perf_tc[15].perf_used, &g_perf_tc[16].perf_used, &g_perf_tc[17].perf_used, &g_perf_tc[18].perf_used,&g_perf_tc[19].perf_used,
        &g_perf_tc[20].perf_used, &g_perf_tc[21].perf_used, &g_perf_tc[22].perf_used);

    ALOGI("[Perfsevice]thm_load_thm_data : %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
        g_perf_tc[0].perf_used, g_perf_tc[1].perf_used, g_perf_tc[2].perf_used, g_perf_tc[3].perf_used, g_perf_tc[4].perf_used,
        g_perf_tc[5].perf_used, g_perf_tc[6].perf_used, g_perf_tc[7].perf_used, g_perf_tc[8].perf_used, g_perf_tc[9].perf_used,
        g_perf_tc[10].perf_used, g_perf_tc[11].perf_used, g_perf_tc[12].perf_used, g_perf_tc[13].perf_used, g_perf_tc[14].perf_used,
        g_perf_tc[15].perf_used, g_perf_tc[16].perf_used, g_perf_tc[17].perf_used, g_perf_tc[18].perf_used, g_perf_tc[19].perf_used,
        g_perf_tc[20].perf_used, g_perf_tc[21].perf_used, g_perf_tc[22].perf_used);

    return ret;

}

static int thm_store_thm_data(void)
{
    int ret = -1;
    char value[PROPERTY_VALUE_MAX];

    ALOGI("[Perfsevice]thm_store_thm_data : %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
        g_perf_tc[0].perf_used, g_perf_tc[1].perf_used, g_perf_tc[2].perf_used, g_perf_tc[3].perf_used, g_perf_tc[4].perf_used,
        g_perf_tc[5].perf_used, g_perf_tc[6].perf_used, g_perf_tc[7].perf_used, g_perf_tc[8].perf_used, g_perf_tc[9].perf_used,
        g_perf_tc[10].perf_used, g_perf_tc[11].perf_used, g_perf_tc[12].perf_used, g_perf_tc[13].perf_used, g_perf_tc[14].perf_used,
        g_perf_tc[15].perf_used, g_perf_tc[16].perf_used, g_perf_tc[17].perf_used, g_perf_tc[18].perf_used, g_perf_tc[19].perf_used,
        g_perf_tc[20].perf_used, g_perf_tc[21].perf_used, g_perf_tc[22].perf_used);

    sprintf(value,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
        g_perf_tc[0].perf_used, g_perf_tc[1].perf_used, g_perf_tc[2].perf_used, g_perf_tc[3].perf_used, g_perf_tc[4].perf_used,
        g_perf_tc[5].perf_used, g_perf_tc[6].perf_used, g_perf_tc[7].perf_used, g_perf_tc[8].perf_used, g_perf_tc[9].perf_used,
        g_perf_tc[10].perf_used, g_perf_tc[11].perf_used, g_perf_tc[12].perf_used, g_perf_tc[13].perf_used, g_perf_tc[14].perf_used,
        g_perf_tc[15].perf_used, g_perf_tc[16].perf_used, g_perf_tc[17].perf_used, g_perf_tc[18].perf_used, g_perf_tc[19].perf_used,
        g_perf_tc[20].perf_used, g_perf_tc[21].perf_used, g_perf_tc[22].perf_used);

    ret = property_set("vendor.thermal.manager.data.perf", value);


    return ret;
}

int load_thm_api_start(int idx, void *scn)
{
    ALOGV("load_thm_api_start: %p", scn);
    return load_thm_api(idx, 1);
}

int load_thm_api_stop(int idx, void *scn)
{
    ALOGV("load_thm_api_stop: %p", scn);
    return load_thm_api(idx, 0);
}

static int load_thm_api(int idx, bool start)
{
    void *handle, *func;
    char conf_name[MAX_CONF_NAME] = {0};
    int ret = 0;
    int next_index = -2; /* -1 is unnecessary to load conf */


    ALOGI("[Perfsevice]load_thm_api idx:%d, start:%d", idx, start);

    /*sp mode can use idx: 97,98,99*/

    /*max policy idx = 19*/
    if ((idx > (MAX_POLICY - 4)) || (idx < 0)) {
        ALOGE("[Perfsevice]load_thm_api idx out of range: %d", idx);
        return -1;
    }


    handle = dlopen(THM_LIB_FULL_NAME, RTLD_NOW);

    if (handle == NULL) {
        ALOGE("[Perfsevice]Can't load library: %s", dlerror());
        return -1;
    }

    func = dlsym(handle, "change_policy");
    if(func == NULL) {
        ALOGE("[Perfsevice]load_thm_api dlsym fail:%s", dlerror());
        dlclose(handle);
        return -1;
    }


    typedef int (*load_change_policy)(char *, int);

    load_change_policy change_policy =
        reinterpret_cast<load_change_policy>(func);
    if (change_policy == NULL) {
        ALOGE("[Perfsevice]load_thm_api change_policy err: %s.\n", dlerror());
        dlclose(handle);
        return -1;
    }


    snprintf(conf_name, sizeof(conf_name), "thermal_policy_%02d\n", idx);


    ret = change_policy(conf_name, start);
    if(ret < 0) {/*change poilcy fail*/
        ALOGE("[Perfsevice]change_policy err: %d, %s\n", ret, conf_name);
        dlclose(handle);
        return -1;
    }

    /*record thermal policies from perf service*/
    ret = thm_load_thm_data();
    if (ret < 0) {
        ALOGE("[Perfsevice]thm_load_thm_data err: %d.\n", ret);
        dlclose(handle);
        return ret;
    }

    next_index = thm_get_next_conf(conf_name, start);

    ret = thm_store_thm_data();
    if (ret < 0) {
        ALOGE("[Perfsevice]thm_store_thm_data err: %d.\n", ret);
        dlclose(handle);
        return ret;
    }

    dlclose(handle);
    return 0;
}

int reset_thermal_policy(int power_on_init)
{
    void *handle, *func;
    int ret = 0;

    ALOGI("reset_thermal_policy");

    if(power_on_init == 1) {
        ALOGI("reset_thermal_policy skip");
        return 0;
    }

    handle = dlopen(THM_LIB_FULL_NAME, RTLD_NOW);

    ALOGI("[Perfsevice]reset_thermal_policy");

    if (handle == NULL) {
        ALOGE("[Perfsevice]Can't load library: %s", dlerror());
        return -1;
    }

    /*reset thermal policy counter*/
    func = dlsym(handle, "reset_propertydata");
    if(func == NULL) {
        ALOGE("[Perfsevice]reset_thermal_policy dlsym: reset_propertydata fail:%s",
        dlerror());
        dlclose(handle);
        return -1;
    }

    typedef int (*reset_thermal_policy)(void);

    reset_thermal_policy reset_propertydata =
        reinterpret_cast<reset_thermal_policy>(func);
    if (reset_propertydata == NULL) {
        ALOGE("[Perfsevice]reset_thermal_policy reset_propertydata err: %s.\n",
        dlerror());
        dlclose(handle);
        return -1;
    }

    ret = reset_propertydata();
    if(ret < 0) {
        ALOGE("[Perfsevice]reset_propertydata ret: %d\n", ret);
        dlclose(handle);
        return -1;
    }
    /*reset thermal policy counter*/

   dlclose(handle);
   return 0;

}
