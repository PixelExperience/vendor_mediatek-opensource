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
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include "libnvram.h"
#include "libnvram_log.h"
//#include "CFG_file_lid.h"
//#include "Custom_NvRam_LID.h"
//#include "CFG_WIFI_Default.h"
//#include "CFG_WIFI_Custom_Default.h"
#include "CFG_Wifi_File.h"
//#include "CFG_Wifi_Custom_File.h"

extern int iFileWIFILID;
extern int iFileCustomWIFILID;


/* Just tell NVRAM to create wifi default record */
void* NVRAM_WIFI(void* arg) {
	F_ID wifi_nvram_fd, wifi_custom_nvram_fd;
	int rec_size = 0;
	int rec_num = 0;

	//NVRAM_LOG("[NVRAM Daemon]wifi lid %d ++\n",AP_CFG_RDEB_FILE_WIFI_LID);
	NVRAM_LOG("[NVRAM Daemon]wifi lid %d ++\n", iFileWIFILID);
	//wifi_nvram_fd = NVM_GetFileDesc(AP_CFG_RDEB_FILE_WIFI_LID, &rec_size, &rec_num, true);
	wifi_nvram_fd = NVM_GetFileDesc(iFileWIFILID, &rec_size, &rec_num, true);
	NVRAM_LOG("[wifi] wifi FD %d rec_size %d rec_num %d\n", wifi_nvram_fd.iFileDesc, rec_size, rec_num);
	NVM_CloseFileDesc(wifi_nvram_fd);

	rec_size = 0;
	rec_num = 0;
	//NVRAM_LOG("[NVRAM Daemon]wifi custom lid %d ++\n",AP_CFG_RDEB_WIFI_CUSTOM_LID);
	NVRAM_LOG("[NVRAM Daemon]wifi custom lid %d ++\n", iFileCustomWIFILID);
	//wifi_custom_nvram_fd = NVM_GetFileDesc(AP_CFG_RDEB_WIFI_CUSTOM_LID, &rec_size, &rec_num, true);
	wifi_custom_nvram_fd = NVM_GetFileDesc(iFileCustomWIFILID, &rec_size, &rec_num,
	                                       true);
	NVRAM_LOG("[wifi] wifi custom FD %d rec_size %d rec_num %d\n",
	          wifi_custom_nvram_fd.iFileDesc, rec_size, rec_num);
	NVM_CloseFileDesc(wifi_custom_nvram_fd);
	pthread_exit(NULL);
	return NULL;
}
