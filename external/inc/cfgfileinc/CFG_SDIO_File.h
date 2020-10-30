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
 *   cfg_sdio_file.h
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
 *   Juju sung(MTK04314)
 *
 *------------------------------------------------------------------------------
 * $Revision:$
 * $Modtime:$
 * $Log:$
 *******************************************************************************/



#ifndef _CFG_SDIO_FILE_H
#define _CFG_SDIO_FILE_H


// the record structure define of bt nvram file
typedef struct
{
    unsigned char file_count;
    unsigned char id[19];
    unsigned int file_length[19];
    char data[3998];
} ap_nvram_sdio_config_struct;


//the record size and number of bt nvram file
#define CFG_FILE_SDIO_CONFIG_SIZE    sizeof(ap_nvram_sdio_config_struct)
#define CFG_FILE_SDIO_CONFIG_TOTAL   1

#endif /* _CFG_GPS_FILE_H */
