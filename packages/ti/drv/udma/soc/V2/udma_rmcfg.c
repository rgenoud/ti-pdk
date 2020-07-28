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
 *  \file udma_rmcfg.c
 *
 *  \brief File containing the UDMA driver default RM configuration used to
 *  initialize the RM init parameters passed during driver init.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/udma/src/udma_priv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* TODO: Replace when CSLR is ready */
#define UDMA_MAIN_NAVSS0_EVENT_CNT      (4608U)
#define UDMA_MAIN_NAVSS0_VINTR_CNT      (256U)
#define UDMA_MCU_NAVSS0_EVENT_CNT       (1536U)
#define UDMA_MCU_NAVSS0_VINTR_CNT       (256U)

/* Block copy needs to be checked against BC_HC/BC_UHC, TX/TX_HC/TX_UHC and
 * RX/RX_HC/RX_UHC. Hence need six sets to compare */
#define UDMA_RM_CHECK_MAX_ENTRY         (UDMA_NUM_CORE * 6U)
/* This is an assumption and should the max of all resource count across cores */
#define UDMA_RM_CHECK_MAX_WORDS         (150U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief UDMA instance RM check parameters - local defined for passing
 *  multiple parameters to check function.
 */
typedef struct
{
    uint32_t                numCores;
    uint32_t                startCoreId;
    uint32_t                maxTxCh;
    uint32_t                maxRxCh;
    uint32_t                maxUtcCh;
    uint32_t                maxFreeRing;
    uint32_t                maxFreeFlow;
    uint32_t                maxEvents;
    uint32_t                maxVintr;
    uint32_t                maxProxy;
    uint32_t                maxRingMon;
    const Udma_RmInitPrms  *selfCfg;
    const Udma_RmInitPrms  *crossCfg;
} Udma_RmInstCheckPrms;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static int32_t Udma_rmCheckInstOverlap(const Udma_RmInstCheckPrms *prms);
static int32_t Udma_rmCheckOverlap(uint32_t startRes[UDMA_RM_CHECK_MAX_ENTRY],
                                   uint32_t numRes[UDMA_RM_CHECK_MAX_ENTRY],
                                   uint32_t numEntries,
                                   uint32_t maxRes);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* This assumes all resources are equally split across cores.
 * Once RM is aligned across usecases, this will be fixed to reflect that */
