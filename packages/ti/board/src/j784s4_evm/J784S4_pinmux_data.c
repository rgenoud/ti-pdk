/**
* Note: This file was auto-generated by TI PinMux on 6/16/2022 at 8:34:58 AM.
*
* \file  J784S4_pinmux_data.c
*
* \brief  This file contains the pin mux configurations for the boards.
*         These are prepared based on how the peripherals are extended on
*         the boards.
*
* \copyright Copyright (CU) 2022 Texas Instruments Incorporated -
*             http://www.ti.com/
*/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "J784S4_pinmux.h"

/** Peripheral Pin Configurations */


static pinmuxPerCfg_t gCpsw2g0PinCfg[] =
{
    /* MyCPSW2G -> MDIO0_MDC -> AD38 */
    {
        PIN_MCASP1_AXR0, PIN_MODE(6) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyCPSW2G -> MDIO0_MDIO -> AD33 */
    {
        PIN_MCASP1_AFSX, PIN_MODE(6) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyCPSW2G -> RGMII1_RD0 -> AC34 */
    {
        PIN_MCASP1_ACLKX, PIN_MODE(6) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyCPSW2G -> RGMII1_RD1 -> AD34 */
    {
        PIN_MCASP0_AXR12, PIN_MODE(6) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyCPSW2G -> RGMII1_RD2 -> AJ36 */
    {
        PIN_MCASP0_AXR13, PIN_MODE(6) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyCPSW2G -> RGMII1_RD3 -> AF34 */
    {
        PIN_MCASP0_AXR14, PIN_MODE(6) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyCPSW2G -> RGMII1_RXC -> AL33 */
    {
        PIN_MCASP1_AXR3, PIN_MODE(6) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyCPSW2G -> RGMII1_RX_CTL -> AE34 */
    {
        PIN_MCASP0_AXR15, PIN_MODE(6) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyCPSW2G -> RGMII1_TD0 -> AE35 */
    {
        PIN_MCASP0_AXR7, PIN_MODE(6) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyCPSW2G -> RGMII1_TD1 -> AC35 */
    {
        PIN_MCASP0_AXR8, PIN_MODE(6) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyCPSW2G -> RGMII1_TD2 -> AG35 */
    {
        PIN_MCASP0_AXR9, PIN_MODE(6) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyCPSW2G -> RGMII1_TD3 -> AH36 */
    {
        PIN_MCASP0_AXR10, PIN_MODE(6) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyCPSW2G -> RGMII1_TXC -> AL34 */
    {
        PIN_MCASP1_AXR4, PIN_MODE(6) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyCPSW2G -> RGMII1_TX_CTL -> AF35 */
    {
        PIN_MCASP0_AXR11, PIN_MODE(6) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gCpsw2gPinCfg[] =
{
    {0, 1, gCpsw2g0PinCfg},
    {PINMUX_END}
};


static pinmuxPerCfg_t gCpsw9x0PinCfg[] =
{
    /* MyCPSW9X -> MDIO1_MDIO -> AC36 */
    {
        PIN_MCASP2_AXR0, PIN_MODE(4) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyCPSW9X -> MDIO1_MDC -> AE37 */
    {
        PIN_MCASP2_AFSX, PIN_MODE(4) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gCpsw9xPinCfg[] =
{
    {0, 1, gCpsw9x0PinCfg},
    {PINMUX_END}
};


static pinmuxPerCfg_t gDp0PinCfg[] =
{
    /* MyDP -> DP0_HPD -> AM37 */
    {
        PIN_SPI0_CS0, PIN_MODE(12) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gDpPinCfg[] =
{
    {0, 1, gDp0PinCfg},
    {PINMUX_END}
};


static pinmuxPerCfg_t gGpio_vddshv22PinCfg[] =
{
    /* MyGPIO_VDDSHV2 -> GPIO0_3 -> AF33 */
    {
        PIN_MCAN13_TX, PIN_MODE(7) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyGPIO_VDDSHV2 -> GPIO0_8 -> AJ35 */
    {
        PIN_MCAN15_RX, PIN_MODE(7) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyGPIO_VDDSHV2 -> GPIO0_11 -> AL32 */
    {
        PIN_GPIO0_11, PIN_MODE(7) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyGPIO_VDDSHV2 -> GPIO0_18 -> AK33 */
    {
        PIN_MCASP0_AXR2, PIN_MODE(7) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyGPIO_VDDSHV2 -> GPIO0_21 -> AD37 */
    {
        PIN_MCASP2_ACLKX, PIN_MODE(7) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyGPIO_VDDSHV2 -> GPIO0_26 -> AE38 */
    {
        PIN_MCAN0_RX, PIN_MODE(7) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyGPIO_VDDSHV2 -> GPIO0_28 -> AH38 */
    {
        PIN_MCAN1_RX, PIN_MODE(7) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gGpio_vddshv2PinCfg[] =
{
    {2, 1, gGpio_vddshv22PinCfg},
    {PINMUX_END}
};


static pinmuxPerCfg_t gI2c4PinCfg[] =
{
    /* MyI2C4 -> I2C4_SCL -> AG33 */
    {
        PIN_MCAN14_TX, PIN_MODE(8) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyI2C4 -> I2C4_SDA -> AH33 */
    {
        PIN_MCAN13_RX, PIN_MODE(8) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxPerCfg_t gI2c5PinCfg[] =
{
    /* MyI2C5 -> I2C5_SCL -> AG34 */
    {
        PIN_MCAN15_TX, PIN_MODE(8) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyI2C5 -> I2C5_SDA -> AK36 */
    {
        PIN_MCAN14_RX, PIN_MODE(8) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxPerCfg_t gI2c3PinCfg[] =
{
    /* MyI2C3 -> I2C3_SCL -> AF38 */
    {
        PIN_MCAN0_TX, PIN_MODE(13) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyI2C3 -> I2C3_SDA -> AE36 */
    {
        PIN_MCASP2_AXR1, PIN_MODE(13) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxPerCfg_t gI2c1PinCfg[] =
{
    /* MyI2C1 -> I2C1_SCL -> AD36 */
    {
        PIN_ECAP0_IN_APWM_OUT, PIN_MODE(13) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyI2C1 -> I2C1_SDA -> AJ32 */
    {
        PIN_EXT_REFCLK1, PIN_MODE(13) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxPerCfg_t gI2c0PinCfg[] =
{
    /* MyI2C0 -> I2C0_SCL -> AN36 */
    {
        PIN_I2C0_SCL, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyI2C0 -> I2C0_SDA -> AP37 */
    {
        PIN_I2C0_SDA, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gI2cPinCfg[] =
{
    {4, 1, gI2c4PinCfg},
    {5, 1, gI2c5PinCfg},
    {3, 1, gI2c3PinCfg},
    {1, 1, gI2c1PinCfg},
    {0, 1, gI2c0PinCfg},
    {PINMUX_END}
};


static pinmuxPerCfg_t gJtag_vddshv00PinCfg[] =
{
    /* MyJTAG_VDDSHV0 -> TDI -> AL37 */
    {
        PIN_TDI, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyJTAG_VDDSHV0 -> TDO -> AL35 */
    {
        PIN_TDO, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyJTAG_VDDSHV0 -> TMS -> AL36 */
    {
        PIN_TMS, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gJtag_vddshv0PinCfg[] =
{
    {0, 1, gJtag_vddshv00PinCfg},
    {PINMUX_END}
};


static pinmuxPerCfg_t gMcan6PinCfg[] =
{
    /* MyMCAN16 -> MCAN16_RX -> AE33 */
    {
        PIN_MCAN16_RX, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCAN16 -> MCAN16_TX -> AH34 */
    {
        PIN_MCAN16_TX, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxPerCfg_t gMcan5PinCfg[] =
{
    /* MyMCAN5 -> MCAN5_RX -> AK38 */
    {
        PIN_MCASP0_AFSX, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCAN5 -> MCAN5_TX -> AK35 */
    {
        PIN_MCASP0_ACLKX, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxPerCfg_t gMcan3PinCfg[] =
{
    /* MyMCAN3 -> MCAN3_RX -> AK34 */
    {
        PIN_MCASP0_AXR4, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCAN3 -> MCAN3_TX -> AJ38 */
    {
        PIN_MCASP0_AXR3, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxPerCfg_t gMcan4PinCfg[] =
{
    /* MyMCAN4 -> MCAN4_RX -> AF36 */
    {
        PIN_MCASP0_AXR6, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCAN4 -> MCAN4_TX -> AG38 */
    {
        PIN_MCASP0_AXR5, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gMcanPinCfg[] =
{
    {6, 1, gMcan6PinCfg},
    {5, 1, gMcan5PinCfg},
    {3, 1, gMcan3PinCfg},
    {4, 1, gMcan4PinCfg},
    {PINMUX_END}
};


static pinmuxPerCfg_t gMcu_adc0PinCfg[] =
{
    /* MyMCU_ADC0 -> MCU_ADC0_AIN0 -> P36 */
    {
        PIN_MCU_ADC0_AIN0, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_ADC0 -> MCU_ADC0_AIN1 -> V36 */
    {
        PIN_MCU_ADC0_AIN1, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_ADC0 -> MCU_ADC0_AIN2 -> T34 */
    {
        PIN_MCU_ADC0_AIN2, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_ADC0 -> MCU_ADC0_AIN3 -> T36 */
    {
        PIN_MCU_ADC0_AIN3, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_ADC0 -> MCU_ADC0_AIN4 -> P34 */
    {
        PIN_MCU_ADC0_AIN4, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_ADC0 -> MCU_ADC0_AIN5 -> R37 */
    {
        PIN_MCU_ADC0_AIN5, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_ADC0 -> MCU_ADC0_AIN6 -> R33 */
    {
        PIN_MCU_ADC0_AIN6, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_ADC0 -> MCU_ADC0_AIN7 -> V38 */
    {
        PIN_MCU_ADC0_AIN7, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gMcu_adcPinCfg[] =
{
    {0, 1, gMcu_adc0PinCfg},
    {PINMUX_END}
};


static pinmuxPerCfg_t gMcu_cpsw2g0PinCfg[] =
{
    /* MyMCU_CPSW2G -> MCU_RGMII1_RD0 -> A35 */
    {
        PIN_MCU_RGMII1_RD0, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_CPSW2G -> MCU_RGMII1_RD1 -> B36 */
    {
        PIN_MCU_RGMII1_RD1, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_CPSW2G -> MCU_RGMII1_RD2 -> C36 */
    {
        PIN_MCU_RGMII1_RD2, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_CPSW2G -> MCU_RGMII1_RD3 -> D36 */
    {
        PIN_MCU_RGMII1_RD3, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_CPSW2G -> MCU_RGMII1_RXC -> B37 */
    {
        PIN_MCU_RGMII1_RXC, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_CPSW2G -> MCU_RGMII1_RX_CTL -> C37 */
    {
        PIN_MCU_RGMII1_RX_CTL, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_CPSW2G -> MCU_RGMII1_TD0 -> D37 */
    {
        PIN_MCU_RGMII1_TD0, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_CPSW2G -> MCU_RGMII1_TD1 -> D38 */
    {
        PIN_MCU_RGMII1_TD1, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_CPSW2G -> MCU_RGMII1_TD2 -> E37 */
    {
        PIN_MCU_RGMII1_TD2, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_CPSW2G -> MCU_RGMII1_TD3 -> E38 */
    {
        PIN_MCU_RGMII1_TD3, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_CPSW2G -> MCU_RGMII1_TXC -> E36 */
    {
        PIN_MCU_RGMII1_TXC, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_CPSW2G -> MCU_RGMII1_TX_CTL -> C38 */
    {
        PIN_MCU_RGMII1_TX_CTL, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gMcu_cpsw2gPinCfg[] =
{
    {0, 1, gMcu_cpsw2g0PinCfg},
    {PINMUX_END}
};


static pinmuxPerCfg_t gMcu_i2c0PinCfg[] =
{
    /* MyMCU_I2C0 -> MCU_I2C0_SCL -> M35 */
    {
        PIN_MCU_I2C0_SCL, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_I2C0 -> MCU_I2C0_SDA -> G34 */
    {
        PIN_MCU_I2C0_SDA, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gMcu_i2cPinCfg[] =
{
    {0, 1, gMcu_i2c0PinCfg},
    {PINMUX_END}
};


static pinmuxPerCfg_t gMcu_i3c0PinCfg[] =
{
    /* MyMCU_I3C -> MCU_I3C0_SCL -> L35 */
    {
        PIN_WKUP_GPIO0_8, PIN_MODE(3) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_I3C -> MCU_I3C0_SDA -> L34 */
    {
        PIN_WKUP_GPIO0_9, PIN_MODE(3) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_I3C -> MCU_I3C0_SDAPULLEN -> M38 */
    {
        PIN_WKUP_GPIO0_11, PIN_MODE(5) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gMcu_i3cPinCfg[] =
{
    {0, 1, gMcu_i3c0PinCfg},
    {PINMUX_END}
};


static pinmuxPerCfg_t gMcu_mcan0PinCfg[] =
{
    /* MyMCU_MCAN0 -> MCU_MCAN0_RX -> F38 */
    {
        PIN_MCU_MCAN0_RX, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_MCAN0 -> MCU_MCAN0_TX -> K33 */
    {
        PIN_MCU_MCAN0_TX, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxPerCfg_t gMcu_mcan1PinCfg[] =
{
    /* MyMCU_MCAN1 -> MCU_MCAN1_RX -> K36 */
    {
        PIN_WKUP_GPIO0_5, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_MCAN1 -> MCU_MCAN1_TX -> H35 */
    {
        PIN_WKUP_GPIO0_4, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gMcu_mcanPinCfg[] =
{
    {0, 1, gMcu_mcan0PinCfg},
    {1, 1, gMcu_mcan1PinCfg},
    {PINMUX_END}
};


static pinmuxPerCfg_t gMcu_mdio0PinCfg[] =
{
    /* MyMCU_MDIO -> MCU_MDIO0_MDC -> A36 */
    {
        PIN_MCU_MDIO0_MDC, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_MDIO -> MCU_MDIO0_MDIO -> B35 */
    {
        PIN_MCU_MDIO0_MDIO, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gMcu_mdioPinCfg[] =
{
    {0, 1, gMcu_mdio0PinCfg},
    {PINMUX_END}
};


static pinmuxPerCfg_t gMcu_ospi0PinCfg[] =
{
    /* MyMCU_OSPI0 -> MCU_OSPI0_CLK -> E32 */
    {
        PIN_MCU_OSPI0_CLK, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_OSPI0 -> MCU_OSPI0_CSn0 -> A32 */
    {
        PIN_MCU_OSPI0_CSN0, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_OSPI0 -> MCU_OSPI0_D0 -> B33 */
    {
        PIN_MCU_OSPI0_D0, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_OSPI0 -> MCU_OSPI0_D1 -> B32 */
    {
        PIN_MCU_OSPI0_D1, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_OSPI0 -> MCU_OSPI0_D2 -> C33 */
    {
        PIN_MCU_OSPI0_D2, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_OSPI0 -> MCU_OSPI0_D3 -> C35 */
    {
        PIN_MCU_OSPI0_D3, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_OSPI0 -> MCU_OSPI0_D4 -> D33 */
    {
        PIN_MCU_OSPI0_D4, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_OSPI0 -> MCU_OSPI0_D5 -> D34 */
    {
        PIN_MCU_OSPI0_D5, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_OSPI0 -> MCU_OSPI0_D6 -> E34 */
    {
        PIN_MCU_OSPI0_D6, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_OSPI0 -> MCU_OSPI0_D7 -> E33 */
    {
        PIN_MCU_OSPI0_D7, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_OSPI0 -> MCU_OSPI0_DQS -> C34 */
    {
        PIN_MCU_OSPI0_DQS, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_OSPI0 -> MCU_OSPI0_ECC_FAIL -> C32 */
    {
        PIN_MCU_OSPI0_CSN3, PIN_MODE(6) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_OSPI0 -> MCU_OSPI0_RESET_OUT0 -> B34 */
    {
        PIN_MCU_OSPI0_CSN2, PIN_MODE(6) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxPerCfg_t gMcu_ospi1PinCfg[] =
{
    /* MyMCU_OSPI1 -> MCU_OSPI1_CLK -> F32 */
    {
        PIN_MCU_OSPI1_CLK, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_OSPI1 -> MCU_OSPI1_CSn0 -> G32 */
    {
        PIN_MCU_OSPI1_CSN0, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_OSPI1 -> MCU_OSPI1_D0 -> E35 */
    {
        PIN_MCU_OSPI1_D0, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_OSPI1 -> MCU_OSPI1_D1 -> D31 */
    {
        PIN_MCU_OSPI1_D1, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_OSPI1 -> MCU_OSPI1_D2 -> G31 */
    {
        PIN_MCU_OSPI1_D2, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_OSPI1 -> MCU_OSPI1_D3 -> F33 */
    {
        PIN_MCU_OSPI1_D3, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_OSPI1 -> MCU_OSPI1_DQS -> F31 */
    {
        PIN_MCU_OSPI1_DQS, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_OSPI1 -> MCU_OSPI1_LBCLKO -> C31 */
    {
        PIN_MCU_OSPI1_LBCLKO, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gMcu_ospiPinCfg[] =
{
    {0, 1, gMcu_ospi0PinCfg},
    {1, 1, gMcu_ospi1PinCfg},
    {PINMUX_END}
};


static pinmuxPerCfg_t gMcu_uart0PinCfg[] =
{
    /* MyMCU_UART0 -> MCU_UART0_CTSn -> H37 */
    {
        PIN_WKUP_GPIO0_14, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_UART0 -> MCU_UART0_RTSn -> K37 */
    {
        PIN_WKUP_GPIO0_15, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_UART0 -> MCU_UART0_RXD -> K38 */
    {
        PIN_WKUP_GPIO0_13, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCU_UART0 -> MCU_UART0_TXD -> J37 */
    {
        PIN_WKUP_GPIO0_12, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gMcu_uartPinCfg[] =
{
    {0, 1, gMcu_uart0PinCfg},
    {PINMUX_END}
};


static pinmuxPerCfg_t gMmcsd1PinCfg[] =
{
    /* MyMMCSD1 -> MMC1_CLK -> AB38 */
    {
        PIN_MMC1_CLK, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMMCSD1 -> MMC1_CMD -> AB36 */
    {
        PIN_MMC1_CMD, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMMCSD1 -> MMC1_DAT0 -> AA33 */
    {
        PIN_MMC1_DAT0, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMMCSD1 -> MMC1_DAT1 -> AB34 */
    {
        PIN_MMC1_DAT1, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMMCSD1 -> MMC1_DAT2 -> AA32 */
    {
        PIN_MMC1_DAT2, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMMCSD1 -> MMC1_DAT3 -> AC38 */
    {
        PIN_MMC1_DAT3, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMMCSD1 -> MMC1_SDCD -> AR38 */
    {
        PIN_TIMER_IO0, PIN_MODE(8) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMMC1 -> MMC1_CLKLB */
    {
        PIN_MMC1_CLKLB, PIN_MODE(0) | \
        ((PIN_PULL_DIRECTION | PIN_INPUT_ENABLE) & (~PIN_PULL_DISABLE))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gMmcsdPinCfg[] =
{
    {1, 1, gMmcsd1PinCfg},
    {PINMUX_END}
};


static pinmuxPerCfg_t gSystem_vddshv00PinCfg[] =
{
    /* MySYSTEM_VDDSHV0 -> EXTINTn -> AN35 */
    {
        PIN_EXTINTN, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MySYSTEM_VDDSHV0 -> RESETSTATz -> AL38 */
    {
        PIN_RESETSTATZ, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MySYSTEM_VDDSHV0 -> SOC_SAFETY_ERRORn -> AM34 */
    {
        PIN_SOC_SAFETY_ERRORN, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gSystem_vddshv0PinCfg[] =
{
    {0, 1, gSystem_vddshv00PinCfg},
    {PINMUX_END}
};


static pinmuxPerCfg_t gSystem_vddshv22PinCfg[] =
{
    /* MySYSTEM_VDDSHV2 -> PMIC_WAKE0n -> AJ34 */
    {
        PIN_PMIC_WAKE0N, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gSystem_vddshv2PinCfg[] =
{
    {2, 1, gSystem_vddshv22PinCfg},
    {PINMUX_END}
};


static pinmuxPerCfg_t gUart5PinCfg[] =
{
    /* MyUART5 -> UART5_RXD -> AJ33 */
    {
        PIN_MCAN12_RX, PIN_MODE(11) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyUART5 -> UART5_TXD -> AG36 */
    {
        PIN_MCAN12_TX, PIN_MODE(11) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxPerCfg_t gUart9PinCfg[] =
{
    /* MyUART9 -> UART9_RXD -> AC32 */
    {
        PIN_MCASP1_AXR1, PIN_MODE(12) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyUART9 -> UART9_TXD -> AC37 */
    {
        PIN_MCASP1_AXR2, PIN_MODE(12) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxPerCfg_t gUart6PinCfg[] =
{
    /* MyUART6 -> UART6_RXD -> AK37 */
    {
        PIN_GPIO0_12, PIN_MODE(12) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyUART6 -> UART6_TXD -> AJ37 */
    {
        PIN_MCAN1_TX, PIN_MODE(11) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxPerCfg_t gUart3PinCfg[] =
{
    /* MyUART3 -> UART3_RXD -> AC33 */
    {
        PIN_MCAN2_TX, PIN_MODE(11) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyUART3 -> UART3_TXD -> AH37 */
    {
        PIN_MCAN2_RX, PIN_MODE(11) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxPerCfg_t gUart2PinCfg[] =
{
    /* MyUART2 -> UART2_RXD -> AM35 */
    {
        PIN_SPI0_D0, PIN_MODE(11) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyUART2 -> UART2_TXD -> AM36 */
    {
        PIN_SPI0_D1, PIN_MODE(11) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxPerCfg_t gUart8PinCfg[] =
{
    /* MyUART8 -> UART8_CTSn -> AF37 */
    {
        PIN_MCASP0_AXR0, PIN_MODE(14) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyUART8 -> UART8_RTSn -> AG37 */
    {
        PIN_MCASP0_AXR1, PIN_MODE(14) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyUART8 -> UART8_RXD -> AP38 */
    {
        PIN_SPI0_CS1, PIN_MODE(11) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyUART8 -> UART8_TXD -> AN38 */
    {
        PIN_SPI0_CLK, PIN_MODE(11) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gUartPinCfg[] =
{
    {5, 1, gUart5PinCfg},
    {9, 1, gUart9PinCfg},
    {6, 1, gUart6PinCfg},
    {3, 1, gUart3PinCfg},
    {2, 1, gUart2PinCfg},
    {8, 1, gUart8PinCfg},
    {PINMUX_END}
};


static pinmuxPerCfg_t gUsb0PinCfg[] =
{
    /* MyUSB0 -> USB0_DRVVBUS -> AN37 */
    {
        PIN_TIMER_IO1, PIN_MODE(6) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gUsbPinCfg[] =
{
    {0, 1, gUsb0PinCfg},
    {PINMUX_END}
};


static pinmuxPerCfg_t gWkup_gpio_vddshv0_mcu0PinCfg[] =
{
    /* MyWKUP_GPIO_VDDSHV0_MCU -> WKUP_GPIO0_0 -> H38 */
    {
        PIN_WKUP_GPIO0_0, PIN_MODE(7) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyWKUP_GPIO_VDDSHV0_MCU -> WKUP_GPIO0_1 -> J34 */
    {
        PIN_WKUP_GPIO0_1, PIN_MODE(7) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyWKUP_GPIO_VDDSHV0_MCU -> WKUP_GPIO0_2 -> J35 */
    {
        PIN_WKUP_GPIO0_2, PIN_MODE(7) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyWKUP_GPIO_VDDSHV0_MCU -> WKUP_GPIO0_3 -> J36 */
    {
        PIN_WKUP_GPIO0_3, PIN_MODE(7) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyWKUP_GPIO_VDDSHV0_MCU -> WKUP_GPIO0_6 -> L37 */
    {
        PIN_WKUP_GPIO0_6, PIN_MODE(7) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyWKUP_GPIO_VDDSHV0_MCU -> WKUP_GPIO0_7 -> L36 */
    {
        PIN_WKUP_GPIO0_7, PIN_MODE(7) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyWKUP_GPIO_VDDSHV0_MCU -> WKUP_GPIO0_54 -> G38 */
    {
        PIN_MCU_SPI0_CLK, PIN_MODE(7) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyWKUP_GPIO_VDDSHV0_MCU -> WKUP_GPIO0_55 -> H36 */
    {
        PIN_MCU_SPI0_D0, PIN_MODE(7) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyWKUP_GPIO_VDDSHV0_MCU -> WKUP_GPIO0_56 -> M37 */
    {
        PIN_WKUP_GPIO0_56, PIN_MODE(7) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyWKUP_GPIO_VDDSHV0_MCU -> WKUP_GPIO0_57 -> M36 */
    {
        PIN_WKUP_GPIO0_57, PIN_MODE(7) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyWKUP_GPIO_VDDSHV0_MCU -> WKUP_GPIO0_66 -> N34 */
    {
        PIN_WKUP_GPIO0_66, PIN_MODE(7) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyWKUP_GPIO_VDDSHV0_MCU -> WKUP_GPIO0_69 -> J38 */
    {
        PIN_MCU_SPI0_D1, PIN_MODE(7) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyWKUP_GPIO_VDDSHV0_MCU -> WKUP_GPIO0_70 -> F37 */
    {
        PIN_MCU_SPI0_CS0, PIN_MODE(7) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gWkup_gpio_vddshv0_mcuPinCfg[] =
{
    {0, 1, gWkup_gpio_vddshv0_mcu0PinCfg},
    {PINMUX_END}
};


static pinmuxPerCfg_t gWkup_gpio_vddshv1_mcu0PinCfg[] =
{
    /* MyWKUP_GPIO_VDDSHV1_MCU -> WKUP_GPIO0_28 -> A33 */
    {
        PIN_MCU_OSPI0_CSN1, PIN_MODE(7) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyWKUP_GPIO_VDDSHV1_MCU -> WKUP_GPIO0_39 -> G33 */
    {
        PIN_MCU_OSPI1_CSN1, PIN_MODE(7) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gWkup_gpio_vddshv1_mcuPinCfg[] =
{
    {0, 1, gWkup_gpio_vddshv1_mcu0PinCfg},
    {PINMUX_END}
};


static pinmuxPerCfg_t gWkup_i2c0PinCfg[] =
{
    /* MyWKUP_I2C0 -> WKUP_I2C0_SCL -> N33 */
    {
        PIN_WKUP_I2C0_SCL, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyWKUP_I2C0 -> WKUP_I2C0_SDA -> N35 */
    {
        PIN_WKUP_I2C0_SDA, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gWkup_i2cPinCfg[] =
{
    {0, 1, gWkup_i2c0PinCfg},
    {PINMUX_END}
};


static pinmuxPerCfg_t gWkup_jtag_vddshv0_mcu0PinCfg[] =
{
    /* MyWKUP_JTAG_VDDSHV0_MCU -> EMU0 -> F35 */
    {
        PIN_EMU0, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyWKUP_JTAG_VDDSHV0_MCU -> EMU1 -> H34 */
    {
        PIN_EMU1, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyWKUP_JTAG_VDDSHV0_MCU -> TCK -> G35 */
    {
        PIN_TCK, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyWKUP_JTAG_VDDSHV0_MCU -> TRSTn -> G37 */
    {
        PIN_TRSTN, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gWkup_jtag_vddshv0_mcuPinCfg[] =
{
    {0, 1, gWkup_jtag_vddshv0_mcu0PinCfg},
    {PINMUX_END}
};


static pinmuxPerCfg_t gWkup_system_mcu0PinCfg[] =
{
    /* MyWKUP_SYSTEM_MCU -> WKUP_LF_CLKIN -> M34 */
    {
        PIN_WKUP_GPIO0_67, PIN_MODE(1) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyWKUP_SYSTEM_MCU -> MCU_RESETSTATz -> F36 */
    {
        PIN_MCU_RESETSTATZ, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyWKUP_SYSTEM_MCU -> MCU_RESETz -> G36 */
    {
        PIN_MCU_RESETZ, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyWKUP_SYSTEM_MCU -> PMIC_POWER_EN1 -> L38 */
    {
        PIN_PMIC_POWER_EN1, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyWKUP_SYSTEM_MCU -> RESET_REQz -> F34 */
    {
        PIN_RESET_REQZ, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyWKUP_SYSTEM_MCU -> PMIC_WAKE1n -> M33 */
    {
        PIN_WKUP_GPIO0_49, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyWKUP_SYSTEM_MCU -> MCU_ADC_EXT_TRIGGER0 -> L33 */
    {
        PIN_WKUP_GPIO0_10, PIN_MODE(3) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gWkup_system_mcuPinCfg[] =
{
    {0, 1, gWkup_system_mcu0PinCfg},
    {PINMUX_END}
};


static pinmuxPerCfg_t gWkup_system_vdda_wkup0PinCfg[] =
{
    /* MyWKUP_SYSTEM_VDDA_WKUP -> MCU_SAFETY_ERRORn -> N36 */
    {
        PIN_MCU_SAFETY_ERRORN, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyWKUP_SYSTEM_VDDA_WKUP -> PORz -> P33 */
    {
        PIN_PORZ, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gWkup_system_vdda_wkupPinCfg[] =
{
    {0, 1, gWkup_system_vdda_wkup0PinCfg},
    {PINMUX_END}
};


static pinmuxPerCfg_t gWkup_uart0PinCfg[] =
{
    /* MyWKUP_UART0 -> WKUP_UART0_RXD -> K35 */
    {
        PIN_WKUP_UART0_RXD, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyWKUP_UART0 -> WKUP_UART0_TXD -> K34 */
    {
        PIN_WKUP_UART0_TXD, PIN_MODE(0) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gWkup_uartPinCfg[] =
{
    {0, 1, gWkup_uart0PinCfg},
    {PINMUX_END}
};


pinmuxBoardCfg_t gJ784S4_MainPinmuxData[] =
{
    {0, gCpsw2gPinCfg},
    {1, gCpsw9xPinCfg},
    {2, gDpPinCfg},
    {3, gGpio_vddshv2PinCfg},
    {4, gI2cPinCfg},
    {5, gJtag_vddshv0PinCfg},
    {6, gMcanPinCfg},
    {7, gMmcsdPinCfg},
    {8, gSystem_vddshv0PinCfg},
    {9, gSystem_vddshv2PinCfg},
    {10, gUartPinCfg},
    {11, gUsbPinCfg},
    {PINMUX_END}
};

pinmuxBoardCfg_t gJ784S4_WkupPinmuxData[] =
{
    {0, gMcu_adcPinCfg},
    {1, gMcu_cpsw2gPinCfg},
    {2, gMcu_i2cPinCfg},
    {3, gMcu_i3cPinCfg},
    {4, gMcu_mcanPinCfg},
    {5, gMcu_mdioPinCfg},
    {6, gMcu_ospiPinCfg},
    {7, gMcu_uartPinCfg},
    {8, gWkup_gpio_vddshv0_mcuPinCfg},
    {9, gWkup_gpio_vddshv1_mcuPinCfg},
    {10, gWkup_i2cPinCfg},
    {11, gWkup_jtag_vddshv0_mcuPinCfg},
    {12, gWkup_system_mcuPinCfg},
    {13, gWkup_system_vdda_wkupPinCfg},
    {14, gWkup_uartPinCfg},
    {PINMUX_END}
};
