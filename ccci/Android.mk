LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

ifdef MTK_MD_SBP_CUSTOM_VALUE
ifneq ($(MTK_MD_SBP_CUSTOM_VALUE), "")
LOCAL_CFLAGS += -DMD_SBP_CUSTOM_VALUE=$(subst ",,$(MTK_MD_SBP_CUSTOM_VALUE))
endif
endif

ifdef MTK_MD2_SBP_CUSTOM_VALUE
ifneq ($(MTK_MD2_SBP_CUSTOM_VALUE), "")
LOCAL_CFLAGS += -DMD2_SBP_CUSTOM_VALUE=$(subst ",,$(MTK_MD2_SBP_CUSTOM_VALUE))
endif
endif

LOCAL_CFLAGS += -DMTK_ECCCI_C2K

LOCAL_SRC_FILES := ccci_lib.c

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/include \
	$(LOCAL_PATH)/platform

LOCAL_EXPORT_C_INCLUDE_DIRS := \
	$(LOCAL_PATH)/include \

LOCAL_MODULE := libccci_util
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_MODULE_TAGS := optional
include $(call all-makefiles-under,$(LOCAL_PATH))
include $(BUILD_SHARED_LIBRARY)
