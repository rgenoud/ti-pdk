/******************************************************************************
 * Copyright (c) 2019-2020 Texas Instruments Incorporated - http://www.ti.com
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
 *****************************************************************************/

/**
 *  \file   hyperbus_test.c
 *
 *  \brief  hyperbus diagnostic test main file
 *
 *  Targeted Functionality: This file implements hyperbus diagnostic test.
 *
 *  Operation: Verification of hyperbus by accessing the device connected to it.
 *
 *  Supported SoCs : J721E & J7200.
 *
 *  Supported Platforms: j721e_evm & j7200_evm.
 *
 */

#include "hyperbus_test.h"

#if (defined(DIAG_STRESS_TEST) && defined(j7200_evm))
uint8_t txBuf[BOARD_DIAG_HPB_TEST_BYTES] __attribute__ ((section (".data_buffer")));
uint8_t rxBuf[BOARD_DIAG_HPB_TEST_BYTES] __attribute__ ((section (".data_buffer")));
#else
uint8_t txBuf[BOARD_DIAG_HPB_TEST_BYTES];
uint8_t rxBuf[BOARD_DIAG_HPB_TEST_BYTES];
#endif

#if defined(DIAG_STRESS_TEST)
/**
 * \brief   This function executes HyperFlash stress test.
 *
 * \return  int8_t
 *               0 - in case of success
 *              -1 - in case of failure.
 *
 */
static int8_t BoardDiag_hpbHyperFlashStressTest(void)
{
    Board_flashHandle boardHandle;
    Board_FlashInfo *flashInfo;
    Board_flash_STATUS retVal;
    uint32_t offset;
    uint32_t failIndex;
    char rdBuf = 'y';

    boardHandle = Board_flashOpen(BOARD_FLASH_ID_S71KS512S,
                                  BOARD_HPF_INSTANCE, NULL);
    if (!boardHandle)
    {
        UART_printf("Board_flashOpen Failed\n");
        return -1;
    }
    else
    {
        flashInfo = (Board_FlashInfo *)boardHandle;
        UART_printf("\nHyperFlash Device ID: 0x%x, Manufacturer ID: 0x%x \n",
                            flashInfo->device_id, flashInfo->manufacturer_id);
    }

    flashInfo->blkErase_flag = BFALSE;
    UART_printf("Erasing the complete chip... This will take few seconds\n\n");
    /* Erasing the complete chip */
    retVal = Board_flashEraseBlk(boardHandle, BOARD_DIAG_HPB_CHIP_ERASE);
    if (retVal != BOARD_FLASH_EOK)
    {
        UART_printf("\nBoard_flashEraseBlk failed\n");
        return -1;
    }

    BoardDiag_genPattern(&txBuf[0], BOARD_DIAG_HPB_TEST_BYTES,
                         BOARD_DIAG_TEST_PATTERN_RANDOM);

    for(offset = BOARD_DIAG_HPB_FIRST_VERIFY_ADDR;
        offset <= BOARD_DIAG_HPB_LAST_VERIFY_ADDR;
        offset += BOARD_DIAG_HPB_TEST_BYTES)
    {
        UART_printf("Verifying sector - %d...\n", (offset/BOARD_DIAG_HPB_TEST_BYTES));

        /* Write buffer to hyperflash */
        retVal = Board_flashWrite(boardHandle, offset,
                                  &txBuf[0], BOARD_DIAG_HPB_TEST_BYTES, NULL);
        if (retVal != BOARD_FLASH_EOK)
        {
            UART_printf("\nBoard_flashWrite failed\n");
            return -1;
        }

        BoardDiag_genPattern(&rxBuf[0], BOARD_DIAG_HPB_TEST_BYTES,
                             BOARD_DIAG_TEST_PATTERN_RANDOM);

        /* Read the hyperflash memory */
        retVal = Board_flashRead(boardHandle, offset,
                                 &rxBuf[0], BOARD_DIAG_HPB_TEST_BYTES, NULL);
        if (retVal != BOARD_FLASH_EOK)
        {
            UART_printf("\nBoard_flashRead failed\n");
            return -1;
        }

        if (!(BoardDiag_memCompare(&txBuf[0], &rxBuf[0], BOARD_DIAG_HPB_TEST_BYTES, &failIndex)))
        {
            UART_printf("\nData mismatch at offset = 0x%x\n", offset+failIndex);
            return -1;
        }

        /* Check if there a input from console to break the test */
        rdBuf = (char)BoardDiag_getUserInput(BOARD_UART_INSTANCE);
        if((rdBuf == 'b') || (rdBuf == 'B'))
        {
            UART_printf("Received Test Termination... Exiting the Test\n");
            UART_printf("HyperFlash Stress Test Status\n");
            UART_printf("============================================\n");
            UART_printf("\nHyperFlash Verified upto Sector - %d\n", ((offset/BOARD_DIAG_HPB_TEST_BYTES) + 1));
            break;
        }
    }
    return 0;
} /* DIAG_STRESS_TEST */
#else

