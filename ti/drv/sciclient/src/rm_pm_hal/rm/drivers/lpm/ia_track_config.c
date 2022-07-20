/*
 * LPM Interrupt Aggregator Tracker
 *
 * LPM management interrupt aggregator tracking infrastructure
 *
 * Copyright (C) 2021-2022, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 * its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
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

#include <boardcfg/boardcfg_rm_data.h>
#include <ia_track_config.h>
#include <rm_ia.h>
#include <rm_lpm.h>
#include <types/errno.h>
#include <types/sbool.h>

static struct ia_config_entry ia_config_data[NUM_IA_CONFIGS] = { 0, 0, 0, 0, SFALSE, SFALSE };

s32 lpm_sleep_save_ia_config(u16 id, u16 vint, u16 global_evt, u8 vint_sb_index,
			     sbool fwl_cfg_dmsc_only, sbool validate_sec_rm_devgrp)
{
	u16 i;
	sbool sec_proxy_ia_global_event = SFALSE;

	/* Check if the config is a sec proxy IA config */
	for (i = 0; i < NUM_SEC_PROXY_IA_GLOBAL_EVENTS; i++) {
		if (global_evt == sec_proxy_ia_global_events[i]) {
			sec_proxy_ia_global_event = STRUE;
		}
	}

	/* Exlude the sec proxy IA configs from being added to the list */
	if (sec_proxy_ia_global_event == SFALSE) {
		/* Insert config into the next empty spot */
		for (i = 0; i < NUM_IA_CONFIGS; i++) {
			if ((ia_config_data[i].id == 0) &&
			    (ia_config_data[i].vint == 0) &&
			    (ia_config_data[i].global_evt == 0) &&
			    (ia_config_data[i].vint_sb_index == 0) &&
			    (ia_config_data[i].fwl_cfg_dmsc_only == SFALSE) &&
			    (ia_config_data[i].validate_sec_rm_devgrp == SFALSE)) {
				ia_config_data[i].id = id;
				ia_config_data[i].vint = vint;
				ia_config_data[i].global_evt = global_evt;
				ia_config_data[i].vint_sb_index = vint_sb_index;
				ia_config_data[i].fwl_cfg_dmsc_only = fwl_cfg_dmsc_only;
				ia_config_data[i].validate_sec_rm_devgrp = validate_sec_rm_devgrp;

				break;
			}
		}
	}

	return SUCCESS;
}

s32 lpm_sleep_save_ia_unconfig(u16 id, u16 vint, u16 global_evt, u8 vint_sb_index)
{
	u16 i;

	/* Remove the entry from the list */
	for (i = 0; i < NUM_IA_CONFIGS; i++) {
		if ((ia_config_data[i].id == id) &&
		    (ia_config_data[i].vint == vint) &&
		    (ia_config_data[i].global_evt == global_evt) &&
		    (ia_config_data[i].vint_sb_index == vint_sb_index)) {
			ia_config_data[i].id = 0;
			ia_config_data[i].vint = 0;
			ia_config_data[i].global_evt = 0;
			ia_config_data[i].vint_sb_index = 0;
			ia_config_data[i].fwl_cfg_dmsc_only = SFALSE;
			ia_config_data[i].validate_sec_rm_devgrp = SFALSE;

			break;
		}
	}

	/*
	 * Remove the empty slot from the middle of the list
	 * by swapping the empty slot with all of the filled slots
	 */
	for (i = 0; i < (NUM_IA_CONFIGS - 1); i++) {
		if ((ia_config_data[i].id == 0) &&
		    (ia_config_data[i].vint == 0) &&
		    (ia_config_data[i].global_evt == 0) &&
		    (ia_config_data[i].vint_sb_index == 0) &&
		    (ia_config_data[i].fwl_cfg_dmsc_only == SFALSE) &&
		    (ia_config_data[i].validate_sec_rm_devgrp == SFALSE)) {
			if ((ia_config_data[i + 1].id == 0) &&
			    (ia_config_data[i + 1].vint == 0) &&
			    (ia_config_data[i + 1].global_evt == 0) &&
			    (ia_config_data[i + 1].vint_sb_index == 0) &&
			    (ia_config_data[i + 1].fwl_cfg_dmsc_only == SFALSE) &&
			    (ia_config_data[i + 1].validate_sec_rm_devgrp == SFALSE)) {
				/* No more filled entries remaining to be swapped */
				break;
			} else {
				/* Next entry is filled, so swap it */

				ia_config_data[i].id = ia_config_data[i + 1].id;
				ia_config_data[i].vint = ia_config_data[i + 1].vint;
				ia_config_data[i].global_evt = ia_config_data[i + 1].global_evt;
				ia_config_data[i].vint_sb_index = ia_config_data[i + 1].vint_sb_index;
				ia_config_data[i].fwl_cfg_dmsc_only = ia_config_data[i + 1].fwl_cfg_dmsc_only;
				ia_config_data[i].validate_sec_rm_devgrp = ia_config_data[i + 1].validate_sec_rm_devgrp;

				ia_config_data[i + 1].id = 0;
				ia_config_data[i + 1].vint = 0;
				ia_config_data[i + 1].global_evt = 0;
				ia_config_data[i + 1].vint_sb_index = 0;
				ia_config_data[i + 1].fwl_cfg_dmsc_only = SFALSE;
				ia_config_data[i + 1].validate_sec_rm_devgrp = SFALSE;
			}
		}
	}

	return SUCCESS;
}

s32 lpm_resume_restore_ia_config()
{
	u16 i;

	for (i = 0; i < NUM_IA_CONFIGS; i++) {
		if ((ia_config_data[i].id == 0) &&
		    (ia_config_data[i].vint == 0) &&
		    (ia_config_data[i].global_evt == 0) &&
		    (ia_config_data[i].vint_sb_index == 0) &&
		    (ia_config_data[i].fwl_cfg_dmsc_only == SFALSE) &&
		    (ia_config_data[i].validate_sec_rm_devgrp == SFALSE)) {
			/* No more entries remaining to be reconfigured */
			break;
		} else {
			u16 temp_id;
			u16 temp_vint;
			u16 temp_global_evt;
			u8 temp_vint_sb_index;
			sbool temp_fwl_cfg_dmsc_only;
			sbool temp_validate_sec_rm_devgrp;

			/* Store the parameters before they are erased */
			temp_id = ia_config_data[i].id;
			temp_vint = ia_config_data[i].vint;
			temp_global_evt = ia_config_data[i].global_evt;
			temp_vint_sb_index = ia_config_data[i].vint_sb_index;
			temp_fwl_cfg_dmsc_only = ia_config_data[i].fwl_cfg_dmsc_only;
			temp_validate_sec_rm_devgrp = ia_config_data[i].validate_sec_rm_devgrp;

			/*
			 * Remove the entry from the list so that way when it's reconfigured
			 * in the next step, it will be re-added to the list in its original
			 * spot, rather than the end of the list
			 */
			ia_config_data[i].id = 0;
			ia_config_data[i].vint = 0;
			ia_config_data[i].global_evt = 0;
			ia_config_data[i].vint_sb_index = 0;
			ia_config_data[i].fwl_cfg_dmsc_only = SFALSE;
			ia_config_data[i].validate_sec_rm_devgrp = SFALSE;

			/* Reconfigure the IA entry */
			rm_ia_vint_map(temp_id,
				       temp_vint,
				       temp_global_evt,
				       temp_vint_sb_index,
				       temp_fwl_cfg_dmsc_only,
				       temp_validate_sec_rm_devgrp);
		}
	}

	return SUCCESS;
}
