/*
 * FreeRTOS Kernel V10.4.1
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 * 1 tab == 4 spaces!
 */
/*
 *  Copyright (C) 2018-2021 Texas Instruments Incorporated
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
#include <stdint.h>
#include <stdio.h>
#include <FreeRTOS.h>
#include <task.h>
#include <ti/osal/HwiP.h>
#include <ti/osal/TimerP.h>
#include <ti/osal/DebugP.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/r5/csl_arm_r5_pmu.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/osal/src/nonos/Nonos_config.h>

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case is messes up unwinding of the stack in the
 * debugger. */
#ifdef configTASK_RETURN_ADDRESS
    #define portTASK_RETURN_ADDRESS    configTASK_RETURN_ADDRESS
#else
    #define portTASK_RETURN_ADDRESS    prvTaskExitError
#endif

/* Constants required to setup the initial task context. */
#define portINITIAL_SPSR                 ( ( StackType_t ) 0x1f ) /* System mode, ARM mode, IRQ enabled FIQ enabled. */
#define portTHUMB_MODE_BIT               ( ( StackType_t ) 0x20 )
#define portINTERRUPT_ENABLE_BIT         ( 0x80UL )
#define portTHUMB_MODE_ADDRESS           ( 0x01UL )

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#define portNO_CRITICAL_NESTING          ( ( uint32_t ) 0 )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#define portNO_FLOATING_POINT_CONTEXT    ( ( StackType_t ) 0 )

/* A variable is used to keep track of the critical section nesting.  This
 * variable has to be stored as part of the task context and must be initialised to
 * a non zero value to ensure interrupts don't inadvertently become unmasked before
 * the scheduler starts.  As it is stored as part of the task context it will
 * automatically be set to 0 when the first task is started. */
volatile uint32_t ulCriticalNesting = 9999UL;

/* Saved as part of the task context.  If ulPortTaskHasFPUContext is non-zero then
 * a floating point context must be saved and restored for the task. */
uint32_t ulPortTaskHasFPUContext = pdFALSE;

/* Set to 1 to pend a context switch from an ISR. */
uint32_t ulPortYieldRequired = pdFALSE;

/* Counts the interrupt nesting depth.  A context switch is only performed if
 * if the nesting depth is 0. */
uint32_t ulPortInterruptNesting = 0UL;

/* set to true when schedular gets enabled in xPortStartScheduler */
uint32_t ulPortSchedularRunning = pdFALSE;

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
extern void vPortRestoreTaskContext( void );
static uint64_t prvPortReadPmuCounter(void);
    
static void prvTaskExitError( void )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    DebugP_assert(0);
}

