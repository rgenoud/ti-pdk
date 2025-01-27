/*
 *  Copyright (c) Texas Instruments Incorporated 2018
 *  All rights reserved.
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
 *  \file dss_soc.c
 *
 *  \brief File containing the SOC related configuration functions for DSS.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/dss/dss.h>
#include <dss_soc_priv.h>
#include <ti/drv/dss/src/drv/common/dss_evtMgr.h>

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

/** Module ids for display controller nodes. For nodes that are not part of DSS
 *  HW, module id is not defined
 */
static const Dss_DctrlNodeIdInfo gDss_DctrlNodeIdInfo[] = {
    {DSS_DCTRL_NODE_VID1,     CSL_DSS_VID_PIPE_ID_VID1,  DSS_DCTRL_NODE_TYPE_PIPE},
    {DSS_DCTRL_NODE_VIDL1,    CSL_DSS_VID_PIPE_ID_VIDL1, DSS_DCTRL_NODE_TYPE_PIPE},
    {DSS_DCTRL_NODE_VID2,     CSL_DSS_VID_PIPE_ID_VID2,  DSS_DCTRL_NODE_TYPE_PIPE},
    {DSS_DCTRL_NODE_VIDL2,    CSL_DSS_VID_PIPE_ID_VIDL2, DSS_DCTRL_NODE_TYPE_PIPE},
    {DSS_DCTRL_NODE_OVERLAY1, CSL_DSS_OVERLAY_ID_1,      DSS_DCTRL_NODE_TYPE_OVERLAY},
    {DSS_DCTRL_NODE_OVERLAY2, CSL_DSS_OVERLAY_ID_2,      DSS_DCTRL_NODE_TYPE_OVERLAY},
    {DSS_DCTRL_NODE_OVERLAY3, CSL_DSS_OVERLAY_ID_3,      DSS_DCTRL_NODE_TYPE_OVERLAY},
    {DSS_DCTRL_NODE_OVERLAY4, CSL_DSS_OVERLAY_ID_4,      DSS_DCTRL_NODE_TYPE_OVERLAY},
    {DSS_DCTRL_NODE_VP1,      CSL_DSS_VP_ID_1,           DSS_DCTRL_NODE_TYPE_VP},
    {DSS_DCTRL_NODE_VP2,      CSL_DSS_VP_ID_2,           DSS_DCTRL_NODE_TYPE_VP},
    {DSS_DCTRL_NODE_VP3,      CSL_DSS_VP_ID_3,           DSS_DCTRL_NODE_TYPE_VP},
    {DSS_DCTRL_NODE_VP4,      CSL_DSS_VP_ID_4,           DSS_DCTRL_NODE_TYPE_VP},
    {DSS_DCTRL_NODE_DPI_DPI0, CSL_DSS_DPI_ID_DPI_0,      DSS_DCTRL_NODE_TYPE_OUTPUT},  /* Virtual Node */
    {DSS_DCTRL_NODE_DPI_DPI1, CSL_DSS_DPI_ID_DPI_1,      DSS_DCTRL_NODE_TYPE_OUTPUT},  /* Virtual Node */
    {DSS_DCTRL_NODE_EDP_DPI0, CSL_DSS_DPI_ID_EDP_0,      DSS_DCTRL_NODE_TYPE_OUTPUT},  /* Virtual Node */
    {DSS_DCTRL_NODE_EDP_DPI1, CSL_DSS_DPI_ID_EDP_1,      DSS_DCTRL_NODE_TYPE_OUTPUT},  /* Virtual Node */
    {DSS_DCTRL_NODE_EDP_DPI2, CSL_DSS_DPI_ID_EDP_2,      DSS_DCTRL_NODE_TYPE_OUTPUT},  /* Virtual Node */
    {DSS_DCTRL_NODE_EDP_DPI3, CSL_DSS_DPI_ID_EDP_3,      DSS_DCTRL_NODE_TYPE_OUTPUT},  /* Virtual Node */
    {DSS_DCTRL_NODE_DSI_DPI2, CSL_DSS_DPI_ID_DSI,        DSS_DCTRL_NODE_TYPE_OUTPUT},   /* Virtual Node */
    {DSS_DCTRL_NODE_WB,       CSL_DSS_WB_PIPE_ID_1,      DSS_DCTRL_NODE_TYPE_OUTPUT}   /* Virtual Node */
};

