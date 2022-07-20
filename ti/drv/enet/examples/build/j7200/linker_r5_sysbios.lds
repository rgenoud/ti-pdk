/* linker options */
--fill_value=0

-e __VECS_ENTRY_POINT
--retain="*(.utilsCopyVecsToAtcm)"

MEMORY
{
    R5F_TCMA_SBL_RSVD(X): ORIGIN = 0x00000000 , LENGTH = 0x100
    RESET_VECTORS(X)    : ORIGIN = 0x41c40000 , LENGTH = 0x100  /* Bottom 256 KB used by SBL */
    R5F_TCMB0(RWIX)     : ORIGIN = 0x41010000 , LENGTH = 0x00008000
    DDR0 (RWIX)         : ORIGIN = 0x80000000 , LENGTH = 0x10000000
    DDR0_NONCACHED ( RWIX ) : ORIGIN = 0xA3000000 , LENGTH = 0x01000000
    MSMC3 (RWIX)        : ORIGIN = 0x70040000 , LENGTH = 0xB0000    /* 1MB - 320KB */
}

SECTIONS
{
    .vecs       : {
        __VECS_ENTRY_POINT = .;
    } palign(8) > RESET_VECTORS
    .text_boot {
        *boot.aer5f*<*boot.o*>(.text)
     }  palign(8)   > R5F_TCMB0
    .text:xdc_runtime_Startup_reset__I     : {} palign(8) > R5F_TCMB0
    .text:ti_sysbios_family_arm_v7r_Cache* : {} palign(8) > R5F_TCMB0
    .text:ti_sysbios_family_arm_MPU*       : {} palign(8) > R5F_TCMB0
    .utilsCopyVecsToAtcm                   : {} palign(8) > R5F_TCMB0

    /* DMA packet info (metadata), packet data and UDMA ring and desc memory */
    .bss:ENET_DMA_DESC_MEMPOOL (NOLOAD) {} ALIGN (128) > DDR0
    .bss:ENET_DMA_RING_MEMPOOL (NOLOAD) {} ALIGN (128) > DDR0
    .bss:ENET_DMA_PKT_MEMPOOL  (NOLOAD) {} ALIGN (128) > DDR0
    .bss:ENET_DMA_OBJ_MEM      (NOLOAD) {} ALIGN (128) > DDR0
    .bss:ENET_DMA_PKT_INFO_MEMPOOL (NOLOAD) {} ALIGN (128) > DDR0

    /* For NDK packet memory*/
    .bss:NDK_MMBUFFER  (NOLOAD) {} ALIGN (128) > DDR0
    .bss:NDK_PACKETMEM (NOLOAD) {} ALIGN (128) > DDR0

    /* Used in Switch configuration tool */
    .serialContext     (NOLOAD) {} ALIGN (128) > DDR0

    .text       : {} palign(8)   > DDR0
    .cinit      : {} palign(8)   > DDR0
    .bss        : {} align(8)    > DDR0
    .far        : {} align(8)    > DDR0
    .const      : {} palign(8)   > DDR0
    .rodata     : {} palign(8)   > DDR0
    .data       : {} palign(128) > DDR0
    .sysmem     : {} align(8)    > DDR0
    .stack      : {} align(4)    > DDR0
    .data_buffer: {} palign(128) > DDR0
    .noncached_section: {} palign(128) > DDR0_NONCACHED
    .bss.devgroup*   : {} align(4) > DDR0
    .const.devgroup* : {} align(4) > DDR0
    .boardcfg_data   : {} align(4) > DDR0
}
