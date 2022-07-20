/*
 *  Copyright (C) 2013-2020 Texas Instruments Incorporated - http://www.ti.com/
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
 
/**
 *   \file       main.c
 *   \brief      This demonstrates Spinlock dal by acquiring different locks.
**/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "stdio.h"
#include "stdint.h"
#include <ti/csl/csl_spinlock.h>
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x) || defined (SOC_AM65XX) || defined (SOC_J721E) || defined (SOC_J7200) || defined (SOC_AM64X)
#include <ti/board/board.h>
#endif
#if defined (SOC_AM65XX) || defined (SOC_J721E) || defined (SOC_J7200) || defined (SOC_AM64X)
#include <ti/drv/uart/UART.h>
#include <ti/drv/uart/UART_stdio.h>
#else
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>
#endif
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>

#ifdef UNITY_INCLUDE_CONFIG_H
#include <ti/build/unit-test/Unity/src/unity.h>
#include <ti/build/unit-test/config/unity_config.h>
#endif

/* Unity test functions */
void test_csl_spinlock_test_app_runner(void);
void test_csl_spinlock_test_app(void);


/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */
#define MAX_NUM_SPINLOCKS       (256U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/*To use UARTConfigPuts function for prints*/
#if (defined (SOC_AM574x) || defined (SOC_AM572x)) || (defined (SOC_AM571x))
uint32_t uartBaseAddr = CSL_MPU_UART3_REGS;
uint32_t spinlockBaseAddr = CSL_MPU_SPINLOCK_REGS;
#endif
#if defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x)
uint32_t uartBaseAddr = SOC_UART1_BASE;
uint32_t spinlockBaseAddr = SOC_SPINLOCK_BASE;
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
uint32_t uartBaseAddr = SOC_UART3_BASE;
uint32_t spinlockBaseAddr = SOC_SPINLOCK_BASE;
#endif
#if defined (SOC_AM65XX) || defined (SOC_J721E) || defined (SOC_J7200)
uint32_t spinlockBaseAddr = CSL_NAVSS0_SPINLOCK_BASE;
#endif
#if defined (SOC_AM64X)
uint32_t spinlockBaseAddr = CSL_SPINLOCK0_BASE;
#endif

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
static void SpinlockAppPrint(const char * str);
static void SpinlockAppPrintNum(uint32_t num);
static uint32_t SpinlockAppIsPrintfSupported(void);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void padConfig_prcmEnable()
{
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x) || defined (SOC_AM65XX) || defined (SOC_J721E) || defined (SOC_J7200) || defined (SOC_AM64X)
/*Pad configurations */
    Board_initCfg boardCfg;
    boardCfg = BOARD_INIT_UNLOCK_MMR | BOARD_INIT_UART_STDIO | 
               BOARD_INIT_MODULE_CLOCK | BOARD_INIT_PINMUX_CONFIG;
    Board_init(boardCfg);
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_RXD,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_TXD,0x00000000);
    /* Set the UART Parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_SCLK,0x00040001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_CS0,0x00000001);
    /* Set the UART Parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);
#endif
}

void test_csl_spinlock_test_app(void)
{
    uint32_t status = 0, lock_num = 0;
    uint32_t numLocAcquired = 0;

    /*Pad configuration and PRCM enable*/
    padConfig_prcmEnable();

    #if defined (__ARM_ARCH_7A__)
    char     coreName[10] = {"A15"};
    #elif ((__ARM_ARCH == 7) && (__ARM_ARCH_PROFILE == 'M') && defined(__ARM_FEATURE_SIMD32))
    char     coreName[10] = {"M4"};
    #elif defined (_TMS320C6X)
    char     coreName[10] = {"DSP"};
    #elif defined (BUILD_MPU1_0)
    char     coreName[10] = {"MPU1_0"};
    #elif defined (BUILD_MCU1_0)
    char     coreName[10] = {"MCU1_0"};
    #elif defined (BUILD_MCU2_1)
    char     coreName[10] = {"MCU2_1"};
    #endif

    SpinlockAppPrint("\nOn ");
    SpinlockAppPrint(coreName);
    SpinlockAppPrint("\nSpinlock App\n");
    for (lock_num = 0; lock_num < MAX_NUM_SPINLOCKS; lock_num++)
    {
        status = SPINLOCKLockStatusSet(spinlockBaseAddr, lock_num);
#if defined(UNITY_INCLUDE_CONFIG_H)
        TEST_ASSERT_EQUAL_UINT32(0U, status);
#endif
        if (status == 0)
        {
            SpinlockAppPrint("\n");
            SpinlockAppPrint(coreName);
            SpinlockAppPrint(" acquired lock number:");
            SpinlockAppPrintNum(lock_num);
            numLocAcquired++;
        }
        else if (status == 1)
        {
            SpinlockAppPrint("\n");
            SpinlockAppPrint(coreName);
            SpinlockAppPrint(" could not acquire lock number:");
            SpinlockAppPrintNum(lock_num);
            SpinlockAppPrint(", lock is not free");
        }
    }
    SpinlockAppPrint("\n");
