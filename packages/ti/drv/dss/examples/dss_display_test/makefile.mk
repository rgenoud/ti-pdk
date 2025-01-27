#
# This file is the makefile for building DSS display test app for both TI RTOS
# and baremetal
#

SRCDIR = .
INCDIR = .

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk

ifeq ($(BUILD_OS_TYPE), baremetal)
  COMP_LIST_COMMON += $(PDK_COMMON_BAREMETAL_COMP)
  COMP_LIST_COMMON += dss_app_utils
  SRCS_COMMON = main_baremetal.c
  CFLAGS_LOCAL_COMMON += -DDSS_TESTAPP_BAREMETAL
  ifeq ($(ISA),$(filter $(ISA), a53))
    LNKFLAGS_LOCAL_$(CORE) += --entry Entry
  endif
endif

ifeq ($(BUILD_OS_TYPE),tirtos)
  CFLAGS_OS_DEFINES = -DUSE_BIOS
  INCLUDE_EXTERNAL_INTERFACES += xdc bios
  COMP_LIST_COMMON += $(PDK_COMMON_TIRTOS_COMP)
  COMP_LIST_COMMON += dss_app_utils_sysbios
  SRCS_COMMON += main_rtos.c
  CFLAGS_LOCAL_COMMON += -DDSS_TESTAPP_TIRTOS
  # Enable XDC build for application by providing XDC CFG File per core
  XDC_CFG_FILE_$(CORE) = $(PDK_INSTALL_PATH)/ti/build/$(SOC)/sysbios_$(ISA).cfg
  XDC_CFG_UPDATE_$(CORE) = dss_display_test_prf.cfg
endif

ifeq ($(BUILD_OS_TYPE),freertos)
  CFLAGS_OS_DEFINES = -DFREERTOS
  INCLUDE_EXTERNAL_INTERFACES += freertos
  COMP_LIST_COMMON += dss_app_utils
  COMP_LIST_COMMON += $(PDK_COMMON_FREERTOS_COMP)
  SRCS_COMMON += main_rtos.c
  CFLAGS_LOCAL_COMMON += -DDSS_TESTAPP_FREERTOS
endif

# List all the specific components required by the application
COMP_LIST_COMMON += fvid2 dss

# Common source files and CFLAGS across all platforms and cores
PACKAGE_SRCS_COMMON = .
SRCS_COMMON += dss_display_test.c
ifeq ($(BOARD),$(filter $(BOARD), j721e_evm j721s2_evm j784s4_evm))
SRCS_COMMON += dss_display_dsi_cfg.c
endif

CFLAGS_LOCAL_COMMON += $(PDK_CFLAGS) $(DSS_CFLAGS) $(CFLAGS_OS_DEFINES)

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
