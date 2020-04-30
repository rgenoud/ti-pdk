/*
 *   @file  mibspi_test_common.c
 *
 *   @brief
 *      Unit Test common code for the MibSpi Driver
 *
 *  \par
 *  NOTE:
 *      (C) Copyright 2020 Texas Instruments, Inc.
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

/**************************************************************************
 *************************** Include Files ********************************
 **************************************************************************/

/* Standard Include Files. */
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

/* BIOS/XDC Include Files. */
#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/IHeap.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Memory.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Event.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/heaps/HeapBuf.h>
#include <ti/sysbios/heaps/HeapMem.h>
#include <ti/sysbios/knl/Event.h>
#include <ti/sysbios/family/arm/v7a/Pmu.h>
#include <ti/csl/soc.h>

#include <ti/drv/spi/MIBSPI.h>
#include <ti/drv/edma/edma.h>
#include <ti/osal/HwiP.h>

#include "mibspi_test_common.h"


/**************************************************************************
 *************************** Local Definitions *********************************
 **************************************************************************/

/* Test flag for multiple icount */
/* #define SPI_MULT_ICOUNT_SUPPORT */

/* VBUSP Frequency in MHz */
#define VBUSP_FREQ              MSS_SYS_VCLK /1000000U

/* Number of Loops of Data echo test when XWR1xxx is configured as Master */
#define SPI_TEST_LOOP           1000

#ifdef SPI_MULT_ICOUNT_SUPPORT
 /* Block size used for the test*/
#define SPI_DATA_BLOCK_SIZE     1024
#else
 /* Block size used for the test*/
#define SPI_DATA_BLOCK_SIZE     128
#endif

/* Test message definitio for SPI test as a slave with external devices */
#define MAGIC_NUMBER            0x3456

#ifdef SPI_MULT_ICOUNT_SUPPORT
#define SPI_TEST_MSGLEN         1024
#else
#define SPI_TEST_MSGLEN         128
#endif
#define SPI_TEST_SYNC_MSGLEN    16
#define SWAP_BYTES(x)           (( (x&0xff) << 8) | ((x >>8) & 0xff))

/**************************************************************************
 *************************** Local Data Structure ******************************
 **************************************************************************/

/* SPI Test message definition */
typedef struct spiTestMsg
{
    /* Test message MAGIC number */
    uint16_t magicNumber;

    /* Test message sequence number */
    uint16_t seqNo;

    /* Test message valid data length */
    uint16_t dataLen;

    /* Test message checksum */
    uint16_t checksum;

    /* Test message data payload */
    uint8_t data[SPI_TEST_MSGLEN - 8];
}spiTestMsg;

/**************************************************************************
 *************************** Global Definitions ********************************
 **************************************************************************/
 /* Global data buffers used for SPI test */
volatile uint8_t    txBuf[SPI_DATA_BLOCK_SIZE];
volatile uint8_t    rxBuf[SPI_DATA_BLOCK_SIZE];

/* Debug flag */
uint32_t            gPrintHwStats = 1;

/**************************************************************************
 *************************** SPI Test Functions *******************************
 **************************************************************************/
/**
 *  @b Description
 *  @n
 *      This function delay by running in tight loops.
 *
 *   @param[in] count             count for the delay loop
 *
 *  @retval
 *      Not Applicable.
 */
void Test_delay(uint32_t count)
{
    volatile uint32_t i;

    for(i=0; i<count; i++);
}

/**
 *  @b Description
 *  @n
 *      This function starts a PMU counter .
 *
 *   @param[in] counter             Counter id used for benchmarking
 *
 *  @retval
 *      Not Applicable.
 */
void Test_benchmarkStart(counter)
{
    /* Initialize counter to count cycles */
    Pmu_configureCounter(counter, 0x11, FALSE);

    /* Reset PMU counter */
    Pmu_resetCount(counter);

    /* Start PMU counter */
    Pmu_startCounter(counter);
}

/**
 *  @b Description
 *  @n
 *      This function stops a PMU counter and returns the current counter value.
 *
 *   @param[in] counter             Counter id used for benchmarking
 *
 *  @retval
 *      Current PMU counter value.
 */
uint32_t Test_benchmarkStop(counter)
{
    /* Stop PMU counter */
    Pmu_stopCounter(counter);

    /* Read PMU counter */
    return (Pmu_getCount(counter));
}

/**
 *  @b Description
 *  @n
 *      SPI get hardware statistics function.
 *
 *   @param[in] handle            SPI driver handle
 *   @param[in] printStats        Flag to print the stats
 *
 *   @retval    Successful        =0
 *                 Failed         <0
 */
static int32_t Test_getSpiStats(const MIBSPI_Handle handle, bool printStats)
{
    MIBSPI_Stats   stats;
    int32_t     retVal;

    retVal = MIBSPI_getStats(handle, &stats);
    if(retVal == 0)
    {
        if(printStats)
        {
            System_printf("SPI hardware stats:\n");
            System_printf("datalen Error    = %d\n", stats.dlenErr);
            System_printf("timeout          = %d\n", stats.timeout);
            System_printf("Parity Error     = %d\n", stats.parErr);
            System_printf("Desync error     = %d\n", stats.desync);
            System_printf("Tx bit error     = %d\n", stats.bitErr);
            System_printf("RX overrun       = %d\n", stats.rxOvrnErr);
        }
    }

    return retVal;
}

