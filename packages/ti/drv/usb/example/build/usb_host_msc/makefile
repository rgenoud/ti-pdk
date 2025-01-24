# Makefile for USB sample app
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

ifeq ($(BAREMETAL),yes)
    BUILD_OS_TYPE=baremetal
    OS_FLAGS=-DBAREMETAL
    LNKFLAGS_LOCAL_mpu1_0  += --entry Entry

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
    INCLUDE_EXTERNAL_INTERFACES = pdk

# List all the components required by the application
    COMP_LIST_COMMON = $(PDK_COMMON_BAREMETAL_COMP)
    COMP_LIST_COMMON += fatfs_indp usb

# Enable XDC build for application by providing XDC CFG File per core
    XDC_CFG_FILE_$(CORE) =

#using USB local linker file instead of ti/build for customization
    ifeq ($(CORE),$(filter $(CORE), mcu1_0))
        EXTERNAL_LNKCMD_FILE_LOCAL = $(pdk_PATH)/ti/drv/usb/example/build/$(SOC)/linker_r5.lds
    endif

    ifeq ($(CORE),$(filter $(CORE), mpu1_0))
        EXTERNAL_LNKCMD_FILE_LOCAL = $(pdk_PATH)/ti/drv/usb/example/build/$(SOC)/linker_a53.lds
    endif

    USB_OS_TESTPREFIX=_Baremetal
    USB_OS_TESTPOSTFIX=
endif
ifeq ($(BUILD_OS_TYPE), tirtos)
    OS_FLAGS=-DTIRTOS

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
    INCLUDE_EXTERNAL_INTERFACES = bios xdc pdk

# List all the components required by the application
    COMP_LIST_COMMON = $(PDK_COMMON_TIRTOS_COMP)
    COMP_LIST_COMMON += fatfs_indp usb

# Enable XDC build for application by providing XDC CFG File per core
    XDC_CFG_FILE_$(CORE) = $(PDK_INSTALL_PATH)/ti/drv/usb/example/bios/$(SOC)/usb_$(SOC)_evm.cfg

#using USB local linker file instead of ti/build for customization
    ifeq ($(CORE),$(filter $(CORE), mcu1_0))
        EXTERNAL_LNKCMD_FILE_LOCAL = $(pdk_PATH)/ti/drv/usb/example/build/$(SOC)/linker_r5_sysbios.lds
    endif

    ifeq ($(CORE),$(filter $(CORE), mpu1_0))
        EXTERNAL_LNKCMD_FILE_LOCAL = $(pdk_PATH)/ti/drv/usb/example/build/$(SOC)/linker_a53.lds
    endif

    USB_OS_TESTPREFIX=
    USB_OS_TESTPOSTFIX=_tirtos

    SRCS_COMMON += host_msc_main.c biosMmu.c
    SRCDIR += $(PDK_INSTALL_PATH)/ti/drv/usb/example/bios
endif

ifeq ($(BUILD_OS_TYPE), freertos)
    OS_FLAGS=-DFREERTOS

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
    INCLUDE_EXTERNAL_INTERFACES = pdk freertos

# List all the components required by the application
    COMP_LIST_COMMON = $(PDK_COMMON_FREERTOS_COMP)
    COMP_LIST_COMMON += fatfs_indp usb

#using USB local linker file instead of ti/build for customization
    ifeq ($(CORE),$(filter $(CORE), mcu1_0))
        EXTERNAL_LNKCMD_FILE_LOCAL = $(pdk_PATH)/ti/drv/usb/example/build/$(SOC)/linker_r5_freertos.lds
        SRCS_COMMON += r5_mpu.c
        SRCS_ASM_COMMON += usb_arm_r5.asm
    endif

    ifeq ($(CORE),$(filter $(CORE), mpu1_0))
        EXTERNAL_LNKCMD_FILE_LOCAL = $(pdk_PATH)/ti/drv/usb/example/build/$(SOC)/linker_$(ISA).lds
    endif

    USB_OS_TESTPREFIX=
    USB_OS_TESTPOSTFIX=_freertos

    SRCS_COMMON += host_msc_main.c
    SRCDIR += $(PDK_INSTALL_PATH)/ti/drv/usb/example/bios
endif

USB3OPT=
USB3FLG=

ifeq ($(USB30),yes)
    USB3OPT=usb30_
    USB3FLG=-DUSB3SS_EN
endif

#Name of the directory created under packages/ti/binary/
APP_NAME = USB$(USB_OS_TESTPREFIX)_HostMsc_$(USB3OPT)TestApp$(USB_OS_TESTPOSTFIX)

SRCDIR += . $(PDK_INSTALL_PATH)/ti/drv/usb/example/shell
SRCDIR += $(PDK_INSTALL_PATH)/ti/drv/usb/example/usb_host/msc
SRCDIR += $(PDK_INSTALL_PATH)/ti/drv/usb/example/common

INCDIR = . src
INCDIR += $(PDK_INSTALL_PATH)/ti/csl
INCDIR += $(PDK_INSTALL_PATH)/ti/csl/arch/r5
INCDIR += $(PDK_INSTALL_PATH)/ti/drv/usb
INCDIR += $(PDK_INSTALL_PATH)/ti/drv/usb/example/usb_host/msc
INCDIR += $(PDK_INSTALL_PATH)/ti/drv/usb/src/usb_func/include
INCDIR += $(PDK_INSTALL_PATH)/ti/drv/usb/src/include
INCDIR += $(PDK_INSTALL_PATH)/ti/drv/usb/example/shell
INCDIR += $(PDK_INSTALL_PATH)/ti/drv/usb/example/common

# Common source files across all platforms and cores
SRCS_COMMON += fs_shell_app_utils.c fatfs_port_usbmsc.c usb_osal.c intRouter.c timer.c


ifeq ($(BOARD),$(filter $(BOARD), j721e_evm))
    SRCS_COMMON += usb_c_handler.c
endif

ifeq ($(BAREMETAL),yes)
    SRCS_COMMON += usb_main.c

    ifeq ($(CORE),mcu1_0)
    # bare-metal R5 USB host MSC apps needs different MPU settings compared
    # to the standard MPU configurations offered in CSL.
    # So adding it here.
        SRCS_COMMON += r5_mpu.c
        SRCS_ASM_COMMON += usb_arm_r5.asm
        INCDIR += $(PDK_INSTALL_PATH)/ti/csl/arch/r5
    endif
endif

PACKAGE_SRCS_COMMON += .
CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS) $(OS_FLAGS) $(USB3FLG)


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
