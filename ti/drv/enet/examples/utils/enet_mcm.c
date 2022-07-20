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

/*!
 * \file enet_mcm.c
 *
 * \brief This file contains Multi-client Manager related functionality.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
/* This is needed for memset/memcpy */
#include <string.h>

#include <ti/osal/osal.h>
#include <ti/osal/TaskP.h>
#include <ti/osal/ClockP.h>
#include <ti/osal/SemaphoreP.h>
#include <ti/osal/MailboxP.h>
#include <ti/osal/MutexP.h>
#include <ti/osal/HwiP.h>

#include "include/enet_apputils.h"
#include "include/enet_appmemutils.h"
#include "include/enet_appsoc.h"
#include "include/enet_mcm.h"

#include <ti/drv/enet/include/core/enet_soc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define ENETMCM_TSK_STACK_MAIN              (8U * 1024U)
#define ENETMCM_MBOX_MSG_COUNT              (10U)
#define ENETMCM_TSK_PRIORITY                (2U)
#define ENETMCM_PERIODICTSK_PRIORITY        (7U)
#define ENETMCM_ASYNCIOCTLTASK_PRIORITY     (9U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/*!
 * \brief CPSW MCM handle
 *
 * CPSW MCM opaque handle.
 */
typedef struct EnetMcm_Obj_s *EnetMcm_Handle;

typedef struct EnetMcm_CoreAttachTableEntry_s
{
    uint32_t coreId;
    EnetPer_AttachCoreOutArgs coreInfo;
}  EnetMcm_CoreAttachTableEntry;

typedef struct EnetMcm_CoreAttachTable_s
{
    uint32_t numCoresAttached;
    EnetMcm_CoreAttachTableEntry entry[ENET_CFG_REMOTE_CLIENT_CORES_MAX];
}  EnetMcm_CoreAttachTable;

typedef struct EnetMcm_Obj_s
{
    bool isInitDone;

    uint8_t refCnt;

    Enet_Type enetType;

    uint32_t instId;

    Enet_Handle hEnet;

#if !(defined(SOC_TPR12) || defined(SOC_AWR294X))
    Udma_DrvHandle hUdmaDrv;
#endif

    Cpsw_Cfg cpswCfg;

#if defined(ENET_ENABLE_ICSSG)
    Icssg_Cfg icssgCfg;
#endif

#if (defined(SOC_TPR12) || defined(SOC_AWR294X))
    EnetCpdma_Cfg dmaCfg;
#else
    EnetUdma_Cfg dmaCfg;
#endif

    uint32_t selfCoreId;

    EnetMcm_setPortLinkCfg setPortLinkCfg;

    Enet_MacPort macPortList[ENET_MAC_PORT_NUM];

    uint8_t numMacPorts;

    TaskP_Handle task;

    MailboxP_Handle hMboxCmd;

    MailboxP_Handle hMboxResponse;

    ClockP_Handle hTimer;

    TaskP_Handle task_periodicTick;

    SemaphoreP_Handle timerSem;

    volatile bool timerTaskShutDownFlag;

    MutexP_Object mutexObj;

    MutexP_Handle hMutex;

    uint32_t periodicTaskPeriod;

    EnetMcm_CoreAttachTable coreAttachTable;

    Enet_Print print;

    /* Async IOCTL handling */

    /*! Whether an ICSSG async IOCTL is complete or not */
    volatile bool asyncIoctlDone;

    /*! Flag to indicate that async IOCTL task should be shut down */
    bool asyncIoctlTaskShutdown;

    /*! Async IOCTL task that pends on asyncIoctlSem and then indicates
     *  IOCTL completion */
    TaskP_Handle asyncIoctlTask;

    /*! Semaphore used to wait for async IOCTL completion. It's posted from
     *  async IOCTL callback which is called from Enet_poll() */
    SemaphoreP_Handle asyncIoctlSem;
}EnetMcm_Obj;

typedef enum EnetMcm_Command_e
{
    /*! GET CPSW & UDMA HANDLE */
    MCM_GET_HANDLE,

    /*! RELEASE HANDLE */
    MCM_RELEASE_HANDLE,

    /*! ATTACH core */
    MCM_CORE_ATTACH,

    /*! DETACH core */
    MCM_CORE_DETACH,

    /*! Run IOCTL. Mainly useful for asynchronous IOCTLs */
    MCM_IOCTL,

    /*! SHUTDOWN MCM */
    MCM_SHUTDOWN,

    /*! Response to MCM_GET_HANDLE command */
    MCM_RESPONSE_GET_HANDLE,

    /*! Response to MCM_RELEASE_HANDLE command */
    MCM_RESPONSE_RELEASE_HANDLE,

    /*! Response to MCM_CORE_ATTACH command */
    MCM_RESPONSE_CORE_ATTACH,

    /*! Response to MCM_CORE_DETACH command */
    MCM_RESPONSE_CORE_DETACH,

    /*! Response to MCM_IOCL command */
    MCM_RESPONSE_IOCTL,

    /*! Response to SHUTDOWN MCM */
    MCM_RESPONSE_SHUTDOWN,
}
EnetMcm_Command;

typedef struct EnetMcm_mailboxObj_s
{
    EnetMcm_Command cmd;

    struct EnetMcm_mailboxMsgs_s
    {
        uint32_t coreId;
        uint32_t coreKey;
        uint32_t ioctlStatus;
        uint32_t ioctlCmd;
        Enet_IoctlPrms *ioctlPrms;
        EnetMcm_HandleInfo handleInfo;
        EnetPer_AttachCoreOutArgs attachInfo;
    } msgBody;
}EnetMcm_mailboxObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static int32_t  EnetMcm_open(EnetMcm_Handle hMcm);

static void     EnetMcm_close(EnetMcm_Handle hMcm);

static void     EnetMcm_serverTask(void * hMcm);

