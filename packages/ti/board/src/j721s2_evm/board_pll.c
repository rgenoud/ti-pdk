/******************************************************************************
 * Copyright (c) 2021 Texas Instruments Incorporated - http://www.ti.com
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
 * \file   board_pll.c
 *
 * \brief  Board pll configurations
 *
 */

#include "board_internal.h"
#include "board_pll.h"
#include <ti/drv/sciclient/sciclient.h>

static Board_PllClkCfg_t gBoardPllClkCfgMcu[] =
{
 { TISCI_DEV_MCU_MCAN0,
   TISCI_DEV_MCU_MCAN0_MCANSS_CCLK_CLK_PARENT_HSDIV4_16FFT_MCU_1_HSDIVOUT2_CLK,
   80000000
 }, //MCU_PLL1_HSDIV2_CLKOUT
 { TISCI_DEV_MCU_UART0,
   TISCI_DEV_MCU_UART0_FCLK_CLK_PARENT_HSDIV4_16FFT_MCU_1_HSDIVOUT3_CLK,
   96000000
 }, //MCU_PLL1_HSDIV3_CLKOUT,
 { TISCI_DEV_MCU_FSS0_OSPI_0,
   TISCI_DEV_MCU_FSS0_OSPI_0_OSPI_RCLK_CLK,
   133333333
 }, //MCU_PLL1_HSDIV4_CLKOUT
 { TISCI_DEV_MCU_FSS0_OSPI_1,
   TISCI_DEV_MCU_FSS0_OSPI_1_OSPI_RCLK_CLK,
   133333333
 }, //MCU_PLL1_HSDIV4_CLKOUT
  /* MCU PLL2 Clockout */
 { TISCI_DEV_MCU_CPSW0,
   TISCI_DEV_MCU_CPSW0_RGMII_MHZ_250_CLK,
   250000000
 }, //MCU_PLL2_HSDIV0_CLKOUT
 { TISCI_DEV_MCU_CPSW0,
   TISCI_DEV_MCU_CPSW0_CPTS_RFT_CLK_PARENT_HSDIV4_16FFT_MCU_2_HSDIVOUT1_CLK,
   200000000
 }, //MCU_PLL2_HSDIV1_CLKOUT
 { TISCI_DEV_MCU_MCAN0,
   TISCI_DEV_MCU_MCAN0_MCANSS_CCLK_CLK_PARENT_HSDIV4_16FFT_MCU_2_HSDIVOUT3_CLK,
   80000000
 }, //MCU_PLL2_HSDIV3_CLKOUT
};

static Board_PllClkCfg_t gBoardPllClkCfgMain[] =
{
 { TISCI_DEV_MMCSD0,
   TISCI_DEV_MMCSD0_EMMCSS_XIN_CLK_PARENT_HSDIV4_16FFT_MAIN_0_HSDIVOUT2_CLK,
   200000000
 }, //MAIN_PLL0_HSDIV2_CLKOUT
 { TISCI_DEV_MCAN0,
   TISCI_DEV_MCAN0_MCANSS_CCLK_CLK_PARENT_HSDIV4_16FFT_MAIN_0_HSDIVOUT4_CLK,
   80000000
 }, //MAIN_PLL0_HSDIV4_CLKOUT
 { TISCI_DEV_MCSPI0,
   TISCI_DEV_MCSPI0_CLKSPIREF_CLK,
   50000000
 }, //MAIN_PLL0_HSDIV5_CLKOUT
 { TISCI_DEV_MMCSD1,
   TISCI_DEV_MMCSD1_EMMCSDSS_XIN_CLK_PARENT_HSDIV4_16FFT_MAIN_1_HSDIVOUT2_CLK,
   192000000
 }, //MAIN_PLL1_HSDIV2_CLKOUT
 { TISCI_DEV_MCU_UART0,
   TISCI_DEV_MCU_UART0_FCLK_CLK_PARENT_POSTDIV3_16FFT_MAIN_1_HSDIVOUT5_CLK,
   192000000
 }, //MAIN_PLL1_HSDIV5_CLKOUT
   /* MAIN PLL2(PER1_PLL) Clockout */
 { TISCI_DEV_MMCSD0,
   TISCI_DEV_MMCSD0_EMMCSS_XIN_CLK_PARENT_HSDIV4_16FFT_MAIN_3_HSDIVOUT2_CLK,
   200000000
 }, //MAIN_PLL2_HSDIV2_CLKOUTT
   /* MAIN PLL4((AUDIO0_PLL) Clockout */
 { TISCI_DEV_MCASP0,
   TISCI_DEV_MCASP0_AUX_CLK_PARENT_HSDIV2_16FFT_MAIN_4_HSDIVOUT0_CLK,
   196608000
 },//MAIN_PLL4_HSDIV0_CLKOUT
 { TISCI_DEV_CPSW1,
   TISCI_DEV_CPSW1_RGMII_MHZ_250_CLK,
   250000000
 }, //MAIN_PLL3_HSDIV0_CLKOUT
 { TISCI_DEV_CPSW1,
   TISCI_DEV_CPSW1_CPTS_RFT_CLK,
   200000000
 }, //MAIN_PLL3_HSDIV1_CLKOUT
 { TISCI_DEV_CPSW1,
   TISCI_DEV_CPSW1_CPPI_CLK_CLK,
   320000000
 }, //MAIN_PLL1_HSDIV1_CLKOUT
};

