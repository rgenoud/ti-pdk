/*----------------------------------------------------------------------------*/
/* File: k3m4_r5f_linker.cmd                                                  */
/* Description:																  */
/*    Link command file for j721e M4 MCU 0 view							  */
/*	  TI ARM Compiler version 15.12.3 LTS or later							  */
/*                                                                            */
/*    Platform: QT                                                            */
/* (c) Texas Instruments 2021, All rights reserved.                           */
/*----------------------------------------------------------------------------*/
/* Linker Settings                                                            */
/* Standard linker options													  */
--retain="*(.bootCode)"
--retain="*(.startupCode)"
--retain="*(.startupData)"
--retain="*(.irqStack)"
--retain="*(.fiqStack)"
--retain="*(.abortStack)"
--retain="*(.undStack)"
--retain="*(.svcStack)"
--fill_value=0
-e __VECS_ENTRY_POINT

/* interface with SBL */
sblProfileLogAddr = 0x41c001f0;
sblProfileLogIndxAddr = 0x41c001f4;
sblProfileLogOvrFlwAddr = 0x41c001f8;
/*----------------------------------------------------------------------------*/
/* Memory Map                                                                 */

--stack_size=0x4000
--heap_size=0x2000
--entry_point=_freertosresetvectors

-stack  0x4000  /* SOFTWARE STACK SIZE */
-heap   0x2000  /* HEAP AREA SIZE      */

/*-------------------------------------------*/
/*       Stack Sizes for various modes       */
/*-------------------------------------------*/
__IRQ_STACK_SIZE   = 0x1000;
__FIQ_STACK_SIZE   = 0x1000;
__ABORT_STACK_SIZE = 0x1000;
__UND_STACK_SIZE   = 0x1000;
__SVC_STACK_SIZE   = 0x1000;

--define FILL_PATTERN=0xFEAA55EF
--define FILL_LENGTH=0x100

/* 1 MB of MCU Domain MSRAM is split as shown below */
/* Size used  F0000 Number of slices 4 */
/*                                  Rounding Offset */
/*SBL?      Start   41C00000    245760  0   */
/*          End     41C3C000                */
/*MCU 10    Start   41C3C100    245760  100 */
/*          End     41C78100                */
/*MCU 11    Start   41C78200    245760  100 */
/*          End     41CB4200                */

#define BTCM_START 0x41010000

#define MCU1_0_ALLOCATED_START 0xA0000000

#define IPC_DATA_SIZE   0x00100000 /*  1MB */
#define EXT_DATA_SIZE   0x00100000 /*  1MB */
#define MEM_TEXT_SIZE   0x00100000 /*  1MB */
#define MEM_DATA_SIZE   0x00100000 /*  1MB */
#define DDR_SPACE_SIZE  0x00C00000 /* 12MB */

#define MCU1_0_IPC_DATA_BASE     MCU1_0_ALLOCATED_START
#define MCU1_0_EXT_DATA_BASE     MCU1_0_IPC_DATA_BASE     + IPC_DATA_SIZE
#define MCU1_0_MEM_TEXT_BASE     MCU1_0_EXT_DATA_BASE     + EXT_DATA_SIZE
#define MCU1_0_MEM_DATA_BASE     MCU1_0_MEM_TEXT_BASE     + MEM_TEXT_SIZE
#define MCU1_0_DDR_SPACE_BASE    MCU1_0_MEM_DATA_BASE     + MEM_DATA_SIZE

MEMORY
{
    VECTORS (X)                 : origin = 0x00000000   length = 0x00000040

    /* MCU0_R5F_0 local view */
    MCU0_R5F_TCMA (RWIX)        : origin=0x00000040     length=0x00007FC0
    MCU0_R5F_TCMB0_VECS (RWIX)	: origin=0x41010000	    length=0x100
    MCU0_R5F_TCMB0(RWIX)        : origin=0x41010100     length=0x00008000-0x100

    /* MCU0_R5F_1 SoC view */
    MCU0_R5F1_ATCM (RWIX)   : origin=0x41400000 length=0x8000
    MCU0_R5F1_BTCM (RWIX)   : origin=0x41410000 length=0x8000

    /* j7200 MCMS3 locations */
    /* j7200 Reserved Memory for ARM Trusted Firmware */
    MSMC3_ARM_FW   (RWIX)   : origin=0x70000000 length=0x20000         /* 128KB */
    MSMC3   (RWIX)          : origin=0x70020000 length=0xD0000         /* 1MB - 192KB */
    /* j7200 Reserved Memory for DMSC Firmware */
    MSMC3_DMSC_FW  (RWIX)   : origin=0x700F0000 length=0x10000         /* 64KB */

    DDR0    (RWIX)          : origin=0x80000000 length=0x8000000      /* 128MB */

    /* Used in this file */
    MCU1_0_DDR_IPC_SPACE (RWIX)     : origin=MCU1_0_IPC_DATA_BASE length=IPC_DATA_SIZE       /* 12MB */
    MCU1_0_DDR_EXT_SPACE (RWIX)     : origin=MCU1_0_EXT_DATA_BASE length=EXT_DATA_SIZE       /* 12MB */
    MCU1_0_DDR_MEM_SPACE (RWIX)     : origin=MCU1_0_MEM_DATA_BASE length=DDR_SPACE_SIZE       /* 12MB */

    RESERVED (X)            : origin=0x41C3E000 length=0x2000
    /* Refer the user guide for details on persistence of these sections */
    //OCMC_RAM_BOARD_CFG (RWIX)   : origin=0x41C80000 length=0x2000
    //OCMC_RAM_SCISERVER (RWIX)   : origin=0x41C82000 length=0x60000
    //RESET_VECTORS (X)           : origin=0x41CE2000 length=0x100
    //OCMC_RAM (RWIX)             : origin=0x41CE2100 length=0x1DA00
    //OCMC_RAM_X509_HEADER (RWIX) : origin=0x41CFFB00 length=0x500

    OCMC_RAM_BOARD_CFG (RWIX)   : origin=0x41C80000 length=0x2000
    OCMC_RAM (RWIX)             : origin=0x41C82000 length=0x7DA00
    OCMC_RAM_X509_HEADER (RWIX) : origin=0x41CFFB00 length=0x500

}  /* end of MEMORY */