static const Dss_CommRegInfo gDss_commRegInfo[] = {
    {CSL_DSS_COMM_REG_ID_0, (void *)CSL_DSS0_DISPC_0_COMMON_M_BASE},
    {CSL_DSS_COMM_REG_ID_1, (void *)CSL_DSS0_DISPC_0_COMMON_S0_BASE},
    {CSL_DSS_COMM_REG_ID_2, (void *)CSL_DSS0_DISPC_0_COMMON_S1_BASE},
    {CSL_DSS_COMM_REG_ID_3, (void *)CSL_DSS0_DISPC_0_COMMON_S2_BASE}
};

static const Dss_PipeRegInfo gDss_pipeRegInfo[] = {
    {CSL_DSS_VID_PIPE_ID_VID1, (void *)CSL_DSS0_VID1_BASE},
    {CSL_DSS_VID_PIPE_ID_VIDL1, (void *)CSL_DSS0_VIDL1_BASE},
    {CSL_DSS_VID_PIPE_ID_VID2, (void *)CSL_DSS0_VID2_BASE},
    {CSL_DSS_VID_PIPE_ID_VIDL2, (void *)CSL_DSS0_VIDL2_BASE}
};

static const Dss_OverlayRegInfo gDss_overlayRegInfo[] = {
    {CSL_DSS_OVERLAY_ID_1, (void *)CSL_DSS0_OVR1_BASE},
    {CSL_DSS_OVERLAY_ID_2, (void *)CSL_DSS0_OVR2_BASE},
    {CSL_DSS_OVERLAY_ID_3, (void *)CSL_DSS0_OVR3_BASE},
    {CSL_DSS_OVERLAY_ID_4, (void *)CSL_DSS0_OVR4_BASE}
};

static const Dss_VpRegInfo gDss_vpRegInfo[] = {
    {CSL_DSS_VP_ID_1, (void *)CSL_DSS0_VP1_BASE},
    {CSL_DSS_VP_ID_2, (void *)CSL_DSS0_VP2_BASE},
    {CSL_DSS_VP_ID_3, (void *)CSL_DSS0_VP3_BASE},
    {CSL_DSS_VP_ID_4, (void *)CSL_DSS0_VP4_BASE}
};

static const Dss_WbPipeRegInfo gDss_wbRegInfo[] = {
    {CSL_DSS_WB_PIPE_ID_1, (void *)CSL_DSS0_WB_BASE},
};

static const Dss_OverlayConnInfo gDss_OverlayConnInfo[] = {
    {CSL_DSS_OVERLAY_ID_1, CSL_DSS_VP_ID_1},
    {CSL_DSS_OVERLAY_ID_2, CSL_DSS_VP_ID_2},
    {CSL_DSS_OVERLAY_ID_3, CSL_DSS_VP_ID_3},
    {CSL_DSS_OVERLAY_ID_4, CSL_DSS_VP_ID_4}
};

static const Dss_VpSafetyRegionIdInfo gDss_VpSafetyRegionIdInfo[] = {
    {CSL_DSS_VP_SAFETY_REGION_0, DSS_VP_EVENT_SAFETY_VIOLATION_0},
    {CSL_DSS_VP_SAFETY_REGION_1, DSS_VP_EVENT_SAFETY_VIOLATION_1},
    {CSL_DSS_VP_SAFETY_REGION_2, DSS_VP_EVENT_SAFETY_VIOLATION_2},
    {CSL_DSS_VP_SAFETY_REGION_3, DSS_VP_EVENT_SAFETY_VIOLATION_3},
    {CSL_DSS_VP_SAFETY_REGION_4, DSS_VP_EVENT_SAFETY_VIOLATION_4},
    {CSL_DSS_VP_SAFETY_REGION_5, DSS_VP_EVENT_SAFETY_VIOLATION_5},
    {CSL_DSS_VP_SAFETY_REGION_6, DSS_VP_EVENT_SAFETY_VIOLATION_6},
    {CSL_DSS_VP_SAFETY_REGION_7, DSS_VP_EVENT_SAFETY_VIOLATION_7}
};

