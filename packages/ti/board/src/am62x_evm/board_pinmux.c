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
 *  \file board_pinmux.c
 *
 *  \brief This file Enables pinmux for the board 
 *
 */

#include <ti/csl/soc.h>				
#include "board_internal.h"
#include "board_pinmux.h"

#ifdef BUILD_M4F
#define MAIN_PADCONFIG_CTRL_BASE    CSL_PADCFG_CTRL0_CFG0_BASE + 0x60000000
#define MCU_PADCONFIG_CTRL_BASE     CSL_WKUP_PADCFG_CTRL0_CFG0_BASE
#else
#define MAIN_PADCONFIG_CTRL_BASE    CSL_PADCFG_CTRL0_CFG0_BASE
#define MCU_PADCONFIG_CTRL_BASE     CSL_WKUP_PADCFG_CTRL0_CFG0_BASE
#endif

#define CTRL_MMR0_PARTITION_SIZE    0x4000
#define MAIN_CTRL_PINCFG_BASE       (MAIN_PADCONFIG_CTRL_BASE + (1 * CTRL_MMR0_PARTITION_SIZE))

/* Default pinmux configuration of UART Tx pin used by R5 DM */
#define BOARD_UART_TX_PINMUX_VAL            (PIN_MODE(0) | ((PIN_PULL_DISABLE) & \
                                                 (~PIN_PULL_DIRECTION & ~PIN_INPUT_ENABLE)))
#define BOARD_WKUP_UART_TX_PINMUX_ADDR           (MCU_PADCONFIG_CTRL_BASE + CSL_MCU_PADCFG_CTRL_MMR_CFG0_PADCONFIG10)
#define BOARD_MAIN_UART0_TX_PINMUX_ADDR           (MAIN_PADCONFIG_CTRL_BASE + CSL_MAIN_PADCFG_CTRL_MMR_CFG0_PADCONFIG145)
#define BOARD_UART_TX_LOCK_KICK_ADDR        (MAIN_PADCONFIG_CTRL_BASE + \
                                                 CSL_MAIN_PADCFG_CTRL_MMR_CFG0_LOCK1_KICK0)

/**
 *  \brief  Gets base address of padconfig registers
 *
 *  \param   domain [IN]  SoC domain for pinmux
 *  \n                     BOARD_SOC_DOMAIN_MAIN - Main domain
 *  \n                     BOARD_SOC_DOMAIN_MCU  - MCU domain
 *
 *  \return   Valid address in case success or 0 in case of failure
 */
static uint32_t Board_pinmuxGetBaseAddr(uint8_t domain)
{
    uint32_t baseAddr;

    switch(domain)
    {
        case BOARD_SOC_DOMAIN_MAIN:
            baseAddr = BOARD_MAIN_PMUX_CTRL;
        break;
        case BOARD_SOC_DOMAIN_MCU:
            baseAddr = BOARD_WKUP_PMUX_CTRL;
        break;
        default:
            baseAddr = 0;
        break;
    }

    return baseAddr;
}


/**
 * \brief  Function to configure UART Tx pinmux
 *
 */
Board_STATUS Board_uartTxPinmuxConfig(void)
{
    Board_unlockMMR();
    /* Board_unlockMMR */
    // HW_WR_REG32(BOARD_UART_TX_LOCK_KICK_ADDR, KICK0_UNLOCK_VAL);
    // HW_WR_REG32(BOARD_UART_TX_LOCK_KICK_ADDR + 4U, KICK1_UNLOCK_VAL);

    /* Configure pinmux for WKUP UART Tx pin */
    HW_WR_REG32(BOARD_WKUP_UART_TX_PINMUX_ADDR, BOARD_UART_TX_PINMUX_VAL);     

    /* Configure pinmux for  Main UART0 Tx pin */
    HW_WR_REG32(BOARD_MAIN_UART0_TX_PINMUX_ADDR, BOARD_UART_TX_PINMUX_VAL);
    
    // /* Board_lockMMR */
    // HW_WR_REG32(BOARD_UART_TX_LOCK_KICK_ADDR + 4U, 0);
    // HW_WR_REG32(BOARD_UART_TX_LOCK_KICK_ADDR, 0);
    // Board_lockMMR(); //;locking MMR might casue issues with linux

    return BOARD_SOK;
}

/**
 *  \brief Sets padconfig register of a pin at given offset
 *
 *  Configures whole padconfig register of the pin at given offset
 *  with the value in 'muxData'.
 *
 *  \param   domain  [IN]  SoC domain for pinmux
 *  \n                      BOARD_SOC_DOMAIN_MAIN - Main domain
 *
 *  \param   offset  [IN]  Pad config offset of the pin
 *  \param   muxData [IN]  Value to be written to padconfig register
 *
 *  \return   BOARD_SOK in case of success or appropriate error code
 *
 */
Board_STATUS Board_pinmuxSetReg(uint8_t  domain,
                                uint32_t offset,
                                uint32_t muxData)
{
    uint32_t baseAddr;
    Board_STATUS status = BOARD_SOK;

    Board_unlockMMR();

    baseAddr = Board_pinmuxGetBaseAddr(domain);
    if(baseAddr != 0)
    {
        HW_WR_REG32((baseAddr + offset), muxData);
    }
    else
    {
        status = BOARD_INVALID_PARAM;
    }

    return status;
}
