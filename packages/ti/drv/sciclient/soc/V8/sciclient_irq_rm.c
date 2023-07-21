/*
 * Copyright (c) 2023, Texas Instruments Incorporated
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
 *  \file V8/sciclient_irq_rm.c
 *
 *  \brief irq_tree for J722S
 *
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/sciclient/src/sciclient/sciclient_rm_priv.h>
#include <ti/drv/sciclient/soc/V8/sciclient_irq_rm.h>

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
static struct Sciclient_rmIaUsedMapping rom_usage_DMASS0_INTAGGR_0[1U] = {
    {
        .event = 30U,
        .cleared = false,
    },
};
uint8_t vint_usage_count_DMASS0_INTAGGR_0[184U]= {0};

static struct Sciclient_rmIaUsedMapping rom_usage_DMASS1_INTAGGR_0[1U] = {
    {
        .event = 5651U,
        .cleared = false,
    },
};
uint8_t vint_usage_count_DMASS1_INTAGGR_0[40]= {0};
struct Sciclient_rmIaInst gRmIaInstances[SCICLIENT_RM_IA_NUM_INST] =
{
    {
        .dev_id             = TISCI_DEV_DMASS0_INTAGGR_0,
        .imap               = 0x48100000,
        .sevt_offset        = 0u,
        .n_sevt             = 1536u,
        .n_vint             = 184,
        .vint_usage_count   = &vint_usage_count_DMASS0_INTAGGR_0[0],
        .v0_b0_evt          = 0,
        .rom_usage = &rom_usage_DMASS0_INTAGGR_0[0U],
		.n_rom_usage = 1,
    },
    {
        .dev_id             = TISCI_DEV_DMASS1_INTAGGR_0,
        .imap               = 0x4e0b0000,
        .sevt_offset        = 12288u,
        .n_sevt             = 216u,
        .n_vint             = 40,
        .vint_usage_count   = &vint_usage_count_DMASS1_INTAGGR_0[0],
        .v0_b0_evt          = 0,
        .rom_usage = &rom_usage_DMASS1_INTAGGR_0[0U],
		.n_rom_usage = 1,
    }
};

struct Sciclient_rmIrInst gRmIrInstances[SCICLIENT_RM_IR_NUM_INST] =
{
    {
        .dev_id         = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
        .cfg            = 0xa00000,
        .n_inp          = 200u,
        .n_outp         = 36u,
        .inp0_mapping   = 0,
        .rom_usage      = NULL,
        .n_rom_usage    = 0U,
    },
    {
        .dev_id         = TISCI_DEV_WKUP_MCU_GPIOMUX_INTROUTER0,
        .cfg            = 0x4210000,
        .n_inp          = 32u,
        .n_outp         = 16u,
        .inp0_mapping   = 0,
        .rom_usage      = NULL,
        .n_rom_usage    = 0U,
    },
    {
        .dev_id         = TISCI_DEV_TIMESYNC_EVENT_INTROUTER0,
        .cfg            = 0xa40000,
        .n_inp          = 20u,
        .n_outp         = 26u,
        .inp0_mapping   = 0,
        .rom_usage      = NULL,
        .n_rom_usage    = 0U,
    },
};

/* IRQ Tree definition */

/* Start of MAIN_GPIOMUX_INTROUTER0 interface definition */
const struct Sciclient_rmIrqIf MAIN_GPIOMUX_INTROUTER0_outp_0_15_to_GICSS0_spi_32_47 = {
	.lbase = 0,
	.len = 16,
	.rid = TISCI_DEV_GICSS0,
	.rbase = 32,
};
const struct Sciclient_rmIrqIf MAIN_GPIOMUX_INTROUTER0_outp_0_15_to_WKUP_R5FSS0_CORE0_intr_32_47 = {
	.lbase = 0,
	.len = 16,
	.rid = TISCI_DEV_WKUP_R5FSS0_CORE0,
	.rbase = 32,
};
const struct Sciclient_rmIrqIf MAIN_GPIOMUX_INTROUTER0_outp_0_15_to_C7X256V0_CLEC_gic_spi_32_47 = {
	.lbase = 0,
	.len = 16,
	.rid = TISCI_DEV_C7X256V0_CLEC,
	.rbase = 32,
};
const struct Sciclient_rmIrqIf MAIN_GPIOMUX_INTROUTER0_outp_0_15_to_C7X256V1_CLEC_gic_spi_32_47 = {
	.lbase = 0,
	.len = 16,
	.rid = TISCI_DEV_C7X256V1_CLEC,
	.rbase = 32,
};
const struct Sciclient_rmIrqIf MAIN_GPIOMUX_INTROUTER0_outp_20_21_to_R5FSS0_CORE0_intr_56_57 = {
	.lbase = 20,
	.len = 2,
	.rid = TISCI_DEV_R5FSS0_CORE0,
	.rbase = 56,
};
const struct Sciclient_rmIrqIf MAIN_GPIOMUX_INTROUTER0_outp_32_33_to_R5FSS0_CORE0_intr_58_59 = {
	.lbase = 32,
	.len = 2,
	.rid = TISCI_DEV_R5FSS0_CORE0,
	.rbase = 58,
};
const struct Sciclient_rmIrqIf MAIN_GPIOMUX_INTROUTER0_outp_16_19_to_R5FSS0_CORE0_intr_104_107 = {
	.lbase = 16,
	.len = 4,
	.rid = TISCI_DEV_R5FSS0_CORE0,
	.rbase = 104,
};
const struct Sciclient_rmIrqIf MAIN_GPIOMUX_INTROUTER0_outp_24_31_to_DMASS0_INTAGGR_0_intaggr_levi_pend_16_23 = {
	.lbase = 24,
	.len = 8,
	.rid = TISCI_DEV_DMASS0_INTAGGR_0,
	.rbase = 16,
};
const struct Sciclient_rmIrqIf MAIN_GPIOMUX_INTROUTER0_outp_22_23_to_DMASS0_INTAGGR_0_intaggr_levi_pend_24_25 = {
	.lbase = 22,
	.len = 2,
	.rid = TISCI_DEV_DMASS0_INTAGGR_0,
	.rbase = 24,
};
const struct Sciclient_rmIrqIf MAIN_GPIOMUX_INTROUTER0_outp_34_35_to_MCU_R5FSS0_CORE0_cpu0_intr_32_33 = {
	.lbase = 34,
	.len = 2,
	.rid = TISCI_DEV_MCU_R5FSS0_CORE0,
	.rbase = 32,
};
const struct Sciclient_rmIrqIf * const tisci_if_MAIN_GPIOMUX_INTROUTER0[] = {
	&MAIN_GPIOMUX_INTROUTER0_outp_0_15_to_GICSS0_spi_32_47,
	&MAIN_GPIOMUX_INTROUTER0_outp_0_15_to_WKUP_R5FSS0_CORE0_intr_32_47,
	&MAIN_GPIOMUX_INTROUTER0_outp_0_15_to_C7X256V0_CLEC_gic_spi_32_47,
	&MAIN_GPIOMUX_INTROUTER0_outp_0_15_to_C7X256V1_CLEC_gic_spi_32_47,
	&MAIN_GPIOMUX_INTROUTER0_outp_20_21_to_R5FSS0_CORE0_intr_56_57,
	&MAIN_GPIOMUX_INTROUTER0_outp_32_33_to_R5FSS0_CORE0_intr_58_59,
	&MAIN_GPIOMUX_INTROUTER0_outp_16_19_to_R5FSS0_CORE0_intr_104_107,
	&MAIN_GPIOMUX_INTROUTER0_outp_24_31_to_DMASS0_INTAGGR_0_intaggr_levi_pend_16_23,
	&MAIN_GPIOMUX_INTROUTER0_outp_22_23_to_DMASS0_INTAGGR_0_intaggr_levi_pend_24_25,
	&MAIN_GPIOMUX_INTROUTER0_outp_34_35_to_MCU_R5FSS0_CORE0_cpu0_intr_32_33,
};
static const struct Sciclient_rmIrqNode tisci_irq_MAIN_GPIOMUX_INTROUTER0 = {
	.id = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.n_if = 10,
	.p_if = &tisci_if_MAIN_GPIOMUX_INTROUTER0[0],
};

