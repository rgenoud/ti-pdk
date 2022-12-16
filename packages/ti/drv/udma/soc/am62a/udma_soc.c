/*
 *  Copyright (c) Texas Instruments Incorporated 2020
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
 *  \file udma_soc.c
 *
 *  \brief File containing the UDMA driver SOC related configuration functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/udma/src/udma_priv.h>

#ifdef QNX_OS
// #define QNX_UDMA_DEBUG_CSL_REGS
#endif

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

const Udma_MappedChRingAttributes gUdmaTxMappedChRingAttributes[CSL_DMSS_PKTDMA_NUM_TX_CHANS - CSL_DMSS_PKTDMA_TX_CHANS_UNMAPPED_CNT] =
{
    /* defaultRing, startFreeRing, numFreeRing */
    {19U, 20U, 7U}, /* Channel 16 - UDMA_MAPPED_TX_GROUP_CPSW Ch 0 */
    {27U, 28U, 7U}, /* Channel 17 - UDMA_MAPPED_TX_GROUP_CPSW Ch 1 */
    {35U, 36U, 7U}, /* Channel 18 - UDMA_MAPPED_TX_GROUP_CPSW Ch 2 */
    {43U, 44U, 7U}, /* Channel 19 - UDMA_MAPPED_TX_GROUP_CPSW Ch 3 */
    {51U, 52U, 7U}, /* Channel 20 - UDMA_MAPPED_TX_GROUP_CPSW Ch 4 */
    {59U, 60U, 7U}, /* Channel 21 - UDMA_MAPPED_TX_GROUP_CPSW Ch 5 */
    {67U, 68U, 7U}, /* Channel 22 - UDMA_MAPPED_TX_GROUP_CPSW Ch 6 */
    {75U, 76U, 7U}, /* Channel 23 - UDMA_MAPPED_TX_GROUP_CPSW Ch 7 */
    {83U, 84U, 7U}, /* Channel 24 - UDMA_MAPPED_TX_GROUP_SAUL Ch 0  */
    {91U, 92U, 7U}, /* Channel 25 - UDMA_MAPPED_TX_GROUP_SAUL Ch 1 */
};

