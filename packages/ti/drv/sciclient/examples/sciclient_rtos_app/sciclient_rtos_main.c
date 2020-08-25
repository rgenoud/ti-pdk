/*
 *  Copyright (C) 2017-2018 Texas Instruments Incorporated
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
 *  \file sciclient_rtos_main.c
 *
 *  \brief Implementation of tests for RTOS
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifndef BARE_METAL
/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#if defined (__aarch64__)
#include <ti/sysbios/family/arm/v8a/Mmu.h>
#endif
#endif

#include <stdint.h>
#include <string.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/hw_types.h>
#include <sciclient_appCommon.h>
#include <ti/sysbios/knl/Clock.h>

#if defined (__C7100__)
#include <ti/sysbios/family/c7x/Mmu.h>
#endif

#include <ti/board/board.h>

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

void GetClkFreq(UArg arg0, UArg arg1);
void appReset(void);

/**
 * \brief   Set the interrupt config for C66x Timer interrupts.
 *
 * \param   None.
 *
 * \return  None
 */
void App_sciclientC66xIntrConfig(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void appReset(void)
{
}

int main(void)
{
    Task_Handle task;
    Task_Params taskParams;
    Task_Params_init(&taskParams);
    taskParams.priority = 15;
    Error_Block eb;

    App_SciclientC7xPreInit();

    uint32_t    retVal = CSL_PASS;

    Error_init(&eb);
    App_sciclientC66xIntrConfig();

    task = Task_create(GetClkFreq, &taskParams, &eb);
    if (task == NULL)
    {
        BIOS_exit(0);
    }
    /* Start BIOS */
    BIOS_start();

    return retVal;
}

int32_t PsilPair()
{
    int32_t status = CSL_PASS;

    struct tisci_msg_rm_psil_pair_req request;
    request.nav_id = 199; //J721E_DEV_NAVSS0,
    request.src_thread = 0x1040;
    request.dst_thread = 0x1041 + 0x8000;
    const Sciclient_ReqPrm_t      reqPrm =
    {
        TISCI_MSG_RM_PSIL_PAIR,
        TISCI_MSG_FLAG_AOP,
        (uint8_t *) &request,
        sizeof(request),
        SCICLIENT_SERVICE_WAIT_FOREVER
    };

    struct tisci_msg_rm_psil_pair_resp response;
    Sciclient_RespPrm_t           respPrm =
    {
        0,
        (uint8_t *) &response,
        sizeof (response)
    };

    status = Sciclient_service(&reqPrm, &respPrm);
    UART_printf("PsilPair: done. status =%d\n", status);

    return status;
}

int32_t PsilUnpair()
{
    int32_t status = CSL_PASS;

    struct tisci_msg_rm_psil_unpair_req request;
    request.nav_id = 199; //J721E_DEV_NAVSS0,
    request.src_thread = 0x1040;
    request.dst_thread = 0x1041 + 0x8000;
    const Sciclient_ReqPrm_t      reqPrm =
    {
        TISCI_MSG_RM_PSIL_UNPAIR,
        TISCI_MSG_FLAG_AOP,
        (uint8_t *) &request,
        sizeof(request),
        SCICLIENT_SERVICE_WAIT_FOREVER
    };

    struct tisci_msg_rm_psil_unpair_resp response;
    Sciclient_RespPrm_t           respPrm =
    {
        0,
        (uint8_t *) &response,
        sizeof (response)
    };

    status = Sciclient_service(&reqPrm, &respPrm);
    UART_printf("PsilUnpair: done. status =%d\n", status);

    return status;
}

int32_t RmProxyCfg()
{
    int32_t status = CSL_PASS;

    struct tisci_msg_rm_proxy_cfg_req request;
    // request.nav_id = 234; //J721E_DEV_MCU_NAVSS0_PROXY0
    request.nav_id = 210; //J721E_DEV_NAVSS0_PROXY_0
    request.index = 36;
    const Sciclient_ReqPrm_t      reqPrm =
    {
        TISCI_MSG_RM_PROXY_CFG,
        TISCI_MSG_FLAG_AOP,
        (uint8_t *) &request,
        sizeof(request),
        SCICLIENT_SERVICE_WAIT_FOREVER
    };

    struct tisci_msg_rm_proxy_cfg_resp response;
    Sciclient_RespPrm_t           respPrm =
    {
        0,
        (uint8_t *) &response,
        sizeof (response)
    };

    status = Sciclient_service(&reqPrm, &respPrm);
    UART_printf("RmProxyCfg: done. status =%d\n", status);

    return status;
}

int32_t RmGetResourceRange(
    uint16_t            type,
    uint8_t            subtype,
    uint8_t            secondary_host)
{
    int32_t status = CSL_PASS;

    struct tisci_msg_rm_get_resource_range_req request;
    request.type = type;
    request.subtype = subtype;
    request.secondary_host = secondary_host;
    const Sciclient_ReqPrm_t      reqPrm =
    {
        TISCI_MSG_RM_GET_RESOURCE_RANGE,
        TISCI_MSG_FLAG_AOP,
        (uint8_t *) &request,
        sizeof(request),
        SCICLIENT_SERVICE_WAIT_FOREVER
    };

    struct tisci_msg_rm_get_resource_range_resp response;
    Sciclient_RespPrm_t           respPrm =
    {
        0,
        (uint8_t *) &response,
        sizeof (response)
    };

    status = Sciclient_service(&reqPrm, &respPrm);
    UART_printf("RmGetResourceRange: done. status =%d\n", status);

    return status;
}

void GetClkFreq(UArg arg0, UArg arg1)
{
    int32_t status = CSL_PASS;
    volatile uint32_t loopForever = 1U;

    Board_initCfg           boardCfg;

    Sciclient_ConfigPrms_t config;
    Sciclient_configPrmsInit(&config);
    config.isSecureMode = 1;
    status = Sciclient_init(&config);

    boardCfg = BOARD_INIT_PINMUX_CONFIG |
               BOARD_INIT_UART_STDIO;
    Board_init(boardCfg);

    uint32_t modId = 83; //J721E_DEV_EHRPWM0;
    uint8_t clkId = 0; //J721E_DEV_EHRPWM0_VBUSP_CLK;
    uint32_t freqHz;

    // Sciclient_ConfigPrms_t        config =
    // {
    //     SCICLIENT_SERVICE_OPERATION_MODE_POLLED,
    //     NULL,
    //     1
    // };

    struct tisci_msg_get_freq_req request;
    request.device = (uint32_t) modId;
    request.clk    = (uint8_t) clkId;
    const Sciclient_ReqPrm_t      reqPrm =
    {
        TISCI_MSG_GET_FREQ,
        TISCI_MSG_FLAG_AOP,
        (uint8_t *) &request,
        sizeof(request),
        SCICLIENT_SERVICE_WAIT_FOREVER
    };

    struct tisci_msg_get_freq_resp response;
    Sciclient_RespPrm_t           respPrm =
    {
        0,
        (uint8_t *) &response,
        sizeof (response)
    };

    // status = Sciclient_init(&config);
    if (status == CSL_PASS)
    {
        // App_sciclientConsoleInit();
        UART_printf("RTOS application2\n");

        status = RmProxyCfg();
        RmGetResourceRange(213, 0, 36);
        RmGetResourceRange(213, 0, 128);

        status = PsilPair();
        status = PsilUnpair();

        request.device = 264; //J721E_DEV_SA2_UL0
        request.clk = 0; //J721E_DEV_SA2_UL0_X2_CLK

        App_sciclientPrintf("SCIClient GetClkFreq\n");

        status = Sciclient_service(&reqPrm, &respPrm);
        freqHz = (uint32_t) (response.freq_hz & 0xFFFFFFFF);
        UART_printf("Freq = %d MHz\n", freqHz / 1000000);

        status = Sciclient_service(&reqPrm, &respPrm);
        freqHz = (uint32_t) (response.freq_hz & 0xFFFFFFFF);
        UART_printf("Freq2 = %d MHz\n", freqHz / 1000000);
    }
}

#if defined(BUILD_MPU) || defined (__C7100__)
extern void Osal_initMmuDefault(void);
void InitMmu(void)
{
    Osal_initMmuDefault();
}
#endif