/* Start of WKUP_MCU_GPIOMUX_INTROUTER0 interface definition */
const struct Sciclient_rmIrqIf WKUP_MCU_GPIOMUX_INTROUTER0_outp_0_3_to_GICSS0_spi_104_107 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_GICSS0,
	.rbase = 104,
};
const struct Sciclient_rmIrqIf WKUP_MCU_GPIOMUX_INTROUTER0_outp_0_3_to_WKUP_R5FSS0_CORE0_intr_104_107 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_WKUP_R5FSS0_CORE0,
	.rbase = 104,
};
const struct Sciclient_rmIrqIf WKUP_MCU_GPIOMUX_INTROUTER0_outp_0_3_to_C7X256V0_CLEC_gic_spi_104_107 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_C7X256V0_CLEC,
	.rbase = 104,
};
const struct Sciclient_rmIrqIf WKUP_MCU_GPIOMUX_INTROUTER0_outp_0_3_to_C7X256V1_CLEC_gic_spi_104_107 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_C7X256V1_CLEC,
	.rbase = 104,
};
const struct Sciclient_rmIrqIf WKUP_MCU_GPIOMUX_INTROUTER0_outp_4_7_to_MCU_R5FSS0_CORE0_cpu0_intr_104_107 = {
	.lbase = 4,
	.len = 4,
	.rid = TISCI_DEV_MCU_R5FSS0_CORE0,
	.rbase = 104,
};
const struct Sciclient_rmIrqIf WKUP_MCU_GPIOMUX_INTROUTER0_outp_8_11_to_WKUP_ESM0_esm_pls_event0_88_91 = {
	.lbase = 8,
	.len = 4,
	.rid = TISCI_DEV_WKUP_ESM0,
	.rbase = 88,
};
const struct Sciclient_rmIrqIf WKUP_MCU_GPIOMUX_INTROUTER0_outp_8_11_to_WKUP_ESM0_esm_pls_event1_92_95 = {
	.lbase = 8,
	.len = 4,
	.rid = TISCI_DEV_WKUP_ESM0,
	.rbase = 92,
};
const struct Sciclient_rmIrqIf WKUP_MCU_GPIOMUX_INTROUTER0_outp_8_11_to_WKUP_ESM0_esm_pls_event2_96_99 = {
	.lbase = 8,
	.len = 4,
	.rid = TISCI_DEV_WKUP_ESM0,
	.rbase = 96,
};
const struct Sciclient_rmIrqIf WKUP_MCU_GPIOMUX_INTROUTER0_outp_12_13_to_R5FSS0_CORE0_intr_32_33 = {
	.lbase = 12,
	.len = 2,
	.rid = TISCI_DEV_R5FSS0_CORE0,
	.rbase = 32,
};
const struct Sciclient_rmIrqIf WKUP_MCU_GPIOMUX_INTROUTER0_outp_14_15_to_R5FSS0_CORE0_intr_60_61 = {
	.lbase = 14,
	.len = 2,
	.rid = TISCI_DEV_R5FSS0_CORE0,
	.rbase = 60,
};
const struct Sciclient_rmIrqIf * const tisci_if_WKUP_MCU_GPIOMUX_INTROUTER0[] = {
	&WKUP_MCU_GPIOMUX_INTROUTER0_outp_0_3_to_GICSS0_spi_104_107,
	&WKUP_MCU_GPIOMUX_INTROUTER0_outp_0_3_to_WKUP_R5FSS0_CORE0_intr_104_107,
	&WKUP_MCU_GPIOMUX_INTROUTER0_outp_0_3_to_C7X256V0_CLEC_gic_spi_104_107,
	&WKUP_MCU_GPIOMUX_INTROUTER0_outp_0_3_to_C7X256V1_CLEC_gic_spi_104_107,
	&WKUP_MCU_GPIOMUX_INTROUTER0_outp_4_7_to_MCU_R5FSS0_CORE0_cpu0_intr_104_107,
	&WKUP_MCU_GPIOMUX_INTROUTER0_outp_8_11_to_WKUP_ESM0_esm_pls_event0_88_91,
	&WKUP_MCU_GPIOMUX_INTROUTER0_outp_8_11_to_WKUP_ESM0_esm_pls_event1_92_95,
	&WKUP_MCU_GPIOMUX_INTROUTER0_outp_8_11_to_WKUP_ESM0_esm_pls_event2_96_99,
	&WKUP_MCU_GPIOMUX_INTROUTER0_outp_12_13_to_R5FSS0_CORE0_intr_32_33,
	&WKUP_MCU_GPIOMUX_INTROUTER0_outp_14_15_to_R5FSS0_CORE0_intr_60_61,
};
static const struct Sciclient_rmIrqNode tisci_irq_WKUP_MCU_GPIOMUX_INTROUTER0 = {
	.id = TISCI_DEV_WKUP_MCU_GPIOMUX_INTROUTER0,
	.n_if = 10,
	.p_if = &tisci_if_WKUP_MCU_GPIOMUX_INTROUTER0[0],
};

