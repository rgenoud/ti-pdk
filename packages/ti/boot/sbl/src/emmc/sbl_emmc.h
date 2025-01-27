/**
 *  \file    sbl_emmc.h
 *
 *  \brief   This file contains function prototypes for EMMC Boot functionality
 *           of SBL.
 *
 */

/*
 * Copyright (C) 2015-2022 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef SBL_EMMC_H
#define SBL_EMMC_H

/* FATFS header file */
#include <ti/fs/fatfs/ff.h>
#include <ti/fs/fatfs/FATFS.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const FATFS_Config FATFS_config[_VOLUMES + 1];

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/*
 *  \brief    SBL_MMCBootImage function initializes the MMCSD driver and copies
 *            the application image from the SD card to the DDR memory and
 *            gives control to the processor core.
 *
 *  \param    pointer to the structure holding the entry pointers for different
 *            cores.
 *
 *  \return   error status.If error has occured it returns a non zero value.
 *            If no error has occured then return status will be zero.
 *
 */
int32_t SBL_eMMCBootImage(sblEntryPoint_t *pEntry);

/*
 *  \brief    SBL_enableEmmcBoot0 updates the global variable gIsEmmcBoot0Enable to true if EMMC_BOOT0 is defined
 *
 *  \param    none
 *
 *  \return   none
 *
 */
void SBL_enableEmmcBoot0();

#ifdef __cplusplus
}
#endif

#endif

