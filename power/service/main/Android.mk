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

ifneq ($(wildcard $(LOCAL_PATH)/../../config/$(MTK_PLATFORM_DIR)/cus_hint),)

LOCAL_C_INCLUDES += \
    $(LOCAL_PATH)/../util \
    $(LOCAL_PATH)/../../include \
    $(LOCAL_PATH)/../../lib/powerhal \
    $(LOCAL_PATH)/../../config/common/intf_types \
    $(LOCAL_PATH)/../../config/$(MTK_PLATFORM_DIR)/cus_hint

else

LOCAL_C_INCLUDES += \
    $(LOCAL_PATH)/../util \
    $(LOCAL_PATH)/../../include \
    $(LOCAL_PATH)/../../lib/powerhal \
    $(LOCAL_PATH)/../../config/common/intf_types \
    $(LOCAL_PATH)/../../config/common/cus_hint

endif

LOCAL_CFLAGS += -DMTK_POWER_HAL_V_2_1_SUPPORT

LOCAL_SRC_FILES += \
    service.cpp \
    PowerManager.cpp \
    ../util/mi_util.cpp \
    ../util/ptimer.cpp \
    ../util/ports.cpp \
    ../util/power_ipc.cpp \
    ../util/powerd.cpp \
    ../util/powerd_core.cpp \
    ../util/powerd_cmd.cpp

LOCAL_SHARED_LIBRARIES += \
    liblog \
    libdl \
    libutils \
    libcutils \
    libhwbinder \
    libhardware \
    libhidlbase \
    libhidltransport \
    android.hardware.power@1.0 \
    android.hardware.power@1.1 \
    android.hardware.power@1.2 \
    android.hardware.power@1.3 \
    vendor.mediatek.hardware.power@2.0 \
    vendor.mediatek.hardware.power@2.1 \
    vendor.mediatek.hardware.mtkpower@1.0

LOCAL_MODULE := vendor.mediatek.hardware.mtkpower@1.0-service
LOCAL_INIT_RC += \
    vendor.mediatek.hardware.mtkpower@1.0-service.rc \
    vendor.mediatek.hardware.mtkpower@1.0-init.rc
LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_VENDOR_MODULE := true
LOCAL_MODULE_OWNER := mtk

include $(BUILD_EXECUTABLE)
