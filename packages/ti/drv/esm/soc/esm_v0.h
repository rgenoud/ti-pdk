/*
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
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

/** ============================================================================
 *  @file       esm_v0.h
 *
 *  @brief      ESM driver SoC specific interface.
 *
 *  ============================================================================
 */

#ifndef ESM_V0_H
#define ESM_V0_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <ti/csl/src/ip/esm/V0/esm.h>

/**
 *
 * @brief
 *  ESM Hardware Atrributes
 *
 * @details
 *  The structure is used to store the hardware specific configuration which is
 *  passed to the driver instance

 *  ESM parameters are used with the ESM_init() call.
 *
 *  @ingroup DRV_ESM_SOC_MODULE
 */
typedef struct ESM_v0_HwAttrs_t {
    CSL_esmRegs*            ptrESMRegs;         /*!< ESM Peripheral's base address for the control register space */
    uint32_t                numGroup1Err;       /*!< ESM Peripheral's supported number of group1 errors */
    uint32_t                highPrioIntNum;     /*!< ESM Peripheral's interrupt vector for high priority line*/
    uint32_t                lowPrioIntNum;      /*!< ESM Peripheral's interrupt vector for low priority line*/
} ESM_v0_HwAttrs;

#ifdef __cplusplus
}
#endif

#endif /* _ESM_V0_H */
