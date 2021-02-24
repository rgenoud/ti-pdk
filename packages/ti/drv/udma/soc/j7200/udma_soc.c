/*
 *  Copyright (c) Texas Instruments Incorporated 2018
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

#define UDMA_MCU_NAVSS0_UDMASS_UDMAP0_CFG_GCFG_BASE             (CSL_MCU_NAVSS0_UDMASS_UDMAP0_CFG_GCFG_BASE)
#define UDMA_MCU_NAVSS0_UDMASS_UDMAP0_CFG_RFLOW_BASE            (CSL_MCU_NAVSS0_UDMASS_UDMAP0_CFG_RFLOW_BASE)
#define UDMA_MCU_NAVSS0_UDMASS_UDMAP0_TCHAN_BASE                (CSL_MCU_NAVSS0_UDMASS_UDMAP0_TCHAN_BASE)
#define UDMA_MCU_NAVSS0_UDMASS_UDMAP0_RCHAN_BASE                (CSL_MCU_NAVSS0_UDMASS_UDMAP0_RCHAN_BASE)
#define UDMA_MCU_NAVSS0_UDMASS_UDMAP_TCHANRT_BASE               (CSL_MCU_NAVSS0_UDMASS_UDMAP_TCHANRT_BASE)
#define UDMA_MCU_NAVSS0_UDMASS_UDMAP_RCHANRT_BASE               (CSL_MCU_NAVSS0_UDMASS_UDMAP_RCHANRT_BASE)

#define UDMA_NAVSS0_UDMASS_UDMAP0_CFG_BASE                      (CSL_NAVSS0_UDMASS_UDMAP0_CFG_BASE)
#define UDMA_NAVSS0_UDMASS_UDMAP0_CFG_RFLOW_BASE                (CSL_NAVSS0_UDMASS_UDMAP0_CFG_RFLOW_BASE)
#define UDMA_NAVSS0_UDMASS_UDMAP0_CFG_TCHAN_BASE                (CSL_NAVSS0_UDMASS_UDMAP0_CFG_TCHAN_BASE)
#define UDMA_NAVSS0_UDMASS_UDMAP0_CFG_RCHAN_BASE                (CSL_NAVSS0_UDMASS_UDMAP0_CFG_RCHAN_BASE)
#define UDMA_NAVSS0_UDMASS_UDMAP0_CFG_TCHANRT_BASE              (CSL_NAVSS0_UDMASS_UDMAP0_CFG_TCHANRT_BASE)
#define UDMA_NAVSS0_UDMASS_UDMAP0_CFG_RCHANRT_BASE              (CSL_NAVSS0_UDMASS_UDMAP0_CFG_RCHANRT_BASE)

#define UDMA_MCU_NAVSS0_UDMASS_RINGACC0_CFG_GCFG_BASE           (CSL_MCU_NAVSS0_UDMASS_RINGACC0_CFG_GCFG_BASE)
#define UDMA_MCU_NAVSS0_UDMASS_RINGACC0_CFG_BASE                (CSL_MCU_NAVSS0_UDMASS_RINGACC0_CFG_BASE)
#define UDMA_MCU_NAVSS0_UDMASS_RINGACC0_CFG_RT_BASE             (CSL_MCU_NAVSS0_UDMASS_RINGACC0_CFG_RT_BASE)
#define UDMA_MCU_NAVSS0_UDMASS_RINGACC0_CFG_MON_BASE            (CSL_MCU_NAVSS0_UDMASS_RINGACC0_CFG_MON_BASE)
#define UDMA_MCU_NAVSS0_UDMASS_RINGACC0_FIFOS_BASE              (CSL_MCU_NAVSS0_UDMASS_RINGACC0_FIFOS_BASE)
#define UDMA_MCU_NAVSS0_UDMASS_RINGACC0_ISC_ISC_BASE            (CSL_MCU_NAVSS0_UDMASS_RINGACC0_ISC_BASE)

#define UDMA_NAVSS0_UDMASS_RINGACC0_GCFG_BASE                   (CSL_NAVSS0_UDMASS_RINGACC0_GCFG_BASE)
#define UDMA_NAVSS0_UDMASS_RINGACC0_CFG_BASE                    (CSL_NAVSS0_UDMASS_RINGACC0_CFG_BASE)
#define UDMA_NAVSS0_UDMASS_RINGACC0_CFG_RT_BASE                 (CSL_NAVSS0_UDMASS_RINGACC0_CFG_RT_BASE)
#define UDMA_NAVSS0_UDMASS_RINGACC0_CFG_MON_BASE                (CSL_NAVSS0_UDMASS_RINGACC0_CFG_MON_BASE)
#define UDMA_NAVSS0_UDMASS_RINGACC0_SRC_FIFOS_BASE              (CSL_NAVSS0_UDMASS_RINGACC0_SRC_FIFOS_BASE)
#define UDMA_NAVSS0_UDMASS_RINGACC0_ISC_ISC_BASE                (CSL_NAVSS0_UDMASS_RINGACC0_ISC_BASE)

#define UDMA_MCU_NAVSS0_UDMASS_PSILSS_CFG0_PROXY_BASE           (CSL_MCU_NAVSS0_UDMASS_PSILSS_CFG0_PROXY_BASE)
#define UDMA_NAVSS0_UDMASS_PSILCFG0_CFG_PROXY_BASE              (CSL_NAVSS0_UDMASS_PSILCFG0_CFG_PROXY_BASE)

#define UDMA_MCU_NAVSS0_UDMASS_INTA0_CFG_BASE                   (CSL_MCU_NAVSS0_UDMASS_INTA0_CFG_BASE)
#define UDMA_MCU_NAVSS0_UDMASS_INTA0_IMAP_BASE                  (CSL_MCU_NAVSS0_UDMASS_INTA0_IMAP_BASE)
#define UDMA_MCU_NAVSS0_UDMASS_INTA0_INTR_BASE                  (CSL_MCU_NAVSS0_UDMASS_INTA0_INTR_BASE)
#define UDMA_MCU_NAVSS0_PAR_UDMASS_UDMASS_INTA0_CFG_L2G_BASE    (CSL_MCU_NAVSS0_UDMASS_INTA0_I2G_BASE)
#define UDMA_MCU_NAVSS0_UDMASS_INTA0_MCAST_BASE                 (CSL_MCU_NAVSS0_UDMASS_INTA0_MCAST_BASE)
#define UDMA_MCU_NAVSS0_UDMASS_INTA0_GCNT_BASE                  (CSL_MCU_NAVSS0_UDMASS_INTA0_GCNT_BASE)
#define UDMA_MCU_NAVSS0_UDMASS_INTA0_GCNTRTI_BASE               (CSL_MCU_NAVSS0_UDMASS_INTA0_GCNTRTI_BASE)

#define UDMA_MCU_NAVSS0_INTR0_CFG_BASE                          (CSL_MCU_NAVSS0_INTR0_CFG_BASE)

#define UDMA_NAVSS0_UDMASS_INTA0_CFG_BASE                       (CSL_NAVSS0_UDMASS_INTA0_CFG_BASE)
#define UDMA_NAVSS0_UDMASS_INTA0_IMAP_BASE                      (CSL_NAVSS0_UDMASS_INTA0_IMAP_BASE)
#define UDMA_NAVSS0_UDMASS_INTA0_CFG_INTR_BASE                  (CSL_NAVSS0_UDMASS_INTA0_CFG_INTR_BASE)
#define UDMA_NAVSS0_UDMASS_INTA0_CFG_L2G_BASE                   (CSL_NAVSS0_UDMASS_INTA0_CFG_L2G_BASE)
#define UDMA_NAVSS0_UDMASS_INTA0_CFG_MCAST_BASE                 (CSL_NAVSS0_UDMASS_INTA0_CFG_MCAST_BASE)
#define UDMA_NAVSS0_UDMASS_INTA0_CFG_GCNTCFG_BASE               (CSL_NAVSS0_UDMASS_INTA0_CFG_GCNTCFG_BASE)
#define UDMA_NAVSS0_UDMASS_INTA0_CFG_GCNTRTI_BASE               (CSL_NAVSS0_UDMASS_INTA0_CFG_GCNTRTI_BASE)

#define UDMA_NAVSS0_INTR0_INTR_ROUTER_CFG_BASE                  (CSL_NAVSS0_INTR0_INTR_ROUTER_CFG_BASE)

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void Udma_initDrvHandle(Udma_DrvHandle drvHandle)
{
    uint32_t            instId;
    CSL_UdmapCfg       *pUdmapRegs;
    CSL_RingAccCfg     *pRaRegs;
    CSL_IntaggrCfg     *pIaRegs;
    CSL_ProxyCfg       *pProxyCfg;
    CSL_ProxyTargetParams *pProxyTargetRing;

    instId = drvHandle->initPrms.instId;
    
    drvHandle->instType = UDMA_INST_TYPE_NORMAL;
    
    /*
     * UDMA config init
     */
    /* Init the config structure - one time step */
    pUdmapRegs = &drvHandle->udmapRegs;
    if(UDMA_INST_ID_MCU_0 == instId)
    {
#ifndef QNX_OS
        pUdmapRegs->pGenCfgRegs     = ((CSL_udmap_gcfgRegs *) UDMA_MCU_NAVSS0_UDMASS_UDMAP0_CFG_GCFG_BASE);
        pUdmapRegs->pRxFlowCfgRegs  = ((CSL_udmap_rxfcfgRegs *) UDMA_MCU_NAVSS0_UDMASS_UDMAP0_CFG_RFLOW_BASE);
        pUdmapRegs->pTxChanCfgRegs  = ((CSL_udmap_txccfgRegs *) UDMA_MCU_NAVSS0_UDMASS_UDMAP0_TCHAN_BASE);
        pUdmapRegs->pRxChanCfgRegs  = ((CSL_udmap_rxccfgRegs *) UDMA_MCU_NAVSS0_UDMASS_UDMAP0_RCHAN_BASE);
        pUdmapRegs->pTxChanRtRegs   = ((CSL_udmap_txcrtRegs *) UDMA_MCU_NAVSS0_UDMASS_UDMAP_TCHANRT_BASE);
        pUdmapRegs->pRxChanRtRegs   = ((CSL_udmap_rxcrtRegs *) UDMA_MCU_NAVSS0_UDMASS_UDMAP_RCHANRT_BASE);
#else
        pUdmapRegs->pGenCfgRegs     = ((CSL_udmap_gcfgRegs *) mmap_device_memory(0,
              CSL_MCU_NAVSS0_UDMASS_UDMAP0_CFG_GCFG_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_MCU_NAVSS0_UDMASS_UDMAP0_CFG_GCFG_BASE));
        pUdmapRegs->pRxFlowCfgRegs  = ((CSL_udmap_rxfcfgRegs *) mmap_device_memory(0,
              CSL_MCU_NAVSS0_UDMASS_UDMAP0_CFG_RFLOW_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_MCU_NAVSS0_UDMASS_UDMAP0_CFG_RFLOW_BASE));
        pUdmapRegs->pTxChanCfgRegs  = ((CSL_udmap_txccfgRegs *) mmap_device_memory(0,
            CSL_MCU_NAVSS0_UDMASS_UDMAP0_TCHAN_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_MCU_NAVSS0_UDMASS_UDMAP0_TCHAN_BASE));
        pUdmapRegs->pRxChanCfgRegs  = ((CSL_udmap_rxccfgRegs *) mmap_device_memory(0,
            CSL_MCU_NAVSS0_UDMASS_UDMAP0_RCHAN_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_MCU_NAVSS0_UDMASS_UDMAP0_RCHAN_BASE));
        pUdmapRegs->pTxChanRtRegs   = ((CSL_udmap_txcrtRegs *) mmap_device_memory(0,
            CSL_MCU_NAVSS0_UDMASS_UDMAP_TCHANRT_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_MCU_NAVSS0_UDMASS_UDMAP_TCHANRT_BASE));
        pUdmapRegs->pRxChanRtRegs   = ((CSL_udmap_rxcrtRegs *) mmap_device_memory(0,
            CSL_MCU_NAVSS0_UDMASS_UDMAP_RCHANRT_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_MCU_NAVSS0_UDMASS_UDMAP_RCHANRT_BASE));

#ifdef QNX_UDMA_DEBUG_CSL_REGS
        printf( "%s: pUdmapRegs->pGenCfgRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
            UDMA_MCU_NAVSS0_UDMASS_UDMAP0_CFG_GCFG_BASE, pUdmapRegs->pGenCfgRegs, CSL_MCU_NAVSS0_UDMASS_UDMAP0_CFG_GCFG_SIZE);
        printf( "%s: pUdmapRegs->pRxFlowCfgRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
            UDMA_MCU_NAVSS0_UDMASS_UDMAP0_CFG_RFLOW_BASE, pUdmapRegs->pRxFlowCfgRegs, CSL_MCU_NAVSS0_UDMASS_UDMAP0_CFG_RFLOW_SIZE);
        printf( "%s: pUdmapRegs->pTxChanCfgRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
            UDMA_MCU_NAVSS0_UDMASS_UDMAP0_TCHAN_BASE, pUdmapRegs->pTxChanCfgRegs, CSL_MCU_NAVSS0_UDMASS_UDMAP0_TCHAN_SIZE);
        printf( "%s: pUdmapRegs->pRxChanCfgRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
            UDMA_MCU_NAVSS0_UDMASS_UDMAP0_RCHAN_BASE, pUdmapRegs->pRxChanCfgRegs, CSL_MCU_NAVSS0_UDMASS_UDMAP0_RCHAN_SIZE);
        printf( "%s: pUdmapRegs->pTxChanRtRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
            UDMA_MCU_NAVSS0_UDMASS_UDMAP_TCHANRT_BASE, pUdmapRegs->pTxChanRtRegs, CSL_MCU_NAVSS0_UDMASS_UDMAP_TCHANRT_SIZE);
        printf( "%s: pUdmapRegs->pRxChanRtRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
            UDMA_MCU_NAVSS0_UDMASS_UDMAP_RCHANRT_BASE, pUdmapRegs->pRxChanRtRegs, CSL_MCU_NAVSS0_UDMASS_UDMAP_RCHANRT_SIZE);
#endif

#endif
        drvHandle->trigGemOffset    = CSL_NAVSS_GEM_MCU_UDMA_TRIGGER_OFFSET;
    }
    else
    {
#ifndef QNX_OS
        pUdmapRegs->pGenCfgRegs     = ((CSL_udmap_gcfgRegs *) UDMA_NAVSS0_UDMASS_UDMAP0_CFG_BASE);
        pUdmapRegs->pRxFlowCfgRegs  = ((CSL_udmap_rxfcfgRegs *) UDMA_NAVSS0_UDMASS_UDMAP0_CFG_RFLOW_BASE);
        pUdmapRegs->pTxChanCfgRegs  = ((CSL_udmap_txccfgRegs *) UDMA_NAVSS0_UDMASS_UDMAP0_CFG_TCHAN_BASE);
        pUdmapRegs->pRxChanCfgRegs  = ((CSL_udmap_rxccfgRegs *) UDMA_NAVSS0_UDMASS_UDMAP0_CFG_RCHAN_BASE);
        pUdmapRegs->pTxChanRtRegs   = ((CSL_udmap_txcrtRegs *) UDMA_NAVSS0_UDMASS_UDMAP0_CFG_TCHANRT_BASE);
        pUdmapRegs->pRxChanRtRegs   = ((CSL_udmap_rxcrtRegs *) UDMA_NAVSS0_UDMASS_UDMAP0_CFG_RCHANRT_BASE);
#else
        pUdmapRegs->pGenCfgRegs     = ((CSL_udmap_gcfgRegs *) mmap_device_memory(0,
            CSL_NAVSS0_UDMASS_UDMAP0_CFG_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_NAVSS0_UDMASS_UDMAP0_CFG_BASE));
        pUdmapRegs->pRxFlowCfgRegs  = ((CSL_udmap_rxfcfgRegs *) mmap_device_memory(0,
            CSL_NAVSS0_UDMASS_UDMAP0_CFG_RFLOW_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_NAVSS0_UDMASS_UDMAP0_CFG_RFLOW_BASE));
        pUdmapRegs->pTxChanCfgRegs  = ((CSL_udmap_txccfgRegs *) mmap_device_memory(0,
            CSL_NAVSS0_UDMASS_UDMAP0_CFG_TCHAN_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_NAVSS0_UDMASS_UDMAP0_CFG_TCHAN_BASE));
        pUdmapRegs->pRxChanCfgRegs  = ((CSL_udmap_rxccfgRegs *) mmap_device_memory(0,
            CSL_NAVSS0_UDMASS_UDMAP0_CFG_RCHAN_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_NAVSS0_UDMASS_UDMAP0_CFG_RCHAN_BASE));
        pUdmapRegs->pTxChanRtRegs   = ((CSL_udmap_txcrtRegs *) mmap_device_memory(0,
            CSL_NAVSS0_UDMASS_UDMAP0_CFG_TCHANRT_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_NAVSS0_UDMASS_UDMAP0_CFG_TCHANRT_BASE));
        pUdmapRegs->pRxChanRtRegs   = ((CSL_udmap_rxcrtRegs *) mmap_device_memory(0,
            CSL_NAVSS0_UDMASS_UDMAP0_CFG_RCHANRT_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_NAVSS0_UDMASS_UDMAP0_CFG_RCHANRT_BASE));

#ifdef QNX_UDMA_DEBUG_CSL_REGS
        printf( "%s: pUdmapRegs->pGenCfgRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
            CSL_NAVSS0_UDMASS_UDMAP0_CFG_BASE, pUdmapRegs->pGenCfgRegs, CSL_NAVSS0_UDMASS_UDMAP0_CFG_SIZE);
        printf( "%s: pUdmapRegs->pRxFlowCfgRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
            UDMA_NAVSS0_UDMASS_UDMAP0_CFG_RFLOW_BASE, pUdmapRegs->pRxFlowCfgRegs, CSL_NAVSS0_UDMASS_UDMAP0_CFG_RFLOW_SIZE);
        printf( "%s: pUdmapRegs->pTxChanCfgRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
            UDMA_NAVSS0_UDMASS_UDMAP0_CFG_TCHAN_BASE, pUdmapRegs->pTxChanCfgRegs, CSL_NAVSS0_UDMASS_UDMAP0_CFG_TCHAN_SIZE);
        printf( "%s: pUdmapRegs->pRxChanCfgRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
            UDMA_NAVSS0_UDMASS_UDMAP0_CFG_RCHAN_BASE, pUdmapRegs->pRxChanCfgRegs, CSL_NAVSS0_UDMASS_UDMAP0_CFG_RCHAN_SIZE);
        printf( "%s: pUdmapRegs->pTxChanRtRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
            UDMA_NAVSS0_UDMASS_UDMAP0_CFG_TCHANRT_BASE, pUdmapRegs->pTxChanRtRegs, CSL_NAVSS0_UDMASS_UDMAP0_CFG_TCHANRT_SIZE);
        printf( "%s: pUdmapRegs->pRxChanRtRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
            UDMA_NAVSS0_UDMASS_UDMAP0_CFG_RCHANRT_BASE, pUdmapRegs->pRxChanRtRegs, CSL_NAVSS0_UDMASS_UDMAP0_CFG_RCHANRT_SIZE);
#endif

#endif
        drvHandle->trigGemOffset    = CSL_NAVSS_GEM_MAIN_UDMA_TRIGGER_OFFSET;
    }
    drvHandle->clecRegs = NULL;
    /* Fill other SOC specific parameters by reading from UDMA config
     * registers */
    CSL_udmapGetCfg(pUdmapRegs);

    /*
     * RA config init
     */
    drvHandle->raType = UDMA_RA_TYPE_NORMAL;
    pRaRegs = &drvHandle->raRegs;
    if(UDMA_INST_ID_MCU_0 == instId)
    {
#ifndef QNX_OS
        pRaRegs->pGlbRegs   = (CSL_ringacc_gcfgRegs *) UDMA_MCU_NAVSS0_UDMASS_RINGACC0_CFG_GCFG_BASE;
        pRaRegs->pCfgRegs   = (CSL_ringacc_cfgRegs *) UDMA_MCU_NAVSS0_UDMASS_RINGACC0_CFG_BASE;
        pRaRegs->pRtRegs    = (CSL_ringacc_rtRegs *) UDMA_MCU_NAVSS0_UDMASS_RINGACC0_CFG_RT_BASE;
        pRaRegs->pMonRegs   = (CSL_ringacc_monitorRegs *) UDMA_MCU_NAVSS0_UDMASS_RINGACC0_CFG_MON_BASE;
        pRaRegs->pFifoRegs  = (CSL_ringacc_fifosRegs *) UDMA_MCU_NAVSS0_UDMASS_RINGACC0_FIFOS_BASE;
        pRaRegs->pIscRegs   = (CSL_ringacc_iscRegs *) UDMA_MCU_NAVSS0_UDMASS_RINGACC0_ISC_ISC_BASE;
#else
        pRaRegs->pGlbRegs   = (CSL_ringacc_gcfgRegs *) mmap_device_memory(0,
            CSL_MCU_NAVSS0_UDMASS_RINGACC0_CFG_GCFG_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_MCU_NAVSS0_UDMASS_RINGACC0_CFG_GCFG_BASE);
        pRaRegs->pCfgRegs   = (CSL_ringacc_cfgRegs *) mmap_device_memory(0,
            CSL_MCU_NAVSS0_UDMASS_RINGACC0_CFG_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_MCU_NAVSS0_UDMASS_RINGACC0_CFG_BASE);
        pRaRegs->pRtRegs    = (CSL_ringacc_rtRegs *) mmap_device_memory(0,
            CSL_MCU_NAVSS0_UDMASS_RINGACC0_CFG_RT_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_MCU_NAVSS0_UDMASS_RINGACC0_CFG_RT_BASE);
        pRaRegs->pMonRegs   = (CSL_ringacc_monitorRegs *) mmap_device_memory(0,
            CSL_MCU_NAVSS0_UDMASS_RINGACC0_CFG_MON_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_MCU_NAVSS0_UDMASS_RINGACC0_CFG_MON_BASE);
        pRaRegs->pFifoRegs  = (CSL_ringacc_fifosRegs *) mmap_device_memory(0,
            CSL_MCU_NAVSS0_UDMASS_RINGACC0_FIFOS_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_MCU_NAVSS0_UDMASS_RINGACC0_FIFOS_BASE);
        pRaRegs->pIscRegs   = (CSL_ringacc_iscRegs *) mmap_device_memory(0,
            CSL_MCU_NAVSS0_UDMASS_RINGACC0_ISC_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_MCU_NAVSS0_UDMASS_RINGACC0_ISC_ISC_BASE);

#ifdef QNX_UDMA_DEBUG_CSL_REGS
        printf( "%s: pRaRegs->pGlbRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
            UDMA_MCU_NAVSS0_UDMASS_RINGACC0_CFG_GCFG_BASE, pRaRegs->pGlbRegs, CSL_MCU_NAVSS0_UDMASS_RINGACC0_CFG_GCFG_SIZE);
        printf( "%s: pRaRegs->pCfgRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
            UDMA_MCU_NAVSS0_UDMASS_RINGACC0_CFG_BASE, pRaRegs->pCfgRegs, CSL_MCU_NAVSS0_UDMASS_RINGACC0_CFG_SIZE);
        printf( "%s: pRaRegs->pRtRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
            UDMA_MCU_NAVSS0_UDMASS_RINGACC0_CFG_RT_BASE, pRaRegs->pRtRegs, CSL_MCU_NAVSS0_UDMASS_RINGACC0_CFG_RT_SIZE);
        printf( "%s: pRaRegs->pMonRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
            UDMA_MCU_NAVSS0_UDMASS_RINGACC0_CFG_MON_BASE, pRaRegs->pMonRegs, CSL_MCU_NAVSS0_UDMASS_RINGACC0_CFG_MON_SIZE);
        printf( "%s: pRaRegs->pFifoRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
            UDMA_MCU_NAVSS0_UDMASS_RINGACC0_FIFOS_BASE, pRaRegs->pFifoRegs, CSL_MCU_NAVSS0_UDMASS_RINGACC0_FIFOS_SIZE);
        printf( "%s: pRaRegs->pIscRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
            UDMA_MCU_NAVSS0_UDMASS_RINGACC0_ISC_ISC_BASE, pRaRegs->pIscRegs, CSL_MCU_NAVSS0_UDMASS_RINGACC0_ISC_SIZE);
#endif

#endif
        pRaRegs->maxRings   = CSL_NAVSS_MCU_RINGACC_RING_CNT;
    }
    else
    {
#ifndef QNX_OS
        pRaRegs->pGlbRegs   = (CSL_ringacc_gcfgRegs *) UDMA_NAVSS0_UDMASS_RINGACC0_GCFG_BASE;
        pRaRegs->pCfgRegs   = (CSL_ringacc_cfgRegs *) UDMA_NAVSS0_UDMASS_RINGACC0_CFG_BASE;
        pRaRegs->pRtRegs    = (CSL_ringacc_rtRegs *) UDMA_NAVSS0_UDMASS_RINGACC0_CFG_RT_BASE;
        pRaRegs->pMonRegs   = (CSL_ringacc_monitorRegs *) UDMA_NAVSS0_UDMASS_RINGACC0_CFG_MON_BASE;
        pRaRegs->pFifoRegs  = (CSL_ringacc_fifosRegs *) UDMA_NAVSS0_UDMASS_RINGACC0_SRC_FIFOS_BASE;
        pRaRegs->pIscRegs   = (CSL_ringacc_iscRegs *) UDMA_NAVSS0_UDMASS_RINGACC0_ISC_ISC_BASE;
#else
        pRaRegs->pGlbRegs   = (CSL_ringacc_gcfgRegs *) mmap_device_memory(0,
            CSL_NAVSS0_UDMASS_RINGACC0_GCFG_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_NAVSS0_UDMASS_RINGACC0_GCFG_BASE);
        pRaRegs->pCfgRegs   = (CSL_ringacc_cfgRegs *) mmap_device_memory(0,
            CSL_NAVSS0_UDMASS_RINGACC0_CFG_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_NAVSS0_UDMASS_RINGACC0_CFG_BASE);
        pRaRegs->pRtRegs    = (CSL_ringacc_rtRegs *) mmap_device_memory(0,
            CSL_NAVSS0_UDMASS_RINGACC0_CFG_RT_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_NAVSS0_UDMASS_RINGACC0_CFG_RT_BASE);
        pRaRegs->pMonRegs   = (CSL_ringacc_monitorRegs *) mmap_device_memory(0,
            CSL_NAVSS0_UDMASS_RINGACC0_CFG_MON_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_NAVSS0_UDMASS_RINGACC0_CFG_MON_BASE);
        pRaRegs->pFifoRegs  = (CSL_ringacc_fifosRegs *) mmap_device_memory(0,
            CSL_NAVSS0_UDMASS_RINGACC0_SRC_FIFOS_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_NAVSS0_UDMASS_RINGACC0_SRC_FIFOS_BASE);
        pRaRegs->pIscRegs   = (CSL_ringacc_iscRegs *) mmap_device_memory(0,
            CSL_NAVSS0_UDMASS_RINGACC0_ISC_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_NAVSS0_UDMASS_RINGACC0_ISC_BASE);

#ifdef QNX_UDMA_DEBUG_CSL_REGS
        printf( "%s: pRaRegs->pGlbRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
            UDMA_NAVSS0_UDMASS_RINGACC0_GCFG_BASE, pRaRegs->pGlbRegs, CSL_NAVSS0_UDMASS_RINGACC0_GCFG_SIZE);
        printf( "%s: pRaRegs->pCfgRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
            UDMA_NAVSS0_UDMASS_RINGACC0_CFG_BASE, pRaRegs->pCfgRegs, CSL_NAVSS0_UDMASS_RINGACC0_CFG_SIZE);
        printf( "%s: pRaRegs->pRtRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
            UDMA_NAVSS0_UDMASS_RINGACC0_CFG_RT_BASE, pRaRegs->pRtRegs, CSL_NAVSS0_UDMASS_RINGACC0_CFG_RT_SIZE);
        printf( "%s: pRaRegs->pMonRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
            UDMA_NAVSS0_UDMASS_RINGACC0_CFG_MON_BASE, pRaRegs->pMonRegs, CSL_NAVSS0_UDMASS_RINGACC0_CFG_MON_SIZE);
        printf( "%s: pRaRegs->pFifoRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
            CSL_NAVSS0_UDMASS_RINGACC0_SRC_FIFOS_BASE, pRaRegs->pFifoRegs, CSL_NAVSS0_UDMASS_RINGACC0_SRC_FIFOS_SIZE);
        printf( "%s: pRaRegs->pIscRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
            UDMA_NAVSS0_UDMASS_RINGACC0_ISC_ISC_BASE, pRaRegs->pIscRegs, CSL_NAVSS0_UDMASS_RINGACC0_ISC_SIZE);
#endif

#endif
        pRaRegs->maxRings   = CSL_NAVSS_MAIN_RINGACC_RING_CNT;
    }
    pRaRegs->maxMonitors     = CSL_RINGACC_MAX_MONITORS;
    pRaRegs->bTraceSupported = (bool)true;

    drvHandle->ringDequeueRaw           = &Udma_ringDequeueRawNormal;
    drvHandle->ringQueueRaw             = &Udma_ringQueueRawNormal;
    drvHandle->ringFlushRaw             = &Udma_ringFlushRawNormal;
    drvHandle->ringGetElementCnt        = &Udma_ringGetElementCntNormal;
    drvHandle->ringGetMemPtr            = &Udma_ringGetMemPtrNormal;
    drvHandle->ringGetMode              = &Udma_ringGetModeNormal;
    drvHandle->ringGetForwardRingOcc    = &Udma_ringGetRingOccNormal;
    drvHandle->ringGetReverseRingOcc    = &Udma_ringGetRingOccNormal;
    drvHandle->ringGetWrIdx             = &Udma_ringGetWrIdxNormal;
    drvHandle->ringGetRdIdx             = &Udma_ringGetRdIdxNormal;
    drvHandle->ringPrime                = &Udma_ringPrimeNormal;
    drvHandle->ringPrimeRead            = &Udma_ringPrimeReadNormal;
    drvHandle->ringSetDoorBell          = &Udma_ringSetDoorBellNormal;
    drvHandle->ringSetCfg               = &Udma_ringSetCfgNormal;
    drvHandle->ringHandleClearRegs      = &Udma_ringHandleClearRegsNormal;

    /*
     * All interrupt related config should be based on core and not
     * based on NAVSS instance
     */
