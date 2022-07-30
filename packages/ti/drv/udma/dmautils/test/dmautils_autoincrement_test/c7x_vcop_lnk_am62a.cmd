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

MEMORY
{
  L2_Main (RWX): org = 0x7e000000, len = 0x100000
  L2_Aux  (RWX): org = 0x7f000000, len = 0x40000
  L1D          : org = 0x64E00000, len = 0x4000
// L2_Main          : org = 0x80000100, len = 0x800000
// L2_Main_CINIT    : org = 0x80000000, len = 0x000100
}


SECTIONS
{
    .text:_c_int00:   > L2_Main
    .text       >       L2_Main    
    .bss        >       L2_Main  /* Zero-initialized data */
    .data       >       L2_Main  /* Initialized data */
    .cinit      >       L2_Main  /* could be part of const */
    .init_array >       L2_Main  /* C++ initializations */
    .stack      >       L2_Main
    .args       >       L2_Main
    .cio        >       L2_Main
    .const      >       L2_Main
    .switch     >       L2_Main /* For exception handling. */
                             /* Not a default ELF section -- remove?  */
                             /* could be part of const */
    .sysmem     >       L2_Main /* heap */
	.L2SramSect >       L2_Aux /* TODO */
	.MSMCSramSect >     L2_Main
}
