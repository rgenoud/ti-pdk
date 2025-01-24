
#define DDR0_RESERVED_START     0x80000000
#define DDR0_RESERVED_SIZE      0x20000000 /* 512MB */

#define DDR0_ALLOCATED_START    0xA0000000 /* DDR0_RESERVED_START + DDR0_RESERVED_SIZE */

/*------------------------------------------------*/
/* Size of various Memory Locations for each core */ 
/*------------------------------------------------*/
#define IPC_DATA_SIZE   0x00100000 /*  1MB */
#define EXT_DATA_SIZE   0x00100000 /*  1MB */
#define MEM_TEXT_SIZE   0x00100000 /*  1MB */
#define MEM_DATA_SIZE   0x00100000 /*  1MB */
#define DDR_SPACE_SIZE  0x00C00000 /* 12MB */

#define CORE_TOTAL_SIZE 0x01000000 /* 16MB (IPC_DATA_SIZE + R5F_MEM_TEXT_SIZE + R5F_MEM_DATA_SIZE + DDR_SPACE_SIZE) */

/*-----------------------------*/
/* Start address for each core */ 
/*-----------------------------*/

#define MCU1_0_ALLOCATED_START   DDR0_ALLOCATED_START                     /* 0xA0000000 */  
#define MCU1_1_ALLOCATED_START   MCU1_0_ALLOCATED_START + CORE_TOTAL_SIZE /* 0xA1000000 */ 
#define MCU2_0_ALLOCATED_START   MCU1_1_ALLOCATED_START + CORE_TOTAL_SIZE /* 0xA2000000 */
#define MCU2_1_ALLOCATED_START   MCU2_0_ALLOCATED_START + CORE_TOTAL_SIZE /* 0xA3000000 */
#define MCU3_0_ALLOCATED_START   MCU2_1_ALLOCATED_START + CORE_TOTAL_SIZE /* 0xA4000000 */
#define MCU3_1_ALLOCATED_START   MCU3_0_ALLOCATED_START + CORE_TOTAL_SIZE /* 0xA5000000 */
#define MCU4_0_ALLOCATED_START   MCU3_1_ALLOCATED_START + CORE_TOTAL_SIZE /* 0xA6000000 */
#define MCU4_1_ALLOCATED_START   MCU4_0_ALLOCATED_START + CORE_TOTAL_SIZE /* 0xA7000000 */
#define C7x_1_ALLOCATED_START    MCU4_1_ALLOCATED_START + CORE_TOTAL_SIZE /* 0xA8000000 */
#define C7x_2_ALLOCATED_START    C7x_1_ALLOCATED_START  + CORE_TOTAL_SIZE /* 0xA9000000 */
#define C7x_3_ALLOCATED_START    C7x_2_ALLOCATED_START  + CORE_TOTAL_SIZE /* 0xAA000000 */
#define C7x_4_ALLOCATED_START    C7x_3_ALLOCATED_START  + CORE_TOTAL_SIZE /* 0xAB000000 */

#define SHARED_DDR_SPACE_START   C7x_4_ALLOCATED_START + CORE_TOTAL_SIZE  /* 0xAC000000 */
#define SHARED_DDR_SPACE_SIZE    0x03000000  /*  48 MB */

