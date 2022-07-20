/*
 * Ring Accelerator
 *
 * Ring accelerator driver instance data definition
 *
 * Data version: 220214_141435
 *
 * Copyright (C) 2021-2022 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <types/short_types.h>
#include <types/array_size.h>
#include <types/sbool.h>
#include <soc/rm_mmr.h>
#include <devices.h>
#include <soc/j721s2/resasg_types.h>
#include <soc/j721s2/soc_devgrps.h>

#include "../../include/ra_inst.h"
#include "ra_cfg.h"

static const struct rm_mmr mmr_NAVSS0_BCDMA_0_BCDMA0_CFG_GCFG = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x311a0000U,
};

static const struct rm_mmr mmr_NAVSS0_BCDMA_0_BCDMA0_CFG_RING = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x35900000U,
};

static const struct rm_mmr mmr_NAVSS0_BCDMA_0_BCDMA0_CFG_RINGRT = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x35e00000U,
};

static const struct ra_ring_type ring_types_NAVSS0_BCDMA_0[2] = {
	{
		.start = 0U,
		.end = 15U,
		.type = RA_DMSS_RING,
		.utype = RESASG_UTYPE(J721S2_DEV_NAVSS0_BCDMA_0, RESASG_SUBTYPE_BCDMA_RING_SPLIT_TR_TX_CHAN),
	},
	{
		.start = 16U,
		.end = 47U,
		.type = RA_DMSS_RING,
		.utype = RESASG_UTYPE(J721S2_DEV_NAVSS0_BCDMA_0, RESASG_SUBTYPE_BCDMA_RING_SPLIT_TR_RX_CHAN),
	},
};

static const struct rm_mmr mmr_NAVSS0_RINGACC_0_UDMASS_RINGACC0_GCFG = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x31160000U,
};

static const struct rm_mmr mmr_NAVSS0_RINGACC_0_UDMASS_RINGACC0_SRC_FIFOS = {
	.fwl_id		= 4128U,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 1023U,
	.base		= 0x38000000U,
};

static const struct rm_mmr mmr_NAVSS0_RINGACC_0_UDMASS_RINGACC0_CFG_MON = {
	.fwl_id		= 4224U,
	.fwl_ch_start	= 1024U,
	.fwl_ch_end	= 1055U,
	.base		= 0x32000000U,
};

static const struct rm_mmr mmr_NAVSS0_RINGACC_0_UDMASS_RINGACC0_CFG = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x31080000U,
};

static const struct rm_mmr mmr_NAVSS0_RINGACC_0_UDMASS_RINGACC0_CFG_RT = {
	.fwl_id		= 4224U,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 1023U,
	.base		= 0x3c000000U,
};

static const struct ra_ring_type ring_types_NAVSS0_RINGACC_0[8] = {
	{
		.start = 0U,
		.end = 1U,
		.type = RA_STANDARD_RING,
		.utype = RESASG_UTYPE(J721S2_DEV_NAVSS0_RINGACC_0, RESASG_SUBTYPE_RA_UDMAP_TX_UH),
	},
	{
		.start = 2U,
		.end = 5U,
		.type = RA_STANDARD_RING,
		.utype = RESASG_UTYPE(J721S2_DEV_NAVSS0_RINGACC_0, RESASG_SUBTYPE_RA_UDMAP_TX_H),
	},
	{
		.start = 6U,
		.end = 84U,
		.type = RA_STANDARD_RING,
		.utype = RESASG_UTYPE(J721S2_DEV_NAVSS0_RINGACC_0, RESASG_SUBTYPE_RA_UDMAP_TX),
	},
	{
		.start = 85U,
		.end = 340U,
		.type = RA_STANDARD_RING,
		.utype = RESASG_UTYPE(J721S2_DEV_NAVSS0_RINGACC_0, RESASG_SUBTYPE_RA_UDMAP_TX_EXT),
	},
	{
		.start = 341U,
		.end = 342U,
		.type = RA_STANDARD_RING,
		.utype = RESASG_UTYPE(J721S2_DEV_NAVSS0_RINGACC_0, RESASG_SUBTYPE_RA_UDMAP_RX_UH),
	},
	{
		.start = 343U,
		.end = 346U,
		.type = RA_STANDARD_RING,
		.utype = RESASG_UTYPE(J721S2_DEV_NAVSS0_RINGACC_0, RESASG_SUBTYPE_RA_UDMAP_RX_H),
	},
	{
		.start = 347U,
		.end = 422U,
		.type = RA_STANDARD_RING,
		.utype = RESASG_UTYPE(J721S2_DEV_NAVSS0_RINGACC_0, RESASG_SUBTYPE_RA_UDMAP_RX),
	},
	{
		.start = 423U,
		.end = 973U,
		.type = RA_STANDARD_RING,
		.utype = RESASG_UTYPE(J721S2_DEV_NAVSS0_RINGACC_0, RESASG_SUBTYPE_RA_GP),
	},
};

static const struct rm_mmr mmr_MCU_NAVSS0_RINGACC0_UDMASS_RINGACC0_CFG_GCFG = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x285d0000U,
};

static const struct rm_mmr mmr_MCU_NAVSS0_RINGACC0_UDMASS_RINGACC0_FIFOS = {
	.fwl_id		= 6272U,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 285U,
	.base		= 0x2b000000U,
};

static const struct rm_mmr mmr_MCU_NAVSS0_RINGACC0_UDMASS_RINGACC0_CFG_MON = {
	.fwl_id		= 6160U,
	.fwl_ch_start	= 286U,
	.fwl_ch_end	= 317U,
	.base		= 0x2a280000U,
};

static const struct rm_mmr mmr_MCU_NAVSS0_RINGACC0_UDMASS_RINGACC0_CFG = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x28440000U,
};

static const struct rm_mmr mmr_MCU_NAVSS0_RINGACC0_UDMASS_RINGACC0_CFG_RT = {
	.fwl_id		= 6160U,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 285U,
	.base		= 0x2b800000U,
};

static const struct ra_ring_type ring_types_MCU_NAVSS0_RINGACC0[5] = {
	{
		.start = 0U,
		.end = 1U,
		.type = RA_STANDARD_RING,
		.utype = RESASG_UTYPE(J721S2_DEV_MCU_NAVSS0_RINGACC0, RESASG_SUBTYPE_RA_UDMAP_TX_H),
	},
	{
		.start = 2U,
		.end = 47U,
		.type = RA_STANDARD_RING,
		.utype = RESASG_UTYPE(J721S2_DEV_MCU_NAVSS0_RINGACC0, RESASG_SUBTYPE_RA_UDMAP_TX),
	},
	{
		.start = 48U,
		.end = 49U,
		.type = RA_STANDARD_RING,
		.utype = RESASG_UTYPE(J721S2_DEV_MCU_NAVSS0_RINGACC0, RESASG_SUBTYPE_RA_UDMAP_RX_H),
	},
	{
		.start = 50U,
		.end = 95U,
		.type = RA_STANDARD_RING,
		.utype = RESASG_UTYPE(J721S2_DEV_MCU_NAVSS0_RINGACC0, RESASG_SUBTYPE_RA_UDMAP_RX),
	},
	{
		.start = 96U,
		.end = 255U,
		.type = RA_STANDARD_RING,
		.utype = RESASG_UTYPE(J721S2_DEV_MCU_NAVSS0_RINGACC0, RESASG_SUBTYPE_RA_GP),
	},
};

/*
 * Resources used by ROM which must have their OES registers reset
 */
