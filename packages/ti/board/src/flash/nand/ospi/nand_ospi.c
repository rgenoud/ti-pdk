/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <ti/board/src/flash/nand/ospi/nand_ospi.h>
#include <ti/drv/spi/soc/SPI_soc.h>
#include <ti/csl/soc.h>

#if defined(j721s2_evm)
/* SPI entry offset is at index 5 of SPI config array */
#define SPI_CONFIG_OFFSET     (5U)
#endif

NAND_HANDLE Nand_ospiOpen(uint32_t norIntf, uint32_t portNum, void *params);
void Nand_ospiClose(NAND_HANDLE handle);
NAND_STATUS Nand_ospiRead(NAND_HANDLE handle, uint32_t addr,
                               uint32_t len, uint8_t *buf);
NAND_STATUS Nand_ospiWrite(NAND_HANDLE handle, uint32_t addr,
                                uint32_t len, uint8_t *buf);
NAND_STATUS Nand_ospiErase(NAND_HANDLE handle, int32_t eraseCnt);

NAND_STATUS Nand_ospiCmdWrite(SPI_Handle handle, uint8_t *cmdBuf,
                                   uint32_t cmdLen, uint32_t dataLen);

/* NAND function table for NAND OSPI interface implementation */
const NAND_FxnTable Nand_ospiFxnTable =
{
    &Nand_ospiOpen,
    &Nand_ospiClose,
    &Nand_ospiRead,
    &Nand_ospiWrite,
    &Nand_ospiErase,
};

NAND_Info Nand_ospiInfo =
{
    0,                          /* hwHandle */
    0,                          /* manufacturerId */
    0,                          /* deviceId */
    0,                          /* busWidth */
    NAND_NUM_BLOCKS,            /* blockCnt */
    NAND_NUM_PAGES_PER_BLOCK,   /* pageCnt */
    NAND_PAGE_SIZE,             /* pageSize */
    0,                         /* baseAddr */
    NAND_SECTOR_SIZE            /* sectorSize */
};

bool gPhyEnable;
bool gDtrEnable;

NAND_STATUS NAND_ospiCmdRead(SPI_Handle handle, uint8_t *cmdBuf,
                            uint32_t cmdLen, uint8_t *rxBuf, uint32_t rxLen)
{
    /* TO DO */
    return NAND_PASS;
}

NAND_STATUS Nand_ospiReadId(SPI_Handle handle)
{
    /* TO DO */
    return NAND_PASS;
}

NAND_STATUS Nand_ospiEnableDDR(SPI_Handle handle)
{
    /* TO DO */
    return NAND_PASS;
}

NAND_STATUS Nand_ospiEnableSDR(SPI_Handle handle)
{
    /* TO DO */
    return NAND_PASS;
}

NAND_STATUS Nand_ospiResetMemory(SPI_Handle handle)
{
    /* TO DO */
    return NAND_PASS;
}

NAND_STATUS Nand_ospiXipEnable(SPI_Handle handle)
{
    /* TO DO */
    return NAND_PASS;
}

NAND_STATUS Nand_ospiSetDummyCycle(SPI_Handle handle, uint32_t dummyCycle)
{
    /* TO DO */
    return NAND_PASS;
}

void Nand_ospiSetOpcode(SPI_Handle handle)
{
    /* TO DO */
}

NAND_HANDLE Nand_ospiOpen(uint32_t norIntf, uint32_t portNum, void *params)
{
    /* TO DO */
    NAND_HANDLE nandHandle = 0;
    return (nandHandle);
}

void Nand_ospiClose(NAND_HANDLE handle)
{
    /* TO DO */
}

NAND_STATUS Nand_ospiCmdWrite(SPI_Handle handle, uint8_t *cmdBuf,
                                        uint32_t cmdLen, uint32_t dataLen)
{
    /* TO DO */
    return NAND_PASS;
}

NAND_STATUS Nand_ospiWaitReady(SPI_Handle handle, uint32_t timeOut)
{
    /* TO DO */
    return NAND_PASS;
}

SPI_Transaction transaction;
NAND_STATUS Nand_ospiRead(NAND_HANDLE handle, uint32_t addr, uint32_t len, uint8_t *buf)
{
    /* TO DO */
    return NAND_PASS;
}

NAND_STATUS Nand_ospiWrite(NAND_HANDLE handle, uint32_t addr, uint32_t len, uint8_t *buf)
{
    /* TO DO */
    return NAND_PASS;
}

NAND_STATUS Nand_ospiErase(NAND_HANDLE handle, int32_t erLoc)
{
    /* TO DO */
    return NAND_PASS;
}
