/*
 * Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com/
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of
 * its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 *  \file   osal_extended_testapp_archutils.c
 *
 *  \brief  OSAL archutils Sub Module testcase for c7x file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "osal_extended_test.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define OSAL_APP_IRQ_INT_NUM           (28U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                           Function Declarations                            */
/* ========================================================================== */

/*
 * Description: Testing Arch utils API for c7x
 */
static int32_t OsalApp_archUtilsGeneralTest(void);

/* ========================================================================== */
/*                    Internal Function Definitions                           */
/* ========================================================================== */

static void OsalApp_hwiIRQ(uintptr_t arg)
{
    /* Do Nothing */
}

static int32_t OsalApp_archUtilsGeneralTest(void)
{
    HwiP_Params     hwiParams;
    HwiP_Handle     hwiHandle;
    uintptr_t       val = NULL;
    uint32_t        intNum = OSAL_APP_IRQ_INT_NUM;
    int32_t         result = osal_OK;

    HwiP_Params_init(&hwiParams);
    
    if(CSL_INVALID_EVENT_ID != OsalArch_getEventId(intNum))
    {
        result = osal_FAILURE;
    }
    if(NULL_PTR != OsalArch_HwiPCreate(intNum, OsalApp_hwiIRQ, NULL_PTR))
    {
        result = osal_FAILURE;
    }
    hwiHandle = OsalArch_HwiPCreate(intNum, OsalApp_hwiIRQ, &hwiParams);
    if((NULL_PTR == hwiHandle) || (NULL_PTR != OsalArch_getHandle(intNum)))
    {
        result = osal_FAILURE;
    }

    osalArch_TimestampCcntAutoRefresh(val);

    OsalArch_enableInterrupt(intNum);

    OsalArch_globalDisableInterrupt();

    OsalArch_globalRestoreInterrupt(val);
    
    if(CSL_PASS == OsalArch_postInterrupt(intNum))
    {
        result = osal_FAILURE;
    }

    OsalArch_clearInterrupt(intNum);

    OsalArch_disableInterrupt(intNum);

    if(HwiP_OK != OsalArch_HwiPDelete(hwiHandle))
    {
        result = osal_FAILURE;
    }

    return result;
}

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t OsalApp_ArchutilsTests(void)
{
    int32_t result = osal_OK;
    
    result += OsalApp_archUtilsGeneralTest();
    
    if(osal_OK == result)
    {
        OSAL_log("\n All Arch utils tests for c7x have passed!\n");
    }
    else
    {
        OSAL_log("\n Some or All Arch utils tests for c7x have failed!\n");
    }
    
    return result;
}
