# This makefile has for goal to generate the
# ti/drv/sciclient/src/sciclient/sram_s2r.h file. It is an header file that
# contains code that will be loaded to SRAM for S2R support.

ifndef LD
# The Linux SDK contains an appropriate toolchain:
# linux-devkit/sysroots/x86_64-arago-linux/usr/bin/arm-none-linux-gnueabihf-
$(error Missing LD or CROSS_COMPILE for "arm-none-linux-gnueabihf-" GCC toolchain)
endif

ifndef OBJCOPY
$(error Missing OBJCOPY or CROSS_COMPILE for "arm-none-linux-gnueabihf-" GCC toolchain)
endif

ifndef TOOLCHAIN_PATH_R5
# The RTOS SDK contains an appropriate toolchain:
# ti-cgt-armllvm_1.3.0.LTS/
$(error Missing TOOLCHAIN_PATH_R5 for cgt-armllvm toolchain)
endif

ifndef PDK_INSTALL_PATH
# Should be the PDK root folder, probably $(pwd)/../..
$(error Missing PDK_INSTALL_PATH)
endif

INSTALL_PATH = $(PDK_INSTALL_PATH)/ti/drv/sciclient/src/sciclient/sram_s2r.h

.PHONY: all clean

all: $(INSTALL_PATH)

clean:
	$(RM) $(addprefix sram_s2r., elf bin o h)
	$(RM) $(INSTALL_PATH)

sram_s2r.o: sram_s2r.c
	$(TOOLCHAIN_PATH_R5)/bin/tiarmclang \
		-fomit-frame-pointer -nostdlib -DSOC_J7200 -mcpu=cortex-r5 \
		-I$(PDK_INSTALL_PATH) -o $@ -c $<

sram_s2r.elf: sram.lds sram_s2r.o
	$(LD) -T sram.lds -Bstatic sram_s2r.o -o $@

sram_s2r.bin: sram_s2r.elf
	$(OBJCOPY) -O binary $< $@

sram_s2r.h: sram_s2r.bin
	echo "/* Automatically generated, see ti/sram_suspend/ */" > $@
	xxd -i $< >> $@

$(INSTALL_PATH): sram_s2r.h
	cp $< $@
