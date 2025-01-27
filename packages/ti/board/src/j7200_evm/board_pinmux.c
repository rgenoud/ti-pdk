/******************************************************************************
 * Copyright (c) 2020-2024 Texas Instruments Incorporated - http://www.ti.com
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
 *  \file board_pinmux.c
 *
 *  \brief This file enables pinmux for the board 
 *
 */

#include <ti/csl/soc.h>
#include "board_internal.h"
#include "board_pinmux.h"

static Board_PinmuxConfig_t gBoardPinmuxCfg = {BOARD_PINMUX_CUSTOM,
                                               BOARD_PINMUX_SOM_CAN,
                                               BOARD_PINMUX_GESI_CPSW,
                                               BOARD_PINMUX_ENET_QSGMII,
                                               BOARD_PINMUX_FSS_OSPI};

/**
 * \brief  Configures kick registers for Pinmux MMR access
 *
 * \param   domain   [IN]   MMR register domain
 * \param   lockCtrl [IN]   Register lock/unlock control
 *                          0 - Unlocks the MMR register write access
 *                          1 - Locks the MMR register write access
 *
 * \return  Board_STATUS
 */
static Board_STATUS Board_pinmuxKickCtrl(uint32_t domain, uint32_t lockCtrl)
{
    Board_STATUS status;

    if(lockCtrl)
    {
        status = Board_lockMMRPartition(domain, BOARD_MMR_PARTITION7);
    }
    else
    {
        status = Board_unlockMMRPartition(domain, BOARD_MMR_PARTITION7);
    }

    return (status);
}

/**
 *  \brief  Gets base address of padconfig registers
 *
 *  \param   domain [IN]  SoC domain for pinmux
 *  \n                     BOARD_SOC_DOMAIN_MAIN - Main domain
 *  \n                     BOARD_SOC_DOMAIN_WKUP - Wakeup domain
 *
 *  \return   Valid address in case success or 0 in case of failure
 */
static void Board_pinmuxWriteProxy1Reg(uint8_t domain,
                                       uint32_t baseAddr,
                                       uint32_t regVal)
{
    uint32_t    claimAddr;
    uint32_t    claimOffset;
    uint32_t    claimShift;
    uint32_t    claimRegVal;

    if(BOARD_SOC_DOMAIN_MAIN == domain)
    {
        claimAddr = BOARD_MAIN_MMR_P7_CLAIM_ADDR;
        /* Get the register offset from base of P7 claim offset range */
        claimOffset = (baseAddr - BOARD_MAIN_PMUX_CTRL_ADDR);
    }
    else
    {
        claimAddr = BOARD_WKUP_MMR_P7_CLAIM_ADDR;
        /* Get the register offset from base of P7 claim offset range */
        claimOffset = (baseAddr - BOARD_WKUP_PMUX_CTRL_ADDR);
    }

    /* Each claim register configures 128 byte address range.
       Calculate the register offset for P7 claim register block and
       and shift values within the claim register */
    claimShift  = claimOffset % BOARD_MMR_CLAIM_ADDR_PER_REG;
    claimOffset = claimOffset / BOARD_MMR_CLAIM_ADDR_PER_REG;

    claimRegVal = HW_RD_REG32((claimAddr + (4U*claimOffset)));
    claimRegVal |= (1U << claimShift);

    /* Claim the register access */
    HW_WR_REG32((claimAddr + (4U*claimOffset)), claimRegVal);

    /* Write PAD config MMR register */
    HW_WR_REG32(baseAddr, regVal);
}

/**
 *  \brief  Gets base address of padconfig registers
 *
 *  \param   domain [IN]  SoC domain for pinmux
 *  \n                     BOARD_SOC_DOMAIN_MAIN - Main domain
 *  \n                     BOARD_SOC_DOMAIN_WKUP - Wakeup domain
 *
 *  \return   Valid address in case success or 0 in case of failure
 */
static uint32_t Board_pinmuxGetBaseAddr(uint8_t domain)
{
    uint32_t baseAddr;

    switch(domain)
    {
        case BOARD_SOC_DOMAIN_MAIN:
            baseAddr = BOARD_MAIN_PMUX_CTRL_ADDR;
        break;
        case BOARD_SOC_DOMAIN_WKUP:
            baseAddr = BOARD_WKUP_PMUX_CTRL_ADDR;
        break;
        default:
            baseAddr = 0U;
        break;
    }

    return baseAddr;
}

#if defined (_TMS320C6X)
/**
 *  \brief  Sets RAT configuration for C66x core
 *
 *  MAIN padconfig registers are not directly accessible for C66x core
 *  which requires RAT configuration for the access.
 *
 *  \return   None
 */
