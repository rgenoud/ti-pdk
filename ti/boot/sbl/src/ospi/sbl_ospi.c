/**
 *  \file    sbl_ospi.c
 *
 *  \brief   This file contains functions for OSPI read/write operations for SBL
 *
 */

/*
 * Copyright (C) 2018 Texas Instruments Incorporated - http://www.ti.com/
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include "string.h"

/* SBL Header files. */
#include "sbl_soc.h"
#include "sbl_rprc_parse.h"
#include "sbl_err_trap.h"
#include "sbl_sci_client.h"
#include "sbl_soc_cfg.h"

#if SBL_USE_DMA
#include "sbl_dma.h"
#endif

/* TI-RTOS Header files */
#include <ti/drv/spi/SPI.h>
#if SBL_USE_DMA
#include <ti/drv/udma/udma.h>
#endif

#include <ti/drv/spi/src/SPI_osal.h>
#include <ti/drv/uart/UART_stdio.h>
#include <ti/drv/spi/soc/SPI_soc.h>
#include <ti/drv/spi/src/v0/OSPI_v0.h>
#include <ti/drv/sciclient/sciclient.h>
#include <ti/csl/cslr_device.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/arch/r5/csl_arm_r5.h>
#include <ti/csl/arch/r5/interrupt.h>
#include <ti/board/board_cfg.h>
#include <ti/board/src/flash/include/board_flash.h>
#include "sbl_ospi.h"

#ifdef SECURE_BOOT
#include "sbl_sec.h"
#endif

/* Macro representing the offset where the App Image has to be written/Read from
   the OSPI Flash.
*/
#define OSPI_OFFSET_SI              (0x100000U)
#define OSPI_OFFSET_SYSFW           (0x80000U)
#define OSPI_MPU_REGION_NUM         (0x6)
#define OSPI_MPU_ENABLE_REGION      (0x1)

/* Macro to config OSPI for optimized XIP performance (166MHz+PHY+Pipeline) */
#undef BUILD_XIP

/* Initialize the OSPI driver and the controller. */
static void SBL_OSPI_Initialize(void);

void SBL_DCacheClean(void *addr, uint32_t size);

void SBL_SysFwLoad(void *dst, void *src, uint32_t size);

static void *boardHandle = NULL;

static OSPI_v0_HwAttrs ospi_cfg;

#ifdef SECURE_BOOT
extern SBL_incomingBootData_S sblInBootData;

int32_t SBL_loadOSPIBootData(void);
#endif

#if SBL_USE_DMA

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
/**
 *  \brief UDMA TR packet descriptor memory.
 *  This contains the CSL_UdmapCppi5TRPD + Padding to sizeof(CSL_UdmapTR15) +
 *  one Type_15 TR (CSL_UdmapTR15) + one TR response of 4 bytes.
 *  Since CSL_UdmapCppi5TRPD is less than CSL_UdmapTR15, size is just two times
 *  CSL_UdmapTR15 for alignment.
 */
#define UDMA_TEST_APP_TRPD_SIZE         ((sizeof(CSL_UdmapTR15) * 2U) + 4U)

/*
 * UDMA driver objects
 */
struct Udma_DrvObj      gUdmaDrvObj;
struct Udma_ChObj       gUdmaChObj;
struct Udma_EventObj    gUdmaCqEventObj;

static Udma_DrvHandle          gDrvHandle = NULL;
/*
 * UDMA Memories
 */
uint8_t gTxRingMem[UDMA_TEST_APP_RING_MEM_SIZE] __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));
uint8_t gTxCompRingMem[UDMA_TEST_APP_RING_MEM_SIZE] __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));
uint8_t gTxTdCompRingMem[UDMA_TEST_APP_RING_MEM_SIZE] __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));
uint8_t gUdmaTprdMem[UDMA_TEST_APP_TRPD_SIZE] __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));
OSPI_dmaInfo gUdmaInfo;

static int32_t Ospi_udma_deinit(void);
static int32_t Ospi_udma_init(OSPI_v0_HwAttrs *cfg);

