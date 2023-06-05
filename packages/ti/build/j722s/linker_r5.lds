/* Linker Settings */
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
--heap_size=0x1000
--entry_point=_resetvectors     /* Default C RTS boot.asm   */

-stack  0x2000                              /* SOFTWARE STACK SIZE           */
-heap   0x2000                              /* HEAP AREA SIZE                */

/* Stack Sizes for various modes */
__IRQ_STACK_SIZE = 0x1000;
__FIQ_STACK_SIZE = 0x1000;
__ABORT_STACK_SIZE = 0x1000;
__UND_STACK_SIZE = 0x1000;
__SVC_STACK_SIZE = 0x1000;

/* Memory Map */
MEMORY
{
       
    /*  Reset Vectors base address(RESET_VECTORS) should be 64 bytes aligned  */
    RESET_VECTORS (X)       : origin=0x00000000 length=0x40
    /* am62a HSM RAM location */
    HSM_RAM   (RWIX)          : origin=0x43C00000 length=0x34000

}

/* Section Configuration */
SECTIONS
{
    /* 'intvecs' and 'intc_text' sections shall be placed within */
    /* a range of +\- 16 MB */
    .intvecs       : {} palign(8)      > HSM_RAM
    .intc_text     : {} palign(8)      > HSM_RAM
    .rstvectors    : {} palign(8)      > RESET_VECTORS 
    .bootCode      : {} palign(8)      > HSM_RAM
    .startupCode   : {} palign(8)      > HSM_RAM
    .startupData   : {} palign(8)      > HSM_RAM, type = NOINIT
    .text          : {} palign(8)      > HSM_RAM
    .const         : {} palign(8)      > HSM_RAM
    .rodata          : {} palign(8)    > HSM_RAM
    .const.devgroup.MCU_WAKEUP    : {} align(8)      > HSM_RAM
    .const.devgroup.MAIN          : {} align(8)      > HSM_RAM
    .const.devgroup.DMSC_INTERNAL : {} align(8)      > HSM_RAM
    .cinit         : {} palign(8)      > HSM_RAM
    .pinit         : {} palign(8)      > HSM_RAM
    .bss           : {} align(4)       > HSM_RAM
    .bss.devgroup.MAIN            : {} align(8)      > HSM_RAM
    .bss.devgroup.MCU_WAKEUP      : {} align(8)      > HSM_RAM
    .bss.devgroup.DMSC_INTERNAL   : {} align(8)      > HSM_RAM
    .far           : {} align(4)       > HSM_RAM
    .data          : {} palign(128)    > HSM_RAM  
   
    .boardcfg_data : {} palign(128)    > HSM_RAM
    .sysmem        : {}                > HSM_RAM
    .data_buffer   : {} palign(128)    > HSM_RAM

    /* USB or any other LLD buffer for benchmarking */
    .benchmark_buffer (NOLOAD) {} ALIGN (8) > HSM_RAM

    .stack      : {} align(4)       > HSM_RAM
    .irqStack   : {. = . + __IRQ_STACK_SIZE;} align(4)      > HSM_RAM
    RUN_START(__IRQ_STACK_START)
    RUN_END(__IRQ_STACK_END)
    .fiqStack   : {. = . + __FIQ_STACK_SIZE;} align(4)      > HSM_RAM
    RUN_START(__FIQ_STACK_START)
    RUN_END(__FIQ_STACK_END)
    .abortStack : {. = . + __ABORT_STACK_SIZE;} align(4)    > HSM_RAM
    RUN_START(__ABORT_STACK_START)
    RUN_END(__ABORT_STACK_END)
    .undStack   : {. = . + __UND_STACK_SIZE;} align(4)      > HSM_RAM
    RUN_START(__UND_STACK_START)
    RUN_END(__UND_STACK_END)
    .svcStack   : {. = . + __SVC_STACK_SIZE;} align(4)      > HSM_RAM
    RUN_START(__SVC_STACK_START)
    RUN_END(__SVC_STACK_END)
}