static int32_t  EnetMcm_enablePorts(EnetMcm_Handle hMcm);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static EnetMcm_Obj gMcmObj[] =
{
    [ENET_CPSW_2G] =
    {
        .isInitDone             = false,
        .timerTaskShutDownFlag  = false,
        .hMutex                 = NULL,
        .task                   = NULL,
        .hMboxCmd               = NULL,
        .hMboxResponse          = NULL,
        .hTimer                 = NULL,
        .task_periodicTick      = NULL,
        .timerSem               = NULL,
        .asyncIoctlDone         = false,
        .asyncIoctlTaskShutdown = false,
        .asyncIoctlTask         = NULL,
        .asyncIoctlSem          = NULL,
    },

    [ENET_CPSW_9G] =
    {
        .isInitDone             = false,
        .timerTaskShutDownFlag  = false,
        .hMutex                 = NULL,
        .task                   = NULL,
        .hMboxCmd               = NULL,
        .hMboxResponse          = NULL,
        .hTimer                 = NULL,
        .task_periodicTick      = NULL,
        .timerSem               = NULL,
        .asyncIoctlDone         = false,
        .asyncIoctlTaskShutdown = false,
        .asyncIoctlTask         = NULL,
        .asyncIoctlSem          = NULL,

    },

    [ENET_ICSSG_DUALMAC] =
    {
        .isInitDone             = false,
        .timerTaskShutDownFlag  = false,
        .hMutex                 = NULL,
        .task                   = NULL,
        .hMboxCmd               = NULL,
        .hMboxResponse          = NULL,
        .hTimer                 = NULL,
        .task_periodicTick      = NULL,
        .timerSem               = NULL,
        .asyncIoctlDone         = false,
        .asyncIoctlTaskShutdown = false,
        .asyncIoctlTask         = NULL,
        .asyncIoctlSem          = NULL,

    },

    [ENET_ICSSG_SWITCH] =
    {
        .isInitDone             = false,
        .timerTaskShutDownFlag  = false,
        .hMutex                 = NULL,
        .task                   = NULL,
        .hMboxCmd               = NULL,
        .hMboxResponse          = NULL,
        .hTimer                 = NULL,
        .task_periodicTick      = NULL,
        .timerSem               = NULL,
        .asyncIoctlDone         = false,
        .asyncIoctlTaskShutdown = false,
        .asyncIoctlTask         = NULL,
        .asyncIoctlSem          = NULL,
    },
};

uint8_t mcmMainTaskStack[ENETMCM_TSK_STACK_MAIN] __attribute__ ((aligned(32)));

uint8_t mcmPrdTaskStack[ENETMCM_TSK_STACK_MAIN] __attribute__ ((aligned(32)));

uint8_t asyncIoctlTaskStack[ENETMCM_TSK_STACK_MAIN] __attribute__ ((aligned(32)));

uint8_t mcmRequestMbxBuf[sizeof(EnetMcm_mailboxObj) * ENETMCM_MBOX_MSG_COUNT] __attribute__ ((aligned(32)));

uint8_t mcmResponseMbxBuf[sizeof(EnetMcm_mailboxObj) * ENETMCM_MBOX_MSG_COUNT] __attribute__ ((aligned(32)));

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#if defined(ENET_ENABLE_ICSSG)
static void EnetMcm_evtCb(Enet_Event evt,
                          uint32_t evtNum,
                          void *evtCbArgs,
                          void *arg1,
                          void *arg2)
{
    if (ENET_EVT_ASYNC_CMD_RESP == evt)
    {
        SemaphoreP_Handle asyncIoctlSem = (SemaphoreP_Handle)evtCbArgs;
        SemaphoreP_post(asyncIoctlSem);
    }
    else
    {
        EnetAppUtils_print("Unhandled Event: %d\n", evtNum);
    }
}
#endif

static void EnetMcm_asyncIoctlTask(void * arg0,
                                   void * arg1)
{
    EnetMcm_Handle hMcm = (EnetMcm_Handle)arg0;
    SemaphoreP_Handle asyncIoctlSem = (SemaphoreP_Handle)arg1;

    while (!hMcm->asyncIoctlTaskShutdown)
    {
        SemaphoreP_pend(asyncIoctlSem, SemaphoreP_WAIT_FOREVER);
        hMcm->asyncIoctlDone = true;
    }
}

static void EnetMcm_initAttachTable(EnetMcm_CoreAttachTable *attachTbl)
{
    uint32_t i;

    attachTbl->numCoresAttached = 0;
    for (i = 0; i < ENET_ARRAYSIZE(attachTbl->entry); i++)
    {
        attachTbl->entry[i].coreId = ENET_RM_INVALIDCORE;
    }
}

static EnetMcm_CoreAttachTableEntry *EnetMcm_getCoreAttachEntry(EnetMcm_CoreAttachTable *attachTbl,
                                                                uint32_t coreId)
{
    uint32_t i;
    EnetMcm_CoreAttachTableEntry *entry;

    entry = NULL;
    for (i = 0; i < attachTbl->numCoresAttached; i++)
    {
        if (attachTbl->entry[i].coreId == coreId)
        {
            entry = &attachTbl->entry[i];
            break;
        }
    }

    return entry;
}

static void EnetMcm_addCoreAttachEntry(EnetMcm_CoreAttachTable *attachTbl,
                                       uint32_t coreId,
                                       EnetPer_AttachCoreOutArgs *coreInfo)
{
    EnetMcm_CoreAttachTableEntry *entry;

    entry = EnetMcm_getCoreAttachEntry(attachTbl, coreId);
    if (entry == NULL)
    {
        EnetAppUtils_assert(attachTbl->numCoresAttached < ENET_ARRAYSIZE(attachTbl->entry));
        attachTbl->entry[attachTbl->numCoresAttached].coreId   = coreId;
        attachTbl->entry[attachTbl->numCoresAttached].coreInfo = *coreInfo;
        attachTbl->numCoresAttached++;
    }
    else
    {
        uint32_t i;

        EnetAppUtils_assert(entry->coreId == coreId);
        EnetAppUtils_assert(entry->coreInfo.coreKey == coreInfo->coreKey);
        EnetAppUtils_assert(entry->coreInfo.rxMtu == coreInfo->rxMtu);
        for (i = 0; i < ENET_ARRAYSIZE(entry->coreInfo.txMtu); i++)
        {
            EnetAppUtils_assert(entry->coreInfo.txMtu[i] == coreInfo->txMtu[i]);
        }
    }
}