static int32_t Ospi_udma_init(OSPI_v0_HwAttrs *cfg)
{
    int32_t         retVal = UDMA_SOK;
    Udma_InitPrms   initPrms;
    uint32_t        instId;

    SBL_ADD_PROFILE_POINT;

    if (gDrvHandle == (Udma_DrvHandle)uint32_to_void_ptr(0U))
    {
        /* UDMA driver init */
#if defined (SOC_AM64X)
        /* Use Block Copy DMA for AM64x */
        instId = UDMA_INST_ID_BCDMA_0;
#else
        instId = UDMA_INST_ID_MCU_0;
#endif

        UdmaInitPrms_init(instId, &initPrms);
        retVal = Udma_init(&gUdmaDrvObj, &initPrms);
        if(UDMA_SOK == retVal)
        {
            gDrvHandle = &gUdmaDrvObj;
        }
    }

    if(gDrvHandle)
    {
        gUdmaInfo.drvHandle      = (void *)gDrvHandle;
        gUdmaInfo.chHandle       = (void *)&gUdmaChObj;
        gUdmaInfo.ringMem        = (void *)&gTxRingMem[0];
        gUdmaInfo.cqRingMem      = (void *)&gTxCompRingMem[0];
        gUdmaInfo.tdCqRingMem    = (void *)&gTxTdCompRingMem[0];
        gUdmaInfo.tprdMem        = (void *)&gUdmaTprdMem[0];
        gUdmaInfo.eventHandle    = (void *)&gUdmaCqEventObj;
        cfg->dmaInfo             = &gUdmaInfo;
    }

    SBL_ADD_PROFILE_POINT;

    return (retVal);
}

static int32_t Ospi_udma_deinit(void)
{
    int32_t         retVal = UDMA_SOK;

    SBL_ADD_PROFILE_POINT;

    if (gDrvHandle)
    {
        retVal = Udma_deinit(gDrvHandle);
        if(UDMA_SOK == retVal)
        {
            gDrvHandle = NULL;
        }
    }

    SBL_ADD_PROFILE_POINT;

    return (retVal);
}
#endif

int32_t SBL_ReadSysfwImage(void **pBuffer, uint32_t num_bytes)
{
#if !defined(SBL_BYPASS_OSPI_DRIVER) && !defined(SBL_BYPASS_OSPI_DRIVER_FOR_SYSFW_DOWNLOAD)
    Board_flashHandle h;

    SBL_ADD_PROFILE_POINT;

    /* Init SPI driver */
    SPI_init();

    /* Get default OSPI cfg */
    OSPI_socGetInitCfg(BOARD_OSPI_NOR_INSTANCE, &ospi_cfg);

#if defined(SOC_J7200) || defined(SOC_AM64X)
    ospi_cfg.funcClk = OSPI_MODULE_CLK_200M;
#else
    ospi_cfg.funcClk = OSPI_MODULE_CLK_133M;
#endif

    /* false: unstable, cpu read @ 120Mbytes per sec          */
    /*        can work with direct ROM load once it is stable */
    /* true:  stable, CPU read @60Mbytes per sec, will not    */
    /*        work with ROM, as ROM needs byte accesses       */
    ospi_cfg.dtrEnable = true;

    /* OSPI clock is set to 200MHz by RBL on J7200 & AM64X platforms.
     * PHY mode cannot be used until sysfw is loaded and OSPI clock is
     * configured to 133MHz.
     */
#if defined(SIM_BUILD) || defined(SOC_J7200) || defined(SOC_AM64X)
    ospi_cfg.phyEnable = false;
#endif

#if defined(SOC_J721E) || defined(BUILD_XIP)
    ospi_cfg.phyEnable = false;
    /* OSPI baud rate = (master reference clock) / (baud rate devisor)
     * Default baud rate devisor is 32
     * Using a smaller devisor to get higher speeds */
    ospi_cfg.baudRateDiv = 6;
#endif

    /* Set the default SPI init configurations */
    OSPI_socSetInitCfg(BOARD_OSPI_NOR_INSTANCE, &ospi_cfg);

#if defined(SOC_J7200) || defined(SOC_AM64X)
    h = Board_flashOpen(BOARD_FLASH_ID_S28HS512T,
                        BOARD_OSPI_NOR_INSTANCE, NULL);
#else
    h = Board_flashOpen(BOARD_FLASH_ID_MT35XU512ABA1G12,
                        BOARD_OSPI_NOR_INSTANCE, NULL);
#endif

    if (h)
    {
        SBL_ADD_PROFILE_POINT;

        /* Disable PHY pipeline mode */
        CSL_ospiPipelinePhyEnable((const CSL_ospi_flash_cfgRegs *)(ospi_cfg.baseAddr), FALSE);

#if defined(SOC_J7200) || defined(SOC_AM64X)
        /* Until OSPI PHY + DMA is enabled at this early stage, the
         * ROM can more efficiently load the SYSFW directly from xSPI flash */
        if(pBuffer)
        {
            /* Set up ROM to load system firmware */
            *pBuffer = (void *)(ospi_cfg.dataAddr + OSPI_OFFSET_SYSFW);
        }
#else
        /* Optimized CPU copy loop - can be removed once ROM load is working */
        SBL_SysFwLoad((void *)(*pBuffer), (void *)(ospi_cfg.dataAddr + OSPI_OFFSET_SYSFW), num_bytes);
#endif

        /* Update handle for later use*/
        boardHandle = (void *)h;
    }
    else
    {
        SBL_log(SBL_LOG_ERR, "Board_flashOpen failed!\n");
        SblErrLoop(__FILE__, __LINE__);
    }

    SBL_ADD_PROFILE_POINT;

    return CSL_PASS;
#else
   SBL_ADD_PROFILE_POINT;

     /* Get default OSPI cfg */
    OSPI_socGetInitCfg(BOARD_OSPI_NOR_INSTANCE, &ospi_cfg);

   if(pBuffer)
   {
      /* Set up ROM to load system firmware */
      *pBuffer = (void *)(ospi_cfg.dataAddr + OSPI_OFFSET_SYSFW);
   }

   SBL_ADD_PROFILE_POINT;

   return CSL_PASS;
#endif

}