StackType_t * pxPortInitialiseStack( StackType_t * pxTopOfStack,
                                     TaskFunction_t pxCode,
                                     void * pvParameters )
{
    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro.
     *
     * The fist real value on the stack is the status register, which is set for
     * system mode, with interrupts enabled.  A few NULLs are added first to ensure
     * GDB does not try decoding a non-existent return address. */
    *pxTopOfStack = ( StackType_t ) NULL;
    pxTopOfStack--;
    *pxTopOfStack = ( StackType_t ) NULL;
    pxTopOfStack--;
    *pxTopOfStack = ( StackType_t ) NULL;
    pxTopOfStack--;
    *pxTopOfStack = ( StackType_t ) portINITIAL_SPSR;

    if( ( ( uint32_t ) pxCode & portTHUMB_MODE_ADDRESS ) != 0x00UL )
    {
        /* The task will start in THUMB mode. */
        *pxTopOfStack |= portTHUMB_MODE_BIT;
    }

    pxTopOfStack--;

    /* Next the return address, which in this case is the start of the task. */
    *pxTopOfStack = ( StackType_t ) pxCode;
    pxTopOfStack--;

    /* Next all the registers other than the stack pointer. */
    *pxTopOfStack = ( StackType_t ) portTASK_RETURN_ADDRESS; /* R14 */
    pxTopOfStack--;
    *pxTopOfStack = ( StackType_t ) 0x12121212;              /* R12 */
    pxTopOfStack--;
    *pxTopOfStack = ( StackType_t ) 0x11111111;              /* R11 */
    pxTopOfStack--;
    *pxTopOfStack = ( StackType_t ) 0x10101010;              /* R10 */
    pxTopOfStack--;
    *pxTopOfStack = ( StackType_t ) 0x09090909;              /* R9 */
    pxTopOfStack--;
    *pxTopOfStack = ( StackType_t ) 0x08080808;              /* R8 */
    pxTopOfStack--;
    *pxTopOfStack = ( StackType_t ) 0x07070707;              /* R7 */
    pxTopOfStack--;
    *pxTopOfStack = ( StackType_t ) 0x06060606;              /* R6 */
    pxTopOfStack--;
    *pxTopOfStack = ( StackType_t ) 0x05050505;              /* R5 */
    pxTopOfStack--;
    *pxTopOfStack = ( StackType_t ) 0x04040404;              /* R4 */
    pxTopOfStack--;
    *pxTopOfStack = ( StackType_t ) 0x03030303;              /* R3 */
    pxTopOfStack--;
    *pxTopOfStack = ( StackType_t ) 0x02020202;              /* R2 */
    pxTopOfStack--;
    *pxTopOfStack = ( StackType_t ) 0x01010101;              /* R1 */
    pxTopOfStack--;
    *pxTopOfStack = ( StackType_t ) pvParameters;            /* R0 */
    pxTopOfStack--;

    /* The task will start with a critical nesting count of 0 as interrupts are
     * enabled. */
    *pxTopOfStack = portNO_CRITICAL_NESTING;
    pxTopOfStack--;

    /* The task will start without a floating point context.  A task that uses
     * the floating point hardware must call vPortTaskUsesFPU() before executing
     * any floating point instructions. */
    *pxTopOfStack = portNO_FLOATING_POINT_CONTEXT;

    return pxTopOfStack;
}

TimerP_Handle pTickTimerHandle = NULL;
uint64_t portLastTimerTS;
static void prvPorttimerTickIsr(uintptr_t args)
{
    void vPortTimerTickHandler();

    portLastTimerTS = prvPortReadPmuCounter();
    vPortTimerTickHandler();
}

static void prvPortInitTickTimer(void)
{

    TimerP_Params timerParams;

    TimerP_Params_init(&timerParams);
    timerParams.runMode    = TimerP_RunMode_CONTINUOUS;
    timerParams.startMode  = TimerP_StartMode_USER;
    timerParams.periodType = TimerP_PeriodType_MICROSECS;
    timerParams.period     = (portTICK_PERIOD_MS * 1000);

    pTickTimerHandle = TimerP_create(configTIMER_ID, &prvPorttimerTickIsr, &timerParams);

    /* don't expect the handle to be null */
    DebugP_assert (pTickTimerHandle != NULL);

}

static void prvPortStartTickTimer(void)
{
    TimerP_Status status;
    status = TimerP_start(pTickTimerHandle);

    /* don't expect the handle to be null */
    DebugP_assert (status == TimerP_OK);

}

BaseType_t xPortStartScheduler(void)
{
    /* Interrupts are turned off in the CPU itself to ensure tick does
     * not execute	while the scheduler is being started.  Interrupts are
     * automatically turned back on in the CPU when the first task starts
     * executing.
     */
    portDISABLE_INTERRUPTS();

    #if (configCOPY_RESET_VECTORS==1)
    /* Relocate FreeRTOS Reset Vectors to ATCM*/
    void _freertosresetvectors (void);  
    memcpy((void *)configMCU_ATCM_BASE, (void *)_freertosresetvectors, 0x40);
    #endif

    /* Start the ISR handling of the timer that generates the tick ISR. */
    ulPortSchedularRunning = pdTRUE;

    prvPortInitTickTimer();
    prvPortStartTickTimer();
    /* Start the first task executing. */
    vPortRestoreTaskContext();

    /* Will only get here if vTaskStartScheduler() was called with the CPU in
     * a non-privileged mode or the binary point register was not set to its lowest
     * possible value.  prvTaskExitError() is referenced to prevent a compiler
     * warning about it being defined but not referenced in the case that the user
     * defines their own exit address. */
    ( void ) prvTaskExitError;

    return pdTRUE;
}

