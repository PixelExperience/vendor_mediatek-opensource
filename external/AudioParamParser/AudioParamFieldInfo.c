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
 *   Implement ParamInfo & FieldInfo related APIs
 */

#include "AudioParamParserPriv.h"

EXPORT size_t paramInfoGetNumOfFieldInfo(ParamInfo *paramInfo) {
    if (!paramInfo) {
        ERR_LOG("paramInfo is NULL!\n");
        return 0;
    }

    return HASH_COUNT(paramInfo->fieldInfoHash);
}

EXPORT FieldInfo *paramInfoGetFieldInfoByIndex(ParamInfo *paramInfo, size_t index) {
    FieldInfo *fieldInfo = NULL;
    size_t i = 0;

    if (!paramInfo) {
        ERR_LOG("paramInfo is NULL!\n");
        return NULL;
    }

    for (fieldInfo = paramInfo->fieldInfoHash; fieldInfo ; fieldInfo = fieldInfo->hh.next) {
        if (index == i++) {
            return fieldInfo;
        }
    }

    return NULL;
}

EXPORT FieldInfo *paramInfoGetFieldInfoByName(ParamInfo *paramInfo, const char *fieldName) {
    FieldInfo *fieldInfo;

    if (!paramInfo) {
        ERR_LOG("paramInfo is NULL!\n");
        return NULL;
    }

    /* Query Param name */
    HASH_FIND_STR(paramInfo->fieldInfoHash, fieldName, fieldInfo);

    return fieldInfo;
}

EXPORT ParamInfo *paramInfoCreate(const char *name, DATA_TYPE dataType, AudioType *audioType) {
    ParamInfo *paramInfo = (ParamInfo *)malloc(sizeof(ParamInfo));
    if (!paramInfo) {
        ERR_LOG("malloc fail!\n");
        return NULL;
    }

    paramInfo->audioType = audioType;
    paramInfo->name = strdup(name);
    paramInfo->dataType = dataType;
    paramInfo->fieldInfoHash = NULL;
    return paramInfo;
}

EXPORT FieldInfo *fieldInfoCreate(const char *fieldName, unsigned int arrayIndex, int startBit, int endBit, const char *checkList, ParamInfo *paramInfo) {
    FieldInfo *fieldInfo = (FieldInfo *)malloc(sizeof(FieldInfo));

    if (!fieldInfo) {
        ERR_LOG("malloc fail!\n");
        return NULL;
    }

    /* Setup members */
    fieldInfo->name = strdup(fieldName);
    fieldInfo->arrayIndex = arrayIndex;
    fieldInfo->startBit = startBit;
    fieldInfo->endBit = endBit;
    fieldInfo->paramInfo = paramInfo;


    if (checkList) {
        fieldInfo->checkListStr = strdup(checkList);
    } else {
#ifdef WIN32
        fieldInfo->checkListStr = utilGenCheckList(endBit - startBit + 1);
#else
        /* Reduce memory usage, don't generate check list automatically */
        fieldInfo->checkListStr = strdup("");
#endif
    }

    return fieldInfo;
}

EXPORT void paramInfoRelease(ParamInfo *paramInfo) {
    if (paramInfo == NULL) {
        return;
    }

    if (paramInfo->fieldInfoHash) {
        FieldInfo *tmp, *item;
        HASH_ITER(hh, paramInfo->fieldInfoHash, item, tmp) {
            if (paramInfo->fieldInfoHash) {
                HASH_DEL(paramInfo->fieldInfoHash, item);
                fieldInfoRelease(item);
            }
        }
    }

    free(paramInfo->name);
    free(paramInfo);
}

EXPORT void fieldInfoRelease(FieldInfo *fieldInfo) {
    if (fieldInfo == NULL) {
        return;
    }

    if (fieldInfo->checkListStr) {
        free(fieldInfo->checkListStr);
    }

    free(fieldInfo->name);
    free(fieldInfo);
}

EXPORT APP_STATUS fieldInfoGetCheckListValue(FieldInfo *fieldInfo, const char *checkName, unsigned int *checkVal) {
    char *checkList;
    char *valStr;
    char *nameStr;
    char *restOfStr = NULL;
    if (!fieldInfo) {
        ERR_LOG("fieldInfo is NULL\n");
        return APP_ERROR;
    }

    if (!checkName) {
        ERR_LOG("checkName is NULL\n");
        return APP_ERROR;
    }

    if (!checkVal) {
        ERR_LOG("checkVal is NULL\n");
        return APP_ERROR;
    }

    checkList = strdup(fieldInfo->checkListStr);
    valStr = utilStrtok(checkList, ARRAY_SEPERATOR, &restOfStr);
    if (!valStr) {
        ERR_LOG("Cannot parse valStr\n");
        free(checkList);
        return APP_ERROR;
    }

    while ((nameStr = utilStrtok(NULL, ARRAY_SEPERATOR, &restOfStr)) != NULL) {
        if (!strncmp(nameStr, checkName, strlen(checkName) + 1)) {
            *checkVal = strtoul(valStr, NULL, 0);
            free(checkList);
            return APP_NO_ERROR;
        }

        valStr = utilStrtok(NULL, ARRAY_SEPERATOR, &restOfStr);
        if (!valStr) {
            ERR_LOG("Cannot parse valStr\n");
            free(checkList);
            return APP_ERROR;
        }
    }

    free(checkList);
    return APP_ERROR;
}