#if defined(SOC_J721E) || defined(SOC_J7200) || defined(SOC_AM64X)
void OSPI_configClk(uint32_t freq)
{
    OSPI_v0_HwAttrs ospi_cfg;
	int32_t retVal;
    uint64_t ospi_rclk_freq;
    uint32_t parClk;
#if defined (SOC_AM64X)
    uint32_t clkID[] = {
                           TISCI_DEV_FSS0_OSPI_0_OSPI_RCLK_CLK,
    };
    uint32_t devID[] = {
                           TISCI_DEV_FSS0_OSPI_0,
    };
#else
    uint32_t clkID[] = {
                           TISCI_DEV_MCU_FSS0_OSPI_0_OSPI_RCLK_CLK,
                           TISCI_DEV_MCU_FSS0_OSPI_1_OSPI_RCLK_CLK
    };
    uint32_t devID[] = {
                           TISCI_DEV_MCU_FSS0_OSPI_0,
	                       TISCI_DEV_MCU_FSS0_OSPI_1
    };
#endif

    /* Get the default SPI init configurations */
    OSPI_socGetInitCfg(BOARD_OSPI_NOR_INSTANCE, &ospi_cfg);

    retVal = Sciclient_pmModuleClkRequest(devID[BOARD_OSPI_NOR_INSTANCE],
                                          clkID[BOARD_OSPI_NOR_INSTANCE],
                                          TISCI_MSG_VALUE_CLOCK_SW_STATE_REQ,
                                          TISCI_MSG_FLAG_AOP,
                                          SCICLIENT_SERVICE_WAIT_FOREVER);
    if (retVal != CSL_PASS)
    {
        SBL_log(SBL_LOG_MAX, "Sciclient_pmModuleClkRequest failed \n");
    }

    /* Max clocks */
    if (freq == OSPI_MODULE_CLK_166M)
    {
#if defined (SOC_AM64X)
        parClk = TISCI_DEV_FSS0_OSPI_0_OSPI_RCLK_CLK_PARENT_HSDIV4_16FFT_MAIN_0_HSDIVOUT1_CLK;
#else
        parClk = TISCI_DEV_MCU_FSS0_OSPI_0_OSPI_RCLK_CLK_PARENT_HSDIV4_16FFT_MCU_2_HSDIVOUT4_CLK;
#endif

        retVal = Sciclient_pmSetModuleClkParent(devID[BOARD_OSPI_NOR_INSTANCE],
                                                clkID[BOARD_OSPI_NOR_INSTANCE],
                                                parClk,
                                                SCICLIENT_SERVICE_WAIT_FOREVER);
    }
    else
    {
#if defined (SOC_AM64X)
        parClk = TISCI_DEV_FSS0_OSPI_0_OSPI_RCLK_CLK_PARENT_HSDIV4_16FFT_MAIN_0_HSDIVOUT1_CLK;
#else
        parClk = TISCI_DEV_MCU_FSS0_OSPI_0_OSPI_RCLK_CLK_PARENT_HSDIV4_16FFT_MCU_1_HSDIVOUT4_CLK;
#endif
        retVal = Sciclient_pmSetModuleClkParent(devID[BOARD_OSPI_NOR_INSTANCE],
                                                clkID[BOARD_OSPI_NOR_INSTANCE],
                                                parClk,
                                                SCICLIENT_SERVICE_WAIT_FOREVER);
    }

    if (retVal != CSL_PASS)
    {
        SBL_log(SBL_LOG_MAX, "Sciclient_pmSetModuleClkParent failed \n");
    }

	ospi_cfg.funcClk = freq;
    OSPI_socSetInitCfg(BOARD_OSPI_NOR_INSTANCE, &ospi_cfg);

    ospi_rclk_freq = (uint64_t)freq;
    retVal = Sciclient_pmSetModuleClkFreq(devID[BOARD_OSPI_NOR_INSTANCE],
                                          clkID[BOARD_OSPI_NOR_INSTANCE],
                                          ospi_rclk_freq,
                                          TISCI_MSG_FLAG_AOP,
                                          SCICLIENT_SERVICE_WAIT_FOREVER);

    if (retVal != CSL_PASS)
    {
        SBL_log(SBL_LOG_MAX, "Sciclient_pmSetModuleClkFreq failed \n");
    }

	ospi_rclk_freq = 0;
    retVal = Sciclient_pmGetModuleClkFreq(devID[BOARD_OSPI_NOR_INSTANCE],
                                          clkID[BOARD_OSPI_NOR_INSTANCE],
                                          &ospi_rclk_freq,
                                          SCICLIENT_SERVICE_WAIT_FOREVER);
    if (retVal != CSL_PASS)
    {
        SBL_log(SBL_LOG_MAX, "Sciclient_pmGetModuleClkFreq failed \n");
    }

    SBL_log(SBL_LOG_MAX, "OSPI RCLK running at %d MHz. \n", (uint32_t)ospi_rclk_freq);

}
#endif

