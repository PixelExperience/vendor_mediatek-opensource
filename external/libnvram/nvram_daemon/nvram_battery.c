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
#include "nvram_battery.h"
#include "CFG_ADC_File.h"
#include "CFG_ADC_Default.h"
//#include "CFG_file_lid.h"

#define TEST_ADC_CALI_PRINT 	_IO('k', 0)
#define SET_ADC_CALI_Slop 		_IOW('k', 1, int)
#define SET_ADC_CALI_Offset 	_IOW('k', 2, int)
#define SET_ADC_CALI_Cal 			_IOW('k', 3, int)


extern int iFileAuxADCLID;
void* NVRAM_BATTERY(void* arg) {
	//int adc_cali_slop[9] = {1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000};
	//int adc_cali_offset[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	//int adc_cali_cal[1] = {0};

	int ts_nvram_bat_fd = 0;
	// int adc_nvram_fd = 0;
	F_ID adc_nvram_fd;
	//int file_lid = AP_CFG_RDCL_FILE_AUXADC_LID;
	int file_lid = iFileAuxADCLID;
	int i = 0;
	int rec_size;
	int rec_num;
	int adc_cali_cal[1] = {0};

	AUXADC_CFG_Struct stADCReadback = {
		{1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		5,
	};

	stADCReadback.cal = 0xA;
	NVRAM_LOG("NVRAM AP_CFG_RDCL_FILE_AUXADC_LID:%d \n", iFileAuxADCLID);
	/* To be delete */
	//adc_nvram_fd = NVM_GetFileDesc(file_lid, &rec_size, &rec_num, ISWRITE);
	//write(adc_nvram_fd, &stADCDefualt , rec_size*rec_num);
	//NVM_CloseFileDesc(adc_nvram_fd);

	//adc_nvram_fd = NVM_GetFileDesc(file_lid, &rec_size, &rec_num, ISWRITE);
	//read(adc_nvram_fd, &stADCReadback , rec_size*rec_num);
	//NVM_CloseFileDesc(adc_nvram_fd);

	adc_nvram_fd = NVM_GetFileDesc(file_lid, &rec_size, &rec_num, ISWRITE);
	read(adc_nvram_fd.iFileDesc, &stADCReadback , rec_size * rec_num);
	NVM_CloseFileDesc(adc_nvram_fd);

	adc_cali_cal[0] = stADCReadback.cal;

#if 0
	NVRAM_LOG("NVRAM Battery Start!\n");
	for (i = 0; i < 9; i++) {
		NVRAM_LOG("slop = %d\n", stADCReadback.Slop[i]);
		NVRAM_LOG("Offset = %d\n", stADCReadback.Offset[i]);
	}
	NVRAM_LOG("cal = %d , %d\n", adc_cali_cal[0], stADCReadback.cal);
#endif

	/* open file */
	ts_nvram_bat_fd = open("/dev/mtk-adc-cali", O_RDWR, 0);
	if (ts_nvram_bat_fd == -1) {
		//NVRAM_LOG("Open /dev/MT6516-adc_cali : ERROR \n");
		return 0;
	}

	/* test ioctl flow */
	//ioctl(ts_nvram_bat_fd, TEST_ADC_CALI_PRINT, NULL);

	/* set adc calibration data : slop*/
	ioctl(ts_nvram_bat_fd, SET_ADC_CALI_Slop, stADCReadback.Slop);

	/* set adc calibration data : offset*/
	ioctl(ts_nvram_bat_fd, SET_ADC_CALI_Offset, stADCReadback.Offset);

	/* set adc calibration data : cal*/
	ioctl(ts_nvram_bat_fd, SET_ADC_CALI_Cal, adc_cali_cal);

	close(ts_nvram_bat_fd);

	//NVRAM_LOG("NVRAM Battery End!\n");
	pthread_exit(NULL);
	return NULL;
}
