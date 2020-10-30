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
 *   cfg_mdtype_file.h
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
 *   Haow Wang(MTK81183)
 *
 *------------------------------------------------------------------------------
 * $Revision:$
 * $Modtime:$
 * $Log:$
 *
 *******************************************************************************/



#ifndef _CFG_MDTYPE_FILE_H
#define _CFG_MDTYPE_FILE_H


// the record structure define of md type nvram file
typedef struct
{

    unsigned int md_type;
	
} md_type_struct;


//the record size and number of md type nvram file
#define CFG_FILE_MDTYPE_CONFIG_SIZE    sizeof(md_type_struct)
#define CFG_FILE_MDTYPE_CONFIG_TOTAL   1

#endif /* _CFG_MDTYPE_FILE_H */
