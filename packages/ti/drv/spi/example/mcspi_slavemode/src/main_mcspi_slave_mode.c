/**
 *  \file   main_mcspi_slave_mode.c
 *
 *  \brief  The application Demonstrate the MCSPI slave mode functionality.
 *          This application transmits data from master to slave and at the
 *          same instance data from slave will be transferred to master.
 *
 *  \details
 *          For K2x and AM3/AM4/AM5 devices, to demonstrate the example two
 *          boards are needed one board acts as master and another as slave.
 *
 *          Following is the Pin connection information:
 *          MasterSPI_SCLK----SlaveSPI_SCLK
 *          MasterSPI_D0------SlaveSPI_D1
 *          MasterSPI_D1------SlaveSPI_D0
 *          MasterSPI_CS------SlaveSPI_CS
 *
 *          To run the example:
 *          1) Connect the master and slave boards as per above pin connections.
 *          2) Two consoles. One for master and another for slave.
 *          3) Run slave application binary and then master application binary.
 *
 *          For AM65xx and J721e/J7200/J721S2 devices, to demonstrate the example two cores
 *          on the same SoC are needed, mcu1_0 uses McSPI instance 2 on the MCU
 *          domain as the master and mpu1_0 uses  McSPI instance 4 on the Main
 *          doman as slave. These two instances are internally connected in the SoC:
 *
 *          Following is the internal pin signal connection information:
 *          MasterSPI_SCLK----SlaveSPI_SCLK
 *          MasterSPI_D1------SlaveSPI_D0
 *          MasterSPI_D0------SlaveSPI_D1
 *          MasterSPI_CS------SlaveSPI_CS
 *
 *          To run the example:
 *          1) Run the MasterSlave mpu1_0 test binary (slave) on MPU1_0 core
 *          2) Run the MasterSlave mcu1_0 test binary (master) on MCU1_0 core
 *          3) Be sure to run slave application and then master application
 *
 *  \Output
 *          At slave end console:
 *              SPI initialized
 *              Slave: PASS: Txd from master SPI
 *
 *          At master end console:
 *              SPI initialized
 *              Master: PASS: Txd from slave SPI
 *              Done
 */

/*
 * Copyright (C) 2016 - 2023 Texas Instruments Incorporated - http://www.ti.com/
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

/* CSL Header files */
#ifdef _TMS320C6X
#include <ti/csl/csl_chip.h>
#endif

/* OSAL Header files */
#include <ti/osal/osal.h>

/* TI-RTOS Header files */
#include <ti/drv/spi/soc/SPI_soc.h>
#include <ti/drv/spi/src/SPI_osal.h>
#include <ti/drv/spi/SPI.h>
#include "SPI_log.h"

#if defined(iceAMIC110)
#include <ti/drv/gpio/GPIO.h>
#include <ti/drv/gpio/soc/GPIO_soc.h>
#endif

#include <ti/board/board.h>

#if defined(SOC_J721E)
#include <ti/board/src/j721e_evm/include/board_utils.h>
#elif defined(SOC_J7200)
#include <ti/board/src/j7200_evm/include/board_utils.h>
#elif defined(SOC_AM64X)
#include <ti/board/src/am64x_evm/include/board_utils.h>
#elif defined(SOC_J721S2)
#include <ti/board/src/j721s2_evm/include/board_utils.h>
#elif defined(SOC_J784S4)
#include <ti/board/src/j784s4_evm/include/board_utils.h>
#endif

#ifdef SOC_AM65XX
#include <ti/csl/soc/am65xx/src/cslr_soc_baseaddress.h>
#include <ti/csl/soc/am65xx/src/cslr_wkup_ctrl_mmr.h>
#elif defined(SOC_J721E)
#include <ti/csl/soc/j721e/src/cslr_soc_baseaddress.h>
#include <ti/csl/soc/j721e/src/cslr_wkup_ctrl_mmr.h>
#elif defined(SOC_J7200)
#include <ti/csl/soc/j7200/src/cslr_soc_baseaddress.h>
#include <ti/csl/soc/j7200/src/cslr_wkup_ctrl_mmr.h>
#elif defined(SOC_J721S2)
#include <ti/csl/soc/j721s2/src/cslr_soc_baseaddress.h>
#include <ti/csl/soc/j721s2/src/cslr_wkup_ctrl_mmr.h>
#elif defined(SOC_J784S4)
#include <ti/csl/soc/j784s4/src/cslr_soc_baseaddress.h>
#include <ti/csl/soc/j784s4/src/cslr_wkup_ctrl_mmr.h>
#endif

#ifdef SPI_DMA_ENABLE
#include <ti/osal/CacheP.h>

#if defined (SOC_AM65XX) || defined(SOC_J721E) || defined(SOC_J7200) || defined (SOC_AM64X) || defined(SOC_J721S2) || defined(SOC_J784S4)
#include <ti/drv/udma/udma.h>
#else
/* EDMA3 Header files */
#include <ti/sdo/edma3/drv/edma3_drv.h>
#include <ti/sdo/edma3/rm/edma3_rm.h>
#include <ti/sdo/edma3/rm/sample/bios6_edma3_rm_sample.h>

#if defined(evmK2G)
#include <ti/csl/soc.h>
#endif

static EDMA3_RM_Handle MCSPIApp_edmaInit(void);

#if defined(SOC_K2H) || defined(SOC_K2K) || defined(SOC_K2L) || defined(SOC_K2E) || defined(SOC_K2G) || \
    defined(SOC_C6678) || defined(SOC_C6657)
extern EDMA3_RM_InstanceInitConfig sampleInstInitConfig[][EDMA3_MAX_REGIONS];
extern EDMA3_RM_GblConfigParams sampleEdma3GblCfgParams[];
#endif
#endif
#endif

#if (defined (SOC_J721E) || defined (SOC_J7200) || defined(SOC_J721S2) || defined(SOC_J784S4))
#include <ti/drv/sciclient/sciclient.h>
#if defined (BUILD_MCU1_0)
#include <ti/drv/sciclient/sciserver_tirtos.h>
#endif
#endif

/* Define the SPI test interface */
typedef struct SPI_Tests_s
{
    bool     (*testFunc)(void *);
    int32_t  testId;
    bool     master;
    bool     pollMode;
    bool     cbMode;
    bool     dmaMode;
    bool     useTR;
    uint32_t timeout;
    char     testDesc[80];
    uint32_t param;
    uint32_t trigLvl;

} SPI_Tests;

/**********************************************************************
 ************************** Macros ************************************
 **********************************************************************/
#define SPI_TIMEOUT_VALUE 5000
/* SPI transfer message definitions */
#define SPI_MSG_LENGTH    26
#define SPI_MSG_LENGTH2   78

#define SPI_NUM_XFERS     2
uint32_t spi_test_xfer_len[SPI_NUM_XFERS] =
{
    SPI_MSG_LENGTH,
    SPI_MSG_LENGTH2
};

/* Maximum # of channels per SPI instance */
#define MCSPI_MAX_NUM_CHN       4

/* Test channel # */
#define MCSPI_TEST_CHN          0

/* SPI Test definitions */

/* Unit test IDs */
#define SPI_TEST_ID_DMA         0   /* Single-channel DMA mode test */
#define SPI_TEST_ID_INT         1   /* Single-channel interrupt mode test */
#define SPI_TEST_ID_POLL        2   /* Single-channel polling mode test */
#define SPI_TEST_ID_CB          3   /* Single-channel non-DMA callback mode test */
#define SPI_TEST_ID_DMA_CB      4   /* Single-channel DMA callback mode test */
#define SPI_TEST_ID_MC_DMA      5   /* Multi-channel DMA mode test */
#define SPI_TEST_ID_MC_INT      6   /* Multi-channel interrupt mode test */
#define SPI_TEST_ID_MC_POLL     7   /* Multie-channel polling mode test */
#define SPI_TEST_ID_MC_CB       8   /* Multi-channel non-DMA callback mode test */
#define SPI_TEST_ID_MC_DMA_CB   9   /* Multi-channel DMA callback mode test */
#define SPI_TEST_ID_TX_ONLY     10  /* Multi-channel TX only test */
#define SPI_TEST_ID_RX_ONLY     11  /* Multi-channel RX only test */
#define SPI_TEST_ID_XFER_ERR    12  /* Single-channel transfer error test */
#define SPI_TEST_ID_PHA_POL     13  /* Single-channel phase/polarity test */
#define SPI_TEST_ID_TIMEOUT     14  /* Single-channel Timeout test with interrupt enabled */
#define SPI_TEST_ID_TIMEOUT_POLL 15 /* Single-channel Timeout test with polling enabled */
#define SPI_TEST_ID_DMA_CB_CANCEL   16
#define SPI_TEST_ID_CB_CANCEL      17

/* Loopback tests */
#define SPI_TEST_ID_LOOPBACK    20
#define SPI_TEST_ID_WORD_LEN    (SPI_TEST_ID_LOOPBACK)      /* transfer data size test */
#define SPI_TEST_ID_TRIG_LVL    (SPI_TEST_ID_LOOPBACK + 1)  /* FIFO trigger level test */
#define SPI_TEST_ID_TCS         (SPI_TEST_ID_LOOPBACK + 2)  /* Multi-channel chip select time control test */
#define SPI_TEST_ID_INIT_DELAY  (SPI_TEST_ID_LOOPBACK + 3)  /* Multi-channel 1st transfer init delay test */


/* Transfer data size test parameter, in # of bits per SPI word */
#define SPI_TEST_DATA_SIZE_16   16
#define SPI_TEST_DATA_SIZE_32   32

#if defined(SOC_DRA78x) || defined(SOC_TDA3XX) || defined(SOC_TDA2XX) || defined(SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x) || defined(SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x) || defined (SOC_AM437x) || defined (SOC_AM335x) || defined (SOC_AM65XX) || defined(SOC_J721E) || defined(SOC_J7200) || defined (SOC_AM64X) || defined(SOC_J721S2) || defined(SOC_J784S4)
#define SPI_TEST_DATA_SIZE      SPI_TEST_DATA_SIZE_32
#else
#define SPI_TEST_DATA_SIZE      SPI_TEST_DATA_SIZE_16
#endif

#ifdef MCSPI_MULT_CHANNEL
/* Chip select time control test parameter */
#define SPI_TEST_TCS            MCSPI_CH0CONF_TCS0_ONECYCLEDLY

/* 1st transfer init delay test parameter */
#define SPI_TEST_INIT_DELAY     MCSPI_INITDLY_4

/* FIFO trigger level test parameter, in # of bytes */
#define SPI_TEST_TRIG_LVL       16
#endif

