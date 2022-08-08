/*
 *  Copyright ( C ) 2022 Texas Instruments Incorporated
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
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES ( INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION ) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  ( INCLUDING NEGLIGENCE OR OTHERWISE ) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <ti/osal/DebugP.h>
#include <ti/osal/TimerP.h>
#include <ti/osal/HwiP.h>
#include <ti/csl/soc.h>
#include <SAFERTOS_log.h>
#include <SafeRTOS_API.h>

#if defined (BUILD_C7X)
#include <c7x.h>    /* for C7x intrinsics */
#endif

/*
 * IMPORTANT NOTES:
 *
 * Alignment of stack is not strictly needed for R5F but debug is easier if stack is nicely
 * aligned.
 *
 * Task priority, 0 is lowest priority, configMAX_PRIORITIES-1 is highest
 * For this example any valid task priority can be set.
 *
 * See SafeRTOSConfig.h for configMAX_PRIORITIES and portStackType type.
 * SafeRTOSConfig.h can be found under kernel/SafeRTOS/config/${device}/${cpu}/
 *
 * In this example,
 * We create task's, semaphore's, ISR's and stack for the tasks using static allocation.
 * We dont need to delete these semaphore's since static allocation is used.
 *
 * One MUST not return out of a SafeRTOS task instead one MUST call vTaskDelete instead.
 */

#define NUM_TASK_SWITCHES      ( 1000000u )

#ifdef SOC_J721E
    #ifdef BUILD_MCU1_0
        #define PING_INT_NUM           ( CSLR_MCU_R5FSS0_CORE0_INTR_MAIN2MCU_LVL_INTRTR0_OUTL_0 )
        #define PONG_INT_NUM           ( CSLR_MCU_R5FSS0_CORE0_INTR_MAIN2MCU_LVL_INTRTR0_OUTL_1 )
    #endif
    #ifdef BUILD_MCU1_1
        #define PING_INT_NUM           ( CSLR_MCU_R5FSS0_CORE1_INTR_MAIN2MCU_LVL_INTRTR0_OUTL_0 )
        #define PONG_INT_NUM           ( CSLR_MCU_R5FSS0_CORE1_INTR_MAIN2MCU_LVL_INTRTR0_OUTL_1 )
#endif
    #ifdef BUILD_MCU2_0
        #define PING_INT_NUM           ( CSLR_R5FSS0_CORE0_INTR_R5FSS0_INTROUTER0_OUTL_0 )
        #define PONG_INT_NUM           ( CSLR_R5FSS0_CORE0_INTR_R5FSS0_INTROUTER0_OUTL_1 )
    #endif
    #ifdef BUILD_MCU2_1
        #define PING_INT_NUM           ( CSLR_R5FSS0_CORE1_INTR_R5FSS0_INTROUTER0_OUTL_0 )
        #define PONG_INT_NUM           ( CSLR_R5FSS0_CORE1_INTR_R5FSS0_INTROUTER0_OUTL_1 )
    #endif
    #ifdef BUILD_MCU3_0
        #define PING_INT_NUM           ( CSLR_R5FSS1_CORE0_INTR_R5FSS1_INTROUTER0_OUTL_0 )
        #define PONG_INT_NUM           ( CSLR_R5FSS1_CORE0_INTR_R5FSS1_INTROUTER0_OUTL_1 )
    #endif
    #ifdef BUILD_MCU3_1
        #define PING_INT_NUM           ( CSLR_R5FSS1_CORE1_INTR_R5FSS1_INTROUTER0_OUTL_0 )
        #define PONG_INT_NUM           ( CSLR_R5FSS1_CORE1_INTR_R5FSS1_INTROUTER0_OUTL_1 )
    #endif
    #ifdef BUILD_C66X_1
        #define PING_INT_NUM           (8u)
        #define PING_EVT_ID            (CSLR_C66SS0_CORE0_C66_EVENT_IN_SYNC_C66SS0_INTROUTER0_OUTL_0)
        #define PONG_INT_NUM           (9u)
        #define PONG_EVT_ID            (CSLR_C66SS0_CORE0_C66_EVENT_IN_SYNC_C66SS0_INTROUTER0_OUTL_1)
    #endif
    #ifdef BUILD_C66X_2
        #define PING_INT_NUM           (8u)
        #define PING_EVT_ID            (CSLR_C66SS1_CORE0_C66_EVENT_IN_SYNC_C66SS1_INTROUTER0_OUTL_0)
        #define PONG_INT_NUM           (9u)
        #define PONG_EVT_ID            (CSLR_C66SS1_CORE0_C66_EVENT_IN_SYNC_C66SS1_INTROUTER0_OUTL_1)
    #endif
    #ifdef BUILD_C7X_1
        #define PING_INT_NUM           (14u)
        #define PING_EVT_ID            (0x4E0)
        #define PONG_INT_NUM           (15u)
        #define PONG_EVT_ID            (0x4E1)
    #endif
