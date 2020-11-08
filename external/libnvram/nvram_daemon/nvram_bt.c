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
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "CFG_BT_File.h"
#include "CFG_file_lid.h"
#include "libnvram.h"
#include "libnvram_log.h"


extern int nvram_bt_default_value(unsigned char *);
void* NVRAM_BT(void* arg) {
	F_ID bt_nvram_fd = {0};
	int rec_size = 0;
	int rec_num = 0;
	ap_nvram_btradio_struct bt_nvram, zero;

	bt_nvram_fd = NVM_GetFileDesc(AP_CFG_RDEB_FILE_BT_ADDR_LID, &rec_size, &rec_num,
	                              ISWRITE);
	NVRAM_LOG("FD %d rec_size %d rec_num %d\n", bt_nvram_fd.iFileDesc, rec_size,
	          rec_num);

	if (rec_num != 1) {
		NVRAM_LOG("Unexpected record num %d", rec_num);
		NVM_CloseFileDesc(bt_nvram_fd);
		return NULL;
	}

	if (rec_size != sizeof(ap_nvram_btradio_struct)) {
		NVRAM_LOG("Unexpected record size %d ap_nvram_btradio_struct %d",
		          rec_size, sizeof(ap_nvram_btradio_struct));
		NVM_CloseFileDesc(bt_nvram_fd);
		return NULL;
	}

	if (read(bt_nvram_fd.iFileDesc, &bt_nvram, rec_num * rec_size) < 0) {
		NVRAM_LOG("Read NVRAM fails %d\n", errno);
		NVM_CloseFileDesc(bt_nvram_fd);
		return NULL;
	}

	NVRAM_LOG("Read NVRAM: [BDAddr %02x-%02x-%02x-%02x-%02x-%02x][Voice %02x %02x][Codec %02x %02x %02x %02x] \
              [Radio %02x %02x %02x %02x %02x %02x][Sleep %02x %02x %02x %02x %02x %02x %02x][BtFTR %02x %02x] \
              [TxPWOffset %02x %02x %02x][CoexAdjust %02x %02x %02x %02x %02x %02x]\n",
	          bt_nvram.addr[0], bt_nvram.addr[1], bt_nvram.addr[2], bt_nvram.addr[3],
	          bt_nvram.addr[4], bt_nvram.addr[5],
	          bt_nvram.Voice[0], bt_nvram.Voice[1],
	          bt_nvram.Codec[0], bt_nvram.Codec[1], bt_nvram.Codec[2], bt_nvram.Codec[3],
	          bt_nvram.Radio[0], bt_nvram.Radio[1], bt_nvram.Radio[2], bt_nvram.Radio[3],
	          bt_nvram.Radio[4], bt_nvram.Radio[5],
	          bt_nvram.Sleep[0], bt_nvram.Sleep[1], bt_nvram.Sleep[2], bt_nvram.Sleep[3],
	          bt_nvram.Sleep[4], bt_nvram.Sleep[5], bt_nvram.Sleep[6],
	          bt_nvram.BtFTR[0], bt_nvram.BtFTR[1],
	          bt_nvram.TxPWOffset[0], bt_nvram.TxPWOffset[1], bt_nvram.TxPWOffset[2],
	          bt_nvram.CoexAdjust[0], bt_nvram.CoexAdjust[1], bt_nvram.CoexAdjust[2],
	          bt_nvram.CoexAdjust[3], bt_nvram.CoexAdjust[4], bt_nvram.CoexAdjust[5]);

	memset(&zero, 0, sizeof(ap_nvram_btradio_struct));

	if (0 == memcmp(&bt_nvram, &zero, sizeof(ap_nvram_btradio_struct))) {
		if (!nvram_bt_default_value(&bt_nvram)) {
			/* NVRAM data All Zero */
		} else {
			/* Initialize NVRAM with specific default value */
			lseek(bt_nvram_fd.iFileDesc, 0, 0);

			if (write(bt_nvram_fd.iFileDesc, &bt_nvram, rec_num * rec_size) < 0) {
				NVRAM_LOG("Initialize NVRAM fails %d\n", errno);
			}
		}
	}

	NVM_CloseFileDesc(bt_nvram_fd);
	pthread_exit(NULL);
	return NULL;
}