/**
 * \brief   This function writes data, reads back the written data and compares.
 *
 * \param   offset      [IN]    Offset Address to write
 * \param   numOfBytes  [IN]    Number of bytes to write.
 *
 * \return  int8_t
 *               0 - in case of success
 *              -1 - in case of failure.
 *
 */
static int8_t BoardDiag_hpbReadWriteTest(Board_flashHandle handle,
                                         uint32_t offset,
                                         uint32_t numOfBytes)
{
    Board_flash_STATUS retVal;
    uint32_t blockNum, pageNum;
    uint32_t failIndex;

    retVal = Board_flashOffsetToBlkPage(handle, offset, &blockNum, &pageNum);
    if (retVal != BOARD_FLASH_EOK)
    {
        UART_printf("\nBoard_flashOffsetToBlkPage failed\n");
        return -1;
    }

    /* Erase block, to which data has to be written */
    retVal = Board_flashEraseBlk(handle, blockNum);
    if (retVal != BOARD_FLASH_EOK)
    {
        UART_printf("\nBoard_flashEraseBlk failed\n");
        return -1;
    }

    BoardDiag_genPattern(&txBuf[0], numOfBytes,
                         BOARD_DIAG_TEST_PATTERN_RANDOM);

    /* Write buffer to hyperflash */
    retVal = Board_flashWrite(handle, offset,
                              &txBuf[0], numOfBytes, NULL);
    if (retVal != BOARD_FLASH_EOK)
    {
        UART_printf("\nBoard_flashWrite failed\n");
        return -1;
    }

    /* Read the hyperflash memory */
    retVal = Board_flashRead(handle, offset,
                             &rxBuf[0], numOfBytes, NULL);
    if (retVal != BOARD_FLASH_EOK)
    {
        UART_printf("\nBoard_flashRead failed\n");
        return -1;
    }

    if (BoardDiag_memCompare(&txBuf[0], &rxBuf[0], numOfBytes, &failIndex)
                                                                    == BFALSE)
    {
        UART_printf("\nData mismatch at offset = 0x%x\n", failIndex);
        return -1;
    }
    return 0;
}

/**
 * \brief   This function executes HyperFlash functionality test.
 *
 * \return  int8_t
 *               0 - in case of success
 *              -1 - in case of failure.
 *
 */
static int8_t BoardDiag_hpbHyperFlashFunctionalTest(void)
{
    Board_flashHandle boardHandle;
    Board_FlashInfo *flashInfo;
    int8_t ret;

    boardHandle = Board_flashOpen(BOARD_FLASH_ID_S71KS512S,
                                  BOARD_HPF_INSTANCE, NULL);
    if (!boardHandle)
    {
        UART_printf("Board_flashOpen Failed\n");
        return -1;
    }
    else
    {
        flashInfo = (Board_FlashInfo *)boardHandle;
        UART_printf("\nHyperFlash Device ID: 0x%x, Manufacturer ID: 0x%x \n",
                            flashInfo->device_id, flashInfo->manufacturer_id);
    }

    UART_printf("\n\nVerifying First 512 bytes...");
    ret = BoardDiag_hpbReadWriteTest(boardHandle,
                                     BOARD_DIAG_HPB_FIRST_VERIFY_ADDR,
                                     BOARD_DIAG_HPB_TEST_BYTES);
    if (ret != 0)
    {
        UART_printf("Verifying first 512 bytes failed\n");
        Board_flashClose(boardHandle);
        return -1;
    }
    UART_printf("\nVerification of first 512 bytes was successful");

    UART_printf("\n\nVerifying Last 512 bytes...");
    ret = BoardDiag_hpbReadWriteTest(boardHandle,
                                     BOARD_DIAG_HPB_LAST_VERIFY_ADDR,
                                     BOARD_DIAG_HPB_TEST_BYTES);
    if (ret != 0)
    {
        UART_printf("Verifying last 512 bytes failed\n");
        Board_flashClose(boardHandle);
        return -1;
    }
    UART_printf("\nVerification of last 512 bytes was successful\n");
    Board_flashClose(boardHandle);

    return 0;
}
#endif

