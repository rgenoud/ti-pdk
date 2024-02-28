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
#if defined (LOKI_BUILD)
#define HOST_EMULATION (1U)
#endif

#if defined (HOST_EMULATION)
/* These variables are defined for supporting host emulation ( PC emulation ) and
will not be used for target*/
CSL_udmap_gcfgRegs              gHost_udmap_gcfgRegs;
CSL_udmap_rxfcfgRegs            gHost_udmap_rxfcfgRegs;
CSL_udmap_txccfgRegs            gHost_udmap_txccfgRegs;
CSL_udmap_rxccfgRegs            gHost_udmap_rxccfgRegs;
CSL_udmap_txcrtRegs             gHost_udmap_txcrtRegs;
CSL_udmap_rxcrtRegs             gHost_udmap_rxcrtRegs;
CSL_bcdma_gcfgRegs              gHost_bcdma_gcfgRegs;
CSL_bcdma_txccfgRegs            gHost_bcdma_txccfgRegs;
CSL_bcdma_txcrtRegs             gHost_bcdma_txcrtRegs;
CSL_bcdma_rxccfgRegs            gHost_bcdma_rxccfgRegs;
CSL_bcdma_rxcrtRegs             gHost_bcdma_rxcrtRegs;
CSL_ringacc_gcfgRegs            gHost_ringacc_gcfgRegs;
CSL_ringacc_cfgRegs             gHost_ringacc_cfgRegs;
CSL_ringacc_rtRegs              gHost_ringacc_rtRegs;
CSL_ringacc_monitorRegs         gHost_ringacc_monitorRegs;
CSL_ringacc_fifosRegs           gHost_ringacc_fifosRegs;
CSL_ringacc_iscRegs             gHost_ringacc_iscRegs;
CSL_lcdma_ringacc_ring_cfgRegs  gHost_lcdma_ringacc_cfgRegs;
CSL_lcdma_ringacc_ringrtRegs    gHost_lcdma_ringacc_ringrtRegs;
CSL_lcdma_ringacc_credRegs      gHost_lcdma_ringacc_credRegs;
CSL_psilcfgRegs                 gHost_psilcfgRegs;
CSL_intaggr_cfgRegs             gHost_intaggr_cfgRegs;
CSL_intaggr_imapRegs            gHost_intaggr_imapRegs;
CSL_intaggr_intrRegs            gHost_intaggr_intrRegs;
CSL_intaggr_l2gRegs             gHost_intaggr_l2gRegs;
CSL_intaggr_mcastRegs           gHost_intaggr_mcastRegs;
CSL_intaggr_gcntcfgRegs         gHost_intaggr_gcntcfgRegs;
CSL_intaggr_gcntrtiRegs         gHost_intaggr_gcntrtiRegs;
CSL_intaggr_unmapRegs           gHost_intaggr_unmapRegs;
CSL_intr_router_cfgRegs         gHost_intr_router_cfgRegs;
CSL_CLEC_EVTRegs                gHost_clec_evtRegs;

CSL_DRU_t                gHost_DRU_t0, gHost_DRU_t4, gHost_DRU_t5, gHost_DRU_t6, gHost_DRU_t7;
#define UDMA_MCU_NAVSS0_UDMASS_UDMAP0_CFG_GCFG_BASE         (&gHost_udmap_gcfgRegs)
#define UDMA_MCU_NAVSS0_UDMASS_UDMAP0_CFG_RFLOW_BASE        (&gHost_udmap_rxfcfgRegs)
#define UDMA_MCU_NAVSS0_UDMASS_UDMAP0_TCHAN_BASE            (&gHost_udmap_txccfgRegs)
#define UDMA_MCU_NAVSS0_UDMASS_UDMAP0_RCHAN_BASE            (&gHost_udmap_rxccfgRegs)
#define UDMA_MCU_NAVSS0_UDMASS_UDMAP_TCHANRT_BASE           (&gHost_udmap_txcrtRegs)
#define UDMA_MCU_NAVSS0_UDMASS_UDMAP_RCHANRT_BASE           (&gHost_udmap_rxcrtRegs)

#define UDMA_NAVSS0_UDMASS_UDMAP0_CFG_BASE                  (&gHost_udmap_gcfgRegs)
#define UDMA_NAVSS0_UDMASS_UDMAP0_CFG_RFLOW_BASE            (&gHost_udmap_rxfcfgRegs)
#define UDMA_NAVSS0_UDMASS_UDMAP0_CFG_TCHAN_BASE            (&gHost_udmap_txccfgRegs)
#define UDMA_NAVSS0_UDMASS_UDMAP0_CFG_RCHAN_BASE            (&gHost_udmap_rxccfgRegs)
#define UDMA_NAVSS0_UDMASS_UDMAP0_CFG_TCHANRT_BASE          (&gHost_udmap_txcrtRegs)
#define UDMA_NAVSS0_UDMASS_UDMAP0_CFG_RCHANRT_BASE          (&gHost_udmap_rxcrtRegs)

#define UDMA_NAVSS0_BCDMA0_CFG_GCFG_BASE                    (&gHost_bcdma_gcfgRegs)
#define UDMA_NAVSS0_BCDMA0_CFG_TCHAN_BASE                   (&gHost_bcdma_txccfgRegs)
#define UDMA_NAVSS0_BCDMA0_CFG_RCHAN_BASE                   (&gHost_bcdma_rxccfgRegs)
#define UDMA_NAVSS0_BCDMA0_CFG_TCHANRT_BASE                 (&gHost_bcdma_txcrtRegs)
#define UDMA_NAVSS0_BCDMA0_CFG_RCHANRT_BASE                 (&gHost_bcdma_rxcrtRegs)