/** \brief Main Navss default configuration */
const Udma_RmInitPrms gUdmaRmDefCfg_MainNavss[UDMA_NUM_CORE] =
{
    /* MPU1_0 */
    {
        0U,                                         /* startBlkCopyUhcCh */
        0U,                                         /* numBlkCopyUhcCh */
        0U,                                         /* startBlkCopyHcCh */
        0U,                                         /* numBlkCopyHcCh */
        4U,                                         /* startBlkCopyCh */
        4U,                                         /* numBlkCopyCh */

        0U,                                         /* startTxUhcCh */
        0U,                                         /* numTxUhcCh */
        0U,                                         /* startTxHcCh */
        0U,                                         /* numTxHcCh */
        18U,                                        /* startTxCh */
        20U,                                        /* numTxCh */

        0U,                                         /* startRxUhcCh */
        0U,                                         /* numRxUhcCh */
        0U,                                         /* startRxHcCh */
        0U,                                         /* numRxHcCh */
        18U,                                        /* startRxCh */
        20U,                                        /* numRxCh */

#if (UDMA_NUM_UTC_INSTANCE > 0)
        {0U, 0U, 0U, 0U},                           /* startUtcCh[] */
        {0U, 0U, 0U, 0U},                           /* numUtcCh[] */
#endif

        60U,                                        /* startFreeFlow */
        8U,                                         /* numFreeFlow */
        120U,                                       /* startFreeRing */
        200U,                                       /* numFreeRing */

        18U,                                        /* startGlobalEvent */
        974U,                                       /* numGlobalEvent */
        18U,                                        /* startVintr */
        82U,                                        /* numVintr */
        84U,                                        /* startIrIntr */
        20U,                                        /* numIrIntr */

        0U,                                         /* proxyThreadNum */
        0U,                                         /* startC7xCoreIntr */

        1U,                                         /* startProxy */
        3U,                                         /* numProxy */

        0U,                                         /* startRingMon */
        3U,                                         /* numRingMon */
    },
    /* MCU2_0 */
    {
        0U,                                         /* startBlkCopyUhcCh */
        0U,                                         /* numBlkCopyUhcCh */
        0U,                                         /* startBlkCopyHcCh */
        0U,                                         /* numBlkCopyHcCh */
        14U,                                        /* startBlkCopyCh */
        2U,                                         /* numBlkCopyCh */

        0U,                                         /* startTxUhcCh */
        0U,                                         /* numTxUhcCh */
        2U,                                         /* startTxHcCh */
        2U,                                         /* numTxHcCh */
        42U,                                        /* startTxCh */
        8U,                                         /* numTxCh */

        0U,                                         /* startRxUhcCh */
        0U,                                         /* numRxUhcCh */
        2U,                                         /* startRxHcCh */
        2U,                                         /* numRxHcCh */
        42U,                                        /* startRxCh */
        8U,                                         /* numRxCh */

#if (UDMA_NUM_UTC_INSTANCE > 0)
        {0U, 0U, 0U, 0U},                           /* startUtcCh[] */
        {0U, 0U, 0U, 0U},                           /* numUtcCh[] */
#endif

        84U,                                        /* startFreeFlow */
        64U,                                        /* numFreeFlow */
        424U,                                       /* startFreeRing */
        256U,                                       /* numFreeRing */

        1810U,                                      /* startGlobalEvent */
        206U,                                       /* numGlobalEvent */
        168U,                                       /* startVintr */
        22U,                                        /* numVintr */
        228U,                                       /* startIrIntr */
        20U,                                        /* numIrIntr */

        16U,                                        /* proxyThreadNum */
        0U,                                         /* startC7xCoreIntr */

        17U,                                        /* startProxy */
        15U,                                        /* numProxy */

        7U,                                         /* startRingMon */
        16U,                                        /* numRingMon */
    },
    /* MCU2_1 */
    {
        0U,                                         /* startBlkCopyUhcCh */
        0U,                                         /* numBlkCopyUhcCh */
        0U,                                         /* startBlkCopyHcCh */
        0U,                                         /* numBlkCopyHcCh */
        16U,                                        /* startBlkCopyCh */
        2U,                                         /* numBlkCopyCh */

        0U,                                         /* startTxUhcCh */
        2U,                                         /* numTxUhcCh */
        0U,                                         /* startTxHcCh */
        0U,                                         /* numTxHcCh */
        50U,                                        /* startTxCh */
        8U,                                         /* numTxCh */

        0U,                                         /* startRxUhcCh */
        2U,                                         /* numRxUhcCh */
        0U,                                         /* startRxHcCh */
        0U,                                         /* numRxHcCh */
        50U,                                        /* startRxCh */
        8U,                                         /* numRxCh */

#if (UDMA_NUM_UTC_INSTANCE > 0)
        {0U, 0U, 0U, 0U},                           /* startUtcCh[] */
        {0U, 0U, 0U, 0U},                           /* numUtcCh[] */
#endif

        76U,                                        /* startFreeFlow */
        8U,                                         /* numFreeFlow */
        680U,                                       /* startFreeRing */
        256U,                                       /* numFreeRing */

        2066U,                                      /* startGlobalEvent */
        462U,                                       /* numGlobalEvent */
        200U,                                       /* startVintr */
        20U,                                        /* numVintr */
        228U,                                       /* startIrIntr */
        20U,                                        /* numIrIntr */

        32U,                                        /* proxyThreadNum */
        0U,                                         /* startC7xCoreIntr */

        33U,                                        /* startProxy */
        15U,                                        /* numProxy */

        23U,                                        /* startRingMon */
        8U,                                         /* numRingMon */
    },
    /* MCU1_0 */
    {
        0U,                                         /* startBlkCopyUhcCh */
        0U,                                         /* numBlkCopyUhcCh */
        0U,                                         /* startBlkCopyHcCh */
        0U,                                         /* numBlkCopyHcCh */
        10U,                                        /* startBlkCopyCh */
        2U,                                         /* numBlkCopyCh */

        0U,                                         /* startTxUhcCh */
        0U,                                         /* numTxUhcCh */
        0U,                                         /* startTxHcCh */
        0U,                                         /* numTxHcCh */
        0U,                                         /* startTxCh */
        0U,                                         /* numTxCh */

        0U,                                         /* startRxUhcCh */
        0U,                                         /* numRxUhcCh */
        0U,                                         /* startRxHcCh */
        0U,                                         /* numRxHcCh */
        0U,                                         /* startRxCh */
        0U,                                         /* numRxCh */

#if (UDMA_NUM_UTC_INSTANCE > 0)
        {0U, 0U, 0U, 0U},                           /* startUtcCh[] */
        {0U, 0U, 0U, 0U},                           /* numUtcCh[] */
#endif

        0U,                                         /* startFreeFlow */
        0U,                                         /* numFreeFlow */
        360U,                                       /* startFreeRing */
        32U,                                        /* numFreeRing */

        464U,                                       /* startGlobalEvent */
        56U,                                        /* numGlobalEvent */
        116U,                                       /* startVintr */
        4U,                                         /* numVintr */
        78U,                                        /* startIrIntr */
        4U,                                         /* numIrIntr */

        8U,                                         /* proxyThreadNum */
        0U,                                         /* startC7xCoreIntr */

        9U,                                         /* startProxy */
        3U,                                         /* numProxy */

        5U,                                         /* startRingMon */
        1U,                                         /* numRingMon */
    },
    /* MCU1_1 */
    {
        0U,                                         /* startBlkCopyUhcCh */
        0U,                                         /* numBlkCopyUhcCh */
        0U,                                         /* startBlkCopyHcCh */
        0U,                                         /* numBlkCopyHcCh */
        12U,                                        /* startBlkCopyCh */
        2U,                                         /* numBlkCopyCh */

        0U,                                         /* startTxUhcCh */
        0U,                                         /* numTxUhcCh */
        0U,                                         /* startTxHcCh */
        0U,                                         /* numTxHcCh */
        0U,                                         /* startTxCh */
        0U,                                         /* numTxCh */

        0U,                                         /* startRxUhcCh */
        0U,                                         /* numRxUhcCh */
        0U,                                         /* startRxHcCh */
        0U,                                         /* numRxHcCh */
        0U,                                         /* startRxCh */
        0U,                                         /* numRxCh */

#if (UDMA_NUM_UTC_INSTANCE > 0)
        {0U, 0U, 0U, 0U},                           /* startUtcCh[] */
        {0U, 0U, 0U, 0U},                           /* numUtcCh[] */
#endif

        0U,                                         /* startFreeFlow */
        0U,                                         /* numFreeFlow */
        392U,                                       /* startFreeRing */
        32U,                                         /* numFreeRing */

        616U,                                       /* startGlobalEvent */
        32U,                                        /* numGlobalEvent */
        148U,                                       /* startVintr */
        4U,                                         /* numVintr */
        78U,                                        /* startIrIntr */
        4U,                                         /* numIrIntr */

        12U,                                        /* proxyThreadNum */
        0U,                                         /* startC7xCoreIntr */

        13U,                                        /* startProxy */
        3U,                                         /* numProxy */

        6U,                                         /* startRingMon */
        1U,                                         /* numRingMon */
    }
};