/* Start of TIMESYNC_EVENT_INTROUTER0 interface definition */
const struct Sciclient_rmIrqIf TIMESYNC_EVENT_INTROUTER0_outl_0_7_to_DMASS0_INTAGGR_0_intaggr_levi_pend_8_15 = {
	.lbase = 0,
	.len = 8,
	.rid = TISCI_DEV_DMASS0_INTAGGR_0,
	.rbase = 8,
};
const struct Sciclient_rmIrqIf TIMESYNC_EVENT_INTROUTER0_outl_8_8_to_PCIE0_pcie_cpts_hw2_push_0_0 = {
	.lbase = 8,
	.len = 1,
	.rid = TISCI_DEV_PCIE0,
	.rbase = 0,
};
const struct Sciclient_rmIrqIf TIMESYNC_EVENT_INTROUTER0_outl_10_10_to_CPSW0_cpts_hw1_push_0_0 = {
	.lbase = 10,
	.len = 1,
	.rid = TISCI_DEV_CPSW0,
	.rbase = 0,
};
const struct Sciclient_rmIrqIf TIMESYNC_EVENT_INTROUTER0_outl_11_11_to_CPSW0_cpts_hw2_push_1_1 = {
	.lbase = 11,
	.len = 1,
	.rid = TISCI_DEV_CPSW0,
	.rbase = 1,
};
const struct Sciclient_rmIrqIf TIMESYNC_EVENT_INTROUTER0_outl_12_12_to_CPSW0_cpts_hw3_push_2_2 = {
	.lbase = 12,
	.len = 1,
	.rid = TISCI_DEV_CPSW0,
	.rbase = 2,
};
const struct Sciclient_rmIrqIf TIMESYNC_EVENT_INTROUTER0_outl_13_13_to_CPSW0_cpts_hw4_push_3_3 = {
	.lbase = 13,
	.len = 1,
	.rid = TISCI_DEV_CPSW0,
	.rbase = 3,
};
const struct Sciclient_rmIrqIf TIMESYNC_EVENT_INTROUTER0_outl_14_14_to_CPSW0_cpts_hw5_push_4_4 = {
	.lbase = 14,
	.len = 1,
	.rid = TISCI_DEV_CPSW0,
	.rbase = 4,
};
const struct Sciclient_rmIrqIf TIMESYNC_EVENT_INTROUTER0_outl_15_15_to_CPSW0_cpts_hw6_push_5_5 = {
	.lbase = 15,
	.len = 1,
	.rid = TISCI_DEV_CPSW0,
	.rbase = 5,
};
const struct Sciclient_rmIrqIf TIMESYNC_EVENT_INTROUTER0_outl_16_16_to_CPSW0_cpts_hw7_push_6_6 = {
	.lbase = 16,
	.len = 1,
	.rid = TISCI_DEV_CPSW0,
	.rbase = 6,
};
const struct Sciclient_rmIrqIf TIMESYNC_EVENT_INTROUTER0_outl_17_17_to_CPSW0_cpts_hw8_push_7_7 = {
	.lbase = 17,
	.len = 1,
	.rid = TISCI_DEV_CPSW0,
	.rbase = 7,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMESYNC_EVENT_INTROUTER0[] = {
	&TIMESYNC_EVENT_INTROUTER0_outl_0_7_to_DMASS0_INTAGGR_0_intaggr_levi_pend_8_15,
	&TIMESYNC_EVENT_INTROUTER0_outl_8_8_to_PCIE0_pcie_cpts_hw2_push_0_0,
	&TIMESYNC_EVENT_INTROUTER0_outl_10_10_to_CPSW0_cpts_hw1_push_0_0,
	&TIMESYNC_EVENT_INTROUTER0_outl_11_11_to_CPSW0_cpts_hw2_push_1_1,
	&TIMESYNC_EVENT_INTROUTER0_outl_12_12_to_CPSW0_cpts_hw3_push_2_2,
	&TIMESYNC_EVENT_INTROUTER0_outl_13_13_to_CPSW0_cpts_hw4_push_3_3,
	&TIMESYNC_EVENT_INTROUTER0_outl_14_14_to_CPSW0_cpts_hw5_push_4_4,
	&TIMESYNC_EVENT_INTROUTER0_outl_15_15_to_CPSW0_cpts_hw6_push_5_5,
	&TIMESYNC_EVENT_INTROUTER0_outl_16_16_to_CPSW0_cpts_hw7_push_6_6,
	&TIMESYNC_EVENT_INTROUTER0_outl_17_17_to_CPSW0_cpts_hw8_push_7_7,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMESYNC_EVENT_INTROUTER0 = {
	.id = TISCI_DEV_TIMESYNC_EVENT_INTROUTER0,
	.n_if = 10,
	.p_if = &tisci_if_TIMESYNC_EVENT_INTROUTER0[0],
};

/* Start of CPSW0 interface definition */
const struct Sciclient_rmIrqIf CPSW0_cpts_comp_0_0_to_DMASS0_INTAGGR_0_intaggr_levi_pend_0_0 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_DMASS0_INTAGGR_0,
	.rbase = 0,
};
const struct Sciclient_rmIrqIf CPSW0_cpts_genf0_1_1_to_TIMESYNC_EVENT_INTROUTER0_in_16_16 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_EVENT_INTROUTER0,
	.rbase = 16,
};
const struct Sciclient_rmIrqIf CPSW0_cpts_genf1_2_2_to_TIMESYNC_EVENT_INTROUTER0_in_17_17 = {
	.lbase = 2,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_EVENT_INTROUTER0,
	.rbase = 17,
};
const struct Sciclient_rmIrqIf CPSW0_cpts_sync_3_3_to_TIMESYNC_EVENT_INTROUTER0_in_18_18 = {
	.lbase = 3,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_EVENT_INTROUTER0,
	.rbase = 18,
};
const struct Sciclient_rmIrqIf * const tisci_if_CPSW0[] = {
	&CPSW0_cpts_comp_0_0_to_DMASS0_INTAGGR_0_intaggr_levi_pend_0_0,
	&CPSW0_cpts_genf0_1_1_to_TIMESYNC_EVENT_INTROUTER0_in_16_16,
	&CPSW0_cpts_genf1_2_2_to_TIMESYNC_EVENT_INTROUTER0_in_17_17,
	&CPSW0_cpts_sync_3_3_to_TIMESYNC_EVENT_INTROUTER0_in_18_18,
};
static const struct Sciclient_rmIrqNode tisci_irq_CPSW0 = {
	.id = TISCI_DEV_CPSW0,
	.n_if = 4,
	.p_if = &tisci_if_CPSW0[0],
};

