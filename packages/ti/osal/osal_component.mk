#
# Copyright (c) 2016-2021, Texas Instruments Incorporated
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

# File: osal_component.mk
#       This file is component include make file of OSAL library.
# List of variables set in this file and their purpose:
# <mod>_RELPATH        - This is the relative path of the module, typically from
#                        top-level directory of the package
# <mod>_PATH           - This is the absolute path of the module. It derives from
#                        absolute path of the top-level directory (set in env.mk)
#                        and relative path set above
# <mod>_INCLUDE        - This is the path that has interface header files of the
#                        module. This can be multiple directories (space separated)
# <mod>_PKG_LIST       - Names of the modules (and sub-modules) that are a part
#                        part of this module, including itself.
# <mod>_BOARD_DEPENDENCY - "yes": means the code for this module depends on
#                             board and the compiled obj/lib has to be kept
#                             under <board> directory
#                             "no" or "" or if this variable is not defined: means
#                             this module has no baord dependent code and hence
#                             the obj/libs are not kept under <board> dir.
# <mod>_CORE_DEPENDENCY     - "yes": means the code for this module depends on
#                             core and the compiled obj/lib has to be kept
#                             under <core> directory
#                             "no" or "" or if this variable is not defined: means
#                             this module has no core dependent code and hence
#                             the obj/libs are not kept under <core> dir.
# <mod>_APP_STAGE_FILES     - List of source files that belongs to the module
#                             <mod>, but that needs to be compiled at application
#                             build stage (in the context of the app). This is
#                             primarily for link time configurations or if the
#                             source file is dependent on options/defines that are
#                             application dependent. This can be left blank or
#                             not defined at all, in which case, it means there
#                             no source files in the module <mod> that are required
#                             to be compiled in the application build stage.
#
ifeq ($(osal_component_make_include), )

libosal_RTOS_LIST = $(DEFAULT_RTOS_LIST)

libosal_BOARDLIST  = j721e_evm j7200_evm j721s2_evm j784s4_evm j722s_evm am62x_evm am62a_evm

libosal_SOCLIST   =  j721e j7200 j721s2 j784s4 am62x am62a j722s

libosal_freertos_BOARDLIST  = j721e_evm j7200_evm j721s2_evm j784s4_evm j722s_evm am62x_evm am62a_evm
libosal_freertos_SOCLIST    = j721e j7200 j721s2 j784s4 j722s am62x am62a
libosal_safertos_BOARDLIST  = j721e_evm
libosal_safertos_SOCLIST    = j721e


ifeq ($(SOC),$(filter $(SOC), $(libosal_SOCLIST)))
libosal_$(SOC)_CORELIST   = $(DEFAULT_$(SOC)_CORELIST)
libosal_freertos_$(SOC)_CORELIST = $(filter-out mpu%, $(libosal_$(SOC)_CORELIST))
endif

libosal_safertos_j721e_CORELIST   = mcu1_0 mcu1_1 mcu2_0 mcu2_1 mcu3_0 mcu3_1 c66xdsp_1 c66xdsp_2 c7x_1
libosal_am62x_CORELIST = $(DEFAULT_am62x_CORELIST)
libosal_am62a_CORELIST = $(DEFAULT_am62a_CORELIST)
libosal_j722s_CORELIST = $(DEFAULT_j722s_CORELIST)
libosal_freertos_am62x_CORELIST = mcu1_0
libosal_freertos_am62a_CORELIST = mcu1_0 c7x_1
libosal_freertos_j722s_CORELIST = mcu1_0 mcu2_0 c7x_1

############################
# osal package
# List of components included under osal lib
# The components included here are built and will be part of osal lib
############################
osal_LIB_LIST = osal_nonos osal_nonos_indp
osal_LIB_LIST += osal_freertos
ifeq ($(SOC),$(filter $(SOC), $(libosal_safertos_SOCLIST)))
ifneq ($(wildcard $(SAFERTOS_KERNEL_INSTALL_PATH)),)
osal_LIB_LIST += osal_safertos
endif
endif
ifeq ($(BUILD_OS_TYPE), qnx)
osal_LIB_LIST += osal_qnx
endif

libosal_LIB_LIST = $(osal_LIB_LIST)

############################
# osal examples
# List of examples under osal
# All the tests mentioned in list are built when test target is called
# List below all examples for allowed values
############################

#
# QNX Modules
#

# OSAL QNX LIB
export osal_qnx_COMP_LIST = osal_qnx
osal_qnx_RELPATH = ti/osal
osal_qnx_PATH = $(PDK_OSAL_COMP_PATH)
export osal_qnx_LIBNAME = ti.osal
export osal_qnx_LIBPATH = $(osal_qnx_PATH)/lib/qnx
export osal_qnx_OBJPATH = $(osal_qnx_RELPATH)/osal_qnx
export osal_qnx_MAKEFILE = -f build/makefile_qnx.mk
export osal_qnx_PLATFORM_DEPENDENCY = no
export osal_qnx_CORE_DEPENDENCY = no
export osal_qnx_SOC_DEPENDENCY = yes
export osal_qnx_PKG_LIST = osal_qnx
osal_qnx_INCLUDE = $(osal_qnx_PATH)
export osal_qnx_SOCLIST = $(libosal_SOCLIST)
export osal_qnx_$(SOC)_CORELIST = qnx_mpu1_0

