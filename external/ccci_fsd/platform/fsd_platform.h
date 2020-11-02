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

#ifndef __FSD_PLATFORM_H__
#define __FSD_PLATFORM_H__
#include "ccci_fsd.h"

#include <android/log.h>
#include <log/log.h>
#include <cutils/properties.h>
#include "power.h"

#define FS_WAKE_LOCK_NAME "ccci_fsd"
#define FS_WAKE_LOCK() acquire_wake_lock(PARTIAL_WAKE_LOCK, FS_WAKE_LOCK_NAME)
#define FS_WAKE_UNLOCK() release_wake_lock(FS_WAKE_LOCK_NAME)

//----------------debug macro and function define--------------//
#define ENABLE_ERROR_LOG
#define ENABLE_DEBUG_LOG

#define FSD_ERR_MTKLOG(md_id, ...)      do{ \
    if(md_id == 0) \
        __android_log_print(ANDROID_LOG_ERROR, MD1_FS_TAG, __VA_ARGS__); \
        else if(md_id == 1) \
            __android_log_print(ANDROID_LOG_ERROR, MD2_FS_TAG, __VA_ARGS__); \
        else if(md_id == 2) \
            __android_log_print(ANDROID_LOG_ERROR, MD3_FS_TAG, __VA_ARGS__); \
        else if(md_id == 4) \
            __android_log_print(ANDROID_LOG_ERROR, MD5_FS_TAG, __VA_ARGS__); \
        else \
            __android_log_print(ANDROID_LOG_ERROR, MD_COMN_TAG, __VA_ARGS__); \
    }while(0)

#define FSD_VER_MTKLOG(md_id, ...)      do{ \
        if(md_id == 0) \
            __android_log_print(ANDROID_LOG_VERBOSE, MD1_FS_TAG, __VA_ARGS__); \
        else if(md_id == 1) \
            __android_log_print(ANDROID_LOG_VERBOSE, MD2_FS_TAG, __VA_ARGS__); \
        else if(md_id == 2) \
            __android_log_print(ANDROID_LOG_VERBOSE, MD3_FS_TAG, __VA_ARGS__); \
        else if(md_id == 4) \
            __android_log_print(ANDROID_LOG_VERBOSE, MD5_FS_TAG, __VA_ARGS__); \
        else \
            __android_log_print(ANDROID_LOG_VERBOSE, MD_COMN_TAG, __VA_ARGS__); \
    }while(0)

#define FSD_DEBUG_MTKLOG(md_id, ...)      do{ \
        if(md_id == 0) \
            __android_log_print(ANDROID_LOG_DEBUG, MD1_FS_TAG, __VA_ARGS__); \
        else if(md_id == 1) \
            __android_log_print(ANDROID_LOG_DEBUG, MD2_FS_TAG, __VA_ARGS__); \
        else if(md_id == 2) \
            __android_log_print(ANDROID_LOG_DEBUG, MD3_FS_TAG, __VA_ARGS__); \
        else if(md_id == 4) \
            __android_log_print(ANDROID_LOG_DEBUG, MD5_FS_TAG, __VA_ARGS__); \
        else \
            __android_log_print(ANDROID_LOG_DEBUG, MD_COMN_TAG, __VA_ARGS__); \
    }while(0)

#define FSD_INF_MTKLOG(md_id, ...)      do{ \
        if(md_id == 0) \
            __android_log_print(ANDROID_LOG_INFO, MD1_FS_TAG, __VA_ARGS__); \
        else if(md_id == 1) \
            __android_log_print(ANDROID_LOG_INFO, MD2_FS_TAG, __VA_ARGS__); \
        else if(md_id == 2) \
            __android_log_print(ANDROID_LOG_INFO, MD3_FS_TAG, __VA_ARGS__); \
        else if(md_id == 4) \
            __android_log_print(ANDROID_LOG_INFO, MD5_FS_TAG, __VA_ARGS__); \
        else \
            __android_log_print(ANDROID_LOG_INFO, MD_COMN_TAG, __VA_ARGS__); \
    }while(0)

#define FSD_WARN_MTKLOG(md_id, ...)      do{ \
        if(md_id == 0) \
            __android_log_print(ANDROID_LOG_WARN, MD1_FS_TAG, __VA_ARGS__); \
        else if(md_id == 1) \
            __android_log_print(ANDROID_LOG_WARN, MD2_FS_TAG, __VA_ARGS__); \
        else if(md_id == 2) \
            __android_log_print(ANDROID_LOG_WARN, MD3_FS_TAG, __VA_ARGS__); \
        else if(md_id == 4) \
            __android_log_print(ANDROID_LOG_WARN, MD5_FS_TAG, __VA_ARGS__); \
        else \
            __android_log_print(ANDROID_LOG_WARN, MD_COMN_TAG, __VA_ARGS__); \
    }while(0)

#ifdef ENABLE_ERROR_LOG
#define LOGE(...)    FSD_ERR_MTKLOG(md_id, __VA_ARGS__)
#define LOGE_COM(...)  FSD_ERR_MTKLOG(0xFF, __VA_ARGS__)
#else
#define LOGE(...)
#define LOGE_COM(...)
#endif

#ifdef ENABLE_DEBUG_LOG
extern char  debug_level;

#define LOGV(...)    do{ \
        if(debug_level <= ANDROID_LOG_VERBOSE) \
            FSD_VER_MTKLOG(md_id, __VA_ARGS__); \
    }while(0)

#define LOGD(...)    do{ \
        if(debug_level <= ANDROID_LOG_DEBUG) \
            FSD_DEBUG_MTKLOG(md_id, __VA_ARGS__); \
    }while(0)

#define LOGI(...)    do{ \
        if(debug_level <= ANDROID_LOG_INFO) \
            FSD_INF_MTKLOG(md_id, __VA_ARGS__); \
    }while(0)

#define LOGW(...)    do{ \
        if(debug_level <= ANDROID_LOG_WARN) \
            FSD_WARN_MTKLOG(md_id, __VA_ARGS__); \
    }while(0)
#else
#define LOGV(...)    {}

#define LOGD(...)    {}

#define LOGI(...)    {}

#define LOGW(...)    {}

#endif

void get_debug_log_level(void);

int FS_OTPLock(int devtype __attribute__((unused)));
int FS_OTPQueryLength(int devtype __attribute__((unused)), unsigned int * Length);
int FS_OTPRead(int devtype __attribute__((unused)), unsigned int  Offset, void * BufferPtr, unsigned int Length);
int FS_OTPWrite(int devtype __attribute__((unused)), unsigned int  Offset, void * BufferPtr, unsigned int Length);
int FS_OTP_init(int md_id);
int get_modem_status();

extern bool NVM_RestoreFromBinRegion_OneFile(int file_lid, const char* filename);
#endif

