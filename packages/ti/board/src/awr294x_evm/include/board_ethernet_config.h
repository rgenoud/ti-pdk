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
 * \brief  board_ethernet_config.h
 *
 * This file contains the Ethernet PHY configurations for AWR294X EVM
 *
 */

#ifndef _BOARD_ETHERNET_CONFIG_H_
#define _BOARD_ETHERNET_CONFIG_H_

#include <ti/board/board.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ENABLE_AWR294X_BOARD_MDIO  (TRUE)

/**
 * \enum emac_mode
 *
 * \brief specifies the available emac mode types.
 */
typedef enum
{
    RMII = 1,
    RGMII = 2,
}emac_mode;

/**
 * \brief  Board specific configurations for MCU Ethernet PHY
 *
 * This function takes care of configuring the internal delays for MCU gigabit
 * Ethernet PHY
 *
 * \return  none
 */
Board_STATUS Board_mcuEthConfig(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _BOARD_ETHERNET_CONFIG_H_ */
