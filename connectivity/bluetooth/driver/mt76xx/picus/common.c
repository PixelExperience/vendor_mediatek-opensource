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

//---------------------------------------------------------------------------
#include "common.h"

//---------------------------------------------------------------------------
int g_debuglevel = MT_DEBUG_WARN;       // show priority than WARN

//---------------------------------------------------------------------------
void DBGPRINT(int level, const char *format, ...)
{
    if (level > g_debuglevel) {
        // don't print
        return;
    }

    char buf[1024] = "";
    va_list Arg;
    va_start(Arg, format);
    vsnprintf(buf, 300, format, Arg);
    va_end(Arg);
    printf("[picus] %s\n", buf);
    fflush(stdout);
    return;
}

//---------------------------------------------------------------------------