/**
 * \brief   The function performs the Hyperbus Diagnostic test.
 *
 * \return  int8_t
 *               0 - in case of success
 *              -1 - in case of failure.
 *
 */
int8_t BoardDiag_HyperBusTest(void)
{
    int8_t ret;

#ifdef DIAG_STRESS_TEST
    ret = BoardDiag_hpbHyperFlashStressTest();
#else
    ret = BoardDiag_hpbHyperFlashFunctionalTest();
#endif

    if (ret)
    {
        UART_printf("\nHyperflash Test Failed!!\n");
    }
    else
    {
        UART_printf("\nHyperflash Test Passed!");
    }

    return ret;
}

static void BoardDiag_ospiHyperFlashMux(void)
{
    GPIO_v0_HwAttrs gpioCfg;
    GPIO_socGetInitCfg(0, &gpioCfg);
    gpioCfg.baseAddr = CSL_WKUP_GPIO0_BASE;
    GPIO_socSetInitCfg(0, &gpioCfg);

    GPIO_init();
    GPIO_write(0, 1);
}

/**
 *  \brief   Hyperbus Diagnostic test main function
 *
 *  \return  int - Hyperbus Diagnostic test status.
 *             0 - in case of success
 *            -1 - in case of failure.
 *
 */
#ifndef SPI_BOOT_FRAMEWORK
int main(void)
{
    Board_STATUS status;
    Board_initCfg boardCfg;
    Board_PinmuxConfig_t pixmuxCfg;
    int ret = 0;

    /* Configure the pinmux for hyperbus as the default
       pinmux configuration is set for OSPI */
    Board_pinmuxGetCfg(&pixmuxCfg);
    pixmuxCfg.fssCfg = BOARD_PINMUX_FSS_HPB;
    Board_pinmuxSetCfg(&pixmuxCfg);

#ifdef PDK_RAW_BOOT
    boardCfg = BOARD_INIT_MODULE_CLOCK |
               BOARD_INIT_PINMUX_CONFIG |
               BOARD_INIT_UART_STDIO;
#else
    boardCfg = BOARD_INIT_UART_STDIO | 
               BOARD_INIT_PINMUX_CONFIG | BOARD_INIT_PLL;
#endif

    status = Board_init(boardCfg);
    if(status != BOARD_SOK)
    {
        return -1;
    }

#ifdef DIAG_STRESS_TEST
    UART_printf("\n***********************************************\n");
    UART_printf  ("*            HYPERBUS Stress Test             *\n");
    UART_printf  ("***********************************************\n");
#else
    UART_printf("\n*********************************************\n");
    UART_printf  ("*              HYPERBUS Test                *\n");
    UART_printf  ("*********************************************\n");
#endif

#if defined (j721e_evm) || defined (j7200_evm)
    UART_printf("\nConfiguring PLLs...");
    status = Board_init(BOARD_INIT_PLL);
    if(status != BOARD_SOK)
    {
        /* PLL configuration failure is observed with some of the clocks
           while running from JTAG but HyperBus clock gets configured properly.
           Print fail message and continue with the test.
         */
        UART_printf("PLL Configurations Failed!!");
    }
    else
    {
        UART_printf("Done\n");
    }
#endif

    BoardDiag_ospiHyperFlashMux();

    ret = BoardDiag_HyperBusTest();

    /* Switch back to default pinmux */
    Board_pinmuxGetCfg(&pixmuxCfg);
    pixmuxCfg.fssCfg = BOARD_PINMUX_FSS_OSPI;
    Board_pinmuxSetCfg(&pixmuxCfg);
    Board_init(BOARD_INIT_PINMUX_CONFIG);

    return ret;
}
#endif