/**
 *  @b Description
 *  @n
 *      SPI read only function.
 *
 *   @param[in] handle            SPI driver handle
 *   @param[in] dataLen           Number of bytes need to be transferred
 *   @param[in] buffer            Pointer of the buffer
 *   @param[in] slaveIndex        Slave index for the SPI transfer
 *
 *  @retval    Successful         =0
 *                 Failed         <0
 */
static int32_t Test_spiRead(const MIBSPI_Handle handle, uint32_t dataLen, void* buffer, uint8_t slaveIndex)
{
    MIBSPI_Transaction transaction;

    /* Configure Data Transfer */
    transaction.base.count = dataLen;
    transaction.base.txBuf = NULL;
    transaction.base.rxBuf = buffer;
    transaction.slaveIndex = slaveIndex;

    /* Start Data Transfer */
    if (MIBSPI_transfer(handle, &transaction) != true)
    {
        return -1;
    }
    return 0;
}

/**
 *  @b Description
 *  @n
 *      SPI write only function.
 *
 *   @param[in] handle            SPI driver handle
 *   @param[in] dataLen           Number of bytes need to be transferred
 *   @param[in] buffer            Pointer of the buffer
 *   @param[in] slaveIndex        Slave index for the SPI transfer
 *
 *  @retval    Successful         =0
 *                 Failed         <0
 */
static int32_t Test_spiWrite(const MIBSPI_Handle handle, uint32_t dataLen, void* buffer, uint8_t slaveIndex)
{
    MIBSPI_Transaction transaction;

    /* Configure Data Transfer */
    transaction.base.count = dataLen;
    transaction.base.txBuf = buffer;
    transaction.base.rxBuf = NULL;
    transaction.slaveIndex = slaveIndex;

    /* Start Data Transfer */
    if (MIBSPI_transfer(handle, &transaction) != true)
    {
        return -1;
    }
    return 0;
}

/**
 *  @b Description
 *  @n
 *      SPI read and write function.
 *
 *   @param[in] handle            SPI driver handle
 *   @param[in] dataLen           Number of bytes need to be transferred
 *   @param[in] inBuffer          Pointer of the read buffer
 *   @param[in] outBuffer         Pointer of the write buffer
 *   @param[in] slaveIndex        Slave index for the SPI transfer
 *
 *  @retval    Successful         =0
 *                 Failed         <0
 */
static int32_t Test_spiReadWrite(const MIBSPI_Handle handle, uint32_t dataLen, void* inBuffer, void* outBuffer, uint8_t slaveIndex)
{
    MIBSPI_Transaction  transaction;

    /* Configure Data Transfer */
    transaction.base.count = dataLen;
    transaction.base.txBuf = outBuffer;
    transaction.base.rxBuf = inBuffer;
    transaction.slaveIndex = slaveIndex;

    /* Start Data Transfer */
    if (MIBSPI_transfer(handle, &transaction) != true)
    {
        return -1;
    }
    return 0;
}

/**
 *  @b Description
 *  @n
 *      This function tests SPI driver in Digital Loopback mode.
 *
 *   @param[in] handle            SPI driver handle
 *   @param[in] slaveIndex        Flag for internal/external loopback
 *   @param[in] maxElem           Maxim data element
 *   @param[in] dataSize          Data size in number of bytes
 *
 *  @retval    Successful                   =0
 *             Number of transfer failures  >0
 *             API failures                 <0
 */
static int32_t Test_spiLoopback(const MIBSPI_Handle handle, uint8_t slaveIndex, uint32_t maxElem, uint8_t dataSize)
{
    uint8_t            loopback;
    uint32_t           loop;
    uint32_t           idx;
    uint32_t           failed = 0;
    uint32_t           len=0;

    /* Only dataSize of 1 byte or 2 bytes are supported */
    if ((dataSize != (uint8_t)1U) && (dataSize != (uint8_t)2U))
        return -1;

    /* Enable digital loopback */
    loopback = MIBSPI_LOOPBK_DIGITAL;
    if(MIBSPI_control(handle, MIBSPI_CMD_LOOPBACK_ENABLE, (void *)&loopback) < 0)
        return -1;
    for(loop=0; loop < maxElem; loop++)
    {
        len = (maxElem - loop) * dataSize;

        /* Prepare Tx/Rx Buffer */
        for(idx=0; idx<maxElem * dataSize; idx++)
        {
            txBuf[idx] = (loop * 0x10 + 0x55 + idx) & 0xFF;
        }

        /* Clear receive buffer */
        memset((void *)&rxBuf[0], 0x0, SPI_DATA_BLOCK_SIZE);

        if(Test_spiReadWrite(handle, len, (void *)rxBuf, (void *)txBuf, slaveIndex) == 0)
        {
            /* Check data integrity */
            if (memcmp((void *)txBuf, (void *)rxBuf, len) != 0)
            {
                System_printf("Error: MIBSPI_transfer is successful with incorrect data(0x%x), length = %d\n", rxBuf[0], len);
                failed++;
            }
        }
        else
        {
            System_printf("Debug: MIBSPI_transfer failed for length = %d\n", len);
            failed++;
        }
    }
    System_printf("Debug: Finished Digital loopback with various length test,  failed %d out of %d times\n", failed, loop);

    /* Disable digital loopback */
    loopback = MIBSPI_LOOPBK_NONE;
    if(MIBSPI_control(handle, MIBSPI_CMD_LOOPBACK_ENABLE, (void *)&loopback) < 0)
        return -1;

    /* Return number of failures */
    return failed;
}

