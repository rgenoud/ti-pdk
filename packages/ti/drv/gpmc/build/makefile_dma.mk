#
# Copyright (c) 2020, Texas Instruments Incorporated
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# *  Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#
# *  Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# *  Neither the name of Texas Instruments Incorporated nor the names of
#    its contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
# EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

include $(PDK_INSTALL_PATH)/ti/build/Rules.make
include $(PDK_GPMC_COMP_PATH)/src/src_files_common.mk

MODULE_NAME = gpmc_dma

SRCDIR += soc/$(SOC)
ifeq ($(SOC),$(filter $(SOC), am437x am335x))
    SRCDIR += soc/dma/v0
endif
ifeq ($(SOC),$(filter $(SOC), am64x))
    SRCDIR += soc/dma/v1
endif

INCDIR += soc
# Common source files across all platforms and cores
SRCS_COMMON += GPMC_soc.c GPMC_dma.c

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk
ifeq ($(SOC),$(filter $(SOC), am437x am335x))
    INCLUDE_EXTERNAL_INTERFACES += edma
endif
ifeq ($(SOC),$(filter $(SOC), am64x))
    INCLUDE_EXTERNAL_INTERFACES += udma
endif

PACKAGE_SRCS_COMMON += soc/$(SOC)
ifeq ($(SOC),$(filter $(SOC), am437x am335x))
    PACKAGE_SRCS_COMMON += soc/dma/v0
endif
ifeq ($(SOC),$(filter $(SOC), am64x))
    PACKAGE_SRCS_COMMON += soc/dma/v1
endif

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS) -DGPMC_DMA_ENABLE

# Include common make files
ifeq ($(MAKERULEDIR), )
#Makerule path not defined, define this and assume relative path from ROOTDIR
  MAKERULEDIR := $(ROOTDIR)/ti/build/makerules
  export MAKERULEDIR
endif
include $(MAKERULEDIR)/common.mk

# OBJs and libraries are built by using rule defined in rules_<target>.mk
#     and need not be explicitly specified here

# Nothing beyond this point
