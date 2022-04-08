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
 *  \file udma.c
 *
 *  \brief File containing the UDMA generic driver APIs.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <string.h>
#include "ti/drv/udma/dmautils/udma_standalone/udma.h"
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

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

//:TODO:
#define Udma_printf
#define UDMA_EVENT_INVALID              ((uint32_t) 0xFFFFU)


int32_t Udma_init(Udma_DrvHandle drvHandle, const Udma_InitPrms *initPrms)
{
    int32_t                             retVal = UDMA_SOK;

    if((drvHandle == NULL_PTR) || (initPrms == NULL_PTR))
    {
      retVal = UDMA_EBADARGS;
    }

    if(UDMA_SOK == retVal)
    {
      (void) memset(drvHandle, 0, sizeof(*drvHandle));
      (void) memcpy(&drvHandle->initPrms, initPrms, sizeof(Udma_InitPrms));
    }

    return (retVal);
}

int32_t Udma_deinit(Udma_DrvHandle drvHandle)
{
    int32_t     retVal = UDMA_SOK;

    /* Error check */
    if((NULL_PTR == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
    {
        retVal = UDMA_EBADARGS;
    }

    return (retVal);
}

int32_t UdmaInitPrms_init(uint32_t instId, Udma_InitPrms *initPrms)
{
    int32_t retVal = UDMA_SOK;

    /* Error check */
    if(NULL_PTR == initPrms)
    {
        retVal = UDMA_EBADARGS;
    }

    if(UDMA_SOK == retVal)
    {
        initPrms->instId                = instId;
        initPrms->virtToPhyFxn          = &Udma_defaultVirtToPhyFxn;
        initPrms->phyToVirtFxn          = &Udma_defaultPhyToVirtFxn;
        initPrms->printFxn              = (Udma_PrintFxn) NULL_PTR;
        initPrms->rmInitPrms.druStartId = 0;
        initPrms->rmInitPrms.druEndId   = 15;
    }

    return (retVal);
}



/* Channel specific functions */

void UdmaChPrms_init(Udma_ChPrms *chPrms, uint32_t chType)
{
    if(NULL_PTR != chPrms)
    {
        chPrms->chNum       = UDMA_DMA_CH_ANY;
        chPrms->utcId       = UDMA_UTC_ID_INVALID;
    }

    return;
}



uint32_t Udma_chGetNum(Udma_ChHandle chHandle)
{
    int32_t         retVal = UDMA_SOK;
    Udma_DrvHandle  drvHandle;
    uint32_t        chNum = UDMA_DMA_CH_INVALID;

    /* Error check */
    if((NULL_PTR == chHandle) )
    {
        retVal = UDMA_EBADARGS;
    }

    if(UDMA_SOK == retVal)
    {
      chNum = chHandle->druChNum;
    }

    return (chNum);
}

int32_t Udma_chOpen(Udma_DrvHandle drvHandle,
                    Udma_ChHandle chHandle,
                    uint32_t chType,
                    const Udma_ChPrms *chPrms)
{
    int32_t     retVal = UDMA_SOK, tempRetVal;
    uint32_t    allocDone = (uint32_t) FALSE;

    /* Error check */
    if((drvHandle == NULL_PTR) || (NULL_PTR == chHandle) || (NULL_PTR == chPrms))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        if(drvHandle->drvInitDone != UDMA_INIT_DONE)
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        /* Copy and init parameters */
        (void) memset(chHandle, 0, sizeof(struct Udma_ChObj));
        (void) memcpy(&chHandle->chPrms, chPrms, sizeof(Udma_ChPrms));
        chHandle->drvHandle         = drvHandle;

    }

    if(UDMA_SOK == retVal)
    {
        /* Alloc UDMA channel/rings */
        //:TODO:
       //retVal = Udma_chAllocResource(chHandle);
        if(UDMA_SOK == retVal)
        {
            allocDone = (uint32_t) TRUE;
        }
        else
        {
            Udma_printf(drvHandle, "[Error] Channel resource allocation failed!!\n");
        }
    }

    if(UDMA_SOK == retVal)
    {
        chHandle->chInitDone        = UDMA_INIT_DONE;
    }
    else
    {
        /* Error. Free-up resource if allocated */
        if(((uint32_t) TRUE) == allocDone)
        {
//            tempRetVal = Udma_chFreeResource(chHandle);
            if(UDMA_SOK != tempRetVal)
            {
                Udma_printf(drvHandle, "[Error] Free resource failed!!!\n");
            }
        }
    }

    return (retVal);
}

int32_t Udma_chConfigUtc(Udma_ChHandle chHandle, const Udma_ChUtcPrms *utcPrms)
{
    int32_t                 retVal = UDMA_SOK;
    uint32_t                utcChNum;
    Udma_DrvHandle          drvHandle;
    const Udma_UtcInstInfo *utcInfo;
    CSL_DruChConfig         druChCfg;

    /* Error check */
    if((NULL_PTR == chHandle) ||
       (chHandle->chInitDone != UDMA_INIT_DONE) )
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = chHandle->drvHandle;
        if((NULL_PTR == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        utcInfo = chHandle->utcInfo;
        utcChNum = chHandle->chPrms.chNum;
        /* Configure DRU */
        /* Disable the channel before any configuration */
        retVal = CSL_druChDisable(utcInfo->druRegs, utcChNum);
        if(CSL_PASS != retVal)
        {
            Udma_printf(drvHandle, "[Error] DRU channel disable failed!!\n");
            retVal = UDMA_EFAIL;
        }

        if(UDMA_SOK == retVal)
        {
            druChCfg.type       = 0U;   /* Not used */
            druChCfg.owner      = utcPrms->druOwner;
            druChCfg.pauseOnErr = utcPrms->pauseOnError;
            druChCfg.evtNum     = UDMA_EVENT_INVALID;
            druChCfg.queueId    = (uint64_t)utcPrms->druQueueId;
            retVal = CSL_druChConfig(utcInfo->druRegs, utcChNum, &druChCfg);
            if(CSL_PASS != retVal)
            {
                Udma_printf(drvHandle,
                    "[Error] DRU channel config failed!!\n");
                retVal = UDMA_EFAIL;
            }
        }
    }

    if(UDMA_SOK == retVal)
    {
        /* Copy the config */
        (void) memcpy(&chHandle->utcPrms, utcPrms, sizeof(chHandle->utcPrms));
    }

    return (retVal);
}

int32_t Udma_chEnable(Udma_ChHandle chHandle)
{
    int32_t         retVal = UDMA_SOK;
    Udma_DrvHandle  drvHandle;
    uint32_t utcChNum;

    /* Error check */
    if((NULL_PTR == chHandle) || (chHandle->chInitDone != UDMA_INIT_DONE))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = chHandle->drvHandle;
        if((NULL_PTR == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        utcChNum = chHandle->chPrms.chNum;
        /* Enable channel based on channel type */
        retVal = CSL_druChEnable(chHandle->utcInfo->druRegs, utcChNum);
        if(CSL_PASS != retVal)
        {
            retVal = UDMA_EFAIL;
            Udma_printf(drvHandle,
                "[Error] DRU channel enable failed!!\n");
        }

        if(UDMA_SOK != retVal)
        {
            Udma_printf(drvHandle, "[Error] UDMA channel enable failed!!\n");
        }
    }

    return (retVal);
}

int32_t Udma_chDisable(Udma_ChHandle chHandle, uint32_t timeout)
{
    int32_t                 retVal = UDMA_SOK;
    Udma_DrvHandle          drvHandle;
    uint32_t utcChNum;
    /* Error check */
    if((NULL_PTR == chHandle) || (chHandle->chInitDone != UDMA_INIT_DONE))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = chHandle->drvHandle;
        if((NULL_PTR == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        if(CSL_DRU_OWNER_DIRECT_TR == chHandle->utcPrms.druOwner)
        {
            utcChNum = chHandle->chPrms.chNum;

            retVal = CSL_druChTeardown(chHandle->utcInfo->druRegs, utcChNum);
            if(CSL_PASS != retVal)
            {
                Udma_printf(drvHandle, "[Error] DRU channel teardown failed!!\n");
                retVal = UDMA_EFAIL;
            }
        }
    }
    else
    {
      retVal = UDMA_EFAIL;
    }

    return (retVal);
}



volatile uint64_t *Udma_druGetTriggerRegAddr(Udma_ChHandle chHandle)
{
    int32_t                 retVal = UDMA_SOK;
    Udma_DrvHandle          drvHandle;
    const Udma_UtcInstInfo *utcInfo;
    volatile uint64_t      *pSwTrigReg = (volatile uint64_t *) NULL_PTR;

    /* Error check */
    if((NULL_PTR == chHandle) ||
       (chHandle->chInitDone != UDMA_INIT_DONE) )
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = chHandle->drvHandle;
        if((NULL_PTR == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        utcInfo = chHandle->utcInfo;
        pSwTrigReg = &chHandle->pDruRtRegs->CHRT_SWTRIG;
    }

    return (pSwTrigReg);
}



void Udma_chDruSubmitTr(Udma_ChHandle chHandle, const CSL_UdmapTR *tr)
{
    uint32_t                utcChNum;
    const Udma_UtcInstInfo *utcInfo;

    utcInfo = chHandle->utcInfo;
    utcChNum = chHandle->druChNum;
#if defined (__C7100__) || (__C7120__)
    CSL_druChSubmitAtomicTr(utcInfo->druRegs, utcChNum, (__ulong8 *)  tr);
#else
    Udma_DrvHandle          drvHandle = chHandle->drvHandle;
    CSL_druChSubmitTr(utcInfo->druRegs, utcChNum, drvHandle->druCoreId, tr);
#endif

    return;
}


int32_t Udma_chClose(Udma_ChHandle chHandle)
{
    int32_t         retVal = UDMA_SOK;
    Udma_DrvHandle  drvHandle;

    /* Error check */
    if((NULL_PTR == chHandle) || (chHandle->chInitDone != UDMA_INIT_DONE))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = chHandle->drvHandle;
        if((NULL_PTR == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        /* Free-up UDMA channel/rings */
//:TODO:        retVal += Udma_chFreeResource(chHandle);
        if(UDMA_SOK != retVal)
        {
            Udma_printf(drvHandle, "[Error] Free resource failed!!!\n");
        }

        (void) memset(chHandle, 0, sizeof(*chHandle));
        chHandle->chInitDone = UDMA_DEINIT_DONE;
    }

    return (retVal);
}


void UdmaChUtcPrms_init(Udma_ChUtcPrms *utcPrms)
{
    return;
}