/* Start of DMASS0_INTAGGR_0 interface definition */
const struct Sciclient_rmIrqIf DMASS0_INTAGGR_0_intaggr_vintr_pend_0_39_to_GICSS0_spi_64_103 = {
	.lbase = 0,
	.len = 40,
	.rid = TISCI_DEV_GICSS0,
	.rbase = 64,
};
const struct Sciclient_rmIrqIf DMASS0_INTAGGR_0_intaggr_vintr_pend_0_39_to_C7X256V0_CLEC_gic_spi_64_103 = {
	.lbase = 0,
	.len = 40,
	.rid = TISCI_DEV_C7X256V0_CLEC,
	.rbase = 64,
};
const struct Sciclient_rmIrqIf DMASS0_INTAGGR_0_intaggr_vintr_pend_84_99_to_C7X256V0_CLEC_soc_events_in_16_31 = {
	.lbase = 84,
	.len = 16,
	.rid = TISCI_DEV_C7X256V0_CLEC,
	.rbase = 16,
};
const struct Sciclient_rmIrqIf DMASS0_INTAGGR_0_intaggr_vintr_pend_0_39_to_C7X256V1_CLEC_gic_spi_64_103 = {
	.lbase = 0,
	.len = 40,
	.rid = TISCI_DEV_C7X256V1_CLEC,
	.rbase = 64,
};
const struct Sciclient_rmIrqIf DMASS0_INTAGGR_0_intaggr_vintr_pend_100_115_to_C7X256V1_CLEC_soc_events_in_16_31 = {
	.lbase = 100,
	.len = 16,
	.rid = TISCI_DEV_C7X256V1_CLEC,
	.rbase = 16,
};
const struct Sciclient_rmIrqIf DMASS0_INTAGGR_0_intaggr_vintr_pend_72_79_to_WKUP_R5FSS0_CORE0_intr_8_15 = {
	.lbase = 72,
	.len = 8,
	.rid = TISCI_DEV_WKUP_R5FSS0_CORE0,
	.rbase = 8,
};
const struct Sciclient_rmIrqIf DMASS0_INTAGGR_0_intaggr_vintr_pend_40_71_to_WKUP_R5FSS0_CORE0_intr_64_95 = {
	.lbase = 40,
	.len = 32,
	.rid = TISCI_DEV_WKUP_R5FSS0_CORE0,
	.rbase = 64,
};
const struct Sciclient_rmIrqIf DMASS0_INTAGGR_0_intaggr_vintr_pend_152_167_to_R5FSS0_CORE0_intr_64_79 = {
	.lbase = 152,
	.len = 16,
	.rid = TISCI_DEV_R5FSS0_CORE0,
	.rbase = 64,
};
const struct Sciclient_rmIrqIf DMASS0_INTAGGR_0_intaggr_vintr_pend_168_183_to_MCU_R5FSS0_CORE0_cpu0_intr_64_79 = {
	.lbase = 168,
	.len = 16,
	.rid = TISCI_DEV_MCU_R5FSS0_CORE0,
	.rbase = 64,
};
const struct Sciclient_rmIrqIf * const tisci_if_DMASS0_INTAGGR_0[] = {
	&DMASS0_INTAGGR_0_intaggr_vintr_pend_0_39_to_GICSS0_spi_64_103,
	&DMASS0_INTAGGR_0_intaggr_vintr_pend_0_39_to_C7X256V0_CLEC_gic_spi_64_103,
	&DMASS0_INTAGGR_0_intaggr_vintr_pend_84_99_to_C7X256V0_CLEC_soc_events_in_16_31,
	&DMASS0_INTAGGR_0_intaggr_vintr_pend_0_39_to_C7X256V1_CLEC_gic_spi_64_103,
	&DMASS0_INTAGGR_0_intaggr_vintr_pend_100_115_to_C7X256V1_CLEC_soc_events_in_16_31,
	&DMASS0_INTAGGR_0_intaggr_vintr_pend_72_79_to_WKUP_R5FSS0_CORE0_intr_8_15,
	&DMASS0_INTAGGR_0_intaggr_vintr_pend_40_71_to_WKUP_R5FSS0_CORE0_intr_64_95,
	&DMASS0_INTAGGR_0_intaggr_vintr_pend_152_167_to_R5FSS0_CORE0_intr_64_79,
	&DMASS0_INTAGGR_0_intaggr_vintr_pend_168_183_to_MCU_R5FSS0_CORE0_cpu0_intr_64_79,
};
static const struct Sciclient_rmIrqNode tisci_irq_DMASS0_INTAGGR_0 = {
	.id = TISCI_DEV_DMASS0_INTAGGR_0,
	.n_if = 9,
	.p_if = &tisci_if_DMASS0_INTAGGR_0[0],
};

