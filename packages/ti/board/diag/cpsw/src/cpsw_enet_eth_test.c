/*
 *  Copyright (c) Texas Instruments Incorporated 2022
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
 *  \file   cpsw_enet_eth_test.c
 *
 *  \brief  CPSW ethernet diagnostic test file
 *
 *  Targeted Functionality: Verification of basic functionality of
 *  CPSW Ethernet interface.
 *
 *  Operation: This is the Loopback test code for the Ethernet Interface.
 *  The test code showcases usage of the ENET Driver exported API for
 *  sending/receiving Ethernet packets.
 *  Test includes MAC, PHY, EXTERNAL loopbacks for CPSW 2G MAIN and CPSW 2G MCU.
 *
 *  Test Setup: To run the example:
 *              1) Build the example for MCU2_1 core to verify CPSW 2G MAIN
 *              2) Build the example for MCU1_0 core to verify CPSW 2G MCU
 *              3) Connect single ended ethernet cables to the ports J39(MAIN RGMII)
 *                 and J40(MCU RGMII)
 *              4) Run each binaries at a time to verify MAIN RGMII and MCU RGMII
 *                 seperately
 * 
 *  Supported SoCs: J784S4
 *
 *  Supported Platforms: j784s4_evm.
 *
 */

/* Test application local header file */
#include "cpsw_enet_eth_test.h"

/* Enet loopback test object */
BoardDiag_EnetObj gEnetLpbk;

volatile bool txSem = false;
volatile bool rxSem = false;


/**
 * \brief   ENET receive ISR function
 *
 * \param   appData      [IN]   Pointer to application data
 *
 */
void BoardDiag_enetRxIsrFxn(void *appData)
{
    rxSem = true;
}

/**
 * \brief   ENET transmit ISR function
 *
 * \param   appData      [IN]   Pointer to application data
 *
 */
void BoardDiag_enetTxIsrFxn(void *appData)
{
    txSem = true;
}

/**
 * \brief   This function is used to retrieve's any CPSW packets that may be free now
 *
 * \param   NULL
 *
 * \return  uint32_t - Transmit free queue count
 *
 */
uint32_t BoardDiag_enetRetrieveFreeTxPkts(void)
{
    EnetDma_PktQ txFreeQ;
    EnetDma_Pkt *pktInfo;
    int32_t status;
    uint32_t txFreeQCnt = 0U;

    EnetQueue_initQ(&txFreeQ);

    /* Retrieve any CPSW packets that may be free now */
    status = EnetDma_retrieveTxPktQ(gEnetLpbk.hTxCh, &txFreeQ);
    if (status == ENET_SOK)
    {
        txFreeQCnt = EnetQueue_getQCount(&txFreeQ);

        pktInfo = (EnetDma_Pkt *)EnetQueue_deq(&txFreeQ);
        while (NULL != pktInfo)
        {
            EnetDma_checkPktState(&pktInfo->pktState,
                                    ENET_PKTSTATE_MODULE_APP,
                                    ENET_PKTSTATE_APP_WITH_DRIVER,
                                    ENET_PKTSTATE_APP_WITH_FREEQ);

            EnetQueue_enq(&gEnetLpbk.txFreePktInfoQ, &pktInfo->node);
            pktInfo = (EnetDma_Pkt *)EnetQueue_deq(&txFreeQ);
        }
    }
    else
    {
        UART_printf("retrieveFreeTxPkts() failed to retrieve pkts: %d\n",
                           status);
    }

    return txFreeQCnt;
}

/**
 * \brief   This function is used for CPSW packet transmission
 *
 * \param   NULL
 *
 *
 */
void BoardDiag_enetPktTx(void)
{
    EnetDma_PktQ txSubmitQ;
    EnetDma_Pkt *pktInfo;
    EthFrame *frame;
    uint32_t txRetrievePktCnt;
    uint32_t loopCnt, pktCnt;
    int32_t status = ENET_SOK;
    uint8_t bcastAddr[ENET_MAC_ADDR_LEN] = {0xffU, 0xffU, 0xffU, 0xffU, 0xffU, 0xffU};

    gEnetLpbk.totalTxCnt = 0U;
    for (loopCnt = 0U; loopCnt < ENETLPBK_NUM_ITERATION; loopCnt++)
    {
        pktCnt = 0U;
        while (pktCnt < ENETLPBK_TEST_PKT_NUM)
        {
            /* Transmit a single packet */
            EnetQueue_initQ(&txSubmitQ);

            /* Dequeue one free TX Eth packet */
            pktInfo = (EnetDma_Pkt *)EnetQueue_deq(&gEnetLpbk.txFreePktInfoQ);

            while (NULL != pktInfo)
            {
                pktCnt++;

                /* Fill the TX Eth frame with test content */
                frame = (EthFrame *)pktInfo->bufPtr;
                memcpy(frame->hdr.dstMac, bcastAddr, ENET_MAC_ADDR_LEN);
                memcpy(frame->hdr.srcMac, &gEnetLpbk.hostMacAddr[0U], ENET_MAC_ADDR_LEN);
                frame->hdr.etherType = Enet_htons(ETHERTYPE_EXPERIMENTAL1);
                memset(&frame->payload[0U], (uint8_t)(0xA5 + pktCnt), ENETLPBK_TEST_PKT_LEN);

                pktInfo->userBufLen = ENETLPBK_TEST_PKT_LEN + sizeof(EthFrameHeader);
                pktInfo->appPriv    = &gEnetLpbk;
                pktInfo->chkSumInfo = 0U;
                pktInfo->txPortNum  = ENET_MAC_PORT_INV;
                pktInfo->tsInfo.enableHostTxTs = false;
                EnetDma_checkPktState(&pktInfo->pktState,
                                        ENET_PKTSTATE_MODULE_APP,
                                        ENET_PKTSTATE_APP_WITH_FREEQ,
                                        ENET_PKTSTATE_APP_WITH_DRIVER);

                /* Enqueue the packet for later transmission */
                EnetQueue_enq(&txSubmitQ, &pktInfo->node);

                if (pktCnt >= ENETLPBK_TEST_PKT_NUM)
                {
                    break;
                }

                /* Dequeue one free TX Eth packet */
                pktInfo = (EnetDma_Pkt *)EnetQueue_deq(&gEnetLpbk.txFreePktInfoQ);
            }

            while (0U != EnetQueue_getQCount(&txSubmitQ))
            {
                uint32_t txCnt = EnetQueue_getQCount(&txSubmitQ);
                status = EnetDma_submitTxPktQ(gEnetLpbk.hTxCh,
                                                   &txSubmitQ);
                while (txSem != true);
                txSem = false;

                /* Retrieve TX free packets */
                if (status == ENET_SOK)
                {
                    txCnt            = txCnt - EnetQueue_getQCount(&txSubmitQ);
                    txRetrievePktCnt = 0U;
                    while (txRetrievePktCnt != txCnt)
                    {
                        txRetrievePktCnt += BoardDiag_enetRetrieveFreeTxPkts();
                    }
                }
                else
                {
                    break;
                }
            }
        }

        gEnetLpbk.totalTxCnt += pktCnt;
    }

    UART_printf("Transmitted %d packets \n", gEnetLpbk.totalTxCnt);

}

