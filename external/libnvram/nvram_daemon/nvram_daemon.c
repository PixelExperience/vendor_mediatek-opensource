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

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <cutils/properties.h>
#include "libnvram.h"
#include "libnvram_log.h"
#include "nvram_battery.h"
#include "nvram_bt.h"
#include "nvram_wifi.h"
//#include "nvram_touchpanel.h"
#include "nvram_acc.h"
#include "nvram_gyro.h"
#include "nvram_ps.h"
#include "nvram_productinfo.h"
#include "libfile_op.h"
enum NVRAM_USER {
	NU_BATTERY,
	NU_WIFI,
	NU_BT,
	NU_FM,
	//NU_TOUCHPANEL,
	NU_HWMON,
	NU_HWMON_PS,
	NU_PRODUCT_INFO,
	NU_MAX
};

typedef struct _NVRAM_USER_DATA {
	const char*	pcName;
	pthread_t	kThread;
	void* (*start_routine)(void*);
} NVRAM_USER_DATA;

static NVRAM_USER_DATA g_akNUData[NU_MAX] = {
	{"Battery", 0, NVRAM_BATTERY},
	{"Bluetooth", 0, NVRAM_BT},
	{"WIFI", 0, NVRAM_WIFI},
	//{"Touchpanel", 0, NVRAM_TOUCHPANEL},
#ifndef MTK_BASIC_PACKAGE
	{"HWMON_ACC", 0, NVRAM_ACC},
	{"HWMON_GYRO", 0, NVRAM_GYRO},
	{"HWMON_PS", 0, NVRAM_PS},
#endif
	{"PROUDCT_INFO", 0, NVRAM_PRODUCTINFO},
	{"None", 0, NULL}
};
extern int iCustomBeginLID;
extern pfCallbackForDaemon callback_for_nvram_daemon;

bool Init_AllThreads_In_Nvram(void) {
	int i, ret;
	void* thread_result;
	for (i = 0; i < NU_MAX; ++i) {
		if (g_akNUData[i].start_routine) {
			ret = pthread_create(&g_akNUData[i].kThread, NULL, g_akNUData[i].start_routine,
			                     NULL);
			if (ret != 0) {
				//NVRAM_LOG("%s Thread creation failed\n", g_akNUData[i].pcName);
				return false;
			}
		}
	}
	//NVRAM_LOG("Finish thread create\n");

	for (i = NU_MAX - 1; i >= 0 ; --i) {
		if (g_akNUData[i].start_routine) {
			ret = pthread_join(g_akNUData[i].kThread, &thread_result);
			if (ret != 0) {
				//NVRAM_LOG("%s Thread join failed\n", g_akNUData[i].pcName);
				return false;
			}
		}
	}
	//NVRAM_LOG("Finish thread joint\n");
	return true;
}
bool Init_Productinfo_In_Nvram(void) {
	int i, ret;
	void* thread_result;
	for (i = 0; i < NU_MAX; ++i) {
		if (strcmp(g_akNUData[i].pcName, "PROUDCT_INFO") == 0) {
			if (g_akNUData[i].start_routine) {
				ret = pthread_create(&g_akNUData[i].kThread, NULL, g_akNUData[i].start_routine,
				                     NULL);
				if (ret != 0) {
					//NVRAM_LOG("%s Thread creation failed\n", g_akNUData[i].pcName);
					return false;
				}
			}
			if (g_akNUData[i].start_routine) {
				ret = pthread_join(g_akNUData[i].kThread, &thread_result);
				if (ret != 0) {
					//NVRAM_LOG("%s Thread join failed\n", g_akNUData[i].pcName);
					return false;
				}
			}
			return true;
		}
	}
	NVRAM_LOG("PROUDCT_INFO thread is not in init list\n");
	return false;
}

int main(void) {
	int iMaxLidNum = 0;
	int ret_callback = -1;
	char nvram_init_value[100] = {0};

	iMaxLidNum = NVM_Init();
	NVRAM_LOG("Total nvram Lid number is %d\n", iMaxLidNum);
	umask(000);
	if (iMaxLidNum <= 0) {
		NVRAM_LOG("Total nvram Lid number is error !!!\n");
		exit(EXIT_FAILURE);
	}

	if (nvram_emmc_support() || nvram_ufs_support()) {
		if (!Check_UpdateStatus()) {
			NVRAM_LOG("fail to check upgrade status in first boot\n");
		}
	}
#ifdef MTK_NVRAM_AUTO_BACKUP
	if (!FileOp_CmpBackupFileNum()) {
		FileOp_BackupToBinRegion_All();
		FileOp_SetCleanBootFlag(true);
	} else {
#endif
		if (!FileOp_RecoveryData())
			//if(!FileOp_RestoreFromBinRegionForDM())
		{
			NVRAM_LOG("Bin Region Restore to NvRam Fail\n");
			//exit(EXIT_FAILURE);
		}
#ifdef MTK_NVRAM_AUTO_BACKUP
	}
#endif

	if (!Check_FileVerinFirstBoot()) {
		NVRAM_LOG("Check FILE_VER in first boot, and fail to generate FILE_VER\n");
	}

	//Add for product info feature
	if (nvram_new_partition_support()) {
		NVRAM_LOG("Begin excute customer callback!!!\n");
		init_callback();
		if (callback_for_nvram_daemon != NULL)
			ret_callback = callback_for_nvram_daemon();
		NVRAM_LOG("Callback return %d\n", ret_callback);
	}
	//end for product info feature

	property_get("vendor.service.nvram_init", &nvram_init_value[0], "");

	if (0 == property_set("vendor.service.nvram_init", "Ready")) {
		NVRAM_LOG("Set Ready property success\n");
		if (!Init_AllThreads_In_Nvram())
			NVRAM_LOG("init all threads fail\n");
	} else
		NVRAM_LOG("Set property failed, %s\n", (char*)strerror(errno));
	NVRAM_LOG("NVRAM daemon sleep !\n");
	sleep(10);
	NVRAM_LOG("NVRAM daemon sync start !\n");
	sync();
	NVRAM_LOG("NVRAM daemon sync end !\n");
	NVRAM_LOG("NVRAM daemon exits !\n");
	exit(EXIT_SUCCESS);
}
