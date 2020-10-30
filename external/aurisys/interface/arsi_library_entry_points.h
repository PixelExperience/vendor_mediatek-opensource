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

#ifndef MTK_ARSI_LIBRARY_ENTRY_POINTS_H
#define MTK_ARSI_LIBRARY_ENTRY_POINTS_H

#include <string.h>

#include <arsi_api.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * =============================================================================
 *                     Need 3rd-party to implement the libraries
 * =============================================================================
 */

#if 1 /* For HAL */
/*
 * ONLY for dynamic link, like libXXX.so in HAL (including parsing lib.so)
 * NEVER implement this function for libXXX.a in FreeRTOS
 */
void dynamic_link_arsi_assign_lib_fp(AurisysLibInterface *lib);


#else /* For FreeRTOS */
/*
 * For static link, like libXXX.a in FreeRTOS
 * However, it's fine to implement it for libXXX.so
 */
void demo_arsi_assign_lib_fp(AurisysLibInterface *lib); /* DEMO only */

void FV_arsi_assign_lib_fp(AurisysLibInterface *lib);
void iir_arsi_assign_lib_fp(AurisysLibInterface *lib);
void mtk_sp_team_arsi_assign_lib_fp(AurisysLibInterface *lib);
void besloudness_arsi_assign_lib_fp(AurisysLibInterface *lib);
void dcremoval_arsi_assign_lib_fp(AurisysLibInterface *lib);
void lvve_arsi_assign_lib_fp(AurisysLibInterface *lib);


#define AURISYS_LINK_LIB_NAME_TO_API(name, api) \
    do { \
        if (!name || !api) { \
            break; \
        } \
        if (!strcmp(name, "aurisys_demo")) { \
            demo_arsi_assign_lib_fp(api); \
        } else if (!strcmp(name, "mtk_bessound")) {\
            besloudness_arsi_assign_lib_fp(api); \
        } else if (!strcmp(name, "mtk_dcrflt")) {\
            dcremoval_arsi_assign_lib_fp(api); \
        } else if (!strcmp(name, "nxp_speech")) {\
            lvve_arsi_assign_lib_fp(api); \
        } \
    } while (0)


#endif




#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* end of MTK_ARSI_LIBRARY_ENTRY_POINTS_H */

