/*
 * Copyright (c) 2018, Texas Instruments Incorporated
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
 *  \file V3/sciclient_defaultBoardcfg.c
 *
 *  \brief File containing the boardcfg default data structure to
 *      send TISCI_MSG_BOARD_CONFIG message.
 *
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/drv/sciclient/soc/V3/sciclient_defaultBoardcfg.h>

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#if defined (BUILD_MCU1_0)
const struct tisci_boardcfg gBoardConfigLow
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
        .main_isolation_hostid = TISCI_HOST_ID_MAIN_0_R5_0,
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
         * debug.
         */
        /* Uncomment for Debug */
        /*
        .trace_dst_enables = (TISCI_BOARDCFG_TRACE_DST_UART0 |
                              TISCI_BOARDCFG_TRACE_DST_ITM |
                              TISCI_BOARDCFG_TRACE_DST_MEM),
        .trace_src_enables = (TISCI_BOARDCFG_TRACE_SRC_PM |
                              TISCI_BOARDCFG_TRACE_SRC_RM |
                              TISCI_BOARDCFG_TRACE_SRC_SEC |
                              TISCI_BOARDCFG_TRACE_SRC_BASE |
                              TISCI_BOARDCFG_TRACE_SRC_USER |
                              TISCI_BOARDCFG_TRACE_SRC_SUPR)
        */
        .trace_dst_enables = 0,
        .trace_src_enables = 0
    },
};
#endif

#if defined (BUILD_MCU1_0)
const struct tisci_local_rm_boardcfg gBoardConfigLow_rm
__attribute__(( aligned(128), section(".boardcfg_data") )) =

