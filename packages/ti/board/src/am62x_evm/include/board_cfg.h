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
 * \brief  Board library configurations
 *
 * This file configures the instance numbers, address and gpio reset
 * details of different interfaces of the board.
 *
 */
#ifndef BOARD_CFG_H_
#define BOARD_CFG_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Board ID information */
#define BOARD_INFO_CPU_NAME     "am62x"
#define BOARD_INFO_BOARD_NAME   "am62x_evm"

/* UART LLD instance number for MAIN UART0 port */
#define BOARD_UART0_INSTANCE                            (0U)
/* UART LLD instance number for MAIN UART1 port */
#define BOARD_UART1_INSTANCE                            (1U)
/* UART LLD instance number for MAIN UART2 port */
#define BOARD_UART2_INSTANCE                            (2U)
/* UART LLD instance number for MAIN UART3 port */
#define BOARD_UART3_INSTANCE                            (3U)
/* UART LLD instance number for MAIN UART4 port */
#define BOARD_UART4_INSTANCE                            (4U)
/* UART0 on the MCU domain */
#define BOARD_MCU_UART0_INSTANCE                        (5U)
 /* UART0 on the WKUP domain */
#define BOARD_WKUP_UART0_INSTANCE                       (6U)

#ifdef BUILD_M4F
    #define BOARD_UART_INSTANCE (BOARD_MCU_UART0_INSTANCE)
#else
    #define BOARD_UART_INSTANCE (BOARD_WKUP_UART0_INSTANCE)
#endif

/** @brief Number of UART instances */
#define BOARD_UART_PER_CNT                              (6U)

/* Maximum number of SoC domains */
#define BOARD_SOC_DOMAIN_MAX                            (2U)
/* Value for indicating SoC main domain */
#define BOARD_SOC_DOMAIN_MAIN                           (0)
/* Value for indicating SoC MCU domain */
#define BOARD_SOC_DOMAIN_MCU                            (1U)

/* SoC domain used by UART module */
#define BOARD_UART_SOC_DOMAIN    (BOARD_SOC_DOMAIN_MAIN)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif   /* BOARD_CFG_H_ */

