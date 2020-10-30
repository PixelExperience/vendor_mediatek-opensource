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
 *   cfg_uart_config_default.h
 *
 * Project:
 * --------
 *   DUMA
 *
 * Description:
 * ------------
 *    header file of UART default config
 *
 * Author:
 * -------
 *    LiChunhui (MTK80143)
 *
 *------------------------------------------------------------------------------
 * $Revision:$
 * $Modtime:$
 * $Log:$
 *
 * Apr 10 2009 mtk80306
 * [DUMA00114160] daily build error
 * remove the include path.
 *
 * Mar 24 2009 mtk80143
 * [DUMA00112375] [uart] UART EM mode
 * Add for UART EM mode
 *
 *
 *******************************************************************************/

#ifndef _CFG_UART_CONFIG_DEFAULT_H
#define _CFG_UART_CONFIG_DEFAULT_H

///#include "cfgfileinc/CFG_UART_File.h"

ap_nvram_uart_config_struct stUARTConfigDefault =
{		
    {0x01,0x0,0x0,0x0}
};

#endif