static void EnetMcm_delCoreAttachEntry(EnetMcm_CoreAttachTable *attachTbl,
                                       uint32_t coreId,
                                       uint32_t coreKey)
{
    uint32_t i;
    EnetMcm_CoreAttachTableEntry *entry;

    entry = EnetMcm_getCoreAttachEntry(attachTbl, coreId);
    if (entry != NULL)
    {
        EnetAppUtils_assert(attachTbl->numCoresAttached > 0);
        for (i = 0; i < attachTbl->numCoresAttached; i++)
        {
            if (attachTbl->entry[i].coreId == coreId)
            {
                break;
            }
        }

        EnetAppUtils_assert(i < attachTbl->numCoresAttached);
        EnetAppUtils_assert(attachTbl->entry[i].coreId == coreId);
        EnetAppUtils_assert(attachTbl->entry[i].coreInfo.coreKey == coreKey);
        /* Move the last entry to the freed entry */
        attachTbl->numCoresAttached--;
        attachTbl->entry[i] = attachTbl->entry[attachTbl->numCoresAttached];
    }
}

static void EnetMcm_initMbox(EnetMcm_Handle hMcm)
{
    TaskP_Params params;

    MailboxP_Params mboxParams;

    MailboxP_Params_init(&mboxParams);
    mboxParams.name = (uint8_t *)"MCM Request MBX";
    mboxParams.size =  sizeof(EnetMcm_mailboxObj);
    mboxParams.count = ENETMCM_MBOX_MSG_COUNT;
    mboxParams.buf = (void *)mcmRequestMbxBuf;
    mboxParams.bufsize = sizeof(EnetMcm_mailboxObj) * ENETMCM_MBOX_MSG_COUNT;

    hMcm->hMboxCmd = MailboxP_create(&mboxParams);
    EnetAppUtils_assert(hMcm->hMboxCmd != NULL);

    MailboxP_Params_init(&mboxParams);
    mboxParams.name = (uint8_t *)"MCM Response MBX";
    mboxParams.size =  sizeof(EnetMcm_mailboxObj);
    mboxParams.count = ENETMCM_MBOX_MSG_COUNT;
    mboxParams.buf = (void *)mcmResponseMbxBuf;
    mboxParams.bufsize = sizeof(EnetMcm_mailboxObj) * ENETMCM_MBOX_MSG_COUNT;

    hMcm->hMboxResponse = MailboxP_create(&mboxParams);
    EnetAppUtils_assert(hMcm->hMboxResponse != NULL);

    TaskP_Params_init(&params);

    params.priority  = ENETMCM_TSK_PRIORITY;
    params.stack     = &mcmMainTaskStack[0];
    params.stacksize = ENETMCM_TSK_STACK_MAIN;
    params.arg0      = hMcm;

    switch (hMcm->enetType)
    {
        case ENET_CPSW_2G:
            params.name = (uint8_t *)"MCM2G_Task";
            break;

#if defined(SOC_J7200)
    case ENET_CPSW_5G:
            params.name = (uint8_t *)"MCM5G_Task";
            break;
#endif
#if defined(SOC_J721E)
    case ENET_CPSW_9G:
            params.name = (uint8_t *)"MCM9G_Task";
            break;
#endif
#if defined(ENET_ENABLE_ICSSG)
    case ENET_ICSSG_DUALMAC:
            params.name = (uint8_t *)"MCMICSSG_Task";
            break;
    case ENET_ICSSG_SWITCH:
            params.name = (uint8_t *)"MCMICSSG_SWITCH_Task";
            break;
#endif

        default:
            EnetAppUtils_assert(false);
    }

    hMcm->task = TaskP_create((void *)EnetMcm_serverTask, &params);

    EnetAppUtils_assert(hMcm->task != NULL);
}

static int32_t EnetMcm_validateInitCfg(const EnetMcm_InitConfig *pMcmInitCfg)
{
    int32_t status = ENET_SOK;
#if !(defined(SOC_TPR12) || defined(SOC_AWR294X))
    EnetUdma_Cfg *udmaCfg = NULL;
    Cpsw_Cfg *cpswCfg;
#endif
    Enet_Type enetType;
    uint32_t instId;
#if defined(ENET_ENABLE_ICSSG)
    Icssg_Cfg *icssgCfg;
#endif

    if ((pMcmInitCfg != NULL) &&
        (pMcmInitCfg->perCfg != NULL) &&
        (pMcmInitCfg->setPortLinkCfg != NULL))
    {
        enetType = pMcmInitCfg->enetType;
        instId = pMcmInitCfg->instId;

        if (Enet_isCpswFamily(enetType))
        {
#if !(defined(SOC_TPR12) || defined(SOC_AWR294X))
            cpswCfg = (Cpsw_Cfg *) pMcmInitCfg->perCfg;
            udmaCfg = (EnetUdma_Cfg *)cpswCfg->dmaCfg;
#endif
        }
#if defined(ENET_ENABLE_ICSSG)
        else
        {
            icssgCfg = (Icssg_Cfg *) pMcmInitCfg->perCfg;
            udmaCfg = (EnetUdma_Cfg *)icssgCfg->dmaCfg;
        }
#endif
#if !(defined(SOC_TPR12) || defined(SOC_AWR294X))
        if ((udmaCfg == NULL) || (udmaCfg->hUdmaDrv == NULL))
        {
            status = ENET_EINVALIDPARAMS;
        }
#endif

        if ((enetType == ENET_CPSW_2G) &&
            ((pMcmInitCfg->numMacPorts != EnetSoc_getMacPortMax(enetType, instId)) ||
             (pMcmInitCfg->macPortList[0] != ENET_MAC_PORT_1)))
        {
            status = ENET_EINVALIDPARAMS;
        }

        if ((pMcmInitCfg->numMacPorts > EnetSoc_getMacPortMax(enetType, instId)))
        {
            status = ENET_EINVALIDPARAMS;
        }

    }
    else
    {
        status = ENET_EINVALIDPARAMS;
    }

    return status;
}