/**
 *  @b Description
 *  @n
 *      This function tests SPI driver throughput in Loopback mode.
 *      Test is performed with following configurations:
 *       a. 16bits data size
 *       b. one slave
 *       c. Maximum data buffer
 *
 *   @param[in] inst             SPI instance (0=MibSPIA, 1=MibSPIB)
 *   @param[in] bitRate          SPI clock bit rate
 *
 *  @retval
 *      Not Applicable.
 */
static void Test_spiLoopBackDataThroughput(uint32_t inst, uint32_t bitRate)
{
    MIBSPI_Params       params;
    MIBSPI_Handle       handle;
    MIBSPI_Transaction  transaction;
    uint8_t          loopback;
    uint32_t         failed = 0;
    uint32_t         idx=0;
    uint32_t         loop;
    volatile uint32_t  cycles;
    float            throughput = 0;
    char             testCase[64];

    snprintf(testCase, 64, "SPI throughput test at bitRate %d Kbps", bitRate/1000);
    /**************************************************************************
     * Test: SPI Open
     **************************************************************************/
    /* Setup the default SPI Parameters */
    MIBSPI_Params_init(&params);
    params.spiParams.frameFormat = SPI_POL0_PHA0;

    /* Enable DMA and set DMA channels to be used */
    params.mibspiParams.dmaEnable = 1;
    params.mibspiParams.eccEnable = 1;

    params.spiParams.mode = SPI_MASTER;
    params.mibspiParams.u.masterParams.bitRate = bitRate;

    params.mibspiParams.u.masterParams.numSlaves = 1U;
    params.mibspiParams.u.masterParams.slaveProf[0].chipSelect = 0U;
    params.mibspiParams.u.masterParams.slaveProf[0].ramBufLen = MIBSPI_RAM_MAX_ELEM;
    params.mibspiParams.u.masterParams.slaveProf[0].dmaReqLine = 0U;

    handle = MIBSPI_open(gMibspiInst[inst], &params);
    if (handle == NULL)
    {
        System_printf("Error: Unable to open the SPI Instance\n");

        return;
    }

    /* Set SPI Digital loopback mode */
    loopback = MIBSPI_LOOPBK_DIGITAL;
    if(MIBSPI_control(handle, MIBSPI_CMD_LOOPBACK_ENABLE, (void *)&loopback) < 0)
    {
        return;
    }

    /* Prepare data in TX Buffer */
    for(idx=0; idx<SPI_DATA_BLOCK_SIZE; idx++)
    {
        txBuf[idx] =  (0x55 + idx) & 0xFF;
    }

    memset((void *)&rxBuf[0], 0x0, SPI_DATA_BLOCK_SIZE);

    // Start the counter
    Test_benchmarkStart(0);

    for(loop=0; loop < 1000; loop++)
    {
        /* Change only the first bytes in the TX buffer */
        txBuf[0] = loop;

        /* Configure Data Transfer */
        transaction.base.count = SPI_DATA_BLOCK_SIZE;
        transaction.base.txBuf = (void *)txBuf;
        transaction.base.rxBuf = (void *)rxBuf;
        transaction.slaveIndex = 0U;

        /* Start Data Transfer */
        if (MIBSPI_transfer(handle, &transaction) != true)
        {
            System_printf("Debug: MIBSPI_transfer failed for , loop=%d\n", loop);
            failed++;
        }
    }

    // Stop the counter
    cycles = Test_benchmarkStop(0);
    throughput = 8.0 * SPI_DATA_BLOCK_SIZE * loop  * VBUSP_FREQ / cycles;

    System_printf("Debug: Finished Digital loopback througput test,  failed %d out of %d times\n", failed, loop);

    /* Disable SPI Digital loopback mode */
    loopback = MIBSPI_LOOPBK_NONE;
    if (MIBSPI_control(handle, MIBSPI_CMD_LOOPBACK_ENABLE, (void *)&loopback) < 0)
    {
        return;
    }

    /* Check failures and return results */
    if(failed == 0)
    {
        snprintf(testCase, 64, "SPI throughput at bitRate %d Kbps : %f Mbps", bitRate/1000, throughput);
    }
    else
    {

    }

    /* Print hardware error stats */
    Test_getSpiStats(handle, gPrintHwStats);

    /* Close the driver: */
    MIBSPI_close(handle);
}

/**
 *  @b Description
 *  @n
 *       This function generates the test pattern for read/write test.
 *
 *   @param[in] buffer           Buffer pointer for the generated data
 *   @param[in] dataLen          Buffer len (in bytes) for pattern generation
 *
 *  @retval    None
 */
