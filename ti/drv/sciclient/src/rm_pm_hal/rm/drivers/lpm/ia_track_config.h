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

#ifndef IA_TRK_CFG_H
#define IA_TRK_CFG_H

#include <config.h>
#include <lpm_ia_cfg.h>
#include <types/short_types.h>

#ifdef CONFIG_LPM_LIMIT_IA_IR_TRACKING
#define NUM_IA_CONFIGS                  256
#else
#define NUM_IA_CONFIGS                  65535
#endif

/**
 * \brief Struct for containing all of the IA configuration parameters
 *
 * \param id
 * IA SoC device ID
 *
 * \param vint
 * IA virtual interrupt
 *
 * \param global_evt
 * Global event to map to VINT status bit
 *
 * \param vint_sb_index
 * Virtual interrupt status bit to map to global event
 *
 * \param fwl_cfg_dmsc_only STRUE to explicitly program only DMSC with RW access
 *
 * \param validate_sec_rm_devgrp STRUE to validate against the configured
 *                               Secure RM devgrp
 */
struct ia_config_entry {
	u16	id;
	u16	vint;
	u16	global_evt;
	u8	vint_sb_index;
	sbool	fwl_cfg_dmsc_only;
	sbool	validate_sec_rm_devgrp;
} __attribute__((__packed__));

/**
 * \brief List of the sec proxy IA global event numbers
 */
extern const u16 sec_proxy_ia_global_events[NUM_SEC_PROXY_IA_GLOBAL_EVENTS];

#endif /* IA_TRK_CFG_H */
