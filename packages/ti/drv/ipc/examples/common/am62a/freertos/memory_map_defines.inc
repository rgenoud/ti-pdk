
#define DDR0_RESERVED_START     0x80000000
#define DDR0_RESERVED_SIZE      0x19800000 /* Reserved Space MB */

#define DDR0_ALLOCATED_START    0x99800000 /* DDR0_RESERVED_START + DDR0_RESERVED_SIZE */

#define SHARED_DDR_SPACE_START  0xA0000000
#define SHARED_DDR_SPACE_SIZE   0x00300000  /*  3MB */

/*------------------------------------------------*/
/* Size of various Memory Locations for each core */ 
/*------------------------------------------------*/
#define C7X_VECTOR_SIZE             0x4000     /*  16KB */
#define C7X_IMG_ALIGN               0x10000    /*  64 */ 
#define C7X_RT_SIZE                 0x400      /*  1024B */
#define C7X_BOOT_SIZE               0x400      /*  1024B */
#define ALGNT_DATA_SIZE             0x00200000 /*  2MB */
#define IPC_DATA_SIZE               0x00100000 /*  1MB */
#define EXT_DATA_SIZE               0x00100000 /*  1MB */
#define MEM_TEXT_SIZE               0x00100000 /*  1MB */
#define MEM_DATA_SIZE               0x00100000 /*  1MB */
#define DDR_SPACE_SIZE_C7X          0x01BF0000 /* 27.98MB */
#define DDR_SPACE_SIZE_DMR5         0x01A00000 /* 29MB - (EXT_DATA_SIZE + MEM_TEXT_SIZE + MEM_DATA_SIZE)*/
#define DDR_SPACE_SIZE_MCUR5        0x00B00000 /* 14MB - (EXT_DATA_SIZE + MEM_TEXT_SIZE + MEM_DATA_SIZE)*/

#define CORE_TOTAL_SIZE 0x01000000 /* 16MB (IPC_DATA_SIZE + R5F_MEM_TEXT_SIZE + R5F_MEM_DATA_SIZE + DDR_SPACE_SIZE) */

/*-----------------------------*/
/* Start address for each core */ 
/*-----------------------------*/

#define C7x_1_ALLOCATED_START    DDR0_ALLOCATED_START
#define MCU1_0_ALLOCATED_START   0x9C800000  /* Start address for DM R5 */
#define MCU2_0_ALLOCATED_START   0x9B800000  /* Start address for DM R5 */
/*------------------------------------------------------------------------/
 * NOTE: C66x Cores IPC_DATA is swapped each other, for proper caching!! *           
 * This is to overcome the limitation - "16 MB" being the minimum cache  *
 * block size in C66x. Requirement is to disable cache for IPC_DATA only * 
 * i.e, the "first 1 MB" allocated for a core.                           *
 * To handle this,                                                       *
 *   - which is un-cached region from C66x_1's perspective               *
 * - Places rest of the core sections (EXT_DATA/MEM_TEXT/MEM_DATA/DDR)   *
 *   in its own dedicated regions.                                       *
 *   - i.e. starting from C66x1_ALLOCATED_START + 1 MB                   *
 *   - which remains "cached" region from C66x_1's perspective           *
 * Vice versa for C66x_2                                                 *
 * - C66x_2 marks "C66x1_ALLOCATED_START" + 16 MB as Cache Disabled.     *
 * - Places C66x2_IPC_DATA in "C66x1_ALLOCATED_START" + 1 MB             *
 *   - which is un-cached region from C66x_2's perspective               *
 * - Places rest of the core sections (EXT_DATA/MEM_TEXT/MEM_DATA/DDR)   *
 *   in its own dedicated regions.                                       *
 *   - i.e. starting from C66x1_ALLOCATED_START + 1 MB                   *
 *   - which remains "cached" region from C66x_1's perspective           */
/*--------------------------- C66x DSP CORE1 ----------------------------*/

/*--------------------------- C7x ---------------------------------------*/
#define C7x_1_IPC_DATA_BASE         C7x_1_ALLOCATED_START
#define C7X_1_RESOURCE_TABLE_BASE   C7x_1_IPC_DATA_BASE         + IPC_DATA_SIZE
#define C7X_1_BOOT_BASE             C7X_1_RESOURCE_TABLE_BASE   + IPC_DATA_SIZE
#define C7X_1_VECTOR_BASE           C7X_1_BOOT_BASE             + ALGNT_DATA_SIZE   
#define C7x_1_DDR_SPACE_BASE        C7X_1_VECTOR_BASE           + C7X_IMG_ALIGN
/*--------------------------- MCU R5FSS0 CORE0 --------------------------*/
#define MCU1_0_IPC_DATA_BASE     MCU1_0_ALLOCATED_START
#define MCU1_0_EXT_DATA_BASE     MCU1_0_IPC_DATA_BASE           + IPC_DATA_SIZE
#define MCU1_0_MEM_TEXT_BASE     MCU1_0_EXT_DATA_BASE           + EXT_DATA_SIZE
#define MCU1_0_MEM_DATA_BASE     MCU1_0_MEM_TEXT_BASE           + MEM_TEXT_SIZE
#define MCU1_0_DDR_SPACE_BASE    MCU1_0_MEM_DATA_BASE           + MEM_DATA_SIZE
/*--------------------------- MAIN R5FSS0 CORE0 -------------------------*/
#define MCU2_0_IPC_DATA_BASE     MCU2_0_ALLOCATED_START
#define MCU2_0_EXT_DATA_BASE     MCU2_0_IPC_DATA_BASE           + IPC_DATA_SIZE
#define MCU2_0_MEM_TEXT_BASE     MCU2_0_EXT_DATA_BASE           + EXT_DATA_SIZE
#define MCU2_0_MEM_DATA_BASE     MCU2_0_MEM_TEXT_BASE           + MEM_TEXT_SIZE
#define MCU2_0_DDR_SPACE_BASE    MCU2_0_MEM_DATA_BASE           + MEM_DATA_SIZE
