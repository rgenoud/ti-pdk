/**
* Note: This file was auto-generated by TI PinMux on 7/7/2020 at 6:15:36 PM.
*
* \file  J7200_pinmux_data.c
*
* \brief  This file contains the pin mux configurations for the boards.
*         These are prepared based on how the peripherals are extended on
*         the boards.
*
* \copyright Copyright (CU) 2020 Texas Instruments Incorporated -
*             http://www.ti.com/
*/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "J7200_pinmux.h"

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
    {0, 0, gDebugss0PinCfg},
    {PINMUX_END}
};


static pinmuxPerCfg_t gGpio0PinCfg[] =
{
    /* MyGPIO1 -> GPIO0_4 -> AA20 */
    {
        PIN_RMII1_CRS_DV, PIN_MODE(7) | \
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
    {PINMUX_END}
};

static pinmuxModuleCfg_t gGpioPinCfg[] =
{
    {0, 1, gGpio0PinCfg},
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
    {0, 1, gI2c0PinCfg},
    {PINMUX_END}
};


static pinmuxPerCfg_t gMdio0PinCfg[] =
{
    /* MyMDIO0 -> MDIO0_MDC -> W19 */
    {
        PIN_UART8_TXD, PIN_MODE(5) | \
        ((PIN_PULL_DISABLE) & (~PIN_PULL_DIRECTION & ~PIN_INPUT_ENABLE))
    },
    /* MyMDIO0 -> MDIO0_MDIO -> W14 */
    {
        PIN_UART8_RXD, PIN_MODE(5) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gMdioPinCfg[] =
{
    {0, 1, gMdio0PinCfg},
    {PINMUX_END}
};


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
    {2, 1, gRgmii2PinCfg},
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
    {0, 0, gSystem0PinCfg},
    {PINMUX_END}
};


static pinmuxPerCfg_t gUart3PinCfg[] =
{
    /* MyUART3 -> UART3_RXD -> Y18 */
    {
        PIN_MCAN2_TX, PIN_MODE(11) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyUART3 -> UART3_TXD -> Y19 */
    {
        PIN_MCAN2_RX, PIN_MODE(11) | \
        ((PIN_PULL_DISABLE) & (~PIN_PULL_DIRECTION & ~PIN_INPUT_ENABLE))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gUartPinCfg[] =
{
    {3, 1, gUart3PinCfg},
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
    {0, 1, gWkup_i2c0PinCfg},
    {PINMUX_END}
};


pinmuxBoardCfg_t gJ7200_MainPinmuxDataCpsw[] =
{
    {0, gDebugssPinCfg},
    {1, gGpioPinCfg},
    {2, gI2cPinCfg},
    {3, gMdioPinCfg},
    {4, gRgmiiPinCfg},
    {5, gSystemPinCfg},
    {6, gUartPinCfg},
    {PINMUX_END}
};

pinmuxBoardCfg_t gJ7200_WkupPinmuxDataCpsw[] =
{
    {0, gWkup_i2cPinCfg},
    {PINMUX_END}
};
