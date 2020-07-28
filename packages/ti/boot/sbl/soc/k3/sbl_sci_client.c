/*
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
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
#include <ti/csl/tistdtypes.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/hw_types.h>
#include <ti/drv/uart/UART_stdio.h>
#include <ti/drv/uart/soc/UART_soc.h>
#include <ti/board/board.h>
#include <sbl_soc.h>
#include <sbl_soc_cfg.h>
#include <sbl_err_trap.h>
#include <sbl_sci_client.h>

#if defined(SBL_ENABLE_HLOS_BOOT)
#if defined(SOC_J721E)
const uint32_t gSciclient_boardCfgLow_hlos_rm[(SCICLIENT_BOARDCFG_RM_LINUX_SIZE_IN_BYTES+3U)/4U]
    __attribute__(( aligned(128), section(".boardcfg_data") ))
    = SCICLIENT_BOARDCFG_RM_LINUX;
#endif
#endif

#ifdef __cplusplus
#pragma DATA_SECTION(".firmware")
#else
#pragma WEAK (SBL_ReadSysfwImage)
#pragma DATA_SECTION(gSciclient_firmware, ".firmware")
#endif
uint32_t gSciclient_firmware[1];

#if SCICLIENT_FIRMWARE_SIZE_IN_BYTES > SBL_SYSFW_MAX_SIZE
#error "SYSFW too large...update SBL_SYSFW_MAX_SIZE"
#endif

uint32_t SBL_IsAuthReq(void)
{
    uint32_t retVal = SBL_ALWAYS_AUTH_APP;
    uint32_t dev_type;
    uint32_t dev_subtype;

    SBL_ADD_PROFILE_POINT;

    dev_type = CSL_REG32_RD(SBL_SYS_STATUS_REG) & SBL_SYS_STATUS_DEV_TYPE_MASK;
    dev_subtype = CSL_REG32_RD(SBL_SYS_STATUS_REG) & SBL_SYS_STATUS_DEV_SUBTYPE_MASK;

    /* No auth possible, if valid SMPK/BMPK is not present */
    if ((dev_subtype == SBL_SYS_STATUS_DEV_SUBTYPE_FS) ||
        (dev_type == SBL_SYS_STATUS_DEV_TYPE_GP) ||
        (dev_type == SBL_SYS_STATUS_DEV_TYPE_TEST))
    {
        retVal = SBL_NEVER_AUTH_APP;
    }

    SBL_ADD_PROFILE_POINT;

    return retVal;
}

