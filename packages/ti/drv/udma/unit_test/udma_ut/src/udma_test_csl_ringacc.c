/*
 *  Copyright (c) Texas Instruments Incorporated 2024
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
 *  \file udma_test_csl_ringacc.c
 *
 *  \brief File containing test cases for UDMA UTC related APIs.
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

static int32_t UdmaTestInitRingAcc(Udma_DrvHandle drvHandle, Udma_ChHandle chHandle, uint32_t elemCnt);
static int32_t UdmaTestDeInitRingAcc(Udma_ChHandle chHandle);

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

int32_t udmaTestCslRingAcc(UdmaTestTaskObj *taskObj)
{
    int32_t             retVal = UDMA_SOK;
    Udma_DrvHandle      drvHandle = &taskObj->testObj->drvObj[UDMA_TEST_INST_ID_MAIN_0];
    struct Udma_ChObj   chObj;
    Udma_ChHandle       chHandle  = &chObj;
    uint32_t            elemCnt   = 10U;
    uint32_t            ringMemSize = elemCnt * sizeof (uint64_t);
    uint64_t           *ringMem = Utils_memAlloc(UTILS_MEM_HEAP_ID_DDR, ringMemSize, UDMA_CACHELINE_ALIGNMENT);

    GT_1trace(taskObj->traceMask, GT_INFO1,
              " |TEST INFO|:: Task:%d: CSL RingAcc Test ::\r\n", taskObj->taskId);

    retVal = UdmaTestInitRingAcc(drvHandle, chHandle, elemCnt);

    /* Test CSL_ringaccGetRevision */
    if(UDMA_SOK == retVal)
    {
        GT_1trace(taskObj->traceMask, GT_INFO1,
                " |TEST INFO|:: Task:%d: CSL_ringaccGetRevision Testcase ::\r\n", taskObj->taskId);
        uint32_t rev = CSL_ringaccGetRevision(&drvHandle->raRegs);
        GT_1trace(taskObj->traceMask, GT_INFO1,
                " |TEST INFO|:: RING ACC VERSION: %u::\r\n", rev);
    }
    /* Test CSL_ringaccInitRingCfg */
    if(UDMA_SOK == retVal)
    {
        CSL_RingAccRingCfg ringCfg;
        GT_1trace(taskObj->traceMask, GT_INFO1,
                " |TEST INFO|:: Task:%d: CSL_ringaccInitRingCfg Testcase ::\r\n", taskObj->taskId);
        CSL_ringaccInitRingCfg(&ringCfg);
    }
    /* Test CSL_ringaccGetRingNum */
    if(UDMA_SOK == retVal)
    {
        GT_1trace(taskObj->traceMask, GT_INFO1,
                " |TEST INFO|:: Task:%d: CSL_ringaccGetRingNum Testcase ::\r\n", taskObj->taskId);
        uint32_t ringNum = CSL_ringaccGetRingNum(&chHandle->fqRing->cfg);
        GT_1trace(taskObj->traceMask, GT_INFO1,
                " |TEST INFO|:: Ring Number: %u::\r\n", ringNum);
    }
    /* Test CSL_ringaccGetCmdRingPtr */
    if(UDMA_SOK == retVal)
    {
        GT_1trace(taskObj->traceMask, GT_INFO1,
                " |TEST INFO|:: Task:%d: CSL_ringaccGetCmdRingPtr Testcase ::\r\n", taskObj->taskId);
        uint32_t loopCnt = 0U;
        while((UDMA_SOK == retVal) && (loopCnt < 100))
        {
            retVal = Udma_ringQueueRaw(chHandle->fqRing, (uint64_t)ringMem);
            if(UDMA_SOK == retVal)
            {
                loopCnt += 1;
            }
        }
        if(loopCnt <= elemCnt)
        {
            retVal = UDMA_SOK;
        }
        else
        {
            GT_1trace(taskObj->traceMask, GT_INFO1,
                    " |TEST INFO|:: Task:%d: FAIL :: CSL_ringaccGetCmdRingPtr Testcase ::\r\n", taskObj->taskId);
        }
        loopCnt = 0U;
        while((UDMA_SOK == retVal) && (loopCnt < 100))
        {
            retVal = Udma_ringFlushRaw(chHandle->fqRing, ringMem);
            if(UDMA_SOK == retVal)
            {
                loopCnt += 1;
            }
        }
        if(loopCnt <= elemCnt)
        {
            retVal = UDMA_SOK;
        }
        else
        {
            GT_1trace(taskObj->traceMask, GT_INFO1,
                    " |TEST INFO|:: Task:%d: FAIL :: CSL_ringaccGetCmdRingPtr Testcase: Udma_ringFlushRaw failed ::\r\n", taskObj->taskId);
        }
    }
    /* Test CSL_ringaccAckRspRing when cnt is 0 */
    if(UDMA_SOK == retVal)
    {
        CSL_RingAccRingCfg ringCfg;
        ringCfg.ringNum = UDMA_RING_INVALID;
        ringCfg.waiting = 0U;
        GT_1trace(taskObj->traceMask, GT_INFO1,
                " |TEST INFO|:: Task:%d: CSL_ringaccAckRspRing Testcase ::\r\n", taskObj->taskId);
        CSL_ringaccAckRspRing(&drvHandle->raRegs, &ringCfg, 0U);
        ringCfg.waiting += 1U;
        CSL_ringaccAckRspRing(&drvHandle->raRegs, &ringCfg, 0U);
    }
    /* Test CSL_ringaccGetRingIdx */
    if(UDMA_SOK == retVal)
    {
        GT_1trace(taskObj->traceMask, GT_INFO1,
                " |TEST INFO|:: Task:%d: CSL_ringaccGetRingIdx Testcase ::\r\n", taskObj->taskId);
        CSL_ringaccGetRingIdx(&drvHandle->raRegs, chHandle->fqRing->ringNum);
        CSL_ringaccGetRingIdx(&drvHandle->raRegs, UDMA_RING_INVALID);
    }
    /* Test CSL_ringaccGetRingHwIdx */
    if(UDMA_SOK == retVal)
    {
        GT_1trace(taskObj->traceMask, GT_INFO1,
                " |TEST INFO|:: Task:%d: CSL_ringaccGetRingHwIdx Testcase ::\r\n", taskObj->taskId);
        CSL_ringaccGetRingHwIdx(&drvHandle->raRegs, chHandle->fqRing->ringNum);
        CSL_ringaccGetRingHwIdx(&drvHandle->raRegs, UDMA_RING_INVALID);
    }
    /* Test CSL_ringaccGetRingOcc */
    if(UDMA_SOK == retVal)
    {
        GT_1trace(taskObj->traceMask, GT_INFO1,
                " |TEST INFO|:: Task:%d: CSL_ringaccGetRingOcc Testcase ::\r\n", taskObj->taskId);
        CSL_ringaccGetRingOcc(&drvHandle->raRegs, UDMA_RING_INVALID);
    }
    /* Test CSL_ringaccGetRingHwOcc */
    if(UDMA_SOK == retVal)
    {
        GT_1trace(taskObj->traceMask, GT_INFO1,
                " |TEST INFO|:: Task:%d: CSL_ringaccGetRingHwIdx Testcase ::\r\n", taskObj->taskId);
        CSL_ringaccGetRingHwOcc(&drvHandle->raRegs, UDMA_RING_INVALID);
    }
    /* Test CSL_ringaccPush64 */
    if(UDMA_SOK == retVal)
    {
        CSL_RingAccRingCfg ringCfg;
        ringCfg.elSz = 0U;
        GT_1trace(taskObj->traceMask, GT_INFO1,
                " |TEST INFO|:: Task:%d: CSL_ringaccGetRingHwIdx Testcase ::\r\n", taskObj->taskId);
        /* Test CSL_ringaccPeek64 when ring is empty */
        CSL_ringaccPeek64(&drvHandle->raRegs, &chHandle->fqRing->cfg, ringMem, NULL);
        /* Test CSL_ringaccPush64 when CSL_ringaccMemOpsFxnPtr is NULL */
        CSL_ringaccPush64(&drvHandle->raRegs, &chHandle->fqRing->cfg, ringMem[0], NULL);
        /* Test CSL_ringaccPush64 when ring elsz < sizeof(uint64_t) */
        CSL_ringaccPush64(&drvHandle->raRegs, &ringCfg, ringMem[0], NULL);
        /* Test CSL_ringaccPeek64 when CSL_ringaccMemOpsFxnPtr is NULL */
        CSL_ringaccPeek64(&drvHandle->raRegs, &chHandle->fqRing->cfg, ringMem, NULL);
        /* Test CSL_ringaccPeek64 when ring elsz < sizeof(uint64_t) */
        CSL_ringaccPeek64(&drvHandle->raRegs, &ringCfg, ringMem, NULL);
        /* Test CSL_ringaccPop64 when CSL_ringaccMemOpsFxnPtr is NULL */
        CSL_ringaccPop64(&drvHandle->raRegs, &chHandle->fqRing->cfg, ringMem, NULL);
    }

    retVal = UdmaTestDeInitRingAcc(chHandle);

    return (retVal);
}