static struct ra_used_mapping rom_usage_MCU_NAVSS0_RINGACC0[13U] = {
	{
		.ring = 0U,
		.cleared = SFALSE,
	},
	{
		.ring = 1U,
		.cleared = SFALSE,
	},
	{
		.ring = 2U,
		.cleared = SFALSE,
	},
	{
		.ring = 3U,
		.cleared = SFALSE,
	},
	{
		.ring = 4U,
		.cleared = SFALSE,
	},
	{
		.ring = 52U,
		.cleared = SFALSE,
	},
	{
		.ring = 100U,
		.cleared = SFALSE,
	},
	{
		.ring = 101U,
		.cleared = SFALSE,
	},
	{
		.ring = 102U,
		.cleared = SFALSE,
	},
	{
		.ring = 256U,
		.cleared = SFALSE,
	},
	{
		.ring = 257U,
		.cleared = SFALSE,
	},
	{
		.ring = 258U,
		.cleared = SFALSE,
	},
	{
		.ring = 259U,
		.cleared = SFALSE,
	},
};

static const struct rm_mmr mmr_MCU_SA3_SS0_PKTDMA_0_PKTDMA_CFG_GCFG = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x44910000U,
};

static const struct rm_mmr mmr_MCU_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RING = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x4491a000U,
};