/**
 * \brief   This function is used to queue the received packets to rx ready queue
 *
 * \param   NULL
 *
 * \return  uint32_t - Receive ready queue count
 *
 */
uint32_t BoardDiag_enetReceivePkts(void)
{
    EnetDma_PktQ rxReadyQ;
    EnetDma_Pkt *pktInfo;
    int32_t status;
    uint32_t rxReadyCnt = 0U;

    EnetQueue_initQ(&rxReadyQ);

    /* Retrieve any CPSW packets which are ready */
    status = EnetDma_retrieveRxPktQ(gEnetLpbk.hRxCh, &rxReadyQ);
    if (status == ENET_SOK)
    {
        rxReadyCnt = EnetQueue_getQCount(&rxReadyQ);

        /* Queue the received packet to rxReadyQ and pass new ones from rxFreeQ
        **/
        pktInfo = (EnetDma_Pkt *)EnetQueue_deq(&rxReadyQ);
        while (pktInfo != NULL)
        {
            EnetDma_checkPktState(&pktInfo->pktState,
                                    ENET_PKTSTATE_MODULE_APP,
                                    ENET_PKTSTATE_APP_WITH_DRIVER,
                                    ENET_PKTSTATE_APP_WITH_READYQ);

            EnetQueue_enq(&gEnetLpbk.rxReadyQ, &pktInfo->node);
            pktInfo = (EnetDma_Pkt *)EnetQueue_deq(&rxReadyQ);
        }
    }
    else
    {
        UART_printf("receivePkts() failed to retrieve pkts: %d\n",
                           status);
    }

    return rxReadyCnt;
}

/**
 * \brief   This function is used for CPSW packet reception
 *
 * \param   NULL
 *
 */
void BoardDiag_enetPktRx(void)
{
    EnetDma_Pkt *pktInfo;
    EthFrame *frame;
    uint32_t rxReadyCnt;
    uint32_t loopCnt, loopRxPktCnt;
    int32_t status = ENET_SOK;

    gEnetLpbk.totalRxCnt = 0U;

    for (loopCnt = 0U; loopCnt < ENETLPBK_NUM_ITERATION; loopCnt++)
    {
        loopRxPktCnt = 0U;
        /* Wait for packet reception */
        do
        {
            while (rxSem != true);
                rxSem = false;

            /* Get the packets received so far */
            rxReadyCnt = BoardDiag_enetReceivePkts();
            if (rxReadyCnt > 0U)
            {
                /* Consume the received packets and release them */
                pktInfo = (EnetDma_Pkt *)EnetQueue_deq(&gEnetLpbk.rxReadyQ);
                while (NULL != pktInfo)
                {
                    EnetDma_checkPktState(&pktInfo->pktState,
                                            ENET_PKTSTATE_MODULE_APP,
                                            ENET_PKTSTATE_APP_WITH_READYQ,
                                            ENET_PKTSTATE_APP_WITH_FREEQ);

                    /* Consume the packet by just printing its content */
                    if (gEnetLpbk.printFrame)
                    {
                        frame = (EthFrame *)pktInfo->bufPtr;

                        EnetAppUtils_printFrame(frame,
                                                pktInfo->userBufLen - sizeof(EthFrameHeader));
                    }

                    /* Release the received packet */
                    EnetQueue_enq(&gEnetLpbk.rxFreeQ, &pktInfo->node);
                    pktInfo = (EnetDma_Pkt *)EnetQueue_deq(&gEnetLpbk.rxReadyQ);
                }

                /*Submit now processed buffers */
                if (status == ENET_SOK)
                {
                    EnetAppUtils_validatePacketState(&gEnetLpbk.rxFreeQ,
                                                     ENET_PKTSTATE_APP_WITH_FREEQ,
                                                     ENET_PKTSTATE_APP_WITH_DRIVER);

                    EnetDma_submitRxPktQ(gEnetLpbk.hRxCh,
                                         &gEnetLpbk.rxFreeQ);
                }
            }

            loopRxPktCnt += rxReadyCnt;
        }
        while (loopRxPktCnt < ENETLPBK_TEST_PKT_NUM);

        gEnetLpbk.totalRxCnt += loopRxPktCnt;
    }

    if (status != ENET_SOK)
    {
        UART_printf("Failed to transmit/receive packets, transmitted : %d, received: %d \n", ENETLPBK_TEST_PKT_NUM, gEnetLpbk.totalRxCnt);
    }
    else
    {
        UART_printf("Received %d packets\n", gEnetLpbk.totalRxCnt);
    }

}

/**
 * \brief   This function is used to perform the CPSW
 *          Ethernet external loopback test
 *
 * \param   NULL
 *
 * \return  int8_t
 *               0 - in case of success
 *              -1 - in case of failure.
 *
 */
