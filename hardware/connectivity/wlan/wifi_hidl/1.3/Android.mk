LOCAL_PATH := $(call my-dir)

###
### android.hardware.wifi static library
###
include $(CLEAR_VARS)
LOCAL_MODULE := android.hardware.wifi@1.0-service-lib-mediatek
LOCAL_MODULE_OWNER := mtk
LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_PROPRIETARY_MODULE := true
LOCAL_CPPFLAGS := -Wall -Werror -Wextra
ifdef WIFI_HAL_INTERFACE_COMBINATIONS
LOCAL_CPPFLAGS += -DWIFI_HAL_INTERFACE_COMBINATIONS="$(WIFI_HAL_INTERFACE_COMBINATIONS)"
endif
ifdef WIFI_HIDL_FEATURE_AWARE
LOCAL_CPPFLAGS += -DWIFI_HIDL_FEATURE_AWARE
endif
ifdef WIFI_HIDL_FEATURE_DUAL_INTERFACE
LOCAL_CPPFLAGS += -DWIFI_HIDL_FEATURE_DUAL_INTERFACE
endif
ifdef WIFI_HIDL_FEATURE_DISABLE_AP
LOCAL_CPPFLAGS += -DWIFI_HIDL_FEATURE_DISABLE_AP
endif
ifdef WIFI_HIDL_FEATURE_DISABLE_AP_MAC_RANDOMIZATION
LOCAL_CPPFLAGS += -DWIFI_HIDL_FEATURE_DISABLE_AP_MAC_RANDOMIZATION
endif

# Allow implicit fallthroughs in wifi_legacy_hal.cpp until they are fixed.
LOCAL_CFLAGS += -Wno-error=implicit-fallthrough
LOCAL_CFLAGS += -DPLATFORM_VERSION=$(PLATFORM_VERSION)

LOCAL_SRC_FILES := \
    hidl_struct_util.cpp \
    hidl_sync_util.cpp \
    ringbuffer.cpp \
    wifi.cpp \
    wifi_ap_iface.cpp \
    wifi_chip.cpp \
    wifi_feature_flags.cpp \
    wifi_iface_util.cpp \
    wifi_legacy_hal.cpp \
    wifi_legacy_hal_stubs.cpp \
    wifi_mode_controller.cpp \
    wifi_nan_iface.cpp \
    wifi_p2p_iface.cpp \
    wifi_rtt_controller.cpp \
    wifi_sta_iface.cpp \
    wifi_status_util.cpp

LOCAL_SHARED_LIBRARIES := \
    libbase \
    libcutils \
    libhidlbase \
    libhidltransport \
    liblog \
    libnl \
    libutils \
    libwifi-hal \
    libwifi-system-iface \
    android.hardware.wifi@1.0 \
    android.hardware.wifi@1.1 \
    android.hardware.wifi@1.2 \
    android.hardware.wifi@1.3
LOCAL_EXPORT_C_INCLUDE_DIRS := $(LOCAL_PATH)
include $(BUILD_STATIC_LIBRARY)

###
### android.hardware.wifi daemon
###
include $(CLEAR_VARS)
LOCAL_MODULE := android.hardware.wifi@1.0-service-mediatek
LOCAL_VINTF_FRAGMENTS := android.hardware.wifi@1.0-service-mediatek.xml
LOCAL_MODULE_OWNER := mtk
LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_PROPRIETARY_MODULE := true
LOCAL_CPPFLAGS := -Wall -Werror -Wextra
LOCAL_CFLAGS += -DPLATFORM_VERSION=$(PLATFORM_VERSION)
LOCAL_SRC_FILES := \
    service.cpp
LOCAL_SHARED_LIBRARIES := \
    libbase \
    libcutils \
    libhidlbase \
    libhidltransport \
    liblog \
    libnl \
    libutils \
    libwifi-hal \
    libwifi-system-iface \
    android.hardware.wifi@1.0 \
    android.hardware.wifi@1.1 \
    android.hardware.wifi@1.2 \
    android.hardware.wifi@1.3
LOCAL_STATIC_LIBRARIES := \
    android.hardware.wifi@1.0-service-lib-mediatek
LOCAL_INIT_RC := android.hardware.wifi@1.0-service-mediatek.rc
include $(BUILD_EXECUTABLE)

###
### android.hardware.wifi daemon
###
include $(CLEAR_VARS)
LOCAL_MODULE := android.hardware.wifi@1.0-service-lazy-mediatek
LOCAL_VINTF_FRAGMENTS := android.hardware.wifi@1.0-service-mediatek.xml
LOCAL_MODULE_OWNER := mtk
LOCAL_OVERRIDES_MODULES := android.hardware.wifi@1.0-service-mediatek
LOCAL_CFLAGS := -DLAZY_SERVICE
LOCAL_CFLAGS += -DPLATFORM_VERSION=$(PLATFORM_VERSION)
LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_PROPRIETARY_MODULE := true
LOCAL_CPPFLAGS := -Wall -Werror -Wextra
LOCAL_SRC_FILES := \
    service.cpp
LOCAL_SHARED_LIBRARIES := \
    libbase \
    libcutils \
    libhidlbase \
    libhidltransport \
    liblog \
    libnl \
    libutils \
    libwifi-hal \
    libwifi-system-iface \
    android.hardware.wifi@1.0 \
    android.hardware.wifi@1.1 \
    android.hardware.wifi@1.2 \
    android.hardware.wifi@1.3
LOCAL_STATIC_LIBRARIES := \
    android.hardware.wifi@1.0-service-lib-mediatek
LOCAL_INIT_RC := android.hardware.wifi@1.0-service-lazy-mediatek.rc
include $(BUILD_EXECUTABLE)