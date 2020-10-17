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
    liblog \
    libutils \
    libhidlbase \
    android.hardware.power@1.0 \
    android.hardware.power@1.1 \
    android.hardware.power@1.2 \
    vendor.mediatek.hardware.power@2.0 \
    vendor.mediatek.hardware.power@2.1 \
    vendor.mediatek.hardware.mtkpower@1.0

LOCAL_SRC_FILES := power_hal_wrap.cpp

LOCAL_C_INCLUDES += \
    ../../power/include

LOCAL_MODULE := libpowerhalwrap
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_OWNER := mtk
LOCAL_PRELINK_MODULE := false

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_SHARED_LIBRARIES += \
    liblog \
    libutils \
    libhidlbase \
    android.hardware.power@1.0 \
    android.hardware.power@1.1 \
    android.hardware.power@1.2 \
    vendor.mediatek.hardware.power@2.0 \
    vendor.mediatek.hardware.power@2.1 \
    vendor.mediatek.hardware.mtkpower@1.0

LOCAL_SRC_FILES := power_hal_wrap.cpp

LOCAL_C_INCLUDES += \
    ../../power/include

LOCAL_MODULE := libpowerhalwrap_vendor
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_OWNER := mtk
LOCAL_PRELINK_MODULE := false
LOCAL_VENDOR_MODULE := true

include $(BUILD_SHARED_LIBRARY)