int32_t BoardDiag_enetLoopbackTest(void)
{
    EnetOsal_Cfg osalCfg;
    EnetUtils_Cfg utilsCfg;
    Enet_IoctlPrms prms;
    int32_t status;

    EnetAppUtils_enableClocks(gEnetLpbk.enetType, gEnetLpbk.instId);

    /* Local core id */
    gEnetLpbk.coreId = EnetSoc_getCoreId();

    /* Initialize Enet driver (use default OSAL and utils) */
    Enet_initOsalCfg(&osalCfg);
    Enet_initUtilsCfg(&utilsCfg);
    Enet_init(&osalCfg, &utilsCfg);

    /* Open Enet driver */
    status = BoardDiag_enetOpenEnet();
    if (status != ENET_SOK)
    {
        UART_printf("Failed to open Enet driver: %d\n", status);
    }

    if (status == ENET_SOK)
    {
        /* Attach the core with RM */
        uint32_t coreId;
        EnetPer_AttachCoreOutArgs attachCoreOutArgs;
        coreId = gEnetLpbk.coreId;

        ENET_IOCTL_SET_INOUT_ARGS(&prms, &coreId, &attachCoreOutArgs);
        status = Enet_ioctl(gEnetLpbk.hEnet, gEnetLpbk.coreId, ENET_PER_IOCTL_ATTACH_CORE, &prms);
        if (status != ENET_SOK)
        {
            UART_printf("BoardDiag_enetloopbackTest failed ENET_PER_IOCTL_ATTACH_CORE: %d\n", status);
        }
        else
        {
            gEnetLpbk.coreKey = attachCoreOutArgs.coreKey;
        }
    }

    if (status == ENET_SOK)
    {
        /* memutils open should happen after Cpsw is opened as it uses CpswUtils_Q
         * functions */
        status = EnetMem_init();
        EnetAppUtils_assert(ENET_SOK == status);
    }

    /* Open DMA driver */
    if (status == ENET_SOK)
    {
        status = BoardDiag_enetOpenDma();
        if (status != ENET_SOK)
        {
            UART_printf("Failed to open DMA: %d\n", status);
        }
    }

    /* Enable host port */
    if (status == ENET_SOK)
    {
        if (Enet_isCpswFamily(gEnetLpbk.enetType))
        {
            status = BoardDiag_enetSetupCpswAle();
            if (status != ENET_SOK)
            {
                UART_printf("Failed to setup CPSW ALE: %d\n", status);
            }
        }

        if (status == ENET_SOK)
        {
            ENET_IOCTL_SET_NO_ARGS(&prms);
            status = Enet_ioctl(gEnetLpbk.hEnet, gEnetLpbk.coreId, ENET_HOSTPORT_IOCTL_ENABLE, &prms);
            if (status != ENET_SOK)
            {
                UART_printf("Failed to enable host port: %d\n", status);
            }
        }
    }

    /* Show alive PHYs */
    if (status == ENET_SOK)
    {
        status = BoardDiag_enetShowAlivePhys();
    }

    /* Wait for link up */
    if ((status == ENET_SOK) && gEnetLpbk.testPhyLoopback)
    {
        status = BoardDiag_enetWaitForLinkUp();
    }

    /* Do packet transmission and reception */
    if (status == ENET_SOK)
    {
        BoardDiag_enetPktTx();
        BoardDiag_enetPktRx();
    }

    /* Print network statistics */
    if (status == ENET_SOK)
    {
        if (Enet_isCpswFamily(gEnetLpbk.enetType))
        {
            BoardDiag_enetShowCpswStats();
        }
    }

    /* Disable host port */
    if (status == ENET_SOK)
    {
        ENET_IOCTL_SET_NO_ARGS(&prms);
        status = Enet_ioctl(gEnetLpbk.hEnet, gEnetLpbk.coreId, ENET_HOSTPORT_IOCTL_DISABLE, &prms);
        if (status != ENET_SOK)
        {
            UART_printf("Failed to disable host port: %d\n", status);
        }
    }
    /* Print DMA statistics */
    if (status == ENET_SOK)
    {
        EnetAppUtils_showRxChStats(gEnetLpbk.hRxCh);
        EnetAppUtils_showTxChStats(gEnetLpbk.hTxCh);
    }


    /* Close Enet DMA driver */
    BoardDiag_enetCloseDma();

    /* Close Enet driver */
    BoardDiag_enetCloseEnet();

    /* Disable peripheral clocks */
    EnetAppUtils_disableClocks(gEnetLpbk.enetType, gEnetLpbk.instId);

    /* Deinit Enet driver */
    Enet_deinit();

    return status;
}

/**
 * \brief   This function is used to initialize cpsw configurations.
 *
 * \param   cpswCfg           cpsw configurations
 *
 * \return  None
 *
 */
void BoardDiag_enetInitCpswCfg(Cpsw_Cfg *cpswCfg)
{
    CpswHostPort_Cfg *hostPortCfg = &cpswCfg->hostPortCfg;
    CpswAle_Cfg *aleCfg = &cpswCfg->aleCfg;
    CpswCpts_Cfg *cptsCfg = &cpswCfg->cptsCfg;

    /* Set initial config */
    Enet_initCfg(gEnetLpbk.enetType, gEnetLpbk.instId, cpswCfg, sizeof(*cpswCfg));

    /* Peripheral config */
    cpswCfg->vlanCfg.vlanAware = false;

    /* Host port config */
    hostPortCfg->removeCrc      = true;
    hostPortCfg->padShortPacket = true;
    hostPortCfg->passCrcErrors  = true;

    /* ALE config */
    aleCfg->modeFlags                          = CPSW_ALE_CFG_MODULE_EN;
    aleCfg->agingCfg.autoAgingEn               = true;
    aleCfg->agingCfg.agingPeriodInMs           = 1000;
    aleCfg->nwSecCfg.vid0ModeEn                = true;
    aleCfg->vlanCfg.aleVlanAwareMode           = false;
    aleCfg->vlanCfg.cpswVlanAwareMode          = false;
    aleCfg->vlanCfg.unknownUnregMcastFloodMask = CPSW_ALE_ALL_PORTS_MASK;
    aleCfg->vlanCfg.unknownRegMcastFloodMask   = CPSW_ALE_ALL_PORTS_MASK;
    aleCfg->vlanCfg.unknownVlanMemberListMask  = CPSW_ALE_ALL_PORTS_MASK;

    /* CPTS config */
    /* Note: Timestamping and MAC loopback are not supported together because of
     * IP limitation, so disabling timestamping for this application */
    cptsCfg->hostRxTsEn = false;

    EnetAppUtils_initResourceConfig(gEnetLpbk.enetType, gEnetLpbk.instId, gEnetLpbk.coreId, &cpswCfg->resCfg);
}