static const Dss_EventGroupInfo gDss_EventGroupInfo[] = {
    {DSS_EVENT_GROUP_VP1, CSL_DSS_VP_ID_1, DSS_EVENT_GROUP_TYPE_VP},
    {DSS_EVENT_GROUP_VP2, CSL_DSS_VP_ID_2, DSS_EVENT_GROUP_TYPE_VP},
    {DSS_EVENT_GROUP_VP3, CSL_DSS_VP_ID_3, DSS_EVENT_GROUP_TYPE_VP},
    {DSS_EVENT_GROUP_VP4, CSL_DSS_VP_ID_4, DSS_EVENT_GROUP_TYPE_VP},
    {DSS_EVENT_GROUP_VID1, CSL_DSS_VID_PIPE_ID_VID1, DSS_EVENT_GROUP_TYPE_PIPE},
    {DSS_EVENT_GROUP_VIDL1, CSL_DSS_VID_PIPE_ID_VIDL1, DSS_EVENT_GROUP_TYPE_PIPE},
    {DSS_EVENT_GROUP_VID2, CSL_DSS_VID_PIPE_ID_VID2, DSS_EVENT_GROUP_TYPE_PIPE},
    {DSS_EVENT_GROUP_VIDL2, CSL_DSS_VID_PIPE_ID_VIDL2, DSS_EVENT_GROUP_TYPE_PIPE},
    {DSS_EVENT_GROUP_WB, CSL_DSS_WB_PIPE_ID_1, DSS_EVENT_GROUP_TYPE_WB_PIPE}
};

static const uint32_t gDss_PipeErrEvents[] = {
    DSS_PIPE_EVENT_BUFF_UNDERFLOW
};

static const uint32_t gDss_VpFuncEvents[] = {
    DSS_VP_EVENT_VSYNC,
    DSS_VP_EVENT_LINE_NUM
};

static const uint32_t gDss_VpErrEvents[] = {
    DSS_VP_EVENT_SYNC_LOST
};

static const uint32_t gDss_WbFuncEvents[] = {
    DSS_WB_PIPE_EVENT_BUFF_FRAME_DONE,
    DSS_WB_PIPE_EVENT_BUFF_OVERFLOW
};

/* Global containing SoC information. */
static Dss_SocInfo gDss_SocInfo;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void Dss_fillSocInfo(Dss_RmInfo *rmInfo)
{
    uint32_t i = 0U;

    for(i = CSL_DSS_COMM_REG_ID_0; i < CSL_DSS_COMM_REG_ID_MAX; i++)
    {
        if(UTRUE == rmInfo->isCommRegAvailable[i])
        {
            gDss_SocInfo.commRegs[i] =
                (CSL_dss_commRegs *)gDss_commRegInfo[i].commRegs;
        }
    }
    for(i = CSL_DSS_VID_PIPE_ID_VID1; i < CSL_DSS_VID_PIPE_ID_MAX; i++)
    {
        if(UTRUE == rmInfo->isPipeAvailable[i])
        {
            gDss_SocInfo.pipeRegs[i] =
                    (CSL_dss_pipeRegs *)gDss_pipeRegInfo[i].pipeRegs;
        }
    }
    for(i = CSL_DSS_OVERLAY_ID_1; i < CSL_DSS_OVERLAY_ID_MAX; i++)
    {
        if(UTRUE == rmInfo->isOverlayAvailable[i])
        {
            gDss_SocInfo.overlayRegs[i] =
                    (CSL_dss_overlayRegs *)gDss_overlayRegInfo[i].overlayRegs;
        }
    }
    for(i = CSL_DSS_VP_ID_1; i < CSL_DSS_VP_ID_MAX; i++)
    {
        if(UTRUE == rmInfo->isPortAvailable[i])
        {
            gDss_SocInfo.vpRegs[i] =
                    (CSL_dss_vpRegs *)gDss_vpRegInfo[i].vpRegs;
        }
    }
    for(i = CSL_DSS_WB_PIPE_ID_1; i < CSL_DSS_WB_PIPE_ID_MAX; i++)
    {
        if(UTRUE == rmInfo->isWbPipeAvailable[i])
        {
            gDss_SocInfo.wbRegs[i] =
                    (CSL_dss_wbRegs *)gDss_wbRegInfo[i].wbPipeRegs;
        }
    }
}