#if defined (BUILD_MCU1_0) || defined (BUILD_MCU1_1)
    /* IA config init */
    pIaRegs = &drvHandle->iaRegs;
#ifndef QNX_OS
    pIaRegs->pCfgRegs       = (CSL_intaggr_cfgRegs *) UDMA_MCU_NAVSS0_UDMASS_INTA0_CFG_BASE;
    pIaRegs->pImapRegs      = (CSL_intaggr_imapRegs *) UDMA_MCU_NAVSS0_UDMASS_INTA0_IMAP_BASE;
    pIaRegs->pIntrRegs      = (CSL_intaggr_intrRegs *) UDMA_MCU_NAVSS0_UDMASS_INTA0_INTR_BASE;
    pIaRegs->pL2gRegs       = (CSL_intaggr_l2gRegs *) UDMA_MCU_NAVSS0_PAR_UDMASS_UDMASS_INTA0_CFG_L2G_BASE;
    pIaRegs->pMcastRegs     = (CSL_intaggr_mcastRegs *) UDMA_MCU_NAVSS0_UDMASS_INTA0_MCAST_BASE;
    pIaRegs->pGcntCfgRegs   = (CSL_intaggr_gcntcfgRegs *) UDMA_MCU_NAVSS0_UDMASS_INTA0_GCNT_BASE;
    pIaRegs->pGcntRtiRegs   = (CSL_intaggr_gcntrtiRegs *) UDMA_MCU_NAVSS0_UDMASS_INTA0_GCNTRTI_BASE;
