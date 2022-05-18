/*

 * Copyright (c) 2015-2019, Texas Instruments Incorporated
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
 *  ======== TimerP_default.c ========
 */


#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ti/csl/soc.h>
#include <ti/osal/src/nonos/Nonos_config.h>


#define CLEC_OFFSET       (256u)

/* This information is derived from sysbios timer implmentation for multiple SoCs */
/* Below defines are for R5 Cores */
TimerP_dmTimerDefault gDmTimerPInfoTbl[TimerP_numTimerDevices] = {
  /* Timer ID 0 */
  {
    "DMTimer0",        /* Timer Name */
#if defined (BUILD_C7X)
     (uint32_t)CSL_TIMER0_CFG_BASE,                                /* Main domain's DM Timer base address */
     (int32_t)0xe,                                                 /* intNum */
     CLEC_OFFSET + CSLR_C7X256V0_CLEC_GIC_SPI_TIMER0_INTR_PEND_0, /* eventId It is the CLEC event ID from where the SPI events
                                                            are mapped to the clec */
#endif
#if defined (BUILD_MCU1_0)
     CSL_WKUP_TIMER0_CFG_BASE,  /* base address */
     CSLR_R5FSS0_CORE0_INTR_WKUP_TIMER0_INTR_PEND_0,           /* Interrupt Number */
     TIMERP_EVENT_NOT_AVAILABLE               /* Event Id */
#endif
  },  
  /* Timer ID 1 */
  {
    "DMTimer1",        /* Timer Name */
#if defined (BUILD_C7X)
     (uint32_t)CSL_TIMER1_CFG_BASE,                                /* Main domain's DM Timer base address */
     (int32_t)0xf,                                                 /* intNum */
     CLEC_OFFSET + CSLR_C7X256V0_CLEC_GIC_SPI_TIMER1_INTR_PEND_0, /* eventId It is the CLEC event ID from where the SPI events
                                                            are mapped to the clec */
#endif
#if defined (BUILD_MCU1_0)
     CSL_WKUP_TIMER1_CFG_BASE,  /* base address */
     CSLR_R5FSS0_CORE0_INTR_WKUP_TIMER1_INTR_PEND_0,               /* Interrupt Number */
     TIMERP_EVENT_NOT_AVAILABLE               /* Event Id */
#endif
  },
  {
     "DMTimer2",        /* Timer Name */ 
#if defined (BUILD_C7X)
     (uint32_t)CSL_TIMER2_CFG_BASE,                                /* Main domain's DM Timer base address */
     (int32_t)0x10,                                                 /* intNum */
     CLEC_OFFSET + CSLR_C7X256V0_CLEC_GIC_SPI_TIMER2_INTR_PEND_0, /* eventId It is the CLEC event ID from where the SPI events
                                                            are mapped to the clec */
#endif
  },
  {
     "DMTimer3",        /* Timer Name */ 
#if defined (BUILD_C7X)
     (uint32_t)CSL_TIMER2_CFG_BASE,                                /* Main domain's DM Timer base address */
     (int32_t)0x11,                                                 /* intNum */
     CLEC_OFFSET + CSLR_C7X256V0_CLEC_GIC_SPI_TIMER3_INTR_PEND_0, /* eventId It is the CLEC event ID from where the SPI events
                                                            are mapped to the clec */
#endif
  }
};

/* Returns the default frquency lower 32 bits */
int32_t TimerP_getDefaultFreqLo(uint32_t timerId)
{
    /* return the same default frequency for all timer Ids */
    return(TIMERP_TIMER_FREQ_LO);
}

/* Returns the default frquency higher 32 bits */
int32_t TimerP_getDefaultFreqHi(uint32_t timerId)
{
    /* return the same default frequency for all timer Ids */
    return(TIMERP_TIMER_FREQ_HI);
}

#if defined (BUILD_MCU)
uint32_t TimerP_mapId(uint32_t id)
{
    /*
     * Pulsar R5 SS is always on the MCU domain
     * use the default info table configuration,
     * no need to map the id.
     */
    return (id);
}
uint32_t TimerP_reverseMapId(uint32_t id)
{
    return (id);
}
void TimerP_updateDefaultInfoTbl(void)
{
    /*
     * Pulsar R5 SS is always on the MCU domain
     * use the default info table configuration,
     * no need to update the table.
     */
}
#endif

/* Nothing past this point */