#if defined(SOC_AM65XX) || defined(SOC_J721E) || defined(SOC_J7200) || defined(SOC_J721S2) || defined(SOC_J784S4)

/* WKUP CTRL base address + offset to beginning of PAD CONFIG section */
#define WKUP_PINMUX_REG_BASE            (CSL_WKUP_CTRL_MMR0_CFG0_BASE + \
                                         CSL_WKUP_CTRL_MMR_CFG0_PADCONFIG0)
#define MCU_SPI0_CLK_PADCFG_OFFSET      (0x90U)
#define MCU_SPI0_D1_PADCFG_OFFSET       (0x98U)

#define PIN_MODE(mode)                  (mode)

/** \brief Active mode configurations */
/** \brief Resistor disable */
#define PIN_PULL_DISABLE                (0x1U << 16U)
/** \brief Pull direction */
#define PIN_PULL_DIRECTION              (0x1U << 17U)
/** \brief Receiver enable */
#define PIN_INPUT_ENABLE                (0x1U << 18U)
/** \brief Driver disable */
#define PIN_OUTPUT_DISABLE              (0x1U << 21U)
/** \brief Wakeup enable */
#define PIN_WAKEUP_ENABLE               (0x1U << 29U)
#endif

#if defined(SOC_AM65XX) || defined(SOC_J721E) || defined(SOC_J7200) || defined(SOC_AM64X) || defined(SOC_J721S2) || defined(SOC_J784S4)
#ifdef SPI_DMA_ENABLE
/*
 * Ring parameters
 */
/** \brief Number of ring entries - we can prime this much memcpy operations */
#define UDMA_TEST_APP_RING_ENTRIES      (1U)
/** \brief Size (in bytes) of each ring entry (Size of pointer - 64-bit) */
#define UDMA_TEST_APP_RING_ENTRY_SIZE   (sizeof(uint64_t))
/** \brief Total ring memory */
#define UDMA_TEST_APP_RING_MEM_SIZE     (UDMA_TEST_APP_RING_ENTRIES * \
                                         UDMA_TEST_APP_RING_ENTRY_SIZE)
/** \brief This ensures every channel memory is aligned */
#define UDMA_TEST_APP_RING_MEM_SIZE_ALIGN ((UDMA_TEST_APP_RING_MEM_SIZE + UDMA_CACHELINE_ALIGNMENT) & ~(UDMA_CACHELINE_ALIGNMENT - 1U))

/** \brief UDMA host mode buffer descriptor memory size. */
#define UDMA_TEST_APP_DESC_SIZE         (sizeof(CSL_UdmapCppi5HMPD))
/** \brief UDMA TR packet descriptor memory size. */
#define UDMA_TEST_APP_TRPD_SIZE         ((sizeof(CSL_UdmapTR15) * 2U) + 4U)
/** \brief This ensures every channel memory is aligned */
#define UDMA_TEST_APP_DESC_SIZE_ALIGN   ((UDMA_TEST_APP_DESC_SIZE + UDMA_CACHELINE_ALIGNMENT) & ~(UDMA_CACHELINE_ALIGNMENT - 1U))
#define UDMA_TEST_APP_TRPD_SIZE_ALIGN   ((UDMA_TEST_APP_TRPD_SIZE + UDMA_CACHELINE_ALIGNMENT) & ~(UDMA_CACHELINE_ALIGNMENT - 1U))

/*
 * UDMA driver objects
 */
struct Udma_DrvObj      gUdmaDrvObj;
struct Udma_ChObj       gUdmaTxChObj;
struct Udma_ChObj       gUdmaRxChObj;
struct Udma_EventObj    gUdmaTxCqEventObj;
struct Udma_EventObj    gUdmaRxCqEventObj;

Udma_DrvHandle          gDrvHandle = NULL;
/*
 * UDMA Memories
 */
static uint8_t gTxRingMem[UDMA_TEST_APP_RING_MEM_SIZE_ALIGN] __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));
static uint8_t gTxCompRingMem[UDMA_TEST_APP_RING_MEM_SIZE_ALIGN] __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));
static uint8_t gUdmaTxHpdMem[UDMA_TEST_APP_DESC_SIZE_ALIGN] __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));
static uint8_t gUdmaTxTrpdMem[UDMA_TEST_APP_TRPD_SIZE_ALIGN] __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));
static uint8_t gRxRingMem[UDMA_TEST_APP_RING_MEM_SIZE_ALIGN] __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));
static uint8_t gRxCompRingMem[UDMA_TEST_APP_RING_MEM_SIZE_ALIGN] __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));
static uint8_t gUdmaRxTrpdMem[UDMA_TEST_APP_TRPD_SIZE_ALIGN] __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));
static uint8_t gUdmaRxHpdMem[UDMA_TEST_APP_DESC_SIZE_ALIGN] __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));

static SPI_dmaInfo gUdmaInfo;

#endif

#if defined (RTOS_ENV)
/** \brief Application stack size */
#define APP_TSK_STACK_MAIN              (0x4000U)
/** \brief Task stack */
static uint8_t  gAppTskStackMain[APP_TSK_STACK_MAIN] __attribute__((aligned(32)));
#endif

#if defined (SPI_DMA_ENABLE)
static void App_print(const char *str)
{
    UART_printf("%s", str);
    return;
}

Udma_DrvHandle MCSPIApp_udmaInit(SPI_v1_HWAttrs *cfg, uint32_t chn, bool useTR)
{
    int32_t         retVal = UDMA_SOK;
    Udma_InitPrms   initPrms;
    uint32_t        instId;

    if (NULL == gDrvHandle)
    {
        /* UDMA driver init */
#if defined(SOC_AM64X)
        instId = UDMA_INST_ID_PKTDMA_0;
#else
        /* Use MCU NAVSS for MCU domain cores. Rest cores all uses Main NAVSS */
#if defined (BUILD_MCU1_0) || defined (BUILD_MCU1_1)
        instId = UDMA_INST_ID_MCU_0;
#else
        instId = UDMA_INST_ID_MAIN_0;
#endif
#endif
        UdmaInitPrms_init(instId, &initPrms);
        initPrms.printFxn = &App_print;
        retVal = Udma_init(&gUdmaDrvObj, &initPrms);
        if(UDMA_SOK == retVal)
        {
            gDrvHandle = &gUdmaDrvObj;
        }
    }

    if(NULL != gDrvHandle)
    {
        gDrvHandle = &gUdmaDrvObj;

        gUdmaInfo.txChHandle     = (void *)&gUdmaTxChObj;
        gUdmaInfo.rxChHandle     = (void *)&gUdmaRxChObj;
        gUdmaInfo.txRingMem      = (void *)&gTxRingMem[0];
        gUdmaInfo.cqTxRingMem    = (void *)&gTxCompRingMem[0];
        gUdmaInfo.rxRingMem      = (void *)&gRxRingMem[0];
        gUdmaInfo.cqRxRingMem    = (void *)&gRxCompRingMem[0];
        gUdmaInfo.txHpdMem       = (void *)&gUdmaTxHpdMem[0];
        gUdmaInfo.txTrpdMem       = (void *)&gUdmaTxTrpdMem[0];
        gUdmaInfo.rxTrpdMem       = (void *)&gUdmaRxTrpdMem[0];
        gUdmaInfo.rxHpdMem       = (void *)&gUdmaRxHpdMem[0];
        gUdmaInfo.txEventHandle  = (void *)&gUdmaTxCqEventObj;
        gUdmaInfo.rxEventHandle  = (void *)&gUdmaRxCqEventObj;
        gUdmaInfo.useTR          = useTR;
        cfg->chnCfg[chn].dmaInfo = &gUdmaInfo;
    }
    else
    {
        UART_printf("MCSPIApp_udmaInit:  Udma_init failed with error code: %d\n", retVal);
    }

    return (gDrvHandle);
}

int32_t MCSPI_udma_deinit(void)
{
    int32_t         retVal = UDMA_SOK;

    if (NULL != gDrvHandle)
    {
        retVal = Udma_deinit(gDrvHandle);
        if(UDMA_SOK == retVal)
        {
            gDrvHandle = NULL;
        }
    }

    return (retVal);
}
#endif
#endif /* #if defined(SOC_AM65XX) || defined(SOC_J721E) || defined(SOC_J7200) || defined(SOC_J721S2) || defined(SOC_J784S4) */

/**********************************************************************
 ************************** Global Variables **************************
 **********************************************************************/
#if (defined(_TMS320C6X) || ((__ARM_ARCH == 7) && (__ARM_ARCH_PROFILE == 'M')))
#pragma DATA_ALIGN (masterRxBuffer, 128)
unsigned char masterRxBuffer[128];
#pragma DATA_ALIGN (slaveRxBuffer, 128)
unsigned char slaveRxBuffer[128];
#else
unsigned char masterRxBuffer[128] __attribute__ ((aligned (128)));
unsigned char slaveRxBuffer[128] __attribute__ ((aligned (128)));
#endif

#define CANCEL_TX_LEN   (1024)
unsigned char cancelTxBuff[CANCEL_TX_LEN];
unsigned char cancelRxBuff[CANCEL_TX_LEN];
unsigned char masterTxBuffer[128] = "PASS: Txd from master SPI PASS: Txd from master SPI PASS: Txd from master SPI ";
unsigned char slaveTxBuffer[128] =  "PASS: Txd from slave SPI  PASS: Txd from slave SPI  PASS: Txd from slave SPI  ";

#if defined(iceAMIC110)
#define GPIO_BUS_SWITCH_ENABLE_OFFSET     (0)
#define GPIO_PIN_VAL_LOW     (0U)
#define GPIO_PIN_VAL_HIGH    (1U)

#define GPIO_BUS_SWITCH_ENABLE_PIN_NUM    (0x15)
#define GPIO_BUS_SWITCH_ENABLE_PORT_NUM   (0x2)

/* GPIO Driver board specific pin configuration structure */
GPIO_PinConfig gpioPinConfigs[] = {
    /* Boot switch enable pin to control the buffer for routing McSPI
     * lines to Launchpad header on iceAMIC110 board */
    GPIO_DEVICE_CONFIG((GPIO_BUS_SWITCH_ENABLE_PORT_NUM + 1), GPIO_BUS_SWITCH_ENABLE_PIN_NUM) |
    GPIO_CFG_IN_INT_NONE | GPIO_CFG_OUTPUT,
};

/* GPIO Driver call back functions */
GPIO_CallbackFxn gpioCallbackFunctions[] = {
    NULL
};

/* GPIO Driver configuration structure */
GPIO_v1_Config GPIO_v1_config = {
    gpioPinConfigs,
    gpioCallbackFunctions,
    sizeof(gpioPinConfigs) / sizeof(GPIO_PinConfig),
    sizeof(gpioCallbackFunctions) / sizeof(GPIO_CallbackFxn),
    0x1U,
    };
