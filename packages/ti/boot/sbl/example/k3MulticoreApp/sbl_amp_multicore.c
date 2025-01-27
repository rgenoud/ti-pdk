/*
 * Copyright (c) 2018, Texas Instruments Incorporated
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

#include "sbl_amp_multicore_sections.h"
#include "sbl_print.h"

int SBLApp_main(void)
{
    volatile int *pokeMemAddr = (volatile int *)POKE_MEM_ADDR;
#if defined(BOOTAPP_TEST)
    volatile int delay1 = 10;
    volatile int delay2 = BOOT_DELAY;
#if defined(BUILD_MCU2_0)
    volatile int *bootFlagAddr = (volatile int *)POKE_MEM_ADDR_MCU1_0;
    volatile int numCoresBooted = 0;
#endif
#else
#if defined(BUILD_MCU1_0)
    volatile int delay1 = 10;
    volatile int delay2 = BOOT_DELAY;
    volatile int *bootFlagAddr = (volatile int *)POKE_MEM_ADDR_MCU1_0;
    volatile int numCoresBooted = 0;
#endif
#endif

#if !defined(BOOTAPP_TEST)
    volatile int bootDelay = BOOT_DELAY;
#endif

#if defined(BOOTAPP_TEST)
    if (*pokeMemAddr != UPDATE_VALUE)
    {
        /* Adding extra delay so that this application logs print after BootApp logs */
        while(delay1--)
        {
            while (delay2--);
            delay2 = BOOT_DELAY;
        }
        sbl_puts(CORE_NAME);
        sbl_puts(" booted\n\r");
        *pokeMemAddr = UPDATE_VALUE;
    }

#if defined(BUILD_MCU2_0)
    delay1 = 2;
    delay2 = BOOT_DELAY;
    while(delay1--)
    {
        while (delay2--)
        {
            /* Do Nothing */
        }
        delay2 = BOOT_DELAY;
    }
    while(1)
    {
        for (bootFlagAddr = (volatile int *)POKE_MEM_ADDR_MCU1_0; bootFlagAddr <= (int *)POKE_MEM_ADDR_MPU2_3; bootFlagAddr += POKE_MEM_ADDR_GAP)
        {
            if (*bootFlagAddr == UPDATE_VALUE)
            {
                numCoresBooted++;
            }
        }
        if(numCoresBooted == BOOTAPP_NUM_BOOT_CORES)
        {
            sbl_puts("lateapps booted successfully\n\r");
            sbl_puts(CORE_NAME);
            sbl_puts(" reports: All tests have passed\n\r");
            break;
        }
        else
        {
            numCoresBooted = 0;
        }
    }
    /* Clean up pokemem flags for the next run */
    for (bootFlagAddr = (volatile int *)POKE_MEM_ADDR_MCU1_0;
        bootFlagAddr <= (int *)POKE_MEM_ADDR_MPU2_3;
        bootFlagAddr += POKE_MEM_ADDR_GAP)
    {
        *bootFlagAddr = DEFAULT_VALUE;
    }
#endif
#else
    /* if we have run before, someone
       reset the system, dont print message */
    if (*pokeMemAddr != UPDATE_VALUE)
    {
        while (bootDelay--);
        sbl_puts(CORE_NAME);
        sbl_puts(" running\n\r");
        /* log completion */
        *pokeMemAddr = UPDATE_VALUE;
        #if defined(BUILD_XIP)
            sbl_puts("XIP Boot test has passed\n\r");
        #endif
    }
#if defined(BUILD_MCU1_0)
    delay1 = 10;
    delay2 = BOOT_DELAY;
    while(delay1--)
    {
        while (delay2--)
        {
            /* Do Nothing */
        }
        delay2 = BOOT_DELAY;
    }
    while(1)
    {
        for (bootFlagAddr = (volatile int *)POKE_MEM_ADDR_MCU1_0; bootFlagAddr <= (int *)POKE_MEM_ADDR_MPU2_3; bootFlagAddr += POKE_MEM_ADDR_GAP)
        {
            if (*bootFlagAddr == UPDATE_VALUE)
            {
                numCoresBooted++;
            }
        }
        if(numCoresBooted == SBL_AMP_TEST_NUM_BOOT_CORES)
        {
            sbl_puts(CORE_NAME);
            sbl_puts(" reports: All tests have passed\n\r");
            break;
        }
        else
        {
            numCoresBooted = 0;
        }
    }
    /* Clean up pokemem flags for the next run */
    for (bootFlagAddr = (volatile int *)POKE_MEM_ADDR_MCU1_0;
        bootFlagAddr <= (int *)POKE_MEM_ADDR_MPU2_3;
        bootFlagAddr += POKE_MEM_ADDR_GAP)
    {
        *bootFlagAddr = DEFAULT_VALUE;
    }
#endif
#endif

    return DEFAULT_VALUE;
}

