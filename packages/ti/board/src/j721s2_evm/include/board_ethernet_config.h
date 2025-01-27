/******************************************************************************
 * Copyright (c) 2021 Texas Instruments Incorporated - http://www.ti.com
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
 * This file contains Ethernet PHY configurations for the board
 *
 */

#ifndef _BOARD_ETHERNET_CONFIG_H_
#define _BOARD_ETHERNET_CONFIG_H_

#include <ti/board/board.h>
#include <ti/board/src/j721s2_evm/include/board_i2c_io_exp.h>
#include <ti/board/src/j721s2_evm/include/board_control.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RGMII_ID_DISABLE_MASK           (0x10U)

typedef struct Board_pruicssMdioInfo
{
    uint32_t mdioBaseAddrs;
    uint8_t  phyAddrs;
}Board_pruicssMdioInfo;

/**
 * \enum emac_mode
 *
 * \brief specifies the available emac mode types.
 */
typedef enum
{
    GMII = 0,
    RMII,
    RGMII,
    SGMII,
    QSGMII,
    XFI,
    QSGMII_SUB
}emac_mode;

/**
 * \brief  Board specific configurations for CPSW2G Main Domain Ethernet PHYs
 *
 * This function takes care of configuring the internal delays for CPSW2G Main Domain
 * Ethernet PHYs
 *
 * \return  BOARD_SOK in case of success or appropriate error code
 */
Board_STATUS Board_cpsw2gMainEthPhyConfig(void);

/**
 * \brief  Board specific configurations for CPSW2G Ethernet PHY
 *
 * This function takes care of configuring the internal delays for MCU gigabit
 * Ethernet PHY
 *
 * \return  BOARD_SOK in case of success or appropriate error code
 */
Board_STATUS Board_cpsw2gEthPhyConfig(void);

/**
 * \brief  Board specific configurations for CPSW2G Ethernet ports
 *
 * This function used to configures CPSW2G Ethernet controllers with the respective modes
 *
 * \return  BOARD_SOK in case of success or appropriate error code
 */
Board_STATUS Board_ethConfigCpsw2g(void);

/**
 * \brief  Board specific configurations for CPSW2G MAIN Domain Ethernet ports
 *
 * This function used to configures CPSW2G MAIN Domain Ethernet controllers with the respective modes
 *
 * \return  BOARD_SOK in case of success or appropriate error code
 */
Board_STATUS Board_ethConfigCpsw2gMain(void);

/**
 * \brief  Configures the CPSW2G Subsytem for RGMII mode
 *
 * \param  portNum [IN]    EMAC port number
 * \param  mode    [IN]    Mode selection for the specified port number
 *                         00 - GMII
 *                         01 - RMII
 *                         10 - RGMII
 *                         11 - SGMII
 *
 * \return  BOARD_SOK in case of success or appropriate error code
 */
Board_STATUS Board_cpsw2gMacModeConfig(uint8_t mode);

/**
 * \brief  Configures the CPSW2G Main Subsytem for RGMII and RMII mode
 *
 * \param  mode    [IN]    Mode selection for the specified port number
 *                         000 - GMII
 *                         001 - RMII
 *                         010 - RGMII
 *                         011 - SGMII
 *                         100 - QSGMII
 *
 * \return  BOARD_SOK in case of success or appropriate error code
 */
Board_STATUS Board_cpsw2gMainEthConfig(uint8_t mode);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _BOARD_ETHERNET_CONFIG_H_ */
