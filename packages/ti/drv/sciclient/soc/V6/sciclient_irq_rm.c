/*
 * Copyright (c) 2022, Texas Instruments Incorporated
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
 *  \file V6/sciclient_irq_rm.c
 *
 *  \brief File containing the J7 Family specific interrupt management data for
 *         RM.
 *
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/sciclient/src/sciclient/sciclient_rm_priv.h>
#include <ti/drv/sciclient/soc/V6/sciclient_irq_rm.h>

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#if defined (SOC_J784S4)
uint8_t vint_usage_count_NAVSS0_MODSS_INTA_0[64] = {0};
uint8_t vint_usage_count_NAVSS0_MODSS_INTA_1[64] = {0};
uint8_t vint_usage_count_NAVSS0_UDMASS_INTA_0[256] = {0};
uint8_t vint_usage_count_MCU_NAVSS0_UDMASS_INTA_0[256] = {0};
static struct Sciclient_rmIaUsedMapping rom_usage_MCU_NAVSS0_UDMASS_INTA_0[1U] = {
    {
        .event = 16414U,
        .cleared = (bool)false,
    },
};

struct Sciclient_rmIaInst gRmIaInstances[SCICLIENT_RM_IA_NUM_INST] =
{
    {
        .dev_id             = TISCI_DEV_NAVSS0_MODSS_INTA_0,
        .imap               = 0x30900000,
        .sevt_offset        = 20480u,
        .n_sevt             = 1024u,
        .n_vint             = 64,
        .vint_usage_count   = &vint_usage_count_NAVSS0_MODSS_INTA_0[0],
        .v0_b0_evt          = SCICLIENT_RM_IA_GENERIC_EVT_RESETVAL,
        .rom_usage          = NULL,
        .n_rom_usage        = 0U,
    },
    {
        .dev_id             = TISCI_DEV_NAVSS0_MODSS_INTA_1,
        .imap               = 0x30908000,
        .sevt_offset        = 22528u,
        .n_sevt             = 1024u,
        .n_vint             = 64,
        .vint_usage_count   = &vint_usage_count_NAVSS0_MODSS_INTA_1[0],
        .v0_b0_evt          = SCICLIENT_RM_IA_GENERIC_EVT_RESETVAL,
        .rom_usage          = NULL,
        .n_rom_usage        = 0U,
    },
    {
        .dev_id             = TISCI_DEV_NAVSS0_UDMASS_INTA_0,
        .imap               = 0x30940000,
        .sevt_offset        = 0u,
        .n_sevt             = 4608u,
        .n_vint             = 256,
        .vint_usage_count   = &vint_usage_count_NAVSS0_UDMASS_INTA_0[0],
        .v0_b0_evt          = SCICLIENT_RM_IA_GENERIC_EVT_RESETVAL,
        .rom_usage          = NULL,
        .n_rom_usage        = 0U,
    },
    {
        .dev_id             = TISCI_DEV_MCU_NAVSS0_UDMASS_INTA_0,
        .imap               = 0x28560000,
        .sevt_offset        = 16384u,
        .n_sevt             = 1536u,
        .n_vint             = 256,
        .vint_usage_count   = &vint_usage_count_MCU_NAVSS0_UDMASS_INTA_0[0],
        .v0_b0_evt          = SCICLIENT_RM_IA_GENERIC_EVT_RESETVAL,
        .rom_usage          = &rom_usage_MCU_NAVSS0_UDMASS_INTA_0[0U],
        .n_rom_usage        = 1U,
    }
};

static struct Sciclient_rmIrUsedMapping rom_usage_MAIN2MCU_LVL_INTRTR0[3U] = {
    {
        .inp_start = 28U,
        .outp_start = 32U,
        .length = 2U,
        .cleared = (bool)false,
        .opCleared = (bool)false,
    },
    {
        .inp_start = 128U,
        .outp_start = 34U,
        .length = 8U,
        .cleared = (bool)false,
        .opCleared = (bool)false,
    },
    {
        .inp_start = 218U,
        .outp_start = 50U,
        .length = 1U,
        .cleared = (bool)false,
        .opCleared = (bool)false,
    },
};

struct Sciclient_rmIrInst gRmIrInstances[SCICLIENT_RM_IR_NUM_INST] =
{
    {
        .dev_id         = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
        .cfg            = 0xa10000,
        .n_inp          = 320u,
        .n_outp         = 64u,
        .inp0_mapping   = SCICLIENT_RM_IR_MAPPING_FREE,
        .rom_usage      = &rom_usage_MAIN2MCU_LVL_INTRTR0[0U],
        .n_rom_usage    = 3U,
    },
    {
        .dev_id         = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
        .cfg            = 0xa20000,
        .n_inp          = 112u,
        .n_outp         = 48u,
        .inp0_mapping   = SCICLIENT_RM_IR_MAPPING_FREE,
        .rom_usage      = NULL,
        .n_rom_usage    = 0U,
    },
    {
        .dev_id         = TISCI_DEV_TIMESYNC_INTRTR0,
        .cfg            = 0xa40000,
        .n_inp          = 56u,
        .n_outp         = 48u,
        .inp0_mapping   = SCICLIENT_RM_IR_MAPPING_FREE,
        .rom_usage      = NULL,
        .n_rom_usage    = 0U,
    },
    {
        .dev_id         = TISCI_DEV_WKUP_GPIOMUX_INTRTR0,
        .cfg            = 0x42200000,
        .n_inp          = 120u,
        .n_outp         = 32u,
        .inp0_mapping   = SCICLIENT_RM_IR_MAPPING_FREE,
        .rom_usage      = NULL,
        .n_rom_usage    = 0U,
    },
    {
        .dev_id         = TISCI_DEV_GPIOMUX_INTRTR0,
        .cfg            = 0xa00000,
        .n_inp          = 180u,
        .n_outp         = 64u,
        .inp0_mapping   = SCICLIENT_RM_IR_MAPPING_FREE,
        .rom_usage      = NULL,
        .n_rom_usage    = 0U,
    },
    {
        .dev_id         = TISCI_DEV_CMPEVENT_INTRTR0,
        .cfg            = 0xa30000,
        .n_inp          = 16u,
        .n_outp         = 16u,
        .inp0_mapping   = SCICLIENT_RM_IR_MAPPING_FREE,
        .rom_usage      = NULL,
        .n_rom_usage    = 0U,
    },
    {
        .dev_id         = TISCI_DEV_NAVSS0_INTR_0,
        .cfg            = 0x310e0000,
        .n_inp          = 490u,
        .n_outp         = 512u,
        .inp0_mapping   = SCICLIENT_RM_IR_MAPPING_FREE,
        .rom_usage      = NULL,
        .n_rom_usage    = 0U,
    },
    {
        .dev_id         = TISCI_DEV_MCU_NAVSS0_INTR_ROUTER_0,
        .cfg            = 0x28540000,
        .n_inp          = 261u,
        .n_outp         = 64u,
        .inp0_mapping   = SCICLIENT_RM_IR_MAPPING_FREE,
        .rom_usage      = NULL,
        .n_rom_usage    = 0U,
    },
};

#endif

/* IRQ Tree definition */

#if defined (SOC_J784S4)
const struct Sciclient_rmIrqIf GPIOMUX_INTRTR0_outp_0_7_to_ESM0_esm_pls_event0_664_671 = {
	.lbase = 0,
	.len = 8,
	.rid = TISCI_DEV_ESM0,
	.rbase = 664,
};
const struct Sciclient_rmIrqIf GPIOMUX_INTRTR0_outp_0_7_to_ESM0_esm_pls_event1_672_679 = {
	.lbase = 0,
	.len = 8,
	.rid = TISCI_DEV_ESM0,
	.rbase = 672,
};
const struct Sciclient_rmIrqIf GPIOMUX_INTRTR0_outp_0_7_to_ESM0_esm_pls_event2_680_687 = {
	.lbase = 0,
	.len = 8,
	.rid = TISCI_DEV_ESM0,
	.rbase = 680,
};
const struct Sciclient_rmIrqIf GPIOMUX_INTRTR0_outp_0_31_to_MAIN2MCU_PLS_INTRTR0_in_64_95 = {
	.lbase = 0,
	.len = 32,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 64,
};
const struct Sciclient_rmIrqIf GPIOMUX_INTRTR0_outp_16_31_to_R5FSS0_CORE0_intr_176_191 = {
	.lbase = 16,
	.len = 16,
	.rid = TISCI_DEV_R5FSS0_CORE0,
	.rbase = 176,
};
const struct Sciclient_rmIrqIf GPIOMUX_INTRTR0_outp_0_15_to_R5FSS0_CORE0_intr_396_411 = {
	.lbase = 0,
	.len = 16,
	.rid = TISCI_DEV_R5FSS0_CORE0,
	.rbase = 396,
};
const struct Sciclient_rmIrqIf GPIOMUX_INTRTR0_outp_16_31_to_R5FSS0_CORE1_intr_176_191 = {
	.lbase = 16,
	.len = 16,
	.rid = TISCI_DEV_R5FSS0_CORE1,
	.rbase = 176,
};
const struct Sciclient_rmIrqIf GPIOMUX_INTRTR0_outp_0_15_to_R5FSS0_CORE1_intr_396_411 = {
	.lbase = 0,
	.len = 16,
	.rid = TISCI_DEV_R5FSS0_CORE1,
	.rbase = 396,
};
const struct Sciclient_rmIrqIf GPIOMUX_INTRTR0_outp_16_31_to_R5FSS1_CORE0_intr_176_191 = {
	.lbase = 16,
	.len = 16,
	.rid = TISCI_DEV_R5FSS1_CORE0,
	.rbase = 176,
};
const struct Sciclient_rmIrqIf GPIOMUX_INTRTR0_outp_0_15_to_R5FSS1_CORE0_intr_396_411 = {
	.lbase = 0,
	.len = 16,
	.rid = TISCI_DEV_R5FSS1_CORE0,
	.rbase = 396,
};
const struct Sciclient_rmIrqIf GPIOMUX_INTRTR0_outp_16_31_to_R5FSS1_CORE1_intr_176_191 = {
	.lbase = 16,
	.len = 16,
	.rid = TISCI_DEV_R5FSS1_CORE1,
	.rbase = 176,
};
const struct Sciclient_rmIrqIf GPIOMUX_INTRTR0_outp_0_15_to_R5FSS1_CORE1_intr_396_411 = {
	.lbase = 0,
	.len = 16,
	.rid = TISCI_DEV_R5FSS1_CORE1,
	.rbase = 396,
};
const struct Sciclient_rmIrqIf GPIOMUX_INTRTR0_outp_16_31_to_R5FSS2_CORE0_intr_176_191 = {
	.lbase = 16,
	.len = 16,
	.rid = TISCI_DEV_R5FSS2_CORE0,
	.rbase = 176,
};
const struct Sciclient_rmIrqIf GPIOMUX_INTRTR0_outp_0_15_to_R5FSS2_CORE0_intr_396_411 = {
	.lbase = 0,
	.len = 16,
	.rid = TISCI_DEV_R5FSS2_CORE0,
	.rbase = 396,
};
const struct Sciclient_rmIrqIf GPIOMUX_INTRTR0_outp_16_31_to_R5FSS2_CORE1_intr_176_191 = {
	.lbase = 16,
	.len = 16,
	.rid = TISCI_DEV_R5FSS2_CORE1,
	.rbase = 176,
};
const struct Sciclient_rmIrqIf GPIOMUX_INTRTR0_outp_0_15_to_R5FSS2_CORE1_intr_396_411 = {
	.lbase = 0,
	.len = 16,
	.rid = TISCI_DEV_R5FSS2_CORE1,
	.rbase = 396,
};
const struct Sciclient_rmIrqIf GPIOMUX_INTRTR0_outp_8_63_to_COMPUTE_CLUSTER0_CLEC_soc_events_in_392_447 = {
	.lbase = 8,
	.len = 56,
	.rid = TISCI_DEV_COMPUTE_CLUSTER0_CLEC,
	.rbase = 392,
};
const struct Sciclient_rmIrqIf GPIOMUX_INTRTR0_outp_8_63_to_COMPUTE_CLUSTER0_GIC500SS_spi_392_447 = {
	.lbase = 8,
	.len = 56,
	.rid = TISCI_DEV_COMPUTE_CLUSTER0_GIC500SS,
	.rbase = 392,
};
const struct Sciclient_rmIrqIf GPIOMUX_INTRTR0_outp_16_31_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_116_131 = {
	.lbase = 16,
	.len = 16,
	.rid = TISCI_DEV_NAVSS0_UDMASS_INTA_0,
	.rbase = 116,
};
const struct Sciclient_rmIrqIf * const tisci_if_GPIOMUX_INTRTR0[] = {
	&GPIOMUX_INTRTR0_outp_0_7_to_ESM0_esm_pls_event0_664_671,
	&GPIOMUX_INTRTR0_outp_0_7_to_ESM0_esm_pls_event1_672_679,
	&GPIOMUX_INTRTR0_outp_0_7_to_ESM0_esm_pls_event2_680_687,
	&GPIOMUX_INTRTR0_outp_0_31_to_MAIN2MCU_PLS_INTRTR0_in_64_95,
	&GPIOMUX_INTRTR0_outp_16_31_to_R5FSS0_CORE0_intr_176_191,
	&GPIOMUX_INTRTR0_outp_0_15_to_R5FSS0_CORE0_intr_396_411,
	&GPIOMUX_INTRTR0_outp_16_31_to_R5FSS0_CORE1_intr_176_191,
	&GPIOMUX_INTRTR0_outp_0_15_to_R5FSS0_CORE1_intr_396_411,
	&GPIOMUX_INTRTR0_outp_16_31_to_R5FSS1_CORE0_intr_176_191,
	&GPIOMUX_INTRTR0_outp_0_15_to_R5FSS1_CORE0_intr_396_411,
	&GPIOMUX_INTRTR0_outp_16_31_to_R5FSS1_CORE1_intr_176_191,
	&GPIOMUX_INTRTR0_outp_0_15_to_R5FSS1_CORE1_intr_396_411,
	&GPIOMUX_INTRTR0_outp_16_31_to_R5FSS2_CORE0_intr_176_191,
	&GPIOMUX_INTRTR0_outp_0_15_to_R5FSS2_CORE0_intr_396_411,
	&GPIOMUX_INTRTR0_outp_16_31_to_R5FSS2_CORE1_intr_176_191,
	&GPIOMUX_INTRTR0_outp_0_15_to_R5FSS2_CORE1_intr_396_411,
	&GPIOMUX_INTRTR0_outp_8_63_to_COMPUTE_CLUSTER0_CLEC_soc_events_in_392_447,
	&GPIOMUX_INTRTR0_outp_8_63_to_COMPUTE_CLUSTER0_GIC500SS_spi_392_447,
	&GPIOMUX_INTRTR0_outp_16_31_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_116_131,
};
static const struct Sciclient_rmIrqNode tisci_irq_GPIOMUX_INTRTR0 = {
	.id = TISCI_DEV_GPIOMUX_INTRTR0,
	.n_if = 19,
	.p_if = &tisci_if_GPIOMUX_INTRTR0[0],
};

/* Start of CMPEVENT_INTRTR0 interface definition */
const struct Sciclient_rmIrqIf CMPEVENT_INTRTR0_outp_0_3_to_COMPUTE_CLUSTER0_CLEC_soc_events_in_544_547 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_COMPUTE_CLUSTER0_CLEC,
	.rbase = 544,
};
const struct Sciclient_rmIrqIf CMPEVENT_INTRTR0_outp_0_3_to_COMPUTE_CLUSTER0_GIC500SS_spi_544_547 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_COMPUTE_CLUSTER0_GIC500SS,
	.rbase = 544,
};
const struct Sciclient_rmIrqIf CMPEVENT_INTRTR0_outp_4_7_to_MAIN2MCU_PLS_INTRTR0_in_96_99 = {
	.lbase = 4,
	.len = 4,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 96,
};
const struct Sciclient_rmIrqIf CMPEVENT_INTRTR0_outp_8_11_to_R5FSS0_CORE0_intr_326_329 = {
	.lbase = 8,
	.len = 4,
	.rid = TISCI_DEV_R5FSS0_CORE0,
	.rbase = 326,
};
const struct Sciclient_rmIrqIf CMPEVENT_INTRTR0_outp_8_11_to_R5FSS0_CORE1_intr_326_329 = {
	.lbase = 8,
	.len = 4,
	.rid = TISCI_DEV_R5FSS0_CORE1,
	.rbase = 326,
};
const struct Sciclient_rmIrqIf CMPEVENT_INTRTR0_outp_8_11_to_R5FSS1_CORE0_intr_326_329 = {
	.lbase = 8,
	.len = 4,
	.rid = TISCI_DEV_R5FSS1_CORE0,
	.rbase = 326,
};
const struct Sciclient_rmIrqIf CMPEVENT_INTRTR0_outp_8_11_to_R5FSS1_CORE1_intr_326_329 = {
	.lbase = 8,
	.len = 4,
	.rid = TISCI_DEV_R5FSS1_CORE1,
	.rbase = 326,
};
const struct Sciclient_rmIrqIf CMPEVENT_INTRTR0_outp_8_11_to_R5FSS2_CORE0_intr_326_329 = {
	.lbase = 8,
	.len = 4,
	.rid = TISCI_DEV_R5FSS2_CORE0,
	.rbase = 326,
};
const struct Sciclient_rmIrqIf CMPEVENT_INTRTR0_outp_8_11_to_R5FSS2_CORE1_intr_326_329 = {
	.lbase = 8,
	.len = 4,
	.rid = TISCI_DEV_R5FSS2_CORE1,
	.rbase = 326,
};
const struct Sciclient_rmIrqIf CMPEVENT_INTRTR0_outp_12_15_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_108_111 = {
	.lbase = 12,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_UDMASS_INTA_0,
	.rbase = 108,
};
const struct Sciclient_rmIrqIf * const tisci_if_CMPEVENT_INTRTR0[] = {
	&CMPEVENT_INTRTR0_outp_0_3_to_COMPUTE_CLUSTER0_CLEC_soc_events_in_544_547,
	&CMPEVENT_INTRTR0_outp_0_3_to_COMPUTE_CLUSTER0_GIC500SS_spi_544_547,
	&CMPEVENT_INTRTR0_outp_4_7_to_MAIN2MCU_PLS_INTRTR0_in_96_99,
	&CMPEVENT_INTRTR0_outp_8_11_to_R5FSS0_CORE0_intr_326_329,
	&CMPEVENT_INTRTR0_outp_8_11_to_R5FSS0_CORE1_intr_326_329,
	&CMPEVENT_INTRTR0_outp_8_11_to_R5FSS1_CORE0_intr_326_329,
	&CMPEVENT_INTRTR0_outp_8_11_to_R5FSS1_CORE1_intr_326_329,
	&CMPEVENT_INTRTR0_outp_8_11_to_R5FSS2_CORE0_intr_326_329,
	&CMPEVENT_INTRTR0_outp_8_11_to_R5FSS2_CORE1_intr_326_329,
	&CMPEVENT_INTRTR0_outp_12_15_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_108_111,
};
static const struct Sciclient_rmIrqNode tisci_irq_CMPEVENT_INTRTR0 = {
	.id = TISCI_DEV_CMPEVENT_INTRTR0,
	.n_if = 10,
	.p_if = &tisci_if_CMPEVENT_INTRTR0[0],
};

/* Start of GTC0 interface definition */
const struct Sciclient_rmIrqIf GTC0_gtc_push_event_0_0_to_TIMESYNC_INTRTR0_in_1_1 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 1,
};
const struct Sciclient_rmIrqIf * const tisci_if_GTC0[] = {
	&GTC0_gtc_push_event_0_0_to_TIMESYNC_INTRTR0_in_1_1,
};
static const struct Sciclient_rmIrqNode tisci_irq_GTC0 = {
	.id = TISCI_DEV_GTC0,
	.n_if = 1,
	.p_if = &tisci_if_GTC0[0],
};

/* Start of CPSW1 interface definition */
const struct Sciclient_rmIrqIf CPSW1_cpts_comp_0_0_to_CMPEVENT_INTRTR0_in_11_11 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_CMPEVENT_INTRTR0,
	.rbase = 11,
};
const struct Sciclient_rmIrqIf CPSW1_cpts_genf0_1_1_to_TIMESYNC_INTRTR0_in_18_18 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 18,
};
const struct Sciclient_rmIrqIf CPSW1_cpts_genf1_2_2_to_TIMESYNC_INTRTR0_in_19_19 = {
	.lbase = 2,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 19,
};
const struct Sciclient_rmIrqIf CPSW1_cpts_sync_3_3_to_TIMESYNC_INTRTR0_in_39_39 = {
	.lbase = 3,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 39,
};
const struct Sciclient_rmIrqIf CPSW1_stat_pend_6_6_to_MAIN2MCU_LVL_INTRTR0_in_70_70 = {
	.lbase = 6,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 70,
};
const struct Sciclient_rmIrqIf CPSW1_mdio_pend_5_5_to_MAIN2MCU_LVL_INTRTR0_in_71_71 = {
	.lbase = 5,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 71,
};
const struct Sciclient_rmIrqIf CPSW1_evnt_pend_4_4_to_MAIN2MCU_LVL_INTRTR0_in_72_72 = {
	.lbase = 4,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 72,
};
const struct Sciclient_rmIrqIf * const tisci_if_CPSW1[] = {
	&CPSW1_cpts_comp_0_0_to_CMPEVENT_INTRTR0_in_11_11,
	&CPSW1_cpts_genf0_1_1_to_TIMESYNC_INTRTR0_in_18_18,
	&CPSW1_cpts_genf1_2_2_to_TIMESYNC_INTRTR0_in_19_19,
	&CPSW1_cpts_sync_3_3_to_TIMESYNC_INTRTR0_in_39_39,
	&CPSW1_stat_pend_6_6_to_MAIN2MCU_LVL_INTRTR0_in_70_70,
	&CPSW1_mdio_pend_5_5_to_MAIN2MCU_LVL_INTRTR0_in_71_71,
	&CPSW1_evnt_pend_4_4_to_MAIN2MCU_LVL_INTRTR0_in_72_72,
};
static const struct Sciclient_rmIrqNode tisci_irq_CPSW1 = {
	.id = TISCI_DEV_CPSW1,
	.n_if = 7,
	.p_if = &tisci_if_CPSW1[0],
};

/* Start of MCU_CPSW0 interface definition */
const struct Sciclient_rmIrqIf MCU_CPSW0_cpts_comp_0_0_to_CMPEVENT_INTRTR0_in_10_10 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_CMPEVENT_INTRTR0,
	.rbase = 10,
};
const struct Sciclient_rmIrqIf MCU_CPSW0_cpts_genf0_1_1_to_TIMESYNC_INTRTR0_in_16_16 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 16,
};
const struct Sciclient_rmIrqIf MCU_CPSW0_cpts_genf1_2_2_to_TIMESYNC_INTRTR0_in_17_17 = {
	.lbase = 2,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 17,
};
const struct Sciclient_rmIrqIf MCU_CPSW0_cpts_sync_3_3_to_TIMESYNC_INTRTR0_in_38_38 = {
	.lbase = 3,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 38,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCU_CPSW0[] = {
	&MCU_CPSW0_cpts_comp_0_0_to_CMPEVENT_INTRTR0_in_10_10,
	&MCU_CPSW0_cpts_genf0_1_1_to_TIMESYNC_INTRTR0_in_16_16,
	&MCU_CPSW0_cpts_genf1_2_2_to_TIMESYNC_INTRTR0_in_17_17,
	&MCU_CPSW0_cpts_sync_3_3_to_TIMESYNC_INTRTR0_in_38_38,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCU_CPSW0 = {
	.id = TISCI_DEV_MCU_CPSW0,
	.n_if = 4,
	.p_if = &tisci_if_MCU_CPSW0[0],
};

/* Start of cpsw_9xuss_j7am0 interface definition */
const struct Sciclient_rmIrqIf cpsw_9xuss_j7am0_cpts_comp_0_0_to_CMPEVENT_INTRTR0_in_9_9 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_CMPEVENT_INTRTR0,
	.rbase = 9,
};
const struct Sciclient_rmIrqIf cpsw_9xuss_j7am0_cpts_genf0_1_1_to_TIMESYNC_INTRTR0_in_14_14 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 14,
};
const struct Sciclient_rmIrqIf cpsw_9xuss_j7am0_cpts_genf1_2_2_to_TIMESYNC_INTRTR0_in_15_15 = {
	.lbase = 2,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 15,
};
const struct Sciclient_rmIrqIf cpsw_9xuss_j7am0_cpts_sync_3_3_to_TIMESYNC_INTRTR0_in_37_37 = {
	.lbase = 3,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 37,
};
const struct Sciclient_rmIrqIf cpsw_9xuss_j7am0_stat_pend_6_6_to_MAIN2MCU_LVL_INTRTR0_in_221_221 = {
	.lbase = 6,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 221,
};
const struct Sciclient_rmIrqIf cpsw_9xuss_j7am0_mdio_pend_5_5_to_MAIN2MCU_LVL_INTRTR0_in_222_222 = {
	.lbase = 5,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 222,
};
const struct Sciclient_rmIrqIf cpsw_9xuss_j7am0_evnt_pend_4_4_to_MAIN2MCU_LVL_INTRTR0_in_223_223 = {
	.lbase = 4,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 223,
};
const struct Sciclient_rmIrqIf * const tisci_if_cpsw_9xuss_j7am0[] = {
	&cpsw_9xuss_j7am0_cpts_comp_0_0_to_CMPEVENT_INTRTR0_in_9_9,
	&cpsw_9xuss_j7am0_cpts_genf0_1_1_to_TIMESYNC_INTRTR0_in_14_14,
	&cpsw_9xuss_j7am0_cpts_genf1_2_2_to_TIMESYNC_INTRTR0_in_15_15,
	&cpsw_9xuss_j7am0_cpts_sync_3_3_to_TIMESYNC_INTRTR0_in_37_37,
	&cpsw_9xuss_j7am0_stat_pend_6_6_to_MAIN2MCU_LVL_INTRTR0_in_221_221,
	&cpsw_9xuss_j7am0_mdio_pend_5_5_to_MAIN2MCU_LVL_INTRTR0_in_222_222,
	&cpsw_9xuss_j7am0_evnt_pend_4_4_to_MAIN2MCU_LVL_INTRTR0_in_223_223,
};
static const struct Sciclient_rmIrqNode tisci_irq_cpsw_9xuss_j7am0 = {
	.id = TISCI_DEV_CPSW_9XUSS_J7AM0,
	.n_if = 7,
	.p_if = &tisci_if_cpsw_9xuss_j7am0[0],
};

