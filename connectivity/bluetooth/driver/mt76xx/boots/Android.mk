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

LOCAL_PATH := $(call my-dir)

boots_socket_path := "\"/data/misc/\""

#- boots -------------------------------------------------------------------
include $(CLEAR_VARS)
LOCAL_CFLAGS := -Werror -Wall
LOCAL_SRC_FILES := \
    boots.c \
    boots_pkt.c \
    boots_skt.c \
    boots_eth.c \
    boots_uart.c \
    boots_script.c

LOCAL_CFLAGS += -DBOOTS_SOCKET_PATH=$(boots_socket_path)
LOCAL_CFLAGS += -DANDROID_PLATFORM
LOCAL_C_INCLUDES := system/core/libcutils/include
LOCAL_SHARED_LIBRARIES := libcutils
LOCAL_MODULE := boots
LOCAL_MODULE_TAGS := optional
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_MODULE_CLASS := EXECUTABLES
include $(BUILD_EXECUTABLE)

#- boots_srv ----------------------------------------------------------------
include $(CLEAR_VARS)
LOCAL_CFLAGS := -Werror -Wall
LOCAL_SRC_FILES := \
    boots_srv.c \
    boots_btif.c \
    boots_pkt.c \
    boots_skt.c \
    boots_eth.c \
    boots_mt6xx.c \
    boots_uart.c \
    boots_script.c

LOCAL_CFLAGS += -DBOOTS_SOCKET_PATH=$(boots_socket_path)
LOCAL_CFLAGS += -DANDROID_PLATFORM
LOCAL_C_INCLUDES := system/core/libcutils/include
LOCAL_SHARED_LIBRARIES := libcutils
LOCAL_MODULE := boots_srv
LOCAL_MODULE_TAGS := optional
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_MODULE_CLASS := EXECUTABLES
include $(BUILD_EXECUTABLE)
