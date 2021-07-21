/*============================*/
/*      DDR MEMORY MAP        */
/*============================*/

#include "memory_map_defines.inc"

MEMORY
{
    DDR0_RESERVED       (RWIX)  : ORIGIN = DDR0_RESERVED_START      LENGTH = DDR0_RESERVED_SIZE 
    /*---------------------------------- MCU R5FSS0 CORE0 ------------------------------*/
    MCU1_0_IPC_DATA     (RWIX)	: ORIGIN = MCU1_0_IPC_DATA_BASE     LENGTH = IPC_DATA_SIZE
    MCU1_0_EXT_DATA     (RWIX)	: ORIGIN = MCU1_0_EXT_DATA_BASE     LENGTH = EXT_DATA_SIZE
    MCU1_0_R5F_MEM_TEXT (RWIX)	: ORIGIN = MCU1_0_MEM_TEXT_BASE     LENGTH = MEM_TEXT_SIZE
    MCU1_0_R5F_MEM_DATA (RWIX)	: ORIGIN = MCU1_0_MEM_DATA_BASE     LENGTH = MEM_DATA_SIZE
    MCU1_0_DDR_SPACE    (RWIX)	: ORIGIN = MCU1_0_DDR_SPACE_BASE    LENGTH = DDR_SPACE_SIZE
    /*---------------------------------- MCU R5FSS0 CORE1 ------------------------------*/
    MCU1_1_IPC_DATA     (RWIX)	: ORIGIN = MCU1_1_IPC_DATA_BASE     LENGTH = IPC_DATA_SIZE
    MCU1_1_EXT_DATA     (RWIX)	: ORIGIN = MCU1_1_EXT_DATA_BASE     LENGTH = EXT_DATA_SIZE
    MCU1_1_R5F_MEM_TEXT (RWIX)	: ORIGIN = MCU1_1_MEM_TEXT_BASE     LENGTH = MEM_TEXT_SIZE
    MCU1_1_R5F_MEM_DATA (RWIX)	: ORIGIN = MCU1_1_MEM_DATA_BASE     LENGTH = MEM_DATA_SIZE
    MCU1_1_DDR_SPACE    (RWIX)	: ORIGIN = MCU1_1_DDR_SPACE_BASE    LENGTH = DDR_SPACE_SIZE
    /*---------------------------------- Shared Region ----------------------------------------*/
    SHARED_DDR_SPACE    (RWIX)	: ORIGIN = SHARED_DDR_SPACE_START  LENGTH = SHARED_DDR_SPACE_SIZE  
} 