/* Start of csi_rx_if0 interface definition */
const struct Sciclient_rmIrqIf csi_rx_if0_csi_irq_1_1_to_MAIN2MCU_LVL_INTRTR0_in_254_254 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 254,
};
const struct Sciclient_rmIrqIf csi_rx_if0_csi_err_irq_0_0_to_MAIN2MCU_LVL_INTRTR0_in_255_255 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 255,
};
const struct Sciclient_rmIrqIf csi_rx_if0_csi_level_2_2_to_MAIN2MCU_LVL_INTRTR0_in_256_256 = {
	.lbase = 2,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 256,
};
const struct Sciclient_rmIrqIf * const tisci_if_csi_rx_if0[] = {
	&csi_rx_if0_csi_irq_1_1_to_MAIN2MCU_LVL_INTRTR0_in_254_254,
	&csi_rx_if0_csi_err_irq_0_0_to_MAIN2MCU_LVL_INTRTR0_in_255_255,
	&csi_rx_if0_csi_level_2_2_to_MAIN2MCU_LVL_INTRTR0_in_256_256,
};
static const struct Sciclient_rmIrqNode tisci_irq_csi_rx_if0 = {
	.id = TISCI_DEV_CSI_RX_IF0,
	.n_if = 3,
	.p_if = &tisci_if_csi_rx_if0[0],
};

/* Start of csi_rx_if1 interface definition */
const struct Sciclient_rmIrqIf csi_rx_if1_csi_irq_1_1_to_MAIN2MCU_LVL_INTRTR0_in_257_257 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 257,
};
const struct Sciclient_rmIrqIf csi_rx_if1_csi_err_irq_0_0_to_MAIN2MCU_LVL_INTRTR0_in_258_258 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 258,
};
const struct Sciclient_rmIrqIf csi_rx_if1_csi_level_2_2_to_MAIN2MCU_LVL_INTRTR0_in_259_259 = {
	.lbase = 2,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 259,
};
const struct Sciclient_rmIrqIf * const tisci_if_csi_rx_if1[] = {
	&csi_rx_if1_csi_irq_1_1_to_MAIN2MCU_LVL_INTRTR0_in_257_257,
	&csi_rx_if1_csi_err_irq_0_0_to_MAIN2MCU_LVL_INTRTR0_in_258_258,
	&csi_rx_if1_csi_level_2_2_to_MAIN2MCU_LVL_INTRTR0_in_259_259,
};
static const struct Sciclient_rmIrqNode tisci_irq_csi_rx_if1 = {
	.id = TISCI_DEV_CSI_RX_IF1,
	.n_if = 3,
	.p_if = &tisci_if_csi_rx_if1[0],
};

/* Start of csi_rx_if2 interface definition */
const struct Sciclient_rmIrqIf csi_rx_if2_csi_irq_1_1_to_MAIN2MCU_LVL_INTRTR0_in_260_260 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 260,
};
const struct Sciclient_rmIrqIf csi_rx_if2_csi_err_irq_0_0_to_MAIN2MCU_LVL_INTRTR0_in_261_261 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 261,
};
const struct Sciclient_rmIrqIf csi_rx_if2_csi_level_2_2_to_MAIN2MCU_LVL_INTRTR0_in_262_262 = {
	.lbase = 2,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 262,
};
const struct Sciclient_rmIrqIf * const tisci_if_csi_rx_if2[] = {
	&csi_rx_if2_csi_irq_1_1_to_MAIN2MCU_LVL_INTRTR0_in_260_260,
	&csi_rx_if2_csi_err_irq_0_0_to_MAIN2MCU_LVL_INTRTR0_in_261_261,
	&csi_rx_if2_csi_level_2_2_to_MAIN2MCU_LVL_INTRTR0_in_262_262,
};
static const struct Sciclient_rmIrqNode tisci_irq_csi_rx_if2 = {
	.id = TISCI_DEV_CSI_RX_IF2,
	.n_if = 3,
	.p_if = &tisci_if_csi_rx_if2[0],
};

/* Start of CSI_TX_IF0 interface definition */
const struct Sciclient_rmIrqIf CSI_TX_IF0_csi_interrupt_0_0_to_MAIN2MCU_LVL_INTRTR0_in_250_250 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 250,
};
const struct Sciclient_rmIrqIf CSI_TX_IF0_csi_level_1_1_to_MAIN2MCU_LVL_INTRTR0_in_251_251 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 251,
};
const struct Sciclient_rmIrqIf * const tisci_if_CSI_TX_IF0[] = {
	&CSI_TX_IF0_csi_interrupt_0_0_to_MAIN2MCU_LVL_INTRTR0_in_250_250,
	&CSI_TX_IF0_csi_level_1_1_to_MAIN2MCU_LVL_INTRTR0_in_251_251,
};
static const struct Sciclient_rmIrqNode tisci_irq_CSI_TX_IF0 = {
	.id = TISCI_DEV_CSI_TX_IF0,
	.n_if = 2,
	.p_if = &tisci_if_CSI_TX_IF0[0],
};

/* Start of CSI_TX_IF1 interface definition */
const struct Sciclient_rmIrqIf CSI_TX_IF1_csi_interrupt_0_0_to_MAIN2MCU_LVL_INTRTR0_in_248_248 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 248,
};
const struct Sciclient_rmIrqIf CSI_TX_IF1_csi_level_1_1_to_MAIN2MCU_LVL_INTRTR0_in_249_249 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 249,
};
const struct Sciclient_rmIrqIf * const tisci_if_CSI_TX_IF1[] = {
	&CSI_TX_IF1_csi_interrupt_0_0_to_MAIN2MCU_LVL_INTRTR0_in_248_248,
	&CSI_TX_IF1_csi_level_1_1_to_MAIN2MCU_LVL_INTRTR0_in_249_249,
};
static const struct Sciclient_rmIrqNode tisci_irq_CSI_TX_IF1 = {
	.id = TISCI_DEV_CSI_TX_IF1,
	.n_if = 2,
	.p_if = &tisci_if_CSI_TX_IF1[0],
};

/* Start of DCC0 interface definition */
const struct Sciclient_rmIrqIf DCC0_intr_done_level_0_0_to_MAIN2MCU_LVL_INTRTR0_in_88_88 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 88,
};
const struct Sciclient_rmIrqIf * const tisci_if_DCC0[] = {
	&DCC0_intr_done_level_0_0_to_MAIN2MCU_LVL_INTRTR0_in_88_88,
};
static const struct Sciclient_rmIrqNode tisci_irq_DCC0 = {
	.id = TISCI_DEV_DCC0,
	.n_if = 1,
	.p_if = &tisci_if_DCC0[0],
};

/* Start of DCC1 interface definition */
const struct Sciclient_rmIrqIf DCC1_intr_done_level_0_0_to_MAIN2MCU_LVL_INTRTR0_in_89_89 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 89,
};
const struct Sciclient_rmIrqIf * const tisci_if_DCC1[] = {
	&DCC1_intr_done_level_0_0_to_MAIN2MCU_LVL_INTRTR0_in_89_89,
};
static const struct Sciclient_rmIrqNode tisci_irq_DCC1 = {
	.id = TISCI_DEV_DCC1,
	.n_if = 1,
	.p_if = &tisci_if_DCC1[0],
};

/* Start of DCC2 interface definition */
const struct Sciclient_rmIrqIf DCC2_intr_done_level_0_0_to_MAIN2MCU_LVL_INTRTR0_in_90_90 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 90,
};
const struct Sciclient_rmIrqIf * const tisci_if_DCC2[] = {
	&DCC2_intr_done_level_0_0_to_MAIN2MCU_LVL_INTRTR0_in_90_90,
};
static const struct Sciclient_rmIrqNode tisci_irq_DCC2 = {
	.id = TISCI_DEV_DCC2,
	.n_if = 1,
	.p_if = &tisci_if_DCC2[0],
};

/* Start of DCC3 interface definition */
const struct Sciclient_rmIrqIf DCC3_intr_done_level_0_0_to_MAIN2MCU_LVL_INTRTR0_in_91_91 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 91,
};
const struct Sciclient_rmIrqIf * const tisci_if_DCC3[] = {
	&DCC3_intr_done_level_0_0_to_MAIN2MCU_LVL_INTRTR0_in_91_91,
};
static const struct Sciclient_rmIrqNode tisci_irq_DCC3 = {
	.id = TISCI_DEV_DCC3,
	.n_if = 1,
	.p_if = &tisci_if_DCC3[0],
};

/* Start of DCC4 interface definition */
const struct Sciclient_rmIrqIf DCC4_intr_done_level_0_0_to_MAIN2MCU_LVL_INTRTR0_in_92_92 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 92,
};
const struct Sciclient_rmIrqIf * const tisci_if_DCC4[] = {
	&DCC4_intr_done_level_0_0_to_MAIN2MCU_LVL_INTRTR0_in_92_92,
};
static const struct Sciclient_rmIrqNode tisci_irq_DCC4 = {
	.id = TISCI_DEV_DCC4,
	.n_if = 1,
	.p_if = &tisci_if_DCC4[0],
};

/* Start of DCC5 interface definition */
const struct Sciclient_rmIrqIf DCC5_intr_done_level_0_0_to_MAIN2MCU_LVL_INTRTR0_in_93_93 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 93,
};
const struct Sciclient_rmIrqIf * const tisci_if_DCC5[] = {
	&DCC5_intr_done_level_0_0_to_MAIN2MCU_LVL_INTRTR0_in_93_93,
};
static const struct Sciclient_rmIrqNode tisci_irq_DCC5 = {
	.id = TISCI_DEV_DCC5,
	.n_if = 1,
	.p_if = &tisci_if_DCC5[0],
};

/* Start of DCC6 interface definition */
const struct Sciclient_rmIrqIf DCC6_intr_done_level_0_0_to_MAIN2MCU_LVL_INTRTR0_in_94_94 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 94,
};
const struct Sciclient_rmIrqIf * const tisci_if_DCC6[] = {
	&DCC6_intr_done_level_0_0_to_MAIN2MCU_LVL_INTRTR0_in_94_94,
};
static const struct Sciclient_rmIrqNode tisci_irq_DCC6 = {
	.id = TISCI_DEV_DCC6,
	.n_if = 1,
	.p_if = &tisci_if_DCC6[0],
};

/* Start of DCC7 interface definition */
const struct Sciclient_rmIrqIf DCC7_intr_done_level_0_0_to_MAIN2MCU_LVL_INTRTR0_in_95_95 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 95,
};
const struct Sciclient_rmIrqIf * const tisci_if_DCC7[] = {
	&DCC7_intr_done_level_0_0_to_MAIN2MCU_LVL_INTRTR0_in_95_95,
};
static const struct Sciclient_rmIrqNode tisci_irq_DCC7 = {
	.id = TISCI_DEV_DCC7,
	.n_if = 1,
	.p_if = &tisci_if_DCC7[0],
};

/* Start of DCC8 interface definition */
const struct Sciclient_rmIrqIf DCC8_intr_done_level_0_0_to_MAIN2MCU_LVL_INTRTR0_in_208_208 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 208,
};
const struct Sciclient_rmIrqIf * const tisci_if_DCC8[] = {
	&DCC8_intr_done_level_0_0_to_MAIN2MCU_LVL_INTRTR0_in_208_208,
};
static const struct Sciclient_rmIrqNode tisci_irq_DCC8 = {
	.id = TISCI_DEV_DCC8,
	.n_if = 1,
	.p_if = &tisci_if_DCC8[0],
};

/* Start of DCC9 interface definition */
const struct Sciclient_rmIrqIf DCC9_intr_done_level_0_0_to_MAIN2MCU_LVL_INTRTR0_in_209_209 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 209,
};
const struct Sciclient_rmIrqIf * const tisci_if_DCC9[] = {
	&DCC9_intr_done_level_0_0_to_MAIN2MCU_LVL_INTRTR0_in_209_209,
};
static const struct Sciclient_rmIrqNode tisci_irq_DCC9 = {
	.id = TISCI_DEV_DCC9,
	.n_if = 1,
	.p_if = &tisci_if_DCC9[0],
};

/* Start of DMPAC0_INTD_0 interface definition */
const struct Sciclient_rmIrqIf DMPAC0_INTD_0_system_intr_level_0_1_to_MAIN2MCU_LVL_INTRTR0_in_268_269 = {
	.lbase = 0,
	.len = 2,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 268,
};
const struct Sciclient_rmIrqIf * const tisci_if_DMPAC0_INTD_0[] = {
	&DMPAC0_INTD_0_system_intr_level_0_1_to_MAIN2MCU_LVL_INTRTR0_in_268_269,
};
static const struct Sciclient_rmIrqNode tisci_irq_DMPAC0_INTD_0 = {
	.id = TISCI_DEV_DMPAC0_INTD_0,
	.n_if = 1,
	.p_if = &tisci_if_DMPAC0_INTD_0[0],
};

