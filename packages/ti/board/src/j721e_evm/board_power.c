/*
 * Copyright (C) 2019 Texas Instruments Incorporated - http://www.ti.com/
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

/**
 *  \file   board_power.c
 *
 *  \brief  Implements functions to control the power on the board.
 *
 */

#include <ti/csl/cslr_device.h>

#include <ti/drv/i2c/i2c.h>
#include <ti/drv/i2c/soc/i2c_soc.h>
#include <ti/osal/osal.h>
#include <ti/board/board.h>
#include <ti/board/src/devices/common/common.h>
#include "board_internal.h"
#include "board_power.h"
#include "board_utils.h"

/**
 *  \brief    Function to configure SD card voltage gpio configuration.
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
    regVal = HW_RD_REG32(CSL_GPIO0_BASE + 0x88);
    regVal &= ~(0x01 << (BOARD_SDIO_1V8_EN_PIN_NUM % 32));
    HW_WR_REG32((CSL_GPIO0_BASE + 0x88), regVal);

    /* Setting the GPIO value */
    regVal = HW_RD_REG32(CSL_GPIO0_BASE + 0x90);

    if(0 == gpioValue)
    {
        regVal &= ~(0x01 << (BOARD_SDIO_1V8_EN_PIN_NUM % 32));
        HW_WR_REG32((CSL_GPIO0_BASE + 0x90), regVal);
    }
    else
    {
        regVal |= (gpioValue << (BOARD_SDIO_1V8_EN_PIN_NUM % 32));
        HW_WR_REG32((CSL_GPIO0_BASE + 0x90), regVal);
    }
}

/**
 *  \brief    Function to programs VDD_CORE to 0.9V.
 *
 *  \return   BOARD_SOK in case of success or appropriate error code
 *
 */
Board_STATUS Board_pmVDDCoreVoltageCfg(void)
{
    I2C_Handle handle = NULL;
	Board_STATUS retVal = BOARD_SOK;
    uint8_t regData;

    /* VDD voltage is 0.9v by default for Leo PMIC SoM */
    if(BTRUE != Board_detectBoard(BOARD_ID_SOM))
    {
        handle = Board_getI2CHandle(BOARD_SOC_DOMAIN_WKUP,
                                    BOARD_PMIC_LP87561_I2C_INSTANCE);
        if(NULL == handle)
        {
            retVal = BOARD_I2C_OPEN_FAIL;
        }
        else
        {
            regData = BOARD_PMIC_LP87561_VOLTAGE_0V9_VAL;
            retVal= Board_i2c8BitRegWr(handle,
                                       BOARD_PMIC_LP87561_I2C_SLAVE_ADDR,
                                       BOARD_PMIC_LP87561_BUCK0_VOUT_REG,
                                       &regData,
                                       1U,
                                       I2C_WAIT_FOREVER);
            if(BOARD_SOK != retVal)
            {
                retVal = BOARD_I2C_TRANSFER_FAIL;
            }
        }

        /* Wait for some time to ensure voltage ramp is complete */
        BOARD_delay(100000);

        Board_i2cDeInit();
    }

    return retVal;
}

/**
 *  \brief    Function to configure SD card voltage.
 *
 *  \param vsel [IN] SD voltage selection. 0 for 1.8v, 1 for 3.3v
 *
 *  \return   BOARD_SOK in case of success or appropriate error code
 *
 */