/* Start of MCU_TIMER0 interface definition */
const struct Sciclient_rmIrqIf MCU_TIMER0_timer_pwm_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_170_170 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.rbase = 170,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCU_TIMER0[] = {
	&MCU_TIMER0_timer_pwm_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_170_170,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCU_TIMER0 = {
	.id = TISCI_DEV_MCU_TIMER0,
	.n_if = 1,
	.p_if = &tisci_if_MCU_TIMER0[0],
};

/* Start of DMASS1_INTAGGR_0 interface definition */
const struct Sciclient_rmIrqIf DMASS1_INTAGGR_0_intaggr_vintr_pend_0_7_to_GICSS0_spi_237_244 = {
	.lbase = 0,
	.len = 8,
	.rid = TISCI_DEV_GICSS0,
	.rbase = 237,
};
const struct Sciclient_rmIrqIf DMASS1_INTAGGR_0_intaggr_vintr_pend_0_7_to_C7X256V0_CLEC_gic_spi_237_244 = {
	.lbase = 0,
	.len = 8,
	.rid = TISCI_DEV_C7X256V0_CLEC,
	.rbase = 237,
};
const struct Sciclient_rmIrqIf DMASS1_INTAGGR_0_intaggr_vintr_pend_0_7_to_C7X256V1_CLEC_gic_spi_237_244 = {
	.lbase = 0,
	.len = 8,
	.rid = TISCI_DEV_C7X256V1_CLEC,
	.rbase = 237,
};
const struct Sciclient_rmIrqIf DMASS1_INTAGGR_0_intaggr_vintr_pend_8_11_to_WKUP_R5FSS0_CORE0_intr_129_132 = {
	.lbase = 8,
	.len = 4,
	.rid = TISCI_DEV_WKUP_R5FSS0_CORE0,
	.rbase = 129,
};
const struct Sciclient_rmIrqIf DMASS1_INTAGGR_0_intaggr_vintr_pend_12_12_to_WKUP_R5FSS0_CORE0_intr_150_150 = {
	.lbase = 12,
	.len = 1,
	.rid = TISCI_DEV_WKUP_R5FSS0_CORE0,
	.rbase = 150,
};
const struct Sciclient_rmIrqIf DMASS1_INTAGGR_0_intaggr_vintr_pend_13_15_to_WKUP_R5FSS0_CORE0_intr_158_160 = {
	.lbase = 13,
	.len = 3,
	.rid = TISCI_DEV_WKUP_R5FSS0_CORE0,
	.rbase = 158,
};
const struct Sciclient_rmIrqIf DMASS1_INTAGGR_0_intaggr_vintr_pend_32_39_to_R5FSS0_CORE0_intr_8_15 = {
	.lbase = 32,
	.len = 8,
	.rid = TISCI_DEV_R5FSS0_CORE0,
	.rbase = 8,
};
const struct Sciclient_rmIrqIf DMASS1_INTAGGR_0_intaggr_vintr_pend_24_27_to_R5FSS0_CORE0_intr_129_132 = {
	.lbase = 24,
	.len = 4,
	.rid = TISCI_DEV_R5FSS0_CORE0,
	.rbase = 129,
};
const struct Sciclient_rmIrqIf DMASS1_INTAGGR_0_intaggr_vintr_pend_28_29_to_R5FSS0_CORE0_intr_138_139 = {
	.lbase = 28,
	.len = 2,
	.rid = TISCI_DEV_R5FSS0_CORE0,
	.rbase = 138,
};
const struct Sciclient_rmIrqIf DMASS1_INTAGGR_0_intaggr_vintr_pend_30_31_to_R5FSS0_CORE0_intr_143_144 = {
	.lbase = 30,
	.len = 2,
	.rid = TISCI_DEV_R5FSS0_CORE0,
	.rbase = 143,
};
const struct Sciclient_rmIrqIf DMASS1_INTAGGR_0_intaggr_vintr_pend_23_23_to_R5FSS0_CORE0_intr_150_150 = {
	.lbase = 23,
	.len = 1,
	.rid = TISCI_DEV_R5FSS0_CORE0,
	.rbase = 150,
};
const struct Sciclient_rmIrqIf DMASS1_INTAGGR_0_intaggr_vintr_pend_14_15_to_R5FSS0_CORE0_intr_158_159 = {
	.lbase = 14,
	.len = 2,
	.rid = TISCI_DEV_R5FSS0_CORE0,
	.rbase = 158,
};
const struct Sciclient_rmIrqIf DMASS1_INTAGGR_0_intaggr_vintr_pend_22_22_to_R5FSS0_CORE0_intr_160_160 = {
	.lbase = 22,
	.len = 1,
	.rid = TISCI_DEV_R5FSS0_CORE0,
	.rbase = 160,
};
const struct Sciclient_rmIrqIf DMASS1_INTAGGR_0_intaggr_vintr_pend_16_19_to_MCU_R5FSS0_CORE0_cpu0_intr_129_132 = {
	.lbase = 16,
	.len = 4,
	.rid = TISCI_DEV_MCU_R5FSS0_CORE0,
	.rbase = 129,
};
const struct Sciclient_rmIrqIf DMASS1_INTAGGR_0_intaggr_vintr_pend_20_20_to_MCU_R5FSS0_CORE0_cpu0_intr_150_150 = {
	.lbase = 20,
	.len = 1,
	.rid = TISCI_DEV_MCU_R5FSS0_CORE0,
	.rbase = 150,
};
const struct Sciclient_rmIrqIf DMASS1_INTAGGR_0_intaggr_vintr_pend_21_23_to_MCU_R5FSS0_CORE0_cpu0_intr_158_160 = {
	.lbase = 21,
	.len = 3,
	.rid = TISCI_DEV_MCU_R5FSS0_CORE0,
	.rbase = 158,
};
const struct Sciclient_rmIrqIf * const tisci_if_DMASS1_INTAGGR_0[] = {
	&DMASS1_INTAGGR_0_intaggr_vintr_pend_0_7_to_GICSS0_spi_237_244,
	&DMASS1_INTAGGR_0_intaggr_vintr_pend_0_7_to_C7X256V0_CLEC_gic_spi_237_244,
	&DMASS1_INTAGGR_0_intaggr_vintr_pend_0_7_to_C7X256V1_CLEC_gic_spi_237_244,
	&DMASS1_INTAGGR_0_intaggr_vintr_pend_8_11_to_WKUP_R5FSS0_CORE0_intr_129_132,
	&DMASS1_INTAGGR_0_intaggr_vintr_pend_12_12_to_WKUP_R5FSS0_CORE0_intr_150_150,
	&DMASS1_INTAGGR_0_intaggr_vintr_pend_13_15_to_WKUP_R5FSS0_CORE0_intr_158_160,
	&DMASS1_INTAGGR_0_intaggr_vintr_pend_32_39_to_R5FSS0_CORE0_intr_8_15,
	&DMASS1_INTAGGR_0_intaggr_vintr_pend_24_27_to_R5FSS0_CORE0_intr_129_132,
	&DMASS1_INTAGGR_0_intaggr_vintr_pend_28_29_to_R5FSS0_CORE0_intr_138_139,
	&DMASS1_INTAGGR_0_intaggr_vintr_pend_30_31_to_R5FSS0_CORE0_intr_143_144,
	&DMASS1_INTAGGR_0_intaggr_vintr_pend_23_23_to_R5FSS0_CORE0_intr_150_150,
	&DMASS1_INTAGGR_0_intaggr_vintr_pend_14_15_to_R5FSS0_CORE0_intr_158_159,
	&DMASS1_INTAGGR_0_intaggr_vintr_pend_22_22_to_R5FSS0_CORE0_intr_160_160,
	&DMASS1_INTAGGR_0_intaggr_vintr_pend_16_19_to_MCU_R5FSS0_CORE0_cpu0_intr_129_132,
	&DMASS1_INTAGGR_0_intaggr_vintr_pend_20_20_to_MCU_R5FSS0_CORE0_cpu0_intr_150_150,
	&DMASS1_INTAGGR_0_intaggr_vintr_pend_21_23_to_MCU_R5FSS0_CORE0_cpu0_intr_158_160,
};
static const struct Sciclient_rmIrqNode tisci_irq_DMASS1_INTAGGR_0 = {
	.id = TISCI_DEV_DMASS1_INTAGGR_0,
	.n_if = 16,
	.p_if = &tisci_if_DMASS1_INTAGGR_0[0],
};

/* Start of TIMER0 interface definition */
const struct Sciclient_rmIrqIf TIMER0_timer_pwm_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_162_162 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.rbase = 162,
};
const struct Sciclient_rmIrqIf TIMER0_timer_pwm_0_0_to_TIMESYNC_EVENT_INTROUTER0_in_0_0 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_EVENT_INTROUTER0,
	.rbase = 0,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER0[] = {
	&TIMER0_timer_pwm_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_162_162,
	&TIMER0_timer_pwm_0_0_to_TIMESYNC_EVENT_INTROUTER0_in_0_0,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER0 = {
	.id = TISCI_DEV_TIMER0,
	.n_if = 2,
	.p_if = &tisci_if_TIMER0[0],
};

/* Start of TIMER1 interface definition */
const struct Sciclient_rmIrqIf TIMER1_timer_pwm_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_163_163 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.rbase = 163,
};
const struct Sciclient_rmIrqIf TIMER1_timer_pwm_0_0_to_TIMESYNC_EVENT_INTROUTER0_in_1_1 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_EVENT_INTROUTER0,
	.rbase = 1,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER1[] = {
	&TIMER1_timer_pwm_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_163_163,
	&TIMER1_timer_pwm_0_0_to_TIMESYNC_EVENT_INTROUTER0_in_1_1,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER1 = {
	.id = TISCI_DEV_TIMER1,
	.n_if = 2,
	.p_if = &tisci_if_TIMER1[0],
};

/* Start of TIMER2 interface definition */
const struct Sciclient_rmIrqIf TIMER2_timer_pwm_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_164_164 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.rbase = 164,
};
const struct Sciclient_rmIrqIf TIMER2_timer_pwm_0_0_to_TIMESYNC_EVENT_INTROUTER0_in_2_2 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_EVENT_INTROUTER0,
	.rbase = 2,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER2[] = {
	&TIMER2_timer_pwm_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_164_164,
	&TIMER2_timer_pwm_0_0_to_TIMESYNC_EVENT_INTROUTER0_in_2_2,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER2 = {
	.id = TISCI_DEV_TIMER2,
	.n_if = 2,
	.p_if = &tisci_if_TIMER2[0],
};

/* Start of TIMER3 interface definition */
const struct Sciclient_rmIrqIf TIMER3_timer_pwm_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_165_165 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.rbase = 165,
};
const struct Sciclient_rmIrqIf TIMER3_timer_pwm_0_0_to_TIMESYNC_EVENT_INTROUTER0_in_3_3 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_EVENT_INTROUTER0,
	.rbase = 3,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER3[] = {
	&TIMER3_timer_pwm_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_165_165,
	&TIMER3_timer_pwm_0_0_to_TIMESYNC_EVENT_INTROUTER0_in_3_3,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER3 = {
	.id = TISCI_DEV_TIMER3,
	.n_if = 2,
	.p_if = &tisci_if_TIMER3[0],
};

/* Start of TIMER4 interface definition */
const struct Sciclient_rmIrqIf TIMER4_timer_pwm_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_166_166 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.rbase = 166,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER4[] = {
	&TIMER4_timer_pwm_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_166_166,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER4 = {
	.id = TISCI_DEV_TIMER4,
	.n_if = 1,
	.p_if = &tisci_if_TIMER4[0],
};

/* Start of TIMER5 interface definition */
const struct Sciclient_rmIrqIf TIMER5_timer_pwm_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_167_167 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.rbase = 167,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER5[] = {
	&TIMER5_timer_pwm_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_167_167,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER5 = {
	.id = TISCI_DEV_TIMER5,
	.n_if = 1,
	.p_if = &tisci_if_TIMER5[0],
};

/* Start of TIMER6 interface definition */
const struct Sciclient_rmIrqIf TIMER6_timer_pwm_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_168_168 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.rbase = 168,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER6[] = {
	&TIMER6_timer_pwm_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_168_168,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER6 = {
	.id = TISCI_DEV_TIMER6,
	.n_if = 1,
	.p_if = &tisci_if_TIMER6[0],
};

/* Start of TIMER7 interface definition */
const struct Sciclient_rmIrqIf TIMER7_timer_pwm_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_169_169 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.rbase = 169,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER7[] = {
	&TIMER7_timer_pwm_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_169_169,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER7 = {
	.id = TISCI_DEV_TIMER7,
	.n_if = 1,
	.p_if = &tisci_if_TIMER7[0],
};

/* Start of MCU_TIMER1 interface definition */
const struct Sciclient_rmIrqIf MCU_TIMER1_timer_pwm_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_171_171 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.rbase = 171,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCU_TIMER1[] = {
	&MCU_TIMER1_timer_pwm_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_171_171,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCU_TIMER1 = {
	.id = TISCI_DEV_MCU_TIMER1,
	.n_if = 1,
	.p_if = &tisci_if_MCU_TIMER1[0],
};

/* Start of MCU_TIMER2 interface definition */
const struct Sciclient_rmIrqIf MCU_TIMER2_timer_pwm_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_172_172 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.rbase = 172,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCU_TIMER2[] = {
	&MCU_TIMER2_timer_pwm_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_172_172,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCU_TIMER2 = {
	.id = TISCI_DEV_MCU_TIMER2,
	.n_if = 1,
	.p_if = &tisci_if_MCU_TIMER2[0],
};

/* Start of MCU_TIMER3 interface definition */
const struct Sciclient_rmIrqIf MCU_TIMER3_timer_pwm_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_173_173 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.rbase = 173,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCU_TIMER3[] = {
	&MCU_TIMER3_timer_pwm_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_173_173,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCU_TIMER3 = {
	.id = TISCI_DEV_MCU_TIMER3,
	.n_if = 1,
	.p_if = &tisci_if_MCU_TIMER3[0],
};

/* Start of WKUP_TIMER0 interface definition */
const struct Sciclient_rmIrqIf WKUP_TIMER0_timer_pwm_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_174_174 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.rbase = 174,
};
const struct Sciclient_rmIrqIf * const tisci_if_WKUP_TIMER0[] = {
	&WKUP_TIMER0_timer_pwm_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_174_174,
};
static const struct Sciclient_rmIrqNode tisci_irq_WKUP_TIMER0 = {
	.id = TISCI_DEV_WKUP_TIMER0,
	.n_if = 1,
	.p_if = &tisci_if_WKUP_TIMER0[0],
};

/* Start of WKUP_TIMER1 interface definition */
const struct Sciclient_rmIrqIf WKUP_TIMER1_timer_pwm_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_175_175 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.rbase = 175,
};
const struct Sciclient_rmIrqIf * const tisci_if_WKUP_TIMER1[] = {
	&WKUP_TIMER1_timer_pwm_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_175_175,
};
static const struct Sciclient_rmIrqNode tisci_irq_WKUP_TIMER1 = {
	.id = TISCI_DEV_WKUP_TIMER1,
	.n_if = 1,
	.p_if = &tisci_if_WKUP_TIMER1[0],
};

/* Start of WKUP_GTC0 interface definition */
const struct Sciclient_rmIrqIf WKUP_GTC0_gtc_push_event_0_0_to_TIMESYNC_EVENT_INTROUTER0_in_11_11 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_EVENT_INTROUTER0,
	.rbase = 11,
};
const struct Sciclient_rmIrqIf * const tisci_if_WKUP_GTC0[] = {
	&WKUP_GTC0_gtc_push_event_0_0_to_TIMESYNC_EVENT_INTROUTER0_in_11_11,
};
static const struct Sciclient_rmIrqNode tisci_irq_WKUP_GTC0 = {
	.id = TISCI_DEV_WKUP_GTC0,
	.n_if = 1,
	.p_if = &tisci_if_WKUP_GTC0[0],
};

/* Start of GPIO0 interface definition */
const struct Sciclient_rmIrqIf GPIO0_gpio_0_89_to_MAIN_GPIOMUX_INTROUTER0_in_0_89 = {
	.lbase = 0,
	.len = 90,
	.rid = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.rbase = 0,
};
const struct Sciclient_rmIrqIf GPIO0_gpio_90_91_to_MAIN_GPIOMUX_INTROUTER0_in_176_177 = {
	.lbase = 90,
	.len = 2,
	.rid = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.rbase = 176,
};
const struct Sciclient_rmIrqIf GPIO0_gpio_bank_92_97_to_MAIN_GPIOMUX_INTROUTER0_in_190_195 = {
	.lbase = 92,
	.len = 6,
	.rid = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.rbase = 190,
};
const struct Sciclient_rmIrqIf * const tisci_if_GPIO0[] = {
	&GPIO0_gpio_0_89_to_MAIN_GPIOMUX_INTROUTER0_in_0_89,
	&GPIO0_gpio_90_91_to_MAIN_GPIOMUX_INTROUTER0_in_176_177,
	&GPIO0_gpio_bank_92_97_to_MAIN_GPIOMUX_INTROUTER0_in_190_195,
};
static const struct Sciclient_rmIrqNode tisci_irq_GPIO0 = {
	.id = TISCI_DEV_GPIO0,
	.n_if = 3,
	.p_if = &tisci_if_GPIO0[0],
};

/* Start of GPIO1 interface definition */
const struct Sciclient_rmIrqIf GPIO1_gpio_0_71_to_MAIN_GPIOMUX_INTROUTER0_in_90_161 = {
	.lbase = 0,
	.len = 72,
	.rid = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.rbase = 90,
};
const struct Sciclient_rmIrqIf GPIO1_gpio_bank_72_77_to_MAIN_GPIOMUX_INTROUTER0_in_180_185 = {
	.lbase = 72,
	.len = 6,
	.rid = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.rbase = 180,
};
const struct Sciclient_rmIrqIf * const tisci_if_GPIO1[] = {
	&GPIO1_gpio_0_71_to_MAIN_GPIOMUX_INTROUTER0_in_90_161,
	&GPIO1_gpio_bank_72_77_to_MAIN_GPIOMUX_INTROUTER0_in_180_185,
};
static const struct Sciclient_rmIrqNode tisci_irq_GPIO1 = {
	.id = TISCI_DEV_GPIO1,
	.n_if = 2,
	.p_if = &tisci_if_GPIO1[0],
};

/* Start of MCU_GPIO0 interface definition */
const struct Sciclient_rmIrqIf MCU_GPIO0_gpio_0_23_to_WKUP_MCU_GPIOMUX_INTROUTER0_in_0_23 = {
	.lbase = 0,
	.len = 24,
	.rid = TISCI_DEV_WKUP_MCU_GPIOMUX_INTROUTER0,
	.rbase = 0,
};
const struct Sciclient_rmIrqIf MCU_GPIO0_gpio_bank_24_25_to_WKUP_MCU_GPIOMUX_INTROUTER0_in_30_31 = {
	.lbase = 24,
	.len = 2,
	.rid = TISCI_DEV_WKUP_MCU_GPIOMUX_INTROUTER0,
	.rbase = 30,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCU_GPIO0[] = {
	&MCU_GPIO0_gpio_0_23_to_WKUP_MCU_GPIOMUX_INTROUTER0_in_0_23,
	&MCU_GPIO0_gpio_bank_24_25_to_WKUP_MCU_GPIOMUX_INTROUTER0_in_30_31,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCU_GPIO0 = {
	.id = TISCI_DEV_MCU_GPIO0,
	.n_if = 2,
	.p_if = &tisci_if_MCU_GPIO0[0],
};

/* Start of GPMC0 interface definition */
const struct Sciclient_rmIrqIf GPMC0_gpmc_sdmareq_0_0_to_DMASS0_INTAGGR_0_intaggr_levi_pend_26_26 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_DMASS0_INTAGGR_0,
	.rbase = 26,
};
const struct Sciclient_rmIrqIf * const tisci_if_GPMC0[] = {
	&GPMC0_gpmc_sdmareq_0_0_to_DMASS0_INTAGGR_0_intaggr_levi_pend_26_26,
};
static const struct Sciclient_rmIrqNode tisci_irq_GPMC0 = {
	.id = TISCI_DEV_GPMC0,
	.n_if = 1,
	.p_if = &tisci_if_GPMC0[0],
};

/* Start of DSS0 interface definition */
const struct Sciclient_rmIrqIf DSS0_dispc_intr_req_0_0_0_to_DMASS0_INTAGGR_0_intaggr_levi_pend_2_2 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_DMASS0_INTAGGR_0,
	.rbase = 2,
};
const struct Sciclient_rmIrqIf DSS0_dispc_intr_req_1_1_1_to_DMASS0_INTAGGR_0_intaggr_levi_pend_3_3 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_DMASS0_INTAGGR_0,
	.rbase = 3,
};
const struct Sciclient_rmIrqIf * const tisci_if_DSS0[] = {
	&DSS0_dispc_intr_req_0_0_0_to_DMASS0_INTAGGR_0_intaggr_levi_pend_2_2,
	&DSS0_dispc_intr_req_1_1_1_to_DMASS0_INTAGGR_0_intaggr_levi_pend_3_3,
};
static const struct Sciclient_rmIrqNode tisci_irq_DSS0 = {
	.id = TISCI_DEV_DSS0,
	.n_if = 2,
	.p_if = &tisci_if_DSS0[0],
};

/* Start of DSS1 interface definition */
const struct Sciclient_rmIrqIf DSS1_dispc_intr_req_0_0_0_to_DMASS0_INTAGGR_0_intaggr_levi_pend_4_4 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_DMASS0_INTAGGR_0,
	.rbase = 4,
};
const struct Sciclient_rmIrqIf DSS1_dispc_intr_req_1_1_1_to_DMASS0_INTAGGR_0_intaggr_levi_pend_5_5 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_DMASS0_INTAGGR_0,
	.rbase = 5,
};
const struct Sciclient_rmIrqIf * const tisci_if_DSS1[] = {
	&DSS1_dispc_intr_req_0_0_0_to_DMASS0_INTAGGR_0_intaggr_levi_pend_4_4,
	&DSS1_dispc_intr_req_1_1_1_to_DMASS0_INTAGGR_0_intaggr_levi_pend_5_5,
};
static const struct Sciclient_rmIrqNode tisci_irq_DSS1 = {
	.id = TISCI_DEV_DSS1,
	.n_if = 2,
	.p_if = &tisci_if_DSS1[0],
};

/* Start of EPWM0 interface definition */
const struct Sciclient_rmIrqIf EPWM0_epwm_synco_o_0_0_to_TIMESYNC_EVENT_INTROUTER0_in_8_8 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_EVENT_INTROUTER0,
	.rbase = 8,
};
const struct Sciclient_rmIrqIf * const tisci_if_EPWM0[] = {
	&EPWM0_epwm_synco_o_0_0_to_TIMESYNC_EVENT_INTROUTER0_in_8_8,
};
static const struct Sciclient_rmIrqNode tisci_irq_EPWM0 = {
	.id = TISCI_DEV_EPWM0,
	.n_if = 1,
	.p_if = &tisci_if_EPWM0[0],
};

/* Start of MCASP3 interface definition */
const struct Sciclient_rmIrqIf MCASP3_rec_intr_pend_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_186_186 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.rbase = 186,
};
const struct Sciclient_rmIrqIf MCASP3_xmit_intr_pend_1_1_to_MAIN_GPIOMUX_INTROUTER0_in_187_187 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.rbase = 187,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCASP3[] = {
	&MCASP3_rec_intr_pend_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_186_186,
	&MCASP3_xmit_intr_pend_1_1_to_MAIN_GPIOMUX_INTROUTER0_in_187_187,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCASP3 = {
	.id = TISCI_DEV_MCASP3,
	.n_if = 2,
	.p_if = &tisci_if_MCASP3[0],
};

/* Start of MCASP4 interface definition */
const struct Sciclient_rmIrqIf MCASP4_rec_intr_pend_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_188_188 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.rbase = 188,
};
const struct Sciclient_rmIrqIf MCASP4_xmit_intr_pend_1_1_to_MAIN_GPIOMUX_INTROUTER0_in_189_189 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.rbase = 189,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCASP4[] = {
	&MCASP4_rec_intr_pend_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_188_188,
	&MCASP4_xmit_intr_pend_1_1_to_MAIN_GPIOMUX_INTROUTER0_in_189_189,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCASP4 = {
	.id = TISCI_DEV_MCASP4,
	.n_if = 2,
	.p_if = &tisci_if_MCASP4[0],
};

/* Start of MCRC64_0 interface definition */
const struct Sciclient_rmIrqIf MCRC64_0_int_mcrc_4_4_to_DMASS0_INTAGGR_0_intaggr_levi_pend_7_7 = {
	.lbase = 4,
	.len = 1,
	.rid = TISCI_DEV_DMASS0_INTAGGR_0,
	.rbase = 7,
};
const struct Sciclient_rmIrqIf MCRC64_0_dma_event_0_3_to_DMASS0_INTAGGR_0_intaggr_levi_pend_28_31 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_DMASS0_INTAGGR_0,
	.rbase = 28,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCRC64_0[] = {
	&MCRC64_0_int_mcrc_4_4_to_DMASS0_INTAGGR_0_intaggr_levi_pend_7_7,
	&MCRC64_0_dma_event_0_3_to_DMASS0_INTAGGR_0_intaggr_levi_pend_28_31,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCRC64_0 = {
	.id = TISCI_DEV_MCRC64_0,
	.n_if = 2,
	.p_if = &tisci_if_MCRC64_0[0],
};

/* Start of I2C4 interface definition */
const struct Sciclient_rmIrqIf I2C4_pointrpend_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_178_178 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.rbase = 178,
};
const struct Sciclient_rmIrqIf * const tisci_if_I2C4[] = {
	&I2C4_pointrpend_0_0_to_MAIN_GPIOMUX_INTROUTER0_in_178_178,
};
static const struct Sciclient_rmIrqNode tisci_irq_I2C4 = {
	.id = TISCI_DEV_I2C4,
	.n_if = 1,
	.p_if = &tisci_if_I2C4[0],
};

/* Start of PCIE0 interface definition */
const struct Sciclient_rmIrqIf PCIE0_pcie_cpts_comp_0_0_to_DMASS0_INTAGGR_0_intaggr_levi_pend_1_1 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_DMASS0_INTAGGR_0,
	.rbase = 1,
};
const struct Sciclient_rmIrqIf PCIE0_pcie_cpts_genf0_1_1_to_TIMESYNC_EVENT_INTROUTER0_in_4_4 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_EVENT_INTROUTER0,
	.rbase = 4,
};
const struct Sciclient_rmIrqIf PCIE0_pcie_cpts_hw1_push_2_2_to_TIMESYNC_EVENT_INTROUTER0_in_5_5 = {
	.lbase = 2,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_EVENT_INTROUTER0,
	.rbase = 5,
};
const struct Sciclient_rmIrqIf PCIE0_pcie_cpts_sync_3_3_to_TIMESYNC_EVENT_INTROUTER0_in_6_6 = {
	.lbase = 3,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_EVENT_INTROUTER0,
	.rbase = 6,
};
const struct Sciclient_rmIrqIf PCIE0_pcie_ptm_valid_pulse_4_4_to_TIMESYNC_EVENT_INTROUTER0_in_7_7 = {
	.lbase = 4,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_EVENT_INTROUTER0,
	.rbase = 7,
};
const struct Sciclient_rmIrqIf * const tisci_if_PCIE0[] = {
	&PCIE0_pcie_cpts_comp_0_0_to_DMASS0_INTAGGR_0_intaggr_levi_pend_1_1,
	&PCIE0_pcie_cpts_genf0_1_1_to_TIMESYNC_EVENT_INTROUTER0_in_4_4,
	&PCIE0_pcie_cpts_hw1_push_2_2_to_TIMESYNC_EVENT_INTROUTER0_in_5_5,
	&PCIE0_pcie_cpts_sync_3_3_to_TIMESYNC_EVENT_INTROUTER0_in_6_6,
	&PCIE0_pcie_ptm_valid_pulse_4_4_to_TIMESYNC_EVENT_INTROUTER0_in_7_7,
};
static const struct Sciclient_rmIrqNode tisci_irq_PCIE0 = {
	.id = TISCI_DEV_PCIE0,
	.n_if = 5,
	.p_if = &tisci_if_PCIE0[0],
};

