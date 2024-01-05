/******************************************************************************
 * Copyright (c) 2022-2023 Texas Instruments Incorporated - http://www.ti.com
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
 *  \file   board_utils.c
 *
 *  \brief  Implements multiple board utility functions
 *
 */

#include <stdio.h>
#include <string.h>
#include <ti/csl/arch/csl_arch.h>
#include "board_internal.h"
#include "board_utils.h"
#include "board_cfg.h"
#include "board_info_ddr.h"
#include <ti/drv/mmcsd/MMCSD.h>
#include <ti/drv/mmcsd/soc/MMCSD_soc.h>

Board_DetectCfg_t  gBoardDetCfg[BOARD_ID_MAX_BOARDS] =
 {{BOARD_COMMON_EEPROM_I2C_INST, BOARD_GESI_EEPROM_SLAVE_ADDR, BOARD_SOC_DOMAIN_WKUP, "J7X-GESI-EXP"},
  {BOARD_CSI2_EEPROM_I2C_INST, BOARD_CSI2_EEPROM_SLAVE_ADDR, BOARD_SOC_DOMAIN_MAIN, "J7X-FUSION2-CSI"},
  {BOARD_COMMON_EEPROM_I2C_INST, BOARD_ENET1_EEPROM_SLAVE_ADDR, BOARD_SOC_DOMAIN_WKUP, "J7X-VSC8514-ETH"},
  {BOARD_COMMON_EEPROM_I2C_INST, BOARD_EVM_EEPROM_SLAVE_ADDR, BOARD_SOC_DOMAIN_WKUP, "J784S4X-EVM"},
  {BOARD_COMMON_EEPROM_I2C_INST, BOARD_ENET2_EEPROM_SLAVE_ADDR, BOARD_SOC_DOMAIN_WKUP, "J7X-VSC8514-ETH"}};

Board_I2cInitCfg_t gBoardI2cInitCfg = {0, BOARD_SOC_DOMAIN_MAIN, 0};
Board_initParams_t gBoardInitParams = {BOARD_UART_INSTANCE, BOARD_UART_SOC_DOMAIN, BOARD_PSC_DEVICE_MODE_NONEXCLUSIVE,
                                       BOARD_MAIN_CLOCK_GROUP_ALL, BOARD_MCU_CLOCK_GROUP_ALL, BOARD_ID_ENET, 0};

/**
 *  \brief    Function to configure SD card voltage control gpio configuration.
 *
 *  \param    gpioValue [IN] GPIO pin value.
 *            1 for GPIO pin high
 *            0 for GPIO pin low
 *
 *  \return   BOARD_SOK in case of success or appropriate error code
 *
 */
static void Board_sdVoltageCtrlGpioCfg(uint8_t gpioValue)
{
    uint32_t regVal;

    /* Setting the GPIO direction to output */
    regVal = HW_RD_REG32(CSL_GPIO0_BASE + 0x10);
    regVal &= ~(0x01 << (BOARD_SDIO_1V8_EN_PIN_NUM % 32));
    HW_WR_REG32((CSL_GPIO0_BASE + 0x10), regVal);

    /* Setting the GPIO value */
    regVal = HW_RD_REG32(CSL_GPIO0_BASE + 0x18);

    if(gpioValue == 0)
    {
        regVal &= ~(0x01 << (BOARD_SDIO_1V8_EN_PIN_NUM % 32));
        HW_WR_REG32((CSL_GPIO0_BASE + 0x18), regVal);
    }
    else
    {
        regVal |= (gpioValue << (BOARD_SDIO_1V8_EN_PIN_NUM % 32));
        HW_WR_REG32((CSL_GPIO0_BASE + 0x18), regVal);
    }
}

/**
 * \brief Board ID read function
 *
 * \param   info     [IN]  Board info structure
 * \param   boardID  [IN]  ID of the board to be detected
 * \n                      BOARD_ID_GESI(0x0) - GESI Board
 * \n                      BOARD_ID_FUSION2(0x1) - Fusion 2 Board
 * \n                      BOARD_ID_ENET(0x2) - ENET Board (ENET-EXP-1)
 * \n                      BOARD_ID_EVM(0x3) - EVM Board
 * \n                      BOARD_ID_ENET2(0x4) - ENET board (ENET-EXP-2)
 *
 * \return   BOARD_SOK in case of success or appropriate error code.
 *
 */
