/*
 *  Copyright (C) 2017-2024 Texas Instruments Incorporated
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
 * \ingroup TISCI
 * \defgroup tisci_sec_proxy tisci_sec_proxy
 *
 * DMSC controls the power management, security and resource management
 * of the device.
 *
 *
 * @{
 */
/**
 *
 *  \brief  This file contains:
 *
 *          WARNING!!: Autogenerated file from SYSFW. DO NOT MODIFY!!
 * System Firmware Source File
 *
 * Secure Proxy indices for J721S2 device
 *
 * Data version: 220525_125254
 *
 */
#ifndef J721S2_TISCI_SEC_PROXY_H
#define J721S2_TISCI_SEC_PROXY_H

/*
 * Secure Proxy configurations for MCU_0_R5_0 host
 */

/** Thread ID macro for MCU_0_R5_0 notify */
#define TISCI_SEC_PROXY_MCU_0_R5_0_READ_NOTIFY_THREAD_ID (0U)
/** Num messages macro for MCU_0_R5_0 notify */
#define TISCI_SEC_PROXY_MCU_0_R5_0_READ_NOTIFY_NUM_MESSAGES (2U)

/** Thread ID macro for MCU_0_R5_0 response */
#define TISCI_SEC_PROXY_MCU_0_R5_0_READ_RESPONSE_THREAD_ID (1U)
/** Num messages macro for MCU_0_R5_0 response */
#define TISCI_SEC_PROXY_MCU_0_R5_0_READ_RESPONSE_NUM_MESSAGES (20U)

/** Thread ID macro for MCU_0_R5_0 high_priority */
#define TISCI_SEC_PROXY_MCU_0_R5_0_WRITE_HIGH_PRIORITY_THREAD_ID (2U)
/** Num messages macro for MCU_0_R5_0 high_priority */
#define TISCI_SEC_PROXY_MCU_0_R5_0_WRITE_HIGH_PRIORITY_NUM_MESSAGES (10U)

/** Thread ID macro for MCU_0_R5_0 low_priority */
#define TISCI_SEC_PROXY_MCU_0_R5_0_WRITE_LOW_PRIORITY_THREAD_ID (3U)
/** Num messages macro for MCU_0_R5_0 low_priority */
#define TISCI_SEC_PROXY_MCU_0_R5_0_WRITE_LOW_PRIORITY_NUM_MESSAGES (10U)

/** Thread ID macro for MCU_0_R5_0 notify_resp */
#define TISCI_SEC_PROXY_MCU_0_R5_0_WRITE_NOTIFY_RESP_THREAD_ID (4U)
/** Num messages macro for MCU_0_R5_0 notify_resp */
#define TISCI_SEC_PROXY_MCU_0_R5_0_WRITE_NOTIFY_RESP_NUM_MESSAGES (2U)

/*
 * Secure Proxy configurations for MCU_0_R5_1 host
 */

/** Thread ID macro for MCU_0_R5_1 notify */
#define TISCI_SEC_PROXY_MCU_0_R5_1_READ_NOTIFY_THREAD_ID (5U)
/** Num messages macro for MCU_0_R5_1 notify */
#define TISCI_SEC_PROXY_MCU_0_R5_1_READ_NOTIFY_NUM_MESSAGES (2U)

/** Thread ID macro for MCU_0_R5_1 response */
#define TISCI_SEC_PROXY_MCU_0_R5_1_READ_RESPONSE_THREAD_ID (6U)
/** Num messages macro for MCU_0_R5_1 response */
#define TISCI_SEC_PROXY_MCU_0_R5_1_READ_RESPONSE_NUM_MESSAGES (20U)

/** Thread ID macro for MCU_0_R5_1 high_priority */
#define TISCI_SEC_PROXY_MCU_0_R5_1_WRITE_HIGH_PRIORITY_THREAD_ID (7U)
/** Num messages macro for MCU_0_R5_1 high_priority */
#define TISCI_SEC_PROXY_MCU_0_R5_1_WRITE_HIGH_PRIORITY_NUM_MESSAGES (10U)

/** Thread ID macro for MCU_0_R5_1 low_priority */
#define TISCI_SEC_PROXY_MCU_0_R5_1_WRITE_LOW_PRIORITY_THREAD_ID (8U)
/** Num messages macro for MCU_0_R5_1 low_priority */
#define TISCI_SEC_PROXY_MCU_0_R5_1_WRITE_LOW_PRIORITY_NUM_MESSAGES (10U)

/** Thread ID macro for MCU_0_R5_1 notify_resp */
#define TISCI_SEC_PROXY_MCU_0_R5_1_WRITE_NOTIFY_RESP_THREAD_ID (9U)
/** Num messages macro for MCU_0_R5_1 notify_resp */
#define TISCI_SEC_PROXY_MCU_0_R5_1_WRITE_NOTIFY_RESP_NUM_MESSAGES (2U)

/*
 * Secure Proxy configurations for MCU_0_R5_2 host
 */

/** Thread ID macro for MCU_0_R5_2 notify */
#define TISCI_SEC_PROXY_MCU_0_R5_2_READ_NOTIFY_THREAD_ID (10U)
/** Num messages macro for MCU_0_R5_2 notify */
#define TISCI_SEC_PROXY_MCU_0_R5_2_READ_NOTIFY_NUM_MESSAGES (1U)

/** Thread ID macro for MCU_0_R5_2 response */
#define TISCI_SEC_PROXY_MCU_0_R5_2_READ_RESPONSE_THREAD_ID (11U)
/** Num messages macro for MCU_0_R5_2 response */
#define TISCI_SEC_PROXY_MCU_0_R5_2_READ_RESPONSE_NUM_MESSAGES (2U)

/** Thread ID macro for MCU_0_R5_2 high_priority */
#define TISCI_SEC_PROXY_MCU_0_R5_2_WRITE_HIGH_PRIORITY_THREAD_ID (12U)
/** Num messages macro for MCU_0_R5_2 high_priority */
#define TISCI_SEC_PROXY_MCU_0_R5_2_WRITE_HIGH_PRIORITY_NUM_MESSAGES (1U)

