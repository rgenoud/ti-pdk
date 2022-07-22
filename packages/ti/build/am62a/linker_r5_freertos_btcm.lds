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
--stack_size=0x8000
--heap_size=0x10000
--entry_point=_self_reset_start

-stack  0x8000  /* SOFTWARE STACK SIZE */
-heap   0x10000 /* HEAP AREA SIZE      */

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
    /* R5F_TCMA_VECS [ size 64 B ] */
    R5F_TCMA_VECS            (    X ) : ORIGIN = 0x00000000 , LENGTH = 0x00000040
    /* R5F_TCMA [ size 31.94 KB ] */
    R5F_TCMA                 (    X ) : ORIGIN = 0x00000040 , LENGTH = 0x00007FC0
    /* R5F_TCMB0_VECS [ size 64 B ] */
    R5F_TCMB0_VECS           ( RWIX ) : ORIGIN = 0x41010000 , LENGTH = 0x00000040
    /* R5F_TCMB0 [ size 31.94 KB ] */
    R5F_TCMB0                ( RWIX ) : ORIGIN = 0x41010040 , LENGTH = 0x00007FC0
    /* DDR for DM R5F for Linux resource table [ size 1024 B ] */
    DDR_DM_R5F_RESOURCE_TABLE ( RWIX ) : ORIGIN = 0x9C900000 , LENGTH = 0x00000400
    /* DDR for DM R5F for Linux IPC tracebuffer [ size 1023.00 KB ] */
    DDR_DM_R5F_IPC_TRACEBUF  ( RWIX ) : ORIGIN = 0x9C900400 , LENGTH = 0x000FFC00
    /* DDR for DM R5F for code/data [ size 29.00 MB ] */
    DDR_DM_R5F               ( RWIX ) : ORIGIN = 0x9CA00000 , LENGTH = 0x01D00000
}

/*--------------------------------------------------------------*/
/*                     Section Configuration                    */
/*--------------------------------------------------------------*/
SECTIONS
{
    .freertosrstvectors : align = 8, load = R5F_TCMB0, run = R5F_TCMA
    .bootCode           : align = 8, load = R5F_TCMB0, run = R5F_TCMA
    .startupCode        : align = 8, load = R5F_TCMB0 , run = R5F_TCMA
    .startupData        : {} palign(8)      > DDR_DM_R5F, type = NOINIT
    GROUP
    {
        .text.hwi       : palign(8)
        .text.cache     : palign(8)
        .text.mpu       : palign(8)
        .text.boot      : palign(8)
    }                                       > DDR_DM_R5F
    .text               : {} palign(8)      > DDR_DM_R5F
    .const              : {} palign(8)      > DDR_DM_R5F
    .rodata             : {} palign(8)      > DDR_DM_R5F
    .cinit              : {} palign(8)      > DDR_DM_R5F
    .bss                : {} align(4)       > DDR_DM_R5F
    .far                : {} align(4)       > DDR_DM_R5F
    .data               : {} palign(128)    > DDR_DM_R5F
    .sysmem             : {}                > DDR_DM_R5F
    .data_buffer        : {} palign(128)    > DDR_DM_R5F
    .bss.devgroup*      : {} align(4)       > DDR_DM_R5F
    .const.devgroup*    : {} align(4)       > DDR_DM_R5F
    .boardcfg_data      : {} align(4)       > DDR_DM_R5F
    .bss:taskStackSection            : {}   > DDR_DM_R5F
    .resource_table          :
    {
        __RESOURCE_TABLE = .;
    }                                           > DDR_DM_R5F_RESOURCE_TABLE

    .tracebuf                : {} align(1024)   > DDR_DM_R5F_IPC_TRACEBUF
    .stack                   : {} align(4)      > DDR_DM_R5F  (HIGH)

    .irqStack   : {. = . + __IRQ_STACK_SIZE;} align(4)      > DDR_DM_R5F  (HIGH)
    RUN_START(__IRQ_STACK_START)
    RUN_END(__IRQ_STACK_END)

    .fiqStack   : {. = . + __FIQ_STACK_SIZE;} align(4)      > DDR_DM_R5F  (HIGH)
    RUN_START(__FIQ_STACK_START)
    RUN_END(__FIQ_STACK_END)

    .abortStack : {. = . + __ABORT_STACK_SIZE;} align(4)    > DDR_DM_R5F  (HIGH)
    RUN_START(__ABORT_STACK_START)
    RUN_END(__ABORT_STACK_END)

    .undStack   : {. = . + __UND_STACK_SIZE;} align(4)      > DDR_DM_R5F  (HIGH)
    RUN_START(__UND_STACK_START)
    RUN_END(__UND_STACK_END)

    .svcStack   : {. = . + __SVC_STACK_SIZE;} align(4)      > DDR_DM_R5F  (HIGH)
    RUN_START(__SVC_STACK_START)
    RUN_END(__SVC_STACK_END)
}