/**
 * \brief   This function is used to set the ALE port state to forward.
 *
 * \param   NULL
 *
 * \return  int32_t
 *               0 - in case of success
 *              -1 - in case of failure.
 *
 */
int32_t BoardDiag_enetSetupCpswAle(void)
{
    Enet_IoctlPrms prms;
    CpswAle_SetPortStateInArgs setPortStateInArgs;
    CpswAle_SetUcastEntryInArgs setUcastInArgs;
    uint32_t entryIdx;
    int32_t status;

    /* ALE entry with "secure" bit cleared is required for loopback */
    setUcastInArgs.addr.vlanId  = 0U;
    setUcastInArgs.info.portNum = CPSW_ALE_HOST_PORT_NUM;
    setUcastInArgs.info.blocked = false;
    setUcastInArgs.info.secure  = false;
    setUcastInArgs.info.super   = false;
    setUcastInArgs.info.ageable = false;
    setUcastInArgs.info.trunk   = false;
    EnetUtils_copyMacAddr(&setUcastInArgs.addr.addr[0U], gEnetLpbk.hostMacAddr);
    ENET_IOCTL_SET_INOUT_ARGS(&prms, &setUcastInArgs, &entryIdx);

    status = Enet_ioctl(gEnetLpbk.hEnet, gEnetLpbk.coreId, CPSW_ALE_IOCTL_ADD_UCAST, &prms);
    if (status != ENET_SOK)
    {
        UART_printf("Failed to add ucast entry: %d\n", status);
    }

    /* Set host port to 'forwarding' state */
    if (status == ENET_SOK)
    {
        setPortStateInArgs.portNum   = CPSW_ALE_HOST_PORT_NUM;
        setPortStateInArgs.portState = CPSW_ALE_PORTSTATE_FORWARD;
        ENET_IOCTL_SET_IN_ARGS(&prms, &setPortStateInArgs);

        status = Enet_ioctl(gEnetLpbk.hEnet, gEnetLpbk.coreId, CPSW_ALE_IOCTL_SET_PORT_STATE, &prms);
        if (status != ENET_SOK)
        {
            UART_printf("Failed to set ALE port state: %d\n", status);
        }
    }

    return status;
}

/**
 * \brief   This function is used to open the ENET driver
 *
 * \param   NULL
 *
 * \return  int8_t
 *               0 - in case of success
 *              -1 - in case of failure.
 *
 */
int32_t BoardDiag_enetOpenEnet(void)
{
    Cpsw_Cfg cpswCfg;
    EnetUdma_Cfg dmaCfg;
    Enet_IoctlPrms prms;
    EnetPer_PortLinkCfg portLinkCfg;
    CpswMacPort_Cfg macCfg;
    int32_t status = ENET_SOK;

    cpswCfg.dmaCfg = &dmaCfg;

    /* Initialize peripheral config */
    BoardDiag_enetInitCpswCfg(&cpswCfg);

    if (gEnetLpbk.enetType == ENET_CPSW_9G)
    {
        UART_printf("CPSW_9G Test on MAIN NAVSS\n");
    }
    else if (gEnetLpbk.enetType == ENET_CPSW_5G)
    {
        UART_printf("CPSW_5G Test on MAIN NAVSS\n");
    }
    else if (gEnetLpbk.enetType == ENET_CPSW_2G)
    {
        if (gEnetLpbk.instId == 0)
        {
            UART_printf("CPSW_2G Test on MCU NAVSS\n");
        }
        else if (gEnetLpbk.instId == 1)
        {
            UART_printf("CPSW_2G Test on MAIN NAVSS\n");
        }
    }

    dmaCfg.rxChInitPrms.dmaPriority = UDMA_DEFAULT_RX_CH_DMA_PRIORITY;

    /* App should open UDMA first as UDMA handle is needed to initialize
     * CPSW RX channel */
    gEnetLpbk.hUdmaDrv = EnetAppUtils_udmaOpen(gEnetLpbk.enetType, NULL);
    EnetAppUtils_assert(NULL != gEnetLpbk.hUdmaDrv);

    dmaCfg.hUdmaDrv = gEnetLpbk.hUdmaDrv;

    /* Set Enet global runtime log level */
    Enet_setTraceLevel(ENET_TRACE_DEBUG);

    /* Open the Enet driver */
    gEnetLpbk.hEnet = Enet_open(gEnetLpbk.enetType, gEnetLpbk.instId, &cpswCfg, sizeof(cpswCfg));
    if (gEnetLpbk.hEnet == NULL)
    {
        UART_printf("Failed to open Enet driver\n");
        status = ENET_EFAIL;
    }

    /* Setup port link open parameters */
    if (status == ENET_SOK)
    {
        EnetBoard_EthPort ethPort;
        EnetMacPort_LinkCfg *linkCfg = &portLinkCfg.linkCfg;
        EnetMacPort_Interface *mii = &portLinkCfg.mii;
        EnetPhy_Cfg *phyCfg = &portLinkCfg.phyCfg;
        EnetPhy_Mii phyMii;

        /* Setup board for requested Ethernet port */
        ethPort.enetType = gEnetLpbk.enetType;
        ethPort.instId   = gEnetLpbk.instId;
        ethPort.macPort  = gEnetLpbk.macPort;
        ethPort.boardId  = gEnetLpbk.boardId;
        BoardDiag_macMode2MacMii(gEnetLpbk.macMode, &ethPort.mii);

        status = EnetBoard_setupPorts(&ethPort, 1U);
        EnetAppUtils_assert(status == ENET_SOK);

        /* Set port link params */
        portLinkCfg.macPort = gEnetLpbk.macPort;
        portLinkCfg.macCfg = &macCfg;

        CpswMacPort_initCfg(&macCfg);
        BoardDiag_macMode2MacMii(gEnetLpbk.macMode, mii);

        if (gEnetLpbk.testPhyLoopback)
        {
            const EnetBoard_PhyCfg *boardPhyCfg = NULL;

            /* Set PHY configuration params */
            EnetPhy_initCfg(phyCfg);
            status = BoardDiag_macMode2PhyMii(gEnetLpbk.macMode, &phyMii);

            if (status == ENET_SOK)
            {
                boardPhyCfg = EnetBoard_getPhyCfg(&ethPort);
                if (boardPhyCfg != NULL)
                {
                    phyCfg->phyAddr     = boardPhyCfg->phyAddr;
                    phyCfg->isStrapped  = boardPhyCfg->isStrapped;
                    phyCfg->skipExtendedCfg = boardPhyCfg->skipExtendedCfg;
                    phyCfg->extendedCfgSize = boardPhyCfg->extendedCfgSize;
                    memcpy(phyCfg->extendedCfg, boardPhyCfg->extendedCfg, phyCfg->extendedCfgSize);
                }
                else
                {
                    UART_printf("PHY info not found\n");
                    EnetAppUtils_assert(false);
                }

                if ((phyMii == ENETPHY_MAC_MII_MII) ||
                    (phyMii == ENETPHY_MAC_MII_RMII))
                {
                    linkCfg->speed = ENET_SPEED_100MBIT;
                }
                else
                {
                    if(gEnetLpbk.testLoopBackType)
                    {
                        linkCfg->speed = ENET_SPEED_100MBIT;
                    }
                    else
                    {
                        linkCfg->speed = ENET_SPEED_1GBIT; 
                    }
                }

                linkCfg->duplexity = ENET_DUPLEX_FULL;
            }
        }
        else
        {
            phyCfg->phyAddr = ENETPHY_INVALID_PHYADDR;

            if (mii->layerType == ENET_MAC_LAYER_MII)
            {
                linkCfg->speed = ENET_SPEED_100MBIT;
            }
            else
            {
                linkCfg->speed = ENET_SPEED_1GBIT;
            }

            linkCfg->duplexity = ENET_DUPLEX_FULL;

            if (EnetMacPort_isSgmii(mii))
            {
                macCfg.sgmiiMode = ENET_MAC_SGMIIMODE_SGMII_FORCEDLINK;
            }
        }

        /* MAC and PHY loopbacks are mutually exclusive */
        if(gEnetLpbk.testLoopBackType)
        {
            gEnetLpbk.testExtLoopback = true;
            UART_printf("\n Setting for external loopback\n");
            phyCfg->loopbackEn = gEnetLpbk.testLoopBackType && !gEnetLpbk.testExtLoopback;
            macCfg.loopbackEn = !gEnetLpbk.testLoopBackType;
        }
        else
        {
            gEnetLpbk.testExtLoopback = false;
            phyCfg->loopbackEn = gEnetLpbk.testPhyLoopback && !gEnetLpbk.testExtLoopback;
            macCfg.loopbackEn = !gEnetLpbk.testPhyLoopback;
        }
    }

    /* Open port link */
    if (status == ENET_SOK)
    {
        ENET_IOCTL_SET_IN_ARGS(&prms, &portLinkCfg);

        status = Enet_ioctl(gEnetLpbk.hEnet, gEnetLpbk.coreId, ENET_PER_IOCTL_OPEN_PORT_LINK, &prms);
        if (status != ENET_SOK)
        {
            UART_printf("Failed to open port link: %d\n", status);
        }
    }

    return status;
}