Board_STATUS Board_getBoardData(Board_IDInfo_v2 *info, uint32_t boardID)
{
    Board_I2cInitCfg_t i2cCfg = {0};
    Board_STATUS status;

    i2cCfg.i2cInst    = gBoardDetCfg[boardID].i2cInst;
    i2cCfg.socDomain  = gBoardDetCfg[boardID].socDomain;
    i2cCfg.enableIntr = false;
    Board_setI2cInitConfig(&i2cCfg);

    if(Board_isBoardDDRIdDataValid())
    {
        if((boardID == BOARD_ID_EVM)   ||
           (boardID == BOARD_ID_ENET))
        {
            status = Board_getBoardIdData(info, boardID);
            if(status != BOARD_SOK)
            {
#if defined(BOARD_ID_MEMORY_DUMP_ERR_FALLBACK)
                status = Board_getIDInfo_v2(info, gBoardDetCfg[boardID].slaveAddr);
#endif
            }
        }
        else
        {
            status = Board_getIDInfo_v2(info, gBoardDetCfg[boardID].slaveAddr);
        }
    }
    else
    {
        status = Board_getIDInfo_v2(info, gBoardDetCfg[boardID].slaveAddr);
    }

    return status;
}

/**
 * \brief Board detect function
 *
 *  Checks if the board with given 'boardID' is connected to the
 *  base board.
 *
 *  \n Note: Board ID EEPROM should be programmed for this function
 *           to work properly.
 *
 * \param   boardID  [IN]  ID of the board to be detected
 * \n                      BOARD_ID_GESI(0x0) - GESI Board
 * \n                      BOARD_ID_FUSION2(0x1) - Fusion 2 Board
 * \n                      BOARD_ID_ENET(0x2) - ENET Board (ENET-EXP-1)
 * \n                      BOARD_ID_EVM(0x3) - EVM Board
 * \n                      BOARD_ID_ENET2(0x4) - ENET Board (ENET-EXP-2)
 *
 * \return   TRUE if the given board is detected else FALSE.
 *           SoM board will be always connected to the base board.
 *           For SoM boardID return value TRUE indicates dual PMIC
 *           SoM and FALSE indicates alternate PMIC SoM
 *
 */
bool Board_detectBoard(uint32_t boardID)
{
    Board_IDInfo_v2 info;
    Board_STATUS status;
    bool bDet = FALSE;

    memset(&info, 0, sizeof(info));

    if(boardID <= BOARD_ID_ENET2)
    {
        status = Board_getBoardData(&info, boardID);
        if(status == 0)
        {
            if(!(strncmp(info.boardInfo.boardName,
                         gBoardDetCfg[boardID].bName,
                         BOARD_BOARD_NAME_LEN)))
            {
                bDet = TRUE;
            }
        }
    }

    return bDet;
}

/**
 * \brief  Checks for Alpha board revision
 *
 * \param   boardID  [IN]  ID of the board to be detected
 * \n                      BOARD_ID_GESI(0x0) - GESI Board
 * \n                      BOARD_ID_FUSION2(0x1) - Fusion 2 Board
 * \n                      BOARD_ID_ENET(0x2) - ENET Board (ENET-EXP-1)
 * \n                      BOARD_ID_EVM(0x3) - EVM Board
 * \n                      BOARD_ID_ENET2(0x4) - ENET board (ENET-EXP-2)
 *
 * \return TRUE if board revision is Alpha, FALSE for all other cases
 */
bool Board_isAlpha(uint32_t boardID)
{
    bool alphaBoard = FALSE;

    return alphaBoard;
}