/*----------------------------------------------------------------------------*/
/* Section Configuration                                                      */

SECTIONS
{
    .freertosrstvectors      : {} palign(8)      > MCU0_R5F_TCMB0_VECS
    .bootCode        : {} palign(8)      > MCU0_R5F_TCMB0
    .startupCode     : {} palign(8)      > MCU0_R5F_TCMB0
    .startupData     : {} palign(8)      > MCU0_R5F_TCMB0, type = NOINIT
    GROUP {
        .text.hwi    : palign(8)
        .text.cache  : palign(8)
        .text.mpu    : palign(8)
        .text.boot   : palign(8)
    }                           > MCU0_R5F_TCMB0
    .text    	: {} palign(8) 		> OCMC_RAM
    .const   	: {} palign(8) 		> OCMC_RAM
    .cinit   	: {} palign(8) 		> OCMC_RAM
    .pinit   	: {} palign(8) 		> OCMC_RAM

    /* USB or any other LLD buffer for benchmarking */
    .benchmark_buffer (NOLOAD) {} align (8)     > MCU1_0_DDR_MEM_SPACE
    ipc_data_buffer (NOINIT) : {} palign(128)	> MCU1_0_DDR_MEM_SPACE
    .resource_table          : 
    {
        __RESOURCE_TABLE = .;
    }                                           > MCU1_0_EXT_DATA_BASE
    .tracebuf                : {} align(1024)   > MCU1_0_DDR_EXT_SPACE

    .bss     	: {} align(4)  	> OCMC_RAM
    .far     	: {} align(4)  	> MCU0_R5F_TCMB0
    .data    	: {} palign(128) 	> OCMC_RAM
    .data_buffer: {} palign(128) 	> MCU0_R5F_TCMB0
	.sysmem  	: {}                > MCU0_R5F_TCMB0
    .bss.devgroup  : {*(.bss.devgroup*)} align(4)      > MCU0_R5F_TCMB0
    .const.devgroup : {*(.const.devgroup*)} align(4)     > OCMC_RAM
    .data_user      : {} align(4)      > MCU0_R5F_TCMB0
    .boardcfg_data  : {} align(4)      > MCU0_R5F_TCMB0

    /* Additional sections settings 	*/
    .sysfw_data_cfg_board      : {} palign(128) > OCMC_RAM_BOARD_CFG
    .sysfw_data_cfg_board_rm   : {} palign(128) > MCU0_R5F_TCMB0
    .sysfw_data_cfg_board_pm   : {} palign(128) > OCMC_RAM_BOARD_CFG
    .sysfw_data_cfg_board_sec  : {} palign(128) > OCMC_RAM_BOARD_CFG

	.stack  	: {} align(4)		> MCU0_R5F_TCMA  (HIGH) fill=FILL_PATTERN
    .irqStack   : {. = . + __IRQ_STACK_SIZE;} align(4)      > MCU0_R5F_TCMA  (HIGH)
    RUN_START(__IRQ_STACK_START)
    RUN_END(__IRQ_STACK_END)

    .fiqStack   : {. = . + __FIQ_STACK_SIZE;} align(4)      > MCU0_R5F_TCMA  (HIGH)
    RUN_START(__FIQ_STACK_START)
    RUN_END(__FIQ_STACK_END)

    .abortStack : {. = . + __ABORT_STACK_SIZE;} align(4)    > MCU0_R5F_TCMB0  (HIGH)
    RUN_START(__ABORT_STACK_START)
    RUN_END(__ABORT_STACK_END)

    .undStack   : {. = . + __UND_STACK_SIZE;} align(4)      > MCU0_R5F_TCMB0  (HIGH)
    RUN_START(__UND_STACK_START)
    RUN_END(__UND_STACK_END)

    .svcStack   : {. = . + __SVC_STACK_SIZE;} align(4)      > MCU0_R5F_TCMA  (HIGH)
    RUN_START(__SVC_STACK_START)
    RUN_END(__SVC_STACK_END)

    SciClientBoardCfgSection : align=128, load > OCMC_RAM_BOARD_CFG, type = NOINIT
    {
        .=align(128);
        __linker_boardcfg_data_start = .;
        . += FILL_LENGTH;
        *(.boardcfg_data)
        .=align(128);
        . += FILL_LENGTH;
        __linker_boardcfg_data_end = .;
    }
}  /* end of SECTIONS */

/*----------------------------------------------------------------------------*/
/* Misc linker settings                                                       */


/*-------------------------------- END ---------------------------------------*/