#endif  /* #if defined(iceAMIC110) */

/* Transaction data */
SPI_Transaction   transaction;

/* Callback mode variables */
SemaphoreP_Params cbSemParams;
SemaphoreP_Handle cbSem[MCSPI_MAX_NUM_CHN] = {NULL, NULL, NULL, NULL};

static bool loopBackTest = BFALSE;

#ifdef SPI_DMA_ENABLE
#if !(defined (SOC_AM65XX) || defined(SOC_J721E) || defined(SOC_J7200) || defined (SOC_AM64X) || defined(SOC_J721S2) || defined(SOC_J784S4))
EDMA3_RM_Handle gEdmaHandle = NULL;

/**
 * \brief      Function to initialize the edma driver and get the handle to the
 *             edma driver;
 */
static EDMA3_RM_Handle MCSPIApp_edmaInit(void)
{
    EDMA3_DRV_Result edmaResult = EDMA3_DRV_E_INVALID_PARAM;
    uint32_t         edma3Id;

    if (NULL != gEdmaHandle)
    {
        return (gEdmaHandle);
    }

#if defined(SOC_K2H) || defined(SOC_K2K) || defined(SOC_K2L) || defined(SOC_K2E) || defined(SOC_K2G) || \
    defined(SOC_C6678) || defined(SOC_C6657)
    uint32_t edmaEvent[2], i, chnMapping, chnMappingIdx;

    /* For Keystone devices, edm3Id is SPI instance and SoC specific */
    SPI_getEdmaInfo(BOARD_MCSPI_MASTER_INSTANCE - 1, &edma3Id, edmaEvent);

    /* Set the RX/TX ownDmaChannels and dmaChannelHwEvtMap */
    for (i = 0; i < 2; i++)
    {
        chnMapping = edmaEvent[i];
        if (chnMapping < 32)
            chnMappingIdx = 0;
        else
        {
            chnMapping -= 32;
            chnMappingIdx = 1;
        }
        sampleInstInitConfig[edma3Id][0].ownDmaChannels[chnMappingIdx] |= (1 << chnMapping);
        sampleInstInitConfig[edma3Id][0].ownTccs[chnMappingIdx] |= (1 << chnMapping);
        sampleInstInitConfig[edma3Id][0].ownPaRAMSets[chnMappingIdx] |= (1 << chnMapping);
        sampleEdma3GblCfgParams[edma3Id].dmaChannelHwEvtMap[chnMappingIdx] |= (1 << chnMapping);
    }
#endif

#if defined(SOC_AM574x) || defined(SOC_AM572x)|| defined(SOC_AM571x) || defined (SOC_DRA72x)  || defined (SOC_DRA75x) || defined (SOC_DRA78x) || defined (SOC_AM335x) || defined (SOC_AM437x)
    edma3Id = 0;
#endif
    gEdmaHandle = (EDMA3_RM_Handle)edma3init(edma3Id, &edmaResult);

#if defined (RTOS_ENV)
    if (EDMA3_DRV_SOK != edmaResult)
    {
        /* Report EDMA Error */
        printf("\nEDMA driver initialization FAIL\n");
    }
    else
    {
        printf("\nEDMA driver initialization PASS.\n");
    }
#endif
    return(gEdmaHandle);
}
#endif
#endif

/* Callback mode functions */
void SPI_callback(SPI_Handle handle, SPI_Transaction *transaction)
{
    SPI_osalPostLock(cbSem[0]);
}

#ifdef MCSPI_MULT_CHANNEL
void MCSPI_callback0(MCSPI_Handle handle, SPI_Transaction *transaction)
{
    SPI_osalPostLock(cbSem[0]);
}

void MCSPI_callback1(MCSPI_Handle handle, SPI_Transaction *transaction)
{
    SPI_osalPostLock(cbSem[1]);
}

void MCSPI_callback2(MCSPI_Handle handle, SPI_Transaction *transaction)
{
    SPI_osalPostLock(cbSem[2]);
}

void MCSPI_callback3(MCSPI_Handle handle, SPI_Transaction *transaction)
{
    SPI_osalPostLock(cbSem[3]);
}
#endif

#ifdef MCSPI_MULT_CHANNEL
/*
 *  ======== SPI init config ========
 */
static void SPI_initConfigDefault(SPI_HWAttrs *cfg, uint32_t chn)
{
    cfg->chNum                        = chn;
    cfg->chnCfg[chn].tcs              = MCSPI_CS_TCS_0PNT5_CLK;
#if defined (SOC_AM65XX) || defined(SOC_J721E) || defined(SOC_J7200) || defined(SOC_AM64X) || defined(SOC_J721S2) || defined(SOC_J784S4)
    /* SPIDAT[1] for TX and SPIDAT[0] for RX */
    cfg->chnCfg[chn].dataLineCommMode = MCSPI_DATA_LINE_COMM_MODE_1;
#else
    /* SPIDAT[1] for RX and SPIDAT[0] for TX */
    cfg->chnCfg[chn].dataLineCommMode = MCSPI_DATA_LINE_COMM_MODE_6;
#endif
    cfg->chnCfg[chn].trMode           = MCSPI_TX_RX_MODE;
    cfg->initDelay                    = MCSPI_INITDLY_0;
#if defined (SOC_AM335x)
    cfg->rxTrigLvl                    = MCSPI_RX_TX_FIFO_SIZE / 2;
    cfg->txTrigLvl                    = MCSPI_RX_TX_FIFO_SIZE / 2;
#else
    cfg->rxTrigLvl                    = MCSPI_RX_TX_FIFO_SIZE;
    cfg->txTrigLvl                    = MCSPI_RX_TX_FIFO_SIZE;
#endif
}
#endif

/*
 *  ======== SPI init config ========
 */
static void SPI_deInitConfig(uint32_t domain, uint32_t instance, SPI_Tests *test)
{
    SPI_HWAttrs spi_cfg;

    /* Get the default SPI init configurations */
    SPI_socGetInitCfg(domain, instance, &spi_cfg);

    /* Release interrupt path */
    MCSPI_configSocIntrPath(instance, &spi_cfg, BFALSE);
}

/*
 *  ======== SPI init config ========
 */
static void SPI_initConfig(uint32_t domain, uint32_t instance, SPI_Tests *test, uint32_t chn, bool multiChn)
{
    SPI_HWAttrs spi_cfg;
    int32_t     testId = test->testId;
    bool        pollMode = test->pollMode;
#ifdef SPI_DMA_ENABLE
    bool        dmaMode = test->dmaMode;
#endif

#if defined (BUILD_MCU)
    /* Change interrupt number based on core */
    MCSPI_socInit();
#endif

    /* Get the default SPI init configurations */
    SPI_socGetInitCfg(domain, instance, &spi_cfg);

#ifdef MCSPI_MULT_CHANNEL
    SPI_initConfigDefault(&spi_cfg, chn);
#endif
    /*
     * Set blocking mode (dma mode or non-dma interrupt mode)
     * or callback mode
     */
    if (BTRUE == pollMode)
    {
        /* polling mode */
        spi_cfg.enableIntr = BFALSE;

        /* SPI DMA mode is not supported in polling mode */
        spi_cfg.edmaHandle = NULL;
        spi_cfg.dmaMode    = BFALSE;
    }
    else
    {
        /* interrupt enabled */
        spi_cfg.enableIntr = BTRUE;
#if defined(SOC_DRA78x) || defined(SOC_TDA3XX) || defined(SOC_TDA2XX) || defined(SOC_TDA2PX) || defined(SOC_TDA2EX) || defined (SOC_DRA75x) || \
    defined(SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x) || defined (SOC_AM437x) || defined (SOC_AM335x) || \
    defined(SOC_K2H) || defined(SOC_K2K) || defined(SOC_K2L) || defined(SOC_K2E) || defined(SOC_K2G) || \
    defined(SOC_C6678) || defined(SOC_C6657) || defined (SOC_AM65XX)  || defined(SOC_J721E) || defined(SOC_J7200) || defined (SOC_AM64X) || defined(SOC_J721S2) || defined(SOC_J784S4)
#ifdef SPI_DMA_ENABLE
        if (BTRUE == dmaMode)
        {
            /* Set the DMA related init config */
            spi_cfg.edmaHandle = (void *)MCSPIApp_udmaInit(&spi_cfg, chn, test->useTR);
            spi_cfg.dmaMode    = BTRUE;
            spi_cfg.enableIntr = BFALSE;
        }
        else
#endif
        {
            spi_cfg.edmaHandle = NULL;
            spi_cfg.dmaMode    = BFALSE;
        }
#endif
    }

#ifdef MCSPI_MULT_CHANNEL
    switch(testId)
    {
    case (SPI_TEST_ID_TX_ONLY):
        spi_cfg.chnCfg[chn].trMode = MCSPI_TX_ONLY_MODE;
#if defined (SOC_AM65XX) || defined(SOC_J721E) || defined(SOC_J7200) || defined(SOC_AM64X) || defined(SOC_J721S2) || defined(SOC_J784S4)
        /* Data line 1 TX enabled, data line 0 RX enabled TX disabled */
        spi_cfg.chnCfg[chn].dataLineCommMode = MCSPI_DATA_LINE_COMM_MODE_1;
#else
        /* Data line 0 TX enabled, data line 1 RX enabled TX disabled */
        spi_cfg.chnCfg[chn].dataLineCommMode = MCSPI_DATA_LINE_COMM_MODE_6;
#endif
        break;

    case (SPI_TEST_ID_RX_ONLY):
        spi_cfg.chnCfg[chn].trMode = MCSPI_RX_ONLY_MODE;
#if defined (SOC_AM65XX) || defined(SOC_J721E) || defined(SOC_J7200) || defined(SOC_AM64X) || defined(SOC_J721S2) || defined(SOC_J784S4)
    /* Data line 1 TX disabled, data line 0 RX enabled TX disabled */
        spi_cfg.chnCfg[chn].dataLineCommMode = MCSPI_DATA_LINE_COMM_MODE_3;
#else
        /* Data line 0 TX disabled, data line 1 RX enabled TX disabled */
        spi_cfg.chnCfg[chn].dataLineCommMode = MCSPI_DATA_LINE_COMM_MODE_7;
#endif
        break;

    case (SPI_TEST_ID_TRIG_LVL):
        spi_cfg.rxTrigLvl = test->param;
        spi_cfg.txTrigLvl = test->param;

        /* enalbe loopback mode */
        spi_cfg.chnCfg[chn].dataLineCommMode = MCSPI_DATA_LINE_COMM_MODE_4;
        break;

    case (SPI_TEST_ID_TCS):
        spi_cfg.chnCfg[chn].tcs = test->param;

        /* enalbe loopback mode */
        spi_cfg.chnCfg[chn].dataLineCommMode = MCSPI_DATA_LINE_COMM_MODE_4;
        break;

    case (SPI_TEST_ID_INIT_DELAY):
        spi_cfg.initDelay = test->param;

        /* enalbe loopback mode */
        spi_cfg.chnCfg[chn].dataLineCommMode = MCSPI_DATA_LINE_COMM_MODE_4;
        break;

    default:
        break;
    }

#ifdef SPI_DMA_ENABLE
    if (0 != spi_cfg.txTrigLvl)
    {
        test->trigLvl = spi_cfg.txTrigLvl;
    }
    else
    {
        test->trigLvl = 0;
    }

    if (spi_cfg.txTrigLvl < spi_cfg.rxTrigLvl)
    {
        test->trigLvl = spi_cfg.rxTrigLvl;
    }
#endif
#endif

    if ((SPI_TEST_ID_WORD_LEN == testId) || (SPI_TEST_ID_CB_CANCEL == testId) || (SPI_TEST_ID_DMA_CB_CANCEL == testId))
    {
#if defined(SOC_DRA78x) || defined(SOC_TDA3XX) || defined(SOC_TDA2XX) || defined(SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x) || defined (SOC_AM572x) || defined (SOC_AM571x) || defined (SOC_AM574x) || defined (SOC_AM437x) || defined (SOC_AM335x) || defined (SOC_AM65XX) || defined(SOC_J721E) || defined(SOC_J7200) || defined (SOC_AM64X) || defined(SOC_J721S2) || defined(SOC_J784S4)
        /* enable loopback mode */
        spi_cfg.chnCfg[chn].dataLineCommMode = MCSPI_DATA_LINE_COMM_MODE_4;
#else
        /* enable loopback mode */
        spi_cfg.loopback = 1;
#endif
    }

#if defined(SOC_J721E) || defined(SOC_J7200) || defined(SOC_J721S2) || defined(SOC_J784S4)
    if(spi_cfg.enableIntr)
    {
        /* Set interrupt path */
        if(CSL_PASS != MCSPI_configSocIntrPath(instance, &spi_cfg, BTRUE))
        {
            SPI_log("\n Set interrupt path failed!\n");
        }
        else
        {
            SPI_log("\n The interrupt path has been set with interrupt number %d\n", spi_cfg.intNum);
        }
    }
#endif

    /* Set the SPI init configurations */
    SPI_socSetInitCfg(domain, instance, &spi_cfg);
}