static void Test_generateTestPattern(volatile uint8_t * buffer, uint32_t dataLen)
{
    uint32_t               index;
    volatile uint8_t       *ptrBuff;

    ptrBuff =  buffer;
    for(index=0; index<dataLen; index++)
    {
        *ptrBuff = (index+0x55) & 0xFF;
        ptrBuff++;
    }
}

/**
 *  @b Description
 *  @n
 *      This function tests SPI driver in SPI master mode.
 *
 *   @param[in] handle            SPI driver handle
 *   @param[in] slaveIndex        Slave index for the SPI transfer
 *
 *  @retval
 *      Not Applicable.
 */
void Test_spiMasterWrite(const MIBSPI_Handle handle, uint8_t slaveIndex)
{
    uint16_t    loop;
    uint32_t    cycles;
    uint32_t    delayCycles;
    float       throughput;
    uint32_t    delay = 8U * SPI_TEST_MSGLEN;

    /* Initialize txBuf */
    Test_generateTestPattern(txBuf, SPI_TEST_MSGLEN);

    Test_benchmarkStart(0);
    Test_benchmarkStart(1);

    for (loop = 0; loop < SPI_TEST_LOOP; loop++)
    {
        /* Write data to slave */
        txBuf[0] = loop;
        Test_spiWrite(handle, SPI_TEST_MSGLEN, (void *)txBuf, slaveIndex);

        Pmu_startCounter(1);
        Test_delay(delay);
        Pmu_stopCounter(1);
    }

    cycles = Test_benchmarkStop(0);
    delayCycles = Pmu_getCount(1);

    throughput = 8.0 * SPI_TEST_MSGLEN * loop  * VBUSP_FREQ / (cycles - delayCycles);

    // Read and print the count
    System_printf("Master write Throughput = %.2f Mbps\n", throughput);
}

/**
 *  @b Description
 *  @n
 *      This function tests SPI driver master mode Read data from MSP  SPI slave.
 *
 *   @param[in] handle            SPI driver handle
 *   @param[in] slaveIndex        Slave index for the SPI transfer
 *
 *  @retval
 *      Not Applicable.
 */
void Test_spiMasterRead(const MIBSPI_Handle handle, uint8_t slaveIndex)
{
    uint16_t    loop;
    uint32_t    cycles;
    uint32_t    delayCycles;
    float       throughput;
    uint32_t    delay = 8U * SPI_TEST_MSGLEN;

    Test_benchmarkStart(0);
    Test_benchmarkStart(1);

    for (loop=0; loop<SPI_TEST_LOOP; loop++)
    {
        /* Read data from slave */
        Test_spiRead(handle, SPI_TEST_MSGLEN, (void *)rxBuf, slaveIndex);
        Pmu_startCounter(1);
        Test_delay(delay);
        Pmu_stopCounter(1);

        rxBuf[0] = loop;
    }
    cycles = Test_benchmarkStop(0);
    delayCycles = Pmu_getCount(1);

    throughput = 8.0 * SPI_TEST_MSGLEN * loop  * VBUSP_FREQ / (cycles -delayCycles) ;

    // Read and print the count
    System_printf("Debug: Master read Throughput = %.2f Mbps\n", throughput);

}

/**
 *  @b Description
 *  @n
 *      This function tests SPI driver in slave  mode
 *
 *   @param[in] handle        SPI driver handle
 *
 *  @retval
 *      Not Applicable.
 */
void Test_spiSlaveRead(const MIBSPI_Handle handle)
{
    uint16_t    loop;

    for (loop=0; loop<SPI_TEST_LOOP; loop++)
    {
        /* Read two byte at a time */
        {
            Test_spiRead(handle, SPI_TEST_MSGLEN, (void *)rxBuf, 0U);
        }
    }
}

/**
 *  @b Description
 *  @n
 *      This function tests SPI driver in slave mode.
 *
 *   @param[in] handle      SPI driver handle
 *
 *  @retval
 *      Not Applicable.
 */
void Test_spiSlaveWrite(const MIBSPI_Handle handle)
{
    uint16_t    loop;

    Test_generateTestPattern(txBuf, SPI_TEST_MSGLEN);

    for (loop=0; loop<SPI_TEST_LOOP; loop++)
    {
        txBuf[0]= loop;

        Test_spiWrite(handle, SPI_TEST_MSGLEN, (void *)txBuf, 0U);
    }
}



/**
 *  @b Description
 *  @n
 *      SPI API test for both instance - MibSPIA & MibSPIB.
 *
 *  @retval
 *      Not Applicable.
 */