const Udma_MappedChRingAttributes gUdmaRxMappedChRingAttributes[CSL_DMSS_PKTDMA_NUM_RX_CHANS - CSL_DMSS_PKTDMA_RX_CHANS_UNMAPPED_CNT] =
{
    /* defaultRing, startFreeRing, numFreeRing */
    /*RX Ring Offset of 112U added to the startRing */
    {118U, 119U, 15U}, /* Channel 16 - UDMA_MAPPED_RX_GROUP_CPSW Ch 0 */
    {134U, 136U, 6U}, /* Channel 17 - UDMA_MAPPED_RX_GROUP_SAUL Ch 0 */
    {135U, 136U, 6U}, /* Channel 18 - UDMA_MAPPED_RX_GROUP_SAUL Ch 1 */
    {142U, 144U, 6U}, /* Channel 19 - UDMA_MAPPED_RX_GROUP_SAUL Ch 2 */
    {143U, 144U, 6U}, /* Channel 20 - UDMA_MAPPED_RX_GROUP_SAUL Ch 3 */
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */


void Udma_initDrvHandle(Udma_DrvHandle drvHandle)
{
    uint32_t                 instId;
    CSL_BcdmaCfg    		 *pBcdmaRegs; 
    CSL_PktdmaCfg 	   	     *pPktdmaRegs; 
    CSL_LcdmaRingaccCfg      *pLcdmaRaRegs; 
    CSL_IntaggrCfg   	     *pIaRegs;

    instId = drvHandle->initPrms.instId;
    /*
     * BCDMA/PKTDMA config init
     */
    /* Init the config structure - one time step */
    if(UDMA_INST_ID_BCDMA_0 == instId)
    {
    	drvHandle->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    	pBcdmaRegs = &drvHandle->bcdmaRegs;
#ifndef QNX_OS
        pBcdmaRegs->pGenCfgRegs     = ((CSL_bcdma_gcfgRegs *) CSL_DMASS0_BCDMA_GCFG_BASE);
        pBcdmaRegs->pBcChanCfgRegs  = ((CSL_bcdma_bccfgRegs *) CSL_DMASS0_BCDMA_BCHAN_BASE);
        pBcdmaRegs->pTxChanCfgRegs  = ((CSL_bcdma_txccfgRegs *) CSL_DMASS0_BCDMA_TCHAN_BASE);
        pBcdmaRegs->pRxChanCfgRegs  = ((CSL_bcdma_rxccfgRegs *) CSL_DMASS0_BCDMA_RCHAN_BASE);
        pBcdmaRegs->pBcChanRtRegs   = ((CSL_bcdma_bcrtRegs *) CSL_DMASS0_BCDMA_BCHANRT_BASE);
        pBcdmaRegs->pTxChanRtRegs   = ((CSL_bcdma_txcrtRegs *) CSL_DMASS0_BCDMA_TCHANRT_BASE);
        pBcdmaRegs->pRxChanRtRegs   = ((CSL_bcdma_rxcrtRegs *) CSL_DMASS0_BCDMA_RCHANRT_BASE);
#else
        pBcdmaRegs->pGenCfgRegs     = ((CSL_bcdma_gcfgRegs *) mmap_device_memory(0,
              CSL_DMASS0_BCDMA_GCFG_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS0_BCDMA_GCFG_BASE));
        pBcdmaRegs->pBcChanCfgRegs  = ((CSL_bcdma_bccfgRegs *) mmap_device_memory(0,
              CSL_DMASS0_BCDMA_BCHAN_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS0_BCDMA_BCHAN_BASE));
        pBcdmaRegs->pTxChanCfgRegs  = ((CSL_bcdma_txccfgRegs *) mmap_device_memory(0,
              CSL_DMASS0_BCDMA_TCHAN_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS0_BCDMA_TCHAN_BASE));
        pBcdmaRegs->pRxChanCfgRegs  = ((CSL_bcdma_rxccfgRegs *) mmap_device_memory(0,
              CSL_DMASS0_BCDMA_RCHAN_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS0_BCDMA_RCHAN_BASE));
        pBcdmaRegs->pBcChanRtRegs   = ((CSL_bcdma_bcrtRegs *) mmap_device_memory(0,
              CSL_DMASS0_BCDMA_BCHANRT_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS0_BCDMA_BCHANRT_BASE));
        pBcdmaRegs->pTxChanRtRegs   = ((CSL_bcdma_txcrtRegs *) mmap_device_memory(0,
              CSL_DMASS0_BCDMA_TCHANRT_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS0_BCDMA_TCHANRT_BASE));
        pBcdmaRegs->pRxChanRtRegs   = ((CSL_bcdma_rxcrtRegs *) mmap_device_memory(0,
              CSL_DMASS0_BCDMA_RCHANRT_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS0_BCDMA_RCHANRT_BASE));
#endif
        drvHandle->trigGemOffset    = CSL_DMSS_GEM_BCDMA_TRIGGER_OFFSET;
        /* Fill other SOC specific parameters by reading from UDMA config
	     * registers */
        CSL_bcdmaGetCfg(pBcdmaRegs);
	    
        pPktdmaRegs = &drvHandle->pktdmaRegs;
        memset(pPktdmaRegs, 0, sizeof(*pPktdmaRegs));
    }
    else if(UDMA_INST_ID_CSI_BCDMA_0 == instId)
    {
    	drvHandle->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    	pBcdmaRegs = &drvHandle->bcdmaRegs;
#ifndef QNX_OS
        pBcdmaRegs->pGenCfgRegs     = ((CSL_bcdma_gcfgRegs *) CSL_DMASS1_BCDMA_GCFG_BASE);
        pBcdmaRegs->pRxChanCfgRegs  = ((CSL_bcdma_rxccfgRegs *) CSL_DMASS1_BCDMA_RCHAN_BASE);
        pBcdmaRegs->pRxChanRtRegs   = ((CSL_bcdma_rxcrtRegs *) CSL_DMASS1_BCDMA_RCHANRT_BASE);
#else
        pBcdmaRegs->pGenCfgRegs     = ((CSL_bcdma_gcfgRegs *) mmap_device_memory(0,
              CSL_DMASS1_BCDMA_GCFG_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS1_BCDMA_GCFG_BASE));
        pBcdmaRegs->pRxChanCfgRegs  = ((CSL_bcdma_rxccfgRegs *) mmap_device_memory(0,
              CSL_DMASS1_BCDMA_RCHAN_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS1_BCDMA_RCHAN_BASE));
        pBcdmaRegs->pRxChanRtRegs   = ((CSL_bcdma_rxcrtRegs *) mmap_device_memory(0,
              CSL_DMASS1_BCDMA_RCHANRT_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS1_BCDMA_RCHANRT_BASE));
#endif
        drvHandle->trigGemOffset    = CSL_DMSS_GEM_BCDMA_TRIGGER_OFFSET;
        
        /* Enable power for the csirx module before accessing the dma registers*/
        Sciclient_pmSetModuleState(TISCI_DEV_CSI_RX_IF0,
                                   TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                   TISCI_MSG_FLAG_AOP,
                                   SCICLIENT_SERVICE_WAIT_FOREVER);
        Sciclient_pmSetModuleState(TISCI_DEV_DPHY_RX0,
                                   TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                   TISCI_MSG_FLAG_AOP,
                                   SCICLIENT_SERVICE_WAIT_FOREVER);
        /* Fill other SOC specific parameters by reading from UDMA config
	     * registers */
        CSL_bcdmaGetCfg(pBcdmaRegs);
	    
        pPktdmaRegs = &drvHandle->pktdmaRegs;
        memset(pPktdmaRegs, 0, sizeof(*pPktdmaRegs));
    }
    else 
    {
    	drvHandle->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    	pPktdmaRegs = &drvHandle->pktdmaRegs;
#ifndef QNX_OS
        pPktdmaRegs->pGenCfgRegs     = ((CSL_pktdma_gcfgRegs *) CSL_DMASS0_PKTDMA_GCFG_BASE);
        pPktdmaRegs->pRxFlowCfgRegs  = ((CSL_pktdma_rxfcfgRegs *) CSL_DMASS0_PKTDMA_RFLOW_BASE);
        pPktdmaRegs->pTxChanCfgRegs  = ((CSL_pktdma_txccfgRegs *) CSL_DMASS0_PKTDMA_TCHAN_BASE);
        pPktdmaRegs->pRxChanCfgRegs  = ((CSL_pktdma_rxccfgRegs *) CSL_DMASS0_PKTDMA_RCHAN_BASE);
        pPktdmaRegs->pTxChanRtRegs   = ((CSL_pktdma_txcrtRegs *) CSL_DMASS0_PKTDMA_TCHANRT_BASE);
        pPktdmaRegs->pRxChanRtRegs   = ((CSL_pktdma_rxcrtRegs *) CSL_DMASS0_PKTDMA_RCHANRT_BASE);
#else
        pPktdmaRegs->pGenCfgRegs     = ((CSL_pktdma_gcfgRegs *) mmap_device_memory(0,
              CSL_DMASS0_PKTDMA_GCFG_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS0_PKTDMA_GCFG_BASE));
        pPktdmaRegs->pRxFlowCfgRegs  = ((CSL_pktdma_rxfcfgRegs *) mmap_device_memory(0,
              CSL_DMASS0_PKTDMA_RFLOW_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS0_PKTDMA_RFLOW_BASE));
        pPktdmaRegs->pTxChanCfgRegs  = ((CSL_pktdma_txccfgRegs *) mmap_device_memory(0,
              CSL_DMASS0_PKTDMA_TCHAN_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS0_PKTDMA_TCHAN_BASE));
        pPktdmaRegs->pRxChanCfgRegs  = ((CSL_pktdma_rxccfgRegs *) mmap_device_memory(0,
              CSL_DMASS0_PKTDMA_RCHAN_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS0_PKTDMA_RCHAN_BASE));
        pPktdmaRegs->pTxChanRtRegs   = ((CSL_pktdma_txcrtRegs *) mmap_device_memory(0,
              CSL_DMASS0_PKTDMA_TCHANRT_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS0_PKTDMA_TCHANRT_BASE));
        pPktdmaRegs->pRxChanRtRegs   = ((CSL_pktdma_rxcrtRegs *) mmap_device_memory(0,
              CSL_DMASS0_PKTDMA_RCHANRT_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS0_PKTDMA_RCHANRT_BASE));
#endif

        drvHandle->trigGemOffset     = 0; 
        /* Fill other SOC specific parameters by reading from UDMA config
	     * registers */
        CSL_pktdmaGetCfg(pPktdmaRegs);
        
        pBcdmaRegs = &drvHandle->bcdmaRegs;
        memset(pBcdmaRegs, 0, sizeof(*pBcdmaRegs));
    }
    
    /*
     * RA config init
     */
    drvHandle->raType = UDMA_RA_TYPE_LCDMA;
    pLcdmaRaRegs = &drvHandle->lcdmaRaRegs;
    if(UDMA_INST_ID_BCDMA_0 == instId)
    {
#ifndef QNX_OS
	    pLcdmaRaRegs->pRingCfgRegs   = (CSL_lcdma_ringacc_ring_cfgRegs *) CSL_DMASS0_BCDMA_RING_BASE; 
	    pLcdmaRaRegs->pRingRtRegs    = (CSL_lcdma_ringacc_ringrtRegs *) CSL_DMASS0_BCDMA_RINGRT_BASE;
	    pLcdmaRaRegs->pCredRegs      = (CSL_lcdma_ringacc_credRegs *) CSL_DMASS0_BCDMA_CRED_BASE; 
	    pLcdmaRaRegs->maxRings       = CSL_DMSS_BCDMA_NUM_BC_CHANS + CSL_DMSS_BCDMA_NUM_TX_CHANS + CSL_DMSS_BCDMA_NUM_RX_CHANS;	
#else
	    pLcdmaRaRegs->pRingCfgRegs   = (CSL_lcdma_ringacc_ring_cfgRegs *) mmap_device_memory(0,
              CSL_DMASS0_BCDMA_RING_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS0_BCDMA_RING_BASE);
	    pLcdmaRaRegs->pRingRtRegs    = (CSL_lcdma_ringacc_ringrtRegs *) mmap_device_memory(0,
              CSL_DMASS0_BCDMA_RINGRT_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS0_BCDMA_RINGRT_BASE);
	    pLcdmaRaRegs->pCredRegs      = (CSL_lcdma_ringacc_credRegs *) mmap_device_memory(0,
              CSL_DMASS0_BCDMA_CRED_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS0_BCDMA_CRED_BASE);
	    pLcdmaRaRegs->maxRings       = CSL_DMSS_BCDMA_NUM_BC_CHANS + CSL_DMSS_BCDMA_NUM_TX_CHANS + CSL_DMSS_BCDMA_NUM_RX_CHANS;	
#endif
    }
    else if(UDMA_INST_ID_CSI_BCDMA_0 == instId)
    {
#ifndef QNX_OS
	    pLcdmaRaRegs->pRingCfgRegs   = (CSL_lcdma_ringacc_ring_cfgRegs *) CSL_DMASS1_BCDMA_RING_BASE; 
	    pLcdmaRaRegs->pRingRtRegs    = (CSL_lcdma_ringacc_ringrtRegs *) CSL_DMASS1_BCDMA_RINGRT_BASE;
	    pLcdmaRaRegs->pCredRegs      = (CSL_lcdma_ringacc_credRegs *) CSL_DMASS1_BCDMA_CRED_BASE; 
	    pLcdmaRaRegs->maxRings       = CSL_DMSS_BCDMA_NUM_RX_HC_CHANS;	
#else
	    pLcdmaRaRegs->pRingCfgRegs   = (CSL_lcdma_ringacc_ring_cfgRegs *) mmap_device_memory(0,
              CSL_DMASS1_BCDMA_RING_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS1_BCDMA_RING_BASE);
	    pLcdmaRaRegs->pRingRtRegs    = (CSL_lcdma_ringacc_ringrtRegs *) mmap_device_memory(0,
              CSL_DMASS1_BCDMA_RINGRT_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS1_BCDMA_RINGRT_BASE);
	    pLcdmaRaRegs->pCredRegs      = (CSL_lcdma_ringacc_credRegs *) mmap_device_memory(0,
              CSL_DMASS1_BCDMA_CRED_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS1_BCDMA_CRED_BASE);
	    pLcdmaRaRegs->maxRings       = CSL_DMSS_BCDMA_NUM_RX_HC_CHANS;	
#endif
    }
    else
    {
#ifndef QNX_OS
    	pLcdmaRaRegs->pRingCfgRegs   = (CSL_lcdma_ringacc_ring_cfgRegs *) CSL_DMASS0_PKTDMA_RING_BASE; 
        pLcdmaRaRegs->pRingRtRegs    = (CSL_lcdma_ringacc_ringrtRegs *) CSL_DMASS0_PKTDMA_RINGRT_BASE;
        pLcdmaRaRegs->pCredRegs      = (CSL_lcdma_ringacc_credRegs *) CSL_DMASS0_PKTDMA_CRED_BASE; 
        pLcdmaRaRegs->maxRings       = CSL_DMSS_PKTDMA_NUM_RX_FLOWS + CSL_DMSS_PKTDMA_NUM_TX_FLOWS;	
#else
    	pLcdmaRaRegs->pRingCfgRegs   = (CSL_lcdma_ringacc_ring_cfgRegs *) mmap_device_memory(0,
              CSL_DMASS0_PKTDMA_RING_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS0_PKTDMA_RING_BASE);
        pLcdmaRaRegs->pRingRtRegs    = (CSL_lcdma_ringacc_ringrtRegs *) mmap_device_memory(0,
                     CSL_DMASS0_PKTDMA_RINGRT_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS0_PKTDMA_RINGRT_BASE);
        pLcdmaRaRegs->pCredRegs      = (CSL_lcdma_ringacc_credRegs *) mmap_device_memory(0,
              CSL_DMASS0_PKTDMA_CRED_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS0_PKTDMA_CRED_BASE);
        pLcdmaRaRegs->maxRings       = CSL_DMSS_PKTDMA_NUM_RX_FLOWS + CSL_DMSS_PKTDMA_NUM_TX_FLOWS;	
#endif
    }
    drvHandle->ringDequeueRaw           = &Udma_ringDequeueRawLcdma;
    drvHandle->ringQueueRaw             = &Udma_ringQueueRawLcdma;
    drvHandle->ringFlushRaw             = &Udma_ringFlushRawLcdma;
    drvHandle->ringGetElementCnt        = &Udma_ringGetElementCntLcdma;
    drvHandle->ringGetMemPtr            = &Udma_ringGetMemPtrLcdma;
    drvHandle->ringGetMode              = &Udma_ringGetModeLcdma;
    drvHandle->ringGetForwardRingOcc    = &Udma_ringGetForwardRingOccLcdma;
    drvHandle->ringGetReverseRingOcc    = &Udma_ringGetReverseRingOccLcdma;
    drvHandle->ringGetWrIdx             = &Udma_ringGetWrIdxLcdma;
    drvHandle->ringGetRdIdx             = &Udma_ringGetRdIdxLcdma;
    drvHandle->ringPrime                = &Udma_ringPrimeLcdma;
    drvHandle->ringPrimeRead            = &Udma_ringPrimeReadLcdma;
    drvHandle->ringSetDoorBell          = &Udma_ringSetDoorBellLcdma;
    drvHandle->ringSetCfg               = &Udma_ringSetCfgLcdma;
    drvHandle->ringHandleClearRegs      = &Udma_ringHandleClearRegsLcdma;

    /* IA config init */
    pIaRegs = &drvHandle->iaRegs;
    if(UDMA_INST_ID_CSI_BCDMA_0 != instId)
    {   
#ifndef QNX_OS
        pIaRegs->pCfgRegs       = (CSL_intaggr_cfgRegs *) CSL_DMASS0_INTAGGR_CFG_BASE;
        pIaRegs->pImapRegs      = (CSL_intaggr_imapRegs *) CSL_DMASS0_INTAGGR_IMAP_BASE;
        pIaRegs->pIntrRegs      = (CSL_intaggr_intrRegs *) CSL_DMASS0_INTAGGR_INTR_BASE;
        pIaRegs->pL2gRegs       = (CSL_intaggr_l2gRegs *) CSL_DMASS0_INTAGGR_L2G_BASE;
        pIaRegs->pMcastRegs     = (CSL_intaggr_mcastRegs *) CSL_DMASS0_INTAGGR_MCAST_BASE;
        pIaRegs->pGcntCfgRegs   = (CSL_intaggr_gcntcfgRegs *) CSL_DMASS0_INTAGGR_GCNTCFG_BASE;
        pIaRegs->pGcntRtiRegs   = (CSL_intaggr_gcntrtiRegs *) CSL_DMASS0_INTAGGR_GCNTRTI_BASE;
#else
        pIaRegs->pCfgRegs       = (CSL_intaggr_cfgRegs *) mmap_device_memory(0,
                CSL_DMASS0_INTAGGR_CFG_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS0_INTAGGR_CFG_BASE);
        pIaRegs->pImapRegs      = (CSL_intaggr_imapRegs *) mmap_device_memory(0,
                CSL_DMASS0_INTAGGR_IMAP_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS0_INTAGGR_IMAP_BASE);
        pIaRegs->pIntrRegs      = (CSL_intaggr_intrRegs *) mmap_device_memory(0,
                CSL_DMASS0_INTAGGR_INTR_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS0_INTAGGR_INTR_BASE);
        pIaRegs->pL2gRegs       = (CSL_intaggr_l2gRegs *) mmap_device_memory(0,
                CSL_DMASS0_INTAGGR_L2G_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS0_INTAGGR_L2G_BASE);
        pIaRegs->pMcastRegs     = (CSL_intaggr_mcastRegs *) mmap_device_memory(0,
                CSL_DMASS0_INTAGGR_MCAST_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS0_INTAGGR_MCAST_BASE);
        pIaRegs->pGcntCfgRegs   = (CSL_intaggr_gcntcfgRegs *) mmap_device_memory(0,
                CSL_DMASS0_INTAGGR_GCNTCFG_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS0_INTAGGR_GCNTCFG_BASE);
        pIaRegs->pGcntRtiRegs   = (CSL_intaggr_gcntrtiRegs *) mmap_device_memory(0,
                CSL_DMASS0_INTAGGR_GCNTRTI_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS0_INTAGGR_GCNTRTI_BASE);
#endif
        drvHandle->devIdIa      = TISCI_DEV_DMASS0_INTAGGR_0;
    } else {
#ifndef QNX_OS
        pIaRegs->pCfgRegs       = (CSL_intaggr_cfgRegs *) CSL_DMASS1_INTAGGR_CFG_BASE;
        pIaRegs->pImapRegs      = (CSL_intaggr_imapRegs *) CSL_DMASS1_INTAGGR_IMAP_BASE;
        pIaRegs->pIntrRegs      = (CSL_intaggr_intrRegs *) CSL_DMASS1_INTAGGR_INTR_BASE;
        //pIaRegs->pL2gRegs       = (CSL_intaggr_l2gRegs *) CSL_DMASS0_INTAGGR_L2G_BASE;
        pIaRegs->pMcastRegs     = (CSL_intaggr_mcastRegs *) CSL_DMASS1_INTAGGR_MCAST_BASE;
        pIaRegs->pGcntCfgRegs   = (CSL_intaggr_gcntcfgRegs *) CSL_DMASS1_INTAGGR_GCNTCFG_BASE;
        pIaRegs->pGcntRtiRegs   = (CSL_intaggr_gcntrtiRegs *) CSL_DMASS1_INTAGGR_GCNTRTI_BASE;
#else
        pIaRegs->pCfgRegs       = (CSL_intaggr_cfgRegs *) mmap_device_memory(0,
                CSL_DMASS1_INTAGGR_CFG_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS1_INTAGGR_CFG_BASE);
        pIaRegs->pImapRegs      = (CSL_intaggr_imapRegs *) mmap_device_memory(0,
                CSL_DMASS1_INTAGGR_IMAP_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS1_INTAGGR_IMAP_BASE);
        pIaRegs->pIntrRegs      = (CSL_intaggr_intrRegs *) mmap_device_memory(0,
                CSL_DMASS1_INTAGGR_INTR_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS1_INTAGGR_INTR_BASE);
        /*pIaRegs->pL2gRegs       = (CSL_intaggr_l2gRegs *) mmap_device_memory(0,
                CSL_DMASS0_INTAGGR_L2G_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS0_INTAGGR_L2G_BASE);*/
        pIaRegs->pMcastRegs     = (CSL_intaggr_mcastRegs *) mmap_device_memory(0,
                CSL_DMASS1_INTAGGR_MCAST_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS1_INTAGGR_MCAST_BASE);
        pIaRegs->pGcntCfgRegs   = (CSL_intaggr_gcntcfgRegs *) mmap_device_memory(0,
                CSL_DMASS1_INTAGGR_GCNTCFG_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS1_INTAGGR_GCNTCFG_BASE);
        pIaRegs->pGcntRtiRegs   = (CSL_intaggr_gcntrtiRegs *) mmap_device_memory(0,
                CSL_DMASS1_INTAGGR_GCNTRTI_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_DMASS1_INTAGGR_GCNTRTI_BASE);
#endif
        drvHandle->devIdIa      = TISCI_DEV_DMASS1_INTAGGR_0;
    }
    CSL_intaggrGetCfg(pIaRegs);

    drvHandle->iaGemOffset  = CSL_DMSS_GEM_INTA0_SEVI_OFFSET;
    drvHandle->devIdCore    = Udma_getCoreSciDevId();
    
    /* Init other variables */
    if(UDMA_INST_ID_BCDMA_0 == instId)
    {
        drvHandle->txChOffset           = pBcdmaRegs->bcChanCnt;
	    drvHandle->rxChOffset   		= drvHandle->txChOffset + pBcdmaRegs->splitTxChanCnt;
       /* The srcIdx passed to Sciclient_rmIrqset API for configuring DMA Completion/Ring events, 
        * will be ringNum + the corresponding following offset. 
        * So setting the offset as TISCI Start Idx - corresponding ringNum Offset (if any) */
        drvHandle->blkCopyRingIrqOffset = TISCI_BCDMA0_BC_RC_OES_IRQ_SRC_IDX_START; 
        drvHandle->txRingIrqOffset      = TISCI_BCDMA0_TX_RC_OES_IRQ_SRC_IDX_START - drvHandle->txChOffset;
        drvHandle->rxRingIrqOffset      = TISCI_BCDMA0_RX_RC_OES_IRQ_SRC_IDX_START - drvHandle->rxChOffset;
        drvHandle->udmapSrcThreadOffset = CSL_PSILCFG_DMSS_BCDMA_STRM_PSILS_THREAD_OFFSET; 
        drvHandle->udmapDestThreadOffset= CSL_PSILCFG_DMSS_BCDMA_STRM_PSILD_THREAD_OFFSET;
        drvHandle->maxRings             = CSL_DMSS_BCDMA_NUM_BC_CHANS + CSL_DMSS_BCDMA_NUM_TX_CHANS + CSL_DMSS_BCDMA_NUM_RX_CHANS;
        drvHandle->devIdRing            = TISCI_DEV_DMASS0_BCDMA_0;
	    drvHandle->devIdUdma        	= TISCI_DEV_DMASS0_BCDMA_0;
       /* The srcIdx passed to Sciclient_rmIrqset API for configuring TR events, 
        * will be chNum + the corresponding following offset. 
        * So setting the offset as TISCI Start Idx - corresponding chNum Offset (if any) */
        drvHandle->srcIdTrIrq           = drvHandle->devIdIa;
        drvHandle->blkCopyTrIrqOffset   = TISCI_BCDMA0_BC_DC_OES_IRQ_SRC_IDX_START; 
        drvHandle->txTrIrqOffset        = TISCI_BCDMA0_TX_DC_OES_IRQ_SRC_IDX_START;
        drvHandle->rxTrIrqOffset        = TISCI_BCDMA0_RX_DC_OES_IRQ_SRC_IDX_START;
        drvHandle->devIdPsil            = TISCI_DEV_DMASS0;
    }
    else if (UDMA_INST_ID_CSI_BCDMA_0 == instId)
    {
        drvHandle->txChOffset           = pBcdmaRegs->bcChanCnt;
	    drvHandle->rxChOffset   		= drvHandle->txChOffset + pBcdmaRegs->splitTxChanCnt;
       /* The srcIdx passed to Sciclient_rmIrqset API for configuring DMA Completion/Ring events, 
        * will be ringNum + the corresponding following offset. 
        * So setting the offset as TISCI Start Idx - corresponding ringNum Offset (if any) */
        drvHandle->blkCopyRingIrqOffset = TISCI_BCDMA0_BC_RC_OES_IRQ_SRC_IDX_START; 
        drvHandle->txRingIrqOffset      = TISCI_BCDMA0_TX_RC_OES_IRQ_SRC_IDX_START - drvHandle->txChOffset;
        drvHandle->rxRingIrqOffset      = TISCI_BCDMA1_RX_RC_OES_IRQ_SRC_IDX_START - drvHandle->rxChOffset;
        drvHandle->udmapSrcThreadOffset = CSL_PSILCFG_DMSS_CSI_BCDMA_STRM_PSILS_THREAD_OFFSET; 
        drvHandle->udmapDestThreadOffset= CSL_PSILCFG_DMSS_CSI_BCDMA_STRM_PSILD_THREAD_OFFSET;
        drvHandle->maxRings             = CSL_DMSS_BCDMA_NUM_TX_HC_CHANS + CSL_DMSS_BCDMA_NUM_RX_HC_CHANS;
        drvHandle->devIdRing            = TISCI_DEV_DMASS1_BCDMA_0;
	    drvHandle->devIdUdma        	= TISCI_DEV_DMASS1_BCDMA_0;
       /* The srcIdx passed to Sciclient_rmIrqset API for configuring TR events, 
        * will be chNum + the corresponding following offset. 
        * So setting the offset as TISCI Start Idx - corresponding chNum Offset (if any) */
        drvHandle->srcIdTrIrq           = drvHandle->devIdIa;
        drvHandle->blkCopyTrIrqOffset   = TISCI_BCDMA0_BC_DC_OES_IRQ_SRC_IDX_START; 
        drvHandle->txTrIrqOffset        = TISCI_BCDMA0_TX_DC_OES_IRQ_SRC_IDX_START;
        drvHandle->rxTrIrqOffset        = TISCI_BCDMA0_RX_DC_OES_IRQ_SRC_IDX_START;
        drvHandle->devIdPsil            = TISCI_DEV_DMASS1;
    }
    else {
        drvHandle->txChOffset           = CSL_DMSS_PKTDMA_TX_FLOWS_UNMAPPED_START; 
	    drvHandle->rxChOffset   		= CSL_DMSS_PKTDMA_RX_FLOWS_UNMAPPED_START;
        drvHandle->blkCopyRingIrqOffset = 0U; /* Not used for PktDMA Instance */ 
        drvHandle->txRingIrqOffset      = TISCI_PKTDMA0_TX_FLOW_OES_IRQ_SRC_IDX_START - drvHandle->txChOffset; 
        drvHandle->rxRingIrqOffset      = TISCI_PKTDMA0_RX_FLOW_OES_IRQ_SRC_IDX_START - drvHandle->rxChOffset; 
        drvHandle->udmapSrcThreadOffset = CSL_PSILCFG_DMSS_PKTDMA_STRM_PSILS_THREAD_OFFSET; 
        drvHandle->udmapDestThreadOffset= CSL_PSILCFG_DMSS_PKTDMA_STRM_PSILD_THREAD_OFFSET;
        drvHandle->maxRings             = CSL_DMSS_PKTDMA_NUM_RX_FLOWS + CSL_DMSS_PKTDMA_NUM_TX_FLOWS;
        drvHandle->devIdRing            = TISCI_DEV_DMASS0_PKTDMA_0;
	    drvHandle->devIdUdma       		= TISCI_DEV_DMASS0_PKTDMA_0;
       /* TR Event is not supported for PKTMDA */
        drvHandle->srcIdTrIrq           = 0U;
        drvHandle->blkCopyTrIrqOffset   = 0U; 
        drvHandle->txTrIrqOffset        = 0U;
        drvHandle->rxTrIrqOffset        = 0U;
        drvHandle->devIdPsil            = TISCI_DEV_DMASS0;
    }
    drvHandle->maxProxy     = 0U; 
    drvHandle->maxRingMon   = CSL_DMSS_RINGACC_NUM_MONITORS;
    drvHandle->extChOffset  = 0U;
    drvHandle->srcIdRingIrq = drvHandle->devIdIa;

    return;
}

uint32_t Udma_getGlobalEventOffset(void)
{
    uint32_t globalEventOffset = 0U;

    globalEventOffset = CSL_DMSS_GEM_INTA0_SEVI_OFFSET;

    return (globalEventOffset);
}

uint32_t Udma_getCoreId(void)
{
    uint32_t coreId;

#if defined (BUILD_MPU1_0)
    coreId = UDMA_CORE_ID_MPU1_0;
#endif
#if defined (BUILD_MCU1_0)
    coreId = UDMA_CORE_ID_MCU1_0;
#endif
#if defined (BUILD_M4F_0)
    coreId = UDMA_CORE_ID_M4F_0;
#endif

    return (coreId);
}

uint16_t Udma_getCoreSciDevId(void)
{
    uint16_t coreSciDevId;

#if defined (BUILD_MCU1_0)
    coreSciDevId    = TISCI_DEV_R5FSS0_CORE0;
#endif

#if defined (BUILD_MPU1_0)
    coreSciDevId    = TISCI_DEV_GICSS0;
#endif

#if defined (BUILD_M4F_0)
    coreSciDevId    = TISCI_DEV_MCU_M4FSS0_CORE0;
#endif

    return (coreSciDevId);
}

uint32_t Udma_isCacheCoherent(void)
{
    uint32_t isCacheCoherent;

    isCacheCoherent = FALSE;

    return (isCacheCoherent);
}

int32_t Udma_getMappedChRingAttributes(Udma_DrvHandle drvHandle, uint32_t mappedGrp, uint32_t chNum, Udma_MappedChRingAttributes *chAttr)
{
    const Udma_MappedChRingAttributes  *mappedChRingAttributes;
    uint32_t index = 0U;
    int32_t retVal = UDMA_SOK;

    if(mappedGrp < UDMA_NUM_MAPPED_TX_GROUP) /* Mapped TX Channel */
    {
        /* Check if the channel no. is out of range of mapped channel idx */ 
        if((chNum < CSL_DMSS_PKTDMA_TX_CHANS_CPSW_START) ||
           (chNum >= CSL_DMSS_PKTDMA_NUM_TX_CHANS))
        {
            retVal = UDMA_EINVALID_PARAMS;
            Udma_printf(drvHandle, "[Error] Incorrect Mapped Channel number!!!\n");
        }
        if(UDMA_SOK == retVal)
        {
            /* Calculate index by subtracting the start idx of mapped channels 
            * (For AM64x, mapped channel starts with CPSW channel.) */
            index = chNum - CSL_DMSS_PKTDMA_TX_CHANS_CPSW_START;
            /* Check that, index is less than total no.of mapped TX channels */
            Udma_assert(drvHandle, index < (CSL_DMSS_PKTDMA_NUM_TX_CHANS - CSL_DMSS_PKTDMA_TX_CHANS_UNMAPPED_CNT));
            mappedChRingAttributes = &gUdmaTxMappedChRingAttributes[index];
        }
    }
    else /* Mapped RX Channel */
    {
        /* Check if the channel no. is out of range of mapped channel idx */ 
        if((chNum < CSL_DMSS_PKTDMA_RX_CHANS_CPSW_START) ||
           (chNum >= CSL_DMSS_PKTDMA_NUM_RX_CHANS))
        {
            retVal = UDMA_EINVALID_PARAMS;
            Udma_printf(drvHandle, "[Error] Incorrect Mapped Channel number!!!\n");
        }
        if(UDMA_SOK == retVal)
        {
            /* Calculate index by subtracting the start idx of mapped channels 
            * (For AM64x, mapped channel starts with CPSW channel.) */
            index = chNum - CSL_DMSS_PKTDMA_RX_CHANS_CPSW_START;
            /* Check that, index is less than total no.of mapped RX channels */
            Udma_assert(drvHandle, index < (CSL_DMSS_PKTDMA_NUM_RX_CHANS - CSL_DMSS_PKTDMA_RX_CHANS_UNMAPPED_CNT));
            mappedChRingAttributes = &gUdmaRxMappedChRingAttributes[index];
        }
    }
    if(UDMA_SOK == retVal)
    {
        (void) memcpy(chAttr, mappedChRingAttributes, sizeof (Udma_MappedChRingAttributes));
    }

    return(retVal);
}