bool SPI_verify_data(unsigned char *data1, unsigned char *data2, uint32_t length)
{
	uint32_t i;
	bool     ret = BTRUE;

    for (i = 0; i < length; i++)
    {
        if (data1[i] != data2[i])
        {
            ret = BFALSE;
            break;
        }
    }

	return (ret);
}

/*
 * Utility function which converts a local GEM L2 memory address
 * to global memory address.
 */
static uintptr_t l2_global_address (uintptr_t addr)
{
#if defined(SOC_K2H) || defined(SOC_K2K) || defined(SOC_K2L) || defined(SOC_K2E) || defined(SOC_K2G) || defined(SOC_C6678) || defined(SOC_C6657)
#ifdef _TMS320C6X
    uint32_t corenum;

    /* Get the core number. */
    corenum = CSL_chipReadReg (CSL_CHIP_DNUM);

    /* Compute the global address. */
    return (addr + (0x10000000 + (corenum * 0x1000000)));
#else
    return addr;
#endif
#else
    return addr;
#endif
}

static void SPI_test_xfer_ctrl(SPI_Handle spi, uint32_t xferEnable)
{
#if defined(SOC_K2H) || defined(SOC_K2K) || defined(SOC_K2E) || defined(SOC_K2L) || defined(SOC_K2G) || defined(SOC_C6678) || defined(SOC_C6657)
    uint32_t xferActivate = xferEnable;

    SPI_control(spi, SPI_V0_CMD_XFER_ACTIVATE, (void *)&xferActivate);
#endif
}

static bool SPI_test_mst_slv_xfer(void *spi, SPI_Tests *test, uint32_t xferLen, bool multChn)
{
    bool            transferOK;
    uintptr_t        addrMasterRxBuf, addrMasterTxBuf, addrSlaveRxBuf, addrSlaveTxBuf, addrCancelTxBuff, addrCancelRxBuff;
    bool            ret = BFALSE;
    uint32_t        terminateXfer = 1;
    int32_t         testId = test->testId;
    bool            master = test->master;
    bool            cbMode = test->cbMode;
    bool            dmaMode = test->dmaMode;
    uint32_t        timeout = test->timeout;
    uint32_t        transCount, xferBytes, testLen;
    unsigned char  *srcPtr;

    if (dmaMode)
    {
        addrMasterRxBuf = l2_global_address((uintptr_t)masterRxBuffer);
        addrMasterTxBuf = l2_global_address((uintptr_t)masterTxBuffer);
        addrSlaveRxBuf = l2_global_address((uintptr_t)slaveRxBuffer);
        addrSlaveTxBuf = l2_global_address((uintptr_t)slaveTxBuffer);
        addrCancelTxBuff = l2_global_address((uintptr_t)cancelTxBuff);
        addrCancelRxBuff = l2_global_address((uintptr_t)cancelRxBuff);
    }
    else
    {
        addrMasterRxBuf = (uintptr_t)masterRxBuffer;
        addrMasterTxBuf = (uintptr_t)masterTxBuffer;
        addrSlaveRxBuf = (uintptr_t)slaveRxBuffer;
        addrSlaveTxBuf = (uintptr_t)slaveTxBuffer;
        addrCancelTxBuff = (uintptr_t)cancelTxBuff;
        addrCancelRxBuff = (uintptr_t)cancelRxBuff;
    }

    memset(cancelTxBuff, 0, sizeof(cancelTxBuff));
    memset(cancelRxBuff, 0, sizeof(cancelRxBuff));
    memset(masterRxBuffer, 0, sizeof(masterRxBuffer));
    memset(slaveRxBuffer, 0, sizeof(slaveRxBuffer));
#ifdef SPI_DMA_ENABLE
    if ((BTRUE == master) && (BTRUE == dmaMode))
    {
        CacheP_wbInv((void *)addrMasterTxBuf, (int32_t)sizeof(masterTxBuffer));
        CacheP_wbInv((void *)addrMasterRxBuf, (int32_t)sizeof(masterRxBuffer));
        CacheP_wbInv((void *)addrCancelTxBuff, (int32_t)sizeof(cancelTxBuff));
        CacheP_wbInv((void *)addrCancelRxBuff, (int32_t)sizeof(cancelRxBuff));
    }
    if ((BFALSE == master) && (BTRUE == dmaMode))
    {
        CacheP_wbInv((void *)addrSlaveTxBuf, (int32_t)sizeof(slaveTxBuffer));
        CacheP_wbInv((void *)addrSlaveRxBuf, (int32_t)sizeof(slaveRxBuffer));
    }
#endif

    testLen = xferLen;
#if defined(SOC_AM574x) || defined(SOC_AM572x)|| defined(SOC_AM571x) || defined (SOC_DRA72x)  || defined (SOC_DRA75x) || defined (SOC_DRA78x) || defined (SOC_AM335x) || defined (SOC_AM437x) || defined (SOC_AM65XX)  || defined(SOC_J721E) || defined(SOC_J7200) || defined (SOC_AM64X) || defined(SOC_J721S2) || defined(SOC_J784S4)
#ifdef SPI_DMA_ENABLE
    if (BTRUE == dmaMode)
    {
        if (testLen > test->trigLvl)
        {
            /* always transfer data bytes of multiple trigger level */
            testLen = (xferLen / test->trigLvl) * test->trigLvl;
        }
        else
        {
            /* transfer data bytes of 1 trigger level */
            testLen = test->trigLvl;
        }
    }
#endif
#endif

    if (SPI_TEST_ID_WORD_LEN == testId)
    {
        /*
         * Word length can be 8/16/32 bits,
         * calculate the SPI word count
         */
        transCount = testLen / (test->param / 8);
        xferBytes = transCount * (test->param / 8);
    }
    else
    {
        /* Default word length is 8-bit */
        transCount = testLen;
        xferBytes = testLen;
    }

    /* Initialize slave SPI transaction structure */
    transaction.count = transCount;
    transaction.arg = (void *)&terminateXfer;
    if (BTRUE == master)
    {
        if ((SPI_TEST_ID_CB_CANCEL == testId) || (SPI_TEST_ID_DMA_CB_CANCEL == testId))
        {
            if (BTRUE == dmaMode)
            {
                transaction.txDmaBuf = (uint64_t)addrCancelTxBuff;
                transaction.rxDmaBuf = (uint64_t)addrCancelRxBuff;
            }
            else
            {
                transaction.txBuf = (void *)addrCancelTxBuff;
                transaction.rxBuf = (void *)addrCancelRxBuff;
            }
        }
        else
        {
            if (BTRUE == dmaMode)
            {
                transaction.txDmaBuf = (uint64_t)addrMasterTxBuf;
                transaction.rxDmaBuf = (uint64_t)addrMasterRxBuf;
            }
            else
            {
                transaction.txBuf = (void *)addrMasterTxBuf;
                transaction.rxBuf = (void *)addrMasterRxBuf;
            }
        }
    }
    else
    {
        if (BTRUE == dmaMode)
        {
            transaction.txDmaBuf = (uint64_t)addrSlaveTxBuf;
            transaction.rxDmaBuf = (uint64_t)addrSlaveRxBuf;
        }
        else
        {
            transaction.txBuf = (void *)addrSlaveTxBuf;
            transaction.rxBuf = (void *)addrSlaveRxBuf;
        }
    }

    /* Initiate SPI transfer */
    SPI_test_xfer_ctrl(spi, 1);
#ifdef MCSPI_MULT_CHANNEL
    if (BTRUE == multChn)
    {
        transferOK = MCSPI_transfer((MCSPI_Handle)spi, &transaction);
    }
    else
#endif
    {
        transferOK = SPI_transfer((SPI_Handle)spi, &transaction);
        if ((SPI_TEST_ID_CB_CANCEL == testId) || (SPI_TEST_ID_DMA_CB_CANCEL == testId))
        {
            SPI_transferCancel(spi);
        }
    }

    if(transferOK)
    {
        if (cbMode)
        {
            if (SPI_osalPendLock(cbSem[0], timeout) != SemaphoreP_OK)
            {
                goto Err;
            }
        }
        SPI_test_xfer_ctrl(spi, 0);

       if ((master == BTRUE) && (dmaMode == BTRUE))
       {
           CacheP_Inv((void *)addrMasterRxBuf, (int32_t)sizeof(masterRxBuffer));
           CacheP_Inv((void *)addrCancelRxBuff, (int32_t)sizeof(cancelRxBuff));
       }
       if ((master == BFALSE) && (dmaMode == BTRUE))
       {
           CacheP_Inv((void *)addrSlaveRxBuf, (int32_t)sizeof(slaveRxBuffer));
       }

        /* Get the actual transfer bytes */
        if (SPI_TEST_ID_WORD_LEN == testId)
        {
            xferBytes = transaction.count * (test->param / 8);
        }
        else
        {
            xferBytes = transaction.count;
        }

        if ((SPI_TEST_ID_CB_CANCEL == testId) || (SPI_TEST_ID_DMA_CB_CANCEL == testId))
        {

            if (SPI_TRANSFER_CANCELED == transaction.status)
            {
                SPI_log("\n SPI Transfer Canceled!\n");
            }
            else
            {
                SPI_log("\n SPI Transfer Cancel failed!\n");
                goto Err;
            }
        }
        else if (SPI_TEST_ID_TX_ONLY != testId)
        {
            if (BTRUE == master)
            {
                if (SPI_TEST_ID_LOOPBACK <= testId)
                {
                    srcPtr = masterTxBuffer;
                }
                else
                {
                    srcPtr = slaveTxBuffer;
                }

                /* master mode, verify master recieved data match with slave sent data */
                if (BFALSE == SPI_verify_data(masterRxBuffer, srcPtr, xferBytes))
                {
                    goto Err;
                }

                /* Print contents of master receive buffer */
                SPI_log("Master: %s\n", masterRxBuffer);
            }
            else
            {
                /* slave mode, verify slave recieved data match with master sent data */
                if (BFALSE == SPI_verify_data(slaveRxBuffer, masterTxBuffer, xferBytes))
                {
                    goto Err;
                }
                /* Print contents of slave receive buffer */
                SPI_log("Slave: %s\n", slaveRxBuffer);
            }
        }
    }
    else
    {
        if ((SPI_TEST_ID_TIMEOUT == testId) || (SPI_TEST_ID_TIMEOUT_POLL == testId))
        {
            if (SPI_TRANSFER_TIMEOUT == transaction.status)
            {
                SPI_log("SPI Slave transfer Timed out for transfer length %d\n", xferLen);
            }
            else
            {
                SPI_log("Unsuccessful slave SPI transfer");
                goto Err;
            }
        }
        else
        {
            SPI_log("Unsuccessful slave SPI transfer");
            goto Err;
        }
    }

    ret = BTRUE;

Err:
    return (ret);
}

