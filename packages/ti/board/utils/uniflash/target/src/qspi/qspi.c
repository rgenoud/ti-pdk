/*
 * Copyright (C) 2018-2019 Texas Instruments Incorporated - http://www.ti.com/
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

/**
 *  \file    qspi.c
 *
 *  \brief   qspi flash writer API implementation.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "qspi.h"

/* ========================================================================== */
/*                      Internal Function Declarations                        */
/* ========================================================================== */

static int8_t UFP_qspiInit(void);

static int8_t UFP_qspiFlashErase(uint32_t offset, uint32_t length);

static int8_t UFP_qspiFlashImage(uint8_t *flashAddr, uint8_t *checkAddr,
                                 uint32_t offset, uint32_t size);

static int8_t UFP_qspiClose(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#if (defined(SOC_K2G) || defined(j721e_evm) || defined(j721s2_evm) || defined(j784s4_evm) || defined(tpr12_evm) || defined(awr294x_evm))
    Board_flashHandle gQspiHandle;
#else
    S25FL_Handle gQspiHandle;
#endif

/* Flash programmer qspi function table */
const UFP_fxnTable UFP_qspiFxnTable = {
    &UFP_qspiInit,
    &UFP_qspiFlashErase,
    &UFP_qspiFlashImage,
    &UFP_qspiClose
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#if (defined(SOC_TPR12) || defined(SOC_AWR294X)) && defined(SPI_DMA_ENABLE)
/**
 * \brief      Function to initialize the edma driver and get the handle to the
 *             edma driver;
 */
EDMA_Handle  gUfpEdmaHandle = NULL;

static EDMA_Handle UFP_qspiEdmaInit(void)
{
    uint32_t edma3Id = EDMA_DRV_INST_MSS_A;
    EDMA_instanceInfo_t instanceInfo;
    int32_t errorCode;

    gUfpEdmaHandle = EDMA_getHandle(edma3Id, &instanceInfo);
    if(NULL == gUfpEdmaHandle)
    {
        EDMA3CCInitParams 	initParam;

        EDMA3CCInitParams_init(&initParam);
        initParam.initParamSet = UTRUE;
        if (EDMA_NO_ERROR != EDMA_init(edma3Id, &initParam))
        {
            return(gUfpEdmaHandle);
        }

        /* Open DMA driver instance 0 for SPI test */
        gUfpEdmaHandle = EDMA_open(edma3Id, &errorCode, &instanceInfo);
        if(NULL == gUfpEdmaHandle)
        {
            return(gUfpEdmaHandle);
        }
    }

    return(gUfpEdmaHandle);
}

static uintptr_t UFP_l2GlobalAddress (uintptr_t addr)
{
    return ((uintptr_t)CSL_locToGlobAddr(addr));
}
#endif

/**
 *  \brief		This function closes the qspi Handle.
 *
 *  \return		int8_t
 *					0		- in case of success
 *
 */
static int8_t UFP_qspiClose(void)
{
#if (defined(SOC_K2G) || defined(j721e_evm) || defined(j721s2_evm) || defined(j784s4_evm) || defined(tpr12_evm) || defined(awr294x_evm))
    Board_flashClose(gQspiHandle);
#else
    S25FLFlash_QuadModeEnable(gQspiHandle);
    SF25FL_close(gQspiHandle);
#endif
    return 0;
}

/**
 *  \brief		This function reads the image from specified location of qspi.
 *
 *	\param		dst			[OUT]   Pointer to store the read image
 *	\param		offset		[IN]   	offset of the image on Flash
 *	\param		length		[IN]	Size of image.
 *
 *  \return		int8_t
 *					0		- in case of success
 *	               -1		- in case of failure.
 *
 */
static int8_t UFP_qspiFlashRead(uint8_t *dst, uint32_t offset, uint32_t length)
{
#if (defined(SOC_K2G) || defined(j721e_evm) || defined(j721s2_evm) || defined(j784s4_evm) || defined(tpr12_evm) || defined(awr294x_evm))
    uint32_t ioMode;

    ioMode = BOARD_FLASH_QSPI_IO_MODE_QUAD;

    if (Board_flashRead(gQspiHandle, offset, dst, length, (void *)(&ioMode)))
    {
        return -1;
    }

    return 0;
#else
    S25FL_Transaction flashTransaction;
    int32_t retVal;

    S25FLFlash_QuadModeEnable(gQspiHandle);

    /* Update transaction parameters for the Read operation. */
    flashTransaction.data       = dst;
    flashTransaction.address    = offset;
    flashTransaction.dataSize   = length;

    /* Read data from flash */
    retVal = SF25FL_bufferRead(gQspiHandle, &flashTransaction);
	retVal = !retVal;

    /* SPI_transfer() returns TRUE if successful */
    return retVal;
#endif
}

/**
 *  \brief		This function writes the image to qspi on specified location.
 *
 *	\param		src			[IN]   	Pointer to the image to be flashed
 *	\param		offset		[IN]   	Offset to flash the image
 *	\param		length		[IN]	size of the image to be flashed.
 *
 *  \return		int8_t
 *					0		- in case of success
 *	               -1		- in case of failure.
 *
 */
static int8_t UFP_qspiFlashWrite(uint8_t *src, uint32_t offset, uint32_t length)
{
#if (defined(SOC_K2G) || defined(j721e_evm) || defined(j721s2_evm) || defined(j784s4_evm) || defined(tpr12_evm) || defined(awr294x_evm))
    uint32_t startBlockNum, endBlockNum, pageNum;
    uint32_t ioMode, i;

    ioMode = BOARD_FLASH_QSPI_IO_MODE_QUAD;

#if defined(j721e_evm) || defined(j721s2_evm) || defined(j784s4_evm)
    if (!(offset % QSPI_NOR_BLOCK_SIZE))
#else
    if (!(offset % NOR_BLOCK_SIZE))
#endif
    {
        /* Get starting block number */
        if (Board_flashOffsetToBlkPage(gQspiHandle, offset, &startBlockNum, &pageNum))
        {
            return -1;
        }

        /* Get ending block number */
        if (Board_flashOffsetToBlkPage(gQspiHandle, offset+length, &endBlockNum, &pageNum))
        {
            return -1;
        }

        /* Erase blocks, to which data has to be written */
        for(i = startBlockNum; i <= endBlockNum; i++)
        {
            if (Board_flashEraseBlk(gQspiHandle, i))
            {
                return -1;
            }
        }
    }

    /* Write buffer to flash */
    if (Board_flashWrite(gQspiHandle, offset, src, length, (void *)(&ioMode)))
    {
        return -1;
    }
#else
    S25FL_Transaction flashTransaction;
    uint32_t startBlockNumber, endBlockNumber;
    uint32_t i;

    if (!(offset % QSPI_DEVICE_BLOCK_SIZE))
    {
        /* Computing the block numbers to be erased  */
        startBlockNumber = offset / QSPI_DEVICE_BLOCK_SIZE;
        endBlockNumber = (offset + length) / QSPI_DEVICE_BLOCK_SIZE;

        for (i = startBlockNumber; i <= endBlockNumber; i++)
        {
            S25FLFlash_BlockErase(gQspiHandle, i);
        }
    }

    flashTransaction.data = src;
    flashTransaction.address = (uint32_t) offset;
    flashTransaction.dataSize = length;

    /* Write image to QSPI flash */
    SF25FL_bufferWrite(gQspiHandle, &flashTransaction);
#endif
    return 0;
}

/**
 *  \brief		This function writes the image to qspi and reads back
 *				the image on specified address.
 *
 *  \param      flashAddr   [IN]    Pointer to the image to be flashed
 *	\param		checkAddr   [OUT]   Pointer to store the read image
 *  \param      offset      [IN]    Offset to flash the image.
 *  \param      size        [IN]    size of the image to be flashed.
 *
 *  \return		int8_t
 *					0		- in case of success
 *	               -1		- in case of failure.
 *
 */
#if (defined(SOC_TPR12) || defined(SOC_AWR294X))
static int8_t UFP_qspiFlashImage(uint8_t *flashAddr, uint8_t *checkAddr,
                                 uint32_t offset, uint32_t size)
{
    int8_t ret;
    uint8_t *pFlashAddr;
    uint8_t *pCheckAddr;

#if defined(SPI_DMA_ENABLE)
    CacheP_wbInv((void *)flashAddr, (int32_t)size);
    CacheP_wbInv((void *)checkAddr, (int32_t)size);
    pFlashAddr = (uint8_t *)UFP_l2GlobalAddress((uintptr_t)flashAddr);
    pCheckAddr = (uint8_t *)UFP_l2GlobalAddress((uintptr_t)checkAddr);
#else
    pFlashAddr = flashAddr;
    pCheckAddr = checkAddr;
#endif

    ret = UFP_qspiFlashWrite(pFlashAddr, offset, size);
    if (0 != ret)
    {
        return -1;
    }

    delay(QSPI_FW_WRITE_DELAY);
    ret = UFP_qspiFlashRead(pCheckAddr, offset, size);
    if (0 != ret)
    {
        return -1;
    }

#if (defined(SOC_TPR12) || defined(SOC_AWR294X)) && defined(SPI_DMA_ENABLE)
    CacheP_wbInv((void *)checkAddr, (int32_t)size);
#endif

	return 0;
}
#else
static int8_t UFP_qspiFlashImage(uint8_t *flashAddr, uint8_t *checkAddr,
                                 uint32_t offset, uint32_t size)
{
    int8_t ret;

    ret = UFP_qspiFlashWrite(flashAddr, offset, size);
    if (0 != ret)
    {
        return -1;
    }

    delay(QSPI_FW_WRITE_DELAY);
    ret = UFP_qspiFlashRead(checkAddr, offset, size);
    if (ret != 0)
    {
        return -1;
    }

	return 0;
}
#endif

/**
 *  \brief		This function erases the qspi flash upto specified length
 *              from the specified address.
 *
 *	\param		offset		[IN]    Offset to erase the Flash.
 *	\param		length		[IN]    Erase length.
 *
 *  \return		int8_t
 *					0		- in case of success
 *	               -1		- in case of failure.
 */
static int8_t UFP_qspiFlashErase(uint32_t offset, uint32_t length)
{
#if (defined(SOC_K2G) || defined(j721e_evm) || defined(j721s2_evm) || defined(j784s4_evm) || defined(tpr12_evm) || defined(awr294x_evm))
    uint32_t startBlockNum, endBlockNum, pageNum, i;

    /* Get starting block number */
    if (Board_flashOffsetToBlkPage(gQspiHandle, offset, &startBlockNum, &pageNum))
    {
        return -1;
    }

    /* Get ending block number */
    if (Board_flashOffsetToBlkPage(gQspiHandle, offset+length, &endBlockNum, &pageNum))
    {
        return -1;
    }

    /* Erase blocks, to which data has to be written */
    for(i = startBlockNum; i <= endBlockNum; i++)
    {
        if (Board_flashEraseBlk(gQspiHandle, i))
        {
            return -1;
        }
    }

#else
    uint32_t startBlockNumber, endBlockNumber;
    uint32_t i;

    /* Computing the block numbers to be erased  */
    startBlockNumber = offset / QSPI_DEVICE_BLOCK_SIZE;
    endBlockNumber = (offset + length) / QSPI_DEVICE_BLOCK_SIZE;

    for (i = startBlockNumber; i <= endBlockNumber; i++)
    {
        S25FLFlash_BlockErase(gQspiHandle, i);
    }

#endif
    return 0;
}

/**
 *  \brief		This function initializes qspi flash.
 *				
 *  \return		int8_t
 *					0		- in case of success
 *	               -1		- in case of failure.
 *
 */
static int8_t UFP_qspiInit(void)
{
#if (defined(SOC_K2G) || defined(tpr12_evm) || defined(awr294x_evm))

#if defined(SOC_K2G)
    QSPI_v0_HwAttrs qspi_cfg;
#else /* tpr12_evm */
    QSPI_HwAttrs qspi_cfg;
#endif

    /* Get the default QSPI init configurations */
    QSPI_socGetInitCfg(BOARD_QSPI_NOR_INSTANCE, &qspi_cfg);

    /* Modify the default QSPI configurations if necessary */
    /* Turning off interrupts for baremetal mode. May be re-enabled by app */
    qspi_cfg.intrEnable = BFALSE;

#if (defined(SOC_TPR12) || defined(SOC_AWR294X)) && defined(SPI_DMA_ENABLE)
    qspi_cfg.edmaHandle = UFP_qspiEdmaInit();
    qspi_cfg.dmaEnable  = BTRUE;
#endif

    /* Set the default QSPI init configurations */
    QSPI_socSetInitCfg(BOARD_QSPI_NOR_INSTANCE, &qspi_cfg);

    /* Open the Board QSPI NOR device with QSPI port 0
       and use default QSPI configurations */
    gQspiHandle = Board_flashOpen(QSPI_FLASH_ID,
									BOARD_QSPI_NOR_INSTANCE, NULL);

#elif defined(j721e_evm) || defined(j721s2_evm) || defined(j784s4_evm)
    OSPI_v0_HwAttrs ospi_cfg;

    /* Get the default OSPI init configurations */
    OSPI_socGetInitCfg(BOARD_OSPI_DOMAIN, BOARD_SPI_NOR_INSTANCE, &ospi_cfg);
    ospi_cfg.intrEnable = BFALSE;
    /* Enable quad mode */
    ospi_cfg.xferLines = OSPI_XFER_LINES_QUAD;
    ospi_cfg.phyEnable = BFALSE;
    ospi_cfg.dmaEnable = BFALSE;
    ospi_cfg.dtrEnable = BFALSE;

    /* Set the default SPI init configurations */
    OSPI_socSetInitCfg(BOARD_OSPI_DOMAIN, BOARD_SPI_NOR_INSTANCE, &ospi_cfg);

    /* Open the Board QSPI NOR device */
    gQspiHandle = Board_flashOpen(QSPI_FLASH_ID,
                                  BOARD_SPI_NOR_INSTANCE, NULL);

#else
	SPI_Params spiParams;

     /* Initialize SPI driver */
    SPI_init();

    /* Default SPI configuration parameters */
    SPI_Params_init(&spiParams);

    /* Enabling QSPI in polling mode. */
    qspiInitCfg[0].intrEnable = BFALSE;

    /* Open QSPI driver */
    gQspiHandle = SF25FL_open(((QSPI_INSTANCE) + (QSPI_OFFSET)),
                                                  &spiParams);

#endif

    if (!(gQspiHandle))
    {
        return -1;
    }
    return 0;
}
