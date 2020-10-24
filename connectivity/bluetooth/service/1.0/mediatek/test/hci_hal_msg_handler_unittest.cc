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

#define LOG_TAG "mtk.hal.bt-msg-handler-unittest"

#include <chrono>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <log/log.h>
#include <utils/Looper.h>

#include "hci_hal_msg_handler.h"
#include "mtk_util.h"
#include "TestHelpers.h"

using ::android::DelayedTask;
using ::android::Message;
using ::android::MessageHandler;
using ::android::sp;

using ::testing::InSequence;

namespace {

enum BtTestHanlderMsg {
  kOnMsg = 0,
  kOnAgainMsg = 1,
  kOffMsg = 2,
  kOffAgainMsg = 3,
};

using vendor::mediatek::bluetooth::hal::BtHalMessageLooper;

class DelayedSender : public DelayedTask {
  public:
   DelayedSender(int delay_millis,
       BtHalMessageLooper* looper,
       const android::sp<android::MessageHandler>& handler,
       BtTestHanlderMsg msg)
     : DelayedTask(delay_millis),
       looper_(looper),
       handler_(handler),
       msg_(msg) {}

   void doTask() override {
     looper_->EnqueueMessage(handler_, Message(msg_));
     ALOGI("%s: sent %d", __func__, msg_);
   }

   const BtHalMessageLooper* looper_;
   const android::sp<android::MessageHandler>& handler_;
   BtTestHanlderMsg msg_;

  private:
   DelayedSender(const DelayedSender&);
   DelayedSender& operator = (const DelayedSender&);
};

class MockBtMessageHandler : public MessageHandler {
 public:
  MOCK_METHOD1(handleMessage, void(const Message& message));
};

MATCHER_P(MsgHandlerMatcher, msg, "") {
  return (msg == static_cast<BtTestHanlderMsg>(arg.what));
}

}  // anonymous namespace

namespace vendor {
namespace mediatek {
namespace bluetooth {
namespace hal {

class HciHalMsgHandlerTest : public ::testing::Test {
 protected:
  void SetUp() override {
    ALOGI("%s: HciHalMsgHandlerTest", __func__);
    mock_handler_ = new MockBtMessageHandler();
    bt_hal_msg_looper_  = std::unique_ptr<BtHalMessageLooper>(
        new BtHalMessageLooper());
    bt_hal_msg_looper_->StartMessageLooper(std::string("TestLooperThread"));
    // Need to wait for while for looper thread being started
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  void TearDown() override {
    ALOGI("%s: HciHalMsgHandlerTest", __func__);
    bt_hal_msg_looper_->StopMessageLooper();
    mock_handler_.clear();
  }

  std::unique_ptr<BtHalMessageLooper> bt_hal_msg_looper_;
  sp<MockBtMessageHandler> mock_handler_;
};

TEST_F(HciHalMsgHandlerTest, BasicOnOff) {
  EXPECT_CALL(*(mock_handler_), handleMessage(MsgHandlerMatcher(kOffMsg)))
          .Times(1);
  EXPECT_CALL(*(mock_handler_), handleMessage(MsgHandlerMatcher(kOnMsg)))
          .Times(1);
  bt_hal_msg_looper_->EnqueueMessage(mock_handler_, Message(kOnMsg));
  bt_hal_msg_looper_->EnqueueMessage(mock_handler_, Message(kOffMsg));
}

TEST_F(HciHalMsgHandlerTest, ThreadingTaskOnOff) {
  const BtTestHanlderMsg kMsgs[] = {kOnMsg, kOnAgainMsg, kOffMsg, kOffAgainMsg,};
  const size_t kMsgsSize = array_length(kMsgs);

  {
    InSequence s;
    for (size_t i(0); i < kMsgsSize; i++) {
      EXPECT_CALL(*(mock_handler_), handleMessage(MsgHandlerMatcher(kMsgs[i])))
              .Times(1);
    }
  }

  std::vector<sp<DelayedSender>> senders;
  for (size_t i(0); i < kMsgsSize; i++) {
    senders.emplace_back(
        new DelayedSender((i + 1) *100,
            bt_hal_msg_looper_.get(), mock_handler_, kMsgs[i])
    );
    // Thread name must be constant string
    senders[i]->run("sender");
  }
  ALOGI("%s: start threads to run tasks", __func__);

  for (auto& sender : senders) {
    sender->join();
  }
  ALOGI("%s: ThreadingTaskOnOff exited", __func__);
}

}  // namespace hal
}  // namespace bluetooth
}  // namespace mediatek
}  // namespace vendor

#endif
