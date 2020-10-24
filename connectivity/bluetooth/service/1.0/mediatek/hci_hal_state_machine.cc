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

#if defined(MTK_BT_HAL_STATE_MACHINE) && (TRUE == MTK_BT_HAL_STATE_MACHINE)

#define LOG_TAG "mtk.hal.bt-state-machine"

#include "hci_hal_state_machine.h"

#include <android/hardware/bluetooth/1.0/IBluetoothHci.h>
#include <log/log.h>
#include <utils/Looper.h>

#include <list>
#include <string>
#include <vector>

#include "hci_hal_msg_handler.h"
#include "vendor_interface.h"

namespace vendor {
namespace mediatek {
namespace bluetooth {
namespace hal {

using android::hardware::bluetooth::V1_0::implementation::VendorInterface;
using android::hardware::bluetooth::V1_0::Status;
using android::hardware::hidl_vec;
using android::Message;
using android::MessageHandler;
using android::sp;

class MtkStateController : public VendorStateController {
  public:
   MtkStateController()
     : cb_(nullptr) {}
   virtual ~MtkStateController();

   void InitHciCallbacks(
       const ::android::sp<IBluetoothHciCallbacks>& cb) override {
     cb_ = cb;
   }
   void TurnOn() const override;
   void TurnOff() const override;

  private:
   ::android::sp<IBluetoothHciCallbacks> cb_;
};

MtkStateController::~MtkStateController() {}

void MtkStateController::TurnOn() const {
  bool rc = VendorInterface::Initialize(
      [this](bool status) {
        auto hidl_status = cb_->initializationComplete(
            status ? Status::SUCCESS : Status::INITIALIZATION_ERROR);
        if (!hidl_status.isOk()) {
          ALOGE("VendorInterface -> Unable to call initializationComplete()");
        }
      },
      [this](const hidl_vec<uint8_t>& packet) {
        auto hidl_status = cb_->hciEventReceived(packet);
        if (!hidl_status.isOk()) {
          ALOGE("VendorInterface -> Unable to call hciEventReceived()");
        }
      },
      [this](const hidl_vec<uint8_t>& packet) {
        auto hidl_status = cb_->aclDataReceived(packet);
        if (!hidl_status.isOk()) {
          ALOGE("VendorInterface -> Unable to call aclDataReceived()");
        }
      },
      [this](const hidl_vec<uint8_t>& packet) {
        auto hidl_status = cb_->scoDataReceived(packet);
        if (!hidl_status.isOk()) {
          ALOGE("VendorInterface -> Unable to call scoDataReceived()");
        }
      });
  if (!rc) {
    auto hidl_status = cb_->initializationComplete(Status::INITIALIZATION_ERROR);
    if (!hidl_status.isOk()) {
      ALOGE("VendorInterface -> Unable to call initializationComplete(ERR)");
    }
  }
}

void MtkStateController::TurnOff() const {
  VendorInterface::Shutdown();
}

class Request {
  public:
   explicit Request(BtHalStateMessage request_state,
       const VendorStateController* controller)
     : request_state_(request_state), controller_(controller) {}

  void On() {
    if (controller_) {
      controller_->TurnOn();
    }
  }

  void Off() {
    if (controller_) {
      controller_->TurnOff();
    }
  }

  BtHalStateMessage request_state() const {
    return request_state_;
  }

  private:
   BtHalStateMessage request_state_;
   const VendorStateController* controller_;
};

class State {
 public:
  State() = default;
  virtual ~State() = default;

  virtual bool Handle(Request& request) const = 0;
  virtual BtHalStateMessage GetStateMsg() const = 0;

  static std::string StateMsgToStr(BtHalStateMessage state) {
    switch (state) {
    case kIdleMsg: return std::string("Idle");
    case kOnMsg: return std::string("On");
    case kOffMsg: return std::string("Off");
    default: return std::string("Unknown");
    }
  }
};

class IdleState : public State {
 public:
  IdleState() = default;
  virtual ~IdleState() = default;

  // Be able to handle kOnMsg ONLY
  virtual bool Handle(Request& request) const override {
    bool done(false);
    if (kOnMsg == request.request_state()) {
      request.On();
      done = true;
    } else {
      ALOGW("%s: ignore invalid request: %s",
          __func__, StateMsgToStr(request.request_state()).c_str());
    }
    return done;
  }

  BtHalStateMessage GetStateMsg() const override {
    return kIdleMsg;
  }
};

class OnState : public State {
 public:
  OnState() = default;
  virtual ~OnState() = default;

  virtual bool Handle(Request& request) const override {
    bool done(false);
    if (kOffMsg == request.request_state()) {
      request.Off();
      done = true;
    } else if (kOnMsg == request.request_state()) {
      // It is double on case, apply error handling off -> on
      request.Off();
      request.On();
      done = true;
    } else {
      ALOGW("%s: ignore invalid request: %s",
          __func__, StateMsgToStr(request.request_state()).c_str());
    }
    return done;
  }

  BtHalStateMessage GetStateMsg() const override {
    return kOnMsg;
  }
};

class OffState : public State {
 public:
  OffState() = default;
  virtual ~OffState() = default;

