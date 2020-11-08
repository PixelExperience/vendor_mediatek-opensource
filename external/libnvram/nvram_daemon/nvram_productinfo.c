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
extern int iFilePRODUCT_INFOLID;


/* Just tell NVRAM to create Product info default record */
void* NVRAM_PRODUCTINFO(void* arg) {
	F_ID pin_fid;
	int rec_size = 0;
	int rec_num = 0;

	NVRAM_LOG("[NVRAM Daemon]product info lid %d ++\n", iFilePRODUCT_INFOLID);
	pin_fid = NVM_GetFileDesc(iFilePRODUCT_INFOLID, &rec_size, &rec_num, true);
	NVRAM_LOG("[NVRAM Daemon] product info FID %d rec_size %d rec_num %d\n",
	          pin_fid.iFileDesc, rec_size, rec_num);
	if (!NVM_CloseFileDesc(pin_fid))
		NVRAM_LOG("[NVRAM Daemon] close product info error");
	pthread_exit(NULL);
	return NULL;
}