#endif

#ifdef SOC_J7200
    #ifdef BUILD_MCU1_0
        #define PING_INT_NUM           (CSLR_MCU_R5FSS0_CORE0_INTR_MAIN2MCU_LVL_INTRTR0_OUTL_0)
        #define PONG_INT_NUM           (CSLR_MCU_R5FSS0_CORE0_INTR_MAIN2MCU_LVL_INTRTR0_OUTL_1)
    #endif
    #ifdef BUILD_MCU1_1
        #define PING_INT_NUM           (CSLR_MCU_R5FSS0_CORE1_INTR_MAIN2MCU_LVL_INTRTR0_OUTL_0)
        #define PONG_INT_NUM           (CSLR_MCU_R5FSS0_CORE1_INTR_MAIN2MCU_LVL_INTRTR0_OUTL_1)
#endif
    #ifdef BUILD_MCU2_0
        #define PING_INT_NUM           (CSLR_R5FSS0_CORE0_INTR_COMPUTE_CLUSTER0_MSMC_EN_SOC_EVENTS_OUT_LEVEL_0)
        #define PONG_INT_NUM           (CSLR_R5FSS0_CORE0_INTR_COMPUTE_CLUSTER0_MSMC_EN_SOC_EVENTS_OUT_LEVEL_1)
    #endif
    #ifdef BUILD_MCU2_1
        #define PING_INT_NUM           (CSLR_R5FSS0_CORE1_INTR_COMPUTE_CLUSTER0_MSMC_EN_SOC_EVENTS_OUT_LEVEL_0)
        #define PONG_INT_NUM           (CSLR_R5FSS0_CORE1_INTR_COMPUTE_CLUSTER0_MSMC_EN_SOC_EVENTS_OUT_LEVEL_1)
    #endif
#endif

#define PING_TASK_PRI  ( 2u )
#define PONG_TASK_PRI  ( 3u )


#if !defined (BUILD_C7X)
#define PING_TASK_SIZE ( 4096u )
#define PONG_TASK_SIZE ( 4096u )
#else
#define PING_TASK_SIZE ( 16U * 1024U)
#define PONG_TASK_SIZE ( 16U * 1024U)
#endif

static portInt8Type  gPingTaskStack[PING_TASK_SIZE] __attribute__( ( aligned( PING_TASK_SIZE ) ) );

static portInt8Type  gPongTaskStack[PONG_TASK_SIZE] __attribute__( ( aligned( PONG_TASK_SIZE ) ) );


static xTCB xPingTaskTCB = { 0 };
static xTCB xPongTaskTCB = { 0 };


/* Semaphore buffers. No actual data is stored into these buffers, so the
 * buffer need only be large enough to hold the queue structure itself. */
portInt8Type gPingSemBuf[ safertosapiQUEUE_OVERHEAD_BYTES ] __attribute__( ( aligned ( safertosapiWORD_ALIGNMENT ) ) ) = { 0 };
portInt8Type gPongSemBuf[ safertosapiQUEUE_OVERHEAD_BYTES ] __attribute__( ( aligned ( safertosapiWORD_ALIGNMENT ) ) ) = { 0 };

/* Semaphore Parameters. */
static xSemaphoreHandle gPingSem = NULL;
static xSemaphoreHandle gPongSem = NULL;

static void ping_isr( uintptr_t arg )
{
    xSemaphoreGiveFromISR(gPongSem); /* wake up pong task */
    safertosapiYIELD_FROM_ISR();
}

static void pong_isr( uintptr_t arg )
{
    xSemaphoreGiveFromISR(gPingSem); /* wake up ping task */
    safertosapiYIELD_FROM_ISR();
}

#if defined (BUILD_C7X)
/* return current counter value of high speed counter in units of 10's of usecs */
uint32_t uiPortGetRunTimeCounterValue()
{
    uint64_t ts = __TSC;
    uint64_t timeInUsecs;

    timeInUsecs = (ts * 1000000) / configCPU_CLOCK_HZ;
    /* note, there is no overflow protection for this 32b value in FreeRTOS
     *
     * Dividing by 10 to reduce the resolution and avoid overflow for longer duration
     * This will overflow after
     * ((0x100000000/1000000)/(60*60))*10 hours ~ 12 hrs
     */
    return (uint32_t)timeInUsecs;
}
#endif

