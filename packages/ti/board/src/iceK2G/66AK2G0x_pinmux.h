/**
 * Note: This file was auto-generated by TI PinMux on 8/21/2017 at 3:35:21 PM.
 *
 * \file   66AK2G0x_pinmux.h
 *
 * \brief  This file contains pad configure register offsets and bit-field 
 *         value macros for different configurations,
 *
 *           18   RXACTIVE       Not used in K2G, make sure = 1 anyway
 *           17   PULLTYPESEL    Pad pullup/pulldown type selection
 *           16   PULLUDEN       Pad Pullup/pulldown enable
 *           3:0  MUXMODE        Pad functional signal mux select
 *
 *  \copyright Copyright (CU) 2017 Texas Instruments Incorporated - 
 *             http://www.ti.com/
 */

/**
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
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDINGU, BUT NOT
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
 */

#ifndef _66AK2G0X_PIN_MUX_H_
#define _66AK2G0X_PIN_MUX_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "pinmux.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define PIN_MODE(mode)	                (mode)

/** \brief Active mode configurations */
/** \brief Pull up/down disabled */
#define PIN_PULL_UD_EN	                (0x1U << 16U)
/** \brief Pull UP enable */
#define	PIN_PULL_TYPE_SEL	            (0x1U << 17U)



/** \brief Pad config register offset in control module */
enum pinOffsets
{
	PIN_OFFSET_MIN             = 0x1000U,
	PIN_GPMC_AD0               = 0x1000U,
	PIN_GPMC_AD1               = 0x1004U,
	PIN_GPMC_AD2               = 0x1008U,
	PIN_GPMC_AD3               = 0x100CU,
	PIN_GPMC_AD4               = 0x1010U,
	PIN_GPMC_AD5               = 0x1014U,
	PIN_GPMC_AD6               = 0x1018U,
	PIN_GPMC_AD7               = 0x101CU,
	PIN_GPMC_AD8               = 0x1020U,
	PIN_GPMC_AD9               = 0x1024U,
	PIN_GPMC_AD10              = 0x1028U,
	PIN_GPMC_AD11              = 0x102CU,
	PIN_GPMC_AD12              = 0x1030U,
	PIN_GPMC_AD13              = 0x1034U,
	PIN_GPMC_AD14              = 0x1038U,
	PIN_GPMC_AD15              = 0x103CU,
	PIN_GPMC_CLK               = 0x1040U,
	PIN_GPMC_ADVN_ALE          = 0x1044U,
	PIN_GPMC_OEN_REN           = 0x1048U,
	PIN_GPMC_WEN               = 0x104CU,
	PIN_GPMC_BEN0_CLE          = 0x1050U,
	PIN_GPMC_BEN1              = 0x1054U,
	PIN_GPMC_WAIT0             = 0x1058U,
	PIN_GPMC_WAIT1             = 0x105CU,
	PIN_GPMC_WPN               = 0x1060U,
	PIN_GPMC_DIR               = 0x1064U,
	PIN_GPMC_CSN0              = 0x1068U,
	PIN_GPMC_CSN1              = 0x106CU,
	PIN_GPMC_CSN2              = 0x1070U,
	PIN_GPMC_CSN3              = 0x1074U,
	PIN_DSS_DATA23             = 0x1078U,
	PIN_DSS_DATA22             = 0x107CU,
	PIN_DSS_DATA21             = 0x1080U,
	PIN_DSS_DATA20             = 0x1084U,
	PIN_DSS_DATA19             = 0x1088U,
	PIN_DSS_DATA18             = 0x108CU,
	PIN_DSS_DATA17             = 0x1090U,
	PIN_DSS_DATA16             = 0x1094U,
	PIN_DSS_DATA15             = 0x1098U,
	PIN_DSS_DATA14             = 0x109CU,
	PIN_DSS_DATA13             = 0x10A0U,
	PIN_DSS_DATA12             = 0x10A4U,
	PIN_DSS_DATA11             = 0x10A8U,
	PIN_DSS_DATA10             = 0x10ACU,
	PIN_DSS_DATA9              = 0x10B0U,
	PIN_DSS_DATA8              = 0x10B4U,
	PIN_DSS_DATA7              = 0x10B8U,
	PIN_DSS_DATA6              = 0x10BCU,
	PIN_DSS_DATA5              = 0x10C0U,
	PIN_DSS_DATA4              = 0x10C4U,
	PIN_DSS_DATA3              = 0x10C8U,
	PIN_DSS_DATA2              = 0x10CCU,
	PIN_DSS_DATA1              = 0x10D0U,
	PIN_DSS_DATA0              = 0x10D4U,
	PIN_DSS_VSYNC              = 0x10D8U,
	PIN_DSS_HSYNC              = 0x10DCU,
	PIN_DSS_PCLK               = 0x10E0U,
	PIN_DSS_DE                 = 0x10E4U,
	PIN_DSS_FID                = 0x10E8U,
	PIN_MMC1_DAT7              = 0x10ECU,
	PIN_MMC1_DAT6              = 0x10F0U,
	PIN_MMC1_DAT5              = 0x10F4U,
	PIN_MMC1_DAT4              = 0x10F8U,
	PIN_MMC1_DAT3              = 0x10FCU,
	PIN_MMC1_DAT2              = 0x1100U,
	PIN_MMC1_DAT1              = 0x1104U,
	PIN_MMC1_DAT0              = 0x1108U,
	PIN_MMC1_CLK               = 0x110CU,
	PIN_MMC1_CMD               = 0x1110U,
	PIN_MMC1_SDCD              = 0x1114U,
	PIN_MMC1_SDWP              = 0x1118U,
	PIN_MMC1_POW               = 0x111CU,
	PIN_MII_RXCLK              = 0x1120U,
	PIN_EHRPWM3_A              = 0x1124U,
	PIN_EHRPWM3_B              = 0x1128U,
	PIN_EHRPWM3_SYNCI          = 0x112CU,
	PIN_EHRPWM3_SYNCO          = 0x1130U,
	PIN_MII_RXD3               = 0x1134U,
	PIN_MII_RXD2               = 0x1138U,
	PIN_MII_RXD1               = 0x113CU,
	PIN_MII_RXD0               = 0x1140U,
	PIN_MII_RXDV               = 0x1144U,
	PIN_MII_RXER               = 0x1148U,
	PIN_MII_COL                = 0x114CU,
	PIN_MII_CRS                = 0x1150U,
	PIN_MII_TXCLK              = 0x1154U,
	PIN_SPI3_SCSN0             = 0x1158U,
	PIN_SPI3_SCSN1             = 0x115CU,
	PIN_SPI3_CLK               = 0x1160U,
	PIN_SPI3_SOMI              = 0x1164U,
	PIN_SPI3_SIMO              = 0x1168U,
	PIN_MII_TXD3               = 0x116CU,
	PIN_MII_TXD2               = 0x1170U,
	PIN_MII_TXD1               = 0x1174U,
	PIN_MII_TXD0               = 0x1178U,
	PIN_MII_TXEN               = 0x117CU,
	PIN_MII_TXER               = 0x1180U,
	PIN_RMII_REFCLK            = 0x1184U,
	PIN_MDIO_DATA              = 0x1188U,
	PIN_MDIO_CLK               = 0x118CU,
	PIN_SPI0_SCSN0             = 0x1190U,
	PIN_SPI0_SCSN1             = 0x1194U,
	PIN_SPI0_CLK               = 0x1198U,
	PIN_SPI0_SOMI              = 0x119CU,
	PIN_SPI0_SIMO              = 0x11A0U,
	PIN_SPI1_SCSN0             = 0x11A4U,
	PIN_SPI1_SCSN1             = 0x11A8U,
	PIN_SPI1_CLK               = 0x11ACU,
	PIN_SPI1_SOMI              = 0x11B0U,
	PIN_SPI1_SIMO              = 0x11B4U,
	PIN_SPI2_SCSN0             = 0x11B8U,
	PIN_SPI2_SCSN1             = 0x11BCU,
	PIN_SPI2_CLK               = 0x11C0U,
	PIN_SPI2_SOMI              = 0x11C4U,
	PIN_SPI2_SIMO              = 0x11C8U,
	PIN_UART0_RXD              = 0x11CCU,
	PIN_UART0_TXD              = 0x11D0U,
	PIN_UART0_CTSN             = 0x11D4U,
	PIN_UART0_RTSN             = 0x11D8U,
	PIN_UART1_RXD              = 0x11DCU,
	PIN_UART1_TXD              = 0x11E0U,
	PIN_UART1_CTSN             = 0x11E4U,
	PIN_UART1_RTSN             = 0x11E8U,
	PIN_UART2_RXD              = 0x11ECU,
	PIN_UART2_TXD              = 0x11F0U,
	PIN_UART2_CTSN             = 0x11F4U,
	PIN_UART2_RTSN             = 0x11F8U,
	PIN_DCAN0_TX               = 0x11FCU,
	PIN_DCAN0_RX               = 0x1200U,
	PIN_QSPI_CLK               = 0x1204U,
	PIN_QSPI_RCLK              = 0x1208U,
	PIN_QSPI_D0                = 0x120CU,
	PIN_QSPI_D1                = 0x1210U,
	PIN_QSPI_D2                = 0x1214U,
	PIN_QSPI_D3                = 0x1218U,
	PIN_QSPI_CSN0              = 0x121CU,
	PIN_QSPI_CSN1              = 0x1220U,
	PIN_QSPI_CSN2              = 0x1224U,
	PIN_QSPI_CSN3              = 0x1228U,
	PIN_PR0_PRU0_GPO0          = 0x122CU,
	PIN_PR0_PRU0_GPO1          = 0x1230U,
	PIN_PR0_PRU0_GPO2          = 0x1234U,
	PIN_PR0_PRU0_GPO3          = 0x1238U,
	PIN_PR0_PRU0_GPO4          = 0x123CU,
	PIN_PR0_PRU0_GPO5          = 0x1240U,
	PIN_PR0_PRU0_GPO6          = 0x1244U,
	PIN_PR0_PRU0_GPO7          = 0x1248U,
	PIN_PR0_PRU0_GPO8          = 0x124CU,
	PIN_PR0_PRU0_GPO9          = 0x1250U,
	PIN_PR0_PRU0_GPO10         = 0x1254U,
	PIN_PR0_PRU0_GPO11         = 0x1258U,
	PIN_PR0_PRU0_GPO12         = 0x125CU,
	PIN_PR0_PRU0_GPO13         = 0x1260U,
	PIN_PR0_PRU0_GPO14         = 0x1264U,
	PIN_PR0_PRU0_GPO15         = 0x1268U,
	PIN_PR0_PRU0_GPO16         = 0x126CU,
	PIN_PR0_PRU0_GPO17         = 0x1270U,
	PIN_PR0_PRU0_GPO18         = 0x1274U,
	PIN_PR0_PRU0_GPO19         = 0x1278U,
	PIN_PR0_PRU1_GPO0          = 0x127CU,
	PIN_PR0_PRU1_GPO1          = 0x1280U,
	PIN_PR0_PRU1_GPO2          = 0x1284U,
	PIN_PR0_PRU1_GPO3          = 0x1288U,
	PIN_PR0_PRU1_GPO4          = 0x128CU,
	PIN_PR0_PRU1_GPO5          = 0x1290U,
	PIN_PR0_PRU1_GPO6          = 0x1294U,
	PIN_PR0_PRU1_GPO7          = 0x1298U,
	PIN_PR0_PRU1_GPO8          = 0x129CU,
	PIN_PR0_PRU1_GPO9          = 0x12A0U,
	PIN_PR0_PRU1_GPO10         = 0x12A4U,
	PIN_PR0_PRU1_GPO11         = 0x12A8U,
	PIN_PR0_PRU1_GPO12         = 0x12ACU,
	PIN_PR0_PRU1_GPO13         = 0x12B0U,
	PIN_PR0_PRU1_GPO14         = 0x12B4U,
	PIN_PR0_PRU1_GPO15         = 0x12B8U,
	PIN_PR0_PRU1_GPO16         = 0x12BCU,
	PIN_PR0_PRU1_GPO17         = 0x12C0U,
	PIN_PR0_PRU1_GPO18         = 0x12C4U,
	PIN_PR0_PRU1_GPO19         = 0x12C8U,
	PIN_PR0_MDIO_DATA          = 0x12CCU,
	PIN_PR0_MDIO_MDCLK         = 0x12D0U,
	PIN_PR1_PRU0_GPO0          = 0x12D4U,
	PIN_PR1_PRU0_GPO1          = 0x12D8U,
	PIN_PR1_PRU0_GPO2          = 0x12DCU,
	PIN_PR1_PRU0_GPO3          = 0x12E0U,
	PIN_PR1_PRU0_GPO4          = 0x12E4U,
	PIN_PR1_PRU0_GPO5          = 0x12E8U,
	PIN_PR1_PRU0_GPO6          = 0x12ECU,
	PIN_PR1_PRU0_GPO7          = 0x12F0U,
	PIN_PR1_PRU0_GPO8          = 0x12F4U,
	PIN_PR1_PRU0_GPO9          = 0x12F8U,
	PIN_PR1_PRU0_GPO10         = 0x12FCU,
	PIN_PR1_PRU0_GPO11         = 0x1300U,
	PIN_PR1_PRU0_GPO12         = 0x1304U,
	PIN_PR1_PRU0_GPO13         = 0x1308U,
	PIN_PR1_PRU0_GPO14         = 0x130CU,
	PIN_PR1_PRU0_GPO15         = 0x1310U,
	PIN_PR1_PRU0_GPO16         = 0x1314U,
	PIN_PR1_PRU0_GPO17         = 0x1318U,
	PIN_PR1_PRU0_GPO18         = 0x131CU,
	PIN_PR1_PRU0_GPO19         = 0x1320U,
	PIN_PR1_PRU1_GPO0          = 0x1324U,
	PIN_PR1_PRU1_GPO1          = 0x1328U,
	PIN_PR1_PRU1_GPO2          = 0x132CU,
	PIN_PR1_PRU1_GPO3          = 0x1330U,
	PIN_PR1_PRU1_GPO4          = 0x1334U,
	PIN_PR1_PRU1_GPO5          = 0x1338U,
	PIN_PR1_PRU1_GPO6          = 0x133CU,
	PIN_PR1_PRU1_GPO7          = 0x1340U,
	PIN_PR1_PRU1_GPO8          = 0x1344U,
	PIN_PR1_PRU1_GPO9          = 0x1348U,
	PIN_PR1_PRU1_GPO10         = 0x134CU,
	PIN_PR1_PRU1_GPO11         = 0x1350U,
	PIN_PR1_PRU1_GPO12         = 0x1354U,
	PIN_PR1_PRU1_GPO13         = 0x1358U,
	PIN_PR1_PRU1_GPO14         = 0x135CU,
	PIN_PR1_PRU1_GPO15         = 0x1360U,
	PIN_PR1_PRU1_GPO16         = 0x1364U,
	PIN_PR1_PRU1_GPO17         = 0x1368U,
	PIN_PR1_PRU1_GPO18         = 0x136CU,
	PIN_PR1_PRU1_GPO19         = 0x1370U,
	PIN_PR1_MDIO_DATA          = 0x1374U,
	PIN_PR1_MDIO_MDCLK         = 0x1378U,
	PIN_I2C0_SCL               = 0x137CU,
	PIN_I2C0_SDA               = 0x1380U,
	PIN_I2C1_SCL               = 0x1384U,
	PIN_I2C1_SDA               = 0x1388U,
	PIN_I2C2_SCL               = 0x138CU,
	PIN_I2C2_SDA               = 0x1390U,
	PIN_NMIN                   = 0x1394U,
	PIN_LRESETN                = 0x1398U,
	PIN_LRESETNMIENN           = 0x139CU,
	PIN_RESETSTATN             = 0x13ACU,
	PIN_BOOTCOMPLETE           = 0x13B0U,
	PIN_SYSCLKOUT              = 0x13B4U,
	PIN_OBSPLL_LOCK            = 0x13B8U,
	PIN_RSV13                  = 0x13BCU,
	PIN_RSV14                  = 0x13C0U,
	PIN_RSV15                  = 0x13C4U,
	PIN_RSV16                  = 0x13C8U,
	PIN_RSV17                  = 0x13CCU,
	PIN_RSV18                  = 0x13D0U,
	PIN_USB0_DRVVBUS           = 0x1408U,
	PIN_USB1_DRVVBUS           = 0x140CU,
	PIN_OFFSET_MAX             = 0x140CU
};


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Pinmux configuration data for the board. Auto-generated from 
           Pinmux tool. */
extern pinmuxBoardCfg_t gK2G0xPinmuxData[];

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _66AK2G0X_PIN_MUX_H_ */