#define UDMA_MCU_NAVSS0_UDMASS_RINGACC0_CFG_GCFG_BASE       (&gHost_ringacc_gcfgRegs)
#define UDMA_MCU_NAVSS0_UDMASS_RINGACC0_CFG_BASE            (&gHost_ringacc_cfgRegs)
#define UDMA_MCU_NAVSS0_UDMASS_RINGACC0_CFG_RT_BASE         (&gHost_ringacc_rtRegs)
#define UDMA_MCU_NAVSS0_UDMASS_RINGACC0_CFG_MON_BASE        (&gHost_ringacc_monitorRegs)
#define UDMA_MCU_NAVSS0_UDMASS_RINGACC0_FIFOS_BASE          (&gHost_ringacc_fifosRegs)
#define UDMA_MCU_NAVSS0_UDMASS_RINGACC0_ISC_ISC_BASE        (&gHost_ringacc_iscRegs)

#define UDMA_NAVSS0_UDMASS_RINGACC0_GCFG_BASE               (&gHost_ringacc_gcfgRegs)
#define UDMA_NAVSS0_UDMASS_RINGACC0_CFG_BASE                (&gHost_ringacc_cfgRegs)
#define UDMA_NAVSS0_UDMASS_RINGACC0_CFG_RT_BASE             (&gHost_ringacc_rtRegs)
#define UDMA_NAVSS0_UDMASS_RINGACC0_CFG_MON_BASE            (&gHost_ringacc_monitorRegs)
#define UDMA_NAVSS0_UDMASS_RINGACC0_SRC_FIFOS_BASE          (&gHost_ringacc_fifosRegs)
#define UDMA_NAVSS0_UDMASS_RINGACC0_ISC_ISC_BASE            (&gHost_ringacc_iscRegs)

#define UDMA_NAVSS0_BCDMA0_CFG_RING_BASE                    (&gHost_lcdma_ringacc_cfgRegs)
#define UDMA_NAVSS0_BCDMA0_CFG_RINGRT_BASE                  (&gHost_lcdma_ringacc_ringrtRegs)
#define UDMA_NAVSS0_CRED_BASE                               (&gHost_lcdma_ringacc_credRegs)

#define UDMA_MCU_NAVSS0_UDMASS_PSILSS_CFG0_PROXY_BASE       (&gHost_psilcfgRegs)
#define UDMA_NAVSS0_UDMASS_PSILCFG0_CFG_PROXY_BASE          (&gHost_psilcfgRegs)

#define UDMA_MCU_NAVSS0_UDMASS_INTA0_CFG_BASE               (&gHost_intaggr_cfgRegs )
#define UDMA_MCU_NAVSS0_UDMASS_INTA0_IMAP_BASE              (&gHost_intaggr_imapRegs)
#define UDMA_MCU_NAVSS0_UDMASS_INTA0_INTR_BASE              (&gHost_intaggr_intrRegs)
#define UDMA_MCU_NAVSS0_PAR_UDMASS_UDMASS_INTA0_CFG_L2G_BASE    (&gHost_intaggr_l2gRegs)
#define UDMA_MCU_NAVSS0_UDMASS_INTA0_MCAST_BASE             (&gHost_intaggr_mcastRegs)
#define UDMA_MCU_NAVSS0_UDMASS_INTA0_GCNT_BASE              (&gHost_intaggr_gcntcfgRegs)
#define UDMA_MCU_NAVSS0_UDMASS_INTA0_GCNTRTI_BASE           (&gHost_intaggr_gcntrtiRegs)

#define UDMA_MCU_NAVSS0_INTR0_CFG_BASE                      (&gHost_intr_router_cfgRegs)

#define UDMA_NAVSS0_UDMASS_INTA0_CFG_BASE                   (&gHost_intaggr_cfgRegs )
#define UDMA_NAVSS0_UDMASS_INTA0_IMAP_BASE                  (&gHost_intaggr_imapRegs)
#define UDMA_NAVSS0_UDMASS_INTA0_CFG_INTR_BASE              (&gHost_intaggr_intrRegs)
#define UDMA_NAVSS0_UDMASS_INTA0_CFG_L2G_BASE               (&gHost_intaggr_l2gRegs)
#define UDMA_NAVSS0_UDMASS_INTA0_CFG_MCAST_BASE             (&gHost_intaggr_mcastRegs)
#define UDMA_NAVSS0_UDMASS_INTA0_CFG_GCNTCFG_BASE           (&gHost_intaggr_gcntcfgRegs)
#define UDMA_NAVSS0_UDMASS_INTA0_CFG_GCNTRTI_BASE           (&gHost_intaggr_gcntrtiRegs)
#define UDMA_NAVSS0_UDMASS_INTA0_CFG_UNMAP_BASE             (&gHost_intaggr_unmapRegs)

#define UDMA_NAVSS0_INTR0_INTR_ROUTER_CFG_BASE              (&gHost_intr_router_cfgRegs)

/** \brief DRU0 UTC baseaddress */
#define UDMA_UTC_BASE_DRU0              (&gHost_DRU_t0)
#define UDMA_UTC_BASE_DRU4              (&gHost_DRU_t4)
#define UDMA_UTC_BASE_DRU5              (&gHost_DRU_t5)
#define UDMA_UTC_BASE_DRU6              (&gHost_DRU_t6)
#define UDMA_UTC_BASE_DRU7              (&gHost_DRU_t7)
#define UDMA_COMPUTE_CLUSTER0_CLEC_REGS_BASE (&gHost_clec_evtRegs)

