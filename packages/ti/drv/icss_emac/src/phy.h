/**
 * \file  phy.h
 *
 * \brief Macros and for EMAC PHY 
 */

/* Copyright (C) {2016-2019} Texas Instruments Incorporated - http://www.ti.com/ 
*
*   Redistribution and use in source and binary forms, with or without 
*   modification, are permitted provided that the following conditions 
*   are met:
*
*     Redistributions of source code must retain the above copyright 
*     notice, this list of conditions and the following disclaimer.
*
*     Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in the 
*     documentation and/or other materials provided with the   
*     distribution.
*
*     Neither the name of Texas Instruments Incorporated nor the names of
*     its contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#ifndef PHY__H
#define PHY__H

#ifdef __cplusplus
extern "C" {
#endif

/* PHY register offset definitions */
#define PHY_BCR                           (0u)
#define PHY_BSR                           (1u)
#define PHY_ID1                           (2u)
#define PHY_ID2                           (3u)
#define PHY_AUTONEG_ADV                   (4u)
#define PHY_LINK_PARTNER_ABLTY            (5u)
#define PHY_1000BT_CONTROL                (9u)
#define PHY_1000BT_STATUS                 (0x0A)

/* PHY status definitions */
#define PHY_ID_SHIFT                      (16u)
#define PHY_SOFTRESET                     (0x8000)
#define PHY_AUTONEG_ENABLE                (0x1000u)
#define PHY_AUTONEG_RESTART               (0x0200u)
#define PHY_AUTONEG_COMPLETE              (0x0020u)
#define PHY_AUTONEG_INCOMPLETE            (0x0000u)
#define PHY_AUTONEG_STATUS                (0x0020u)
#define PHY_AUTONEG_ABLE                  (0x0008u)
#define PHY_LPBK_ENABLE                   (0x4000u)
#define PHY_LINK_STATUS                   (0x0004u)

/* PHY ID. The LSB nibble will vary between different phy revisions */
#define PHY_ID_REV_MASK                   (0x0000000Fu)

/* Pause operations */
#define PHY_PAUSE_NIL                     (0x0000u)
#define PHY_PAUSE_SYM                     (0x0400u)
#define PHY_PAUSE_ASYM                    (0x0800u)
#define PHY_PAUSE_BOTH_SYM_ASYM           (0x0C00u)

/* 1000 Base-T capabilities */
#define PHY_NO_1000BT                     (0x0000u)
#define PHY_1000BT_HD                     (0x0100u)
#define PHY_1000BT_FD                     (0x0200u)

/* 100 Base TX Full Duplex capablity */
#define PHY_100BTX_HD                     (0x0000u)
#define PHY_100BTX_FD                     (0x0100u)

/* 100 Base TX capability */
#define PHY_NO_100BTX                     (0x0000u)
#define PHY_100BTX                        (0x0080u)

/* 10 BaseT duplex capabilities */
#define PHY_10BT_HD                       (0x0000u)
#define PHY_10BT_FD                       (0x0040u)

/* 10 BaseT ability*/
#define PHY_NO_10BT                       (0x0000u)
#define PHY_10BT                          (0x0020u)

#define PHY_LINK_PARTNER_1000BT_FD        (0x0800u)
#define PHY_LINK_PARTNER_1000BT_HD        (0x0400u)

/* Speed settings for BCR register */
#define PHY_SPEED_MASK                    (0xDFBF)
#define PHY_SPEED_10MBPS                  (0x0000u)
#define PHY_SPEED_100MBPS                 (0x2000u)
#define PHY_SPEED_1000MBPS                (0x0040)

/* Duplex settings for BCR register */
#define PHY_FULL_DUPLEX                   (0x0100)


/**
*      Configure PHY in AutoNeg mode
*/
#define  PHY_CONFIG_AUTONEG 0u
/**
*      Force PHY to 100 FullDuplex
*/
#define  PHY_CONFIG_100FD 1u
/**
*      Force PHY to 10 FullDuplex
*/
#define  PHY_CONFIG_10FD 2u
/**
*      Force PHY to 100 halfDuplex
*/
#define  PHY_CONFIG_100HD 3u
/**
*      Force PHY to 100 halfDuplex
*/
#define  PHY_CONFIG_10HD 4u

#define PHY_REG_ADVERTISE_FD100      (1<<8)      /* Indicates FD100 negotiated          */
#define PHY_REG_ADVERTISE_HD100      (1<<7)      /* Indicates HD100 negotiated          */
#define PHY_REG_ADVERTISE_FD10       (1<<6)      /* Indicates FD10 negotiated           */
#define PHY_REG_ADVERTISE_HD10       (1<<5)      /* Indicates HD10 negotiated           */

/* Added back for backward compatibility */
#define TLKPHY_PHYCR_REG                          ((uint32_t)0x19)
#define TLKPHY_LEDCR_REG                          ((uint32_t)0x18)
#define TLKPHY_PHYSCR_REG                         ((uint32_t)0x11)
#define TLKPHY_PHYSTS_REG                         ((uint32_t)0x10U)
#define TLK_SPEED_STATUS                          (((uint32_t)1U) << 1)
#define TLK_DUPLEX_STATUS                         (((uint32_t)1U) << 2)


#ifdef __cplusplus
}
#endif
#endif
