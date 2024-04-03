/*
 *  Copyright (c) Texas Instruments Incorporated 2019-2024
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
 *  \file udma_test_ch.c
 *
 *  \brief UDMA channel related test case file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <udma_test.h>
#include <udma_testconfig.h>

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

static int32_t udmaTestChPktdmaParamCheckTestLoop(UdmaTestTaskObj *taskObj);
static int32_t udmaTestChPktdmaChApiTestLoop(UdmaTestTaskObj *taskObj);
static int32_t udmaTestBcdmaParamCheckTestLoop(UdmaTestTaskObj *taskObj);
static int32_t udmaTestBcdmaChApiTestLoop(UdmaTestTaskObj *taskObj);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Global test pass/fail flag */
static volatile int32_t gUdmaTestChResult = UDMA_SOK;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */


int32_t udmaTestChPktdmaParamCheckTc(UdmaTestTaskObj *taskObj)
{
    int32_t     retVal = UDMA_SOK;
    uint32_t    loopCnt = 0U;

    GT_1trace(taskObj->traceMask, GT_INFO1,
              " |TEST INFO|:: Task:%d: PKTDMA Channel Paramter Check Testcase ::\r\n", taskObj->taskId);
    GT_2trace(taskObj->traceMask, GT_INFO1,
              " |TEST INFO|:: Task:%d: Loop count           : %d ::\r\n", taskObj->taskId, taskObj->loopCnt);

    gUdmaTestChResult = UDMA_SOK;
    while(loopCnt < taskObj->loopCnt)
    {
        retVal = udmaTestChPktdmaParamCheckTestLoop(taskObj);
        if(UDMA_SOK != retVal)
        {
            break;
        }

        loopCnt++;
    }

    retVal += gUdmaTestChResult;

    return (retVal);
}


int32_t udmaTestChPktdmaChApiTc(UdmaTestTaskObj *taskObj)
{
    int32_t     retVal = UDMA_SOK;
    uint32_t    loopCnt = 0U;

    GT_1trace(taskObj->traceMask, GT_INFO1,
              " |TEST INFO|:: Task:%d: PKTDMA Channel API's Testcase ::\r\n", taskObj->taskId);
    GT_2trace(taskObj->traceMask, GT_INFO1,
              " |TEST INFO|:: Task:%d: Loop count           : %d ::\r\n", taskObj->taskId, taskObj->loopCnt);

    gUdmaTestChResult = UDMA_SOK;
    while(loopCnt < taskObj->loopCnt)
    {
        retVal = udmaTestChPktdmaChApiTestLoop(taskObj);
        if(UDMA_SOK != retVal)
        {
            break;
        }

        loopCnt++;
    }

    retVal += gUdmaTestChResult;

    return (retVal);
}

static int32_t udmaTestChPktdmaParamCheckTestLoop(UdmaTestTaskObj *taskObj)
{
    int32_t             retVal = UDMA_SOK;
#if (UDMA_SOC_CFG_RA_LCDMA_PRESENT == 1) && (UDMA_SOC_CFG_PKTDMA_PRESENT == 1)
    uint32_t            elemCnt = 50U, ringMemSize;
    uint32_t            heapId = UTILS_MEM_HEAP_ID_MSMC;
    Udma_DrvHandle      drvHandle;
    uint32_t            chType;
    struct Udma_ChObj   chObj;
    Udma_ChHandle       chHandle = &chObj;
    Udma_ChPrms         chPrms;
    void               *ringMem = NULL;

    drvHandle = &taskObj->testObj->drvObj[UDMA_TEST_INST_ID_PKTDMA_0];
    ringMemSize = elemCnt * sizeof (uint64_t);
    ringMem = Utils_memAlloc(heapId, ringMemSize, UDMA_CACHELINE_ALIGNMENT);
    if(NULL == ringMem)
    {
        retVal = UDMA_EALLOC;
        GT_0trace(taskObj->traceMask, GT_ERR, " Ring memory allocation failure\r\n");
    }


#if ((UDMA_NUM_MAPPED_TX_GROUP + UDMA_NUM_MAPPED_RX_GROUP) > 0)
    /* PKTDMA Channel Open with no ring memory test */
    chType = UDMA_CH_TYPE_TX_MAPPED;
    UdmaChPrms_init(&chPrms, chType);
    chPrms.mappedChGrp = UDMA_MAPPED_TX_GROUP_CPSW;
    chPrms.peerChNum   = UDMA_TEST_PKTDMA_CPSW_TX_PEER_CH;
    retVal = Udma_chOpen(drvHandle, chHandle, chType, &chPrms);
    if(UDMA_SOK != retVal)
    {
        GT_0trace(taskObj->traceMask, GT_ERR,
            " UDMA channel open failed!!\n");
    }
    if(UDMA_SOK == retVal)
    {
        if(chHandle->fqRing != (Udma_RingHandle) NULL_PTR)
        {
            GT_0trace(taskObj->traceMask, GT_ERR,
                    " Ring allocated even when no ring memory was provided!!\n");
            retVal = UDMA_EFAIL;
        }
    }
    if(UDMA_SOK == retVal)
    {
        retVal = Udma_chClose(chHandle);
        if(UDMA_SOK != retVal)
        {
            GT_0trace(taskObj->traceMask, GT_ERR,
                " UDMA channel close failed!!\n");
        }
    }

    /* PKTDMA Mapped Channel Open with invalid mapped channel group negative test*/
    chType = UDMA_CH_TYPE_TX_MAPPED;
    UdmaChPrms_init(&chPrms, chType);
    chPrms.fqRingPrms.ringMem       = ringMem;
    chPrms.fqRingPrms.ringMemSize   = ringMemSize;
    chPrms.fqRingPrms.elemCnt       = elemCnt;
    chPrms.mappedChGrp = UDMA_NUM_MAPPED_TX_GROUP + UDMA_NUM_MAPPED_RX_GROUP;
    retVal = Udma_chOpen(drvHandle, chHandle, chType, &chPrms);
    if(UDMA_SOK == retVal)
    {
        GT_0trace(taskObj->traceMask, GT_ERR,
            " Channel Open did not fail for incorrect mappedChGrp check!!\n");
            retVal = UDMA_EFAIL;
    }
    else
    {
        retVal = UDMA_SOK;
    }
    
#endif

    if(NULL != ringMem)
    {
        retVal += Utils_memFree(heapId, ringMem, ringMemSize);
        if(UDMA_SOK != retVal)
        {
            GT_0trace(taskObj->traceMask, GT_ERR, " Ring free failed!!\n");
        }
    }
#endif

    return(retVal);
}