#if defined(UNITY_INCLUDE_CONFIG_H)
    TEST_ASSERT_EQUAL_UINT32(MAX_NUM_SPINLOCKS, numLocAcquired);
#endif
    if (numLocAcquired == MAX_NUM_SPINLOCKS)
    {
        SpinlockAppPrint("Acquired all available locks. Mark test as Pass.\n");
        SpinlockAppPrint("This testcase requires board power cycle.\n");
        SpinlockAppPrint("\nAll tests have passed..\n");
    }
    else
    {
        SpinlockAppPrint("Could not acquire all available locks. Mark test as FAIL.\n");
        SpinlockAppPrint("This testcase requires board power cycle.\n");
        SpinlockAppPrint("\nTest Failed..\n");
    }

    return;
}

static void SpinlockAppPrint(const char * str)
{
#if defined (SOC_AM65XX) || defined (SOC_J721E) || defined (SOC_J7200) || defined (SOC_AM64X)
    if (TRUE == SpinlockAppIsPrintfSupported())
    {
        printf(str);
    }
    UART_printf(str);
#else
    UARTConfigPuts(uartBaseAddr,str, -1);
#endif
}

static void SpinlockAppPrintNum(uint32_t num)
{
#if defined (SOC_AM65XX) || defined (SOC_J721E) || defined (SOC_J7200) || defined (SOC_AM64X)
    if (TRUE == SpinlockAppIsPrintfSupported())
    {
        printf("%d", num);
    }
    UART_printf("%d", num);
#else
    UARTConfigPutNum(uartBaseAddr, num);
#endif
}

static uint32_t SpinlockAppIsPrintfSupported(void)
{
    uint32_t retVal = TRUE;
    /* Printf doesn't work for MPU when run from SBL with no CCS connection
     * There is no flag to detect SBL or CCS mode. Hence disable the print
     * for MPU unconditionally */
#if defined (BUILD_MPU)
    retVal = FALSE;
#endif
#if defined (SOC_AM64X)
    retVal = FALSE;
#endif
    return retVal;
}

#ifdef UNITY_INCLUDE_CONFIG_H
/*
 *  ======== Unity set up and tear down ========
 */
void setUp(void)
{
    /* Do nothing */
}

void tearDown(void)
{
    /* Do nothing */
}
#endif

void test_csl_spinlock_test_app_runner(void)
{
    /* @description:Test runner for spinlock tests

       @requirements: PDK-2444

       @cores: mcu1_0 */
#if defined(UNITY_INCLUDE_CONFIG_H)
    UNITY_BEGIN();
    RUN_TEST (test_csl_spinlock_test_app);
    UNITY_END();
    /* Function to print results defined in our unity_config.h file */
    print_unityOutputBuffer_usingUARTstdio();
#else
    test_csl_spinlock_test_app();
#endif
    return;
}

int main(void)
{
    (void) test_csl_spinlock_test_app_runner();

    while (TRUE)
    {
    }
}
/********************************* End of file ******************************/

