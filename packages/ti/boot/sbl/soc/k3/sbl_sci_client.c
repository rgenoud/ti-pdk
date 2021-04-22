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

#if (!defined(SBL_SKIP_BRD_CFG_PM)) || (!defined(SBL_SKIP_BRD_CFG_RM))
static int32_t Sciclient_setBoardConfigHeader ();
#endif
#if defined(SOC_AM65XX) || defined(SOC_J721E) || defined(SOC_J7200)
/* Firewall ID for MCU_FSS0_S0 */
#define MCU_FSS0_S0_FWID (1036)
#define MCU_FSS0_S0_FW_REGIONS (8)

#if defined (SOC_J721E) || defined (SOC_J7200)
/** \brief Aligned address at which the X509 header is placed. */
#define SCISERVER_COMMON_X509_HEADER_ADDR (0x41cffb00U)

/** \brief Aligned address at which the Board Config header is placed. */
#define SCISERVER_BOARDCONFIG_HEADER_ADDR (0x41c80000U)

/** \brief Aligned address at which the Board Config is placed. */
#define SCISERVER_BOARDCONFIG_DATA_ADDR (0x41c80040U)

#endif
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

#ifndef SBL_SKIP_SYSFW_INIT
Sciclient_BoardCfgPrms_t sblBoardCfgPrms = {0};
Sciclient_BoardCfgPrms_t sblBoardCfgPmPrms = {0};
Sciclient_BoardCfgPrms_t sblBoardCfgRmPrms = {0};
#ifndef SBL_SKIP_BRD_CFG_SEC
Sciclient_BoardCfgPrms_t sblBoardCfgSecPrms = {0};
#endif
#endif

#ifndef SBL_SKIP_BRD_CFG_RM
uint16_t gCertLength = 0;
#endif
static uint16_t boardcfgRmFindCertSize(uint32_t *msg_recv)
{
    uint16_t cert_len = 0;
    uint8_t *cert_len_ptr = (uint8_t *)&cert_len;
    uint8_t *x509_cert_ptr;

    x509_cert_ptr = (uint8_t *)msg_recv;


    if (*x509_cert_ptr != 0x30)
    {
        /* The data does not contain a certificate - return */
        return 0;
    }

    cert_len = *(x509_cert_ptr + 1);

    /* If you need more than 2 bytes to store the cert length  */
    /* it means that the cert length is greater than 64 Kbytes */
    /* and we do not support it                                */
    if ((cert_len > 0x80) &&
        (cert_len != 0x82))
    {
        return 0;
    }

    if (cert_len == 0x82)
    {
        *cert_len_ptr = *(x509_cert_ptr + 3);
        *(cert_len_ptr + 1) = *(x509_cert_ptr + 2);

        /* add current offset from start of x509 cert */
        cert_len += 3;
    }
    else
    {
        /* add current offset from start of x509 cert  */
        /* if cert len was obtained from 2nd byte i.e. */
        /* cert size is 127 bytes or less              */
        cert_len += 1;
    }

    /* cert_len now contains the offset of the last byte */
    /* of the cert from the ccert_start. To get the size */
    /* of certificate, add 1                             */

    return cert_len + 1;
}