  virtual bool Handle(Request& request) const override {
    bool done(false);
    if (kOnMsg == request.request_state()) {
      request.On();
      done = true;
    } else {
      // It is double off case, ignore the extra off request will be okay
      ALOGW("%s: ignore invalid request: %s",
          __func__, StateMsgToStr(request.request_state()).c_str());
    }
    return done;
  }

  BtHalStateMessage GetStateMsg() const override {
    return kOffMsg;
  }
};

class StateMessageHanlder : public MessageHandler {
  public:
   explicit StateMessageHanlder(const VendorStateController* controller)
     : controller_(controller) {
     LOG_ALWAYS_FATAL_IF(!controller, "%s: invalid controller!", __func__);
     SetupStates();
     current_state_ = states_[kIdleMsg].get();
   }

   void set_controller(const VendorStateController* controller) {
     LOG_ALWAYS_FATAL_IF(!controller, "%s: invalid controller!", __func__);
     controller_ = controller;
   }

   virtual void handleMessage(const Message& message) override {
     LOG_ALWAYS_FATAL_IF(!current_state_, "%s: invalid state_!", __func__);
     Request request = Request(
         static_cast<BtHalStateMessage>(message.what), controller_);
     if (current_state_->Handle(request)) {
       // transact to new state
       current_state_ = states_[message.what].get();
       NotifyStateChanged(current_state_->GetStateMsg());
       ALOGW("%s: transact to new state: %s",
           __func__, State::StateMsgToStr(request.request_state()).c_str());
     }
   }

   void AddObserver(VendorStateObserver* ob) {
     observers_.push_back(ob);
   }

   void RemoveObserver(VendorStateObserver* ob) {
     observers_.remove(ob);
   }

   void Reset() {
     ALOGW("%s: reset state to: %s",
         __func__, State::StateMsgToStr(kIdleMsg).c_str());
     current_state_ = states_[kIdleMsg].get();
   }

  private:
   void SetupStates() {
     // kIdleMsg = 0
     states_.emplace_back(new IdleState());
     // kOnMsg = 1
     states_.emplace_back(new OnState());
     // kOffMsg = 2
     states_.emplace_back(new OffState());
   }

   void NotifyStateChanged(BtHalStateMessage state_msg) {
     for (const auto it : observers_) {
       if (it) {
         it->OnStateChanged(state_msg);
       }
     }
   }

   const VendorStateController* controller_;
   const State* current_state_;
   std::vector<std::unique_ptr<State>> states_;
   std::list<VendorStateObserver*> observers_;
};

class StateMachineImpl {
 public:
  explicit StateMachineImpl()
    : default_controler_(new MtkStateController()),
      vendor_controller_(default_controler_.get()),
      msg_handler_(new StateMessageHanlder(vendor_controller_)) {}
  ~StateMachineImpl() {
    if (default_controler_) {
      default_controler_.reset();
      default_controler_ = nullptr;
    }
  }

  int Start() {
    return msg_looper_.StartMessageLooper(std::string("bt_hal_msg_handler"));
  }

  void Stop() {
    msg_looper_.StopMessageLooper();
  }

  void InitHciCallbacks(
           const ::android::sp<IBluetoothHciCallbacks>& cb) {
    LOG_ALWAYS_FATAL_IF(!vendor_controller_, "%s: invalid controller!", __func__);
    vendor_controller_->InitHciCallbacks(cb);
  }

  void Transit(BtHalStateMessage state) {
    msg_looper_.EnqueueMessage(msg_handler_, Message(state));
  }

  void AddObserver(VendorStateObserver* ob) {
    msg_handler_->AddObserver(ob);
  }

  void RemoveObserver(VendorStateObserver* ob) {
    msg_handler_->RemoveObserver(ob);
  }

  void Reset() {
    msg_handler_->Reset();
  }

  void UpdateController(VendorStateController* controller) {
    LOG_ALWAYS_FATAL_IF(!controller, "%s: invalid controller!", __func__);
    vendor_controller_ = controller;
    msg_handler_->set_controller(controller);
  }

 private:
  BtHalMessageLooper msg_looper_;
  std::unique_ptr<VendorStateController> default_controler_;
  VendorStateController* vendor_controller_;
  sp<StateMessageHanlder> msg_handler_;
};

StateMachine::StateMachine()
    : sm_impl_(new StateMachineImpl()) {}

StateMachine::~StateMachine() {
  if (sm_impl_) {
    sm_impl_->Stop();
    sm_impl_.reset();
    sm_impl_ = nullptr;
  }
}

void StateMachine::UpdateVendorController(VendorStateController* controller) {
  sm_impl_->UpdateController(controller);
}

int StateMachine::Start() {
  return sm_impl_->Start();
}

void StateMachine::Stop() {
  sm_impl_->Stop();
}

void StateMachine::InitHciCallbacks(
       const ::android::sp<IBluetoothHciCallbacks>& cb) {
  sm_impl_->InitHciCallbacks(cb);
}

void StateMachine::Transit(BtHalStateMessage state) {
  sm_impl_->Transit(state);
}

void StateMachine::AddObserver(VendorStateObserver* ob) {
  sm_impl_->AddObserver(ob);
}

void StateMachine::RemoveObserver(VendorStateObserver* ob) {
  sm_impl_->RemoveObserver(ob);
}

void StateMachine::Reset() {
  sm_impl_->Reset();
}

}  // namespace hal
}  // namespace bluetooth
}  // namespace mediatek
}  // namespace vendor

#endif
