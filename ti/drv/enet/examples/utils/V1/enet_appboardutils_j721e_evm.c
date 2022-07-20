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
 * \file     enet_appboardutils_j721e_gesi.c
 *
 * \brief    This file contains the board specific utilities for J721E GESI brd.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include <ti/osal/osal.h>
#include <ti/drv/gpio/GPIO.h>
#include <ti/drv/gpio/soc/GPIO_soc.h>
#include <ti/drv/i2c/I2C.h>
#include <ti/drv/i2c/soc/I2C_soc.h>
#include <ti/csl/soc.h>
#include <ti/drv/enet/include/phy/dp83867.h>
#include <ti/board/board.h>
#if defined (SOC_J721E)
#include <ti/board/src/j721e_evm/include/board_pinmux.h>
#include <ti/board/src/j721e_evm/include/board_utils.h>
#include <ti/board/src/j721e_evm/include/board_control.h>
#include <ti/board/src/j721e_evm/include/board_ethernet_config.h>
#include <ti/board/src/j721e_evm/include/board_serdes_cfg.h>
#elif defined (SOC_J7200)
#include <ti/board/src/j7200_evm/include/board_pinmux.h>
#include <ti/board/src/j7200_evm/include/board_utils.h>
#include <ti/board/src/j7200_evm/include/board_control.h>
#include <ti/board/src/j7200_evm/include/board_ethernet_config.h>
#include <ti/board/src/j7200_evm/include/board_serdes_cfg.h>
#else
#error "Invalid SOC"
#endif
#include <ti/drv/enet/enet.h>

#include <ti/drv/enet/examples/utils/include/enet_apputils.h>
#include <ti/drv/enet/examples/utils/include/enet_appboardutils.h>

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

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#if defined(ENETAPPUTILS_GPIO_ALLOWED)
/* GPIO Driver board specific pin configuration structure */
GPIO_PinConfig EnetBoard_gpioPinCfgs[] = {
    GPIO_DEVICE_CONFIG(0, 61) | GPIO_CFG_OUTPUT,
    GPIO_DEVICE_CONFIG(0, 62) | GPIO_CFG_OUTPUT,
};

/* GPIO Driver callback functions */
GPIO_CallbackFxn EnetBoard_gpioCbFunctions[] = {
    NULL
};

/* GPIO Driver configuration structure */
GPIO_v0_Config GPIO_v0_config = {
    EnetBoard_gpioPinCfgs,
    EnetBoard_gpioCbFunctions,
    sizeof(EnetBoard_gpioPinCfgs) / sizeof(GPIO_PinConfig),
    sizeof(EnetBoard_gpioCbFunctions) / sizeof(GPIO_CallbackFxn),
    0,
};
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#if !defined(ENETAPPUTILS_BYPASS_I2C) && defined(BUILD_MCU2_0)
static void EnetBoard_enetExpCfg(void)
{
    Board_STATUS boardStatus;

    /* Release PHY reset. Note this is needed for both SGMII and QSGMII boards */
    boardStatus = Board_cpswEnetExpPhyReset(0U);
    EnetAppUtils_assert(BOARD_SOK == boardStatus);

    if (Board_detectBoard(BOARD_ID_ENET))
    {
        /* Release the COMA_MODE pin */
        boardStatus = Board_cpswEnetExpComaModeCfg(0U);
        EnetAppUtils_assert(BOARD_SOK == boardStatus);
    }
}
#endif

#if !defined(ENETAPPUTILS_BYPASS_QSGMII) && defined(BUILD_MCU2_0)
#if defined (SOC_J721E)
static void EnetBoard_configSierra0Clks(void)
{
    uint32_t moduleId, clkId, clkRateHz;

    /* Configure the required PLLs for SERDES0 */
    moduleId  = TISCI_DEV_SERDES_16G0;
    clkId     = TISCI_DEV_SERDES_16G0_CORE_REF1_CLK;
    clkRateHz = 100000000U;
    EnetAppUtils_clkRateSet(moduleId, clkId, clkRateHz);

    clkId     = TISCI_DEV_SERDES_16G0_CORE_REF_CLK;
    clkRateHz = 100000000U;
    EnetAppUtils_clkRateSet(moduleId, clkId, clkRateHz);
    EnetAppUtils_setDeviceState(moduleId, TISCI_MSG_VALUE_DEVICE_SW_STATE_ON, 0U);
}