const Dss_SocInfo* Dss_getSocInfo(void)
{
    return (const Dss_SocInfo*)(&gDss_SocInfo);
}

int32_t Dss_convNodetoModule(uint32_t nodeId,
                             uint32_t *moduleId)
{
    int32_t retVal = FVID2_EFAIL;
    uint32_t i;
    *moduleId = CSL_DSS_MODULE_INVALID;

    for(i = 0U;
        i < (sizeof (gDss_DctrlNodeIdInfo) / sizeof (gDss_DctrlNodeIdInfo[0U]));
        i++)
    {
        if(nodeId == gDss_DctrlNodeIdInfo[i].nodeId)
        {
            *moduleId = gDss_DctrlNodeIdInfo[i].moduleId;
            retVal = FVID2_SOK;
            break;
        }
    }

    return (retVal);
}

int32_t Dss_convModuletoNode(uint32_t *nodeId,
                             uint32_t  moduleId,
                             uint32_t  nodeType)
{
    int32_t retVal = FVID2_EFAIL;
    uint32_t i;
    *nodeId = DSS_DCTRL_NODE_INVALID;

    for(i = 0U;
        i < (sizeof (gDss_DctrlNodeIdInfo) / sizeof (gDss_DctrlNodeIdInfo[0U]));
        i++)
    {
        if((moduleId == gDss_DctrlNodeIdInfo[i].moduleId) &&
        (nodeType == gDss_DctrlNodeIdInfo[i].nodeType))
        {
            *nodeId = gDss_DctrlNodeIdInfo[i].nodeId;
            retVal = FVID2_SOK;
            break;
        }
    }

    return (retVal);
}

void Dss_convEventGrouptoModule(uint32_t eventGroup,
                                uint32_t *moduleId)
{
    uint32_t i;
    *moduleId = CSL_DSS_MODULE_INVALID;

    for(i = 0U;
        i < (sizeof (gDss_EventGroupInfo) / sizeof (gDss_EventGroupInfo[0U]));
        i++)
    {
        if(eventGroup == gDss_EventGroupInfo[i].eventGroup)
        {
            *moduleId = gDss_EventGroupInfo[i].moduleId;
            break;
        }
    }
}

void Dss_convModuletoEventGroup(uint32_t *eventGroup,
                                uint32_t moduleId,
                                uint32_t eventGroupType)
{
    uint32_t i;
    *eventGroup = DSS_EVENT_GROUP_INVALID;

    for(i = 0U;
        i < (sizeof (gDss_EventGroupInfo) / sizeof (gDss_EventGroupInfo[0U]));
        i++)
    {
        if((moduleId == gDss_EventGroupInfo[i].moduleId) &&
           (eventGroupType == gDss_EventGroupInfo[i].eventGroupType))
        {
            *eventGroup = gDss_EventGroupInfo[i].eventGroup;
            break;
        }
    }
}

uint32_t Dss_getVpConnId(uint32_t overlayId)
{
    uint32_t vpId = CSL_DSS_MODULE_INVALID, i;

    for(i = 0U;
        i < (sizeof(gDss_OverlayConnInfo)/sizeof(gDss_OverlayConnInfo[0U]));
        i++)
    {
        if(overlayId == gDss_OverlayConnInfo[i].overlayId)
        {
            vpId = gDss_OverlayConnInfo[i].vpId;
            break;
        }
    }

    return vpId;
}

