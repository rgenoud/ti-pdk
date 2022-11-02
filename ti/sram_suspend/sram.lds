MEMORY
{
  sram      (rwx) : ORIGIN = /*0x41010c30*/0x41011000, LENGTH = 0x00008000
}

STACK_SIZE = 0x1000; /* 4 kB */

SECTIONS
{
    .text :
    {

    } > sram

    .stack (NOLOAD) :
    {
        . = ALIGN(8);
        . = . + STACK_SIZE;
        . = ALIGN(8);
    } > sram
}