int32_t SBL_ospiInit(void *handle)
{
#if (!defined(SBL_BYPASS_OSPI_DRIVER) \
     /* In simulation, we must ALWAYS bypass the OSPI driver regardless of what */ \
     /* .. bypass option is requested. REMOVE WHEN SIMULATION IS IRRELEVANT. */ \
     && !(defined(SBL_BYPASS_OSPI_DRIVER_FOR_SYSFW_DOWNLOAD) && defined(SIM_BUILD)))

    Board_flashHandle h = *(Board_flashHandle *) handle;
    static uint32_t enableTuning = TRUE;

    SBL_ADD_PROFILE_POINT;

    if (h)
    {
        Board_flashClose(h);
        SBL_ADD_PROFILE_POINT;

    }

    /* Get default OSPI cfg */
    OSPI_socGetInitCfg(BOARD_OSPI_NOR_INSTANCE, &ospi_cfg);

#if !defined(SBL_SKIP_BRD_CFG_PM) && !defined(SBL_SKIP_SYSFW_INIT)
    {
        /* System Firmware reconfigures the OSPI clock to
         * unsupported values. This is a workaround until
         * that issue is fixed
         */
        uint64_t ospiFunClk;
#if defined(SOC_AM64X) || defined(SOC_J721E) || defined(BUILD_XIP)
        ospiFunClk = (uint64_t)(OSPI_MODULE_CLK_166M);
        ospi_cfg.devDelays[3] = OSPI_DEV_DELAY_CSDA_3;
#else
        ospiFunClk = (uint64_t)(OSPI_MODULE_CLK_133M);
        ospi_cfg.devDelays[3] = OSPI_DEV_DELAY_CSDA_2;
#endif
        ospi_cfg.funcClk = ospiFunClk;
        ospi_cfg.baudRateDiv = 0;

#if defined(SOC_J721E) || defined(SOC_J7200) || defined(SOC_AM64X)
        OSPI_configClk(ospiFunClk);
#else
        struct ospiClkParams
        {
            uint32_t moduleId;
            uint32_t clockId;
        };
        struct ospiClkParams ospiClkInfo[] = {
                                                {SBL_DEV_ID_OSPI0, SBL_CLK_ID_OSPI0},
#ifdef SBL_DEV_ID_OSPI1
                                                {SBL_DEV_ID_OSPI1, SBL_CLK_ID_OSPI1},
#endif
                                            };
        Sciclient_pmSetModuleClkFreq(ospiClkInfo[BOARD_OSPI_NOR_INSTANCE].moduleId, ospiClkInfo[BOARD_OSPI_NOR_INSTANCE].clockId, ospiFunClk, TISCI_MSG_FLAG_AOP, SCICLIENT_SERVICE_WAIT_FOREVER);
        ospi_cfg.funcClk = (uint32_t)ospiFunClk;
        SBL_log(SBL_LOG_MAX, "ospiFunClk = %d Hz \n", ospi_cfg.funcClk);
#endif
    }