int32_t  EnetMcm_init(const EnetMcm_InitConfig *pMcmInitCfg)
{
    int32_t status = ENET_SOK;
    uintptr_t key;
    Enet_Type enetType  = pMcmInitCfg->enetType;
    EnetMcm_Handle hMcm;
    Cpsw_Cfg *cpswCfg;
#if (defined(SOC_TPR12) || defined(SOC_AWR294X))
    EnetCpdma_Cfg *dmaCfg = NULL;
#else
    EnetUdma_Cfg *dmaCfg = NULL;
#endif
#if defined(ENET_ENABLE_ICSSG)
    Icssg_Cfg *icssgCfg;
#endif

    key = HwiP_disable();

    hMcm = &gMcmObj[enetType];
    if (hMcm->hMutex == NULL)
    {
        hMcm->hMutex = MutexP_create(&hMcm->mutexObj);
        EnetAppUtils_assert(hMcm->hMutex != NULL);
    }

    HwiP_restore(key);
    EnetAppUtils_assert(hMcm->hMutex != NULL);
    MutexP_lock(hMcm->hMutex, MutexP_WAIT_FOREVER);

    if (hMcm->isInitDone == false)
    {
        status = EnetMcm_validateInitCfg(pMcmInitCfg);

        if (status == ENET_SOK)
        {
            if (Enet_isCpswFamily(enetType))
            {
                cpswCfg = (Cpsw_Cfg *)pMcmInitCfg->perCfg;
                dmaCfg = (typeof(dmaCfg))cpswCfg->dmaCfg;
                hMcm->selfCoreId = cpswCfg->resCfg.selfCoreId;
                hMcm->cpswCfg = *cpswCfg;
            }
#if defined(ENET_ENABLE_ICSSG)
            else if (Enet_isIcssFamily(enetType))
            {
                icssgCfg = (Icssg_Cfg *)pMcmInitCfg->perCfg;
                dmaCfg = (typeof(dmaCfg))icssgCfg->dmaCfg;
                hMcm->selfCoreId = icssgCfg->resCfg.selfCoreId;
                hMcm->icssgCfg = *icssgCfg;
            }
#endif
            else
            {
                EnetAppUtils_assert(false);
            }

            hMcm->dmaCfg             = *dmaCfg;
            hMcm->refCnt             = 0U;
            hMcm->enetType           = enetType;
            hMcm->instId             = pMcmInitCfg->instId;
            hMcm->hEnet              = NULL;
#if !(defined(SOC_TPR12) || defined(SOC_AWR294X))
            hMcm->hUdmaDrv           = NULL;
#endif
            hMcm->setPortLinkCfg     = pMcmInitCfg->setPortLinkCfg;
            hMcm->numMacPorts        = pMcmInitCfg->numMacPorts;
            hMcm->periodicTaskPeriod = pMcmInitCfg->periodicTaskPeriod;

            hMcm->print = pMcmInitCfg->print;
            if (hMcm->print == NULL)
            {
                hMcm->print = EnetAppUtils_print;
            }

            EnetMcm_initAttachTable(&hMcm->coreAttachTable);

            memcpy(&hMcm->macPortList[0U], &pMcmInitCfg->macPortList[0U], sizeof(pMcmInitCfg->macPortList));
            EnetMcm_initMbox(hMcm);

            hMcm->isInitDone = true;
        }
    }

    MutexP_unlock(hMcm->hMutex);

    return status;
}

void  EnetMcm_getCmdIf(Enet_Type enetType,
                       EnetMcm_CmdIf *hMcmCmdIf)
{
    EnetMcm_Handle hMcm = &gMcmObj[enetType];

    EnetAppUtils_assert(hMcmCmdIf != NULL);
    EnetAppUtils_assert(hMcm->hMutex != NULL);

    MutexP_lock(hMcm->hMutex, MutexP_WAIT_FOREVER);
    EnetAppUtils_assert(hMcm->isInitDone == true);

    hMcmCmdIf->hMboxCmd      = hMcm->hMboxCmd;
    hMcmCmdIf->hMboxResponse = hMcm->hMboxResponse;

    MutexP_unlock(hMcm->hMutex);

    EnetAppUtils_assert(hMcmCmdIf->hMboxCmd != NULL);
    EnetAppUtils_assert(hMcmCmdIf->hMboxResponse != NULL);
}

void EnetMcm_deInit(Enet_Type enetType)
{
    EnetMcm_Handle hMcm = &gMcmObj[enetType];
    uint32_t numPendingmsgs;

    EnetAppUtils_assert(hMcm->hMutex != NULL);

    MutexP_lock(hMcm->hMutex, MutexP_WAIT_FOREVER);

    if (hMcm->isInitDone == true)
    {
        EnetMcm_mailboxObj msg;

        msg.cmd = MCM_SHUTDOWN;

        MailboxP_post(hMcm->hMboxCmd, &msg, MailboxP_WAIT_FOREVER);
        MailboxP_pend(hMcm->hMboxResponse, &msg, MailboxP_WAIT_FOREVER);
        EnetAppUtils_assert(msg.cmd == MCM_RESPONSE_SHUTDOWN);

        while (TaskP_isTerminated(hMcm->task) != 1)
        {
            TaskP_sleep(10);
        }
        TaskP_delete(&hMcm->task);

        numPendingmsgs = MailboxP_getNumPendingMsgs(hMcm->hMboxCmd);
        while (numPendingmsgs != 0U)
        {
            MailboxP_pend(hMcm->hMboxCmd, &msg, SemaphoreP_WAIT_FOREVER);
            numPendingmsgs = MailboxP_getNumPendingMsgs(hMcm->hMboxCmd);
        }

        MailboxP_delete(hMcm->hMboxCmd);

        numPendingmsgs = MailboxP_getNumPendingMsgs(hMcm->hMboxResponse);
        while (numPendingmsgs != 0U)
        {
            MailboxP_pend(hMcm->hMboxResponse, &msg, SemaphoreP_WAIT_FOREVER);
            numPendingmsgs = MailboxP_getNumPendingMsgs(hMcm->hMboxResponse);
        }

        MailboxP_delete(hMcm->hMboxResponse);

        EnetMcm_initAttachTable(&hMcm->coreAttachTable);
        hMcm->isInitDone = false;
    }

    MutexP_unlock(hMcm->hMutex);

    MutexP_delete(hMcm->hMutex);
    hMcm->hMutex = NULL;
}