static int32_t udmaTestChPktdmaChApiTestLoop(UdmaTestTaskObj *taskObj)
{
    int32_t             retVal = UDMA_SOK;
#if (UDMA_SOC_CFG_RA_LCDMA_PRESENT == 1) && (UDMA_SOC_CFG_PKTDMA_PRESENT == 1)
    uint32_t            elemCnt = 50U, ringMemSize;
    uint32_t            heapId = UTILS_MEM_HEAP_ID_MSMC;
    Udma_DrvHandle      drvHandle;
    uint32_t            chType;
    struct Udma_ChObj   chObj;
    Udma_ChHandle       chHandle = &chObj;
    Udma_ChPrms         chPrms;
    Udma_ChTxPrms       txPrms;
    Udma_ChRxPrms       rxPrms;
    uint32_t            chGrpIdx;
    void               *ringMem = NULL;
    Udma_RmInitPrms    *rmInitPrms;
    char *pktdmaChGrpStr[] = { "Unmapped TX", "CPSW TX", "SAUL TX", "ICSSG_0 TX", "ICSSG_1_TX",
                               "Unmapped RX", "CPSW RX", "SAUL RX", "ICSSG_0 RX", "ICSSG_1_RX"};
    const UdmaTestPktdmaChPrm  *pktdmaChPrms = NULL;

    drvHandle = &taskObj->testObj->drvObj[UDMA_TEST_INST_ID_PKTDMA_0];
    rmInitPrms = &drvHandle->initPrms.rmInitPrms;
    ringMemSize = elemCnt * sizeof (uint64_t);
    ringMem = Utils_memAlloc(heapId, ringMemSize, UDMA_CACHELINE_ALIGNMENT);
    if(NULL == ringMem)
    {
        retVal = UDMA_EALLOC;
        GT_0trace(taskObj->traceMask, GT_ERR, " Ring memory allocation failure\r\n");
    }
    
    /* Test for each config in PKTMA Channel param table */
    for(chGrpIdx = 0U; chGrpIdx < UDMA_TEST_NUM_PKTDMA_CH_PRM; chGrpIdx++)
    {
        GT_1trace(taskObj->traceMask, GT_INFO1,
                  " Testing for PKTDMA %s Channel Group  ...\r\n",
                  pktdmaChGrpStr[chGrpIdx]);

        if(((UDMA_TEST_PKTDMA_CH_PRMID_UNMAPPED_TX == chGrpIdx) && (0U == rmInitPrms->numTxCh)) ||
           ((UDMA_TEST_PKTDMA_CH_PRMID_CPSW_TX == chGrpIdx) && (0U == rmInitPrms->numMappedTxCh[UDMA_MAPPED_TX_GROUP_CPSW])) ||
           ((UDMA_TEST_PKTDMA_CH_PRMID_SAUL_TX == chGrpIdx) && (0U == rmInitPrms->numMappedTxCh[UDMA_MAPPED_TX_GROUP_SAUL])) ||
           ((UDMA_TEST_PKTDMA_CH_PRMID_ICSSG_0_TX == chGrpIdx) && (0U == rmInitPrms->numMappedTxCh[UDMA_MAPPED_TX_GROUP_ICSSG_0])) ||
           ((UDMA_TEST_PKTDMA_CH_PRMID_ICSSG_1_TX == chGrpIdx) && (0U == rmInitPrms->numMappedTxCh[UDMA_MAPPED_TX_GROUP_ICSSG_1])) ||
           ((UDMA_TEST_PKTDMA_CH_PRMID_UNMAPPED_RX == chGrpIdx) && (0U == rmInitPrms->numRxCh)) ||
           ((UDMA_TEST_PKTDMA_CH_PRMID_CPSW_RX == chGrpIdx) && (0U == rmInitPrms->numMappedRxCh[UDMA_MAPPED_RX_GROUP_CPSW - UDMA_NUM_MAPPED_TX_GROUP])) ||
           ((UDMA_TEST_PKTDMA_CH_PRMID_SAUL_RX == chGrpIdx) && (0U == rmInitPrms->numMappedRxCh[UDMA_MAPPED_RX_GROUP_SAUL - UDMA_NUM_MAPPED_TX_GROUP])) ||
           ((UDMA_TEST_PKTDMA_CH_PRMID_ICSSG_0_RX == chGrpIdx) && (0U == rmInitPrms->numMappedRxCh[UDMA_MAPPED_RX_GROUP_ICSSG_0 - UDMA_NUM_MAPPED_TX_GROUP])) ||
           ((UDMA_TEST_PKTDMA_CH_PRMID_ICSSG_1_RX == chGrpIdx) && (0U == rmInitPrms->numMappedRxCh[UDMA_MAPPED_RX_GROUP_ICSSG_1 - UDMA_NUM_MAPPED_TX_GROUP])))
        {
            GT_1trace(taskObj->traceMask, GT_INFO1,
                      " Skipping the Test for PKTDMA %s Channel Group, since no channels are reserved!!\r\n",
                      pktdmaChGrpStr[chGrpIdx]);
            continue;
        }

        pktdmaChPrms = &gUdmaTestPktdmaChPrm[chGrpIdx];

        chType = pktdmaChPrms->chType;
        UdmaChPrms_init(&chPrms, chType);
        chPrms.fqRingPrms.ringMem       = ringMem;
        chPrms.fqRingPrms.ringMemSize   = ringMemSize;
        chPrms.fqRingPrms.elemCnt       = elemCnt;
        chPrms.mappedChGrp = pktdmaChPrms->mappedChGrp;
        chPrms.peerChNum   = pktdmaChPrms->peerChNum;

        retVal = Udma_chOpen(drvHandle, chHandle, chType, &chPrms);
        if(UDMA_SOK != retVal)
        {
            GT_0trace(taskObj->traceMask, GT_ERR,
                " UDMA channel open failed!!\n");
            break;
        }
        else
        {
            GT_2trace(taskObj->traceMask, GT_INFO1,
                        " |TEST INFO|:: Task:%d: Allocated Ch   : %d ::\r\n",
                        taskObj->taskId, Udma_chGetNum(chHandle));
        }

        if((chType & UDMA_CH_FLAG_TX) == UDMA_CH_FLAG_TX)
        {
            /* Config TX channel */
            UdmaChTxPrms_init(&txPrms, chType);
            retVal = Udma_chConfigTx(chHandle, &txPrms);
            if(UDMA_SOK != retVal)
            {
                GT_0trace(taskObj->traceMask, GT_ERR,
                    " UDMA TX channel config failed!!\n");
                break;
            }
        }
        else
        {
            /* Config RX channel */
            UdmaChRxPrms_init(&rxPrms, chType);
            retVal = Udma_chConfigRx(chHandle, &rxPrms);
            if(UDMA_SOK != retVal)
            {
                GT_0trace(taskObj->traceMask, GT_ERR,
                    " UDMA RX channel config failed!!\n");
                break;
            }
        }
        
        retVal = Udma_chEnable(chHandle);
        if(UDMA_SOK != retVal)
        {
            GT_0trace(taskObj->traceMask, GT_ERR,
                " UDMA channel enable failed!!\n");
            break;
        }

        retVal = Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
        if(UDMA_SOK != retVal)
        {
            GT_0trace(taskObj->traceMask, GT_ERR,
                " UDMA channel disable failed!!\n");
            break;
        }

        retVal = Udma_chClose(chHandle);
        if(UDMA_SOK != retVal)
        {
            GT_0trace(taskObj->traceMask, GT_ERR,
                " UDMA channel close failed!!\n");
            break;
        }
        
        GT_1trace(taskObj->traceMask, GT_INFO1,
                  " Testing for PKTDMA %s Channel Group passed!!\r\n",
                  pktdmaChGrpStr[chGrpIdx]);
    }
#endif

    return(retVal);
}

