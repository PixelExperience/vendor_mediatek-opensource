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

/*******************************************************************************
 *
 * Filename:
 * ---------
 *   AudioFtm.h
 *
 * Project:
 * --------
 *   Android Audio Driver
 *
 * Description:
 * ------------
 *   Factory Mode
 *
 * Author:
 * -------
 *   Chipeng Chang (mtk02308)
 *
 *------------------------------------------------------------------------------
 * $Revision: #5 $
 * $Modtime:$
 * $Log:$
 *
 *
 *******************************************************************************/

#ifndef ANDROID_AUDIO_FTM_H
#define ANDROID_AUDIO_FTM_H

/*****************************************************************************
*                     C O M P I L E R   F L A G S
******************************************************************************
*/

/*****************************************************************************
*                E X T E R N A L   R E F E R E N C E S
******************************************************************************
*/
#include <stdint.h>
#include <sys/types.h>
#include <pthread.h>

#include <tinyalsa/asoundlib.h> // TODO(Harvey): move it

#include "AudioType.h"

#include "AudioFtmBase.h"

/*****************************************************************************
*                          C O N S T A N T S
******************************************************************************
*/

/*****************************************************************************
*                         M A C R O
******************************************************************************
*/

/*****************************************************************************
*                  R E G I S T E R       D E F I N I T I O N
******************************************************************************
*/

/*****************************************************************************
*                        F U N C T I O N   D E F I N I T I O N
******************************************************************************
*/

/*****************************************************************************
*                         D A T A   T Y P E S
******************************************************************************
*/

namespace android {

enum audio_mic_mask_t {
    AUDIO_MIC_MASK_NONE = 1 << 0,
    AUDIO_MIC_MASK_MIC1 = 1 << 1,
    AUDIO_MIC_MASK_MIC2 = 1 << 2,
    AUDIO_MIC_MASK_MIC3 = 1 << 3,
    AUDIO_MIC_MASK_MIC4 = 1 << 4,

    AUDIO_MIC_MASK_HEADSET_MIC = 1 << 16,
};


/*****************************************************************************
*                        C L A S S   D E F I N I T I O N
******************************************************************************
*/

class AudioALSAStreamManager;
class AudioALSAStreamOut;
class AudioALSAStreamIn;

class LoopbackManager;

class AudioALSAHardwareResourceManager;

class AudioFtm : public AudioFtmBase {
public:
    virtual ~AudioFtm();
    static AudioFtm *getInstance();


    virtual int SineGenTest(char sinegen_test);

    /// Output device test
    virtual int RecieverTest(char receiver_test);
    virtual int LouderSPKTest(char left_channel, char right_channel);
    virtual int EarphoneTest(char bEnable);
    virtual int EarphoneTestLR(char bLR);

    /// Input device test
    virtual int SpecificBuildInMicTest(char type);

    /// Speaker over current test
    virtual int Audio_READ_SPK_OC_STA(void);
    virtual int LouderSPKOCTest(char left_channel, char right_channel);


    /// Loopback // TODO: Add in platform!!!
    virtual int PhoneMic_Receiver_Loopback(char echoflag);
    virtual int PhoneMic_EarphoneLR_Loopback(char echoflag);
    virtual int PhoneMic_SpkLR_Loopback(char echoflag);
    virtual int HeadsetMic_EarphoneLR_Loopback(char bEnable, char bHeadsetMic);
    virtual int HeadsetMic_SpkLR_Loopback(char echoflag);
    virtual int HeadsetMic_Receiver_Loopback(char bEnable, char bHeadsetMic);

    virtual int PhoneMic_Receiver_Acoustic_Loopback(int Acoustic_Type, int *Acoustic_Status_Flag, int bHeadset_Output);


    /// FM / mATV
    virtual int FMLoopbackTest(char bEnable);

    virtual int Audio_FM_I2S_Play(char bEnable);
    virtual int Audio_MATV_I2S_Play(int enable_flag);
    virtual int Audio_FMTX_Play(bool Enable, unsigned int Freq);

    virtual int ATV_AudPlay_On(void);
    virtual int ATV_AudPlay_Off(void);
    virtual unsigned int ATV_AudioWrite(void *buffer, unsigned int bytes);

    /// HDMI
    int HDMI_SineGenPlayback(bool Enable, int Freq);


    /// Vibration Speaker // MTK_VIBSPK_SUPPORT??
    virtual int      SetVibSpkCalibrationParam(void *cali_param);
    virtual uint32_t GetVibSpkCalibrationStatus();
    virtual void     SetVibSpkEnable(bool enable, uint32_t freq);
    virtual void     SetVibSpkRampControl(uint8_t rampcontrol);

    virtual bool     ReadAuxadcData(int channel, int *value);
    virtual void     SetStreamOutPostProcessBypass(bool flag);

    // speaker calibration for SmartPa
    virtual bool     SpeakerCalibration(int calibStage);

private:
    static AudioFtm *mAudioFtm;

    AudioFtm();
    AudioFtm(const AudioFtm &);             // intentionally undefined
    AudioFtm &operator=(const AudioFtm &);  // intentionally undefined

    //  SW SineWave for FM Tx and HDMI //[temp]
    bool WavGen_SW_SineWave(bool Enable, unsigned int Freq, int type);
    bool WavGen_SWPattern(bool Enable, unsigned int Freq, int type);
    void WavGen_AudioRead(char *pBuffer, unsigned int bytes);

    static void *FmTx_thread_create(void *arg);
    static void *HDMI_thread_create(void *arg);
    void FmTx_thread_digital_out(void);
    void HDMI_thread_I2SOutput(void);

    pthread_t m_WaveThread;
    bool mAudioSinWave_thread;
    unsigned int IdxAudioPattern;
    unsigned int SizeAudioPattern;
    unsigned char *mDataTable;
    char *mDataBuffer;


    virtual status_t setMicEnable(const audio_mic_mask_t audio_mic_mask, const bool enable); // [TMP]


    AudioALSAStreamManager *mStreamManager;
    AudioALSAStreamOut     *mStreamOut;
    AudioALSAStreamIn      *mStreamIn;

    LoopbackManager        *mLoopbackManager;

    AudioALSAHardwareResourceManager *mHardwareResourceManager;
};

}; // namespace android

#endif