#endif

    ospi_cfg.dtrEnable = true;

#if defined(SOC_AM64X)
    ospi_cfg.funcClk = OSPI_MODULE_CLK_166M;
#endif

#if SBL_USE_DMA
    ospi_cfg.dmaEnable = true;
    Ospi_udma_init(&ospi_cfg);

    #if defined(SOC_J721E)
    SBL_udmaInit(gDrvHandle);
    #endif
#endif

#if SBL_USE_DMA
    /* J721E: PHY mode was already previously enabled, so we keep it enabled */
    /* J7200/AM64X: Enable the PHY mode which was disabled in SBL_ReadSysfwImage */
    ospi_cfg.phyEnable = true;
#else
#if defined(SOC_J721E) || defined(BUILD_XIP)
    ospi_cfg.phyEnable = true;
    ospi_cfg.cacheEnable = true;
#else
    ospi_cfg.phyEnable = false;
#endif
#endif
    /* Set the default SPI init configurations */
    OSPI_socSetInitCfg(BOARD_OSPI_NOR_INSTANCE, &ospi_cfg);

#if defined(SOC_J7200) || defined(SOC_AM64X)
    h = Board_flashOpen(BOARD_FLASH_ID_S28HS512T,
                        BOARD_OSPI_NOR_INSTANCE, (void *)(enableTuning));
#else
    h = Board_flashOpen(BOARD_FLASH_ID_MT35XU512ABA1G12,
                            BOARD_OSPI_NOR_INSTANCE, (void *)(enableTuning));
#endif
    if (h)
    {
        *(Board_flashHandle *) handle = h;
        /* Update the static handle as well, for later use */
        boardHandle = (void *)h;
#if !(SBL_USE_DMA) && !defined(SOC_J721E) && !defined(BUILD_XIP)
        /* Disable PHY pipeline mode if not using DMA */
        CSL_ospiPipelinePhyEnable((const CSL_ospi_flash_cfgRegs *)(ospi_cfg.baseAddr), FALSE);
#endif
    }
    else
    {
        SBL_log(SBL_LOG_ERR, "Board_flashOpen failed!\n");
        SblErrLoop(__FILE__, __LINE__);
    }

    SBL_ADD_PROFILE_POINT;

    return 0;
#else
    SBL_ADD_PROFILE_POINT;

    SBL_ADD_PROFILE_POINT;
    return 0;
#endif
}

int32_t SBL_ospiFlashRead(const void *handle, uint8_t *dst, uint32_t length,
    uint32_t offset)
{
    uint32_t start_time = SBL_ADD_PROFILE_POINT;
    uint32_t end_time = 0;

#if (!defined(SBL_BYPASS_OSPI_DRIVER) \
     /* In simulation, we must ALWAYS bypass the OSPI driver regardless of what */ \
     /* .. bypass option is requested. REMOVE WHEN SIMULATION IS IRRELEVANT. */ \
     && !(defined(SBL_BYPASS_OSPI_DRIVER_FOR_SYSFW_DOWNLOAD) && defined(SIM_BUILD)))

#if SBL_USE_DMA
    Board_flashHandle h = *(const Board_flashHandle *) handle;
    uint32_t ioMode = OSPI_FLASH_OCTAL_READ;

