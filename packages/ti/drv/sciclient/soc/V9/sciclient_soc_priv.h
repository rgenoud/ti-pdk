/*
 *  Copyright (C) 2023 Texas Instruments Incorporated
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
 *  \file j722s/sciclient_soc_priv.h
 *
 *  \brief Private J722S specific SOC file
 */

#ifndef SCICLIENT_SOC_PRIV_J722S_H_
#define SCICLIENT_SOC_PRIV_J722S_H_

#include <ti/drv/sciclient/soc/V9/sciclient_irq_rm.h>

#if defined (BUILD_HS)
#include <ti/drv/sciclient/soc/V9/sciclient_defaultBoardcfg_hexhs.h>
#include <ti/drv/sciclient/soc/V9/sciclient_defaultBoardcfg_rm_hexhs.h>
#include <ti/drv/sciclient/soc/V9/sciclient_defaultBoardcfg_pm_hexhs.h>
#include <ti/drv/sciclient/soc/V9/sciclient_defaultBoardcfg_security_hexhs.h>
#else
#include <ti/drv/sciclient/soc/V9/sciclient_defaultBoardcfg_hex.h>
#include <ti/drv/sciclient/soc/V9/sciclient_defaultBoardcfg_rm_hex.h>
#include <ti/drv/sciclient/soc/V9/sciclient_defaultBoardcfg_pm_hex.h>
#include <ti/drv/sciclient/soc/V9/sciclient_defaultBoardcfg_security_hex.h>
#endif

#if defined (BUILD_MCU1_0)
#define SCICLIENT_CONTEXT_NONSEC    (SCICLIENT_CONTEXT_WKUP_R5_NONSEC_0)
#define SCICLIENT_CONTEXT_SEC       (SCICLIENT_CONTEXT_WKUP_R5_SEC_0)
#endif
#if defined (BUILD_MCU2_0)
#define SCICLIENT_CONTEXT_NONSEC    (SCICLIENT_CONTEXT_MCU_R5_0_NONSEC_0)
#define SCICLIENT_CONTEXT_SEC       (SCICLIENT_CONTEXT_MCU_R5_0_NONSEC_0)
#endif
#if defined (BUILD_MCU3_0)
#define SCICLIENT_CONTEXT_NONSEC    (SCICLIENT_CONTEXT_MAIN_R5_NONSEC_0)
#define SCICLIENT_CONTEXT_SEC       (SCICLIENT_CONTEXT_MAIN_R5_SEC_0)
#endif
#if defined (BUILD_MPU1_0)
#define SCICLIENT_CONTEXT_NONSEC    (SCICLIENT_CONTEXT_A53_NONSEC_0)
#define SCICLIENT_CONTEXT_SEC       (SCICLIENT_CONTEXT_A53_SEC_0)
#endif
#if defined (BUILD_MPU1_1)
#define SCICLIENT_CONTEXT_NONSEC    (SCICLIENT_CONTEXT_A53_NONSEC_1)
#define SCICLIENT_CONTEXT_SEC       (SCICLIENT_CONTEXT_A53_SEC_1)
#endif
#if defined (BUILD_C75X_1)
#define SCICLIENT_CONTEXT_NONSEC    (SCICLIENT_CONTEXT_C7X_NONSEC_0)
#define SCICLIENT_CONTEXT_SEC       (SCICLIENT_CONTEXT_C7X_NONSEC_0)
#endif
#if defined (BUILD_C75X_2)
#define SCICLIENT_CONTEXT_NONSEC    (SCICLIENT_CONTEXT_C7X_NONSEC_1)
#define SCICLIENT_CONTEXT_SEC       (SCICLIENT_CONTEXT_C7X_NONSEC_1)
#endif

#define TISCI_HOST_ID_DEVICE_MANAGER  (TISCI_HOST_ID_WKUP_0_R5_0)

/**
 *  \anchor Sciclient_RomThreadIds
 *  \name Sciclient load firmware ROM Thread Ids.
 *  @{
 */

/** Thread ID's for each message type, R5 Out Bound Normal Priority    */
#define SCICLIENT_ROM_R5_TX_NORMAL_THREAD                           (1U)
/** Thread ID's for each message type, R5 In Bound Normal Priority    */
#define SCICLIENT_ROM_R5_RX_NORMAL_THREAD                           (0U)

#define CSL_NAVSS0_SEC_PROXY0_CFG_SCFG_BASE (CSL_DMASS0_SEC_PROXY_SCFG_BASE)
#define CSL_NAVSS0_SEC_PROXY0_CFG_SCFG_SIZE (CSL_DMASS0_SEC_PROXY_SCFG_SIZE)
#define CSL_NAVSS0_SEC_PROXY0_CFG_MMRS_BASE (CSL_DMASS0_SEC_PROXY_MMRS_BASE)
#define CSL_NAVSS0_SEC_PROXY0_CFG_MMRS_SIZE (CSL_DMASS0_SEC_PROXY_MMRS_SIZE)
#define CSL_NAVSS0_SEC_PROXY0_CFG_RT_BASE (CSL_DMASS0_SEC_PROXY_RT_BASE)
#define CSL_NAVSS0_SEC_PROXY0_CFG_RT_SIZE (CSL_DMASS0_SEC_PROXY_RT_SIZE)
#define CSL_NAVSS0_SEC_PROXY0_SRC_TARGET_DATA_BASE (CSL_DMASS0_SEC_PROXY_SRC_TARGET_DATA_BASE)
#define CSL_NAVSS0_SEC_PROXY0_SRC_TARGET_DATA_SIZE (CSL_DMASS0_SEC_PROXY_SRC_TARGET_DATA_SIZE)


/** @} */

#endif /* ifndef SCICLIENT_SOC_PRIV_J722S_H_ */
