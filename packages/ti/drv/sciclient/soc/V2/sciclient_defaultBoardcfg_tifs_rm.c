/*
 * K3 System Firmware Resource Management Configuration Data
 * Auto generated from K3 Resource Partitioning tool
 *
 * Copyright (c) 2018-2023, Texas Instruments Incorporated
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
 *  \file V2/sciclient_defaultBoardcfg_tifs_rm.c
 *
 *  \brief File containing the tifs_rm_boardcfg default data structure to enable
 *         booting the TIFS firmware.
 *
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/sciclient/soc/sysfw/include/j7200/tisci_hosts.h>
#include <ti/drv/sciclient/soc/sysfw/include/j7200/tisci_boardcfg_constraints.h>
#include <ti/drv/sciclient/soc/sysfw/include/j7200/tisci_devices.h>
#include <ti/drv/sciclient/soc/V2/sciclient_defaultBoardcfg.h>

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#define BOARDCFG_TIFS_RM_RESASG_ENTRIES 213

#if defined (BUILD_MCU1_0)
struct tisci_local_tifs_rm_boardcfg {
    struct tisci_boardcfg_rm rm_boardcfg;
    /**< RM board configuration */
    struct tisci_boardcfg_rm_resasg_entry resasg_entries[BOARDCFG_TIFS_RM_RESASG_ENTRIES];
    /**< Resource Assignment Entries */
};