static uint32_t SPI_test_get_instance (uint32_t testId, bool master)
{
    uint32_t instance;

    /* Soc configuration structures indexing starts from 0. If the IP
     * instances start with 1, to address proper Configuration
     * structure index, McSPI Instance should be substracted with 1
     */
    if (BTRUE == master)
    {
        instance = (uint32_t)BOARD_MCSPI_MASTER_INSTANCE - 1;
    }
    else
    {
        instance = (uint32_t)BOARD_MCSPI_SLAVE_INSTANCE - 1;
    }
#if defined (SOC_AM65XX)  || defined(SOC_J721E) || defined(SOC_J7200) || defined(SOC_J721S2) || defined(SOC_J784S4)
    /*
     * For AM65XX/J721E/J7200/J721S2 SoC, master/slave test is set up to use
     * McSPI 2 on the MCU domain for master and McSPI 4 on the
     * Main domain for slave, for loopback test it uses default
     * board McSPI instance
     */
    if (testId < SPI_TEST_ID_LOOPBACK)
    {
        if (BTRUE == master)
        {
            instance = 2U;
        }
        else
        {
            instance = 4U;
        }
        if ((SPI_TEST_ID_TIMEOUT      == testId) ||
            (SPI_TEST_ID_TIMEOUT_POLL == testId))
        {
            /*
             * Timeout test is done in slave mode,
             * on the McSPI 2 on MCU domain
             */
            instance = 2U;
        }

    }
#endif

    return (instance);
}

static uint32_t SPI_test_get_domain (uint32_t testId, bool master)
{
    uint32_t domain = 0U;

    /*
     * For AM65XX/J721E/J7200 SoC, master/slave test is set up to use
     * McSPI 2 on the MCU domain for master and McSPI 4 on the
     * Main domain for slave, for loopback test it uses default
     * board McSPI instance
     */
    if (testId < SPI_TEST_ID_LOOPBACK)
    {
        if (BTRUE == master)
        {
            domain = SPI_MCSPI_DOMAIN_MCU;
        }
        else
        {
            domain = SPI_MCSPI_DOMAIN_MAIN;
        }
        if ((SPI_TEST_ID_TIMEOUT      == testId) ||
            (SPI_TEST_ID_TIMEOUT_POLL == testId))
        {
            /*
             * Timeout test is done in slave mode,
             * on the McSPI 2 on MCU domain
             */
            domain = SPI_MCSPI_DOMAIN_MCU;
        }

    }

    return (domain);
}

static bool SPI_test_single_channel(void *arg)
{
    SPI_Handle        spi;
    SPI_Params        spiParams;
    uint32_t          instance, i, modeIndex, SPI_modeIndex, xferLen, num_xfers, domain;
    bool              ret = BFALSE;
    SPI_Tests        *test = (SPI_Tests *)arg;
    int32_t           testId = test->testId;
    bool              master = test->master;
    bool              cbMode = test->cbMode;
    uint32_t          timeout = test->timeout;
	SPI_FrameFormat   frameFormat[]=
    {
		SPI_POL0_PHA0, /*!< SPI mode Polarity 0 Phase 0 */
		SPI_POL0_PHA1, /*!< SPI mode Polarity 0 Phase 1 */
		SPI_POL1_PHA0, /*!< SPI mode Polarity 1 Phase 0 */
		SPI_POL1_PHA1,  /*!< SPI mode Polarity 1 Phase 1 */
    };


    if (BTRUE == cbMode)
    {
        /* Create call back semaphore */
        SPI_osalSemParamsInit(&cbSemParams);
        cbSemParams.mode = SemaphoreP_Mode_BINARY;
        cbSem[0] = SPI_osalCreateBlockingLock(0, &cbSemParams);
    }

	if ((SPI_TEST_ID_WORD_LEN == testId) && (BFALSE == test->dmaMode))
	{
        SPI_modeIndex = 4;
    }
    else
    {
        SPI_modeIndex = 1;
    }
	/* In case of SPI_TEST_ID_PHA_POL all SPI modes need to be tested */
    for (modeIndex = 0; modeIndex < SPI_modeIndex; modeIndex++)
    {
        ret = BFALSE;
        instance = SPI_test_get_instance(testId, master);
        domain   = SPI_test_get_domain(testId, master);
        SPI_initConfig(domain, instance, test, MCSPI_TEST_CHN, BFALSE);

        /* Initialize SPI handle */
        SPI_Params_init(&spiParams);
        if (BFALSE == master)
        {
            spiParams.mode = SPI_SLAVE;
        }
        if (BTRUE == cbMode)
        {
            spiParams.transferMode = SPI_MODE_CALLBACK;
            spiParams.transferCallbackFxn = SPI_callback;
        }
        spiParams.transferTimeout = timeout;
        if (SPI_TEST_ID_PHA_POL == testId)
        {
            spiParams.frameFormat = (SPI_FrameFormat)(test->param);
        }

        if (SPI_TEST_ID_WORD_LEN == testId)
        {
            if (BFALSE == test->dmaMode)
            {
                spiParams.frameFormat = frameFormat[modeIndex];
                SPI_log("\n%s with SPI Mode %d\n", test->testDesc, spiParams.frameFormat);
            }
            spiParams.dataSize = test->param;
        }

        spi = SPI_open(domain, instance, &spiParams);

        if (NULL == spi)
        {
            SPI_log("Error initializing SPI\n");
            goto Err;
        }
        else
        {
            SPI_log("SPI initialized\n");
        }

        if ((SPI_TEST_ID_CB_CANCEL == testId) || (SPI_TEST_ID_DMA_CB_CANCEL == testId))
        {
            num_xfers = 1;
        }
        else
        {
#if defined (SOC_AM65XX) || defined(SOC_J721E) || defined(SOC_J7200) || defined(SOC_AM64X) || defined(SOC_J721S2) || defined(SOC_J784S4)
            num_xfers = 1;
#else
            num_xfers = SPI_NUM_XFERS;
#endif
        }
        for (i = 0; i < num_xfers; i++)
        {
            if ((SPI_TEST_ID_CB_CANCEL == testId) || (SPI_TEST_ID_DMA_CB_CANCEL == testId))
            {
                xferLen = CANCEL_TX_LEN;
            }
            else
            {
                xferLen = spi_test_xfer_len[i];
            }
            if ((BTRUE == master) && (SPI_TEST_ID_LOOPBACK > testId))
            {
                /*
                 * master sleep for 1 second after each transfer
                 * to sync with slave transfer
                 */
                Osal_delay(1000);
            }
            else
            {
                /*
                 * slave sleep for half second after each transfer
                 * to sync with master transfer
                 */
                Osal_delay(500);
            }
            if (BFALSE == SPI_test_mst_slv_xfer((void *)spi, test, xferLen, BFALSE))
            {
                goto Err;
            }

            if ((SPI_TEST_ID_CB_CANCEL == testId) || (SPI_TEST_ID_DMA_CB_CANCEL == testId))
            {
                SPI_log("SPI Master Transfer Cancelled!!\n");
            }
        }

        ret = BTRUE;
        if (SPI_TEST_ID_WORD_LEN == testId) {
                if (spi)
                {
                    SPI_close(spi);
                }
            }

        SPI_deInitConfig(domain, instance, test);
	} /* End of for loop */

Err:
	if (SPI_TEST_ID_WORD_LEN != testId) {
	    if (spi)
	    {
	        SPI_close(spi);
		}
    }

    if (cbSem[0])
    {
        SPI_osalDeleteBlockingLock(cbSem[0]);
        cbSem[0] = NULL;
    }
    return (ret);
}

