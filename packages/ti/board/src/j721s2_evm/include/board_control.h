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
 *  \file   board_control.h
 *
 *  \brief  Board control functions header file
 *
 */

#ifndef _BOARD_CONTROL_H_
#define _BOARD_CONTROL_H_

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * Include Files                                                             *
 *****************************************************************************/
#include <ti/csl/csl_types.h>
#include <ti/csl/cslr_device.h>

#include <ti/board/board.h>
#include <ti/csl/tistdtypes.h>
#include <stdio.h>
#include <stdbool.h>

#include "board_internal.h"
#include "board_utils.h"
#include "board_i2c_io_exp.h"

#define BOARD_CTRL_CMD_SET_IO_EXP_PIN_OUT       (0U)

/*
 * Enables Port A to Port B1 routing on SoM Mux which enables below IOs
 *  - Debug Trace Data
 *  - McASP
 */
#define BOARD_CTRL_CMD_SET_SOM_MUX_PORTB1       (1U)

/*
 * Enables Port A to Port B2 routing on SoM Mux which enables below IOs
 *  - UARTs for LIN
 *  - MCAN3, MCAN4, MCAN5
 *  - I2C1, I2C3
 *  - UART8 CTS & RTS
 *  - GPIO0_18 (DP0_HPD)
 *  - GPIO0_23 (GPIO_RGMII1_INT#)
 *  - GPIO0_26 (CSI2_EXP_A_GPIO2)
 *  - GPIO0_28 (CSI2_EXP_A_GPIO4)
 */
#define BOARD_CTRL_CMD_SET_SOM_MUX_PORTB2       (2U)

/*
 * Enables Port A to Port B3 routing on SoM Mux which enables below IOs
 *  - Hyperlink0, Hyperlink1
 *  - SPI5
 */
#define BOARD_CTRL_CMD_SET_SOM_MUX_PORTB3       (3U)

/* Enables the DSI to eDP bridge */
#define BOARD_CTRL_CMD_ENABLE_DSI2DP_BRIDGE     (4U)

#define BOARD_CTRL_CMD_SOM_MUX_PORTB_MASK       (0x7U)
#define BOARD_CTRL_CMD_SOM_MUX_PORTB1_ENABLE    (0x4U)
#define BOARD_CTRL_CMD_SOM_MUX_PORTB2_ENABLE    (0x7U)
#define BOARD_CTRL_CMD_SOM_MUX_PORTB3_ENABLE    (0x3U)

/* Below macros are not supprted on J721S2 but kept for the build compatibility */
#define BOARD_CTRL_CMD_SET_HDMI_MUX             (1)
#define BOARD_CTRL_CMD_SET_HDMI_PD_HIGH         (2U)
#define BOARD_CTRL_CMD_SET_ICSSG_MDIO_MUX       (3U)
#define BOARD_CTRL_CMD_SET_GESI_CPSW_MDIO_MUX   (4U)
#define BOARD_CTRL_CMD_SET_PRG1_RGMII_MDIO_MUX  (5U)
#define BOARD_CTRL_CMD_SET_RS485_UART4_EN_MUX   (6U)
#define BOARD_CTRL_CMD_SET_RMII_DATA_MUX        (7U)

/**
 * \brief Structure to configure the board I2C parameters
 */
typedef struct Board_IoExpCfg_s
{
    /** IO expander slave address */
    uint32_t slaveAddr;
    /** I2C controller instance */
    uint32_t i2cInst;
    /** SoC domain of the I2C controller */
    uint8_t socDomain;
    /** I2C controller interrupt enable/disable flag */
    bool enableIntr;
    /** IO expander type */
    i2cIoExpType_t ioExpType;
    /** IO expander port number */
    i2cIoExpPortNumber_t portNum;
    /** IO expander pin number */
    i2cIoExpPinNumber_t pinNum;
    /** IO expander signal level */
    i2cIoExpSignalLevel_t signalLevel;
} Board_IoExpCfg_t;

/**
 * \brief Board control function
 *
 * \param   cmd  [IN]  Board control command
 * \param   arg  [IN]  Control command argument. 
 *                     Changes based on the command
 *
 * \return   TRUE if the given board is detected else 0.
 *           SoM board will be always connected to the base board.
 *           For SoM boardID return value TRUE indicates dual PMIC
 *           SoM and FALSE indicates alternate PMIC SoM
 *
 */
Board_STATUS Board_control(uint32_t cmd, void *arg);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _BOARD_CONTROL_H_ */