#else
    pIaRegs->pCfgRegs       = (CSL_intaggr_cfgRegs *) mmap_device_memory(0,
      CSL_MCU_NAVSS0_UDMASS_INTA0_CFG_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0,  UDMA_MCU_NAVSS0_UDMASS_INTA0_CFG_BASE);
    pIaRegs->pImapRegs      = (CSL_intaggr_imapRegs *) mmap_device_memory(0,
      CSL_MCU_NAVSS0_UDMASS_INTA0_IMAP_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_MCU_NAVSS0_UDMASS_INTA0_IMAP_BASE);
    pIaRegs->pIntrRegs      = (CSL_intaggr_intrRegs *) mmap_device_memory(0,
      CSL_MCU_NAVSS0_UDMASS_INTA0_INTR_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_MCU_NAVSS0_UDMASS_INTA0_INTR_BASE);
    pIaRegs->pL2gRegs       = (CSL_intaggr_l2gRegs *) mmap_device_memory(0,
      CSL_MCU_NAVSS0_PAR_UDMASS_UDMASS_INTA0_CFG_L2G_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_MCU_NAVSS0_PAR_UDMASS_UDMASS_INTA0_CFG_L2G_BASE);
    pIaRegs->pMcastRegs     = (CSL_intaggr_mcastRegs *) mmap_device_memory(0,
      CSL_MCU_NAVSS0_UDMASS_INTA0_MCAST_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_MCU_NAVSS0_UDMASS_INTA0_MCAST_BASE);
    pIaRegs->pGcntCfgRegs   = (CSL_intaggr_gcntcfgRegs *) mmap_device_memory(0,
      CSL_MCU_NAVSS0_UDMASS_INTA0_GCNT_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_MCU_NAVSS0_UDMASS_INTA0_GCNT_BASE);
    pIaRegs->pGcntRtiRegs   = (CSL_intaggr_gcntrtiRegs *) mmap_device_memory(0,
      CSL_MCU_NAVSS0_UDMASS_INTA0_GCNTRTI_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_MCU_NAVSS0_UDMASS_INTA0_GCNTRTI_BASE);

