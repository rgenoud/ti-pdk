/******************************************************************************
 * Copyright (c) 2015 Texas Instruments Incorporated - http://www.ti.com
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *****************************************************************************/

#include "keystone_pll.h"

const keystonePllcReg keystonePllcRegs[] = {
	{CSL_BOOT_CFG_REGS + 0x350, CSL_BOOT_CFG_REGS + 0x354}, /* system PLL */
	{CSL_BOOT_CFG_REGS + 0x358, CSL_BOOT_CFG_REGS + 0x35c}, /* PA PLL */
	{CSL_BOOT_CFG_REGS + 0x370, CSL_BOOT_CFG_REGS + 0x374}, /* ARM PLL */
	{CSL_BOOT_CFG_REGS + 0x360, CSL_BOOT_CFG_REGS + 0x364}, /* DDR3A PLL */
	{0,                         0}                          /* no DDR3B PLL */
};

const pllcConfig pllcConfigs[] = {
    {CSL_PLL_SYS,    16,     1,      2}, /* 983 MHz */
    {CSL_PLL_PA,     16,     1,      2}, /* 983 MHz*/
    {CSL_PLL_ARM,    16,     1,      2}, /* 983 MHz*/
    {CSL_PLL_DDR3,   16,     1,      4}  /* 400 MHz*/
};

uint32_t Board_getNumPllcConfigs()
{
    return (sizeof(pllcConfigs) / sizeof(pllcConfig));
}

