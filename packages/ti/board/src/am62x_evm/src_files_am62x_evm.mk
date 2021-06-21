
SRCDIR += src/am62x_evm src/am62x_evm/include
INCDIR += src/am62x_evm src/am62x_evm/include

# Common source files across all platforms and cores
SRCS_COMMON += board_init.c board_lld_init.c board_utils.c board_mmr.c board_pinmux.c

PACKAGE_SRCS_COMMON = src/am62x_evm/src_files_am62x_evm.mk
