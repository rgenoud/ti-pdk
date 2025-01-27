#*******************************************************************************
#* FILE PURPOSE: Lower level makefile for Creating Component Libraries
#*******************************************************************************
#* FILE NAME: ./build/armv7/ti.transport.ndk.nimu.aa8fg.mk
#*
#* DESCRIPTION: Defines Source Files, Compilers flags and build rules
#*
#*
#*******************************************************************************
#

#
# Macro definitions referenced below
#
empty =
space =$(empty) $(empty)
CC = $(TOOLCHAIN_PATH_A8)/bin/$(CROSS_TOOL_PRFX)gcc
AC = $(TOOLCHAIN_PATH_A8)/bin/$(CROSS_TOOL_PRFX)as
ARIN = $(TOOLCHAIN_PATH_A8)/bin/$(CROSS_TOOL_PRFX)ar
LD = $(TOOLCHAIN_PATH_A8)/bin/$(CROSS_TOOL_PRFX)gcc
INCS = -I. -I$(strip $(subst ;, -I,$(subst $(space),\$(space),$(INCDIR)))) -I$(TOOLCHAIN_PATH_A8)/include
OBJEXT = oa8fg
AOBJEXT = sa8fg
CFLAGS_INTERNAL = -mno-unaligned-access -c -mtune=cortex-a8 -marm -g -gstrict-dwarf -Wall -D__ARMv7 -D_LITTLE_ENDIAN=1 -mcpu=cortex-a8 -mfpu=neon -mfloat-abi=hard -mabi=aapcs -g
ASFLAGS_INTERNAL =  -mcpu=cortex-a8 -mfpu=neon -mfloat-abi=hard
ARFLAGS_INTERNAL = cr
LNKFLAGS_INTERNAL = 
INTERNALDEFS = -MD -MF $@.dep
INTERNALLINKDEFS = -o $@ -m $@.map
OBJDIR =  $(LIBDIR)/armv7/obj

#List the COMMONSRC Files
COMMONSRCC= \
    src/v1/cpsw_ethdriver.c\
    src/v1/cpsw_impl.c\
    src/v1/cpsw_nimu_eth.c

# FLAGS for the COMMONSRC Files
COMMONSRCCFLAGS =   -I./src -I. 

# Make Rule for the COMMONSRC Files
COMMONSRCCOBJS = $(patsubst %.c, $(OBJDIR)/%.$(OBJEXT), $(COMMONSRCC))

$(COMMONSRCCOBJS): $(OBJDIR)/%.$(OBJEXT): %.c
	-@echo cla8fg $< ...
	if [ ! -d $(@D) ]; then $(MKDIR) $(@D) ; fi;
	$(RM) $@.dep
	$(CC) $(CFLAGS_INTERNAL) $(COMMONSRCCFLAGS) $(INTERNALDEFS) $(INCS) $< -o $@

#Create Empty rule for dependency
$(COMMONSRCCOBJS):.\build\armv7\ti.transport.ndk.nimu.aa8fg.mk
.\build\armv7\ti.transport.ndk.nimu.aa8fg.mk:

#Include Depedency for COMMONSRC Files
ifneq (clean,$(MAKECMDGOALS))
 -include $(COMMONSRCCOBJS:%.$(OBJEXT)=%.$(OBJEXT).dep)
endif


$(LIBDIR)/armv7/ti.transport.ndk.nimu.aa8fg : $(COMMONSRCCOBJS)
	@echo archiving $? into $@ ...
	if [ ! -d $(LIBDIR)/armv7 ]; then $(MKDIR) $(LIBDIR)/armv7 ; fi;
	$(ARIN) $(ARFLAGS_INTERNAL) $@ $?
