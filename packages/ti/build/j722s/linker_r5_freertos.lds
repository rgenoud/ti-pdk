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

-stack  0x4000  /* SOFTWARE STACK SIZE */
-heap   0x8000  /* HEAP AREA SIZE      */

/*-------------------------------------------*/
/*       Stack Sizes for various modes       */
/*-------------------------------------------*/
__IRQ_STACK_SIZE   = 0x1000;
__FIQ_STACK_SIZE   = 0x0100;
__ABORT_STACK_SIZE = 0x0100;
__UND_STACK_SIZE   = 0x0100;
__SVC_STACK_SIZE   = 0x0100;

/*--------------------------------------------------------------------------*/
/*                               Memory Map                                 */
/*--------------------------------------------------------------------------*/
MEMORY
{
     /*  Reset Vectors base address(RESET_VECTORS) should be 64 bytes aligned  */
    MCU0_R5F_TCMA_VEC (X)         : ORIGIN = 0x00000000 LENGTH = 0x00000040

    /* j722s TCM and DDR/RAM location */
    MCU0_R5F_TCMA (RWIX)          : origin = 0x00000040 length = 0x3FE00
    MCU_RAM (RWIX)                : origin = 0x70000040 length = 0x3F000
}

/*--------------------------------------------------------------*/
/*                     Section Configuration                    */
/*--------------------------------------------------------------*/
SECTIONS
{
    .freertosrstvectors : {} palign(8)   > MCU0_R5F_TCMA_VEC
    .bootCode        : {} palign(8)      > MCU0_R5F_TCMA
    .startupCode     : {} palign(8)      > MCU0_R5F_TCMA
    .startupData     : {} palign(8)      > MCU_RAM, type = NOINIT
    .text            : {} palign(8)      > MCU_RAM
    GROUP {
        .text.hwi    : palign(8)
        .text.cache  : palign(8)
        .text.mpu    : palign(8)
        .text.boot   : palign(8)
    }                                    > MCU_RAM
    .const           : {} palign(8)      > MCU_RAM
    .rodata          : {} palign(8)      > MCU_RAM
    .cinit           : {} palign(8)      > MCU_RAM
    .bss             : {} align(4)       > MCU_RAM
    .far             : {} align(4)       > MCU_RAM
    .data            : {} palign(128)    > MCU_RAM
    .sysmem          : {}                > MCU_RAM
    .data_buffer     : {} palign(128)    > MCU_RAM
    .bss.devgroup*   : {} align(4)       > MCU_RAM
    .const.devgroup* : {} align(4)       > MCU_RAM
    .boardcfg_data   : {} align(4)       > MCU_RAM

    /* USB or any other LLD buffer for benchmarking */
    .benchmark_buffer (NOLOAD) {} ALIGN (8) > MCU_RAM

    .stack      : {} align(4)                               > MCU_RAM  (HIGH)

    .irqStack   : {. = . + __IRQ_STACK_SIZE;} align(4)      > MCU_RAM  (HIGH)
    RUN_START(__IRQ_STACK_START)
    RUN_END(__IRQ_STACK_END)

    .fiqStack   : {. = . + __FIQ_STACK_SIZE;} align(4)      > MCU_RAM  (HIGH)
    RUN_START(__FIQ_STACK_START)
    RUN_END(__FIQ_STACK_END)

    .abortStack : {. = . + __ABORT_STACK_SIZE;} align(4)    > MCU_RAM  (HIGH)
    RUN_START(__ABORT_STACK_START)
    RUN_END(__ABORT_STACK_END)

    .undStack   : {. = . + __UND_STACK_SIZE;} align(4)      > MCU_RAM  (HIGH)
    RUN_START(__UND_STACK_START)
    RUN_END(__UND_STACK_END)

    .svcStack   : {. = . + __SVC_STACK_SIZE;} align(4)      > MCU_RAM  (HIGH)
    RUN_START(__SVC_STACK_START)
    RUN_END(__SVC_STACK_END)
}
