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

#ifndef MTK_ARSI_CALL_TYPE_H
#define MTK_ARSI_CALL_TYPE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * =============================================================================
 *                     enum
 * =============================================================================
 */

typedef enum {
    PHONE_CALL_BAND_08K = 0,
    PHONE_CALL_BAND_16K = 1,
    PHONE_CALL_BAND_32K = 2,
    PHONE_CALL_BAND_48K = 3,
} call_band_t;


typedef enum {
    PHONE_CALL_NET_UNKNOWN   = 0,
    PHONE_CALL_NET_GSM       = 1,
    PHONE_CALL_NET_WCDMA     = 2,
    PHONE_CALL_NET_CDMA      = 3,
    PHONE_CALL_NET_VOLTE     = 4,
    PHONE_CALL_NET_C2K       = 5,
} call_net_t;


/*
 * =============================================================================
 *                     Data Structure
 * =============================================================================
 */

typedef struct extra_call_arg_t {
    uint8_t call_band_type;   /* call_band_t */
    uint8_t call_net_type;    /* call_net_t */
} extra_call_arg_t;



#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* end of MTK_ARSI_CALL_TYPE_H */