static const struct rm_mmr mmr_MCU_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RINGRT = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x44940000U,
};

static const struct ra_ring_type ring_types_MCU_SA3_SS0_PKTDMA_0[6] = {
	{
		.start = 0U,
		.end = 7U,
		.type = RA_DMSS_RING,
		.utype = RESASG_UTYPE(J721S2_DEV_MCU_SA3_SS0_PKTDMA_0, RESASG_SUBTYPE_PKTDMA_RING_SAUL_TX_0_CHAN),
	},
	{
		.start = 8U,
		.end = 15U,
		.type = RA_DMSS_RING,
		.utype = RESASG_UTYPE(J721S2_DEV_MCU_SA3_SS0_PKTDMA_0, RESASG_SUBTYPE_PKTDMA_RING_SAUL_TX_1_CHAN),
	},
	{
		.start = 16U,
		.end = 23U,
		.type = RA_DMSS_RING,
		.utype = RESASG_UTYPE(J721S2_DEV_MCU_SA3_SS0_PKTDMA_0, RESASG_SUBTYPE_PKTDMA_RING_SAUL_RX_0_CHAN),
	},
	{
		.start = 16U,
		.end = 23U,
		.type = RA_DMSS_RING,
		.utype = RESASG_UTYPE(J721S2_DEV_MCU_SA3_SS0_PKTDMA_0, RESASG_SUBTYPE_PKTDMA_RING_SAUL_RX_1_CHAN),
	},
	{
		.start = 24U,
		.end = 31U,
		.type = RA_DMSS_RING,
		.utype = RESASG_UTYPE(J721S2_DEV_MCU_SA3_SS0_PKTDMA_0, RESASG_SUBTYPE_PKTDMA_RING_SAUL_RX_2_CHAN),
	},
	{
		.start = 24U,
		.end = 31U,
		.type = RA_DMSS_RING,
		.utype = RESASG_UTYPE(J721S2_DEV_MCU_SA3_SS0_PKTDMA_0, RESASG_SUBTYPE_PKTDMA_RING_SAUL_RX_3_CHAN),
	},
};

static const struct rm_mmr mmr_MCU_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_GCFG = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x44805000U,
};

static const struct rm_mmr mmr_MCU_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x448c0000U,
};

static const struct rm_mmr mmr_MCU_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_RT = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x44c00000U,
};

static const struct ra_ring_type ring_types_MCU_SA3_SS0_RINGACC_0[0] = {
};

