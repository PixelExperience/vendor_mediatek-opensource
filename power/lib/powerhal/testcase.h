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

#ifndef ANDROID_TESTCASE_H
#define ANDROID_TESTCASE_H

/*
 * Notice
 * 1. remember to set the all SCN off in each test case.
 * 2. keywords in pattern
 *    - SCN: scenario, must follow by scn num and state. ex. SCN,A,B
 *    - SLP: unit ms, used for delay operation, ex. SLP,A
 *    - CHK: check the cpu cores ex. CHK,A
 * 3. the cpu num check should be specified in test pattern to reduce test program logic
 *
 *
 * TODO:
 * 1. change the test case to other configurable files thus we don't need build code to do the test.
 * 
 */
struct {
	const char *testDescription;
	const char *testPattern;
} testcase_set[] = {
	{"Test SCN Idx 1...",
	"SCN,1,ON,SLP,100,CHK,2,SLP,100,SCN,1,OFF"},
	{"Test SCN Idx 2...",
	"SCN,2,ON,SLP,100,CHK,2,SLP,100,SCN,2,OFF"},
	/* SCN_2_ON -> SCN_1_ON -> SCN_2_OFF -> SCN_1_OFF */
	{"Test SCN combination (1)...",
	"SCN,2,ON,SLP,100,SCN,1,ON,SLP,100,CHK,2,SCN,2,OFF,SLP,100,CHK,2,SCN,1,OFF"},
	/* SCN_2_ON -> SCN_1_ON -> SCN_1_OFF -> SCN_2_OFF */
	{"Test SCN combination (2)...",
	"SCN,2,ON,SLP,100,SCN,1,ON,SLP,100,CHK,2,SCN,1,OFF,SLP,100,CHK,2,SCN,2,OFF"},
	/* SCN_1_ON -> SCN_2_ON -> SCN_1_OFF -> SCN_2_OFF */
	{"Test SCN combination (3)...",
	"SCN,1,ON,SLP,100,SCN,2,ON,SLP,100,CHK,2,SCN,1,OFF,SLP,100,CHK,2,SCN,2,OFF"},
	/* SCN_1_ON -> SCN_2_ON -> SCN_2_OFF -> SCN_1_OFF */
	{"Test SCN combination (4)...",
	"SCN,1,ON,SLP,100,SCN,2,ON,SLP,100,CHK,2,SCN,2,OFF,SLP,100,CHK,2,SCN,1,OFF"},
	{NULL,NULL},
};

#endif //ANDROID_TESTCASE_H
