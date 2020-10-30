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
 *   bwcs_custom.h
 *
 * Project:
 * --------
 *   YuSu
 *
 * Description:
 * ------------
 *    This file is the header of bwcs customization related function or definition.
 *
 * Author:
 * -------
 *  Saker Hsia(MTK02327) 
 *
 *------------------------------------------------------------------------------
 * $Revision:$
 * $Modtime:$
 * $Log:$
 *
 * 06 30 2010 saker.hsia
 * [ALPS00002764][Need Patch] [Volunteer Patch] ALPS.10X.W10.28 Volunteer patch for BWCS NVRAM customization 
 * .
 *
 *******************************************************************************/
#ifndef BWCS_CUSTOM_H
#define BWCS_CUSTOM_H


#define RT_RSSI_TH_BT            73
#define RT_RSSI_TH_WIFI1         73
#define RT_RSSI_TH_WIFI2         73

#define NRT_RSSI_TH_BT           73
#define NRT_RSSI_TH_WIFI1        73
#define NRT_RSSI_TH_WIFI2        73
#define ANT_PATH_COMP            10
#define ANT_SWITCH_PROT_TIME     10
#define BT_RX_RANGE              {0xC4, 0xE2}
#if defined (MTK_MT6611)
#define WIFI_TX_FLOW_CTRL        {0x0E00, 0x0001}
#define BT_TX_PWR_WIFI_OFF       0x7
#define BT_TX_PWR_SCO            0x4
#define BT_TX_PWR_ACL            0x4
#elif defined (MTK_MT6612)
#define WIFI_TX_FLOW_CTRL        {0x0E00, 0x0001}
#define BT_TX_PWR_WIFI_OFF       0x7
#define BT_TX_PWR_SCO            0x4
#define BT_TX_PWR_ACL            0x3
#elif defined (MTK_MT6616)
#define WIFI_TX_FLOW_CTRL        {0x1100, 0x0001}
#define BT_TX_PWR_WIFI_OFF       0x7
#define BT_TX_PWR_SCO            0x4
#define BT_TX_PWR_ACL            0x3
#else
#define WIFI_TX_FLOW_CTRL        {0x1100, 0x0001}
#define BT_TX_PWR_WIFI_OFF       0x7
#define BT_TX_PWR_SCO            0x4
#define BT_TX_PWR_ACL            0x4
#endif
#define RESERVED                 {0x00, 0x00, 0x00, 0x00, 0x00}
#endif 