/** Thread ID macro for MCU_0_R5_2 low_priority */
#define TISCI_SEC_PROXY_MCU_0_R5_2_WRITE_LOW_PRIORITY_THREAD_ID (13U)
/** Num messages macro for MCU_0_R5_2 low_priority */
#define TISCI_SEC_PROXY_MCU_0_R5_2_WRITE_LOW_PRIORITY_NUM_MESSAGES (1U)

/** Thread ID macro for MCU_0_R5_2 notify_resp */
#define TISCI_SEC_PROXY_MCU_0_R5_2_WRITE_NOTIFY_RESP_THREAD_ID (14U)
/** Num messages macro for MCU_0_R5_2 notify_resp */
#define TISCI_SEC_PROXY_MCU_0_R5_2_WRITE_NOTIFY_RESP_NUM_MESSAGES (1U)

/*
 * Secure Proxy configurations for MCU_0_R5_3 host
 */

/** Thread ID macro for MCU_0_R5_3 notify */
#define TISCI_SEC_PROXY_MCU_0_R5_3_READ_NOTIFY_THREAD_ID (15U)
/** Num messages macro for MCU_0_R5_3 notify */
#define TISCI_SEC_PROXY_MCU_0_R5_3_READ_NOTIFY_NUM_MESSAGES (1U)

/** Thread ID macro for MCU_0_R5_3 response */
#define TISCI_SEC_PROXY_MCU_0_R5_3_READ_RESPONSE_THREAD_ID (16U)
/** Num messages macro for MCU_0_R5_3 response */
#define TISCI_SEC_PROXY_MCU_0_R5_3_READ_RESPONSE_NUM_MESSAGES (2U)

/** Thread ID macro for MCU_0_R5_3 high_priority */
#define TISCI_SEC_PROXY_MCU_0_R5_3_WRITE_HIGH_PRIORITY_THREAD_ID (17U)
/** Num messages macro for MCU_0_R5_3 high_priority */
#define TISCI_SEC_PROXY_MCU_0_R5_3_WRITE_HIGH_PRIORITY_NUM_MESSAGES (1U)

/** Thread ID macro for MCU_0_R5_3 low_priority */
#define TISCI_SEC_PROXY_MCU_0_R5_3_WRITE_LOW_PRIORITY_THREAD_ID (18U)
/** Num messages macro for MCU_0_R5_3 low_priority */
#define TISCI_SEC_PROXY_MCU_0_R5_3_WRITE_LOW_PRIORITY_NUM_MESSAGES (1U)

/** Thread ID macro for MCU_0_R5_3 notify_resp */
#define TISCI_SEC_PROXY_MCU_0_R5_3_WRITE_NOTIFY_RESP_THREAD_ID (19U)
/** Num messages macro for MCU_0_R5_3 notify_resp */
#define TISCI_SEC_PROXY_MCU_0_R5_3_WRITE_NOTIFY_RESP_NUM_MESSAGES (1U)

/*
 * Secure Proxy configurations for A72_0 host
 */

/** Thread ID macro for A72_0 notify */
#define TISCI_SEC_PROXY_A72_0_READ_NOTIFY_THREAD_ID (0U)
/** Num messages macro for A72_0 notify */
#define TISCI_SEC_PROXY_A72_0_READ_NOTIFY_NUM_MESSAGES (2U)

/** Thread ID macro for A72_0 response */
#define TISCI_SEC_PROXY_A72_0_READ_RESPONSE_THREAD_ID (1U)
/** Num messages macro for A72_0 response */
#define TISCI_SEC_PROXY_A72_0_READ_RESPONSE_NUM_MESSAGES (30U)

/** Thread ID macro for A72_0 high_priority */
#define TISCI_SEC_PROXY_A72_0_WRITE_HIGH_PRIORITY_THREAD_ID (2U)
/** Num messages macro for A72_0 high_priority */
#define TISCI_SEC_PROXY_A72_0_WRITE_HIGH_PRIORITY_NUM_MESSAGES (10U)

/** Thread ID macro for A72_0 low_priority */
#define TISCI_SEC_PROXY_A72_0_WRITE_LOW_PRIORITY_THREAD_ID (3U)
/** Num messages macro for A72_0 low_priority */
#define TISCI_SEC_PROXY_A72_0_WRITE_LOW_PRIORITY_NUM_MESSAGES (20U)

/** Thread ID macro for A72_0 notify_resp */
#define TISCI_SEC_PROXY_A72_0_WRITE_NOTIFY_RESP_THREAD_ID (4U)
/** Num messages macro for A72_0 notify_resp */
#define TISCI_SEC_PROXY_A72_0_WRITE_NOTIFY_RESP_NUM_MESSAGES (2U)

/*
 * Secure Proxy configurations for A72_1 host
 */

/** Thread ID macro for A72_1 notify */
#define TISCI_SEC_PROXY_A72_1_READ_NOTIFY_THREAD_ID (5U)
/** Num messages macro for A72_1 notify */
#define TISCI_SEC_PROXY_A72_1_READ_NOTIFY_NUM_MESSAGES (2U)

/** Thread ID macro for A72_1 response */
#define TISCI_SEC_PROXY_A72_1_READ_RESPONSE_THREAD_ID (6U)
/** Num messages macro for A72_1 response */
#define TISCI_SEC_PROXY_A72_1_READ_RESPONSE_NUM_MESSAGES (30U)

/** Thread ID macro for A72_1 high_priority */
#define TISCI_SEC_PROXY_A72_1_WRITE_HIGH_PRIORITY_THREAD_ID (7U)
/** Num messages macro for A72_1 high_priority */
#define TISCI_SEC_PROXY_A72_1_WRITE_HIGH_PRIORITY_NUM_MESSAGES (10U)

/** Thread ID macro for A72_1 low_priority */
#define TISCI_SEC_PROXY_A72_1_WRITE_LOW_PRIORITY_THREAD_ID (8U)
/** Num messages macro for A72_1 low_priority */
#define TISCI_SEC_PROXY_A72_1_WRITE_LOW_PRIORITY_NUM_MESSAGES (20U)

