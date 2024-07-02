BUILD_OS_TYPE = freertos

include $(PDK_INSTALL_PATH)/ti/build/Rules.make

ifeq ($(BUILD_HS), yes)
    HS_SUFFIX =_hs
else 
    HS_SUFFIX =
endif

ifeq ($(HLOSBOOT), qnx)
    HLOS_SUFFIX =_qnx
else ifeq ($(HLOSBOOT), linux)
    HLOS_SUFFIX =_linux
else 
    HLOS_SUFFIX =
endif

SOC_DIR=$(SOC)
ifeq ($(SOC), j742s2)
  SOC_DIR=j784s4
endif

CFLAGS_LOCAL_COMMON  = $(PDK_CFLAGS)
PACKAGE_SRCS_COMMON  = .

ifeq ($(SAFETY_LOOP), yes)
    ifeq ($(BOOTMODE), mmcsd)
        APP_NAME = boot_app_$(BOOTMODE)_safety
        LOCAL_APP_NAME = boot_app_$(BOOTMODE)_safety_$(BOARD)_$(CORE)_$(BUILD_OS_TYPE)
        CFLAGS_LOCAL_COMMON += -DSAFETY_CHECKER_LOOP_ENABLED
        #Enable below flag to take the register configuration for PM, RM and TIFS modules
        #CFLAGS_LOCAL_COMMON += -DSC_REGDUMP_ENABLE
    endif
else
    APP_NAME = boot_app_$(BOOTMODE)$(HLOS_SUFFIX)$(HS_SUFFIX)
    LOCAL_APP_NAME = sbl_boot_app_$(BOOTMODE)$(HLOS_SUFFIX)$(HS_SUFFIX)_$(BOARD)_$(CORE)_$(BUILD_OS_TYPE)_TestApp
endif

SRCDIR      = $(PDK_SBL_COMP_PATH)/example/boot_app

INCDIR      =  $(PDK_INSTALL_PATH)/ti/boot/sbl/soc/k3
INCDIR      += $(PDK_SBL_COMP_PATH)/
INCDIR      += $(PDK_SBL_COMP_PATH)/example/boot_app

ifeq ($(SAFETY_LOOP), yes)
    INCDIR      += $(SAFETY_CHECKERS_COMP_PATH)/src $(SAFETY_CHECKERS_COMP_PATH)/src/soc
    INCDIR      += $(SAFETY_CHECKERS_COMP_PATH)/src/soc/$(SOC)/
    INCDIR      += $(PDK_INSTALL_PATH)/ti/csl/soc/$(SOC)/src/
endif

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk

# List all the components required by the application
COMP_LIST_COMMON = $(PDK_COMMON_FREERTOS_COMP) sciserver_tirtos

ifeq ($(SAFETY_LOOP), yes)
    COMP_LIST_COMMON += safety_checkers
endif

SRCS_COMMON = boot_app_main.c soc/$(SOC_DIR)/boot_core_defs.c r5_mpu_freertos.c

ifeq ($(BOOTMODE), ospi)
    SRCS_COMMON += boot_app_ospi.c
else ifeq ($(BOOTMODE), mmcsd)
    SRCS_COMMON += boot_app_mmcsd.c
endif

ifeq ($(BOOTMODE), mmcsd)
    ifeq ($(BUILD_HS), yes)
        COMP_LIST_COMMON += mmcsd sbl_lib_mmcsd_hs fatfs_indp
    else 
        COMP_LIST_COMMON += mmcsd sbl_lib_mmcsd fatfs_indp
    endif
    CFLAGS_LOCAL_COMMON += -DBOOT_MMCSD
endif

ifeq ($(BOOTMODE), ospi)
    ifeq ($(BUILD_HS), yes)
        COMP_LIST_COMMON += spi_dma sbl_lib_cust_hs
    else 
        COMP_LIST_COMMON += spi_dma sbl_lib_cust
    endif
    CFLAGS_LOCAL_COMMON += -DBOOT_OSPI
endif
ifeq ($(CANRESP), enabled)
    CFLAGS_LOCAL_COMMON += -DCAN_RESP_TASK_ENABLED
    SRCS_COMMON += boot_app_can.c
endif

ifeq ($(HLOSBOOT), linux)
    CFLAGS_LOCAL_COMMON += -DMPU1_HLOS_BOOT_ENABLED -DHLOS_BOOT_LINUX_OS
else ifeq ($(HLOSBOOT), qnx)
    CFLAGS_LOCAL_COMMON += -DMPU1_HLOS_BOOT_ENABLED -DHLOS_BOOT_QNX_OS
endif

ifeq ($(SAFETY_LOOP), yes)
    EXTERNAL_LNKCMD_FILE_LOCAL = $(PDK_SBL_COMP_PATH)/example/boot_app/linker_r5_freertos_safety.lds
else
    EXTERNAL_LNKCMD_FILE_LOCAL = $(PDK_SBL_COMP_PATH)/example/boot_app/linker_r5_freertos.lds
endif

# Include common make files
ifeq ($(MAKERULEDIR), )
#Makerule path not defined, define this and assume relative path from ROOTDIR
  MAKERULEDIR := $(ROOTDIR)/ti/build/makerules
  export MAKERULEDIR
endif
include $(MAKERULEDIR)/common.mk
