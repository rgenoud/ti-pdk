/*
*
* Copyright (c) 2021 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

#ifndef _MAIN_CTRL_MMR_H_
#define _MAIN_CTRL_MMR_H_
#include <ti/drv/lpm/include/io_retention/mx_mmr_mapping.h>
#define MAIN_CTRL_PID                                      (0x00000)
#define MAIN_CTRL_MMR_CFG0                                 (0x00004)
#define MAIN_CTRL_MMR_CFG1                                 (0x00008)
#define MAIN_CTRL_MAIN_DEVSTAT                             (0x00030)
#define MAIN_CTRL_MAIN_BOOTCFG                             (0x00034)
#define MAIN_CTRL_MAIN_FEATURE_STAT1                       (0x00044)
#define MAIN_CTRL_IPC_SET8                                 (0x00120)
#define MAIN_CTRL_IPC_SET9                                 (0x00124)
#define MAIN_CTRL_IPC_SET16                                (0x00140)
#define MAIN_CTRL_IPC_SET17                                (0x00144)
#define MAIN_CTRL_IPC_CLR8                                 (0x001a0)
#define MAIN_CTRL_IPC_CLR9                                 (0x001a4)
#define MAIN_CTRL_IPC_CLR16                                (0x001c0)
#define MAIN_CTRL_IPC_CLR17                                (0x001c4)
#define MAIN_CTRL_PCI_DEVICE_ID                            (0x00210)
#define MAIN_CTRL_USB_DEVICE_ID                            (0x00220)
#define MAIN_CTRL_SPARE_FUSE0                              (0x00300)
#define MAIN_CTRL_SPARE_FUSE1                              (0x00304)
#define MAIN_CTRL_SPARE_FUSE2                              (0x00308)
#define MAIN_CTRL_SPARE_FUSE3                              (0x0030c)
#define MAIN_CTRL_LOCK0_KICK0                              (0x01008)
#define MAIN_CTRL_LOCK1_KICK0                              (0x05008)
#define MAIN_CTRL_LOCK2_KICK0                              (0x09008)
#define MAIN_CTRL_LOCK3_KICK0                              (0x0d008)
#define MAIN_CTRL_LOCK5_KICK0                              (0x15008)
#define MAIN_CTRL_LOCK7_KICK0                              (0x1d008)
#define MAIN_CTRL_LOCK4_KICK0                              (0x11008)
#define MAIN_CTRL_LOCK0_KICK1                              (0x0100c)
#define MAIN_CTRL_LOCK1_KICK1                              (0x0500c)
#define MAIN_CTRL_LOCK2_KICK1                              (0x0900c)
#define MAIN_CTRL_LOCK3_KICK1                              (0x0d00c)
#define MAIN_CTRL_LOCK5_KICK1                              (0x1500c)
#define MAIN_CTRL_LOCK7_KICK1                              (0x1d00c)
#define MAIN_CTRL_LOCK4_KICK1                              (0x1100c)
#define MAIN_CTRL_INTR_RAW_STAT                            (0x01010)
#define MAIN_CTRL_INTR_STAT_CLR                            (0x01014)
#define MAIN_CTRL_INTR_EN_SET                              (0x01018)
#define MAIN_CTRL_INTR_EN_CLR                              (0x0101c)
#define MAIN_CTRL_EOI                                      (0x01020)
#define MAIN_CTRL_FAULT_ADDR                               (0x01024)
#define MAIN_CTRL_FAULT_TYPE                               (0x01028)
#define MAIN_CTRL_FAULT_ATTR                               (0x0102c)
#define MAIN_CTRL_FAULT_CLR                                (0x01030)
#define MAIN_CTRL_P0_CLAIM0                                (0x01100)
#define MAIN_CTRL_P0_CLAIM1                                (0x01104)
#define MAIN_CTRL_P0_CLAIM2                                (0x01108)
#define MAIN_CTRL_P0_CLAIM3                                (0x0110c)
#define MAIN_CTRL_P0_CLAIM4                                (0x01110)
#define MAIN_CTRL_P0_CLAIM5                                (0x01114)
#define MAIN_CTRL_P0_CLAIM6                                (0x01118)
#define MAIN_CTRL_USB0_CTRL                                (0x04000)
#define MAIN_CTRL_USB0_TRACE_CFG                           (0x04004)
#define MAIN_CTRL_USB0_PHY_CTRL                            (0x04008)
#define MAIN_CTRL_ENET1_CTRL                               (0x04044)
#define MAIN_CTRL_ENET2_CTRL                               (0x04048)
#define MAIN_CTRL_ENET3_CTRL                               (0x0404c)
#define MAIN_CTRL_ENET4_CTRL                               (0x04050)
#define MAIN_CTRL_PCIE1_CTRL                               (0x04074)
#define MAIN_CTRL_SERDES0_LN0_CTRL                         (0x04080)
#define MAIN_CTRL_SERDES0_LN1_CTRL                         (0x04084)
#define MAIN_CTRL_SERDES0_LN2_CTRL                         (0x04088)
#define MAIN_CTRL_SERDES0_LN3_CTRL                         (0x0408c)
#define MAIN_CTRL_SERDES0_CTRL                             (0x040e0)
#define MAIN_CTRL_EPWM0_CTRL                               (0x04140)
#define MAIN_CTRL_EPWM1_CTRL                               (0x04144)
#define MAIN_CTRL_EPWM2_CTRL                               (0x04148)
#define MAIN_CTRL_EPWM3_CTRL                               (0x0414c)
#define MAIN_CTRL_EPWM4_CTRL                               (0x04150)
#define MAIN_CTRL_EPWM5_CTRL                               (0x04154)
#define MAIN_CTRL_SOCA_SEL                                 (0x04160)
#define MAIN_CTRL_SOCB_SEL                                 (0x04164)
#define MAIN_CTRL_EQEP_STAT                                (0x041a0)
#define MAIN_CTRL_SDIO1_CTRL                               (0x041b4)
#define MAIN_CTRL_TIMER0_CTRL                              (0x04200)
#define MAIN_CTRL_TIMER1_CTRL                              (0x04204)
#define MAIN_CTRL_TIMER2_CTRL                              (0x04208)
#define MAIN_CTRL_TIMER3_CTRL                              (0x0420c)
#define MAIN_CTRL_TIMER4_CTRL                              (0x04210)
#define MAIN_CTRL_TIMER5_CTRL                              (0x04214)
#define MAIN_CTRL_TIMER6_CTRL                              (0x04218)
#define MAIN_CTRL_TIMER7_CTRL                              (0x0421c)
#define MAIN_CTRL_TIMER8_CTRL                              (0x04220)
#define MAIN_CTRL_TIMER9_CTRL                              (0x04224)
#define MAIN_CTRL_TIMER10_CTRL                             (0x04228)
#define MAIN_CTRL_TIMER11_CTRL                             (0x0422c)
#define MAIN_CTRL_TIMER12_CTRL                             (0x04230)
#define MAIN_CTRL_TIMER13_CTRL                             (0x04234)
#define MAIN_CTRL_TIMER14_CTRL                             (0x04238)
#define MAIN_CTRL_TIMER15_CTRL                             (0x0423c)
#define MAIN_CTRL_TIMER16_CTRL                             (0x04240)
#define MAIN_CTRL_TIMER17_CTRL                             (0x04244)
#define MAIN_CTRL_TIMER18_CTRL                             (0x04248)
#define MAIN_CTRL_TIMER19_CTRL                             (0x0424c)
#define MAIN_CTRL_TIMERIO0_CTRL                            (0x04280)
#define MAIN_CTRL_TIMERIO1_CTRL                            (0x04284)
#define MAIN_CTRL_TIMERIO2_CTRL                            (0x04288)
#define MAIN_CTRL_TIMERIO3_CTRL                            (0x0428c)
#define MAIN_CTRL_TIMERIO4_CTRL                            (0x04290)
#define MAIN_CTRL_TIMERIO5_CTRL                            (0x04294)
#define MAIN_CTRL_TIMERIO6_CTRL                            (0x04298)
#define MAIN_CTRL_TIMERIO7_CTRL                            (0x0429c)
#define MAIN_CTRL_I3C0_CTRL0                               (0x042c0)
#define MAIN_CTRL_I3C0_CTRL1                               (0x042c4)
#define MAIN_CTRL_I2C0_CTRL                                (0x042e0)
#define MAIN_CTRL_SPARE_CTRL0                              (0x04400)
#define MAIN_CTRL_SPARE_CTRL1                              (0x04404)
#define MAIN_CTRL_SPARE_CTRL2                              (0x04408)
#define MAIN_CTRL_SPARE_CTRL3                              (0x0440c)
#define MAIN_CTRL_SPARE_CTRL4                              (0x04410)
#define MAIN_CTRL_SPARE_CTRL5                              (0x04414)
#define MAIN_CTRL_SPARE_CTRL6                              (0x04418)
#define MAIN_CTRL_SPARE_CTRL7                              (0x0441c)
#define MAIN_CTRL_SPARE_STAT0                              (0x04440)
#define MAIN_CTRL_SPARE_STAT1                              (0x04444)
#define MAIN_CTRL_SPARE_STAT2                              (0x04448)
#define MAIN_CTRL_SPARE_STAT3                              (0x0444c)
#define MAIN_CTRL_SPARE_STAT4                              (0x04450)
#define MAIN_CTRL_SPARE_STAT5                              (0x04454)
#define MAIN_CTRL_SPARE_STAT6                              (0x04458)
#define MAIN_CTRL_SPARE_STAT7                              (0x0445c)
#define MAIN_CTRL_SPARE_TRIM0                              (0x04480)
#define MAIN_CTRL_SPARE_TRIM1                              (0x04484)
#define MAIN_CTRL_SPARE_TRIM2                              (0x04488)
#define MAIN_CTRL_SPARE_TRIM3                              (0x0448c)
#define MAIN_CTRL_MCASP1_CTRL                              (0x04584)
#define MAIN_CTRL_MCASP2_CTRL                              (0x04588)
#define MAIN_CTRL_MAIN_MTOG0_CTRL                          (0x04600)
#define MAIN_CTRL_MAIN_MTOG1_CTRL                          (0x04604)
#define MAIN_CTRL_MAIN_MTOG2_CTRL                          (0x04608)
#define MAIN_CTRL_MAIN_MTOG3_CTRL                          (0x0460c)
#define MAIN_CTRL_MAIN_MTOG4_CTRL                          (0x04610)
#define MAIN_CTRL_MAIN_MTOG5_CTRL                          (0x04614)
#define MAIN_CTRL_MAIN_MTOG10_CTRL                         (0x04628)
#define MAIN_CTRL_MAIN_MTOG11_CTRL                         (0x0462c)
#define MAIN_CTRL_MAIN_MTOG12_CTRL                         (0x04630)
#define MAIN_CTRL_MAIN_MTOG13_CTRL                         (0x04634)
#define MAIN_CTRL_MAIN_MTOG14_CTRL                         (0x04638)
#define MAIN_CTRL_MAIN_MTOG16_CTRL                         (0x04640)
#define MAIN_CTRL_MAIN_MTOG17_CTRL                         (0x04644)
#define MAIN_CTRL_MAIN_MTOG18_CTRL                         (0x04648)
#define MAIN_CTRL_MAIN_MTOG19_CTRL                         (0x0464c)
#define MAIN_CTRL_CC_EN_FLUSH_CTRL                         (0x046c0)
#define MAIN_CTRL_SOCTBR_TRB0_W0                           (0x04800)
#define MAIN_CTRL_SOCTBR_TRB1_W0                           (0x04810)
#define MAIN_CTRL_SOCTBR_TRB2_W0                           (0x04820)
#define MAIN_CTRL_SOCTBR_TRB0_W1                           (0x04804)
#define MAIN_CTRL_SOCTBR_TRB1_W1                           (0x04814)
#define MAIN_CTRL_SOCTBR_TRB2_W1                           (0x04824)
#define MAIN_CTRL_SOCTBR_TRB0_W2                           (0x04808)
#define MAIN_CTRL_SOCTBR_TRB1_W2                           (0x04818)
#define MAIN_CTRL_SOCTBR_TRB2_W2                           (0x04828)
#define MAIN_CTRL_SOCTBR_TRB0_W3                           (0x0480c)
#define MAIN_CTRL_SOCTBR_TRB1_W3                           (0x0481c)
#define MAIN_CTRL_SOCTBR_TRB2_W3                           (0x0482c)
#define MAIN_CTRL_CCTBR_TRB0_W0                            (0x04880)
#define MAIN_CTRL_CCTBR_TRB1_W0                            (0x04890)
#define MAIN_CTRL_CCTBR_TRB2_W0                            (0x048a0)
#define MAIN_CTRL_CCTBR_TRB0_W1                            (0x04884)
#define MAIN_CTRL_CCTBR_TRB1_W1                            (0x04894)
#define MAIN_CTRL_CCTBR_TRB2_W1                            (0x048a4)
#define MAIN_CTRL_CCTBR_TRB0_W2                            (0x04888)
#define MAIN_CTRL_CCTBR_TRB1_W2                            (0x04898)
#define MAIN_CTRL_CCTBR_TRB2_W2                            (0x048a8)
#define MAIN_CTRL_CCTBR_TRB0_W3                            (0x0488c)
#define MAIN_CTRL_CCTBR_TRB1_W3                            (0x0489c)
#define MAIN_CTRL_CCTBR_TRB2_W3                            (0x048ac)
#define MAIN_CTRL_MCUTBR_TRB0_W0                           (0x04900)
#define MAIN_CTRL_MCUTBR_TRB1_W0                           (0x04910)
#define MAIN_CTRL_MCUTBR_TRB2_W0                           (0x04920)
#define MAIN_CTRL_MCUTBR_TRB0_W1                           (0x04904)
#define MAIN_CTRL_MCUTBR_TRB1_W1                           (0x04914)
#define MAIN_CTRL_MCUTBR_TRB2_W1                           (0x04924)
#define MAIN_CTRL_MCUTBR_TRB0_W2                           (0x04908)
#define MAIN_CTRL_MCUTBR_TRB1_W2                           (0x04918)
#define MAIN_CTRL_MCUTBR_TRB2_W2                           (0x04928)
#define MAIN_CTRL_MCUTBR_TRB0_W3                           (0x0490c)
#define MAIN_CTRL_MCUTBR_TRB1_W3                           (0x0491c)
#define MAIN_CTRL_MCUTBR_TRB2_W3                           (0x0492c)
#define MAIN_CTRL_P1_CLAIM0                                (0x05100)
#define MAIN_CTRL_P1_CLAIM1                                (0x05104)
#define MAIN_CTRL_P1_CLAIM2                                (0x05108)
#define MAIN_CTRL_P1_CLAIM3                                (0x0510c)
#define MAIN_CTRL_P1_CLAIM4                                (0x05110)
#define MAIN_CTRL_P1_CLAIM5                                (0x05114)
#define MAIN_CTRL_P1_CLAIM6                                (0x05118)
#define MAIN_CTRL_P1_CLAIM7                                (0x0511c)
#define MAIN_CTRL_P1_CLAIM8                                (0x05120)
#define MAIN_CTRL_P1_CLAIM9                                (0x05124)
#define MAIN_CTRL_P1_CLAIM10                               (0x05128)
#define MAIN_CTRL_P1_CLAIM11                               (0x0512c)
#define MAIN_CTRL_P1_CLAIM12                               (0x05130)
#define MAIN_CTRL_P1_CLAIM13                               (0x05134)
#define MAIN_CTRL_P1_CLAIM14                               (0x05138)
#define MAIN_CTRL_P1_CLAIM15                               (0x0513c)
#define MAIN_CTRL_P1_CLAIM16                               (0x05140)
#define MAIN_CTRL_P1_CLAIM17                               (0x05144)
#define MAIN_CTRL_P1_CLAIM18                               (0x05148)
#define MAIN_CTRL_OBSCLK0_CTRL                             (0x08000)
#define MAIN_CTRL_OBSCLK1_CTRL                             (0x08004)
#define MAIN_CTRL_CLKOUT_CTRL                              (0x08010)
#define MAIN_CTRL_GTC_CLKSEL                               (0x08030)
#define MAIN_CTRL_EFUSE_CLKSEL                             (0x0803c)
#define MAIN_CTRL_PCIE1_CLKSEL                             (0x08084)
#define MAIN_CTRL_CPSW_CLKSEL                              (0x08090)
#define MAIN_CTRL_NAVSS_CLKSEL                             (0x08098)
#define MAIN_CTRL_EMMC0_CLKSEL                             (0x080b0)
#define MAIN_CTRL_EMMC1_CLKSEL                             (0x080b4)
#define MAIN_CTRL_GPMC_CLKSEL                              (0x080d0)
#define MAIN_CTRL_USB0_CLKSEL                              (0x080e0)
#define MAIN_CTRL_TIMER0_CLKSEL                            (0x08100)
#define MAIN_CTRL_TIMER1_CLKSEL                            (0x08104)
#define MAIN_CTRL_TIMER2_CLKSEL                            (0x08108)
#define MAIN_CTRL_TIMER3_CLKSEL                            (0x0810c)
#define MAIN_CTRL_TIMER4_CLKSEL                            (0x08110)
#define MAIN_CTRL_TIMER5_CLKSEL                            (0x08114)
#define MAIN_CTRL_TIMER6_CLKSEL                            (0x08118)
#define MAIN_CTRL_TIMER7_CLKSEL                            (0x0811c)
#define MAIN_CTRL_TIMER8_CLKSEL                            (0x08120)
#define MAIN_CTRL_TIMER9_CLKSEL                            (0x08124)
#define MAIN_CTRL_TIMER10_CLKSEL                           (0x08128)
#define MAIN_CTRL_TIMER11_CLKSEL                           (0x0812c)
#define MAIN_CTRL_TIMER12_CLKSEL                           (0x08130)
#define MAIN_CTRL_TIMER13_CLKSEL                           (0x08134)
#define MAIN_CTRL_TIMER14_CLKSEL                           (0x08138)
#define MAIN_CTRL_TIMER15_CLKSEL                           (0x0813c)
#define MAIN_CTRL_TIMER16_CLKSEL                           (0x08140)
#define MAIN_CTRL_TIMER17_CLKSEL                           (0x08144)
#define MAIN_CTRL_TIMER18_CLKSEL                           (0x08148)
#define MAIN_CTRL_TIMER19_CLKSEL                           (0x0814c)
#define MAIN_CTRL_SPI0_CLKSEL                              (0x08190)
#define MAIN_CTRL_SPI1_CLKSEL                              (0x08194)
#define MAIN_CTRL_SPI2_CLKSEL                              (0x08198)
#define MAIN_CTRL_SPI3_CLKSEL                              (0x0819c)
#define MAIN_CTRL_SPI5_CLKSEL                              (0x081a4)
#define MAIN_CTRL_SPI6_CLKSEL                              (0x081a8)
#define MAIN_CTRL_SPI7_CLKSEL                              (0x081ac)
#define MAIN_CTRL_USART0_CLK_CTRL                          (0x081c0)
#define MAIN_CTRL_USART1_CLK_CTRL                          (0x081c4)
#define MAIN_CTRL_USART2_CLK_CTRL                          (0x081c8)
#define MAIN_CTRL_USART3_CLK_CTRL                          (0x081cc)
#define MAIN_CTRL_USART4_CLK_CTRL                          (0x081d0)
#define MAIN_CTRL_USART5_CLK_CTRL                          (0x081d4)
#define MAIN_CTRL_USART6_CLK_CTRL                          (0x081d8)
#define MAIN_CTRL_USART7_CLK_CTRL                          (0x081dc)
#define MAIN_CTRL_USART8_CLK_CTRL                          (0x081e0)
#define MAIN_CTRL_USART9_CLK_CTRL                          (0x081e4)
#define MAIN_CTRL_MCASP0_CLKSEL                            (0x08200)
#define MAIN_CTRL_MCASP1_CLKSEL                            (0x08204)
#define MAIN_CTRL_MCASP2_CLKSEL                            (0x08208)
#define MAIN_CTRL_MCASP0_AHCLKSEL                          (0x08240)
#define MAIN_CTRL_MCASP1_AHCLKSEL                          (0x08244)
#define MAIN_CTRL_MCASP2_AHCLKSEL                          (0x08248)
#define MAIN_CTRL_ATL_BWS0_SEL                             (0x082a0)
#define MAIN_CTRL_ATL_BWS1_SEL                             (0x082a4)
#define MAIN_CTRL_ATL_BWS2_SEL                             (0x082a8)
#define MAIN_CTRL_ATL_BWS3_SEL                             (0x082ac)
#define MAIN_CTRL_ATL_AWS0_SEL                             (0x082b0)
#define MAIN_CTRL_ATL_AWS1_SEL                             (0x082b4)
#define MAIN_CTRL_ATL_AWS2_SEL                             (0x082b8)
#define MAIN_CTRL_ATL_AWS3_SEL                             (0x082bc)
#define MAIN_CTRL_ATL_CLKSEL                               (0x082c0)
#define MAIN_CTRL_AUDIO_REFCLK0_CTRL                       (0x082e0)
#define MAIN_CTRL_AUDIO_REFCLK1_CTRL                       (0x082e4)
#define MAIN_CTRL_WWD0_CLKSEL                              (0x08380)
#define MAIN_CTRL_WWD1_CLKSEL                              (0x08384)
#define MAIN_CTRL_WWD28_CLKSEL                             (0x083f0)
#define MAIN_CTRL_WWD29_CLKSEL                             (0x083f4)
#define MAIN_CTRL_SERDES0_CLKSEL                           (0x08400)
#define MAIN_CTRL_MCAN0_CLKSEL                             (0x08480)
#define MAIN_CTRL_MCAN1_CLKSEL                             (0x08484)
#define MAIN_CTRL_MCAN2_CLKSEL                             (0x08488)
#define MAIN_CTRL_MCAN3_CLKSEL                             (0x0848c)
#define MAIN_CTRL_MCAN4_CLKSEL                             (0x08490)
#define MAIN_CTRL_MCAN5_CLKSEL                             (0x08494)
#define MAIN_CTRL_MCAN6_CLKSEL                             (0x08498)
#define MAIN_CTRL_MCAN7_CLKSEL                             (0x0849c)
#define MAIN_CTRL_MCAN8_CLKSEL                             (0x084a0)
#define MAIN_CTRL_MCAN9_CLKSEL                             (0x084a4)
#define MAIN_CTRL_MCAN10_CLKSEL                            (0x084a8)
#define MAIN_CTRL_MCAN11_CLKSEL                            (0x084ac)
#define MAIN_CTRL_MCAN12_CLKSEL                            (0x084b0)
#define MAIN_CTRL_MCAN13_CLKSEL                            (0x084b4)
#define MAIN_CTRL_MCAN14_CLKSEL                            (0x084b8)
#define MAIN_CTRL_MCAN15_CLKSEL                            (0x084bc)
#define MAIN_CTRL_MCAN16_CLKSEL                            (0x084c0)
#define MAIN_CTRL_MCAN17_CLKSEL                            (0x084c4)
#define MAIN_CTRL_DDR0_RFCLK_TEST0_CLK_CTRL                (0x08500)
#define MAIN_CTRL_DDR0_RFCLK_TEST1_CLK_CTRL                (0x08504)
#define MAIN_CTRL_DDR0_TESTOUT0_CLK_CTRL                   (0x08510)
#define MAIN_CTRL_DDR0_TESTOUT1_CLK_CTRL                   (0x08514)
#define MAIN_CTRL_P2_CLAIM0                                (0x09100)
#define MAIN_CTRL_P2_CLAIM1                                (0x09104)
#define MAIN_CTRL_P2_CLAIM2                                (0x09108)
#define MAIN_CTRL_P2_CLAIM3                                (0x0910c)
#define MAIN_CTRL_P2_CLAIM4                                (0x09110)
#define MAIN_CTRL_P2_CLAIM5                                (0x09114)
#define MAIN_CTRL_P2_CLAIM6                                (0x09118)
#define MAIN_CTRL_P2_CLAIM7                                (0x0911c)
#define MAIN_CTRL_P2_CLAIM8                                (0x09120)
#define MAIN_CTRL_P2_CLAIM9                                (0x09124)
#define MAIN_CTRL_MCU0_LBIST_CTRL                          (0x0c000)
#define MAIN_CTRL_MCU0_LBIST_PATCOUNT                      (0x0c004)
#define MAIN_CTRL_MCU0_LBIST_SEED0                         (0x0c008)
#define MAIN_CTRL_MCU0_LBIST_SEED1                         (0x0c00c)
#define MAIN_CTRL_MCU0_LBIST_SPARE0                        (0x0c010)
#define MAIN_CTRL_MCU0_LBIST_SPARE1                        (0x0c014)
#define MAIN_CTRL_MCU0_LBIST_STAT                          (0x0c018)
#define MAIN_CTRL_MCU0_LBIST_MISR                          (0x0c01c)
#define MAIN_CTRL_MPU0_LBIST_CTRL                          (0x0c100)
#define MAIN_CTRL_MPU0_LBIST_PATCOUNT                      (0x0c104)
#define MAIN_CTRL_MPU0_LBIST_SEED0                         (0x0c108)
#define MAIN_CTRL_MPU0_LBIST_SEED1                         (0x0c10c)
#define MAIN_CTRL_MPU0_LBIST_SPARE0                        (0x0c110)
#define MAIN_CTRL_MPU0_LBIST_SPARE1                        (0x0c114)
#define MAIN_CTRL_MPU0_LBIST_STAT                          (0x0c118)
#define MAIN_CTRL_MPU0_LBIST_MISR                          (0x0c11c)
#define MAIN_CTRL_MCU0_LBIST_SIG                           (0x0c280)
#define MAIN_CTRL_MPU0_LBIST_SIG                           (0x0c2a0)
#define MAIN_CTRL_FUSE_CRC_CTRL                            (0x0c300)
#define MAIN_CTRL_CHAIN1_CRC_FUSE                          (0x0c304)
#define MAIN_CTRL_CHAIN2_CRC_FUSE                          (0x0c308)
#define MAIN_CTRL_CHAIN3_CRC_FUSE                          (0x0c30c)
#define MAIN_CTRL_CHAIN4_CRC_FUSE                          (0x0c310)
#define MAIN_CTRL_CHAIN5_CRC_FUSE                          (0x0c314)
#define MAIN_CTRL_CHAIN6_CRC_FUSE                          (0x0c318)
#define MAIN_CTRL_CHAIN7_CRC_FUSE                          (0x0c31c)
#define MAIN_CTRL_FUSE_CRC_STAT                            (0x0c320)
#define MAIN_CTRL_CHAIN1_CRC_CALC                          (0x0c324)
#define MAIN_CTRL_CHAIN2_CRC_CALC                          (0x0c328)
#define MAIN_CTRL_CHAIN3_CRC_CALC                          (0x0c32c)
#define MAIN_CTRL_CHAIN4_CRC_CALC                          (0x0c330)
#define MAIN_CTRL_CHAIN5_CRC_CALC                          (0x0c334)
#define MAIN_CTRL_CHAIN6_CRC_CALC                          (0x0c338)
#define MAIN_CTRL_CHAIN7_CRC_CALC                          (0x0c33c)
#define MAIN_CTRL_PBIST_EN                                 (0x0c400)
#define MAIN_CTRL_P3_CLAIM0                                (0x0d100)
#define MAIN_CTRL_P3_CLAIM1                                (0x0d104)
#define MAIN_CTRL_P3_CLAIM2                                (0x0d108)
#define MAIN_CTRL_P3_CLAIM3                                (0x0d10c)
#define MAIN_CTRL_P3_CLAIM4                                (0x0d110)
#define MAIN_CTRL_P3_CLAIM5                                (0x0d114)
#define MAIN_CTRL_P3_CLAIM6                                (0x0d118)
#define MAIN_CTRL_DV_REG0                                  (0x10000)
#define MAIN_CTRL_DV_REG1                                  (0x10004)
#define MAIN_CTRL_DV_REG2                                  (0x10008)
#define MAIN_CTRL_DV_REG3                                  (0x1000c)
#define MAIN_CTRL_DV_REG4                                  (0x10010)
#define MAIN_CTRL_DV_REG5                                  (0x10014)
#define MAIN_CTRL_DV_REG6                                  (0x10018)
#define MAIN_CTRL_DV_REG7                                  (0x1001c)
#define MAIN_CTRL_DV_REG0_SET                              (0x10200)
#define MAIN_CTRL_DV_REG1_SET                              (0x10204)
#define MAIN_CTRL_DV_REG2_SET                              (0x10208)
#define MAIN_CTRL_DV_REG3_SET                              (0x1020c)
#define MAIN_CTRL_DV_REG0_CLR                              (0x10300)
#define MAIN_CTRL_DV_REG1_CLR                              (0x10304)
#define MAIN_CTRL_DV_REG2_CLR                              (0x10308)
#define MAIN_CTRL_DV_REG3_CLR                              (0x1030c)
#define MAIN_CTRL_LED_PID                                  (0x10400)
#define MAIN_CTRL_LED_PIDCTRL                              (0x10404)
#define MAIN_CTRL_AVS_CORE_MRGN_MODE0                      (0x10500)
#define MAIN_CTRL_AVS_CORE_MRGN_MODE1                      (0x10504)
#define MAIN_CTRL_AVS_CORE_MRGN_MODE2                      (0x10508)
#define MAIN_CTRL_AVS_CORE_MRGN_MODE3                      (0x1050c)
#define MAIN_CTRL_AVS_CORE_MRGN_MODE4                      (0x10510)
#define MAIN_CTRL_AVS_CORE_MRGN_MODE5                      (0x10514)
#define MAIN_CTRL_AVS_CORE_MRGN_MODE6                      (0x10518)
#define MAIN_CTRL_AVS_CORE_MRGN_MODE7                      (0x1051c)
#define MAIN_CTRL_AVS_CORE_MRGN_MODE8                      (0x10520)
#define MAIN_CTRL_AVS_CORE_MRGN_MODE9                      (0x10524)
#define MAIN_CTRL_NON_AVS_MRGN_MODE0                       (0x10540)
#define MAIN_CTRL_NON_AVS_MRGN_MODE1                       (0x10544)
#define MAIN_CTRL_NON_AVS_MRGN_MODE2                       (0x10548)
#define MAIN_CTRL_NON_AVS_MRGN_MODE3                       (0x1054c)
#define MAIN_CTRL_NON_AVS_MRGN_MODE4                       (0x10550)
#define MAIN_CTRL_NON_AVS_MRGN_MODE5                       (0x10554)
#define MAIN_CTRL_NON_AVS_MRGN_MODE6                       (0x10558)
#define MAIN_CTRL_NON_AVS_MRGN_MODE7                       (0x1055c)
#define MAIN_CTRL_NON_AVS_MRGN_MODE8                       (0x10560)
#define MAIN_CTRL_NON_AVS_MRGN_MODE9                       (0x10564)
#define MAIN_CTRL_FAST_MRGN_MODE0                          (0x10580)
#define MAIN_CTRL_FAST_MRGN_MODE1                          (0x10584)
#define MAIN_CTRL_FAST_MRGN_MODE2                          (0x10588)
#define MAIN_CTRL_FAST_MRGN_MODE3                          (0x1058c)
#define MAIN_CTRL_FAST_MRGN_MODE4                          (0x10590)
#define MAIN_CTRL_FAST_MRGN_MODE5                          (0x10594)
#define MAIN_CTRL_FAST_MRGN_MODE6                          (0x10598)
#define MAIN_CTRL_FAST_MRGN_MODE7                          (0x1059c)
#define MAIN_CTRL_FAST_MRGN_MODE8                          (0x105a0)
#define MAIN_CTRL_FAST_MRGN_MODE9                          (0x105a4)
#define MAIN_CTRL_P4_CLAIM0                                (0x11100)
#define MAIN_CTRL_P4_CLAIM1                                (0x11104)
#define MAIN_CTRL_P4_CLAIM2                                (0x11108)
#define MAIN_CTRL_P4_CLAIM3                                (0x1110c)
#define MAIN_CTRL_P4_CLAIM4                                (0x11110)
#define MAIN_CTRL_P4_CLAIM5                                (0x11114)
#define MAIN_CTRL_P4_CLAIM6                                (0x11118)
#define MAIN_CTRL_P4_CLAIM7                                (0x1111c)
#define MAIN_CTRL_P4_CLAIM8                                (0x11120)
#define MAIN_CTRL_P4_CLAIM9                                (0x11124)
#define MAIN_CTRL_P4_CLAIM10                               (0x11128)
#define MAIN_CTRL_P4_CLAIM11                               (0x1112c)
#define MAIN_CTRL_CHNG_DDR4_FSP_REQ                        (0x14000)
#define MAIN_CTRL_CHNG_DDR4_FSP_ACK                        (0x14004)
#define MAIN_CTRL_DDR4_FSP_CLKCHNG_REQ                     (0x14080)
#define MAIN_CTRL_DDR4_FSP_CLKCHNG_ACK                     (0x140c0)
#define MAIN_CTRL_P5_CLAIM0                                (0x15100)
#define MAIN_CTRL_P5_CLAIM1                                (0x15104)
#define MAIN_CTRL_PADCONFIG0                               (0x1c000)
#define MAIN_CTRL_PADCONFIG1                               (0x1c004)
#define MAIN_CTRL_PADCONFIG2                               (0x1c008)
#define MAIN_CTRL_PADCONFIG3                               (0x1c00c)
#define MAIN_CTRL_PADCONFIG4                               (0x1c010)
#define MAIN_CTRL_PADCONFIG5                               (0x1c014)
#define MAIN_CTRL_PADCONFIG6                               (0x1c018)
#define MAIN_CTRL_PADCONFIG7                               (0x1c01c)
#define MAIN_CTRL_PADCONFIG8                               (0x1c020)
#define MAIN_CTRL_PADCONFIG9                               (0x1c024)
#define MAIN_CTRL_PADCONFIG10                              (0x1c028)
#define MAIN_CTRL_PADCONFIG11                              (0x1c02c)
#define MAIN_CTRL_PADCONFIG12                              (0x1c030)
#define MAIN_CTRL_PADCONFIG13                              (0x1c034)
#define MAIN_CTRL_PADCONFIG14                              (0x1c038)
#define MAIN_CTRL_PADCONFIG15                              (0x1c03c)
#define MAIN_CTRL_PADCONFIG16                              (0x1c040)
#define MAIN_CTRL_PADCONFIG17                              (0x1c044)
#define MAIN_CTRL_PADCONFIG18                              (0x1c048)
#define MAIN_CTRL_PADCONFIG19                              (0x1c04c)
#define MAIN_CTRL_PADCONFIG20                              (0x1c050)
#define MAIN_CTRL_PADCONFIG21                              (0x1c054)
#define MAIN_CTRL_PADCONFIG22                              (0x1c058)
#define MAIN_CTRL_PADCONFIG23                              (0x1c05c)
#define MAIN_CTRL_PADCONFIG24                              (0x1c060)
#define MAIN_CTRL_PADCONFIG25                              (0x1c064)
#define MAIN_CTRL_PADCONFIG26                              (0x1c068)
#define MAIN_CTRL_PADCONFIG27                              (0x1c06c)
#define MAIN_CTRL_PADCONFIG28                              (0x1c070)
#define MAIN_CTRL_PADCONFIG29                              (0x1c074)
#define MAIN_CTRL_PADCONFIG30                              (0x1c078)
#define MAIN_CTRL_PADCONFIG31                              (0x1c07c)
#define MAIN_CTRL_PADCONFIG32                              (0x1c080)
#define MAIN_CTRL_PADCONFIG33                              (0x1c084)
#define MAIN_CTRL_PADCONFIG34                              (0x1c088)
#define MAIN_CTRL_PADCONFIG35                              (0x1c08c)
#define MAIN_CTRL_PADCONFIG36                              (0x1c090)
#define MAIN_CTRL_PADCONFIG37                              (0x1c094)
#define MAIN_CTRL_PADCONFIG38                              (0x1c098)
#define MAIN_CTRL_PADCONFIG39                              (0x1c09c)
#define MAIN_CTRL_PADCONFIG40                              (0x1c0a0)
#define MAIN_CTRL_PADCONFIG41                              (0x1c0a4)
#define MAIN_CTRL_PADCONFIG42                              (0x1c0a8)
#define MAIN_CTRL_PADCONFIG43                              (0x1c0ac)
#define MAIN_CTRL_PADCONFIG44                              (0x1c0b0)
#define MAIN_CTRL_PADCONFIG45                              (0x1c0b4)
#define MAIN_CTRL_PADCONFIG46                              (0x1c0b8)
#define MAIN_CTRL_PADCONFIG47                              (0x1c0bc)
#define MAIN_CTRL_PADCONFIG48                              (0x1c0c0)
#define MAIN_CTRL_PADCONFIG49                              (0x1c0c4)
#define MAIN_CTRL_PADCONFIG50                              (0x1c0c8)
#define MAIN_CTRL_PADCONFIG51                              (0x1c0cc)
#define MAIN_CTRL_PADCONFIG52                              (0x1c0d0)
#define MAIN_CTRL_PADCONFIG53                              (0x1c0d4)
#define MAIN_CTRL_PADCONFIG54                              (0x1c0d8)
#define MAIN_CTRL_PADCONFIG55                              (0x1c0dc)
#define MAIN_CTRL_PADCONFIG56                              (0x1c0e0)
#define MAIN_CTRL_PADCONFIG57                              (0x1c0e4)
#define MAIN_CTRL_PADCONFIG58                              (0x1c0e8)
#define MAIN_CTRL_PADCONFIG59                              (0x1c0ec)
#define MAIN_CTRL_PADCONFIG60                              (0x1c0f0)
#define MAIN_CTRL_PADCONFIG61                              (0x1c0f4)
#define MAIN_CTRL_PADCONFIG62                              (0x1c0f8)
#define MAIN_CTRL_PADCONFIG63                              (0x1c0fc)
#define MAIN_CTRL_PADCONFIG64                              (0x1c100)
#define MAIN_CTRL_PADCONFIG65                              (0x1c104)
#define MAIN_CTRL_PADCONFIG66                              (0x1c108)
#define MAIN_CTRL_PADCONFIG68                              (0x1c110)
#define MAIN_CTRL_PADCONFIG71                              (0x1c11c)
#define MAIN_CTRL_PADCONFIG72                              (0x1c120)
#define MAIN_CTRL_PADCONFIG73                              (0x1c124)
#define MAIN_CTRL_PADCONFIG89                              (0x1c164)
#define MAIN_CTRL_PADCONFIG90                              (0x1c168)
#define MAIN_CTRL_PADCONFIG74                              (0x1c128)
#define MAIN_CTRL_PADCONFIG75                              (0x1c12c)
#define MAIN_CTRL_PADCONFIG76                              (0x1c130)
#define MAIN_CTRL_PADCONFIG77                              (0x1c134)
#define MAIN_CTRL_PADCONFIG78                              (0x1c138)
#define MAIN_CTRL_PADCONFIG79                              (0x1c13c)
#define MAIN_CTRL_PADCONFIG80                              (0x1c140)
#define MAIN_CTRL_PADCONFIG81                              (0x1c144)
#define MAIN_CTRL_PADCONFIG82                              (0x1c148)
#define MAIN_CTRL_PADCONFIG83                              (0x1c14c)
#define MAIN_CTRL_PADCONFIG84                              (0x1c150)
#define MAIN_CTRL_PADCONFIG85                              (0x1c154)
#define MAIN_CTRL_PADCONFIG86                              (0x1c158)
#define MAIN_CTRL_PADCONFIG87                              (0x1c15c)
#define MAIN_CTRL_PADCONFIG88                              (0x1c160)
#define MAIN_CTRL_P7_CLAIM0                                (0x1d100)
#define MAIN_CTRL_P7_CLAIM1                                (0x1d104)
#define MAIN_CTRL_P7_CLAIM2                                (0x1d108)
#endif
