
ifeq ($(SOC),$(filter $(SOC), j7200))
PACKAGE_SRCS_COMMON += cslr_pmmc.h src/ip/pmmc/src_files_pmmc.mk src/ip/pmmc/V0
endif