const struct tisci_local_tifs_rm_boardcfg gBoardConfigLow_rm
__attribute__(( aligned(128), section(".boardcfg_data") )) =
{
    .rm_boardcfg = {
        .rev = {
            .tisci_boardcfg_abi_maj = TISCI_BOARDCFG_RM_ABI_MAJ_VALUE,
            .tisci_boardcfg_abi_min = TISCI_BOARDCFG_RM_ABI_MIN_VALUE,
        },
        .host_cfg = {
            .subhdr = {
                .magic = TISCI_BOARDCFG_RM_HOST_CFG_MAGIC_NUM,
                .size = (uint16_t) sizeof(struct tisci_boardcfg_rm_host_cfg),
            },
            .host_cfg_entries = {
                {
                    .host_id = TISCI_HOST_ID_MCU_0_R5_0,
                    .allowed_atype = 0b101010,
                    .allowed_qos   = 0xAAAA,
                    .allowed_orderid = 0xAAAAAAAA,
                    .allowed_priority = 0xAAAA,
                    .allowed_sched_priority = 0xAA
                },
                {
                    .host_id = TISCI_HOST_ID_MCU_0_R5_2,
                    .allowed_atype = 0b101010,
                    .allowed_qos   = 0xAAAA,
                    .allowed_orderid = 0xAAAAAAAA,
                    .allowed_priority = 0xAAAA,
                    .allowed_sched_priority = 0xAA
                },
                {
                    .host_id = TISCI_HOST_ID_A72_2,
                    .allowed_atype = 0b101010,
                    .allowed_qos   = 0xAAAA,
                    .allowed_orderid = 0xAAAAAAAA,
                    .allowed_priority = 0xAAAA,
                    .allowed_sched_priority = 0xAA
                },
                {
                    .host_id = TISCI_HOST_ID_A72_3,
                    .allowed_atype = 0b101010,
                    .allowed_qos   = 0xAAAA,
                    .allowed_orderid = 0xAAAAAAAA,
                    .allowed_priority = 0xAAAA,
                    .allowed_sched_priority = 0xAA
                },
                {
                    .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
                    .allowed_atype = 0b101010,
                    .allowed_qos   = 0xAAAA,
                    .allowed_orderid = 0xAAAAAAAA,
                    .allowed_priority = 0xAAAA,
                    .allowed_sched_priority = 0xAA
                },
                {
                    .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
                    .allowed_atype = 0b101010,
                    .allowed_qos   = 0xAAAA,
                    .allowed_orderid = 0xAAAAAAAA,
                    .allowed_priority = 0xAAAA,
                    .allowed_sched_priority = 0xAA
                },
            },
        },
        .resasg = {
            .subhdr = {
                .magic = TISCI_BOARDCFG_RM_RESASG_MAGIC_NUM,
                .size = (uint16_t) sizeof(struct tisci_boardcfg_rm_resasg),
            },
            .resasg_entries_size = BOARDCFG_TIFS_RM_RESASG_ENTRIES * sizeof(struct tisci_boardcfg_rm_resasg_entry),
        },
    },
    .resasg_entries = {
        /* Main 2 MCU Level Interrupt router */
        /* Not Applicable for TIFS */
        /* Main 2 MCU Pulse Interrupt router */
        /* Not Applicable for TIFS */
        /* Main GPIO Interrupt router */
        /* Not Applicable for TIFS */
        /* Timesync Interrupt router */
        /* Not Applicable for TIFS */
        /* Wakeup GPIO Interrupt router */
        /* Not Applicable for TIFS */
        /* MODSS Interrupt aggregator0 Virtual interrupts */
            {
                .num_resource = 64,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_MODSS_INTA_0, TISCI_RESASG_SUBTYPE_IA_VINT),
                .start_resource = 0,
                .host_id = TISCI_HOST_ID_ALL,
            },
        /* MODSS Interrupt aggregator0 Global events */
        /* Not Applicable for TIFS */
        /* MODSS Interrupt aggregator1 Virtual interrupts */
            {
                .num_resource = 64,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_MODSS_INTA_1, TISCI_RESASG_SUBTYPE_IA_VINT),
                .start_resource = 0,
                .host_id = TISCI_HOST_ID_ALL,
            },
        /* MODSS Interrupt aggregator1 Global events */
        /* Not Applicable for TIFS */
        /* Main NAVSS UDMA Interrupt aggregator Virtual interrupts */
            {
                .num_resource = 86,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMASS_INTA_0, TISCI_RESASG_SUBTYPE_IA_VINT),
                .start_resource = 18,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 32,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMASS_INTA_0, TISCI_RESASG_SUBTYPE_IA_VINT),
                .start_resource = 104,
                .host_id = TISCI_HOST_ID_A72_3,
            },
            {
                .num_resource = 16,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMASS_INTA_0, TISCI_RESASG_SUBTYPE_IA_VINT),
                .start_resource = 136,
                .host_id = TISCI_HOST_ID_MCU_0_R5_0,
            },
            {
                .num_resource = 16,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMASS_INTA_0, TISCI_RESASG_SUBTYPE_IA_VINT),
                .start_resource = 152,
                .host_id = TISCI_HOST_ID_MCU_0_R5_2,
            },
            {
                .num_resource = 32,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMASS_INTA_0, TISCI_RESASG_SUBTYPE_IA_VINT),
                .start_resource = 168,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
            {
                .num_resource = 24,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMASS_INTA_0, TISCI_RESASG_SUBTYPE_IA_VINT),
                .start_resource = 200,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
            {
                .num_resource = 32,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMASS_INTA_0, TISCI_RESASG_SUBTYPE_IA_VINT),
                .start_resource = 224,
                .host_id = TISCI_HOST_ID_ALL,
            },
        /* Main NAVSS UDMA Interrupt aggregator Global events */
        /* Not Applicable for TIFS */
        /* Main NAVSS Non secure proxies */
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_PROXY_0, TISCI_RESASG_SUBTYPE_PROXY_PROXIES),
                .start_resource = 0,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_PROXY_0, TISCI_RESASG_SUBTYPE_PROXY_PROXIES),
                .start_resource = 4,
                .host_id = TISCI_HOST_ID_A72_3,
            },
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_PROXY_0, TISCI_RESASG_SUBTYPE_PROXY_PROXIES),
                .start_resource = 8,
                .host_id = TISCI_HOST_ID_MCU_0_R5_0,
            },
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_PROXY_0, TISCI_RESASG_SUBTYPE_PROXY_PROXIES),
                .start_resource = 12,
                .host_id = TISCI_HOST_ID_MCU_0_R5_2,
            },
            {
                .num_resource = 16,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_PROXY_0, TISCI_RESASG_SUBTYPE_PROXY_PROXIES),
                .start_resource = 16,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
            {
                .num_resource = 16,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_PROXY_0, TISCI_RESASG_SUBTYPE_PROXY_PROXIES),
                .start_resource = 32,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
            {
                .num_resource = 16,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_PROXY_0, TISCI_RESASG_SUBTYPE_PROXY_PROXIES),
                .start_resource = 48,
                .host_id = TISCI_HOST_ID_ALL,
            },
        /* Main NAVSS Ring accelerator error event config */
            {
                .num_resource = 1,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_ERROR_OES),
                .start_resource = 0,
                .host_id = TISCI_HOST_ID_ALL,
            },
        /* Main NAVSS Ring accelerator Free rings */
            {
                .num_resource = 200,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_GP),
                .start_resource = 120,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 40,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_GP),
                .start_resource = 320,
                .host_id = TISCI_HOST_ID_A72_3,
            },
            {
                .num_resource = 32,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_GP),
                .start_resource = 360,
                .host_id = TISCI_HOST_ID_MCU_0_R5_0,
            },
            {
                .num_resource = 32,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_GP),
                .start_resource = 392,
                .host_id = TISCI_HOST_ID_MCU_0_R5_2,
            },
            {
                .num_resource = 256,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_GP),
                .start_resource = 424,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
            {
                .num_resource = 256,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_GP),
                .start_resource = 680,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
            {
                .num_resource = 38,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_GP),
                .start_resource = 936,
                .host_id = TISCI_HOST_ID_ALL,
            },
        /* Main NAVSS Rings for Normal capacity Rx channels */
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX),
                .start_resource = 64,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX),
                .start_resource = 68,
                .host_id = TISCI_HOST_ID_A72_3,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX),
                .start_resource = 70,
                .host_id = TISCI_HOST_ID_MCU_0_R5_0,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX),
                .start_resource = 72,
                .host_id = TISCI_HOST_ID_MCU_0_R5_2,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX),
                .start_resource = 74,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX),
                .start_resource = 76,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
            {
                .num_resource = 20,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX),
                .start_resource = 78,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX),
                .start_resource = 98,
                .host_id = TISCI_HOST_ID_A72_3,
            },
            {
                .num_resource = 8,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX),
                .start_resource = 102,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
            {
                .num_resource = 8,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX),
                .start_resource = 110,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX),
                .start_resource = 118,
                .host_id = TISCI_HOST_ID_ALL,
            },
        /* Main NAVSS Rings for Normal capacity Tx channels */
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX),
                .start_resource = 4,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX),
                .start_resource = 8,
                .host_id = TISCI_HOST_ID_A72_3,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX),
                .start_resource = 10,
                .host_id = TISCI_HOST_ID_MCU_0_R5_0,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX),
                .start_resource = 12,
                .host_id = TISCI_HOST_ID_MCU_0_R5_2,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX),
                .start_resource = 14,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX),
                .start_resource = 16,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
            {
                .num_resource = 20,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX),
                .start_resource = 18,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX),
                .start_resource = 38,
                .host_id = TISCI_HOST_ID_A72_3,
            },
            {
                .num_resource = 8,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX),
                .start_resource = 42,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
            {
                .num_resource = 8,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX),
                .start_resource = 50,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX),
                .start_resource = 58,
                .host_id = TISCI_HOST_ID_ALL,
            },
        /* Main NAVSS Rings for High capacity Rx channels */
            {
                .num_resource = 0,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX_H),
                .start_resource = 62,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 1,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX_H),
                .start_resource = 62,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 0,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX_H),
                .start_resource = 62,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
            {
                .num_resource = 1,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX_H),
                .start_resource = 63,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
        /* Main NAVSS Rings for Ultra high capacity Rx channels */
            {
                .num_resource = 0,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX_UH),
                .start_resource = 60,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX_UH),
                .start_resource = 60,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
        /* Main NAVSS Rings for High capacity Tx channels */
            {
                .num_resource = 0,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX_H),
                .start_resource = 2,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 1,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX_H),
                .start_resource = 2,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 0,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX_H),
                .start_resource = 2,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
            {
                .num_resource = 1,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX_H),
                .start_resource = 3,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
        /* Main NAVSS Rings for Ultra high capacity Tx channels */
            {
                .num_resource = 0,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX_UH),
                .start_resource = 0,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX_UH),
                .start_resource = 0,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
        /* Main NAVSS Ring accelerator virt_id range */
            {
                .num_resource = 1,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_VIRTID),
                .start_resource = 2,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 1,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_VIRTID),
                .start_resource = 3,
                .host_id = TISCI_HOST_ID_A72_3,
            },
        /* Main NAVSS Ring accelerator ring monitors */
            {
                .num_resource = 3,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_MONITORS),
                .start_resource = 0,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_MONITORS),
                .start_resource = 3,
                .host_id = TISCI_HOST_ID_A72_3,
            },
            {
                .num_resource = 1,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_MONITORS),
                .start_resource = 5,
                .host_id = TISCI_HOST_ID_MCU_0_R5_0,
            },
            {
                .num_resource = 1,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_MONITORS),
                .start_resource = 6,
                .host_id = TISCI_HOST_ID_MCU_0_R5_2,
            },
            {
                .num_resource = 16,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_MONITORS),
                .start_resource = 7,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
            {
                .num_resource = 8,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_MONITORS),
                .start_resource = 23,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
            {
                .num_resource = 1,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_RINGACC_0, TISCI_RESASG_SUBTYPE_RA_MONITORS),
                .start_resource = 31,
                .host_id = TISCI_HOST_ID_ALL,
            },
        /* Main NAVSS UDMA Rx free flows */
            {
                .num_resource = 8,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_FLOW_COMMON),
                .start_resource = 60,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 8,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_FLOW_COMMON),
                .start_resource = 68,
                .host_id = TISCI_HOST_ID_A72_3,
            },
            {
                .num_resource = 8,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_FLOW_COMMON),
                .start_resource = 76,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
            {
                .num_resource = 66,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_FLOW_COMMON),
                .start_resource = 84,
                .host_id = TISCI_HOST_ID_ALL,
            },
        /* Main NAVSS invalid flow event config */
            {
                .num_resource = 1,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_INVALID_FLOW_OES),
                .start_resource = 0,
                .host_id = TISCI_HOST_ID_ALL,
            },
        /* Main NAVSS UDMA global event trigger */
        /* Not Applicable for TIFS */
        /* Main NAVSS UDMA global config */
        /* Not Applicable for TIFS */
        /* Main NAVSS UDMA Normal capacity Rx channels */
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_CHAN),
                .start_resource = 4,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_CHAN),
                .start_resource = 8,
                .host_id = TISCI_HOST_ID_A72_3,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_CHAN),
                .start_resource = 10,
                .host_id = TISCI_HOST_ID_MCU_0_R5_0,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_CHAN),
                .start_resource = 12,
                .host_id = TISCI_HOST_ID_MCU_0_R5_2,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_CHAN),
                .start_resource = 14,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_CHAN),
                .start_resource = 16,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
            {
                .num_resource = 20,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_CHAN),
                .start_resource = 18,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_CHAN),
                .start_resource = 38,
                .host_id = TISCI_HOST_ID_A72_3,
            },
            {
                .num_resource = 8,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_CHAN),
                .start_resource = 42,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
            {
                .num_resource = 8,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_CHAN),
                .start_resource = 50,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_CHAN),
                .start_resource = 58,
                .host_id = TISCI_HOST_ID_ALL,
            },
        /* Main NAVSS UDMA High capacity Rx channels */
            {
                .num_resource = 0,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_HCHAN),
                .start_resource = 2,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 1,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_HCHAN),
                .start_resource = 2,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 0,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_HCHAN),
                .start_resource = 2,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
            {
                .num_resource = 1,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_HCHAN),
                .start_resource = 3,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
        /* Main NAVSS UDMA Ultra high capacity Rx channels */
            {
                .num_resource = 0,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_UHCHAN),
                .start_resource = 0,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_UHCHAN),
                .start_resource = 0,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
        /* Main NAVSS UDMA Normal capacity Tx channels */
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_CHAN),
                .start_resource = 4,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_CHAN),
                .start_resource = 8,
                .host_id = TISCI_HOST_ID_A72_3,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_CHAN),
                .start_resource = 10,
                .host_id = TISCI_HOST_ID_MCU_0_R5_0,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_CHAN),
                .start_resource = 12,
                .host_id = TISCI_HOST_ID_MCU_0_R5_2,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_CHAN),
                .start_resource = 14,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_CHAN),
                .start_resource = 16,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
            {
                .num_resource = 20,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_CHAN),
                .start_resource = 18,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_CHAN),
                .start_resource = 38,
                .host_id = TISCI_HOST_ID_A72_3,
            },
            {
                .num_resource = 8,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_CHAN),
                .start_resource = 42,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
            {
                .num_resource = 8,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_CHAN),
                .start_resource = 50,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_CHAN),
                .start_resource = 58,
                .host_id = TISCI_HOST_ID_ALL,
            },
        /* Main NAVSS UDMA High capacity Tx channels */
            {
                .num_resource = 0,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_HCHAN),
                .start_resource = 2,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 1,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_HCHAN),
                .start_resource = 2,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 0,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_HCHAN),
                .start_resource = 2,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
            {
                .num_resource = 1,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_HCHAN),
                .start_resource = 3,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
        /* Main NAVSS UDMA Ultra high capacity Tx channels */
            {
                .num_resource = 0,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_UHCHAN),
                .start_resource = 0,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_UHCHAN),
                .start_resource = 0,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
        /* Main NAVSS Interrupt router */
        /* Not Applicable for TIFS */
        /* MCU NAVSS Interrupt aggregator Virtual interrupts */
            {
                .num_resource = 32,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMASS_INTA_0, TISCI_RESASG_SUBTYPE_IA_VINT),
                .start_resource = 15,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 16,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMASS_INTA_0, TISCI_RESASG_SUBTYPE_IA_VINT),
                .start_resource = 47,
                .host_id = TISCI_HOST_ID_A72_3,
            },
            {
                .num_resource = 64,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMASS_INTA_0, TISCI_RESASG_SUBTYPE_IA_VINT),
                .start_resource = 63,
                .host_id = TISCI_HOST_ID_MCU_0_R5_0,
            },
            {
                .num_resource = 32,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMASS_INTA_0, TISCI_RESASG_SUBTYPE_IA_VINT),
                .start_resource = 127,
                .host_id = TISCI_HOST_ID_MCU_0_R5_2,
            },
            {
                .num_resource = 16,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMASS_INTA_0, TISCI_RESASG_SUBTYPE_IA_VINT),
                .start_resource = 159,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
            {
                .num_resource = 16,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMASS_INTA_0, TISCI_RESASG_SUBTYPE_IA_VINT),
                .start_resource = 175,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
            {
                .num_resource = 65,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMASS_INTA_0, TISCI_RESASG_SUBTYPE_IA_VINT),
                .start_resource = 191,
                .host_id = TISCI_HOST_ID_ALL,
            },
        /* MCU NAVSS Interrupt aggregator Global events */
        /* Not Applicable for TIFS */
        /* MCU NAVSS Non secure proxies */
            {
                .num_resource = 8,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_PROXY0, TISCI_RESASG_SUBTYPE_PROXY_PROXIES),
                .start_resource = 1,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_PROXY0, TISCI_RESASG_SUBTYPE_PROXY_PROXIES),
                .start_resource = 9,
                .host_id = TISCI_HOST_ID_A72_3,
            },
            {
                .num_resource = 16,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_PROXY0, TISCI_RESASG_SUBTYPE_PROXY_PROXIES),
                .start_resource = 13,
                .host_id = TISCI_HOST_ID_MCU_0_R5_0,
            },
            {
                .num_resource = 16,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_PROXY0, TISCI_RESASG_SUBTYPE_PROXY_PROXIES),
                .start_resource = 29,
                .host_id = TISCI_HOST_ID_MCU_0_R5_2,
            },
            {
                .num_resource = 8,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_PROXY0, TISCI_RESASG_SUBTYPE_PROXY_PROXIES),
                .start_resource = 45,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
            {
                .num_resource = 8,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_PROXY0, TISCI_RESASG_SUBTYPE_PROXY_PROXIES),
                .start_resource = 53,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
            {
                .num_resource = 3,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_PROXY0, TISCI_RESASG_SUBTYPE_PROXY_PROXIES),
                .start_resource = 61,
                .host_id = TISCI_HOST_ID_ALL,
            },
        /* MCU NAVSS Ring accelerator error event config */
            {
                .num_resource = 1,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_ERROR_OES),
                .start_resource = 0,
                .host_id = TISCI_HOST_ID_ALL,
            },
        /* MCU NAVSS Ring accelerator Free rings */
            {
                .num_resource = 32,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_GP),
                .start_resource = 96,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 16,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_GP),
                .start_resource = 128,
                .host_id = TISCI_HOST_ID_A72_3,
            },
            {
                .num_resource = 32,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_GP),
                .start_resource = 144,
                .host_id = TISCI_HOST_ID_MCU_0_R5_0,
            },
            {
                .num_resource = 32,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_GP),
                .start_resource = 176,
                .host_id = TISCI_HOST_ID_MCU_0_R5_2,
            },
            {
                .num_resource = 16,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_GP),
                .start_resource = 208,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
            {
                .num_resource = 16,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_GP),
                .start_resource = 224,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
            {
                .num_resource = 12,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_GP),
                .start_resource = 240,
                .host_id = TISCI_HOST_ID_ALL,
            },
        /* MCU NAVSS Rings for Normal capacity Rx channels */
            {
                .num_resource = 3,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX),
                .start_resource = 50,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX),
                .start_resource = 53,
                .host_id = TISCI_HOST_ID_A72_3,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX),
                .start_resource = 55,
                .host_id = TISCI_HOST_ID_MCU_0_R5_0,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX),
                .start_resource = 57,
                .host_id = TISCI_HOST_ID_MCU_0_R5_2,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX),
                .start_resource = 59,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX),
                .start_resource = 61,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
            {
                .num_resource = 9,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX),
                .start_resource = 63,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX),
                .start_resource = 72,
                .host_id = TISCI_HOST_ID_A72_3,
            },
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX),
                .start_resource = 76,
                .host_id = TISCI_HOST_ID_MCU_0_R5_0,
            },
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX),
                .start_resource = 80,
                .host_id = TISCI_HOST_ID_MCU_0_R5_2,
            },
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX),
                .start_resource = 84,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX),
                .start_resource = 88,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
            {
                .num_resource = 1,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX),
                .start_resource = 92,
                .host_id = TISCI_HOST_ID_ALL,
            },
        /* MCU NAVSS Rings for Normal capacity Tx channels */
            {
                .num_resource = 3,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX),
                .start_resource = 2,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX),
                .start_resource = 5,
                .host_id = TISCI_HOST_ID_A72_3,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX),
                .start_resource = 7,
                .host_id = TISCI_HOST_ID_MCU_0_R5_0,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX),
                .start_resource = 9,
                .host_id = TISCI_HOST_ID_MCU_0_R5_2,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX),
                .start_resource = 11,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX),
                .start_resource = 13,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
            {
                .num_resource = 9,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX),
                .start_resource = 15,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX),
                .start_resource = 24,
                .host_id = TISCI_HOST_ID_A72_3,
            },
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX),
                .start_resource = 28,
                .host_id = TISCI_HOST_ID_MCU_0_R5_0,
            },
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX),
                .start_resource = 32,
                .host_id = TISCI_HOST_ID_MCU_0_R5_2,
            },
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX),
                .start_resource = 36,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX),
                .start_resource = 40,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX),
                .start_resource = 44,
                .host_id = TISCI_HOST_ID_ALL,
            },
        /* MCU NAVSS Rings for High capacity Rx channels */
            {
                .num_resource = 0,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX_H),
                .start_resource = 48,
                .host_id = TISCI_HOST_ID_MCU_0_R5_0,
            },
            {
                .num_resource = 0,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX_H),
                .start_resource = 48,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 1,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX_H),
                .start_resource = 48,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 1,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_RX_H),
                .start_resource = 49,
                .host_id = TISCI_HOST_ID_MCU_0_R5_0,
            },
        /* MCU NAVSS Rings for High capacity Tx channels */
            {
                .num_resource = 0,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX_H),
                .start_resource = 0,
                .host_id = TISCI_HOST_ID_MCU_0_R5_0,
            },
            {
                .num_resource = 0,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX_H),
                .start_resource = 0,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 1,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX_H),
                .start_resource = 0,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 1,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_UDMAP_TX_H),
                .start_resource = 1,
                .host_id = TISCI_HOST_ID_MCU_0_R5_0,
            },
        /* MCU NAVSS Ring accelerator virt_id range */
            {
                .num_resource = 1,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_VIRTID),
                .start_resource = 2,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 1,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_VIRTID),
                .start_resource = 3,
                .host_id = TISCI_HOST_ID_A72_3,
            },
        /* MCU NAVSS Ring accelerator ring monitors */
            {
                .num_resource = 3,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_MONITORS),
                .start_resource = 0,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_MONITORS),
                .start_resource = 3,
                .host_id = TISCI_HOST_ID_A72_3,
            },
            {
                .num_resource = 6,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_MONITORS),
                .start_resource = 5,
                .host_id = TISCI_HOST_ID_MCU_0_R5_0,
            },
            {
                .num_resource = 6,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_MONITORS),
                .start_resource = 11,
                .host_id = TISCI_HOST_ID_MCU_0_R5_2,
            },
            {
                .num_resource = 5,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_MONITORS),
                .start_resource = 17,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
            {
                .num_resource = 5,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_MONITORS),
                .start_resource = 22,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
            {
                .num_resource = 5,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_RINGACC0, TISCI_RESASG_SUBTYPE_RA_MONITORS),
                .start_resource = 27,
                .host_id = TISCI_HOST_ID_ALL,
            },
        /* MCU NAVSS UDMA Rx free flows */
            {
                .num_resource = 8,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_FLOW_COMMON),
                .start_resource = 48,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_FLOW_COMMON),
                .start_resource = 56,
                .host_id = TISCI_HOST_ID_A72_3,
            },
            {
                .num_resource = 8,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_FLOW_COMMON),
                .start_resource = 60,
                .host_id = TISCI_HOST_ID_MCU_0_R5_0,
            },
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_FLOW_COMMON),
                .start_resource = 68,
                .host_id = TISCI_HOST_ID_MCU_0_R5_2,
            },
            {
                .num_resource = 8,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_FLOW_COMMON),
                .start_resource = 72,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_FLOW_COMMON),
                .start_resource = 80,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
            {
                .num_resource = 12,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_FLOW_COMMON),
                .start_resource = 84,
                .host_id = TISCI_HOST_ID_ALL,
            },
        /* MCU NAVSS invalid flow event config */
            {
                .num_resource = 1,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_INVALID_FLOW_OES),
                .start_resource = 0,
                .host_id = TISCI_HOST_ID_ALL,
            },
        /* MCU NAVSS UDMA global event trigger */
        /* Not Applicable for TIFS */
        /* MCU NAVSS UDMA global config */
        /* Not Applicable for TIFS */
        /* MCU NAVSS UDMA Normal capacity Rx channels */
            {
                .num_resource = 3,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_CHAN),
                .start_resource = 2,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_CHAN),
                .start_resource = 5,
                .host_id = TISCI_HOST_ID_A72_3,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_CHAN),
                .start_resource = 7,
                .host_id = TISCI_HOST_ID_MCU_0_R5_0,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_CHAN),
                .start_resource = 9,
                .host_id = TISCI_HOST_ID_MCU_0_R5_2,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_CHAN),
                .start_resource = 11,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_CHAN),
                .start_resource = 13,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
            {
                .num_resource = 9,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_CHAN),
                .start_resource = 15,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_CHAN),
                .start_resource = 24,
                .host_id = TISCI_HOST_ID_A72_3,
            },
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_CHAN),
                .start_resource = 28,
                .host_id = TISCI_HOST_ID_MCU_0_R5_0,
            },
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_CHAN),
                .start_resource = 32,
                .host_id = TISCI_HOST_ID_MCU_0_R5_2,
            },
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_CHAN),
                .start_resource = 36,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_CHAN),
                .start_resource = 40,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
            {
                .num_resource = 1,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_CHAN),
                .start_resource = 44,
                .host_id = TISCI_HOST_ID_ALL,
            },
        /* MCU NAVSS UDMA High capacity Rx channels */
            {
                .num_resource = 0,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_HCHAN),
                .start_resource = 0,
                .host_id = TISCI_HOST_ID_MCU_0_R5_0,
            },
            {
                .num_resource = 0,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_HCHAN),
                .start_resource = 0,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 1,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_HCHAN),
                .start_resource = 0,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 1,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_RX_HCHAN),
                .start_resource = 1,
                .host_id = TISCI_HOST_ID_MCU_0_R5_0,
            },
        /* MCU NAVSS UDMA Normal capacity Tx channels */
            {
                .num_resource = 3,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_CHAN),
                .start_resource = 2,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_CHAN),
                .start_resource = 5,
                .host_id = TISCI_HOST_ID_A72_3,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_CHAN),
                .start_resource = 7,
                .host_id = TISCI_HOST_ID_MCU_0_R5_0,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_CHAN),
                .start_resource = 9,
                .host_id = TISCI_HOST_ID_MCU_0_R5_2,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_CHAN),
                .start_resource = 11,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_CHAN),
                .start_resource = 13,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
            {
                .num_resource = 9,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_CHAN),
                .start_resource = 15,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_CHAN),
                .start_resource = 24,
                .host_id = TISCI_HOST_ID_A72_3,
            },
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_CHAN),
                .start_resource = 28,
                .host_id = TISCI_HOST_ID_MCU_0_R5_0,
            },
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_CHAN),
                .start_resource = 32,
                .host_id = TISCI_HOST_ID_MCU_0_R5_2,
            },
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_CHAN),
                .start_resource = 36,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_0,
            },
            {
                .num_resource = 4,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_CHAN),
                .start_resource = 40,
                .host_id = TISCI_HOST_ID_MAIN_0_R5_2,
            },
            {
                .num_resource = 2,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_CHAN),
                .start_resource = 44,
                .host_id = TISCI_HOST_ID_ALL,
            },
        /* MCU NAVSS UDMA High capacity Tx channels */
            {
                .num_resource = 0,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_HCHAN),
                .start_resource = 0,
                .host_id = TISCI_HOST_ID_MCU_0_R5_0,
            },
            {
                .num_resource = 0,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_HCHAN),
                .start_resource = 0,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 1,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_HCHAN),
                .start_resource = 0,
                .host_id = TISCI_HOST_ID_A72_2,
            },
            {
                .num_resource = 1,
                .type = TISCI_RESASG_UTYPE (TISCI_DEV_MCU_NAVSS0_UDMAP_0, TISCI_RESASG_SUBTYPE_UDMAP_TX_HCHAN),
                .start_resource = 1,
                .host_id = TISCI_HOST_ID_MCU_0_R5_0,
            },
        /* MCU NAVSS Interrupt router */
        /* Not Applicable for TIFS */
    }
};
#endif