int32_t udmaTestBcdmaParamCheckTc(UdmaTestTaskObj *taskObj)
{
    int32_t     retVal = UDMA_SOK;
    uint32_t    loopCnt = 0U;

    GT_1trace(taskObj->traceMask, GT_INFO1,
              " |TEST INFO|:: Task:%d: BCDMA Channel Paramter Check Testcase ::\r\n", taskObj->taskId);
    GT_2trace(taskObj->traceMask, GT_INFO1,
              " |TEST INFO|:: Task:%d: Loop count           : %d ::\r\n", taskObj->taskId, taskObj->loopCnt);

    gUdmaTestChResult = UDMA_SOK;
    while(loopCnt < taskObj->loopCnt)
    {
        retVal = udmaTestBcdmaParamCheckTestLoop(taskObj);
        if(UDMA_SOK != retVal)
        {
            break;
        }

        loopCnt++;
    }

    retVal += gUdmaTestChResult;

    return (retVal);
}

int32_t udmaTestBcdmaChApiTc(UdmaTestTaskObj *taskObj)
{
    int32_t     retVal = UDMA_SOK;
    uint32_t    loopCnt = 0U;

    GT_1trace(taskObj->traceMask, GT_INFO1,
              " |TEST INFO|:: Task:%d: BCDMA Channel API's Testcase ::\r\n", taskObj->taskId);
    GT_2trace(taskObj->traceMask, GT_INFO1,
              " |TEST INFO|:: Task:%d: Loop count           : %d ::\r\n", taskObj->taskId, taskObj->loopCnt);

    gUdmaTestChResult = UDMA_SOK;
    while(loopCnt < taskObj->loopCnt)
    {
        retVal = udmaTestBcdmaChApiTestLoop(taskObj);
        if(UDMA_SOK != retVal)
        {
            break;
        }

        loopCnt++;
    }

    retVal += gUdmaTestChResult;

    return (retVal);
}

