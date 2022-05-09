/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/sciclient/soc/sysfw/include/am62x/tisci_hosts.h>
#include <ti/drv/sciclient/soc/sysfw/include/am62x/tisci_boardcfg_constraints.h>
#include <ti/drv/sciclient/soc/V5/sciclient_defaultBoardcfg.h>

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

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
            .size = (uint16_t) sizeof(struct tisci_boardcfg_proc_acl),
        },
        .proc_acl_entries = {0},
    },

    /* boardcfg_host_hierarchy */
    .host_hierarchy = {
        .subhdr = {
            .magic = TISCI_BOARDCFG_HOST_HIERARCHY_MAGIC_NUM,
            .size = (uint16_t) sizeof(struct tisci_boardcfg_host_hierarchy),
        },
        .host_hierarchy_entries = {0},
    },

    /* OTP access configuration */
    .otp_config = {
        .subhdr = {
            .magic = TISCI_BOARDCFG_OTP_CFG_MAGIC_NUM,
            .size = sizeof(struct tisci_boardcfg_extended_otp),
        },
        /* Host ID 0 is DMSC. This means no host has write acces to OTP array */
        .write_host_id = TISCI_HOST_ID_MAIN_0_R5_0,
        /* This is an array with 32 entries */
        .otp_entry =  {
            {TISCI_HOST_ID_ALL, 0x2U},
            {TISCI_HOST_ID_ALL, 0x2U},
            {TISCI_HOST_ID_ALL, 0x2U},
            {TISCI_HOST_ID_ALL, 0x2U},
            {TISCI_HOST_ID_ALL, 0x2U},
            {TISCI_HOST_ID_ALL, 0x2U},
            {TISCI_HOST_ID_ALL, 0x2U}, 
            {TISCI_HOST_ID_ALL, 0x2U},
            {TISCI_HOST_ID_ALL, 0x2U},
            {TISCI_HOST_ID_ALL, 0x2U},
            {TISCI_HOST_ID_ALL, 0x2U},
            {TISCI_HOST_ID_ALL, 0x2U},
            {TISCI_HOST_ID_ALL, 0x2U},
            {TISCI_HOST_ID_ALL, 0x2U},
            {TISCI_HOST_ID_ALL, 0x2U},
            {TISCI_HOST_ID_ALL, 0x2U},
            {TISCI_HOST_ID_ALL, 0x2U},
            {TISCI_HOST_ID_ALL, 0x2U},
            {TISCI_HOST_ID_ALL, 0x2U},
            {TISCI_HOST_ID_ALL, 0x2U},
            {TISCI_HOST_ID_ALL, 0x2U},
            {TISCI_HOST_ID_ALL, 0x2U},
            {TISCI_HOST_ID_ALL, 0x2U},
            {TISCI_HOST_ID_ALL, 0x2U},
            {TISCI_HOST_ID_ALL, 0x2U},
            {TISCI_HOST_ID_ALL, 0x2U},
            {TISCI_HOST_ID_ALL, 0x2U},
            {TISCI_HOST_ID_ALL, 0x2U},
            {TISCI_HOST_ID_ALL, 0x2U},
            {TISCI_HOST_ID_ALL, 0x2U},
            {TISCI_HOST_ID_ALL, 0x2U},
            {TISCI_HOST_ID_ALL, 0x2U},
        }
    },
    /* DKEK configuration */
    .dkek_config = {
        .subhdr = {
            .magic = TISCI_BOARDCFG_DKEK_CFG_MAGIC_NUM,
            .size = sizeof(struct tisci_boardcfg_dkek),
        },
        .allowed_hosts = { TISCI_HOST_ID_MAIN_0_R5_0, TISCI_HOST_ID_ALL, 0, 0 },
        .allow_dkek_export_tisci = 0x5A,
        .rsvd = {0, 0, 0},
    },
    /* SA2UL RM config */
    .sa2ul_auth_cfg = {
        .subhdr = {
            .magic = TISCI_BOARDCFG_SA2UL_CFG_MAGIC_NUM_RSVD,
            .size = 0,
        },
        .auth_resource_owner = 0,
        .rsvd = {0, 0, 0},
    },
    /* Secure JTAG Unlock Configuration */

    .sec_dbg_config = {
        .subhdr = {
            .magic = TISCI_BOARDCFG_SEC_DBG_CTRL_MAGIC_NUM,
            .size = sizeof(struct tisci_boardcfg_secure_debug_config),
        },
        .allow_jtag_unlock = 0U,
        .allow_wildcard_unlock = 0x0,
        .min_cert_rev = 0x0,
        .jtag_unlock_hosts = {0, 0, 0, 0},
    },
    .sec_handover_cfg = {
		.subhdr = {
			.magic = TISCI_BOARDCFG_SEC_HANDOVER_CFG_MAGIC_NUM,
			.size = sizeof(struct tisci_boardcfg_sec_handover),
		},
		.handover_msg_sender = TISCI_HOST_ID_MAIN_0_R5_0,
		.handover_to_host_id = TISCI_HOST_ID_MAIN_0_R5_0,
		.rsvd = {0,0,0,0},
	},
};
#endif