#if defined(SOC_AM64X)
    /* Special handling for M4F memory region transfers to workaround BCDMA copy issue */
    if (((uint32_t)dst >= (uint32_t)(SBL_M4F_IRAM_BASE_ADDR_SOC)) &&
        ((uint32_t)dst < (uint32_t)(SBL_M4F_DRAM_BASE_ADDR_SOC + SBL_M4F_DRAM_SIZE)))
    {
        memcpy((void *)dst, (void *)(ospi_cfg.dataAddr + offset), length);
        SBL_log(SBL_LOG_MAX, "Copy to M4F mem location 0x%x ...\n", (uint32_t)dst);
    }
    else
    {
#endif
    if (length > 4 * 1024)
    {
        /* split transfer if not reading from 16 byte aligned flash offset */
        uint32_t dma_offset  = (offset + 0xF) & (~0xF);
        uint32_t non_aligned_bytes = dma_offset - offset;
        uint8_t *dma_dst = (dst + non_aligned_bytes);
        uint32_t dma_len = length - non_aligned_bytes;

        SBL_DCacheClean((void *)dst, length);

        if ((non_aligned_bytes) && (Board_flashRead(h, offset, dst, non_aligned_bytes, (void *)(&ioMode))))
        {
            SBL_log(SBL_LOG_ERR, "Board_flashRead failed!\n");
            SblErrLoop(__FILE__, __LINE__);
        }

        if (Board_flashRead(h, dma_offset, dma_dst, dma_len, (void *)(&ioMode)))
        {
            SBL_log(SBL_LOG_ERR, "Board_flashRead failed!\n");
            SblErrLoop(__FILE__, __LINE__);
        }
    }
    else
    {
        SBL_DCacheClean((void *)dst, length);
        Board_flashRead(h, offset, dst, length, (void *)(&ioMode));
    }
#if defined(SOC_AM64X)
    }  /* End of 'else' for M4F memory region transfers */
#endif

#else
#if defined(SOC_J721E) || defined(BUILD_XIP)
    Board_flashHandle h = *(const Board_flashHandle *) handle;
    uint32_t ioMode = OSPI_FLASH_OCTAL_READ;
    SBL_DCacheClean((void *)dst, length);
    Board_flashRead(h, offset, dst, length, (void *)(&ioMode));
#else
    memcpy((void *)dst, (void *)(ospi_cfg.dataAddr + offset), length);
#endif
#endif /* #if SBL_USE_DMA */

#else
    memcpy((void *)dst, (void *)(ospi_cfg.dataAddr + offset), length);
#endif /* #if !defined(SBL_BYPASS_OSPI_DRIVER) */

    end_time = SBL_ADD_PROFILE_POINT;

    SBL_log(SBL_LOG_MAX, "Ospi Read speed for 0x%x bytes from offset 0x%x = %d Mbytes per sec\n", length, offset, ((400000000 / (end_time-start_time)) * length)/0x100000);

    return 0;
}

int32_t SBL_ospiClose(const void *handle)
{
#if (!defined(SBL_BYPASS_OSPI_DRIVER) \
     /* In simulation, we must ALWAYS bypass the OSPI driver regardless of what */ \
     /* .. bypass option is requested. REMOVE WHEN SIMULATION IS IRRELEVANT. */ \
     && !(defined(SBL_BYPASS_OSPI_DRIVER_FOR_SYSFW_DOWNLOAD) && defined(SIM_BUILD)))

    Board_flashHandle h = *(const Board_flashHandle *) handle;

    SBL_ADD_PROFILE_POINT;

    SBL_log(SBL_LOG_MAX, "SBL_ospiClose called\n");
    Board_flashClose(h);
#if SBL_USE_DMA
    #if defined(SOC_J721E)
    SBL_udmaDeInit();
    #endif
    Ospi_udma_deinit();
#endif
    SBL_ADD_PROFILE_POINT;
#else
    SBL_ADD_PROFILE_POINT;
    SBL_ADD_PROFILE_POINT;
#endif
    return 0;
}

