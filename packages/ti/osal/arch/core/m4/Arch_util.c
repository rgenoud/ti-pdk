/*
 * Copyright (c) 2016-2018, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 *  ======== Arch_util.c ========
 */


#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ti/csl/csl_timer.h>
#include <ti/osal/src/nonos/Nonos_config.h>
#include <ti/csl/tistdtypes.h>

/* Local structure definition */
typedef struct HwiP_nonOs_s {
    Bool        used;
    Hwi_Struct  hwi;
} HwiP_nonOs;

/* Local Timer Struct */
typedef struct Arch_TimerP_Struct_s
{
  bool     used;       /* In use or not status */
  uint32_t timerId;    /* timer Id */
} Arch_TimerP_Struct;

/* Local hwi structures */
static HwiP_nonOs hwiStructs[OSAL_NONOS_CONFIGNUM_HWI] = {{0}};
static bool gFirstTime = BTRUE;

static bool gTimestampFirstTime = BTRUE;
static TimeStamp_Struct gTimeStamp = {0U};
static uintptr_t gTimerBaseAddr;
static uint32_t  gTimerId;

/* local defines */
#define OSAL_ARCH_UTIL_ZERO          ((uint32_t) 0U)

/*
 * Dummy function to check size during compile time
 *  ======== HwiP_compileTime_SizeChk ========
 */

void OsalArch_compileTime_SizeChk(void)
{
#if defined(__GNUC__) && !defined(__ti__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#else
/* TI compiler */
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
    OSAL_COMPILE_TIME_SIZE_CHECK (sizeof(HwiP_nonOs),OSAL_NONOS_HWIP_SIZE_BYTES);
#if defined(__GNUC__) && !defined(__ti__)
#pragma GCC diagnostic pop
#endif
}

/* This function enables the interrupt for a given interrupt number */
void OsalArch_enableInterrupt(uint32_t intNum)
{
    Intc_SystemEnable((uint16_t)intNum);
    return;
}

/* This function disables the interrupt for a given interrupt number */
void OsalArch_disableInterrupt(uint32_t intNum)
{
    Intc_SystemDisable((uint16_t)intNum);
    return;
}
/* Below function posts the interrupt */
int32_t OsalArch_postInterrupt(uint32_t intrNum)
{
    Intc_IntSetPend(intrNum);
    return (CSL_PASS);
}

/* Below function clears interrupt in the chip level */
void OsalArch_clearInterrupt(uint32_t intNum)
{
    Intc_IntClrPend((uint16_t)intNum);
    return;
}
/* Below function globally disable interrupt in the chip level */
uintptr_t OsalArch_globalDisableInterrupt(void)
{
    return (uintptr_t)(Intc_IntDisable());
}

/* Below function globally restore interrupt in the chip level */
void OsalArch_globalRestoreInterrupt (uintptr_t restoreValue)
{
    Intc_IntEnable((uint8_t)restoreValue);
}

/* Below function registers the interrupt for a given ISR */
HwiP_Handle OsalArch_HwiPCreate(uint32_t interruptNum, HwiP_Fxn hwiFxn,
                          const HwiP_Params *params)
{
    uint32_t i;
    uintptr_t key;

    uintptr_t         temp;
    HwiP_nonOs       *hwiPool;
    uint32_t          maxHwi;
    HwiP_Handle       retHandle;

    /* Check if user has specified any memory block to be used, which gets
     * the precedence over the internal static memory block
     */
    if ((uintptr_t)NULL_PTR != gOsal_HwAttrs.extHwiPBlock.base)
    {
        /* pick up the external memory block configured */
        hwiPool        = (HwiP_nonOs *) gOsal_HwAttrs.extHwiPBlock.base;
        temp           = (uintptr_t) gOsal_HwAttrs.extHwiPBlock.size;
        maxHwi         = (uint32_t)(temp/(sizeof(Hwi_Struct)));
    }
    else
    {
        /* Pick up the internal static memory block */
        hwiPool        = (HwiP_nonOs *) &hwiStructs[0];
        maxHwi         = OSAL_NONOS_CONFIGNUM_HWI;
    }

    if (NULL_PTR == params)
    {
        return (NULL_PTR);
    }

    key = OsalArch_globalDisableInterrupt();
    for (i = 0U; i < maxHwi; i++) {
        if (UFALSE == hwiPool[i].used) {
            hwiPool[i].used = UTRUE;
            break;
        }
    }
    OsalArch_globalRestoreInterrupt(key);

    if (i < maxHwi)
    {
      retHandle  = (HwiP_Handle)&hwiPool[i];
    }
    else
    {
      retHandle  = (HwiP_Handle)(NULL_PTR);
    }

    if ((HwiP_Handle) NULL_PTR != retHandle)
    {
        if (BTRUE == gFirstTime)  {
          Intc_Init();
          gFirstTime = BFALSE;
        }

        /* Enable the interrupt */
        OsalArch_globalRestoreInterrupt(0);

        /* Registering the Interrupt Service Routine(ISR). */
        Intc_IntRegister((uint16_t)interruptNum, (IntrFuncPtr) hwiFxn, (void *)params->arg);

        /* Setting the priority for the UART interrupt in INTC. */
        Intc_IntPrioritySet((uint16_t)interruptNum, params->priority, 0);

        /* Enabling the interrupt if configured */
        if (UTRUE == params->enableIntr)
        {
            /* Enabling the interrupt in INTC. */
            OsalArch_enableInterrupt(interruptNum);
        }
        else
        {
            /* Disabling the interrupt in INTC. */
            OsalArch_disableInterrupt(interruptNum);
        }
    }
    return ( (HwiP_Handle) (retHandle) );

}