int32_t Dss_enableL1Event(Dss_EvtMgrInfo *evtMgrInfo,
                          uint32_t dssCommonRegionId,
                          uint32_t eventGroup,
                          uint32_t event,
                          uint32_t eventCnt)
{
    int32_t retVal = FVID2_SOK;
    uint32_t regVal;
    CSL_dss_commRegs *commRegs;
    const Dss_SocInfo *socInfo;

    GT_assert(DssTrace, (NULL != evtMgrInfo));

    /* Get common register space */
    socInfo = Dss_getSocInfo();
    commRegs = socInfo->commRegs[dssCommonRegionId];
    GT_assert(DssTrace, (NULL != commRegs));

    if(DSS_EVENT_GROUP_VP1 == eventGroup)
    {
        /* Clear the status of interrupt */
        regVal = CSL_REG32_RD(&commRegs->VP_IRQSTATUS_0);
        regVal |= eventGroup;
        CSL_REG32_WR(&commRegs->VP_IRQSTATUS_0, regVal);

        /* Enable the interrupts at the VP1 level */
        regVal = CSL_REG32_RD(&commRegs->VP_IRQENABLE_0);
        regVal |= event;
        CSL_REG32_WR(&commRegs->VP_IRQENABLE_0, regVal);

        /* Store the register address in evtMgrInfo instance */
        evtMgrInfo->l1EnableReg[eventCnt] = &commRegs->VP_IRQENABLE_0;
        evtMgrInfo->l1StatusReg[eventCnt] = &commRegs->VP_IRQSTATUS_0;
        evtMgrInfo->l1Mask[eventCnt] = event;
        evtMgrInfo->allEvents[eventCnt] = event;
    }
    else if(DSS_EVENT_GROUP_VP2 == eventGroup)
    {
        /* Clear the status of interrupt */
        regVal = CSL_REG32_RD(&commRegs->VP_IRQSTATUS_1);
        regVal |= eventGroup;
        CSL_REG32_WR(&commRegs->VP_IRQSTATUS_1, regVal);

        /* Enable the interrupts at the VP2 level */
        regVal = CSL_REG32_RD(&commRegs->VP_IRQENABLE_1);
        regVal |= event;
        CSL_REG32_WR(&commRegs->VP_IRQENABLE_1, regVal);

        /* Store the register address in evtMgrInfo instance */
        evtMgrInfo->l1EnableReg[eventCnt] = &commRegs->VP_IRQENABLE_1;
        evtMgrInfo->l1StatusReg[eventCnt] = &commRegs->VP_IRQSTATUS_1;
        evtMgrInfo->l1Mask[eventCnt] = event;
        evtMgrInfo->allEvents[eventCnt] = event;
    }
    else if(DSS_EVENT_GROUP_VP3 == eventGroup)
    {
        /* Clear the status of interrupt */
        regVal = CSL_REG32_RD(&commRegs->VP_IRQSTATUS_2);
        regVal |= eventGroup;
        CSL_REG32_WR(&commRegs->VP_IRQSTATUS_2, regVal);

        /* Enable the interrupts at the VP3 level */
        regVal = CSL_REG32_RD(&commRegs->VP_IRQENABLE_2);
        regVal |= event;
        CSL_REG32_WR(&commRegs->VP_IRQENABLE_2, regVal);

        /* Store the register address in evtMgrInfo instance */
        evtMgrInfo->l1EnableReg[eventCnt] = &commRegs->VP_IRQENABLE_2;
        evtMgrInfo->l1StatusReg[eventCnt] = &commRegs->VP_IRQSTATUS_2;
        evtMgrInfo->l1Mask[eventCnt] = event;
        evtMgrInfo->allEvents[eventCnt] = event;
    }
    else if(DSS_EVENT_GROUP_VP4 == eventGroup)
    {
        /* Clear the status of interrupt */
        regVal = CSL_REG32_RD(&commRegs->VP_IRQSTATUS_3);
        regVal |= eventGroup;
        CSL_REG32_WR(&commRegs->VP_IRQSTATUS_3, regVal);

        /* Enable the interrupts at the VP4 level */
        regVal = CSL_REG32_RD(&commRegs->VP_IRQENABLE_3);
        regVal |= event;
        CSL_REG32_WR(&commRegs->VP_IRQENABLE_3, regVal);

        /* Store the register address in evtMgrInfo instance */
        evtMgrInfo->l1EnableReg[eventCnt] = &commRegs->VP_IRQENABLE_3;
        evtMgrInfo->l1StatusReg[eventCnt] = &commRegs->VP_IRQSTATUS_3;
        evtMgrInfo->l1Mask[eventCnt] = event;
        evtMgrInfo->allEvents[eventCnt] = event;
    }
    else if(DSS_EVENT_GROUP_VID1 == eventGroup)
    {
        /* Clear the status of interrupt */
        regVal = CSL_REG32_RD(&commRegs->VID_IRQSTATUS_0);
        regVal |= eventGroup;
        CSL_REG32_WR(&commRegs->VID_IRQSTATUS_0, regVal);

        /* Enable the interrupts at the VID1 Pipe level */
        regVal = CSL_REG32_RD(&commRegs->VID_IRQENABLE_0);
        regVal |= event;
        CSL_REG32_WR(&commRegs->VID_IRQENABLE_0, regVal);

        /* Store the register address in evtMgrInfo instance */
        evtMgrInfo->l1EnableReg[eventCnt] = &commRegs->VID_IRQENABLE_0;
        evtMgrInfo->l1StatusReg[eventCnt] = &commRegs->VID_IRQSTATUS_0;
        evtMgrInfo->l1Mask[eventCnt] = event;
        evtMgrInfo->allEvents[eventCnt] = event;
    }
    else if(DSS_EVENT_GROUP_VIDL1 == eventGroup)
    {
        /* Clear the status of interrupt */
        regVal = CSL_REG32_RD(&commRegs->VID_IRQSTATUS_1);
        regVal |= eventGroup;
        CSL_REG32_WR(&commRegs->VID_IRQSTATUS_1, regVal);

        /* Enable the interrupts at the VIDL1 Pipe level */
        regVal = CSL_REG32_RD(&commRegs->VID_IRQENABLE_1);
        regVal |= event;
        CSL_REG32_WR(&commRegs->VID_IRQENABLE_1, regVal);

        /* Store the register address in evtMgrInfo instance */
        evtMgrInfo->l1EnableReg[eventCnt] = &commRegs->VID_IRQENABLE_1;
        evtMgrInfo->l1StatusReg[eventCnt] = &commRegs->VID_IRQSTATUS_1;
        evtMgrInfo->l1Mask[eventCnt] = event;
        evtMgrInfo->allEvents[eventCnt] = event;
    }
    else if(DSS_EVENT_GROUP_VID2 == eventGroup)
    {
        /* Clear the status of interrupt */
        regVal = CSL_REG32_RD(&commRegs->VID_IRQSTATUS_2);
        regVal |= eventGroup;
        CSL_REG32_WR(&commRegs->VID_IRQSTATUS_2, regVal);

        /* Enable the interrupts at the VID2 Pipe level */
        regVal = CSL_REG32_RD(&commRegs->VID_IRQENABLE_2);
        regVal |= event;
        CSL_REG32_WR(&commRegs->VID_IRQENABLE_2, regVal);

        /* Store the register address in evtMgrInfo instance */
        evtMgrInfo->l1EnableReg[eventCnt] = &commRegs->VID_IRQENABLE_2;
        evtMgrInfo->l1StatusReg[eventCnt] = &commRegs->VID_IRQSTATUS_2;
        evtMgrInfo->l1Mask[eventCnt] = event;
        evtMgrInfo->allEvents[eventCnt] = event;
    }
    else if(DSS_EVENT_GROUP_VIDL2 == eventGroup)
    {
        /* Clear the status of interrupt */
        regVal = CSL_REG32_RD(&commRegs->VID_IRQSTATUS_3);
        regVal |= eventGroup;
        CSL_REG32_WR(&commRegs->VID_IRQSTATUS_3, regVal);

        /* Enable the interrupts at the VIDL2 Pipe level */
        regVal = CSL_REG32_RD(&commRegs->VID_IRQENABLE_3);
        regVal |= event;
        CSL_REG32_WR(&commRegs->VID_IRQENABLE_3, regVal);

        /* Store the register address in evtMgrInfo instance */
        evtMgrInfo->l1EnableReg[eventCnt] = &commRegs->VID_IRQENABLE_3;
        evtMgrInfo->l1StatusReg[eventCnt] = &commRegs->VID_IRQSTATUS_3;
        evtMgrInfo->l1Mask[eventCnt] = event;
        evtMgrInfo->allEvents[eventCnt] = event;
    }
    else if(DSS_EVENT_GROUP_WB == eventGroup)
    {
        /* Clear the status of interrupt */
        regVal = CSL_REG32_RD(&commRegs->WB_IRQSTATUS);
        regVal |= eventGroup;
        CSL_REG32_WR(&commRegs->WB_IRQSTATUS, regVal);

        /* Enable the interrupts at the WB Pipe level */
        regVal = CSL_REG32_RD(&commRegs->WB_IRQENABLE);
        regVal |= event;
        CSL_REG32_WR(&commRegs->WB_IRQENABLE, regVal);

        /* Store the register address in evtMgrInfo instance */
        evtMgrInfo->l1EnableReg[eventCnt] = &commRegs->WB_IRQENABLE;
        evtMgrInfo->l1StatusReg[eventCnt] = &commRegs->WB_IRQSTATUS;
        evtMgrInfo->l1Mask[eventCnt] = event;
        evtMgrInfo->allEvents[eventCnt] = event;
    }
    else
    {
        GT_assert(DssTrace, BFALSE);
        retVal = FVID2_EBADARGS;
    }

    return retVal;
}

