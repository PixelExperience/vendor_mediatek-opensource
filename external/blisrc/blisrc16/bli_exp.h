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
 *   bli_exp.h
 *
 * Project:
 * --------
 *
 *
 * Description:
 * ------------
 *   BLI SRC Interface Definition
 *
 * Author:
 * -------
 *   HP Cheng
 *
 *==============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 *
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *==============================================================================
 *******************************************************************************/

#ifndef BLI_EXP_H
#define BLI_EXP_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef void     BLI_HANDLE;

#ifndef NULL
#define NULL    0
#endif


    /*----------------------------------------------------------------------*/
    /* Get required buffer size for BLI Software SRC                        */
    /*----------------------------------------------------------------------*/
    void BLI_GetMemSize(unsigned int inSR,                  /* Input, input sampling rate of the conversion */
                        unsigned int inChannel,             /* Input, input channel number of the conversion */
                        unsigned int outSR,                 /* Input, output sampling rate of the conversion */
                        unsigned int outChannel,            /* Input, output channel number of the conversion */
                        unsigned int *workBufSize);         /* Output, the required working buffer size in byte */

    /*----------------------------------------------------------------------*/
    /* Get the BLI Software SRC handler.                                    */
    /* Return: the handle of current BLI Software SRC                       */
    /*----------------------------------------------------------------------*/
    BLI_HANDLE *BLI_Open(unsigned int inSR,                 /* Input, input sampling rate of the conversion */
                         unsigned int inChannel,            /* Input, input channel number of the conversion */
                         unsigned int outSR,                /* Input, output sampling rate of the conversion */
                         unsigned int outChannel,           /* Input, output channel number of the conversion */
                         char *buffer,                      /* Input, pointer to the working buffer */
                         void * (*custom_alloc)(unsigned int));

    /*----------------------------------------------------------------------*/
    /* Decompress the bitstream to PCM data                                 */
    /* Return: consumed input buffer size(byte)                             */
    /*----------------------------------------------------------------------*/
    unsigned int BLI_Convert(void *hdl,                  /* Input, handle of this conversion */
                             short *inBuf,               /* Input, pointer to input buffer */
                             unsigned int *inLength,     /* Input, length(byte) of input buffer */
                             /* Output, length(byte) left in the input buffer after conversion */
                             short *outBuf,              /* Input, pointer to output buffer */
                             unsigned int *outLength);   /* Input, length(byte) of output buffer */
    /* Output, output data length(byte) */

    /*----------------------------------------------------------------------*/
    /* Close the process                                                    */
    /*----------------------------------------------------------------------*/
    void BLI_Close(void *hdl,
                   void (*custom_free)(void *));


    /*----------------------------------------------------------------------*/
    /* Change the input sampling rate during the process                    */
    /* Return: error code, 0 represents "everything is OK"                  */
    /*----------------------------------------------------------------------*/
    int BLI_SetSamplingRate(void *hdl,
                            unsigned int inSR);     /* Input, input sampling rate of the conversion */

    /*----------------------------------------------------------------------*/
    /* Clear the internal status for the discontinuous input buffer         */
    /*----------------------------------------------------------------------*/
    int BLI_Reset(void *hdl);

#ifdef __cplusplus
}
#endif

#endif

