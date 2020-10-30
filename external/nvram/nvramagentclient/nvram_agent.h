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

#include <utils/KeyedVector.h>
#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <utils/String16.h>
#include <utils/threads.h>

#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <log/log.h>

#include<sys/mount.h>
//#include "../../../external/mediatek/meta/include/FT_Public.h"
//#include "../../../external/mediatek/meta/include/WM2Linux.h"
//#include "../../../../kernel/include/mtd/mtd-abi.h"
//#include "../../../../kernel/include/mtd/mtd-abi.h"
#include <mtd/mtd-abi.h>
//#include "../../../mediatek/source/external/nvram/libfile_op/libfile_op.h"

#include <cutils/atomic.h>
#include <utils/Errors.h>
#include <binder/IServiceManager.h>
#include <utils/String16.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <utils/Vector.h>
#include "libnvram.h"
#include "libnvram_log.h"
using namespace android;
enum {
	TRANSACTION_readFile = IBinder::FIRST_CALL_TRANSACTION,
	TRANSACTION_writeFile,
	TRANSACTION_readFileByName,
	TRANSACTION_writeFileByName,
	TRANSACTION_getFileDesSize,
	TRANSACTION_writeFileEx,
};

class INvRAMAgent: public IInterface {
  public:
	DECLARE_META_INTERFACE(NvRAMAgent)
	virtual char* readFile(int file_lid, int & size) = 0;
	virtual int writeFile(int file_lid, int size, char *buff) = 0;
	virtual char* readFileByName(char* file_name, int & size) = 0;
	virtual int writeFileByName(char*  file_name, int size, char *buff) = 0;
	virtual int getFileDesSize(int file_lid, int & recSize, int & recNum) = 0;
	virtual int writeFileEx(int file_lid, int rec_no, int size, char *buff) = 0;
};

class BpNvRAMAgent: public android::BpInterface<INvRAMAgent> {
  public:
	BpNvRAMAgent(const android::sp<android::IBinder>& impl)
		: android::BpInterface<INvRAMAgent>(impl) {
	}
	char* readFile(int file_lid, int & size) {
		Parcel data, reply;
		data.writeInterfaceToken(INvRAMAgent::getInterfaceDescriptor());
		data.writeInt32(file_lid);
		if (remote()->transact(TRANSACTION_readFile, data, &reply)) {
			NVRAM_LOG("remote->transact error\n");
		}
		int tap = reply.readInt32();
		if (tap < 0) {
			NVRAM_LOG("Read Error,file_lid = %d\n", file_lid);
			return NULL;
		}
		size = reply.readInt32();
		char *buf = NULL;
		if (size > 0) {
			buf = (char *) malloc(sizeof(char) * size);
			if (!buf) {
				NVRAM_LOG("Malloc Error in readFile(),file_lid = %d\n", file_lid);
				return NULL;
			}
			reply.read(buf, size);
		}
		return buf;
	}
	int writeFile(int file_lid, int size, char *buff) {
		Parcel data, reply;
		data.writeInterfaceToken(INvRAMAgent::getInterfaceDescriptor());
		data.writeInt32(file_lid);
		data.writeInt32(size);
		data.write(buff, size);
		if (remote()->transact(TRANSACTION_writeFile, data, &reply)) {
			NVRAM_LOG("remote->transact error\n");
		}

		int ret = reply.readInt32();
		if (ret < 0) {
			NVRAM_LOG("writeFile Error,file_lid = %d\n", file_lid);
			return 0;
		}

		return reply.readInt32();
	}

	int writeFileEx(int file_lid, int rec_no, int size, char *buff) {
		Parcel data, reply;
		data.writeInterfaceToken(INvRAMAgent::getInterfaceDescriptor());
		data.writeInt32(file_lid);
		data.writeInt32(rec_no);
		data.writeInt32(size);
		data.write(buff, size);
		if (remote()->transact(TRANSACTION_writeFileEx, data, &reply)) {
			NVRAM_LOG("remote->transact error\n");
		}

		int ret = reply.readInt32();
		if (ret < 0) {
			NVRAM_LOG("writeFile Error,file_lid = %d\n", file_lid);
			return 0;
		}

		return reply.readInt32();
	}
	char* readFileByName(char*  file_name, int & size) {
		return 0;
	}
	int writeFileByName(char*  file_name, int size, char *buff) {
		return 1;
	}
	int getFileDesSize(int file_lid, int & recSize, int & recNum) {
		Parcel data, reply;
		data.writeInterfaceToken(INvRAMAgent::getInterfaceDescriptor());
		data.writeInt32(file_lid);
		if (remote()->transact(TRANSACTION_getFileDesSize, data, &reply)) {
			NVRAM_LOG("remote()->transact error \n");
		}
		int ret = reply.readInt32();
		if (ret < 0) {
			NVRAM_LOG("getFileDesSize Error,file_lid = %d\n", file_lid);
			return 0;
		}

		recSize = reply.readInt32();
		recNum = reply.readInt32();

		return 1;
	}
};

class BnNvRAMAgent : public BnInterface<INvRAMAgent> {
  public:
	status_t onTransact(uint32_t code,
	                    const Parcel &data,
	                    Parcel *reply,
	                    uint32_t flags);

};

class NvRAMAgent : public BnNvRAMAgent {

  public:
	static  void instantiate();
	NvRAMAgent();
	~NvRAMAgent() {}
	virtual char* readFile(int file_lid, int & size);
	virtual int writeFile(int file_lid, int size, char *buff);
	virtual char* readFileByName(char*  file_name, int & size);
	virtual int writeFileByName(char*  file_name, int size, char *buff);
	virtual int getFileDesSize(int file_lid, int & recSize, int & recNum);

	virtual int writeFileEx(int file_lid, int rec_no, int size, char *buff);
};


IMPLEMENT_META_INTERFACE(NvRAMAgent, "NvRAMAgent")

