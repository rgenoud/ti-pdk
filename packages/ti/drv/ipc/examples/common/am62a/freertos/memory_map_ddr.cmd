/*============================*/
/*      DDR MEMORY MAP        */
/*============================*/

#include "memory_map_defines.inc"

MEMORY
{
    DDR0_RESERVED       (RWIX)  : ORIGIN = DDR0_RESERVED_START         LENGTH = DDR0_RESERVED_SIZE
    /*---------------------------------- C7x-------- -----------------------------------*/
    C7X_IPC_D           (RWIX)	: ORIGIN = C7x_1_IPC_DATA_BASE         LENGTH = IPC_DATA_SIZE
    C7X_RT_D            (RWIX)	: ORIGIN = C7X_1_RESOURCE_TABLE_BASE   LENGTH = C7X_RT_SIZE
    C7X_BOOT_D          (RWIX)	: ORIGIN = C7X_1_BOOT_BASE             LENGTH = C7X_BOOT_SIZE
    C7X_VECS_D          (RWIX)	: ORIGIN = C7X_1_VECTOR_BASE           LENGTH = C7X_VECTOR_SIZE
    C7X_DDR_SPACE       (RWIX)	: ORIGIN = C7x_1_DDR_SPACE_BASE        LENGTH = DDR_SPACE_SIZE_C7X
    /*---------------------------------- MCU R5FSS0 CORE0 ------------------------------*/
    MCU1_0_IPC_DATA     (RWIX)	: ORIGIN = MCU1_0_IPC_DATA_BASE        LENGTH = IPC_DATA_SIZE
    MCU1_0_EXT_DATA     (RWIX)	: ORIGIN = MCU1_0_EXT_DATA_BASE        LENGTH = EXT_DATA_SIZE
    MCU1_0_R5F_MEM_TEXT (RWIX)	: ORIGIN = MCU1_0_MEM_TEXT_BASE        LENGTH = MEM_TEXT_SIZE
    MCU1_0_R5F_MEM_DATA (RWIX)	: ORIGIN = MCU1_0_MEM_DATA_BASE        LENGTH = MEM_DATA_SIZE
    MCU1_0_DDR_SPACE    (RWIX)	: ORIGIN = MCU1_0_DDR_SPACE_BASE       LENGTH = DDR_SPACE_SIZE_DMR5
    /*---------------------------------- MAIN R5FSS0 CORE0 ------------------------------*/
    MCU2_0_IPC_DATA     (RWIX)	: ORIGIN = MCU2_0_IPC_DATA_BASE         LENGTH = IPC_DATA_SIZE
    MCU2_0_EXT_DATA     (RWIX)	: ORIGIN = MCU2_0_EXT_DATA_BASE         LENGTH = EXT_DATA_SIZE
    MCU2_0_R5F_MEM_TEXT (RWIX)	: ORIGIN = MCU2_0_MEM_TEXT_BASE         LENGTH = MEM_TEXT_SIZE
    MCU2_0_R5F_MEM_DATA (RWIX)	: ORIGIN = MCU2_0_MEM_DATA_BASE         LENGTH = MEM_DATA_SIZE
    MCU2_0_DDR_SPACE    (RWIX)	: ORIGIN = MCU2_0_DDR_SPACE_BASE        LENGTH = DDR_SPACE_SIZE_MCUR5
    /*---------------------------------- Shared Region ----------------------------------------*/
    SHARED_DDR_SPACE    (RWIX)	: ORIGIN = SHARED_DDR_SPACE_START  LENGTH = SHARED_DDR_SPACE_SIZE
} 
