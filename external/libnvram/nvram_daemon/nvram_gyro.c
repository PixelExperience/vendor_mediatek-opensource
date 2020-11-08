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
#include "libnvram.h"
#include "libnvram_log.h"
#include "CFG_module_file.h"
#include "CFG_file_lid.h"
#include "hwmsensor.h"
#include "nvram_gyro.h"
#include "libhwm.h"
/*---------------------------------------------------------------------------*/
void* NVRAM_GYRO(void* arg) {
	int err = 0;
	int fd = -1;
	HwmData dat;

	gyroscope_open(&fd);
	if (fd < 0) {
		NVRAM_LOG("null gyroscope file handle pointer: %d!\n", fd);
		err = -EFAULT;
	}

	if (err) {
		NVRAM_LOG("stop due to err\n");
	} else if ((err = gyroscope_read_nvram(&dat)) != 0) {
		NVRAM_LOG("read gyroscope nvram fail: %d(%s)\n", errno, strerror(errno));
	} else if ((err = gyroscope_set_cali(fd, &dat)) != 0) {
		NVRAM_LOG("set gyroscope calibration fail: %d(%s)\n", errno, strerror(errno));
	} else {
		NVRAM_LOG("write gyroscope calibration done\n");
	}
	if (fd > 0) {
		gyroscope_close(fd);
	}
	pthread_exit(NULL);
	return NULL;
}