void vPortYeildFromISR( uint32_t xSwitchRequired )
{
    if( xSwitchRequired != pdFALSE )
    {
        ulPortYieldRequired = pdTRUE;
    }
}

void vPortTimerTickHandler()
{
    if( ulPortSchedularRunning == pdTRUE )
    {
        /* Increment the RTOS tick. */
        if( xTaskIncrementTick() != pdFALSE )
        {
            ulPortYieldRequired = pdTRUE;
        }
    }
}

void vPortTaskUsesFPU( void )
{
    /* A task is registering the fact that it needs an FPU context.  Set the
     * FPU flag (which is saved as part of the task context). */
    ulPortTaskHasFPUContext = pdTRUE;

    /* Initialise the floating point status register. */
    asm ( " FMXR 	FPSCR, R0");
}

void vPortEnterCritical( void )
{
    /* Mask interrupts up to the max syscall interrupt priority. */
    asm ( " DSB ");
    asm ( " ISB ");
    asm ( " CPSID	i");
    asm ( " DSB ");
    asm ( " ISB ");

    /* Now interrupts are disabled ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;
    asm ( " DSB ");
    asm ( " ISB ");

    #if (configOPTIMIZE_FOR_LATENCY==0)
    /* This API should NOT be called from within ISR context. Below logic checks for this.
     * Commenting this reduces task switch latency a bit, however if this API is by mistale
     * called in a ISR by user, it could have unexpected side effects.
     */
    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    if( ulCriticalNesting == 1 )
    {
        DebugP_assert( ulPortInterruptNesting == 0);
    }
    #endif
}

void vPortExitCritical( void )
{
    /* if( ulCriticalNesting > portNO_CRITICAL_NESTING ) */
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        asm ( " DSB ");
        asm ( " ISB ");
        ulCriticalNesting--;
        asm ( " DSB ");
        asm ( " ISB ");

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        if( ulCriticalNesting == portNO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            asm ( " CPSIE	i");
            asm ( " DSB ");
            asm ( " ISB ");
        }
    }
}

static uint32_t gTimeStampOverFlowCount = 0;

/* initialize high resolution timer for CPU and task load calculation */
void vPortConfigTimerForRunTimeStats()
{
    CSL_armR5PmuEnableAllCntrs(1);    /* Set/clear PMCR E-bit */
    CSL_armR5PmuResetCntrs();         /* Set PMCR P-bit */
    CSL_armR5PmuResetCycleCnt();      /* Set PMCR C-bit */
    CSL_armR5PmuEnableCntr(CSL_ARM_R5_PMU_CYCLE_COUNTER_NUM, 1);     /* Set PMCNTENSET for event */
    CSL_armR5PmuClearCntrOverflowStatus(0x80000007);
    gTimeStampOverFlowCount = 0;
}

static uint64_t prvPortReadPmuCounter(void)
{
    uint32_t tsLo;
    uint32_t ovsrStatus;
    uint64_t ts;

    tsLo = CSL_armR5PmuReadCntr(CSL_ARM_R5_PMU_CYCLE_COUNTER_NUM);
    ovsrStatus = (CSL_armR5PmuReadCntrOverflowStatus() & (0x1U << CSL_ARM_R5_PMU_CYCLE_COUNTER_NUM));

    if (ovsrStatus != 0)
    {
        tsLo = CSL_armR5PmuReadCntr(CSL_ARM_R5_PMU_CYCLE_COUNTER_NUM);
        gTimeStampOverFlowCount++;
        CSL_armR5PmuClearCntrOverflowStatus((0x1U << CSL_ARM_R5_PMU_CYCLE_COUNTER_NUM));
    }
    ts = ((uint64_t)tsLo | ((uint64_t) gTimeStampOverFlowCount << 32U));

    return ts;
}


/* return current counter value of high speed counter in usecs */
uint32_t uiPortGetRunTimeCounterValue()
{
    uint64_t timeInUsecs;
    uint64_t ts;

    ts = prvPortReadPmuCounter();
    timeInUsecs = (ts * 1000000) / configCPU_CLOCK_HZ;


    /* note, there is no overflow protection for this 32b value in FreeRTOS
     *
     * This value will overflow in
     * ((0xFFFFFFFF)/(1000000*60)) minutes ~ 71 minutes
     *
     * We call LoadP_update() in idle loop (from vApplicationIdleHook) to accumlate the task load into a 64b value.
     * The implementation of LoadP_update() is in osal/src/freertos/LoadP_freertos.c
     * 
     */
    return (uint32_t)(timeInUsecs);
}