/**
 *  \brief    Function to detect ENET expansion application card type
 *
 *  ENET expansion connector supports QSGMII and SGMII application cards.
 *  This function detects type of the application card connected on
 *  ENET expansion connector.
 *
 * \param   boardID  [IN]  ID of the board to be detected
 * \n                      BOARD_ID_ENET(0x2) - ENET Board (ENET-EXP-1)
 * \n                      BOARD_ID_ENET2(0x4) - ENET board (ENET-EXP-2)
 *
 *  \return
 *            0 (BOARD_ENET_NONE)   - No board connected or invalid board ID data
 *            1 (BOARD_ENET_QSGMII) - QSGMII board connected
 *            2 (BOARD_ENET_SGMII)  - SGMII board connected
 *           -1 (BOARD_ENET_UNKOWN) - Unknown board
*/
int32_t Board_detectEnetCard(uint32_t boardID)
{
    Board_IDInfo_v2 info;
    Board_STATUS status;
    int8_t ret = 0;

    memset(&info, 0, sizeof(info));

    if ((boardID == BOARD_ID_ENET) ||
        (boardID == BOARD_ID_ENET2))
    {
        status = Board_getBoardData(&info, boardID);
        if(status == 0)
        {
            if((strcmp(info.boardInfo.boardName, "J7X-VSC8514-ETH")) == 0)
            {
                ret = BOARD_ENET_QSGMII;
            }
            else if((strcmp(info.boardInfo.boardName, "J7X-DP83869-ETH")) == 0)
            {
                ret = BOARD_ENET_SGMII;
            }
            else
            {
                ret = BOARD_ENET_UNKOWN;
            }
        }
        else
        {
            ret = BOARD_ENET_NONE;
        }
    }
    else
    {
        ret = BOARD_ENET_UNKOWN;
    }

    return ret;
}

/**
 * \brief Read MAC ID function
 *
 *  This function reads the MAC addresses programmed to the board ID EEPROM
 *  on the boards with Ethernet ports. Exception is for MCU Ethernet port
 *  which is supposed to use MAC ID from SoC MMR registers.
 *
 *  There can be multiple MAC IDs stored in the EEPROM based on the
 *  number of Ethernet ports on the board. Number of MAC IDs copied
 *  to 'macAddrBuf' can be read using 'macAddrCnt' parameters.
 *
 *  Each MAC address will be 6 bytes long. MAC IDs will be copied to buffer
 *  based on 'macBufSize'. If the buffer size is long enough, all the MAC
 *  addresses from EEPROM will be copied to 'macAddrBuf' else fewer MAC
 *  IDs to fit within 'macBufSize'. MAC count for a given board can be
 *  read using Board_readMacAddrCount() function.
 *
 *  \n Note: Board ID EEPROM should be programmed for this function
 *           to work properly.
 *
 * \param  boardID  [IN]  ID of the board to be detected
 * \n                      BOARD_ID_GESI(0x0) - GESI Board
 * \n                      BOARD_ID_FUSION2(0x1) - Fusion 2 Board
 * \n                      BOARD_ID_ENET(0x2) - ENET Board (ENET-EXP-1)
 * \n                      BOARD_ID_EVM(0x3) - EVM Board
 * \n                      BOARD_ID_ENET2(0x4) - ENET board (ENET-EXP-2)
 * \param  macAddrBuf[OUT] Buffer to write MAC IDs read from EEPROM
 * \param  macBufSize[IN]  Size of the macAddrBuf
 * \param  macAddrCnt[OUT] Number of valid MAC addresses programmed to the EEPROM
 *                         This an optional variable to read the MAC ID count
 *                         filled to the 'macAddrBuf'.
 *                         Pass a valid address to get MAC ID count.
 *
 * \return   BOARD_SOK in case of success or appropriate error code.
 *
 */
