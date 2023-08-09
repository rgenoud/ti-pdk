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
--entry_point=_self_reset_start

/*-------------------------------------------*/
/*       Stack Sizes for various modes       */
/*-------------------------------------------*/
__IRQ_STACK_SIZE   = 0x1000;
__FIQ_STACK_SIZE   = 0x0100;
__SVC_STACK_SIZE   = 0x0100;
__ABORT_STACK_SIZE = 0x0100;
__UND_STACK_SIZE   = 0x0100;

/*--------------------------------------------------------------------------*/
/*                               Memory Map                                 */
/*--------------------------------------------------------------------------*/
MEMORY
{
    R5F_TCMA_VEC (RWIX) : ORIGIN = 0x00000000 , LENGTH = 0x00000040
    R5F_TCMA     (RWIX) : ORIGIN = 0x00000040 , LENGTH = 0x00007FC0
    R5F_TCMB_VEC (RWIX) : ORIGIN = 0x41010000 , LENGTH = 0x00000040
    R5F_TCMB     (RWIX) : ORIGIN = 0x41010040 , LENGTH = 0x00007FC0

    HSM_RAM             : ORIGIN = 0x43C00000 , LENGTH = 0x6FF00
    OCMC_RAM_BOARD_CFG  : ORIGIN = 0x43C7C800 , LENGTH = 0x2000
    RAM_X509_HEADER     : ORIGIN = 0x43C7F1E0 , LENGTH = 0x500 /* covers header for J722S */

    FLASH         : ORIGIN = 0x60100000 , LENGTH = 0x80000
    NON_CACHE_MEM : ORIGIN = 0x70060000 , LENGTH = 0x8000
    DDR           : ORIGIN = 0x9CA00000 , LENGTH = 0x1D00000
}

/*--------------------------------------------------------------*/
/*                     Section Configuration                    */
/*--------------------------------------------------------------*/
SECTIONS
{
    .freertosrstvectors : align = 8, load = R5F_TCMB, run = R5F_TCMA
    .bootCode           : align = 8, load = R5F_TCMB, run = R5F_TCMA
    .startupCode        : align = 8, load = R5F_TCMB, run = R5F_TCMA
    .startupData        : align = 8, load = R5F_TCMB, run = R5F_TCMA, type = NOINIT

    /* This has the R5F boot code until the MPU is enabled.  This MUST be at an address < 0x80000000
     * i.e., this cannot be placed in DDR
     */
    GROUP
    {
        .text.hwi       : palign(8)
        .text.cache     : palign(8)
        .text.mpu       : palign(8)
        .text.boot      : palign(8)
    } load = R5F_TCMB, run = R5F_TCMA

    /* .tracebuf           : {} align(1024)   > LINUX_IPC_TRACE_BUFFER */

    .text               : {} palign(8)      > DDR
    .const              : {} palign(8)      > DDR
    .rodata             : {} palign(8)      > DDR
    .cinit              : {} palign(8)      > DDR
    .far                : {} align(4)       > DDR
    .data               : {} palign(128)    > DDR
    .sysmem             : {}                > DDR
    .data_buffer        : {} palign(128)    > DDR
    .const.devgroup     : { *(.const.devgroup*) } align(4) > DDR
    .boardcfg_data      : {} align(4)       > DDR

    GROUP {
        .bss.devgroup   : { *(.bss.devgroup*) } align(4)
        RUN_START(__BSS_START)
        .bss:    {} palign4    /* This is where uninitialized globals go */
        RUN_END(__BSS_END)
    } > DDR

    /* USB or any other LLD buffer for benchmarking */
    .benchmark_buffer (NOLOAD) {} align(8) > DDR

    .stack              : {} align(4)      > DDR  (HIGH)

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
    } > DDR  (HIGH)

    /* Sections needed for C++ projects */
    GROUP {
        .ARM.exidx:  {} palign(8)   /* Needed for C++ exception handling */
        .init_array: {} palign(8)   /* Contains function pointers called before main */
        .fini_array: {} palign(8)   /* Contains function pointers called after main */
    } > DDR
}