void Dss_getEnabledVpFuncEvents(uint32_t events[DSS_EVT_MGR_MAX_CLIENT_EVENTS],
                                uint32_t *numEvts)
{
    uint32_t i;
    *numEvts = sizeof(gDss_VpFuncEvents)/sizeof(uint32_t);
    for(i = 0U; i < *numEvts; i++)
    {
        events[i] = gDss_VpFuncEvents[i];
    }
}

void Dss_getEnabledVpErrEvents(uint32_t events[DSS_EVT_MGR_MAX_CLIENT_EVENTS],
                               uint32_t *numEvts)
{
    uint32_t i;
    *numEvts = sizeof(gDss_VpErrEvents)/sizeof(uint32_t);
    for(i = 0U; i < *numEvts; i++)
    {
        events[i] = gDss_VpErrEvents[i];
    }
}

void Dss_getEnabledPipeErrEvents(uint32_t events[DSS_EVT_MGR_MAX_CLIENT_EVENTS],
                                 uint32_t *numEvts)
{
    uint32_t i;
    *numEvts = sizeof(gDss_PipeErrEvents)/sizeof(uint32_t);
    for(i = 0U; i < *numEvts; i++)
    {
        events[i] = gDss_PipeErrEvents[i];
    }
}

void Dss_getEnabledWbPipeFuncEvents(uint32_t events[DSS_EVT_MGR_MAX_CLIENT_EVENTS],
                                    uint32_t *numEvts)
{
    uint32_t i;
    *numEvts = sizeof(gDss_WbFuncEvents)/sizeof(uint32_t);
    for(i = 0U; i < *numEvts; i++)
    {
        events[i] = gDss_WbFuncEvents[i];
    }
}

