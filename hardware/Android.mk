MTK_HARD_ROOT_PATH := $(call my-dir)

# MTK Audio
include $(MTK_HARD_ROOT_PATH)/audio/common/service/5.0/Android.mk
include $(MTK_HARD_ROOT_PATH)/audio/common/client/Android.mk

# MTK Power
include $(MTK_HARD_ROOT_PATH)/power/Android.mk
include $(MTK_HARD_ROOT_PATH)/power_util/mtkperf_client/Android.mk
include $(MTK_HARD_ROOT_PATH)/power_util/powerhalwrap_v_2_0/Android.mk
