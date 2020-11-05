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

#ifndef __CORRECTHWROTATION_H__
#define __CORRECTHWROTATION_H__

#include "CorrectHwRotationAPI.h"
// ----------------------------------------------------------------------------
namespace android {

// ----------------------------------------------------------------------------
class CorrectHwRotation : public CorrectHwRotationAPI {
public:
    CorrectHwRotation();
    ~CorrectHwRotation();
    int getHwOrient();
    void correctSize(uint32_t* w, uint32_t* h);
    void getCropFlags(uint32_t* flags);
    void correctRotation(uint32_t* rotation);
    status_t correctCaptureSize(uint32_t*      reqWidth,
                                uint32_t*      reqHeight,
                                uint32_t       hw_w,
                                uint32_t       hw_h,
                                const uint32_t rotation);

private:
    int mHwRotation;
    int mHwOrientation;

    void setupPrimaryHwOrientation();
};

class Transform
{
public:
            enum orientation_flags {
                ROT_0   = 0x00000000,
                FLIP_H  = HAL_TRANSFORM_FLIP_H,
                FLIP_V  = HAL_TRANSFORM_FLIP_V,
                ROT_90  = HAL_TRANSFORM_ROT_90,
                ROT_180 = FLIP_H|FLIP_V,
                ROT_270 = ROT_180|ROT_90,
                ROT_INVALID = 0x80
            };
};

}

#endif
