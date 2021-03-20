#
# Copyright (C) 2020 The PixelExperience Project
#
# SPDX-License-Identifier: Apache-2.0
#

# Call Interfaces (vendor)
$(call inherit-product, vendor/mediatek/opensource/mtk-interfaces.mk)

# Call ProjectConfig For Begonia
$(call inherit-product, vendor/mediatek/opensource/BegoniaConfig.mk)

# External
PRODUCT_PACKAGES += \
    libladder \
    libudf \
    libmtkaudio_utils \

# hardware
PRODUCT_PACKAGES += \
    fstb.cfg \
    libpowerhal \
    power.$(TARGET_BOARD_PLATFORM) \
    power.default \
    powerscntbl.xml \
    libmtkperf_client \
    powercontable.xml \
    libmtkaudio_utils \
    libpowerhalwrap_vendor \
    power_whitelist_cfg.xml \
    power_legacy_test_v_1_0 \
    power_native_test_v_1_0 \
    libmtkperf_client_vendor \
    libaudioprimarydevicehalifclient \
    vendor.mediatek.hardware.power@2.1-impl \
    android.hardware.audio@5.0-impl-mediatek \
    android.hardware.power@1.3-impl-mediatek \
    vendor.mediatek.hardware.mtkpower@1.0-impl \
    android.hardware.audio@5.0-service-mediatek \
    vendor.mediatek.hardware.mtkpower@1.0-service
