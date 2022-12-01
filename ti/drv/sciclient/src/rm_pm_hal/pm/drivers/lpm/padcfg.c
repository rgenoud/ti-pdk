/*
 * Device Manager - Manage PADCFG Ctrl MMR during Suspend/Resume
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

#include <lib/ioremap.h>
#include <lib/mmr_lock.h>
#include <types/errno.h>
#include <ti/csl/soc.h>

/* TODO move the base addresses to device specific header files. */
#ifdef SOC_J7200
#define PADCFG_CTRL_BASE    (CSL_CTRL_MMR0_CFG0_BASE)
#define PADCFG_OFFSET	    (CSL_MAIN_CTRL_MMR_CFG0_PADCONFIG0)
#define PADCFG_SIZE	    (67 + 6) /* 0 to 66, 68, 71, 72, 73, 89,90 */
#else
#define PADCFG_CTRL_BASE    (0xf0000UL)
#define PADCFG_OFFSET	    (0x4000U)
#define PADCFG_SIZE	    (((0x42a8U - PADCFG_OFFSET) >> 2) + 1)
#endif
static u32 padcfg_data[PADCFG_SIZE];

static void get_pad(u32 i, u32 p)
{
	padcfg_data[i] = readl(p);
}

s32 lpm_sleep_save_main_padconf()
{
	u32 p = PADCFG_CTRL_BASE + PADCFG_OFFSET;
	u32 i;

#ifdef SOC_J7200
	for (i = 0; i < 67; i++, p+=4) {
#else
	for (i = 0; i < PADCFG_SIZE; i++, p+=4){
#endif
		padcfg_data[i] = readl(p);
	}

#ifdef SOC_J7200
	get_pad(i++, PADCFG_CTRL_BASE + PADCFG_OFFSET + 68*4);
	get_pad(i++, PADCFG_CTRL_BASE + PADCFG_OFFSET + 71*4);
	get_pad(i++, PADCFG_CTRL_BASE + PADCFG_OFFSET + 72*4);
	get_pad(i++, PADCFG_CTRL_BASE + PADCFG_OFFSET + 73*4);
	get_pad(i++, PADCFG_CTRL_BASE + PADCFG_OFFSET + 89*4);
	get_pad(i++, PADCFG_CTRL_BASE + PADCFG_OFFSET + 90*4);
#endif
	return SUCCESS;
}

s32 lpm_resume_restore_main_padconf()
{
	u32 p = PADCFG_CTRL_BASE + PADCFG_OFFSET;
	u32 i;

#ifdef SOC_J7200
	mmr_unlock(PADCFG_CTRL_BASE, 5);
#else
	mmr_unlock(PADCFG_CTRL_BASE, 1);
#endif

	for (i = 0; i < PADCFG_SIZE; i++, p+=4) {
		writel(padcfg_data[i], p);
	}

	return SUCCESS;
}
