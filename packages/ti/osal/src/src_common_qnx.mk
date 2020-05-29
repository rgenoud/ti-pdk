
SRCDIR = . src/qnx
INCDIR = . src/qnx

SRCS_COMMON += HwiP_qnx.c SwiP_qnx.c Utils_qnx.c SemaphoreP_qnx.c RegisterIntr_qnx.c TaskP_qnx.c Queue_qnx.c

ifeq ($(SOC),$(filter $(SOC), am65xx j721e))
  SRCDIR      += soc/$(SOC)
  SRCS_COMMON +=
endif

ifeq ($(CORE),mpu1_0)
  SRCDIR += arch/core/a53
  SRCS_COMMON +=
endif

PACKAGE_SRCS_COMMON = makefile HwiP.h SwiP.h MuxIntcP.h osal.h osal_component.mk SemaphoreP.h CacheP.h \
                      TimerP.h RegisterIntr.h EventCombinerP.h Queue.h TaskP.h EventP.h \
                      arch soc src/qnx src/src_common_qnx.mk \
                      docs/OSAL_SoftwareManifest.html docs/ReleaseNotes_OSAL.pdf \
                      build/makefile_qnx.mk