uint32_t Dss_dctrlIsPipeNode(uint32_t nodeId)
{
    uint32_t isPipeNode = UFALSE;

    if((DSS_DCTRL_NODE_VID1  == nodeId) ||
       (DSS_DCTRL_NODE_VIDL1 == nodeId) ||
       (DSS_DCTRL_NODE_VID2  == nodeId) ||
       (DSS_DCTRL_NODE_VIDL2 == nodeId))
    {
        isPipeNode = UTRUE;
    }

    return (isPipeNode);
}

uint32_t Dss_dctrlIsValidNode(uint32_t nodeId)
{
    uint32_t i, isValidNode = UFALSE, graphNodeInfoSize = 0U;
    const Fvid2_GraphNodeInfo *graphNodeInfo;

    graphNodeInfo = Dss_dctrlGetDefaultNodeInfo(&graphNodeInfoSize);

    for(i = 1U; i < graphNodeInfoSize; i++)
    {
        if(nodeId == graphNodeInfo[i].nodeId)
        {
            isValidNode = UTRUE;
            break;
        }
    }

    return (isValidNode);
}

uint32_t Dss_dctrlIsVideoMuxNeeded(uint32_t vpNodeId,
                                   uint32_t outNodeId)
{
    uint32_t isMuxNeeded = UFALSE;

    if(((DSS_DCTRL_NODE_DPI_DPI0 == outNodeId) ||
        (DSS_DCTRL_NODE_DPI_DPI1 == outNodeId)) &&
       ((DSS_DCTRL_NODE_VP2 == vpNodeId) ||
        (DSS_DCTRL_NODE_VP4 == vpNodeId)))
    {
        isMuxNeeded = UTRUE;
    }

    return isMuxNeeded;
}

