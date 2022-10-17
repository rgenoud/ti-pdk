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
__DM_STUB_STACK_SIZE = 0x0400;

/*--------------------------------------------------------------------------*/
/*                               Memory Map                                 */
/*--------------------------------------------------------------------------*/
MEMORY
{
    /*  Reset Vectors base address(RESET_VECTORS) should be 64 bytes aligned  */
    MCU0_R5F_TCMA_VEC   (RWIX)      : ORIGIN = 0x00000000 LENGTH = 0x00000040
    MCU0_R5F_TCMA       (RWIX)      : ORIGIN = 0x00000040 LENGTH = 0x00007FC0
    MCU0_R5F_TCMB_VEC   (RWIX)      : ORIGIN = 0x41010000 LENGTH = 0x00000040
    MCU0_R5F_TCMB       (RWIX)      : ORIGIN = 0x41010040 LENGTH = 0x00007FC0   
   
    /* am62x HSM RAM location */
    HSM_RAM             (RWIX)      : ORIGIN = 0x43C00000 LENGTH = 0x3FF00

    DDR_DM_R5F_RESOURCE_TABLE ( RWIX ) : ORIGIN = 0x9DB00000 , LENGTH = 0x00000400
    /* DDR for DM R5F for Linux IPC tracebuffer [ size 1023.00 KB ] */
    DDR_DM_R5F_IPC_TRACEBUF  ( RWIX ) : ORIGIN = 0x9DB00400 , LENGTH = 0x000FFC00
    /* DDR for DM R5F for code/data [ size 29.00 MB ] */
    DDR_DM_R5F               ( RWIX ) : ORIGIN = 0x9DC00000 , LENGTH = 0x00B00000
}

/*--------------------------------------------------------------*/
/*                     Section Configuration                    */
/*--------------------------------------------------------------*/
SECTIONS
{
    .freertosrstvectors      : align = 8 ,load = MCU0_R5F_TCMB, run = MCU0_R5F_TCMA
    .bootCode        : align = 8 ,load = MCU0_R5F_TCMB, run = MCU0_R5F_TCMA
    .startupCode     : align = 8 ,load = MCU0_R5F_TCMB, run = MCU0_R5F_TCMA
    .startupData     : {} palign(8)      > DDR_DM_R5F, type = NOINIT
    GROUP {
        .text.hwi    : palign(8)
        .text.cache  : palign(8)
        .text.mpu    : palign(8)
        .text.boot   : palign(8)
    }                                    > DDR_DM_R5F
    GROUP{

        .dm_stub_text : {
            _privileged_code_begin = .;
            _text_secure_start = .;
            dm_stub*(.text)
        }  palign(8)

        .dm_stub_const : {
            dm_stub*(.const)
            _text_secure_end = .;
            _privileged_code_end = .;
        }  palign(8)

        .dm_stub_data : {
            _privileged_data_begin = .;
            dm_stub*(.data)
            _privileged_data_end = .;
        }  palign(8)

        .dm_stub_bss : {
            _start_bss = .;
            dm_stub*(.bss)
            _end_bss = .;
        }  palign(8)

         .dm_stub_rodata : {
            _start_rodata = .;
            dm_stub*(.rodata)
            _end_rodata = .;
        }  palign(8)

       .dm_stub_stack : {
            _start_stack = .;
            . += __DM_STUB_STACK_SIZE;
            _end_stack = .;
        }  palign(8)
}  load = MCU0_R5F_TCMB, run = MCU0_R5F_TCMA
    .text            : {} palign(8)      > DDR_DM_R5F
    .const           : {} palign(8)      > DDR_DM_R5F
    .rodata          : {} palign(8)      > DDR_DM_R5F
    .cinit           : {} palign(8)      > DDR_DM_R5F
    .bss             : {} align(4)       > DDR_DM_R5F
    .far             : {} align(4)       > DDR_DM_R5F
    .data            : {} palign(128)    > DDR_DM_R5F
    .sysmem          : {}                > DDR_DM_R5F
    .data_buffer     : {} palign(128)    > DDR_DM_R5F
    .bss.devgroup*   : {} align(4)       > DDR_DM_R5F
    .const.devgroup* : {} align(4)       > DDR_DM_R5F
    .boardcfg_data   : {} align(4)       > DDR_DM_R5F
    .bss:taskStackSection         : {}   > DDR_DM_R5F

    .resource_table          :
    {
        __RESOURCE_TABLE = .;
    }                                           > DDR_DM_R5F_RESOURCE_TABLE

    .tracebuf                : {} align(1024)   > DDR_DM_R5F_IPC_TRACEBUF

    .stack      : {} align(4)                               > DDR_DM_R5F  (HIGH)

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