static bool SPI_test_xfer_error(void *arg)
{
    bool              ret;
#if defined(SOC_K2G)
    SPI_Handle        spi;
    SPI_Params        spiParams;
    bool              transferOK;
    uint32_t          domain;
    uint32_t          instance;
    SPI_Tests        *test = (SPI_Tests *)arg;
    bool              master = test->master;
    uint32_t          timeout = test->timeout;
    uint32_t          terminateXfer = 1;
    uint32_t          xferErr;

    if (BTRUE == master)
    {
        ret = BFALSE;
        domain = 0;
        instance = 2;
        SPI_initConfig(domain, instance, test, MCSPI_TEST_CHN, BFALSE);

        /* Initialize SPI handle */
        SPI_Params_init(&spiParams);
        spiParams.transferTimeout = timeout;
        spi = SPI_open(domain, instance, &spiParams);

        if (NULL == spi)
        {
            SPI_log("Error initializing SPI\n");
            goto Err;
        }
        else
        {
            SPI_log("SPI initialized\n");
        }

        /* Initialize slave SPI transaction structure */
        transaction.count = 10;
        transaction.arg = (void *)&terminateXfer;
        transaction.txBuf = (void *)masterTxBuffer;
        transaction.rxBuf = (void *)masterRxBuffer;

        /* Initiate SPI transfer */
        SPI_test_xfer_ctrl(spi, 1);

        transferOK = SPI_transfer((SPI_Handle)spi, &transaction);

        if(transferOK)
        {
            SPI_test_xfer_ctrl(spi, 0);
            SPI_control(spi, SPI_V0_CMD_GET_XFER_ERR, (void *)&xferErr);
            if (SPI_XFER_ERR_RXOR == xferErr)
            {
                SPI_log("Receive overrun error detected\n");
            }
            else if (SPI_XFER_ERR_BE == xferErr)
            {
                SPI_log("Bit error detected\n");
            }
            else
            {
                SPI_log("No error detected\n");
            }
            ret = BTRUE;
        }

        /*
         * master sleep for 1 second after each transfer
         * to sync with slave transfer
         */
#if defined (RTOS_ENV)
        Task_sleep(1000);
#else
#endif

    Err:
        if (spi)
        {
            SPI_close(spi);
        }
        SPI_deInitConfig(domain, instance, test);
    }
    else
    {
        /* slave do nothing for xfer error test */
        ret = BTRUE;
    }
#else
    ret = BTRUE;
#endif
    return (ret);
}

#ifdef MCSPI_MULT_CHANNEL
static bool SPI_test_multi_channel(void *arg)
{
    MCSPI_Handle      spi[MCSPI_MAX_NUM_CHN];
    MCSPI_Params      spiParams;
    uint32_t          instance, i, domain;
    bool              ret = BFALSE;
    uint32_t          chn, maxNumChn, testChn;
    MCSPI_CallbackFxn cbFxn[MCSPI_MAX_NUM_CHN] = {MCSPI_callback0, MCSPI_callback1, MCSPI_callback2, MCSPI_callback3};
    SPI_Tests        *test = (SPI_Tests *)arg;
    int32_t           testId = test->testId;
    bool              master = test->master;
    bool              cbMode = test->cbMode;
    uint32_t          timeout = test->timeout;

    if (BTRUE == cbMode)
    {
        /* Create call back semaphore */
        SPI_osalSemParamsInit(&cbSemParams);
        cbSemParams.mode = SemaphoreP_Mode_BINARY;
    }

    instance = SPI_test_get_instance(testId, master);
    domain   = SPI_test_get_domain(testId, master);
    testChn = MCSPI_TEST_CHN;
    SPI_initConfig(domain, instance, test, testChn, BFALSE);

    /* Initialize SPI handle */
    MCSPI_Params_init(&spiParams);
    if (BFALSE == master)
    {
        spiParams.mode = SPI_SLAVE;
    }
    if (BTRUE == cbMode)
    {
        spiParams.transferMode = SPI_MODE_CALLBACK;
    }
    spiParams.transferTimeout = timeout;

    if (testId == SPI_TEST_ID_WORD_LEN)
    {
        spiParams.dataSize = test->param;
    }

    if (BTRUE == master)
    {
        maxNumChn = MCSPI_MAX_NUM_CHN;
    }
    else
    {
        /* Only 1 channel supported in slave mode */
        maxNumChn = 1;
    }
    for (i = 0; i < maxNumChn; i++)
    {
        if (BTRUE == master)
        {
            chn = i;
        }
        else
        {
            chn = testChn;
        }

        if (BTRUE == cbMode)
        {
            cbSem[chn] = SPI_osalCreateBlockingLock(0, &cbSemParams);
            spiParams.transferCallbackFxn = cbFxn[chn];;
        }

        spi[chn] = MCSPI_open(domain, instance, chn, &spiParams);

        if (spi[chn] == NULL)
        {
            SPI_log("Error initializing SPI instance %d channel %d\n",
                    instance, chn);
            goto Err;
        }
        else
        {
            SPI_log("SPI instance %d channel %d\n",
                    instance, chn);
        }
    }

#if defined(SOC_AM65XX) || defined(SOC_J721E) || defined(SOC_J7200) || defined(SOC_AM64X) || defined(SOC_J721S2) || defined(SOC_J784S4)
    for (i = 0; i < 1; i++)
#else
    for (i = 0; i < SPI_NUM_XFERS; i++)
#endif
    {

        if ((BTRUE == master) && (testId < SPI_TEST_ID_LOOPBACK))
        {
            /*
             * master sleep for 1 second after each transfer
             * to sync with slave transfer
             */
            Osal_delay(1000);
        }
        else
        {
            /*
             * slave sleep for half second after each transfer
             * to sync with master transfer
             */
            Osal_delay(500);
        }
        if (SPI_test_mst_slv_xfer((void *)(spi[testChn]), test, spi_test_xfer_len[i], true) == false)
        {
            goto Err;
        }
    }

    ret = BTRUE;

Err:
    for (i = 0; i < maxNumChn; i++)
    {
        if (BTRUE == master)
        {
            chn = i;
        }
        else
        {
            chn = testChn;
        }

        if (spi[chn])
        {
            MCSPI_close(spi[chn]);
        }

        if (cbSem[chn])
        {
            SPI_osalDeleteBlockingLock(cbSem[chn]);
            cbSem[chn] = NULL;
        }
    }

    SPI_deInitConfig(domain, instance, test);

    return (ret);
}
#endif

void SPI_test_print_test_desc(SPI_Tests *test)
{
    char        testId[16] = {0, };

    /* Print unit test ID */
    sprintf(testId, "%d", test->testId);
	SPI_log("\r\n SPI UT %s\r\n", testId);

	/* Print test description */
	SPI_log("\r\n %s\r\n", test->testDesc);
}