static int32_t EnetMcm_enablePorts(EnetMcm_Handle hMcm)
{
    int32_t status = ENET_SOK;
    Enet_IoctlPrms prms;
    Enet_Handle hEnet = hMcm->hEnet;
    uint32_t coreId   = hMcm->selfCoreId;
    uint8_t i;
    bool alive;

    /* Show alive PHYs */
    for (i = 0U; i < ENET_MDIO_PHY_CNT_MAX; i++)
    {
        ENET_IOCTL_SET_INOUT_ARGS(&prms, &i, &alive);
        status = Enet_ioctl(hEnet,
                            coreId,
                            ENET_MDIO_IOCTL_IS_ALIVE,
                            &prms);
        if (status == ENET_SOK)
        {
            if (alive == true)
            {
                hMcm->print("PHY %d is alive\n", i);
            }
        }
        else
        {
            hMcm->print("Failed to get PHY %d alive status: %d\n", i, status);
        }
    }

    for (i = 0U; i < hMcm->numMacPorts; i++)
    {
        EnetPer_PortLinkCfg linkArgs;
        CpswMacPort_Cfg cpswMacCfg;
#if defined(ENET_ENABLE_ICSSG)
        IcssgMacPort_Cfg icssgMacCfg;
#endif
        if (Enet_isCpswFamily(hMcm->enetType))
        {
            linkArgs.macCfg = &cpswMacCfg;
        }
#if defined(ENET_ENABLE_ICSSG)
        else
        {
            linkArgs.macCfg = &icssgMacCfg;
        }
#endif
        linkArgs.macPort = hMcm->macPortList[i];
        hMcm->setPortLinkCfg(&linkArgs, hMcm->macPortList[i]);

        ENET_IOCTL_SET_IN_ARGS(&prms, &linkArgs);
        status = Enet_ioctl(hEnet,
                            coreId,
                            ENET_PER_IOCTL_OPEN_PORT_LINK,
                            &prms);
        if (status != ENET_SOK)
        {
            hMcm->print("EnetMcm_enablePorts() failed to open MAC port: %d\n", status);
        }

#if defined(ENET_ENABLE_ICSSG)
        if ((status == ENET_SOK) && (Enet_isIcssFamily(hMcm->enetType)))
        {
            IcssgMacPort_SetPortStateInArgs setPortStateInArgs;

            setPortStateInArgs.macPort   = hMcm->macPortList[i];
            setPortStateInArgs.portState = ICSSG_PORT_STATE_FORWARD;
            ENET_IOCTL_SET_IN_ARGS(&prms, &setPortStateInArgs);
            prms.outArgs = NULL;

            status = Enet_ioctl(hEnet, coreId, ICSSG_PER_IOCTL_SET_PORT_STATE, &prms);
            if (status == ENET_SINPROGRESS)
            {
                /* Wait for asyc ioctl to complete */
                hMcm->asyncIoctlDone = false;
                while (!hMcm->asyncIoctlDone)
                {
                    Enet_poll(hEnet, ENET_EVT_ASYNC_CMD_RESP, NULL, 0U);
                    TaskP_sleep(1);
                }

                status = ENET_SOK;
            }
            else
            {
                hMcm->print("EnetMcm_enablePorts() failed ICSSG_MACPORT_IOCTL_SET_PORT_STATE: %d\n", status);
            }
        }
#endif
    }

    if ((status == ENET_SOK) && (Enet_isCpswFamily(hMcm->enetType)))
    {
        CpswAle_SetPortStateInArgs setPortStateInArgs;

        setPortStateInArgs.portNum   = CPSW_ALE_HOST_PORT_NUM;
        setPortStateInArgs.portState = CPSW_ALE_PORTSTATE_FORWARD;
        ENET_IOCTL_SET_IN_ARGS(&prms, &setPortStateInArgs);
        prms.outArgs = NULL;
        status       = Enet_ioctl(hEnet,
                                  coreId,
                                  CPSW_ALE_IOCTL_SET_PORT_STATE,
                                  &prms);
        if (status != ENET_SOK)
        {
            hMcm->print("EnetMcm_enablePorts() failed CPSW_ALE_IOCTL_SET_PORT_STATE: %d\n", status);
        }

        if (status == ENET_SOK)
        {
            ENET_IOCTL_SET_NO_ARGS(&prms);
            status = Enet_ioctl(hEnet,
                                coreId,
                                ENET_HOSTPORT_IOCTL_ENABLE,
                                &prms);
            if (status != ENET_SOK)
            {
                hMcm->print("EnetMcm_enablePorts() Failed to enable host port: %d\n", status);
            }
        }
    }

    return status;
}

static void EnetMcm_timerCb(void * arg)
{
    SemaphoreP_Handle timerSem = (SemaphoreP_Handle)arg;

    /* Tick! */
    SemaphoreP_post(timerSem);
}

static void EnetMcm_periodicTick(void * hTimerSem,
                                 void * mcmHandle)
{
    SemaphoreP_Handle timerSem = (SemaphoreP_Handle)hTimerSem;
    EnetMcm_Handle hMcm       = (EnetMcm_Handle)mcmHandle;

    while (hMcm->timerTaskShutDownFlag != true)
    {
        SemaphoreP_pend(timerSem, SemaphoreP_WAIT_FOREVER);
        /* Enet_periodicTick should be called from only task context */
        Enet_periodicTick(hMcm->hEnet);
    }
}

static void EnetMcm_createClock(EnetMcm_Handle hMcm)
{
    TaskP_Params params;
    SemaphoreP_Params semParams;
    ClockP_Params clkParams;

    SemaphoreP_Params_init(&semParams);
    semParams.mode = SemaphoreP_Mode_COUNTING;
    hMcm->timerSem = SemaphoreP_create(0, &semParams);

    ClockP_Params_init(&clkParams);
    clkParams.startMode = ClockP_StartMode_USER;
    clkParams.period    = hMcm->periodicTaskPeriod;
    clkParams.runMode   = ClockP_RunMode_CONTINUOUS;
    clkParams.arg       = hMcm->timerSem;

    /* Creating timer and setting timer callback function*/
    hMcm->hTimer = ClockP_create((void *)&EnetMcm_timerCb,
                                &clkParams);
    if (hMcm->hTimer != NULL)
    {
        ClockP_start(hMcm->hTimer);
        hMcm->timerTaskShutDownFlag = false;
    }
    else
    {
        hMcm->print("EnetMcm_createClock() failed to create clock\n");
    }

    /* Initialize the taskperiodicTick params. Set the task priority higher than the
     * default priority (1) */
    TaskP_Params_init(&params);
    params.priority       = ENETMCM_PERIODICTSK_PRIORITY;
    params.stack          = &mcmPrdTaskStack[0];
    params.stacksize      = ENETMCM_TSK_STACK_MAIN;
    params.arg0           = hMcm->timerSem;
    params.arg1           = hMcm;
    params.name           = (uint8_t *)"Enet_PeriodicTickTask";

    hMcm->task_periodicTick = TaskP_create((void *)EnetMcm_periodicTick, &params);
    EnetAppUtils_assert(hMcm->task_periodicTick != NULL);
}

