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
 *  \file   osal_extended_testapp_hwi.c
 *
 *  \brief  OSAL Hwi Sub Module testcases file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "osal_extended_test.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define OSAL_APP_IRQ_SECONDARY_INT_NUM (29U)
/* C7x cores can serve only 64 interrupts, numbered 0 to 63. */
#if defined (BUILD_C7X)
#define INVALID_INT_NUM_C7X           (64U)
#endif
#define OSAL_APP_IRQ_INT_NUM           (28U)


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

volatile uint32_t gOsalAppFlagHwiTest = UFALSE;

/* ========================================================================== */
/*                           Function Declarations                            */
/* ========================================================================== */

/*
 * Description : Testing Null check for Hwi API
 */
static int32_t OsalApp_hwiNullTest(void);

/*
 * Description : Test posting of interrupts. 
 */
static int32_t OsalApp_hwiCreateAllocOvrflwTest(void);

/*
 * Description : Testing Negative test for API Hwi_delete
 */
static int32_t OsalApp_hwiDeleteNegativeTest(void);

/*
 * Description : Testing Negative test for API HwiP_create
 */
#if defined(BUILD_C7X) 
static int32_t OsalApp_hwiCreateNegativeTest(void);
#endif

/* ========================================================================== */
/*                       Internal Function Definitions                        */
/* ========================================================================== */

static void OsalApp_hwiIRQ(uintptr_t arg)
{
    gOsalAppFlagHwiTest = UTRUE;
}

static int32_t OsalApp_hwiNullTest(void)
{
    HwiP_Params      hwiParams;
    HwiP_Handle      hwiHandle = NULL_PTR;
    int32_t          result = osal_OK;

    HwiP_Params_init(&hwiParams);

    hwiHandle = HwiP_create(CSL_INVALID_VEC_ID, NULL_PTR, NULL_PTR);
#if defined(BUILD_MCU)
    if(NULL_PTR != hwiHandle)
    {
        result = osal_FAILURE;
    }
#else
    if(NULL_PTR == hwiHandle)
    {
        result = osal_FAILURE;
    }
#endif
    if(NULL_PTR != hwiHandle)
    {
        if(HwiP_OK != HwiP_delete(hwiHandle))
        {
            result = osal_FAILURE;
        }
    }
    if(osal_OK == result)
    {
        if(NULL_PTR != HwiP_createDirect(CSL_INVALID_VEC_ID, NULL_PTR, NULL_PTR))
        {
            result = osal_FAILURE;
        }
    }

    if(osal_OK == result)
    {
        if(HwiP_OK == HwiP_delete(NULL_PTR))
        {
            result = osal_FAILURE;
        }
    }
    
    if(osal_OK != result)
    {
        OSAL_log("\n HwiP Null test failed!\n");
    }
    else
    {
        OSAL_log("\n HwiP Null test passed!\n");
    }

    return result;
}

static int32_t OsalApp_hwiCreateAllocOvrflwTest()
{
    HwiP_Params hwiParams;
    HwiP_Handle handle1, handle2;
    int32_t result = osal_OK;

    HwiP_Params_init(&hwiParams);

    /* Create 2 HwiP to register a change in peakHandles */
    handle1 = HwiP_create(OSAL_APP_IRQ_INT_NUM, (HwiP_Fxn)OsalApp_hwiIRQ, &hwiParams);
    handle2 = HwiP_createDirect(OSAL_APP_IRQ_SECONDARY_INT_NUM, (HwiP_DirectFxn)OsalApp_hwiIRQ, &hwiParams);

    /* handle2 is not deleted for C7x as HwiP_createDirect returns NULL for C7x */
#if defined(BUILD_C7X)
    if((NULL_PTR == handle1) || (NULL_PTR != handle2))
#else
    if((NULL_PTR == handle1) || (NULL_PTR == handle2) || (HwiP_OK != HwiP_delete(handle2)))
#endif
    {
        result = osal_FAILURE;
    }

    if(osal_OK == result)
    {
        HwiP_post(OSAL_APP_IRQ_INT_NUM);
        /* Wait till the interupt is hit */
        while(UFALSE == gOsalAppFlagHwiTest)
        {
            /* Do nothing */
        }
        gOsalAppFlagHwiTest = UFALSE;
        if(HwiP_OK != HwiP_delete(handle1))
        {
            result = osal_FAILURE;
        }
    }
    if(osal_OK != result)
    {
        OSAL_log("\n HwiP create Alloc overflow test failed!\n");
    }

    return result;
}