static int32_t udmaTestBcdmaParamCheckTestLoop(UdmaTestTaskObj *taskObj)
{
    int32_t             retVal = UDMA_SOK;
#if (UDMA_SOC_CFG_RA_LCDMA_PRESENT == 1) && (UDMA_SOC_CFG_BCDMA_PRESENT == 1)
    uint32_t            elemCnt = 50U, ringMemSize;
    uint32_t            heapId = UTILS_MEM_HEAP_ID_MSMC;
    Udma_DrvHandle      drvHandle;
    uint32_t            chType[UDMA_TEST_BCDMA_CH_NUM_CH_TYPE] = {UDMA_CH_TYPE_TX, UDMA_CH_TYPE_RX};
    uint32_t            peerCh[UDMA_TEST_BCDMA_CH_NUM_CH_TYPE] = {UDMA_TEST_BCDMA_PEER_CH_NUM_TX, UDMA_TEST_BCDMA_PEER_CH_NUM_RX};
    struct Udma_ChObj   chObj;
    Udma_ChHandle       chHandle = &chObj;
    Udma_ChPrms         chPrms;
    uint32_t            i;
    void               *ringMem = NULL;

    drvHandle = &taskObj->testObj->drvObj[UDMA_TEST_INST_ID_BCDMA_0];

    for (i = 0; i < UDMA_TEST_BCDMA_CH_NUM_CH_TYPE; i++)
    {
        /* BCDMA Channel Open with no ring memory test */
        memset(&chPrms, 0u, sizeof(Udma_ChPrms));
        UdmaChPrms_init(&chPrms, chType[i]);
        chPrms.peerChNum   = peerCh[i];
        retVal = Udma_chOpen(drvHandle, chHandle, chType[i], &chPrms);
        if(UDMA_SOK != retVal)
        {
            GT_0trace(taskObj->traceMask, GT_ERR,
                " UDMA channel open failed!!\n");
        }
        if(UDMA_SOK == retVal)
        {
            if(chHandle->fqRing != (Udma_RingHandle) NULL_PTR)
            {
                GT_0trace(taskObj->traceMask, GT_ERR,
                        " Ring allocated even when no ring memory was provided!!\n");
                retVal = UDMA_EFAIL;
            }
        }
        if(UDMA_SOK == retVal)
        {
            retVal = Udma_chClose(chHandle);
            if(UDMA_SOK != retVal)
            {
                GT_0trace(taskObj->traceMask, GT_ERR,
                    " UDMA channel close failed!!\n");
            }
        }

        ringMemSize = elemCnt * sizeof (uint64_t);
        ringMem = Utils_memAlloc(heapId, ringMemSize, UDMA_CACHELINE_ALIGNMENT);
        if(NULL == ringMem)
        {
            retVal = UDMA_EALLOC;
            GT_0trace(taskObj->traceMask, GT_ERR, " Ring memory allocation failure\r\n");
        }


        /* BCDMA Channel Open with ring memory test */
        UdmaChPrms_init(&chPrms, chType[i]);
        chPrms.peerChNum   = peerCh[i];
        chPrms.fqRingPrms.ringMem       = ringMem;
        chPrms.fqRingPrms.ringMemSize   = ringMemSize;
        chPrms.fqRingPrms.elemCnt       = elemCnt;
        retVal = Udma_chOpen(drvHandle, chHandle, chType[i], &chPrms);
        if(UDMA_SOK != retVal)
        {
            GT_0trace(taskObj->traceMask, GT_ERR,
                " UDMA channel open failed!!\n");
        }
        if(UDMA_SOK == retVal)
        {
            if(chHandle->fqRing == (Udma_RingHandle) NULL_PTR)
            {
                GT_0trace(taskObj->traceMask, GT_ERR,
                        " Ring allocation failed even ring memory was provided!!\n");
                retVal = UDMA_EFAIL;
            }
        }
        if(UDMA_SOK == retVal)
        {
            retVal = Udma_chClose(chHandle);
            if(UDMA_SOK != retVal)
            {
                GT_0trace(taskObj->traceMask, GT_ERR,
                    " UDMA channel close failed!!\n");
            }
        }

        if(NULL != ringMem)
        {
            retVal += Utils_memFree(heapId, ringMem, ringMemSize);
            if(UDMA_SOK != retVal)
            {
                GT_0trace(taskObj->traceMask, GT_ERR, " Ring free failed!!\n");
            }
        }
    }
#endif

    return(retVal);
}