/**
 * \brief   This function is used for close the ENET module.
 *
 * \param   NULL
 *
 * \return  None
 */
void BoardDiag_enetCloseEnet(void)
{
    Enet_IoctlPrms prms;
    int32_t status;

    /* Close port link */
    ENET_IOCTL_SET_IN_ARGS(&prms, &gEnetLpbk.macPort);

    status = Enet_ioctl(gEnetLpbk.hEnet, gEnetLpbk.coreId, ENET_PER_IOCTL_CLOSE_PORT_LINK, &prms);
    if (status != ENET_SOK)
    {
        UART_printf("Failed to close port link: %d\n", status);
    }

    /* Detach core */
    if (status == ENET_SOK)
    {
        ENET_IOCTL_SET_IN_ARGS(&prms, &gEnetLpbk.coreKey);

        status = Enet_ioctl(gEnetLpbk.hEnet, gEnetLpbk.coreId, ENET_PER_IOCTL_DETACH_CORE, &prms);
        if (status != ENET_SOK)
        {
            UART_printf("Failed to detach core key %u: %d\n", gEnetLpbk.coreKey, status);
        }
    }

    /* Close Enet driver */
    Enet_close(gEnetLpbk.hEnet);

    /* Close UDMA */
    EnetAppUtils_udmaclose(gEnetLpbk.hUdmaDrv);

    gEnetLpbk.hEnet = NULL;
}

/**
 * \brief   This function checks the live status of the phy
 *
 * \param   NULL
 *
 * \return  int32_t
 *               0 - in case of success
 *              -1 - in case of failure.
 *
 */
int32_t BoardDiag_enetShowAlivePhys(void)
{
    Enet_IoctlPrms prms;
    bool alive = false;
    int8_t i;
    int32_t status;

    for (i = 0U; i < ENET_MDIO_PHY_CNT_MAX; i++)
    {
        ENET_IOCTL_SET_INOUT_ARGS(&prms, &i, &alive);

        status = Enet_ioctl(gEnetLpbk.hEnet, gEnetLpbk.coreId, ENET_MDIO_IOCTL_IS_ALIVE, &prms);
        if (status == ENET_SOK)
        {
            if (alive == true)
            {
                UART_printf("PHY %u is alive\n", i);
            }
        }
        else
        {
            UART_printf("Failed to get PHY %u alive status: %d\n", i, status);
        }
    }

    return status;
}

/**
 * \brief   This function Waits till phy link is up.
 *
 * \param   NULL
 *
 * \return  int32_t
 *               0 - in case of phy link is up
 *              -1 - in case of phy link is down.
 *
 */
