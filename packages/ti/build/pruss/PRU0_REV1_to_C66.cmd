--load_image
--image
--load_image:machine=C6000
--load_image:endian=little

--load_image:symbol_binding=local
--load_image:localize=shared_buf

--exclude=.resource_table

ROMS
{
   PAGE 0:
      PRU0_REV1_IMEM: o=0x00000000 l=0x00002000

   PAGE 1:
      PRU0_REV1_DMEM: o=0x00000000 l=0x00002000
      PRU0_REV1_EXT:  o=0x80000000 l=0x00001000
}