static int32_t EnetMcm_open(EnetMcm_Handle hMcm)
{
    int32_t status = ENET_SOK;
    EnetOsal_Cfg osalPrms;
    EnetUtils_Cfg utilsPrms;
    void *perCfg = NULL;
#if !(defined(SOC_TPR12) || defined(SOC_AWR294X))
    EnetUdma_Cfg *udmaCfg = &hMcm->dmaCfg;
#endif
    uint32_t cfgSize;
    TaskP_Params params;
    SemaphoreP_Params semParams;

    if (Enet_isCpswFamily(hMcm->enetType))
    {
        perCfg = &hMcm->cpswCfg;
        hMcm->cpswCfg.dmaCfg = &hMcm->dmaCfg;
        cfgSize = sizeof(hMcm->cpswCfg);
    }
#if defined(ENET_ENABLE_ICSSG)
    else if (Enet_isIcssFamily(hMcm->enetType))
    {
        perCfg = &hMcm->icssgCfg;
        cfgSize = sizeof(hMcm->icssgCfg);
    }
#endif
    else
    {
        EnetAppUtils_assert(false);
    }

    if (ENET_CPSW_2G == hMcm->enetType)
    {
        hMcm->print("EnetMcm: CPSW_2G on MCU NAVSS\n");
    }
    else if (ENET_CPSW_9G == hMcm->enetType)
    {
        hMcm->print("EnetMcm: CPSW_9G on MAIN NAVSS\n");
    }
    else if (ENET_CPSW_5G == hMcm->enetType)
    {
        hMcm->print("EnetMcm: CPSW_5G on MAIN NAVSS\n");
    }
    else if (ENET_ICSSG_DUALMAC == hMcm->enetType)
    {
        hMcm->print("EnetMcm: ICSSG Dual MAC\n");
    }
    else if (ENET_ICSSG_SWITCH == hMcm->enetType)
    {
        hMcm->print("EnetMcm: ICSSG Switch\n");
    }
    else
    {
        hMcm->print("EnetMcm: Invalid Enet Type\n");
    }

    /* Initialize CPSW driver with default OSAL, utils */
    utilsPrms.print     = hMcm->print;
    utilsPrms.physToVirt = &EnetAppUtils_phyToVirtFxn;
    utilsPrms.virtToPhys = &EnetAppUtils_virtToPhyFxn;

    Enet_initOsalCfg(&osalPrms);

    Enet_init(&osalPrms, &utilsPrms);

    status = EnetMem_init();
    EnetAppUtils_assert(ENET_SOK == status);

#if !(defined(SOC_TPR12) || defined(SOC_AWR294X))
    hMcm->hUdmaDrv = udmaCfg->hUdmaDrv;
#endif

    hMcm->hEnet = Enet_open(hMcm->enetType, hMcm->instId, perCfg, cfgSize);
    if(hMcm->hEnet == NULL)
    {
        EnetAppUtils_print("Enet_open failed\n");
        EnetAppUtils_assert(hMcm->hEnet != NULL);
    }

    SemaphoreP_Params_init(&semParams);
    semParams.mode = SemaphoreP_Mode_COUNTING;
    hMcm->asyncIoctlSem = SemaphoreP_create(0, &semParams);

    /* Initialize the taskperiodicTick params. Set the task priority higher than the
     * default priority (1) */
    TaskP_Params_init(&params);
    params.priority       = ENETMCM_ASYNCIOCTLTASK_PRIORITY;
    params.arg0           = hMcm;
    params.arg1           = hMcm->asyncIoctlSem;
    params.name           = (uint8_t *)"EnetMcm_AsyncIoctlTask";
    params.stack          =  &asyncIoctlTaskStack[0];
    params.stacksize      =  sizeof(asyncIoctlTaskStack);

    hMcm->asyncIoctlTaskShutdown = false;

    hMcm->asyncIoctlTask = TaskP_create((void *)EnetMcm_asyncIoctlTask, &params);
    EnetAppUtils_assert(hMcm->asyncIoctlTask != NULL);

#if defined(ENET_ENABLE_ICSSG)
    if (Enet_isIcssFamily(hMcm->enetType))
    {
        Enet_registerEventCb(hMcm->hEnet,
                             ENET_EVT_ASYNC_CMD_RESP,
                             0U,
                             EnetMcm_evtCb,
                             (void *) hMcm->asyncIoctlSem);
    }
#endif

    /* Enable Host and MAC Ports */
    status = EnetMcm_enablePorts(hMcm);
    if(status != ENET_SOK)
    {
        EnetAppUtils_print("EnetMcm_enablePorts failed\n");
        EnetAppUtils_assert(ENET_SOK == status);
    }

    EnetMcm_createClock(hMcm);

    return status;
}

static void EnetMcm_coreAttachHandler(EnetMcm_Handle hMcm,
                                      uint32_t coreId,
                                      EnetPer_AttachCoreOutArgs *pAttachCoreOutArgs)
{
    Enet_IoctlPrms prms;
    EnetMcm_CoreAttachTableEntry *entry;
    int32_t status;

    if (NULL != pAttachCoreOutArgs)
    {
        entry = EnetMcm_getCoreAttachEntry(&hMcm->coreAttachTable, coreId);
        if (entry == NULL)
        {
            ENET_IOCTL_SET_INOUT_ARGS(&prms, &coreId, pAttachCoreOutArgs);
            status = Enet_ioctl(hMcm->hEnet,
                                coreId,
                                ENET_PER_IOCTL_ATTACH_CORE,
                                &prms);
            if (status != ENET_SOK)
            {
                hMcm->print("EnetMcm_open failed ENET_PER_IOCTL_ATTACH_CORE: %d\n", status);
                EnetAppUtils_assert(false);
            }

            EnetMcm_addCoreAttachEntry(&hMcm->coreAttachTable, coreId, pAttachCoreOutArgs);
            entry = EnetMcm_getCoreAttachEntry(&hMcm->coreAttachTable, coreId);
        }

        EnetAppUtils_assert((entry != NULL));
        if (entry != NULL)
        {
            *pAttachCoreOutArgs = entry->coreInfo;
        }
    }
    else
    {
        EnetAppUtils_assert(false);
    }
}