void SBL_SciClientInit(void)
{
    int32_t status = CSL_EFAIL;
    void *sysfw_ptr = gSciclient_firmware;

#ifndef SBL_SKIP_SYSFW_INIT
    /* SYSFW board configurations */
    Sciclient_DefaultBoardCfgInfo_t boardCfgInfo;
    Sciclient_ConfigPrms_t config;
    Sciclient_configPrmsInit(&config);
    config.opModeFlag               =   SCICLIENT_SERVICE_OPERATION_MODE_POLLED;
    config.pBoardCfgPrms            =   NULL;
    config.isSecureMode             =   0; /* default board cfg is for non-secure mode */
    config.c66xRatRegion            =   0;
    config.skipLocalBoardCfgProcess =   TRUE;
#endif

    SBL_ADD_PROFILE_POINT;

    status = SBL_ReadSysfwImage(&sysfw_ptr, SBL_SYSFW_MAX_SIZE);
    if (status != CSL_PASS)
    {
#if defined(SOC_J721E) || defined(SOC_J7200)
        SBL_log(SBL_LOG_ERR,"TIFS read...FAILED \n");
#else
        SBL_log(SBL_LOG_ERR,"SYSFW read...FAILED \n");
#endif
        SblErrLoop(__FILE__, __LINE__);
    }

#ifndef SBL_SKIP_SYSFW_INIT
    SBL_ADD_PROFILE_POINT;

    status = Sciclient_getDefaultBoardCfgInfo(&boardCfgInfo);

    if (status != CSL_PASS)
    {
        SBL_log(SBL_LOG_ERR,"Sciclient get default board config...FAILED \n");
        SblErrLoop(__FILE__, __LINE__);
    }

    status = Sciclient_loadFirmware((const uint32_t *) sysfw_ptr);
    if (status != CSL_PASS)
    {
#if defined(SOC_J721E) || defined(SOC_J7200)
        SBL_log(SBL_LOG_ERR,"TIFS load...FAILED \n");
#else
        SBL_log(SBL_LOG_ERR,"SYSFW load...FAILED \n");
#endif
        SblErrLoop(__FILE__, __LINE__);
    }

    SBL_ADD_PROFILE_POINT;
    status = Sciclient_init(&config);
    if (status != CSL_PASS)
    {
        SBL_log(SBL_LOG_ERR,"Sciclient init ...FAILED \n");
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
        SBL_log(SBL_LOG_ERR,"Sciclient board config ...FAILED \n");
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
        SBL_log(SBL_LOG_ERR,"Sciclient board config pm...FAILED \n")
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

#ifndef SBL_SKIP_BRD_CFG_SEC
    SBL_ADD_PROFILE_POINT;
    sblBoardCfgSecPrms.boardConfigLow = (uint32_t)boardCfgInfo.boardCfgLowSec;
    sblBoardCfgSecPrms.boardConfigHigh = 0;
    sblBoardCfgSecPrms.boardConfigSize = boardCfgInfo.boardCfgLowSecSize;
    sblBoardCfgSecPrms.devGrp = SBL_DEVGRP;
    status = Sciclient_boardCfgSec(&sblBoardCfgSecPrms);
    if (status != CSL_PASS)
    {
        SBL_log(SBL_LOG_ERR,"Sciclient board config sec...FAILED \n");
        SblErrLoop(__FILE__, __LINE__);
    }
#if defined(SOC_AM65XX) || defined(SOC_J721E) || defined(SOC_J7200)
    /* Secure ROM has left firewall regions for FSS DAT0 set.  Disable them for DMA usage. */
    uint16_t i;
    struct tisci_msg_fwl_set_firewall_region_resp respFwCtrl = {0};
    struct tisci_msg_fwl_set_firewall_region_req reqFwCtrl =
    {
        .fwl_id = (uint16_t) MCU_FSS0_S0_FWID,
        .region = (uint16_t) 0,
        .n_permission_regs = (uint32_t) 3,
        /* Set .control to zero to disable the firewall region */
        .control = (uint32_t) 0,
        .permissions[0] = (uint32_t) 0,
        .permissions[1] = (uint32_t) 0,
        .permissions[2] = (uint32_t) 0,
        .start_address = 0,
        .end_address = 0
    };

    for (i = 0; i < MCU_FSS0_S0_FW_REGIONS; i++)
    {
        reqFwCtrl.region = i;
        status = Sciclient_firewallSetRegion(&reqFwCtrl, &respFwCtrl, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status != CSL_PASS)
        {
            SBL_log(SBL_LOG_ERR,"MCU FSS0_S0 firewall region # %d disable...FAILED \n", i);
        }
    }
#endif
#endif

#ifndef SBL_SKIP_BRD_CFG_RM
    SBL_ADD_PROFILE_POINT;
    sblBoardCfgRmPrms.boardConfigLow = (uint32_t)boardCfgInfo.boardCfgLowRm;
    sblBoardCfgRmPrms.boardConfigHigh = 0;
    sblBoardCfgRmPrms.boardConfigSize = boardCfgInfo.boardCfgLowRmSize;
    sblBoardCfgRmPrms.devGrp = SBL_DEVGRP;
    gCertLength = boardcfgRmFindCertSize((uint32_t*)boardCfgInfo.boardCfgLowRm);
    status = Sciclient_boardCfgRm(&sblBoardCfgRmPrms);
    if (status != CSL_PASS)
    {
        SBL_log(SBL_LOG_ERR,"Sciclient board config rm...FAILED \n");
        SblErrLoop(__FILE__, __LINE__);
    }
#endif

    /* Get SYSFW/TIFS version */
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
#if defined(SOC_J721E) || defined(SOC_J7200)
                SBL_log(SBL_LOG_MIN,"TIFS  ver: %s\n", (char *) response.str);
#else
                SBL_log(SBL_LOG_MIN,"SYSFW  ver: %s\n", (char *) response.str);
#endif
            }
            else
            {
#if defined(SOC_J721E) || defined(SOC_J7200)
                SBL_log(SBL_LOG_ERR,"TIFS Get Version failed \n");
#else
                SBL_log(SBL_LOG_ERR,"SYSFW Get Version failed \n");
#endif
                SblErrLoop(__FILE__, __LINE__);
            }
        }
    }


