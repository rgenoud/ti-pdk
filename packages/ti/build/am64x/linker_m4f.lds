

-stack  0x20000                            /* SOFTWARE STACK SIZE           */
-heap   0x20000                            /* HEAP AREA SIZE                */

/* SPECIFY THE SYSTEM MEMORY MAP */
MEMORY
{
    IRAM_M4F_VTBL (X)             : origin=0x70000100 length=0x1000
    /*  Reset Vectors base address(RESET_VECTORS) should be 64 bytes aligned  */
    RESET_VECTORS (X)       : origin=0x70000000 length=0x100
    /* am64x MCMS3 locations */
    IRAM_MEM   (RWIX)          : origin=0x70001100 length=0x100000-0x1100 /* 2MB - 0x1100 */
}

/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY */

SECTIONS
{
    .intvecs : load > IRAM_MEM
    .intc_text : load > IRAM_MEM
    .TI.noinit : load > IRAM_M4F_VTBL

    .init    : load > IRAM_MEM

    .text    : load > IRAM_MEM /* CODE                         */
    .data    : load > IRAM_MEM /* INITIALIZED GLOBAL AND STATIC VARIABLES. */
    .bss     : load > IRAM_MEM /* UNINITIALIZED OR ZERO INITIALIZED */
                                            /* GLOBAL & STATIC VARIABLES.   */
                    RUN_START(bss_start)
                    RUN_END(bss_end)
    .const   : load > IRAM_MEM              /* GLOBAL CONSTANTS             */
    .cinit   : load > IRAM_MEM
    .stack   : load > IRAM_MEM            /* SOFTWARE SYSTEM STACK        */
    .plt     : load > IRAM_MEM
    .sysmem  : load > IRAM_MEM
	.my_sect_ddr : load > IRAM_MEM

}

