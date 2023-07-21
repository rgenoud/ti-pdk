/*----------------------------------------------------------------------------*/
/* File: linker_r5_tiny.lds                                                   */
/* Description:                                                               */
/*    Linker command file for SoCs with small RAM size                        */
/*                                                                            */
/* (c) Texas Instruments 2023, All rights reserved.                           */
/*----------------------------------------------------------------------------*/
/* Linker Settings                                                            */
/* Standard linker options                                                    */
--retain="*(.bootCode)"
--retain="*(.startupCode)"
--retain="*(.startupData)"
--retain="*(.intvecs)"
--retain="*(.intc_text)"
--retain="*(.rstvectors)"
--retain="*(.irqStack)"
--retain="*(.fiqStack)"
--retain="*(.abortStack)"
--retain="*(.undStack)"
--retain="*(.svcStack)"
--fill_value=0
--stack_size=0x2000
--heap_size=0x2000

-stack  0x2000                              /* SOFTWARE STACK SIZE           */
-heap   0x2000                              /* HEAP AREA SIZE                */

/* Stack Sizes for various modes */
__IRQ_STACK_SIZE = 0x100;
__FIQ_STACK_SIZE = 0x100;
__ABORT_STACK_SIZE = 0x100;
__UND_STACK_SIZE = 0x100;
__SVC_STACK_SIZE = 0x100;


/*----------------------------------------------------------------------------*/
/* Memory Map                                                                 */
/*----------------------------------------------------------------------------*/
/* Memory Map                                                                 */
MEMORY
{
    /*  Reset Vectors base address(RESET_VECTORS) should be 64 bytes aligned  */
    RESET_VECTORS (X)                : origin=0x70000000 length=0x100
    /* Last 64K of the OSMCRAM is used by SYSFW for the Secure Proxy Backing RAM */
    OCMRAM_sciclientTest    (RWIX)   : origin=0x70000100 length=0x40000-0x100 /* 256KB - 0x100 */
    /* Populate the SCISERVER Board configuration paramters */
    OCMC_RAM_BOARD_CFG_TABLE (RWIX) : ORIGIN = 0x43C7C800 , LENGTH = 0x40
    /* Location of all board configurations */
    OCMC_RAM_BOARD_CFG (RWIX)       : ORIGIN = 0x43C7C840 , LENGTH = 0x2000 - 0x40
    /* Sciserver App Space */
    OCMC_RAM_SCISERVER (RWIX)   : origin=0x43C00000 length=0x40000
    /* X509 Header to be left behind by CCS Init for Sciserver to read */
    OCMC_RAM_X509_HEADER1 (RWIX)     : origin=0x43C7F1E0 length=0x500 /* covers header for J722S */

}  /* end of MEMORY */

/*----------------------------------------------------------------------------*/
/* Section Configuration                                                      */

SECTIONS
{
/* 'intvecs' and 'intc_text' sections shall be placed within                  */
/* a range of +\- 16 MB                                                       */
    .rstvectors           : {} palign(8)                            > RESET_VECTORS
    .bootCode             : {} palign(8)                            > OCMRAM_sciclientTest
    .startupCode          : {} palign(8)                            > OCMRAM_sciclientTest
    .startupData          : {} palign(8)                            > OCMRAM_sciclientTest, type = NOINIT
    .text                 : {} palign(8)                            > OCMRAM_sciclientTest
    .const                : {} palign(8)                            > OCMRAM_sciclientTest
    .rodata               : {} palign(8)                            > OCMRAM_sciclientTest
    .cinit                : {} palign(8)                            > OCMRAM_sciclientTest
    .pinit                : {} palign(8)                            > OCMRAM_sciclientTest
    .data                 : {} palign(128)                          > OCMRAM_sciclientTest
    .boardcfg_data        : {} palign(128)                          > OCMRAM_sciclientTest
    .bss                  : {} align(4)                             > OCMRAM_sciclientTest
    .sysmem               : {}                                      > OCMRAM_sciclientTest
    .stack                : {} align(4)                             > OCMRAM_sciclientTest  (HIGH)
    .irqStack             : {. = . + __IRQ_STACK_SIZE;} align(4)    > OCMRAM_sciclientTest  (HIGH)
                            RUN_START(__IRQ_STACK_START)
                            RUN_END(__IRQ_STACK_END)
    .fiqStack             : {. = . + __FIQ_STACK_SIZE;} align(4)    > OCMRAM_sciclientTest  (HIGH)
                            RUN_START(__FIQ_STACK_START)
                            RUN_END(__FIQ_STACK_END)
    .abortStack           : {. = . + __ABORT_STACK_SIZE;} align(4)  > OCMRAM_sciclientTest  (HIGH)
                            RUN_START(__ABORT_STACK_START)
                            RUN_END(__ABORT_STACK_END)
    .undStack             : {. = . + __UND_STACK_SIZE;} align(4)    > OCMRAM_sciclientTest  (HIGH)
                            RUN_START(__UND_STACK_START)
                            RUN_END(__UND_STACK_END)
    .svcStac              : {. = . + __SVC_STACK_SIZE;} align(4)    > OCMRAM_sciclientTest  (HIGH)
                            RUN_START(__SVC_STACK_START)
                            RUN_END(__SVC_STACK_END)
}  /* end of SECTIONS */

/*----------------------------------------------------------------------------*/
/* Misc linker settings                                                       */


/*-------------------------------- END ---------------------------------------*/
