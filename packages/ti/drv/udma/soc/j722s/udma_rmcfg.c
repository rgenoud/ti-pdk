/*
 *  Copyright (C) 2023 Texas Instruments Incorporated
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

/** \brief BCDMA defaultBoardCfg Params */
const Udma_RmDefBoardCfgPrms gUdmaRmDefBoardCfg_Bcdma[UDMA_RM_NUM_BCDMA_RES] =
{
    /* resId,                               reqType,                           reqSubtype,                                  secHost */
    {UDMA_RM_RES_ID_BC_UHC,                 UDMA_RM_SCI_REQ_TYPE_INVALID,      UDMA_RM_SCI_REQ_SUBTYPE_INVALID,             TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_BC_HC,                  UDMA_RM_SCI_REQ_TYPE_INVALID,      UDMA_RM_SCI_REQ_SUBTYPE_INVALID,             TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_BC,                     TISCI_DEV_DMASS0_BCDMA_0,          TISCI_RESASG_SUBTYPE_BCDMA_BLOCK_COPY_CHAN,  TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_TX_UHC,                 UDMA_RM_SCI_REQ_TYPE_INVALID,      UDMA_RM_SCI_REQ_SUBTYPE_INVALID,             TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_TX_HC,                  UDMA_RM_SCI_REQ_TYPE_INVALID,      UDMA_RM_SCI_REQ_SUBTYPE_INVALID,             TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_TX,                     TISCI_DEV_DMASS0_BCDMA_0,          TISCI_RESASG_SUBTYPE_BCDMA_SPLIT_TR_TX_CHAN, TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_RX_UHC,                 UDMA_RM_SCI_REQ_TYPE_INVALID,      UDMA_RM_SCI_REQ_SUBTYPE_INVALID,             TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_RX_HC,                  UDMA_RM_SCI_REQ_TYPE_INVALID,      UDMA_RM_SCI_REQ_SUBTYPE_INVALID,             TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_RX,                     TISCI_DEV_DMASS0_BCDMA_0,          TISCI_RESASG_SUBTYPE_BCDMA_SPLIT_TR_RX_CHAN, TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_GLOBAL_EVENT,           TISCI_DEV_DMASS0_INTAGGR_0,        TISCI_RESASG_SUBTYPE_GLOBAL_EVENT_SEVT,      TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_VINTR,                  TISCI_DEV_DMASS0_INTAGGR_0,        TISCI_RESASG_SUBTYPE_IA_VINT,                TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
};

/** \brief BCDMA(CSI) defaultBoardCfg Params */
const Udma_RmDefBoardCfgPrms gUdmaRmDefBoardCfg_BcdmaCsi[UDMA_RM_NUM_BCDMA_RES] =
{
    /* resId,                               reqType,                           reqSubtype,                                  secHost */
    {UDMA_RM_RES_ID_BC_UHC,                 UDMA_RM_SCI_REQ_TYPE_INVALID,      UDMA_RM_SCI_REQ_SUBTYPE_INVALID,             TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_BC_HC,                  UDMA_RM_SCI_REQ_TYPE_INVALID,      UDMA_RM_SCI_REQ_SUBTYPE_INVALID,             TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_BC,                     UDMA_RM_SCI_REQ_TYPE_INVALID,      UDMA_RM_SCI_REQ_SUBTYPE_INVALID,             TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_TX_UHC,                 UDMA_RM_SCI_REQ_TYPE_INVALID,      UDMA_RM_SCI_REQ_SUBTYPE_INVALID,             TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_TX_HC,                  UDMA_RM_SCI_REQ_TYPE_INVALID,      UDMA_RM_SCI_REQ_SUBTYPE_INVALID,             TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_TX,                     TISCI_DEV_DMASS1_BCDMA_0,          TISCI_RESASG_SUBTYPE_BCDMA_SPLIT_TR_TX_CHAN, TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_RX_UHC,                 UDMA_RM_SCI_REQ_TYPE_INVALID,      UDMA_RM_SCI_REQ_SUBTYPE_INVALID,             TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_RX_HC,                  UDMA_RM_SCI_REQ_TYPE_INVALID,      UDMA_RM_SCI_REQ_SUBTYPE_INVALID,             TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_RX,                     TISCI_DEV_DMASS1_BCDMA_0,          TISCI_RESASG_SUBTYPE_BCDMA_SPLIT_TR_RX_CHAN, TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_GLOBAL_EVENT,           TISCI_DEV_DMASS1_INTAGGR_0,        TISCI_RESASG_SUBTYPE_GLOBAL_EVENT_SEVT,      TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_VINTR,                  TISCI_DEV_DMASS1_INTAGGR_0,        TISCI_RESASG_SUBTYPE_IA_VINT,                TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
};

/** \brief PKTDMA defaultBoardCfg Params */
const Udma_RmDefBoardCfgPrms gUdmaRmDefBoardCfg_Pktdma[UDMA_RM_NUM_PKTDMA_RES] =
{
    /* resId,                               reqType,                        reqSubtype,                                         secHost */
    {UDMA_RM_RES_ID_BC_UHC,                 UDMA_RM_SCI_REQ_TYPE_INVALID,   UDMA_RM_SCI_REQ_SUBTYPE_INVALID,                    TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_BC_HC,                  UDMA_RM_SCI_REQ_TYPE_INVALID,   UDMA_RM_SCI_REQ_SUBTYPE_INVALID,                    TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_BC,                     UDMA_RM_SCI_REQ_TYPE_INVALID,   UDMA_RM_SCI_REQ_SUBTYPE_INVALID,                    TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_TX_UHC,                 UDMA_RM_SCI_REQ_TYPE_INVALID,   UDMA_RM_SCI_REQ_SUBTYPE_INVALID,                    TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_TX_HC,                  UDMA_RM_SCI_REQ_TYPE_INVALID,   UDMA_RM_SCI_REQ_SUBTYPE_INVALID,                    TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_TX,                     TISCI_DEV_DMASS0_PKTDMA_0,      TISCI_RESASG_SUBTYPE_PKTDMA_UNMAPPED_TX_CHAN,       TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_RX_UHC,                 UDMA_RM_SCI_REQ_TYPE_INVALID,   UDMA_RM_SCI_REQ_SUBTYPE_INVALID,                    TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_RX_HC,                  UDMA_RM_SCI_REQ_TYPE_INVALID,   UDMA_RM_SCI_REQ_SUBTYPE_INVALID,                    TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_RX,                     TISCI_DEV_DMASS0_PKTDMA_0,      TISCI_RESASG_SUBTYPE_PKTDMA_UNMAPPED_RX_CHAN,       TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_GLOBAL_EVENT,           TISCI_DEV_DMASS0_INTAGGR_0,     TISCI_RESASG_SUBTYPE_GLOBAL_EVENT_SEVT,             TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_VINTR,                  TISCI_DEV_DMASS0_INTAGGR_0,     TISCI_RESASG_SUBTYPE_IA_VINT,                       TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_MAPPED_TX_CPSW,         TISCI_DEV_DMASS0_PKTDMA_0,      TISCI_RESASG_SUBTYPE_PKTDMA_CPSW_TX_CHAN,           TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_MAPPED_TX_SAUL_0,       TISCI_DEV_DMASS0_PKTDMA_0,      TISCI_RESASG_SUBTYPE_PKTDMA_SAUL_TX_0_CHAN,         TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_MAPPED_TX_SAUL_1,       TISCI_DEV_DMASS0_PKTDMA_0,      TISCI_RESASG_SUBTYPE_PKTDMA_SAUL_TX_1_CHAN,         TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_MAPPED_RX_CPSW,         TISCI_DEV_DMASS0_PKTDMA_0,      TISCI_RESASG_SUBTYPE_PKTDMA_CPSW_RX_CHAN,           TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_MAPPED_RX_SAUL_0,       TISCI_DEV_DMASS0_PKTDMA_0,      TISCI_RESASG_SUBTYPE_PKTDMA_SAUL_RX_0_CHAN,         TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_MAPPED_RX_SAUL_1,       TISCI_DEV_DMASS0_PKTDMA_0,      TISCI_RESASG_SUBTYPE_PKTDMA_SAUL_RX_1_CHAN,         TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_MAPPED_RX_SAUL_2,       TISCI_DEV_DMASS0_PKTDMA_0,      TISCI_RESASG_SUBTYPE_PKTDMA_SAUL_RX_2_CHAN,         TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_MAPPED_RX_SAUL_3,       TISCI_DEV_DMASS0_PKTDMA_0,      TISCI_RESASG_SUBTYPE_PKTDMA_SAUL_RX_3_CHAN,         TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_MAPPED_TX_RING_CPSW,    TISCI_DEV_DMASS0_PKTDMA_0,      TISCI_RESASG_SUBTYPE_PKTDMA_RING_CPSW_TX_CHAN,      TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_MAPPED_TX_RING_SAUL_0,  TISCI_DEV_DMASS0_PKTDMA_0,      TISCI_RESASG_SUBTYPE_PKTDMA_RING_SAUL_TX_0_CHAN,    TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_MAPPED_TX_RING_SAUL_1,  TISCI_DEV_DMASS0_PKTDMA_0,      TISCI_RESASG_SUBTYPE_PKTDMA_RING_SAUL_TX_1_CHAN,    TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_MAPPED_RX_RING_CPSW,    TISCI_DEV_DMASS0_PKTDMA_0,      TISCI_RESASG_SUBTYPE_PKTDMA_RING_CPSW_RX_CHAN,      TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_MAPPED_RX_RING_SAUL_0,  TISCI_DEV_DMASS0_PKTDMA_0,      TISCI_RESASG_SUBTYPE_PKTDMA_RING_SAUL_RX_0_CHAN,    TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_MAPPED_RX_RING_SAUL_1,  TISCI_DEV_DMASS0_PKTDMA_0,      TISCI_RESASG_SUBTYPE_PKTDMA_RING_SAUL_RX_1_CHAN,    TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_MAPPED_RX_RING_SAUL_2,  TISCI_DEV_DMASS0_PKTDMA_0,      TISCI_RESASG_SUBTYPE_PKTDMA_RING_SAUL_RX_2_CHAN,    TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
    {UDMA_RM_RES_ID_MAPPED_RX_RING_SAUL_3,  TISCI_DEV_DMASS0_PKTDMA_0,      TISCI_RESASG_SUBTYPE_PKTDMA_RING_SAUL_RX_3_CHAN,    TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST},
};

uint32_t gEvtInstShare[UDMA_NUM_INST_ID]  = {UDMA_RM_SHARED_RES_CNT_REST, UDMA_RM_SHARED_RES_CNT_REST, 0U};
/** \brief Shared resource Params */
Udma_RmSharedResPrms gUdmaRmSharedResPrms[UDMA_RM_NUM_SHARED_RES] =
{
    /* Global Events/VINTR must be used based on core and split across BCDMA and PKTDMA instances */
    /* resId,                     startResrvCnt, endResrvCnt, numInst,           minReq, instShare[BCDMA,PKTDMA,BCDMA(CSI)] */
    {UDMA_RM_RES_ID_GLOBAL_EVENT, 0U,            0U,          UDMA_NUM_INST_ID,  50U, gEvtInstShare},
    {UDMA_RM_RES_ID_VINTR,        0U,            0U,          UDMA_NUM_INST_ID,  4U, gEvtInstShare},
};
/** \brief Shared resource Params */
Udma_RmSharedResPrms gBcdmaCsiRmSharedResPrms[UDMA_RM_NUM_SHARED_RES] =
{
    /* Global Events/VINTR must be used based on core and split across BCDMA and PKTDMA instances */
    /* resId,                     startResrvCnt, endResrvCnt, numInst,           minReq, instShare[BCDMA,PKTDMA,BCDMA(CSI)] */
    {UDMA_RM_RES_ID_GLOBAL_EVENT, 0U,            0U,          UDMA_NUM_INST_ID,  50U,    {0U, 0U, UDMA_RM_SHARED_RES_CNT_REST} },
    {UDMA_RM_RES_ID_VINTR,        0U,            0U,          UDMA_NUM_INST_ID,  4U,     {0U, 0U, UDMA_RM_SHARED_RES_CNT_REST} },
};

/* These DRUs are local to C7X cores, user need to take care of resource overlapping when they try to override default allocation */
Udma_RmSharedResPrms gBcdmaDruRmSharedResPrms[UDMA_RM_NUM_SHARED_RES] =
{
#if defined (BUILD_C75X_1)
    /* resId,                     startResrvCnt, endResrvCnt, numInst,           minReq, instShare */
    {UDMA_INST_ID_C7X_DRU_0,       0U,            0U,          UDMA_NUM_C7X_CORE,     4U, {UDMA_RM_SHARED_RES_CNT_REST, UDMA_RM_SHARED_RES_CNT_MIN}},
    {UDMA_INST_ID_C7X_DRU_1,       0U,            0U,          UDMA_NUM_C7X_CORE,     4U, {UDMA_RM_SHARED_RES_CNT_MIN, UDMA_RM_SHARED_RES_CNT_REST}},
#elif defined (BUILD_C75X_2)
    {UDMA_INST_ID_C7X_DRU_0,       0U,            0U,          UDMA_NUM_C7X_CORE,     4U, {UDMA_RM_SHARED_RES_CNT_MIN, UDMA_RM_SHARED_RES_CNT_REST}},
    {UDMA_INST_ID_C7X_DRU_1,       0U,            0U,          UDMA_NUM_C7X_CORE,     4U, {UDMA_RM_SHARED_RES_CNT_REST, UDMA_RM_SHARED_RES_CNT_MIN}},
#endif
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

const Udma_RmDefBoardCfgPrms *Udma_rmGetDefBoardCfgPrms(uint32_t instId)
{
    const Udma_RmDefBoardCfgPrms  *rmDefBoardCfgPrms;

    if(UDMA_INST_ID_BCDMA_0 == instId)
    {
        rmDefBoardCfgPrms = &gUdmaRmDefBoardCfg_Bcdma[0U];
    }
    else if(UDMA_INST_ID_BCDMA_1 == instId)
    {
        rmDefBoardCfgPrms = &gUdmaRmDefBoardCfg_BcdmaCsi[0U];
    }
    else
    {
        rmDefBoardCfgPrms = &gUdmaRmDefBoardCfg_Pktdma[0U];
    }

    return (rmDefBoardCfgPrms);
}


// TODO:: Lohit reviewed. Need to add instance id and check between CSI and general bcdma.
// Need to handle CSI separately
Udma_RmSharedResPrms *Udma_rmGetSharedResPrms(uint32_t resId)
{
    Udma_RmSharedResPrms  *rmSharedResPrms = NULL;
    uint32_t    i;

    for(i = 0; i < UDMA_RM_NUM_SHARED_RES; i++)
    {
        if(resId == gUdmaRmSharedResPrms[i].resId)
        {
            rmSharedResPrms = &gUdmaRmSharedResPrms[i];
            break;
        }
    }
    
    return (rmSharedResPrms);
}

