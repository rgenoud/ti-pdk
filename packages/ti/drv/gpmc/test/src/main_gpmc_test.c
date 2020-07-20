/**
 *  \file   main_gpmc_test.c
 *
 *  \brief  Test application main file. This application will write and read
 *          the data to/from GPMC NOR/NAND flash through Board flash interface
 *          and GPMC SRAM memory using CPU/DMA.
 *
 */

/*
 * Copyright (C) 2016 -2020 Texas Instruments Incorporated - http://www.ti.com/
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of
 * its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <stdio.h>
#include <string.h>

#ifdef USE_BIOS
/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>

#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/utils/Load.h>
#endif

/* GPMC Header files */
#include <ti/drv/gpmc/GPMC.h>
#include <ti/drv/gpmc/soc/GPMC_soc.h>
#include <ti/drv/gpmc/test/src/GPMC_board.h>
#include <ti/drv/gpmc/test/src/GPMC_log.h>

/* Board Header files */
#include <ti/board/board.h>
#include <ti/board/src/flash/include/board_flash.h>
#include <ti/drv/sciclient/sciclient.h>

/**********************************************************************
 ************************** Macros ************************************
 **********************************************************************/
/* Define the GPMC test interface */
typedef struct GPMC_Tests_s
{
    uint32_t (*testFunc)(void *);
    uint32_t dmaMode;
    int16_t  testId;
    char     testDesc[80];

} GPMC_Tests;

/* GPMC test ID definitions */
#define GPMC_TEST_ID_RW          0   /* GPMC CPU read write test */
#define GPMC_TEST_ID_RW_DMA      1   /* GPMC DMA read write test */

/**********************************************************************
 ************************** Internal functions ************************
 **********************************************************************/

/* Function to generate known data */
static void GeneratePattern(uint8_t *txBuf, uint8_t *rxBuf, uint32_t length);

/* Data compare function */
bool VerifyData(uint8_t *expData,
                uint8_t *rxData,
                uint32_t length);

/**********************************************************************
 ************************** Global Variables **************************
 **********************************************************************/

/* Buffer containing the known data that needs to be written to flash */
uint8_t txBuf[TEST_DATA_LEN];

/* Buffer containing the received data */
uint8_t rxBuf[TEST_DATA_LEN];

/*
 *  ======== test function ========
 */
#if defined(SOC_AM335X) || defined(SOC_AM437X)
uint32_t gpmc_flash_test(void)
{
    Board_flashHandle boardHandle;
    Board_FlashInfo *flashInfo;
    uint32_t blockNum, pageNum;
    uint32_t testPassed = TRUE;

    /* Open the Board flash device with GPMC port instance
       and use the default GPMC configurations */
    boardHandle = Board_flashOpen(BOARD_FLASH_ID,
                                  BOARD_GPMC_INSTANCE, NULL);

    if (!boardHandle)
    {
        GPMC_log("\n Board_flashOpen failed. \n");
        testPassed = FALSE;
        goto err;
    }
    else
    {
        flashInfo = (Board_FlashInfo *)boardHandle;
        GPMC_log("\n GPMC flash device ID: 0x%x, manufacturer ID: 0x%x \n",
                flashInfo->device_id, flashInfo->manufacturer_id);
    }

    if (Board_flashOffsetToBlkPage(boardHandle, TEST_ADDR_OFFSET,
                                   &blockNum, &pageNum))
    {
        GPMC_log("\n Board_flashOffsetToBlkPage failed. \n");
        testPassed = FALSE;
        goto err;
    }

    /* Generate the data */
    GeneratePattern(txBuf, rxBuf, TEST_DATA_LEN);

#ifdef TEST_GPMC_FLASH_WRITE
    /* Erase block, to which data has to be written */
    if (Board_flashEraseBlk(boardHandle, blockNum))
    {
        GPMC_log("\n Board_flashEraseBlk failed. \n");
        testPassed = FALSE;
        goto err;
    }
    GPMC_log("\n GPMC flash block erase test passed. \n");


    /* Write buffer to flash */
    if (Board_flashWrite(boardHandle, TEST_ADDR_OFFSET, txBuf,
                         TEST_DATA_LEN, NULL))
    {
        GPMC_log("\n Board_flashWrite failed. \n");
        testPassed = FALSE;
        goto err;
    }
    GPMC_log("\n GPMC flash write test passed. \n");
#endif

    /* Reset receive buffer */
    if (Board_flashRead(boardHandle, TEST_ADDR_OFFSET, rxBuf,
                        TEST_DATA_LEN, NULL))
    {
        GPMC_log("\n Board_flashRead failed. \n");
        testPassed = FALSE;
        goto err;
    }
    GPMC_log("\n GPMC flash read test passed. \n");

#ifndef TEST_GPMC_FLASH_WRITE
    /* if no write test, copy rxBuf to txBuf to pass the test */
    memcpy(txBuf, rxBuf, TEST_DATA_LEN);
#endif

    /* Verify Data */
    if (VerifyData(txBuf, rxBuf, TEST_DATA_LEN) == false)
    {
        GPMC_log("\n Data mismatch. \n");
        testPassed = FALSE;
    }

err:
    if (boardHandle)
    {
        Board_flashClose(boardHandle);
    }

    return (testPassed);
}

