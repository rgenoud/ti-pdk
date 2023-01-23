/*
 *  Copyright (C) 2018-2023 Texas Instruments Incorporated
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
 */

/*
 * ======== GENERATED SECTIONS ========
 *
 *     PROLOGUE
 *     INCLUDES
 *
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     VIRTUAL FUNCTIONS
 *     FUNCTION DECLARATIONS
 *     CONVERTORS
 *     SYSTEM FUNCTIONS
 *
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */

#ifndef Cache__include
#define Cache__include


/*
 * ======== INCLUDES ========
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>
#include <c7x.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Cache_Size Cache_Size;
typedef struct Cache_Module_State Cache_Module_State;

/* Type */
enum Cache_Type {
    Cache_Type_L1D = 0x2,
    Cache_Type_ALLD = 0xA,
    Cache_Type_ALL = 0x7fff
};
typedef enum Cache_Type Cache_Type;


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* Mode */
enum Cache_Mode {
    Cache_Mode_FREEZE,
    Cache_Mode_BYPASS,
    Cache_Mode_NORMAL
};
typedef enum Cache_Mode Cache_Mode;

/* L1Size */
enum Cache_L1Size {
    Cache_L1Size_0K = 0,
    Cache_L1Size_4K = 1,
    Cache_L1Size_8K = 2,
    Cache_L1Size_16K = 3,
    Cache_L1Size_32K = 4,
    Cache_L1Size_64K = 5
};
typedef enum Cache_L1Size Cache_L1Size;
/* PC */
#define Cache_PC (1)

/* WTE */
#define Cache_WTE (2)

/* PCX */
#define Cache_PCX (4)

/* PFX */
#define Cache_PFX (8)

/* Size */
struct Cache_Size {
    Cache_L1Size l1dSize;
};

/* enableCache */
extern const bool Cache_enableCache;

/* atomicBlockSize */
extern const uint32_t Cache_atomicBlockSize;




/*
 * ======== FUNCTION DECLARATIONS ========
 */


/* enable */
void Cache_enable( uint16_t type);

/* enable writeback */
void Cache_enableWB(uint16_t type);

/* enable writethrough */
void Cache_enableWT(uint16_t type);

/* inv */
void Cache_inv( void * blockPtr, size_t byteCnt, uint16_t type, bool wait);

/* wb */
void Cache_wb( void * blockPtr, size_t byteCnt, uint16_t type, bool wait);

/* wbInv */
void Cache_wbInv( void * blockPtr, size_t byteCnt, uint16_t type, bool wait);

/* wait */
void Cache_wait( void);

/* disable */
void Cache_disable( uint16_t type);

/* wbAll */
void Cache_wbAll( void);

/* wbL1dAll */
void Cache_wbL1dAll( void);

/* wbInvAll */
void Cache_wbInvAll( void);

/* wbInvL1dAll */
void Cache_wbInvL1dAll( void);

/* wbInvL1dAll */
void Cache_invL1dAll( void);

/* setL1DCFG */
void Cache_setL1DCFG( unsigned long size);

/* getL1DCFG */
unsigned long Cache_getL1DCFG( void);

/* setL1DWB */
void Cache_setL1DWB( unsigned int flag);

/* setL1DWBINV */
void Cache_setL1DWBINV( unsigned int flag);

/* setL1DINV */
void Cache_setL1DINV( unsigned int flag);

void Cache_Module_startup( void );



/*
 * ======== STATE STRUCTURES ========
 */



/* Module_State */
struct Cache_Module_State {
    uint64_t L1DCFG;
};

/* Module__state__V */
extern struct Cache_Module_State Cache_Module_state;






#ifdef __cplusplus
    } /* extern C */
#endif

#endif