Board_STATUS Board_pmSdVoltageCtrl(uint8_t vsel)
{
    I2C_Handle handle = NULL;
	Board_STATUS retVal = BOARD_INVALID_PARAM;
    uint8_t voltage;
    uint8_t regData;
    uint8_t leoPMIC = 0;

    /* Detecting SoM board */
    if(BTRUE == Board_detectBoard(BOARD_ID_SOM))
    {
        leoPMIC = 1;
        Board_sdVoltageCtrlGpioCfg(vsel);
    }
    else
    {
        handle = Board_getI2CHandle(BOARD_SOC_DOMAIN_WKUP,
                                    BOARD_PMIC_I2C_INSTANCE);
        if(NULL == handle)
        {
            retVal = BOARD_I2C_OPEN_FAIL;
            goto voltage_switch_exit;
        }

        if(1 == vsel)
        {
            voltage = BOARD_PMIC_LDO1_VSEL_3V3;
        }
        else
        {
            voltage = BOARD_PMIC_LDO1_VSEL_1V8;
        }

        /* Write voltage */
        retVal = Board_i2c8BitRegWr(handle,
                                    BOARD_PMIC_I2C_SLAVE_ADDR,
                                    BOARD_PMIC_LDO1_VOLTAGE_REG,
                                    &voltage,
                                    1U,
                                    I2C_WAIT_FOREVER);
        if(BOARD_SOK != retVal)
        {
            retVal = BOARD_I2C_TRANSFER_FAIL;
            goto voltage_switch_exit;
        }

        BOARD_delay(10000);

        /* Enable LDO */
        regData = 0x1;
        retVal = Board_i2c8BitRegWr(handle,
                                    BOARD_PMIC_I2C_SLAVE_ADDR,
                                    BOARD_PMIC_LDO1_CTRL_REG,
                                    &regData,
                                    1U,
                                    I2C_WAIT_FOREVER);
        if(BOARD_SOK != retVal)
        {
        retVal = BOARD_I2C_TRANSFER_FAIL;
        goto voltage_switch_exit;
        }
    }
    /* Wait for some time to ensure voltage ramp is complete */
    BOARD_delay(100000);
    retVal = BOARD_SOK; /* Success */

voltage_switch_exit:
    if(0 == leoPMIC)
    {
        Board_i2cDeInit();
    }

    return retVal;
}

/**
 *  \brief    Function to power off the PMIC.
 *
 *  \param slaveAddr [IN] PMIC slave address
 *
 *  \return   BOARD_SOK in case of success or appropriate error code
 *
 */
Board_STATUS Board_pmPowerOff(uint32_t slaveAddr)
{
    I2C_Handle handle = NULL;
    Board_STATUS retVal = BOARD_INVALID_PARAM;
    uint8_t regData;

    handle = Board_getI2CHandle(BOARD_SOC_DOMAIN_WKUP,
                                BOARD_PMIC_I2C_INSTANCE);
    if(NULL == handle)
    {
        return (retVal);
    }

    /* Write voltage */
    regData = (TPS6594X_FSM_NSLEEP_NSLEEP1B | TPS6594X_FSM_NSLEEP_NSLEEP2B);
    retVal = Board_i2c8BitRegWr(handle,
                                slaveAddr,
                                TPS6594X_FSM_NSLEEP_TRIGGERS,
                                &regData,
                                1U,
                                I2C_WAIT_FOREVER);
    if(BOARD_SOK != retVal)
    {
        return (retVal);
    }

    BOARD_delay(10000);

    regData = (TPS6594X_INT_STARTUP_NPWRON_START_INT |
               TPS6594X_INT_STARTUP_ENABLE_INT       |
               TPS6594X_INT_STARTUP_RTC_INT          |
               TPS6594X_INT_STARTUP_SOFT_REBOOT_INT);
    retVal = Board_i2c8BitRegWr(handle,
                                slaveAddr,
                                TPS6594X_INT_STARTUP,
                                &regData,
                                1U,
                                I2C_WAIT_FOREVER);
    if(BOARD_SOK != retVal)
    {
        return (retVal);
    }

    BOARD_delay(10000);

    regData = (TPS6594X_INT_MISC_BIST_PASS_INT |
               TPS6594X_INT_MISC_EXT_CLK_INT   |
               TPS6594X_INT_MISC_TWARN_INT);
    retVal = Board_i2c8BitRegWr(handle,
                                slaveAddr,
                                TPS6594X_INT_MISC,
                                &regData,
                                1U,
                                I2C_WAIT_FOREVER);
    if(BOARD_SOK != retVal)
    {
        return (retVal);
    }

    BOARD_delay(10000);

    regData = (TPS6594X_CONFIG_NSLEEP1_MASK | TPS6594X_CONFIG_NSLEEP2_MASK);
    retVal = Board_i2c8BitRegWr(handle,
                                slaveAddr,
                                TPS6594X_CONFIG_1,
                                &regData,
                                1U,
                                I2C_WAIT_FOREVER);
    if(BOARD_SOK != retVal)
    {
        return (retVal);
    }

    BOARD_delay(10000);

    regData = (TPS6594X_FSM_I2C_TRIGGERS_I2C0);
    retVal = Board_i2c8BitRegWr(handle,
                                slaveAddr,
                                TPS6594X_FSM_I2C_TRIGGERS,
                                &regData,
                                1U,
                                I2C_WAIT_FOREVER);
    if(BOARD_SOK != retVal)
    {
        return (retVal);
    }

    return retVal;
}