/** Thread ID macro for A72_1 notify_resp */
#define TISCI_SEC_PROXY_A72_1_WRITE_NOTIFY_RESP_THREAD_ID (9U)
/** Num messages macro for A72_1 notify_resp */
#define TISCI_SEC_PROXY_A72_1_WRITE_NOTIFY_RESP_NUM_MESSAGES (2U)

/*
 * Secure Proxy configurations for A72_2 host
 */

/** Thread ID macro for A72_2 notify */
#define TISCI_SEC_PROXY_A72_2_READ_NOTIFY_THREAD_ID (10U)
/** Num messages macro for A72_2 notify */
#define TISCI_SEC_PROXY_A72_2_READ_NOTIFY_NUM_MESSAGES (2U)

/** Thread ID macro for A72_2 response */
#define TISCI_SEC_PROXY_A72_2_READ_RESPONSE_THREAD_ID (11U)
/** Num messages macro for A72_2 response */
#define TISCI_SEC_PROXY_A72_2_READ_RESPONSE_NUM_MESSAGES (22U)

/** Thread ID macro for A72_2 high_priority */
#define TISCI_SEC_PROXY_A72_2_WRITE_HIGH_PRIORITY_THREAD_ID (12U)
/** Num messages macro for A72_2 high_priority */
#define TISCI_SEC_PROXY_A72_2_WRITE_HIGH_PRIORITY_NUM_MESSAGES (2U)

/** Thread ID macro for A72_2 low_priority */
#define TISCI_SEC_PROXY_A72_2_WRITE_LOW_PRIORITY_THREAD_ID (13U)
/** Num messages macro for A72_2 low_priority */
#define TISCI_SEC_PROXY_A72_2_WRITE_LOW_PRIORITY_NUM_MESSAGES (20U)

/** Thread ID macro for A72_2 notify_resp */
#define TISCI_SEC_PROXY_A72_2_WRITE_NOTIFY_RESP_THREAD_ID (14U)
/** Num messages macro for A72_2 notify_resp */
#define TISCI_SEC_PROXY_A72_2_WRITE_NOTIFY_RESP_NUM_MESSAGES (2U)

/*
 * Secure Proxy configurations for A72_3 host
 */

/** Thread ID macro for A72_3 notify */
#define TISCI_SEC_PROXY_A72_3_READ_NOTIFY_THREAD_ID (15U)
/** Num messages macro for A72_3 notify */
#define TISCI_SEC_PROXY_A72_3_READ_NOTIFY_NUM_MESSAGES (2U)

/** Thread ID macro for A72_3 response */
#define TISCI_SEC_PROXY_A72_3_READ_RESPONSE_THREAD_ID (16U)
/** Num messages macro for A72_3 response */
#define TISCI_SEC_PROXY_A72_3_READ_RESPONSE_NUM_MESSAGES (7U)

/** Thread ID macro for A72_3 high_priority */
#define TISCI_SEC_PROXY_A72_3_WRITE_HIGH_PRIORITY_THREAD_ID (17U)
/** Num messages macro for A72_3 high_priority */
#define TISCI_SEC_PROXY_A72_3_WRITE_HIGH_PRIORITY_NUM_MESSAGES (2U)

/** Thread ID macro for A72_3 low_priority */
#define TISCI_SEC_PROXY_A72_3_WRITE_LOW_PRIORITY_THREAD_ID (18U)
/** Num messages macro for A72_3 low_priority */
#define TISCI_SEC_PROXY_A72_3_WRITE_LOW_PRIORITY_NUM_MESSAGES (5U)

/** Thread ID macro for A72_3 notify_resp */
#define TISCI_SEC_PROXY_A72_3_WRITE_NOTIFY_RESP_THREAD_ID (19U)
/** Num messages macro for A72_3 notify_resp */
#define TISCI_SEC_PROXY_A72_3_WRITE_NOTIFY_RESP_NUM_MESSAGES (2U)

/*
 * Secure Proxy configurations for A72_4 host
 */

/** Thread ID macro for A72_4 notify */
#define TISCI_SEC_PROXY_A72_4_READ_NOTIFY_THREAD_ID (20U)
/** Num messages macro for A72_4 notify */
#define TISCI_SEC_PROXY_A72_4_READ_NOTIFY_NUM_MESSAGES (2U)

/** Thread ID macro for A72_4 response */
#define TISCI_SEC_PROXY_A72_4_READ_RESPONSE_THREAD_ID (21U)
/** Num messages macro for A72_4 response */
#define TISCI_SEC_PROXY_A72_4_READ_RESPONSE_NUM_MESSAGES (7U)

/** Thread ID macro for A72_4 high_priority */
#define TISCI_SEC_PROXY_A72_4_WRITE_HIGH_PRIORITY_THREAD_ID (22U)
/** Num messages macro for A72_4 high_priority */
#define TISCI_SEC_PROXY_A72_4_WRITE_HIGH_PRIORITY_NUM_MESSAGES (2U)

/** Thread ID macro for A72_4 low_priority */
#define TISCI_SEC_PROXY_A72_4_WRITE_LOW_PRIORITY_THREAD_ID (23U)
/** Num messages macro for A72_4 low_priority */
#define TISCI_SEC_PROXY_A72_4_WRITE_LOW_PRIORITY_NUM_MESSAGES (5U)

/** Thread ID macro for A72_4 notify_resp */
#define TISCI_SEC_PROXY_A72_4_WRITE_NOTIFY_RESP_THREAD_ID (24U)
/** Num messages macro for A72_4 notify_resp */
#define TISCI_SEC_PROXY_A72_4_WRITE_NOTIFY_RESP_NUM_MESSAGES (2U)

/*
 * Secure Proxy configurations for C7X_0_0 host
 */

/** Thread ID macro for C7X_0_0 notify */
#define TISCI_SEC_PROXY_C7X_0_0_READ_NOTIFY_THREAD_ID (25U)
/** Num messages macro for C7X_0_0 notify */
#define TISCI_SEC_PROXY_C7X_0_0_READ_NOTIFY_NUM_MESSAGES (2U)

