/*
 *  Copyright (C) 2018 Texas Instruments Incorporated
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
 *  \file   V0/sciclient_fmwMsgParams.h
 *
 *  \brief  This file contains the definition of all the parameter IDs for
 *          PM, RM, Security.
 */

#ifndef SCICLIENT_FMWMSGPARAMS_H_
#define SCICLIENT_FMWMSGPARAMS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** Undefined Param Undefined */
#define TISCI_PARAM_UNDEF                                        (0xFFFFFFFFU)

/**
 *  \anchor Sciclient_FirmwareABI_V0
 *  \name Sciclient Firmware ABI revisions
 *  @{
 *  ABI revisions for compatibility check.
 */
/* ABI Major revision - Major revision changes
*       indicate backward compatibility breakage */
#define SCICLIENT_FIRMWARE_ABI_MAJOR                     (2U)
/* ABI Minor revision - Minor revision changes
*       indicate backward compatibility is maintained,
*       however, new messages OR extensions to existing
*       messages might have been adde */
#define SCICLIENT_FIRMWARE_ABI_MINOR                     (9U)
/* @} */

/**
 *  \anchor Sciclient_ContextIds_V0
 *  \name Sciclient Context Ids
 *  @{
 *  Context IDs for Sciclient_ConfigPrms_t .
 */
/** r5(Secure): Cortex R5 Context 0 */
#define SCICLIENT_CONTEXT_R5_0_SEC_0                   (0U)
/** r5(Non Secure): Cortex R5 Context 1 */
#define SCICLIENT_CONTEXT_R5_0_NONSEC_0                (1U)
/** r5(Secure): Cortex R5 Context 2 */
#define SCICLIENT_CONTEXT_R5_0_SEC_1                   (2U)
/** r5(Non Secure): Cortex R5 Context 3 */
#define SCICLIENT_CONTEXT_R5_0_NONSEC_1                (3U)
/** a53(Secure): Cortex A53 context 0 */
#define SCICLIENT_CONTEXT_A53_SEC_0                    (4U)
/** a53(Non Secure): Cortex A53 context 1 */
#define SCICLIENT_CONTEXT_A53_NONSEC_0                 (5U)
/** a53(Non Secure): Cortex A53 context 2 */
#define SCICLIENT_CONTEXT_A53_NONSEC_1                 (6U)
/** a53(Non Secure): Cortex A53 context 3 */
#define SCICLIENT_CONTEXT_A53_NONSEC_2                 (7U)
/** a53(Non Secure): Cortex A53 context 4 */
#define SCICLIENT_CONTEXT_A53_NONSEC_3                 (8U)
/** M4 (Non Secure): Cortex M4 context 1 */
#define SCICLIENT_CONTEXT_M4_NONSEC_0                  (9U)
/** r5(Secure): Cortex R5 Context 0 */
#define SCICLIENT_CONTEXT_R5_1_SEC_0                   (10U)
/** r5(Non Secure): Cortex R5 Context 1 */
#define SCICLIENT_CONTEXT_R5_1_NONSEC_0                (11U)
/** r5(Secure): Cortex R5 Context 2 */
#define SCICLIENT_CONTEXT_R5_1_SEC_1                   (12U)
/** r5(Non Secure): Cortex R5 Context 3 */
#define SCICLIENT_CONTEXT_R5_1_NONSEC_1                (13U)
/** ICSSG (Non Secure) : ICSSG Non Secure Context */
#define SCICLIENT_CONTEXT_ICSSG_NONSEC_0               (14U)
/** M4 (Secure): Cortex M4 context 1 */
#define SCICLIENT_CONTEXT_M4_SEC_0                     (15U) /* TBD */

/** Total number of possible contexts for application. */
#define SCICLIENT_CONTEXT_MAX_NUM                      (16U)
/* @} */

/** -------------------- Resource Management Parameters ---------------------*/
#define TISCI_MSG_VALUE_RM_NULL_RING_TYPE     (0xFFFFu)
#define TISCI_MSG_VALUE_RM_NULL_RING_INDEX    (0xFFFFFFFFu)
#define TISCI_MSG_VALUE_RM_NULL_RING_ADDR     (0xFFFFFFFFu)
#define TISCI_MSG_VALUE_RM_NULL_RING_COUNT    (0xFFFFFFFFu)
/**
 * The ring mode field of the RING_SIZE register is not modified if this value
 * is used for:
 * @ref tisci_msg_rm_ring_cfg_req::mode
 */
#define TISCI_MSG_VALUE_RM_NULL_RING_MODE      (0xFFu)
#define TISCI_MSG_VALUE_RM_NULL_RING_SIZE      (0xFFu)
#define TISCI_MSG_VALUE_RM_NULL_ORDER_ID       (0xFFu)
#define TISCI_MSG_VALUE_RM_UDMAP_NULL_CH_TYPE  (0xFFu)
#define TISCI_MSG_VALUE_RM_UDMAP_NULL_CH_INDEX (0xFFFFFFFFu)

/** ------------ Power Management Messages Parameters -----------------------*/
/**
 *  \anchor Sciclient_PmDeviceIds_V0
 *  \name Power Management Device IDs
 *  @{
 *  Power Management Module Device IDs
 */
#include <ti/drv/sciclient/soc/sysfw/include/am64x/tisci_devices.h>
/* @} */

/**
 *  \anchor Sciclient_PmModuleClockIds_V0
 *  \name Power Management Clock IDs Module Wise
 *  @{
 *  Power Management Module Clock IDs for individual modules.
 */
#include <ti/drv/sciclient/soc/sysfw/include/am64x/tisci_clocks.h>
/* @} */

/**
 *  \anchor Sciclient_IrqSrcIdxStart_V0
 *  \name IRQ source index start
 *  @{
 *  Start offset of IRQ source index.
 */
#define TISCI_RINGACC0_OES_IRQ_SRC_IDX_START        (0U)
#define TISCI_RINGACC0_MON_IRQ_SRC_IDX_START        (1024U)
#define TISCI_RINGACC0_EOES_IRQ_SRC_IDX_START       (4096U)
#define TISCI_UDMAP0_TX_OES_IRQ_SRC_IDX_START       (0U)
#define TISCI_UDMAP0_TX_EOES_IRQ_SRC_IDX_START      (4096U)
#define TISCI_UDMAP0_RX_OES_IRQ_SRC_IDX_START       (8192U)
#define TISCI_UDMAP0_RX_EOES_IRQ_SRC_IDX_START      (12288U)
#define TISCI_UDMAP0_RX_FLOW_EOES_IRQ_SRC_IDX_START (16384U)
/* @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef SCICLIENT_FMWMSGPARAMS_H_ */
