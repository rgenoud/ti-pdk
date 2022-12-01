/*
 * Device Manager - LPM interface
 *
 * TISCI_MSG_PREPARE_SLEEP and TISCI_MSG_ENTER_SLEEP handler for
 * Low Power Mode implementation
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
//#define DEBUG_SUSPEND
#include <lib/ioremap.h>
#include <types/errno.h>
#include <string.h>
#include <tisci/lpm/tisci_lpm.h>
#include <osal/osal_clock_user.h>
#include <osal_hwi.h>
#include <osal_dm.h>
#include "gtc.h"
#include "lpm_handler.h"
#include "padcfg.h"
#include "device.h"
#include "device_pm.h"
#include "devices.h"
#ifndef SOC_J7200
/* following include didn't work with this SoC */
#include "sec_proxy.h"
#endif
#include <ti/csl/soc.h>
#include "clk.h"

#ifdef DEBUG_SUSPEND
#include <ti/drv/uart/UART_stdio.h>
#define debug_printf UART_printf
#else
#define debug_printf(...)
#endif

/* TODO move the base addresses to device specific header files. */
#define WKUP_CTRL_BASE             (0x43000000UL)
#define WKUP_CTRL_WFI_STATUS       (0x18400UL)
#define SMS_CPU0_WFI               BIT(2)

#define DS_DM_RESET_UNMASK              0xF
#define DS_DM_RESET                     (0x00018440U)

/* counts of 1us delay for 10ms */
#define TIMEOUT_10MS                    10000

#if defined (SOC_J7200)
#define POWER_MASTER J7200_DEV_A72SS0_CORE0 /* to conftim */
#else
#define DEV_GTC AM62X_DEV_WKUP_GTC0
#define POWER_MASTER AM62X_DEV_A53SS0_CORE_0
#endif

extern void _stub_start(void);
extern void lpm_populate_prepare_sleep_data(struct tisci_msg_prepare_sleep_req *p);
extern void go_retention(uint32_t core_resume_addr);

u32 key;

static s32 lpm_sleep_wait_for_tifs_wfi()
{
	u32 reg;
	int i = 0;

	do {
		reg = readl(WKUP_CTRL_BASE + WKUP_CTRL_WFI_STATUS);
		if ((reg & SMS_CPU0_WFI) == SMS_CPU0_WFI) {
			return SUCCESS;
		}
		osal_delay(1);
	} while (i++ < TIMEOUT_10MS);

	return -ETIMEDOUT;
}

static s32 lpm_sleep_disable_sec_lpsc()
{
	/* Disable security LPSCs */
	return SUCCESS;
}

static s32 lpm_sleep_disable_misc_lpsc()
{
	/* Disable non-crtitical  LPSCs */
	return SUCCESS;
}

static s32 lpm_resume_enable_lpsc()
{
	/* enable LPSCs as needed for cores to resume */
	return SUCCESS;
}

static s32 lpm_resume_disable_DM_reset_isolation()
{
	/* Clear WKUP_CTRL DS_DM_RESET.mask to stop
	* isolation of DM from MAIN domain
	*/
	writel(DS_DM_RESET_UNMASK, WKUP_CTRL_BASE + DS_DM_RESET);
	return SUCCESS;
}

static s32 lpm_resume_restore_RM_context()
{
	/* restore IA and IR configurations */
	return SUCCESS;
}

#ifndef SOC_J7200
static s32 lpm_resume_send_core_resume_message()
{
	/* send core resume message */
	s32 ret = 0;

	struct tisci_msg_core_resume_req req = {
		.hdr		= {
			.type	= TISCI_MSG_CORE_RESUME,
			.flags	= TISCI_MSG_FLAG_AOP,
			.host	= HOST_ID_DM2TIFS
		}
	};

	ret = sproxy_send_msg_dm2dmsc_fw(&req, sizeof(req));

	if (ret) {
		return ret;
	}

	struct tisci_msg_core_resume_resp resp;
	memset(&resp, 0, sizeof(resp));
	ret = sproxy_receive_msg_dm2dmsc_fw(&resp, sizeof(resp));

	if (ret) {
		return ret;
	}

	if (resp.hdr.type != TISCI_MSG_CORE_RESUME || (resp.hdr.flags & (TISCI_MSG_FLAG_ACK != TISCI_MSG_FLAG_ACK))) {
		ret = -EINVAL;
	}

	return ret;
}
#endif

static s32 lpm_suspend_power_master()
{
	/* release reset of power master */
	struct device *dev;
#ifndef SOC_J7200
	dev = device_lookup(DEV_GTC);
	soc_device_ret_disable(dev);
	soc_device_disable(dev, SFALSE);
#endif

	dev = device_lookup(POWER_MASTER);
	soc_device_ret_disable(dev);
	soc_device_disable(dev, SFALSE);

#ifndef SOC_J7200
	dev = device_lookup(AM62X_DEV_A53SS0);
	soc_device_ret_disable(dev);
	soc_device_disable(dev, SFALSE);
#endif

	return SUCCESS;
}

static s32 lpm_resume_release_reset_of_power_master()
{
	/* release reset of power master */
	struct device *dev;
#ifndef SOC_J7200
	dev = device_lookup(AM62X_DEV_A53SS0);
	soc_device_enable(dev);
#endif

	dev = device_lookup(POWER_MASTER);
	soc_device_enable(dev);

#ifndef SOC_J7200
	dev = device_lookup(DEV_GTC);
	soc_device_enable(dev);
#endif

	return SUCCESS;
}