static int32_t udmaTestBcdmaChApiTestLoop(UdmaTestTaskObj *taskObj)
{
    int32_t             retVal = UDMA_SOK;
#if (UDMA_SOC_CFG_RA_LCDMA_PRESENT == 1) && (UDMA_SOC_CFG_BCDMA_PRESENT == 1)
    uint32_t            elemCnt = 50U, ringMemSize;
    uint32_t            heapId = UTILS_MEM_HEAP_ID_MSMC;
    Udma_DrvHandle      drvHandle;
    uint32_t            chType[UDMA_TEST_BCDMA_CH_NUM_CH_TYPE] = {UDMA_CH_TYPE_TX, UDMA_CH_TYPE_RX};
    uint32_t            peerCh[UDMA_TEST_BCDMA_CH_NUM_CH_TYPE] = {UDMA_TEST_BCDMA_PEER_CH_NUM_TX, UDMA_TEST_BCDMA_PEER_CH_NUM_RX};
    struct Udma_ChObj   chObj;
    Udma_ChHandle       chHandle = &chObj;
    Udma_ChPrms         chPrms;
    Udma_ChTxPrms       txPrms;
    Udma_ChRxPrms       rxPrms;
    uint32_t            i;
    void               *ringMem = NULL;

    drvHandle = &taskObj->testObj->drvObj[UDMA_TEST_INST_ID_BCDMA_0];

    for (i = 0; i < UDMA_TEST_BCDMA_CH_NUM_CH_TYPE; i++)
    {
        ringMemSize = elemCnt * sizeof (uint64_t);
        ringMem = Utils_memAlloc(heapId, ringMemSize, UDMA_CACHELINE_ALIGNMENT);
        if(NULL == ringMem)
        {
            retVal = UDMA_EALLOC;
            GT_0trace(taskObj->traceMask, GT_ERR, " Ring memory allocation failure\r\n");
        }
        memset(&chPrms, 0u, sizeof(Udma_ChPrms));
        UdmaChPrms_init(&chPrms, chType[i]);
        chPrms.peerChNum   = peerCh[i];
        chPrms.fqRingPrms.ringMem       = ringMem;
        chPrms.fqRingPrms.ringMemSize   = ringMemSize;
        chPrms.fqRingPrms.elemCnt       = elemCnt;
        retVal = Udma_chOpen(drvHandle, chHandle, chType[i], &chPrms);
        if(UDMA_SOK != retVal)
        {
            GT_0trace(taskObj->traceMask, GT_ERR,
                " UDMA channel open failed!!\n");
        }
        else
        {
            GT_2trace(taskObj->traceMask, GT_INFO1,
                        " |TEST INFO|:: Task:%d: Allocated Ch   : %d ::\r\n",
                        taskObj->taskId, Udma_chGetNum(chHandle));
        }

        if((chType[i] & UDMA_CH_FLAG_TX) == UDMA_CH_FLAG_TX)
        {
            /* Config TX channel */
            UdmaChTxPrms_init(&txPrms, chType[i]);
            retVal = Udma_chConfigTx(chHandle, &txPrms);
            if(UDMA_SOK != retVal)
            {
                GT_0trace(taskObj->traceMask, GT_ERR,
                    " UDMA TX channel config failed!!\n");
            }
        }

        if((chType[i] & UDMA_CH_FLAG_RX) == UDMA_CH_FLAG_RX)
        {
            /* Config RX channel */
            UdmaChRxPrms_init(&rxPrms, chType[i]);
            retVal = Udma_chConfigRx(chHandle, &rxPrms);
            if(UDMA_SOK != retVal)
            {
                GT_0trace(taskObj->traceMask, GT_ERR,
                    " UDMA RX channel config failed!!\n");
            }
        }
        
        retVal = Udma_chEnable(chHandle);
        if(UDMA_SOK != retVal)
        {
            GT_0trace(taskObj->traceMask, GT_ERR,
                " UDMA channel enable failed!!\n");
        }

        retVal = Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
        if(UDMA_SOK != retVal)
        {
            GT_0trace(taskObj->traceMask, GT_ERR,
                " UDMA channel disable failed!!\n");
        }

        retVal = Udma_chClose(chHandle);
        if(UDMA_SOK != retVal)
        {
            GT_0trace(taskObj->traceMask, GT_ERR,
                " UDMA channel close failed!!\n");
        }

        if(NULL != ringMem)
        {
            retVal += Utils_memFree(heapId, ringMem, ringMemSize);
            if(UDMA_SOK != retVal)
            {
                GT_0trace(taskObj->traceMask, GT_ERR, " Ring free failed!!\n");
            }
        }
    }

#endif

    return(retVal);
}

/*
 * Test Case Description: Verifies the function Udma_chPause 
 * Test scenario 1: Check when instType is UDMA_INST_TYPE_LCDMA_BCDMA 
 *                  and chType is UDMA_CH_TYPE_TX
 * Test scenario 2: Check when chType is UDMA_CH_TYPE_RX
 */
int32_t UdmaTestChPause(UdmaTestTaskObj *taskObj)
{
    int32_t            retVal = UDMA_SOK;
    #if (UDMA_SOC_CFG_BCDMA_PRESENT == 1)
    struct Udma_ChObj  chObj;
    Udma_ChHandle      chHandle;
    struct Udma_DrvObj backUpDrvObj;
    Udma_DrvHandle     drvHandle;
    Udma_ChPrms        chPrms;
    uint32_t           chType;
    uint32_t           timeout;
    uint32_t           instID; 

    GT_1trace(taskObj->traceMask, GT_INFO1,
              " |TEST INFO|:: Task:%d: UDMA ChPause positive Testcase ::\r\n",
              taskObj->taskId);

    /* Test scenario 1: Check when instType is UDMA_INST_TYPE_LCDMA_BCDMA 
    *                   and chType is UDMA_CH_TYPE_TX 
    */
    chHandle         = &chObj;
    timeout          = 0U;
    instID           = UDMA_TEST_INST_ID_BCDMA_0;
    chType           = UDMA_CH_TYPE_TX;
    backUpDrvObj     = taskObj->testObj->drvObj[instID];
    drvHandle        = &taskObj->testObj->drvObj[instID];
    UdmaChPrms_init(&chPrms, chType);
    chPrms.peerChNum = UDMA_PSIL_CH_MAIN_CSI_TX;
    retVal           = Udma_chOpen(drvHandle, chHandle, chType, &chPrms);
    Udma_ChTxPrms txChPrms;
    UdmaChTxPrms_init(&txChPrms, chType);
    if(retVal == UDMA_SOK)
    {
        retVal = Udma_chConfigTx(chHandle, &txChPrms);
        if(retVal == UDMA_SOK)
        {
            retVal = Udma_chEnable(chHandle);
            if(retVal == UDMA_SOK)
            {
                retVal = Udma_chPause(chHandle);
                if(retVal != UDMA_SOK)
                {
                    GT_0trace(taskObj->traceMask, GT_ERR,
                              " |TEST INFO|:: FAIL:: UDMA:: Udma_chPauseTxLocal:: "
                              " Pos:: Check when instType is UDMA_INST_TYPE_LCDMA_BCDMA "
                              " and chType is UDMA_CH_TYPE_TX!!\n");
                    retVal = UDMA_EFAIL;
                }
                else
                {
                    retVal = Udma_chResume(chHandle);
                    if(retVal != UDMA_SOK)
                    {
                        GT_0trace(taskObj->traceMask, GT_ERR,
                                  " |TEST INFO|:: FAIL:: UDMA:: Udma_chUnpauseTxLocal::"
                                  " Pos:: Check when instType is UDMA_INST_TYPE_LCDMA_BCDMA"
                                  " and chType is UDMA_CH_TYPE_TX!!\n");
                        retVal = UDMA_EFAIL;
                    }
                    Udma_chDisable(chHandle, timeout);
                    Udma_chClose(chHandle);
                }
            }
        }
    }
    taskObj->testObj->drvObj[instID] = backUpDrvObj;


    /* Test scenario 2: Check when chType is UDMA_CH_TYPE_RX */
    if(retVal == UDMA_SOK)
    {
        chType           = UDMA_CH_TYPE_RX;
        backUpDrvObj     = taskObj->testObj->drvObj[instID];
        drvHandle        = &taskObj->testObj->drvObj[instID];
        UdmaChPrms_init(&chPrms, chType);
        chPrms.peerChNum = UDMA_PSIL_CH_MCU_CPSW0_RX;
        retVal           = Udma_chOpen(drvHandle, chHandle, chType, &chPrms);
        Udma_ChRxPrms rxPrms;
        UdmaChRxPrms_init(&rxPrms, chType);
        if(retVal == UDMA_SOK)
        {
            retVal = Udma_chConfigRx(chHandle, &rxPrms);
            if(retVal == UDMA_SOK)
            {
                retVal = Udma_chEnable(chHandle);
                if(retVal == UDMA_SOK)
                {
                    retVal = Udma_chPause(chHandle);
                    if(retVal != UDMA_SOK)
                    {
                        GT_0trace(taskObj->traceMask, GT_ERR,
                                  " |TEST INFO|:: FAIL:: UDMA:: Udma_chPauseRxLocal:: "
                                  " Pos:: Check when chType is UDMA_CH_TYPE_RX!!\n");
                        retVal = UDMA_EFAIL;
                    }
                    else
                    {
                        retVal = Udma_chResume(chHandle);
                        if(retVal != UDMA_SOK)
                        {
                            GT_0trace(taskObj->traceMask, GT_ERR,
                                      " |TEST INFO|:: FAIL:: UDMA:: Udma_chUnpauseRxLocal:: "
                                      " Pos:: Check when chType is UDMA_CH_TYPE_RX!!\n");
                            retVal = UDMA_EFAIL;
                        }
                        Udma_chDisable(chHandle, timeout);
                        Udma_chClose(chHandle);
                    }
                }
            }
        }
    }
    taskObj->testObj->drvObj[instID] = backUpDrvObj;
    #endif

    return retVal;
}