#elif defined (SOC_J7200)
static void EnetBoard_configTorrentClks(void)
{
    uint32_t moduleId, clkId, clkRateHz;

     /* Configure the required PLLs for SERDES1 */
    moduleId  = TISCI_DEV_SERDES_10G1;
    clkId     = TISCI_DEV_SERDES_10G1_CORE_REF_CLK;
    clkRateHz = 100000000U;
    EnetAppUtils_clkRateSet(moduleId, clkId, clkRateHz);
    EnetAppUtils_setDeviceState(moduleId, TISCI_MSG_VALUE_DEVICE_SW_STATE_ON, 0U);
}
#endif
#endif

static void EnetBoard_boardInit(Board_initCfg *boardCfg)
{
    Board_STATUS status;
    Board_PinmuxConfig_t pinmuxCfg;

    /* Configure CPSW9G PADs for Ports on the GESI board */
    Board_pinmuxGetCfg(&pinmuxCfg);
#if defined(ENET_ENABLE_ICSSG) && defined(TEST_ICSSG)
    pinmuxCfg.gesiExp = BOARD_PINMUX_GESI_ICSSG;
#else
    pinmuxCfg.gesiExp = BOARD_PINMUX_GESI_CPSW;
#endif
    Board_pinmuxSetCfg(&pinmuxCfg);

#if defined(BUILD_MCU2_0)
    Board_initParams_t initParams;

    Board_getInitParams(&initParams);
    /* mcu2_0 UART instances:
     *  - J721E EVM: UART2
     *  - J7200 EVM: UART3 */
    initParams.uartInst      = ENET_UTILS_MCU2_0_UART_INSTANCE;
    initParams.uartSocDomain = BOARD_SOC_DOMAIN_MAIN;
    /* Use non-exclusive mode in board lib when accessing the module for clock enable
     * to let Linux also access the module */
    initParams.pscMode = BOARD_PSC_DEVICE_MODE_NONEXCLUSIVE;
    Board_setInitParams(&initParams);
#endif

    status = Board_init(*boardCfg);
    EnetAppUtils_assert(status == BOARD_SOK);

    /* Avoid I2C conflicts between EthFw and u-boot */
#if !defined(ENETAPPUTILS_BYPASS_I2C)
    if (Board_detectBoard(BOARD_ID_GESI))
    {
        EnetAppUtils_print("GESI board detected\n");
    }

    if (Board_detectBoard(BOARD_ID_ENET))
    {
        EnetAppUtils_print("QSGMII board detected\n");
    }
#endif
}

/* Hack to run EthFw with Linux
 * We do only limited pinmux configuration and also don't configure RMII and MDIO board muxes
 * as it causes conflict with Linux in using Main domain I2C0. If we need any of configuration on I2c
 * we should ask Linux to do that. Currently we wouldn't use RMII port in EthFw and we don't need MDIO
 * board mux as default is CPSW9G
 */