int32_t BoardDiag_enetWaitForLinkUp(void)
{
    Enet_IoctlPrms prms;
    bool linked = false;
    int32_t status = ENET_SOK;

    ENET_IOCTL_SET_INOUT_ARGS(&prms, &gEnetLpbk.macPort, &linked);

    while (!linked)
    {
        status = Enet_ioctl(gEnetLpbk.hEnet, gEnetLpbk.coreId, ENET_PER_IOCTL_IS_PORT_LINK_UP, &prms);
        if (status != ENET_SOK)
        {
            UART_printf("Failed to get port %u's link status: %d\n",
                            ENET_MACPORT_ID(gEnetLpbk.macPort), status);
            linked = false;
            break;
        }

        if (!linked)
        {
            Enet_periodicTick(gEnetLpbk.hEnet);
            BOARD_delay(1000);
        }
    }

    return status;
}

/**
 * \brief   This function is used to display Mac and Host port statistics
 *
 * \param   NULL
 *
 * \return  None
 *
 */
void BoardDiag_enetShowCpswStats(void)
{
    Enet_IoctlPrms prms;
    CpswStats_PortStats portStats;
    int32_t status;

    /* Show host port statistics */
    ENET_IOCTL_SET_OUT_ARGS(&prms, &portStats);
    status = Enet_ioctl(gEnetLpbk.hEnet, gEnetLpbk.coreId, ENET_STATS_IOCTL_GET_HOSTPORT_STATS, &prms);
    if (status == ENET_SOK)
    {
        UART_printf("\n Port 0 Statistics\n");
        UART_printf("-----------------------------------------\n");
        EnetAppUtils_printHostPortStats2G((CpswStats_HostPort_2g *)&portStats);
        UART_printf("\n");
    }
    else
    {
        UART_printf("Failed to get host stats: %d\n", status);
    }

    /* Show MAC port statistics */
    if (status == ENET_SOK)
    {
        ENET_IOCTL_SET_INOUT_ARGS(&prms, &gEnetLpbk.macPort, &portStats);
        status = Enet_ioctl(gEnetLpbk.hEnet, gEnetLpbk.coreId, ENET_STATS_IOCTL_GET_MACPORT_STATS, &prms);
        if (status == ENET_SOK)
        {
            UART_printf("\n Port 1 Statistics\n");
            UART_printf("-----------------------------------------\n");
            EnetAppUtils_printMacPortStats2G((CpswStats_MacPort_2g *)&portStats);
            UART_printf("\n");
        }
        else
        {
            UART_printf("Failed to get MAC stats: %d\n", status);
        }
    }
}

/**
 * \brief   This function is used to initialize the free packet
 *          info queue with the Ethernet packets to be transmitted.
 *
 * \param   NULL
 *
 * \return  None
 *
 */
void BoardDiag_enetInitTxFreePktQ(void)
{
    EnetDma_Pkt *pPktInfo;
    uint32_t pktNum;

    /* Initialize all queues */
    EnetQueue_initQ(&gEnetLpbk.txFreePktInfoQ);

    /* Initialize TX EthPkts and queue them to txFreePktInfoQ */
    for (pktNum = 0U; pktNum < ENET_MEM_NUM_TX_PKTS; pktNum++)
    {
        pPktInfo = EnetMem_allocEthPkt(&gEnetLpbk,
                                                  ENET_MEM_LARGE_POOL_PKT_SIZE,
                                                  ENETDMA_CACHELINE_ALIGNMENT);
        EnetAppUtils_assert(pPktInfo != NULL);
        ENET_UTILS_SET_PKT_APP_STATE(&pPktInfo->pktState, ENET_PKTSTATE_APP_WITH_FREEQ);

        EnetQueue_enq(&gEnetLpbk.txFreePktInfoQ, &pPktInfo->node);
    }

    UART_printf("initQs() txFreePktInfoQ initialized with %d pkts\n",
                       EnetQueue_getQCount(&gEnetLpbk.txFreePktInfoQ));
}

/**
 * \brief   This function is used to initialize the receive ready packet queue
 *
 * \param   NULL
 *
 * \return  None
 *
 */
void BoardDiag_enetInitRxReadyPktQ(void)
{
    EnetDma_PktQ rxReadyQ;
    EnetDma_Pkt *pPktInfo;
    int32_t status;
    uint32_t pktNum;

    EnetQueue_initQ(&gEnetLpbk.rxFreeQ);
    EnetQueue_initQ(&gEnetLpbk.rxReadyQ);
    EnetQueue_initQ(&rxReadyQ);

    for (pktNum = 0U; pktNum < ENET_MEM_NUM_RX_PKTS; pktNum++)
    {
        pPktInfo = EnetMem_allocEthPkt(&gEnetLpbk,
                                                  ENET_MEM_LARGE_POOL_PKT_SIZE,
                                                  ENETDMA_CACHELINE_ALIGNMENT);
        EnetAppUtils_assert(pPktInfo != NULL);
        ENET_UTILS_SET_PKT_APP_STATE(&pPktInfo->pktState, ENET_PKTSTATE_APP_WITH_FREEQ);
        EnetQueue_enq(&gEnetLpbk.rxFreeQ, &pPktInfo->node);
    }

    /* Retrieve any CPSW packets which are ready */
    status = EnetDma_retrieveRxPktQ(gEnetLpbk.hRxCh, &rxReadyQ);
    EnetAppUtils_assert(status == ENET_SOK);
    /* There should not be any packet with DMA during init */
    EnetAppUtils_assert(EnetQueue_getQCount(&rxReadyQ) == 0U);

    EnetAppUtils_validatePacketState(&gEnetLpbk.rxFreeQ,
                                     ENET_PKTSTATE_APP_WITH_FREEQ,
                                     ENET_PKTSTATE_APP_WITH_DRIVER);

    EnetDma_submitRxPktQ(gEnetLpbk.hRxCh,
                         &gEnetLpbk.rxFreeQ);

    /* Assert here as during init no. of DMA descriptors should be equal to
       no. of free Ethernet buffers available with app */
    EnetAppUtils_assert(0U == EnetQueue_getQCount(&gEnetLpbk.rxFreeQ));
}

/**
 * \brief   This function is used to open the CPSW DMA module
 *
 * \param   NULL
 *
 * \return  int8_t
 *               0 - in case of success
 *              -1 - in case of failure.
 *
 */