Board_STATUS Board_readMacAddr(uint32_t boardID,
                               uint8_t  *macAddrBuf,
                               uint32_t macBufSize,
                               uint32_t *macAddrCnt)
{
    Board_IDInfo_v2 info;
    Board_STATUS status;
    uint8_t macCount = 0;

    memset(&info, 0, sizeof(info));

    if((boardID <= BOARD_ID_ENET2) && (macAddrBuf != NULL))
    {
        status = Board_getBoardData(&info, boardID);
        if(status == 0)
        {
            macCount = ((info.macInfo.macControl & BOARD_MAC_COUNT_MASK)
                          >> BOARD_MAC_COUNT_SHIFT) + 1;
            if(macBufSize < (macCount * BOARD_MAC_ADDR_BYTES))
            {
                macCount = (macBufSize / BOARD_MAC_ADDR_BYTES);
            }

            memcpy(macAddrBuf, &(info.macInfo.macAddress[0]),
                   (macCount * BOARD_MAC_ADDR_BYTES));
        }
    }
    else
    {
        status = BOARD_INVALID_PARAM;
    }

    if(macAddrCnt != NULL)
    {
        *macAddrCnt = macCount;
    }

    return status;
}

/**
 * \brief Read MAC ID count
 *
 *  This function reads the number of MAC addresses programmed to
 *  board ID EEPROM on the boards with Ethernet ports. Exception is
 *  for MCU Ethernet port which is supposed to use MAC ID from SoC
 *  MMR registers. Each MAC address programmed to EEPROM is 6 bytes long.
 *
 *  \n Note: Board ID EEPROM should be programmed for this function
 *           to work properly.
 *
 * \param  boardID  [IN]  ID of the board to be detected
 * \n                      BOARD_ID_GESI(0x0) - GESI Board
 * \n                      BOARD_ID_FUSION2(0x1) - Fusion 2 Board
 * \n                      BOARD_ID_ENET(0x2) - ENET Board (ENET-EXP-1)
 * \n                      BOARD_ID_EVM(0x3) - EVM Board
 * \n                      BOARD_ID_ENET2(0x4) - ENET board (ENET-EXP-2)
 * \param  macAddrCnt[OUT] Number of valid MAC addresses programmed to the EEPROM
 *
 * \return   BOARD_SOK in case of success or appropriate error code.
 *
 */
Board_STATUS Board_readMacAddrCount(uint32_t boardID,
                                    uint32_t *macAddrCnt)
{
    Board_IDInfo_v2 info;
    Board_STATUS status;

    memset(&info, 0, sizeof(info));

    if((boardID <= BOARD_ID_ENET2) && (macAddrCnt != NULL))
    {
        status = Board_getBoardData(&info, boardID);
        if(status == 0)
        {
            *macAddrCnt = ((info.macInfo.macControl & BOARD_MAC_COUNT_MASK)
                           >> BOARD_MAC_COUNT_SHIFT) + 1;
        }
    }
    else
    {
        status = BOARD_INVALID_PARAM;
    }

    return status;
}

/**
 * \brief Function to configure I2C configurations used by board
 *
 * This function is used to set the I2C controller instance and
 * SoC domain used by the board module for IO expander and board
 * ID info read.
 *
 * Usage:
 * Call Board_setI2cInitConfig to set the I2C configurations
 * Call IO expander Init or Board ID info read/write
 *
 *  \return   BOARD_SOK in case of success or appropriate error code.
 *
 */
Board_STATUS Board_setI2cInitConfig(Board_I2cInitCfg_t *i2cCfg)
{
    if(i2cCfg == NULL)
    {
        return BOARD_INVALID_PARAM;
    }

    gBoardI2cInitCfg = *i2cCfg;

    return BOARD_SOK;
}

/**
 * \brief Function to get board init params
 *
 *  This function shall be used to know the current board init
 *  parameters and update them if needed using the function Board_setInitParams.
 *
 * \param   initParams  [IN]  Board init params structure
 *
 * \return   BOARD_SOK in case of success or appropriate error code.
 *
 */
Board_STATUS Board_getInitParams(Board_initParams_t *initParams)
{
    if(initParams == NULL)
    {
        return BOARD_INVALID_PARAM;
    }

    *initParams = gBoardInitParams;

    return BOARD_SOK;
}