void ping_main( void *args )
{
    uint32_t count; /* loop `count` times */
    volatile uint64_t curTime; /* time in units of 10's of usecs */
    portBaseType xResult = pdPASS;
    portBaseType semaphoreResult = pdPASS;

    SAFERTOS_log( "\r\n" );
    SAFERTOS_log( "[SafeRTOS] ping task ... start !!!\r\n" );
    { /* switch between ping and pong tasks using semaphores */
        count = NUM_TASK_SWITCHES;
        curTime = TimerP_getTimeInUsecs();
        while( count-- && ( pdPASS == semaphoreResult ) )
        {
            semaphoreResult = xSemaphoreGive( gPongSem );
            if( pdPASS == semaphoreResult )
            {
                semaphoreResult = xSemaphoreTake( gPingSem, safertosapiMAX_DELAY );
            }
        }
        DebugP_assert( pdPASS == semaphoreResult );

        curTime = TimerP_getTimeInUsecs() - curTime;

        SAFERTOS_log( "\r\n" );
        SAFERTOS_log("execution time for task switches = %d us\r\n", (uint32_t)(curTime/1000));
        SAFERTOS_log("number of task switches = %d \r\n", (uint32_t)NUM_TASK_SWITCHES*2);
        SAFERTOS_log("time per task switch (semaphore give/take) = %d ns\r\n", (uint32_t)(curTime*1000/(NUM_TASK_SWITCHES*2)));
    }
    { /* switch from ping task to ISR to pong task and back to ping task using semaphores, here there is a task switch */
        HwiP_Params hwiParams;
        HwiP_Handle hHwi;
        HwiP_Status hwiStatus;

        HwiP_Params_init( &hwiParams );
#if defined (BUILD_C66X)
        hwiParams.evtId = PING_EVT_ID;
#endif
        hHwi = HwiP_create( PING_INT_NUM, ping_isr, &hwiParams );
        DebugP_assert( hHwi != NULL );

        count = NUM_TASK_SWITCHES;
        curTime = TimerP_getTimeInUsecs();
        while( count-- && ( pdPASS == semaphoreResult ) )
        {
            HwiP_post( PING_INT_NUM );
            semaphoreResult = xSemaphoreTake( gPingSem, safertosapiMAX_DELAY );
        }
        DebugP_assert( pdPASS == semaphoreResult );

        curTime = TimerP_getTimeInUsecs() - curTime;
        
        hwiStatus = HwiP_delete( hHwi );
        DebugP_assert( hwiStatus == HwiP_OK );

        SAFERTOS_log( "\r\n" );
        SAFERTOS_log("execution time for task switches = %d us\r\n", (uint32_t)(curTime/1000));
        SAFERTOS_log("number of task switches = %d \r\n", (uint32_t)NUM_TASK_SWITCHES*2);
        SAFERTOS_log("time per task switch (semaphore give/take) = %d ns\r\n", (uint32_t)(curTime*1000/(NUM_TASK_SWITCHES*2)));
    }

    /* delay some time, just to show delay works */
    xResult = xTaskDelay( 100 / configTICK_RATE_MS );
    if( pdPASS == xResult )
    {
        xResult = xTaskDelay( 101 / configTICK_RATE_MS );
        if( pdPASS == xResult )
        {
            SAFERTOS_log( "\r\n" );
            SAFERTOS_log( "[SafeRTOS] ping task ... done !!!\r\n" );
            SAFERTOS_log( "\r\n" );
            SAFERTOS_log( "All tests have passed!!\r\n" );
            SAFERTOS_log( "All tests have passed!!\r\n" );
            ( void )xTaskDelete(  NULL  );
        }
    }
    DebugP_assert( xResult ); /* Failed if task reaches here. */
}