/** Thread ID macro for C7X_0_0 response */
#define TISCI_SEC_PROXY_C7X_0_0_READ_RESPONSE_THREAD_ID (26U)
/** Num messages macro for C7X_0_0 response */
#define TISCI_SEC_PROXY_C7X_0_0_READ_RESPONSE_NUM_MESSAGES (7U)

/** Thread ID macro for C7X_0_0 high_priority */
#define TISCI_SEC_PROXY_C7X_0_0_WRITE_HIGH_PRIORITY_THREAD_ID (27U)
/** Num messages macro for C7X_0_0 high_priority */
#define TISCI_SEC_PROXY_C7X_0_0_WRITE_HIGH_PRIORITY_NUM_MESSAGES (2U)

/** Thread ID macro for C7X_0_0 low_priority */
#define TISCI_SEC_PROXY_C7X_0_0_WRITE_LOW_PRIORITY_THREAD_ID (28U)
/** Num messages macro for C7X_0_0 low_priority */
#define TISCI_SEC_PROXY_C7X_0_0_WRITE_LOW_PRIORITY_NUM_MESSAGES (5U)

/** Thread ID macro for C7X_0_0 notify_resp */
#define TISCI_SEC_PROXY_C7X_0_0_WRITE_NOTIFY_RESP_THREAD_ID (29U)
/** Num messages macro for C7X_0_0 notify_resp */
#define TISCI_SEC_PROXY_C7X_0_0_WRITE_NOTIFY_RESP_NUM_MESSAGES (2U)

/*
 * Secure Proxy configurations for C7X_0_1 host
 */

/** Thread ID macro for C7X_0_1 notify */
#define TISCI_SEC_PROXY_C7X_0_1_READ_NOTIFY_THREAD_ID (30U)
/** Num messages macro for C7X_0_1 notify */
#define TISCI_SEC_PROXY_C7X_0_1_READ_NOTIFY_NUM_MESSAGES (2U)

/** Thread ID macro for C7X_0_1 response */
#define TISCI_SEC_PROXY_C7X_0_1_READ_RESPONSE_THREAD_ID (31U)
/** Num messages macro for C7X_0_1 response */
#define TISCI_SEC_PROXY_C7X_0_1_READ_RESPONSE_NUM_MESSAGES (7U)

/** Thread ID macro for C7X_0_1 high_priority */
#define TISCI_SEC_PROXY_C7X_0_1_WRITE_HIGH_PRIORITY_THREAD_ID (32U)
/** Num messages macro for C7X_0_1 high_priority */
#define TISCI_SEC_PROXY_C7X_0_1_WRITE_HIGH_PRIORITY_NUM_MESSAGES (2U)

/** Thread ID macro for C7X_0_1 low_priority */
#define TISCI_SEC_PROXY_C7X_0_1_WRITE_LOW_PRIORITY_THREAD_ID (33U)
/** Num messages macro for C7X_0_1 low_priority */
#define TISCI_SEC_PROXY_C7X_0_1_WRITE_LOW_PRIORITY_NUM_MESSAGES (5U)

/** Thread ID macro for C7X_0_1 notify_resp */
#define TISCI_SEC_PROXY_C7X_0_1_WRITE_NOTIFY_RESP_THREAD_ID (34U)
/** Num messages macro for C7X_0_1 notify_resp */
#define TISCI_SEC_PROXY_C7X_0_1_WRITE_NOTIFY_RESP_NUM_MESSAGES (2U)

/*
 * Secure Proxy configurations for C7X_1_0 host
 */

/** Thread ID macro for C7X_1_0 notify */
#define TISCI_SEC_PROXY_C7X_1_0_READ_NOTIFY_THREAD_ID (35U)
/** Num messages macro for C7X_1_0 notify */
#define TISCI_SEC_PROXY_C7X_1_0_READ_NOTIFY_NUM_MESSAGES (2U)

/** Thread ID macro for C7X_1_0 response */
#define TISCI_SEC_PROXY_C7X_1_0_READ_RESPONSE_THREAD_ID (36U)
/** Num messages macro for C7X_1_0 response */
#define TISCI_SEC_PROXY_C7X_1_0_READ_RESPONSE_NUM_MESSAGES (7U)

/** Thread ID macro for C7X_1_0 high_priority */
#define TISCI_SEC_PROXY_C7X_1_0_WRITE_HIGH_PRIORITY_THREAD_ID (37U)
/** Num messages macro for C7X_1_0 high_priority */
#define TISCI_SEC_PROXY_C7X_1_0_WRITE_HIGH_PRIORITY_NUM_MESSAGES (2U)

/** Thread ID macro for C7X_1_0 low_priority */
#define TISCI_SEC_PROXY_C7X_1_0_WRITE_LOW_PRIORITY_THREAD_ID (38U)
/** Num messages macro for C7X_1_0 low_priority */
#define TISCI_SEC_PROXY_C7X_1_0_WRITE_LOW_PRIORITY_NUM_MESSAGES (5U)

/** Thread ID macro for C7X_1_0 notify_resp */
#define TISCI_SEC_PROXY_C7X_1_0_WRITE_NOTIFY_RESP_THREAD_ID (39U)
/** Num messages macro for C7X_1_0 notify_resp */
#define TISCI_SEC_PROXY_C7X_1_0_WRITE_NOTIFY_RESP_NUM_MESSAGES (2U)

/*
 * Secure Proxy configurations for C7X_1_1 host
 */

/** Thread ID macro for C7X_1_1 notify */
#define TISCI_SEC_PROXY_C7X_1_1_READ_NOTIFY_THREAD_ID (40U)
/** Num messages macro for C7X_1_1 notify */
#define TISCI_SEC_PROXY_C7X_1_1_READ_NOTIFY_NUM_MESSAGES (2U)

/** Thread ID macro for C7X_1_1 response */
#define TISCI_SEC_PROXY_C7X_1_1_READ_RESPONSE_THREAD_ID (41U)
/** Num messages macro for C7X_1_1 response */
#define TISCI_SEC_PROXY_C7X_1_1_READ_RESPONSE_NUM_MESSAGES (7U)

