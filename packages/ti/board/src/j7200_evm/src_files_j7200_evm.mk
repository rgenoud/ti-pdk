
SRCDIR += src/j7200_evm src/j7200_evm/include
INCDIR += src/j7200_evm src/j7200_evm/include

# Common source files across all platforms and cores
SRCS_COMMON += board_init.c board_lld_init.c board_clock.c board_mmr.c board_pll.c board_serdes_cfg.c
SRCS_COMMON += board_ddr.c board_info.c board_info_ddr.c board_ethernet_config.c board_i2c_io_exp.c board_utils.c board_control.c board_power.c
SRCS_COMMON += board_pinmux.c J7200_pinmux_data.c J7200_pinmux_data_cpsw.c J7200_pinmux_data_audio.c J7200_pinmux_data_profibus.c
SRCS_COMMON += board_ddrtempmonitor.c board_ddr_prime_dma.c
PACKAGE_SRCS_COMMON = src/j7200_evm/src_files_j7200_evm.mk