static int32_t OsalApp_hwiDeleteNegativeTest(void)
{
    HwiP_Params    hwiParams;
    HwiP_Handle    handle;
    int32_t        result = osal_OK;
    uint32_t       count = 0U;
    
    HwiP_Params_init(&hwiParams);
    
    handle = HwiP_create(OSAL_APP_IRQ_INT_NUM, (HwiP_Fxn)OsalApp_hwiIRQ, &hwiParams);
    
    /* Here handleAddr is used to get the memory location of the handle
     * we are corrupting the content of the handle and passing in a corrupt handle to the driver
     * to test negative condition for HwiP_delete API
     */
    uint32_t *handleAddr = (uint32_t *)handle, temp;
    temp = (*handleAddr);
    (*handleAddr) = 0U;
    
    if((NULL_PTR == handle) || (HwiP_OK == HwiP_delete(handle)))
    {
        result = osal_FAILURE;
    }

    /* Restore the value in the handle and delete the created Hwi. */
    *handleAddr = temp;
    if((osal_OK != result) || (HwiP_OK != HwiP_delete(handle)))
    {
        result = osal_FAILURE;
    }

    /* This handle is already deleted, but we are setting the 
     * isUsed parameter to 1(forced corruption), to see how the driver reacts. */
    if(osal_OK == result)
    {
        for(count = 0U; count < 2U; count++)
        {
            *handleAddr = 1U;
            if(HwiP_OK != HwiP_delete(handle))
            {
                break;
            }
        }
    }

    if(osal_OK == result)
    {
        OSAL_log("\n Hwi Delete negative test passed!\n");
    }
    else
    {
        OSAL_log("\n Hwi Delete negative test failed!\n");
    }
    
    return result;
}

#if defined(BUILD_C7X) 
int32_t  OsalApp_hwiCreateNegativeTest()
{
    HwiP_Params hwiParams;
    HwiP_Handle handle;
    int32_t result = osal_OK;

    HwiP_Params_init(&hwiParams); 
    
    hwiParams.priority  = 0U;
    hwiParams.enableIntr  = 0U;
    
    /*when OSAL_APP_IRQ_INT_NUM 64 for c7x,Hwi_construct API will fails
    and HwiP_create API will return NULL_PTR */
    handle = HwiP_create(INVALID_INT_NUM_C7X, (HwiP_Fxn)OsalApp_hwiIRQ, &hwiParams);
    
    if (NULL_PTR != handle)
    {
       result = osal_FAILURE;
    }
    
    if(osal_OK == result)
    {
        OSAL_log("\n Hwi Create negative test passed!\n");
    }
    else
    {
        OSAL_log("\n Hwi Create negative test failed!\n");
    }
    return result;
  
}
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t OsalApp_hwiTests(void)
{
    int32_t result = osal_OK;

    #if defined(BUILD_C7X) 
    result += OsalApp_hwiCreateNegativeTest();
    #endif
    result += OsalApp_hwiCreateAllocOvrflwTest();
    result += OsalApp_hwiNullTest();
    result += OsalApp_hwiDeleteNegativeTest();

    if(osal_OK == result)
    {
        OSAL_log("\n All HwiP tests have Passed!!\n");
    }
    else
    {
        OSAL_log("\n Some or all HwiP tests have Failed!!\n");
    }

    return result;
}

