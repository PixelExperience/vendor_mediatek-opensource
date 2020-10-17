/* Copyright (C) 2020 The Evolution X Project
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

#define LOG_TAG "libPowerHal"

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <utils/Log.h>
#include <errno.h>
#include <sys/stat.h>

#include "common.h"
#include "utility_io.h"

#define PATH_BLKDEV_UFS_USER      "/sys/block/sdc/queue/read_ahead_kb"
#define PATH_BLKDEV_DM_USER       "/sys/block/dm-2/queue/read_ahead_kb"
#define PATH_BLKDEV_EMMC_USER     "/sys/block/mmcblk0/queue/read_ahead_kb"

static int blkdev_init = 0;
static int blkdev_ufsSupport = 0;
static int blkdev_dmSupport = 0;
static int blkdev_emmcSupport = 0;
static int blkdev_ufsDefault = 0;
static int blkdev_dmDefault = 0;
static int blkdev_emmDefault = 0;

/* static function */
static void check_blkDevSupport(void)
{
    struct stat stat_buf;

    if (0 == stat(PATH_BLKDEV_UFS_USER, &stat_buf)) {
        blkdev_ufsSupport = 1;
        blkdev_ufsDefault = get_int_value(PATH_BLKDEV_UFS_USER);
    }
    if (0 == stat(PATH_BLKDEV_DM_USER, &stat_buf)) {
        blkdev_dmSupport = 1;
        blkdev_dmDefault = get_int_value(PATH_BLKDEV_DM_USER);
    }
    if (0 == stat(PATH_BLKDEV_EMMC_USER, &stat_buf)) {
        blkdev_emmcSupport = 1;
        blkdev_emmDefault = get_int_value(PATH_BLKDEV_EMMC_USER);
    }
    ALOGI("check_blkDevSupport: %d, %d, %d", blkdev_ufsDefault, blkdev_dmDefault, blkdev_emmDefault);
}

int setBlkDev_readAhead(int value, void *scn)
{
    ALOGV("setBlkDev_readAhead: %p", scn);
    if (!blkdev_init) {
        check_blkDevSupport();
        blkdev_init = 1;
    }

    if (value != -1) {
        if (blkdev_ufsSupport)
            set_value(PATH_BLKDEV_UFS_USER, value);
        if (blkdev_dmSupport)
            set_value(PATH_BLKDEV_DM_USER, value);
        if (blkdev_emmcSupport)
            set_value(PATH_BLKDEV_EMMC_USER, value);
    } else {
        if (blkdev_ufsSupport)
            set_value(PATH_BLKDEV_UFS_USER, blkdev_ufsDefault);
        if (blkdev_dmSupport)
            set_value(PATH_BLKDEV_DM_USER, blkdev_dmDefault);
        if (blkdev_emmcSupport)
            set_value(PATH_BLKDEV_EMMC_USER, blkdev_emmDefault);
    }
    ALOGI("setBlkDev_readAhead: value:%d", value);
    return 0;
}