osal_EXAMPLE_LIST =

#
# OSAL Modules
#

# OSAL NONOS LIB
export osal_nonos_COMP_LIST = osal_nonos
osal_nonos_RELPATH = ti/osal
osal_nonos_PATH = $(PDK_OSAL_COMP_PATH)
export osal_nonos_LIBNAME = ti.osal
export osal_nonos_LIBPATH = $(osal_nonos_PATH)/lib/nonos
export osal_nonos_OBJPATH = $(osal_nonos_RELPATH)/osal_nonos
export osal_nonos_MAKEFILE = -f build/makefile_nonos.mk
export osal_nonos_PLATFORM_DEPENDENCY = no
export osal_nonos_CORE_DEPENDENCY = no
export osal_nonos_SOC_DEPENDENCY = yes
export osal_nonos_PKG_LIST = osal_nonos
osal_nonos_INCLUDE = $(osal_nonos_PATH)
export osal_nonos_SOCLIST = $(libosal_SOCLIST)
osal_nonos_$(SOC)_CORELIST = $(libosal_$(SOC)_CORELIST)
ifeq ($(SOC),$(filter $(SOC), j721e j721s2 j784s4 j722s))
osal_nonos_$(SOC)_CORELIST += c7x-hostemu
endif
export osal_nonos_$(SOC)_CORELIST

# OSAL FREE RTOS LIB
export osal_freertos_COMP_LIST = osal_freertos
osal_freertos_RELPATH = ti/osal
osal_freertos_PATH = $(PDK_OSAL_COMP_PATH)
export osal_freertos_LIBNAME = ti.osal
export osal_freertos_LIBPATH = $(osal_freertos_PATH)/lib/freertos
export osal_freertos_OBJPATH = $(osal_freertos_RELPATH)/osal_freertos
export osal_freertos_MAKEFILE = -f build/makefile_freertos.mk
export osal_freertos_PLATFORM_DEPENDENCY = no
export osal_freertos_CORE_DEPENDENCY = no
export osal_freertos_SOC_DEPENDENCY = yes
export osal_freertos_PKG_LIST = osal_freertos
osal_freertos_INCLUDE = $(osal_freertos_PATH)
export osal_freertos_SOCLIST = $(libosal_freertos_SOCLIST)
export osal_freertos_$(SOC)_CORELIST = $(libosal_freertos_$(SOC)_CORELIST)

# OSAL SAFE RTOS LIB
export osal_safertos_COMP_LIST = osal_safertos
osal_safertos_RELPATH = ti/osal
osal_safertos_PATH = $(PDK_OSAL_COMP_PATH)
export osal_safertos_LIBNAME = ti.osal
export osal_safertos_LIBPATH = $(osal_safertos_PATH)/lib/safertos
export osal_safertos_OBJPATH = $(osal_safertos_RELPATH)/osal_safertos
export osal_safertos_MAKEFILE = -f build/makefile_safertos.mk
export osal_safertos_PLATFORM_DEPENDENCY = no
export osal_safertos_CORE_DEPENDENCY = no
export osal_safertos_SOC_DEPENDENCY = yes
export osal_safertos_PKG_LIST = osal_safertos
osal_safertos_INCLUDE = $(osal_safertos_PATH)
export osal_safertos_SOCLIST = $(libosal_safertos_SOCLIST)
export osal_safertos_$(SOC)_CORELIST = $(libosal_safertos_$(SOC)_CORELIST)

#
# OSAL Examples
#
export OSAL_Baremetal_TestApp_COMP_LIST = OSAL_Baremetal_TestApp
OSAL_Baremetal_TestApp_RELPATH = ti/osal/test/baremetal
OSAL_Baremetal_TestApp_PATH = $(PDK_OSAL_COMP_PATH)/test/baremetal
export OSAL_Baremetal_TestApp_BOARD_DEPENDENCY = yes
export OSAL_Baremetal_TestApp_CORE_DEPENDENCY = no
OSAL_Baremetal_TestApp_PKG_LIST = OSAL_Baremetal_TestApp
OSAL_Baremetal_TestApp_INCLUDE = $(OSAL_Baremetal_TestApp_PATH)
export OSAL_Baremetal_TestApp_BOARDLIST = $(libosal_BOARDLIST)
ifeq ($(SOC),$(filter $(SOC), am62x am62a j722s))
export OSAL_Baremetal_TestApp_SBL_APPIMAGEGEN = no
else
export OSAL_Baremetal_TestApp_SBL_APPIMAGEGEN = yes
endif
osal_EXAMPLE_LIST += OSAL_Baremetal_TestApp

define OSAL_TestApp_RULE

