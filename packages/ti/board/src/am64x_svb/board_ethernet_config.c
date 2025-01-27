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
 *   \file  board_ethernet_config.c
 *
 *   \brief
 *      This file contains the boards specific Ethernet PHY configurations.
 *
 */

#include "board_ethernet_config.h"
#include "board_internal.h"
#include <ti/csl/soc.h>

/**
 * \brief  Board specific configurations for MCU Ethernet PHY
 *
 * This function takes care of configuring the internal delays for MCU gigabit
 * Ethernet PHY
 * 
 * J7ES_TODO: Place holder. Needs update
 *
 * \return  none
 */
Board_STATUS Board_mcuEthConfig(void)
{
	return BOARD_SOK;
}

/**
 * \brief  Board specific configurations for ICSS EMAC Ethernet PHYs
 *
 * This function takes care of configuring the internal delays for ICSS 
 * Ethernet PHY
 *
 * J7ES_TODO: Place holder. Needs update
 *
 * \return  none
 */
Board_STATUS Board_icssEthConfig(void)
{
	return BOARD_SOK;
}

/**
 * \brief  Board specific configurations for CPSW RGMII Ethernet
 *
 * This function takes care of configuring the internal delays for CPSW9G 
 * RGMII Ethernet PHY
 *
 * J7ES_TODO: Place holder. Needs update
 *
 * \return  none
 */
Board_STATUS Board_rgmiiEthConfig(void)
{
	return BOARD_SOK;
}

/**
 * \brief  Board specific configurations for SGMII Ethernet
 *
 * This function takes care of configuring the internal delays for 
 * SGMII Ethernet PHY
 *
 * J7ES_TODO: Place holder. Needs update
 *
 * \return  none
 */
Board_STATUS Board_sgmiiEthConfig(void)
{
	return BOARD_SOK;
}
