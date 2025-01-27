/**
* Note: This file was auto-generated by TI PinMux on 7/8/2020 at 8:33:56 AM.
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


static pinmuxPerCfg_t gMcasp0PinCfg[] =
{
    /* MyMCASP0 -> MCASP0_ACLKR -> U17 */
    {
        PIN_MCAN10_TX, PIN_MODE(12) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCASP0 -> MCASP0_ACLKX -> W15 */
    {
        PIN_MCAN4_TX, PIN_MODE(12) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCASP0 -> MCASP0_AFSX -> Y16 */
    {
        PIN_RMII1_TXD0, PIN_MODE(12) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCASP0 -> MCASP0_AXR0 -> W16 */
    {
        PIN_MCAN3_RX, PIN_MODE(12) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCASP0 -> MCASP0_AXR1 -> Y21 */
    {
        PIN_MCAN3_TX, PIN_MODE(12) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCASP0 -> MCASP0_AXR2 -> Y20 */
    {
        PIN_MCAN4_RX, PIN_MODE(12) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCASP0 -> MCASP0_AXR3 -> AA19 */
    {
        PIN_RMII1_TXD1, PIN_MODE(12) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCASP0 -> MCASP0_AXR4 -> U19 */
    {
        PIN_MCAN8_RX, PIN_MODE(12) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCASP0 -> MCASP0_AXR5 -> T15 */
    {
        PIN_MCAN8_TX, PIN_MODE(12) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCASP0 -> MCASP0_AXR6 -> U20 */
    {
        PIN_MCAN10_RX, PIN_MODE(12) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxPerCfg_t gMcasp1PinCfg[] =
{
    /* MyMCASP1 -> MCASP1_ACLKX -> Y19 */
    {
        PIN_MCAN2_RX, PIN_MODE(12) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCASP1 -> MCASP1_AFSX -> Y18 */
    {
        PIN_MCAN2_TX, PIN_MODE(12) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCASP1 -> MCASP1_AXR0 -> Y17 */
    {
        PIN_RMII1_RX_ER, PIN_MODE(12) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCASP1 -> MCASP1_AXR1 -> AA20 */
    {
        PIN_RMII1_CRS_DV, PIN_MODE(12) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCASP1 -> MCASP1_AXR2 -> Y15 */
    {
        PIN_RMII1_RXD1, PIN_MODE(12) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCASP1 -> MCASP1_AXR3 -> AA17 */
    {
        PIN_RMII1_RXD0, PIN_MODE(12) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCASP1 -> MCASP1_AXR4 -> U16 */
    {
        PIN_MCAN7_TX, PIN_MODE(12) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCASP1 -> MCASP1_AXR5 -> U14 */
    {
        PIN_MCAN6_RX, PIN_MODE(12) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCASP1 -> MCASP1_AXR6 -> T13 */
    {
        PIN_MCAN6_TX, PIN_MODE(12) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    /* MyMCASP1 -> MCASP1_AXR7 -> V19 */
    {
        PIN_MCAN5_RX, PIN_MODE(12) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gMcaspPinCfg[] =
{
    {0, 1, gMcasp0PinCfg},
    {1, 1, gMcasp1PinCfg},
    {PINMUX_END}
};


static pinmuxPerCfg_t gSystem0PinCfg[] =
{
    /* MySYSTEM1 -> AUDIO_EXT_REFCLK1 -> U21 */
    {
        PIN_MCAN16_RX, PIN_MODE(14) | \
        ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION))
    },
    {PINMUX_END}
};

static pinmuxModuleCfg_t gSystemPinCfg[] =
{
    {0, 1, gSystem0PinCfg},
    {PINMUX_END}
};


pinmuxBoardCfg_t gJ7200_MainPinmuxDataAudio[] =
{
    {0, gMcaspPinCfg},
    {1, gSystemPinCfg},
    {PINMUX_END}
};

pinmuxBoardCfg_t gJ7200_WkupPinmuxDataAudio[] =
{
    {PINMUX_END}
};