static void Board_setC66xRATCfg(void)
{
    HW_WR_REG32((CSL_C66_COREPAC_C66_RATCFG_BASE + 0x24),
                BOARD_PINMUX_C66X_RAT_OFFSET);
    HW_WR_REG32((CSL_C66_COREPAC_C66_RATCFG_BASE + 0x28), 0);
    HW_WR_REG32((CSL_C66_COREPAC_C66_RATCFG_BASE + 0x20), 
                BOARD_PINMUX_C66X_RAT_CONFIG);
}

/**
 *  \brief  Clears RAT configuration for C66x core
 *
 *  \return   None
 */
static void Board_clearC66xRATCfg(void)
{
    HW_WR_REG32((CSL_C66_COREPAC_C66_RATCFG_BASE + 0x20), 0);
    HW_WR_REG32((CSL_C66_COREPAC_C66_RATCFG_BASE + 0x24), 0);
    HW_WR_REG32((CSL_C66_COREPAC_C66_RATCFG_BASE + 0x28), 0);
}
#endif  /* #if defined (_TMS320C6X) */

/**
 *  \brief  Sets pinmux mode for a pin in main domain
 *
 *  Only pinmux mode is updated by this function. Other values of
 *  padconfig register remains unchanged after this function call.
 *
 *  \param    offset [IN]    Pad config offset of the pin
 *  \param    mode   [IN]    Pad config mux mode.
 *
 *  \return   BOARD_SOK in case of success or appropriate error code
 */
Board_STATUS Board_pinMuxSetMode(uint32_t offset, uint32_t mode)
{
    Board_STATUS status = BOARD_SOK;
    uint32_t baseAddr;
    uint32_t regVal;

    /* Unlock MMR write access */
    status = Board_pinmuxKickCtrl(BOARD_SOC_DOMAIN_MAIN, 0);
    if(BOARD_SOK == status)
    {
        baseAddr = Board_pinmuxGetBaseAddr(BOARD_SOC_DOMAIN_MAIN);

        regVal = HW_RD_REG32((baseAddr + offset));
        regVal &= ~(BOARD_MODE_PIN_MASK);
        mode &= BOARD_MODE_PIN_MASK;
        regVal |= mode;
        Board_pinmuxWriteProxy1Reg(BOARD_SOC_DOMAIN_MAIN, 
                                   (baseAddr + offset), 
                                   regVal);

        /* Lock MMR write access */
        status = Board_pinmuxKickCtrl(BOARD_SOC_DOMAIN_MAIN, 1);
    }

    return status;
}

/**
 *  \brief  Sets pinmux mode for a pin in wake-up domain
 *
 *  Only pinmux mode is updated by this function. Other values of
 *  padconfig register remains unchanged after this function call.
 *
 *  \param    offset [IN]    Pad config offset of the pin
 *  \param    mode   [IN]    Pad config mux mode.
 *
 *  \return   BOARD_SOK in case of success or appropriate error code
 */
Board_STATUS Board_pinMuxSetModeWkup(uint32_t offset, uint32_t mode)
{
    Board_STATUS status = BOARD_SOK;
    uint32_t baseAddr;
    uint32_t regVal;

    /* Unlock MMR write access */
    status = Board_pinmuxKickCtrl(BOARD_SOC_DOMAIN_WKUP, 0);
    if(BOARD_SOK == status)
    {
        baseAddr = Board_pinmuxGetBaseAddr(BOARD_SOC_DOMAIN_WKUP);

        regVal = HW_RD_REG32((baseAddr + offset));
        regVal &= ~(BOARD_MODE_PIN_MASK);
        mode &= BOARD_MODE_PIN_MASK;
        regVal |= mode;
        Board_pinmuxWriteProxy1Reg(BOARD_SOC_DOMAIN_WKUP, 
                                   (baseAddr + offset), 
                                   regVal);

        /* Lock MMR write access */
        status = Board_pinmuxKickCtrl(BOARD_SOC_DOMAIN_WKUP, 1);
    }

    return status;
}

/**
 *  \brief Sets padconfig register of a pin at given offset
 *
 *  Configures whole padconfig register of the pin at given offset
 *  with the value in 'muxData'.
 *
 *  \param   domain  [IN]  SoC domain for pinmux
 *  \n                      BOARD_SOC_DOMAIN_MAIN - Main domain
 *  \n                      BOARD_SOC_DOMAIN_WKUP - Wakeup domain
 *
 *  \param   offset  [IN]  Pad config offset of the pin
 *  \param   muxData [IN]  Value to be written to padconfig register
 *
 *  \return   BOARD_SOK in case of success or appropriate error code
 *
 */
