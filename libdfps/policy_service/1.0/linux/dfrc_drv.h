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

#include <linux/ioctl.h>

#ifndef __DFRC_DRV_H__
#define __DFRC_DRV_H__

enum DFRC_DRV_API {
	DFRC_DRV_API_UNKNOWN = -1,
	DFRC_DRV_API_GIFT,
	DFRC_DRV_API_VIDEO,
	DFRC_DRV_API_RRC_TOUCH,
	DFRC_DRV_API_RRC_VIDEO,
	DFRC_DRV_API_THERMAL,
	DFRC_DRV_API_LOADING,
	DFRC_DRV_API_WHITELIST,
	DFRC_DRV_API_MAXIMUM,
};

enum DFRC_DRV_FLAG {
	DFRC_DRV_FLAG_MULTI_WINDOW = 0x01,
};

enum DFRC_DRV_MODE {
	DFRC_DRV_MODE_DEFAULT = 0,
	DFRC_DRV_MODE_FRR,
	DFRC_DRV_MODE_ARR,
	DFRC_DRV_MODE_INTERNAL_SW,
	DFRC_DRV_MODE_MAXIMUM,
};

enum DFRC_DRV_SW_MODE {
	DFRC_DRV_SW_MODE_CALIBRATED_SW = 0,
	DFRC_DRV_SW_MODE_PASS_HW,
	DFRC_DRV_SW_MODE_INTERNAL_SW,
};

enum DFRC_DRV_HW_MODE {
	DFRC_DRV_HW_MODE_DEFAULT = 0,
	DFRC_DRV_HW_MODE_ARR,
};

enum DFRC_DRV_POLICY_FLAG {
	DFRC_DRV_POLICY_FLAG_NONE = 0x00,
	DFRC_DRV_POLICY_FLAG_USE_VIDEO_MODE = 0x01,
};

struct DFRC_DRV_POLICY {
	unsigned long long sequence;
	int api;
	int pid;
	int fps;
	int mode;
	int target_pid;
	unsigned long long gl_context_id;
	int flag;
};

struct DFRC_DRV_HWC_INFO {
	int single_layer;
	int num_display;
};

struct DFRC_DRV_INPUT_WINDOW_INFO {
	int pid;
};

struct DFRC_DRV_VSYNC_REQUEST {
	int fps;
	int mode;
	int sw_fps;
	int sw_mode;
	int valid_info;
	int transient_state;
	int num_policy;
	int forbid_vsync;
};

struct DFRC_DRC_REQUEST_SET {
	int num;
	struct DFRC_DRV_POLICY *policy;
};

struct DFRC_DRV_REFRESH_RANGE {
	int index;
	int min_fps;
	int max_fps;
};

struct DFRC_DRV_PANEL_INFO {
	int support_120;
	int support_90;
	int num;
};

struct DFRC_DRV_WINDOW_STATE {
	int window_flag;
};

struct DFRC_DRV_FOREGROUND_WINDOW_INFO {
	int pid;
};

#define DFRC_IOCTL_MAGIC 'd'

#define DFRC_IOCTL_CMD_REG_POLICY \
	_IOWR(DFRC_IOCTL_MAGIC, 1000, struct DFRC_DRV_POLICY)
#define DFRC_IOCTL_CMD_SET_POLICY \
	_IOWR(DFRC_IOCTL_MAGIC, 1001, struct DFRC_DRV_POLICY)
#define DFRC_IOCTL_CMD_UNREG_POLICY \
	_IOWR(DFRC_IOCTL_MAGIC, 1002, unsigned long long)
#define DFRC_IOCTL_CMD_SET_HWC_INFO \
	_IOWR(DFRC_IOCTL_MAGIC, 1003, struct DFRC_DRV_HWC_INFO)
#define DFRC_IOCTL_CMD_SET_INPUT_WINDOW \
	_IOWR(DFRC_IOCTL_MAGIC, 1004, struct DFRC_DRV_INPUT_WINDOW_INFO)
#define DFRC_IOCTL_CMD_RESET_STATE \
	_IO(DFRC_IOCTL_MAGIC, 1005)
#define DFRC_IOCTL_CMD_GET_VSYNC_REQUEST \
	_IOWR(DFRC_IOCTL_MAGIC, 1006, struct DFRC_DRV_VSYNC_REQUEST)
#define DFRC_IOCTL_CMD_GET_REQUEST_SET \
	_IOWR(DFRC_IOCTL_MAGIC, 1007, struct DFRC_DRC_REQUEST_SET)
#define DFRC_IOCTL_CMD_GET_PANEL_INFO \
	_IOWR(DFRC_IOCTL_MAGIC, 1008, struct DFRC_DRV_PANEL_INFO)
#define DFRC_IOCTL_CMD_GET_REFRESH_RANGE \
	_IOWR(DFRC_IOCTL_MAGIC, 1009, struct DFRC_DRV_REFRESH_RANGE)
#define DFRC_IOCTL_CMD_SET_WINDOW_STATE \
	_IOWR(DFRC_IOCTL_MAGIC, 1010, struct DFRC_DRV_WINDOW_STATE)
#define DFRC_IOCTL_CMD_SET_FOREGROUND_WINDOW \
	_IOWR(DFRC_IOCTL_MAGIC, 1011, struct DFRC_DRV_FOREGROUND_WINDOW_INFO)
#define DFRC_IOCTL_CMD_FORBID_ADJUSTING_VSYNC \
	_IOWR(DFRC_IOCTL_MAGIC, 1012, int32_t)

#endif