/* Start of DEBUGSS0 interface definition */
const struct Sciclient_rmIrqIf DEBUGSS0_davdma_level_0_0_to_DMASS0_INTAGGR_0_intaggr_levi_pend_27_27 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_DMASS0_INTAGGR_0,
	.rbase = 27,
};
const struct Sciclient_rmIrqIf * const tisci_if_DEBUGSS0[] = {
	&DEBUGSS0_davdma_level_0_0_to_DMASS0_INTAGGR_0_intaggr_levi_pend_27_27,
};
static const struct Sciclient_rmIrqNode tisci_irq_DEBUGSS0 = {
	.id = TISCI_DEV_DEBUGSS0,
	.n_if = 1,
	.p_if = &tisci_if_DEBUGSS0[0],
};

/* Start of sam67_dmpac_wrap0 interface definition */
const struct Sciclient_rmIrqIf sam67_dmpac_wrap0_dmpac_level_0_1_to_MAIN_GPIOMUX_INTROUTER0_in_196_197 = {
	.lbase = 0,
	.len = 2,
	.rid = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	.rbase = 196,
};
const struct Sciclient_rmIrqIf * const tisci_if_sam67_dmpac_wrap0[] = {
	&sam67_dmpac_wrap0_dmpac_level_0_1_to_MAIN_GPIOMUX_INTROUTER0_in_196_197,
};
static const struct Sciclient_rmIrqNode tisci_irq_sam67_dmpac_wrap0 = {
	.id = TISCI_DEV_SAM67_DMPAC_WRAP0,
	.n_if = 1,
	.p_if = &tisci_if_sam67_dmpac_wrap0[0],
};


