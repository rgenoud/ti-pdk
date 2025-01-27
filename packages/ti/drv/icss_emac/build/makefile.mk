#
# Copyright (c) 2016, Texas Instruments Incorporated
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
include $(PDK_ICSS_EMAC_COMP_PATH)/src/src_files_common.mk

MODULE_NAME = icss_emac

ifeq ($(SOC),$(filter $(SOC), am571x am572x am574x am437x am335x k2g am65xx am64x))
SRCDIR += soc/$(SOC)
INCDIR += soc
# Common source files across all platforms and cores
  SRCS_COMMON += icss_emacSoc.c
endif

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk

ifeq ($(SOC),$(filter $(SOC), am571x am572x am574x am437x am335x k2g am65xx am64x))
PACKAGE_SRCS_COMMON += soc/$(SOC)
endif

#Package the associated header, ignore other non-required files
PACKAGE_SRCS_COMMON += soc/icss_emacSoc.h

# Package whole firmware folder for am335x, am437x and am57xx 
# For other platforms package only needed header files
ifeq ($(SOC),$(filter $(SOC), am335x am437x am571x am572x am574x))
PACKAGE_SRCS_COMMON += firmware
else
PACKAGE_SRCS_COMMON += firmware/icss_switch/src/icss_stp_switch.h
PACKAGE_SRCS_COMMON += firmware/icss_switch/config/icss_emacFwVersion.h
PACKAGE_SRCS_COMMON += firmware/icss_dualemac/src/icss_vlan_mcast_filter_mmap.h
PACKAGE_SRCS_COMMON += firmware/icss_dualemac/src/icss_rx_int_pacing_mmap.h
PACKAGE_SRCS_COMMON += firmware/icss_dualemac/config/icss_emacFwConfig.h
PACKAGE_SRCS_COMMON += firmware/icss_dualemac/config/icss_emacFwVersion.h
endif

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS)

ifeq ($(SOC),$(filter $(SOC), am65xx am64x))
CFLAGS_LOCAL_COMMON += -DICSS_EMAC_MII_MODE
endif

# Include common make files
ifeq ($(MAKERULEDIR), )
#Makerule path not defined, define this and assume relative path from ROOTDIR
  MAKERULEDIR := $(ROOTDIR)/ti/build/makerules
  export MAKERULEDIR
endif
include $(MAKERULEDIR)/common.mk

# Nothing beyond this point