/** Thread ID macro for C7X_1_1 high_priority */
#define TISCI_SEC_PROXY_C7X_1_1_WRITE_HIGH_PRIORITY_THREAD_ID (42U)
/** Num messages macro for C7X_1_1 high_priority */
#define TISCI_SEC_PROXY_C7X_1_1_WRITE_HIGH_PRIORITY_NUM_MESSAGES (2U)

/** Thread ID macro for C7X_1_1 low_priority */
#define TISCI_SEC_PROXY_C7X_1_1_WRITE_LOW_PRIORITY_THREAD_ID (43U)
/** Num messages macro for C7X_1_1 low_priority */
#define TISCI_SEC_PROXY_C7X_1_1_WRITE_LOW_PRIORITY_NUM_MESSAGES (5U)

/** Thread ID macro for C7X_1_1 notify_resp */
#define TISCI_SEC_PROXY_C7X_1_1_WRITE_NOTIFY_RESP_THREAD_ID (44U)
/** Num messages macro for C7X_1_1 notify_resp */
#define TISCI_SEC_PROXY_C7X_1_1_WRITE_NOTIFY_RESP_NUM_MESSAGES (2U)

/*
 * Secure Proxy configurations for GPU_0 host
 */

/** Thread ID macro for GPU_0 notify */
#define TISCI_SEC_PROXY_GPU_0_READ_NOTIFY_THREAD_ID (45U)
/** Num messages macro for GPU_0 notify */
#define TISCI_SEC_PROXY_GPU_0_READ_NOTIFY_NUM_MESSAGES (2U)

/** Thread ID macro for GPU_0 response */
#define TISCI_SEC_PROXY_GPU_0_READ_RESPONSE_THREAD_ID (46U)
/** Num messages macro for GPU_0 response */
#define TISCI_SEC_PROXY_GPU_0_READ_RESPONSE_NUM_MESSAGES (7U)

/** Thread ID macro for GPU_0 high_priority */
#define TISCI_SEC_PROXY_GPU_0_WRITE_HIGH_PRIORITY_THREAD_ID (47U)
/** Num messages macro for GPU_0 high_priority */
#define TISCI_SEC_PROXY_GPU_0_WRITE_HIGH_PRIORITY_NUM_MESSAGES (2U)

/** Thread ID macro for GPU_0 low_priority */
#define TISCI_SEC_PROXY_GPU_0_WRITE_LOW_PRIORITY_THREAD_ID (48U)
/** Num messages macro for GPU_0 low_priority */
#define TISCI_SEC_PROXY_GPU_0_WRITE_LOW_PRIORITY_NUM_MESSAGES (5U)

/** Thread ID macro for GPU_0 notify_resp */
#define TISCI_SEC_PROXY_GPU_0_WRITE_NOTIFY_RESP_THREAD_ID (49U)
/** Num messages macro for GPU_0 notify_resp */
#define TISCI_SEC_PROXY_GPU_0_WRITE_NOTIFY_RESP_NUM_MESSAGES (2U)

/*
 * Secure Proxy configurations for MAIN_0_R5_0 host
 */

/** Thread ID macro for MAIN_0_R5_0 notify */
#define TISCI_SEC_PROXY_MAIN_0_R5_0_READ_NOTIFY_THREAD_ID (50U)
/** Num messages macro for MAIN_0_R5_0 notify */
#define TISCI_SEC_PROXY_MAIN_0_R5_0_READ_NOTIFY_NUM_MESSAGES (2U)

/** Thread ID macro for MAIN_0_R5_0 response */
#define TISCI_SEC_PROXY_MAIN_0_R5_0_READ_RESPONSE_THREAD_ID (51U)
/** Num messages macro for MAIN_0_R5_0 response */
#define TISCI_SEC_PROXY_MAIN_0_R5_0_READ_RESPONSE_NUM_MESSAGES (7U)

/** Thread ID macro for MAIN_0_R5_0 high_priority */
#define TISCI_SEC_PROXY_MAIN_0_R5_0_WRITE_HIGH_PRIORITY_THREAD_ID (52U)
/** Num messages macro for MAIN_0_R5_0 high_priority */
#define TISCI_SEC_PROXY_MAIN_0_R5_0_WRITE_HIGH_PRIORITY_NUM_MESSAGES (2U)

/** Thread ID macro for MAIN_0_R5_0 low_priority */
#define TISCI_SEC_PROXY_MAIN_0_R5_0_WRITE_LOW_PRIORITY_THREAD_ID (53U)
/** Num messages macro for MAIN_0_R5_0 low_priority */
#define TISCI_SEC_PROXY_MAIN_0_R5_0_WRITE_LOW_PRIORITY_NUM_MESSAGES (5U)

/** Thread ID macro for MAIN_0_R5_0 notify_resp */
#define TISCI_SEC_PROXY_MAIN_0_R5_0_WRITE_NOTIFY_RESP_THREAD_ID (54U)
/** Num messages macro for MAIN_0_R5_0 notify_resp */
#define TISCI_SEC_PROXY_MAIN_0_R5_0_WRITE_NOTIFY_RESP_NUM_MESSAGES (2U)

/*
 * Secure Proxy configurations for MAIN_0_R5_1 host
 */

/** Thread ID macro for MAIN_0_R5_1 notify */
#define TISCI_SEC_PROXY_MAIN_0_R5_1_READ_NOTIFY_THREAD_ID (55U)
/** Num messages macro for MAIN_0_R5_1 notify */
#define TISCI_SEC_PROXY_MAIN_0_R5_1_READ_NOTIFY_NUM_MESSAGES (2U)

/** Thread ID macro for MAIN_0_R5_1 response */
#define TISCI_SEC_PROXY_MAIN_0_R5_1_READ_RESPONSE_THREAD_ID (56U)
/** Num messages macro for MAIN_0_R5_1 response */
#define TISCI_SEC_PROXY_MAIN_0_R5_1_READ_RESPONSE_NUM_MESSAGES (7U)

/** Thread ID macro for MAIN_0_R5_1 high_priority */
#define TISCI_SEC_PROXY_MAIN_0_R5_1_WRITE_HIGH_PRIORITY_THREAD_ID (57U)
/** Num messages macro for MAIN_0_R5_1 high_priority */
#define TISCI_SEC_PROXY_MAIN_0_R5_1_WRITE_HIGH_PRIORITY_NUM_MESSAGES (2U)