const struct Sciclient_rmIrqNode *const gRmIrqTree[] = {
	&tisci_irq_MAIN_GPIOMUX_INTROUTER0,
	&tisci_irq_WKUP_MCU_GPIOMUX_INTROUTER0,
	&tisci_irq_TIMESYNC_EVENT_INTROUTER0,
	&tisci_irq_CPSW0,
	&tisci_irq_DMASS0_INTAGGR_0,
	&tisci_irq_MCU_TIMER0,
	&tisci_irq_DMASS1_INTAGGR_0,
	&tisci_irq_TIMER0,
	&tisci_irq_TIMER1,
	&tisci_irq_TIMER2,
	&tisci_irq_TIMER3,
	&tisci_irq_TIMER4,
	&tisci_irq_TIMER5,
	&tisci_irq_TIMER6,
	&tisci_irq_TIMER7,
	&tisci_irq_MCU_TIMER1,
	&tisci_irq_MCU_TIMER2,
	&tisci_irq_MCU_TIMER3,
	&tisci_irq_WKUP_TIMER0,
	&tisci_irq_WKUP_TIMER1,
	&tisci_irq_WKUP_GTC0,
	&tisci_irq_GPIO0,
	&tisci_irq_GPIO1,
	&tisci_irq_MCU_GPIO0,
	&tisci_irq_GPMC0,
	&tisci_irq_DSS0,
	&tisci_irq_DSS1,
	&tisci_irq_EPWM0,
	&tisci_irq_MCASP3,
	&tisci_irq_MCASP4,
	&tisci_irq_MCRC64_0,
	&tisci_irq_I2C4,
	&tisci_irq_PCIE0,
	&tisci_irq_DEBUGSS0,
	&tisci_irq_sam67_dmpac_wrap0,
};

const uint32_t gRmIrqTreeCount = sizeof(gRmIrqTree)/sizeof(gRmIrqTree[0]);