void EnetBoard_initEthFw(void)
{
    Board_initCfg boardCfg = 0U;
    Board_STATUS status;
    uint32_t i, moduleCnt, appFlags;
    uint32_t clkModuleId[] = { TISCI_DEV_DDR0,
                               TISCI_DEV_TIMER12,
                               TISCI_DEV_TIMER13,
                               TISCI_DEV_UART2, };

    appFlags = 0U;
    moduleCnt = ENET_ARRAYSIZE(clkModuleId);
    for(i = 0; i < moduleCnt; i++)
    {
        EnetAppUtils_setDeviceState(clkModuleId[i],
                                    TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                    appFlags);
    }

    status = EnetBoard_configEthFwPinmux();
    EnetAppUtils_assert(status == BOARD_SOK);

#if defined(ENETAPPUTILS_GPIO_ALLOWED)
    GPIO_init();
    GPIO_write(0, 1);
    GPIO_write(1, 1);
#endif

    /* Setting up UART3 in J7200 requires I2C accesses, so need to be bypassed for mcu2_0 */
#if defined(ENETAPPUTILS_UART_ALLOWED)
    boardCfg |= BOARD_INIT_UART_STDIO;
#endif

#if defined (SOC_J721E)
    boardCfg |= BOARD_INIT_ENETCTRL_CPSW9G;
#elif defined (SOC_J7200)
    boardCfg |= BOARD_INIT_ENETCTRL_CPSW5G;
#endif

    EnetBoard_boardInit(&boardCfg);

#if defined(ENETAPPUTILS_UART_ALLOWED) && defined (SOC_J7200) && defined(BUILD_MCU2_0)
    /* Set SOM's MUX2 for UART3 route */
    status = Board_control(BOARD_CTRL_CMD_SET_SOM_UART_MUX, NULL);
    EnetAppUtils_assert(status == BOARD_SOK);
#endif

#if !defined(ENETAPPUTILS_BYPASS_I2C) && defined(BUILD_MCU2_0)
    /* Configure SGMII/QSGMII expansion board
     * Note - We call below without any check as these functions can be called
     * without daughter board also. They just change the output state of IO
     * expander pins on CP board which goes to daughter board.
     * No negative impact when they are configured without DB. */
    EnetBoard_enetExpCfg();
#endif

#if !defined(ENETAPPUTILS_BYPASS_QSGMII) && defined(BUILD_MCU2_0)
#if defined (SOC_J721E)
    EnetBoard_configSierra0Clks();
#elif defined (SOC_J7200)
    EnetBoard_configTorrentClks();
#endif

    if (Board_detectBoard(BOARD_ID_ENET))
    {
        status = Board_serdesCfgQsgmii();
        EnetAppUtils_assert(status == BOARD_SOK);
    }
#endif
}

uint32_t EnetBoard_getPhyAddr(Enet_Type enetType,
                                      Enet_MacPort portNum)
{
    uint32_t phyAddr = ENETPHY_INVALID_PHYADDR;

    switch (enetType)
    {
        case ENET_CPSW_2G:
            EnetAppUtils_assert(portNum == ENET_MAC_PORT_1);
            phyAddr = 0x00U;
            break;

        case ENET_CPSW_5G:
            switch (portNum)
            {
                case ENET_MAC_PORT_1:
                    /* QSGMII port */
                    phyAddr = 16U;
                    break;

                case ENET_MAC_PORT_2:
                    /* Use RGMII port in GESI board when QSGMII is disabled */
#if defined(ENETAPPUTILS_BYPASS_QSGMII)
                    /* RGMII port */
                    phyAddr = 0U;
#else
                    /* QSGMII port */
                    phyAddr = 17U;
#endif
                    break;

                case ENET_MAC_PORT_3:
                    /* QSGMII port */
                    phyAddr = 18U;
                    break;

                case ENET_MAC_PORT_4:
                    /* QSGMII port */
                    phyAddr = 19U;
                    break;

                default:
                    EnetAppUtils_assert(false);
                    break;
            }

            break;

        case ENET_CPSW_9G:
            switch (portNum)
            {
                case ENET_MAC_PORT_1:
                    /* RGMII port */
                    phyAddr = 12U;
                    break;

                case ENET_MAC_PORT_3:
                    /* RGMII port */
                    phyAddr = 0U;
                    break;

                case ENET_MAC_PORT_4:
                    /* RGMII port */
                    phyAddr = 3U;
                    break;

                case ENET_MAC_PORT_8:
                    /* RGMII port */
                    phyAddr = 15U;
                    break;

                case ENET_MAC_PORT_2:
                    /* QSGMII port */
                    phyAddr = 16U;
                    break;

                case ENET_MAC_PORT_5:
                    /* QSGMII port */
                    phyAddr = 17U;
                    break;

                case ENET_MAC_PORT_6:
                    /* QSGMII port */
                    phyAddr = 18U;
                    break;

                case ENET_MAC_PORT_7:
                    /* QSGMII port */
                    phyAddr = 19U;
                    break;

                default:
                    EnetAppUtils_assert(false);
                    break;
            }

            break;

        default:
            EnetAppUtils_assert(false);
            break;
    }

    return phyAddr;
}