#else

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

#define UDMA_NAVSS0_BCDMA0_CFG_GCFG_BASE                        (CSL_NAVSS0_BCDMA0_CFG_GCFG_BASE)
#define UDMA_NAVSS0_BCDMA0_CFG_TCHAN_BASE                       (CSL_NAVSS0_BCDMA0_CFG_TCHAN_BASE)
#define UDMA_NAVSS0_BCDMA0_CFG_RCHAN_BASE                       (CSL_NAVSS0_BCDMA0_CFG_RCHAN_BASE)
#define UDMA_NAVSS0_BCDMA0_CFG_TCHANRT_BASE                     (CSL_NAVSS0_BCDMA0_CFG_TCHANRT_BASE)
#define UDMA_NAVSS0_BCDMA0_CFG_RCHANRT_BASE                     (CSL_NAVSS0_BCDMA0_CFG_RCHANRT_BASE)

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

#define UDMA_NAVSS0_BCDMA0_CFG_RING_BASE                        (CSL_NAVSS0_BCDMA0_CFG_RING_BASE)
#define UDMA_NAVSS0_BCDMA0_CFG_RINGRT_BASE                      (CSL_NAVSS0_BCDMA0_CFG_RINGRT_BASE)
#define UDMA_NAVSS0_CRED_BASE                                   (CSL_NAVSS0_CRED_BASE)

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
#define UDMA_NAVSS0_UDMASS_INTA0_CFG_UNMAP_BASE                 (CSL_NAVSS0_UDMASS_INTA0_CFG_UNMAP_BASE)

