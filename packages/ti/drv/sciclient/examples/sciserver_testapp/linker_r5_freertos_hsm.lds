/*=========================*/
/*     Linker Settings     */
/*=========================*/

--retain="*(.bootCode)"
--retain="*(.startupCode)"
--retain="*(.startupData)"
--retain="*(.irqStack)"
--retain="*(.fiqStack)"
--retain="*(.abortStack)"
--retain="*(.undStack)"
--retain="*(.svcStack)"

--fill_value=0
--stack_size=0x4000
--heap_size=0x8000
--entry_point=_freertosresetvectors

/*-------------------------------------------*/
/*       Stack Sizes for various modes       */
/*-------------------------------------------*/
__IRQ_STACK_SIZE   = 0x1000;
__FIQ_STACK_SIZE   = 0x0100;
__SVC_STACK_SIZE   = 0x0100;
__ABORT_STACK_SIZE = 0x0100;
__UND_STACK_SIZE   = 0x0100;
__DM_STUB_STACK_SIZE = 0x0400;

/*--------------------------------------------------------------------------*/
/*                               Memory Map                                 */
/*--------------------------------------------------------------------------*/
MEMORY
{
    HSM_RAM_VECS  : ORIGIN = 0x43C00000 , LENGTH = 0x100
    HSM_RAM       : ORIGIN = 0x43C00100 , LENGTH = 0x6FE00
    OCMC_RAM_BOARD_CFG : ORIGIN = 0x43C7C800 , LENGTH = 0x2000
    RAM_X509_HEADER : ORIGIN = 0x43C7F1E0 , LENGTH = 0x500 /* covers header for J722S */

    FLASH         : ORIGIN = 0x60100000 , LENGTH = 0x80000
    NON_CACHE_MEM : ORIGIN = 0x70060000 , LENGTH = 0x8000

    DDR_DM_R5F_RESOURCE_TABLE (RWIX) : ORIGIN = 0x9C900000 , LENGTH = 0x00000400
    DDR           : ORIGIN = 0x9CA00000 , LENGTH = 0x01D00000
}

/*--------------------------------------------------------------*/
/*                     Section Configuration                    */
/*--------------------------------------------------------------*/
SECTIONS
{
    .freertosrstvectors : palign(8) > HSM_RAM_VECS
    .bootCode           : palign(8) > HSM_RAM
    .startupCode        : palign(8) > HSM_RAM
    .startupData        : palign(8) > HSM_RAM, type = NOINIT
    GROUP
    {
        .text.hwi       : palign(8)
        .text.cache     : palign(8)
        .text.mpu       : palign(8)
        .text.boot      : palign(8)
    } > HSM_RAM
    .text               : {} palign(8)      > HSM_RAM
    .const              : {} palign(8)      > HSM_RAM
    .rodata             : {} palign(8)      > HSM_RAM
    .cinit              : {} palign(8)      > HSM_RAM
    .far                : {} align(4)       > HSM_RAM
    .data               : {} palign(128)    > HSM_RAM
    .sysmem             : {}                > HSM_RAM
    .data_buffer        : {} palign(128)    > HSM_RAM
    .const.devgroup     : { *(.const.devgroup*) } align(4) > HSM_RAM
    .boardcfg_data      : {} align(4)       > HSM_RAM

    GROUP {
        .bss.devgroup   : { *(.bss.devgroup*) } align(4)
        RUN_START(__BSS_START)
        .bss:    {} palign4    /* This is where uninitialized globals go */
        RUN_END(__BSS_END)
    } > HSM_RAM

    .resource_table          :
    {
        __RESOURCE_TABLE = .;
    }                                       > DDR_DM_R5F_RESOURCE_TABLE

    /* .tracebuf           : {} align(1024)   > DDR_DM_R5F_IPC_TRACEBUF */
    .stack              : {} align(4)      > HSM_RAM  (HIGH)

    GROUP {
        .irqStack   : {. = . + __IRQ_STACK_SIZE;} align(4)
        RUN_START(__IRQ_STACK_START)
        RUN_END(__IRQ_STACK_END)
        .fiqStack   : {. = . + __FIQ_STACK_SIZE;} align(4)
        RUN_START(__FIQ_STACK_START)
        RUN_END(__FIQ_STACK_END)
        .svcStack   : {. = . + __SVC_STACK_SIZE;} align(4)
        RUN_START(__SVC_STACK_START)
        RUN_END(__SVC_STACK_END)
        .abortStack : {. = . + __ABORT_STACK_SIZE;} align(4)
        RUN_START(__ABORT_STACK_START)
        RUN_END(__ABORT_STACK_END)
        .undStack   : {. = . + __UND_STACK_SIZE;} align(4)
        RUN_START(__UND_STACK_START)
        RUN_END(__UND_STACK_END)
    } > HSM_RAM  (HIGH)
}
