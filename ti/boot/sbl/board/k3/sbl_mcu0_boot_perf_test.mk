#
# This file is the makefile for building images used for SBL testing.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

APP_NAME = sbl_boot_perf_test
BUILD_OS_TYPE = baremetal
LOCAL_APP_NAME = sbl_$(BUILD_OS_TYPE)_boot_perf_$(BOARD)_$(CORE)TestApp

SBL_SRC_DIR =  $(PDK_INSTALL_PATH)/ti/boot/sbl

SRCDIR      += $(PDK_SBL_COMP_PATH)/example/k3MulticoreApp

INCDIR      += $(PDK_SBL_COMP_PATH)
INCDIR      += $(PDK_SBL_COMP_PATH)/soc
INCDIR      += $(PDK_SBL_COMP_PATH)/soc/k3
INCDIR      += $(PDK_SBL_COMP_PATH)/example/k3MulticoreApp

# Check for custom flags
ifeq ($(BOOTMODE), cust)
  SBL_CFLAGS = $(CUST_SBL_FLAGS)
endif # ifeq ($(BOOTMODE), cust)

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS) $(SBL_CFLAGS)
PACKAGE_SRCS_COMMON = .

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk

# List all the components required by the application
COMP_LIST_COMMON = $(PDK_COMMON_BAREMETAL_COMP) sbl_lib_$(BOOTMODE)

ifeq ($(filter $(SBL_CFLAGS), -DBOOT_MMCSD), -DBOOT_MMCSD)
  COMP_LIST_COMMON += mmcsd fatfs_indp
endif # ifeq ($(filter $(SBL_CFLAGS), -DBOOT_MMCSD), -DBOOT_MMCSD)

ifeq ($(filter $(SBL_CFLAGS), -DBOOT_OSPI), -DBOOT_OSPI)
ifeq ($(filter $(SBL_CFLAGS), -DSBL_USE_DMA=1), -DSBL_USE_DMA=1)
  COMP_LIST_COMMON += spi_dma
else
  COMP_LIST_COMMON += spi
endif # ifeq ($(filter $(SBL_CFLAGS), -DSBL_USE_DMA=1), -DSBL_USE_DMA=1)
endif # ifeq ($(filter $(SBL_CFLAGS), -DBOOT_OSPI), -DBOOT_OSPI)


SRCS_COMMON += sbl_mcu_0_boot_perf_benchmark.c sbl_printf.c
SRCS_ASM_COMMON = sbl_smp_r5.asm
ifeq ($(filter $(SBL_CFLAGS), -DSBL_ENABLE_DEV_GRP_MCU), -DSBL_ENABLE_DEV_GRP_MCU)
  EXTERNAL_LNKCMD_FILE_LOCAL =  $(PDK_SBL_COMP_PATH)/example/k3MulticoreApp/mcuBootPerfLinker_small.lds
else
  ifeq ($(SOC),$(filter $(SOC), j7200 am65xx))
    EXTERNAL_LNKCMD_FILE_LOCAL =  $(PDK_SBL_COMP_PATH)/example/k3MulticoreApp/mcuBootPerfLinker_small.lds
  else
    SRCS_ASM_COMMON += sbl_boot_perf_r5.asm
    ifeq ($(SOC),$(filter $(SOC), j721e))
      EXTERNAL_LNKCMD_FILE_LOCAL =  $(PDK_SBL_COMP_PATH)/example/k3MulticoreApp/mcuBootPerfLinker_j7.lds
    else
      EXTERNAL_LNKCMD_FILE_LOCAL =  $(PDK_SBL_COMP_PATH)/example/k3MulticoreApp/mcuBootPerfLinker.lds
    endif
  endif
endif # ifeq ($(filter $(SBL_CFLAGS), -DSBL_USE_MCU_DOMAIN_ONLY), -DSBL_USE_MCU_DOMAIN_ONLY)

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