Board_STATUS Board_pinmuxSetReg(uint8_t  domain,
                                uint32_t offset,
                                uint32_t muxData)
{
    uint32_t baseAddr;
    Board_STATUS status = BOARD_SOK;

    /* Unlock MMR write access */
    status = Board_pinmuxKickCtrl(domain, 0);
    if(BOARD_SOK == status)
    {
        baseAddr = Board_pinmuxGetBaseAddr(domain);
        if(0U != baseAddr)
        {
            Board_pinmuxWriteProxy1Reg(domain, 
                                       (baseAddr + offset), 
                                       muxData);
        }
        else
        {
            status = BOARD_INVALID_PARAM;
        }

        /* Lock MMR write access */
        status = Board_pinmuxKickCtrl(domain, 1);
    }

    return status;
}

/**
 *  \brief Gets padconfig register of a pin at given offset
 *
 *  \param   domain  [IN]  SoC domain for pinmux
 *  \n                      BOARD_SOC_DOMAIN_MAIN - Main domain
 *  \n                      BOARD_SOC_DOMAIN_WKUP - Wakeup domain
 *  \param   offset  [IN]  Pad config offset of the pin
 *  \param   muxData [OUT] Value of padconfig register
 *
 *  \return   BOARD_SOK in case of success or appropriate error code
 *
 */
Board_STATUS Board_pinmuxGetReg(uint8_t  domain,
                                uint32_t offset,
                                uint32_t *muxData)
{
    uint32_t baseAddr;
    Board_STATUS status = BOARD_SOK;

    baseAddr = Board_pinmuxGetBaseAddr(domain);
    if(0U != baseAddr)
    {
        *muxData = HW_RD_REG32((baseAddr + offset));
    }
    else
    {
        status = BOARD_INVALID_PARAM;
    }

    return status;
}

/**
 *  \brief Sets the board pinmux configuration.
 *
 *  There are multiple addon cards that can connected to baseboard and
 *  multiple addon cards can be connected to one expansion connector.
 *  Pinmux configured through Board_init will be set to a default
 *  combination of the boards which can be changed using this function.
 *
 *  \n Usage:
 *  \n - Call Board_pinmuxGetCfg to get default pinmux config
 *  \n - Call Board_pinmuxSetCfg to change pinmux config
 *  \n - Call Board_init with pinmux flag to apply the updated pinmux config
 *
 *  \param   pinmuxCfg [IN]  Pinmux configurations
 *
 *  \return  BOARD_SOK in case of success or appropriate error code
 *
 */
Board_STATUS Board_pinmuxSetCfg(Board_PinmuxConfig_t *pinmuxCfg)
{
    gBoardPinmuxCfg = *pinmuxCfg;

    return BOARD_SOK;
}

/**
 *  \brief Gets the board pinmux configuration.
 *
 *  There are multiple addon cards that can connected to baseboard and
 *  multiple addon cards can be connected to one expansion connector.
 *  Pinmux configured through Board_init will be set to a default
 *  combination of the boards which can be read using this function.
 *
 *  \param   pinmuxCfg [IN]  Pinmux configurations
 *
 *  \return  BOARD_SOK in case of success or appropriate error code
 *
 */
Board_STATUS Board_pinmuxGetCfg(Board_PinmuxConfig_t *pinmuxCfg)
{
    *pinmuxCfg = gBoardPinmuxCfg;

    return BOARD_SOK;
}

/**
 * \brief  Board pinmuxing update function
 *
 * Provides the option to configure/update the pinmux.
 * This function can be used to change the pinmux set by
 * Board_init by default.
 *
 * \param   pinmuxData [IN]  Pinmux data structure
 * \param   domain     [IN]  SoC domain for pinmux
 *  \n                        BOARD_SOC_DOMAIN_MAIN - Main domain
 *  \n                        BOARD_SOC_DOMAIN_WKUP - Wakeup domain
 *
 * \return  BOARD_SOK in case of success or appropriate error code
 *
 */