#if (!defined(SBL_SKIP_BRD_CFG_PM)) || (!defined(SBL_SKIP_BRD_CFG_RM))
    status = Sciclient_setBoardConfigHeader();
    if (CSL_PASS == status)
    {
        SBL_log(SBL_LOG_MAX,"Sciclient_setBoardConfigHeader... PASSED\n");
    }
    else
    {
        SBL_log(SBL_LOG_ERR,"Sciclient_setBoardConfigHeader... FAILED\n");
        SblErrLoop(__FILE__, __LINE__);
    }
#endif


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

#if (!defined(SBL_SKIP_BRD_CFG_PM)) || (!defined(SBL_SKIP_BRD_CFG_RM))
static int32_t Sciclient_setBoardConfigHeader ()
{
    int32_t status = CSL_PASS;
#if defined (SOC_J7200) || defined (SOC_J721E)
    //uint32_t alignedOffset = ((SCICLIENT_BOARDCFG_PM_SIZE_IN_BYTES + 128U)/128U)*128U;
    uint32_t alignedOffset = SCICLIENT_BOARDCFG_PM_SIZE_IN_BYTES;
    Sciclient_BoardCfgPrms_t boardCfgPrms_pm =
    {
        .boardConfigLow = (uint32_t)SCISERVER_BOARDCONFIG_DATA_ADDR,
        .boardConfigHigh = 0,
        .boardConfigSize = (uint16_t)SCICLIENT_BOARDCFG_PM_SIZE_IN_BYTES,
        .devGrp = DEVGRP_ALL
    };
    Sciclient_BoardCfgPrms_t boardCfgPrms_rm =
    {
        .boardConfigLow =
            (uint32_t) SCISERVER_BOARDCONFIG_DATA_ADDR + alignedOffset,
        .boardConfigHigh = 0,
        .boardConfigSize = (uint16_t)SCICLIENT_BOARDCFG_RM_SIZE_IN_BYTES - gCertLength,
        .devGrp = DEVGRP_ALL
    };
    status = Sciclient_boardCfgPrepHeader (
        (uint8_t *) SCISERVER_COMMON_X509_HEADER_ADDR,
        (uint8_t *) SCISERVER_BOARDCONFIG_HEADER_ADDR,
        &boardCfgPrms_pm, &boardCfgPrms_rm);
    if (CSL_PASS == status)
    {
        SBL_log(SBL_LOG_MAX,"SCISERVER Board Configuration header population... ");
        SBL_log(SBL_LOG_MAX,"PASSED\n");
    }
    else
    {
        SBL_log(SBL_LOG_MIN,"SCISERVER Board Configuration header population... ");
        SBL_log(SBL_LOG_MIN,"FAILED\n");
    }
    memcpy((void *)boardCfgPrms_pm.boardConfigLow, (void *) sblBoardCfgPmPrms.boardConfigLow, SCICLIENT_BOARDCFG_PM_SIZE_IN_BYTES);
    memcpy((void *)boardCfgPrms_rm.boardConfigLow, (void *) sblBoardCfgRmPrms.boardConfigLow, SCICLIENT_BOARDCFG_RM_SIZE_IN_BYTES - gCertLength);
#endif
    return status;
}
#endif