uint32_t EnetBoard_getSgmiiPhyAddr(void)
{
    /* Both Q/SGMII DB and GESI board use MAC port 2, so we can't use generic EnetBoard_getPhyAddr
     * function */
    return 10U;
}

uint32_t EnetBoard_getRmiiPhyAddr(void)
{
    /* Both QSGMII DB and GESI board use MAC port 7, so we can't use generic EnetBoard_getPhyAddr
     * function */
    return 23U;
}

void EnetBoard_setPhyConfigSgmii(Enet_MacPort portNum,
                                         CpswMacPort_Cfg *macCfg,
                                         EnetMacPort_Interface *interface,
                                         EnetPhy_Cfg *phyCfg)
{
    Board_STATUS boardStatus;
    Enet_Type enetType;
    uint32_t instId;

    /* Override the ENET control set by board lib */
#if defined (SOC_J721E)
    EnetAppUtils_assert(portNum == ENET_MAC_PORT_2);
    enetType = ENET_CPSW_9G;
    instId   = 0U;
#elif defined (SOC_J7200)
    EnetAppUtils_assert(portNum == ENET_MAC_PORT_1);
    enetType = ENET_CPSW_5G;
    instId   = 0U;
#endif

    /* Override the ENET control set by board lib */
    EnetBoard_setEnetControl(enetType, instId, portNum, SGMII);

    boardStatus = Board_serdesCfgSgmii();
    EnetAppUtils_assert(boardStatus == BOARD_SOK);

    EnetPhy_initCfg(phyCfg);
    phyCfg->phyAddr = EnetBoard_getSgmiiPhyAddr();
    phyCfg->skipExtendedCfg = true;

    /* RGMII interface type */
    interface->layerType    = ENET_MAC_LAYER_GMII;
    interface->sublayerType = ENET_MAC_SUBLAYER_SERIAL;
    interface->variantType  = ENET_MAC_VARIANT_NONE;

    macCfg->sgmiiMode = ENET_MAC_SGMIIMODE_SGMII_WITH_PHY;
}

void EnetBoard_setPhyConfigQsgmii(Enet_Type enetType,
                                          Enet_MacPort portNum,
                                          CpswMacPort_Cfg *macCfg,
                                          EnetMacPort_Interface *interface,
                                          EnetPhy_Cfg *phyCfg)
{
    Enet_MacPort qsgmiiMain;
#if !defined(ENETAPPUTILS_BYPASS_I2C)
    bool isAlpha = false;

    /*
     * Disable QSGMII on alpha revision EVMs due to ADASVISION-3869 cpsw - mdio
     * instability for QSGMII PHYs on alpha EVM. Issue is resolved in the Beta
     * HW revision.
     */
    isAlpha = Board_isAlpha(BOARD_ID_CP);

    if (isAlpha)
    {
        EnetAppUtils_print("QSGMII DB not supported on alpha revision of EVM\n");
        EnetAppUtils_assert(false);
    }
#endif

#if defined (SOC_J721E)
    /* QSGMII PHYs are routed as follows in QUAD PORT ETH EXP board:
     *  MAC port 1 = QSGMII MAIN
     *  MAC port 4 = QSGMII SUB
     *  MAC port 5 = QSGMII SUB
     *  MAC port 6 = QSGMII SUB
     */
    EnetAppUtils_assert((portNum == ENET_MAC_PORT_2) ||
                        (portNum == ENET_MAC_PORT_5) ||
                        (portNum == ENET_MAC_PORT_6) ||
                        (portNum == ENET_MAC_PORT_7));

    qsgmiiMain = ENET_MAC_PORT_2;
#elif defined (SOC_J7200)
    EnetAppUtils_assert((portNum == ENET_MAC_PORT_1) ||
                        (portNum == ENET_MAC_PORT_2) ||
                        (portNum == ENET_MAC_PORT_3) ||
                        (portNum == ENET_MAC_PORT_4));

    qsgmiiMain = ENET_MAC_PORT_1;
#endif

    EnetPhy_initCfg(phyCfg);
    phyCfg->phyAddr = EnetBoard_getPhyAddr(enetType, portNum);

    /* QSGMII ports */
    /* In QSGMII config each port is independent port just going over one link so
     * we need set up each port just like SGMII ports - autoneg, mac control etc.*/
    interface->layerType    = ENET_MAC_LAYER_GMII;
    interface->variantType  = ENET_MAC_VARIANT_NONE;
    macCfg->sgmiiMode = ENET_MAC_SGMIIMODE_SGMII_WITH_PHY;

    if (portNum == qsgmiiMain)
    {
        interface->sublayerType = ENET_MAC_SUBLAYER_QUAD_SERIAL_MAIN;
    }
    else
    {
        interface->sublayerType = ENET_MAC_SUBLAYER_QUAD_SERIAL_SUB;
    }
}

