/*
 *  Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com/
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
 
 /**
  *
  *  \file  sciclient_extended_ut_tests.h
  *
  *  \brief This file defines the test cases for Sciclient Extended Unit Test 
  *         application
  *
  */

 #ifndef SCICLIENT_EXTENDED_UT_TESTS_H_
 #define SCICLIENT_EXTENDED_UT_TESTS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define SCICLIENT_NUM_TESTCASES   (sizeof (gSciApp_TestcaseParams) / \
                                   sizeof (SciApp_TestParams_t))

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief  Defines the various Sciclient extended unit test cases. */
SciApp_TestParams_t gSciApp_TestcaseParams[] =
{
#if defined (BUILD_MCU1_0)
  {
      /** enableTest **/
      SCI_APP_TEST_ENABLE,

      /** testCaseId **/
      1U,

      /** *reqId **/
      "PDK-14042",

      /** *testCaseName **/
      "Sciclient PM Related Functions Testcase",

      /** *userInfo **/
      "None",

      /** *disableReason **/
      "None",

      /** *passFailCriteria **/
      "PM related functions should Pass when called \
       with valid parameters ",

      /** cpuID **/
      SCI_APP_CORE_TYPE_R5F,

      /** printEnable **/
      SCI_APP_PRINT_ENABLE,

      /** testType **/
      (SCI_APP_TEST_TYPE_SANITY)
    },
#endif
    {
        /** enableTest **/
        SCI_APP_TEST_ENABLE,

        /** testCaseId **/
        2U,

        /** *reqId **/
        "PDK-14044",

        /** *testCaseName **/
        "SCICLIENT MSMC Query Negative Testcase",

        /** *userInfo **/
        "None",

        /** *disableReason **/
        "None",

        /** *passFailCriteria **/
        "Sciclient_msmcQuery should fail when \
         the request parameter is set to NULL ",

        /** cpuID **/
        SCI_APP_CORE_TYPE_R5F,

        /** printEnable **/
        SCI_APP_PRINT_ENABLE,

        /** testType **/
        (SCI_APP_TEST_TYPE_SANITY)
    },
    {
        /** enableTest **/
        SCI_APP_TEST_ENABLE,

        /** testCaseId **/
        3U,

        /** *reqId **/
        "PDK-14046",

        /** *testCaseName **/
        "Sciclient keywriter Negative Testcase",

        /** *userInfo **/
        "None",

        /** *disableReason **/
        "None",

        /** *passFailCriteria **/
        "sciclient keywriter function should fail when \
         the request parameter is set to NULL ",

        /** cpuID **/
        SCI_APP_CORE_TYPE_R5F,

        /** printEnable **/
        SCI_APP_PRINT_ENABLE,

        /** testType **/
        (SCI_APP_TEST_TYPE_SANITY)
    },
    {
        /** enableTest **/
        SCI_APP_TEST_ENABLE,

        /** testCaseId **/
        4U,

        /** *reqId **/
        "PDK-14048",

        /** *testCaseName **/
        "Sciclient dkek Negative Testcase",

        /** *userInfo **/
        "None",

        /** *disableReason **/
        "None",

        /** *passFailCriteria **/
        "sciclient dkek functions should fail when \
         the request parameter is set to NULL ",

        /** cpuID **/
        SCI_APP_CORE_TYPE_R5F,

        /** printEnable **/
        SCI_APP_PRINT_ENABLE,

        /** testType **/
        (SCI_APP_TEST_TYPE_NEGATIVE)
    },
    {
        /** enableTest **/
        SCI_APP_TEST_ENABLE,

        /** testCaseId **/
        5U,

        /** *reqId **/
        "PDK-14043",

        /** *testCaseName **/
        "Sciclient firewall Negative Testcase",

        /** *userInfo **/
        "None",

        /** *disableReason **/
        "None",

        /** *passFailCriteria **/
        "Sciclient firewall functions should fail \
         when the request parameter is set to NULL ",

        /** cpuID **/
        SCI_APP_CORE_TYPE_R5F,

        /** printEnable **/
        SCI_APP_PRINT_ENABLE,

        /** testType **/
        (SCI_APP_TEST_TYPE_SANITY)
    },
    {
        /** enableTest **/
        SCI_APP_TEST_ENABLE,

        /** testCaseId **/
        6U,

        /** *reqId **/
        "PDK-14045",

        /** *testCaseName **/
        "Sciclient prepare header Negative Testcase",

        /** *userInfo **/
        "None",

        /** *disableReason **/
        "None",

        /** *passFailCriteria **/
        "Sciclient prepare header functions should \
         fail when called with invalid parameters ",

        /** cpuID **/
        SCI_APP_CORE_TYPE_R5F,

        /** printEnable **/
        SCI_APP_PRINT_ENABLE,

        /** testType **/
        (SCI_APP_TEST_TYPE_SANITY)
    },
#if defined (SOC_J784S4)
    {
        /** enableTest **/
        SCI_APP_TEST_ENABLE,

        /** testCaseId **/
        7U,

        /** *reqId **/
        "PDK-14047",

        /** *testCaseName **/
        "Sciclient context Negative Testcase",

        /** *userInfo **/
        "None",

        /** *disableReason **/
        "None",

        /** *passFailCriteria **/
        "sciclient context functions should fail \
         when called with invalid parameters and \
         should pass when called with valid parameters ",

        /** cpuID **/
        SCI_APP_CORE_TYPE_R5F,

        /** printEnable **/
        SCI_APP_PRINT_ENABLE,

        /** testType **/
        (SCI_APP_TEST_TYPE_SANITY)
    },
#endif
    {
        /** enableTest **/
        SCI_APP_TEST_ENABLE,

        /** testCaseId **/
        8U,

        /** *reqId **/
        "PDK-14049",

        /** *testCaseName **/
        "Sciclient Init Negative Testcase",

        /** *userInfo **/
        "None",

        /** *disableReason **/
        "None",

        /** *passFailCriteria **/
        "Sciclient Init functions should fail when called with invalid parameters",

        /** cpuID **/
        SCI_APP_CORE_TYPE_R5F,

        /** printEnable **/
        SCI_APP_PRINT_ENABLE,

        /** testType **/
        (SCI_APP_TEST_TYPE_SANITY)
    },
    {
        /** enableTest **/
        SCI_APP_TEST_ENABLE,

        /** testCaseId **/
        9U,

        /** *reqId **/
        "PDK-14053",

        /** *testCaseName **/
        "Sciclient RmPsil Negative Testcase",

        /** *userInfo **/
        "None",

        /** *disableReason **/
        "None",

        /** *passFailCriteria **/
        "sciclient RmPsil functions should fail when called with invalid parameters",

        /** cpuID **/
        SCI_APP_CORE_TYPE_R5F,

        /** printEnable **/
        SCI_APP_PRINT_ENABLE,

        /** testType **/
        (SCI_APP_TEST_TYPE_SANITY)
    },
    {
        /** enableTest **/
        SCI_APP_TEST_ENABLE,

        /** testCaseId **/
        10U,

        /** *reqId **/
        "PDK-14055",

        /** *testCaseName **/
        "Sciclient RmRingCfg Negative Testcase",

        /** *userInfo **/
        "None",

        /** *disableReason **/
        "None",

        /** *passFailCriteria **/
        "sciclient RmRingCfg functions should fail when called with invalid parameters",

        /** cpuID **/
        SCI_APP_CORE_TYPE_R5F,

        /** printEnable **/
        SCI_APP_PRINT_ENABLE,

        /** testType **/
        (SCI_APP_TEST_TYPE_SANITY)
    },
    {
        /** enableTest **/
        SCI_APP_TEST_ENABLE,

        /** testCaseId **/
        11U,

        /** *reqId **/
        "PDK-14058",

        /** *testCaseName **/
        "Sciclient RmRingMonCfg Negative Testcase",

        /** *userInfo **/
        "None",

        /** *disableReason **/
        "None",

        /** *passFailCriteria **/
        "sciclient RmRingMonCfg functions should fail when called with invalid parameters",

        /** cpuID **/
        SCI_APP_CORE_TYPE_R5F,

        /** printEnable **/
        SCI_APP_PRINT_ENABLE,

        /** testType **/
        (SCI_APP_TEST_TYPE_SANITY)
    },
    {
        /** enableTest **/
        SCI_APP_TEST_ENABLE,

        /** testCaseId **/
        12U,

        /** *reqId **/
        "PDK-14060",

        /** *testCaseName **/
        "Sciclient RmUdmap Negative Testcase",

        /** *userInfo **/
        "None",

        /** *disableReason **/
        "None",

        /** *passFailCriteria **/
        "sciclient RmUdmap functions should fail when called with invalid parameters",

        /** cpuID **/
        SCI_APP_CORE_TYPE_R5F,

        /** printEnable **/
        SCI_APP_PRINT_ENABLE,

        /** testType **/
        (SCI_APP_TEST_TYPE_SANITY)
    },
    {
        /** enableTest **/
        SCI_APP_TEST_ENABLE,

        /** testCaseId **/
        13U,

        /** *reqId **/
        "PDK-14061",

        /** *testCaseName **/
        "Sciclient RmSetProxy Negative Testcase",

        /** *userInfo **/
        "None",

        /** *disableReason **/
        "None",

        /** *passFailCriteria **/
        "sciclient RmSetProxy functions should fail when called with invalid parameters",

        /** cpuID **/
        SCI_APP_CORE_TYPE_R5F,

        /** printEnable **/
        SCI_APP_PRINT_ENABLE,

        /** testType **/
        (SCI_APP_TEST_TYPE_SANITY)
    },
#if defined(BUILD_MCU1_0)
    {
        /** enableTest **/
        SCI_APP_TEST_ENABLE,

        /** testCaseId **/
        14U,

        /** *reqId **/
        "PDK-14054",

        /** *testCaseName **/
        "Sciclient direct Negative Testcase",

        /** *userInfo **/
        "None",

        /** *disableReason **/
        "None",

        /** *passFailCriteria **/
        "sciclient direct functions should fail when \
         called with invalid parameters ",

        /** cpuID **/
        SCI_APP_CORE_TYPE_R5F,

        /** printEnable **/
        SCI_APP_PRINT_ENABLE,

        /** testType **/
        (SCI_APP_TEST_TYPE_SANITY)
    },
    {
        /** enableTest **/
        SCI_APP_TEST_ENABLE,

        /** testCaseId **/
        15U,

        /** *reqId **/
        "PDK-14056",

        /** *testCaseName **/
        "Sciclient PM Negative Testcase",

        /** *userInfo **/
        "None",

        /** *disableReason **/
        "None",

        /** *passFailCriteria **/
        "sciclient PM related functions should fail \
         when called with invalid parameters ",

        /** cpuID **/
        SCI_APP_CORE_TYPE_R5F,

        /** printEnable **/
        SCI_APP_PRINT_ENABLE,

        /** testType **/
        (SCI_APP_TEST_TYPE_SANITY)
    },
#endif
    {
        /** enableTest **/
        SCI_APP_TEST_ENABLE,

        /** testCaseId **/
        16U,

        /** *reqId **/
        "PDK-14057",

        /** *testCaseName **/
        "Sciclient procboot Negative Testcase",

        /** *userInfo **/
        "None",

        /** *disableReason **/
        "None",

        /** *passFailCriteria **/
        "sciclient procboot functions should fail \
         when called with invalid parameters ",

        /** cpuID **/
        SCI_APP_CORE_TYPE_R5F,

        /** printEnable **/
        SCI_APP_PRINT_ENABLE,

        /** testType **/
        (SCI_APP_TEST_TYPE_SANITY)
    },
    {
        /** enableTest **/
        SCI_APP_TEST_ENABLE,

        /** testCaseId **/
        17U,

        /** *reqId **/
        "PDK-14059",

        /** *testCaseName **/
        "Sciclient RM Negative Testcase",

        /** *userInfo **/
        "None",

        /** *disableReason **/
        "None",

        /** *passFailCriteria **/
        "sciclient RM related functions should fail \
         when called with invalid parameters ",

        /** cpuID **/
        SCI_APP_CORE_TYPE_R5F,

        /** printEnable **/
        SCI_APP_PRINT_ENABLE,

        /** testType **/
        (SCI_APP_TEST_TYPE_SANITY)
    },
    {
        /** enableTest **/
        SCI_APP_TEST_ENABLE,

        /** testCaseId **/
        18U,

        /** *reqId **/
        "PDK-14063",

        /** *testCaseName **/
        "Sciclient procboot Positive Testcase",

        /** *userInfo **/
        "None",

        /** *disableReason **/
        "None",

        /** *passFailCriteria **/
        "sciclient procboot functions should pass when \
         called with valid parameters",

        /** cpuID **/
        SCI_APP_CORE_TYPE_R5F,

        /** printEnable **/
        SCI_APP_PRINT_ENABLE,

        /** testType **/
        (SCI_APP_TEST_TYPE_SANITY)
    },
    {
        /** enableTest **/
        SCI_APP_TEST_ENABLE,

        /** testCaseId **/
        19U,

        /** *reqId **/
        "PDK-14064",

        /** *testCaseName **/
        "Sciclient procboot Negative Testcase",

        /** *userInfo **/
        "None",

        /** *disableReason **/
        "None",

        /** *passFailCriteria **/
        "sciclient procboot functions should fail when \
         called with invalid parameters",

        /** cpuID **/
        SCI_APP_CORE_TYPE_R5F,

        /** printEnable **/
        SCI_APP_PRINT_ENABLE,

        /** testType **/
        (SCI_APP_TEST_TYPE_SANITY)
    },
#if defined (BUILD_MCU1_0)
    {
        /** enableTest **/
        SCI_APP_TEST_ENABLE,

        /** testCaseId **/
        20U,

        /** *reqId **/
        "PDK-14062",

        /** *testCaseName **/
        "SCICLIENT PM and RM BoardCfg Negative Testcase",

        /** *userInfo **/
        "None",

        /** *disableReason **/
        "None",

        /** *passFailCriteria **/
        "SCICLIENT PM and RM BoardCfg functions should fail \
         when called with invalid parameters ",

        /** cpuID **/
        SCI_APP_CORE_TYPE_R5F,

        /** printEnable **/
        SCI_APP_PRINT_ENABLE,

        /** testType **/
        (SCI_APP_TEST_TYPE_SANITY)
    },
#endif
    {
        /** enableTest **/
        SCI_APP_TEST_ENABLE,

        /** testCaseId **/
        21U,

        /** *reqId **/
        "PDK-14129",

        /** *testCaseName **/
        "Sciclient rm irq Negative Testcase",

        /** *userInfo **/
        "None",

        /** *disableReason **/
        "None",

        /** *passFailCriteria **/
        "sciclient rm irq functions should fail when called \
         with invalid parameters ",

        /** cpuID **/
        SCI_APP_CORE_TYPE_R5F,

        /** printEnable **/
        SCI_APP_PRINT_ENABLE,

        /** testType **/
        (SCI_APP_TEST_TYPE_SANITY)
    },
    {
        /** enableTest **/
        SCI_APP_TEST_ENABLE,

        /** testCaseId **/
        22U,

        /** *reqId **/
        "PDK-14124",

        /** *testCaseName **/
        "Sciclient rmTranslateIntOutput Testcase",

        /** *userInfo **/
        "None",

        /** *disableReason **/
        "None",

        /** *passFailCriteria **/
        "sciclient rmTranslateIntOutput functions should fail when \
         called with invalid parameters and should pass when \
         called with valid parameters",

        /** cpuID **/
        SCI_APP_CORE_TYPE_R5F,

        /** printEnable **/
        SCI_APP_PRINT_ENABLE,

        /** testType **/
        (SCI_APP_TEST_TYPE_SANITY)
    },
    {
        /** enableTest **/
        SCI_APP_TEST_ENABLE,

        /** testCaseId **/
        23U,

        /** *reqId **/
        "PDK-14125",

        /** *testCaseName **/
        "Sciclient rmTranslateIrqInput Testcase",

        /** *userInfo **/
        "None",

        /** *disableReason **/
        "None",

        /** *passFailCriteria **/
        "sciclient rmTranslateIrqInput functions should fail when \
         called with invalid parameters and should pass when \
         called with valid parameters",

        /** cpuID **/
        SCI_APP_CORE_TYPE_R5F,

        /** printEnable **/
        SCI_APP_PRINT_ENABLE,

        /** testType **/
        (SCI_APP_TEST_TYPE_SANITY)
    },
    {
        /** enableTest **/
        SCI_APP_TEST_ENABLE,

        /** testCaseId **/
        24U,

        /** *reqId **/
        "PDK-14175",

        /** *testCaseName **/
        "Sciclient rmClearInterruptRouteTest Negative Testcase",

        /** *userInfo **/
        "None",

        /** *disableReason **/
        "None",

        /** *passFailCriteria **/
        "Sciclient rmClearInterruptRouteTest functions should fail when \
         the request parameter is set to NULL or called with invalid parameters ",

        /** cpuID **/
        SCI_APP_CORE_TYPE_R5F,

        /** printEnable **/
        SCI_APP_PRINT_ENABLE,

        /** testType **/
        (SCI_APP_TEST_TYPE_SANITY)
    },
    {
        /** enableTest **/
        SCI_APP_TEST_ENABLE,

        /** testCaseId **/
        25U,

        /** *reqId **/
        "PDK-14176",

        /** *testCaseName **/
        "Sciclient rmProgramInterruptRoute Negative Testcase",

        /** *userInfo **/
        "None",

        /** *disableReason **/
        "None",

        /** *passFailCriteria **/
        "Sciclient rmProgramInterruptRoute functions should fail when \
         the request parameter is set to NULL or called with invalid parameters ",

        /** cpuID **/
        SCI_APP_CORE_TYPE_R5F,

        /** printEnable **/
        SCI_APP_PRINT_ENABLE,

        /** testType **/
        (SCI_APP_TEST_TYPE_SANITY)
    } 
};

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Function Declarations                              */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                        Internal Function Declarations                      */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Internal Function Definitions                     */
/* ========================================================================== */

/* None */

#endif /* SCICLIENT_EXTENDED_UT_TESTS_H_ */