void Test_spiAPI_twoInstance(void)
{
    MIBSPI_Params     params;
    MIBSPI_Handle     handleA = NULL;
    MIBSPI_Handle     handleB = NULL;
    uint32_t       instA = 0;
    uint32_t       instB = 1;
    char           testCase[64];

    /**************************************************************************
     * Test: Verify SPI open/close API
     **************************************************************************/
    snprintf(testCase, 64, "MIBSPI_open API test for two instances");

    /* Setup the default SPIA Parameters */
    MIBSPI_Params_init(&params);

    /* Enable DMA and set DMA channels */
    params.mibspiParams.dmaEnable = 1;
    params.mibspiParams.dmaHandle = gDmaHandle[instA];

    params.spiParams.mode = SPI_SLAVE;
    params.mibspiParams.u.slaveParams.dmaReqLine = 0;

    /* Open the SPI Instance for MibSpiA */
    handleA = MIBSPI_open(gMibspiInst[instA], &params);
    if (handleA == NULL)
    {
        System_printf("Error: Unable to open the SPI Instance\n");
        goto exit;
    }
    System_printf("Debug: SPI Instance(%d) %p has been opened successfully\n", instA, handleA);

    /* Setup the default SPIB Parameters */
    MIBSPI_Params_init(&params);

    /* Enable DMA and set DMA channels */
    params.mibspiParams.dmaEnable = 1;
    params.mibspiParams.dmaHandle = gDmaHandle[instB];

    params.spiParams.mode = SPI_SLAVE;
    params.mibspiParams.u.slaveParams.dmaReqLine = 0;

    /* Open the SPI Instance for MibSpiB */
    handleB = MIBSPI_open(gMibspiInst[instB], &params);
    if (handleB == NULL)
    {
        System_printf("Error: Unable to open the SPI Instance\n");
        goto exit;
    }
    System_printf("Debug: SPI Instance(1) %p has been opened successfully\n", handleB);

    /* Close SPIA */
    MIBSPI_close(handleA);
    System_printf("Debug: SPI Instance(0) %p has been closed successfully\n", handleA);
    handleA= NULL;

    /* Close SPIB */
    MIBSPI_close(handleB);
    System_printf("Debug: SPI Instance(1) %p has been closed successfully\n", handleB);
    handleB = NULL;

    /**************************************************************************
     * Test: Verify SPI API parameters for DMA channel configuration
     **************************************************************************/
    snprintf(testCase, 64, "MIBSPI_open API test for two instances: DMA channel validation");

    /* Setup the default SPI Parameters */
    MIBSPI_Params_init(&params);

    /* Enable DMA and set DMA channels */
    params.mibspiParams.dmaEnable = 1;
    params.mibspiParams.dmaHandle = gDmaHandle[instA];

    params.spiParams.mode = SPI_SLAVE;
    params.mibspiParams.u.slaveParams.dmaReqLine = 0U;


    /* Open the SPI Instance for MibSpiA */
    handleA = MIBSPI_open(gMibspiInst[instA], &params);
    if (handleA != NULL)
    {
        System_printf("Debug: SPI Instance(0) %p has been opened successfully\n", handleA);
    }
    else
    {
        System_printf("Error: Failed to open SPI Instance(0)\n");
        goto exit;
    }

    /* Setup the default SPIB Parameters */
    MIBSPI_Params_init(&params);

    /* Enable DMA and set DMA channels that same as SPIA, test should fail */
    params.mibspiParams.dmaEnable = 1;
    params.mibspiParams.dmaHandle = gDmaHandle[instB];

    params.spiParams.mode = SPI_SLAVE;
    params.mibspiParams.u.slaveParams.dmaReqLine = 0U;

    /* Open the SPI Instance for MibSpiA */
    handleB = MIBSPI_open(gMibspiInst[instB], &params);

    if (handleB == NULL)
    {
        System_printf("Debug: passed DMA channel number check for two SPI instances.\n");
    }
    else
    {
        System_printf("Error: Failed DMA channel number check for two SPI instances\n");
    }
exit:
    if(handleA != NULL)
    {
        MIBSPI_close(handleA);
        System_printf("Debug: SPI Instance %p has been closed successfully\n", handleA);
    }

    if(handleB != NULL)
    {
        MIBSPI_close(handleB);
        System_printf("Debug: SPI Instance %p has been closed successfully\n", handleB);
    }

    return;
}

/**
 *  @b Description
 *  @n
 *      SPI API test for one instance.
 *
 *   @param[in] inst               SPI instance: 0-SPIA, 1-SPIB
 *
 *  @retval
 *      Not Applicable.
 */