#if defined(SBL_HLOS_OWNS_FLASH) && !defined(SBL_USE_MCU_DOMAIN_ONLY) && !defined(SBL_ENABLE_DEV_GRP_MCU)
/* Only put OSPI flash back into SPI mode if we're going to directly boot ATF/U-boot/Linux from SBL */
int32_t SBL_ospiLeaveConfigSPI()
{
    int32_t retVal = E_PASS;
    Board_flashHandle h;
    Board_FlashInfo *flashInfo;

    SBL_ADD_PROFILE_POINT;

    /* Get default OSPI cfg */
    OSPI_socGetInitCfg(BOARD_OSPI_NOR_INSTANCE, &ospi_cfg);

    ospi_cfg.funcClk = OSPI_MODULE_CLK_133M;
    /* Configure the flash for SPI mode */
    ospi_cfg.xferLines = OSPI_XFER_LINES_SINGLE;
    /* Put controller in DAC mode so flash ID can be read directly */
    ospi_cfg.dacEnable = true;
    /* Disable PHY in legacy SPI mode (1-1-1) */
    ospi_cfg.phyEnable = false;
    ospi_cfg.dtrEnable = false;
    ospi_cfg.xipEnable = false;

    /* Set the default SPI init configurations */
    OSPI_socSetInitCfg(BOARD_OSPI_NOR_INSTANCE, &ospi_cfg);

    SBL_ADD_PROFILE_POINT;

#if defined(SOC_J7200) || defined(SOC_AM64X)
    h = Board_flashOpen(BOARD_FLASH_ID_S28HS512T,
                        BOARD_OSPI_NOR_INSTANCE, NULL);
#else
    h = Board_flashOpen(BOARD_FLASH_ID_MT35XU512ABA1G12,
                        BOARD_OSPI_NOR_INSTANCE, NULL);
#endif

    if (h)
    {
        SBL_log(SBL_LOG_MAX, "OSPI flash left configured in Legacy SPI mode.\n");
        flashInfo = (Board_FlashInfo *)h;
        SBL_log(SBL_LOG_MAX, "\n OSPI NOR device ID: 0x%x, manufacturer ID: 0x%x \n",
                flashInfo->device_id, flashInfo->manufacturer_id);
        Board_flashClose(h);
    }
    else
    {
        SBL_log(SBL_LOG_ERR, "Board_flashOpen failed in SPI mode!!\n");
        retVal = E_FAIL;
    }

    SBL_ADD_PROFILE_POINT;

    return(retVal);
}
#endif

int32_t SBL_OSPIBootImage(sblEntryPoint_t *pEntry)
{
    int32_t retVal;

#ifdef SECURE_BOOT
    uint32_t authenticated = 0;
    uint32_t srcAddr = 0;
    uint32_t imgOffset = 0;
#else
    uint32_t offset = OSPI_OFFSET_SI;
#endif

    /* Initialization of the driver. */
    SBL_OSPI_Initialize();

#ifndef SECURE_BOOT
#if defined(SBL_ENABLE_HLOS_BOOT) && (defined(SOC_J721E) || defined(SOC_J7200))
    retVal =  SBL_MulticoreImageParse((void *) &offset, OSPI_OFFSET_SI, pEntry, SBL_SKIP_BOOT_AFTER_COPY);
#else
    retVal =  SBL_MulticoreImageParse((void *) &offset, OSPI_OFFSET_SI, pEntry, SBL_BOOT_AFTER_COPY);
#endif

#else
    retVal = SBL_loadOSPIBootData();

    if (retVal == E_PASS)
    {
        /* authentiate it */
        authenticated = SBL_authentication(sblInBootData.sbl_boot_buff);
        if (authenticated == 0)
        {
            /* fails authentiation */
            SBL_log(SBL_LOG_ERR, "\n OSPI Boot - fail authentication\n");

            retVal = E_FAIL;
        }
        else
        {
            /* need to skip the TOC headers */
            imgOffset = ((uint32_t*)sblInBootData.sbl_boot_buff)[0];
            srcAddr = (uint32_t)(sblInBootData.sbl_boot_buff) + imgOffset;
#if defined(SBL_ENABLE_HLOS_BOOT) && (defined(SOC_J721E) || defined(SOC_J7200))
            retVal = SBL_MulticoreImageParse((void *)srcAddr, 0, pEntry, SBL_SKIP_BOOT_AFTER_COPY);
#else
            retVal = SBL_MulticoreImageParse((void *)srcAddr, 0, pEntry, SBL_BOOT_AFTER_COPY);
#endif
        }
    }
    else
    {
        retVal = E_FAIL;
        SBL_log(SBL_LOG_ERR, "\n OSPI Boot - problem processing image \n");
    }

#endif

    SBL_ospiClose(&boardHandle);

#if defined(BUILD_XIP) && (defined(SOC_J7200) || defined(SOC_AM64X)) /* These fields are reset by Nor_xspiClose but are required for XIP */
    const CSL_ospi_flash_cfgRegs *pRegs = (const CSL_ospi_flash_cfgRegs *)(ospi_cfg.baseAddr);

    CSL_REG32_FINS(&pRegs->RD_DATA_CAPTURE_REG,
                    OSPI_FLASH_CFG_RD_DATA_CAPTURE_REG_SAMPLE_EDGE_SEL_FLD,
                    1);

    CSL_REG32_FINS(&pRegs->RD_DATA_CAPTURE_REG,
                    OSPI_FLASH_CFG_RD_DATA_CAPTURE_REG_DQS_ENABLE_FLD,
                    1);
#endif

#if defined(SBL_HLOS_OWNS_FLASH) && !defined(SBL_USE_MCU_DOMAIN_ONLY) && !defined(SBL_ENABLE_DEV_GRP_MCU)
/* Only put OSPI flash back into SPI mode if we're going to directly boot ATF/U-boot/Linux from SBL */
    SBL_ospiLeaveConfigSPI();
#endif

    return retVal;
}

