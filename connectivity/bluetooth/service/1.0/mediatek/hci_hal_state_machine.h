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

#pragma once

#if defined(MTK_BT_HAL_STATE_MACHINE) && (TRUE == MTK_BT_HAL_STATE_MACHINE)

#include <android/hardware/bluetooth/1.0/IBluetoothHciCallbacks.h>
#include <utils/StrongPointer.h>

#include <functional>
#include <memory>

#include "mtk_util.h"

namespace vendor {
namespace mediatek {
namespace bluetooth {
namespace hal {

enum BtHalStateMessage {
  kIdleMsg = 0,
  kOnMsg = 1,
  kOffMsg = 2,
};

class VendorStateObserver {
  public:
   virtual ~VendorStateObserver() = default;

   virtual void OnStateChanged(BtHalStateMessage state_msg) = 0;
};

using ::android::hardware::bluetooth::V1_0::IBluetoothHciCallbacks;
class VendorStateController {
 public:
  virtual ~VendorStateController() = default;

  virtual void InitHciCallbacks(
      const ::android::sp<IBluetoothHciCallbacks>& cb) = 0;
  virtual void TurnOn() const = 0;
  virtual void TurnOff() const = 0;
};

class StateMachineImpl;
class StateMachine : public Singleton<StateMachine> {
 public:
  ~StateMachine();

  int Start();
  void Stop();

  void InitHciCallbacks(
         const ::android::sp<IBluetoothHciCallbacks>& cb);

  // Off state is responsible to free controller
  void Transit(BtHalStateMessage state);

  /* Observe BT HAL state change, mainly for UT test right now */
  void AddObserver(VendorStateObserver* ob);
  void RemoveObserver(VendorStateObserver* ob);
  void Reset();
  /* Observe BT HAL state change, mainly for UT test right now */

  // To expose to receive controller from the external, mainly for UTTest
  void UpdateVendorController(VendorStateController* controller);

 private:
  StateMachine();

  friend class Singleton<StateMachine>;

  std::unique_ptr<StateMachineImpl> sm_impl_;
};

}  // namespace hal
}  // namespace bluetooth
}  // namespace mediatek
}  // namespace vendor

#endif