void EnetBoard_setPhyConfigRmii(Enet_MacPort portNum,
                                        CpswMacPort_Cfg *macCfg,
                                        EnetMacPort_Interface *interface,
                                        EnetPhy_Cfg *phyCfg)
{
    EnetAppUtils_assert(portNum == ENET_MAC_PORT_8);

    /* Override the ENET control set by board lib */
    EnetBoard_setEnetControl(ENET_CPSW_9G, 0U/* instId */, portNum, RMII);

    EnetPhy_initCfg(phyCfg);
    phyCfg->phyAddr = EnetBoard_getRmiiPhyAddr();
    phyCfg->skipExtendedCfg = false;

    /* Mac port 7 on GESI board is RMII port */
    interface->layerType    = ENET_MAC_LAYER_MII;
    interface->sublayerType = ENET_MAC_SUBLAYER_REDUCED;
    interface->variantType  = ENET_MAC_VARIANT_NONE;
}

void EnetBoard_setPhyConfigRgmii(Enet_Type enetType,
                                         Enet_MacPort portNum,
                                         CpswMacPort_Cfg *macCfg,
                                         EnetMacPort_Interface *interface,
                                         EnetPhy_Cfg *phyCfg)
{
    Dp83867_Cfg extendedCfg;

#if defined (SOC_J721E)
    /* RGMII PHYs can be used on the following MAC ports as per board library pinmux:
     *   GESI board: 0, 1, 2, 3
     *  SGMII board: 2, 3, 6, 7
     * QSGMII board: 0, 2, 3, 7
     */
    EnetAppUtils_assert((portNum == ENET_MAC_PORT_1) ||
                        (portNum == ENET_MAC_PORT_2) ||
                        (portNum == ENET_MAC_PORT_3) ||
                        (portNum == ENET_MAC_PORT_4) ||
                        (portNum == ENET_MAC_PORT_7) ||
                        (portNum == ENET_MAC_PORT_8));
#elif defined (SOC_J7200)
    if (enetType == ENET_CPSW_2G)
    {
        EnetAppUtils_assert(portNum == ENET_MAC_PORT_1);
    }
    else if (enetType == ENET_CPSW_5G)
    {
        EnetAppUtils_assert(portNum == ENET_MAC_PORT_2);
        /* Override the ENET control set by board lib */
        EnetBoard_setEnetControl(enetType, 0U/* instId */, portNum, RGMII);
    }
#endif

    EnetPhy_initCfg(phyCfg);

#if defined(SOC_J7200)
    phyCfg->phyAddr = 0U;
#else
    phyCfg->phyAddr = EnetBoard_getPhyAddr(enetType, portNum);
#endif

    /* DP83867 specific configuration */
    Dp83867_initCfg(&extendedCfg);
    extendedCfg.txClkShiftEn  = true;
    extendedCfg.rxClkShiftEn  = true;
    extendedCfg.txFifoDepth   = 4U;
    extendedCfg.idleCntThresh = 4U; /* Improves short cable performance */
    extendedCfg.impedanceInMilliOhms = 35000; /* 35 ohms */
    extendedCfg.gpio0Mode     = DP83867_GPIO0_LED3;
    extendedCfg.ledMode[1]    = DP83867_LED_LINKED_100BTX;
    extendedCfg.ledMode[2]    = DP83867_LED_RXTXACT;
    extendedCfg.ledMode[3]    = DP83867_LED_LINKED_1000BT;

    if ((enetType == ENET_CPSW_9G) || (enetType == ENET_CPSW_5G))
    {
        extendedCfg.txDelayInPs      = 2750U; /* 2.75 ns */
        extendedCfg.rxDelayInPs      = 2500U; /* 2.50 ns */
    }

    EnetPhy_setExtendedCfg(phyCfg,
                              &extendedCfg,
                              sizeof(extendedCfg));

    /* RGMII interface type */
    interface->layerType    = ENET_MAC_LAYER_GMII;
    interface->sublayerType = ENET_MAC_SUBLAYER_REDUCED;
    interface->variantType  = ENET_MAC_VARIANT_NONE;
}