void pong_main( void *args )
{
    uint32_t count; /* loop `count` times */
    portBaseType semaphoreResult = pdPASS;

    count = NUM_TASK_SWITCHES;
    while( count-- && ( pdPASS == semaphoreResult ) )
    {
        semaphoreResult = xSemaphoreTake( gPongSem, safertosapiMAX_DELAY );
        if( pdPASS == semaphoreResult )
        {
            semaphoreResult = xSemaphoreGive( gPingSem );
        }
    }
    DebugP_assert( pdPASS == semaphoreResult );

    {
        HwiP_Params hwiParams;
        HwiP_Handle hHwi;
        HwiP_Status hwiStatus;

        HwiP_Params_init( &hwiParams );
#if defined (BUILD_C66X)
        hwiParams.evtId = PONG_EVT_ID;
#endif
        hHwi = HwiP_create( PONG_INT_NUM, pong_isr, &hwiParams );
        DebugP_assert( hHwi != NULL );

        count = NUM_TASK_SWITCHES;
        while( count-- && ( pdPASS == semaphoreResult ) )
        {
            semaphoreResult = xSemaphoreTake( gPongSem, safertosapiMAX_DELAY );
            if( pdPASS == semaphoreResult )
            {
                HwiP_post( PONG_INT_NUM );
            }
        }
        DebugP_assert( pdPASS == semaphoreResult );

        hwiStatus = HwiP_delete( hHwi );
        DebugP_assert( HwiP_OK == hwiStatus );
    }
    ( void )xTaskDelete(  NULL  );
}

void task_switch_main( void *args )
{
    portBaseType xStatus;

    /* Create the semaphore used by the first two tasks. */
    xSemaphoreCreateBinary( gPingSemBuf, &gPingSem );
    if( gPingSem == NULL )
    {
        xStatus = pdFAIL;
    }
    else
    {
        xStatus = xSemaphoreTake( gPingSem, safertosapiMAX_DELAY );
    }
    DebugP_assert(xStatus != pdFAIL);
    xSemaphoreCreateBinary( gPongSemBuf, &gPongSem );
    if( gPongSem == NULL )
    {
        xStatus = pdFAIL;
    }
    else
    {
        xStatus = xSemaphoreTake( gPongSem, safertosapiMAX_DELAY );
    }
    DebugP_assert(xStatus != pdFAIL);
    
    xTaskParameters xPongMainParameters =
    {
        &pong_main,                         /* Task code */
        "pong",                             /* Task name */
        &xPongTaskTCB,                      /* TCB */
        gPongTaskStack,                     /* Stack buffer */
        PONG_TASK_SIZE,                     /* Stack depth bytes */
        NULL,                               /* Parameters */
        PONG_TASK_PRI,                      /* Priority */
        NULL,                               /* TLS object */
#if defined (BUILD_MCU)
        pdFALSE,                            /* Check task does not use the FPU. */
         {                                  /* MPU task parameters. */
                mpuPRIVILEGED_TASK,         /* Check task is privileged. */
                {
                    { NULL, 0U, 0U, 0U },   /* No additional region definitions are required. */
                    { NULL, 0U, 0U, 0U },
                }
            }                               /* Port-specific task parameters */
#endif
#if defined (BUILD_C66X)
        safertosapiUNPRIVILEGED_TASK,           /* The idle hook will not be executed in privileged mode. */
#endif
    };

    
    xTaskParameters xPingMainParameters =
    {
        &ping_main,                         /* Task code */
        "ping",                             /* Task name */
        &xPingTaskTCB,                      /* TCB */
        gPingTaskStack,                     /* Stack buffer */
        PING_TASK_SIZE,                     /* Stack depth bytes */
        NULL,                               /* Parameters */
        PING_TASK_PRI,                      /* Priority */
        NULL,                               /* TLS object */
#if defined (BUILD_MCU)
        pdFALSE,                            /* Check task does not use the FPU. */
         {                                  /* MPU task parameters. */
                mpuPRIVILEGED_TASK,         /* Check task is privileged. */
                {
                    { NULL, 0U, 0U, 0U },   /* No additional region definitions are required. */
                    { NULL, 0U, 0U, 0U },
                }
            }                               /* Port-specific task parameters */
#endif
#if defined (BUILD_C66X)
        safertosapiUNPRIVILEGED_TASK,           /* The idle hook will not be executed in privileged mode. */
#endif
    };
    
    /* Create the privileged test tasks. */
    if( xTaskCreate( &xPongMainParameters, NULL ) != pdPASS )
    {
        xStatus = pdFAIL;
    } 
    DebugP_assert(xStatus != pdFAIL);

    if( xTaskCreate( &xPingMainParameters, NULL ) != pdPASS )
    {
        xStatus = pdFAIL;
    }
    DebugP_assert(xStatus != pdFAIL);

    /* Dont close drivers to keep the UART driver open for console */
    /* Drivers_close(  ); */
    ( void )xTaskDelete( NULL );
}

