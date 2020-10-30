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

/*
 * Description:
 *   Implement convert hex XML to dec format tool
 */

#include "AudioParamParser.h"
#include "AudioParamParserPriv.h"

#include <stdio.h>
#include <string.h>

static const char *INPUT_UNNORMALIZED_DIR[] = {
    ".\\unnormalized_xml\\",
    NULL
};
#define OUTPUT_NORMALIZED_DIR ".\\normalized_xml"

int main() {
    size_t num, i;
    AppHandle *appHandle = NULL;
    AppHandle Handle;

    /* Set the debug level, default is INFO_LEVEL */
    appSetDebugLevel(ERR_LEVEL);

    /* For Tuning Tool debug usage, used to show the APP lib message to the console */
    appHandleRedirectIOToConsole();

    /* Init app handle */
    appHandleInit(&Handle);
    appHandle = &Handle;

    /* Save XML with Dec mode */
    appHandle->saveXmlWithHexMode = 1;

    /* Save XML with Dec mode */
    appHandle->normalizeXmlContent = 1;

    /* Parse the xml in default and cus folder,
      if cus folder has the same name of XML file,
      parser will load the cus folder xml instead of default xml folder */
    appHandleParseXml(appHandle, INPUT_UNNORMALIZED_DIR, NULL);

    /* Save all Xml */
    num = appHandleGetNumOfAudioType(appHandle);
    i = 0;

    for (i = 0; i < num; i++) {
        AudioType *audioType = appHandleGetAudioTypeByIndex(appHandle, i);

        /* Read lock */
        audioTypeReadLock(audioType, __FUNCTION__);

        /* Save changed AudioType to XML */
        audioTypeSaveAudioParamXml(audioType, OUTPUT_NORMALIZED_DIR, 1);

        /* Unlock */
        audioTypeUnlock(audioType);
    }

    /* Release appHandle resources */
    appHandleUninit(appHandle);

    return 0;
}

