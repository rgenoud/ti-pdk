/*
 *  Copyright (c) Texas Instruments Incorporated 2023-2024
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
 */

/**
 *  \file udma_test_event_neg.c
 *
 *  \brief File containing UDMA negative test cases for UDMA event APIs.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <udma_test.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/*
 * Test Case Description: Verifies the function Udma_eventRegister for
 * 1)Test scenario 1: Check when driver handle, event Handle and eventPrms are
 *                    NULL.
 * 2)Test scenario 2: Check when driver handle and event Handle are NULL.
 * 3)Test scenario 3: Check when driver handle and eventPrms are NULL.
 * 4)Test scenario 4: Check when driver handle is NULL.
 * 5)Test scenario 5: Check when event handle and eventPrms are NULL.
 * 6)Test scenario 6: Check when event handle is NULL.
 * 7)Test scenario 7: Check when event Prms is NULL.
 * 8)Test scenario 8: Check when drvInitDone is UDMA_DEINIT_DONE.
 * 9)Test scenario 9: Check to print error message "[Error] Event resource
 *                    allocation failed.
 */
int32_t UdmaTestEventRegisterNeg(UdmaTestTaskObj *taskObj)
{
    int32_t              retVal = UDMA_SOK;
    Udma_EventHandle     eventHandle;
    Udma_EventPrms       eventPrms;
    struct Udma_EventObj eventObj;
    Udma_DrvHandle       drvHandle;
    uint32_t             instId;
    struct Udma_DrvObj   backUpDrvObj;
    struct Udma_ChObj    chObj;

    GT_1trace(taskObj->traceMask, GT_INFO1,
              " |TEST INFO|:: Task:%d: UDMA EventRegister negative Testcase ::\r\n",
              taskObj->taskId);

    /* Test scenario 1: Check when driver handle, event Handle and eventPrms
     *                  are NULL */
    UdmaEventPrms_init(&eventPrms);
    drvHandle   = (Udma_DrvHandle) NULL_PTR;
    eventHandle = (Udma_EventHandle) NULL_PTR;
    retVal      = Udma_eventRegister(drvHandle, eventHandle, NULL );
    if(UDMA_SOK != retVal)
    {
        retVal = UDMA_SOK;
    }
    else
    {
        GT_0trace(taskObj->traceMask, GT_ERR," |TEST INFO|:: FAIL:: UDMA::"
                  " EventRegister::Neg:: Check when driver handle, event Handle"
                  " and eventPrms are NULL!!\n");
        retVal = UDMA_EFAIL;
    }

    if(UDMA_SOK == retVal)
    {
        /* Test scenario 2: Check when driver handle and event handle are NULL */
        drvHandle   = (Udma_DrvHandle) NULL_PTR;
        eventHandle = (Udma_EventHandle) NULL_PTR;
        retVal      = Udma_eventRegister(drvHandle, eventHandle, &eventPrms);
        if(UDMA_SOK != retVal)
        {
            retVal = UDMA_SOK;
        }
        else
        {
            GT_0trace(taskObj->traceMask, GT_ERR," |TEST INFO|:: FAIL:: UDMA::"
                      " EventRegister:: Neg:: Check when driver handle and"
                      " event handle are NULL!!\n");
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        /* Test scenario 3: Check when driver handle and eventPrms are NULL */
        drvHandle   = (Udma_DrvHandle) NULL_PTR;
        eventHandle = &eventObj;
        retVal      = Udma_eventRegister(drvHandle, eventHandle, NULL);
        if(UDMA_SOK != retVal)
        {
            retVal = UDMA_SOK;
        }
        else
        {
            GT_0trace(taskObj->traceMask, GT_ERR," |TEST INFO|:: FAIL:: UDMA::"
                      " EventRegister:: Neg:: Check when driver handle and"
                      " eventPrms are NULL!!\n");
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        /* Test scenario 4: Check when driver handle is NULL */
        drvHandle   = (Udma_DrvHandle) NULL_PTR;
        eventHandle = &eventObj;
        retVal      = Udma_eventRegister(drvHandle, eventHandle, &eventPrms);
        if(UDMA_SOK != retVal)
        {
            retVal = UDMA_SOK;
        }
        else
        {
            GT_0trace(taskObj->traceMask, GT_ERR," |TEST INFO|:: FAIL:: UDMA::"
                      " EventRegister:: Neg:: Check when driver handle is NULL!!\n");
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        /* Test scenario 5: Check when event handle and eventPrms are NULL */
        instId      = UDMA_TEST_INST_ID_MAIN_0;
        drvHandle   = &taskObj->testObj->drvObj[instId];
        eventHandle = (Udma_EventHandle) NULL_PTR;
        retVal      = Udma_eventRegister(drvHandle, eventHandle, NULL);
        if(UDMA_SOK != retVal)
        {
            retVal = UDMA_SOK;
        }
        else
        {
            GT_0trace(taskObj->traceMask, GT_ERR," |TEST INFO|:: FAIL:: UDMA::"
                      " EventRegister:: Neg:: Check when event handle and"
                      " eventPrms are NULL!!\n");
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        /* Test scenario 6: Check when event handle is NULL */
        eventHandle = (Udma_EventHandle) NULL_PTR ;
        retVal      = Udma_eventRegister(drvHandle, eventHandle, NULL);
        if(UDMA_SOK != retVal)
        {
            retVal = UDMA_SOK;
        }
        else
        {
            GT_0trace(taskObj->traceMask, GT_ERR," |TEST INFO|:: FAIL:: UDMA::"
                      " EventRegister:: Neg:: Check when event handle is NULL!!\n");
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        /* Test scenario 7: Check when event Prms is NULL */
        eventHandle = &eventObj;
        retVal      = Udma_eventRegister(drvHandle, eventHandle, NULL);
        if(UDMA_SOK != retVal)
        {
            retVal = UDMA_SOK;
        }
        else
        {
            GT_0trace(taskObj->traceMask, GT_ERR," |TEST INFO|:: FAIL:: UDMA::"
                      " EventRegister:: Neg:: Check when event handle is NULL!!\n");
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        /* Test scenario 8: Check when drvInitDone is UDMA_DEINIT_DONE */
        backUpDrvObj           = taskObj->testObj->drvObj[instId];
        drvHandle              = &taskObj->testObj->drvObj[instId];
        drvHandle->drvInitDone = UDMA_DEINIT_DONE;
        retVal                 = Udma_eventRegister(drvHandle, eventHandle, &eventPrms);
        if(UDMA_SOK != retVal)
        {
            retVal = UDMA_SOK;
        }
        else
        {
            GT_0trace(taskObj->traceMask, GT_ERR," |TEST INFO|:: FAIL:: UDMA::"
                      " EventRegister:: Neg:: Check when drvInitDone is "
                      " UDMA_DEINIT_DONE!!\n");
            retVal = UDMA_EFAIL;
        }
        taskObj->testObj->drvObj[instId] = backUpDrvObj;
    }

    if(UDMA_SOK == retVal)
    {
        /* Test scenario 9: Check to print error message "[Error] Event resource
         *                   allocation failed" */
        backUpDrvObj                                  = taskObj->testObj->drvObj[instId];
        drvHandle                                     = &taskObj->testObj->drvObj[instId];
        eventPrms.chHandle                            = &chObj;
        instId                                        = UDMA_TEST_INST_ID_MAIN_0;
        drvHandle                                     = &taskObj->testObj->drvObj[instId];
        drvHandle->initPrms.rmInitPrms.numGlobalEvent = 0U;
        retVal                                        = Udma_eventRegister(drvHandle,
                                                                           eventHandle,
                                                                           &eventPrms);
        if(UDMA_SOK != retVal)
        {
            retVal = UDMA_SOK;
        }
        else
        {
            GT_0trace(taskObj->traceMask, GT_ERR," |TEST INFO|:: FAIL:: UDMA:: EventRegister::"
                      " Neg:: Check to print error message [Error] Event resource"
                      " allocation failed !!\n");
            retVal = UDMA_EFAIL;
        }
        taskObj->testObj->drvObj[instId] = backUpDrvObj;
    }

    return (retVal);
}

/*
 * Test Case Description: Verifies the function Udma_eventUnRegister for
 * 1)Test scenario 1: Check when eventHandle is NULL.
 * 2)Test scenario 2: Check when drvInitDone is UDMA_INIT_DONE.
 * 3)Test scenario 3: Check to get print message [Error] Free Event resource failed!!.
 */
int32_t UdmaTestEventUnRegisterNeg(UdmaTestTaskObj *taskObj)
{
    int32_t              retVal = UDMA_SOK;
    Udma_EventHandle     eventHandle;
    struct Udma_EventObj eventObj;
    uint32_t             instId;
    struct Udma_DrvObj   backUpDrvObj;
    struct Udma_ChObj    chObj;

    GT_1trace(taskObj->traceMask, GT_INFO1,
              " |TEST INFO|:: Task:%d: UDMA EventUnRegister negative Testcase ::\r\n",
              taskObj->taskId);

    /* Test scenario 1: Check when eventHandle is NULL */
    eventHandle = (Udma_EventHandle) NULL_PTR;
    retVal      = Udma_eventUnRegister(eventHandle);
    if(UDMA_SOK != retVal)
    {
        retVal = UDMA_SOK;
    }
    else
    {
        GT_0trace(taskObj->traceMask, GT_ERR," |TEST INFO|:: FAIL:: UDMA::"
                  " EventUnRegister:: Neg:: Check when eventHandle is NULL !!\n");
        retVal = UDMA_EFAIL;
    }

    if(UDMA_SOK == retVal)
    {
        /* Test scenario 2: Check when drvInitDone is UDMA_INIT_DONE */
        instId                              = UDMA_TEST_INST_ID_MAIN_0;
        eventHandle                         = &eventObj;
        backUpDrvObj                        = taskObj->testObj->drvObj[instId];
        eventHandle->drvHandle              = &taskObj->testObj->drvObj[instId];
        eventHandle->drvHandle->drvInitDone = UDMA_DEINIT_DONE;
        retVal                              = Udma_eventUnRegister(eventHandle);
        if(UDMA_SOK != retVal)
        {
            retVal = UDMA_SOK;
        }
        else
        {
            GT_0trace(taskObj->traceMask, GT_ERR," |TEST INFO|:: FAIL:: UDMA::"
                      " EventUnRegister:: Neg:: Check when drvInitDone is "
                      " UDMA_INIT_DONE !!\n");
            retVal = UDMA_EFAIL;
        }
        taskObj->testObj->drvObj[instId] = backUpDrvObj;
    }

    if(UDMA_SOK == retVal)
    {
        /* Test scenario 3: Check to get print message [Error] Free Event resource failed!! */
        eventHandle->eventInitDone               = UDMA_INIT_DONE;
        eventHandle->eventPrms.chHandle          = &chObj;
        eventHandle->globalEvent                 = UDMA_EVENT_INVALID;
        eventHandle->irIntrNum                   = UDMA_INTR_INVALID;
        eventHandle->vintrNum                    = UDMA_EVENT_INVALID;
        eventHandle->vintrBitNum                 = UDMA_EVENT_INVALID;
        eventHandle->coreIntrNum                 = UDMA_INTR_INVALID;
        eventHandle->eventPrms.masterEventHandle = (Udma_EventHandle) NULL_PTR;
        retVal                                   = Udma_eventUnRegister(eventHandle);
        if(UDMA_SOK != retVal)
        {
            retVal = UDMA_SOK;
        }
        else
        {
            GT_0trace(taskObj->traceMask, GT_ERR," |TEST INFO|:: FAIL:: UDMA::"
                      " EventUnRegister:: Neg:: to get print message [Error] "
                      " Free Event resource failed!!\n");
            retVal = UDMA_EFAIL;
        }
    }

    return (retVal);
}

/*
 * Test Case Description: Verifies the function Udma_eventGetId for
 * 1)Test scenario 1: Check when eventHandle is NULL.
 * 2)Test scenario 2: Check when eventInitDone is UDMA_DEINIT_DONE.
 * 3)Test scenario 3: Check when drvHandle is NULL.
 */
int32_t UdmaTestEventGetIdNeg(UdmaTestTaskObj *taskObj)
{
    uint32_t             evtNum = UDMA_EVENT_INVALID;
    int32_t              retVal = UDMA_SOK;
    Udma_EventHandle     eventHandle;
    struct Udma_EventObj eventObj;

    GT_1trace(taskObj->traceMask, GT_INFO1,
              " |TEST INFO|:: Task:%d: UDMA EventGetId negative Testcase ::\r\n",
              taskObj->taskId);

    /* Test scenario 1: Check when eventHandle is NULL */
    eventHandle = (Udma_EventHandle) NULL_PTR;
    evtNum      = Udma_eventGetId(eventHandle);
    if(UDMA_EVENT_INVALID == evtNum)
    {
        retVal = UDMA_SOK;
    }
    else
    {
        GT_0trace(taskObj->traceMask, GT_ERR," |TEST INFO|:: FAIL:: UDMA::"
                  " EventGetId:: Neg:: Check when eventHandle is NULL!!\n");
        retVal = UDMA_EFAIL;
    }

    if(UDMA_SOK == retVal)
    {
        /* Test scenario 2: Check when eventInitDone is UDMA_DEINIT_DONE */
        eventHandle                = &eventObj;
        eventHandle->eventInitDone = UDMA_DEINIT_DONE;
        retVal                     = Udma_eventGetId(eventHandle);
        if(UDMA_EVENT_INVALID == evtNum)
        {
            retVal = UDMA_SOK;
        }
        else
        {
            GT_0trace(taskObj->traceMask, GT_ERR," |TEST INFO|:: FAIL:: UDMA::"
                      " EventGetId:: Neg:: Check when eventInitDone is "
                      " UDMA_DEINIT_DONE !!\n");
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        /* Test scenario 3: Check when drvHandle is NULL */
        eventHandle->eventInitDone = UDMA_INIT_DONE;
        eventHandle->drvHandle     = NULL_PTR;
        evtNum                     = Udma_eventGetId(eventHandle);
        if(UDMA_EVENT_INVALID == evtNum)
        {
            retVal = UDMA_SOK;
        }
        else
        {
            GT_0trace(taskObj->traceMask, GT_ERR," |TEST INFO|:: FAIL:: UDMA::"
                      " EventGetId:: Neg:: Check when drvHandle is NU!!\n");
            retVal = UDMA_EFAIL;
        }
    }

    return retVal;
}

/*
 * Test Case Description: Verifies the function Udma_eventDisable for
 * 1)Test scenario 1: Check when eventHandle is NULL.
 * 2)Test scenario 2: Check when eventInitDone is UDMA_DEINIT_DONE.
 * 3)Test scenario 3: Check when drvHandle is NULL.
 */
int32_t UdmaTestEventDisableNeg(UdmaTestTaskObj *taskObj)
{
    int32_t              retVal = UDMA_SOK;
    Udma_EventHandle     eventHandle;
    struct Udma_EventObj eventObj;

    GT_1trace(taskObj->traceMask, GT_INFO1,
              " |TEST INFO|:: Task:%d: UDMA EventDisable negative Testcase ::\r\n",
              taskObj->taskId);

    /* Test scenario 1: Check when eventHandle is NULL */
    eventHandle = (Udma_EventHandle) NULL_PTR;
    retVal      = Udma_eventDisable(eventHandle);
    if(UDMA_SOK != retVal)
    {
        retVal = UDMA_SOK;
    }
    else
    {
        GT_0trace(taskObj->traceMask, GT_ERR," |TEST INFO|:: FAIL:: UDMA::"
                  " EventDisable:: Neg:: Check when eventHandle is NULL!!\n");
        retVal = UDMA_EFAIL;
    }

    if(UDMA_SOK == retVal)
    {
        /* Test scenario 2: Check when eventInitDone is UDMA_DEINIT_DONE */
        eventHandle                = &eventObj;
        eventHandle->eventInitDone = UDMA_DEINIT_DONE;
        retVal                     = Udma_eventDisable(eventHandle);
        if(UDMA_SOK != retVal)
        {
            retVal = UDMA_SOK;
        }
        else
        {
            GT_0trace(taskObj->traceMask, GT_ERR," |TEST INFO|:: FAIL:: UDMA::"
                      " EventDisable:: Neg:: Check when eventInitDone is "
                      " UDMA_DEINIT_DONE !!\n");
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        /* Test scenario 3: Check when drvHandle is NULL */
        eventHandle->eventInitDone = UDMA_INIT_DONE;
        eventHandle->drvHandle     = NULL_PTR;
        retVal                     = Udma_eventDisable(eventHandle);
        if(UDMA_SOK != retVal)
        {
            retVal = UDMA_SOK;
        }
        else
        {
            GT_0trace(taskObj->traceMask, GT_ERR," |TEST INFO|:: FAIL:: UDMA::"
                      " EventDisable:: Neg:: Check when drvHandle is NU!!\n");
            retVal = UDMA_EFAIL;
        }
    }

    return retVal;
}

/*
 * Test Case Description: Verifies the function Udma_eventEnable for
 * 1)Test scenario 1: Check when eventHandle is NULL.
 * 2)Test scenario 2: Check when eventInitDone is UDMA_DEINIT_DONE.
 * 3)Test scenario 3: Check when drvHandle is NULL.
 */
int32_t UdmaTestEvenEnableNeg(UdmaTestTaskObj *taskObj)
{
    int32_t              retVal = UDMA_SOK;
    Udma_EventHandle     eventHandle;
    struct Udma_EventObj eventObj;

    GT_1trace(taskObj->traceMask, GT_INFO1,
              " |TEST INFO|:: Task:%d: UDMA EventEnable negative Testcase ::\r\n",
              taskObj->taskId);

    /* Test scenario 1: Check when eventHandle is NULL */
    eventHandle = (Udma_EventHandle) NULL_PTR;
    retVal      = Udma_eventEnable(eventHandle);
    if(UDMA_SOK != retVal)
    {
        retVal = UDMA_SOK;
    }
    else
    {
        GT_0trace(taskObj->traceMask, GT_ERR," |TEST INFO|:: FAIL:: UDMA::"
                  " EventEnable:: Neg:: Check when eventHandle is NULL!!\n");
        retVal = UDMA_EFAIL;
    }

    if(UDMA_SOK == retVal)
    {
        /* Test scenario 2: Check when eventInitDone is UDMA_DEINIT_DONE */
        eventHandle                = &eventObj;
        eventHandle->eventInitDone = UDMA_DEINIT_DONE;
        retVal                     = Udma_eventEnable(eventHandle);
        if(UDMA_SOK != retVal)
        {
            retVal = UDMA_SOK;
        }
        else
        {
            GT_0trace(taskObj->traceMask, GT_ERR," |TEST INFO|:: FAIL:: UDMA::"
                      " EventEnable:: Neg:: Check when eventInitDone is "
                      " UDMA_DEINIT_DONE !!\n");
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        /* Test scenario 3: Check when drvHandle is NULL */
        eventHandle->eventInitDone = UDMA_INIT_DONE;
        eventHandle->drvHandle     = NULL_PTR;
        retVal                     = Udma_eventEnable(eventHandle);
        if(UDMA_SOK != retVal)
        {
            retVal = UDMA_SOK;
        }
        else
        {
            GT_0trace(taskObj->traceMask, GT_ERR," |TEST INFO|:: FAIL:: UDMA::"
                      " EventEnable:: Neg:: Check when drvHandle is NU!!\n");
            retVal = UDMA_EFAIL;
        }
    }

    return retVal;
}

/*
 * Test Case Description: Verifies the function Udma_eventGetGlobalHandle for
 * 1)Test scenario 1: Check when eventHandle is NULL.
 * 2)Test scenario 2: Check when drvInitDone is UDMA_DEINIT_DONE.
 */
int32_t UdmaTestEventGetGlobalNeg(UdmaTestTaskObj *taskObj)
{
    int32_t              retVal      = UDMA_SOK;
    Udma_EventHandle     eventHandle = NULL_PTR;
    Udma_DrvHandle       drvHandle;
    uint32_t             instId;
    struct Udma_DrvObj   backUpDrvObj;

    GT_1trace(taskObj->traceMask, GT_INFO1,
              " |TEST INFO|:: Task:%d: UDMA EventGetGlobal negative Testcase ::\r\n",
              taskObj->taskId);

    /* Test scenario 1: Check when driver Handle is NULL */
    drvHandle   = (Udma_DrvHandle) NULL_PTR;
    eventHandle = Udma_eventGetGlobalHandle(drvHandle);
    if(NULL_PTR == eventHandle)
    {
        retVal = UDMA_SOK;
    }
    else
    {
        GT_0trace(taskObj->traceMask, GT_ERR," |TEST INFO|:: FAIL:: UDMA::"
                  " EventGetGlobal:: Neg:: Check when driver Handle is NULL!!\n");
        retVal = UDMA_EFAIL;
    }

    if(UDMA_SOK == retVal)
    {
        /* Test scenario 2: Check when drvInitDone is UDMA_DEINIT_DONE */
        instId                 = UDMA_TEST_INST_ID_MAIN_0;
        backUpDrvObj           = taskObj->testObj->drvObj[instId];
        drvHandle              = &taskObj->testObj->drvObj[instId];
        drvHandle->drvInitDone = UDMA_DEINIT_DONE;
        eventHandle            = Udma_eventGetGlobalHandle(drvHandle);
        if(NULL_PTR == eventHandle)
        {
            retVal = UDMA_SOK;
        }
        else
        {
            GT_0trace(taskObj->traceMask, GT_ERR," |TEST INFO|:: FAIL:: UDMA::"
                      " EventGetGlobal:: Neg:: Check when drvInitDone is "
                      " UDMA_DEINIT_DONE !!\n");
            retVal = UDMA_EFAIL;
        }
        taskObj->testObj->drvObj[instId] = backUpDrvObj;
    }

    return retVal;
}

/*
 * Test Case Description: Verifies the function Udma_eventGetRxFlowIdFwStatus for
 * 1)Test scenario 1: Check eventHandle and Status are NULL.
 * 2)Test scenario 2: Check when eventHandle is NULL.
 * 3)Test scenario 3: Check when Status is NULL.
 * 4)Test scenario 4: Check when eventInitDone is UDMA_DEINIT_DONE.
 * 5)Test scenario 5: Check when drvHandle is NULL.
 * 6)Test scenario 6: Check when drvInitDone is UDMA_DEINIT_DONE
 */
int32_t UdmaTestEventGetRxFlowStatusNeg(UdmaTestTaskObj *taskObj)
{
    int32_t                    retVal = UDMA_SOK;
    Udma_EventHandle           eventHandle;
    uint32_t                   instId;
    struct Udma_DrvObj         backUpDrvObj;
    Udma_EventRxFlowIdFwStatus status;
    struct Udma_EventObj       eventObj;

    GT_1trace(taskObj->traceMask, GT_INFO1,
              " |TEST INFO|:: Task:%d: UDMA EventGetRxFlowStatus negative Testcase ::\r\n",
              taskObj->taskId);

    /* Test scenario 1: Check eventHandle and Status are NULL */
    eventHandle = (Udma_EventHandle) NULL_PTR;
    retVal      = Udma_eventGetRxFlowIdFwStatus(eventHandle, NULL);
    if(UDMA_SOK != retVal)
    {
        retVal = UDMA_SOK;
    }
    else
    {
        GT_0trace(taskObj->traceMask, GT_ERR," |TEST INFO|:: FAIL:: UDMA::"
                  " EventGetRxFlowStatus:: Neg:: Check eventHandle Status"
                  " are NULL !!\n");
        retVal = UDMA_EFAIL;
    }

    if(UDMA_SOK == retVal)
    {
        /* Test scenario 2: Check when eventHandle is NULL */
        retVal = Udma_eventGetRxFlowIdFwStatus(eventHandle, &status);
        if(UDMA_SOK != retVal)
        {
            retVal = UDMA_SOK;
        }
        else
        {
            GT_0trace(taskObj->traceMask, GT_ERR," |TEST INFO|:: FAIL:: UDMA::"
                      " EventGetRxFlowStatus:: Neg:: Check when eventHandle"
                      " is NULL!!\n");
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        /* Test scenario 3: Check when Status is NULL */
        eventHandle                = &eventObj;
        eventHandle->eventInitDone = UDMA_INIT_DONE;
        retVal                     = Udma_eventGetRxFlowIdFwStatus(eventHandle, NULL);
        if(UDMA_SOK != retVal)
        {
            retVal = UDMA_SOK;
        }
        else
        {
            GT_0trace(taskObj->traceMask, GT_ERR," |TEST INFO|:: FAIL:: UDMA::"
                      " EventGetRxFlowStatus:: Neg:: Check when Status is NULL!!\n");
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        /* Test scenario 4: Check when eventInitDone is UDMA_DEINIT_DONE */
        eventHandle->eventInitDone = UDMA_DEINIT_DONE;
        retVal                     = Udma_eventGetRxFlowIdFwStatus(eventHandle, &status);
        if(UDMA_SOK != retVal)
        {
            retVal = UDMA_SOK;
        }
        else
        {
            GT_0trace(taskObj->traceMask, GT_ERR," |TEST INFO|:: FAIL:: UDMA::"
                      " EventGetRxFlowStatus:: Neg:: Check when eventInitDone is "
                      " UDMA_DEINIT_DONE!!\n");
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        /* Test scenario 5: Check when drvHandle is NULL */
        eventHandle->eventInitDone = UDMA_INIT_DONE;
        eventHandle->drvHandle     = NULL_PTR;
        retVal                     = Udma_eventGetRxFlowIdFwStatus(eventHandle, &status);
        if(UDMA_SOK != retVal)
        {
            retVal = UDMA_SOK;
        }
        else
        {
            GT_0trace(taskObj->traceMask, GT_ERR," |TEST INFO|:: FAIL:: UDMA::"
                      " EventGetRxFlowStatus:: Neg:: Check when drvHandle is NULL!!\n");
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        /* Test scenario 6:  Check when drvInitDone is UDMA_DEINIT_DONE */
        instId                              = UDMA_TEST_INST_ID_MAIN_0;
        backUpDrvObj                        = taskObj->testObj->drvObj[instId];
        eventHandle->drvHandle              = &taskObj->testObj->drvObj[instId];
        eventHandle->drvHandle->drvInitDone = UDMA_DEINIT_DONE;
        retVal                              = Udma_eventGetRxFlowIdFwStatus(eventHandle,
                                                                            &status);
        if(UDMA_SOK != retVal)
        {
            retVal = UDMA_SOK;
        }
        else
        {
            GT_0trace(taskObj->traceMask, GT_ERR," |TEST INFO|:: FAIL:: UDMA::"
                      " EventGetRxFlowStatus:: Neg:: Check when drvInitDone is "
                      " UDMA_DEINIT_DONE!!\n");
            retVal = UDMA_EFAIL;
        }
        taskObj->testObj->drvObj[instId] = backUpDrvObj;
    }

    return retVal;
}

/*
 * Test Case Description: Verifies the function Udma_eventRegister for
 * 1)Test scenario 1: Check when instType is UDMA_INST_ID_BCDMA_0.
 */
int32_t UdmaTestEventRegisterBcdmaTestNeg(UdmaTestTaskObj *taskObj)
{

    int32_t              retVal = UDMA_SOK;
    Udma_EventHandle     eventHandle;
    Udma_EventPrms       eventPrms;
    struct Udma_EventObj eventObj;
    Udma_DrvHandle       drvHandle;
    uint32_t             instId;
    struct Udma_ChObj    chObj;

    GT_1trace(taskObj->traceMask, GT_INFO1,
              " |TEST INFO|:: Task:%d: UDMA EventRegisterBcdmaTest negative Testcase ::\r\n",
              taskObj->taskId);

    /* Test scenario 1: Check when instType is UDMA_INST_ID_BCDMA_0 */
    UdmaEventPrms_init(&eventPrms);
    eventHandle         = &eventObj;
    instId              = UDMA_TEST_INST_ID_BCDMA_0;
    eventPrms.chHandle  = &chObj;
    drvHandle           = &taskObj->testObj->drvObj[instId];
    eventPrms.eventType = UDMA_EVENT_TYPE_TEARDOWN_PACKET;
    retVal              = Udma_eventRegister(drvHandle, eventHandle, &eventPrms);
    if(UDMA_SOK == retVal)
    {
        retVal = UDMA_SOK;
    }
    else
    {
        GT_0trace(taskObj->traceMask, GT_ERR," |TEST INFO|:: FAIL:: UDMA::"
                  " EventRegister:: Neg:: Check when instType is "
                  " UDMA_INST_ID_BCDMA_0 !!\n");
        retVal = UDMA_EFAIL;
    }

    return retVal;
}

/*
 * Test Case Description: Verifies the function Udma_eventUnRegister for
 * 1)Test scenario 1: Check when instType is UDMA_INST_ID_BCDMA_0.
 */
int32_t UdmaTestEventUnRegisterBcdmaTestNeg(UdmaTestTaskObj *taskObj)
{
    int32_t              retVal = UDMA_SOK;
    Udma_EventHandle     eventHandle;
    struct Udma_EventObj eventObj;
    uint32_t             instId;

    GT_1trace(taskObj->traceMask, GT_INFO1,
              " |TEST INFO|:: Task:%d: UDMA EventUnRegister negative Testcase ::\r\n",
              taskObj->taskId);

    /* Test scenario 1: Check when instType is UDMA_INST_ID_BCDMA_0 */
    instId                           = UDMA_TEST_INST_ID_BCDMA_0;
    eventHandle                      = &eventObj;
    eventHandle->drvHandle           = &taskObj->testObj->drvObj[instId];
    eventHandle->eventPrms.eventType = UDMA_EVENT_TYPE_TEARDOWN_PACKET;
    retVal                           = Udma_eventUnRegister(eventHandle);
    if(UDMA_SOK == retVal)
    {
        retVal = UDMA_SOK;
    }
    else
    {
        GT_0trace(taskObj->traceMask, GT_ERR," |TEST INFO|:: FAIL:: UDMA::"
                  " EventUnRegister:: Neg:: Check when instType is "
                  " UDMA_INST_ID_BCDMA_0 !!\n");
        retVal = UDMA_EFAIL;
    }

    return retVal;
}