/** \brief MCU Navss default configuration */
const Udma_RmInitPrms gUdmaRmDefCfg_McuNavss[UDMA_NUM_CORE] =
{
    /* MPU1_0 */
    {
        0U,         /* startBlkCopyUhcCh */
        0U,         /* numBlkCopyUhcCh */
        0U,         /* startBlkCopyHcCh */
        0U,         /* numBlkCopyHcCh */
        2U,         /* startBlkCopyCh */
        3U,         /* numBlkCopyCh */

        0U,         /* startTxUhcCh */
        0U,         /* numTxUhcCh */
        0U,         /* startTxHcCh */
        0U,         /* numTxHcCh */
        15U,        /* startTxCh */
        9U,         /* numTxCh */

        0U,         /* startRxUhcCh */
        0U,         /* numRxUhcCh */
        0U,         /* startRxHcCh */
        0U,         /* numRxHcCh */
        15U,        /* startRxCh */
        9U,         /* numRxCh */

#if (UDMA_NUM_UTC_INSTANCE > 0)
        {0U, 0U, 0U, 0U},       /* startUtcCh[] */
        {0U, 0U, 0U, 0U},       /* numUtcCh[] */
#endif

        48U,        /* startFreeFlow */
        8U,         /* numFreeFlow */
        96U,         /* startFreeRing */
        32U,        /* numFreeRing */

        992U,      /* startGlobalEvent */
        50U,        /* numGlobalEvent */
        100U,       /* startVintr */
        4U,         /* numVintr */
        448U,       /* startIrIntr */
        4U,         /* numIrIntr */

        1U,         /* proxyThreadNum */
        0U,         /* startC7xCoreIntr */

        2U,         /* startProxy */
        7U,         /* numProxy */

        0U,         /* startRingMon */
        3U,         /* numRingMon */
    },
    /* MCU2_0 */
    {
        0U,         /* startBlkCopyUhcCh */
        0U,         /* numBlkCopyUhcCh */
        0U,         /* startBlkCopyHcCh */
        0U,         /* numBlkCopyHcCh */
        11U,        /* startBlkCopyCh */
        2U,         /* numBlkCopyCh */

        0U,         /* startTxUhcCh */
        0U,         /* numTxUhcCh */
        0U,         /* startTxHcCh */
        0U,         /* numTxHcCh */
        36U,        /* startTxCh */
        4U,         /* numTxCh */

        0U,         /* startRxUhcCh */
        0U,         /* numRxUhcCh */
        0U,         /* startRxHcCh */
        0U,         /* numRxHcCh */
        36U,        /* startRxCh */
        4U,         /* numRxCh */

#if (UDMA_NUM_UTC_INSTANCE > 0)
        {0U, 0U, 0U, 0U},       /* startUtcCh[] */
        {0U, 0U, 0U, 0U},       /* numUtcCh[] */
#endif

        72U,        /* startFreeFlow */
        8U,         /* numFreeFlow */
        208U,       /* startFreeRing */
        16U,        /* numFreeRing */

        2016U,      /* startGlobalEvent */
        50U,        /* numGlobalEvent */
        190U,       /* startVintr */
        10U,        /* numVintr */
        248U,       /* startIrIntr */
        8U,         /* numIrIntr */

        45U,        /* proxyThreadNum */
        0U,         /* startC7xCoreIntr */

        46U,        /* startProxy */
        7U,         /* numProxy */

        17U,        /* startRingMon */
        5U,         /* numRingMon */
    },
    /* MCU2_1 */
    {
        0U,         /* startBlkCopyUhcCh */
        0U,         /* numBlkCopyUhcCh */
        0U,         /* startBlkCopyHcCh */
        0U,         /* numBlkCopyHcCh */
        13U,        /* startBlkCopyCh */
        2U,         /* numBlkCopyCh */

        0U,         /* startTxUhcCh */
        0U,         /* numTxUhcCh */
        0U,         /* startTxHcCh */
        0U,         /* numTxHcCh */
        40U,        /* startTxCh */
        4U,         /* numTxCh */

        0U,         /* startRxUhcCh */
        0U,         /* numRxUhcCh */
        0U,         /* startRxHcCh */
        0U,         /* numRxHcCh */
        40U,        /* startRxCh */
        4U,         /* numRxCh */

#if (UDMA_NUM_UTC_INSTANCE > 0)
        {0U, 0U, 0U, 0U},       /* startUtcCh[] */
        {0U, 0U, 0U, 0U},       /* numUtcCh[] */
#endif

        80U,        /* startFreeFlow */
        4U,         /* numFreeFlow */
        224U,       /* startFreeRing */
        16U,         /* numFreeRing */

        2528U,      /* startGlobalEvent */
        50U,        /* numGlobalEvent */
        220U,       /* startVintr */
        4U,         /* numVintr */
        248U,       /* startIrIntr */
        8U,         /* numIrIntr */

        53U,        /* proxyThreadNum */
        0U,         /* startC7xCoreIntr */

        54U,        /* startProxy */
        7U,        /* numProxy */

        22U,        /* startRingMon */
        5U,         /* numRingMon */
    },
    /* MCU1_0 */
    {
        0U,         /* startBlkCopyUhcCh */
        0U,         /* numBlkCopyUhcCh */
        0U,         /* startBlkCopyHcCh */
        0U,         /* numBlkCopyHcCh */
        7U,        /* startBlkCopyCh */
        2U,         /* numBlkCopyCh */

        0U,         /* startTxUhcCh */
        0U,         /* numTxUhcCh */
        0U,         /* startTxHcCh */
        2U,         /* numTxHcCh */
        28U,        /* startTxCh */
        4U,         /* numTxCh */

        0U,         /* startRxUhcCh */
        0U,         /* numRxUhcCh */
        0U,         /* startRxHcCh */
        2U,         /* numRxHcCh */
        28U,        /* startRxCh */
        4U,         /* numRxCh */

#if (UDMA_NUM_UTC_INSTANCE > 0)
        {0U, 0U, 0U, 0U},       /* startUtcCh[] */
        {0U, 0U, 0U, 0U},       /* numUtcCh[] */
#endif

        60U,        /* startFreeFlow */
        8U,         /* numFreeFlow */
        144U,       /* startFreeRing */
        32U,        /* numFreeRing */

        264U,       /* startGlobalEvent */
        200U,       /* numGlobalEvent */
        56U,        /* startVintr */
        60U,        /* numVintr */
        72U,        /* startIrIntr */
        6U,         /* numIrIntr */

        13U,         /* proxyThreadNum */
        0U,         /* startC7xCoreIntr */

        14U,        /* startProxy */
        15U,         /* numProxy */

        5U,         /* startRingMon */
        6U,         /* numRingMon */
    },
    /* MCU1_1 */
    {
        0U,         /* startBlkCopyUhcCh */
        0U,         /* numBlkCopyUhcCh */
        0U,         /* startBlkCopyHcCh */
        0U,         /* numBlkCopyHcCh */
        9U,         /* startBlkCopyCh */
        2U,         /* numBlkCopyCh */

        0U,         /* startTxUhcCh */
        0U,         /* numTxUhcCh */
        0U,         /* startTxHcCh */
        0U,         /* numTxHcCh */
        32U,        /* startTxCh */
        4U,         /* numTxCh */

        0U,         /* startRxUhcCh */
        0U,         /* numRxUhcCh */
        0U,         /* startRxHcCh */
        0U,         /* numRxHcCh */
        32U,        /* startRxCh */
        4U,         /* numRxCh */

#if (UDMA_NUM_UTC_INSTANCE > 0)
        {0U, 0U, 0U, 0U},       /* startUtcCh[] */
        {0U, 0U, 0U, 0U},       /* numUtcCh[] */
#endif

        68U,        /* startFreeFlow */
        4U,         /* numFreeFlow */
        176U,       /* startFreeRing */
        32U,        /* numFreeRing */

        520U,       /* startGlobalEvent */
        96U,        /* numGlobalEvent */
        120U,       /* startVintr */
        28U,        /* numVintr */
        72U,        /* startIrIntr */
        6U,         /* numIrIntr */

        29U,        /* proxyThreadNum */
        0U,         /* startC7xCoreIntr */

        30U,        /* startProxy */
        15U,        /* numProxy */

        11U,        /* startRingMon */
        6U,         /* numRingMon */
    }
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

const Udma_RmInitPrms *Udma_rmGetDefaultCfg(uint32_t instId)
{
    uint32_t                coreId;
    const Udma_RmInitPrms  *rmInitPrms;

    coreId = Udma_getCoreId();
    if(UDMA_INST_ID_MCU_0 == instId)
    {
        rmInitPrms = &gUdmaRmDefCfg_McuNavss[coreId];
    }
    else
    {
        rmInitPrms = &gUdmaRmDefCfg_MainNavss[coreId];
    }

    return (rmInitPrms);
}

int32_t Udma_rmCheckDefaultCfg(void)
{
    int32_t                 retVal = UDMA_SOK;
    Udma_RmInstCheckPrms    prms;

    /* Check MCU instance */
    prms.selfCfg     = &gUdmaRmDefCfg_McuNavss[0U];
    prms.crossCfg    = &gUdmaRmDefCfg_MainNavss[0U];
    prms.numCores    = UDMA_NUM_MCU_CORE;
    prms.startCoreId = UDMA_CORE_ID_MCU1_0;
    prms.maxTxCh     = CSL_NAVSS_MCU_UDMAP_NUM_TX_CHANS;
    prms.maxRxCh     = CSL_NAVSS_MCU_UDMAP_NUM_RX_CHANS;
    prms.maxUtcCh    = CSL_NAVSS_MCU_UDMAP_NUM_EXT_CHANS;
    prms.maxFreeRing = CSL_NAVSS_MCU_RINGACC_RING_CNT -
                        (prms.maxTxCh + prms.maxRxCh + prms.maxUtcCh + CSL_NAVSS_MCU_UDMAP_NUM_SECURE_CHANS);
    prms.maxFreeFlow = CSL_NAVSS_MCU_UDMAP_NUM_RX_FLOWS - prms.maxRxCh;
    prms.maxEvents   = UDMA_MCU_NAVSS0_EVENT_CNT;
    prms.maxVintr    = UDMA_MCU_NAVSS0_VINTR_CNT;
    prms.maxProxy    = CSL_NAVSS_MCU_PROXY_NUM_PROXIES;
    prms.maxRingMon  = CSL_NAVSS_MCU_RINGACC_NUM_MONITORS;
    retVal += Udma_rmCheckInstOverlap(&prms);

    /* Check Main instance */
    prms.selfCfg     = &gUdmaRmDefCfg_MainNavss[0U];
    prms.crossCfg    = &gUdmaRmDefCfg_McuNavss[0U];
    prms.numCores    = UDMA_NUM_MAIN_CORE;
    prms.startCoreId = UDMA_CORE_ID_MPU1_0;
    prms.maxTxCh     = CSL_NAVSS_MAIN_UDMAP_NUM_TX_CHANS;
    prms.maxRxCh     = CSL_NAVSS_MAIN_UDMAP_NUM_RX_CHANS;
    prms.maxUtcCh    = CSL_NAVSS_MAIN_UDMAP_NUM_EXT_CHANS;
    prms.maxFreeRing = CSL_NAVSS_MAIN_RINGACC_RING_CNT -
                        (prms.maxTxCh + prms.maxRxCh + prms.maxUtcCh + CSL_NAVSS_MAIN_UDMAP_NUM_SECURE_CHANS);
    prms.maxFreeFlow = CSL_NAVSS_MAIN_UDMAP_NUM_RX_FLOWS - prms.maxRxCh;
    prms.maxEvents   = UDMA_MAIN_NAVSS0_EVENT_CNT;
    prms.maxVintr    = UDMA_MAIN_NAVSS0_VINTR_CNT;
    prms.maxProxy    = CSL_NAVSS_MAIN_PROXY_NUM_PROXIES;
    prms.maxRingMon  = CSL_NAVSS_MAIN_RINGACC_NUM_MONITORS;
    retVal += Udma_rmCheckInstOverlap(&prms);

    return (retVal);
}

static int32_t Udma_rmCheckInstOverlap(const Udma_RmInstCheckPrms *prms)
{
    int32_t     retVal = UDMA_SOK;
    uint32_t    startRes[UDMA_RM_CHECK_MAX_ENTRY];
    uint32_t    numRes[UDMA_RM_CHECK_MAX_ENTRY];
    uint32_t    startIdx, numIdx;
    uint32_t    coreId;
#if (UDMA_NUM_UTC_INSTANCE > 0)
    uint32_t    utcId;
#endif

    /* Check TX channels */
    startIdx = 0U; numIdx = 0U;
    for(coreId = 0U; coreId < UDMA_NUM_CORE; coreId++)
    {
        startRes[startIdx] = prms->selfCfg[coreId].startBlkCopyCh; startIdx++;
        startRes[startIdx] = prms->selfCfg[coreId].startBlkCopyHcCh; startIdx++;
        startRes[startIdx] = prms->selfCfg[coreId].startBlkCopyUhcCh; startIdx++;
        startRes[startIdx] = prms->selfCfg[coreId].startTxCh; startIdx++;
        startRes[startIdx] = prms->selfCfg[coreId].startTxHcCh; startIdx++;
        startRes[startIdx] = prms->selfCfg[coreId].startTxUhcCh; startIdx++;
        numRes[numIdx] = prms->selfCfg[coreId].numBlkCopyCh; numIdx++;
        numRes[numIdx] = prms->selfCfg[coreId].numBlkCopyHcCh; numIdx++;
        numRes[numIdx] = prms->selfCfg[coreId].numBlkCopyUhcCh; numIdx++;
        numRes[numIdx] = prms->selfCfg[coreId].numTxCh; numIdx++;
        numRes[numIdx] = prms->selfCfg[coreId].numTxHcCh; numIdx++;
        numRes[numIdx] = prms->selfCfg[coreId].numTxUhcCh; numIdx++;
    }
    retVal += Udma_rmCheckOverlap(startRes, numRes, startIdx, prms->maxTxCh);

    /* Check RX channels */
    startIdx = 0U; numIdx = 0U;
    for(coreId = 0U; coreId < UDMA_NUM_CORE; coreId++)
    {
        startRes[startIdx] = prms->selfCfg[coreId].startBlkCopyCh; startIdx++;
        startRes[startIdx] = prms->selfCfg[coreId].startBlkCopyHcCh; startIdx++;
        startRes[startIdx] = prms->selfCfg[coreId].startBlkCopyUhcCh; startIdx++;
        startRes[startIdx] = prms->selfCfg[coreId].startRxCh; startIdx++;
        startRes[startIdx] = prms->selfCfg[coreId].startRxHcCh; startIdx++;
        startRes[startIdx] = prms->selfCfg[coreId].startRxUhcCh; startIdx++;
        numRes[numIdx] = prms->selfCfg[coreId].numBlkCopyCh; numIdx++;
        numRes[numIdx] = prms->selfCfg[coreId].numBlkCopyHcCh; numIdx++;
        numRes[numIdx] = prms->selfCfg[coreId].numBlkCopyUhcCh; numIdx++;
        numRes[numIdx] = prms->selfCfg[coreId].numRxCh; numIdx++;
        numRes[numIdx] = prms->selfCfg[coreId].numRxHcCh; numIdx++;
        numRes[numIdx] = prms->selfCfg[coreId].numRxUhcCh; numIdx++;
    }
    retVal += Udma_rmCheckOverlap(startRes, numRes, startIdx, prms->maxRxCh);

#if (UDMA_NUM_UTC_INSTANCE > 0)
    /* Check UTC channels */
    startIdx = 0U; numIdx = 0U;
    for(utcId = 0U; utcId < UDMA_NUM_UTC_INSTANCE; utcId++)
    {
        for(coreId = 0U; coreId < UDMA_NUM_CORE; coreId++)
        {
            startRes[startIdx] = prms->selfCfg[coreId].startUtcCh[utcId]; startIdx++;
            numRes[numIdx] = prms->selfCfg[coreId].numUtcCh[utcId]; numIdx++;
        }
    }
    retVal += Udma_rmCheckOverlap(startRes, numRes, startIdx, prms->maxUtcCh);
#endif

    /* Check free ring */
    startIdx = 0U; numIdx = 0U;
    for(coreId = 0U; coreId < UDMA_NUM_CORE; coreId++)
    {
        startRes[startIdx] = prms->selfCfg[coreId].startFreeRing; startIdx++;
        numRes[numIdx] = prms->selfCfg[coreId].numFreeRing; numIdx++;
    }
    retVal += Udma_rmCheckOverlap(startRes, numRes, startIdx, prms->maxFreeRing);

    /* Check free flow */
    startIdx = 0U; numIdx = 0U;
    for(coreId = 0U; coreId < UDMA_NUM_CORE; coreId++)
    {
        startRes[startIdx] = prms->selfCfg[coreId].startFreeFlow; startIdx++;
        numRes[numIdx] = prms->selfCfg[coreId].numFreeFlow; numIdx++;
    }
    retVal += Udma_rmCheckOverlap(startRes, numRes, startIdx, prms->maxFreeFlow);

    /*
     * Note the cross usage!! This is intentional as events/interrupts
     * are allocated based on core and not based on UDMA instance
     *
     */
    /* Check events */
    startIdx = 0U; numIdx = 0U;
    for(coreId = 0U; coreId < prms->numCores; coreId++)
    {
        startRes[startIdx] = prms->selfCfg[prms->startCoreId + coreId].startGlobalEvent; startIdx++;
        startRes[startIdx] = prms->crossCfg[prms->startCoreId + coreId].startGlobalEvent; startIdx++;
        numRes[numIdx] = prms->selfCfg[prms->startCoreId + coreId].numGlobalEvent; numIdx++;
        numRes[numIdx] = prms->crossCfg[prms->startCoreId + coreId].numGlobalEvent; numIdx++;
    }
    retVal += Udma_rmCheckOverlap(startRes, numRes, startIdx, prms->maxEvents);

    /* Check VINTR */
    startIdx = 0U; numIdx = 0U;
    for(coreId = 0U; coreId < prms->numCores; coreId++)
    {
        startRes[startIdx] = prms->selfCfg[prms->startCoreId + coreId].startVintr; startIdx++;
        startRes[startIdx] = prms->crossCfg[prms->startCoreId + coreId].startVintr; startIdx++;
        numRes[numIdx] = prms->selfCfg[prms->startCoreId + coreId].numVintr; numIdx++;
        numRes[numIdx] = prms->crossCfg[prms->startCoreId + coreId].numVintr; numIdx++;
    }
    retVal += Udma_rmCheckOverlap(startRes, numRes, startIdx, prms->maxVintr);

    /* Check proxy */
    startIdx = 0U; numIdx = 0U;
    for(coreId = 0U; coreId < UDMA_NUM_CORE; coreId++)
    {
        startRes[startIdx] = prms->selfCfg[coreId].proxyThreadNum; startIdx++;
        startRes[startIdx] = prms->selfCfg[coreId].startProxy; startIdx++;
        numRes[numIdx] = 1U; numIdx++;
        numRes[numIdx] = prms->selfCfg[coreId].numProxy; numIdx++;
    }
    retVal += Udma_rmCheckOverlap(startRes, numRes, startIdx, prms->maxProxy);

    /* Check ring monitor */
    startIdx = 0U; numIdx = 0U;
    for(coreId = 0U; coreId < UDMA_NUM_CORE; coreId++)
    {
        startRes[startIdx] = prms->selfCfg[coreId].startRingMon; startIdx++;
        numRes[numIdx] = prms->selfCfg[coreId].numRingMon; numIdx++;
    }
    retVal += Udma_rmCheckOverlap(startRes, numRes, startIdx, prms->maxRingMon);

    return (retVal);
}

static int32_t Udma_rmCheckOverlap(uint32_t startRes[UDMA_RM_CHECK_MAX_ENTRY],
                                   uint32_t numRes[UDMA_RM_CHECK_MAX_ENTRY],
                                   uint32_t numEntries,
                                   uint32_t maxRes)
{
    uint32_t                i, j;
    uint32_t                offset, bitPos, bitMask;
    int32_t                 retVal = UDMA_SOK;
    uint32_t                mask[UDMA_RM_CHECK_MAX_WORDS];

    /* Reset */
    for(i = 0U; i < UDMA_RM_CHECK_MAX_WORDS; i++)
    {
        mask[i] = 0U;
    }
    for(j = 0U; j < numEntries; j++)
    {
        if((startRes[j]+numRes[j]) > maxRes)
        {
            /* Resource going out of bound */
            retVal = UDMA_EFAIL;
        }
        else
        {
            for(i = 0U; i < numRes[j]; i++)
            {
                offset = (i + startRes[j]) >> 5U;
                bitPos = (i + startRes[j]) - (offset << 5U);
                bitMask = (uint32_t) 1U << bitPos;
                if((offset >= UDMA_RM_CHECK_MAX_WORDS) ||
                   ((mask[offset] & bitMask) == bitMask))
                {
                    /* Resource already allocate or array out of bound */
                    retVal = UDMA_EFAIL;
                    break;
                }
                else
                {
                    mask[offset] |= bitMask;
                }
            }
        }

        /* Break on error */
        if(retVal != UDMA_SOK)
        {
            break;
        }
    }

    return (retVal);
}
