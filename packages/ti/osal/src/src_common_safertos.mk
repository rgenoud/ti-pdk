
SRCDIR = . src/safertos src/nonos arch/core
INCDIR = . src/safertos src/nonos arch/core

SRCS_COMMON += HwiP_nonos.c SwiP_nonos.c DebugP_nonos.c RegisterIntr_nonos.c Core_utils.c
SRCS_COMMON += SemaphoreP_SafeRTOS.c TaskP_SafeRTOS.c Utils_SafeRTOS.c

PACKAGE_SRCS_COMMON = makefile HwiP.h SwiP.h MuxIntcP.h osal.h osal_component.mk SemaphoreP.h \
                      TimerP.h RegisterIntr.h EventCombinerP.h CycleprofilerP.h CacheP.h DebugP.h soc/osal_soc.h soc/$(SOC) \
                      src/nonos/Nonos_config.h src/nonos/HwiP_nonos.c src/nonos/SwiP_nonos.c src/nonos/CycleprofilerP_nonos.c \
                      src/nonos/RegisterIntr_nonos.c src/safertos/SemaphoreP_SafeRTOS.c src/safertos/TaskP_SafeRTOS.c src/safertos/Utils_SafeRTOS.c src/nonos/DebugP_nonos.c \
                      src/src_common_safertos.mk src/Module.xs \
                      arch/core/Core_utils.c docs/OSAL_SoftwareManifest.html docs/ReleaseNotes_OSAL.pdf \
                      build \
                      config_mk.bld osalver.h osalver.h.xdt package.bld package.xdc package.xs Settings.xdc.xdt

ifeq ($(SOC),$(filter $(SOC), am65xx j721e))
  SRCDIR      += soc/$(SOC)
  SRCS_COMMON += TimerP_default.c
endif

ifeq ($(SOC),$(filter $(SOC), j7200))
  SRCDIR      += soc/$(SOC)
  SRCS_COMMON += TimerP_default_$(ISA).c
endif

ifeq ($(SOC),$(filter $(SOC), tpr12 awr294x))
  SRCDIR      += soc/$(SOC)
  SRCS_COMMON += TimerP_default.c CycleprofilerP_nonos.c
endif

ifeq ($(CORE),$(filter $(CORE), mcu1_0 mcu2_0 mcu2_1 mcu1_1 mcu3_0 mcu3_1))
  SRCDIR += arch/core/r5
  SRCS_COMMON += CacheP_nonos.c Arch_util.c
  SRCS_ASM_COMMON += TimestampProvider_asm.asm
  PACKAGE_SRCS_COMMON += arch/core/r5
endif

ifeq ($(CORE),$(filter $(CORE), c66x c66xdsp_1 c66xdsp_2 c674x))
  SRCDIR += arch/core/c6x
  SRCS_COMMON += CacheP_nonos.c Arch_util.c EventCombinerP_nonos.c
  PACKAGE_SRCS_COMMON += arch/core/c6x src/nonos/EventCombinerP_nonos.c
endif
