/*
 *  Copyright (C) 2020-2021 Texas Instruments Incorporated
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
 */

/**
 *  \file sciserver_testapp_main.c
 *
 *  \brief Example Application for sciserver
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>

#include <ti/board/board.h>
#include <ti/drv/sciclient/sciserver_tirtos.h>
#include <ti/drv/sciclient/examples/common/sciclient_appCommon.h>
#include <ti/osal/osal.h>
#include <ti/osal/TaskP.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/**< Main application stack size */
#define APP_TSK_STACK_MAIN              (32U * 1024U)
#define APP_TSK_STACK_MAIN_PRI         (6)

/*
 * BoardCfg & boardCfg_Sec should have been done already by the bootloader
 * #define CONFIG_BOARDCFG (1)
 * #define CONFIG_BOARDCFG_SECURITY (1)
 */

/* PM Init may have been done before. It is harmless to do it again. */
#define CONFIG_BOARDCFG_PM (1)
#define CONFIG_BOARDCFG_RM (1)

#if defined(SOC_J722S)
#define SCICLIENT_CCS_DEVGRP0 (DEVGRP_ALL)
#else
#define SCICLIENT_CCS_DEVGRP0 (DEVGRP_00)
#define SCICLIENT_CCS_DEVGRP1 (DEVGRP_01)
#endif

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

#if defined(SOC_J722S)
static int32_t Sciclient_init_send_boardcfg (uint8_t devgrp_curr);
static int32_t SOC_moduleClockEnable(uint32_t moduleId, uint32_t enable);
static int32_t setPLLClk(uint32_t modId, uint32_t clkId, uint64_t clkRate);
#endif
static void taskFxn(void* a0, void* a1);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Main task application stack */
static uint8_t  gAppTskStackMain[APP_TSK_STACK_MAIN]
__attribute__ ((aligned(8192)));

#if CONFIG_BOARDCFG
const struct tisci_boardcfg gBoardConfigLow_debug
__attribute__(( aligned(128), section(".boardcfg_data") )) =
{
    /* tisci_boardcfg_abi_rev */
    .rev = {
        .tisci_boardcfg_abi_maj = TISCI_BOARDCFG_ABI_MAJ_VALUE,
        .tisci_boardcfg_abi_min = TISCI_BOARDCFG_ABI_MIN_VALUE,
    },

    /* tisci_boardcfg_control */
    .control = {
        .subhdr = {
            .magic = TISCI_BOARDCFG_CONTROL_MAGIC_NUM,
            .size = sizeof(struct tisci_boardcfg_control),
        },
        /* Enable/disable support for System Firmware main isolation.
         * If disabled, main isolation SCI message will be rejected with NAK.
         */
        .main_isolation_enable = 0x5A,
        /* Host-ID allowed to send SCI-message for main isolation.
         * If mismatch, SCI message will be rejected with NAK.
         */
#if defined(SOC_J722S)
        .main_isolation_hostid = TISCI_HOST_ID_WKUP_0_R5_1,
#else
        .main_isolation_hostid = TISCI_HOST_ID_MCU_0_R5_1,
#endif
    },

    /* tisci_boardcfg_sec_proxy */
    .secproxy = {
        .subhdr = {
            .magic = TISCI_BOARDCFG_SECPROXY_MAGIC_NUM,
            .size = sizeof(struct tisci_boardcfg_secproxy),
        },
        /* Memory allocation for messages scaling factor. In current design,
         * only value of “1” is supported. For future design, a value of “2”
         * would double all memory allocations and credits, “3” would triple,
         * and so on.
         */
        .scaling_factor = 0x1,
        /* Memory allocation for messages profile number. In current design,
         * only a value of “1” is supported. “0” is always invalid due to
         * fault tolerance.
         */
        .scaling_profile = 0x1,
        /* Do not configure main nav secure proxy. This removes all MSMC memory
         * demands from System Firmware but limits MPU channels to one set of
         * secure and one set of insecure. In current design, supports only “0”.
         */
        .disable_main_nav_secure_proxy = 0,
    },

    /* tisci_boardcfg_msmc */
    .msmc = {
        .subhdr = {
            .magic = TISCI_BOARDCFG_MSMC_MAGIC_NUM,
            .size = sizeof(struct tisci_boardcfg_msmc),
        },
        /* If the whole memory is X MB the value you write to this field is n.
         * The value of n sets the cache size as n * X/32. The value of n should
         * be given in steps of 4, which makes the size of cache to be
         * configured in steps on X/8 MB.
         */
        .msmc_cache_size = 0x00,
    },

    /* boardcfg_dbg_cfg */
    .debug_cfg = {
        .subhdr = {
            .magic = TISCI_BOARDCFG_DBG_CFG_MAGIC_NUM,
            .size = sizeof(struct tisci_boardcfg_dbg_cfg),
        },
        /* This enables the trace for DMSC logging. Should be used only for
         * debug. Profiling should not be done with this enabled.
         */
        .trace_dst_enables = (TISCI_BOARDCFG_TRACE_DST_UART0 |
                              TISCI_BOARDCFG_TRACE_DST_ITM |
                              TISCI_BOARDCFG_TRACE_DST_MEM),
        .trace_src_enables = (TISCI_BOARDCFG_TRACE_SRC_PM |
                              TISCI_BOARDCFG_TRACE_SRC_RM |
                              TISCI_BOARDCFG_TRACE_SRC_SEC |
                              TISCI_BOARDCFG_TRACE_SRC_BASE |
                              TISCI_BOARDCFG_TRACE_SRC_USER |
                              TISCI_BOARDCFG_TRACE_SRC_SUPR)
    }
};
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    TaskP_Handle task;
    TaskP_Params taskParams;

