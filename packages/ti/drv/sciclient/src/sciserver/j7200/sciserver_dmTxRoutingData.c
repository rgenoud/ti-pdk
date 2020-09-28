/*
 * Copyright (c) 2020, Texas Instruments Incorporated
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
 * \file dm_tx_routing_data.c
 *
 * \brief DM Tx Routing Data
 */

#include <hosts.h>
#include <sciserver_secproxyConfigData.h>
#include <sciserver_secproxyRoutingDescription.h>

/** Maximum Host Entries */
#define J7200_CONFIG_MAX (0xFFU)

const uint16_t sproxy_route_data_count = J7200_CONFIG_MAX;

const struct sproxy_host_tx_thread_data sproxy_route_data[J7200_CONFIG_MAX] = {
	/*
	 * Secure Host MCU_0_R5_1[4]
	 */
	[HOST_ID_MCU_0_R5_1] =	{
		.sproxy_resp_conf_id	= J7200_MCU_NAVSS0_SEC_PROXY0_TX_DMSC_SEC_MCU_0_R5_1_RESPONSE_TX_THR085_CONF046,
		.sproxy_ntfy_conf_id	= J7200_MCU_NAVSS0_SEC_PROXY0_TX_DMSC_SEC_MCU_0_R5_1_NOTIFY_TX_THR086_CONF045,
	},
	/*
	 * Secure Host MCU_0_R5_3[6]
	 */
	[HOST_ID_MCU_0_R5_3] =	{
		.sproxy_resp_conf_id	= J7200_MCU_NAVSS0_SEC_PROXY0_TX_DMSC_SEC_MCU_0_R5_3_RESPONSE_TX_THR083_CONF048,
		.sproxy_ntfy_conf_id	= J7200_MCU_NAVSS0_SEC_PROXY0_TX_DMSC_SEC_MCU_0_R5_3_NOTIFY_TX_THR084_CONF047,
	},
	/*
	 * Secure Host A72_0[10]
	 */
	[HOST_ID_A72_0] =	{
		.sproxy_resp_conf_id	= J7200_NAVSS0_SEC_PROXY_0_TX_DMSC_SEC_A72_0_RESPONSE_TX_THR155_CONF001,
		.sproxy_ntfy_conf_id	= J7200_NAVSS0_SEC_PROXY_0_TX_DMSC_SEC_A72_0_NOTIFY_TX_THR156_CONF000,
	},
	/*
	 * Secure Host A72_1[11]
	 */
	[HOST_ID_A72_1] =	{
		.sproxy_resp_conf_id	= J7200_NAVSS0_SEC_PROXY_0_TX_DMSC_SEC_A72_1_RESPONSE_TX_THR153_CONF003,
		.sproxy_ntfy_conf_id	= J7200_NAVSS0_SEC_PROXY_0_TX_DMSC_SEC_A72_1_NOTIFY_TX_THR154_CONF002,
	},
	/*
	 * Secure Host MAIN_0_R5_1[36]
	 */
	[HOST_ID_MAIN_0_R5_1] = {
		.sproxy_resp_conf_id	= J7200_NAVSS0_SEC_PROXY_0_TX_DMSC_SEC_MAIN_0_R5_1_RESPONSE_TX_THR151_CONF005,
		.sproxy_ntfy_conf_id	= J7200_NAVSS0_SEC_PROXY_0_TX_DMSC_SEC_MAIN_0_R5_1_NOTIFY_TX_THR152_CONF004,
	},
	/*
	 * Secure Host MAIN_0_R5_3[38]
	 */
	[HOST_ID_MAIN_0_R5_3] = {
		.sproxy_resp_conf_id	= J7200_NAVSS0_SEC_PROXY_0_TX_DMSC_SEC_MAIN_0_R5_3_RESPONSE_TX_THR149_CONF007,
		.sproxy_ntfy_conf_id	= J7200_NAVSS0_SEC_PROXY_0_TX_DMSC_SEC_MAIN_0_R5_3_NOTIFY_TX_THR150_CONF006,
	},
	/*
	 * Secure Host DM2DMSC[250]
	 */
	[HOST_ID_DM2DMSC] =	{
		.sproxy_resp_conf_id	= J7200_MCU_NAVSS0_SEC_PROXY0_TX_DMSC_SEC_DM2DMSC_RESPONSE_TX_THR081_CONF050,
		.sproxy_ntfy_conf_id	= J7200_MCU_NAVSS0_SEC_PROXY0_TX_DMSC_SEC_DM2DMSC_NOTIFY_TX_THR082_CONF049,
	},
};