/* Start of TIMER0 interface definition */
const struct Sciclient_rmIrqIf TIMER0_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_108_108 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 108,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER0[] = {
	&TIMER0_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_108_108,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER0 = {
	.id = TISCI_DEV_TIMER0,
	.n_if = 1,
	.p_if = &tisci_if_TIMER0[0],
};

/* Start of TIMER1 interface definition */
const struct Sciclient_rmIrqIf TIMER1_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_109_109 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 109,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER1[] = {
	&TIMER1_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_109_109,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER1 = {
	.id = TISCI_DEV_TIMER1,
	.n_if = 1,
	.p_if = &tisci_if_TIMER1[0],
};

/* Start of TIMER2 interface definition */
const struct Sciclient_rmIrqIf TIMER2_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_110_110 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 110,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER2[] = {
	&TIMER2_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_110_110,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER2 = {
	.id = TISCI_DEV_TIMER2,
	.n_if = 1,
	.p_if = &tisci_if_TIMER2[0],
};

/* Start of TIMER3 interface definition */
const struct Sciclient_rmIrqIf TIMER3_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_111_111 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 111,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER3[] = {
	&TIMER3_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_111_111,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER3 = {
	.id = TISCI_DEV_TIMER3,
	.n_if = 1,
	.p_if = &tisci_if_TIMER3[0],
};

/* Start of TIMER4 interface definition */
const struct Sciclient_rmIrqIf TIMER4_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_112_112 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 112,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER4[] = {
	&TIMER4_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_112_112,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER4 = {
	.id = TISCI_DEV_TIMER4,
	.n_if = 1,
	.p_if = &tisci_if_TIMER4[0],
};

/* Start of TIMER5 interface definition */
const struct Sciclient_rmIrqIf TIMER5_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_113_113 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 113,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER5[] = {
	&TIMER5_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_113_113,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER5 = {
	.id = TISCI_DEV_TIMER5,
	.n_if = 1,
	.p_if = &tisci_if_TIMER5[0],
};

/* Start of TIMER6 interface definition */
const struct Sciclient_rmIrqIf TIMER6_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_114_114 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 114,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER6[] = {
	&TIMER6_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_114_114,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER6 = {
	.id = TISCI_DEV_TIMER6,
	.n_if = 1,
	.p_if = &tisci_if_TIMER6[0],
};

/* Start of TIMER7 interface definition */
const struct Sciclient_rmIrqIf TIMER7_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_115_115 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 115,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER7[] = {
	&TIMER7_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_115_115,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER7 = {
	.id = TISCI_DEV_TIMER7,
	.n_if = 1,
	.p_if = &tisci_if_TIMER7[0],
};

/* Start of TIMER8 interface definition */
const struct Sciclient_rmIrqIf TIMER8_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_116_116 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 116,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER8[] = {
	&TIMER8_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_116_116,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER8 = {
	.id = TISCI_DEV_TIMER8,
	.n_if = 1,
	.p_if = &tisci_if_TIMER8[0],
};

/* Start of TIMER9 interface definition */
const struct Sciclient_rmIrqIf TIMER9_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_117_117 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 117,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER9[] = {
	&TIMER9_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_117_117,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER9 = {
	.id = TISCI_DEV_TIMER9,
	.n_if = 1,
	.p_if = &tisci_if_TIMER9[0],
};

/* Start of TIMER10 interface definition */
const struct Sciclient_rmIrqIf TIMER10_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_118_118 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 118,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER10[] = {
	&TIMER10_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_118_118,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER10 = {
	.id = TISCI_DEV_TIMER10,
	.n_if = 1,
	.p_if = &tisci_if_TIMER10[0],
};

/* Start of TIMER11 interface definition */
const struct Sciclient_rmIrqIf TIMER11_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_119_119 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 119,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER11[] = {
	&TIMER11_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_119_119,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER11 = {
	.id = TISCI_DEV_TIMER11,
	.n_if = 1,
	.p_if = &tisci_if_TIMER11[0],
};

/* Start of TIMER12 interface definition */
const struct Sciclient_rmIrqIf TIMER12_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_120_120 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 120,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER12[] = {
	&TIMER12_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_120_120,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER12 = {
	.id = TISCI_DEV_TIMER12,
	.n_if = 1,
	.p_if = &tisci_if_TIMER12[0],
};

/* Start of TIMER13 interface definition */
const struct Sciclient_rmIrqIf TIMER13_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_121_121 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 121,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER13[] = {
	&TIMER13_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_121_121,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER13 = {
	.id = TISCI_DEV_TIMER13,
	.n_if = 1,
	.p_if = &tisci_if_TIMER13[0],
};

/* Start of TIMER14 interface definition */
const struct Sciclient_rmIrqIf TIMER14_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_122_122 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 122,
};
const struct Sciclient_rmIrqIf TIMER14_timer_pwm_1_1_to_TIMESYNC_INTRTR0_in_2_2 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 2,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER14[] = {
	&TIMER14_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_122_122,
	&TIMER14_timer_pwm_1_1_to_TIMESYNC_INTRTR0_in_2_2,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER14 = {
	.id = TISCI_DEV_TIMER14,
	.n_if = 2,
	.p_if = &tisci_if_TIMER14[0],
};

/* Start of TIMER15 interface definition */
const struct Sciclient_rmIrqIf TIMER15_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_123_123 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 123,
};
const struct Sciclient_rmIrqIf TIMER15_timer_pwm_1_1_to_TIMESYNC_INTRTR0_in_3_3 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 3,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER15[] = {
	&TIMER15_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_123_123,
	&TIMER15_timer_pwm_1_1_to_TIMESYNC_INTRTR0_in_3_3,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER15 = {
	.id = TISCI_DEV_TIMER15,
	.n_if = 2,
	.p_if = &tisci_if_TIMER15[0],
};

/* Start of TIMER16 interface definition */
const struct Sciclient_rmIrqIf TIMER16_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_124_124 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 124,
};
const struct Sciclient_rmIrqIf TIMER16_timer_pwm_1_1_to_TIMESYNC_INTRTR0_in_40_40 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 40,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER16[] = {
	&TIMER16_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_124_124,
	&TIMER16_timer_pwm_1_1_to_TIMESYNC_INTRTR0_in_40_40,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER16 = {
	.id = TISCI_DEV_TIMER16,
	.n_if = 2,
	.p_if = &tisci_if_TIMER16[0],
};

/* Start of TIMER17 interface definition */
const struct Sciclient_rmIrqIf TIMER17_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_125_125 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 125,
};
const struct Sciclient_rmIrqIf TIMER17_timer_pwm_1_1_to_TIMESYNC_INTRTR0_in_41_41 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 41,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER17[] = {
	&TIMER17_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_125_125,
	&TIMER17_timer_pwm_1_1_to_TIMESYNC_INTRTR0_in_41_41,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER17 = {
	.id = TISCI_DEV_TIMER17,
	.n_if = 2,
	.p_if = &tisci_if_TIMER17[0],
};

/* Start of TIMER18 interface definition */
const struct Sciclient_rmIrqIf TIMER18_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_126_126 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 126,
};
const struct Sciclient_rmIrqIf TIMER18_timer_pwm_1_1_to_TIMESYNC_INTRTR0_in_42_42 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 42,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER18[] = {
	&TIMER18_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_126_126,
	&TIMER18_timer_pwm_1_1_to_TIMESYNC_INTRTR0_in_42_42,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER18 = {
	.id = TISCI_DEV_TIMER18,
	.n_if = 2,
	.p_if = &tisci_if_TIMER18[0],
};

/* Start of TIMER19 interface definition */
const struct Sciclient_rmIrqIf TIMER19_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_127_127 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 127,
};
const struct Sciclient_rmIrqIf TIMER19_timer_pwm_1_1_to_TIMESYNC_INTRTR0_in_43_43 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 43,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMER19[] = {
	&TIMER19_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_127_127,
	&TIMER19_timer_pwm_1_1_to_TIMESYNC_INTRTR0_in_43_43,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMER19 = {
	.id = TISCI_DEV_TIMER19,
	.n_if = 2,
	.p_if = &tisci_if_TIMER19[0],
};

/* Start of ECAP0 interface definition */
const struct Sciclient_rmIrqIf ECAP0_ecap_int_0_0_to_MAIN2MCU_PLS_INTRTR0_in_17_17 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 17,
};
const struct Sciclient_rmIrqIf * const tisci_if_ECAP0[] = {
	&ECAP0_ecap_int_0_0_to_MAIN2MCU_PLS_INTRTR0_in_17_17,
};
static const struct Sciclient_rmIrqNode tisci_irq_ECAP0 = {
	.id = TISCI_DEV_ECAP0,
	.n_if = 1,
	.p_if = &tisci_if_ECAP0[0],
};

/* Start of ECAP1 interface definition */
const struct Sciclient_rmIrqIf ECAP1_ecap_int_0_0_to_MAIN2MCU_PLS_INTRTR0_in_18_18 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 18,
};
const struct Sciclient_rmIrqIf * const tisci_if_ECAP1[] = {
	&ECAP1_ecap_int_0_0_to_MAIN2MCU_PLS_INTRTR0_in_18_18,
};
static const struct Sciclient_rmIrqNode tisci_irq_ECAP1 = {
	.id = TISCI_DEV_ECAP1,
	.n_if = 1,
	.p_if = &tisci_if_ECAP1[0],
};

/* Start of ECAP2 interface definition */
const struct Sciclient_rmIrqIf ECAP2_ecap_int_0_0_to_MAIN2MCU_PLS_INTRTR0_in_19_19 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 19,
};
const struct Sciclient_rmIrqIf * const tisci_if_ECAP2[] = {
	&ECAP2_ecap_int_0_0_to_MAIN2MCU_PLS_INTRTR0_in_19_19,
};
static const struct Sciclient_rmIrqNode tisci_irq_ECAP2 = {
	.id = TISCI_DEV_ECAP2,
	.n_if = 1,
	.p_if = &tisci_if_ECAP2[0],
};

/* Start of ELM0 interface definition */
const struct Sciclient_rmIrqIf ELM0_elm_porocpsinterrupt_lvl_0_0_to_MAIN2MCU_LVL_INTRTR0_in_7_7 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 7,
};
const struct Sciclient_rmIrqIf * const tisci_if_ELM0[] = {
	&ELM0_elm_porocpsinterrupt_lvl_0_0_to_MAIN2MCU_LVL_INTRTR0_in_7_7,
};
static const struct Sciclient_rmIrqNode tisci_irq_ELM0 = {
	.id = TISCI_DEV_ELM0,
	.n_if = 1,
	.p_if = &tisci_if_ELM0[0],
};

/* Start of MMCSD0 interface definition */
const struct Sciclient_rmIrqIf MMCSD0_emmcss_intr_0_0_to_MAIN2MCU_LVL_INTRTR0_in_28_28 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 28,
};
const struct Sciclient_rmIrqIf * const tisci_if_MMCSD0[] = {
	&MMCSD0_emmcss_intr_0_0_to_MAIN2MCU_LVL_INTRTR0_in_28_28,
};
static const struct Sciclient_rmIrqNode tisci_irq_MMCSD0 = {
	.id = TISCI_DEV_MMCSD0,
	.n_if = 1,
	.p_if = &tisci_if_MMCSD0[0],
};

/* Start of MMCSD1 interface definition */
const struct Sciclient_rmIrqIf MMCSD1_emmcsdss_intr_0_0_to_MAIN2MCU_LVL_INTRTR0_in_29_29 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 29,
};
const struct Sciclient_rmIrqIf * const tisci_if_MMCSD1[] = {
	&MMCSD1_emmcsdss_intr_0_0_to_MAIN2MCU_LVL_INTRTR0_in_29_29,
};
static const struct Sciclient_rmIrqNode tisci_irq_MMCSD1 = {
	.id = TISCI_DEV_MMCSD1,
	.n_if = 1,
	.p_if = &tisci_if_MMCSD1[0],
};

/* Start of EQEP0 interface definition */
const struct Sciclient_rmIrqIf EQEP0_eqep_int_0_0_to_MAIN2MCU_PLS_INTRTR0_in_14_14 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 14,
};
const struct Sciclient_rmIrqIf * const tisci_if_EQEP0[] = {
	&EQEP0_eqep_int_0_0_to_MAIN2MCU_PLS_INTRTR0_in_14_14,
};
static const struct Sciclient_rmIrqNode tisci_irq_EQEP0 = {
	.id = TISCI_DEV_EQEP0,
	.n_if = 1,
	.p_if = &tisci_if_EQEP0[0],
};

/* Start of EQEP1 interface definition */
const struct Sciclient_rmIrqIf EQEP1_eqep_int_0_0_to_MAIN2MCU_PLS_INTRTR0_in_15_15 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 15,
};
const struct Sciclient_rmIrqIf * const tisci_if_EQEP1[] = {
	&EQEP1_eqep_int_0_0_to_MAIN2MCU_PLS_INTRTR0_in_15_15,
};
static const struct Sciclient_rmIrqNode tisci_irq_EQEP1 = {
	.id = TISCI_DEV_EQEP1,
	.n_if = 1,
	.p_if = &tisci_if_EQEP1[0],
};

/* Start of EQEP2 interface definition */
const struct Sciclient_rmIrqIf EQEP2_eqep_int_0_0_to_MAIN2MCU_PLS_INTRTR0_in_16_16 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 16,
};
const struct Sciclient_rmIrqIf * const tisci_if_EQEP2[] = {
	&EQEP2_eqep_int_0_0_to_MAIN2MCU_PLS_INTRTR0_in_16_16,
};
static const struct Sciclient_rmIrqNode tisci_irq_EQEP2 = {
	.id = TISCI_DEV_EQEP2,
	.n_if = 1,
	.p_if = &tisci_if_EQEP2[0],
};

/* Start of UART0 interface definition */
const struct Sciclient_rmIrqIf UART0_usart_irq_0_0_to_MAIN2MCU_LVL_INTRTR0_in_96_96 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 96,
};
const struct Sciclient_rmIrqIf * const tisci_if_UART0[] = {
	&UART0_usart_irq_0_0_to_MAIN2MCU_LVL_INTRTR0_in_96_96,
};
static const struct Sciclient_rmIrqNode tisci_irq_UART0 = {
	.id = TISCI_DEV_UART0,
	.n_if = 1,
	.p_if = &tisci_if_UART0[0],
};

/* Start of GPIO0 interface definition */
const struct Sciclient_rmIrqIf GPIO0_gpio_bank_0_7_to_GPIOMUX_INTRTR0_in_145_152 = {
	.lbase = 0,
	.len = 8,
	.rid = TISCI_DEV_GPIOMUX_INTRTR0,
	.rbase = 145,
};
const struct Sciclient_rmIrqIf * const tisci_if_GPIO0[] = {
	&GPIO0_gpio_bank_0_7_to_GPIOMUX_INTRTR0_in_145_152,
};
static const struct Sciclient_rmIrqNode tisci_irq_GPIO0 = {
	.id = TISCI_DEV_GPIO0,
	.n_if = 1,
	.p_if = &tisci_if_GPIO0[0],
};

/* Start of GPIO2 interface definition */
const struct Sciclient_rmIrqIf GPIO2_gpio_bank_0_7_to_GPIOMUX_INTRTR0_in_154_161 = {
	.lbase = 0,
	.len = 8,
	.rid = TISCI_DEV_GPIOMUX_INTRTR0,
	.rbase = 154,
};
const struct Sciclient_rmIrqIf * const tisci_if_GPIO2[] = {
	&GPIO2_gpio_bank_0_7_to_GPIOMUX_INTRTR0_in_154_161,
};
static const struct Sciclient_rmIrqNode tisci_irq_GPIO2 = {
	.id = TISCI_DEV_GPIO2,
	.n_if = 1,
	.p_if = &tisci_if_GPIO2[0],
};

/* Start of GPIO4 interface definition */
const struct Sciclient_rmIrqIf GPIO4_gpio_bank_0_7_to_GPIOMUX_INTRTR0_in_163_170 = {
	.lbase = 0,
	.len = 8,
	.rid = TISCI_DEV_GPIOMUX_INTRTR0,
	.rbase = 163,
};
const struct Sciclient_rmIrqIf * const tisci_if_GPIO4[] = {
	&GPIO4_gpio_bank_0_7_to_GPIOMUX_INTRTR0_in_163_170,
};
static const struct Sciclient_rmIrqNode tisci_irq_GPIO4 = {
	.id = TISCI_DEV_GPIO4,
	.n_if = 1,
	.p_if = &tisci_if_GPIO4[0],
};

/* Start of GPIO6 interface definition */
const struct Sciclient_rmIrqIf GPIO6_gpio_bank_0_7_to_GPIOMUX_INTRTR0_in_172_179 = {
	.lbase = 0,
	.len = 8,
	.rid = TISCI_DEV_GPIOMUX_INTRTR0,
	.rbase = 172,
};
const struct Sciclient_rmIrqIf * const tisci_if_GPIO6[] = {
	&GPIO6_gpio_bank_0_7_to_GPIOMUX_INTRTR0_in_172_179,
};
static const struct Sciclient_rmIrqNode tisci_irq_GPIO6 = {
	.id = TISCI_DEV_GPIO6,
	.n_if = 1,
	.p_if = &tisci_if_GPIO6[0],
};

/* Start of WKUP_GPIO0 interface definition */
const struct Sciclient_rmIrqIf WKUP_GPIO0_gpio_bank_0_5_to_WKUP_GPIOMUX_INTRTR0_in_103_108 = {
	.lbase = 0,
	.len = 6,
	.rid = TISCI_DEV_WKUP_GPIOMUX_INTRTR0,
	.rbase = 103,
};
const struct Sciclient_rmIrqIf * const tisci_if_WKUP_GPIO0[] = {
	&WKUP_GPIO0_gpio_bank_0_5_to_WKUP_GPIOMUX_INTRTR0_in_103_108,
};
static const struct Sciclient_rmIrqNode tisci_irq_WKUP_GPIO0 = {
	.id = TISCI_DEV_WKUP_GPIO0,
	.n_if = 1,
	.p_if = &tisci_if_WKUP_GPIO0[0],
};

/* Start of WKUP_GPIO1 interface definition */
const struct Sciclient_rmIrqIf WKUP_GPIO1_gpio_bank_0_5_to_WKUP_GPIOMUX_INTRTR0_in_112_117 = {
	.lbase = 0,
	.len = 6,
	.rid = TISCI_DEV_WKUP_GPIOMUX_INTRTR0,
	.rbase = 112,
};
const struct Sciclient_rmIrqIf * const tisci_if_WKUP_GPIO1[] = {
	&WKUP_GPIO1_gpio_bank_0_5_to_WKUP_GPIOMUX_INTRTR0_in_112_117,
};
static const struct Sciclient_rmIrqNode tisci_irq_WKUP_GPIO1 = {
	.id = TISCI_DEV_WKUP_GPIO1,
	.n_if = 1,
	.p_if = &tisci_if_WKUP_GPIO1[0],
};

/* Start of GPMC0 interface definition */
const struct Sciclient_rmIrqIf GPMC0_gpmc_sinterrupt_0_0_to_MAIN2MCU_LVL_INTRTR0_in_8_8 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 8,
};
const struct Sciclient_rmIrqIf * const tisci_if_GPMC0[] = {
	&GPMC0_gpmc_sinterrupt_0_0_to_MAIN2MCU_LVL_INTRTR0_in_8_8,
};
static const struct Sciclient_rmIrqNode tisci_irq_GPMC0 = {
	.id = TISCI_DEV_GPMC0,
	.n_if = 1,
	.p_if = &tisci_if_GPMC0[0],
};

/* Start of MAIN2MCU_LVL_INTRTR0 interface definition */
const struct Sciclient_rmIrqIf MAIN2MCU_LVL_INTRTR0_outl_0_63_to_MCU_R5FSS0_CORE0_intr_160_223 = {
	.lbase = 0,
	.len = 64,
	.rid = TISCI_DEV_MCU_R5FSS0_CORE0,
	.rbase = 160,
};
const struct Sciclient_rmIrqIf MAIN2MCU_LVL_INTRTR0_outl_0_63_to_MCU_R5FSS0_CORE1_intr_160_223 = {
	.lbase = 0,
	.len = 64,
	.rid = TISCI_DEV_MCU_R5FSS0_CORE1,
	.rbase = 160,
};
const struct Sciclient_rmIrqIf MAIN2MCU_LVL_INTRTR0_outl_56_63_to_WKUP_HSM0_nvic_64_71 = {
	.lbase = 56,
	.len = 8,
	.rid = TISCI_DEV_WKUP_HSM0,
	.rbase = 64,
};
const struct Sciclient_rmIrqIf * const tisci_if_MAIN2MCU_LVL_INTRTR0[] = {
	&MAIN2MCU_LVL_INTRTR0_outl_0_63_to_MCU_R5FSS0_CORE0_intr_160_223,
	&MAIN2MCU_LVL_INTRTR0_outl_0_63_to_MCU_R5FSS0_CORE1_intr_160_223,
	&MAIN2MCU_LVL_INTRTR0_outl_56_63_to_WKUP_HSM0_nvic_64_71,
};
static const struct Sciclient_rmIrqNode tisci_irq_MAIN2MCU_LVL_INTRTR0 = {
	.id = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.n_if = 3,
	.p_if = &tisci_if_MAIN2MCU_LVL_INTRTR0[0],
};

/* Start of MAIN2MCU_PLS_INTRTR0 interface definition */
const struct Sciclient_rmIrqIf MAIN2MCU_PLS_INTRTR0_outp_0_47_to_MCU_R5FSS0_CORE0_intr_224_271 = {
	.lbase = 0,
	.len = 48,
	.rid = TISCI_DEV_MCU_R5FSS0_CORE0,
	.rbase = 224,
};
const struct Sciclient_rmIrqIf MAIN2MCU_PLS_INTRTR0_outp_0_47_to_MCU_R5FSS0_CORE1_intr_224_271 = {
	.lbase = 0,
	.len = 48,
	.rid = TISCI_DEV_MCU_R5FSS0_CORE1,
	.rbase = 224,
};
const struct Sciclient_rmIrqIf MAIN2MCU_PLS_INTRTR0_outp_40_47_to_WKUP_HSM0_nvic_72_79 = {
	.lbase = 40,
	.len = 8,
	.rid = TISCI_DEV_WKUP_HSM0,
	.rbase = 72,
};
const struct Sciclient_rmIrqIf * const tisci_if_MAIN2MCU_PLS_INTRTR0[] = {
	&MAIN2MCU_PLS_INTRTR0_outp_0_47_to_MCU_R5FSS0_CORE0_intr_224_271,
	&MAIN2MCU_PLS_INTRTR0_outp_0_47_to_MCU_R5FSS0_CORE1_intr_224_271,
	&MAIN2MCU_PLS_INTRTR0_outp_40_47_to_WKUP_HSM0_nvic_72_79,
};
static const struct Sciclient_rmIrqNode tisci_irq_MAIN2MCU_PLS_INTRTR0 = {
	.id = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.n_if = 3,
	.p_if = &tisci_if_MAIN2MCU_PLS_INTRTR0[0],
};

/* Start of TIMESYNC_INTRTR0 interface definition */
const struct Sciclient_rmIrqIf TIMESYNC_INTRTR0_outl_0_0_to_NAVSS0_cpts0_hw1_push_0_0 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_NAVSS0,
	.rbase = 0,
};
const struct Sciclient_rmIrqIf TIMESYNC_INTRTR0_outl_1_1_to_NAVSS0_cpts0_hw2_push_1_1 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_NAVSS0,
	.rbase = 1,
};
const struct Sciclient_rmIrqIf TIMESYNC_INTRTR0_outl_2_2_to_NAVSS0_cpts0_hw3_push_2_2 = {
	.lbase = 2,
	.len = 1,
	.rid = TISCI_DEV_NAVSS0,
	.rbase = 2,
};
const struct Sciclient_rmIrqIf TIMESYNC_INTRTR0_outl_3_3_to_NAVSS0_cpts0_hw4_push_3_3 = {
	.lbase = 3,
	.len = 1,
	.rid = TISCI_DEV_NAVSS0,
	.rbase = 3,
};
const struct Sciclient_rmIrqIf TIMESYNC_INTRTR0_outl_4_4_to_NAVSS0_cpts0_hw5_push_4_4 = {
	.lbase = 4,
	.len = 1,
	.rid = TISCI_DEV_NAVSS0,
	.rbase = 4,
};
const struct Sciclient_rmIrqIf TIMESYNC_INTRTR0_outl_5_5_to_NAVSS0_cpts0_hw6_push_5_5 = {
	.lbase = 5,
	.len = 1,
	.rid = TISCI_DEV_NAVSS0,
	.rbase = 5,
};
const struct Sciclient_rmIrqIf TIMESYNC_INTRTR0_outl_6_6_to_NAVSS0_cpts0_hw7_push_6_6 = {
	.lbase = 6,
	.len = 1,
	.rid = TISCI_DEV_NAVSS0,
	.rbase = 6,
};
const struct Sciclient_rmIrqIf TIMESYNC_INTRTR0_outl_7_7_to_NAVSS0_cpts0_hw8_push_7_7 = {
	.lbase = 7,
	.len = 1,
	.rid = TISCI_DEV_NAVSS0,
	.rbase = 7,
};
const struct Sciclient_rmIrqIf TIMESYNC_INTRTR0_outl_20_20_to_PCIE0_pcie_cpts_hw2_push_0_0 = {
	.lbase = 20,
	.len = 1,
	.rid = TISCI_DEV_PCIE0,
	.rbase = 0,
};
const struct Sciclient_rmIrqIf TIMESYNC_INTRTR0_outl_21_21_to_PCIE1_pcie_cpts_hw2_push_0_0 = {
	.lbase = 21,
	.len = 1,
	.rid = TISCI_DEV_PCIE1,
	.rbase = 0,
};
const struct Sciclient_rmIrqIf TIMESYNC_INTRTR0_outl_22_22_to_PCIE2_pcie_cpts_hw2_push_0_0 = {
	.lbase = 22,
	.len = 1,
	.rid = TISCI_DEV_PCIE2,
	.rbase = 0,
};
const struct Sciclient_rmIrqIf TIMESYNC_INTRTR0_outl_23_23_to_PCIE3_pcie_cpts_hw2_push_0_0 = {
	.lbase = 23,
	.len = 1,
	.rid = TISCI_DEV_PCIE3,
	.rbase = 0,
};
const struct Sciclient_rmIrqIf TIMESYNC_INTRTR0_outl_24_24_to_MCU_CPSW0_cpts_hw3_push_0_0 = {
	.lbase = 24,
	.len = 1,
	.rid = TISCI_DEV_MCU_CPSW0,
	.rbase = 0,
};
const struct Sciclient_rmIrqIf TIMESYNC_INTRTR0_outl_25_25_to_MCU_CPSW0_cpts_hw4_push_1_1 = {
	.lbase = 25,
	.len = 1,
	.rid = TISCI_DEV_MCU_CPSW0,
	.rbase = 1,
};
const struct Sciclient_rmIrqIf TIMESYNC_INTRTR0_outl_26_26_to_cpsw_9xuss_j7am0_cpts_hw1_push_0_0 = {
	.lbase = 26,
	.len = 1,
	.rid = TISCI_DEV_CPSW_9XUSS_J7AM0,
	.rbase = 0,
};
const struct Sciclient_rmIrqIf TIMESYNC_INTRTR0_outl_27_27_to_cpsw_9xuss_j7am0_cpts_hw2_push_1_1 = {
	.lbase = 27,
	.len = 1,
	.rid = TISCI_DEV_CPSW_9XUSS_J7AM0,
	.rbase = 1,
};
const struct Sciclient_rmIrqIf TIMESYNC_INTRTR0_outl_28_28_to_cpsw_9xuss_j7am0_cpts_hw3_push_2_2 = {
	.lbase = 28,
	.len = 1,
	.rid = TISCI_DEV_CPSW_9XUSS_J7AM0,
	.rbase = 2,
};
const struct Sciclient_rmIrqIf TIMESYNC_INTRTR0_outl_29_29_to_cpsw_9xuss_j7am0_cpts_hw4_push_3_3 = {
	.lbase = 29,
	.len = 1,
	.rid = TISCI_DEV_CPSW_9XUSS_J7AM0,
	.rbase = 3,
};
const struct Sciclient_rmIrqIf TIMESYNC_INTRTR0_outl_30_30_to_cpsw_9xuss_j7am0_cpts_hw5_push_4_4 = {
	.lbase = 30,
	.len = 1,
	.rid = TISCI_DEV_CPSW_9XUSS_J7AM0,
	.rbase = 4,
};
const struct Sciclient_rmIrqIf TIMESYNC_INTRTR0_outl_31_31_to_cpsw_9xuss_j7am0_cpts_hw6_push_5_5 = {
	.lbase = 31,
	.len = 1,
	.rid = TISCI_DEV_CPSW_9XUSS_J7AM0,
	.rbase = 5,
};
const struct Sciclient_rmIrqIf TIMESYNC_INTRTR0_outl_32_32_to_cpsw_9xuss_j7am0_cpts_hw7_push_6_6 = {
	.lbase = 32,
	.len = 1,
	.rid = TISCI_DEV_CPSW_9XUSS_J7AM0,
	.rbase = 6,
};
const struct Sciclient_rmIrqIf TIMESYNC_INTRTR0_outl_33_33_to_cpsw_9xuss_j7am0_cpts_hw8_push_7_7 = {
	.lbase = 33,
	.len = 1,
	.rid = TISCI_DEV_CPSW_9XUSS_J7AM0,
	.rbase = 7,
};
const struct Sciclient_rmIrqIf TIMESYNC_INTRTR0_outl_38_38_to_CPSW1_cpts_hw3_push_0_0 = {
	.lbase = 38,
	.len = 1,
	.rid = TISCI_DEV_CPSW1,
	.rbase = 0,
};
const struct Sciclient_rmIrqIf TIMESYNC_INTRTR0_outl_39_39_to_CPSW1_cpts_hw4_push_1_1 = {
	.lbase = 39,
	.len = 1,
	.rid = TISCI_DEV_CPSW1,
	.rbase = 1,
};
const struct Sciclient_rmIrqIf TIMESYNC_INTRTR0_outl_40_47_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_100_107 = {
	.lbase = 40,
	.len = 8,
	.rid = TISCI_DEV_NAVSS0_UDMASS_INTA_0,
	.rbase = 100,
};
const struct Sciclient_rmIrqIf * const tisci_if_TIMESYNC_INTRTR0[] = {
	&TIMESYNC_INTRTR0_outl_0_0_to_NAVSS0_cpts0_hw1_push_0_0,
	&TIMESYNC_INTRTR0_outl_1_1_to_NAVSS0_cpts0_hw2_push_1_1,
	&TIMESYNC_INTRTR0_outl_2_2_to_NAVSS0_cpts0_hw3_push_2_2,
	&TIMESYNC_INTRTR0_outl_3_3_to_NAVSS0_cpts0_hw4_push_3_3,
	&TIMESYNC_INTRTR0_outl_4_4_to_NAVSS0_cpts0_hw5_push_4_4,
	&TIMESYNC_INTRTR0_outl_5_5_to_NAVSS0_cpts0_hw6_push_5_5,
	&TIMESYNC_INTRTR0_outl_6_6_to_NAVSS0_cpts0_hw7_push_6_6,
	&TIMESYNC_INTRTR0_outl_7_7_to_NAVSS0_cpts0_hw8_push_7_7,
	&TIMESYNC_INTRTR0_outl_20_20_to_PCIE0_pcie_cpts_hw2_push_0_0,
	&TIMESYNC_INTRTR0_outl_21_21_to_PCIE1_pcie_cpts_hw2_push_0_0,
	&TIMESYNC_INTRTR0_outl_22_22_to_PCIE2_pcie_cpts_hw2_push_0_0,
	&TIMESYNC_INTRTR0_outl_23_23_to_PCIE3_pcie_cpts_hw2_push_0_0,
	&TIMESYNC_INTRTR0_outl_24_24_to_MCU_CPSW0_cpts_hw3_push_0_0,
	&TIMESYNC_INTRTR0_outl_25_25_to_MCU_CPSW0_cpts_hw4_push_1_1,
	&TIMESYNC_INTRTR0_outl_26_26_to_cpsw_9xuss_j7am0_cpts_hw1_push_0_0,
	&TIMESYNC_INTRTR0_outl_27_27_to_cpsw_9xuss_j7am0_cpts_hw2_push_1_1,
	&TIMESYNC_INTRTR0_outl_28_28_to_cpsw_9xuss_j7am0_cpts_hw3_push_2_2,
	&TIMESYNC_INTRTR0_outl_29_29_to_cpsw_9xuss_j7am0_cpts_hw4_push_3_3,
	&TIMESYNC_INTRTR0_outl_30_30_to_cpsw_9xuss_j7am0_cpts_hw5_push_4_4,
	&TIMESYNC_INTRTR0_outl_31_31_to_cpsw_9xuss_j7am0_cpts_hw6_push_5_5,
	&TIMESYNC_INTRTR0_outl_32_32_to_cpsw_9xuss_j7am0_cpts_hw7_push_6_6,
	&TIMESYNC_INTRTR0_outl_33_33_to_cpsw_9xuss_j7am0_cpts_hw8_push_7_7,
	&TIMESYNC_INTRTR0_outl_38_38_to_CPSW1_cpts_hw3_push_0_0,
	&TIMESYNC_INTRTR0_outl_39_39_to_CPSW1_cpts_hw4_push_1_1,
	&TIMESYNC_INTRTR0_outl_40_47_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_100_107,
};
static const struct Sciclient_rmIrqNode tisci_irq_TIMESYNC_INTRTR0 = {
	.id = TISCI_DEV_TIMESYNC_INTRTR0,
	.n_if = 25,
	.p_if = &tisci_if_TIMESYNC_INTRTR0[0],
};

/* Start of WKUP_GPIOMUX_INTRTR0 interface definition */
const struct Sciclient_rmIrqIf WKUP_GPIOMUX_INTRTR0_outp_0_15_to_MCU_R5FSS0_CORE0_intr_124_139 = {
	.lbase = 0,
	.len = 16,
	.rid = TISCI_DEV_MCU_R5FSS0_CORE0,
	.rbase = 124,
};
const struct Sciclient_rmIrqIf WKUP_GPIOMUX_INTRTR0_outp_0_15_to_MCU_R5FSS0_CORE1_intr_124_139 = {
	.lbase = 0,
	.len = 16,
	.rid = TISCI_DEV_MCU_R5FSS0_CORE1,
	.rbase = 124,
};
const struct Sciclient_rmIrqIf WKUP_GPIOMUX_INTRTR0_outp_0_11_to_WKUP_HSM0_nvic_184_195 = {
	.lbase = 0,
	.len = 12,
	.rid = TISCI_DEV_WKUP_HSM0,
	.rbase = 184,
};
const struct Sciclient_rmIrqIf WKUP_GPIOMUX_INTRTR0_outp_8_15_to_WKUP_ESM0_esm_pls_event0_120_127 = {
	.lbase = 8,
	.len = 8,
	.rid = TISCI_DEV_WKUP_ESM0,
	.rbase = 120,
};
const struct Sciclient_rmIrqIf WKUP_GPIOMUX_INTRTR0_outp_8_15_to_WKUP_ESM0_esm_pls_event1_128_135 = {
	.lbase = 8,
	.len = 8,
	.rid = TISCI_DEV_WKUP_ESM0,
	.rbase = 128,
};
const struct Sciclient_rmIrqIf WKUP_GPIOMUX_INTRTR0_outp_8_15_to_WKUP_ESM0_esm_pls_event2_136_143 = {
	.lbase = 8,
	.len = 8,
	.rid = TISCI_DEV_WKUP_ESM0,
	.rbase = 136,
};
const struct Sciclient_rmIrqIf WKUP_GPIOMUX_INTRTR0_outp_12_19_to_MCU_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_4_11 = {
	.lbase = 12,
	.len = 8,
	.rid = TISCI_DEV_MCU_NAVSS0_UDMASS_INTA_0,
	.rbase = 4,
};
const struct Sciclient_rmIrqIf WKUP_GPIOMUX_INTRTR0_outp_16_31_to_COMPUTE_CLUSTER0_CLEC_soc_events_in_960_975 = {
	.lbase = 16,
	.len = 16,
	.rid = TISCI_DEV_COMPUTE_CLUSTER0_CLEC,
	.rbase = 960,
};
const struct Sciclient_rmIrqIf WKUP_GPIOMUX_INTRTR0_outp_16_31_to_COMPUTE_CLUSTER0_GIC500SS_spi_960_975 = {
	.lbase = 16,
	.len = 16,
	.rid = TISCI_DEV_COMPUTE_CLUSTER0_GIC500SS,
	.rbase = 960,
};
const struct Sciclient_rmIrqIf WKUP_GPIOMUX_INTRTR0_outp_16_31_to_R5FSS0_CORE0_intr_488_503 = {
	.lbase = 16,
	.len = 16,
	.rid = TISCI_DEV_R5FSS0_CORE0,
	.rbase = 488,
};
const struct Sciclient_rmIrqIf WKUP_GPIOMUX_INTRTR0_outp_16_31_to_R5FSS0_CORE1_intr_488_503 = {
	.lbase = 16,
	.len = 16,
	.rid = TISCI_DEV_R5FSS0_CORE1,
	.rbase = 488,
};
const struct Sciclient_rmIrqIf WKUP_GPIOMUX_INTRTR0_outp_16_31_to_R5FSS1_CORE0_intr_488_503 = {
	.lbase = 16,
	.len = 16,
	.rid = TISCI_DEV_R5FSS1_CORE0,
	.rbase = 488,
};
const struct Sciclient_rmIrqIf WKUP_GPIOMUX_INTRTR0_outp_16_31_to_R5FSS1_CORE1_intr_488_503 = {
	.lbase = 16,
	.len = 16,
	.rid = TISCI_DEV_R5FSS1_CORE1,
	.rbase = 488,
};
const struct Sciclient_rmIrqIf WKUP_GPIOMUX_INTRTR0_outp_16_31_to_R5FSS2_CORE0_intr_488_503 = {
	.lbase = 16,
	.len = 16,
	.rid = TISCI_DEV_R5FSS2_CORE0,
	.rbase = 488,
};
const struct Sciclient_rmIrqIf WKUP_GPIOMUX_INTRTR0_outp_16_31_to_R5FSS2_CORE1_intr_488_503 = {
	.lbase = 16,
	.len = 16,
	.rid = TISCI_DEV_R5FSS2_CORE1,
	.rbase = 488,
};
const struct Sciclient_rmIrqIf * const tisci_if_WKUP_GPIOMUX_INTRTR0[] = {
	&WKUP_GPIOMUX_INTRTR0_outp_0_15_to_MCU_R5FSS0_CORE0_intr_124_139,
	&WKUP_GPIOMUX_INTRTR0_outp_0_15_to_MCU_R5FSS0_CORE1_intr_124_139,
	&WKUP_GPIOMUX_INTRTR0_outp_0_11_to_WKUP_HSM0_nvic_184_195,
	&WKUP_GPIOMUX_INTRTR0_outp_8_15_to_WKUP_ESM0_esm_pls_event0_120_127,
	&WKUP_GPIOMUX_INTRTR0_outp_8_15_to_WKUP_ESM0_esm_pls_event1_128_135,
	&WKUP_GPIOMUX_INTRTR0_outp_8_15_to_WKUP_ESM0_esm_pls_event2_136_143,
	&WKUP_GPIOMUX_INTRTR0_outp_12_19_to_MCU_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_4_11,
	&WKUP_GPIOMUX_INTRTR0_outp_16_31_to_COMPUTE_CLUSTER0_CLEC_soc_events_in_960_975,
	&WKUP_GPIOMUX_INTRTR0_outp_16_31_to_COMPUTE_CLUSTER0_GIC500SS_spi_960_975,
	&WKUP_GPIOMUX_INTRTR0_outp_16_31_to_R5FSS0_CORE0_intr_488_503,
	&WKUP_GPIOMUX_INTRTR0_outp_16_31_to_R5FSS0_CORE1_intr_488_503,
	&WKUP_GPIOMUX_INTRTR0_outp_16_31_to_R5FSS1_CORE0_intr_488_503,
	&WKUP_GPIOMUX_INTRTR0_outp_16_31_to_R5FSS1_CORE1_intr_488_503,
	&WKUP_GPIOMUX_INTRTR0_outp_16_31_to_R5FSS2_CORE0_intr_488_503,
	&WKUP_GPIOMUX_INTRTR0_outp_16_31_to_R5FSS2_CORE1_intr_488_503,
};
static const struct Sciclient_rmIrqNode tisci_irq_WKUP_GPIOMUX_INTRTR0 = {
	.id = TISCI_DEV_WKUP_GPIOMUX_INTRTR0,
	.n_if = 15,
	.p_if = &tisci_if_WKUP_GPIOMUX_INTRTR0[0],
};

/* Start of j7aep_gpu_bxs464_wrap0 interface definition */
const struct Sciclient_rmIrqIf j7aep_gpu_bxs464_wrap0_gpu_pwrctrl_req_0_0_to_MAIN2MCU_LVL_INTRTR0_in_316_316 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 316,
};
const struct Sciclient_rmIrqIf * const tisci_if_j7aep_gpu_bxs464_wrap0[] = {
	&j7aep_gpu_bxs464_wrap0_gpu_pwrctrl_req_0_0_to_MAIN2MCU_LVL_INTRTR0_in_316_316,
};
static const struct Sciclient_rmIrqNode tisci_irq_j7aep_gpu_bxs464_wrap0 = {
	.id = TISCI_DEV_J7AEP_GPU_BXS464_WRAP0,
	.n_if = 1,
	.p_if = &tisci_if_j7aep_gpu_bxs464_wrap0[0],
};