/* 
 * Test Case Description: Verifies the function Udma_chGetDefaultFlowHandle
 * Test scenario 1: Check for Valid args 
 */
int32_t UdmaTestChGetDefaultFlowHandle(UdmaTestTaskObj *taskObj)
{
    int32_t            retVal = UDMA_SOK;
    struct Udma_ChObj  chObj;
    struct Udma_DrvObj backUpDrvObj;
    Udma_ChHandle      chHandle;
    Udma_ChPrms        chPrms;
    Udma_DrvHandle     drvHandle;
    uint32_t           chType;
    uint32_t           instID;

    GT_1trace(taskObj->traceMask, GT_INFO1,
              " |TEST INFO|:: Task:%d: UDMA ChGetDefaultFlowHandle positive Testcase ::\r\n",
              taskObj->taskId);

    /* Test scenario 1: Check for Valid args */
    chHandle         = &chObj;
    instID           = UDMA_TEST_INST_ID_BCDMA_0;
    chType           = UDMA_CH_TYPE_RX;
    UdmaChPrms_init(&chPrms, chType);
    backUpDrvObj     = taskObj->testObj->drvObj[instID];
    drvHandle        = &taskObj->testObj->drvObj[instID];
    chPrms.peerChNum = UDMA_PSIL_CH_MCU_CPSW0_RX;
    retVal           = Udma_chOpen(drvHandle, chHandle, chType, &chPrms);
    if(retVal == UDMA_SOK)
    {
        if(Udma_chGetDefaultFlowHandle(chHandle) == NULL_PTR)
        {
            GT_0trace(taskObj->traceMask, GT_ERR,
                      " |TEST INFO|:: FAIL:: UDMA:: chGetDefaultFlowHandle:: "
                      " Pos:: Check for Valid args!!\n");
            retVal = UDMA_EFAIL;
        }
        else
        {
            retVal = UDMA_SOK;
            Udma_chClose(chHandle);
        }
    }
    taskObj->testObj->drvObj[instID] = backUpDrvObj;
    
    return retVal;
}

/* 
 * Test Case Description: Verifies the function Udma_chDisable when
 * Test scenario 1: Check when chType is UDMA_CH_TYPE_TX and instType is UDMA_INST_TYPE_NORMAL
 */ 