/*--------------------------- MCU R5FSS0 CORE0 --------------------------*/
#define MCU1_0_IPC_DATA_BASE     MCU1_0_ALLOCATED_START
#define MCU1_0_EXT_DATA_BASE     MCU1_0_IPC_DATA_BASE     + IPC_DATA_SIZE
#define MCU1_0_MEM_TEXT_BASE     MCU1_0_EXT_DATA_BASE     + EXT_DATA_SIZE
#define MCU1_0_MEM_DATA_BASE     MCU1_0_MEM_TEXT_BASE     + MEM_TEXT_SIZE
#define MCU1_0_DDR_SPACE_BASE    MCU1_0_MEM_DATA_BASE     + MEM_DATA_SIZE
/*--------------------------- MCU R5FSS0 CORE1 --------------------------*/
#define MCU1_1_IPC_DATA_BASE     MCU1_1_ALLOCATED_START
#define MCU1_1_EXT_DATA_BASE     MCU1_1_IPC_DATA_BASE     + IPC_DATA_SIZE
#define MCU1_1_MEM_TEXT_BASE     MCU1_1_EXT_DATA_BASE     + EXT_DATA_SIZE
#define MCU1_1_MEM_DATA_BASE     MCU1_1_MEM_TEXT_BASE     + MEM_TEXT_SIZE
#define MCU1_1_DDR_SPACE_BASE    MCU1_1_MEM_DATA_BASE     + MEM_DATA_SIZE
/*--------------------------- MAIN R5FSS0 CORE0 -------------------------*/
#define MCU2_0_IPC_DATA_BASE     MCU2_0_ALLOCATED_START
#define MCU2_0_EXT_DATA_BASE     MCU2_0_IPC_DATA_BASE     + IPC_DATA_SIZE
#define MCU2_0_MEM_TEXT_BASE     MCU2_0_EXT_DATA_BASE     + EXT_DATA_SIZE
#define MCU2_0_MEM_DATA_BASE     MCU2_0_MEM_TEXT_BASE     + MEM_TEXT_SIZE
#define MCU2_0_DDR_SPACE_BASE    MCU2_0_MEM_DATA_BASE     + MEM_DATA_SIZE
/*--------------------------- MAIN R5FSS0 CORE1 -------------------------*/
#define MCU2_1_IPC_DATA_BASE     MCU2_1_ALLOCATED_START
#define MCU2_1_EXT_DATA_BASE     MCU2_1_IPC_DATA_BASE     + IPC_DATA_SIZE
#define MCU2_1_MEM_TEXT_BASE     MCU2_1_EXT_DATA_BASE     + EXT_DATA_SIZE
#define MCU2_1_MEM_DATA_BASE     MCU2_1_MEM_TEXT_BASE     + MEM_TEXT_SIZE
#define MCU2_1_DDR_SPACE_BASE    MCU2_1_MEM_DATA_BASE     + MEM_DATA_SIZE
/*--------------------------- MAIN R5FSS1 CORE0 -------------------------*/
#define MCU3_0_IPC_DATA_BASE     MCU3_0_ALLOCATED_START
#define MCU3_0_EXT_DATA_BASE     MCU3_0_IPC_DATA_BASE     + IPC_DATA_SIZE
#define MCU3_0_MEM_TEXT_BASE     MCU3_0_EXT_DATA_BASE     + EXT_DATA_SIZE
#define MCU3_0_MEM_DATA_BASE     MCU3_0_MEM_TEXT_BASE     + MEM_TEXT_SIZE
#define MCU3_0_DDR_SPACE_BASE    MCU3_0_MEM_DATA_BASE     + MEM_DATA_SIZE
/*--------------------------- MAIN R5FSS1 CORE1 -------------------------*/
#define MCU3_1_IPC_DATA_BASE     MCU3_1_ALLOCATED_START
#define MCU3_1_EXT_DATA_BASE     MCU3_1_IPC_DATA_BASE     + IPC_DATA_SIZE
#define MCU3_1_MEM_TEXT_BASE     MCU3_1_EXT_DATA_BASE     + EXT_DATA_SIZE
#define MCU3_1_MEM_DATA_BASE     MCU3_1_MEM_TEXT_BASE     + MEM_TEXT_SIZE
#define MCU3_1_DDR_SPACE_BASE    MCU3_1_MEM_DATA_BASE     + MEM_DATA_SIZE
/*--------------------------- MAIN R5FSS2 CORE0 -------------------------*/
#define MCU4_0_IPC_DATA_BASE     MCU4_0_ALLOCATED_START
#define MCU4_0_EXT_DATA_BASE     MCU4_0_IPC_DATA_BASE     + IPC_DATA_SIZE
#define MCU4_0_MEM_TEXT_BASE     MCU4_0_EXT_DATA_BASE     + EXT_DATA_SIZE
#define MCU4_0_MEM_DATA_BASE     MCU4_0_MEM_TEXT_BASE     + MEM_TEXT_SIZE
#define MCU4_0_DDR_SPACE_BASE    MCU4_0_MEM_DATA_BASE     + MEM_DATA_SIZE
/*--------------------------- MAIN R5FSS2 CORE1 -------------------------*/
#define MCU4_1_IPC_DATA_BASE     MCU4_1_ALLOCATED_START
#define MCU4_1_EXT_DATA_BASE     MCU4_1_IPC_DATA_BASE     + IPC_DATA_SIZE
#define MCU4_1_MEM_TEXT_BASE     MCU4_1_EXT_DATA_BASE     + EXT_DATA_SIZE
#define MCU4_1_MEM_DATA_BASE     MCU4_1_MEM_TEXT_BASE     + MEM_TEXT_SIZE
#define MCU4_1_DDR_SPACE_BASE    MCU4_1_MEM_DATA_BASE     + MEM_DATA_SIZE
/*----------------------------- C7x CORE1--------------------------------*/
#define C7x_1_IPC_DATA_BASE      C7x_1_ALLOCATED_START
#define C7x_1_EXT_DATA_BASE      C7x_1_IPC_DATA_BASE     + IPC_DATA_SIZE
#define C7x_1_MEM_TEXT_BASE      C7x_1_EXT_DATA_BASE     + EXT_DATA_SIZE
#define C7x_1_MEM_DATA_BASE      C7x_1_MEM_TEXT_BASE     + MEM_TEXT_SIZE
#define C7x_1_DDR_SPACE_BASE     C7x_1_MEM_DATA_BASE     + MEM_DATA_SIZE
/*----------------------------- C7x CORE2--------------------------------*/
#define C7x_2_IPC_DATA_BASE      C7x_2_ALLOCATED_START
#define C7x_2_EXT_DATA_BASE      C7x_2_IPC_DATA_BASE     + IPC_DATA_SIZE
#define C7x_2_MEM_TEXT_BASE      C7x_2_EXT_DATA_BASE     + EXT_DATA_SIZE
#define C7x_2_MEM_DATA_BASE      C7x_2_MEM_TEXT_BASE     + MEM_TEXT_SIZE
#define C7x_2_DDR_SPACE_BASE     C7x_2_MEM_DATA_BASE     + MEM_DATA_SIZE
/*----------------------------- C7x CORE3--------------------------------*/
#define C7x_3_IPC_DATA_BASE      C7x_3_ALLOCATED_START
#define C7x_3_EXT_DATA_BASE      C7x_3_IPC_DATA_BASE     + IPC_DATA_SIZE
#define C7x_3_MEM_TEXT_BASE      C7x_3_EXT_DATA_BASE     + EXT_DATA_SIZE
#define C7x_3_MEM_DATA_BASE      C7x_3_MEM_TEXT_BASE     + MEM_TEXT_SIZE
#define C7x_3_DDR_SPACE_BASE     C7x_3_MEM_DATA_BASE     + MEM_DATA_SIZE
/*----------------------------- C7x CORE4--------------------------------*/
#define C7x_4_IPC_DATA_BASE      C7x_4_ALLOCATED_START
#define C7x_4_EXT_DATA_BASE      C7x_4_IPC_DATA_BASE     + IPC_DATA_SIZE
#define C7x_4_MEM_TEXT_BASE      C7x_4_EXT_DATA_BASE     + EXT_DATA_SIZE
#define C7x_4_MEM_DATA_BASE      C7x_4_MEM_TEXT_BASE     + MEM_TEXT_SIZE
#define C7x_4_DDR_SPACE_BASE     C7x_4_MEM_DATA_BASE     + MEM_DATA_SIZE
/*-----------------------------------------------------------------------*/