#define UDMA_NAVSS0_INTR0_INTR_ROUTER_CFG_BASE                  (CSL_NAVSS0_INTR0_INTR_ROUTER_CFG_BASE)
/** \brief DRU0 UTC baseaddress */
/* CSL_COMPUTE_CLUSTER0_DRU0_FW_BASE flag inconsistency */
#define UDMA_UTC_BASE_DRU0                                      (CSL_COMPUTE_CLUSTER0_MMR_DRU0_MMR_CFG_DRU_BASE)
#define UDMA_UTC_BASE_DRU4                                      (CSL_COMPUTE_CLUSTER0_MMR_DRU4_MMR_CFG_DRU_BASE)
#define UDMA_UTC_BASE_DRU5                                      (CSL_COMPUTE_CLUSTER0_MMR_DRU5_MMR_CFG_DRU_BASE)
#define UDMA_UTC_BASE_DRU6                                      (CSL_COMPUTE_CLUSTER0_MMR_DRU6_MMR_CFG_DRU_BASE)
#define UDMA_UTC_BASE_DRU7                                      (CSL_COMPUTE_CLUSTER0_MMR_DRU7_MMR_CFG_DRU_BASE)
/* CSL_COMPUTE_CLUSTER0_DRU0_FW_BASE flag inconsistency */                                    
#define UDMA_COMPUTE_CLUSTER0_CLEC_REGS_BASE                    (CSL_COMPUTE_CLUSTER0_CLEC_REGS_BASE)
#endif
/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void Udma_initDrvHandle(Udma_DrvHandle drvHandle)
{
    uint32_t                instId;
    CSL_UdmapCfg            *pUdmapRegs;
    CSL_BcdmaCfg            *pBcdmaRegs;
    CSL_RingAccCfg          *pRaRegs;
    CSL_LcdmaRingaccCfg     *pLcdmaRaRegs; 
    CSL_IntaggrCfg          *pIaRegs;
    Udma_UtcInstInfo        *utcInfo;
    CSL_ProxyCfg            *pProxyCfg;
    CSL_ProxyTargetParams   *pProxyTargetRing;

    instId = drvHandle->initPrms.instId;
    
/* Host Emulation not verified for j721s2 */
#if defined (HOST_EMULATION)
    gHost_udmap_gcfgRegs.CAP0 = 0x000B800F;
    gHost_udmap_gcfgRegs.CAP1 = 0;
    gHost_udmap_gcfgRegs.CAP2 = 0x02584078;
    gHost_udmap_gcfgRegs.CAP3 = 0x0000012C;

    gHost_intaggr_cfgRegs.INTCAP  = 0x0000000001001200;
    gHost_intaggr_cfgRegs.AUXCAP = 0x0000020000040200;
#endif

    /*
     * UDMA config init
     */
    /* Init the config structure - one time step */
    if(UDMA_INST_ID_BCDMA_0 == instId)
    {
        drvHandle->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
        pBcdmaRegs = &drvHandle->bcdmaRegs;
#ifndef QNX_OS
        pBcdmaRegs->pGenCfgRegs     = ((CSL_bcdma_gcfgRegs *) UDMA_NAVSS0_BCDMA0_CFG_GCFG_BASE);
        pBcdmaRegs->pTxChanCfgRegs  = ((CSL_bcdma_txccfgRegs *) UDMA_NAVSS0_BCDMA0_CFG_TCHAN_BASE);
        pBcdmaRegs->pRxChanCfgRegs  = ((CSL_bcdma_rxccfgRegs *) UDMA_NAVSS0_BCDMA0_CFG_RCHAN_BASE);
        pBcdmaRegs->pTxChanRtRegs   = ((CSL_bcdma_txcrtRegs *) UDMA_NAVSS0_BCDMA0_CFG_TCHANRT_BASE);
        pBcdmaRegs->pRxChanRtRegs   = ((CSL_bcdma_rxcrtRegs *) UDMA_NAVSS0_BCDMA0_CFG_RCHANRT_BASE);
#else
        pBcdmaRegs->pGenCfgRegs     = ((CSL_bcdma_gcfgRegs *) mmap_device_memory(0,
                CSL_NAVSS0_BCDMA0_CFG_GCFG_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_NAVSS0_BCDMA0_CFG_GCFG_BASE));
        pBcdmaRegs->pTxChanCfgRegs  = ((CSL_bcdma_txccfgRegs *) mmap_device_memory(0,
                CSL_NAVSS0_BCDMA0_CFG_TCHAN_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_NAVSS0_BCDMA0_CFG_TCHAN_BASE));
        pBcdmaRegs->pRxChanCfgRegs  = ((CSL_bcdma_rxccfgRegs *) mmap_device_memory(0,
                CSL_NAVSS0_BCDMA0_CFG_RCHAN_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_NAVSS0_BCDMA0_CFG_RCHAN_BASE));
        pBcdmaRegs->pTxChanRtRegs   = ((CSL_bcdma_txcrtRegs *) mmap_device_memory(0,
                CSL_NAVSS0_BCDMA0_CFG_TCHANRT_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_NAVSS0_BCDMA0_CFG_TCHANRT_BASE));
        pBcdmaRegs->pRxChanRtRegs   = ((CSL_bcdma_rxcrtRegs *) mmap_device_memory(0,
                CSL_NAVSS0_BCDMA0_CFG_RCHANRT_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_NAVSS0_BCDMA0_CFG_RCHANRT_BASE));
#endif
        drvHandle->trigGemOffset    = CSL_NAVSS_GEM_MAIN_BCDMA_TRIGGER_OFFSET;

        /* Fill other SOC specific parameters by reading from UDMA config
         * registers */
        CSL_bcdmaGetCfg(pBcdmaRegs);

        pUdmapRegs = &drvHandle->udmapRegs;
        memset(pUdmapRegs, 0, sizeof(*pUdmapRegs));
    }
    else 
    {
        drvHandle->instType = UDMA_INST_TYPE_NORMAL;

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
        else if(UDMA_INST_ID_MAIN_0 == instId)
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
        else
        {
            /* Do Nothing */
        }
        
        /* UDMA not present in CC QT build. Only DRU is present */
#ifndef CC_QT_BUILD
        /* Fill other SOC specific parameters by reading from UDMA config
        * registers */
        CSL_udmapGetCfg(pUdmapRegs);
#endif

        pBcdmaRegs = &drvHandle->bcdmaRegs;
        memset(pBcdmaRegs, 0, sizeof(*pBcdmaRegs));
    }
#ifndef QNX_OS
    drvHandle->clecRegs = (CSL_CLEC_EVTRegs *) UDMA_COMPUTE_CLUSTER0_CLEC_REGS_BASE;
#else
    drvHandle->clecRegs = (CSL_CLEC_EVTRegs *) mmap_device_memory(0,
            CSL_COMPUTE_CLUSTER0_CLEC_REGS_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_COMPUTE_CLUSTER0_CLEC_REGS_BASE);
#ifdef QNX_UDMA_DEBUG_CSL_REGS
    printf( "%s: clecRegs phys/0x%lx virt/0x%p size/%ld\n",__FUNCTION__,
            UDMA_COMPUTE_CLUSTER0_CLEC_REGS_BASE, drvHandle->clecRegs, CSL_COMPUTE_CLUSTER0_CLEC_REGS_SIZE);
#endif
#endif
    /*
     * RA config init
     */
    if(UDMA_INST_ID_BCDMA_0 == instId)
    {
        drvHandle->raType = UDMA_RA_TYPE_LCDMA;

        pLcdmaRaRegs = &drvHandle->lcdmaRaRegs;

#ifndef QNX_OS
        pLcdmaRaRegs->pRingCfgRegs   = (CSL_lcdma_ringacc_ring_cfgRegs *) UDMA_NAVSS0_BCDMA0_CFG_RING_BASE;
        pLcdmaRaRegs->pRingRtRegs    = (CSL_lcdma_ringacc_ringrtRegs *) UDMA_NAVSS0_BCDMA0_CFG_RINGRT_BASE;
        pLcdmaRaRegs->pCredRegs      = (CSL_lcdma_ringacc_credRegs *) UDMA_NAVSS0_CRED_BASE;
#else
        pLcdmaRaRegs->pRingCfgRegs = (CSL_lcdma_ringacc_ring_cfgRegs *) mmap_device_memory(0,
            CSL_NAVSS0_BCDMA0_CFG_RING_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_NAVSS0_BCDMA0_CFG_RING_BASE);
        pLcdmaRaRegs->pRingRtRegs = (CSL_lcdma_ringacc_ringrtRegs *) mmap_device_memory(0,
            CSL_NAVSS0_BCDMA0_CFG_RINGRT_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_NAVSS0_BCDMA0_CFG_RINGRT_BASE);
        pLcdmaRaRegs->pCredRegs = (CSL_lcdma_ringacc_credRegs *) mmap_device_memory(0,
            CSL_NAVSS0_CRED_SIZE, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, UDMA_NAVSS0_CRED_BASE);
#endif
        pLcdmaRaRegs->maxRings       = CSL_NAVSS_BCDMA_NUM_BC_CHANS + CSL_NAVSS_BCDMA_NUM_TX_CHANS + CSL_NAVSS_BCDMA_NUM_RX_CHANS;

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

        pRaRegs = &drvHandle->raRegs;
        memset(pRaRegs, 0 , sizeof(*pRaRegs));
    }
    else 
    {
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
        else if(UDMA_INST_ID_MAIN_0 == instId)
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
        else
        {
           /* Do Nothing */
        }

        pRaRegs->maxMonitors     = CSL_RINGACC_MAX_MONITORS;
        pRaRegs->bTraceSupported = BTRUE;

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

        pLcdmaRaRegs = &drvHandle->lcdmaRaRegs;
        memset(pLcdmaRaRegs, 0 , sizeof(*pLcdmaRaRegs));
    }

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

    drvHandle->devIdIa      = TISCI_DEV_MCU_NAVSS0_UDMASS_INTA_0;
    drvHandle->devIdIr      = TISCI_DEV_MCU_NAVSS0_INTR_ROUTER_0;
#if defined (BUILD_MCU1_0)
    drvHandle->druCoreId    = UDMA_DRU_CORE_ID_MCU1_0;
#else
    drvHandle->druCoreId    = UDMA_DRU_CORE_ID_MCU1_1;
#endif
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
    /* UDMA not present in CC QT build. Only DRU is present */
#ifndef CC_QT_BUILD
    CSL_intaggrGetCfg(pIaRegs);
#endif

    drvHandle->devIdIa      = TISCI_DEV_NAVSS0_UDMASS_INTA_0;
    drvHandle->devIdIr      = TISCI_DEV_NAVSS0_INTR_0;
    drvHandle->clecRtMap    = CSL_CLEC_RTMAP_DISABLE;
    drvHandle->clecOffset   = 0U;
#if defined (BUILD_MPU1_0)
    drvHandle->druCoreId    = UDMA_DRU_CORE_ID_MPU1_0;
#endif
#if defined (BUILD_MCU2_0)
    drvHandle->druCoreId    = UDMA_DRU_CORE_ID_MCU2_0;
#endif
#if defined (BUILD_MCU2_1)
    drvHandle->druCoreId    = UDMA_DRU_CORE_ID_MCU2_1;
#endif
#if defined (BUILD_MCU3_0)
    drvHandle->druCoreId    = UDMA_DRU_CORE_ID_MCU3_0;
#endif
#if defined (BUILD_MCU3_1)
    drvHandle->druCoreId    = UDMA_DRU_CORE_ID_MCU3_1;
#endif
#if defined (BUILD_MCU4_0)
    drvHandle->druCoreId    = UDMA_DRU_CORE_ID_MCU4_0;
#endif
#if defined (BUILD_MCU4_1)
    drvHandle->druCoreId    = UDMA_DRU_CORE_ID_MCU4_1;
#endif
#if defined (BUILD_C7X_1)
    drvHandle->druCoreId    = UDMA_DRU_CORE_ID_C7X_1;
    drvHandle->clecRtMap    = CSL_CLEC_RTMAP_CPU_4; /* CPU4 is C7x_1 in J784S4 */
    /* CLEC interrupt number 1024 is connected to GIC interrupt number 32 in J784S4.
     * Due to this for CLEC programming one needs to add an offset of 992 (1024 - 32)
     * to the event number which is shared between GIC and CLEC. */
    drvHandle->clecOffset   = 1024U - 32U;
#endif
#if defined (BUILD_C7X_2)
    drvHandle->druCoreId    = UDMA_DRU_CORE_ID_C7X_2;
    drvHandle->clecRtMap    = CSL_CLEC_RTMAP_CPU_5; /* CPU5 is C7x_2 in J784S4 */
    /* CLEC interrupt number 1024 is connected to GIC interrupt number 32 in J784S4.
     * Due to this for CLEC programming one needs to add an offset of 992 (1024 - 32)
     * to the event number which is shared between GIC and CLEC. */
    drvHandle->clecOffset   = 1024U - 32U;
#endif
#if defined (BUILD_C7X_3)
    drvHandle->druCoreId    = UDMA_DRU_CORE_ID_C7X_3;
    drvHandle->clecRtMap    = CSL_CLEC_RTMAP_CPU_6; /* CPU4 is C7x_1 in J784S4 */
    /* CLEC interrupt number 1024 is connected to GIC interrupt number 32 in J784S4.
     * Due to this for CLEC programming one needs to add an offset of 992 (1024 - 32)
     * to the event number which is shared between GIC and CLEC. */
    drvHandle->clecOffset   = 1024U - 32U;
#endif
#if defined (BUILD_C7X_4)
    drvHandle->druCoreId    = UDMA_DRU_CORE_ID_C7X_4;
    drvHandle->clecRtMap    = CSL_CLEC_RTMAP_CPU_7; /* CPU5 is C7x_2 in J784S4 */
    /* CLEC interrupt number 1024 is connected to GIC interrupt number 32 in J784S4.
     * Due to this for CLEC programming one needs to add an offset of 992 (1024 - 32)
     * to the event number which is shared between GIC and CLEC. */
    drvHandle->clecOffset   = 1024U - 32U;
#endif
#endif
    if(UDMA_INST_ID_BCDMA_0 == instId)
    {
        /* Set NAVSS Interrupt Aggregator Unmapped Event Register base address (used for BCDMA events) */
        pIaRegs->pUnmapRegs   = (CSL_intaggr_unmapRegs *) UDMA_NAVSS0_UDMASS_INTA0_CFG_UNMAP_BASE;
    }


    drvHandle->devIdCore    = Udma_getCoreSciDevId();
    drvHandle->iaGemOffset  = Udma_getGlobalEventOffset();

    /*
     * UTC config init
     */
    /* Each UTC config */
    utcInfo = &drvHandle->utcInfo[UDMA_UTC_ID_MSMC_DRU0];
    utcInfo->utcId         = UDMA_UTC_ID_MSMC_DRU0;
    utcInfo->utcType       = UDMA_UTC_TYPE_DRU;
    utcInfo->startCh       = UDMA_UTC_START_CH_DRU0;
    utcInfo->numCh         = UDMA_UTC_NUM_CH_DRU0;
    utcInfo->startThreadId = UDMA_UTC_START_THREAD_ID_DRU0;
    utcInfo->txCredit      = 2U;
    utcInfo->druRegs       = ((CSL_DRU_t *) UDMA_UTC_BASE_DRU0);
    utcInfo->numQueue      = CSL_NAVSS_UTC_MSMC_DRU_QUEUE_CNT;

#if defined (BUILD_C7X)
    utcInfo = &drvHandle->utcInfo[UDMA_UTC_ID_C7X_MSMC_DRU4];
    utcInfo->utcId         = UDMA_UTC_ID_C7X_MSMC_DRU4;
    utcInfo->utcType       = UDMA_UTC_TYPE_DRU;
    utcInfo->startCh       = UDMA_UTC_START_CH_DRU4;
    utcInfo->numCh         = UDMA_UTC_NUM_CH_DRU4;
    utcInfo->startThreadId = UDMA_THREAD_ID_INVALID;
    utcInfo->txCredit      = 2U;
    utcInfo->druRegs       = ((CSL_DRU_t *) UDMA_UTC_BASE_DRU4);
    utcInfo->numQueue      = CSL_NAVSS_UTC_MSMC_DRU4_QUEUE_CNT;

    utcInfo = &drvHandle->utcInfo[UDMA_UTC_ID_C7X_MSMC_DRU5];
    utcInfo->utcId         = UDMA_UTC_ID_C7X_MSMC_DRU5;
    utcInfo->utcType       = UDMA_UTC_TYPE_DRU;
    utcInfo->startCh       = UDMA_UTC_START_CH_DRU5;
    utcInfo->numCh         = UDMA_UTC_NUM_CH_DRU5;
    utcInfo->startThreadId = UDMA_THREAD_ID_INVALID;
    utcInfo->txCredit      = 2U;
    utcInfo->druRegs       = ((CSL_DRU_t *) UDMA_UTC_BASE_DRU5);
    utcInfo->numQueue      = CSL_NAVSS_UTC_MSMC_DRU5_QUEUE_CNT;

    utcInfo = &drvHandle->utcInfo[UDMA_UTC_ID_C7X_MSMC_DRU6];
    utcInfo->utcId         = UDMA_UTC_ID_C7X_MSMC_DRU6;
    utcInfo->utcType       = UDMA_UTC_TYPE_DRU;
    utcInfo->startCh       = UDMA_UTC_START_CH_DRU6;
    utcInfo->numCh         = UDMA_UTC_NUM_CH_DRU6;
    utcInfo->startThreadId = UDMA_THREAD_ID_INVALID;
    utcInfo->txCredit      = 2U;
    utcInfo->druRegs       = ((CSL_DRU_t *) UDMA_UTC_BASE_DRU6);
    utcInfo->numQueue      = CSL_NAVSS_UTC_MSMC_DRU6_QUEUE_CNT;

    utcInfo = &drvHandle->utcInfo[UDMA_UTC_ID_C7X_MSMC_DRU7];
    utcInfo->utcId         = UDMA_UTC_ID_C7X_MSMC_DRU7;
    utcInfo->utcType       = UDMA_UTC_TYPE_DRU;
    utcInfo->startCh       = UDMA_UTC_START_CH_DRU7;
    utcInfo->numCh         = UDMA_UTC_NUM_CH_DRU7;
    utcInfo->startThreadId = UDMA_THREAD_ID_INVALID;
    utcInfo->txCredit      = 2U;
    utcInfo->druRegs       = ((CSL_DRU_t *) UDMA_UTC_BASE_DRU7);
    utcInfo->numQueue      = CSL_NAVSS_UTC_MSMC_DRU7_QUEUE_CNT;
#else
    /* These DRUs are local to C7X cores cannot be used by other cores */
    utcInfo = &drvHandle->utcInfo[UDMA_UTC_ID_C7X_MSMC_DRU4];
    utcInfo->utcId         = UDMA_UTC_ID_INVALID;

    utcInfo = &drvHandle->utcInfo[UDMA_UTC_ID_C7X_MSMC_DRU5];
    utcInfo->utcId         = UDMA_UTC_ID_INVALID;

    utcInfo = &drvHandle->utcInfo[UDMA_UTC_ID_C7X_MSMC_DRU6];
    utcInfo->utcId         = UDMA_UTC_ID_INVALID;

    utcInfo = &drvHandle->utcInfo[UDMA_UTC_ID_C7X_MSMC_DRU7];
    utcInfo->utcId         = UDMA_UTC_ID_INVALID;
#endif

    utcInfo = &drvHandle->utcInfo[UDMA_UTC_ID_VPAC_TC0];
    utcInfo->utcId         = UDMA_UTC_ID_VPAC_TC0;
    utcInfo->utcType       = UDMA_UTC_TYPE_DRU_VHWA;
    utcInfo->startCh       = UDMA_UTC_START_CH_VPAC_TC0;
    utcInfo->numCh         = UDMA_UTC_NUM_CH_VPAC_TC0;
    utcInfo->startThreadId = UDMA_UTC_START_THREAD_ID_VPAC_TC0;
    utcInfo->txCredit      = 3U;
    utcInfo->druRegs       = ((CSL_DRU_t *) CSL_VPAC0_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_BASE);
    utcInfo->numQueue      = CSL_NAVSS_UTC_VPAC_TC0_QUEUE_CNT;

    utcInfo = &drvHandle->utcInfo[UDMA_UTC_ID_VPAC_TC1];
    utcInfo->utcId         = UDMA_UTC_ID_VPAC_TC1;
    utcInfo->utcType       = UDMA_UTC_TYPE_DRU_VHWA;
    utcInfo->startCh       = UDMA_UTC_START_CH_VPAC_TC1;
    utcInfo->numCh         = UDMA_UTC_NUM_CH_VPAC_TC1;
    utcInfo->startThreadId = UDMA_UTC_START_THREAD_ID_VPAC_TC1;
    utcInfo->txCredit      = 3U;
    utcInfo->druRegs       = ((CSL_DRU_t *) CSL_VPAC0_DRU_UTC_VPAC1_DRU_MMR_CFG_DRU_DRU_BASE);
    utcInfo->numQueue      = CSL_NAVSS_UTC_VPAC_TC1_QUEUE_CNT;

    utcInfo = &drvHandle->utcInfo[UDMA_UTC_ID_VPAC1_TC0];
    utcInfo->utcId         = UDMA_UTC_ID_VPAC1_TC0;
    utcInfo->utcType       = UDMA_UTC_TYPE_DRU_VHWA;
    utcInfo->startCh       = UDMA_UTC_START_CH_VPAC1_TC0;
    utcInfo->numCh         = UDMA_UTC_NUM_CH_VPAC1_TC0;
    utcInfo->startThreadId = UDMA_UTC_START_THREAD_ID_VPAC1_TC0;
    utcInfo->txCredit      = 3U;
    utcInfo->druRegs       = ((CSL_DRU_t *) CSL_VPAC1_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_BASE);
    utcInfo->numQueue      = CSL_NAVSS_UTC_VPAC1_TC0_QUEUE_CNT;

    utcInfo = &drvHandle->utcInfo[UDMA_UTC_ID_VPAC1_TC1];
    utcInfo->utcId         = UDMA_UTC_ID_VPAC1_TC1;
    utcInfo->utcType       = UDMA_UTC_TYPE_DRU_VHWA;
    utcInfo->startCh       = UDMA_UTC_START_CH_VPAC1_TC1;
    utcInfo->numCh         = UDMA_UTC_NUM_CH_VPAC1_TC1;
    utcInfo->startThreadId = UDMA_UTC_START_THREAD_ID_VPAC1_TC1;
    utcInfo->txCredit      = 3U;
    utcInfo->druRegs       = ((CSL_DRU_t *) CSL_VPAC1_DRU_UTC_VPAC1_DRU_MMR_CFG_DRU_DRU_BASE);
    utcInfo->numQueue      = CSL_NAVSS_UTC_VPAC1_TC1_QUEUE_CNT;

    utcInfo = &drvHandle->utcInfo[UDMA_UTC_ID_DMPAC_TC0];
    utcInfo->utcId         = UDMA_UTC_ID_DMPAC_TC0;
    utcInfo->utcType       = UDMA_UTC_TYPE_DRU_VHWA;
    utcInfo->startCh       = UDMA_UTC_START_CH_DMPAC_TC0;
    utcInfo->numCh         = UDMA_UTC_NUM_CH_DMPAC_TC0;
    utcInfo->startThreadId = UDMA_UTC_START_THREAD_ID_DMPAC_TC0;
    utcInfo->txCredit      = 3U;
    utcInfo->druRegs       = ((CSL_DRU_t *) CSL_DMPAC0_DRU_UTC_DMPAC0_DRU_MMR_CFG_DRU_DRU_BASE);
    utcInfo->numQueue      = CSL_NAVSS_UTC_DMPAC_QUEUE_CNT;

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
    else if(UDMA_INST_ID_MAIN_0 == instId)
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
    else
    {
        /* Since BCDMA does not use proxy setting proxy paramenters to NULL */
        memset(pProxyCfg, 0, sizeof(*pProxyCfg));
        memset(pProxyTargetRing, 0, sizeof(*pProxyTargetRing));
        drvHandle->proxyTargetNumRing = 0U;
    }

    /* Init other variables */
    if(UDMA_INST_ID_BCDMA_0 == instId)
    {
        drvHandle->txChOffset           = pBcdmaRegs->bcChanCnt;
        drvHandle->rxChOffset           = drvHandle->txChOffset + pBcdmaRegs->splitTxChanCnt;
       /* The srcIdx passed to Sciclient_rmIrqset API for configuring DMA Completion/Ring events, 
        * will be ringNum + the corresponding following offset. 
        * So setting the offset as TISCI Start Idx - corresponding ringNum Offset (if any) */
        drvHandle->blkCopyRingIrqOffset = TISCI_BCDMA0_BC_RC_OES_IRQ_SRC_IDX_START;
        drvHandle->txRingIrqOffset      = (uint16_t)(TISCI_BCDMA0_TX_RC_OES_IRQ_SRC_IDX_START - drvHandle->txChOffset);
        drvHandle->rxRingIrqOffset      = (uint16_t)(TISCI_BCDMA0_RX_RC_OES_IRQ_SRC_IDX_START - drvHandle->rxChOffset);
        drvHandle->udmapSrcThreadOffset = CSL_PSILCFG_NAVSS_MAIN_BCDMA0_STRM_PSILS_THREAD_OFFSET;
        drvHandle->udmapDestThreadOffset= CSL_PSILCFG_NAVSS_MAIN_BCDMA0_STRM_PSILD_THREAD_OFFSET;
        drvHandle->maxRings             = CSL_NAVSS_BCDMA_NUM_BC_CHANS + CSL_NAVSS_BCDMA_NUM_TX_CHANS + CSL_NAVSS_BCDMA_NUM_RX_CHANS;
        drvHandle->devIdRing            = TISCI_DEV_NAVSS0_BCDMA_0;
        drvHandle->devIdUdma            = TISCI_DEV_NAVSS0_BCDMA_0;
       /* The srcIdx passed to Sciclient_rmIrqset API for configuring TR events, 
        * will be chNum + the corresponding following offset. 
        * So setting the offset as TISCI Start Idx - corresponding chNum Offset (if any) */
        drvHandle->srcIdTrIrq           = TISCI_DEV_NAVSS0_UDMASS_INTA_0;
        drvHandle->blkCopyTrIrqOffset   = TISCI_BCDMA0_BC_DC_OES_IRQ_SRC_IDX_START;
        drvHandle->txTrIrqOffset        = TISCI_BCDMA0_TX_DC_OES_IRQ_SRC_IDX_START;
        drvHandle->rxTrIrqOffset        = TISCI_BCDMA0_RX_DC_OES_IRQ_SRC_IDX_START;
        drvHandle->devIdPsil            = TISCI_DEV_NAVSS0; 
        drvHandle->maxProxy             = 0U; 
        drvHandle->maxRingMon           = 0U;
        drvHandle->extChOffset          = 0U;
        drvHandle->srcIdRingIrq         = TISCI_DEV_NAVSS0_UDMASS_INTA_0;
    }
    else
    {
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
        /* `TISCI_DEV_NAVSS0_TIMERMGR_0` is a part of IA Event Sources and does not contain any OES registers */
        drvHandle->devIdDummyEvtSrc      = TISCI_DEV_NAVSS0_TIMERMGR_0;
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
    }

    return;
}

