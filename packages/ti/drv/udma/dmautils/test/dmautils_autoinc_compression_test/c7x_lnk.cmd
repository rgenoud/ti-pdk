/****************************************************************************/
/*  lnk.cmd   v#.##                                                         */
/*  Copyright (c) 2014-%%%%  Texas Instruments Incorporated                 */
/*                                                                          */
/*  Usage: cl7x  <src files...> -z -o <out file> -m <map file> lnk.cmd      */
/*                                                                          */
/*    Description: THIS FILE IS A SAMPLE linker command file that can be    */
/*                 used for linking programs built with the C compiler and  */
/*                 running the resulting .out file on a C7100 simulator.    */
/*                 Use it as a guideline.  You will want to change the      */
/*                 memory layout to match your specific C7xxx target        */
/*                 system.  You may want to change the allocation scheme    */
/*                 according to the size of your program.                   */
/*                                                                          */
/*    Notes: (1)   You must specify a directory in which your library is    */
/*                 located.  either add a -i"<directory>" line to this      */
/*                 file or use the system environment variable C_DIR to     */
/*                 specify a search path for the libraries.                 */
/*                                                                          */
/*           (2)   You may need to specify your library name with           */
/*                 -llibrary.lib if the correct library is not found        */
/*                 automatically.                                           */
/*                                                                          */
/****************************************************************************/
-c
-heap  0x2000
-stack 0x2000
--args 0x1000
--diag_suppress=10068 // "no matching section"
//--cinit_compression=off
--ram_model
-e _c_int00_secure

MEMORY
{
  L2SRAM   (RWX): org = 0x64800000, len = 0x080000
  MSMCSRAM (RWX): org = 0x70040000, len = 0x800000
  L1D           : org = 0x64E00000, len = 0x4000
  DDR           : org = 0x80000000, len = 0x80000000
}


SECTIONS
{
    boot:
    {
      boot.*<boot.oe71>(.text)
    } load > DDR ALIGN(0x200000)
    .vecs       >       DDR ALIGN(0x400000)
    .secure_vecs    >   DDR ALIGN(0x200000)
    .text:_c_int00_secure > DDR ALIGN(0x200000)

    .text       >       MSMCSRAM

    .bss        >       MSMCSRAM  /* Zero-initialized data */
    .data       >       MSMCSRAM  /* Initialized data */

    .cinit      >       MSMCSRAM  /* could be part of const */
    .init_array >       MSMCSRAM  /* C++ initializations */
    .stack      >       MSMCSRAM
    .args       >       MSMCSRAM
    .cio        >       MSMCSRAM
    .const      >       MSMCSRAM
    .switch     >       MSMCSRAM /* For exception handling. */
                             /* Not a default ELF section -- remove?  */
                             /* could be part of const */
    .sysmem     >       MSMCSRAM /* heap */
	.L2SramSect >       L2SRAM /* TODO */
	.MSMCSramSect >     MSMCSRAM
  
    GROUP:              >  DDR
    {
        .data.Mmu_tableArray          : type=NOINIT
        .data.Mmu_tableArraySlot      : type=NOINIT
        .data.Mmu_level1Table         : type=NOINIT
        .data.Mmu_tableArray_NS       : type=NOINIT
        .data.Mmu_tableArraySlot_NS   : type=NOINIT
        .data.Mmu_level1Table_NS      : type=NOINIT
    }
}