#if defined (SOC_AM62X) || defined (SOC_AM62A) || defined (SOC_J722S)
    void _freertosresetvectors (void);
    memcpy((void *)0x0, (void *)_freertosresetvectors , 0x40);
#endif
    OS_init();

        /* Initialize the task params */
    TaskP_Params_init(&taskParams);
    /* Set the task priority higher than the default priority (1) */
    taskParams.priority     = APP_TSK_STACK_MAIN_PRI;
    taskParams.stack        = gAppTskStackMain;
    taskParams.stacksize    = sizeof (gAppTskStackMain);

    task = TaskP_create(taskFxn, &taskParams);
    if(NULL == task)
    {
        OS_stop();
    }
    OS_start();    /* does not return */

    return(0);
}


static void taskFxn(void* a0, void* a1)
{
    int32_t ret = CSL_PASS;
    Sciclient_ConfigPrms_t clientPrms;
    Sciserver_TirtosCfgPrms_t appPrms;
    struct tisci_msg_proc_get_status_resp cpuStatus;
    struct tisci_msg_proc_set_config_req  proc_set_config_req;
    char *version_str = NULL;
    char *rmpmhal_version_str = NULL;
    uint64_t freqHz;
    /* Sciclient needs to be initialized before Sciserver. Sciserver depends on
     * Sciclient API to execute message forwarding */
    ret = Sciclient_configPrmsInit(&clientPrms);

    if (ret == CSL_PASS)
    {
        ret = Sciclient_boardCfgParseHeader(
            (uint8_t *) SCISERVER_COMMON_X509_HEADER_ADDR,
            &clientPrms.inPmPrms, &clientPrms.inRmPrms);
    }
    
    /* Enable UART console print*/
    if (ret == CSL_PASS)
    {
        App_sciclientConsoleInit();
    }

    if (ret == CSL_PASS)
    {
        ret = Sciclient_init(&clientPrms);
    }

    if (ret == CSL_PASS)
    {
        ret = Sciclient_init_send_boardcfg(SCICLIENT_CCS_DEVGRP0);
    }
    else
    {
        App_sciclientPrintf("Sciclient_init Send Boardcfg with SCICLIENT_CCS_DEVGRP0..... FAILED\n");
    }
#if defined(SCICLIENT_CCS_DEVGRP1)
    if (ret == CSL_STATUS)
    {
        App_sciclientPrintf("=================================================================\n");
        App_sciclientPrintf("Sciclient Dev Group 01 initilization started\n");
#if CONFIG_BOARDCFG_PM
#if !defined(SOC_J722S)
        App_sciclientPrintf("Power on the MCU-to-MAIN and MAIN-to-MCU... ");
        ret = Sciclient_pmSetModuleState(TISCI_DEV_WKUPMCU2MAIN_VD,
                                         TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                         TISCI_MSG_FLAG_AOP | TISCI_MSG_FLAG_DEVICE_RESET_ISO,
                                         0xFFFFFFFFU);
        ret += Sciclient_pmSetModuleState(TISCI_DEV_MAIN2WKUPMCU_VD,
                                          TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                          TISCI_MSG_FLAG_AOP | TISCI_MSG_FLAG_DEVICE_RESET_ISO,
                                          0xFFFFFFFFU);
        if (ret == CSL_PASS)
        {
            App_sciclientPrintf("PASSED\n");
        }
        else
        {
            App_sciclientPrintf("FAILED\n");
        }
#endif
#endif
    }
    if (ret == CSL_PASS)
    {
        ret = Sciclient_init_send_boardcfg(SCICLIENT_CCS_DEVGRP1);
    }
#endif

    if (ret == CSL_PASS)
    {
        ret = Sciserver_tirtosInitPrms_Init(&appPrms);
    }

    if (ret == CSL_PASS)
    {
        ret = Sciserver_tirtosInit(&appPrms);
    }

    version_str = Sciserver_getVersionStr();
    rmpmhal_version_str = Sciserver_getRmPmHalVersionStr();

    App_sciclientPrintf("Sciserver Testapp Built On: %s %s\n", __DATE__, __TIME__);
    App_sciclientPrintf("Sciserver Version: %s\n", version_str);
    App_sciclientPrintf("RM_PM_HAL Version: %s\n", rmpmhal_version_str);
    if (ret == CSL_PASS)
    {
       App_sciclientPrintf("Starting Sciserver..... PASSED\n");

#if defined (SOC_AM62X) || defined (SOC_AM62A) || defined (SOC_J722S)
        Sciclient_pmGetModuleClkFreq(TISCI_DEV_WKUP_GTC0, TISCI_DEV_WKUP_GTC0_GTC_CLK,
            (uint64_t *) &freqHz, SCICLIENT_SERVICE_WAIT_FOREVER);
#else
        Sciclient_pmGetModuleClkFreq(TISCI_DEV_GTC0, TISCI_DEV_GTC0_GTC_CLK,
            (uint64_t *) &freqHz, SCICLIENT_SERVICE_WAIT_FOREVER);
#endif
       App_sciclientPrintf("GTC freq: %lld\n", freqHz);

#if defined(SOC_J722S)
       /* Enable clocks, set MCU PLL, and enable MCU_R5FSS & core to connect to CPU with the Debugger */
       SOC_moduleClockEnable(TISCI_DEV_MAIN2MCU_VD, 1);
       SOC_moduleClockEnable(TISCI_DEV_MCU_R5FSS0, 1);
       SOC_moduleClockEnable(TISCI_DEV_MCU_TIMER0, 1);
       SOC_moduleClockEnable(TISCI_DEV_MCU_TIMER1, 1);
       SOC_moduleClockEnable(TISCI_DEV_MCU_TIMER2, 1);
       SOC_moduleClockEnable(TISCI_DEV_MCU_TIMER3, 1);
       SOC_moduleClockEnable(TISCI_DEV_MCU_I2C0, 1);
       SOC_moduleClockEnable(TISCI_DEV_MCU_UART0, 1);

       Sciclient_pmGetModuleClkFreq(TISCI_DEV_MCU_UART0, TISCI_DEV_MCU_UART0_FCLK_CLK,
                                    (uint64_t *) &freqHz, SCICLIENT_SERVICE_WAIT_FOREVER);
       App_sciclientPrintf("MCU UART clk freq: %lld\n", freqHz);

       /* Set the MCU R5 clock rate */
       ret = setPLLClk(TISCI_DEV_MCU_R5FSS0_CORE0, TISCI_DEV_MCU_R5FSS0_CORE0_CPU0_CLK, 800000000);
       if (ret == CSL_PASS)
       {
           App_sciclientPrintf("Setting MCU R5FSS0 CPU0 clk freq..... PASSED\n");
       }
       else
       {
           App_sciclientPrintf("Setting MCU R5FSS0 CPU0 clk freq..... FAILED\n");
       }
       ret = Sciclient_pmGetModuleClkFreq(TISCI_DEV_MCU_R5FSS0_CORE0, TISCI_DEV_MCU_R5FSS0_CORE0_CPU0_CLK,
                                          (uint64_t *) &freqHz, SCICLIENT_SERVICE_WAIT_FOREVER);
       if (ret == CSL_PASS)
       {
           App_sciclientPrintf("MCU R5FSS0 CPU0 clk freq: %lld\n", freqHz);
       }


       /* Get ready to enable MCU_R5 CPU0 */
       Sciclient_procBootRequestProcessor(SCICLIENT_PROC_ID_MCU_R5FSS0_CORE0, SCICLIENT_SERVICE_WAIT_FOREVER);
       Sciclient_pmSetModuleState(TISCI_DEV_MCU_R5FSS0_CORE0, TISCI_MSG_VALUE_DEVICE_SW_STATE_AUTO_OFF,
                                  TISCI_MSG_FLAG_AOP, SCICLIENT_SERVICE_WAIT_FOREVER);
       ret = Sciclient_procBootGetProcessorState(SCICLIENT_PROC_ID_MCU_R5FSS0_CORE0, &cpuStatus,
                                                 SCICLIENT_SERVICE_WAIT_FOREVER);
       if (ret != CSL_PASS)
       {
           App_sciclientPrintf("Sciclient_procBootGetProcessorState...FAILED\n");
       }
       proc_set_config_req.processor_id = cpuStatus.processor_id;
       proc_set_config_req.bootvector_lo = cpuStatus.bootvector_lo;
       proc_set_config_req.bootvector_hi = cpuStatus.bootvector_hi;
       proc_set_config_req.config_flags_1_clear = TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_MEM_INIT_DIS;
       proc_set_config_req.config_flags_1_set = (TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_ATCM_EN |
                                                 TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_BTCM_EN |
                                                 TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_TCM_RSTBASE |
                                                 TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_SINGLE_CORE);
       /* Update TCM enable/disable settings */
       Sciclient_procBootSetProcessorCfg(&proc_set_config_req, SCICLIENT_SERVICE_WAIT_FOREVER);
       /* Set HALT bit on the MCU R5 core */
       Sciclient_procBootSetSequenceCtrl(SCICLIENT_PROC_ID_MCU_R5FSS0_CORE0, TISCI_MSG_VAL_PROC_BOOT_CTRL_FLAG_R5_CORE_HALT, 0,
                                         TISCI_MSG_FLAG_AOP, SCICLIENT_SERVICE_WAIT_FOREVER);

       proc_set_config_req.bootvector_lo = 0x0;
       proc_set_config_req.bootvector_hi = 0x0;
       proc_set_config_req.config_flags_1_clear = 0;
       proc_set_config_req.config_flags_1_set = 0;
       Sciclient_procBootSetProcessorCfg(&proc_set_config_req, SCICLIENT_SERVICE_WAIT_FOREVER);
       /* Clear HALT bit on the core */
       Sciclient_procBootSetSequenceCtrl(SCICLIENT_PROC_ID_MCU_R5FSS0_CORE0, 0, TISCI_MSG_VAL_PROC_BOOT_CTRL_FLAG_R5_CORE_HALT,
                                         TISCI_MSG_FLAG_AOP, SCICLIENT_SERVICE_WAIT_FOREVER);
       /* Turn on the MCU R5 core */
       ret = Sciclient_pmSetModuleState(TISCI_DEV_MCU_R5FSS0_CORE0, TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                        TISCI_MSG_FLAG_AOP, SCICLIENT_SERVICE_WAIT_FOREVER);
       /* ret = SOC_moduleClockEnable(TISCI_DEV_MCU_R5FSS0_CORE0, 1); */
       if (ret == CSL_PASS)
       {
           App_sciclientPrintf("Setting PM state ON for TISCI_DEV_MCU_R5FSS0_CORE0..... PASSED\n");
       }
       else
       {
           App_sciclientPrintf("Setting PM state ON for TISCI_DEV_MCU_R5FSS0_CORE0..... FAILED\n");
       }
       /* Release control of the MCU R5 core */
       Sciclient_procBootReleaseProcessor(SCICLIENT_PROC_ID_MCU_R5FSS0_CORE0, TISCI_MSG_FLAG_AOP, SCICLIENT_SERVICE_WAIT_FOREVER);
#endif
    }
    else
    {
        App_sciclientPrintf("Starting Sciserver..... FAILED\n");
    }
    return;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */

#if defined(SOC_J722S)
static int32_t Sciclient_init_send_boardcfg (uint8_t devgrp_curr)
{
    int32_t status = CSL_PASS;
    /* Common Board configuration to set up trace, secure Proxy and
     * MSMC configuration.
     */
#if CONFIG_BOARDCFG
    if (CSL_PASS == status)
    {
        App_sciclientPrintf("\n=================================================================\n");
        App_sciclientPrintf(" DEVGRP = %d\n", devgrp_curr);
        App_sciclientPrintf("=================================================================\n");
        App_sciclientPrintf("SYSFW Common Board Configuration with Debug enabled... ");
        Sciclient_BoardCfgPrms_t boardCfgPrms =
        {
            .boardConfigLow = (uint32_t) &gBoardConfigLow_debug,
            .boardConfigHigh = 0,
            .boardConfigSize = sizeof(gBoardConfigLow_debug),
            .devGrp = devgrp_curr
        };
        status = Sciclient_boardCfg(&boardCfgPrms);
        if (CSL_PASS == status)
        {
            App_sciclientPrintf("PASSED\n");
        }
        else
        {
            App_sciclientPrintf("FAILED\n");
        }
    }
#endif
    /* PM board configuration to setup the PLLs and internal state of
     * the devices.
     */
#if CONFIG_BOARDCFG_PM
    if (CSL_PASS == status)
    {
        uint32_t boardCfgLow[] = SCICLIENT_BOARDCFG_PM;
        Sciclient_BoardCfgPrms_t boardCfgPrms_pm =
        {
            .boardConfigLow = (uint32_t)boardCfgLow,
            .boardConfigHigh = 0,
            .boardConfigSize = 0,
            .devGrp = devgrp_curr
        };
        App_sciclientPrintf("SYSFW PM Board Configuration... ");
        status = Sciclient_boardCfgPm(&boardCfgPrms_pm);
        if (CSL_PASS == status)
        {
            App_sciclientPrintf("PASSED\n");
#if defined(SOC_J722S)
            /* TEMP HACK: trigger deferred PM init w/ dummy request */
            Sciclient_pmSetModuleRst(0xffffffffU, 0, SCICLIENT_SERVICE_WAIT_FOREVER);
            App_sciclientPrintf("!! Completed PM deferred init!!\n");
#endif
        }
        else
        {
            App_sciclientPrintf("FAILED\n");
        }
    }
#endif
    /* RM Board configuration to define the use of Resources allocated
     * to each core.
     */
#if CONFIG_BOARDCFG_RM
    if (status == CSL_PASS)
    {
        uint32_t boardCfgLow[] = SCICLIENT_BOARDCFG_RM;
        Sciclient_BoardCfgPrms_t boardCfgPrms_rm =
        {
            .boardConfigLow = (uint32_t) boardCfgLow,
            .boardConfigHigh = 0,
            .boardConfigSize = SCICLIENT_BOARDCFG_RM_SIZE_IN_BYTES,
            .devGrp = devgrp_curr
        };
        App_sciclientPrintf("SYSFW RM Board Configuration... ");
        status = Sciclient_boardCfgRm(&boardCfgPrms_rm);
        if (CSL_PASS == status)
        {
            App_sciclientPrintf("PASSED\n");
        }
        else
        {
            App_sciclientPrintf("FAILED\n");
        }
    }
#endif
    /* Security board configuration for the security subsystem init */
#if CONFIG_BOARDCFG_SECURITY
    if (status == CSL_PASS)
    {
        uint32_t boardCfgLow[] = SCICLIENT_BOARDCFG_SECURITY;
        Sciclient_BoardCfgPrms_t boardCfgPrms_security =
        {
            .boardConfigLow = (uint32_t) boardCfgLow,
            .boardConfigHigh = 0,
            .boardConfigSize = SCICLIENT_BOARDCFG_SECURITY_SIZE_IN_BYTES,
            .devGrp = devgrp_curr
        };
        App_sciclientPrintf("SYSFW Security Board Configuration... ");
        status = Sciclient_boardCfgSec(&boardCfgPrms_security) ;
        if (CSL_PASS == status)
        {
            App_sciclientPrintf("PASSED\n");
        }
        else
        {
            App_sciclientPrintf("FAILED\n");
        }
    }
#endif
    return status;
}

static int32_t SOC_moduleClockEnable(uint32_t moduleId, uint32_t enable)
{
    int32_t status = CSL_PASS;
    uint32_t moduleState = TISCI_MSG_VALUE_DEVICE_HW_STATE_TRANS;
    uint32_t resetState = 0U;
    uint32_t contextLossState = 0U;


    /* Get the module state.
       No need to change the module state if it
       is already in the required state
     */
    status = Sciclient_pmGetModuleState(moduleId,
                                        &moduleState,
                                        &resetState,
                                        &contextLossState,
                                        SCICLIENT_SERVICE_WAIT_FOREVER);
    if(status == CSL_PASS)
    {
        if(moduleState == TISCI_MSG_VALUE_DEVICE_HW_STATE_OFF && (enable == 1))
        {
            /* enable the module */
            status = Sciclient_pmSetModuleState(moduleId,
                                                TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                                (TISCI_MSG_FLAG_AOP |
                                                TISCI_MSG_FLAG_DEVICE_RESET_ISO),
                                                SCICLIENT_SERVICE_WAIT_FOREVER);
            if (status == CSL_PASS)
            {
                status = Sciclient_pmSetModuleRst(moduleId,
                                                0x0U,
                                                SCICLIENT_SERVICE_WAIT_FOREVER);
            }
        }
        else
        if(moduleState == TISCI_MSG_VALUE_DEVICE_HW_STATE_ON && (enable == 0))
        {
            /* disable the module */
            status = Sciclient_pmSetModuleState(moduleId,
                                                TISCI_MSG_VALUE_DEVICE_SW_STATE_AUTO_OFF,
                                                (TISCI_MSG_FLAG_AOP),
                                                SCICLIENT_SERVICE_WAIT_FOREVER);
        }
    }
    return status;
}

/**
 * \brief  PLL clock configuration
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
static int32_t setPLLClk(uint32_t modId,
                             uint32_t clkId,
                             uint64_t clkRate)
{
    uint32_t i = 0U;
    int32_t status = 0;
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

    if(status == CSL_PASS)
    {
        /* Check the number of parents for the clock */
        status = Sciclient_pmGetModuleClkNumParent(modId,
                                                   clkId,
                                                   &numParents,
                                                   SCICLIENT_SERVICE_WAIT_FOREVER);
    }
    if ((status == CSL_PASS) && (numParents > 1U))
    {
        status = Sciclient_pmGetModuleClkParent(modId, clkId, &origParent,
                                       SCICLIENT_SERVICE_WAIT_FOREVER);
    }
    if (status == CSL_PASS)
    {
        /* Disabling the clock */
        status = Sciclient_pmModuleClkRequest(modId,
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
                status = Sciclient_pmSetModuleClkParent(modId,
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
            }
            if (foundParent)
            {
                break;
            }
        }
    }
    if (foundParent == 1U)
    {
        /* Set the clock at the desirable frequency*/
        status = Sciclient_pmSetModuleClkFreq(modId,
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
        status = Sciclient_pmModuleClkRequest(modId,
                                              clkId,
                                              clockStatus,
                                              0U,
                                              SCICLIENT_SERVICE_WAIT_FOREVER);
    }
    if ((status != CSL_PASS) && (moduleClockParentChanged == 1U))
    {
        /* Setting the original parent if failure */
        Sciclient_pmSetModuleClkParent(modId,
                                       clkId,
                                       origParent,
                                       SCICLIENT_SERVICE_WAIT_FOREVER);
    }
    return status;
}
#endif

