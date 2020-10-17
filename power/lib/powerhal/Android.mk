# Copyright (C) 2020 The Evolution X Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SHARED_LIBRARIES += \
    libc \
    libcutils \
    libdl \
    libexpat \
    libhardware \
    libhidlbase \
    libhidltransport \
    libhwbinder \
    liblog \
    libui \
    libtinyxml2 \
    libutils \
    android.hardware.power@1.0 \
    android.hardware.power@1.1 \
    android.hardware.power@1.2 \
    android.hardware.power@1.3 \
    vendor.mediatek.hardware.power@2.0 \
    vendor.mediatek.hardware.netdagent@1.0

LOCAL_SRC_FILES += \
    common.cpp \
    perfservice.cpp \
    perfservice_smart.cpp \
    perfservice_xmlparse.cpp \
    utility_thermal.cpp \
    utility_consys.cpp \
    utility_fps.cpp \
    utility_vpu.cpp \
    utility_netd.cpp \
    utility_ux.c \
    utility_ril.c \
    utility_io.cpp \
    utility_sys.cpp

LOCAL_C_INCLUDES += \
    $(LOCAL_PATH)/../../config/common/intf_types \
    $(LOCAL_PATH)/../../include \
    $(LOCAL_PATH)/../../../../../external/tinyxml2

LOCAL_MODULE := libpowerhal
LOCAL_MODULE_OWNER := mtk
LOCAL_VENDOR_MODULE := true

include $(BUILD_SHARED_LIBRARY)