#ifdef QNX_UDMA_DEBUG_CSL_REGS
    printf( "%s: pIaRegs->pCfgRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
        UDMA_MCU_NAVSS0_UDMASS_INTA0_CFG_BASE, pIaRegs->pCfgRegs, CSL_MCU_NAVSS0_UDMASS_INTA0_CFG_SIZE);
    printf( "%s: pIaRegs->pImapRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
        UDMA_MCU_NAVSS0_UDMASS_INTA0_IMAP_BASE, pIaRegs->pImapRegs, CSL_MCU_NAVSS0_UDMASS_INTA0_IMAP_SIZE);
    printf( "%s: pIaRegs->pIntrRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
        UDMA_MCU_NAVSS0_UDMASS_INTA0_INTR_BASE, pIaRegs->pIntrRegs, CSL_MCU_NAVSS0_UDMASS_INTA0_INTR_SIZE);
    printf( "%s: pIaRegs->pL2gRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
        UDMA_MCU_NAVSS0_PAR_UDMASS_UDMASS_INTA0_CFG_L2G_BASE, pIaRegs->pL2gRegs, CSL_MCU_NAVSS0_PAR_UDMASS_UDMASS_INTA0_CFG_L2G_SIZE);
    printf( "%s: pIaRegs->pMcastRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
        UDMA_MCU_NAVSS0_UDMASS_INTA0_MCAST_BASE, pIaRegs->pMcastRegs, CSL_MCU_NAVSS0_UDMASS_INTA0_MCAST_SIZE);
    printf( "%s: pIaRegs->pGcntCfgRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
        UDMA_MCU_NAVSS0_UDMASS_INTA0_GCNT_BASE, pIaRegs->pGcntCfgRegs, CSL_MCU_NAVSS0_UDMASS_INTA0_GCNT_SIZE);
    printf( "%s: pIaRegs->pGcntRtiRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
        UDMA_MCU_NAVSS0_UDMASS_INTA0_GCNTRTI_BASE, pIaRegs->pGcntRtiRegs, CSL_MCU_NAVSS0_UDMASS_INTA0_GCNTRTI_SIZE);
