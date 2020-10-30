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

#ifndef _CFG_BT_FILE_H
#define _CFG_BT_FILE_H


/* The record structure of bt nvram file */
typedef struct
{
    unsigned char addr[6];             /* BT address */
    unsigned char Voice[2];            /* Voice setting for SCO connection */
    unsigned char Codec[4];            /* PCM codec setting */
    unsigned char Radio[6];            /* RF configuration */
    unsigned char Sleep[7];            /* Sleep mode configuration */
    unsigned char BtFTR[2];            /* Other feature setting */
    unsigned char TxPWOffset[3];       /* TX power channel offset compensation */
    unsigned char CoexAdjust[6];       /* BT/WIFI coexistence performance adjustment */
    unsigned char RadioExt[2];         /* RF configuration extended parameters */
    unsigned char TxPWOffsetExt1[3];   /* Tx power channel offset compensation with new range */
    unsigned char TxPWOffsetExt2[10];  /* Tx power channel offset compensation for CONNAC */
    unsigned char PIP[2];              /* PIP value for CONNAC */
    unsigned char TSSI[35];            /* TSSI value for CONNAC */
    unsigned char Reserved1[2];        /* Reserved */
    unsigned char Reserved2[4];        /* Reserved */
    unsigned char Reserved3[8];        /* Reserved */
    unsigned char Reserved4[8];        /* Reserved */
} ap_nvram_btradio_struct, ap_nvram_btradio_mt6610_struct;


/* The record size and number of bt nvram file */
#define CFG_FILE_BT_ADDR_REC_SIZE    sizeof(ap_nvram_btradio_struct)
#define CFG_FILE_BT_ADDR_REC_TOTAL   1

#endif


