/******************************************************************************
 * Copyright (c) 2022 Texas Instruments Incorporated - http://www.ti.com
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

/** \file board_clock.h
*
*   \brief This file contains structure, typedefs, functions and
*          prototypes used for clock configurations.
*/
 
#ifndef BOARD_CLOCK_H
#define BOARD_CLOCK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/board/src/j784s4_evm/include/board_internal.h>

/**
 * \brief Enables module clock
 *
 * \return  BOARD_SOK   - Clock enable sucessful. 
 *          BOARD_FAIL  - Clock enable failed.
 *
 */
Board_STATUS Board_moduleClockEnable(uint32_t moduleId);

/**
 * \brief Disables module clock
 *
 * \return  BOARD_SOK   - Clock disable successful.
 *          BOARD_FAIL  - Clock disable failed.
 *
 */
Board_STATUS Board_moduleClockDisable(uint32_t moduleId);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* BOARD_CLOCK_H */