#endif

#endif
    CSL_intaggrGetCfg(pIaRegs);

    drvHandle->iaGemOffset  = CSL_NAVSS_GEM_MCU_UDMA_INTA0_SEVI_OFFSET;
    drvHandle->devIdIa      = TISCI_DEV_MCU_NAVSS0_UDMASS_INTA_0;
    drvHandle->devIdIr      = TISCI_DEV_MCU_NAVSS0_INTR_0;
#else
    /* IA config init */
    pIaRegs = &drvHandle->iaRegs;
#ifndef QNX_OS
    pIaRegs->pCfgRegs       = (CSL_intaggr_cfgRegs *) UDMA_NAVSS0_UDMASS_INTA0_CFG_BASE;
    pIaRegs->pImapRegs      = (CSL_intaggr_imapRegs *) UDMA_NAVSS0_UDMASS_INTA0_IMAP_BASE;
    pIaRegs->pIntrRegs      = (CSL_intaggr_intrRegs *) UDMA_NAVSS0_UDMASS_INTA0_CFG_INTR_BASE;
    pIaRegs->pL2gRegs       = (CSL_intaggr_l2gRegs *) UDMA_NAVSS0_UDMASS_INTA0_CFG_L2G_BASE;
    pIaRegs->pMcastRegs     = (CSL_intaggr_mcastRegs *) UDMA_NAVSS0_UDMASS_INTA0_CFG_MCAST_BASE;
    pIaRegs->pGcntCfgRegs   = (CSL_intaggr_gcntcfgRegs *) UDMA_NAVSS0_UDMASS_INTA0_CFG_GCNTCFG_BASE;
    pIaRegs->pGcntRtiRegs   = (CSL_intaggr_gcntrtiRegs *) UDMA_NAVSS0_UDMASS_INTA0_CFG_GCNTRTI_BASE;
