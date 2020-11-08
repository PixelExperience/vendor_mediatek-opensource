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

#include <stdio.h>
#include <sys/stat.h>
#include <private/android_filesystem_config.h>
#include "libnvram.h"
#include "libnvram_log.h"
#include "nvram_battery.h"

void* NVRAM_TOUCHPANEL(void* arg) {
	char buf[1024];
	int fd, size;
	struct stat stat_dir, stat_file;
	NVRAM_LOG("touch panel calibration");
	stat("/data/misc/touchpanel", &stat_dir);
	stat("/data/misc/touchpanel/calibration", &stat_file);
	if (!S_ISREG(stat_dir.st_mode)) mkdir("/data/misc/touchpanel", 0755);
	if (!S_ISREG(stat_file.st_mode)) {
		fd = open("/data/misc/touchpanel/calibration", O_CREAT,
		          S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
		close(fd);
		chown("/data/misc/touchpanel/calibration", AID_ROOT, AID_DIAG);
	}
	if ((fd = open("/data/misc/touchpanel/calibration", O_RDWR)) < 0) {
		NVRAM_LOG("failed to open touchpanel calibration data");
		return NULL;
	}
	size = read(fd, buf, 1024);
	close(fd);
	if ((fd = open("/sys/module/tpd_setting/parameters/tpd_calmat",
	               O_WRONLY)) < 0) {
		NVRAM_LOG("failed to open touch panel driver");
		return NULL;
	}
	write(fd, buf, size);
	close(fd);
	pthread_exit(NULL);
	return NULL;
}