void EnetBoard_setPhyConfig(Enet_Type enetType,
                                    Enet_MacPort portNum,
                                    CpswMacPort_Cfg *macCfg,
                                    EnetMacPort_Interface *interface,
                                    EnetPhy_Cfg *phyCfg)
{
    switch (enetType)
    {
        case ENET_CPSW_2G:
            EnetAppUtils_assert(portNum == ENET_MAC_PORT_1);

            EnetBoard_setPhyConfigRgmii(enetType,
                                                portNum,
                                                macCfg,
                                                interface,
                                                phyCfg);
            break;

        case ENET_CPSW_5G:
            /* Use RGMII port in GESI board when QSGMII is disabled */
#if defined(ENETAPPUTILS_BYPASS_QSGMII)
            if (ENET_MAC_PORT_2 == portNum)
            {
                EnetBoard_setPhyConfigRgmii(enetType,
                                                    portNum,
                                                    macCfg,
                                                    interface,
                                                    phyCfg);
            }
#else
            EnetBoard_setPhyConfigQsgmii(enetType,
                                                 portNum,
                                                 macCfg,
                                                 interface,
                                                 phyCfg);
#endif
            break;

        case ENET_CPSW_9G:
            if ( ENET_MAC_PORT_1 == portNum ||
                 ENET_MAC_PORT_3 == portNum ||
                 ENET_MAC_PORT_4 == portNum ||
                 ENET_MAC_PORT_8 == portNum )
            {
                EnetBoard_setPhyConfigRgmii(enetType,
                                                    portNum,
                                                    macCfg,
                                                    interface,
                                                    phyCfg);
            }
            else
            {
                EnetBoard_setPhyConfigQsgmii(enetType,
                                                     portNum,
                                                     macCfg,
                                                     interface,
                                                     phyCfg);
            }
            break;

        default:
            EnetAppUtils_assert(false);
    }

}

void EnetBoard_setLpbkCfg(bool phyLpbk,
                                  Enet_MacPort portNum,
                                  const EnetMacPort_Interface *interface,
                                  CpswMacPort_Cfg *macCfg,
                                  EnetPhy_Cfg *phyCfg,
                                  EnetMacPort_LinkCfg *linkCfg)
{
    /* Set speed according to the interface type */
    if (interface->layerType == ENET_MAC_LAYER_MII)
    {
        linkCfg->speed = ENET_SPEED_100MBIT;
    }
    else
    {
        linkCfg->speed = ENET_SPEED_1GBIT;
    }

    linkCfg->duplexity = ENET_DUPLEX_FULL;

    /* MAC and PHY loopbacks are mutually exclusive */
    phyCfg->loopbackEn = phyLpbk;
    macCfg->loopbackEn = !phyLpbk;
}

void EnetBoard_setEnetControl(Enet_Type enetType,
                                      uint32_t instId,
                                      Enet_MacPort portNum,
                                      uint32_t modeSel)
{
    int32_t status = BOARD_FAIL;

    switch (enetType)
    {
        case ENET_CPSW_2G:
            status = Board_cpsw2gMacModeConfig(modeSel);
            break;
#if defined (SOC_J7200)
        case ENET_CPSW_5G:
            status = Board_cpsw5gEthConfig(portNum, modeSel);
            break;
#endif
#if defined (SOC_J721E)
        case ENET_CPSW_9G:
            status = Board_cpsw9gEthConfig(portNum, modeSel);
            break;
#endif
        default:
            break;
    }

    EnetAppUtils_assert(status == BOARD_SOK);
}