void SBL_SciClientInit(void)
{
    int32_t status = CSL_EFAIL;
    void *sysfw_ptr = gSciclient_firmware;

#ifndef SBL_SKIP_SYSFW_INIT
    /* SYSFW board configurations */
    Sciclient_DefaultBoardCfgInfo_t boardCfgInfo;
    Sciclient_BoardCfgPrms_t sblBoardCfgPrms;
    Sciclient_BoardCfgPrms_t sblBoardCfgPmPrms;
    Sciclient_BoardCfgPrms_t sblBoardCfgRmPrms;
#ifndef SBL_SKIP_BRD_CFG_SEC
    Sciclient_BoardCfgPrms_t sblBoardCfgSecPrms;
#endif
    Sciclient_ConfigPrms_t        config =
    {
        SCICLIENT_SERVICE_OPERATION_MODE_POLLED,
    };
#endif

    SBL_ADD_PROFILE_POINT;

    status = SBL_ReadSysfwImage(&sysfw_ptr, SBL_SYSFW_MAX_SIZE);
    if (status != CSL_PASS)
    {
        SBL_log(SBL_LOG_ERR,"SYSFW read...FAILED \n");
        SblErrLoop(__FILE__, __LINE__);
    }

#ifndef SBL_SKIP_SYSFW_INIT
    SBL_ADD_PROFILE_POINT;

    status = Sciclient_getDefaultBoardCfgInfo(&boardCfgInfo);

#if defined(SBL_ENABLE_HLOS_BOOT)
#if defined(SOC_J721E)
    /* Replace default Sciclient boardCfgLowRm with alternate version for HLOS boot */
	boardCfgInfo.boardCfgLowRm     = &gSciclient_boardCfgLow_hlos_rm[0U];
	boardCfgInfo.boardCfgLowRmSize = SCICLIENT_BOARDCFG_RM_LINUX_SIZE_IN_BYTES;
#endif
#endif

    if (status != CSL_PASS)
    {
        SBL_log(SBL_LOG_ERR,"SYSFW get default board config...FAILED \n");
        SblErrLoop(__FILE__, __LINE__);
    }

    status = Sciclient_loadFirmware((const uint32_t *) sysfw_ptr);
    if (status != CSL_PASS)
    {
        SBL_log(SBL_LOG_ERR,"SYSFW load...FAILED \n");
        SblErrLoop(__FILE__, __LINE__);
    }

    SBL_ADD_PROFILE_POINT;
    status = Sciclient_init(&config);
    if (status != CSL_PASS)
    {
        SBL_log(SBL_LOG_ERR,"SYSFW init ...FAILED \n");
        SblErrLoop(__FILE__, __LINE__);
    }

#ifndef SBL_SKIP_BRD_CFG_BOARD
    SBL_ADD_PROFILE_POINT;
    sblBoardCfgPrms.boardConfigLow = (uint32_t)boardCfgInfo.boardCfgLow;
    sblBoardCfgPrms.boardConfigHigh = 0;
    sblBoardCfgPrms.boardConfigSize = boardCfgInfo.boardCfgLowSize;
    sblBoardCfgPrms.devGrp = SBL_DEVGRP;
    status = Sciclient_boardCfg(&sblBoardCfgPrms);
    if (status != CSL_PASS)
    {
        SBL_log(SBL_LOG_ERR,"SYSFW board config ...FAILED \n");
        SblErrLoop(__FILE__, __LINE__);
    }
#endif

#ifndef SBL_SKIP_BRD_CFG_PM
    if (SBL_LOG_LEVEL > SBL_LOG_NONE)
    {
        SBL_ADD_PROFILE_POINT;
        UART_stdioDeInit();
    }
    SBL_ADD_PROFILE_POINT;
    sblBoardCfgPmPrms.boardConfigLow = (uint32_t)boardCfgInfo.boardCfgLowPm;
    sblBoardCfgPmPrms.boardConfigHigh = 0;
    sblBoardCfgPmPrms.boardConfigSize = boardCfgInfo.boardCfgLowPmSize;
    sblBoardCfgPmPrms.devGrp = SBL_DEVGRP;
    status = Sciclient_boardCfgPm(&sblBoardCfgPmPrms);
    if (status != CSL_PASS)
    {
        SBL_log(SBL_LOG_ERR,"SYSFW board config pm...FAILED \n")
        SblErrLoop(__FILE__, __LINE__);
    }

    if (SBL_LOG_LEVEL > SBL_LOG_NONE)
    {
        /* Re-init UART for logging */
        UART_HwAttrs uart_cfg;

        SBL_ADD_PROFILE_POINT;
        UART_socGetInitCfg(BOARD_UART_INSTANCE, &uart_cfg);
        uart_cfg.frequency = SBL_SYSFW_UART_MODULE_INPUT_CLK;
        UART_socSetInitCfg(BOARD_UART_INSTANCE, &uart_cfg);
        UART_stdioInit(BOARD_UART_INSTANCE);
    }
#endif

#ifndef SBL_SKIP_BRD_CFG_RM
    SBL_ADD_PROFILE_POINT;
    sblBoardCfgRmPrms.boardConfigLow = (uint32_t)boardCfgInfo.boardCfgLowRm;
    sblBoardCfgRmPrms.boardConfigHigh = 0;
    sblBoardCfgRmPrms.boardConfigSize = boardCfgInfo.boardCfgLowRmSize;
    sblBoardCfgRmPrms.devGrp = SBL_DEVGRP;
    status = Sciclient_boardCfgRm(&sblBoardCfgRmPrms);
    if (status != CSL_PASS)
    {
        SBL_log(SBL_LOG_ERR,"SYSFW board config rm...FAILED \n");
        SblErrLoop(__FILE__, __LINE__);
    }
#endif

#ifndef SBL_SKIP_BRD_CFG_SEC
    SBL_ADD_PROFILE_POINT;
    sblBoardCfgSecPrms.boardConfigLow = (uint32_t)boardCfgInfo.boardCfgLowSec;
    sblBoardCfgSecPrms.boardConfigHigh = 0;
    sblBoardCfgSecPrms.boardConfigSize = boardCfgInfo.boardCfgLowSecSize;
    sblBoardCfgSecPrms.devGrp = SBL_DEVGRP;
    status = Sciclient_boardCfgSec(&sblBoardCfgSecPrms);
    if (status != CSL_PASS)
    {
        SBL_log(SBL_LOG_ERR,"SYSFW board config sec...FAILED \n");
        SblErrLoop(__FILE__, __LINE__);
    }
#endif

    /* Get SYSFW version */
    SBL_ADD_PROFILE_POINT;

    if (SBL_LOG_LEVEL > SBL_LOG_ERR)
    {
        struct tisci_msg_version_req req = {0};
        const Sciclient_ReqPrm_t      reqPrm =
        {
            TISCI_MSG_VERSION,
            TISCI_MSG_FLAG_AOP,
            (const uint8_t *)&req,
            sizeof(req),
            SCICLIENT_SERVICE_WAIT_FOREVER
        };

        struct tisci_msg_version_resp response;
        Sciclient_RespPrm_t           respPrm =
        {
            0,
            (uint8_t *) &response,
            (uint32_t)sizeof (response)
        };

        status = Sciclient_service(&reqPrm, &respPrm);
        if (CSL_PASS == status)
        {
            if (respPrm.flags == (uint32_t)TISCI_MSG_FLAG_ACK)
            {
                SBL_ADD_PROFILE_POINT;
                SBL_log(SBL_LOG_MIN,"SYSFW  ver: %s\n", (char *) response.str);
            }
            else
            {
                SBL_log(SBL_LOG_ERR,"SYSFW Get Version failed \n");
                SblErrLoop(__FILE__, __LINE__);
            }
        }
    }

#if !defined(SBL_SKIP_MCU_RESET)
    /* RTI seems to be turned on by ROM. Turning it off so that Power domain can transition */
    Sciclient_pmSetModuleState(SBL_DEV_ID_RTI0, TISCI_MSG_VALUE_DEVICE_SW_STATE_AUTO_OFF, TISCI_MSG_FLAG_AOP, SCICLIENT_SERVICE_WAIT_FOREVER);
    Sciclient_pmSetModuleState(SBL_DEV_ID_RTI1, TISCI_MSG_VALUE_DEVICE_SW_STATE_AUTO_OFF, TISCI_MSG_FLAG_AOP, SCICLIENT_SERVICE_WAIT_FOREVER);
#if defined(SOC_AM64X)
    Sciclient_pmSetModuleState(SBL_DEV_ID_RTI8, TISCI_MSG_VALUE_DEVICE_SW_STATE_AUTO_OFF, TISCI_MSG_FLAG_AOP, SCICLIENT_SERVICE_WAIT_FOREVER);
    Sciclient_pmSetModuleState(SBL_DEV_ID_RTI9, TISCI_MSG_VALUE_DEVICE_SW_STATE_AUTO_OFF, TISCI_MSG_FLAG_AOP, SCICLIENT_SERVICE_WAIT_FOREVER);
    Sciclient_pmSetModuleState(SBL_DEV_ID_RTI10, TISCI_MSG_VALUE_DEVICE_SW_STATE_AUTO_OFF, TISCI_MSG_FLAG_AOP, SCICLIENT_SERVICE_WAIT_FOREVER);
    Sciclient_pmSetModuleState(SBL_DEV_ID_RTI11, TISCI_MSG_VALUE_DEVICE_SW_STATE_AUTO_OFF, TISCI_MSG_FLAG_AOP, SCICLIENT_SERVICE_WAIT_FOREVER);
    Sciclient_pmSetModuleState(SBL_DEV_ID_MCU_RTI0, TISCI_MSG_VALUE_DEVICE_SW_STATE_AUTO_OFF, TISCI_MSG_FLAG_AOP, SCICLIENT_SERVICE_WAIT_FOREVER);
#endif
#endif


#endif

    SBL_ADD_PROFILE_POINT;
}
