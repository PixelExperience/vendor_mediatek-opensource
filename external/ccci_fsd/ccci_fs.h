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
 *   ccci_fs.h
 *
 * Project:
 * --------
 *   YuSu
 *
 * Description:
 * ------------
 *   MT6516 CCCI FS Proxy Driver
 *
 * Author:
 * -------
 *   TL Lau (mtk02008)
 *
 ****************************************************************************/

#ifndef __CCCI_FS_H__
#define __CCCI_FS_H__


#define  CCCI_FS_MAX_BUF_SIZE   (16384)
#define  CCCI_FS_MAX_BUFFERS    (5)


typedef struct
{
    unsigned length;
    unsigned index;
} fs_stream_msg_t;
  

typedef struct
{
    unsigned fs_ops;
    unsigned char buffer[CCCI_FS_MAX_BUF_SIZE];
} fs_stream_buffer_t;


#endif // __CCCI_FS_H__
