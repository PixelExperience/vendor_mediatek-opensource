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

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <linux/input.h>
#include <sys/resource.h>
#include <cutils/properties.h>
#include "fg_log.h"
//using namespace android;

#if defined(MTK_GM_30)
#define LIB_FULL_NAME "/vendor/lib/libfgauge_gm30.so"
#else
#define LIB_FULL_NAME "/vendor/lib/libfgauge.so"
#endif

int (*libfgauge_setup)(void ) = NULL;

void loadlib()
{
        void *handle;

        handle = dlopen(LIB_FULL_NAME, RTLD_NOW);
        if (handle == NULL) {
                FGLOG_NOTICE("Can't load library: %s", dlerror());
                goto fail_out;
        }

        if ((libfgauge_setup = (int (*)(void))dlsym(handle, "libfgauge_setup")) == NULL) {
                FGLOG_NOTICE("load 'libfgauge_setup' error: %s", dlerror());
                goto close_handle;
        }
        return;

close_handle:
        dlclose(handle);
fail_out:
        return;
}

int main(int argc, char *argv[]) 
{
	int fix_warning;
	char **fix_warning2;
	
	fix_warning = argc;
	fix_warning2 = argv;

	fgdlog_init();
	fgdlog_set_level(6);  
	loadlib();
  	  
	if(libfgauge_setup){
		
		libfgauge_setup();
	}
	fgdlog_exit();
	return 0;
}

