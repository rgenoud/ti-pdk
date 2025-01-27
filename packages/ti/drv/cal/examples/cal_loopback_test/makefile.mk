#
# This file is the makefile for building CAL loopback example application.
#
SRCDIR =   src
INCDIR = . src

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk
INCLUDE_INTERNAL_INTERFACES =

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS) $(CAL_CFLAGS)

ifeq ($(BUILD_OS_TYPE), baremetal)
  COMP_LIST_COMMON = $(PDK_COMMON_BAREMETAL_COMP) 
  COMP_LIST_COMMON += cal_app_utils_baremetal
  SRCS_COMMON = main_baremetal.c
  ifeq ($(ISA),$(filter $(ISA), a53))
    LNKFLAGS_LOCAL_$(CORE) += --entry Entry
  endif
  CFLAGS_LOCAL_COMMON += -DBARE_METAL
else
  INCLUDE_EXTERNAL_INTERFACES += xdc bios
  COMP_LIST_COMMON = $(PDK_COMMON_TIRTOS_COMP) 
  COMP_LIST_COMMON += cal_app_utils
  SRCS_COMMON = main_tirtos.c
  # Enable XDC build for application by providing XDC CFG File per core
  XDC_CFG_FILE_$(CORE) = $(PDK_INSTALL_PATH)/ti/build/$(SOC)/sysbios_$(ISA).cfg
endif

# List all the specific components required by the application
COMP_LIST_COMMON += fvid2 cal dss 
COMP_LIST_COMMON += dss_app_utils

ifeq ($(CORE),$(filter $(CORE), mpu1_0 mpu1_1))
EXTERNAL_LNKCMD_FILE_LOCAL = $(PDK_CAL_COMP_PATH)/examples/utils/src/V0/linker_cal_a53.lds
endif

PACKAGE_SRCS_COMMON = .

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON += cal_loopback_test.c

# Core/SoC/platform specific source files and CFLAGS
# Example:
#   SRCS_<core/SoC/platform-name> =
#   CFLAGS_LOCAL_<core/SoC/platform-name> =

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
