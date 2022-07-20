/*
 *  Copyright (c) Texas Instruments Incorporated 2020
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
 */

/*!
 * \file     enet_board_pinmux_j7200_data.c
 *
 * \brief    This file contains the CPSW5G specific pinmux functions for J7200 SOC.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/soc.h>
#include <ti/board/board.h>
#include <ti/board/src/j7200_evm/include/board_pinmux.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/** Peripheral Pin Configurations */

static pinmuxPerCfg_t gDebugss0PinCfg[] =
{
    /* MyDEBUGSS1 -> TMS -> U4 */
    {
        PIN_TMS, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyDEBUGSS1 -> TDI -> F19 */
    {
        PIN_TDI, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyDEBUGSS1 -> TDO -> F21 */
    {
        PIN_TDO, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE) & (~PIN_PULL_DIRECTION & ~PIN_INPUT_ENABLE))
    },
    /* MyDEBUGSS1 -> EMU0 -> A13 */
    {
        PIN_EMU0, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyDEBUGSS1 -> EMU1 -> D12 */
    {
        PIN_EMU1, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyDEBUGSS1 -> TCK -> B15 */
    {
        PIN_TCK, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyDEBUGSS1 -> TRSTn -> B20 */
    {
        PIN_TRSTN, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gDebugssPinCfg[] =
{
    {0, TRUE, gDebugss0PinCfg},
    {PINMUX_END}
};

static pinmuxPerCfg_t gGpio0PinCfg[] =
{
    /* MyGPIO1 -> GPIO0_4 -> AA20 */
    {
        PIN_RMII1_CRS_DV, PIN_MODE(7) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyGPIO1 -> GPIO0_12 -> V16 */
    {
        PIN_MCAN1_RX, PIN_MODE(7) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyGPIO1 -> GPIO0_27 -> T14 */
    {
        PIN_MCAN9_TX, PIN_MODE(7) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyGPIO1 -> GPIO0_28 -> U18 */
    {
        PIN_MCAN9_RX, PIN_MODE(7) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyGPIO1 -> GPIO0_44 -> U13 */
    {
        PIN_GPMC0_CLK, PIN_MODE(7) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyGPIO1 -> GPIO0_55 -> T5 */
    {
        PIN_SPI0_D1, PIN_MODE(7) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gGpioPinCfg[] =
{
    {0, TRUE, gGpio0PinCfg},
    {PINMUX_END}
};

static pinmuxPerCfg_t gI2c0PinCfg[] =
{
    /* MyI2C0 -> I2C0_SCL -> V3 */
    {
        PIN_I2C0_SCL, PIN_MODE(0) | \
        ((PIN_PULL_DIRECTION | PIN_INPUT_ENABLE) & (~PIN_PULL_DISABLE))
    },
    /* MyI2C0 -> I2C0_SDA -> W2 */
    {
        PIN_I2C0_SDA, PIN_MODE(0) | \
        ((PIN_PULL_DIRECTION | PIN_INPUT_ENABLE) & (~PIN_PULL_DISABLE))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gI2cPinCfg[] =
{
    {0, TRUE, gI2c0PinCfg},
    {PINMUX_END}
};

static pinmuxPerCfg_t gSystem0PinCfg[] =
{
    /* MySYSTEM1 -> EXTINTn -> U6 */
    {
        PIN_EXTINTN, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MySYSTEM1 -> RESETSTATz -> U2 */
    {
        PIN_RESETSTATZ, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE) & (~PIN_PULL_DIRECTION & ~PIN_INPUT_ENABLE))
    },
    /* MySYSTEM1 -> SOC_SAFETY_ERRORn -> V2 */
    {
        PIN_SOC_SAFETY_ERRORN, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gSystemPinCfg[] =
{
    {0, TRUE, gSystem0PinCfg},
    {PINMUX_END}
};

static pinmuxPerCfg_t gUart1PinCfg[] =
{
    /* MyUART1 -> UART1_RXD -> T18 */
    {
        PIN_UART1_RXD, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyUART1 -> UART1_TXD -> T20 */
    {
        PIN_UART1_TXD, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE) & (~PIN_PULL_DIRECTION & ~PIN_INPUT_ENABLE))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gUartPinCfg[] =
{
    {2, TRUE, gUart1PinCfg},
    {PINMUX_END}
};

static pinmuxPerCfg_t gWkup_i2c0PinCfg[] =
{
    /* MyWKUP_I2C0 -> WKUP_I2C0_SCL -> F20 */
    {
        PIN_WKUP_I2C0_SCL, PIN_MODE(0) | \
        ((PIN_PULL_DIRECTION | PIN_INPUT_ENABLE) & (~PIN_PULL_DISABLE))
    },
    /* MyWKUP_I2C0 -> WKUP_I2C0_SDA -> H21 */
    {
        PIN_WKUP_I2C0_SDA, PIN_MODE(0) | \
        ((PIN_PULL_DIRECTION | PIN_INPUT_ENABLE) & (~PIN_PULL_DISABLE))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gWkup_i2cPinCfg[] =
{
    {0, TRUE, gWkup_i2c0PinCfg},
    {PINMUX_END}
};

/* Q/SGMII doesn't need config due to dedicated pins and RGMII pins don't
 * interfere with it, so keeping RGMII pins also configured by default */
static pinmuxPerCfg_t gRgmii2PinCfg[] =
{
    /* MyRGMII2 -> RGMII2_RD0 -> Y13 */
    {
        PIN_MCAN11_RX, PIN_MODE(4) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyRGMII2 -> RGMII2_RD1 -> AA15 */
    {
        PIN_MCAN12_TX, PIN_MODE(4) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyRGMII2 -> RGMII2_RD2 -> AA14 */
    {
        PIN_MCAN12_RX, PIN_MODE(4) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyRGMII2 -> RGMII2_RD3 -> AA18 */
    {
        PIN_MCAN13_TX, PIN_MODE(4) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyRGMII2 -> RGMII2_RXC -> Y14 */
    {
        PIN_MCAN11_TX, PIN_MODE(4) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyRGMII2 -> RGMII2_RX_CTL -> AA16 */
    {
        PIN_MCAN13_RX, PIN_MODE(4) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyRGMII2 -> RGMII2_TD0 -> W17 */
    {
        PIN_MCAN15_TX, PIN_MODE(4) | \
        ((PIN_PULL_DISABLE) & (~PIN_PULL_DIRECTION & ~PIN_INPUT_ENABLE))
    },
    /* MyRGMII2 -> RGMII2_TD1 -> W20 */
    {
        PIN_MCAN15_RX, PIN_MODE(4) | \
        ((PIN_PULL_DISABLE) & (~PIN_PULL_DIRECTION & ~PIN_INPUT_ENABLE))
    },
    /* MyRGMII2 -> RGMII2_TD2 -> V14 */
    {
        PIN_UART2_RXD, PIN_MODE(4) | \
        ((PIN_PULL_DISABLE) & (~PIN_PULL_DIRECTION & ~PIN_INPUT_ENABLE))
    },
    /* MyRGMII2 -> RGMII2_TD3 -> V13 */
    {
        PIN_UART2_TXD, PIN_MODE(4) | \
        ((PIN_PULL_DISABLE) & (~PIN_PULL_DIRECTION & ~PIN_INPUT_ENABLE))
    },
    /* MyRGMII2 -> RGMII2_TXC -> W21 */
    {
        PIN_MCAN1_TX, PIN_MODE(4) | \
        ((PIN_PULL_DISABLE) & (~PIN_PULL_DIRECTION & ~PIN_INPUT_ENABLE))
    },
    /* MyRGMII2 -> RGMII2_TX_CTL -> U12 */
    {
        PIN_GPIO0_41, PIN_MODE(4) | \
        ((PIN_PULL_DISABLE) & (~PIN_PULL_DIRECTION & ~PIN_INPUT_ENABLE))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gRgmiiPinCfg[] =
{
    {2, TRUE, gRgmii2PinCfg},
    {PINMUX_END}
};


pinmuxBoardCfg_t gEthFwPinmuxData[] =
{
    {0, gWkup_i2cPinCfg},
    {1, gDebugssPinCfg},
    {2, gGpioPinCfg},
    {3, gI2cPinCfg},
    {4, gSystemPinCfg},
    {5, gUartPinCfg},
    {6, gRgmiiPinCfg},
    {PINMUX_END}
};