/** Thread ID macro for MAIN_0_R5_1 low_priority */
#define TISCI_SEC_PROXY_MAIN_0_R5_1_WRITE_LOW_PRIORITY_THREAD_ID (58U)
/** Num messages macro for MAIN_0_R5_1 low_priority */
#define TISCI_SEC_PROXY_MAIN_0_R5_1_WRITE_LOW_PRIORITY_NUM_MESSAGES (5U)

/** Thread ID macro for MAIN_0_R5_1 notify_resp */
#define TISCI_SEC_PROXY_MAIN_0_R5_1_WRITE_NOTIFY_RESP_THREAD_ID (59U)
/** Num messages macro for MAIN_0_R5_1 notify_resp */
#define TISCI_SEC_PROXY_MAIN_0_R5_1_WRITE_NOTIFY_RESP_NUM_MESSAGES (2U)

/*
 * Secure Proxy configurations for MAIN_0_R5_2 host
 */

/** Thread ID macro for MAIN_0_R5_2 notify */
#define TISCI_SEC_PROXY_MAIN_0_R5_2_READ_NOTIFY_THREAD_ID (60U)
/** Num messages macro for MAIN_0_R5_2 notify */
#define TISCI_SEC_PROXY_MAIN_0_R5_2_READ_NOTIFY_NUM_MESSAGES (1U)

/** Thread ID macro for MAIN_0_R5_2 response */
#define TISCI_SEC_PROXY_MAIN_0_R5_2_READ_RESPONSE_THREAD_ID (61U)
/** Num messages macro for MAIN_0_R5_2 response */
#define TISCI_SEC_PROXY_MAIN_0_R5_2_READ_RESPONSE_NUM_MESSAGES (2U)

/** Thread ID macro for MAIN_0_R5_2 high_priority */
#define TISCI_SEC_PROXY_MAIN_0_R5_2_WRITE_HIGH_PRIORITY_THREAD_ID (62U)
/** Num messages macro for MAIN_0_R5_2 high_priority */
#define TISCI_SEC_PROXY_MAIN_0_R5_2_WRITE_HIGH_PRIORITY_NUM_MESSAGES (1U)

/** Thread ID macro for MAIN_0_R5_2 low_priority */
#define TISCI_SEC_PROXY_MAIN_0_R5_2_WRITE_LOW_PRIORITY_THREAD_ID (63U)
/** Num messages macro for MAIN_0_R5_2 low_priority */
#define TISCI_SEC_PROXY_MAIN_0_R5_2_WRITE_LOW_PRIORITY_NUM_MESSAGES (1U)

/** Thread ID macro for MAIN_0_R5_2 notify_resp */
#define TISCI_SEC_PROXY_MAIN_0_R5_2_WRITE_NOTIFY_RESP_THREAD_ID (64U)
/** Num messages macro for MAIN_0_R5_2 notify_resp */
#define TISCI_SEC_PROXY_MAIN_0_R5_2_WRITE_NOTIFY_RESP_NUM_MESSAGES (1U)

/*
 * Secure Proxy configurations for MAIN_0_R5_3 host
 */

/** Thread ID macro for MAIN_0_R5_3 notify */
#define TISCI_SEC_PROXY_MAIN_0_R5_3_READ_NOTIFY_THREAD_ID (65U)
/** Num messages macro for MAIN_0_R5_3 notify */
#define TISCI_SEC_PROXY_MAIN_0_R5_3_READ_NOTIFY_NUM_MESSAGES (1U)

/** Thread ID macro for MAIN_0_R5_3 response */
#define TISCI_SEC_PROXY_MAIN_0_R5_3_READ_RESPONSE_THREAD_ID (66U)
/** Num messages macro for MAIN_0_R5_3 response */
#define TISCI_SEC_PROXY_MAIN_0_R5_3_READ_RESPONSE_NUM_MESSAGES (2U)

/** Thread ID macro for MAIN_0_R5_3 high_priority */
#define TISCI_SEC_PROXY_MAIN_0_R5_3_WRITE_HIGH_PRIORITY_THREAD_ID (67U)
/** Num messages macro for MAIN_0_R5_3 high_priority */
#define TISCI_SEC_PROXY_MAIN_0_R5_3_WRITE_HIGH_PRIORITY_NUM_MESSAGES (1U)

/** Thread ID macro for MAIN_0_R5_3 low_priority */
#define TISCI_SEC_PROXY_MAIN_0_R5_3_WRITE_LOW_PRIORITY_THREAD_ID (68U)
/** Num messages macro for MAIN_0_R5_3 low_priority */
#define TISCI_SEC_PROXY_MAIN_0_R5_3_WRITE_LOW_PRIORITY_NUM_MESSAGES (1U)

/** Thread ID macro for MAIN_0_R5_3 notify_resp */
#define TISCI_SEC_PROXY_MAIN_0_R5_3_WRITE_NOTIFY_RESP_THREAD_ID (69U)
/** Num messages macro for MAIN_0_R5_3 notify_resp */
#define TISCI_SEC_PROXY_MAIN_0_R5_3_WRITE_NOTIFY_RESP_NUM_MESSAGES (1U)

/*
 * Secure Proxy configurations for MAIN_1_R5_0 host
 */

/** Thread ID macro for MAIN_1_R5_0 notify */
#define TISCI_SEC_PROXY_MAIN_1_R5_0_READ_NOTIFY_THREAD_ID (70U)
/** Num messages macro for MAIN_1_R5_0 notify */
#define TISCI_SEC_PROXY_MAIN_1_R5_0_READ_NOTIFY_NUM_MESSAGES (2U)

/** Thread ID macro for MAIN_1_R5_0 response */
#define TISCI_SEC_PROXY_MAIN_1_R5_0_READ_RESPONSE_THREAD_ID (71U)
/** Num messages macro for MAIN_1_R5_0 response */
#define TISCI_SEC_PROXY_MAIN_1_R5_0_READ_RESPONSE_NUM_MESSAGES (7U)

