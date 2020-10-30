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
 *   File_OP.h
 *
 * Project:
 * --------
 *   YuSu
 *
 * Description:
 * ------------
 *    header file of main function
 *
 * Author:
 * -------
 *   Nick Huang (mtk02183)
 *
 *------------------------------------------------------------------------------
 * $Revision:$
 * $Modtime:$
 * $Log:$
 *
 * Jun 18 2009 mtk80306
 * [DUMA00120904] optimize the power button and nvram
 *
 *
 * Apr 29 2009 mtk80306
 * [DUMA00116080] revise the customization of nvram
 * revise nvram customization
 *
 * Mar 21 2009 mtk80306
 * [DUMA00112158] fix the code convention.
 * fix the codeing convention.
 *
 * Mar 15 2009 mtk80306
 * [DUMA00111629] add camera nvram files
 * add the check of bin region.
 *
 * Feb 23 2009 mtk80306
 * [DUMA00109277] add meta _battery mode.
 *
 *
 * Nov 24 2008 mbj08139
 * [DUMA00105099] create meta code
 *
 *
 * Oct 29 2008 mbj08139
 * [DUMA00105099] create meta code
 *
 *
 *
 *
 *******************************************************************************/

#ifndef __NVRAM_LOG_H__
#define __NVRAM_LOG_H__



//#define LOG_TAG "META  "


//#define META_LOG(fmt, args...) printf(LOG_TAG fmt, ##args)

#ifdef _WIN32
#define LOGD(x)
#else
//#include <utils/Log.h>
#include <log/log.h>
#undef LOG_TAG
#define LOG_TAG "NVRAM"
#endif

#define NVBAK_LOG(...) \
        do { \
            ALOGD(__VA_ARGS__); \
        } while (0)

#define TEXT(__a)  __a

#define NVRAM_LOG(...) \
    do { \
        ALOGD(__VA_ARGS__); \
    } while (0)




/*****************************************************************************/







#endif /* __NVRAM_LOG_H__ */