#else
    pIaRegs->pCfgRegs       = (CSL_intaggr_cfgRegs *) mmap_device_memory(0,
      CSL_NAVSS0_UDMASS_INTA0_CFG_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0,  CSL_NAVSS0_UDMASS_INTA0_CFG_BASE);
    pIaRegs->pImapRegs      = (CSL_intaggr_imapRegs *) mmap_device_memory(0,
      CSL_NAVSS0_UDMASS_INTA0_IMAP_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_NAVSS0_UDMASS_INTA0_IMAP_BASE);
    pIaRegs->pIntrRegs      = (CSL_intaggr_intrRegs *) mmap_device_memory(0,
      CSL_NAVSS0_UDMASS_INTA0_CFG_INTR_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_NAVSS0_UDMASS_INTA0_CFG_INTR_BASE);
    pIaRegs->pL2gRegs       = (CSL_intaggr_l2gRegs *) mmap_device_memory(0,
      CSL_NAVSS0_UDMASS_INTA0_CFG_L2G_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_NAVSS0_UDMASS_INTA0_CFG_L2G_BASE);
    pIaRegs->pMcastRegs     = (CSL_intaggr_mcastRegs *) mmap_device_memory(0,
      CSL_NAVSS0_UDMASS_INTA0_CFG_MCAST_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_NAVSS0_UDMASS_INTA0_CFG_MCAST_BASE);
    pIaRegs->pGcntCfgRegs   = (CSL_intaggr_gcntcfgRegs *) mmap_device_memory(0,
      CSL_NAVSS0_UDMASS_INTA0_CFG_GCNTCFG_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_NAVSS0_UDMASS_INTA0_CFG_GCNTCFG_BASE);
    pIaRegs->pGcntRtiRegs   = (CSL_intaggr_gcntrtiRegs *) mmap_device_memory(0,
      CSL_NAVSS0_UDMASS_INTA0_CFG_GCNTRTI_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, CSL_NAVSS0_UDMASS_INTA0_CFG_GCNTRTI_BASE);