/* This is used to make sure we are using the FreeRTOS API from within a valid interrupt priority level
 * In our R%F port this means IRQ.
 * i.e FreeRTOS API should not be called from FIQ, however right now we dont enforce it by checking
 * if we are in FIQ when this API is called.
 */
void vPortValidateInterruptPriority()
{
}

/* This is called as part of vTaskEndScheduler(), in our port, there is nothing to do here.
 * interrupt are disabled by FreeRTOS before calling this.
 */
void vPortEndScheduler()
{
    /* nothing to do */
}

/* configCHECK_FOR_STACK_OVERFLOW is set to 1, so the application must provide an
 * implementation of vApplicationStackOverflowHook()
 */
void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                    char * pcTaskName )
{
    DebugP_log1("[FreeRTOS] Stack overflow detected for task [%s]", (uintptr_t)pcTaskName);
    DebugP_assert(0);
}

/* configSUPPORT_STATIC_ALLOCATION is set to 1, so the application must provide an
 * implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
 * used by the Idle task.
 */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize )
{
/* If the buffers to be provided to the Idle task are declared inside this
 * function then they must be declared static – otherwise they will be allocated on
 * the stack and so not exists after this function exits.
 */
static StaticTask_t xIdleTaskTCB;
static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle task’s
     * state will be stored.
     */
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

    /* Pass out the array that will be used as the Idle task’s stack. */
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
     * Note that, as the array is necessarily of type StackType_t,
     * configMINIMAL_STACK_SIZE is specified in words, not bytes.
     */
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

/* configSUPPORT_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
 * application must provide an implementation of vApplicationGetTimerTaskMemory()
 * to provide the memory that is used by the Timer service task.
 */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t **ppxTimerTaskStackBuffer,
                                     uint32_t *pulTimerTaskStackSize )
{
/* If the buffers to be provided to the Timer task are declared inside this
 * function then they must be declared static – otherwise they will be allocated on
 * the stack and so not exists after this function exits.
 */
static StaticTask_t xTimerTaskTCB;
static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

    /* Pass out a pointer to the StaticTask_t structure in which the Timer
     * task’s state will be stored.
     */
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

    /* Pass out the array that will be used as the Timer task’s stack. */
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;

    /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
     * Note that, as the array is necessarily of type StackType_t,
     * configTIMER_TASK_STACK_DEPTH is specified in words, not bytes.
     */
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

/*
 * Returns true if the current core is in ISR context; low prio ISR, med prio ISR or timer tick ISR. High prio ISRs
 * aren't detected here, but they normally cannot call C code, so that should not be an issue anyway.
 */
BaseType_t xPortInIsrContext()
{
    BaseType_t inISR = false;
    if (ulPortInterruptNesting != 0)
    {
        inISR =  true;
    }
    return inISR;
}

/*****************************************************************************/
/* _SYSTEM_POST_CINIT() - _system_post_cinit() is a hook function called in  */
/* the C/C++ auto-initialization function after cinit() and before pinit().  */
/*                                                                           */
/* The version of _system_post_cinit() below is skeletal and is provided to  */
/* illustrate the interface and provide default behavior.  To replace this   */
/* version rewrite the routine and include it as part of the current project.*/
/* The linker will include the updated version if it is linked in prior to   */
/* linking with the C/C++ runtime library.                                   */
/*****************************************************************************/

/*---------------------------------------------------------------------------*/
/* __TI_default_system_post_cinit indicates that the default                 */

__attribute__((weak)) void _system_post_cinit(void)
{
    osalArch_Config_t cfg;

    cfg.disableIrqOnInit = true;
    osalArch_Init(&cfg);
}

/* This function is called when configUSE_IDLE_HOOK is 1 in FreeRTOSConfig.h */
void vApplicationIdleHook( void )
{
#if (configLOAD_UPDATE_IN_IDLE==1)
    void vApplicationLoadHook();

    vApplicationLoadHook();
#endif

}
