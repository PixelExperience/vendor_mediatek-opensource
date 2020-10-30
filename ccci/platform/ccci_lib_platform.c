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

/*****************************************************************************
 *
 * Filename:
 * ---------
 *   ccci_lib.c
 *
 * Project:
 * --------
 *
 *
 * Description:
 * ------------
 *
 *
 * Author:
 * -------
 *
 *
 ****************************************************************************/

#include <stdio.h>
#include <string.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <fcntl.h>
//#include <unistd.h>
#include <cutils/properties.h>
//#include <android/log.h>
//#include <sys/ioctl.h>
//#include <errno.h>
#include <stdlib.h>
//#include <sys/mman.h>
//#include <stdint.h>
//#include <pthread.h>
//#include "hardware/ccci_intf.h"
#include "ccci_lib_platform.h"


#define AB_PROPERTY_NAME        "ro.boot.slot_suffix"

void AB_image_get(char *buf)
{
    if (property_get(AB_PROPERTY_NAME, buf, NULL) == 0)
        buf[0] = 0;
}

int query_prj_cfg_setting_platform(char name[], char val[], int size)
{
    char prop_value[PROPERTY_VALUE_MAX] = {0};

    //-- For MTK_ECCCI_C2K
    #ifdef MTK_ECCCI_C2K
    if(strcmp(name, "MTK_ECCCI_C2K")==0) {
        snprintf(val, size, "1");
        return 0;
    }
    #endif

    #ifdef MD_SBP_CUSTOM_VALUE
    if(strcmp(name, "MTK_MD_SBP_CUSTOM_VALUE")==0) {
        snprintf(val, size, "%d", MD_SBP_CUSTOM_VALUE);
        return 0;
    }
    #endif

    #ifdef MD2_SBP_CUSTOM_VALUE
    if(strcmp(name, "MTK_MD2_SBP_CUSTOM_VALUE")==0) {
        snprintf(val, size, "%d", MD2_SBP_CUSTOM_VALUE);
        return 0;
    }
    #endif

    return -1;
}