int32_t UdmaChDisableTest(UdmaTestTaskObj *taskObj)
{
    int32_t            retVal = UDMA_SOK;
    struct Udma_ChObj  chObj;
    Udma_ChHandle      chHandle;
    uint32_t           timeout = 0U;
    uint32_t           instID;
    struct Udma_DrvObj backUpDrvObj;
    Udma_DrvHandle     drvHandle;
    Udma_ChPrms        chPrms;
    uint32_t           chType;

    GT_1trace(taskObj->traceMask, GT_INFO1,
              " |TEST INFO|:: Task:%d: UDMA ChDisable Testcase ::\r\n",
              taskObj->taskId);

    /* Test scenario 1: Check when chType is UDMA_CH_TYPE_TX and instType is UDMA_INST_TYPE_NORMAL */
    chHandle         = &chObj;
    chType           = UDMA_CH_TYPE_TX;
    UdmaChPrms_init(&chPrms, chType);
    instID           = UDMA_TEST_DEFAULT_UDMA_INST;
    backUpDrvObj     = taskObj->testObj->drvObj[instID];
    drvHandle        = &taskObj->testObj->drvObj[instID];
    chPrms.peerChNum = UDMA_PSIL_CH_MCU_CPSW0_TX;
    retVal           = Udma_chOpen(drvHandle, chHandle, chType, &chPrms);
    Udma_ChTxPrms txChPrms;
    UdmaChTxPrms_init(&txChPrms, chType);
    if(UDMA_SOK == retVal)
    {
        retVal = Udma_chConfigTx(chHandle, &txChPrms);
        if(UDMA_SOK == retVal)
        {
            retVal = Udma_chEnable(chHandle);
            if(UDMA_SOK == retVal)
            {
                retVal = Udma_chDisable(chHandle, timeout);
                if(UDMA_SOK != retVal)
                {
                    GT_0trace(taskObj->traceMask, GT_ERR,
                              " |TEST INFO|:: FAIL:: UDMA:: UdmachDisableTxChan:: Pos:: "
                              " Check when chType is UDMA_CH_TYPE_TX and instType is UDMA_INST_TYPE_NORMAL!!\n");
                    retVal = UDMA_EFAIL;
                }
                else
                {
                    retVal = UDMA_SOK;
                }
            }
        }
    }
    Udma_chClose(chHandle);
    taskObj->testObj->drvObj[instID] = backUpDrvObj;
   
    return retVal;
}

/* 
 * Test Case Description: Verifies the function Udma_chConfigPdma when
 * Test scenario 1: Check when instType is UDMA_INST_TYPE_NORMAL and chType is UDMA_CH_TYPE_PDMA_TX
 */ 
int32_t UdmaChConfigPdmaTest(UdmaTestTaskObj *taskObj)
{
    int32_t           retVal = UDMA_SOK;
    struct Udma_ChObj chObj;
    Udma_ChHandle     chHandle;
    Udma_ChTxPrms     txPrms;
    Udma_ChPdmaPrms   pdmaPrms;
    uint32_t          instID;
    Udma_DrvHandle    drvHandle;
    Udma_ChPrms       chPrms;
    uint32_t          chType;
    
    GT_1trace(taskObj->traceMask, GT_INFO1,
              " |TEST INFO|:: Task:%d: UDMA ChConfigPdma Testcase ::\r\n",
              taskObj->taskId);

    /* Test scenario 1: Check when instType is UDMA_INST_TYPE_NORMAL and chType is UDMA_CH_TYPE_PDMA_TX */
    chHandle         = &chObj;
    chType           = UDMA_CH_TYPE_PDMA_TX;
    UdmaChPrms_init(&chPrms, chType);
    instID           = UDMA_TEST_DEFAULT_UDMA_INST;
    drvHandle        = &taskObj->testObj->drvObj[instID];
    chPrms.peerChNum = CSL_PDMA_CH_MCU_MCAN0_CH0_TX;
    retVal           = Udma_chOpen(drvHandle, chHandle, chType, &chPrms);
    if(UDMA_SOK == retVal)
    {
        /* Config RX channel */
        UdmaChTxPrms_init(&txPrms, UDMA_CH_TYPE_PDMA_TX);
        retVal = Udma_chConfigTx(chHandle, &txPrms);
        /* Config PDMA channel */
        UdmaChPdmaPrms_init(&pdmaPrms);
        retVal = Udma_chConfigPdma(chHandle, &pdmaPrms);
        if(UDMA_SOK != retVal)
        {
            GT_0trace(taskObj->traceMask, GT_ERR,
                      " |TEST INFO|:: FAIL:: UDMA:: ChConfigPdma:: Neg:: "
                      " when instType is UDMA_INST_TYPE_NORMAL and chType is UDMA_CH_TYPE_PDMA_TX!!\n");
            retVal = UDMA_EFAIL;
        }
        else
        {
            retVal = UDMA_SOK;
        }
    }
    Udma_chClose(chHandle);

    return retVal;
}

/* 
 * Test Case Description: Verifies the function Udma_chGetTdCqRingHandle 
 * Test scenario 1: Check for Valid args
 */
int32_t UdmaTestChGetTdCqRingHandle(UdmaTestTaskObj *taskObj)
{
    int32_t           retVal = UDMA_SOK;
    Udma_ChHandle     chHandle;
    struct Udma_ChObj chObj;
    Udma_ChPrms       chPrms;
    uint32_t          chType;
    Udma_DrvHandle    drvHandle;
    uint32_t          instID;

    GT_1trace(taskObj->traceMask, GT_INFO1,
              " |TEST INFO|:: Task:%d: UDMA ChGetTdCqRingHandle Testcase ::\r\n",
              taskObj->taskId);

    /*Test scenario 1: Check for Valid args*/
    chHandle         = &chObj;
    instID           = UDMA_TEST_DEFAULT_UDMA_INST;
    chType           = UDMA_CH_TYPE_TX;
    UdmaChPrms_init(&chPrms, chType);
    drvHandle        = &taskObj->testObj->drvObj[instID];
    chPrms.peerChNum = UDMA_PSIL_CH_MCU_CPSW0_TX;
    retVal           = Udma_chOpen(drvHandle, chHandle, chType, &chPrms);
    if(UDMA_SOK == retVal)
    {
        if(Udma_chGetTdCqRingHandle(chHandle) != NULL_PTR)
        {
            GT_0trace(taskObj->traceMask, GT_ERR,
                      " |TEST INFO|:: FAIL:: UDMA:: chGetTdCqRingHandle:: Pos::"
                      " Check for Valid args!!\n");
            retVal = UDMA_EFAIL;
        }
        else
        {
            retVal = UDMA_SOK;
        }
    }
    Udma_chClose(chHandle);

    return retVal;
}

/* 
 * Test Case Description: Verifies the function Udma_chGetFqRingNum
 * Test scenario 1: Check for Valid args
 */