Board_STATUS Board_pinmuxUpdate (pinmuxBoardCfg_t *pinmuxData,
                                 uint32_t domain)
{
    pinmuxModuleCfg_t *pModuleData = NULL;
    pinmuxPerCfg_t *pInstanceData = NULL;
    int32_t i, j, k;
    uint32_t rdRegVal;
    uint32_t baseAddr;
    Board_STATUS status = BOARD_SOK;

    /* Unlock MMR write access */
    status = Board_pinmuxKickCtrl(domain, 0);
    if(BOARD_SOK == status)
    {

#if defined (_TMS320C6X)
        /* MAIN domain pinmux needs RAT configuration for C66x core. */
        if(BOARD_SOC_DOMAIN_MAIN == domain)
        {
            Board_setC66xRATCfg();
        }
#endif

        baseAddr = Board_pinmuxGetBaseAddr(domain);
        if(0U != baseAddr)
        {
            for(i = 0; PINMUX_END != pinmuxData[i].moduleId; i++)
            {
                pModuleData = pinmuxData[i].modulePinCfg;
                for(j = 0; (PINMUX_END != pModuleData[j].modInstNum); j++)
                {
                    if(1 == pModuleData[j].doPinConfig)
                    {
                        pInstanceData = pModuleData[j].instPins;
                        for(k = 0; (PINMUX_END != pInstanceData[k].pinOffset); k++)
                        {
                            rdRegVal = HW_RD_REG32((baseAddr + pInstanceData[k].pinOffset));
                            rdRegVal = (rdRegVal & BOARD_PINMUX_BIT_MASK);
                            Board_pinmuxWriteProxy1Reg(domain, 
                                                       (baseAddr + pInstanceData[k].pinOffset), 
                                                       (pInstanceData[k].pinSettings));
                        }
                    }
                }
            }
        }
        else
        {
            status = BOARD_INVALID_PARAM;
        }

#if defined (_TMS320C6X)
        if(BOARD_SOC_DOMAIN_MAIN == domain)
        {
            /* Clear the RAT configuration to allow applications to use the region */
            Board_clearC66xRATCfg();
        }
#endif

        /* Lock MMR write access */
        status = Board_pinmuxKickCtrl(domain, 1);
    }

    return status;
}

/**
 * \brief  Board pinmuxing enable function
 *
 * Enables pinmux for the board interfaces. Pin mux is done based
 * on the default/primary functionality of the board. Any pins shared by
 * multiple interfaces need to be reconfigured to access the secondary
 * functionality.
 *
 * \param   void
 *
 * \return  BOARD_SOK in case of success or appropriate error code
 *
 */
Board_STATUS Board_pinmuxConfig (void)
{
    Board_STATUS status = BOARD_SOK;

    Board_pinmuxUpdate(gJ7200_MainPinmuxData,
                       BOARD_SOC_DOMAIN_MAIN);
    Board_pinmuxUpdate(gJ7200_WkupPinmuxData,
                       BOARD_SOC_DOMAIN_WKUP);

    if(BOARD_PINMUX_SOM_AUDIO == gBoardPinmuxCfg.somMux)
    {
        Board_pinmuxUpdate(gJ7200_MainPinmuxDataAudio,
                           BOARD_SOC_DOMAIN_MAIN);
        Board_pinmuxUpdate(gJ7200_WkupPinmuxDataAudio,
                           BOARD_SOC_DOMAIN_WKUP);
    }
    else if(BOARD_PINMUX_SOM_PROFIBUS == gBoardPinmuxCfg.somMux)
    {
        Board_pinmuxUpdate(gJ7200_MainPinmuxDataProfibus,
                           BOARD_SOC_DOMAIN_MAIN);
        Board_pinmuxUpdate(gJ7200_WkupPinmuxDataProfibus,
                           BOARD_SOC_DOMAIN_WKUP);
    }
    else
    {
        /* Pinmux for 'BOARD_PINMUX_SOM_CAN' is active by default */
    }

    if(BOARD_PINMUX_FSS_HPB == gBoardPinmuxCfg.fssCfg)
    {
        Board_pinmuxUpdate(gJ7200_WkupPinmuxDataHpb,
                           BOARD_SOC_DOMAIN_WKUP);
    }

    return status;
}

Board_STATUS Board_uartTxPinmuxConfig(void)
{
    Board_STATUS status = BOARD_SOK;

    /* Unlock MMR write access */
    status = Board_pinmuxKickCtrl(BOARD_SOC_DOMAIN_WKUP, 0);
    if(BOARD_SOK == status)
    {
        /* Configure pinmux for UART Tx pin */
        HW_WR_REG32(BOARD_MCU_UART_TX_PINMUX_ADDR, BOARD_MCU_UART_TX_PINMUX_VAL);

        /* Lock MMR write access */
        status = Board_pinmuxKickCtrl(BOARD_SOC_DOMAIN_WKUP, 1);
    }

    return status;
}