/* Start of J7AEP_GPU_BXS464_WRAP0_GPU_SS_0 interface definition */
const struct Sciclient_rmIrqIf J7AEP_GPU_BXS464_WRAP0_GPU_SS_0_os_irq_0_3_to_MAIN2MCU_LVL_INTRTR0_in_312_315 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 312,
};
const struct Sciclient_rmIrqIf * const tisci_if_J7AEP_GPU_BXS464_WRAP0_GPU_SS_0[] = {
	&J7AEP_GPU_BXS464_WRAP0_GPU_SS_0_os_irq_0_3_to_MAIN2MCU_LVL_INTRTR0_in_312_315,
};
static const struct Sciclient_rmIrqNode tisci_irq_J7AEP_GPU_BXS464_WRAP0_GPU_SS_0 = {
	.id = TISCI_DEV_J7AEP_GPU_BXS464_WRAP0_GPU_SS_0,
	.n_if = 1,
	.p_if = &tisci_if_J7AEP_GPU_BXS464_WRAP0_GPU_SS_0[0],
};

/* Start of DDR0 interface definition */
const struct Sciclient_rmIrqIf DDR0_ddrss_pll_freq_change_req_2_2_to_MAIN2MCU_LVL_INTRTR0_in_9_9 = {
	.lbase = 2,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 9,
};
const struct Sciclient_rmIrqIf DDR0_ddrss_controller_0_0_to_MAIN2MCU_LVL_INTRTR0_in_10_10 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 10,
};
const struct Sciclient_rmIrqIf DDR0_ddrss_v2a_other_err_lvl_3_3_to_MAIN2MCU_LVL_INTRTR0_in_11_11 = {
	.lbase = 3,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 11,
};
const struct Sciclient_rmIrqIf DDR0_ddrss_hs_phy_global_error_1_1_to_MAIN2MCU_LVL_INTRTR0_in_12_12 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 12,
};
const struct Sciclient_rmIrqIf * const tisci_if_DDR0[] = {
	&DDR0_ddrss_pll_freq_change_req_2_2_to_MAIN2MCU_LVL_INTRTR0_in_9_9,
	&DDR0_ddrss_controller_0_0_to_MAIN2MCU_LVL_INTRTR0_in_10_10,
	&DDR0_ddrss_v2a_other_err_lvl_3_3_to_MAIN2MCU_LVL_INTRTR0_in_11_11,
	&DDR0_ddrss_hs_phy_global_error_1_1_to_MAIN2MCU_LVL_INTRTR0_in_12_12,
};
static const struct Sciclient_rmIrqNode tisci_irq_DDR0 = {
	.id = TISCI_DEV_DDR0,
	.n_if = 4,
	.p_if = &tisci_if_DDR0[0],
};

/* Start of DDR1 interface definition */
const struct Sciclient_rmIrqIf DDR1_ddrss_pll_freq_change_req_2_2_to_MAIN2MCU_LVL_INTRTR0_in_63_63 = {
	.lbase = 2,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 63,
};
const struct Sciclient_rmIrqIf DDR1_ddrss_controller_0_0_to_MAIN2MCU_LVL_INTRTR0_in_64_64 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 64,
};
const struct Sciclient_rmIrqIf DDR1_ddrss_v2a_other_err_lvl_3_3_to_MAIN2MCU_LVL_INTRTR0_in_65_65 = {
	.lbase = 3,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 65,
};
const struct Sciclient_rmIrqIf DDR1_ddrss_hs_phy_global_error_1_1_to_MAIN2MCU_LVL_INTRTR0_in_66_66 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 66,
};
const struct Sciclient_rmIrqIf * const tisci_if_DDR1[] = {
	&DDR1_ddrss_pll_freq_change_req_2_2_to_MAIN2MCU_LVL_INTRTR0_in_63_63,
	&DDR1_ddrss_controller_0_0_to_MAIN2MCU_LVL_INTRTR0_in_64_64,
	&DDR1_ddrss_v2a_other_err_lvl_3_3_to_MAIN2MCU_LVL_INTRTR0_in_65_65,
	&DDR1_ddrss_hs_phy_global_error_1_1_to_MAIN2MCU_LVL_INTRTR0_in_66_66,
};
static const struct Sciclient_rmIrqNode tisci_irq_DDR1 = {
	.id = TISCI_DEV_DDR1,
	.n_if = 4,
	.p_if = &tisci_if_DDR1[0],
};

/* Start of DDR2 interface definition */
const struct Sciclient_rmIrqIf DDR2_ddrss_pll_freq_change_req_2_2_to_MAIN2MCU_LVL_INTRTR0_in_200_200 = {
	.lbase = 2,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 200,
};
const struct Sciclient_rmIrqIf DDR2_ddrss_controller_0_0_to_MAIN2MCU_LVL_INTRTR0_in_201_201 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 201,
};
const struct Sciclient_rmIrqIf DDR2_ddrss_v2a_other_err_lvl_3_3_to_MAIN2MCU_LVL_INTRTR0_in_202_202 = {
	.lbase = 3,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 202,
};
const struct Sciclient_rmIrqIf DDR2_ddrss_hs_phy_global_error_1_1_to_MAIN2MCU_LVL_INTRTR0_in_203_203 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 203,
};
const struct Sciclient_rmIrqIf * const tisci_if_DDR2[] = {
	&DDR2_ddrss_pll_freq_change_req_2_2_to_MAIN2MCU_LVL_INTRTR0_in_200_200,
	&DDR2_ddrss_controller_0_0_to_MAIN2MCU_LVL_INTRTR0_in_201_201,
	&DDR2_ddrss_v2a_other_err_lvl_3_3_to_MAIN2MCU_LVL_INTRTR0_in_202_202,
	&DDR2_ddrss_hs_phy_global_error_1_1_to_MAIN2MCU_LVL_INTRTR0_in_203_203,
};
static const struct Sciclient_rmIrqNode tisci_irq_DDR2 = {
	.id = TISCI_DEV_DDR2,
	.n_if = 4,
	.p_if = &tisci_if_DDR2[0],
};

/* Start of DDR3 interface definition */
const struct Sciclient_rmIrqIf DDR3_ddrss_pll_freq_change_req_2_2_to_MAIN2MCU_LVL_INTRTR0_in_148_148 = {
	.lbase = 2,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 148,
};
const struct Sciclient_rmIrqIf DDR3_ddrss_controller_0_0_to_MAIN2MCU_LVL_INTRTR0_in_149_149 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 149,
};
const struct Sciclient_rmIrqIf DDR3_ddrss_v2a_other_err_lvl_3_3_to_MAIN2MCU_LVL_INTRTR0_in_150_150 = {
	.lbase = 3,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 150,
};
const struct Sciclient_rmIrqIf DDR3_ddrss_hs_phy_global_error_1_1_to_MAIN2MCU_LVL_INTRTR0_in_151_151 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 151,
};
const struct Sciclient_rmIrqIf * const tisci_if_DDR3[] = {
	&DDR3_ddrss_pll_freq_change_req_2_2_to_MAIN2MCU_LVL_INTRTR0_in_148_148,
	&DDR3_ddrss_controller_0_0_to_MAIN2MCU_LVL_INTRTR0_in_149_149,
	&DDR3_ddrss_v2a_other_err_lvl_3_3_to_MAIN2MCU_LVL_INTRTR0_in_150_150,
	&DDR3_ddrss_hs_phy_global_error_1_1_to_MAIN2MCU_LVL_INTRTR0_in_151_151,
};
static const struct Sciclient_rmIrqNode tisci_irq_DDR3 = {
	.id = TISCI_DEV_DDR3,
	.n_if = 4,
	.p_if = &tisci_if_DDR3[0],
};

/* Start of DSS_DSI0 interface definition */
const struct Sciclient_rmIrqIf DSS_DSI0_dsi_0_func_intr_0_0_to_MAIN2MCU_LVL_INTRTR0_in_224_224 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 224,
};
const struct Sciclient_rmIrqIf * const tisci_if_DSS_DSI0[] = {
	&DSS_DSI0_dsi_0_func_intr_0_0_to_MAIN2MCU_LVL_INTRTR0_in_224_224,
};
static const struct Sciclient_rmIrqNode tisci_irq_DSS_DSI0 = {
	.id = TISCI_DEV_DSS_DSI0,
	.n_if = 1,
	.p_if = &tisci_if_DSS_DSI0[0],
};

/* Start of DSS_DSI1 interface definition */
const struct Sciclient_rmIrqIf DSS_DSI1_dsi_0_func_intr_0_0_to_MAIN2MCU_LVL_INTRTR0_in_225_225 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 225,
};
const struct Sciclient_rmIrqIf * const tisci_if_DSS_DSI1[] = {
	&DSS_DSI1_dsi_0_func_intr_0_0_to_MAIN2MCU_LVL_INTRTR0_in_225_225,
};
static const struct Sciclient_rmIrqNode tisci_irq_DSS_DSI1 = {
	.id = TISCI_DEV_DSS_DSI1,
	.n_if = 1,
	.p_if = &tisci_if_DSS_DSI1[0],
};

/* Start of DSS_EDP0 interface definition */
const struct Sciclient_rmIrqIf DSS_EDP0_intr_0_3_to_MAIN2MCU_LVL_INTRTR0_in_238_241 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 238,
};
const struct Sciclient_rmIrqIf * const tisci_if_DSS_EDP0[] = {
	&DSS_EDP0_intr_0_3_to_MAIN2MCU_LVL_INTRTR0_in_238_241,
};
static const struct Sciclient_rmIrqNode tisci_irq_DSS_EDP0 = {
	.id = TISCI_DEV_DSS_EDP0,
	.n_if = 1,
	.p_if = &tisci_if_DSS_EDP0[0],
};

/* Start of DSS0 interface definition */
const struct Sciclient_rmIrqIf DSS0_dss_inst0_dispc_func_irq_proc0_0_0_to_MAIN2MCU_LVL_INTRTR0_in_226_226 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 226,
};
const struct Sciclient_rmIrqIf DSS0_dss_inst0_dispc_func_irq_proc1_1_1_to_MAIN2MCU_LVL_INTRTR0_in_227_227 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 227,
};
const struct Sciclient_rmIrqIf DSS0_dss_inst0_dispc_secure_irq_proc0_4_4_to_MAIN2MCU_LVL_INTRTR0_in_228_228 = {
	.lbase = 4,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 228,
};
const struct Sciclient_rmIrqIf DSS0_dss_inst0_dispc_secure_irq_proc1_5_5_to_MAIN2MCU_LVL_INTRTR0_in_229_229 = {
	.lbase = 5,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 229,
};
const struct Sciclient_rmIrqIf DSS0_dss_inst0_dispc_safety_error_irq_proc0_2_2_to_MAIN2MCU_LVL_INTRTR0_in_230_230 = {
	.lbase = 2,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 230,
};
const struct Sciclient_rmIrqIf DSS0_dss_inst0_dispc_safety_error_irq_proc1_3_3_to_MAIN2MCU_LVL_INTRTR0_in_231_231 = {
	.lbase = 3,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 231,
};
const struct Sciclient_rmIrqIf * const tisci_if_DSS0[] = {
	&DSS0_dss_inst0_dispc_func_irq_proc0_0_0_to_MAIN2MCU_LVL_INTRTR0_in_226_226,
	&DSS0_dss_inst0_dispc_func_irq_proc1_1_1_to_MAIN2MCU_LVL_INTRTR0_in_227_227,
	&DSS0_dss_inst0_dispc_secure_irq_proc0_4_4_to_MAIN2MCU_LVL_INTRTR0_in_228_228,
	&DSS0_dss_inst0_dispc_secure_irq_proc1_5_5_to_MAIN2MCU_LVL_INTRTR0_in_229_229,
	&DSS0_dss_inst0_dispc_safety_error_irq_proc0_2_2_to_MAIN2MCU_LVL_INTRTR0_in_230_230,
	&DSS0_dss_inst0_dispc_safety_error_irq_proc1_3_3_to_MAIN2MCU_LVL_INTRTR0_in_231_231,
};
static const struct Sciclient_rmIrqNode tisci_irq_DSS0 = {
	.id = TISCI_DEV_DSS0,
	.n_if = 6,
	.p_if = &tisci_if_DSS0[0],
};

/* Start of EPWM0 interface definition */
const struct Sciclient_rmIrqIf EPWM0_epwm_etint_0_0_to_MAIN2MCU_PLS_INTRTR0_in_2_2 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 2,
};
const struct Sciclient_rmIrqIf EPWM0_epwm_tripzint_1_1_to_MAIN2MCU_PLS_INTRTR0_in_8_8 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 8,
};
const struct Sciclient_rmIrqIf * const tisci_if_EPWM0[] = {
	&EPWM0_epwm_etint_0_0_to_MAIN2MCU_PLS_INTRTR0_in_2_2,
	&EPWM0_epwm_tripzint_1_1_to_MAIN2MCU_PLS_INTRTR0_in_8_8,
};
static const struct Sciclient_rmIrqNode tisci_irq_EPWM0 = {
	.id = TISCI_DEV_EPWM0,
	.n_if = 2,
	.p_if = &tisci_if_EPWM0[0],
};

/* Start of EPWM1 interface definition */
const struct Sciclient_rmIrqIf EPWM1_epwm_etint_0_0_to_MAIN2MCU_PLS_INTRTR0_in_3_3 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 3,
};
const struct Sciclient_rmIrqIf EPWM1_epwm_tripzint_1_1_to_MAIN2MCU_PLS_INTRTR0_in_9_9 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 9,
};
const struct Sciclient_rmIrqIf * const tisci_if_EPWM1[] = {
	&EPWM1_epwm_etint_0_0_to_MAIN2MCU_PLS_INTRTR0_in_3_3,
	&EPWM1_epwm_tripzint_1_1_to_MAIN2MCU_PLS_INTRTR0_in_9_9,
};
static const struct Sciclient_rmIrqNode tisci_irq_EPWM1 = {
	.id = TISCI_DEV_EPWM1,
	.n_if = 2,
	.p_if = &tisci_if_EPWM1[0],
};

/* Start of EPWM2 interface definition */
const struct Sciclient_rmIrqIf EPWM2_epwm_etint_0_0_to_MAIN2MCU_PLS_INTRTR0_in_4_4 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 4,
};
const struct Sciclient_rmIrqIf EPWM2_epwm_tripzint_1_1_to_MAIN2MCU_PLS_INTRTR0_in_10_10 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 10,
};
const struct Sciclient_rmIrqIf * const tisci_if_EPWM2[] = {
	&EPWM2_epwm_etint_0_0_to_MAIN2MCU_PLS_INTRTR0_in_4_4,
	&EPWM2_epwm_tripzint_1_1_to_MAIN2MCU_PLS_INTRTR0_in_10_10,
};
static const struct Sciclient_rmIrqNode tisci_irq_EPWM2 = {
	.id = TISCI_DEV_EPWM2,
	.n_if = 2,
	.p_if = &tisci_if_EPWM2[0],
};

/* Start of EPWM3 interface definition */
const struct Sciclient_rmIrqIf EPWM3_epwm_etint_0_0_to_MAIN2MCU_PLS_INTRTR0_in_5_5 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 5,
};
const struct Sciclient_rmIrqIf EPWM3_epwm_tripzint_1_1_to_MAIN2MCU_PLS_INTRTR0_in_11_11 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 11,
};
const struct Sciclient_rmIrqIf * const tisci_if_EPWM3[] = {
	&EPWM3_epwm_etint_0_0_to_MAIN2MCU_PLS_INTRTR0_in_5_5,
	&EPWM3_epwm_tripzint_1_1_to_MAIN2MCU_PLS_INTRTR0_in_11_11,
};
static const struct Sciclient_rmIrqNode tisci_irq_EPWM3 = {
	.id = TISCI_DEV_EPWM3,
	.n_if = 2,
	.p_if = &tisci_if_EPWM3[0],
};

/* Start of EPWM4 interface definition */
const struct Sciclient_rmIrqIf EPWM4_epwm_etint_0_0_to_MAIN2MCU_PLS_INTRTR0_in_6_6 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 6,
};
const struct Sciclient_rmIrqIf EPWM4_epwm_tripzint_1_1_to_MAIN2MCU_PLS_INTRTR0_in_12_12 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 12,
};
const struct Sciclient_rmIrqIf * const tisci_if_EPWM4[] = {
	&EPWM4_epwm_etint_0_0_to_MAIN2MCU_PLS_INTRTR0_in_6_6,
	&EPWM4_epwm_tripzint_1_1_to_MAIN2MCU_PLS_INTRTR0_in_12_12,
};
static const struct Sciclient_rmIrqNode tisci_irq_EPWM4 = {
	.id = TISCI_DEV_EPWM4,
	.n_if = 2,
	.p_if = &tisci_if_EPWM4[0],
};

