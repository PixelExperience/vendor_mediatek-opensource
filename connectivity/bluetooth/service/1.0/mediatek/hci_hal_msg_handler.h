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

#include <atomic>
#include <string>
#include <thread>

#include <utils/Looper.h>

namespace vendor {
namespace mediatek {
namespace bluetooth {
namespace hal {

class BtHalMessageLooper {
 public:
  BtHalMessageLooper();
  ~BtHalMessageLooper() = default;

  int StartMessageLooper(const std::string& thread_name);
  void StopMessageLooper();
  void EnqueueMessage(const android::sp<android::MessageHandler>& handler,
      const android::Message& message) const;

 private:
  int StartThread(const std::string& thread_name);
  int StopThread();
  inline void RunLooper(void);
  void ThreadRoutine(const std::string& thread_name);

  std::thread thread_;
  android::sp<android::Looper> looper_;
  int event_fd_;
  std::atomic_bool running_{false};
};

}  // namespace hal
}  // namespace bluetooth
}  // namespace mediatek
}  // namespace vendor

#endif