HwiP_Status OsalArch_HwiPDelete(HwiP_Handle handle)
{
    HwiP_nonOs *hwi_hnd = (HwiP_nonOs*) handle;
    uintptr_t   key;
    HwiP_Status ret_val = HwiP_OK;

    /* mark that handle as free */
    key = OsalArch_globalDisableInterrupt();
    if (UTRUE == hwi_hnd->used)
    {
        hwi_hnd->used = UFALSE;
    }
    else
    {
        ret_val = HwiP_FAILURE;
    }
    OsalArch_globalRestoreInterrupt(key);
    return (ret_val);
}


/* Return the cycle frequency used for timeStamp */
uint32_t  osalArch_TimeStampGetFreqKHz(void)
{
    uint32_t  lo, hi;
    uint64_t  freq;
    uint32_t  freqKHz;
    lo = TimerP_getDefaultFreqLo(gTimerId);
    hi = TimerP_getDefaultFreqHi(gTimerId);

    freq = ((((uint64_t) (hi)) << 32U) + (uint64_t) lo);
    freqKHz = freq/1000U;

    /* R5F time Stamp provider is timer */
    return (freqKHz);
}

/* Initialize the time stamp module */
void    osalArch_TimestampInit(void)
{
    TimerP_Params  timerParams;
    TimerP_Handle  timerHandle;
    uint32_t       timerId;

    if (BTRUE == gTimestampFirstTime)
    {
        /* One time initialization is done */
        gTimestampFirstTime = BFALSE;

        /* Initialize the parameters */
        TimerP_Params_init(&timerParams);
        timerParams.startMode = TimerP_StartMode_USER;
        timerParams.periodType = TimerP_PeriodType_COUNTS;
        timerParams.period    = TimerP_MAX_PERIOD-1U;
        timerHandle = TimerP_create(TimerP_ANY, (TimerP_Fxn)&osalArch_TimestampCcntAutoRefresh, &timerParams);

        if ( (TimerP_Handle) NULL_PTR != timerHandle )
        {
            Arch_TimerP_Struct *timer = (Arch_TimerP_Struct *) timerHandle;
            gTimerBaseAddr = gDmTimerPInfoTbl[timer->timerId].baseAddr;
            gTimerId       = timer->timerId;
            /* start the timer */
            TimerP_start(timerHandle);
        }
    }

    return;
}

/* Osal time stamp provider implementations */
void osalArch_TimestampGet64(TimeStamp_Struct *tStamp)
{
    uintptr_t   key;

    if ((TimeStamp_Struct *) NULL_PTR != tStamp)
    {
        key        = HwiP_disable();
        /* Make sure init is done, if not done already */
        osalArch_TimestampInit();

        gTimeStamp.lo = TIMERCounterGet(gTimerBaseAddr);

        tStamp->lo         = gTimeStamp.lo;
        tStamp->hi         = gTimeStamp.hi;
        /* restore */
        HwiP_restore(key);
    }
    /* return time in micro seconds */
    return;
}

/* Needs to be run at least once after a over flow happens and before next overflow */
void osalArch_TimestampCcntAutoRefresh(uintptr_t arg)
{
    uintptr_t   key;

    key        = HwiP_disable();

    gTimeStamp.hi++;
    gTimeStamp.lo = TIMERCounterGet(gTimerBaseAddr);
    /* restore */
    HwiP_restore(key);

    /* return time in micro seconds */
    return;
}

/* Nothing past this point */
