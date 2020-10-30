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
 *   Libnvram_sec.h
 *
 * Project:
 * --------
 *   YuSu
 *
 * Description:
 * ------------
 *
 *
 *
 * Author:
 * -------
 *  Jian lin (mtk81139)
 *
 ****************************************************************************/


#ifndef __NVRAM_LIB_SEC_H
#define __NVRAM_LIB_SEC_H

#include "libnvram.h"
#include "libnvram_log.h"
#include "../../inc/CFG_file_lid.h"
#include "../../inc/cfgdefault/inc/Custom_NvRam_LID.h"
//#include "sec_nvram.h"



#ifdef __cplusplus
extern "C"
{
#endif


#define BOOT_MODE_FILE "/sys/class/BOOT/BOOT/boot/boot_mode"
#define META_MODE '1'
#define ADVMETA_MODE '5'
#define ENCODE  true
#define DECODE  false

bool NVM_Enc_Dnc_File(int file_lid, bool IS_end);
bool NVM_CheckWritePermission(bool IsRead, int file_lid);

typedef struct {
	int lid;
	unsigned char meta_mode_write;
	unsigned char security_enable;
} TCFG_FILE_PROTECT;




/* used for META library */
#define NVRAM_CIPHER_LEN (16)

/******************************************************************************
 *  MODEM CONTEXT FOR BOTH USER SPACE PROGRAM AND KERNEL MODULE
 ******************************************************************************/
typedef struct {
	unsigned char data[NVRAM_CIPHER_LEN];
	unsigned int ret;

} META_CONTEXT;

/******************************************************************************
 *  EXPORT FUNCTIONS
 ******************************************************************************/
int __attribute__((weak)) sec_nvram_enc (META_CONTEXT *meta_ctx);
int __attribute__((weak)) sec_nvram_dec (META_CONTEXT *meta_ctx);


#ifdef __cplusplus
}
#endif


#endif //__NVRAM_LIB_H
