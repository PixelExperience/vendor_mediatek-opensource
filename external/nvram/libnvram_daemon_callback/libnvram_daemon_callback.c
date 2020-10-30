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
 *   libnvram_sec.c
 *
 * Project:
 * --------
 *   YuSu
 *
 * Description:
 * ------------
 *   Security interface for moto.
 *
 *
 * Author:
 * -------
 *   Jian lin (mtk81139)
 *
 ****************************************************************************/

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libnvram_daemon_callback.h"

extern pfCallbackForDaemon callback_for_nvram_daemon;

int my_callback(void) {
	ALOGD("nvram daemon callback will run!!!");
	return 0;
}

int init_callback(void) {
#ifdef MTK_PRODUCT_INFO_SUPPORT
	callback_for_nvram_daemon = my_callback;
#endif
	return 0;
}