/** Thread ID macro for MAIN_1_R5_0 high_priority */
#define TISCI_SEC_PROXY_MAIN_1_R5_0_WRITE_HIGH_PRIORITY_THREAD_ID (72U)
/** Num messages macro for MAIN_1_R5_0 high_priority */
#define TISCI_SEC_PROXY_MAIN_1_R5_0_WRITE_HIGH_PRIORITY_NUM_MESSAGES (2U)

/** Thread ID macro for MAIN_1_R5_0 low_priority */
#define TISCI_SEC_PROXY_MAIN_1_R5_0_WRITE_LOW_PRIORITY_THREAD_ID (73U)
/** Num messages macro for MAIN_1_R5_0 low_priority */
#define TISCI_SEC_PROXY_MAIN_1_R5_0_WRITE_LOW_PRIORITY_NUM_MESSAGES (5U)

/** Thread ID macro for MAIN_1_R5_0 notify_resp */
#define TISCI_SEC_PROXY_MAIN_1_R5_0_WRITE_NOTIFY_RESP_THREAD_ID (74U)
/** Num messages macro for MAIN_1_R5_0 notify_resp */
#define TISCI_SEC_PROXY_MAIN_1_R5_0_WRITE_NOTIFY_RESP_NUM_MESSAGES (2U)

/*
 * Secure Proxy configurations for MAIN_1_R5_1 host
 */

/** Thread ID macro for MAIN_1_R5_1 notify */
#define TISCI_SEC_PROXY_MAIN_1_R5_1_READ_NOTIFY_THREAD_ID (75U)
/** Num messages macro for MAIN_1_R5_1 notify */
#define TISCI_SEC_PROXY_MAIN_1_R5_1_READ_NOTIFY_NUM_MESSAGES (2U)

/** Thread ID macro for MAIN_1_R5_1 response */
#define TISCI_SEC_PROXY_MAIN_1_R5_1_READ_RESPONSE_THREAD_ID (76U)
/** Num messages macro for MAIN_1_R5_1 response */
#define TISCI_SEC_PROXY_MAIN_1_R5_1_READ_RESPONSE_NUM_MESSAGES (7U)

/** Thread ID macro for MAIN_1_R5_1 high_priority */
#define TISCI_SEC_PROXY_MAIN_1_R5_1_WRITE_HIGH_PRIORITY_THREAD_ID (77U)
/** Num messages macro for MAIN_1_R5_1 high_priority */
#define TISCI_SEC_PROXY_MAIN_1_R5_1_WRITE_HIGH_PRIORITY_NUM_MESSAGES (2U)

/** Thread ID macro for MAIN_1_R5_1 low_priority */
#define TISCI_SEC_PROXY_MAIN_1_R5_1_WRITE_LOW_PRIORITY_THREAD_ID (78U)
/** Num messages macro for MAIN_1_R5_1 low_priority */
#define TISCI_SEC_PROXY_MAIN_1_R5_1_WRITE_LOW_PRIORITY_NUM_MESSAGES (5U)

/** Thread ID macro for MAIN_1_R5_1 notify_resp */
#define TISCI_SEC_PROXY_MAIN_1_R5_1_WRITE_NOTIFY_RESP_THREAD_ID (79U)
/** Num messages macro for MAIN_1_R5_1 notify_resp */
#define TISCI_SEC_PROXY_MAIN_1_R5_1_WRITE_NOTIFY_RESP_NUM_MESSAGES (2U)

/*
 * Secure Proxy configurations for MAIN_1_R5_2 host
 */

/** Thread ID macro for MAIN_1_R5_2 notify */
#define TISCI_SEC_PROXY_MAIN_1_R5_2_READ_NOTIFY_THREAD_ID (80U)
/** Num messages macro for MAIN_1_R5_2 notify */
#define TISCI_SEC_PROXY_MAIN_1_R5_2_READ_NOTIFY_NUM_MESSAGES (1U)

/** Thread ID macro for MAIN_1_R5_2 response */
#define TISCI_SEC_PROXY_MAIN_1_R5_2_READ_RESPONSE_THREAD_ID (81U)
/** Num messages macro for MAIN_1_R5_2 response */
#define TISCI_SEC_PROXY_MAIN_1_R5_2_READ_RESPONSE_NUM_MESSAGES (2U)

/** Thread ID macro for MAIN_1_R5_2 high_priority */
#define TISCI_SEC_PROXY_MAIN_1_R5_2_WRITE_HIGH_PRIORITY_THREAD_ID (82U)
/** Num messages macro for MAIN_1_R5_2 high_priority */
#define TISCI_SEC_PROXY_MAIN_1_R5_2_WRITE_HIGH_PRIORITY_NUM_MESSAGES (1U)

/** Thread ID macro for MAIN_1_R5_2 low_priority */
#define TISCI_SEC_PROXY_MAIN_1_R5_2_WRITE_LOW_PRIORITY_THREAD_ID (83U)
/** Num messages macro for MAIN_1_R5_2 low_priority */
#define TISCI_SEC_PROXY_MAIN_1_R5_2_WRITE_LOW_PRIORITY_NUM_MESSAGES (1U)

/** Thread ID macro for MAIN_1_R5_2 notify_resp */
#define TISCI_SEC_PROXY_MAIN_1_R5_2_WRITE_NOTIFY_RESP_THREAD_ID (84U)
/** Num messages macro for MAIN_1_R5_2 notify_resp */
#define TISCI_SEC_PROXY_MAIN_1_R5_2_WRITE_NOTIFY_RESP_NUM_MESSAGES (1U)

/*
 * Secure Proxy configurations for MAIN_1_R5_3 host
 */

/** Thread ID macro for MAIN_1_R5_3 notify */
#define TISCI_SEC_PROXY_MAIN_1_R5_3_READ_NOTIFY_THREAD_ID (85U)
/** Num messages macro for MAIN_1_R5_3 notify */
#define TISCI_SEC_PROXY_MAIN_1_R5_3_READ_NOTIFY_NUM_MESSAGES (1U)