#ifdef QNX_UDMA_DEBUG_CSL_REGS
    printf( "%s: pIaRegs->pCfgRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
        CSL_NAVSS0_UDMASS_INTA0_CFG_BASE, pIaRegs->pCfgRegs, CSL_NAVSS0_UDMASS_INTA0_CFG_SIZE);
    printf( "%s: pIaRegs->pImapRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
        CSL_NAVSS0_UDMASS_INTA0_IMAP_BASE, pIaRegs->pImapRegs, CSL_NAVSS0_UDMASS_INTA0_IMAP_SIZE);
    printf( "%s: pIaRegs->pIntrRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
        CSL_NAVSS0_UDMASS_INTA0_CFG_INTR_BASE, pIaRegs->pIntrRegs, CSL_NAVSS0_UDMASS_INTA0_CFG_INTR_SIZE);
    printf( "%s: pIaRegs->pL2gRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
        CSL_NAVSS0_UDMASS_INTA0_CFG_L2G_BASE, pIaRegs->pL2gRegs, CSL_NAVSS0_UDMASS_INTA0_CFG_L2G_SIZE);
    printf( "%s: pIaRegs->pMcastRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
        CSL_NAVSS0_UDMASS_INTA0_CFG_MCAST_BASE, pIaRegs->pMcastRegs, CSL_NAVSS0_UDMASS_INTA0_CFG_MCAST_SIZE);
    printf( "%s: pIaRegs->pGcntCfgRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
        CSL_NAVSS0_UDMASS_INTA0_CFG_GCNTCFG_BASE, pIaRegs->pGcntCfgRegs, CSL_NAVSS0_UDMASS_INTA0_CFG_GCNTCFG_SIZE);
    printf( "%s: pIaRegs->pGcntRtiRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
        CSL_NAVSS0_UDMASS_INTA0_CFG_GCNTRTI_BASE, pIaRegs->pGcntRtiRegs, CSL_NAVSS0_UDMASS_INTA0_CFG_GCNTRTI_SIZE);
#endif

#endif
    CSL_intaggrGetCfg(pIaRegs);

    drvHandle->iaGemOffset  = CSL_NAVSS_GEM_MAIN_UDMA_INTA0_SEVI_OFFSET;
    drvHandle->devIdIa      = TISCI_DEV_NAVSS0_UDMASS_INTA_0;
    drvHandle->devIdIr      = TISCI_DEV_NAVSS0_INTR_ROUTER_0;
    drvHandle->clecRtMap    = CSL_CLEC_RTMAP_DISABLE;
    drvHandle->clecOffset   = 0U;