/**
 * \brief  PLL clock enable
 *
 * This function is used to set the PLL Module clock frequency
 *
 * \param  moduleId [IN]  Module for which the state should be set.
 *                        Refer Sciclient_PmDeviceIds in sciclient_fmwMsgParams.h
 * \param  clockId  [IN]  Clock Id for the module.
 *                        Refer Sciclient_PmModuleClockIds in sciclient_fmwMsgParams.h
 * \param  clkRate  [IN]  Value of the clock frequency to be set
 *
 * \return int32_t
 *                CSL_PASS - on Success
 *                CSL_EFAIL - on Failure
 *
 */
static int32_t Board_PLLSetModuleClkFreq(uint32_t modId,
                                         uint32_t clkId,
                                         uint64_t clkRate)
{
    uint32_t i = 0U;
    int32_t status   = CSL_EFAIL;
    uint64_t respClkRate = 0;
    uint32_t numParents = 0U;
    uint32_t moduleClockParentChanged = 0U;
    uint32_t clockStatus = 0U;
    uint32_t origParent = 0U;
    uint32_t foundParent = 0U;

    /* Check if the clock is enabled or not */
    status = Sciclient_pmModuleGetClkStatus(modId,
                                            clkId,
                                            &clockStatus,
                                            SCICLIENT_SERVICE_WAIT_FOREVER);
    if (status == CSL_PASS)
    {
        /* Get the number of parents for the clock */
        status = Sciclient_pmGetModuleClkNumParent(modId,
                                                clkId,
                                                &numParents,
                                                SCICLIENT_SERVICE_WAIT_FOREVER);
        if ((status == CSL_PASS) && (numParents > 1U))
        {
            status = Sciclient_pmGetModuleClkParent(modId, clkId, &origParent,
                                       SCICLIENT_SERVICE_WAIT_FOREVER);
        }
    }
    if (status == CSL_PASS)
    {
        /* Disabling the clock */
        status = Sciclient_pmModuleClkRequest(
                                            modId,
                                            clkId,
                                            TISCI_MSG_VALUE_CLOCK_SW_STATE_UNREQ,
                                            0U,
                                            SCICLIENT_SERVICE_WAIT_FOREVER);
    }
    if (status == CSL_PASS)
    {
        foundParent = 0U;
        /* Try to loop and change parents of the clock */
        for(i=0U;i<numParents;i++)
        {
            if (numParents > 1U)
            {
                /* Setting the new parent */
                status = Sciclient_pmSetModuleClkParent(
                                            modId,
                                            clkId,
                                            clkId+i+1,
                                            SCICLIENT_SERVICE_WAIT_FOREVER);
                /* Check if the clock can be set to desirable freq. */
                if (status == CSL_PASS)
                {
                    moduleClockParentChanged = 1U;
                }
            }
            if (status == CSL_PASS)
            {
                status = Sciclient_pmQueryModuleClkFreq(modId,
                                                        clkId,
                                                        clkRate,
                                                        &respClkRate,
                                                        SCICLIENT_SERVICE_WAIT_FOREVER);
            }
            if ((status == CSL_PASS) && (respClkRate == clkRate))
            {
                foundParent = 1U;
                break;
            }
        }
    }

    if ((status == CSL_PASS) && (numParents == 0U))
    {
        status = Sciclient_pmQueryModuleClkFreq(modId,
                                                clkId,
                                                clkRate,
                                                &respClkRate,
                                                SCICLIENT_SERVICE_WAIT_FOREVER);
        if ((status == CSL_PASS) && (respClkRate == clkRate))
        {
            foundParent = 1U;
        }
    }

    if (foundParent == 1U)
    {
        /* Set the clock at the desirable frequency*/
        status = Sciclient_pmSetModuleClkFreq(
                                modId,
                                clkId,
                                clkRate,
                                TISCI_MSG_FLAG_CLOCK_ALLOW_FREQ_CHANGE,
                                SCICLIENT_SERVICE_WAIT_FOREVER);
    }
    else
    {
        status = CSL_EFAIL;
    }
    if ((status == CSL_PASS) &&
        (clockStatus == TISCI_MSG_VALUE_CLOCK_SW_STATE_UNREQ))
    {
        /* Restore the clock again to original state */
        status = Sciclient_pmModuleClkRequest(
                                            modId,
                                            clkId,
                                            clockStatus,
                                            0U,
                                            SCICLIENT_SERVICE_WAIT_FOREVER);
    }
    if ((status != CSL_PASS) && (moduleClockParentChanged == 1U))
    {
        /* Setting the original parent if failure */
        status = Sciclient_pmSetModuleClkParent(
                                    modId,
                                    clkId,
                                    origParent,
                                    SCICLIENT_SERVICE_WAIT_FOREVER);
    }
    return status;
}