static s32 lpm_sleep_suspend_dm()
{
	/* Suspend DM OS */
#ifndef SOC_J7200
	/* these function are actually void so do not need to build osal */
	osal_dm_disable_interrupt();    /* Disable sciserver interrupt */
	osal_suspend_dm();              /* Suspend DM task scheduler */
#endif
	key = osal_hwip_disable();      /* Disable Global interrupt */
	return SUCCESS;
}

static s32 lpm_resume_dm()
{
	/* Resume DM OS */
#ifndef SOC_J7200
	/* these function are actually void so do not need to build osal */
	osal_dm_enable_interrupt();     /* Enable sciserver interrupts */
	osal_resume_dm();               /* Resume DM task scheduler */
#endif
	osal_hwip_restore(key);         /* Enable Global interrupts */
	return SUCCESS;
}

static s32 lpm_sleep_jump_to_dm_Stub()
{
	/* Jump to DM stub */
	_stub_start();
	return SUCCESS;
}

s32 dm_prepare_sleep_handler(u32 *msg_recv)
{
	struct tisci_msg_prepare_sleep_req *req =
		(struct tisci_msg_prepare_sleep_req *) msg_recv;
	s32 ret = SUCCESS;
	u8 mode = req->mode;

	/* Only DEEP_SLEEP mode supported at the moment */
	if (mode == TISCI_MSG_VALUE_SLEEP_MODE_DEEP_SLEEP) {
		/* Parse and store the mode info and ctx address in the prepare sleep message*/
		lpm_populate_prepare_sleep_data(req);
		/* TODO: Parse and store the mode info and ctx address */
		/* TODO: Forward TISCI_MSG_PREPARE_SLEEP to TIFS */
	} else {
		ret = -EINVAL;
	}

	return ret;
}

s32 dm_enter_sleep_handler(u32 *msg_recv)
{
	uint32_t core_resume_addr;
	struct tisci_msg_enter_sleep_req *req =
		(struct tisci_msg_enter_sleep_req *) msg_recv;
	/*
	struct tisci_msg_enter_sleep_resp *resp =
	        (struct tisci_msg_enter_sleep_resp *) msg_recv;
	*/
	s32 ret = SUCCESS;
	u8 mode = req->mode;
	if (req->core_resume_hi)
		debug_printf("Adress too high, not reachable, upper 32bits=%x\n",
			    req->core_resume_hi);
	core_resume_addr = req->core_resume_lo;
	debug_printf("enter sleep mode=%X \n", mode);


	/* Only DEEP_SLEEP mode supported at the moment */
	if (mode == TISCI_MSG_VALUE_SLEEP_MODE_DEEP_SLEEP) {
#ifndef SOC_J7200
		ret = lpm_sleep_wait_for_tifs_wfi();
#endif

		debug_printf("%s (%d)\n", __func__, __LINE__);
		lpm_suspend_power_master();

		debug_printf("%s (%d)\n", __func__, __LINE__);
		devices_deinit(PM_DEVGRP_00);

		debug_printf("%s (%d)\n", __func__, __LINE__);
		if (ret == SUCCESS) {
			ret = lpm_sleep_disable_sec_lpsc();
		}
		debug_printf("%s (%d)\n", __func__, __LINE__);

		if (ret == SUCCESS) {
			ret = lpm_sleep_disable_misc_lpsc();
		}
		debug_printf("%s (%d)\n", __func__, __LINE__);

		if (ret == SUCCESS) {
			ret = lpm_sleep_save_main_padconf();
		}
		debug_printf("%s (%d)\n", __func__, __LINE__);

#ifndef SOC_J7200
		if (ret == SUCCESS) {
			ret = lpm_sleep_suspend_gtc();
		}
		debug_printf("%s (%d)\n", __func__, __LINE__);
#endif

		if (ret == SUCCESS) {
			ret = clks_suspend();
		}
		debug_printf("%s (%d)\n", __func__, __LINE__);

		if (ret == SUCCESS) {
			ret = lpm_sleep_suspend_dm();
		}
		debug_printf("%s (%d)\n", __func__, __LINE__);

		if (ret == SUCCESS) {
			go_retention(core_resume_addr);
		}
		debug_printf("%s (%d)\n", __func__, __LINE__);

		if (ret == SUCCESS) {
			ret = lpm_resume_enable_lpsc();
		}
		debug_printf("%s (%d)\n", __func__, __LINE__);

		if (ret == SUCCESS) {
			ret = lpm_resume_disable_DM_reset_isolation();
		}
		debug_printf("%s (%d)\n", __func__, __LINE__);

		if (ret == SUCCESS) {
			ret = lpm_resume_restore_RM_context();
		}

		if (ret == SUCCESS) {
			ret = clks_resume();
		}
#ifndef SOC_J7200
		if (ret == SUCCESS) {
			ret = lpm_resume_gtc();
		}
#endif

		if (ret == SUCCESS) {
#ifndef SOC_J7200
			/* no support in the SM firmware for this message */
			ret = lpm_resume_send_core_resume_message();
#endif
		}

		if (ret == SUCCESS) {
			ret = lpm_resume_dm();
		}

		devices_init();

		if (ret == SUCCESS) {
			ret = lpm_resume_release_reset_of_power_master();
		}

		if (ret == SUCCESS) {
			ret = lpm_resume_restore_main_padconf();
		}
	} else {
		ret = -EINVAL;
	}

	return ret;
}