static void EnetMcm_coreDetachHandler(EnetMcm_Handle hMcm,
                                      uint32_t coreId,
                                      uint32_t coreKey)
{
    Enet_IoctlPrms prms;
    EnetMcm_CoreAttachTableEntry *entry;

    entry = EnetMcm_getCoreAttachEntry(&hMcm->coreAttachTable, coreId);

    if (entry != NULL)
    {
        int32_t status;

        ENET_IOCTL_SET_IN_ARGS(&prms, &coreKey);
        status = Enet_ioctl(hMcm->hEnet,
                            coreId,
                            ENET_PER_IOCTL_DETACH_CORE,
                            &prms);
        if (status != ENET_SOK)
        {
            hMcm->print("close() failed ENET_PER_IOCTL_DETACH_CORE: %d\n", status);
            EnetAppUtils_assert(false);
        }

        EnetMcm_delCoreAttachEntry(&hMcm->coreAttachTable, coreId, coreKey);
    }
}

static int32_t EnetMcm_ioctlHandler(EnetMcm_Handle hMcm,
                                    uint32_t cmd,
                                    Enet_IoctlPrms *prms)
{
    int32_t status;

    if (prms != NULL)
    {
        status = Enet_ioctl(hMcm->hEnet, hMcm->selfCoreId, cmd, prms);
        if (status == ENET_SINPROGRESS)
        {
            /* Wait for asyc ioctl to complete */
            hMcm->asyncIoctlDone = false;
            while (!hMcm->asyncIoctlDone)
            {
                Enet_poll(hMcm->hEnet, ENET_EVT_ASYNC_CMD_RESP, NULL, 0U);
                TaskP_sleep(1);
            }

            status = ENET_SOK;
        }
        else if (status != ENET_SOK)
        {
            hMcm->print("EnetMcm_asyncIoctlHandler failed: %d\n", status);
        }
    }
    else
    {
        status = ENET_EBADARGS;
        EnetAppUtils_assert(false);
    }

    return status;
}

static void EnetMcm_serverTask(void * McmHandle)
{
    volatile bool isShutdownMcm = false;
    EnetMcm_Handle hMcm         = (EnetMcm_Handle)McmHandle;

    while (!isShutdownMcm)
    {
        int32_t status = ENET_SOK;
        EnetMcm_mailboxObj msg;

        MailboxP_pend(hMcm->hMboxCmd, &msg, SemaphoreP_WAIT_FOREVER);

        switch (msg.cmd)
        {
            case MCM_GET_HANDLE:
                if (hMcm->refCnt == 0)
                {
                    status = EnetMcm_open(hMcm);
                    EnetAppUtils_assert(ENET_SOK == status);
                }

                if (status == ENET_SOK)
                {
                    hMcm->refCnt++;
                }

                msg.cmd                         = MCM_RESPONSE_GET_HANDLE;
                msg.msgBody.handleInfo.hEnet    = hMcm->hEnet;
#if !(defined(SOC_TPR12) || defined(SOC_AWR294X))
                msg.msgBody.handleInfo.hUdmaDrv = hMcm->hUdmaDrv;
#endif
                break;

            case MCM_RELEASE_HANDLE:
                EnetAppUtils_assert(hMcm->refCnt > 0);
                hMcm->refCnt--;

                if (hMcm->refCnt == 0)
                {
                    EnetMcm_close(hMcm);
                }

                msg.cmd = MCM_RESPONSE_RELEASE_HANDLE;
                break;

            case MCM_CORE_ATTACH:
                EnetAppUtils_assert(hMcm->hEnet != NULL);
                EnetMcm_coreAttachHandler(hMcm, msg.msgBody.coreId, &msg.msgBody.attachInfo);
                msg.cmd = MCM_RESPONSE_CORE_ATTACH;
                break;

            case MCM_CORE_DETACH:
                EnetAppUtils_assert(hMcm->hEnet != NULL);
                EnetMcm_coreDetachHandler(hMcm, msg.msgBody.coreId, msg.msgBody.coreKey);
                msg.cmd = MCM_RESPONSE_CORE_DETACH;
                break;

            case MCM_IOCTL:
                EnetAppUtils_assert(hMcm->hEnet != NULL);
                msg.msgBody.ioctlStatus = EnetMcm_ioctlHandler(hMcm, msg.msgBody.ioctlCmd, msg.msgBody.ioctlPrms);
                msg.cmd = MCM_RESPONSE_IOCTL;
                break;

            case MCM_SHUTDOWN:
                isShutdownMcm = true;
                msg.cmd       = MCM_RESPONSE_SHUTDOWN;
                break;

            default:
                /* Unahandle MCM command */
                EnetAppUtils_assert(false);
        }

        MailboxP_post(hMcm->hMboxResponse, &msg, SemaphoreP_WAIT_FOREVER);
    }
}

