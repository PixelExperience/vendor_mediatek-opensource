LOCAL_PATH := $(call my-dir)

ifneq ($(wildcard $(LOCAL_PATH)/$(shell echo $(MTK_PLATFORM) | tr A-Z a-z)),)

include $(LOCAL_PATH)/$(shell echo $(MTK_PLATFORM) | tr A-Z a-z)/Android.mk

endif