int32_t UdmaTestChGetFqRingNum(UdmaTestTaskObj *taskObj)
{
    int32_t           retVal = UDMA_SOK;
    uint32_t          heapId = UTILS_MEM_HEAP_ID_MSMC;
    uint32_t          instID;
    Udma_ChHandle     chHandle;
    struct Udma_ChObj chObj;
    Udma_ChPrms       chPrms;
    uint32_t          elemCnt = 50U, ringMemSize;
    uint32_t          chType;
    Udma_DrvHandle    drvHandle;
    void              *ringMem = NULL;

    GT_1trace(taskObj->traceMask, GT_INFO1,
              " |TEST INFO|:: Task:%d: UDMA ChGetFqRingNum Testcase ::\r\n",
              taskObj->taskId);

    ringMemSize = elemCnt * sizeof (uint64_t);
    ringMem = Utils_memAlloc(heapId, ringMemSize, UDMA_CACHELINE_ALIGNMENT);
    if(NULL == ringMem)
    {
        retVal = UDMA_EALLOC;
        GT_0trace(taskObj->traceMask, GT_ERR, " Ring memory allocation failure\r\n");
    }

    if(UDMA_SOK == retVal)
    {
        /*Test scenario 1: Check for Valid args*/
        chHandle                      = &chObj;
        instID                        = UDMA_TEST_DEFAULT_UDMA_INST;
        chType                        = UDMA_CH_TYPE_TX;
        UdmaChPrms_init(&chPrms, chType);
        drvHandle                     = &taskObj->testObj->drvObj[instID];
        chPrms.peerChNum              = UDMA_PSIL_CH_MCU_CPSW0_TX;
        chPrms.fqRingPrms.ringMem     = ringMem;
        chPrms.fqRingPrms.ringMemSize = ringMemSize;
        chPrms.fqRingPrms.elemCnt     = elemCnt;
        retVal                        = Udma_chOpen(drvHandle, chHandle, chType, &chPrms);
        if(UDMA_SOK == retVal)
        {
            retVal = Udma_chGetFqRingNum(chHandle);
            if(retVal == UDMA_RING_INVALID)
            {
                GT_0trace(taskObj->traceMask, GT_ERR,
                          " |TEST INFO|:: FAIL:: UDMA:: chGetFqRingNum:: Pos::"
                          " Check for Valid args!!\n");
                retVal = UDMA_EFAIL;
            }
            else
            {
                retVal = UDMA_SOK;
            }
        }
        Udma_chClose(chHandle);
    }

    if(NULL != ringMem)
    {
        retVal += Utils_memFree(heapId, ringMem, ringMemSize);
        if(UDMA_SOK != retVal)
        {
            GT_0trace(taskObj->traceMask, GT_ERR, " Ring free failed!!\n");
        }
    }

    return (retVal);
}

/*
 * Test Case Description: Verifies the function Udma_chPause 
 * Test scenario 1: Check when instType is UDMA_INST_TYPE_LCDMA_BCDMA 
 *                  and chType is UDMA_CH_TYPE_TX
 */
int32_t UdmaTestChSetSwTriggerRegister(UdmaTestTaskObj *taskObj)
{
    int32_t            retVal = UDMA_SOK;
#if (UDMA_SOC_CFG_BCDMA_PRESENT == 1)
    struct Udma_ChObj  chObj;
    Udma_ChHandle      chHandle;
    struct Udma_DrvObj backUpDrvObj;
    Udma_DrvHandle     drvHandle;
    Udma_ChPrms        chPrms;
    uint32_t           chType;
    uint32_t           timeout;
    uint32_t           instID; 
    uint32_t           trigger;

    GT_1trace(taskObj->traceMask, GT_INFO1,
              " |TEST INFO|:: Task:%d: UDMA ChSetSwTriggerRegister positive Testcase ::\r\n",
              taskObj->taskId);

    /* Test scenario 1: Check when instType is UDMA_INST_TYPE_LCDMA_BCDMA 
    *                   and chType is UDMA_CH_TYPE_TX 
    */
    chHandle         = &chObj;
    timeout          = 0U;
    instID           = UDMA_TEST_INST_ID_BCDMA_0;
    chType           = UDMA_CH_TYPE_TX;
    backUpDrvObj     = taskObj->testObj->drvObj[instID];
    drvHandle        = &taskObj->testObj->drvObj[instID];
    UdmaChPrms_init(&chPrms, chType);
    chPrms.peerChNum = UDMA_PSIL_CH_MAIN_CSI_TX;
    retVal           = Udma_chOpen(drvHandle, chHandle, chType, &chPrms);
    trigger          = CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL1;
    Udma_ChTxPrms txChPrms;
    UdmaChTxPrms_init(&txChPrms, chType);
    if(UDMA_SOK == retVal)
    {
        retVal = Udma_chConfigTx(chHandle, &txChPrms);
        if(UDMA_SOK == retVal)
        {
            retVal = Udma_chEnable(chHandle);
            if(UDMA_SOK == retVal)
            {
                retVal = Udma_chSetSwTrigger(chHandle, trigger);
                if(UDMA_SOK != retVal)
                {                
                    GT_0trace(taskObj->traceMask, GT_ERR,
                              " |TEST INFO|:: FAIL:: UDMA:: ChSetSwTriggerRegister::"
                              " Pos:: Check when instType is UDMA_INST_TYPE_LCDMA_BCDMA "
                              " and chType is UDMA_CH_TYPE_TX!!\n");
                    retVal = UDMA_EFAIL;
                }
                else
                {
                    Udma_chDisable(chHandle, timeout);
                    Udma_chClose(chHandle);
                }
            }
        }
    }
    taskObj->testObj->drvObj[instID] = backUpDrvObj;
#endif

    return retVal;
}

