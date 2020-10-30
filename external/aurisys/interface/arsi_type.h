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

#ifndef MTK_ARSI_TYPE_H
#define MTK_ARSI_TYPE_H

#include <stdint.h>
#include <stdbool.h>



#ifdef __cplusplus
extern "C" {
#endif


/*
 * =============================================================================
 *                     enum
 * =============================================================================
 */

/** arsi_process_type_t */
enum {
    ARSI_PROCESS_TYPE_UL_ONLY,
    ARSI_PROCESS_TYPE_DL_ONLY,
    ARSI_PROCESS_TYPE_UL_AND_DL
};

typedef uint8_t arsi_process_type_t;



/** data_buf_type_t */
enum {
    DATA_BUF_UPLINK_IN,
    DATA_BUF_UPLINK_OUT,

    DATA_BUF_DOWNLINK_IN,
    DATA_BUF_DOWNLINK_OUT,

    DATA_BUF_ECHO_REF,      /* Echo ref for AEC */
    DATA_BUF_IV_BUFFER,     /* I/V buffer for speaker protection */
    DATA_BUF_CALL_INFO,     /* extra_call_arg_t */

    NUM_DATA_BUF_TYPE       /* the #types of data_buf_type_t */
};

typedef uint8_t data_buf_type_t;



/** output_device_hw_info_mask_t */
enum {
    /* 2-in-1 speaker */
    OUTPUT_DEVICE_HW_INFO_2IN1_SPEAKER       = (1 << 0),

    /* vibration speaker */
    OUTPUT_DEVICE_HW_INFO_VIBRATION_SPEAKER  = (1 << 1),

    /* stereo speaker */
    OUTPUT_DEVICE_HW_INFO_STEREO_SPEAKER     = (1 << 2),

    OUTPUT_DEVICE_HW_INFO_SMARTPA_SPEAKER    = (1 << 3),
};

typedef uint16_t output_device_hw_info_mask_t;



/** input_device_hw_info_mask_t */
enum {
    /* digital mic */
    INPUT_DEVICE_HW_INFO_DIGITAL_MIC     = (1 << 0),

    /* headset mic */
    INPUT_DEVICE_HW_INFO_HEADSET_POLE_3      = (1 << 1),
    INPUT_DEVICE_HW_INFO_HEADSET_POLE_4      = (1 << 2),
    INPUT_DEVICE_HW_INFO_HEADSET_POLE_5      = (1 << 3),
    INPUT_DEVICE_HW_INFO_HEADSET_POLE_5_ANC  = (1 << 4),

};

typedef uint16_t input_device_hw_info_mask_t;



/** enhancement_feature_mask_t, controlled by Apk or device environment */
enum {
    /* BT Noise Reduction and Echo Cancellation */
    ENHANCEMENT_FEATURE_BT_NREC = (1 << 0),

    /* HAC Receiver */
    ENHANCEMENT_FEATURE_EARPIECE_HAC = (1 << 1),

    /* Echo Cancellation */
    ENHANCEMENT_FEATURE_EC = (1 << 2),

    /* Noise Reduction */
    ENHANCEMENT_FEATURE_NS = (1 << 3),

    /* Auto Gain Control */
    ENHANCEMENT_FEATURE_AGC = (1 << 4),

    ENHANCEMENT_FEATURE_ALL  = (ENHANCEMENT_FEATURE_BT_NREC |
                                ENHANCEMENT_FEATURE_EARPIECE_HAC |
                                ENHANCEMENT_FEATURE_EC |
                                ENHANCEMENT_FEATURE_NS |
                                ENHANCEMENT_FEATURE_AGC)
};

typedef uint16_t enhancement_feature_mask_t;



/*
 * =============================================================================
 *                     Data Structure
 * =============================================================================
 */

/** char string buffer */
typedef struct string_buf_t {
    uint32_t memory_size;       /* 0 <= string_size < memory_size */
    uint32_t string_size;       /* string_size = strlen(p_string); */
    union {
        char    *p_string;      /* string address */
        uint32_t dummy[2];      /* reserve for 64 bits pointer only */
    };
} string_buf_t; /* sizeof(): 16 bytes */


/** data buffer (PCM, I/V buffer, speech parameters, ... */
typedef struct data_buf_t {
    uint32_t memory_size;       /* buffer size (memory) */
    uint32_t data_size;         /* 0 <= data_size <= memory_size */
    union {
        void    *p_buffer;      /* memory address */
        uint32_t dummy[2];      /* reserve for 64 bits pointer only */
    };
} data_buf_t; /* sizeof(): 16 bytes */


/** audio_buf_t */
typedef struct audio_buf_t {
    data_buf_t  data_buf;               /* PCM data, I/V buffer, ... */
    uint8_t     data_buf_type;          /* data_buf_type_t */

    uint8_t     frame_size_ms;          /* arsi_lib_config_t frame_size_ms */
    uint8_t     b_interleave;           /* arsi_lib_config_t b_interleave */

    uint8_t     num_channels;           /* 1, 2, 3, 4, ... */
    uint32_t    channel_mask;           /* audio_channel_mask_t */

    uint32_t    sample_rate_buffer;     /* 8000, 16000, 24000, 32000, ... */
    uint32_t    sample_rate_content;    /* 8000, 16000, 24000, 32000, ... */

    uint32_t    audio_format;           /* audio_format_t */

    uint32_t    reserve3;
} audio_buf_t; /* sizeof(): 40 bytes */


/** arsi_lib_config_t */
typedef struct arsi_lib_config_t {
    /* Uplink */
    union {
        audio_buf_t *p_ul_buf_in;   /* UL unprocessed buffer */
        uint32_t dummy1[2];         /* reserve for 64 bits pointer only */
    };

    union {
        audio_buf_t *p_ul_buf_out;  /* UL processed buffer */
        uint32_t dummy2[2];         /* reserve for 64 bits pointer only */
    };

    union {
        audio_buf_t *p_ul_ref_bufs; /* UL reference buffer array */
        uint32_t dummy3[2];         /* reserve for 64 bits pointer only */
    };

    /* Downlink */
    union {
        audio_buf_t *p_dl_buf_in;   /* DL unprocessed buffer */
        uint32_t dummy4[2];         /* reserve for 64 bits pointer only */
    };

    union {
        audio_buf_t *p_dl_buf_out;  /* DL processed buffer */
        uint32_t dummy5[2];         /* reserve for 64 bits pointer only */
    };

    union {
        audio_buf_t *p_dl_ref_bufs; /* DL reference buffer array */
        uint32_t dummy6[2];         /* reserve for 64 bits pointer only */
    };


    uint32_t sample_rate;   /* 8000, 16000, 24000, 32000, ... */
    uint32_t audio_format;  /* audio_format_t */

    uint8_t  frame_size_ms; /* ex, 20ms; 0: not frame base. */
    uint8_t  b_interleave;  /* 0: non-interleave, 1: interleave */

    uint8_t  num_ul_ref_buf_array; /* how much ref bufs for ul processing */
    uint8_t  num_dl_ref_buf_array; /* how much ref bufs for dl processing */
    uint32_t reserve2;
} arsi_lib_config_t; /* sizeof(): 64 bytes */


/** arsi_lib_config_t */
typedef struct audio_device_info_t {
    uint32_t devices;           /* audio_devices_t */
    uint32_t audio_format;      /* audio_format_t */

    uint32_t sample_rate;       /* 8000, 16000, 24000, 32000, ... */
    uint32_t reserve1;

    uint32_t channel_mask;      /* audio_channel_mask_t */
    uint8_t  num_channels;      /* 1, 2, 3, 4, ..., from channel_mask */
    uint8_t  reserve2;

    uint16_t hw_info_mask;      /* input_device_hw_info_mask_t, output_device_hw_info_mask_t */
} audio_device_info_t; /* sizeof(): 24 bytes */


/** arsi_task_config_t. scene, hw related */
typedef struct arsi_task_config_t {
    audio_device_info_t input_device_info;
    audio_device_info_t output_device_info;

    uint8_t  task_scene;                /* task_scene_t */
    uint8_t  audio_mode;                /* audio_mode_t */

    int8_t   stream_type;               /* audio_stream_type_t */
    uint8_t  network_info;              /* GSM, Volte, CDMA, ... */

    uint32_t max_input_device_sample_rate;      /* 8000, 16000, 24000, 32000, ... */
    uint32_t max_output_device_sample_rate;     /* 8000, 16000, 24000, 32000, ... */

    uint8_t  max_input_device_num_channels;     /* max number of channels in all in/out devices */
    uint8_t  max_output_device_num_channels;    /* max number of channels in all in/out devices */
    uint16_t reserve2;

    uint32_t output_flags;              /* audio_output_flags_t */

    uint32_t input_source;              /* audio_source_t, for record only */
    uint32_t input_flags;               /* audio_input_flags_t */

    uint32_t enhancement_feature_mask;  /* enhancement_feature_mask_t */

    uint16_t audio_usage;               /* audio_usage_t */
    uint16_t audio_content_type;        /* audio_content_type_t */
    uint16_t microphone_direction;      /* audio_microphone_direction_t */
    uint16_t reserve3;
} arsi_task_config_t;



/*
 * =============================================================================
 *                     Function Type
 * =============================================================================
 */

/** debug log function pointer */
typedef void (*debug_log_fp_t)(const char *message, ...);



#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* end of MTK_ARSI_TYPE_H */