{
    .rm_boardcfg = {
        .rev = {
            .tisci_boardcfg_abi_maj = 0x0,
            .tisci_boardcfg_abi_min = 0x1,
        },
        .host_cfg = {
            .subhdr = {
                .magic = TISCI_BOARDCFG_RM_HOST_CFG_MAGIC_NUM,
                .size = sizeof(struct tisci_boardcfg_rm_host_cfg),
            },
            .host_cfg_entries = {0},
        },
        .resasg = {
            .subhdr = {
                .magic = TISCI_BOARDCFG_RM_RESASG_MAGIC_NUM,
                .size = sizeof(struct tisci_boardcfg_rm_resasg),
            },
            .resasg_entries_size = TISCI_RESASG_UTYPE_CNT * sizeof(struct tisci_boardcfg_rm_resasg_entry),
        },
    },
    .resasg_entries = {
        {
            .num_resource = 36U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_VINT_TO_GICSS0),
            .start_resource = 4U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 28U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_VINT_TO_R5FSS0_CORE0_AND_R5FSS0_CORE1),
            .start_resource = 44U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_VINT_TO_R5FSS0_CORE0),
            .start_resource = 72U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_VINT_TO_R5FSS0_CORE1),
            .start_resource = 80U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 28U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_VINT_TO_R5FSS1_CORE1_AND_R5FSS1_CORE0),
            .start_resource = 92U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_VINT_TO_R5FSS1_CORE0),
            .start_resource = 120U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_VINT_TO_R5FSS1_CORE1),
            .start_resource = 128U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_VINT_TO_PRU_ICSSG0),
            .start_resource = 152U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_VINT_TO_PRU_ICSSG1),
            .start_resource = 160U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 16U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_VINT_TO_MCU_M4FSS0_CORE0),
            .start_resource = 168U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1024U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_TIMERMGR_EVT_OES),
            .start_resource = 0U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 42U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_PKTDMA_TX_CHAN_ERROR_OES),
            .start_resource = 4096U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 112U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_PKTDMA_TX_FLOW_COMPLETION_OES),
            .start_resource = 4608U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 29U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_PKTDMA_RX_CHAN_ERROR_OES),
            .start_resource = 5120U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 176U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_PKTDMA_RX_FLOW_COMPLETION_OES),
            .start_resource = 5632U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 176U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_PKTDMA_RX_FLOW_STARVATION_OES),
            .start_resource = 6144U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 176U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_PKTDMA_RX_FLOW_FIREWALL_OES),
            .start_resource = 6656U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 28U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_BCDMA_CHAN_ERROR_OES),
            .start_resource = 8192U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 28U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_BCDMA_CHAN_DATA_COMPLETION_OES),
            .start_resource = 8704U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 28U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_BCDMA_CHAN_RING_COMPLETION_OES),
            .start_resource = 9216U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 20U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_BCDMA_TX_CHAN_ERROR_OES),
            .start_resource = 9728U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 20U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_BCDMA_TX_CHAN_DATA_COMPLETION_OES),
            .start_resource = 10240U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 20U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_BCDMA_TX_CHAN_RING_COMPLETION_OES),
            .start_resource = 10752U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 20U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_BCDMA_RX_CHAN_ERROR_OES),
            .start_resource = 11264U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 20U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_BCDMA_RX_CHAN_DATA_COMPLETION_OES),
            .start_resource = 11776U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 20U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_IA_BCDMA_RX_CHAN_RING_COMPLETION_OES),
            .start_resource = 12288U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1521,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_GLOBAL_EVENT_SEVT),
            .start_resource = 15,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 4U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_MCU_M4FSS0_CORE0, TISCI_RESASG_SUBTYPE_MCU_M4FSS0_CORE0_NVIC_IRQ_GROUP0_FROM_MCU_MCU_GPIOMUX_INTROUTER0),
            .start_resource = 0U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 16U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_MCU_M4FSS0_CORE0, TISCI_RESASG_SUBTYPE_MCU_M4FSS0_CORE0_NVIC_IRQ_GROUP0_FROM_DMASS0_INTAGGR_0),
            .start_resource = 32U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 16U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_GICSS0, TISCI_RESASG_SUBTYPE_GICSS0_SPI_IRQ_GROUP0_FROM_MAIN_GPIOMUX_INTROUTER0),
            .start_resource = 32U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 16U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_GICSS0, TISCI_RESASG_SUBTYPE_GICSS0_SPI_IRQ_GROUP0_FROM_CMP_EVENT_INTROUTER0),
            .start_resource = 48U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 36U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_GICSS0, TISCI_RESASG_SUBTYPE_GICSS0_SPI_IRQ_GROUP0_FROM_DMASS0_INTAGGR_0),
            .start_resource = 68U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 4U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_GICSS0, TISCI_RESASG_SUBTYPE_GICSS0_SPI_IRQ_GROUP0_FROM_MCU_MCU_GPIOMUX_INTROUTER0),
            .start_resource = 104U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_PCIE0, TISCI_RESASG_SUBTYPE_PCIE0_PCIE_CPTS_HW2_PUSH_IRQ_GROUP0_FROM_TIMESYNC_EVENT_INTROUTER0),
            .start_resource = 0U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_PRU_ICSSG0, TISCI_RESASG_SUBTYPE_PRU_ICSSG0_PR1_EDC0_LATCH0_IN_IRQ_GROUP0_FROM_TIMESYNC_EVENT_INTROUTER0),
            .start_resource = 0U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_PRU_ICSSG0, TISCI_RESASG_SUBTYPE_PRU_ICSSG0_PR1_EDC0_LATCH1_IN_IRQ_GROUP0_FROM_TIMESYNC_EVENT_INTROUTER0),
            .start_resource = 1U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_PRU_ICSSG0, TISCI_RESASG_SUBTYPE_PRU_ICSSG0_PR1_EDC1_LATCH0_IN_IRQ_GROUP0_FROM_TIMESYNC_EVENT_INTROUTER0),
            .start_resource = 2U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_PRU_ICSSG0, TISCI_RESASG_SUBTYPE_PRU_ICSSG0_PR1_EDC1_LATCH1_IN_IRQ_GROUP0_FROM_TIMESYNC_EVENT_INTROUTER0),
            .start_resource = 3U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 6U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_PRU_ICSSG0, TISCI_RESASG_SUBTYPE_PRU_ICSSG0_PR1_IEP0_CAP_INTR_REQ_IRQ_GROUP0_FROM_MAIN_GPIOMUX_INTROUTER0),
            .start_resource = 4U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 6U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_PRU_ICSSG0, TISCI_RESASG_SUBTYPE_PRU_ICSSG0_PR1_IEP1_CAP_INTR_REQ_IRQ_GROUP0_FROM_MAIN_GPIOMUX_INTROUTER0),
            .start_resource = 10U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_PRU_ICSSG0, TISCI_RESASG_SUBTYPE_PRU_ICSSG0_PR1_SLV_INTR_IRQ_GROUP0_FROM_DMASS0_INTAGGR_0),
            .start_resource = 16U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_PRU_ICSSG0, TISCI_RESASG_SUBTYPE_PRU_ICSSG0_PR1_SLV_INTR_IRQ_GROUP0_FROM_MAIN_GPIOMUX_INTROUTER0),
            .start_resource = 46U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_PRU_ICSSG1, TISCI_RESASG_SUBTYPE_PRU_ICSSG1_PR1_EDC0_LATCH0_IN_IRQ_GROUP0_FROM_TIMESYNC_EVENT_INTROUTER0),
            .start_resource = 0U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_PRU_ICSSG1, TISCI_RESASG_SUBTYPE_PRU_ICSSG1_PR1_EDC0_LATCH1_IN_IRQ_GROUP0_FROM_TIMESYNC_EVENT_INTROUTER0),
            .start_resource = 1U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_PRU_ICSSG1, TISCI_RESASG_SUBTYPE_PRU_ICSSG1_PR1_EDC1_LATCH0_IN_IRQ_GROUP0_FROM_TIMESYNC_EVENT_INTROUTER0),
            .start_resource = 2U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_PRU_ICSSG1, TISCI_RESASG_SUBTYPE_PRU_ICSSG1_PR1_EDC1_LATCH1_IN_IRQ_GROUP0_FROM_TIMESYNC_EVENT_INTROUTER0),
            .start_resource = 3U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 6U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_PRU_ICSSG1, TISCI_RESASG_SUBTYPE_PRU_ICSSG1_PR1_IEP0_CAP_INTR_REQ_IRQ_GROUP0_FROM_MAIN_GPIOMUX_INTROUTER0),
            .start_resource = 4U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 6U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_PRU_ICSSG1, TISCI_RESASG_SUBTYPE_PRU_ICSSG1_PR1_IEP1_CAP_INTR_REQ_IRQ_GROUP0_FROM_MAIN_GPIOMUX_INTROUTER0),
            .start_resource = 10U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_PRU_ICSSG1, TISCI_RESASG_SUBTYPE_PRU_ICSSG1_PR1_SLV_INTR_IRQ_GROUP0_FROM_DMASS0_INTAGGR_0),
            .start_resource = 16U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_PRU_ICSSG1, TISCI_RESASG_SUBTYPE_PRU_ICSSG1_PR1_SLV_INTR_IRQ_GROUP0_FROM_MAIN_GPIOMUX_INTROUTER0),
            .start_resource = 46U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_R5FSS1_CORE1, TISCI_RESASG_SUBTYPE_R5FSS1_CORE1_INTR_IRQ_GROUP0_FROM_DMASS0_INTAGGR_0),
            .start_resource = 8U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 16U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_R5FSS1_CORE1, TISCI_RESASG_SUBTYPE_R5FSS1_CORE1_INTR_IRQ_GROUP0_FROM_MAIN_GPIOMUX_INTROUTER0),
            .start_resource = 32U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_R5FSS1_CORE1, TISCI_RESASG_SUBTYPE_R5FSS1_CORE1_INTR_IRQ_GROUP0_FROM_CMP_EVENT_INTROUTER0),
            .start_resource = 48U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 32U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_R5FSS1_CORE1, TISCI_RESASG_SUBTYPE_R5FSS1_CORE1_INTR_IRQ_GROUP1_FROM_DMASS0_INTAGGR_0),
            .start_resource = 64U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 4U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_R5FSS1_CORE1, TISCI_RESASG_SUBTYPE_R5FSS1_CORE1_INTR_IRQ_GROUP0_FROM_MCU_MCU_GPIOMUX_INTROUTER0),
            .start_resource = 104U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_R5FSS1_CORE0, TISCI_RESASG_SUBTYPE_R5FSS1_CORE0_INTR_IRQ_GROUP0_FROM_DMASS0_INTAGGR_0),
            .start_resource = 8U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 16U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_R5FSS1_CORE0, TISCI_RESASG_SUBTYPE_R5FSS1_CORE0_INTR_IRQ_GROUP0_FROM_MAIN_GPIOMUX_INTROUTER0),
            .start_resource = 32U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_R5FSS1_CORE0, TISCI_RESASG_SUBTYPE_R5FSS1_CORE0_INTR_IRQ_GROUP0_FROM_CMP_EVENT_INTROUTER0),
            .start_resource = 48U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 30U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_R5FSS1_CORE0, TISCI_RESASG_SUBTYPE_R5FSS1_CORE0_INTR_IRQ_GROUP1_FROM_DMASS0_INTAGGR_0),
            .start_resource = 66U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 4U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_R5FSS1_CORE0, TISCI_RESASG_SUBTYPE_R5FSS1_CORE0_INTR_IRQ_GROUP0_FROM_MCU_MCU_GPIOMUX_INTROUTER0),
            .start_resource = 104U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_CPTS0, TISCI_RESASG_SUBTYPE_CPTS0_CPTS_HW1_PUSH_IRQ_GROUP0_FROM_TIMESYNC_EVENT_INTROUTER0),
            .start_resource = 0U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_CPTS0, TISCI_RESASG_SUBTYPE_CPTS0_CPTS_HW2_PUSH_IRQ_GROUP0_FROM_TIMESYNC_EVENT_INTROUTER0),
            .start_resource = 1U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_CPTS0, TISCI_RESASG_SUBTYPE_CPTS0_CPTS_HW3_PUSH_IRQ_GROUP0_FROM_TIMESYNC_EVENT_INTROUTER0),
            .start_resource = 2U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_CPTS0, TISCI_RESASG_SUBTYPE_CPTS0_CPTS_HW4_PUSH_IRQ_GROUP0_FROM_TIMESYNC_EVENT_INTROUTER0),
            .start_resource = 3U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_CPTS0, TISCI_RESASG_SUBTYPE_CPTS0_CPTS_HW5_PUSH_IRQ_GROUP0_FROM_TIMESYNC_EVENT_INTROUTER0),
            .start_resource = 4U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_CPTS0, TISCI_RESASG_SUBTYPE_CPTS0_CPTS_HW6_PUSH_IRQ_GROUP0_FROM_TIMESYNC_EVENT_INTROUTER0),
            .start_resource = 5U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_CPTS0, TISCI_RESASG_SUBTYPE_CPTS0_CPTS_HW7_PUSH_IRQ_GROUP0_FROM_TIMESYNC_EVENT_INTROUTER0),
            .start_resource = 6U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_CPTS0, TISCI_RESASG_SUBTYPE_CPTS0_CPTS_HW8_PUSH_IRQ_GROUP0_FROM_TIMESYNC_EVENT_INTROUTER0),
            .start_resource = 7U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_DMASS0_INTAGGR_0_INTAGGR_LEVI_PEND_IRQ_GROUP0_FROM_CMP_EVENT_INTROUTER0),
            .start_resource = 0U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_DMASS0_INTAGGR_0_INTAGGR_LEVI_PEND_IRQ_GROUP0_FROM_TIMESYNC_EVENT_INTROUTER0),
            .start_resource = 8U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_DMASS0_INTAGGR_0_INTAGGR_LEVI_PEND_IRQ_GROUP0_FROM_MAIN_GPIOMUX_INTROUTER0),
            .start_resource = 16U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 2U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_DMASS0_INTAGGR_0, TISCI_RESASG_SUBTYPE_DMASS0_INTAGGR_0_INTAGGR_LEVI_PEND_IRQ_GROUP1_FROM_MAIN_GPIOMUX_INTROUTER0),
            .start_resource = 24U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 4U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_MCU_ESM0, TISCI_RESASG_SUBTYPE_MCU_ESM0_ESM_PLS_EVENT0_IRQ_GROUP0_FROM_MCU_MCU_GPIOMUX_INTROUTER0),
            .start_resource = 88U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 4U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_MCU_ESM0, TISCI_RESASG_SUBTYPE_MCU_ESM0_ESM_PLS_EVENT1_IRQ_GROUP0_FROM_MCU_MCU_GPIOMUX_INTROUTER0),
            .start_resource = 92U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 4U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_MCU_ESM0, TISCI_RESASG_SUBTYPE_MCU_ESM0_ESM_PLS_EVENT2_IRQ_GROUP0_FROM_MCU_MCU_GPIOMUX_INTROUTER0),
            .start_resource = 96U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_CPSW0, TISCI_RESASG_SUBTYPE_CPSW0_CPTS_HW1_PUSH_IRQ_GROUP0_FROM_TIMESYNC_EVENT_INTROUTER0),
            .start_resource = 0U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_CPSW0, TISCI_RESASG_SUBTYPE_CPSW0_CPTS_HW2_PUSH_IRQ_GROUP0_FROM_TIMESYNC_EVENT_INTROUTER0),
            .start_resource = 1U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_CPSW0, TISCI_RESASG_SUBTYPE_CPSW0_CPTS_HW3_PUSH_IRQ_GROUP0_FROM_TIMESYNC_EVENT_INTROUTER0),
            .start_resource = 2U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_CPSW0, TISCI_RESASG_SUBTYPE_CPSW0_CPTS_HW4_PUSH_IRQ_GROUP0_FROM_TIMESYNC_EVENT_INTROUTER0),
            .start_resource = 3U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_CPSW0, TISCI_RESASG_SUBTYPE_CPSW0_CPTS_HW5_PUSH_IRQ_GROUP0_FROM_TIMESYNC_EVENT_INTROUTER0),
            .start_resource = 4U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_CPSW0, TISCI_RESASG_SUBTYPE_CPSW0_CPTS_HW6_PUSH_IRQ_GROUP0_FROM_TIMESYNC_EVENT_INTROUTER0),
            .start_resource = 5U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_CPSW0, TISCI_RESASG_SUBTYPE_CPSW0_CPTS_HW7_PUSH_IRQ_GROUP0_FROM_TIMESYNC_EVENT_INTROUTER0),
            .start_resource = 6U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 1U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_CPSW0, TISCI_RESASG_SUBTYPE_CPSW0_CPTS_HW8_PUSH_IRQ_GROUP0_FROM_TIMESYNC_EVENT_INTROUTER0),
            .start_resource = 7U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_R5FSS0_CORE0, TISCI_RESASG_SUBTYPE_R5FSS0_CORE0_INTR_IRQ_GROUP0_FROM_DMASS0_INTAGGR_0),
            .start_resource = 8U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 24U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_R5FSS0_CORE0, TISCI_RESASG_SUBTYPE_R5FSS0_CORE0_INTR_IRQ_GROUP0_FROM_MAIN_GPIOMUX_INTROUTER0),
            .start_resource = 32U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 30U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_R5FSS0_CORE0, TISCI_RESASG_SUBTYPE_R5FSS0_CORE0_INTR_IRQ_GROUP1_FROM_DMASS0_INTAGGR_0),
            .start_resource = 66U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 4U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_R5FSS0_CORE0, TISCI_RESASG_SUBTYPE_R5FSS0_CORE0_INTR_IRQ_GROUP0_FROM_MCU_MCU_GPIOMUX_INTROUTER0),
            .start_resource = 104U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 8U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_R5FSS0_CORE1, TISCI_RESASG_SUBTYPE_R5FSS0_CORE1_INTR_IRQ_GROUP0_FROM_DMASS0_INTAGGR_0),
            .start_resource = 8U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 24U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_R5FSS0_CORE1, TISCI_RESASG_SUBTYPE_R5FSS0_CORE1_INTR_IRQ_GROUP0_FROM_MAIN_GPIOMUX_INTROUTER0),
            .start_resource = 32U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 32U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_R5FSS0_CORE1, TISCI_RESASG_SUBTYPE_R5FSS0_CORE1_INTR_IRQ_GROUP1_FROM_DMASS0_INTAGGR_0),
            .start_resource = 64U,
            .host_id = TISCI_HOST_ID_ALL,
        },
        {
            .num_resource = 4U,
            .type = TISCI_RESASG_UTYPE(TISCI_DEV_R5FSS0_CORE1, TISCI_RESASG_SUBTYPE_R5FSS0_CORE1_INTR_IRQ_GROUP0_FROM_MCU_MCU_GPIOMUX_INTROUTER0),
            .start_resource = 104U,
            .host_id = TISCI_HOST_ID_ALL,
        },
    },
};    
#endif

#if defined (BUILD_MCU1_0)
const struct tisci_boardcfg_sec gBoardConfigLow_security
__attribute__(( aligned(128), section(".boardcfg_data") )) =
{
    /* boardcfg_abi_rev */
    .rev = {
        .tisci_boardcfg_abi_maj = TISCI_BOARDCFG_SEC_ABI_MAJ_VALUE,
        .tisci_boardcfg_abi_min = TISCI_BOARDCFG_SEC_ABI_MIN_VALUE,
    },

    /* boardcfg_proc_acl */
    .processor_acl_list = {
        .subhdr = {
            .magic = TISCI_BOARDCFG_PROC_ACL_MAGIC_NUM,
            .size = sizeof(struct tisci_boardcfg_proc_acl),
        },
        .proc_acl_entries = {0},
    },

    /* boardcfg_host_hierarchy */
    .host_hierarchy = {
        .subhdr = {
            .magic = TISCI_BOARDCFG_HOST_HIERARCHY_MAGIC_NUM,
            .size = sizeof(struct tisci_boardcfg_host_hierarchy),
        },
        .host_hierarchy_entries = {0},
    },
};
#endif