uint32_t Udma_getGlobalEventOffset(void)
{
    uint32_t globalEventOffset = 0U;

    /* Global Events(SEVI) Offset - Tied to cores and not based on NAVSS instance */
#if defined (BUILD_MCU1_0) || defined (BUILD_MCU1_1)
    globalEventOffset = CSL_NAVSS_GEM_MCU_UDMA_INTA0_SEVI_OFFSET;
#else
    globalEventOffset = CSL_NAVSS_GEM_MAIN_UDMA_INTA0_SEVI_OFFSET;
#endif

    return (globalEventOffset);
}

uint32_t Udma_getCoreId(void)
{
    uint32_t coreId = UDMA_CORE_ID_INVALID;

#if defined (BUILD_MPU1_0)
    coreId = UDMA_CORE_ID_MPU1_0;
#endif
#if defined (BUILD_MCU2_0)
    coreId = UDMA_CORE_ID_MCU2_0;
#endif
#if defined (BUILD_MCU2_1)
    coreId = UDMA_CORE_ID_MCU2_1;
#endif
#if defined (BUILD_MCU3_0)
    coreId = UDMA_CORE_ID_MCU3_0;
#endif
#if defined (BUILD_MCU3_1)
    coreId = UDMA_CORE_ID_MCU3_1;
#endif
#if defined (BUILD_MCU4_0)
    coreId = UDMA_CORE_ID_MCU4_0;
#endif
#if defined (BUILD_MCU4_1)
    coreId = UDMA_CORE_ID_MCU4_1;
#endif
#if defined (BUILD_C7X_1)
    coreId = UDMA_CORE_ID_C7X_1;
#endif
#if defined (BUILD_C7X_2)
    coreId = UDMA_CORE_ID_C7X_2;
#endif
#if defined (BUILD_C7X_3)
    coreId = UDMA_CORE_ID_C7X_3;
#endif
#if defined (BUILD_C7X_4)
    coreId = UDMA_CORE_ID_C7X_4;
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
    uint16_t coreSciDevId = 0U;

#if defined (BUILD_MPU1_0)
    coreSciDevId = TISCI_DEV_COMPUTE_CLUSTER0_GIC500SS;
#endif
#if defined (BUILD_MCU2_0)
    coreSciDevId = TISCI_DEV_R5FSS0_CORE0;
#endif
#if defined (BUILD_MCU2_1)
    coreSciDevId = TISCI_DEV_R5FSS0_CORE1;
#endif
#if defined (BUILD_MCU3_0)
    coreSciDevId = TISCI_DEV_R5FSS1_CORE0;
#endif
#if defined (BUILD_MCU3_1)
    coreSciDevId = TISCI_DEV_R5FSS1_CORE1;
#endif
#if defined (BUILD_MCU4_0)
    coreSciDevId = TISCI_DEV_R5FSS2_CORE0;
#endif
#if defined (BUILD_MCU4_1)
    coreSciDevId = TISCI_DEV_R5FSS2_CORE1;
#endif
/* On J784S4 all the c7x cores interrupts are handled by clec */
#if defined (BUILD_C7X_1)
    coreSciDevId = TISCI_DEV_COMPUTE_CLUSTER0_CLEC;
#endif
#if defined (BUILD_C7X_2)
    coreSciDevId = TISCI_DEV_COMPUTE_CLUSTER0_CLEC;
#endif
#if defined (BUILD_C7X_3)
    coreSciDevId = TISCI_DEV_COMPUTE_CLUSTER0_CLEC;
#endif
#if defined (BUILD_C7X_4)
    coreSciDevId = TISCI_DEV_COMPUTE_CLUSTER0_CLEC;
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
    isCacheCoherent = UTRUE;
#else
    isCacheCoherent = UFALSE;
#endif

    return (isCacheCoherent);
}
