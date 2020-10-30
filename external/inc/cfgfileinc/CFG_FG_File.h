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

#ifndef _CFG_FG_FILE_H
#define _CFG_FG_FILE_H


// the record structure define of bt nvram file
typedef struct
{
	char dsp_dev[20];
	unsigned int nvram_car_tune_value;
} ap_nvram_fg_config_struct;


//the record size and number of bt nvram file
#define CFG_FILE_FG_CONFIG_SIZE    sizeof(ap_nvram_fg_config_struct)
#define CFG_FILE_FG_CONFIG_TOTAL   1

#endif /* _CFG_FG_FILE_H */
