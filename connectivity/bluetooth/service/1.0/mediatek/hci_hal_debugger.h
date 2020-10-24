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

#if defined(MTK_BT_HAL_DEBUG) && (TRUE == MTK_BT_HAL_DEBUG)

#define MTK_BT_HAL_H4_DEBUG TRUE

#include <stdint.h>

#include <iomanip>
#include <memory>
#include <sstream>
#include <string>

#include "bt_vendor_lib.h"
#include "mtk_util.h"

enum FirmwareAssertReason {
  kUnknownError = 30,
  kCommandTimedout = 31,
  kInvalidEventData = 32,
};

namespace vendor {
namespace mediatek {
namespace bluetooth {
namespace hal {

template <typename T>
std::string DataArrayToString(const T* arr, size_t array_len) {
  std::stringstream ss;
  int temp(0);
  for (size_t i(0); i < array_len; i++) {
    temp = static_cast<int>(arr[i]);
    ss << " " << std::uppercase << std::setfill('0') << std::hex << std::setw(2)
       << temp;
  }
  return ss.str();
}

enum PacketDirectionType {
  kTx,
  kRx,
};

std::string PacketDirTypeToString(PacketDirectionType type);

class BtHciDebuggerImpl;
class BtHciDebugger : public Singleton<BtHciDebugger> {
 public:
  ~BtHciDebugger();

  void Archive(PacketDirectionType dir_type,
      uint8_t type,
      const uint8_t* data,
      uint16_t data_length);
  void OnNotify() const;
  void RefreshHalDebugState();
  void Dump(PacketDirectionType pkt_dir,
      uint8_t type, const uint8_t* data, size_t length) const;

  void RefreshVendorInterface(const bt_vendor_interface_t *interface);
  bool TriggerFirmwareAssert(int reason);

 private:
  BtHciDebugger();

  friend class Singleton<BtHciDebugger>;

  std::unique_ptr<BtHciDebuggerImpl> debugger_impl_;
};

class BtHciDebugBulletinImpl;
class BtHciDebugBulletin : public Singleton<BtHciDebugBulletin> {
  public:
   ~BtHciDebugBulletin();

   void Check(PacketDirectionType dir_type, const uint8_t* data) const;
   void AddObserver(const BtHciDebugger* ob);

  private:
   BtHciDebugBulletin();

   friend class Singleton<BtHciDebugBulletin>;

   std::unique_ptr<BtHciDebugBulletinImpl> bulletin_impl_;
};

}  // namespace hal
}  // namespace bluetooth
}  // namespace mediatek
}  // namespace vendor

#endif
