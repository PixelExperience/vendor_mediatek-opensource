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
 *   CFG_MD_SBP_FILE.h
 *
 * Project:
 * --------
 *   KK
 *
 * Description:
 * ------------
 *    header file of md SBP config struct
 *
 * Author:
 * -------
 *    Jue Zhou (mtk80024)
 *
 *------------------------------------------------------------------------------
 * $Revision:$
 * $Modtime:$
 * $Log:$
 *
 *
 *
 *******************************************************************************/

#ifndef _CFG_MD_SBP_FILE_H
#define _CFG_MD_SBP_FILE_H

#define SBP_FLAG_UPDATED 1 // updated, need not send to md, 0: the latest setting, need update
// SBP: Single Binary Platfor, used for modem customization
typedef struct
{
    unsigned int md_sbp_code;     // bit defined by modem;
    unsigned int flag_updated;    // 0: not updated, needn't send to md, 1:updated, need send to md
    unsigned int md2_sbp_code;     // bit defined by modem 2;
    unsigned int flag2_updated;    // 0: not updated, needn't send to md, 1:updated, need send to md
    unsigned int md3_sbp_code;     // bit defined by modem 3;
    unsigned int flag3_updated;    // 0: not updated, needn't send to md, 1:updated, need send to md
} MD_SBP_Struct;

#define CFG_FILE_MD_SBP_CONFIG_SIZE    sizeof(MD_SBP_Struct)
#define CFG_FILE_MD_SBP_CONFIG_TOTAL   1

#endif	// _CFG_MD_SBP_FILE_H

