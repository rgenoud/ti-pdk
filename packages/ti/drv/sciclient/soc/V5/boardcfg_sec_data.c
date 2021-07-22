#include <boardcfg/boardcfg_data.h>
#include <config.h>

#define SYSFW_TEST_HOST_ID HOST_ID_MAIN_0_R5_0
#define OTHER_HOST_ID HOST_ID_A53_0

struct boardcfg_sec test_boardcfg_security = {
	/* boardcfg_abi_rev */
	.rev = {
		.boardcfg_abi_maj = 0x0,
		.boardcfg_abi_min = 0x1,
	},

	/* boardcfg_proc_acl */
	.processor_acl_list = {
		.subhdr = {
			.magic = BOARDCFG_PROC_ACL_MAGIC_NUM,
			.size = sizeof(struct boardcfg_proc_acl),
		},
		.proc_acl_entries = {0},
	},

	/* boardcfg_host_hierarchy */
	.host_hierarchy = {
		.subhdr = {
			.magic = BOARDCFG_HOST_HIERARCHY_MAGIC_NUM,
			.size = sizeof(struct boardcfg_host_hierarchy),
		},
		.host_hierarchy_entries = {0},
	},
	/* OTP access configuration */
	.otp_config = {
		.subhdr = {
			.magic = BOARDCFG_OTP_CFG_MAGIC_NUM,
			.size = sizeof(struct boardcfg_extended_otp),
		},
#include <boardcfg_sec_otp_fragment.h>
	},
	.dkek_config = {
		.subhdr = {
			.magic = BOARDCFG_DKEK_CFG_MAGIC_NUM,
			.size = sizeof(struct boardcfg_dkek),
		},
		.allowed_hosts = { SYSFW_TEST_HOST_ID, HOST_ID_ALL, 0, 0 },
		.allow_dkek_export_tisci = 0x5A,
		.rsvd = {0, 0, 0},
	},

	/* SA2UL RM config is not supported on this device */
	.sa2ul_cfg = {
		.subhdr = {
			.magic = BOARDCFG_SA2UL_CFG_MAGIC_NUM_RSVD,
			.size = 0,
		},
		.auth_resource_owner = 0,
		.rsvd = {0, 0, 0},
	},
#include <boardcfg_sec_debug_unlock_fragment.h>
	.sec_handover_cfg = {
		.subhdr = {
			.magic = BOARDCFG_SEC_HANDOVER_CFG_MAGIC_NUM,
			.size = sizeof(struct boardcfg_sec_handover),
		},
		.handover_msg_sender = SYSFW_TEST_HOST_ID,
		.handover_to_host_id = SYSFW_TEST_HOST_ID,
		.rsvd = {0,0,0,0},
	},
};
