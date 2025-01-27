/**  
 * @file fw_test.h
 *
 * @brief 
 *  Holds all the constants and API definitions required by the example
 *  application to run.
 *
 *  \par
 *  ============================================================================
 *  @n   (C) Copyright 2012-2013, Texas Instruments, Inc.
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
*/
#ifndef _FW_TEST_H_
#define _FW_TEST_H_

/* C Standard library Include */
#include <stdio.h>
/* System level header files */
#include <stdint.h>
#include <stdlib.h>

#include <sys/types.h> 
#include <string.h>
#include <ti/drv/pa/pa.h>

/* CPPI LLD include */
#include <ti/drv/cppi/cppi_drv.h>
#include <ti/drv/cppi/cppi_desc.h>

/* QMSS LLD include */
#include <ti/drv/qmss/qmss_drv.h>


#define System_printf   printf
extern  void System_flush(void);

/* OSAL functions */
void fw_osalInit(void);
void fw_osalshutdown(void);
void Osal_fwCsEnter (uint32_t *key);
void Osal_fwCsExit (uint32_t key);

/* 
 * Shut off: remark #880-D: parameter "descType" was never referenced
*
* This is better than removing the argument since removal would break
* backwards compatibility
*/
#ifdef _TMS320C6X
#elif defined(__GNUC__)
/* Same for GCC:
* warning: unused parameter descType [-Wunused-parameter]
*/
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-braces"
#pragma GCC diagnostic ignored "-Wunused-function"
#endif


typedef uint16_t fw_Bool_t;
#define  fw_TRUE  1
#define  fw_FALSE  0

/* Total Permanent memory required in Example
 * for Packet buffers & descriptor buffers
 * Allocating entire MSMC
 */
#define MSMC_TEST_PERM_MEM_SZ   (2*1024*1024)

/* Physical address map & size for various subsystems */
#define QMSS_CFG_BASE_ADDR  CSL_QMSS_CFG_BASE
#define QMSS_CFG_BLK_SZ (0x00200000)
#define QMSS_DATA_BASE_ADDR CSL_QMSS_DATA_BASE
#define QMSS_DATA_BLK_SZ (0x00100000)
#define SRIO_CFG_BASE_ADDR  CSL_SRIO_CFG_REGS
#define SRIO_CFG_BLK_SZ (132*1024)
#define PASS_CFG_BASE_ADDR  CSL_NETCP_CFG_REGS 
#define PASS_CFG_BLK_SZ (16*1024*1024)
#define MSMC_SRAM_BASE_ADDR CSL_MSMC_SRAM_REGS

/* Global variables to hold virtual address of various subsystems */
void *fw_qmssCfgVaddr;
void *fw_qmssDataVaddr;
void *fw_srioCfgVaddr;
void *fw_passCfgVaddr;


/** Enable Extended Debug with printfs */
//#define         EXT_DEBUG                   1

/* Invalidate  cache. This should invalidate Cache
 * Wait until operation is complete. Currently stub function
 */    
#define SYS_CACHE_INV(addr, size, code)  Osal_invalidateCache(addr,size)  

/* Writeback L2 cache. This should Writeback L1D as well. 
 * Wait until operation is complete. Currently stub function
 */ 
#define SYS_CACHE_WB(addr, size, code) Osal_writeBackCache(addr,size) 

/* GCC align attribute */
#define ALIGN(x)    __attribute__((aligned (x)))

#endif