static void SBL_OSPI_Initialize(void)
{
    SBL_ospiInit(&boardHandle);

    /* Initialize the function pointers to parse through the RPRC format. */

#ifndef SECURE_BOOT
    fp_readData = &SBL_OSPI_ReadSectors;
    fp_seek     = &SBL_OSPI_seek;
#else
    fp_readData = &SBL_MemRead;
    fp_seek     = &SBL_MemSeek;
#endif

}


#ifndef SECURE_BOOT

void SBL_SPI_init()
{
    SPI_init();
}

int32_t SBL_OSPI_ReadSectors(void *dstAddr,
                             void *srcOffsetAddr,
                             uint32_t length)
{
    int32_t ret;
    ret = SBL_ospiFlashRead(&boardHandle, (uint8_t *) dstAddr, length,
        *((uint32_t *) srcOffsetAddr));
    *((uint32_t *) srcOffsetAddr) += length;
    return ret;
}

void SBL_OSPI_seek(void *srcAddr, uint32_t location)
{
    *((uint32_t *) srcAddr) = location;
}

#else

/* load signed boot data from OSPI */
int32_t SBL_loadOSPIBootData()
{
    int32_t  retVal = E_PASS;
    uint32_t key_size = 0;
    uint32_t load_size = 0;
    uint32_t total_size = 0;
    uint8_t  *u8Ptr = 0;

    sblInBootData.sbl_boot_size = 0;
    sblInBootData.sbl_boot_buff_idx = 0;    /* reset the read pointer */

    u8Ptr = sblInBootData.sbl_boot_buff;

    /* first read a block to figure out the max size */
    retVal = SBL_ospiFlashRead(&boardHandle, sblInBootData.sbl_boot_buff,
                               READ_BUFF_SIZE, OSPI_OFFSET_SI);

    if (retVal == E_PASS)
    {
        if (strcmp((char *)&u8Ptr[TOC_HDR_SIZE + TOC_FILE_NAME_OFFSET], "KEYS")==0)
        {
            /* first TOC HDR is IMG. Second TOC HDR is image */
            key_size = *(uint32_t*)(&u8Ptr[TOC_HDR_SIZE + TOC_DAT_SIZE_OFFSET]);

            if (strcmp((char *)&u8Ptr[TOC_FILE_NAME_OFFSET], "2ND")==0)
            {
                load_size = *(uint32_t*)(&u8Ptr[TOC_DAT_SIZE_OFFSET]);

                total_size = key_size + load_size + 0x60;
                sblInBootData.sbl_boot_size = total_size;

                if (total_size < SBL_MAX_BOOT_BUFF_SIZE)
                {
                    /* read the entire boot data in */
                    retVal = SBL_ospiFlashRead(&boardHandle,
                                            sblInBootData.sbl_boot_buff,
                                            total_size,
                                            OSPI_OFFSET_SI);
                }
                else
                {
                    /* not enough buffer to read entire boot data */
                    retVal = E_FAIL;
                }
            }
            else
            {
                /* bad or unsupported image type */
                retVal = E_FAIL;
            }
        }
        else
        {
            /* Keys not found */
            retVal = E_FAIL;
        }
    }
    else
    {
        /* Fail to read the OSPI flash */
        retVal = E_FAIL;
    }


    return retVal;
}
#endif