static int32_t UdmaTestInitRingAcc(Udma_DrvHandle drvHandle, Udma_ChHandle chHandle, uint32_t elemCnt)
{
    int32_t           retVal  = UDMA_SOK;
    uint32_t          heapId  = UTILS_MEM_HEAP_ID_DDR;
    void             *ringMem = NULL;
    uint32_t          chType;
    Udma_ChPrms       chPrms;
    uint32_t          ringMemSize;
    uint32_t          ringMode;
    Udma_ChTxPrms     txChPrms;

    /* Allocate Ring Memory in heap */
    ringMode    = TISCI_MSG_VALUE_RM_RING_MODE_RING;
    ringMemSize = elemCnt * sizeof (uint64_t);
    ringMem     = Utils_memAlloc(heapId, ringMemSize, UDMA_CACHELINE_ALIGNMENT);
    if(NULL == ringMem)
    {
        retVal = UDMA_EALLOC;
    }

    /* Open Channel */
    if(UDMA_SOK == retVal)
    {
        chType                        = UDMA_CH_TYPE_TX;
        UdmaChPrms_init(&chPrms, chType);
        chPrms.peerChNum              = UDMA_PSIL_CH_MAIN_CSI_TX;
        chPrms.fqRingPrms.ringMem     = ringMem;
        chPrms.fqRingPrms.ringMemSize = ringMemSize;
        chPrms.fqRingPrms.elemCnt     = elemCnt;
        chPrms.fqRingPrms.mode        = ringMode;
        retVal                        = Udma_chOpen(drvHandle, chHandle, chType, &chPrms);
        if(UDMA_SOK == retVal)
        {
            UdmaChTxPrms_init(&txChPrms, chType);
            retVal = Udma_chConfigTx(chHandle, &txChPrms);
        }
    }

    return retVal;
}

static int32_t UdmaTestDeInitRingAcc(Udma_ChHandle chHandle)
{
    int32_t           retVal  = UDMA_SOK;
    uint32_t          heapId  = UTILS_MEM_HEAP_ID_DDR;

    /* Free Ring Memory in heap */
    retVal = Utils_memFree(heapId, chHandle->chPrms.fqRingPrms.ringMem, chHandle->chPrms.fqRingPrms.ringMemSize);

    /* Close Channel */
    if(UDMA_SOK == retVal)
    {
        retVal = Udma_chClose(chHandle);
    }

    return retVal;
}
