/*
 * Copyright (c) 2015-2021, Texas Instruments Incorporated
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
 *  ======== Cache.c ========
 */
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>
#include <c7x.h>

#include "Hwi.h"
#include "Mmu.h"

#include <c6x_migration.h>
#include <c7x.h>

#include "Cache.h"

#include <ti/osal/DebugP.h>

/*
 *  ======== Cache_Module_startup ========
 */
void Cache_Module_startup(void)
{
    Cache_enable(Cache_Type_L1D);
    Cache_enableWB(Cache_Type_L1D);
}

/*
 *  ======== Cache_enable ========
 *  Enables the L1D Cache
 */
void Cache_enable(uint16_t type)
{
    /* Enable L1D cache */
    if (type == Cache_Type_L1D)
    {
        uint64_t L1D_cfg = Cache_getL1DCFG();
        L1D_cfg |= 1U;
        Cache_setL1DCFG(L1D_cfg);
        Cache_Module_state.L1DCFG = L1D_cfg;
    }
}

/*
 *  ======== Cache_disable ========
 *  Disables the L1D Cache
 */
void Cache_disable(uint16_t type)
{
    /* Disable L1D cache */
    if (type == Cache_Type_L1D)
    {
        uint64_t L1D_cfg = Cache_getL1DCFG();
        L1D_cfg &= ~((uint64_t) 1);
        Cache_setL1DCFG(L1D_cfg); 
        Cache_Module_state.L1DCFG = L1D_cfg;       
    }
}

/*
 *  ======== Cache_enableWB ========
 *  Enables the Cache writeback
 */
void Cache_enableWB(uint16_t type)
{
    /* Enable writeback */
    if (type == Cache_Type_L1D)
    {
        uint64_t L1D_cfg = Cache_getL1DCFG();
        L1D_cfg |= 0x10U;
        Cache_setL1DCFG(L1D_cfg);
        Cache_Module_state.L1DCFG = L1D_cfg;
    }
}

/*
 *  ======== Cache_enableWT ========
 *  Enables the Cache writeback
 */
void Cache_enableWT(uint16_t type)
{
    /* Disabling the Writeback enable write through */
    if (type == Cache_Type_L1D)
    {
        uint64_t L1D_cfg = Cache_getL1DCFG();
        L1D_cfg &= ~((uint64_t) 0x10U);
        Cache_setL1DCFG(L1D_cfg);
        Cache_Module_state.L1DCFG = L1D_cfg;
    }
}

/*
 *  ======== Cache_getSize ========
 *  Returns the L1D size. 
 */
void Cache_getSize(Cache_Size *size)
{    
    /*
     * L1D is a non-configurable 64KB cache.
     */
    size->l1dSize = (Cache_L1Size)Cache_L1Size_64K;
}

/*
 *  ======== Cache_wbAll ========
 *  Perform a global write back.  All cache lines are left valid in L1D 
 *  cache and the data in L1D cache is written back external. 
 */
void Cache_wbAll()
{
    Cache_setL1DWB(1);
}

/*
 *  ======== Cache_wbL1dAll ========
 *  Performs a global write back of L1D cache
 */
void Cache_wbL1dAll()
{
    Cache_setL1DWB(1);
}

/*
 *  ======== Cache_wbInvAll ========
 *  Performs a global write back and invalidate. All cache lines are written back 
 *  to external then invalidated in L1D cache.  
 */

void Cache_wbInvAll()
{
    Cache_setL1DWBINV(1);
}

/*
 *  ======== Cache_wbInvL1dAll ========
 *  Performs a global write back then invalidate of L1D cache
 */
void Cache_wbInvL1dAll()
{
    Cache_setL1DWBINV(1);
}

/*
 *  ======== Cache_invAll ========
 *  Performs a global invalidate of L1D cache. This does not trigger writeback.
 */
void Cache_invL1dAll()
{
    Cache_setL1DINV(1);
}

/*
 *  ======== Cache_inv ========
 *  Invalidate the range of memory within the specified starting address and
 *  byte count.  The range of addresses operated on gets quantized to whole
 *  cache lines in each cache.  All cache lines in range are invalidated in L1D
 *  cache. 
 */
void Cache_inv(void * blockPtr, size_t byteCnt, uint16_t type, bool wait)
{
    __se_cache_op((void *)blockPtr, __DCCMIC, byteCnt);

    if (wait) {
        Cache_wait();
    }
}

/*
 *  ======== Cache_wb ========
 *  Writes back the range of memory within the specified starting address
 *  and byte count.  The range of addresses operated on gets quantized to
 *  whole cache lines in each cache.  All cache lines within the range 
 *  are left valid in L1D cache and the data within the range in L1D cache 
 *  will be written back to external.
 */
void Cache_wb(void * blockPtr, size_t byteCnt, uint16_t type, bool wait)
{
    /*
     * There is no SE operation for just WB, so do the next closest thing
     * which is WBINV.
     */
    __se_cache_op((void *)blockPtr, __DCCIC, byteCnt);

    if (wait) {
        Cache_wait();
    }
}

/*
 *  ======== Cache_wbInv ========
 *  Writes back and invalidates the range of memory within the specified
 *  starting address and byte count.  The range of addresses operated on gets
 *  quantized to whole cache lines in each cache.  All cache lines within 
 *  the range are written back to external and then invalidated in L1D cache.
 */
void Cache_wbInv(void * blockPtr, size_t byteCnt, uint16_t type, bool wait)
{
    __se_cache_op((void *)blockPtr, __DCCIC, byteCnt);

    if (wait) {
        Cache_wait();
    }
}


/*
 *  ======== Cache_wait ========
 *  Wait for the cache operation to complete.
 */
void Cache_wait()
{
    __SE0ADV(char);
    /*
     *  Stall CPU while memory system is busy.
     */
    _mfence();

}


/* Module_state */
#ifdef __ti__
struct Cache_Module_State Cache_Module_state __attribute__ ((section(".data:Cache_Module_state")));
#elif !(defined(__MACH__) && defined(__APPLE__))
struct Cache_Module_State Cache_Module_state __attribute__ ((section(".data:Cache_Module_state")));
#endif
struct Cache_Module_State Cache_Module_state = {
    (uint64_t)0x11U,  /* L1DCFG */ /* L1DWBEN and L1DON */
};


/* atomicBlockSize */
#pragma DATA_SECTION(Cache_atomicBlockSize, ".const:Cache_atomicBlockSize");
const uint32_t Cache_atomicBlockSize = (uint32_t)0x400U;
