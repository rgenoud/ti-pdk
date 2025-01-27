/*
 * audioSample_main.c
 *
 * This file contains the test / demo code to demonstrate the Audio component
 * driver functionality on SYS/BIOS 6.
 *
 * Copyright (C) 2009-2018 Texas Instruments Incorporated - http://www.ti.com/
 *
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
 *
*/

/** \file   audioSample_main.c
 *
 *  \brief    sample application for demonstration of audio driver usage
 *
 *  This file contains the implementation of the sample appliation for the
 *  demonstration of audio playing through the audio interface layer.
 *
 *             (C) Copyright 2009-2018, Texas Instruments, Inc
 */

/* ========================================================================== */
/*                            INCLUDE FILES                                   */
/* ========================================================================== */

#include <string.h>

#if defined (USE_BIOS)
#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Task.h>
#endif /* USE BIOS */

#include "mcasp_osal.h"

#include <mcasp_drv.h>
#ifdef AIC_CODEC
#include <Aic31.h>
#endif
#include <ti/drv/uart/UART.h>
#include <ti/drv/uart/UART_stdio.h>

#if !defined(SOC_AM65XX) && !defined(SOC_J721E) && !defined(SOC_J7200) && !defined(SOC_J721S2)
#include <ti/sdo/edma3/drv/edma3_drv.h>
#include <ti/csl/csl_edma3.h>
#endif

#include <ti/drv/mcasp/soc/mcasp_soc.h>

#define MCASP_AUD_SAMPLE_HEAP_SIZE  (200000U)
/**< McASP buffers */
#define MCASP_APP_TASK_STACK_SIZE   (16U * 1024U)
/**< Application stack size */

/* ========================================================================== */
/*                                Globals                                     */
/* ========================================================================== */
/* Application heap for McASP buffers*/
uint8_t mcaspEgAppHeap[MCASP_AUD_SAMPLE_HEAP_SIZE] __attribute__((aligned(128)));
/* Heap handle */
HeapP_Handle myHeap;
/* Application task stack */
/* For SafeRTOS on R5F with FFI Support, task stack should be aligned to the stack size */
#if defined(SAFERTOS) && defined (BUILD_MCU)
uint8_t gAppTskStackMain[MCASP_APP_TASK_STACK_SIZE] __attribute__((aligned(MCASP_APP_TASK_STACK_SIZE)));
#else
uint8_t gAppTskStackMain[MCASP_APP_TASK_STACK_SIZE] __attribute__((aligned(128)));
#endif
#if defined(BUILD_MPU) || defined (BUILD_C7X)
extern void Osal_initMmuDefault(void);
Void InitMmu()
{
    Osal_initMmuDefault();
}

#endif

#if !defined(SOC_AM65XX) && !defined(SOC_J721E) && !defined(SOC_J7200) && !defined(SOC_J721S2)
/* Handle to the EDMA driver instance                                         */
EDMA3_DRV_Handle hEdma;
#endif

void configureAudio(void);
void configMcASP_SocHwInfo(void);

extern void Audio_echo_Task(void *arg0, void *arg1);
/* ========================================================================== */
/*                           FUNCTION DEFINITIONS                             */
/* ========================================================================== */


/**
 *  \brief  Void main(Void)
 *
 *   Main function of the sample application. This function enables
 *   the mcasp instance in the power sleep controller and also
 *   enables the pinmux for the mcasp instance. This also powers up
 *   any codecs if attached to McASP like the AIC codec, before switching to 
 *   the task to Audio_echo_task().
 *
 *  \param  None
 *  \return None
 */
int main(void)
{
    HeapP_Params params;
    TaskP_Params tskParms;

    OS_init();

    myHeap = NULL;
    HeapP_Params_init(&params);

    params.buf = (void *) &mcaspEgAppHeap[0U];
    params.size = MCASP_AUD_SAMPLE_HEAP_SIZE;

    myHeap = HeapP_create (&params);

    /* enable the pinmux & PSC-enable for the mcasp device    */
    configureAudio();

    /* Initializing McASP HwInfo parameters */
    McaspDevice_init();

    /* Perform SOC specific McASP HwInfo Configuration for non-default parameters
     * using the socGetConfig() and socSetConfig(). Please note that
      this is being called AFTER McaspDevice_init() which initializes with the
      default parameters */
    configMcASP_SocHwInfo();
#if defined(AIC_CODEC)
    Aic31_init();
#endif

    /* create task here */
    TaskP_Params_init(&tskParms);
    tskParms.priority   = 5;
    tskParms.stack      = gAppTskStackMain;
    tskParms.stacksize  = MCASP_APP_TASK_STACK_SIZE;

    if ((TaskP_Handle)NULL != TaskP_create(&Audio_echo_Task, &tskParms))
    {
        OS_start();
    }

    return 0;
}
/*
 * Mcasp init function called when creating the driver.
 */




/* ========================================================================== */
/*                                END OF FILE                                 */
/* ========================================================================== */
