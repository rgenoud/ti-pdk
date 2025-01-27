/**
 *  \file   emac_soc.c
 *
 *  \brief  SOC specific EMAC hardware attributes.
 *
 *   This file contains the EMAC hardware attributes like base address and
 *   interrupt ids.
 */

/*
 * Copyright (C) 2014-2017 Texas Instruments Incorporated - http://www.ti.com/
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of
 * its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <ti/drv/emac/soc/emac_soc_v0.h>
#include <ti/drv/emac/emac_drv.h>
#include <ti/csl/csl_emac.h>
#include <ti/csl/csl_mdio.h>
#include <ti/csl/csl_cpsgmii.h>

#define SGMIICFG_RX_CONFIG                  0x00700621
#define SGMIICFG_TX_CONFIG                  0x000108a1
#define SGMIICFG_AUX_CONFIG                 0x00000051


EMAC_HwAttrs_V0 EMACInitCfg[2] =
{
    {
        2,       /* num of dsp cores */
        GMII,       /* mac select */
        EMAC_CONFIG_MODEFLG_FULLDUPLEX         |
        EMAC_CONFIG_MODEFLG_GMIIEN             |
        EMAC_CONFIG_MODEFLG_RMIISPEED,
        -1,  /* Use a valid number from 0 to n-1 to fix the core ID. Where n is number of cores.
            Use -1 for core ID to be updated by the driver dynamically */
        10U,
        CSL_GEM_MACRXINTN,
        11U,
        CSL_GEM_MACTXINTN,
    },
    {
        0U,
        0U,
        0U,
        0U,
        0U,
        0U,
        0U,
        0U,
    },
};

/* EMAC function table pointer */
extern const EMAC_FxnTable EMAC_FxnTable_v0;

/* EMAC configuration structure */
const EMAC_Cfg EMAC_config[2 + 1] =
{
    {
        &EMAC_FxnTable_v0,
        NULL,
        &EMACInitCfg[0],
    },
    {
        &EMAC_FxnTable_v0,
        NULL,
        &EMACInitCfg[1],
    },
    {
        NULL,
        NULL,
        NULL
    }
};

/**
 * \brief  This API sets the SGMII intial configuration
 *
 * \param  void
 *
 * \return 0 success
 *
 */
int32_t EMAC_sgmiiInitCfg(void)
{
        SGMII_Config            SgmiiCfg;
        Uint32                  i;

        SGMII_reset();

        SgmiiCfg.masterEn   = 0x0;                  /* Disable SGMII Master */
        SgmiiCfg.loopbackEn = 0x0;                  /* Disable SGMII loopback */
        SgmiiCfg.txConfig   = SGMIICFG_TX_CONFIG;   /* Enable tx */
        SgmiiCfg.rxConfig   = SGMIICFG_RX_CONFIG;   /* Enable rx */

        /* Setup for 125 MHz ref clock */
        SgmiiCfg.auxConfig  = SGMIICFG_AUX_CONFIG;  /* Enable PLL */
        SgmiiCfg.modeOfOperation = SGMII_MODE_OF_OPERATION_WITH_AN;    // Auto Negotiation on
        i = SGMII_config(&SgmiiCfg);
        return i;
}

/**
 * \brief  This API gets the SoC level of EMAC intial configuration
 *
 * \param  port_num     EMAC port number.
 * \param  cfg       Pointer to EAMC SOC initial config.
 *
 * \return 0 success: -1: error
 *
 */
int32_t EMAC_socGetInitCfg(uint32_t port_num, EMAC_HwAttrs_V0 *cfg)
{
    *cfg = EMACInitCfg[port_num];
    return 0;
}

/**
 * \brief  This API sets the SoC level of EMAC intial configuration
 *
 * \param  index     EMAC port number.
 * \param  cfg       Pointer to EMAC SOC initial config.
 *
 * \return           0 success: -1: error
 *
 */
int32_t EMAC_socSetInitCfg(uint32_t port_num, const EMAC_HwAttrs_V0 *cfg)
{
    EMACInitCfg[port_num] = *cfg;
    return 0;
}

/**
 * \brief  This API sets the RMII speed enable bit in MACCONTROL register
 *
 * \param  tmpval     reg value
 *
 * \return           0 success: -1: error
 *
 */
uint32_t EMAC_RMIISpeedSelect(uint32_t tmpval)
{
    return tmpval;
}



