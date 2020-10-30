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

#ifndef __NVRAM_AGENT_CLIENT_H__
#define __NVRAM_AGENT_CLIENT_H__

#include <binder/IMemory.h>
#include <utils/threads.h>
#include <binder/IInterface.h>
#include <utils/RefBase.h>
#include <binder/Parcel.h>
#include <nvram_agent.h>

using namespace android;

class NvRAMAgentClient {
  private:
	class DeathNotifier: public IBinder::DeathRecipient {
	  public:
		DeathNotifier();
		virtual ~DeathNotifier();
		virtual void binderDied(const wp<IBinder>& who);
	};

	NvRAMAgentClient();
	static Mutex sMutex;
	static sp<DeathNotifier> sDeathNotifier;
	static sp<INvRAMAgent> sNvRAMAgentService;
	static const sp<INvRAMAgent>& getNvRAMAgentService();

  public:
	static NvRAMAgentClient* create();
	char* readFile(int file_lid, int & size);
	int writeFile(int file_lid, int size, char *buff);
	char* readFileByName(char* file_name, int & size);
	int writeFileByName(char* file_name, int size, char *buff);
	int getFileDesSize(int file_lid, int & recSize, int & recNum);

	int writeFileEx(int file_lid, int rec_no, int size, char *buff);
	~NvRAMAgentClient();
};

#endif
