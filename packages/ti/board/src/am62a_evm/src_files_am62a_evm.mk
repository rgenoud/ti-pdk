
SRCDIR += src/am62a_evm src/am62a_evm/include
INCDIR += src/am62a_evm src/am62a_evm/include

# Common source files across all platforms and cores
SRCS_COMMON += board_init.c board_lld_init.c board_utils.c board_mmr.c board_pinmux.c


PACKAGE_SRCS_COMMON = src/am62a_evm/src_files_am62a_evm.mk
