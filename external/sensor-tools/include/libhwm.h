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

#ifndef __LIBHWM_H__
#define __LIBHWM_H__
/*---------------------------------------------------------------------------*/
#include <math.h>
#ifdef __cplusplus
extern "C" {
#endif

#define GSENSOR_NAME                    "/dev/gsensor"
#define GSENSOR_ATTR_SELFTEST           "/sys/bus/platform/drivers/gsensor/selftest"

#define GYROSCOPE_NAME                  "/dev/gyroscope"
#define ALSPS_NAME                      "/dev/als_ps"

#define MSENSOR_NAME                  "/dev/msensor"
/*---------------------------------------------------------------------------*/
// hardware\libhardware\include\hardware\sensors.h
#define LIBHWM_GRAVITY_EARTH            (9.80665f)
/*---------------------------------------------------------------------------*/
#define LIBHWM_ACC_NVRAM_SENSITIVITY    (65536)
/*---------------------------------------------------------------------------*/
#define LSB_TO_GRA(X)                   ((X*LIBHWM_GRAVITY_EARTH)/LIBHWM_ACC_NVRAM_SENSITIVITY)
#define GRA_TO_LSB(X)                   (round((X*LIBHWM_ACC_NVRAM_SENSITIVITY)/LIBHWM_GRAVITY_EARTH))
/*---------------------------------------------------------------------------*/
#define LIBHWM_INVAL_FD                 (-1)
/*---------------------------------------------------------------------------*/
#define LIBHWM_IS_INVAL_FD(fd)          (fd == LIBHWM_INVAL_FD)
// Gyroscope sensor sensitivity 1000
#define LIBHWM_GYRO_NVRAM_SENSITIVITY   1000
/*---------------------------------------------------------------------------*/
#define ABSDIF(X, Y) ((X > Y) ? (Y - X) : (X - Y))
#define ABS(X)      ((X > 0) ? (X) : (-X))
/*---------------------------------------------------------------------------*/
typedef enum {
    HWM_TYPE_NONE = 0,
    HWM_TYPE_ACC = 1,
    HWM_TYPE_MAG = 2,
    HWM_TYPE_PRO = 3,
    HWM_TYPE_LIG = 4,
    HWM_TYPE_PS = 5,
} HwmType;
/*---------------------------------------------------------------------------*/
typedef struct {
    HwmType     type;
    char        *ctl;
    char        *dat;
    int         ctl_fd;
    int         dat_fd;
} HwmDev;
/*---------------------------------------------------------------------------*/
typedef union {
    struct {    /*raw data*/
        int rx;
        int ry;
        int rz;
    };
    struct {
        float x;
        float y;
        float z;
    };
    struct {
        float azimuth;
        float pitch;
        float roll;
    };
    struct {
        int ps_data;
        int ps_cali;
        int ps_threshold_high;
        int ps_threshold_low;
    };
} HwmData;
/*---------------------------------------------------------------------------*/
typedef struct {
    void *ptr;
    int   len;
} HwmPrivate;
/*---------------------------------------------------------------------------*/
struct caliData
{
    int64_t timeStamp;
    float data[6];
    int8_t status;
};
/*---------------------------------------------------------------------------*/
extern int gsensor_calibration(int fd, int period, int count, int tolerance, HwmData *cali);
extern int gsensor_write_nvram(HwmData *dat);
extern int gsensor_read_nvram(HwmData *dat);
extern int gsensor_rst_cali(int fd);
extern int gsensor_set_cali(int fd, HwmData *dat);
extern int gsensor_get_cali(int fd, HwmData *dat);
extern int gsensor_enable_cali(int fd);
extern int gsensor_do_selftest(int fd);
extern int gsensor_read(int fd, HwmData *dat);
extern int gsensor_init(int fd);
extern int gsensor_close(int fd);
extern int gsensor_open(int *fd);
extern int gsensor_start_static_calibration(void);
extern int gsensor_get_static_calibration(struct caliData *caliDat);
extern int gyroscope_calibration(int fd, int period, int count, int tolerance, HwmData *cali);
extern int gyroscope_write_nvram(HwmData *dat);
extern int gyroscope_read_nvram(HwmData *dat);
extern int gyroscope_rst_cali(int fd);
extern int gyroscope_set_cali(int fd, HwmData *dat);
extern int gyroscope_get_cali(int fd, HwmData *dat);
extern int gyroscope_enable_cali(int fd);
extern int gyroscope_do_selftest(int fd);
extern int gyroscope_read(int fd, HwmData *dat);
extern int gyroscope_close(int fd);
extern int gyroscope_open(int *fd);
extern int gyroscope_init(int fd);
extern int gyroscope_start_static_calibration(void);
extern int gyroscope_get_static_calibration(struct caliData *caliDat);
extern int msensor_do_selftest(int fd);
extern int msensor_close(int fd);
extern int msensor_open(int *fd);

/*yucong add for alsps calibration functions*/
extern int alsps_calibration(int fd, int period, int count, HwmData *cali);
extern int alsps_write_nvram(HwmData *dat);
extern int alsps_read_nvram(HwmData *dat);
extern int alsps_rst_cali(int fd);
extern int alsps_set_cali(int fd, HwmData *dat);
extern int alsps_get_cali(int fd, HwmData *dat);
extern int alsps_ps_enable_cali(int fd);
extern int alsps_read(int fd, HwmData *dat);
extern int alsps_set_threshold(int fd, HwmData *dat);
extern int als_start_static_calibration(void);
extern int als_get_static_calibration(struct caliData *caliDat);
extern int als_set_cali(int fd, struct caliData *caliDat);

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
extern int get_psensor_data(void);
extern int calculate_psensor_min_value(void);
extern int get_psensor_min_value(void);
extern int calculate_psensor_max_value(void);
extern int get_psensor_max_value(void);
extern int do_calibration(int min, int max);
extern int get_psensor_threshold(int flag);
extern int set_psensor_threshold(int high, int low);
extern int clear_psensor_calibration(void);
/*---------------------------------------------------------------------------*/
extern int do_gsensor_calibration(int tolerance);
extern int get_gsensor_calibration(float *x, float *y, float *z);
extern int clear_gsensor_calibration(void);

/*---------------------------------------------------------------------------*/
extern int do_gyroscope_calibration(int tolerance);
extern int get_gyroscope_calibration(float *x, float *y, float *z);
extern int clear_gyroscope_calibration(void);
#ifdef __cplusplus
}
#endif
#endif