SPI_Tests Spi_tests_master[] =
{
#ifndef SPI_MASTERONLY_TESTS
	    /* testFunc             testID                  master   pollMode   cbMode  dmaMode,   useTr    timeout                     testDesc */
#ifdef SPI_DMA_ENABLE
    {SPI_test_single_channel,   SPI_TEST_ID_DMA,        BTRUE,  BFALSE,   BFALSE,  BTRUE,    BTRUE,    SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in dma mode", },
#endif
    {SPI_test_single_channel,   SPI_TEST_ID_INT,        BTRUE,  BFALSE,   BFALSE,  BFALSE,   BTRUE,    SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in non-dma interrupt mode", },
    {SPI_test_single_channel,   SPI_TEST_ID_POLL,       BTRUE,  BTRUE,    BFALSE,  BFALSE,   BTRUE,    SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in polling mode", },
    {SPI_test_single_channel,   SPI_TEST_ID_CB,         BTRUE,  BFALSE,   BTRUE,   BFALSE,   BTRUE,    SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in non-dma callback mode", },
#ifdef SPI_DMA_ENABLE
    {SPI_test_single_channel,   SPI_TEST_ID_DMA_CB,     BTRUE,  BFALSE,   BTRUE,   BTRUE,    BTRUE,    SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in dma callback mode", },
#endif
    {SPI_test_xfer_error,       SPI_TEST_ID_XFER_ERR,   BTRUE,  BFALSE,   BFALSE,  BFALSE,   BTRUE,    SemaphoreP_WAIT_FOREVER, "\r\n SPI slave transfer error test in non-dma interrupt mode", },
    {SPI_test_single_channel,   SPI_TEST_ID_PHA_POL,    BTRUE,  BFALSE,   BFALSE,  BFALSE,   BTRUE,    SemaphoreP_WAIT_FOREVER, "\r\n SPI slave phase polarity test in non-dma interrupt mode", 1, },
#ifdef MCSPI_MULT_CHANNEL
#ifdef SPI_DMA_ENABLE
    {SPI_test_multi_channel,    SPI_TEST_ID_MC_DMA,     BTRUE,  BFALSE,   BFALSE,  BTRUE,    BTRUE,    SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave multi channel in dma mode", },
#endif
    {SPI_test_multi_channel,    SPI_TEST_ID_MC_INT,     BTRUE,  BFALSE,   BFALSE,  BFALSE,   BTRUE,    SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave multi channel in non-dma interrupt mode", },
    {SPI_test_multi_channel,    SPI_TEST_ID_MC_POLL,    BTRUE,  BTRUE,    BFALSE,  BFALSE,   BTRUE,    SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in polling mode", },
    {SPI_test_multi_channel,    SPI_TEST_ID_MC_CB,      BTRUE,  BFALSE,   BTRUE,   BFALSE,   BTRUE,    SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in non-dma callback mode", },
#ifdef SPI_DMA_ENABLE
    {SPI_test_multi_channel,    SPI_TEST_ID_MC_DMA_CB,  BTRUE,  BFALSE,   BTRUE,   BTRUE,    BTRUE,    SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in dma callback mode", },
#endif
    {SPI_test_multi_channel,    SPI_TEST_ID_TX_ONLY,    BTRUE,  BFALSE,   BFALSE,  BFALSE,   BTRUE,    SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave multi channel TX_ONLY test", 0, },
#endif
#ifdef SPI_DMA_ENABLE
    {SPI_test_single_channel,   SPI_TEST_ID_DMA,        BTRUE,  BFALSE,   BFALSE,  BTRUE,    BFALSE,   SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in dma mode", },
#endif
    {SPI_test_single_channel,   SPI_TEST_ID_INT,        BTRUE,  BFALSE,   BFALSE,  BFALSE,   BFALSE,   SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in non-dma interrupt mode", },
    {SPI_test_single_channel,   SPI_TEST_ID_POLL,       BTRUE,  BTRUE,    BFALSE,  BFALSE,   BFALSE,   SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in polling mode", },
    {SPI_test_single_channel,   SPI_TEST_ID_CB,         BTRUE,  BFALSE,   BTRUE,   BFALSE,   BFALSE,   SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in non-dma callback mode", },
#ifdef SPI_DMA_ENABLE
    {SPI_test_single_channel,   SPI_TEST_ID_DMA_CB,     BTRUE,  BFALSE,   BTRUE,   BTRUE,    BFALSE,   SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in dma callback mode", },
#endif
    {SPI_test_xfer_error,       SPI_TEST_ID_XFER_ERR,   BTRUE,  BFALSE,   BFALSE,  BFALSE,   BFALSE,   SemaphoreP_WAIT_FOREVER, "\r\n SPI slave transfer error test in non-dma interrupt mode", },
    {SPI_test_single_channel,   SPI_TEST_ID_PHA_POL,    BTRUE,  BFALSE,   BFALSE,  BFALSE,   BFALSE,   SemaphoreP_WAIT_FOREVER, "\r\n SPI slave phase polarity test in non-dma interrupt mode", 1, },
#ifdef MCSPI_MULT_CHANNEL
#ifdef SPI_DMA_ENABLE
    {SPI_test_multi_channel,    SPI_TEST_ID_MC_DMA,     BTRUE,  BFALSE,   BFALSE,  BTRUE,    BFALSE,   SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave multi channel in dma mode", },
#endif
    {SPI_test_multi_channel,    SPI_TEST_ID_MC_INT,     BTRUE,  BFALSE,   BFALSE,  BFALSE,   BFALSE,   SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave multi channel in non-dma interrupt mode", },
    {SPI_test_multi_channel,    SPI_TEST_ID_MC_POLL,    BTRUE,  BTRUE,    BFALSE,  BFALSE,   BFALSE,   SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in polling mode", },
    {SPI_test_multi_channel,    SPI_TEST_ID_MC_CB,      BTRUE,  BFALSE,   BTRUE,   BFALSE,   BFALSE,   SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in non-dma callback mode", },
#ifdef SPI_DMA_ENABLE
    {SPI_test_multi_channel,    SPI_TEST_ID_MC_DMA_CB,  BTRUE,  BFALSE,   BTRUE,   BTRUE,    BFALSE,   SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in dma callback mode", },
#endif
    {SPI_test_multi_channel,    SPI_TEST_ID_TX_ONLY,    BTRUE,  BFALSE,   BFALSE,  BFALSE,   BFALSE,   SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave multi channel TX_ONLY test", 0, },
#endif
#endif

#ifdef SPI_DMA_ENABLE
     {SPI_test_single_channel, SPI_TEST_ID_DMA_CB_CANCEL, BTRUE, BFALSE, BTRUE,   BTRUE,    BFALSE, SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test master transmit cancel in dma callback mode", },
#endif
     {SPI_test_single_channel, SPI_TEST_ID_CB_CANCEL,     BTRUE, BFALSE, BTRUE,   BFALSE,   BFALSE, SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test master transmit cancel in non-dma callback mode", },
    /* NOTE: Timeout Test case should be executed as the final test, as this test requires no transaction on the data lines
     * for the timeout to happen */
    {SPI_test_single_channel, SPI_TEST_ID_TIMEOUT,        BFALSE, BFALSE, BFALSE, BFALSE, BFALSE, SPI_TIMEOUT_VALUE, "\r\n SPI timeout test in interrupt mode", },
    {SPI_test_single_channel, SPI_TEST_ID_TIMEOUT_POLL,   BFALSE, BTRUE,  BFALSE, BFALSE, BFALSE, SPI_TIMEOUT_VALUE, "\r\n SPI timeout test in polling mode", },
    {NULL, },
};

SPI_Tests Spi_tests_slave[] =
{
#ifndef SPI_MASTERONLY_TESTS
	    /* testFunc             testID                  master pollMode cbMode  dmaMode, useTr    timeout                     testDesc */
#ifdef SPI_DMA_ENABLE
    {SPI_test_single_channel,   SPI_TEST_ID_DMA,        BFALSE, BFALSE,   BFALSE,  BTRUE,    BTRUE,    SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in dma mode", },
#endif
    {SPI_test_single_channel,   SPI_TEST_ID_INT,        BFALSE, BFALSE,   BFALSE,  BFALSE,   BTRUE,    SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in non-dma interrupt mode", },
    {SPI_test_single_channel,   SPI_TEST_ID_POLL,       BFALSE, BTRUE,    BFALSE,  BFALSE,   BTRUE,    SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in polling mode", },
    {SPI_test_single_channel,   SPI_TEST_ID_CB,         BFALSE, BFALSE,   BTRUE,   BFALSE,   BTRUE,    SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in non-dma callback mode", },
#ifdef SPI_DMA_ENABLE
    {SPI_test_single_channel,   SPI_TEST_ID_DMA_CB,     BFALSE, BFALSE,   BTRUE,   BTRUE,    BTRUE,    SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in dma callback mode", },
#endif
    {SPI_test_xfer_error,       SPI_TEST_ID_XFER_ERR,   BFALSE, BFALSE,   BFALSE,  BFALSE,   BTRUE,    SemaphoreP_WAIT_FOREVER, "\r\n SPI slave transfer error test in non-dma interrupt mode", },
    {SPI_test_single_channel,   SPI_TEST_ID_PHA_POL,    BFALSE, BFALSE,   BFALSE,  BFALSE,   BTRUE,    SemaphoreP_WAIT_FOREVER, "\r\n SPI slave phase polarity test in non-dma interrupt mode", 1, },
#ifdef MCSPI_MULT_CHANNEL
#ifdef SPI_DMA_ENABLE
    {SPI_test_multi_channel,    SPI_TEST_ID_MC_DMA,     BFALSE, BFALSE,   BFALSE,  BTRUE,    BTRUE,    SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave multi channel in dma mode", },
#endif
    {SPI_test_multi_channel,    SPI_TEST_ID_MC_INT,     BFALSE, BFALSE,   BFALSE,  BFALSE,   BTRUE,    SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave multi channel in non-dma interrupt mode", },
    {SPI_test_multi_channel,    SPI_TEST_ID_MC_POLL,    BFALSE, BTRUE,    BFALSE,  BFALSE,   BTRUE,    SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in polling mode", },
    {SPI_test_multi_channel,    SPI_TEST_ID_MC_CB,      BFALSE, BFALSE,   BTRUE,   BFALSE,   BTRUE,    SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in non-dma callback mode", },
#ifdef SPI_DMA_ENABLE
    {SPI_test_multi_channel,    SPI_TEST_ID_MC_DMA_CB,  BFALSE, BFALSE,   BTRUE,   BTRUE,    BTRUE,    SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in dma callback mode", },
#endif
    {SPI_test_multi_channel,    SPI_TEST_ID_RX_ONLY,    BFALSE, BFALSE,   BFALSE,  BFALSE,   BTRUE,    SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave multi channel RX_ONLY test", 0, },
#endif
#ifdef SPI_DMA_ENABLE
    {SPI_test_single_channel,   SPI_TEST_ID_DMA,        BFALSE, BFALSE,   BFALSE,  BTRUE,    BFALSE,   SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in dma mode", },
#endif
    {SPI_test_single_channel,   SPI_TEST_ID_INT,        BFALSE, BFALSE,   BFALSE,  BFALSE,   BFALSE,   SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in non-dma interrupt mode", },
    {SPI_test_single_channel,   SPI_TEST_ID_POLL,       BFALSE, BTRUE,    BFALSE,  BFALSE,   BFALSE,   SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in polling mode", },
    {SPI_test_single_channel,   SPI_TEST_ID_CB,         BFALSE, BFALSE,   BTRUE,   BFALSE,   BFALSE,   SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in non-dma callback mode", },
#ifdef SPI_DMA_ENABLE
    {SPI_test_single_channel,   SPI_TEST_ID_DMA_CB,     BFALSE, BFALSE,   BTRUE,   BTRUE,    BFALSE,   SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in dma callback mode", },
#endif
    {SPI_test_xfer_error,       SPI_TEST_ID_XFER_ERR,   BFALSE, BFALSE,   BFALSE,  BFALSE,   BFALSE,   SemaphoreP_WAIT_FOREVER, "\r\n SPI slave transfer error test in non-dma interrupt mode", },
    {SPI_test_single_channel,   SPI_TEST_ID_PHA_POL,    BFALSE, BFALSE,   BFALSE,  BFALSE,   BFALSE,   SemaphoreP_WAIT_FOREVER, "\r\n SPI slave phase polarity test in non-dma interrupt mode", 1, },
#ifdef MCSPI_MULT_CHANNEL
#ifdef SPI_DMA_ENABLE
    {SPI_test_multi_channel,    SPI_TEST_ID_MC_DMA,     BFALSE, BFALSE,   BFALSE,  BTRUE,    BFALSE,   SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave multi channel in dma mode", },
#endif
    {SPI_test_multi_channel,    SPI_TEST_ID_MC_INT,     BFALSE, BFALSE,   BFALSE,  BFALSE,   BFALSE,   SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave multi channel in non-dma interrupt mode", },
    {SPI_test_multi_channel,    SPI_TEST_ID_MC_POLL,    BFALSE, BTRUE,    BFALSE,  BFALSE,   BFALSE,   SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in polling mode", },
    {SPI_test_multi_channel,    SPI_TEST_ID_MC_CB,      BFALSE, BFALSE,   BTRUE,   BFALSE,   BFALSE,   SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in non-dma callback mode", },
#ifdef SPI_DMA_ENABLE
    {SPI_test_multi_channel,    SPI_TEST_ID_MC_DMA_CB,  BFALSE, BFALSE,   BTRUE,   BTRUE,    BFALSE,   SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave in dma callback mode", },
#endif
    {SPI_test_multi_channel,    SPI_TEST_ID_RX_ONLY,    BFALSE, BFALSE,   BFALSE,  BFALSE,   BFALSE,   SemaphoreP_WAIT_FOREVER, "\r\n SPI master slave test slave multi channel RX_ONLY test", 0, },
#endif
#endif
    {NULL, },
};
#if defined (SOC_J721E) || defined (SOC_J7200) || defined(SOC_J721S2) || defined(SOC_J784S4)
#define MCSPI_SYNC_ADDR         (0x70000000U)
#endif
/*
 *  ======== slaveTaskFxn ========
 *  The task is part of separate slave example project.
 *  To test slave mode example, slave task has to be
 *  ready for master. Slave SPI sends a message to master
 *  while receiving message from master.
 */
#if defined (RTOS_ENV)
void slaveTaskFxn (void *arg0, void *arg1)
#else
void slaveTaskFxn()
#endif
{
    uint32_t  i;
    bool      testFail = BFALSE;
    SPI_Tests *test;

    SPI_log("Starting SPI Slave test. \n");

    SPI_init();

#if defined (SOC_J721E) || defined (SOC_J7200) || defined(SOC_J721S2) || defined(SOC_J784S4)
    *((volatile uint32_t *)(MCSPI_SYNC_ADDR)) = 0x12341234U;
    CacheP_wb((void *)MCSPI_SYNC_ADDR, 4);
#endif

    for (i = 0; ; i++)
    {
        if (BTRUE == loopBackTest)
        {
            /* Slave mode test not supported for loopback test */
            break;
        }
        test = &Spi_tests_slave[i];
        if (NULL == test->testFunc)
            break;

        if (test->testId >= SPI_TEST_ID_LOOPBACK)
        {
            /* bypass the loopback test for slave task */
            break;
        }
        SPI_test_print_test_desc(test);
        if (BTRUE == test->testFunc((void *)test))
        {
            SPI_log("\r\n %s have passed\r\n", test->testDesc);
        }
        else
        {
            SPI_log("\r\n %s have failed\r\n", test->testDesc);
            testFail = BTRUE;
            break;
        }
    }

    if(BTRUE == testFail)
    {
        SPI_log("\n Some tests have failed. \n");
    }
    else
    {
        SPI_log("\n All tests have passed. \n");
    }

    SPI_log("Done\n");

    while (BTRUE)
    {
    }
}

/*
 *  ======== masterTaskFxn ========
 *  This task is part of master example project.
 *  Slave task has to ensure transaction ready.
 *  Master SPI sends a message to slave and
 *  receives message from slave.
 */
#if defined (RTOS_ENV)
void masterTaskFxn (void *arg0, void *arg1)
#else
void masterTaskFxn()
#endif
{
    uint32_t  i;
    bool      testFail = BFALSE;
    SPI_Tests *test;

#if defined (RTOS_ENV)
    SPI_log("Starting SPI Master test, in RTOS environment \n");
#else
    SPI_log("Starting SPI Master test, in no OS environment \n");
#endif

#if defined (SOC_J721E) || defined (SOC_J7200) || defined(SOC_J721S2) || defined(SOC_J784S4)
    while ( *((volatile uint32_t *)(MCSPI_SYNC_ADDR)) != 0x12341234U)
    {
#if defined (RTOS_ENV)
        TaskP_yield();
#endif
        /* wait for slave to start. */
        CacheP_Inv((void *)MCSPI_SYNC_ADDR, 4);
    }
#if defined (RTOS_ENV)
    /* Add small delay after the sync.
     * for the slave to be ready before master initiates transfer. */
    TaskP_sleepInMsecs(1000);
#endif
#endif

    SPI_init();

    for (i = 0; ; i++)
    {
        test = &Spi_tests_master[i];
        if (NULL == test->testFunc)
            break;

        if (BTRUE == loopBackTest)
        {
            /* Only loopback test supported */
            if ((SPI_TEST_ID_LOOPBACK      > test->testId)       &&
                (SPI_TEST_ID_TIMEOUT      != test->testId)       &&
                (SPI_TEST_ID_TIMEOUT_POLL != test->testId))
                continue;
        }
        SPI_test_print_test_desc(test);
        if (BTRUE == test->testFunc((void *)test))
        {
            SPI_log("\r\n %s have passed\r\n", test->testDesc);
        }
        else
        {
            SPI_log("\r\n %s have failed\r\n", test->testDesc);
            testFail = BTRUE;
            break;
        }
    }

    if(BTRUE == testFail)
    {
        SPI_log("\n Some tests have failed. \n");
    }
    else
    {
        SPI_log("\n All tests have passed. \n");
    }

    SPI_log("Done\n");

    while (BTRUE)
    {
    }
}
#if (defined (RTOS_ENV) && (defined (SOC_J721E) || defined (SOC_J7200) || defined(SOC_J721S2) || defined(SOC_J784S4)))
#if defined (BUILD_MCU1_0)
void MCSPI_setupSciServer(void)
{

    Sciserver_TirtosCfgPrms_t appPrms;
    int32_t ret = CSL_PASS;

    ret = Sciserver_tirtosInitPrms_Init(&appPrms);

    appPrms.taskPriority[SCISERVER_TASK_USER_LO] = 4;
    appPrms.taskPriority[SCISERVER_TASK_USER_HI] = 5;

    if (CSL_PASS == ret)
    {
        ret = Sciserver_tirtosInit(&appPrms);
    }

    if (CSL_PASS == ret)
    {
        printf("Starting Sciserver..... PASSED\n");
    }
    else
    {
        printf("Starting Sciserver..... FAILED\n");
    }

    return;
}
#endif

void MCSPI_initSciclient()
{
    int32_t ret = CSL_PASS;
    Sciclient_ConfigPrms_t        config;

    /* Now reinitialize it as default parameter */
    ret = Sciclient_configPrmsInit(&config);
    if (CSL_PASS != ret)
    {
        printf("Sciclient_configPrmsInit Failed\n");
    }

#if defined (BUILD_MCU1_0)
    if (CSL_PASS == ret)
    {
        ret = Sciclient_boardCfgParseHeader(
            (uint8_t *)SCISERVER_COMMON_X509_HEADER_ADDR,
            &config.inPmPrms, &config.inRmPrms);
        if (CSL_PASS != ret)
        {
            printf("Sciclient_boardCfgParseHeader Failed\n");
        }
    }
#endif

    if (CSL_PASS == ret)
    {
        ret = Sciclient_init(&config);
        if (CSL_PASS != ret)
        {
            printf("Sciclient_init Failed\n");
        }
    }
}

#endif

/*
 *  ======== main ========
 */
int main(void)
{
    /* Call board init functions */
    Board_initCfg boardCfg;
    Board_STATUS  boardStatus;
#if defined (evmK2G)
    SPI_v0_HWAttrs spi_cfg;
    uint8_t instance;
    Board_SoCInfo socInfo;
#endif

#if defined (idkAM571x)
    Board_IDInfo  id;
#endif

#if defined (RTOS_ENV)
#if defined(SOC_AM335x) || defined (SOC_AM437x) || defined (SOC_AM65XX) || defined(SOC_J721E) || defined(SOC_J7200) || defined (SOC_AM64X) || defined(SOC_J721S2) || defined(SOC_J784S4)
    TaskP_Handle task;
    TaskP_Params taskParams;

    OS_init();

    /* Initialize the task params */
    TaskP_Params_init(&taskParams);

    /* Set the task priority higher than the default priority (1) */
    taskParams.priority = 2;
    taskParams.stack        = gAppTskStackMain;
    taskParams.stacksize    = sizeof (gAppTskStackMain);

#if defined (MCSPI_SLAVE_TASK)
    task = TaskP_create(&slaveTaskFxn, &taskParams);
#elif defined (MCSPI_MASTER_TASK)
    task = TaskP_create(&masterTaskFxn, &taskParams);
#endif /* Task type */

    if (NULL == task)
    {
        printf("TaskP_create() failed!\n");
        return (0);
    }
#endif /* Soc type */
#endif /* #ifdef RTOS_ENV */

#if (defined (RTOS_ENV) && (defined (SOC_J721E) || defined (SOC_J7200) || defined(SOC_J721S2) || defined(SOC_J784S4)))
#if defined (BUILD_MCU1_0)
    MCSPI_setupSciServer();
#endif
    /* It must be called before board init */
    MCSPI_initSciclient();
#endif

#if defined(BUILD_MCU2_1)
    Board_initParams_t initParams;
    Board_getInitParams(&initParams);
    /* Slave app on MCU2_1 prints to MAIN UART 2 */
    initParams.uartInst      = 2;
    initParams.uartSocDomain = BOARD_SOC_DOMAIN_MAIN;
    Board_setInitParams(&initParams);
#endif

    boardCfg = BOARD_INIT_PINMUX_CONFIG |
               BOARD_INIT_MODULE_CLOCK  |
               BOARD_INIT_UART_STDIO;
    boardStatus = Board_init(boardCfg);
    if (BOARD_SOK != boardStatus)
    {
        return (0);
    }

#if defined(SOC_AM64X)
    loopBackTest = BTRUE;
#endif

#if defined(SOC_AM65XX) || defined(SOC_J721E) || defined(SOC_J7200) || defined(SOC_J721S2) || defined(SOC_J784S4)
#if ((__ARM_ARCH == 7) && (__ARM_ARCH_PROFILE == 'R'))
    /* Configure the MCU SPI0_D1 pinmux, since it is not set by default in board */
    HW_WR_REG32((WKUP_PINMUX_REG_BASE + MCU_SPI0_D1_PADCFG_OFFSET), PIN_MODE(0) | \
                ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION)));
    /* Configure the MCU SPI0_CLK pinmux to support loopback */
    HW_WR_REG32((WKUP_PINMUX_REG_BASE + MCU_SPI0_CLK_PADCFG_OFFSET), PIN_MODE(0) | \
                ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION)));
#endif
#endif

#if defined (idkAM571x)
    boardStatus = Board_getIDInfo(&id);
    if (BOARD_SOK != boardStatus)
    {
        return (0);
    }

    /* Check if is DRA (AM570x) SoC */
    if ((id.boardName[0] == 'D') &&
        (id.boardName[1] == 'R') &&
        (id.boardName[2] == 'A'))
    {
        loopBackTest = BTRUE;
    }
#endif

#if defined(iceAMIC110)
    /* GPIO initialization */
    GPIO_init();
    /* Set BUS_Switch_ENABLE pin to low for enabling the switch */
    GPIO_write((GPIO_BUS_SWITCH_ENABLE_OFFSET), GPIO_PIN_VAL_LOW);
#endif

#if defined (evmK2G)
    /* Read the SoC info to get the System clock value */
    Board_getSoCInfo(&socInfo);
    if(BOARD_SYS_CLK_DEFAULT != socInfo.sysClock)
    {
        /* Since this is a generic SPI test,
         * configure the input clock for all the available instances */
        for (instance = 0; instance < CSL_SPI_CNT; instance++)
        {
            SPI_socGetInitCfg(domain, instance, &spi_cfg);
            /* Update the I2C functional clock based on CPU clock - 1G or 600MHz */
            spi_cfg.inputClkFreq = socInfo.sysClock/SPI_MODULE_CLOCK_DIVIDER;
            SPI_socSetInitCfg(domain, instance, &spi_cfg);
        }
    }
#endif

#if defined (RTOS_ENV)
    /* Start BIOS */
    OS_start();
#else
#ifdef MCSPI_MASTER_TASK
    masterTaskFxn();
#else
    slaveTaskFxn();
#endif
#endif
    return (0);
}

#if defined(BUILD_MPU) || defined (BUILD_C7X)
extern void Osal_initMmuDefault(void);
void InitMmu(void)
{
    Osal_initMmuDefault();
}
#endif