void Test_spiAPI_oneInstance(uint8_t inst)
{
    MIBSPI_Params     params;
    MIBSPI_Handle     handle;
    char           testCase[64];

    /**************************************************************************
     * Test: Verify SPI open/close API
     **************************************************************************/
    snprintf(testCase, 64, "MIBSPI_open API test (instance=%d)", inst);

    /* Setup the default SPI Parameters */
    MIBSPI_Params_init(&params);

    params.spiParams.mode = SPI_SLAVE;

    /* Enable DMA and set DMA channels */
    params.mibspiParams.dmaEnable = (uint8_t)1U;
    params.mibspiParams.dmaHandle = gDmaHandle[inst];
    params.mibspiParams.u.slaveParams.dmaReqLine = 0U;

    /* Open the SPI Instance for MibSpi */
    handle = MIBSPI_open(gMibspiInst[inst], &params);
    if (handle == NULL)
    {
        System_printf("Error: Unable to open the SPI Instance\n");
        return;
    }
    System_printf("Debug: SPI Instance %p has been opened successfully\n", handle);

    /* Close SPI */
    MIBSPI_close(handle);
    System_printf("Debug: SPI Instance %p has been closed successfully\n", handle);

    /**************************************************************************
     * Test: Verify SPI API for DMA channel configuration
     **************************************************************************/
    snprintf(testCase, 64, "MIBSPI_open API test - DMA channel validation (instance=%d)", inst);

    /* Setup the default SPI Parameters */
    MIBSPI_Params_init(&params);

    params.mibspiParams.dmaEnable = (uint8_t)1U;
    params.mibspiParams.dmaHandle = gDmaHandle[inst];

    params.spiParams.mode = SPI_SLAVE;

    /* Open the SPI Instance for MibSpiA */
    handle = MIBSPI_open(gMibspiInst[inst], &params);
    if (handle == NULL)
    {
        System_printf("Debug: Passed DMA channel number check\n");
    }
    else
    {
        System_printf("Error: Failed SPI DMA channel number check\n");

        /* Graceful shutdown */
        MIBSPI_close(handle);
        System_printf("Debug: SPI Instance %p has been closed successfully\n", handle);
    }

    /**************************************************************************
     * Test: Verify SPI parameters check::chipSelect
     **************************************************************************/
    snprintf(testCase, 64, "MIBSPI_open API test - chip select validation (instance=%d)", inst);

    /* Setup the default SPI Parameters */
    MIBSPI_Params_init(&params);

    /* Enable DMA and set DMA channels */
    params.mibspiParams.dmaEnable = (uint8_t)1U;
    params.mibspiParams.dmaHandle = gDmaHandle[inst];
    params.mibspiParams.u.slaveParams.dmaReqLine = 0U;

    params.spiParams.mode = SPI_SLAVE;

    /* Incorrect chip select */
    params.mibspiParams.u.slaveParams.chipSelect = (uint8_t)10U;

    /* Open the SPI Instance for MibSpiA */
    handle = MIBSPI_open(gMibspiInst[inst], &params);
    if (handle == NULL)
    {
    }
    else
    {
        /* Graceful shutdown */
        MIBSPI_close(handle);
        System_printf("Debug: SPI Instance %p has been closed successfully\n", handle);
    }

    /**************************************************************************
     * Test: Verify SPI open API for parameters check
     **************************************************************************/
    snprintf(testCase, 64, "MIBSPI_open API test - data size validation (instance=%d)", inst);

    /* Setup the default SPI Parameters */
    MIBSPI_Params_init(&params);

    /* Enable DMA and set DMA channels to be used */
    params.mibspiParams.dmaEnable = (uint8_t)1U;
    params.mibspiParams.dmaHandle = gDmaHandle[inst];
    params.mibspiParams.u.slaveParams.dmaReqLine  = 0U;

    params.spiParams.mode = SPI_SLAVE;

    /* Incorrect data Size */
    params.spiParams.dataSize = 7U;

    /* Open the SPI Instance */
    handle = MIBSPI_open(gMibspiInst[inst], &params);
    if (handle == NULL)
    {

    }
    else
    {

        /* Graceful shutdown */
        MIBSPI_close(handle);
        System_printf("Debug: SPI Instance %p has been closed successfully\n", handle);
    }

    /**************************************************************************
     * Test: Verify SPI parameters check::master clock
     **************************************************************************/
    snprintf(testCase, 64, "MIBSPI_open API test - bit rate validation (instance=%d)", inst);

    /* Setup the default SPI Parameters */
    MIBSPI_Params_init(&params);

    /* Enable DMA and set DMA channels */
    params.mibspiParams.dmaEnable = (uint8_t)1U;
    params.mibspiParams.dmaHandle = gDmaHandle[0];
    params.mibspiParams.u.slaveParams.dmaReqLine  =0U;

    params.spiParams.mode = SPI_MASTER;
    params.mibspiParams.u.masterParams.bitRate = 0;

    /* Open the SPI Instance for MibSpiA */
    handle = MIBSPI_open(gMibspiInst[0], &params);
    if (handle == NULL)
    {

    }
    else
    {


        /* Graceful shutdown */
        MIBSPI_close(handle);
        System_printf("Debug: SPI Instance %p has been closed successfully\n", handle);
    }

    /**************************************************************************
     * Test: Verify SPI transfer API for parameters check
     **************************************************************************/

    /* Setup the default SPI Parameters */
    MIBSPI_Params_init(&params);

    /* Enable DMA and set DMA channels to be used */
    params.mibspiParams.dmaEnable = (uint8_t)1U;
    params.mibspiParams.dmaHandle = gDmaHandle[inst];
    params.spiParams.dataSize = 16U;

    params.spiParams.mode = SPI_SLAVE;
    params.mibspiParams.u.slaveParams.dmaReqLine  = 0U;

    System_printf("Debug: Open the SPI Instance for SPI transfer parameter check test\n");

    /* Open the SPI Instance for MibSpi */
    handle = MIBSPI_open(gMibspiInst[inst], &params);
    if (handle == NULL)
    {
        System_printf("Error: Unable to open the SPI Instance\n");
    }
    else
    {
        MIBSPI_Transaction transaction;
        bool          ret;

        /* Configure Data Transfer */
        transaction.base.count = (uint16_t)1U;
        transaction.base.txBuf = (void *)txBuf;
        transaction.base.rxBuf = (void *)rxBuf;
        transaction.slaveIndex = (uint16_t)0U;

        snprintf(testCase, 64, "MIBSPI_transfer API test - data size=%d validation (instance=%d)", transaction.base.count, inst);

        /* Start Data Transfer */
        ret = MIBSPI_transfer(handle, &transaction);
        if (ret != true)
        {
            System_printf("Debug: MIBSPI_transfer with data size = %d failed with error=%d.\n", transaction.base.count, transaction.base.status );
        }
        else
        {
            System_printf("Error: MIBSPI_transfer with data size = %d should fail.\n", transaction.base.count);
        }

        /* Configure Data Transfer */
        transaction.base.count = (uint16_t)11U;
        transaction.base.txBuf = (void *)txBuf;
        transaction.base.rxBuf = (void *)rxBuf;
        transaction.slaveIndex = (uint16_t)0U;

        snprintf(testCase, 64, "MIBSPI_transfer API test - data size=%d validation (instance=%d)",transaction.base.count, inst);

        /* Start Data Transfer */
        ret = MIBSPI_transfer(handle, &transaction);
        if (ret != true)
        {
            System_printf("Debug: MIBSPI_transfer with data size = %d failed with error=%d. \n", transaction.base.count, transaction.base.status);
        }
        else
        {
            System_printf("Error: MIBSPI_transfer with data size = %d should fail.\n", transaction.base.count);
        }

        /* Configure Data Transfer */
        transaction.base.count = (uint16_t)10U;
        transaction.base.txBuf = (void *)NULL;
        transaction.base.rxBuf = (void *)NULL;
        transaction.slaveIndex = (uint16_t)0U;

        snprintf(testCase, 64, "MIBSPI_transfer API test - buffer address validation (instance=%d)", inst);

        /* Start Data Transfer */
        ret = MIBSPI_transfer(handle, &transaction);
        if (ret != true)
        {
            System_printf("Debug: MIBSPI_transfer failed with NULL pointers for both TX and RX. \n", transaction.base.status);
        }
        else
        {
            System_printf("Error: MIBSPI_transfer with NULL pointers for both TX and RX should fail.\n");
        }

        /* Graceful shutdown */
        MIBSPI_close(handle);
        System_printf("Debug: SPI Instance %p has been closed successfully\n", handle);
    }
}

