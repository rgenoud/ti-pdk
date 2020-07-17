--load_image
--image
--load_image:machine=ARM
--load_image:endian=little

--load_image:symbol_binding=local
--load_image:localize=shared_buf

--exclude=.resource_table

ROMS
{
   PAGE 0:
      PRU0_REV2_IMEM: o=0x00000000 l=0x00002000

   PAGE 1:
      PRU0_REV2_DMEM: o=0x00000000 l=0x00002000
      PRU0_REV2_EXT:  o=0x80000000 l=0x00001000
}