#endif

    drvHandle->devIdCore    = Udma_getCoreSciDevId();
    
    /*
     * Proxy init
     */
    pProxyCfg           = &drvHandle->proxyCfg;
    pProxyTargetRing    = &drvHandle->proxyTargetRing;
    if(UDMA_INST_ID_MCU_0 == instId)
    {
#ifdef QNX_OS
        pProxyTargetRing->pTargetRegs   = (CSL_proxy_target0Regs *) (CSL_proxyRegs *) mmap_device_memory(0,
            CSL_MCU_NAVSS0_PROXY0_TARGET0_DATA_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0,  CSL_MCU_NAVSS0_PROXY0_TARGET0_DATA_BASE);

#ifdef QNX_UDMA_DEBUG_CSL_REGS
        printf( "%s: pTargetRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
            CSL_MCU_NAVSS0_PROXY0_TARGET0_DATA_BASE, pProxyTargetRing->pTargetRegs, CSL_MCU_NAVSS0_PROXY0_TARGET0_DATA_SIZE);
#endif

#else
        pProxyTargetRing->pTargetRegs   = (CSL_proxy_target0Regs *) CSL_MCU_NAVSS0_PROXY0_TARGET0_DATA_BASE;
#endif
        pProxyTargetRing->numChns       = CSL_NAVSS_MCU_PROXY_TARGET_RINGACC0_NUM_CHANNELS;
        pProxyTargetRing->chnSizeBytes  = CSL_NAVSS_MCU_PROXY_TARGET_RINGACC0_NUM_CHANNEL_SIZE_BYTES;

#ifdef QNX_OS
        pProxyCfg->pGlbRegs             = (CSL_proxyRegs *) mmap_device_memory(0,
            CSL_MCU_NAVSS0_PROXY_CFG_GCFG_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0,  CSL_MCU_NAVSS0_PROXY_CFG_GCFG_BASE);
        pProxyCfg->pCfgRegs             = (CSL_proxy_cfgRegs *) mmap_device_memory(0,
            CSL_MCU_NAVSS0_PROXY0_BUF_CFG_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0,  CSL_MCU_NAVSS0_PROXY0_BUF_CFG_BASE);

#ifdef QNX_UDMA_DEBUG_CSL_REGS
        printf( "%s: pProxyCfg->pGlbRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
            CSL_MCU_NAVSS0_PROXY_CFG_GCFG_BASE, pProxyCfg->pGlbRegs, CSL_MCU_NAVSS0_PROXY_CFG_GCFG_SIZE);
        printf( "%s: pProxyCfg->pCfgRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
            CSL_MCU_NAVSS0_PROXY0_BUF_CFG_BASE, pProxyCfg->pCfgRegs, CSL_MCU_NAVSS0_PROXY0_BUF_CFG_SIZE);
#endif

#else
        pProxyCfg->pGlbRegs             = (CSL_proxyRegs *) CSL_MCU_NAVSS0_PROXY_CFG_GCFG_BASE;
        pProxyCfg->pCfgRegs             = (CSL_proxy_cfgRegs *) CSL_MCU_NAVSS0_PROXY0_BUF_CFG_BASE;
#endif
        pProxyCfg->bufferSizeBytes      = CSL_NAVSS_MCU_PROXY_BUFFER_SIZE_BYTES;
        pProxyCfg->numTargets           = 1U;
        pProxyCfg->pProxyTargetParams   = pProxyTargetRing;

        drvHandle->proxyTargetNumRing   = CSL_NAVSS_MCU_PROXY_TARGET_NUM_RINGACC0;
    }
    else
    {
#ifdef QNX_OS
        pProxyTargetRing->pTargetRegs   = (CSL_proxy_target0Regs *) (CSL_proxyRegs *) mmap_device_memory(0,
            CSL_NAVSS0_PROXY_TARGET0_DATA_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0,  CSL_NAVSS0_PROXY_TARGET0_DATA_BASE);

#ifdef QNX_UDMA_DEBUG_CSL_REGS
        printf( "%s: pTargetRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
            CSL_NAVSS0_PROXY_TARGET0_DATA_BASE, pProxyTargetRing->pTargetRegs, CSL_NAVSS0_PROXY_TARGET0_DATA_SIZE);
#endif

#else
        pProxyTargetRing->pTargetRegs   = (CSL_proxy_target0Regs *) CSL_NAVSS0_PROXY_TARGET0_DATA_BASE;
#endif
        pProxyTargetRing->numChns       = CSL_NAVSS_MAIN_PROXY_TARGET_RINGACC0_NUM_CHANNELS;
        pProxyTargetRing->chnSizeBytes  = CSL_NAVSS_MAIN_PROXY_TARGET_RINGACC0_NUM_CHANNEL_SIZE_BYTES;

#ifdef QNX_OS
        pProxyCfg->pGlbRegs             = (CSL_proxyRegs *) mmap_device_memory(0,
            CSL_NAVSS0_PROXY0_CFG_BUF_CFG_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0,  CSL_NAVSS0_PROXY0_CFG_BUF_CFG_BASE);
        pProxyCfg->pCfgRegs             = (CSL_proxy_cfgRegs *) mmap_device_memory(0,
            CSL_NAVSS0_PROXY0_BUF_CFG_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0,  CSL_NAVSS0_PROXY0_BUF_CFG_BASE);

#ifdef QNX_UDMA_DEBUG_CSL_REGS
        printf( "%s: pProxyCfg->pGlbRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
            CSL_NAVSS0_PROXY0_CFG_BUF_CFG_BASE, pProxyCfg->pGlbRegs, CSL_NAVSS0_PROXY0_CFG_BUF_CFG_SIZE);
        printf( "%s: pProxyCfg->pCfgRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
            CSL_NAVSS0_PROXY0_BUF_CFG_BASE, pProxyCfg->pCfgRegs, CSL_NAVSS0_PROXY0_BUF_CFG_SIZE);
#endif

#else
        pProxyCfg->pGlbRegs             = (CSL_proxyRegs *) CSL_NAVSS0_PROXY0_CFG_BUF_CFG_BASE;
        pProxyCfg->pCfgRegs             = (CSL_proxy_cfgRegs *) CSL_NAVSS0_PROXY0_BUF_CFG_BASE;
#endif
        pProxyCfg->bufferSizeBytes      = CSL_NAVSS_MAIN_PROXY_BUFFER_SIZE_BYTES;
        pProxyCfg->numTargets           = 1U;
        pProxyCfg->pProxyTargetParams   = pProxyTargetRing;

        drvHandle->proxyTargetNumRing   = CSL_NAVSS_MAIN_PROXY_TARGET_NUM_RINGACC0;
    }

    /* Init other variables */
    if(UDMA_INST_ID_MCU_0 == instId)
    {
        drvHandle->udmapSrcThreadOffset = CSL_PSILCFG_NAVSS_MCU_UDMAP0_TSTRM_THREAD_OFFSET;
        drvHandle->udmapDestThreadOffset= CSL_PSILCFG_NAVSS_MCU_UDMAP0_RSTRM_THREAD_OFFSET;
        drvHandle->maxRings             = CSL_NAVSS_MCU_RINGACC_RING_CNT;
        drvHandle->maxProxy             = CSL_NAVSS_MCU_PROXY_NUM_PROXIES;
        drvHandle->maxRingMon           = CSL_NAVSS_MCU_RINGACC_NUM_MONITORS;
        drvHandle->devIdRing            = TISCI_DEV_MCU_NAVSS0_RINGACC0;
        drvHandle->devIdProxy           = TISCI_DEV_MCU_NAVSS0_PROXY0;
        drvHandle->devIdUdma            = TISCI_DEV_MCU_NAVSS0_UDMAP_0;
        drvHandle->devIdPsil            = TISCI_DEV_MCU_NAVSS0;
    }
    else
    {
        drvHandle->udmapSrcThreadOffset = CSL_PSILCFG_NAVSS_MAIN_UDMAP0_TSTRM_THREAD_OFFSET;
        drvHandle->udmapDestThreadOffset= CSL_PSILCFG_NAVSS_MAIN_UDMAP0_RSTRM_THREAD_OFFSET;
        drvHandle->maxRings             = CSL_NAVSS_MAIN_RINGACC_RING_CNT;
        drvHandle->maxProxy             = CSL_NAVSS_MAIN_PROXY_NUM_PROXIES;
        drvHandle->maxRingMon           = CSL_NAVSS_MAIN_RINGACC_NUM_MONITORS;
        drvHandle->devIdRing            = TISCI_DEV_NAVSS0_RINGACC_0;
        drvHandle->devIdProxy           = TISCI_DEV_NAVSS0_PROXY_0;
        drvHandle->devIdUdma            = TISCI_DEV_NAVSS0_UDMAP_0;
        drvHandle->devIdPsil            = TISCI_DEV_NAVSS0;
    }
    drvHandle->srcIdRingIrq          = drvHandle->devIdRing;
    drvHandle->blkCopyRingIrqOffset  = TISCI_RINGACC0_OES_IRQ_SRC_IDX_START; 
    drvHandle->txRingIrqOffset       = TISCI_RINGACC0_OES_IRQ_SRC_IDX_START;
    drvHandle->rxRingIrqOffset       = TISCI_RINGACC0_OES_IRQ_SRC_IDX_START;
    drvHandle->srcIdTrIrq            = drvHandle->devIdUdma;
    drvHandle->blkCopyTrIrqOffset    = TISCI_UDMAP0_RX_OES_IRQ_SRC_IDX_START; 
    drvHandle->txTrIrqOffset         = TISCI_UDMAP0_TX_OES_IRQ_SRC_IDX_START;
    drvHandle->rxTrIrqOffset         = TISCI_UDMAP0_RX_OES_IRQ_SRC_IDX_START;
    drvHandle->txChOffset            = 0U;
    drvHandle->extChOffset           = drvHandle->txChOffset + pUdmapRegs->txChanCnt;
    drvHandle->rxChOffset            =
        drvHandle->extChOffset + pUdmapRegs->txExtUtcChanCnt;

    return;
}

uint32_t Udma_getCoreId(void)
{
    uint32_t coreId;

#if defined (BUILD_MPU1_0)
    coreId = UDMA_CORE_ID_MPU1_0;
#endif
#if defined (BUILD_MCU2_0)
    coreId = UDMA_CORE_ID_MCU2_0;
#endif
#if defined (BUILD_MCU2_1)
    coreId = UDMA_CORE_ID_MCU2_1;
#endif
#if defined (BUILD_MCU1_0)
    coreId = UDMA_CORE_ID_MCU1_0;
#endif
#if defined (BUILD_MCU1_1)
    coreId = UDMA_CORE_ID_MCU1_1;
#endif

    return (coreId);
}

uint16_t Udma_getCoreSciDevId(void)
{
    uint16_t coreSciDevId;

#if defined (BUILD_MPU1_0)
    coreSciDevId = TISCI_DEV_COMPUTE_CLUSTER0_GIC500SS;
#endif
#if defined (BUILD_MCU2_0)
    coreSciDevId = TISCI_DEV_R5FSS0_CORE0;
#endif
#if defined (BUILD_MCU2_1)
    coreSciDevId = TISCI_DEV_R5FSS0_CORE1;
#endif
#if defined (BUILD_MCU1_0)
    coreSciDevId = TISCI_DEV_MCU_R5FSS0_CORE0;
#endif
#if defined (BUILD_MCU1_1)
    coreSciDevId = TISCI_DEV_MCU_R5FSS0_CORE1;
#endif

    return (coreSciDevId);
}

uint32_t Udma_isCacheCoherent(void)
{
    uint32_t isCacheCoherent;

#if defined (BUILD_MPU1_0)
    isCacheCoherent = TRUE;
#else
    isCacheCoherent = FALSE;
#endif

    return (isCacheCoherent);
}