/* Start of EPWM5 interface definition */
const struct Sciclient_rmIrqIf EPWM5_epwm_etint_0_0_to_MAIN2MCU_PLS_INTRTR0_in_7_7 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 7,
};
const struct Sciclient_rmIrqIf EPWM5_epwm_tripzint_1_1_to_MAIN2MCU_PLS_INTRTR0_in_13_13 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 13,
};
const struct Sciclient_rmIrqIf * const tisci_if_EPWM5[] = {
	&EPWM5_epwm_etint_0_0_to_MAIN2MCU_PLS_INTRTR0_in_7_7,
	&EPWM5_epwm_tripzint_1_1_to_MAIN2MCU_PLS_INTRTR0_in_13_13,
};
static const struct Sciclient_rmIrqNode tisci_irq_EPWM5 = {
	.id = TISCI_DEV_EPWM5,
	.n_if = 2,
	.p_if = &tisci_if_EPWM5[0],
};

/* Start of CODEC0 interface definition */
const struct Sciclient_rmIrqIf CODEC0_vpu_wave521cl_intr_0_0_to_MAIN2MCU_LVL_INTRTR0_in_263_263 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 263,
};
const struct Sciclient_rmIrqIf * const tisci_if_CODEC0[] = {
	&CODEC0_vpu_wave521cl_intr_0_0_to_MAIN2MCU_LVL_INTRTR0_in_263_263,
};
static const struct Sciclient_rmIrqNode tisci_irq_CODEC0 = {
	.id = TISCI_DEV_CODEC0,
	.n_if = 1,
	.p_if = &tisci_if_CODEC0[0],
};

/* Start of CODEC1 interface definition */
const struct Sciclient_rmIrqIf CODEC1_vpu_wave521cl_intr_0_0_to_MAIN2MCU_LVL_INTRTR0_in_264_264 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 264,
};
const struct Sciclient_rmIrqIf * const tisci_if_CODEC1[] = {
	&CODEC1_vpu_wave521cl_intr_0_0_to_MAIN2MCU_LVL_INTRTR0_in_264_264,
};
static const struct Sciclient_rmIrqNode tisci_irq_CODEC1 = {
	.id = TISCI_DEV_CODEC1,
	.n_if = 1,
	.p_if = &tisci_if_CODEC1[0],
};