/**
 * \brief Function to configure board init parameters
 *
 *  Board init params includes the parameters used by Board_init
 *  function for different operations. Default init parameters
 *  used by Board_init can be updated using this function.
 *  All the default params can be overwritten by calling this function
 *  or some of can be changed by reading the existing init parameters
 *  using Board_getInitParams function.
 *
 * Usage:
 * Call Board_getInitParams to get the default board init parameters
 * Update the parameters as needed
 * Call Board_setInitParams to update the default board init parameters
 *
 * \param   initCfg  [IN]  Board Init config structure
 *
 * \return   BOARD_SOK in case of success or appropriate error code.
 *
 */
Board_STATUS Board_setInitParams(Board_initParams_t *initParams)
{
    if(initParams == NULL)
    {
        return BOARD_INVALID_PARAM;
    }

    gBoardInitParams = *initParams;

    return BOARD_SOK;
}

/**
 * \brief Voltage Switching function for MMCSD
 *
 * Functionality: Change the voltage of the MMC CMD & DAT lines.
 *  This function is called by the MMCSD card driver (if the driver is
 *  configured to use this function at init time by the application) to change
 *  the CMD & DAT voltage from 3.0V to 1.8V if a UHS-I card is found.
 *  This function configures the PMIC controller of the board to switch the voltage
 *
 *  Note: This function uses non-standard board API naming and return type
 *        to align with existing platforms.
 *
 * \param   instance       [IN]  Device instance
 * \param   switchVoltage  [IN]  MMCSD IO voltage value
 *
 */
MMCSD_Error Board_mmc_voltageSwitchFxn(uint32_t instance,
                                       MMCSD_BusVoltage_e switchVoltage)
{
	MMCSD_Error mmcRetVal = MMCSD_OK;

    if(switchVoltage == MMCSD_BUS_VOLTAGE_1_8V)
    {
       Board_sdVoltageCtrlGpioCfg(0);
    }
    else if(switchVoltage == MMCSD_BUS_VOLTAGE_3_3V)
    {
       Board_sdVoltageCtrlGpioCfg(1);
	}
    else
    {
        mmcRetVal = MMCSD_ERR;
    }

	return(mmcRetVal);
}

/**
 * \brief Function to get the SoC domain
 *
 *  This function returns the domain of the SoC core on which
 *  it is executing.
 *
 * \return   SoC domain of the core.
 *
 */
uint32_t Board_getSocDomain(void)
{
    uint32_t socDomain = BOARD_SOC_DOMAIN_MAIN;

#ifdef BUILD_MCU
    CSL_ArmR5CPUInfo info = {0U, 0U, 0U};

    CSL_armR5GetCpuID(&info);
    if (info.grpId == (uint32_t)CSL_ARM_R5_CLUSTER_GROUP_ID_0)
    {
        socDomain = BOARD_SOC_DOMAIN_MCU;
    }
#endif

  return socDomain;
}

/**
 *  \brief  Sets RAT configuration
 *
 *  MAIN padconfig registers are not directly accessible for C66x core
 *  which requires RAT configuration for the access.
 *
 *  \return   None
 */
void Board_setRATCfg(void)
{
    /* Not used. Place holder for any future updates */
}

/**
 *  \brief  Restores RAT configuration
 *
 *  \return   None
 */
void Board_restoreRATCfg(void)
{
    /* Not used. Place holder for any future updates */
}

/**
 *  \brief    Function to generate delay in micro seconds
 *
 *  This function takes the delay parameters in usecs but the generated
 *  delay will be in multiples of msecs due to the osal function which
 *  generates delay in msecs. Delay parameter passed will be converted to
 *  msecs and fractional value will be adjusted to nearest msecs value.
 *  Minimum delay generated by this function is 1 msec.
 *  Function parameter is kept in usecs to match with existing
 *  platforms which has delay function for usecs.
 *
 *  \param    usecs [IN]  Specifies the time to delay in micro seconds.
 *
 */
void BOARD_delay(uint32_t usecs)
{
    uint32_t msecs;

    msecs = usecs/1000;
    if(usecs%1000)
    {
        msecs += 1;
    }

    Osal_delay(msecs);
}
