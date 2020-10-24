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

#ifndef __BT_EM_H__
#define __BT_EM_H__

#include <stdbool.h>
#ifndef FALSE
#define FALSE     0
#endif
#ifndef TRUE
#define TRUE      1
#endif
#ifndef BOOL
#define BOOL      bool
#endif

typedef unsigned char UCHAR;
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;

#define UNUSED_ATTR __attribute__((unused))

/* I/O attributes for read/write behavior */
#define WR_INTERRUPTIBLE 0x0001
#define RD_INTERRUPTIBLE 0x0002

/*
* Enum Definitions
*/
typedef enum {
  BT_CHIP_ID_MT6611 = 0,
  BT_CHIP_ID_MT6612,
  BT_CHIP_ID_MT6616,
  BT_CHIP_ID_MT6620,
  BT_CHIP_ID_MT6622,
  BT_CHIP_ID_MT6626,
  BT_CHIP_ID_MT6628,
  BT_CHIP_ID_MT6630,
  BT_CHIP_ID_MT6632
} BT_CHIP_ID;

typedef enum {
  BT_HW_ECO_UNKNOWN = 0,
  BT_HW_ECO_E1,
  BT_HW_ECO_E2,
  BT_HW_ECO_E3,
  BT_HW_ECO_E4,
  BT_HW_ECO_E5,
  BT_HW_ECO_E6,
  BT_HW_ECO_E7
} BT_HW_ECO;


/*
* Exported Function Declaration
*/
#ifdef __cplusplus
extern "C"
{
#endif
BOOL EM_BT_init(void);
void EM_BT_deinit(void);
BOOL EM_BT_write(unsigned char *buf, unsigned int len);
BOOL EM_BT_read(unsigned char *buf, unsigned int len, unsigned int *pu4ResultLen);
void EM_BT_set_io_attr(int flags);
void EM_BT_clear_io_attr(int flags);
void EM_BT_polling_start(void);
void EM_BT_polling_stop(void);
unsigned int EM_BT_getPatchVersion(unsigned char *buf);
#ifdef __cplusplus
}
#endif

#endif
