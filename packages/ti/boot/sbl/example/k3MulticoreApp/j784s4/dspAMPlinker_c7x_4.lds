/*----------------------------------------------------------------------------*/
/* File: linker.lds                                                           */
/* Description:		                            						      */
/*    Linker command file for J784S4 SBL Boot Test on C7x_4    	   		      */
/* (c) Texas Instruments 2023, All rights reserved.                           */
/*----------------------------------------------------------------------------*/

--ram_model
-heap  0x20000
-stack 0x20000
--args 0x1000
--diag_suppress=10068 /* "no matching section" */
--cinit_compression=off
-e _c_int00_secure

MEMORY
{
    DDR_DSP1_C7X 	: ORIGIN = 0x90000000, LENGTH = 0x00900000
    DDR_DSP2_C7X 	: ORIGIN = 0x90900000, LENGTH = 0x00900000
    DDR_DSP3_C7X 	: ORIGIN = 0x91200000, LENGTH = 0x00900000
    DDR_DSP4_C7X 	: ORIGIN = 0x91B00000, LENGTH = 0x00900000
}

SECTIONS
{
    boot:
    {
      boot.*<boot.oe71>(.text)
    } load                   > DDR_DSP4_C7X ALIGN(0x200000)
    .vecs                    > DDR_DSP4_C7X ALIGN(0x400000)
    .secure_vecs             > DDR_DSP4_C7X ALIGN(0x200000)
    .text:_c_int00_secure    > DDR_DSP4_C7X ALIGN(0x200000)
    .text                    > DDR_DSP4_C7X ALIGN(0x200000)

    .bss                     > DDR_DSP4_C7X  /* Zero-initialized data */
    .data                    > DDR_DSP4_C7X  /* Initialized data */
    .sbl_c7x_3_resetvector   > DDR_DSP4_C7X

    .cinit                   > DDR_DSP4_C7X  /* could be part of const */
    .init_array              > DDR_DSP4_C7X  /* C++ initializations */
    .stack                   > DDR_DSP4_C7X ALIGN(0x2000)
    .args                    > DDR_DSP4_C7X
    .cio                     > DDR_DSP4_C7X
    .const                   > DDR_DSP4_C7X
    .switch                  > DDR_DSP4_C7X /* For exception handling. */
    .sysmem                  > DDR_DSP4_C7X /* heap */

    GROUP:                   >  DDR_DSP4_C7X
    {
        .data.Mmu_tableArray          : type=NOINIT
        .data.Mmu_tableArraySlot      : type=NOINIT
        .data.Mmu_level1Table         : type=NOINIT
        .data.Mmu_tableArray_NS       : type=NOINIT
        .data.Mmu_tableArraySlot_NS   : type=NOINIT
        .data.Mmu_level1Table_NS      : type=NOINIT
    }

    ipc_data_buffer:        > DDR_DSP4_C7X
    .benchmark_buffer:      > DDR_DSP4_C7X ALIGN (32) 
    
    .resource_table: { __RESOURCE_TABLE = .;} > DDR_DSP4_C7X
}