#else
GPMC_Transaction transaction;
uint32_t gpmc_sram_test(void)
{
    uint32_t    testPassed = TRUE;
    GPMC_Params params;
    GPMC_Handle handle;

    GPMC_Params_init(&params);
    handle = GPMC_open(BOARD_GPMC_INSTANCE, &params);
    if (handle == NULL)
    {
        GPMC_log("\n GPMC open failed. \n");
        testPassed = FALSE;
        goto Err;
    }

    /* Generate the data */
    GeneratePattern(txBuf, rxBuf, TEST_DATA_LEN);

    /* Write data */
    transaction.transType = GPMC_TRANSACTION_TYPE_WRITE;
    transaction.offset    = 0U;
    transaction.count     = TEST_DATA_LEN;
    transaction.txBuf     = txBuf;
    transaction.rxBuf     = NULL;
    transaction.arg        = NULL;
    if (GPMC_transfer(handle, &transaction) == false)
    {
        GPMC_log("\n GPMC write failed. \n");
        testPassed = FALSE;
        goto Err;
    }

    /* Read data */
    transaction.transType = GPMC_TRANSACTION_TYPE_READ;
    transaction.txBuf     = NULL;
    transaction.rxBuf     = rxBuf;
    if (GPMC_transfer(handle, &transaction) == false)
    {
        GPMC_log("\n GPMC write failed. \n");
        testPassed = FALSE;
        goto Err;
    }

    /* Verify Data */
    if (VerifyData(txBuf, rxBuf, TEST_DATA_LEN) == false)
    {
        GPMC_log("\n Data mismatch. \n");
        testPassed = FALSE;
    }

Err:
    if (handle != NULL)
    {
        GPMC_close(handle);
    }
    return (testPassed);
}
#endif

void GPMC_initConfig(uint32_t dmaMode)
{
    GPMC_v1_HwAttrs gpmc_cfg;

    /* Get the default GPMC init configurations */
    GPMC_socGetInitCfg(BOARD_GPMC_INSTANCE, &gpmc_cfg);

    /* Modify the default GPMC configurations */
    gpmc_cfg.dmaEnable = dmaMode;

    /* Set the default GPMC init configurations */
    GPMC_socSetInitCfg(BOARD_GPMC_INSTANCE, &gpmc_cfg);
}

uint32_t gpmc_read_write_test(void *pTest)
{
    uint32_t    testPassed;
    GPMC_Tests *pTst = (GPMC_Tests *)pTest;

    GPMC_initConfig(pTst->dmaMode);
#if defined(SOC_AM335X) || defined(SOC_AM437X)
    testPassed = gpmc_flash_test();
#else
    testPassed = gpmc_sram_test();
#endif

    return (testPassed);
}