static void EnetMcm_close(EnetMcm_Handle hMcm)
{
    Enet_IoctlPrms prms;
    uint8_t i;
    int32_t status;

    if (Enet_isCpswFamily(hMcm->enetType))
    {
        /* Disable host port */
        ENET_IOCTL_SET_NO_ARGS(&prms);
        status = Enet_ioctl(hMcm->hEnet,
                            hMcm->selfCoreId,
                            ENET_HOSTPORT_IOCTL_DISABLE,
                            &prms);
        if (status != ENET_SOK)
        {
            hMcm->print("Failed to disable host port: %d\n", status);
        }
    }

    if (Enet_isIcssFamily(hMcm->enetType))
    {
        EnetAppUtils_print("Unregister async IOCTL callback\n");
        Enet_unregisterEventCb(hMcm->hEnet,
                               ENET_EVT_ASYNC_CMD_RESP,
                               0U);

        EnetAppUtils_print("Unregister TX timestamp callback\n");
        Enet_unregisterEventCb(hMcm->hEnet,
                               ENET_EVT_TIMESTAMP_TX,
                               0U);
    }

    for (i = 0U; i < hMcm->numMacPorts; i++)
    {
        Enet_MacPort macPort = hMcm->macPortList[i];

        ENET_IOCTL_SET_IN_ARGS(&prms, &macPort);
        status = Enet_ioctl(hMcm->hEnet,
                            hMcm->selfCoreId,
                            ENET_PER_IOCTL_CLOSE_PORT_LINK,
                            &prms);
        if (status != ENET_SOK)
        {
            hMcm->print("close() failed to close MAC port: %d\n", status);
        }
    }

    hMcm->timerTaskShutDownFlag = true;

    if (hMcm->hTimer != NULL)
    {
        ClockP_stop(hMcm->hTimer);
        ClockP_delete(hMcm->hTimer);
    }

    /* Post Timer Sem once to get the Periodic Tick task terminated */
    SemaphoreP_post(hMcm->timerSem);

    while (TaskP_isTerminated(hMcm->task_periodicTick) != 1)
    {
        TaskP_sleep(10);
    }
    TaskP_delete(&hMcm->task_periodicTick);

    if (hMcm->timerSem != NULL)
    {
        SemaphoreP_delete(hMcm->timerSem);
    }

    /* Post semaphore once to get the async IOCTL task terminated */
    hMcm->asyncIoctlTaskShutdown = true;
    SemaphoreP_post(hMcm->asyncIoctlSem);

    while (TaskP_isTerminated(hMcm->asyncIoctlTask) != 1)
    {
        TaskP_sleep(10);
    }
    TaskP_delete(&hMcm->asyncIoctlTask);

    if (hMcm->asyncIoctlSem != NULL)
    {
        SemaphoreP_delete(hMcm->asyncIoctlSem);
    }

    Enet_close(hMcm->hEnet);

    EnetMem_deInit();

    Enet_deinit();

    hMcm->hEnet = NULL;
}

void EnetMcm_acquireHandleInfo(const EnetMcm_CmdIf *hMcmCmdIf,
                               EnetMcm_HandleInfo *handleInfo)
{
    EnetMcm_mailboxObj msg;

    memset(&msg, 0, sizeof(msg));
    msg.cmd = MCM_GET_HANDLE;
    if ((hMcmCmdIf != NULL) && (handleInfo != NULL))
    {
        MailboxP_post(hMcmCmdIf->hMboxCmd, &msg, SemaphoreP_WAIT_FOREVER);
        MailboxP_pend(hMcmCmdIf->hMboxResponse, &msg, SemaphoreP_WAIT_FOREVER);
        EnetAppUtils_assert(msg.cmd == MCM_RESPONSE_GET_HANDLE);

        *handleInfo = msg.msgBody.handleInfo;
    }
    else
    {
        EnetAppUtils_assert(false);
    }
}

void EnetMcm_releaseHandleInfo(const EnetMcm_CmdIf *hMcmCmdIf)
{
    EnetMcm_mailboxObj msg;

    memset(&msg, 0, sizeof(msg));
    msg.cmd = MCM_RELEASE_HANDLE;
    EnetAppUtils_assert(hMcmCmdIf != NULL);

    MailboxP_post(hMcmCmdIf->hMboxCmd, &msg, SemaphoreP_WAIT_FOREVER);
    MailboxP_pend(hMcmCmdIf->hMboxResponse, &msg, SemaphoreP_WAIT_FOREVER);
    EnetAppUtils_assert(msg.cmd == MCM_RESPONSE_RELEASE_HANDLE);
}

void EnetMcm_coreAttach(const EnetMcm_CmdIf *hMcmCmdIf,
                        uint32_t coreId,
                        EnetPer_AttachCoreOutArgs *attachInfo)
{
    EnetMcm_mailboxObj msg;

    memset(&msg, 0, sizeof(msg));
    if ((hMcmCmdIf != NULL) && (attachInfo != NULL))
    {
        msg.cmd            = MCM_CORE_ATTACH;
        msg.msgBody.coreId = coreId;

        MailboxP_post(hMcmCmdIf->hMboxCmd, &msg, SemaphoreP_WAIT_FOREVER);
        MailboxP_pend(hMcmCmdIf->hMboxResponse, &msg, SemaphoreP_WAIT_FOREVER);
        EnetAppUtils_assert(msg.cmd == MCM_RESPONSE_CORE_ATTACH);
        *attachInfo = msg.msgBody.attachInfo;
    }
    else
    {
        EnetAppUtils_assert(false);
    }
}

void     EnetMcm_coreDetach(const EnetMcm_CmdIf *hMcmCmdIf,
                            uint32_t coreId,
                            uint32_t coreKey)
{
    EnetMcm_mailboxObj msg;

    memset(&msg, 0, sizeof(msg));
    EnetAppUtils_assert(hMcmCmdIf != NULL);
    msg.cmd             = MCM_CORE_DETACH;
    msg.msgBody.coreId  = coreId;
    msg.msgBody.coreKey = coreKey;

    MailboxP_post(hMcmCmdIf->hMboxCmd, &msg, SemaphoreP_WAIT_FOREVER);
    MailboxP_pend(hMcmCmdIf->hMboxResponse, &msg, SemaphoreP_WAIT_FOREVER);
    EnetAppUtils_assert(msg.cmd == MCM_RESPONSE_CORE_DETACH);
}

int32_t EnetMcm_ioctl(const EnetMcm_CmdIf *hMcmCmdIf,
                      uint32_t cmd,
                      Enet_IoctlPrms *prms)
{
    EnetMcm_mailboxObj msg;
    int32_t status;

    memset(&msg, 0, sizeof(msg));

    if ((hMcmCmdIf != NULL) && (prms != NULL))
    {
        msg.cmd = MCM_IOCTL;
        msg.msgBody.ioctlCmd  = cmd;
        msg.msgBody.ioctlPrms = prms;

        MailboxP_post(hMcmCmdIf->hMboxCmd, &msg, SemaphoreP_WAIT_FOREVER);
        MailboxP_pend(hMcmCmdIf->hMboxResponse, &msg, SemaphoreP_WAIT_FOREVER);
        EnetAppUtils_assert(msg.cmd == MCM_RESPONSE_IOCTL);
        status = msg.msgBody.ioctlStatus;
    }
    else
    {
        status = ENET_EBADARGS;
        EnetAppUtils_assert(false);
    }

    return status;
}
