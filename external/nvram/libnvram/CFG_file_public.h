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

/*******************************************************************************
 *
 * Filename:
 * ---------
 *   cfg_file_lid.h
 *
 * Project:
 * --------
 *   DUMA
 *
 * Description:
 * ------------
 *    header file of main function
 *
 * Author:
 * -------
 *   Nick Huang (mtk02183)
 *
 *******************************************************************************/

#ifndef CFG_FILE_PUBLIC_H
#define CFG_FILE_PUBLIC_H

#include <sys/types.h>

// the size of file name
#define FILENAMELENGTH 70
//the size of versino information
#define FILEVERLENGTH 4

#define DataReset   1
#define DataConvert 0

typedef int(*pfConvertFunc)(int, int, char*, char*);
typedef enum {
	APRDEB,		//file will reset to default value every boot
	APRDCL		//file will reset to default value only when clean  boot

} FILE_RESTORE_TYPE;

typedef enum {
	MULTIPLE_DEFUALT_REC,	//default value is defined global varible * record number
	SIGNLE_DEFUALT_REC,		//default value is defined global variable.
	DEFAULT_ZERO,			//default value is 0
	DEFAULT_FF,				//default value is 0xff

} FILE_DEFAULT_TYPE;

typedef struct {
	char				cFileName[FILENAMELENGTH];	//file name
	char				cFileVer[FILEVERLENGTH];	//nvram file version information
	int 				i4RecSize;		//record size
	int					i4RecNum;			//record total
	FILE_DEFAULT_TYPE 	stDefualType;	//the type of default value
	char 				*pDefualtVaule;	//the defualt value.
	int                       bDataProcessingType;
	pfConvertFunc             NVM_DataConvertFunc;
} TCFG_FILE;

typedef struct {
	int lid;
	off_t start_address;
	off_t size;
} TABLE_FOR_SPECIAL_LID;
typedef int(*pfCallbackForDaemon)(void);
#endif /* CFG_FILE_LID_H */