export OSAL_TestApp_$(1)_COMP_LIST = OSAL_TestApp_$(1)
export OSAL_TestApp_$(1)_RELPATH = ti/osal/test/os_unit_test
export OSAL_TestApp_$(1)_PATH = $(PDK_OSAL_COMP_PATH)/test/os_unit_test
export OSAL_TestApp_$(1)_BOARD_DEPENDENCY = yes
export OSAL_TestApp_$(1)_CORE_DEPENDENCY = no
export OSAL_TestApp_$(1)_MAKEFILE = -f makefile BUILD_OS_TYPE=$(1)
export OSAL_TestApp_$(1)_PKG_LIST = OSAL_TestApp_$(1)
export OSAL_TestApp_$(1)_INCLUDE = $(OSAL_TestApp_$(1)_PATH)
export OSAL_TestApp_$(1)_BOARDLIST = $(filter $(DEFAULT_BOARDLIST_$(1)), $(libosal_$(1)_BOARDLIST))
export OSAL_TestApp_$(1)_$(SOC)_CORELIST = $(filter $(DEFAULT_$(SOC)_CORELIST_$(1)), $(libosal_$(SOC)_CORELIST))
ifneq ($(1),$(filter $(1), safertos))
osal_EXAMPLE_LIST += OSAL_TestApp_$(1)
else
ifneq ($(wildcard $(SAFERTOS_KERNEL_INSTALL_PATH)),)
osal_EXAMPLE_LIST += OSAL_TestApp_$(1)
endif
endif
ifeq ($(SOC),$(filter $(SOC), am62x am62a j722s))
export OSAL_TestApp_$(1)_SBL_APPIMAGEGEN = no
else
export OSAL_TestApp_$(1)_SBL_APPIMAGEGEN = yes
endif

endef

OSAL_TestApp_MACRO_LIST := $(foreach curos,$(libosal_RTOS_LIST) safertos,$(call OSAL_TestApp_RULE,$(curos)))

$(eval ${OSAL_TestApp_MACRO_LIST})

ifeq ($(SOC),$(filter $(SOC), j721e))
 OSAL_Baremetal_TestApp_$(SOC)_CORELIST = mpu1_0 mcu1_0 mcu2_0 mcu3_0
 OSAL_TestApp_freertos_$(SOC)_CORELIST = mcu1_0 mcu1_1 mcu2_0 mcu2_1 mcu3_0 mcu3_1 c66xdsp_1 c66xdsp_2 c7x_1
 OSAL_TestApp_safertos_$(SOC)_CORELIST = mcu1_0 mcu1_1 mcu2_0 mcu2_1 mcu3_0 mcu3_1 c66xdsp_1 c66xdsp_2 c7x_1
endif

ifeq ($(SOC),$(filter $(SOC), j7200))
 OSAL_Baremetal_TestApp_$(SOC)_CORELIST = mpu1_0 mcu1_0 mcu2_0
 OSAL_TestApp_freertos_$(SOC)_CORELIST = mcu1_0 mcu1_1 mcu2_0 mcu2_1
endif

ifeq ($(SOC),$(filter $(SOC), j721s2))
 OSAL_Baremetal_TestApp_$(SOC)_CORELIST = mpu1_0 mcu1_0 mcu2_0 mcu3_0
 OSAL_TestApp_freertos_$(SOC)_CORELIST = mcu1_0 mcu1_1 mcu2_0 mcu2_1 mcu3_0 mcu3_1 c7x_1 c7x_2
endif

ifeq ($(SOC),$(filter $(SOC), j784s4))
 OSAL_Baremetal_TestApp_$(SOC)_CORELIST = mpu1_0 mcu1_0 mcu2_0 mcu3_0 mcu4_0
 OSAL_TestApp_freertos_$(SOC)_CORELIST = mcu1_0 mcu1_1 mcu2_0 mcu2_1 mcu3_0 mcu3_1 mcu4_0 mcu4_1 c7x_1 c7x_2 c7x_3 c7x_4
endif

ifeq ($(SOC),$(filter $(SOC), am62x))
 OSAL_Baremetal_TestApp_$(SOC)_CORELIST = mcu1_0 m4f_0
 OSAL_TestApp_freertos_$(SOC)_CORELIST = mcu1_0
endif

ifeq ($(SOC),$(filter $(SOC), am62a))
 OSAL_Baremetal_TestApp_$(SOC)_CORELIST = mcu1_0
 OSAL_TestApp_freertos_$(SOC)_CORELIST = mcu1_0
endif

ifeq ($(SOC),$(filter $(SOC), j722s))
 OSAL_Baremetal_TestApp_$(SOC)_CORELIST =
 OSAL_TestApp_freertos_$(SOC)_CORELIST =
endif

export OSAL_Baremetal_TestApp_$(SOC)_CORELIST
export OSAL_freertos_TestApp_$(SOC)_CORELIST

export osal_LIB_LIST
export libosal_LIB_LIST
export osal_EXAMPLE_LIST

export libosal_EXAMPLE_LIST = $(osal_EXAMPLE_LIST)

osal_component_make_include := 1
endif