struct ra_instance ra_inst[] = {
	{
		.id = J721S2_DEV_NAVSS0_BCDMA_0,
		.root_id = J721S2_DEV_NAVSS0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_J721S2_MAIN,
		.gcfg = &mmr_NAVSS0_BCDMA_0_BCDMA0_CFG_GCFG,
		.cfg = &mmr_NAVSS0_BCDMA_0_BCDMA0_CFG_RING,
		.rt = &mmr_NAVSS0_BCDMA_0_BCDMA0_CFG_RINGRT,
		.mon = NULL,
		.fifos = NULL,
		.n_ring = 0U,
		.ring_oes_offset = 0U,
		.ring_types = &ring_types_NAVSS0_BCDMA_0[0U],
		.n_ring_type = ARRAY_SIZE(ring_types_NAVSS0_BCDMA_0),
		.err_evt_index = RA_GCFG_ERROR_EVT_INDEX,
		.err_evt_utype = RESASG_UTYPE(J721S2_DEV_NAVSS0_BCDMA_0, RESASG_SUBTYPE_RA_ERROR_OES),
		.virtid_utype = 0U,
		.n_ring_mon = 0U,
		.ring_mon_utype = 0U,
		.ring_mon_oes_offset = 0U,
		.rom_usage = NULL,
		.n_rom_usage = 0U,
	},
	{
		.id = J721S2_DEV_NAVSS0_RINGACC_0,
		.root_id = J721S2_DEV_NAVSS0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_J721S2_MAIN,
		.gcfg = &mmr_NAVSS0_RINGACC_0_UDMASS_RINGACC0_GCFG,
		.cfg = &mmr_NAVSS0_RINGACC_0_UDMASS_RINGACC0_CFG,
		.rt = &mmr_NAVSS0_RINGACC_0_UDMASS_RINGACC0_CFG_RT,
		.mon = &mmr_NAVSS0_RINGACC_0_UDMASS_RINGACC0_CFG_MON,
		.fifos = &mmr_NAVSS0_RINGACC_0_UDMASS_RINGACC0_SRC_FIFOS,
		.n_ring = RA_NAVSS0_RINGACC_0_MAX_INDEX,
		.ring_oes_offset = RA_NAVSS0_RINGACC_0_RING_OES_EVT_INDEX_OFFSET,
		.ring_types = &ring_types_NAVSS0_RINGACC_0[0U],
		.n_ring_type = ARRAY_SIZE(ring_types_NAVSS0_RINGACC_0),
		.err_evt_index = RA_GCFG_ERROR_EVT_INDEX,
		.err_evt_utype = RESASG_UTYPE(J721S2_DEV_NAVSS0_RINGACC_0, RESASG_SUBTYPE_RA_ERROR_OES),
		.virtid_utype = RESASG_UTYPE(J721S2_DEV_NAVSS0_RINGACC_0, RESASG_SUBTYPE_RA_VIRTID),
		.n_ring_mon = RA_NAVSS0_RINGACC_0_MONITOR_MAX_INDEX,
		.ring_mon_utype = RESASG_UTYPE(J721S2_DEV_NAVSS0_RINGACC_0, RESASG_SUBTYPE_RA_MONITORS),
		.ring_mon_oes_offset = RA_MON_OES_EVT_INDEX_OFFSET,
		.rom_usage = NULL,
		.n_rom_usage = 0U,
	},
	{
		.id = J721S2_DEV_MCU_NAVSS0_RINGACC0,
		.root_id = J721S2_DEV_MCU_NAVSS0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_J721S2_MCU_WAKEUP | SOC_DEVGRP_J721S2_TIFS_INTERNAL,
		.gcfg = &mmr_MCU_NAVSS0_RINGACC0_UDMASS_RINGACC0_CFG_GCFG,
		.cfg = &mmr_MCU_NAVSS0_RINGACC0_UDMASS_RINGACC0_CFG,
		.rt = &mmr_MCU_NAVSS0_RINGACC0_UDMASS_RINGACC0_CFG_RT,
		.mon = &mmr_MCU_NAVSS0_RINGACC0_UDMASS_RINGACC0_CFG_MON,
		.fifos = &mmr_MCU_NAVSS0_RINGACC0_UDMASS_RINGACC0_FIFOS,
		.n_ring = RA_MCU_NAVSS0_RINGACC0_MAX_INDEX,
		.ring_oes_offset = RA_MCU_NAVSS0_RINGACC0_RING_OES_EVT_INDEX_OFFSET,
		.ring_types = &ring_types_MCU_NAVSS0_RINGACC0[0U],
		.n_ring_type = ARRAY_SIZE(ring_types_MCU_NAVSS0_RINGACC0),
		.err_evt_index = RA_GCFG_ERROR_EVT_INDEX,
		.err_evt_utype = RESASG_UTYPE(J721S2_DEV_MCU_NAVSS0_RINGACC0, RESASG_SUBTYPE_RA_ERROR_OES),
		.virtid_utype = RESASG_UTYPE(J721S2_DEV_MCU_NAVSS0_RINGACC0, RESASG_SUBTYPE_RA_VIRTID),
		.n_ring_mon = RA_MCU_NAVSS0_RINGACC0_MONITOR_MAX_INDEX,
		.ring_mon_utype = RESASG_UTYPE(J721S2_DEV_MCU_NAVSS0_RINGACC0, RESASG_SUBTYPE_RA_MONITORS),
		.ring_mon_oes_offset = RA_MON_OES_EVT_INDEX_OFFSET,
		.rom_usage = &rom_usage_MCU_NAVSS0_RINGACC0[0U],
		.n_rom_usage = ARRAY_SIZE(rom_usage_MCU_NAVSS0_RINGACC0),
	},
	{
		.id = J721S2_DEV_MCU_SA3_SS0_PKTDMA_0,
		.root_id = J721S2_DEV_MCU_SA3_SS0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_J721S2_TIFS_INTERNAL,
		.gcfg = &mmr_MCU_SA3_SS0_PKTDMA_0_PKTDMA_CFG_GCFG,
		.cfg = &mmr_MCU_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RING,
		.rt = &mmr_MCU_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RINGRT,
		.mon = NULL,
		.fifos = NULL,
		.n_ring = 0U,
		.ring_oes_offset = 0U,
		.ring_types = &ring_types_MCU_SA3_SS0_PKTDMA_0[0U],
		.n_ring_type = ARRAY_SIZE(ring_types_MCU_SA3_SS0_PKTDMA_0),
		.err_evt_index = RA_GCFG_ERROR_EVT_INDEX,
		.err_evt_utype = RESASG_UTYPE(J721S2_DEV_MCU_SA3_SS0_PKTDMA_0, RESASG_SUBTYPE_RA_ERROR_OES),
		.virtid_utype = 0U,
		.n_ring_mon = 0U,
		.ring_mon_utype = 0U,
		.ring_mon_oes_offset = 0U,
		.rom_usage = NULL,
		.n_rom_usage = 0U,
	},
	{
		.id = J721S2_DEV_MCU_SA3_SS0_RINGACC_0,
		.root_id = J721S2_DEV_MCU_SA3_SS0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_J721S2_TIFS_INTERNAL,
		.gcfg = &mmr_MCU_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_GCFG,
		.cfg = &mmr_MCU_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG,
		.rt = &mmr_MCU_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_RT,
		.mon = NULL,
		.fifos = NULL,
		.n_ring = RA_MCU_SA3_SS0_RINGACC_0_MAX_INDEX,
		.ring_oes_offset = RA_MCU_SA3_SS0_RINGACC_0_RING_OES_EVT_INDEX_OFFSET,
		.ring_types = &ring_types_MCU_SA3_SS0_RINGACC_0[0U],
		.n_ring_type = ARRAY_SIZE(ring_types_MCU_SA3_SS0_RINGACC_0),
		.err_evt_index = RA_GCFG_ERROR_EVT_INDEX,
		.err_evt_utype = RESASG_UTYPE(J721S2_DEV_MCU_SA3_SS0_RINGACC_0, RESASG_SUBTYPE_RA_ERROR_OES),
		.virtid_utype = RESASG_UTYPE(J721S2_DEV_MCU_SA3_SS0_RINGACC_0, RESASG_SUBTYPE_RA_VIRTID),
		.n_ring_mon = 0U,
		.ring_mon_utype = 0U,
		.ring_mon_oes_offset = 0U,
		.rom_usage = NULL,
		.n_rom_usage = 0U,
	},
};

const u32 ra_inst_count = ARRAY_SIZE(ra_inst);
