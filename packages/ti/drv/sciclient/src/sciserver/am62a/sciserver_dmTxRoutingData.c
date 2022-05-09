/*
 * System Firmware Source File
 *
 * DMSC Tx Routing Data for AM62A device
 *
 * Data version: 220316_180112
 *
 * Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <hosts.h>
#include <sciserver_secproxyConfigData.h>
#include <sciserver_secproxyRoutingDescription.h>

/** Maximum Host Entries */
#define AM62A_CONFIG_MAX (0xFFU)

const uint16_t sproxy_route_data_count = AM62A_CONFIG_MAX;

const struct sproxy_host_tx_thread_data sproxy_route_data[AM62A_CONFIG_MAX] = {
	/*
	 * Secure Host MAIN_0_R5_0[35]
	 */
	[HOST_ID_MAIN_0_R5_0] = {
		.sproxy_resp_conf_id	= AM62A_DMASS0_SEC_PROXY_0_TX_TIFS_SEC_MAIN_0_R5_0_RESPONSE_TX_THR074_CONF000,
		.sproxy_ntfy_conf_id	= AM62A_DMASS0_SEC_PROXY_0_TX_TIFS_SEC_MAIN_0_R5_0_RESPONSE_TX_THR074_CONF000,
	},
	/*
	 * Secure Host MAIN_0_R5_2[37]
	 */
	[HOST_ID_MAIN_0_R5_2] = {
		.sproxy_resp_conf_id	= AM62A_DMASS0_SEC_PROXY_0_TX_TIFS_SEC_MAIN_0_R5_2_RESPONSE_TX_THR073_CONF001,
		.sproxy_ntfy_conf_id	= AM62A_DMASS0_SEC_PROXY_0_TX_TIFS_SEC_MAIN_0_R5_2_RESPONSE_TX_THR073_CONF001,
	},
	/*
	 * Secure Host A53_0[10]
	 */
	[HOST_ID_A53_0] =	{
		.sproxy_resp_conf_id	= AM62A_DMASS0_SEC_PROXY_0_TX_TIFS_SEC_A53_0_RESPONSE_TX_THR072_CONF002,
		.sproxy_ntfy_conf_id	= AM62A_DMASS0_SEC_PROXY_0_TX_TIFS_SEC_A53_0_RESPONSE_TX_THR072_CONF002,
	},
	/*
	 * Secure Host DM2TIFS[250]
	 */
	[HOST_ID_DM2TIFS] =	{
		.sproxy_resp_conf_id	= AM62A_DMASS0_SEC_PROXY_0_TX_TIFS_SEC_DM2TIFS_RESPONSE_TX_THR071_CONF003,
		.sproxy_ntfy_conf_id	= AM62A_DMASS0_SEC_PROXY_0_TX_TIFS_SEC_DM2TIFS_RESPONSE_TX_THR071_CONF003,
	},
	/*
	 * Non Secure Host A53_1[11]
	 */
	[HOST_ID_A53_1] =	{
		.sproxy_resp_conf_id	= AM62A_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_A53_1_RESPONSE_TX_THR067_CONF006,
		.sproxy_ntfy_conf_id	= AM62A_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_A53_1_RESPONSE_TX_THR067_CONF006,
	},
	/*
	 * Secure Host A53_2[12]
	 */
	[HOST_ID_A53_2] =	{
		.sproxy_resp_conf_id	= AM62A_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_A53_2_RESPONSE_TX_THR066_CONF007,
		.sproxy_ntfy_conf_id	= AM62A_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_A53_2_RESPONSE_TX_THR066_CONF007,
	},
	/*
	 * Secure Host A53_3[13]
	 */
	[HOST_ID_A53_3] =	{
		.sproxy_resp_conf_id	= AM62A_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_A53_3_RESPONSE_TX_THR065_CONF008,
		.sproxy_ntfy_conf_id	= AM62A_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_A53_3_RESPONSE_TX_THR065_CONF008,
	},
	/*
	 * Non Secure Host TIFS2DM[251]
	 */
	[HOST_ID_TIFS2DM] =	{
		.sproxy_resp_conf_id	= AM62A_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_TIFS2DM_RESPONSE_TX_THR062_CONF011,
		.sproxy_ntfy_conf_id	= AM62A_DMASS0_SEC_PROXY_0_TX_DM_NONSEC_TIFS2DM_RESPONSE_TX_THR062_CONF011,
	},
	/*
	 * Non Secure Host M4_0[30]
	 */
	[HOST_ID_MCU_0_R5_0] =	{
		.sproxy_resp_conf_id	= AM62A_DMASS0_SEC_PROXY_0_TX_MCU_0_R5_0_LOW_PRIORITY_THR017_CONF020,
		.sproxy_ntfy_conf_id	= AM62A_DMASS0_SEC_PROXY_0_TX_MCU_0_R5_0_LOW_PRIORITY_THR017_CONF020,
	},
};
