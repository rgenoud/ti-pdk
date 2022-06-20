/*
 *  Copyright (c) Texas Instruments Incorporated 2020
 *  All rights reserved.
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
 */

/**
 *  \ingroup DRV_IPC_MODULE
 *  \defgroup DRV_IPC_SOC_MODULE IPC SoC Config
 *            This is IPC documentation specific to AM62x SoC
 *
 *  @{
 */

/**
 *  \file ipc_soc.h
 *
 *  \brief IPC Low Level Driver AM62x SOC specific file.
 */
#ifndef IPC_SOC_V4_H_
#define IPC_SOC_V4_H_

#include <ti/drv/ipc/include/ipc_config.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief VRing Buffer Size required for all core
 * combinations.
 */
#define IPC_VRING_BUFFER_SIZE   (0x200000U)

/** \brief Core definitions */
#define    IPC_MPU1_0           (0U)    /**< ARM A53 - VM0 */
#define    IPC_MCU1_0           (1U)    /**< ARM Main R5F0 - core0 */
#define    IPC_C7X_1            (2U)    /**< DSP C7x - core0 */
#define    IPC_MAX_PROCS        (3U)    /**< Maximum Processors */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */


/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/* User selected IRQ number */
#define   C7X1_MBINTR_OFFSET              (2U)
/* Base NAVSS event from group 2 */
#define   IPC_C7X_COMPUTE_CLUSTER_OFFSET  (CSLR_C7X256V0_CLEC_SOC_EVENTS_IN_MAILBOX0_MAILBOX_CLUSTER_0_MAILBOX_CLUSTER0_PEND_1)

#define   C7X_CLEC_BASE_ADDR              (CSL_C7X256V0_CLEC_BASE)

/* CLEC event corresponding to Base NAVSS event */
#define   C7X1_CLEC_BASE_GR2_NAVSS        (1664U)
/* @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

uint32_t Ipc_rprocIdToMboxId(uint32_t id);
uint32_t Ipc_mboxIdToRprocId(uint32_t id);

#if defined(BUILD_C7X_1) || defined(BUILD_C7X_2)
uint32_t Ipc_configClecRouter(uint32_t corePackEvent, uint32_t corePackEventBase);
#endif

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef IPC_SOC_V4_H_ */

/* @} */
