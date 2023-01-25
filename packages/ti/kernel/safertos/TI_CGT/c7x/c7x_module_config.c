/*
 * Copyright (c) 2021, Texas Instruments Incorporated
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
/*
 *  ======== c7x_module_config.c ========
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>
#include <c7x.h>
#include <Cache.h>
#include <Hwi.h>
#include <Mmu.h>

/* enableCache__C */
#pragma DATA_SECTION(Cache_enableCache, ".const:Cache_enableCache");
const bool Cache_enableCache = 1;

/* initSize */
#pragma DATA_SECTION(Cache_initSize, ".const:Cache_initSize");
const Cache_Size Cache_initSize = {
    Cache_L1Size_32K,  /* l1pSize */
    Cache_L1Size_32K,  /* l1dSize */
    Cache_L2Size_0K,  /* l2Size */
};

void vInitMmu( void );

/* initFunc */
#pragma DATA_SECTION(Mmu_initFunc, ".const:Mmu_initFunc");
const Mmu_InitFuncPtr Mmu_initFunc = ((Mmu_InitFuncPtr)(vInitMmu));


/* dispatcherAutoNestingSupport */
#pragma DATA_SECTION(Hwi_dispatcherAutoNestingSupport, ".const:Hwi_dispatcherAutoNestingSupport");
const bool Hwi_dispatcherAutoNestingSupport = 0;

/* DEFAULT_INT_PRIORITY */
#pragma DATA_SECTION(Hwi_DEFAULT_INT_PRIORITY, ".const:Hwi_DEFAULT_INT_PRIORITY");
const unsigned int Hwi_DEFAULT_INT_PRIORITY = (unsigned int)0x6U;

