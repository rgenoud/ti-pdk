/******************************************************************************
 * Copyright (c) 2020 Texas Instruments Incorporated - http://www.ti.com
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
 * \file   board_pinmux.h
 *
 * \brief  TPR12 EVM pinmux interface header file.
 *
 */

#ifndef _BOARD_PIN_MUX_H_
#define _BOARD_PIN_MUX_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/board/src/tpr12_evm/include/pinmux.h>
#include <ti/board/src/tpr12_evm/TPR12_pinmux.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc/tpr12/src/cslr_mss_iomux.h>
#include <ti/csl/soc.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MODE_PIN_MASK                   (0xFU)
#define PINMUX_BIT_MASK                 (0xFFF8FFF0U)

/* MAIN CTRL base address + offset to beginning of PAD CONFIG  section */
#define PMUX_CTRL	(CSL_MSS_IOMUX_U_BASE)

/**
 *  \brief    This function used to set the specified pinMux
 *            mode for a specified pinMux offset address register.
 *
 *  \param    offset     [IN]       Pad config offset address
 *            mode       [IN]       Pad config mux mode.
 *
 *
 */
void Board_pinMuxSetMode(uint32_t offset, uint32_t mode);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _BOARD_PIN_MUX_H_ */