/**
 *  @b Description
 *  @n
 *      SPI loopback test.
 *
 *   @param[in] inst               SPI instance: 0-SPIA, 1-SPIB
 *
 *  @retval
 *      Not Applicable.
 */
void Test_loopback_oneInstance(uint32_t inst, uint8_t slaveIndex)
{
    MIBSPI_Params     params;
    MIBSPI_Handle     handle;
    char testCase[64];

    snprintf(testCase, 64, "SPI loopback test - instance(%d), 16bits DMA mode", inst);

    /**************************************************************************
     * Test: Open the driver in master mode for loopback test
     **************************************************************************/
    /* Setup the default SPI Parameters */
    MIBSPI_Params_init(&params);
    params.spiParams.frameFormat = SPI_POL0_PHA0;

    /* Enable DMA and set DMA channels to be used */
    params.mibspiParams.dmaEnable = 1;
    params.mibspiParams.dmaHandle = gDmaHandle[inst];
    params.mibspiParams.eccEnable = 1;
    params.spiParams.mode = SPI_MASTER;
    params.mibspiParams.u.masterParams.bitRate = 1000000U;

    /* mibSPIA support only one slave */
    if(inst == 0)
    {
        params.mibspiParams.u.masterParams.numSlaves = 1;
        params.mibspiParams.u.masterParams.slaveProf[0].chipSelect = 0;
        params.mibspiParams.u.masterParams.slaveProf[0].ramBufLen = MIBSPI_RAM_MAX_ELEM;
        params.mibspiParams.u.masterParams.slaveProf[0].dmaReqLine = 0U;
    }
    else if(inst == 1)
    {
        /* The total element size of 3 slaves is MIBSPI_RAM_MAX_ELEM
         * In this example, it is distributed among 3 slaves by MIBSPI_RAM_MAX_ELEM - 6U, 4U, and 2U
         */
        memset((void *)&params.mibspiParams.u.masterParams.slaveProf[0], 0, sizeof(params.mibspiParams.u.masterParams.slaveProf));

        params.mibspiParams.u.masterParams.numSlaves = 3;
        params.mibspiParams.u.masterParams.slaveProf[0].chipSelect = 0;
        params.mibspiParams.u.masterParams.slaveProf[0].ramBufLen = MIBSPI_RAM_MAX_ELEM/2;
        params.mibspiParams.u.masterParams.slaveProf[0].dmaReqLine = 0U;
        params.mibspiParams.u.masterParams.slaveProf[1].chipSelect = 1;
        params.mibspiParams.u.masterParams.slaveProf[1].ramBufLen = MIBSPI_RAM_MAX_ELEM/4;
        params.mibspiParams.u.masterParams.slaveProf[1].dmaReqLine = 1U;
        params.mibspiParams.u.masterParams.slaveProf[2].chipSelect = 2;
        params.mibspiParams.u.masterParams.slaveProf[2].ramBufLen = MIBSPI_RAM_MAX_ELEM/4;
        params.mibspiParams.u.masterParams.slaveProf[2].dmaReqLine = 2U;
    }
    else
    {
        printf("Error: Invalid instance(=%d) of MibSPI\n", inst);
    }

    handle = MIBSPI_open(gMibspiInst[inst], &params);
    if (handle == NULL)
    {
        System_printf("Error: Unable to open the SPI Instance\n");
        return;
    }
    System_printf("Debug: SPI Instance %p has been reopened in master mode successfully\n", handle);

    /* Start Internal Loopback Test in master mode */
    if(Test_spiLoopback(handle, slaveIndex, params.mibspiParams.u.masterParams.slaveProf[slaveIndex].ramBufLen, 2) == 0)
    {

    }
    else
    {

    }

    /* Close the driver: */
    MIBSPI_close(handle);
    System_printf("Debug: SPI Instance %p has been closed successfully\n", handle);

    /**************************************************************************
     * Test: Reopen the driver in master mode for loopback test without DMA
     **************************************************************************/
    snprintf(testCase, 64, "SPI loopback test - instance(%d), 16bits non-DMA mode", inst);

    /* Change dma configuration */
    params.mibspiParams.dmaEnable = 0;

    handle = MIBSPI_open(gMibspiInst[inst], &params);
    if (handle == NULL)
    {
        System_printf("Error: Unable to open the SPI Instance\n");
        return;
    }
    System_printf("Debug: SPI Instance %p has been opened successfully\n", handle);

    /* Start Internal Loopback Test in master mode */
    if(Test_spiLoopback(handle, slaveIndex, params.mibspiParams.u.masterParams.slaveProf[slaveIndex].ramBufLen, 2) == 0U)
    {

    }
    else
    {

    }

    /* Close the driver: */
    MIBSPI_close(handle);
    System_printf("Debug: SPI Instance %p has been closed successfully\n", handle);

    /**************************************************************************
     * Test: Reopen the driver in master mode for loopback test DMA enabled 8bits
     **************************************************************************/
    snprintf(testCase, 64, "SPI loopback test - instance(%d), 8bits DMA mode", inst);

    /* Change dma configuration */
    params.mibspiParams.dmaEnable = 1;
    params.spiParams.dataSize =8;

    handle = MIBSPI_open(gMibspiInst[inst], &params);
    if (handle == NULL)
    {
        System_printf("Error: Unable to open the SPI Instance\n");
        return;
    }
    System_printf("Debug: SPI Instance %p has been opened successfully\n", handle);

    /* Start Internal Loopback Test in master mode */
    if(Test_spiLoopback(handle, slaveIndex, params.mibspiParams.u.masterParams.slaveProf[slaveIndex].ramBufLen, 1) == 0U)
    {

    }
    else
    {

    }

    /* Close the driver: */
    MIBSPI_close(handle);
    System_printf("Debug: SPI Instance %p has been closed successfully\n", handle);

    /**************************************************************************
     * Test: Reopen the driver in master mode for loopback test DMA enabled 8bits
     **************************************************************************/
    snprintf(testCase, 64, "SPI loopback test - instance(%d), 8bits non-DMA mode", inst);

    /* Change dma configuration */
    params.mibspiParams.dmaEnable = 0;
    params.spiParams.dataSize =8;

    handle = MIBSPI_open(gMibspiInst[inst], &params);
    if (handle == NULL)
    {
        System_printf("Error: Unable to open the SPI Instance\n");
        return;
    }
    System_printf("Debug: SPI Instance %p has been opened successfully\n", handle);

    /* Start Internal Loopback Test in master mode */
    if(Test_spiLoopback(handle, slaveIndex, params.mibspiParams.u.masterParams.slaveProf[slaveIndex].ramBufLen, 1) == 0U)
    {

    }
    else
    {

    }

    /* Close the driver: */
    MIBSPI_close(handle);
    System_printf("Debug: SPI Instance %p has been closed successfully\n", handle);

    /**************************************************************************
     * Test: Reopen the driver in master mode for loopback throughput test
     **************************************************************************/
    /* Start Loopback throughput Test in master mode */
    Test_spiLoopBackDataThroughput(inst, 1000000U);

    /* Start Loopback throughput Test in master mode */
    Test_spiLoopBackDataThroughput(inst, 2000000U);

    /* Start Loopback throughput Test in master mode */
    Test_spiLoopBackDataThroughput(inst, 6000000U);

    /* Start Loopback throughput Test in master mode */
    Test_spiLoopBackDataThroughput(inst, 10000000U);

    /* Start Loopback throughput Test in master mode */
    Test_spiLoopBackDataThroughput(inst, 20000000U);

    /* Start Loopback throughput Test in master mode */
    Test_spiLoopBackDataThroughput(inst, 40000000U);
}