/** Thread ID macro for MAIN_1_R5_3 response */
#define TISCI_SEC_PROXY_MAIN_1_R5_3_READ_RESPONSE_THREAD_ID (86U)
/** Num messages macro for MAIN_1_R5_3 response */
#define TISCI_SEC_PROXY_MAIN_1_R5_3_READ_RESPONSE_NUM_MESSAGES (2U)

/** Thread ID macro for MAIN_1_R5_3 high_priority */
#define TISCI_SEC_PROXY_MAIN_1_R5_3_WRITE_HIGH_PRIORITY_THREAD_ID (87U)
/** Num messages macro for MAIN_1_R5_3 high_priority */
#define TISCI_SEC_PROXY_MAIN_1_R5_3_WRITE_HIGH_PRIORITY_NUM_MESSAGES (1U)

/** Thread ID macro for MAIN_1_R5_3 low_priority */
#define TISCI_SEC_PROXY_MAIN_1_R5_3_WRITE_LOW_PRIORITY_THREAD_ID (88U)
/** Num messages macro for MAIN_1_R5_3 low_priority */
#define TISCI_SEC_PROXY_MAIN_1_R5_3_WRITE_LOW_PRIORITY_NUM_MESSAGES (1U)

/** Thread ID macro for MAIN_1_R5_3 notify_resp */
#define TISCI_SEC_PROXY_MAIN_1_R5_3_WRITE_NOTIFY_RESP_THREAD_ID (89U)
/** Num messages macro for MAIN_1_R5_3 notify_resp */
#define TISCI_SEC_PROXY_MAIN_1_R5_3_WRITE_NOTIFY_RESP_NUM_MESSAGES (1U)

/*
 * Secure Proxy configurations for DM2TIFS host
 */

/** Thread ID macro for DM2TIFS notify */
#define TISCI_SEC_PROXY_DM2TIFS_READ_NOTIFY_THREAD_ID (20U)
/** Num messages macro for DM2TIFS notify */
#define TISCI_SEC_PROXY_DM2TIFS_READ_NOTIFY_NUM_MESSAGES (2U)

/** Thread ID macro for DM2TIFS response */
#define TISCI_SEC_PROXY_DM2TIFS_READ_RESPONSE_THREAD_ID (21U)
/** Num messages macro for DM2TIFS response */
#define TISCI_SEC_PROXY_DM2TIFS_READ_RESPONSE_NUM_MESSAGES (4U)

/** Thread ID macro for DM2TIFS high_priority */
#define TISCI_SEC_PROXY_DM2TIFS_WRITE_HIGH_PRIORITY_THREAD_ID (22U)
/** Num messages macro for DM2TIFS high_priority */
#define TISCI_SEC_PROXY_DM2TIFS_WRITE_HIGH_PRIORITY_NUM_MESSAGES (2U)

/** Thread ID macro for DM2TIFS low_priority */
#define TISCI_SEC_PROXY_DM2TIFS_WRITE_LOW_PRIORITY_THREAD_ID (23U)
/** Num messages macro for DM2TIFS low_priority */
#define TISCI_SEC_PROXY_DM2TIFS_WRITE_LOW_PRIORITY_NUM_MESSAGES (2U)

/** Thread ID macro for DM2TIFS notify_resp */
#define TISCI_SEC_PROXY_DM2TIFS_WRITE_NOTIFY_RESP_THREAD_ID (24U)
/** Num messages macro for DM2TIFS notify_resp */
#define TISCI_SEC_PROXY_DM2TIFS_WRITE_NOTIFY_RESP_NUM_MESSAGES (2U)

/*
 * Secure Proxy configurations for TIFS2DM host
 */

/** Thread ID macro for TIFS2DM notify */
#define TISCI_SEC_PROXY_TIFS2DM_READ_NOTIFY_THREAD_ID (25U)
/** Num messages macro for TIFS2DM notify */
#define TISCI_SEC_PROXY_TIFS2DM_READ_NOTIFY_NUM_MESSAGES (2U)

/** Thread ID macro for TIFS2DM response */
#define TISCI_SEC_PROXY_TIFS2DM_READ_RESPONSE_THREAD_ID (26U)
/** Num messages macro for TIFS2DM response */
#define TISCI_SEC_PROXY_TIFS2DM_READ_RESPONSE_NUM_MESSAGES (4U)

/** Thread ID macro for TIFS2DM high_priority */
#define TISCI_SEC_PROXY_TIFS2DM_WRITE_HIGH_PRIORITY_THREAD_ID (27U)
/** Num messages macro for TIFS2DM high_priority */
#define TISCI_SEC_PROXY_TIFS2DM_WRITE_HIGH_PRIORITY_NUM_MESSAGES (2U)

/** Thread ID macro for TIFS2DM low_priority */
#define TISCI_SEC_PROXY_TIFS2DM_WRITE_LOW_PRIORITY_THREAD_ID (28U)
/** Num messages macro for TIFS2DM low_priority */
#define TISCI_SEC_PROXY_TIFS2DM_WRITE_LOW_PRIORITY_NUM_MESSAGES (2U)

/** Thread ID macro for TIFS2DM notify_resp */
#define TISCI_SEC_PROXY_TIFS2DM_WRITE_NOTIFY_RESP_THREAD_ID (29U)
/** Num messages macro for TIFS2DM notify_resp */
#define TISCI_SEC_PROXY_TIFS2DM_WRITE_NOTIFY_RESP_NUM_MESSAGES (2U)

/*
 * Secure Proxy configurations for HSM host
 */

/** Thread ID macro for HSM response */
#define TISCI_SEC_PROXY_HSM_READ_RESPONSE_THREAD_ID (0U)
/** Num messages macro for HSM response */
#define TISCI_SEC_PROXY_HSM_READ_RESPONSE_NUM_MESSAGES (8U)

/** Thread ID macro for HSM low_priority */
#define TISCI_SEC_PROXY_HSM_WRITE_LOW_PRIORITY_THREAD_ID (1U)
/** Num messages macro for HSM low_priority */
#define TISCI_SEC_PROXY_HSM_WRITE_LOW_PRIORITY_NUM_MESSAGES (8U)


#endif /* J721S2_TISCI_SEC_PROXY_H */

/* @} */
