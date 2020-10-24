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

#include <sys/syscall.h>
#include <unistd.h>

#include <memory>
#include <mutex>

#include <android-base/macros.h>

namespace vendor {
namespace mediatek {
namespace bluetooth {
namespace hal {

// Thanks to Jiang Bian jbian@uams.edu
// The Singleton design refers to https://gist.github.com/bianjiang/5846512
template <typename T>
class Singleton {
 public:
  template <typename... Args>
  static T* GetInstance(Args&&... args) {
    std::call_once(GetOnceFlag(), [](Args&&... args) {
      instance_.reset(new T(std::forward<Args>(args)...));
    }, std::forward<Args>(args)...);
    return instance_.get();
  }

 protected:
  Singleton<T>() {}
  ~Singleton<T>() {}

 private:
  static std::once_flag& GetOnceFlag() {
    static std::once_flag oncecall_;
    return oncecall_;
  }

  static std::unique_ptr<T> instance_;

  DISALLOW_COPY_AND_ASSIGN(Singleton);
};

template <typename T>
std::unique_ptr<T> Singleton<T>::instance_ = nullptr;

#if __GLIBC__
pid_t gettid() {
  return syscall(SYS_gettid);
}
#endif

template <typename T, size_t N>
size_t array_length(T (&)[N]) {
  return N;
}

}  // namespace hal
}  // namespace bluetooth
}  // namespace mediatek
}  // namespace vendor
