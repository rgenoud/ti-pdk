ifeq ($(SOC),$(filter $(SOC), am65xx j7200 j721e j721s2 am77x tpr12 awr294x am263x am64x am62x))
  PACKAGE_SRCS_COMMON += r5/src/startup
  ifeq ($(ARCH),armv7r)
    SRCDIR += r5/src/startup
    INCDIR += r5/src/startup
    INCDIR += r5
    SRCS_ASM_COMMON += boot.asm r5_startup.asm resetvecs.asm
    SRCS_COMMON += startup.c
  endif

endif
