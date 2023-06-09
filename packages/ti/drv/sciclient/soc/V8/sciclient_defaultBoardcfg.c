/*
 * DMSC firmware test for TISCI_MSG_BOARD_CONFIG
 *
 * Copyright (C) 2021 Texas Instruments Incorporated - http://www.ti.com/
 *
 * This software is licensed under the standard terms and conditions in the
 * Texas Instruments Incorporated Technology and Software Publicly
 * Available Software License Agreement, a copy of which is included in
 * the software download.
 */


#include <ti/drv/sciclient/soc/sysfw/include/am62a/tisci_hosts.h>
#include <ti/drv/sciclient/soc/sysfw/include/am62a/tisci_boardcfg_constraints.h>
#include <ti/drv/sciclient/soc/V7/sciclient_defaultBoardcfg.h>

#if defined(BUILD_MCU1_0)
const struct tisci_boardcfg gBoardConfigLow
	__attribute__((aligned(128), section(".boardcfg_data"))) =
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
				.main_isolation_hostid = 0x2,
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
				.msmc_cache_size = 0x10,
			},

			/* boardcfg_dbg_cfg */
			.debug_cfg = {.subhdr = {
							  .magic = TISCI_BOARDCFG_DBG_CFG_MAGIC_NUM,
							  .size = sizeof(struct tisci_boardcfg_dbg_cfg),
						  },
						  /* This enables the trace for DMSC logging. Should be used only for
         * debug.
         */
						  /* Uncomment for Debug */
						  
        .trace_dst_enables = (TISCI_BOARDCFG_TRACE_DST_UART0 |
                              TISCI_BOARDCFG_TRACE_DST_ITM |
                              TISCI_BOARDCFG_TRACE_DST_MEM),
        .trace_src_enables = (TISCI_BOARDCFG_TRACE_SRC_PM |
                              TISCI_BOARDCFG_TRACE_SRC_RM |
                              TISCI_BOARDCFG_TRACE_SRC_SEC |
                              TISCI_BOARDCFG_TRACE_SRC_BASE |
                              TISCI_BOARDCFG_TRACE_SRC_USER |
                              TISCI_BOARDCFG_TRACE_SRC_SUPR)
        // 
		// 				  .trace_dst_enables = 0,
		// 				  .trace_src_enables = 0
						  },
};

#endif