/* Start of MCAN0 interface definition */
const struct Sciclient_rmIrqIf MCAN0_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_16_17 = {
	.lbase = 1,
	.len = 2,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 16,
};
const struct Sciclient_rmIrqIf MCAN0_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_18_18 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 18,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCAN0[] = {
	&MCAN0_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_16_17,
	&MCAN0_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_18_18,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCAN0 = {
	.id = TISCI_DEV_MCAN0,
	.n_if = 2,
	.p_if = &tisci_if_MCAN0[0],
};

/* Start of MCAN1 interface definition */
const struct Sciclient_rmIrqIf MCAN1_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_19_20 = {
	.lbase = 1,
	.len = 2,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 19,
};
const struct Sciclient_rmIrqIf MCAN1_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_21_21 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 21,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCAN1[] = {
	&MCAN1_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_19_20,
	&MCAN1_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_21_21,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCAN1 = {
	.id = TISCI_DEV_MCAN1,
	.n_if = 2,
	.p_if = &tisci_if_MCAN1[0],
};

/* Start of MCAN2 interface definition */
const struct Sciclient_rmIrqIf MCAN2_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_22_23 = {
	.lbase = 1,
	.len = 2,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 22,
};
const struct Sciclient_rmIrqIf MCAN2_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_24_24 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 24,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCAN2[] = {
	&MCAN2_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_22_23,
	&MCAN2_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_24_24,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCAN2 = {
	.id = TISCI_DEV_MCAN2,
	.n_if = 2,
	.p_if = &tisci_if_MCAN2[0],
};

/* Start of MCAN3 interface definition */
const struct Sciclient_rmIrqIf MCAN3_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_25_26 = {
	.lbase = 1,
	.len = 2,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 25,
};
const struct Sciclient_rmIrqIf MCAN3_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_27_27 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 27,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCAN3[] = {
	&MCAN3_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_25_26,
	&MCAN3_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_27_27,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCAN3 = {
	.id = TISCI_DEV_MCAN3,
	.n_if = 2,
	.p_if = &tisci_if_MCAN3[0],
};

/* Start of MCAN4 interface definition */
const struct Sciclient_rmIrqIf MCAN4_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_278_279 = {
	.lbase = 1,
	.len = 2,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 278,
};
const struct Sciclient_rmIrqIf MCAN4_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_280_280 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 280,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCAN4[] = {
	&MCAN4_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_278_279,
	&MCAN4_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_280_280,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCAN4 = {
	.id = TISCI_DEV_MCAN4,
	.n_if = 2,
	.p_if = &tisci_if_MCAN4[0],
};

/* Start of MCAN5 interface definition */
const struct Sciclient_rmIrqIf MCAN5_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_281_282 = {
	.lbase = 1,
	.len = 2,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 281,
};
const struct Sciclient_rmIrqIf MCAN5_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_283_283 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 283,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCAN5[] = {
	&MCAN5_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_281_282,
	&MCAN5_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_283_283,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCAN5 = {
	.id = TISCI_DEV_MCAN5,
	.n_if = 2,
	.p_if = &tisci_if_MCAN5[0],
};

/* Start of MCAN6 interface definition */
const struct Sciclient_rmIrqIf MCAN6_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_284_285 = {
	.lbase = 1,
	.len = 2,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 284,
};
const struct Sciclient_rmIrqIf MCAN6_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_286_286 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 286,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCAN6[] = {
	&MCAN6_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_284_285,
	&MCAN6_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_286_286,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCAN6 = {
	.id = TISCI_DEV_MCAN6,
	.n_if = 2,
	.p_if = &tisci_if_MCAN6[0],
};

/* Start of MCAN7 interface definition */
const struct Sciclient_rmIrqIf MCAN7_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_287_288 = {
	.lbase = 1,
	.len = 2,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 287,
};
const struct Sciclient_rmIrqIf MCAN7_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_289_289 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 289,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCAN7[] = {
	&MCAN7_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_287_288,
	&MCAN7_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_289_289,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCAN7 = {
	.id = TISCI_DEV_MCAN7,
	.n_if = 2,
	.p_if = &tisci_if_MCAN7[0],
};

/* Start of MCAN8 interface definition */
const struct Sciclient_rmIrqIf MCAN8_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_290_291 = {
	.lbase = 1,
	.len = 2,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 290,
};
const struct Sciclient_rmIrqIf MCAN8_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_292_292 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 292,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCAN8[] = {
	&MCAN8_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_290_291,
	&MCAN8_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_292_292,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCAN8 = {
	.id = TISCI_DEV_MCAN8,
	.n_if = 2,
	.p_if = &tisci_if_MCAN8[0],
};

/* Start of MCAN9 interface definition */
const struct Sciclient_rmIrqIf MCAN9_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_293_294 = {
	.lbase = 1,
	.len = 2,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 293,
};
const struct Sciclient_rmIrqIf MCAN9_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_295_295 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 295,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCAN9[] = {
	&MCAN9_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_293_294,
	&MCAN9_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_295_295,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCAN9 = {
	.id = TISCI_DEV_MCAN9,
	.n_if = 2,
	.p_if = &tisci_if_MCAN9[0],
};

/* Start of MCAN10 interface definition */
const struct Sciclient_rmIrqIf MCAN10_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_296_297 = {
	.lbase = 1,
	.len = 2,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 296,
};
const struct Sciclient_rmIrqIf MCAN10_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_298_298 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 298,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCAN10[] = {
	&MCAN10_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_296_297,
	&MCAN10_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_298_298,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCAN10 = {
	.id = TISCI_DEV_MCAN10,
	.n_if = 2,
	.p_if = &tisci_if_MCAN10[0],
};

/* Start of MCAN11 interface definition */
const struct Sciclient_rmIrqIf MCAN11_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_299_300 = {
	.lbase = 1,
	.len = 2,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 299,
};
const struct Sciclient_rmIrqIf MCAN11_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_301_301 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 301,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCAN11[] = {
	&MCAN11_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_299_300,
	&MCAN11_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_301_301,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCAN11 = {
	.id = TISCI_DEV_MCAN11,
	.n_if = 2,
	.p_if = &tisci_if_MCAN11[0],
};

/* Start of MCAN12 interface definition */
const struct Sciclient_rmIrqIf MCAN12_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_302_303 = {
	.lbase = 1,
	.len = 2,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 302,
};
const struct Sciclient_rmIrqIf MCAN12_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_304_304 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 304,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCAN12[] = {
	&MCAN12_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_302_303,
	&MCAN12_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_304_304,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCAN12 = {
	.id = TISCI_DEV_MCAN12,
	.n_if = 2,
	.p_if = &tisci_if_MCAN12[0],
};

/* Start of MCAN13 interface definition */
const struct Sciclient_rmIrqIf MCAN13_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_305_306 = {
	.lbase = 1,
	.len = 2,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 305,
};
const struct Sciclient_rmIrqIf MCAN13_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_307_307 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 307,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCAN13[] = {
	&MCAN13_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_305_306,
	&MCAN13_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_307_307,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCAN13 = {
	.id = TISCI_DEV_MCAN13,
	.n_if = 2,
	.p_if = &tisci_if_MCAN13[0],
};

/* Start of MCAN14 interface definition */
const struct Sciclient_rmIrqIf MCAN14_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_160_161 = {
	.lbase = 1,
	.len = 2,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 160,
};
const struct Sciclient_rmIrqIf MCAN14_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_162_162 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 162,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCAN14[] = {
	&MCAN14_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_160_161,
	&MCAN14_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_162_162,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCAN14 = {
	.id = TISCI_DEV_MCAN14,
	.n_if = 2,
	.p_if = &tisci_if_MCAN14[0],
};

/* Start of MCAN15 interface definition */
const struct Sciclient_rmIrqIf MCAN15_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_163_164 = {
	.lbase = 1,
	.len = 2,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 163,
};
const struct Sciclient_rmIrqIf MCAN15_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_165_165 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 165,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCAN15[] = {
	&MCAN15_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_163_164,
	&MCAN15_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_165_165,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCAN15 = {
	.id = TISCI_DEV_MCAN15,
	.n_if = 2,
	.p_if = &tisci_if_MCAN15[0],
};

/* Start of MCAN16 interface definition */
const struct Sciclient_rmIrqIf MCAN16_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_170_171 = {
	.lbase = 1,
	.len = 2,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 170,
};
const struct Sciclient_rmIrqIf MCAN16_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_172_172 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 172,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCAN16[] = {
	&MCAN16_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_170_171,
	&MCAN16_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_172_172,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCAN16 = {
	.id = TISCI_DEV_MCAN16,
	.n_if = 2,
	.p_if = &tisci_if_MCAN16[0],
};

/* Start of MCAN17 interface definition */
const struct Sciclient_rmIrqIf MCAN17_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_173_174 = {
	.lbase = 1,
	.len = 2,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 173,
};
const struct Sciclient_rmIrqIf MCAN17_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_175_175 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 175,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCAN17[] = {
	&MCAN17_mcanss_mcan_lvl_int_1_2_to_MAIN2MCU_LVL_INTRTR0_in_173_174,
	&MCAN17_mcanss_ext_ts_rollover_lvl_int_0_0_to_MAIN2MCU_LVL_INTRTR0_in_175_175,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCAN17 = {
	.id = TISCI_DEV_MCAN17,
	.n_if = 2,
	.p_if = &tisci_if_MCAN17[0],
};

/* Start of MCASP0 interface definition */
const struct Sciclient_rmIrqIf MCASP0_xmit_intr_pend_1_1_to_MAIN2MCU_LVL_INTRTR0_in_176_176 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 176,
};
const struct Sciclient_rmIrqIf MCASP0_rec_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_177_177 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 177,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCASP0[] = {
	&MCASP0_xmit_intr_pend_1_1_to_MAIN2MCU_LVL_INTRTR0_in_176_176,
	&MCASP0_rec_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_177_177,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCASP0 = {
	.id = TISCI_DEV_MCASP0,
	.n_if = 2,
	.p_if = &tisci_if_MCASP0[0],
};

/* Start of MCASP1 interface definition */
const struct Sciclient_rmIrqIf MCASP1_xmit_intr_pend_1_1_to_MAIN2MCU_LVL_INTRTR0_in_178_178 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 178,
};
const struct Sciclient_rmIrqIf MCASP1_rec_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_179_179 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 179,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCASP1[] = {
	&MCASP1_xmit_intr_pend_1_1_to_MAIN2MCU_LVL_INTRTR0_in_178_178,
	&MCASP1_rec_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_179_179,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCASP1 = {
	.id = TISCI_DEV_MCASP1,
	.n_if = 2,
	.p_if = &tisci_if_MCASP1[0],
};

/* Start of MCASP2 interface definition */
const struct Sciclient_rmIrqIf MCASP2_xmit_intr_pend_1_1_to_MAIN2MCU_LVL_INTRTR0_in_180_180 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 180,
};
const struct Sciclient_rmIrqIf MCASP2_rec_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_181_181 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 181,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCASP2[] = {
	&MCASP2_xmit_intr_pend_1_1_to_MAIN2MCU_LVL_INTRTR0_in_180_180,
	&MCASP2_rec_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_181_181,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCASP2 = {
	.id = TISCI_DEV_MCASP2,
	.n_if = 2,
	.p_if = &tisci_if_MCASP2[0],
};

/* Start of MCASP3 interface definition */
const struct Sciclient_rmIrqIf MCASP3_xmit_intr_pend_1_1_to_MAIN2MCU_LVL_INTRTR0_in_182_182 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 182,
};
const struct Sciclient_rmIrqIf MCASP3_rec_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_183_183 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 183,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCASP3[] = {
	&MCASP3_xmit_intr_pend_1_1_to_MAIN2MCU_LVL_INTRTR0_in_182_182,
	&MCASP3_rec_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_183_183,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCASP3 = {
	.id = TISCI_DEV_MCASP3,
	.n_if = 2,
	.p_if = &tisci_if_MCASP3[0],
};

/* Start of MCASP4 interface definition */
const struct Sciclient_rmIrqIf MCASP4_xmit_intr_pend_1_1_to_MAIN2MCU_LVL_INTRTR0_in_184_184 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 184,
};
const struct Sciclient_rmIrqIf MCASP4_rec_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_185_185 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 185,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCASP4[] = {
	&MCASP4_xmit_intr_pend_1_1_to_MAIN2MCU_LVL_INTRTR0_in_184_184,
	&MCASP4_rec_intr_pend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_185_185,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCASP4 = {
	.id = TISCI_DEV_MCASP4,
	.n_if = 2,
	.p_if = &tisci_if_MCASP4[0],
};

/* Start of I2C0 interface definition */
const struct Sciclient_rmIrqIf I2C0_pointrpend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_56_56 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 56,
};
const struct Sciclient_rmIrqIf * const tisci_if_I2C0[] = {
	&I2C0_pointrpend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_56_56,
};
static const struct Sciclient_rmIrqNode tisci_irq_I2C0 = {
	.id = TISCI_DEV_I2C0,
	.n_if = 1,
	.p_if = &tisci_if_I2C0[0],
};

/* Start of I2C1 interface definition */
const struct Sciclient_rmIrqIf I2C1_pointrpend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_57_57 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 57,
};
const struct Sciclient_rmIrqIf * const tisci_if_I2C1[] = {
	&I2C1_pointrpend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_57_57,
};
static const struct Sciclient_rmIrqNode tisci_irq_I2C1 = {
	.id = TISCI_DEV_I2C1,
	.n_if = 1,
	.p_if = &tisci_if_I2C1[0],
};

/* Start of I2C2 interface definition */
const struct Sciclient_rmIrqIf I2C2_pointrpend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_58_58 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 58,
};
const struct Sciclient_rmIrqIf * const tisci_if_I2C2[] = {
	&I2C2_pointrpend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_58_58,
};
static const struct Sciclient_rmIrqNode tisci_irq_I2C2 = {
	.id = TISCI_DEV_I2C2,
	.n_if = 1,
	.p_if = &tisci_if_I2C2[0],
};

/* Start of I2C3 interface definition */
const struct Sciclient_rmIrqIf I2C3_pointrpend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_59_59 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 59,
};
const struct Sciclient_rmIrqIf * const tisci_if_I2C3[] = {
	&I2C3_pointrpend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_59_59,
};
static const struct Sciclient_rmIrqNode tisci_irq_I2C3 = {
	.id = TISCI_DEV_I2C3,
	.n_if = 1,
	.p_if = &tisci_if_I2C3[0],
};

/* Start of I2C4 interface definition */
const struct Sciclient_rmIrqIf I2C4_pointrpend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_60_60 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 60,
};
const struct Sciclient_rmIrqIf * const tisci_if_I2C4[] = {
	&I2C4_pointrpend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_60_60,
};
static const struct Sciclient_rmIrqNode tisci_irq_I2C4 = {
	.id = TISCI_DEV_I2C4,
	.n_if = 1,
	.p_if = &tisci_if_I2C4[0],
};

/* Start of I2C5 interface definition */
const struct Sciclient_rmIrqIf I2C5_pointrpend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_61_61 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 61,
};
const struct Sciclient_rmIrqIf * const tisci_if_I2C5[] = {
	&I2C5_pointrpend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_61_61,
};
static const struct Sciclient_rmIrqNode tisci_irq_I2C5 = {
	.id = TISCI_DEV_I2C5,
	.n_if = 1,
	.p_if = &tisci_if_I2C5[0],
};

/* Start of I2C6 interface definition */
const struct Sciclient_rmIrqIf I2C6_pointrpend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_62_62 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 62,
};
const struct Sciclient_rmIrqIf * const tisci_if_I2C6[] = {
	&I2C6_pointrpend_0_0_to_MAIN2MCU_LVL_INTRTR0_in_62_62,
};
static const struct Sciclient_rmIrqNode tisci_irq_I2C6 = {
	.id = TISCI_DEV_I2C6,
	.n_if = 1,
	.p_if = &tisci_if_I2C6[0],
};

/* Start of NAVSS0 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_cpts0_comp_0_0_to_CMPEVENT_INTRTR0_in_8_8 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_CMPEVENT_INTRTR0,
	.rbase = 8,
};
const struct Sciclient_rmIrqIf NAVSS0_cpts0_genf0_1_1_to_TIMESYNC_INTRTR0_in_4_4 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 4,
};
const struct Sciclient_rmIrqIf NAVSS0_cpts0_genf1_2_2_to_TIMESYNC_INTRTR0_in_5_5 = {
	.lbase = 2,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 5,
};
const struct Sciclient_rmIrqIf NAVSS0_cpts0_genf2_3_3_to_TIMESYNC_INTRTR0_in_6_6 = {
	.lbase = 3,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 6,
};
const struct Sciclient_rmIrqIf NAVSS0_cpts0_genf3_4_4_to_TIMESYNC_INTRTR0_in_7_7 = {
	.lbase = 4,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 7,
};
const struct Sciclient_rmIrqIf NAVSS0_cpts0_genf4_5_5_to_TIMESYNC_INTRTR0_in_8_8 = {
	.lbase = 5,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 8,
};
const struct Sciclient_rmIrqIf NAVSS0_cpts0_genf5_6_6_to_TIMESYNC_INTRTR0_in_9_9 = {
	.lbase = 6,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 9,
};
const struct Sciclient_rmIrqIf NAVSS0_cpts0_sync_7_7_to_TIMESYNC_INTRTR0_in_36_36 = {
	.lbase = 7,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 36,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0[] = {
	&NAVSS0_cpts0_comp_0_0_to_CMPEVENT_INTRTR0_in_8_8,
	&NAVSS0_cpts0_genf0_1_1_to_TIMESYNC_INTRTR0_in_4_4,
	&NAVSS0_cpts0_genf1_2_2_to_TIMESYNC_INTRTR0_in_5_5,
	&NAVSS0_cpts0_genf2_3_3_to_TIMESYNC_INTRTR0_in_6_6,
	&NAVSS0_cpts0_genf3_4_4_to_TIMESYNC_INTRTR0_in_7_7,
	&NAVSS0_cpts0_genf4_5_5_to_TIMESYNC_INTRTR0_in_8_8,
	&NAVSS0_cpts0_genf5_6_6_to_TIMESYNC_INTRTR0_in_9_9,
	&NAVSS0_cpts0_sync_7_7_to_TIMESYNC_INTRTR0_in_36_36,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0 = {
	.id = TISCI_DEV_NAVSS0,
	.n_if = 8,
	.p_if = &tisci_if_NAVSS0[0],
};

/* Start of NAVSS0_CPTS_0 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_CPTS_0_event_pend_intr_0_0_to_NAVSS0_INTR_0_in_intr_391_391 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 391,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_CPTS_0[] = {
	&NAVSS0_CPTS_0_event_pend_intr_0_0_to_NAVSS0_INTR_0_in_intr_391_391,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_CPTS_0 = {
	.id = TISCI_DEV_NAVSS0_CPTS_0,
	.n_if = 1,
	.p_if = &tisci_if_NAVSS0_CPTS_0[0],
};

/* Start of NAVSS0_INTR_0 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_INTR_0_outl_intr_0_63_to_COMPUTE_CLUSTER0_CLEC_soc_events_in_64_127 = {
	.lbase = 0,
	.len = 64,
	.rid = TISCI_DEV_COMPUTE_CLUSTER0_CLEC,
	.rbase = 64,
};
const struct Sciclient_rmIrqIf NAVSS0_INTR_0_outl_intr_64_127_to_COMPUTE_CLUSTER0_CLEC_soc_events_in_448_511 = {
	.lbase = 64,
	.len = 64,
	.rid = TISCI_DEV_COMPUTE_CLUSTER0_CLEC,
	.rbase = 448,
};
const struct Sciclient_rmIrqIf NAVSS0_INTR_0_outl_intr_128_191_to_COMPUTE_CLUSTER0_CLEC_soc_events_in_672_735 = {
	.lbase = 128,
	.len = 64,
	.rid = TISCI_DEV_COMPUTE_CLUSTER0_CLEC,
	.rbase = 672,
};
const struct Sciclient_rmIrqIf NAVSS0_INTR_0_outl_intr_0_63_to_COMPUTE_CLUSTER0_GIC500SS_spi_64_127 = {
	.lbase = 0,
	.len = 64,
	.rid = TISCI_DEV_COMPUTE_CLUSTER0_GIC500SS,
	.rbase = 64,
};
const struct Sciclient_rmIrqIf NAVSS0_INTR_0_outl_intr_64_127_to_COMPUTE_CLUSTER0_GIC500SS_spi_448_511 = {
	.lbase = 64,
	.len = 64,
	.rid = TISCI_DEV_COMPUTE_CLUSTER0_GIC500SS,
	.rbase = 448,
};
const struct Sciclient_rmIrqIf NAVSS0_INTR_0_outl_intr_128_191_to_COMPUTE_CLUSTER0_GIC500SS_spi_672_735 = {
	.lbase = 128,
	.len = 64,
	.rid = TISCI_DEV_COMPUTE_CLUSTER0_GIC500SS,
	.rbase = 672,
};
const struct Sciclient_rmIrqIf NAVSS0_INTR_0_outl_intr_192_223_to_R5FSS0_CORE0_intr_224_255 = {
	.lbase = 192,
	.len = 32,
	.rid = TISCI_DEV_R5FSS0_CORE0,
	.rbase = 224,
};
const struct Sciclient_rmIrqIf NAVSS0_INTR_0_outl_intr_224_255_to_R5FSS0_CORE1_intr_224_255 = {
	.lbase = 224,
	.len = 32,
	.rid = TISCI_DEV_R5FSS0_CORE1,
	.rbase = 224,
};
const struct Sciclient_rmIrqIf NAVSS0_INTR_0_outl_intr_256_287_to_R5FSS1_CORE0_intr_224_255 = {
	.lbase = 256,
	.len = 32,
	.rid = TISCI_DEV_R5FSS1_CORE0,
	.rbase = 224,
};
const struct Sciclient_rmIrqIf NAVSS0_INTR_0_outl_intr_288_319_to_R5FSS1_CORE1_intr_224_255 = {
	.lbase = 288,
	.len = 32,
	.rid = TISCI_DEV_R5FSS1_CORE1,
	.rbase = 224,
};
const struct Sciclient_rmIrqIf NAVSS0_INTR_0_outl_intr_320_351_to_R5FSS2_CORE0_intr_224_255 = {
	.lbase = 320,
	.len = 32,
	.rid = TISCI_DEV_R5FSS2_CORE0,
	.rbase = 224,
};
const struct Sciclient_rmIrqIf NAVSS0_INTR_0_outl_intr_352_383_to_R5FSS2_CORE1_intr_224_255 = {
	.lbase = 352,
	.len = 32,
	.rid = TISCI_DEV_R5FSS2_CORE1,
	.rbase = 224,
};
const struct Sciclient_rmIrqIf NAVSS0_INTR_0_outl_intr_400_407_to_MCU_R5FSS0_CORE0_intr_376_383 = {
	.lbase = 400,
	.len = 8,
	.rid = TISCI_DEV_MCU_R5FSS0_CORE0,
	.rbase = 376,
};
const struct Sciclient_rmIrqIf NAVSS0_INTR_0_outl_intr_400_407_to_MCU_R5FSS0_CORE1_intr_376_383 = {
	.lbase = 400,
	.len = 8,
	.rid = TISCI_DEV_MCU_R5FSS0_CORE1,
	.rbase = 376,
};
const struct Sciclient_rmIrqIf NAVSS0_INTR_0_outl_intr_408_439_to_vusr_dual0_v0_vusr_in_int_0_31 = {
	.lbase = 408,
	.len = 32,
	.rid = TISCI_DEV_VUSR_DUAL0,
	.rbase = 0,
};
const struct Sciclient_rmIrqIf NAVSS0_INTR_0_outl_intr_408_439_to_vusr_dual0_v1_vusr_in_int_32_63 = {
	.lbase = 408,
	.len = 32,
	.rid = TISCI_DEV_VUSR_DUAL0,
	.rbase = 32,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_INTR_0[] = {
	&NAVSS0_INTR_0_outl_intr_0_63_to_COMPUTE_CLUSTER0_CLEC_soc_events_in_64_127,
	&NAVSS0_INTR_0_outl_intr_64_127_to_COMPUTE_CLUSTER0_CLEC_soc_events_in_448_511,
	&NAVSS0_INTR_0_outl_intr_128_191_to_COMPUTE_CLUSTER0_CLEC_soc_events_in_672_735,
	&NAVSS0_INTR_0_outl_intr_0_63_to_COMPUTE_CLUSTER0_GIC500SS_spi_64_127,
	&NAVSS0_INTR_0_outl_intr_64_127_to_COMPUTE_CLUSTER0_GIC500SS_spi_448_511,
	&NAVSS0_INTR_0_outl_intr_128_191_to_COMPUTE_CLUSTER0_GIC500SS_spi_672_735,
	&NAVSS0_INTR_0_outl_intr_192_223_to_R5FSS0_CORE0_intr_224_255,
	&NAVSS0_INTR_0_outl_intr_224_255_to_R5FSS0_CORE1_intr_224_255,
	&NAVSS0_INTR_0_outl_intr_256_287_to_R5FSS1_CORE0_intr_224_255,
	&NAVSS0_INTR_0_outl_intr_288_319_to_R5FSS1_CORE1_intr_224_255,
	&NAVSS0_INTR_0_outl_intr_320_351_to_R5FSS2_CORE0_intr_224_255,
	&NAVSS0_INTR_0_outl_intr_352_383_to_R5FSS2_CORE1_intr_224_255,
	&NAVSS0_INTR_0_outl_intr_400_407_to_MCU_R5FSS0_CORE0_intr_376_383,
	&NAVSS0_INTR_0_outl_intr_400_407_to_MCU_R5FSS0_CORE1_intr_376_383,
	&NAVSS0_INTR_0_outl_intr_408_439_to_vusr_dual0_v0_vusr_in_int_0_31,
	&NAVSS0_INTR_0_outl_intr_408_439_to_vusr_dual0_v1_vusr_in_int_32_63,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_INTR_0 = {
	.id = TISCI_DEV_NAVSS0_INTR_0,
	.n_if = 16,
	.p_if = &tisci_if_NAVSS0_INTR_0[0],
};

/* Start of NAVSS0_MAILBOX1_0 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX1_0_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_484_487 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 484,
};
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX1_0_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_4_7 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_UDMASS_INTA_0,
	.rbase = 4,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_MAILBOX1_0[] = {
	&NAVSS0_MAILBOX1_0_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_484_487,
	&NAVSS0_MAILBOX1_0_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_4_7,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_MAILBOX1_0 = {
	.id = TISCI_DEV_NAVSS0_MAILBOX1_0,
	.n_if = 2,
	.p_if = &tisci_if_NAVSS0_MAILBOX1_0[0],
};

/* Start of NAVSS0_MAILBOX1_1 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX1_1_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_480_483 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 480,
};
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX1_1_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_8_11 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_UDMASS_INTA_0,
	.rbase = 8,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_MAILBOX1_1[] = {
	&NAVSS0_MAILBOX1_1_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_480_483,
	&NAVSS0_MAILBOX1_1_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_8_11,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_MAILBOX1_1 = {
	.id = TISCI_DEV_NAVSS0_MAILBOX1_1,
	.n_if = 2,
	.p_if = &tisci_if_NAVSS0_MAILBOX1_1[0],
};

/* Start of NAVSS0_MAILBOX1_2 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX1_2_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_476_479 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 476,
};
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX1_2_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_12_15 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_UDMASS_INTA_0,
	.rbase = 12,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_MAILBOX1_2[] = {
	&NAVSS0_MAILBOX1_2_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_476_479,
	&NAVSS0_MAILBOX1_2_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_12_15,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_MAILBOX1_2 = {
	.id = TISCI_DEV_NAVSS0_MAILBOX1_2,
	.n_if = 2,
	.p_if = &tisci_if_NAVSS0_MAILBOX1_2[0],
};

/* Start of NAVSS0_MAILBOX1_3 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX1_3_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_472_475 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 472,
};
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX1_3_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_16_19 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_UDMASS_INTA_0,
	.rbase = 16,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_MAILBOX1_3[] = {
	&NAVSS0_MAILBOX1_3_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_472_475,
	&NAVSS0_MAILBOX1_3_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_16_19,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_MAILBOX1_3 = {
	.id = TISCI_DEV_NAVSS0_MAILBOX1_3,
	.n_if = 2,
	.p_if = &tisci_if_NAVSS0_MAILBOX1_3[0],
};

/* Start of NAVSS0_MAILBOX1_4 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX1_4_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_468_471 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 468,
};
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX1_4_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_20_23 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_UDMASS_INTA_0,
	.rbase = 20,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_MAILBOX1_4[] = {
	&NAVSS0_MAILBOX1_4_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_468_471,
	&NAVSS0_MAILBOX1_4_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_20_23,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_MAILBOX1_4 = {
	.id = TISCI_DEV_NAVSS0_MAILBOX1_4,
	.n_if = 2,
	.p_if = &tisci_if_NAVSS0_MAILBOX1_4[0],
};

/* Start of NAVSS0_MAILBOX1_5 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX1_5_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_464_467 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 464,
};
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX1_5_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_24_27 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_UDMASS_INTA_0,
	.rbase = 24,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_MAILBOX1_5[] = {
	&NAVSS0_MAILBOX1_5_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_464_467,
	&NAVSS0_MAILBOX1_5_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_24_27,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_MAILBOX1_5 = {
	.id = TISCI_DEV_NAVSS0_MAILBOX1_5,
	.n_if = 2,
	.p_if = &tisci_if_NAVSS0_MAILBOX1_5[0],
};

/* Start of NAVSS0_MAILBOX1_6 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX1_6_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_460_463 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 460,
};
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX1_6_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_28_31 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_UDMASS_INTA_0,
	.rbase = 28,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_MAILBOX1_6[] = {
	&NAVSS0_MAILBOX1_6_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_460_463,
	&NAVSS0_MAILBOX1_6_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_28_31,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_MAILBOX1_6 = {
	.id = TISCI_DEV_NAVSS0_MAILBOX1_6,
	.n_if = 2,
	.p_if = &tisci_if_NAVSS0_MAILBOX1_6[0],
};

/* Start of NAVSS0_MAILBOX1_7 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX1_7_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_456_459 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 456,
};
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX1_7_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_32_35 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_UDMASS_INTA_0,
	.rbase = 32,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_MAILBOX1_7[] = {
	&NAVSS0_MAILBOX1_7_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_456_459,
	&NAVSS0_MAILBOX1_7_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_32_35,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_MAILBOX1_7 = {
	.id = TISCI_DEV_NAVSS0_MAILBOX1_7,
	.n_if = 2,
	.p_if = &tisci_if_NAVSS0_MAILBOX1_7[0],
};

/* Start of NAVSS0_MAILBOX1_8 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX1_8_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_452_455 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 452,
};
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX1_8_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_36_39 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_UDMASS_INTA_0,
	.rbase = 36,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_MAILBOX1_8[] = {
	&NAVSS0_MAILBOX1_8_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_452_455,
	&NAVSS0_MAILBOX1_8_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_36_39,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_MAILBOX1_8 = {
	.id = TISCI_DEV_NAVSS0_MAILBOX1_8,
	.n_if = 2,
	.p_if = &tisci_if_NAVSS0_MAILBOX1_8[0],
};

/* Start of NAVSS0_MAILBOX1_9 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX1_9_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_448_451 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 448,
};
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX1_9_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_40_43 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_UDMASS_INTA_0,
	.rbase = 40,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_MAILBOX1_9[] = {
	&NAVSS0_MAILBOX1_9_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_448_451,
	&NAVSS0_MAILBOX1_9_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_40_43,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_MAILBOX1_9 = {
	.id = TISCI_DEV_NAVSS0_MAILBOX1_9,
	.n_if = 2,
	.p_if = &tisci_if_NAVSS0_MAILBOX1_9[0],
};

/* Start of NAVSS0_MAILBOX1_10 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX1_10_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_444_447 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 444,
};
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX1_10_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_44_47 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_UDMASS_INTA_0,
	.rbase = 44,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_MAILBOX1_10[] = {
	&NAVSS0_MAILBOX1_10_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_444_447,
	&NAVSS0_MAILBOX1_10_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_44_47,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_MAILBOX1_10 = {
	.id = TISCI_DEV_NAVSS0_MAILBOX1_10,
	.n_if = 2,
	.p_if = &tisci_if_NAVSS0_MAILBOX1_10[0],
};

/* Start of NAVSS0_MAILBOX1_11 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX1_11_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_440_443 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 440,
};
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX1_11_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_48_51 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_UDMASS_INTA_0,
	.rbase = 48,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_MAILBOX1_11[] = {
	&NAVSS0_MAILBOX1_11_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_440_443,
	&NAVSS0_MAILBOX1_11_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_48_51,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_MAILBOX1_11 = {
	.id = TISCI_DEV_NAVSS0_MAILBOX1_11,
	.n_if = 2,
	.p_if = &tisci_if_NAVSS0_MAILBOX1_11[0],
};

/* Start of NAVSS0_MAILBOX_0 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX_0_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_436_439 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 436,
};
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX_0_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_52_55 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_UDMASS_INTA_0,
	.rbase = 52,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_MAILBOX_0[] = {
	&NAVSS0_MAILBOX_0_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_436_439,
	&NAVSS0_MAILBOX_0_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_52_55,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_MAILBOX_0 = {
	.id = TISCI_DEV_NAVSS0_MAILBOX_0,
	.n_if = 2,
	.p_if = &tisci_if_NAVSS0_MAILBOX_0[0],
};

/* Start of NAVSS0_MAILBOX_1 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX_1_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_432_435 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 432,
};
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX_1_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_56_59 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_UDMASS_INTA_0,
	.rbase = 56,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_MAILBOX_1[] = {
	&NAVSS0_MAILBOX_1_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_432_435,
	&NAVSS0_MAILBOX_1_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_56_59,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_MAILBOX_1 = {
	.id = TISCI_DEV_NAVSS0_MAILBOX_1,
	.n_if = 2,
	.p_if = &tisci_if_NAVSS0_MAILBOX_1[0],
};

/* Start of NAVSS0_MAILBOX_2 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX_2_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_428_431 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 428,
};
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX_2_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_60_63 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_UDMASS_INTA_0,
	.rbase = 60,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_MAILBOX_2[] = {
	&NAVSS0_MAILBOX_2_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_428_431,
	&NAVSS0_MAILBOX_2_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_60_63,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_MAILBOX_2 = {
	.id = TISCI_DEV_NAVSS0_MAILBOX_2,
	.n_if = 2,
	.p_if = &tisci_if_NAVSS0_MAILBOX_2[0],
};

/* Start of NAVSS0_MAILBOX_3 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX_3_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_424_427 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 424,
};
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX_3_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_64_67 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_UDMASS_INTA_0,
	.rbase = 64,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_MAILBOX_3[] = {
	&NAVSS0_MAILBOX_3_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_424_427,
	&NAVSS0_MAILBOX_3_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_64_67,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_MAILBOX_3 = {
	.id = TISCI_DEV_NAVSS0_MAILBOX_3,
	.n_if = 2,
	.p_if = &tisci_if_NAVSS0_MAILBOX_3[0],
};

/* Start of NAVSS0_MAILBOX_4 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX_4_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_420_423 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 420,
};
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX_4_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_68_71 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_UDMASS_INTA_0,
	.rbase = 68,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_MAILBOX_4[] = {
	&NAVSS0_MAILBOX_4_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_420_423,
	&NAVSS0_MAILBOX_4_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_68_71,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_MAILBOX_4 = {
	.id = TISCI_DEV_NAVSS0_MAILBOX_4,
	.n_if = 2,
	.p_if = &tisci_if_NAVSS0_MAILBOX_4[0],
};

/* Start of NAVSS0_MAILBOX_5 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX_5_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_416_419 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 416,
};
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX_5_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_72_75 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_UDMASS_INTA_0,
	.rbase = 72,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_MAILBOX_5[] = {
	&NAVSS0_MAILBOX_5_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_416_419,
	&NAVSS0_MAILBOX_5_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_72_75,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_MAILBOX_5 = {
	.id = TISCI_DEV_NAVSS0_MAILBOX_5,
	.n_if = 2,
	.p_if = &tisci_if_NAVSS0_MAILBOX_5[0],
};

/* Start of NAVSS0_MAILBOX_6 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX_6_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_412_415 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 412,
};
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX_6_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_76_79 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_UDMASS_INTA_0,
	.rbase = 76,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_MAILBOX_6[] = {
	&NAVSS0_MAILBOX_6_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_412_415,
	&NAVSS0_MAILBOX_6_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_76_79,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_MAILBOX_6 = {
	.id = TISCI_DEV_NAVSS0_MAILBOX_6,
	.n_if = 2,
	.p_if = &tisci_if_NAVSS0_MAILBOX_6[0],
};

/* Start of NAVSS0_MAILBOX_7 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX_7_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_408_411 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 408,
};
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX_7_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_80_83 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_UDMASS_INTA_0,
	.rbase = 80,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_MAILBOX_7[] = {
	&NAVSS0_MAILBOX_7_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_408_411,
	&NAVSS0_MAILBOX_7_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_80_83,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_MAILBOX_7 = {
	.id = TISCI_DEV_NAVSS0_MAILBOX_7,
	.n_if = 2,
	.p_if = &tisci_if_NAVSS0_MAILBOX_7[0],
};

/* Start of NAVSS0_MAILBOX_8 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX_8_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_404_407 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 404,
};
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX_8_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_84_87 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_UDMASS_INTA_0,
	.rbase = 84,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_MAILBOX_8[] = {
	&NAVSS0_MAILBOX_8_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_404_407,
	&NAVSS0_MAILBOX_8_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_84_87,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_MAILBOX_8 = {
	.id = TISCI_DEV_NAVSS0_MAILBOX_8,
	.n_if = 2,
	.p_if = &tisci_if_NAVSS0_MAILBOX_8[0],
};

/* Start of NAVSS0_MAILBOX_9 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX_9_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_400_403 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 400,
};
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX_9_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_88_91 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_UDMASS_INTA_0,
	.rbase = 88,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_MAILBOX_9[] = {
	&NAVSS0_MAILBOX_9_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_400_403,
	&NAVSS0_MAILBOX_9_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_88_91,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_MAILBOX_9 = {
	.id = TISCI_DEV_NAVSS0_MAILBOX_9,
	.n_if = 2,
	.p_if = &tisci_if_NAVSS0_MAILBOX_9[0],
};

/* Start of NAVSS0_MAILBOX_10 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX_10_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_396_399 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 396,
};
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX_10_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_92_95 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_UDMASS_INTA_0,
	.rbase = 92,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_MAILBOX_10[] = {
	&NAVSS0_MAILBOX_10_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_396_399,
	&NAVSS0_MAILBOX_10_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_92_95,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_MAILBOX_10 = {
	.id = TISCI_DEV_NAVSS0_MAILBOX_10,
	.n_if = 2,
	.p_if = &tisci_if_NAVSS0_MAILBOX_10[0],
};

/* Start of NAVSS0_MAILBOX_11 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX_11_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_392_395 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 392,
};
const struct Sciclient_rmIrqIf NAVSS0_MAILBOX_11_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_96_99 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_UDMASS_INTA_0,
	.rbase = 96,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_MAILBOX_11[] = {
	&NAVSS0_MAILBOX_11_pend_intr_0_3_to_NAVSS0_INTR_0_in_intr_392_395,
	&NAVSS0_MAILBOX_11_pend_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_96_99,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_MAILBOX_11 = {
	.id = TISCI_DEV_NAVSS0_MAILBOX_11,
	.n_if = 2,
	.p_if = &tisci_if_NAVSS0_MAILBOX_11[0],
};

/* Start of NAVSS0_MCRC_0 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_MCRC_0_dma_event_intr_0_3_to_NAVSS0_INTR_0_in_intr_384_387 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 384,
};
const struct Sciclient_rmIrqIf NAVSS0_MCRC_0_intaggr_vintr_pend_4_4_to_NAVSS0_INTR_0_in_intr_388_388 = {
	.lbase = 4,
	.len = 1,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 388,
};
const struct Sciclient_rmIrqIf NAVSS0_MCRC_0_dma_event_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_0_3 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_NAVSS0_UDMASS_INTA_0,
	.rbase = 0,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_MCRC_0[] = {
	&NAVSS0_MCRC_0_dma_event_intr_0_3_to_NAVSS0_INTR_0_in_intr_384_387,
	&NAVSS0_MCRC_0_intaggr_vintr_pend_4_4_to_NAVSS0_INTR_0_in_intr_388_388,
	&NAVSS0_MCRC_0_dma_event_intr_0_3_to_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_0_3,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_MCRC_0 = {
	.id = TISCI_DEV_NAVSS0_MCRC_0,
	.n_if = 3,
	.p_if = &tisci_if_NAVSS0_MCRC_0[0],
};

/* Start of NAVSS0_MODSS_INTA_0 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_MODSS_INTA_0_intaggr_vintr_pend_0_63_to_NAVSS0_INTR_0_in_intr_320_383 = {
	.lbase = 0,
	.len = 64,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 320,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_MODSS_INTA_0[] = {
	&NAVSS0_MODSS_INTA_0_intaggr_vintr_pend_0_63_to_NAVSS0_INTR_0_in_intr_320_383,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_MODSS_INTA_0 = {
	.id = TISCI_DEV_NAVSS0_MODSS_INTA_0,
	.n_if = 1,
	.p_if = &tisci_if_NAVSS0_MODSS_INTA_0[0],
};

/* Start of NAVSS0_MODSS_INTA_1 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_MODSS_INTA_1_intaggr_vintr_pend_0_63_to_NAVSS0_INTR_0_in_intr_256_319 = {
	.lbase = 0,
	.len = 64,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 256,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_MODSS_INTA_1[] = {
	&NAVSS0_MODSS_INTA_1_intaggr_vintr_pend_0_63_to_NAVSS0_INTR_0_in_intr_256_319,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_MODSS_INTA_1 = {
	.id = TISCI_DEV_NAVSS0_MODSS_INTA_1,
	.n_if = 1,
	.p_if = &tisci_if_NAVSS0_MODSS_INTA_1[0],
};

/* Start of NAVSS0_PVU_0 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_PVU_0_exp_intr_0_0_to_NAVSS0_INTR_0_in_intr_489_489 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 489,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_PVU_0[] = {
	&NAVSS0_PVU_0_exp_intr_0_0_to_NAVSS0_INTR_0_in_intr_489_489,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_PVU_0 = {
	.id = TISCI_DEV_NAVSS0_PVU_0,
	.n_if = 1,
	.p_if = &tisci_if_NAVSS0_PVU_0[0],
};

/* Start of NAVSS0_PVU_1 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_PVU_1_exp_intr_0_0_to_NAVSS0_INTR_0_in_intr_488_488 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 488,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_PVU_1[] = {
	&NAVSS0_PVU_1_exp_intr_0_0_to_NAVSS0_INTR_0_in_intr_488_488,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_PVU_1 = {
	.id = TISCI_DEV_NAVSS0_PVU_1,
	.n_if = 1,
	.p_if = &tisci_if_NAVSS0_PVU_1[0],
};

/* Start of NAVSS0_UDMASS_INTA_0 interface definition */
const struct Sciclient_rmIrqIf NAVSS0_UDMASS_INTA_0_intaggr_vintr_pend_0_255_to_NAVSS0_INTR_0_in_intr_0_255 = {
	.lbase = 0,
	.len = 256,
	.rid = TISCI_DEV_NAVSS0_INTR_0,
	.rbase = 0,
};
const struct Sciclient_rmIrqIf * const tisci_if_NAVSS0_UDMASS_INTA_0[] = {
	&NAVSS0_UDMASS_INTA_0_intaggr_vintr_pend_0_255_to_NAVSS0_INTR_0_in_intr_0_255,
};
static const struct Sciclient_rmIrqNode tisci_irq_NAVSS0_UDMASS_INTA_0 = {
	.id = TISCI_DEV_NAVSS0_UDMASS_INTA_0,
	.n_if = 1,
	.p_if = &tisci_if_NAVSS0_UDMASS_INTA_0[0],
};

/* Start of MCU_NAVSS0_INTR_ROUTER_0 interface definition */
const struct Sciclient_rmIrqIf MCU_NAVSS0_INTR_ROUTER_0_outl_intr_0_23_to_MCU_R5FSS0_CORE0_intr_64_87 = {
	.lbase = 0,
	.len = 24,
	.rid = TISCI_DEV_MCU_R5FSS0_CORE0,
	.rbase = 64,
};
const struct Sciclient_rmIrqIf MCU_NAVSS0_INTR_ROUTER_0_outl_intr_24_31_to_WKUP_HSM0_nvic_48_55 = {
	.lbase = 24,
	.len = 8,
	.rid = TISCI_DEV_WKUP_HSM0,
	.rbase = 48,
};
const struct Sciclient_rmIrqIf MCU_NAVSS0_INTR_ROUTER_0_outl_intr_56_63_to_WKUP_HSM0_nvic_56_63 = {
	.lbase = 56,
	.len = 8,
	.rid = TISCI_DEV_WKUP_HSM0,
	.rbase = 56,
};
const struct Sciclient_rmIrqIf MCU_NAVSS0_INTR_ROUTER_0_outl_intr_32_55_to_MCU_R5FSS0_CORE1_intr_64_87 = {
	.lbase = 32,
	.len = 24,
	.rid = TISCI_DEV_MCU_R5FSS0_CORE1,
	.rbase = 64,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCU_NAVSS0_INTR_ROUTER_0[] = {
	&MCU_NAVSS0_INTR_ROUTER_0_outl_intr_0_23_to_MCU_R5FSS0_CORE0_intr_64_87,
	&MCU_NAVSS0_INTR_ROUTER_0_outl_intr_24_31_to_WKUP_HSM0_nvic_48_55,
	&MCU_NAVSS0_INTR_ROUTER_0_outl_intr_56_63_to_WKUP_HSM0_nvic_56_63,
	&MCU_NAVSS0_INTR_ROUTER_0_outl_intr_32_55_to_MCU_R5FSS0_CORE1_intr_64_87,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCU_NAVSS0_INTR_ROUTER_0 = {
	.id = TISCI_DEV_MCU_NAVSS0_INTR_ROUTER_0,
	.n_if = 4,
	.p_if = &tisci_if_MCU_NAVSS0_INTR_ROUTER_0[0],
};

/* Start of MCU_NAVSS0_MCRC_0 interface definition */
const struct Sciclient_rmIrqIf MCU_NAVSS0_MCRC_0_dma_event_intr_0_3_to_MCU_NAVSS0_INTR_ROUTER_0_in_intr_256_259 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_MCU_NAVSS0_INTR_ROUTER_0,
	.rbase = 256,
};
const struct Sciclient_rmIrqIf MCU_NAVSS0_MCRC_0_intaggr_vintr_pend_4_4_to_MCU_NAVSS0_INTR_ROUTER_0_in_intr_260_260 = {
	.lbase = 4,
	.len = 1,
	.rid = TISCI_DEV_MCU_NAVSS0_INTR_ROUTER_0,
	.rbase = 260,
};
const struct Sciclient_rmIrqIf MCU_NAVSS0_MCRC_0_dma_event_intr_0_3_to_MCU_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_0_3 = {
	.lbase = 0,
	.len = 4,
	.rid = TISCI_DEV_MCU_NAVSS0_UDMASS_INTA_0,
	.rbase = 0,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCU_NAVSS0_MCRC_0[] = {
	&MCU_NAVSS0_MCRC_0_dma_event_intr_0_3_to_MCU_NAVSS0_INTR_ROUTER_0_in_intr_256_259,
	&MCU_NAVSS0_MCRC_0_intaggr_vintr_pend_4_4_to_MCU_NAVSS0_INTR_ROUTER_0_in_intr_260_260,
	&MCU_NAVSS0_MCRC_0_dma_event_intr_0_3_to_MCU_NAVSS0_UDMASS_INTA_0_intaggr_levi_pend_0_3,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCU_NAVSS0_MCRC_0 = {
	.id = TISCI_DEV_MCU_NAVSS0_MCRC_0,
	.n_if = 3,
	.p_if = &tisci_if_MCU_NAVSS0_MCRC_0[0],
};

/* Start of MCU_NAVSS0_UDMASS_INTA_0 interface definition */
const struct Sciclient_rmIrqIf MCU_NAVSS0_UDMASS_INTA_0_intaggr_vintr_pend_0_255_to_MCU_NAVSS0_INTR_ROUTER_0_in_intr_0_255 = {
	.lbase = 0,
	.len = 256,
	.rid = TISCI_DEV_MCU_NAVSS0_INTR_ROUTER_0,
	.rbase = 0,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCU_NAVSS0_UDMASS_INTA_0[] = {
	&MCU_NAVSS0_UDMASS_INTA_0_intaggr_vintr_pend_0_255_to_MCU_NAVSS0_INTR_ROUTER_0_in_intr_0_255,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCU_NAVSS0_UDMASS_INTA_0 = {
	.id = TISCI_DEV_MCU_NAVSS0_UDMASS_INTA_0,
	.n_if = 1,
	.p_if = &tisci_if_MCU_NAVSS0_UDMASS_INTA_0[0],
};

/* Start of PCIE0 interface definition */
const struct Sciclient_rmIrqIf PCIE0_pcie_cpts_comp_0_0_to_CMPEVENT_INTRTR0_in_4_4 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_CMPEVENT_INTRTR0,
	.rbase = 4,
};
const struct Sciclient_rmIrqIf PCIE0_pcie_cpts_genf0_1_1_to_TIMESYNC_INTRTR0_in_10_10 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 10,
};
const struct Sciclient_rmIrqIf PCIE0_pcie_cpts_hw1_push_2_2_to_TIMESYNC_INTRTR0_in_20_20 = {
	.lbase = 2,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 20,
};
const struct Sciclient_rmIrqIf PCIE0_pcie_cpts_sync_4_4_to_TIMESYNC_INTRTR0_in_32_32 = {
	.lbase = 4,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 32,
};
const struct Sciclient_rmIrqIf PCIE0_pcie_phy_level_13_13_to_MAIN2MCU_LVL_INTRTR0_in_67_67 = {
	.lbase = 13,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 67,
};
const struct Sciclient_rmIrqIf PCIE0_pcie_local_level_12_12_to_MAIN2MCU_LVL_INTRTR0_in_68_68 = {
	.lbase = 12,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 68,
};
const struct Sciclient_rmIrqIf PCIE0_pcie_cpts_pend_3_3_to_MAIN2MCU_LVL_INTRTR0_in_69_69 = {
	.lbase = 3,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 69,
};
const struct Sciclient_rmIrqIf PCIE0_pcie_dpa_pulse_6_6_to_MAIN2MCU_PLS_INTRTR0_in_20_20 = {
	.lbase = 6,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 20,
};
const struct Sciclient_rmIrqIf PCIE0_pcie_legacy_pulse_10_10_to_MAIN2MCU_PLS_INTRTR0_in_32_32 = {
	.lbase = 10,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 32,
};
const struct Sciclient_rmIrqIf PCIE0_pcie_downstream_pulse_5_5_to_MAIN2MCU_PLS_INTRTR0_in_33_33 = {
	.lbase = 5,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 33,
};
const struct Sciclient_rmIrqIf PCIE0_pcie_flr_pulse_8_8_to_MAIN2MCU_PLS_INTRTR0_in_34_34 = {
	.lbase = 8,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 34,
};
const struct Sciclient_rmIrqIf PCIE0_pcie_error_pulse_7_7_to_MAIN2MCU_PLS_INTRTR0_in_35_35 = {
	.lbase = 7,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 35,
};
const struct Sciclient_rmIrqIf PCIE0_pcie_link_state_pulse_11_11_to_MAIN2MCU_PLS_INTRTR0_in_36_36 = {
	.lbase = 11,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 36,
};
const struct Sciclient_rmIrqIf PCIE0_pcie_pwr_state_pulse_15_15_to_MAIN2MCU_PLS_INTRTR0_in_37_37 = {
	.lbase = 15,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 37,
};
const struct Sciclient_rmIrqIf PCIE0_pcie_ptm_valid_pulse_14_14_to_MAIN2MCU_PLS_INTRTR0_in_38_38 = {
	.lbase = 14,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 38,
};
const struct Sciclient_rmIrqIf PCIE0_pcie_hot_reset_pulse_9_9_to_MAIN2MCU_PLS_INTRTR0_in_39_39 = {
	.lbase = 9,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 39,
};
const struct Sciclient_rmIrqIf * const tisci_if_PCIE0[] = {
	&PCIE0_pcie_cpts_comp_0_0_to_CMPEVENT_INTRTR0_in_4_4,
	&PCIE0_pcie_cpts_genf0_1_1_to_TIMESYNC_INTRTR0_in_10_10,
	&PCIE0_pcie_cpts_hw1_push_2_2_to_TIMESYNC_INTRTR0_in_20_20,
	&PCIE0_pcie_cpts_sync_4_4_to_TIMESYNC_INTRTR0_in_32_32,
	&PCIE0_pcie_phy_level_13_13_to_MAIN2MCU_LVL_INTRTR0_in_67_67,
	&PCIE0_pcie_local_level_12_12_to_MAIN2MCU_LVL_INTRTR0_in_68_68,
	&PCIE0_pcie_cpts_pend_3_3_to_MAIN2MCU_LVL_INTRTR0_in_69_69,
	&PCIE0_pcie_dpa_pulse_6_6_to_MAIN2MCU_PLS_INTRTR0_in_20_20,
	&PCIE0_pcie_legacy_pulse_10_10_to_MAIN2MCU_PLS_INTRTR0_in_32_32,
	&PCIE0_pcie_downstream_pulse_5_5_to_MAIN2MCU_PLS_INTRTR0_in_33_33,
	&PCIE0_pcie_flr_pulse_8_8_to_MAIN2MCU_PLS_INTRTR0_in_34_34,
	&PCIE0_pcie_error_pulse_7_7_to_MAIN2MCU_PLS_INTRTR0_in_35_35,
	&PCIE0_pcie_link_state_pulse_11_11_to_MAIN2MCU_PLS_INTRTR0_in_36_36,
	&PCIE0_pcie_pwr_state_pulse_15_15_to_MAIN2MCU_PLS_INTRTR0_in_37_37,
	&PCIE0_pcie_ptm_valid_pulse_14_14_to_MAIN2MCU_PLS_INTRTR0_in_38_38,
	&PCIE0_pcie_hot_reset_pulse_9_9_to_MAIN2MCU_PLS_INTRTR0_in_39_39,
};
static const struct Sciclient_rmIrqNode tisci_irq_PCIE0 = {
	.id = TISCI_DEV_PCIE0,
	.n_if = 16,
	.p_if = &tisci_if_PCIE0[0],
};

/* Start of PCIE1 interface definition */
const struct Sciclient_rmIrqIf PCIE1_pcie_cpts_comp_0_0_to_CMPEVENT_INTRTR0_in_5_5 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_CMPEVENT_INTRTR0,
	.rbase = 5,
};
const struct Sciclient_rmIrqIf PCIE1_pcie_cpts_genf0_1_1_to_TIMESYNC_INTRTR0_in_11_11 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 11,
};
const struct Sciclient_rmIrqIf PCIE1_pcie_cpts_hw1_push_2_2_to_TIMESYNC_INTRTR0_in_21_21 = {
	.lbase = 2,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 21,
};
const struct Sciclient_rmIrqIf PCIE1_pcie_cpts_sync_4_4_to_TIMESYNC_INTRTR0_in_33_33 = {
	.lbase = 4,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 33,
};
const struct Sciclient_rmIrqIf PCIE1_pcie_phy_level_13_13_to_MAIN2MCU_LVL_INTRTR0_in_73_73 = {
	.lbase = 13,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 73,
};
const struct Sciclient_rmIrqIf PCIE1_pcie_local_level_12_12_to_MAIN2MCU_LVL_INTRTR0_in_74_74 = {
	.lbase = 12,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 74,
};
const struct Sciclient_rmIrqIf PCIE1_pcie_cpts_pend_3_3_to_MAIN2MCU_LVL_INTRTR0_in_75_75 = {
	.lbase = 3,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 75,
};
const struct Sciclient_rmIrqIf PCIE1_pcie_dpa_pulse_6_6_to_MAIN2MCU_PLS_INTRTR0_in_21_21 = {
	.lbase = 6,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 21,
};
const struct Sciclient_rmIrqIf PCIE1_pcie_legacy_pulse_10_10_to_MAIN2MCU_PLS_INTRTR0_in_40_40 = {
	.lbase = 10,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 40,
};
const struct Sciclient_rmIrqIf PCIE1_pcie_downstream_pulse_5_5_to_MAIN2MCU_PLS_INTRTR0_in_41_41 = {
	.lbase = 5,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 41,
};
const struct Sciclient_rmIrqIf PCIE1_pcie_flr_pulse_8_8_to_MAIN2MCU_PLS_INTRTR0_in_42_42 = {
	.lbase = 8,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 42,
};
const struct Sciclient_rmIrqIf PCIE1_pcie_error_pulse_7_7_to_MAIN2MCU_PLS_INTRTR0_in_43_43 = {
	.lbase = 7,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 43,
};
const struct Sciclient_rmIrqIf PCIE1_pcie_link_state_pulse_11_11_to_MAIN2MCU_PLS_INTRTR0_in_44_44 = {
	.lbase = 11,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 44,
};
const struct Sciclient_rmIrqIf PCIE1_pcie_pwr_state_pulse_15_15_to_MAIN2MCU_PLS_INTRTR0_in_45_45 = {
	.lbase = 15,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 45,
};
const struct Sciclient_rmIrqIf PCIE1_pcie_ptm_valid_pulse_14_14_to_MAIN2MCU_PLS_INTRTR0_in_46_46 = {
	.lbase = 14,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 46,
};
const struct Sciclient_rmIrqIf PCIE1_pcie_hot_reset_pulse_9_9_to_MAIN2MCU_PLS_INTRTR0_in_47_47 = {
	.lbase = 9,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 47,
};
const struct Sciclient_rmIrqIf * const tisci_if_PCIE1[] = {
	&PCIE1_pcie_cpts_comp_0_0_to_CMPEVENT_INTRTR0_in_5_5,
	&PCIE1_pcie_cpts_genf0_1_1_to_TIMESYNC_INTRTR0_in_11_11,
	&PCIE1_pcie_cpts_hw1_push_2_2_to_TIMESYNC_INTRTR0_in_21_21,
	&PCIE1_pcie_cpts_sync_4_4_to_TIMESYNC_INTRTR0_in_33_33,
	&PCIE1_pcie_phy_level_13_13_to_MAIN2MCU_LVL_INTRTR0_in_73_73,
	&PCIE1_pcie_local_level_12_12_to_MAIN2MCU_LVL_INTRTR0_in_74_74,
	&PCIE1_pcie_cpts_pend_3_3_to_MAIN2MCU_LVL_INTRTR0_in_75_75,
	&PCIE1_pcie_dpa_pulse_6_6_to_MAIN2MCU_PLS_INTRTR0_in_21_21,
	&PCIE1_pcie_legacy_pulse_10_10_to_MAIN2MCU_PLS_INTRTR0_in_40_40,
	&PCIE1_pcie_downstream_pulse_5_5_to_MAIN2MCU_PLS_INTRTR0_in_41_41,
	&PCIE1_pcie_flr_pulse_8_8_to_MAIN2MCU_PLS_INTRTR0_in_42_42,
	&PCIE1_pcie_error_pulse_7_7_to_MAIN2MCU_PLS_INTRTR0_in_43_43,
	&PCIE1_pcie_link_state_pulse_11_11_to_MAIN2MCU_PLS_INTRTR0_in_44_44,
	&PCIE1_pcie_pwr_state_pulse_15_15_to_MAIN2MCU_PLS_INTRTR0_in_45_45,
	&PCIE1_pcie_ptm_valid_pulse_14_14_to_MAIN2MCU_PLS_INTRTR0_in_46_46,
	&PCIE1_pcie_hot_reset_pulse_9_9_to_MAIN2MCU_PLS_INTRTR0_in_47_47,
};
static const struct Sciclient_rmIrqNode tisci_irq_PCIE1 = {
	.id = TISCI_DEV_PCIE1,
	.n_if = 16,
	.p_if = &tisci_if_PCIE1[0],
};

/* Start of PCIE2 interface definition */
const struct Sciclient_rmIrqIf PCIE2_pcie_cpts_comp_0_0_to_CMPEVENT_INTRTR0_in_6_6 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_CMPEVENT_INTRTR0,
	.rbase = 6,
};
const struct Sciclient_rmIrqIf PCIE2_pcie_cpts_genf0_1_1_to_TIMESYNC_INTRTR0_in_12_12 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 12,
};
const struct Sciclient_rmIrqIf PCIE2_pcie_cpts_hw1_push_2_2_to_TIMESYNC_INTRTR0_in_22_22 = {
	.lbase = 2,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 22,
};
const struct Sciclient_rmIrqIf PCIE2_pcie_cpts_sync_4_4_to_TIMESYNC_INTRTR0_in_34_34 = {
	.lbase = 4,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 34,
};
const struct Sciclient_rmIrqIf PCIE2_pcie_phy_level_13_13_to_MAIN2MCU_LVL_INTRTR0_in_76_76 = {
	.lbase = 13,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 76,
};
const struct Sciclient_rmIrqIf PCIE2_pcie_local_level_12_12_to_MAIN2MCU_LVL_INTRTR0_in_77_77 = {
	.lbase = 12,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 77,
};
const struct Sciclient_rmIrqIf PCIE2_pcie_cpts_pend_3_3_to_MAIN2MCU_LVL_INTRTR0_in_78_78 = {
	.lbase = 3,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 78,
};
const struct Sciclient_rmIrqIf PCIE2_pcie_dpa_pulse_6_6_to_MAIN2MCU_PLS_INTRTR0_in_22_22 = {
	.lbase = 6,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 22,
};
const struct Sciclient_rmIrqIf PCIE2_pcie_legacy_pulse_10_10_to_MAIN2MCU_PLS_INTRTR0_in_48_48 = {
	.lbase = 10,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 48,
};
const struct Sciclient_rmIrqIf PCIE2_pcie_downstream_pulse_5_5_to_MAIN2MCU_PLS_INTRTR0_in_49_49 = {
	.lbase = 5,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 49,
};
const struct Sciclient_rmIrqIf PCIE2_pcie_flr_pulse_8_8_to_MAIN2MCU_PLS_INTRTR0_in_50_50 = {
	.lbase = 8,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 50,
};
const struct Sciclient_rmIrqIf PCIE2_pcie_error_pulse_7_7_to_MAIN2MCU_PLS_INTRTR0_in_51_51 = {
	.lbase = 7,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 51,
};
const struct Sciclient_rmIrqIf PCIE2_pcie_link_state_pulse_11_11_to_MAIN2MCU_PLS_INTRTR0_in_52_52 = {
	.lbase = 11,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 52,
};
const struct Sciclient_rmIrqIf PCIE2_pcie_pwr_state_pulse_15_15_to_MAIN2MCU_PLS_INTRTR0_in_53_53 = {
	.lbase = 15,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 53,
};
const struct Sciclient_rmIrqIf PCIE2_pcie_ptm_valid_pulse_14_14_to_MAIN2MCU_PLS_INTRTR0_in_54_54 = {
	.lbase = 14,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 54,
};
const struct Sciclient_rmIrqIf PCIE2_pcie_hot_reset_pulse_9_9_to_MAIN2MCU_PLS_INTRTR0_in_55_55 = {
	.lbase = 9,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 55,
};
const struct Sciclient_rmIrqIf * const tisci_if_PCIE2[] = {
	&PCIE2_pcie_cpts_comp_0_0_to_CMPEVENT_INTRTR0_in_6_6,
	&PCIE2_pcie_cpts_genf0_1_1_to_TIMESYNC_INTRTR0_in_12_12,
	&PCIE2_pcie_cpts_hw1_push_2_2_to_TIMESYNC_INTRTR0_in_22_22,
	&PCIE2_pcie_cpts_sync_4_4_to_TIMESYNC_INTRTR0_in_34_34,
	&PCIE2_pcie_phy_level_13_13_to_MAIN2MCU_LVL_INTRTR0_in_76_76,
	&PCIE2_pcie_local_level_12_12_to_MAIN2MCU_LVL_INTRTR0_in_77_77,
	&PCIE2_pcie_cpts_pend_3_3_to_MAIN2MCU_LVL_INTRTR0_in_78_78,
	&PCIE2_pcie_dpa_pulse_6_6_to_MAIN2MCU_PLS_INTRTR0_in_22_22,
	&PCIE2_pcie_legacy_pulse_10_10_to_MAIN2MCU_PLS_INTRTR0_in_48_48,
	&PCIE2_pcie_downstream_pulse_5_5_to_MAIN2MCU_PLS_INTRTR0_in_49_49,
	&PCIE2_pcie_flr_pulse_8_8_to_MAIN2MCU_PLS_INTRTR0_in_50_50,
	&PCIE2_pcie_error_pulse_7_7_to_MAIN2MCU_PLS_INTRTR0_in_51_51,
	&PCIE2_pcie_link_state_pulse_11_11_to_MAIN2MCU_PLS_INTRTR0_in_52_52,
	&PCIE2_pcie_pwr_state_pulse_15_15_to_MAIN2MCU_PLS_INTRTR0_in_53_53,
	&PCIE2_pcie_ptm_valid_pulse_14_14_to_MAIN2MCU_PLS_INTRTR0_in_54_54,
	&PCIE2_pcie_hot_reset_pulse_9_9_to_MAIN2MCU_PLS_INTRTR0_in_55_55,
};
static const struct Sciclient_rmIrqNode tisci_irq_PCIE2 = {
	.id = TISCI_DEV_PCIE2,
	.n_if = 16,
	.p_if = &tisci_if_PCIE2[0],
};

/* Start of PCIE3 interface definition */
const struct Sciclient_rmIrqIf PCIE3_pcie_cpts_comp_0_0_to_CMPEVENT_INTRTR0_in_7_7 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_CMPEVENT_INTRTR0,
	.rbase = 7,
};
const struct Sciclient_rmIrqIf PCIE3_pcie_cpts_genf0_1_1_to_TIMESYNC_INTRTR0_in_13_13 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 13,
};
const struct Sciclient_rmIrqIf PCIE3_pcie_cpts_hw1_push_2_2_to_TIMESYNC_INTRTR0_in_23_23 = {
	.lbase = 2,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 23,
};
const struct Sciclient_rmIrqIf PCIE3_pcie_cpts_sync_4_4_to_TIMESYNC_INTRTR0_in_35_35 = {
	.lbase = 4,
	.len = 1,
	.rid = TISCI_DEV_TIMESYNC_INTRTR0,
	.rbase = 35,
};
const struct Sciclient_rmIrqIf PCIE3_pcie_phy_level_13_13_to_MAIN2MCU_LVL_INTRTR0_in_79_79 = {
	.lbase = 13,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 79,
};
const struct Sciclient_rmIrqIf PCIE3_pcie_local_level_12_12_to_MAIN2MCU_LVL_INTRTR0_in_80_80 = {
	.lbase = 12,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 80,
};
const struct Sciclient_rmIrqIf PCIE3_pcie_cpts_pend_3_3_to_MAIN2MCU_LVL_INTRTR0_in_81_81 = {
	.lbase = 3,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 81,
};
const struct Sciclient_rmIrqIf PCIE3_pcie_dpa_pulse_6_6_to_MAIN2MCU_PLS_INTRTR0_in_23_23 = {
	.lbase = 6,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 23,
};
const struct Sciclient_rmIrqIf PCIE3_pcie_legacy_pulse_10_10_to_MAIN2MCU_PLS_INTRTR0_in_56_56 = {
	.lbase = 10,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 56,
};
const struct Sciclient_rmIrqIf PCIE3_pcie_downstream_pulse_5_5_to_MAIN2MCU_PLS_INTRTR0_in_57_57 = {
	.lbase = 5,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 57,
};
const struct Sciclient_rmIrqIf PCIE3_pcie_flr_pulse_8_8_to_MAIN2MCU_PLS_INTRTR0_in_58_58 = {
	.lbase = 8,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 58,
};
const struct Sciclient_rmIrqIf PCIE3_pcie_error_pulse_7_7_to_MAIN2MCU_PLS_INTRTR0_in_59_59 = {
	.lbase = 7,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 59,
};
const struct Sciclient_rmIrqIf PCIE3_pcie_link_state_pulse_11_11_to_MAIN2MCU_PLS_INTRTR0_in_60_60 = {
	.lbase = 11,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 60,
};
const struct Sciclient_rmIrqIf PCIE3_pcie_pwr_state_pulse_15_15_to_MAIN2MCU_PLS_INTRTR0_in_61_61 = {
	.lbase = 15,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 61,
};
const struct Sciclient_rmIrqIf PCIE3_pcie_ptm_valid_pulse_14_14_to_MAIN2MCU_PLS_INTRTR0_in_62_62 = {
	.lbase = 14,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 62,
};
const struct Sciclient_rmIrqIf PCIE3_pcie_hot_reset_pulse_9_9_to_MAIN2MCU_PLS_INTRTR0_in_63_63 = {
	.lbase = 9,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_PLS_INTRTR0,
	.rbase = 63,
};
const struct Sciclient_rmIrqIf * const tisci_if_PCIE3[] = {
	&PCIE3_pcie_cpts_comp_0_0_to_CMPEVENT_INTRTR0_in_7_7,
	&PCIE3_pcie_cpts_genf0_1_1_to_TIMESYNC_INTRTR0_in_13_13,
	&PCIE3_pcie_cpts_hw1_push_2_2_to_TIMESYNC_INTRTR0_in_23_23,
	&PCIE3_pcie_cpts_sync_4_4_to_TIMESYNC_INTRTR0_in_35_35,
	&PCIE3_pcie_phy_level_13_13_to_MAIN2MCU_LVL_INTRTR0_in_79_79,
	&PCIE3_pcie_local_level_12_12_to_MAIN2MCU_LVL_INTRTR0_in_80_80,
	&PCIE3_pcie_cpts_pend_3_3_to_MAIN2MCU_LVL_INTRTR0_in_81_81,
	&PCIE3_pcie_dpa_pulse_6_6_to_MAIN2MCU_PLS_INTRTR0_in_23_23,
	&PCIE3_pcie_legacy_pulse_10_10_to_MAIN2MCU_PLS_INTRTR0_in_56_56,
	&PCIE3_pcie_downstream_pulse_5_5_to_MAIN2MCU_PLS_INTRTR0_in_57_57,
	&PCIE3_pcie_flr_pulse_8_8_to_MAIN2MCU_PLS_INTRTR0_in_58_58,
	&PCIE3_pcie_error_pulse_7_7_to_MAIN2MCU_PLS_INTRTR0_in_59_59,
	&PCIE3_pcie_link_state_pulse_11_11_to_MAIN2MCU_PLS_INTRTR0_in_60_60,
	&PCIE3_pcie_pwr_state_pulse_15_15_to_MAIN2MCU_PLS_INTRTR0_in_61_61,
	&PCIE3_pcie_ptm_valid_pulse_14_14_to_MAIN2MCU_PLS_INTRTR0_in_62_62,
	&PCIE3_pcie_hot_reset_pulse_9_9_to_MAIN2MCU_PLS_INTRTR0_in_63_63,
};
static const struct Sciclient_rmIrqNode tisci_irq_PCIE3 = {
	.id = TISCI_DEV_PCIE3,
	.n_if = 16,
	.p_if = &tisci_if_PCIE3[0],
};

/* Start of SA2_UL0 interface definition */
const struct Sciclient_rmIrqIf SA2_UL0_sa_ul_trng_1_1_to_MAIN2MCU_LVL_INTRTR0_in_4_4 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 4,
};
const struct Sciclient_rmIrqIf SA2_UL0_sa_ul_pka_0_0_to_MAIN2MCU_LVL_INTRTR0_in_5_5 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 5,
};
const struct Sciclient_rmIrqIf * const tisci_if_SA2_UL0[] = {
	&SA2_UL0_sa_ul_trng_1_1_to_MAIN2MCU_LVL_INTRTR0_in_4_4,
	&SA2_UL0_sa_ul_pka_0_0_to_MAIN2MCU_LVL_INTRTR0_in_5_5,
};
static const struct Sciclient_rmIrqNode tisci_irq_SA2_UL0 = {
	.id = TISCI_DEV_SA2_UL0,
	.n_if = 2,
	.p_if = &tisci_if_SA2_UL0[0],
};

/* Start of MCSPI0 interface definition */
const struct Sciclient_rmIrqIf MCSPI0_intr_spi_0_0_to_MAIN2MCU_LVL_INTRTR0_in_48_48 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 48,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCSPI0[] = {
	&MCSPI0_intr_spi_0_0_to_MAIN2MCU_LVL_INTRTR0_in_48_48,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCSPI0 = {
	.id = TISCI_DEV_MCSPI0,
	.n_if = 1,
	.p_if = &tisci_if_MCSPI0[0],
};

/* Start of MCSPI1 interface definition */
const struct Sciclient_rmIrqIf MCSPI1_intr_spi_0_0_to_MAIN2MCU_LVL_INTRTR0_in_49_49 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 49,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCSPI1[] = {
	&MCSPI1_intr_spi_0_0_to_MAIN2MCU_LVL_INTRTR0_in_49_49,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCSPI1 = {
	.id = TISCI_DEV_MCSPI1,
	.n_if = 1,
	.p_if = &tisci_if_MCSPI1[0],
};

/* Start of MCSPI2 interface definition */
const struct Sciclient_rmIrqIf MCSPI2_intr_spi_0_0_to_MAIN2MCU_LVL_INTRTR0_in_50_50 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 50,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCSPI2[] = {
	&MCSPI2_intr_spi_0_0_to_MAIN2MCU_LVL_INTRTR0_in_50_50,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCSPI2 = {
	.id = TISCI_DEV_MCSPI2,
	.n_if = 1,
	.p_if = &tisci_if_MCSPI2[0],
};

/* Start of MCSPI3 interface definition */
const struct Sciclient_rmIrqIf MCSPI3_intr_spi_0_0_to_MAIN2MCU_LVL_INTRTR0_in_51_51 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 51,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCSPI3[] = {
	&MCSPI3_intr_spi_0_0_to_MAIN2MCU_LVL_INTRTR0_in_51_51,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCSPI3 = {
	.id = TISCI_DEV_MCSPI3,
	.n_if = 1,
	.p_if = &tisci_if_MCSPI3[0],
};

/* Start of MCSPI4 interface definition */
const struct Sciclient_rmIrqIf MCSPI4_intr_spi_0_0_to_MAIN2MCU_LVL_INTRTR0_in_52_52 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 52,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCSPI4[] = {
	&MCSPI4_intr_spi_0_0_to_MAIN2MCU_LVL_INTRTR0_in_52_52,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCSPI4 = {
	.id = TISCI_DEV_MCSPI4,
	.n_if = 1,
	.p_if = &tisci_if_MCSPI4[0],
};

/* Start of MCSPI5 interface definition */
const struct Sciclient_rmIrqIf MCSPI5_intr_spi_0_0_to_MAIN2MCU_LVL_INTRTR0_in_53_53 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 53,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCSPI5[] = {
	&MCSPI5_intr_spi_0_0_to_MAIN2MCU_LVL_INTRTR0_in_53_53,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCSPI5 = {
	.id = TISCI_DEV_MCSPI5,
	.n_if = 1,
	.p_if = &tisci_if_MCSPI5[0],
};

/* Start of MCSPI6 interface definition */
const struct Sciclient_rmIrqIf MCSPI6_intr_spi_0_0_to_MAIN2MCU_LVL_INTRTR0_in_54_54 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 54,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCSPI6[] = {
	&MCSPI6_intr_spi_0_0_to_MAIN2MCU_LVL_INTRTR0_in_54_54,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCSPI6 = {
	.id = TISCI_DEV_MCSPI6,
	.n_if = 1,
	.p_if = &tisci_if_MCSPI6[0],
};

/* Start of MCSPI7 interface definition */
const struct Sciclient_rmIrqIf MCSPI7_intr_spi_0_0_to_MAIN2MCU_LVL_INTRTR0_in_55_55 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 55,
};
const struct Sciclient_rmIrqIf * const tisci_if_MCSPI7[] = {
	&MCSPI7_intr_spi_0_0_to_MAIN2MCU_LVL_INTRTR0_in_55_55,
};
static const struct Sciclient_rmIrqNode tisci_irq_MCSPI7 = {
	.id = TISCI_DEV_MCSPI7,
	.n_if = 1,
	.p_if = &tisci_if_MCSPI7[0],
};

/* Start of UFS0 interface definition */
const struct Sciclient_rmIrqIf UFS0_ufs_intr_0_0_to_MAIN2MCU_LVL_INTRTR0_in_218_218 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 218,
};
const struct Sciclient_rmIrqIf * const tisci_if_UFS0[] = {
	&UFS0_ufs_intr_0_0_to_MAIN2MCU_LVL_INTRTR0_in_218_218,
};
static const struct Sciclient_rmIrqNode tisci_irq_UFS0 = {
	.id = TISCI_DEV_UFS0,
	.n_if = 1,
	.p_if = &tisci_if_UFS0[0],
};

/* Start of UART1 interface definition */
const struct Sciclient_rmIrqIf UART1_usart_irq_0_0_to_MAIN2MCU_LVL_INTRTR0_in_97_97 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 97,
};
const struct Sciclient_rmIrqIf * const tisci_if_UART1[] = {
	&UART1_usart_irq_0_0_to_MAIN2MCU_LVL_INTRTR0_in_97_97,
};
static const struct Sciclient_rmIrqNode tisci_irq_UART1 = {
	.id = TISCI_DEV_UART1,
	.n_if = 1,
	.p_if = &tisci_if_UART1[0],
};

/* Start of UART2 interface definition */
const struct Sciclient_rmIrqIf UART2_usart_irq_0_0_to_MAIN2MCU_LVL_INTRTR0_in_98_98 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 98,
};
const struct Sciclient_rmIrqIf * const tisci_if_UART2[] = {
	&UART2_usart_irq_0_0_to_MAIN2MCU_LVL_INTRTR0_in_98_98,
};
static const struct Sciclient_rmIrqNode tisci_irq_UART2 = {
	.id = TISCI_DEV_UART2,
	.n_if = 1,
	.p_if = &tisci_if_UART2[0],
};

/* Start of UART3 interface definition */
const struct Sciclient_rmIrqIf UART3_usart_irq_0_0_to_MAIN2MCU_LVL_INTRTR0_in_99_99 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 99,
};
const struct Sciclient_rmIrqIf * const tisci_if_UART3[] = {
	&UART3_usart_irq_0_0_to_MAIN2MCU_LVL_INTRTR0_in_99_99,
};
static const struct Sciclient_rmIrqNode tisci_irq_UART3 = {
	.id = TISCI_DEV_UART3,
	.n_if = 1,
	.p_if = &tisci_if_UART3[0],
};

/* Start of UART4 interface definition */
const struct Sciclient_rmIrqIf UART4_usart_irq_0_0_to_MAIN2MCU_LVL_INTRTR0_in_100_100 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 100,
};
const struct Sciclient_rmIrqIf * const tisci_if_UART4[] = {
	&UART4_usart_irq_0_0_to_MAIN2MCU_LVL_INTRTR0_in_100_100,
};
static const struct Sciclient_rmIrqNode tisci_irq_UART4 = {
	.id = TISCI_DEV_UART4,
	.n_if = 1,
	.p_if = &tisci_if_UART4[0],
};

/* Start of UART5 interface definition */
const struct Sciclient_rmIrqIf UART5_usart_irq_0_0_to_MAIN2MCU_LVL_INTRTR0_in_101_101 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 101,
};
const struct Sciclient_rmIrqIf * const tisci_if_UART5[] = {
	&UART5_usart_irq_0_0_to_MAIN2MCU_LVL_INTRTR0_in_101_101,
};
static const struct Sciclient_rmIrqNode tisci_irq_UART5 = {
	.id = TISCI_DEV_UART5,
	.n_if = 1,
	.p_if = &tisci_if_UART5[0],
};

/* Start of UART6 interface definition */
const struct Sciclient_rmIrqIf UART6_usart_irq_0_0_to_MAIN2MCU_LVL_INTRTR0_in_102_102 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 102,
};
const struct Sciclient_rmIrqIf * const tisci_if_UART6[] = {
	&UART6_usart_irq_0_0_to_MAIN2MCU_LVL_INTRTR0_in_102_102,
};
static const struct Sciclient_rmIrqNode tisci_irq_UART6 = {
	.id = TISCI_DEV_UART6,
	.n_if = 1,
	.p_if = &tisci_if_UART6[0],
};

/* Start of UART7 interface definition */
const struct Sciclient_rmIrqIf UART7_usart_irq_0_0_to_MAIN2MCU_LVL_INTRTR0_in_103_103 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 103,
};
const struct Sciclient_rmIrqIf * const tisci_if_UART7[] = {
	&UART7_usart_irq_0_0_to_MAIN2MCU_LVL_INTRTR0_in_103_103,
};
static const struct Sciclient_rmIrqNode tisci_irq_UART7 = {
	.id = TISCI_DEV_UART7,
	.n_if = 1,
	.p_if = &tisci_if_UART7[0],
};

/* Start of UART8 interface definition */
const struct Sciclient_rmIrqIf UART8_usart_irq_0_0_to_MAIN2MCU_LVL_INTRTR0_in_104_104 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 104,
};
const struct Sciclient_rmIrqIf * const tisci_if_UART8[] = {
	&UART8_usart_irq_0_0_to_MAIN2MCU_LVL_INTRTR0_in_104_104,
};
static const struct Sciclient_rmIrqNode tisci_irq_UART8 = {
	.id = TISCI_DEV_UART8,
	.n_if = 1,
	.p_if = &tisci_if_UART8[0],
};

/* Start of UART9 interface definition */
const struct Sciclient_rmIrqIf UART9_usart_irq_0_0_to_MAIN2MCU_LVL_INTRTR0_in_105_105 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 105,
};
const struct Sciclient_rmIrqIf * const tisci_if_UART9[] = {
	&UART9_usart_irq_0_0_to_MAIN2MCU_LVL_INTRTR0_in_105_105,
};
static const struct Sciclient_rmIrqNode tisci_irq_UART9 = {
	.id = TISCI_DEV_UART9,
	.n_if = 1,
	.p_if = &tisci_if_UART9[0],
};

/* Start of USB0 interface definition */
const struct Sciclient_rmIrqIf USB0_irq_1_8_to_MAIN2MCU_LVL_INTRTR0_in_128_135 = {
	.lbase = 1,
	.len = 8,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 128,
};
const struct Sciclient_rmIrqIf USB0_otgirq_9_9_to_MAIN2MCU_LVL_INTRTR0_in_152_152 = {
	.lbase = 9,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 152,
};
const struct Sciclient_rmIrqIf USB0_host_system_error_0_0_to_MAIN2MCU_LVL_INTRTR0_in_157_157 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 157,
};
const struct Sciclient_rmIrqIf * const tisci_if_USB0[] = {
	&USB0_irq_1_8_to_MAIN2MCU_LVL_INTRTR0_in_128_135,
	&USB0_otgirq_9_9_to_MAIN2MCU_LVL_INTRTR0_in_152_152,
	&USB0_host_system_error_0_0_to_MAIN2MCU_LVL_INTRTR0_in_157_157,
};
static const struct Sciclient_rmIrqNode tisci_irq_USB0 = {
	.id = TISCI_DEV_USB0,
	.n_if = 3,
	.p_if = &tisci_if_USB0[0],
};

/* Start of VPAC0 interface definition */
const struct Sciclient_rmIrqIf VPAC0_vpac_level_0_5_to_MAIN2MCU_LVL_INTRTR0_in_270_275 = {
	.lbase = 0,
	.len = 6,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 270,
};
const struct Sciclient_rmIrqIf * const tisci_if_VPAC0[] = {
	&VPAC0_vpac_level_0_5_to_MAIN2MCU_LVL_INTRTR0_in_270_275,
};
static const struct Sciclient_rmIrqNode tisci_irq_VPAC0 = {
	.id = TISCI_DEV_VPAC0,
	.n_if = 1,
	.p_if = &tisci_if_VPAC0[0],
};

/* Start of VPAC1 interface definition */
const struct Sciclient_rmIrqIf VPAC1_vpac_level_0_5_to_MAIN2MCU_LVL_INTRTR0_in_40_45 = {
	.lbase = 0,
	.len = 6,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 40,
};
const struct Sciclient_rmIrqIf * const tisci_if_VPAC1[] = {
	&VPAC1_vpac_level_0_5_to_MAIN2MCU_LVL_INTRTR0_in_40_45,
};
static const struct Sciclient_rmIrqNode tisci_irq_VPAC1 = {
	.id = TISCI_DEV_VPAC1,
	.n_if = 1,
	.p_if = &tisci_if_VPAC1[0],
};

/* Start of vusr_dual0 interface definition */
const struct Sciclient_rmIrqIf vusr_dual0_v0_vusr_intlvl_2_2_to_MAIN2MCU_LVL_INTRTR0_in_82_82 = {
	.lbase = 2,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 82,
};
const struct Sciclient_rmIrqIf vusr_dual0_v0_mcp_lo_intlvl_1_1_to_MAIN2MCU_LVL_INTRTR0_in_83_83 = {
	.lbase = 1,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 83,
};
const struct Sciclient_rmIrqIf vusr_dual0_v0_mcp_hi_intlvl_0_0_to_MAIN2MCU_LVL_INTRTR0_in_84_84 = {
	.lbase = 0,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 84,
};
const struct Sciclient_rmIrqIf vusr_dual0_v1_vusr_intlvl_5_5_to_MAIN2MCU_LVL_INTRTR0_in_85_85 = {
	.lbase = 5,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 85,
};
const struct Sciclient_rmIrqIf vusr_dual0_v1_mcp_lo_intlvl_4_4_to_MAIN2MCU_LVL_INTRTR0_in_86_86 = {
	.lbase = 4,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 86,
};
const struct Sciclient_rmIrqIf vusr_dual0_v1_mcp_hi_intlvl_3_3_to_MAIN2MCU_LVL_INTRTR0_in_87_87 = {
	.lbase = 3,
	.len = 1,
	.rid = TISCI_DEV_MAIN2MCU_LVL_INTRTR0,
	.rbase = 87,
};
const struct Sciclient_rmIrqIf * const tisci_if_vusr_dual0[] = {
	&vusr_dual0_v0_vusr_intlvl_2_2_to_MAIN2MCU_LVL_INTRTR0_in_82_82,
	&vusr_dual0_v0_mcp_lo_intlvl_1_1_to_MAIN2MCU_LVL_INTRTR0_in_83_83,
	&vusr_dual0_v0_mcp_hi_intlvl_0_0_to_MAIN2MCU_LVL_INTRTR0_in_84_84,
	&vusr_dual0_v1_vusr_intlvl_5_5_to_MAIN2MCU_LVL_INTRTR0_in_85_85,
	&vusr_dual0_v1_mcp_lo_intlvl_4_4_to_MAIN2MCU_LVL_INTRTR0_in_86_86,
	&vusr_dual0_v1_mcp_hi_intlvl_3_3_to_MAIN2MCU_LVL_INTRTR0_in_87_87,
};
static const struct Sciclient_rmIrqNode tisci_irq_vusr_dual0 = {
	.id = TISCI_DEV_VUSR_DUAL0,
	.n_if = 6,
	.p_if = &tisci_if_vusr_dual0[0],
};


const struct Sciclient_rmIrqNode * const gRmIrqTree[] = {
	&tisci_irq_GPIOMUX_INTRTR0,
	&tisci_irq_CMPEVENT_INTRTR0,
	&tisci_irq_GTC0,
	&tisci_irq_CPSW1,
	&tisci_irq_MCU_CPSW0,
	&tisci_irq_cpsw_9xuss_j7am0,
	&tisci_irq_csi_rx_if0,
	&tisci_irq_csi_rx_if1,
	&tisci_irq_csi_rx_if2,
	&tisci_irq_CSI_TX_IF0,
	&tisci_irq_CSI_TX_IF1,
	&tisci_irq_DCC0,
	&tisci_irq_DCC1,
	&tisci_irq_DCC2,
	&tisci_irq_DCC3,
	&tisci_irq_DCC4,
	&tisci_irq_DCC5,
	&tisci_irq_DCC6,
	&tisci_irq_DCC7,
	&tisci_irq_DCC8,
	&tisci_irq_DCC9,
	&tisci_irq_DMPAC0_INTD_0,
	&tisci_irq_TIMER0,
	&tisci_irq_TIMER1,
	&tisci_irq_TIMER2,
	&tisci_irq_TIMER3,
	&tisci_irq_TIMER4,
	&tisci_irq_TIMER5,
	&tisci_irq_TIMER6,
	&tisci_irq_TIMER7,
	&tisci_irq_TIMER8,
	&tisci_irq_TIMER9,
	&tisci_irq_TIMER10,
	&tisci_irq_TIMER11,
	&tisci_irq_TIMER12,
	&tisci_irq_TIMER13,
	&tisci_irq_TIMER14,
	&tisci_irq_TIMER15,
	&tisci_irq_TIMER16,
	&tisci_irq_TIMER17,
	&tisci_irq_TIMER18,
	&tisci_irq_TIMER19,
	&tisci_irq_ECAP0,
	&tisci_irq_ECAP1,
	&tisci_irq_ECAP2,
	&tisci_irq_ELM0,
	&tisci_irq_MMCSD0,
	&tisci_irq_MMCSD1,
	&tisci_irq_EQEP0,
	&tisci_irq_EQEP1,
	&tisci_irq_EQEP2,
	&tisci_irq_UART0,
	&tisci_irq_GPIO0,
	&tisci_irq_GPIO2,
	&tisci_irq_GPIO4,
	&tisci_irq_GPIO6,
	&tisci_irq_WKUP_GPIO0,
	&tisci_irq_WKUP_GPIO1,
	&tisci_irq_GPMC0,
	&tisci_irq_MAIN2MCU_LVL_INTRTR0,
	&tisci_irq_MAIN2MCU_PLS_INTRTR0,
	&tisci_irq_TIMESYNC_INTRTR0,
	&tisci_irq_WKUP_GPIOMUX_INTRTR0,
	&tisci_irq_j7aep_gpu_bxs464_wrap0,
	&tisci_irq_J7AEP_GPU_BXS464_WRAP0_GPU_SS_0,
	&tisci_irq_DDR0,
	&tisci_irq_DDR1,
	&tisci_irq_DDR2,
	&tisci_irq_DDR3,
	&tisci_irq_DSS_DSI0,
	&tisci_irq_DSS_DSI1,
	&tisci_irq_DSS_EDP0,
	&tisci_irq_DSS0,
	&tisci_irq_EPWM0,
	&tisci_irq_EPWM1,
	&tisci_irq_EPWM2,
	&tisci_irq_EPWM3,
	&tisci_irq_EPWM4,
	&tisci_irq_EPWM5,
	&tisci_irq_CODEC0,
	&tisci_irq_CODEC1,
	&tisci_irq_MCAN0,
	&tisci_irq_MCAN1,
	&tisci_irq_MCAN2,
	&tisci_irq_MCAN3,
	&tisci_irq_MCAN4,
	&tisci_irq_MCAN5,
	&tisci_irq_MCAN6,
	&tisci_irq_MCAN7,
	&tisci_irq_MCAN8,
	&tisci_irq_MCAN9,
	&tisci_irq_MCAN10,
	&tisci_irq_MCAN11,
	&tisci_irq_MCAN12,
	&tisci_irq_MCAN13,
	&tisci_irq_MCAN14,
	&tisci_irq_MCAN15,
	&tisci_irq_MCAN16,
	&tisci_irq_MCAN17,
	&tisci_irq_MCASP0,
	&tisci_irq_MCASP1,
	&tisci_irq_MCASP2,
	&tisci_irq_MCASP3,
	&tisci_irq_MCASP4,
	&tisci_irq_I2C0,
	&tisci_irq_I2C1,
	&tisci_irq_I2C2,
	&tisci_irq_I2C3,
	&tisci_irq_I2C4,
	&tisci_irq_I2C5,
	&tisci_irq_I2C6,
	&tisci_irq_NAVSS0,
	&tisci_irq_NAVSS0_CPTS_0,
	&tisci_irq_NAVSS0_INTR_0,
	&tisci_irq_NAVSS0_MAILBOX1_0,
	&tisci_irq_NAVSS0_MAILBOX1_1,
	&tisci_irq_NAVSS0_MAILBOX1_2,
	&tisci_irq_NAVSS0_MAILBOX1_3,
	&tisci_irq_NAVSS0_MAILBOX1_4,
	&tisci_irq_NAVSS0_MAILBOX1_5,
	&tisci_irq_NAVSS0_MAILBOX1_6,
	&tisci_irq_NAVSS0_MAILBOX1_7,
	&tisci_irq_NAVSS0_MAILBOX1_8,
	&tisci_irq_NAVSS0_MAILBOX1_9,
	&tisci_irq_NAVSS0_MAILBOX1_10,
	&tisci_irq_NAVSS0_MAILBOX1_11,
	&tisci_irq_NAVSS0_MAILBOX_0,
	&tisci_irq_NAVSS0_MAILBOX_1,
	&tisci_irq_NAVSS0_MAILBOX_2,
	&tisci_irq_NAVSS0_MAILBOX_3,
	&tisci_irq_NAVSS0_MAILBOX_4,
	&tisci_irq_NAVSS0_MAILBOX_5,
	&tisci_irq_NAVSS0_MAILBOX_6,
	&tisci_irq_NAVSS0_MAILBOX_7,
	&tisci_irq_NAVSS0_MAILBOX_8,
	&tisci_irq_NAVSS0_MAILBOX_9,
	&tisci_irq_NAVSS0_MAILBOX_10,
	&tisci_irq_NAVSS0_MAILBOX_11,
	&tisci_irq_NAVSS0_MCRC_0,
	&tisci_irq_NAVSS0_MODSS_INTA_0,
	&tisci_irq_NAVSS0_MODSS_INTA_1,
	&tisci_irq_NAVSS0_PVU_0,
	&tisci_irq_NAVSS0_PVU_1,
	&tisci_irq_NAVSS0_UDMASS_INTA_0,
	&tisci_irq_MCU_NAVSS0_INTR_ROUTER_0,
	&tisci_irq_MCU_NAVSS0_MCRC_0,
	&tisci_irq_MCU_NAVSS0_UDMASS_INTA_0,
	&tisci_irq_PCIE0,
	&tisci_irq_PCIE1,
	&tisci_irq_PCIE2,
	&tisci_irq_PCIE3,
	&tisci_irq_SA2_UL0,
	&tisci_irq_MCSPI0,
	&tisci_irq_MCSPI1,
	&tisci_irq_MCSPI2,
	&tisci_irq_MCSPI3,
	&tisci_irq_MCSPI4,
	&tisci_irq_MCSPI5,
	&tisci_irq_MCSPI6,
	&tisci_irq_MCSPI7,
	&tisci_irq_UFS0,
	&tisci_irq_UART1,
	&tisci_irq_UART2,
	&tisci_irq_UART3,
	&tisci_irq_UART4,
	&tisci_irq_UART5,
	&tisci_irq_UART6,
	&tisci_irq_UART7,
	&tisci_irq_UART8,
	&tisci_irq_UART9,
	&tisci_irq_USB0,
	&tisci_irq_VPAC0,
	&tisci_irq_VPAC1,
	&tisci_irq_vusr_dual0,
};

// const u32 irq_tree_count = ARRAY_SIZE(irq_tree);
#endif

const uint32_t gRmIrqTreeCount = sizeof(gRmIrqTree)/sizeof(gRmIrqTree[0]);