int32_t BoardDiag_enetOpenDma(void)
{
    int32_t status = ENET_SOK;
    EnetUdma_OpenRxFlowPrms rxChCfg;
    EnetUdma_OpenTxChPrms   txChCfg;

    /* Open the CPSW TX channel  */
    if (status == ENET_SOK)
    {
        EnetDma_initTxChParams(&txChCfg);

        txChCfg.hUdmaDrv = gEnetLpbk.hUdmaDrv;
        txChCfg.cbArg    = &gEnetLpbk;
        txChCfg.notifyCb = BoardDiag_enetTxIsrFxn;

        EnetAppUtils_setCommonTxChPrms(&txChCfg);

        EnetAppUtils_openTxCh(gEnetLpbk.hEnet,
                              gEnetLpbk.coreKey,
                              gEnetLpbk.coreId,
                              &gEnetLpbk.txChNum,
                              &gEnetLpbk.hTxCh,
                              &txChCfg);

        BoardDiag_enetInitTxFreePktQ();

        if (NULL != gEnetLpbk.hTxCh)
        {
            status = EnetDma_enableTxEvent(gEnetLpbk.hTxCh);
            if (ENET_SOK != status)
            {
#if FIX_RM
                /* Free the Ch Num if enable event failed */
                EnetAppUtils_freeTxCh(gEnetLpbk.hEnet,
                                      gEnetLpbk.coreKey,
                                      gEnetLpbk.coreId,
                                      gEnetLpbk.txChNum);
#endif
                UART_printf("EnetUdma_startTxCh() failed: %d\n", status);
                status = ENET_EFAIL;
            }
        }
        else
        {
#if FIX_RM
            /* Free the Ch Num if open Tx Ch failed */
            EnetAppUtils_freeTxCh(gEnetLpbk.hEnet,
                                  gEnetLpbk.coreKey,
                                  gEnetLpbk.coreId,
                                  gEnetLpbk.txChNum);
#endif
            UART_printf("EnetDma_openTxCh() failed to open: %d\n",
                               status);
            status = ENET_EFAIL;
        }
    }

    /* Open the CPSW RX flow  */
    if (status == ENET_SOK)
    {
        EnetDma_initRxChParams(&rxChCfg);

        rxChCfg.hUdmaDrv = gEnetLpbk.hUdmaDrv;
        rxChCfg.notifyCb = BoardDiag_enetRxIsrFxn;
        rxChCfg.cbArg   = &gEnetLpbk;

        EnetAppUtils_setCommonRxFlowPrms(&rxChCfg);
        EnetAppUtils_openRxFlow(gEnetLpbk.enetType,
                                gEnetLpbk.hEnet,
                                gEnetLpbk.coreKey,
                                gEnetLpbk.coreId,
                                true,
                                &gEnetLpbk.rxStartFlowIdx,
                                &gEnetLpbk.rxFlowIdx,
                                &gEnetLpbk.hostMacAddr[0U],
                                &gEnetLpbk.hRxCh,
                                &rxChCfg);
        if (NULL == gEnetLpbk.hRxCh)
        {
            UART_printf("EnetDma_openRxCh() failed to open: %d\n",
                               status);
            EnetAppUtils_assert(NULL != gEnetLpbk.hRxCh);
        }
        else
        {
            UART_printf("Host MAC address: ");
            EnetAppUtils_printMacAddr(gEnetLpbk.hostMacAddr);
            /* Submit all ready RX buffers to DMA.*/
            BoardDiag_enetInitRxReadyPktQ();
        }
    }

    return status;
}

/**
 * \brief   This function is used for de-initialize the ENET DMA driver.
 *
 * \param   NULL
 *
 * \return  None
 */
void BoardDiag_enetCloseDma(void)
{
    EnetDma_PktQ fqPktInfoQ;
    EnetDma_PktQ cqPktInfoQ;

    EnetQueue_initQ(&fqPktInfoQ);
    EnetQueue_initQ(&cqPktInfoQ);

    /* There should not be any ready packet */
    EnetAppUtils_assert(0U == EnetQueue_getQCount(&gEnetLpbk.rxReadyQ));

    /* Close RX channel */
    EnetAppUtils_closeRxFlow(gEnetLpbk.enetType,
                             gEnetLpbk.hEnet,
                             gEnetLpbk.coreKey,
                             gEnetLpbk.coreId,
                             true,
                             &fqPktInfoQ,
                             &cqPktInfoQ,
                             gEnetLpbk.rxStartFlowIdx,
                             gEnetLpbk.rxFlowIdx,
                             gEnetLpbk.hostMacAddr,
                             gEnetLpbk.hRxCh);

    EnetAppUtils_freePktInfoQ(&fqPktInfoQ);
    EnetAppUtils_freePktInfoQ(&cqPktInfoQ);

    /* Close TX channel */
    EnetQueue_initQ(&fqPktInfoQ);
    EnetQueue_initQ(&cqPktInfoQ);

    EnetAppUtils_closeTxCh(gEnetLpbk.hEnet,
                           gEnetLpbk.coreKey,
                           gEnetLpbk.coreId,
                           &fqPktInfoQ,
                           &cqPktInfoQ,
                           gEnetLpbk.hTxCh,
                           gEnetLpbk.txChNum);
    EnetAppUtils_freePktInfoQ(&fqPktInfoQ);
    EnetAppUtils_freePktInfoQ(&cqPktInfoQ);

    EnetAppUtils_freePktInfoQ(&gEnetLpbk.rxFreeQ);
    EnetAppUtils_freePktInfoQ(&gEnetLpbk.txFreePktInfoQ);

    EnetMem_deInit();
}

int32_t BoardDiag_macMode2PhyMii(emac_mode macMode,
                                EnetPhy_Mii *mii)
{
    int32_t status = ENET_SOK;

    switch (macMode)
    {
        case RMII:
            *mii = ENETPHY_MAC_MII_RMII;
            break;

        case RGMII:
            *mii = ENETPHY_MAC_MII_RGMII;
            break;

        case GMII:
            *mii = ENETPHY_MAC_MII_GMII;
            break;

        case SGMII:
            *mii = ENETPHY_MAC_MII_SGMII;
            break;

        case QSGMII:
        case QSGMII_SUB:
            *mii = ENETPHY_MAC_MII_QSGMII;
            break;

        case XFI:
            status = ENET_EFAIL;
            EnetAppUtils_print("XFI is not supported by EnetPhy driver\n");
            EnetAppUtils_assert(false);
            break;

        default:
            status = ENET_EFAIL;
            EnetAppUtils_print("Invalid MAC mode: %u\n", macMode);
            EnetAppUtils_assert(false);
            break;
    }

    return status;
}