int32_t Dss_dctrlProgramVideoMux(uint32_t vpNodeId,
                                 uint32_t outNodeId)
{
    int32_t retVal = FVID2_SOK;
    uint32_t vpId, outId;
    const Dss_SocInfo *socInfo;
    CSL_dss_commRegs *commRegs;

    /* Get common registers */
    socInfo = Dss_getSocInfo();
    commRegs = socInfo->commRegs[CSL_DSS_COMM_REG_ID_0];
    GT_assert(DssTrace, (NULL != commRegs));
    /* Get video port id */
    retVal = Dss_convNodetoModule(vpNodeId, &vpId);
    GT_assert(DssTrace, (CSL_DSS_MODULE_INVALID != vpId));
    /* Get output module id */
    retVal = Dss_convNodetoModule(outNodeId, &outId);
    GT_assert(DssTrace, (CSL_DSS_MODULE_INVALID != outId));
    retVal = CSL_dssConnectVpToDpi(commRegs, vpId, outId);

    return (retVal);
}

uint32_t Dss_getEvtMgrFuncIntrId(void)
{
    uint32_t evtMgrId;

    evtMgrId = DSS_EVT_MGR_INST_ID_FUNC;

    return evtMgrId;
}

uint32_t Dss_getEvtMgrSafetyIntrId(void)
{
    uint32_t evtMgrId;

    evtMgrId = DSS_EVT_MGR_INST_ID_SAFETY;

    return evtMgrId;
}

uint32_t Dss_getEvtMgrSecurityIntrId(void)
{
    uint32_t evtMgrId;

    evtMgrId = DSS_EVT_MGR_INST_ID_SECURITY;

    return evtMgrId;
}

int32_t Dss_fillEvtMgrInitInfo(Dss_EvtMgrInitParams *evtMgrParams,
                               Dss_IrqParams *irqParams)
{
    int32_t retVal = FVID2_SOK;

    evtMgrParams->dssCommonRegionId = irqParams->dssCommonRegionId;
    evtMgrParams->numIrq = irqParams->numValidIrq;
    evtMgrParams->irqNum[0U] = irqParams->irqNum[DSS_EVT_MGR_INST_ID_FUNC];
    evtMgrParams->instId[0U] = DSS_EVT_MGR_INST_ID_FUNC;
    evtMgrParams->irqNum[1U] = irqParams->irqNum[DSS_EVT_MGR_INST_ID_SAFETY];
    evtMgrParams->instId[1U] = DSS_EVT_MGR_INST_ID_SAFETY;
    evtMgrParams->irqNum[2U] = irqParams->irqNum[DSS_EVT_MGR_INST_ID_SECURITY];
    evtMgrParams->instId[2U] = DSS_EVT_MGR_INST_ID_SECURITY;

    return retVal;
}

uint32_t Dss_dctrlGetVpSafetyRegionId(uint32_t evtId)
{
    uint32_t i;
    uint32_t regionId = CSL_DSS_VP_SAFETY_REGION_INVALID;

    for(i = 0U;
        i < (sizeof (gDss_VpSafetyRegionIdInfo) /
           sizeof (gDss_VpSafetyRegionIdInfo[0U]));
        i++)
    {
        if(evtId == gDss_VpSafetyRegionIdInfo[i].regionErrEvt)
        {
            regionId = gDss_VpSafetyRegionIdInfo[i].regionId;
            break;
        }
    }

    return (regionId);
}

uint32_t Dss_dctrlIsSafetyEvent(uint32_t evtId)
{
    uint32_t retVal = UFALSE;
    if((DSS_VP_EVENT_SAFETY_VIOLATION_0 <= evtId) &&
       (DSS_VP_EVENT_SAFETY_VIOLATION_7 >= evtId))
    {
        retVal = UTRUE;
    }
    return retVal;
}


uint32_t Dss_dctrlGetVpSafetyEvtId(uint32_t regionId)
{
    uint32_t i;
    uint32_t evtId = DSS_VP_EVENT_INVALID;

    for(i = 0U;
        i < (sizeof (gDss_VpSafetyRegionIdInfo) /
           sizeof (gDss_VpSafetyRegionIdInfo[0U]));
        i++)
    {
        if(regionId == gDss_VpSafetyRegionIdInfo[i].regionId)
        {
            evtId = gDss_VpSafetyRegionIdInfo[i].regionErrEvt;
            break;
        }
    }

    return (evtId);
}
