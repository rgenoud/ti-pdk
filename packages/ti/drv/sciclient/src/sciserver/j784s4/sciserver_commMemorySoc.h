/*
 * Copyright (c) 2022 Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
 *  \file sciserver_commMemorySoc.h
 *
 *  \brief Memory instances for communication paths in J784S4 device.
 *
 */
#ifndef SOC_J784S4_COMM_MEMORY_H
#define SOC_J784S4_COMM_MEMORY_H

/** Number of unique memories on the SoC */
#define COMM_MEMORY_INSTANCE_COUNT (3U)

/**
 * msmc_sram: MSMC SRAM of 4MB
 */
#define J784S4_SPROXY_MEM_IDX_MSMC_SRAM (0U)
/**
 * mcu_sproxy_sram: Local MCU NAVSS SRAM memory dedicated for SPROXY/RA
 * communication usage
 */
#define J784S4_SPROXY_MEM_IDX_MCU_SPROXY_SRAM (1U)
/**
 * dmss_hsm_ipc_sram: dmss_hsm_ipc_sram
 */
#define J784S4_SPROXY_MEM_IDX_DMSS_HSM_IPC_SRAM (2U)

#endif /* SOC_J784S4_COMM_MEMORY_H */