/**
 * \brief   This function is used set layerType,sublayerType and variantType.
 *
 * \param   emac_mode                   macMode   mac mode
 *          EnetMacPort_Interface       *mii      MII mode
 *
 * \return  None
 *
 */
void BoardDiag_macMode2MacMii(emac_mode macMode,
                             EnetMacPort_Interface *mii)
{
    switch (macMode)
    {
        case RMII:
            mii->layerType    = ENET_MAC_LAYER_MII;
            mii->sublayerType = ENET_MAC_SUBLAYER_REDUCED;
            mii->variantType  = ENET_MAC_VARIANT_NONE;
            break;

        case RGMII:
            mii->layerType    = ENET_MAC_LAYER_GMII;
            mii->sublayerType = ENET_MAC_SUBLAYER_REDUCED;
            mii->variantType  = ENET_MAC_VARIANT_FORCED;
            break;

        case GMII:
            mii->layerType    = ENET_MAC_LAYER_GMII;
            mii->sublayerType = ENET_MAC_SUBLAYER_STANDARD;
            mii->variantType  = ENET_MAC_VARIANT_NONE;
            break;

        case SGMII:
            mii->layerType    = ENET_MAC_LAYER_GMII;
            mii->sublayerType = ENET_MAC_SUBLAYER_SERIAL;
            mii->variantType  = ENET_MAC_VARIANT_NONE;
            break;

        case QSGMII:
            mii->layerType    = ENET_MAC_LAYER_GMII;
            mii->sublayerType = ENET_MAC_SUBLAYER_QUAD_SERIAL_MAIN;
            mii->variantType  = ENET_MAC_VARIANT_NONE;
            break;

        case QSGMII_SUB:
            mii->layerType    = ENET_MAC_LAYER_GMII;
            mii->sublayerType = ENET_MAC_SUBLAYER_QUAD_SERIAL_SUB;
            mii->variantType  = ENET_MAC_VARIANT_NONE;
            break;

        case XFI:
            mii->layerType    = ENET_MAC_LAYER_XGMII;
            mii->sublayerType = ENET_MAC_SUBLAYER_SERIAL;
            mii->variantType  = ENET_MAC_VARIANT_NONE;
            break;

        default:
            EnetAppUtils_print("Invalid MAC mode: %u\n", macMode);
            EnetAppUtils_assert(false);
            break;
    }
}

void BoardDiag_getTestConfig(Enet_Type *enetType,
                            uint32_t *instId,
                            bool *testPhyLoopback,
                            bool *testLoopBackType,
                            Enet_MacPort *macPort,
                            emac_mode *macMode,
                            uint32_t *boardId)
{
    bool retry;
    int32_t choice;

#if defined(BUILD_MCU2_1)
    *enetType = ENET_CPSW_2G;
    *instId   = 1U;
    *boardId  = ENETBOARD_CPB_ID;
    *macPort  = ENET_MAC_PORT_1;
    *macMode  = RGMII;
#elif defined(BUILD_MCU1_0)
    *enetType = ENET_CPSW_2G;
    *instId   = 0U;
    *boardId  = ENETBOARD_CPB_ID;
    *macPort  = ENET_MAC_PORT_1;
    *macMode  = RGMII;
#endif

    do
    {
        EnetAppUtils_print("Select loopback type:\n");
        EnetAppUtils_print("0: Internal (MAC loopback)\n");
        EnetAppUtils_print("1: External (PHY loopback)\n");
        EnetAppUtils_print("2: External (Ext loopback)\n");
        
        
        choice = EnetAppUtils_getNum();

        switch (choice)
        {
            case 0:
                *testPhyLoopback = false;
                retry = false;
                break;
            case 1:
                *testPhyLoopback = true;
                *testLoopBackType = false;
                retry = false;
                break;
            case 2:
                *testPhyLoopback = true;
                *testLoopBackType = true;
                retry = false;
                break;
            default:
                EnetAppUtils_print("Wrong option, try again...\n\n");
                retry = true;
                break;
        }

    }
    while (retry);
}

/**
 * \brief  CPSW diagnostic test main function
 *
 *  This function performs board initializations and calls cpsw ethernet test
 *
 * \return  int
 *              0  - in case of success
 *             -1  - in case of failure
 *
 */
#ifndef SPI_BOOT_FRAMEWORK
int main(void)
{
    char p = 'y';
    Board_initCfg boardCfg;
    Board_STATUS status;

    boardCfg = BOARD_INIT_MODULE_CLOCK |
               BOARD_INIT_PINMUX_CONFIG |
               BOARD_INIT_UART_STDIO;

    status = Board_init(boardCfg);
    if(status != BOARD_SOK)
    {
        return -1;
    }

    UART_printf("\n************************************************\n");
    UART_printf  ("*                  CPSW ENET Test              *\n");
    UART_printf  ("************************************************\n");

    do{
        BoardDiag_getTestConfig(&gEnetLpbk.enetType,
                                &gEnetLpbk.instId,
                                &gEnetLpbk.testPhyLoopback,
                                &gEnetLpbk.testLoopBackType,
                                &gEnetLpbk.macPort,
                                &gEnetLpbk.macMode,
                                &gEnetLpbk.boardId);

        /* Run the loopback test */
        status = BoardDiag_enetLoopbackTest();
    
        UART_printf("Press 'y' to continue the test, 'b' to exit\n");
        UART_scanFmt("%c", &p);

    } while(p == 'y');

    if (status == ENET_SOK)
    {
        UART_printf("\n Enet Loopback test Passed\n");
    }
    else
    {
        UART_printf("\n Enet Loopback test Failed\n");
        return -1;
    }

    EnetBoard_deinit();
    
    return status;
}
#endif