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
    libhardware \
    libhwbinder \
    libhidlbase \
    libhidltransport \
    libutils \
    libcutils \
    vendor.mediatek.hardware.mtkpower@1.0

LOCAL_SRC_FILES += \
    MtkPower.cpp \
    MtkPerf.cpp \
    ../../util/mi_util.cpp \
    ../../util/ptimer.cpp \
    ../../util/ports.cpp \
    ../../util/power_ipc.cpp \
    ../../util/powerc.cpp \
    ../../util/powerd_cmd.cpp

LOCAL_C_INCLUDES += \
    $(LOCAL_PATH)/../../util \
    $(LOCAL_PATH)/../../../include \
    $(LOCAL_PATH)/../../../config/common/intf_types

LOCAL_MODULE := vendor.mediatek.hardware.mtkpower@1.0-impl
LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_MODULE_OWNER := mtk
LOCAL_VENDOR_MODULE := true

include $(BUILD_SHARED_LIBRARY)