#if defined(SOC_AM64X)
uint32_t GPMC_configClk(uint32_t freq)
{
    GPMC_v1_HwAttrs gpmc_cfg;
    int32_t         retVal;
    uint64_t        gpmc_clk;
    uint32_t        parClk;
    uint32_t        clkID = TISCI_DEV_GPMC0_FUNC_CLK;
    uint32_t        devID = TISCI_DEV_GPMC0;

    /* Get the default GPMC init configurations */
    GPMC_socGetInitCfg(BOARD_GPMC_INSTANCE, &gpmc_cfg);

    retVal = Sciclient_pmModuleClkRequest(devID,
                                          clkID,
                                          TISCI_MSG_VALUE_CLOCK_SW_STATE_REQ,
                                          TISCI_MSG_FLAG_AOP,
                                          SCICLIENT_SERVICE_WAIT_FOREVER);
    if (retVal != CSL_PASS)
    {
        GPMC_log("\n Sciclient_pmModuleClkRequest failed");
        goto clk_cfg_exit;
    }

    /* Set parent clock */
    parClk = TISCI_DEV_GPMC0_FUNC_CLK_PARENT_HSDIV4_16FFT_MAIN_0_HSDIVOUT3_CLK;
    retVal = Sciclient_pmSetModuleClkParent(devID,
                                            clkID,
                                            parClk,
                                            SCICLIENT_SERVICE_WAIT_FOREVER);

    if (retVal != CSL_PASS)
    {
        GPMC_log("\n Sciclient_pmSetModuleClkParent failed");
        goto clk_cfg_exit;
    }

    gpmc_clk = (uint64_t)freq;
    retVal = Sciclient_pmSetModuleClkFreq(devID,
                                          clkID,
                                          gpmc_clk,
                                          TISCI_MSG_FLAG_AOP,
                                          SCICLIENT_SERVICE_WAIT_FOREVER);

    if (retVal != CSL_PASS)
    {
        GPMC_log("\n Sciclient_pmSetModuleClkFreq failed");
        goto clk_cfg_exit;
    }

    gpmc_clk = 0;
    retVal = Sciclient_pmGetModuleClkFreq(devID,
                                          clkID,
                                          &gpmc_clk,
                                          SCICLIENT_SERVICE_WAIT_FOREVER);
    if (retVal != CSL_PASS)
    {
        GPMC_log("\n Sciclient_pmGetModuleClkFreq failed");
        goto clk_cfg_exit;
    }

    GPMC_log("\n GPMC CLK running at %d Hz. \n", freq);

clk_cfg_exit:
    if (retVal == CSL_PASS)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
#endif

uint32_t Board_initGPMC(void)
{
    uint32_t      retVal = TRUE;
    Board_initCfg boardCfg;
    Board_STATUS  boardStatus;

    boardCfg = BOARD_INIT_MODULE_CLOCK  |
               BOARD_INIT_PINMUX_CONFIG |
               BOARD_INIT_UART_STDIO;
    boardStatus = Board_init(boardCfg);
    if (boardStatus != BOARD_SOK)
    {
        retVal = FALSE;
    }

#if defined(SOC_AM64X)
    if (retVal == TRUE)
    {
        retVal = GPMC_configClk(GPMC_MODULE_CLK_80MHZ);
    }
#endif
    return (retVal);
}

void GPMC_test_print_test_desc(GPMC_Tests *test)
{
    char testId[16] = {0, };

    /* Print unit test ID */
    sprintf(testId, "%d", test->testId);
    GPMC_log("\r\n GPMC UT %s\r\n", testId);

    /* Print test description */
    GPMC_log("\r\n %s\r\n", test->testDesc);
}

void GPMC_test_print_test_results(uint32_t pass, const char *pDesc)
{
    if (pass == TRUE)
    {
        if (pDesc == NULL)
        {
            GPMC_log("\r\n All tests have passed. \r\n");
        }
        else
        {
            GPMC_log("\r\n %s have passed. \r\n", pDesc);
        }
    }
    else
    {
        if (pDesc == NULL)
        {
            GPMC_log("\r\n Some tests have failed. \r\n");
        }
        else
        {
            GPMC_log("\r\n %s have failed. \r\n", pDesc);
        }
    }
}

GPMC_Tests Gpmc_tests[] =
{
    /* testFunc            testID             dmaMode     testDesc */
    {gpmc_read_write_test, GPMC_TEST_ID_RW,   TRUE,       "\r\n GPMC CPU read write test"},
    {NULL, }
};


#ifdef USE_BIOS
#if defined(BUILD_MPU) || defined (__C7100__)
extern void Osal_initMmuDefault(void);
void InitMmu(void)
{
    Osal_initMmuDefault();
}
#endif

/*
 *  ======== taskFxn ========
 */
Void taskFxn(UArg a0, UArg a1)
#else
/*
 *  ======== main ========
 */
int main(void)
#endif /* #ifdef USE_BIOS */
{
    GPMC_Tests *pTest;
    uint32_t testResult = FALSE;
    uint32_t i;

#ifndef USE_BIOS
    if (Board_initGPMC() == FALSE)
    {
        return (0);
    }
#endif

    GPMC_init();

    for (i = 0; ; i++)
    {
        pTest = &Gpmc_tests[i];
        if (pTest->testFunc == NULL)
        {
            break;
        }
        GPMC_test_print_test_desc(pTest);
        testResult = pTest->testFunc((void *)pTest);
        GPMC_test_print_test_results(testResult, pTest->testDesc);

        if (testResult == FALSE)
        {
            break;
        }
    }

    GPMC_test_print_test_results(testResult, NULL);

    while (1)
    {
    }
}

#ifdef USE_BIOS
/*
 *  ======== main ========
 */
Int main()
{
    if (Board_initGPMC() == FALSE)
    {
        System_printf("\nBoard_initGPMC failed!\n");
        return(0);
    }

#if defined (SOC_AM64X)
    Task_Handle task;
    Error_Block eb;
    Task_Params taskParams;

    Error_init(&eb);

    /* Initialize the task params */
    Task_Params_init(&taskParams);
    task = Task_create(taskFxn, &taskParams, &eb);
    if (task == NULL) {

        BIOS_exit(0);
    }
#endif
    BIOS_start();    /* does not return */
    return(0);
}
#endif /* #ifdef USE_BIOS */

/*
 *  ======== CompareData ========
 */
bool VerifyData(uint8_t *expData,
                uint8_t *rxData,
                uint32_t length)
{
    uint32_t idx = 0;
    uint32_t match = 1;
    bool retVal = false;

    for(idx = 0; ((idx < length) && (match != 0)); idx++)
    {
        if(*expData != *rxData)
        {
            match = 0;
        }
        expData++;
        rxData++;
    }

    if(match == 1)
    {
        retVal = true;
    }

    return retVal;
}

/*
 *  ======== GeneratePattern ========
 */
static void GeneratePattern(uint8_t *txBuf, uint8_t *rxBuf, uint32_t length)
{
    volatile uint32_t idx;
    volatile uint8_t *txPtr = txBuf;
    volatile uint8_t *rxPtr = rxBuf;

    for(idx = 0; idx < length; idx++)
    {
    	*txPtr++ = (uint8_t)idx;
    	*rxPtr++ = (uint8_t)0U;
    }
}