/**
 * \brief  Function to initialize module clock frequency
 *
 * \param  moduleId [IN]  Module for which the state should be set.
 *                        Refer Sciclient_PmDeviceIds in sciclient_fmwMsgParams.h
 * \param  clockId  [IN]  Clock Id for the module.
 *                        Refer Sciclient_PmModuleClockIds in sciclient_fmwMsgParams.h
 * \param  clkRate  [IN]  Value of the clock frequency to be set

 * \return Board_STATUS
 */
Board_STATUS Board_PLLInit(uint32_t modId,
                           uint32_t clkId,
                           uint64_t clkRate)
{
    int32_t  status = CSL_EFAIL;

    status = Board_PLLSetModuleClkFreq(modId, clkId, clkRate);
    if(status != CSL_PASS)
    {
        return BOARD_FAIL;
    }

    return BOARD_SOK;
}
    
/**
 * \brief  Function to initialize the MCU domain PLL clocks with default values
 *
 * \return Board_STATUS
 */
Board_STATUS Board_PLLInitMcu(void)
{
    Board_STATUS  status = BOARD_SOK;
    uint32_t index;
    uint32_t loopCount;

    loopCount = sizeof (gBoardPllClkCfgMcu)/sizeof(Board_PllClkCfg_t);

    for (index = 0; index < loopCount; index++)
    {
        status = Board_PLLInit(gBoardPllClkCfgMcu[index].tisciDevID,
                               gBoardPllClkCfgMcu[index].tisciClkID,
                               gBoardPllClkCfgMcu[index].clkRate);
        if(status != BOARD_SOK)
        {
            BOARD_DEBUG_LOG("Failed to set the PLL clock freq at index =%d\n\n",index);
        }
    }

    return status;
}

/**
 * \brief  Function to initialize the MAIN domain PLL clocks with default values
 *
 * \return Board_STATUS
 */
Board_STATUS Board_PLLInitMain(void)
{
    Board_STATUS  status = BOARD_SOK;
    uint32_t index;
    uint32_t loopCount;

    loopCount = sizeof (gBoardPllClkCfgMain)/sizeof(Board_PllClkCfg_t);

    for (index = 0; index < loopCount; index++)
    {
        status = Board_PLLInit(gBoardPllClkCfgMain[index].tisciDevID,
                               gBoardPllClkCfgMain[index].tisciClkID,
                               gBoardPllClkCfgMain[index].clkRate);
        if(status != BOARD_SOK)
        {
            BOARD_DEBUG_LOG("Failed to set the PLL clock freq at index =%d\n\n",index);
        }
    }

    return status;
}
