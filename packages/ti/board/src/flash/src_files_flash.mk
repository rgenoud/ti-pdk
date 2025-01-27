#
# Copyright (c) 2016 - 2022, Texas Instruments Incorporated
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

# Common source files across all platforms and cores
SRCS_COMMON += board_flash.c

SRCDIR += src/flash src/flash/include
INCDIR += src/flash src/flash/include

ifeq ($(BOARD),$(filter $(BOARD), icev2AM335x am64x_svb am640x_svb))
SRCDIR += src/flash/nor src/flash/nor/device src/flash/nor/gpmc
INCDIR += src/flash/nor src/flash/nor/device src/flash/nor/gpmc

ifeq ($(BOARD),$(filter $(BOARD), am64x_svb am640x_svb))
SRCS_COMMON += nor_gpmc.c
PACKAGE_SRCS_COMMON += src/flash/nor/gpmc/nor_gpmc.c
else
SRCS_COMMON += nor.c nor_gpmc.c
endif
endif

ifeq ($(BOARD),$(filter $(BOARD), evmAM437x am64x_svb am640x_svb))
SRCDIR += src/flash/nand src/flash/nand/device src/flash/nand/gpmc
INCDIR += src/flash/nand src/flash/nand/device src/flash/nand/gpmc

SRCS_COMMON += nand.c nand_gpmc.c
endif


ifeq ($(BOARD),$(filter $(BOARD), evmK2H evmK2K evmK2E evmK2L evmK2G iceK2G evmC6657 evmC6678 evmOMAPL137))
SRCDIR += src/flash/nor src/flash/nor/device src/flash/nor/spi
INCDIR += src/flash/nor src/flash/nor/device src/flash/nor/spi
SRCS_COMMON += nor.c nor_spi.c
PACKAGE_SRCS_COMMON += src/flash/nor/nor.c src/flash/nor/nor.h
PACKAGE_SRCS_COMMON += src/flash/nor/spi/nor_spi.c src/flash/nor/spi/nor_spi.h
PACKAGE_SRCS_COMMON += src/flash/nor/device/n25q128a13esf40f.h
endif

ifeq ($(BOARD),$(filter $(BOARD), evmK2G iceK2G))
SRCDIR += src/flash/nor/qspi
INCDIR += src/flash/nor/qspi
SRCS_COMMON += nor_qspi.c

ifeq ($(CORE),$(filter $(CORE), c66x))
SRCDIR += src/flash/platform_flash
INCDIR += src/flash/platform_flash
SRCS_COMMON += evm66x_i2c.c evm66x_nand.c evmc66x.c evmc66x_elm.c evmc66x_gpio.c evmc66x_gpmc.c evmc66x_i2c_eeprom.c
SRCS_COMMON += evmc66x_nand_gpmc.c evmc66x_nor.c evmc66x_pinmux.c evmc66x_qspi.c evmc66x_qspi_norflash.c evmc66x_spi.c platform.c
endif

endif


ifeq ($(BOARD),$(filter $(BOARD), am65xx_idk am65xx_evm j721e_sim j721e_evm))
SRCDIR += src/flash/nor src/flash/nor/device src/flash/nor/ospi
INCDIR += src/flash/nor src/flash/nor/device src/flash/nor/ospi
SRCS_COMMON += nor_ospi.c nor.c nor_spi_patterns.c nor_spi_phy_tune.c
PACKAGE_SRCS_COMMON += src/flash/nor/nor.c src/flash/nor/nor.h
PACKAGE_SRCS_COMMON += src/flash/nor/ospi/nor_ospi.c src/flash/nor/ospi/nor_ospi.h
PACKAGE_SRCS_COMMON += src/flash/nor/ospi/nor_spi_patterns.c src/flash/nor/ospi/nor_spi_patterns.h
PACKAGE_SRCS_COMMON += src/flash/nor/ospi/nor_spi_phy_tune.c src/flash/nor/ospi/nor_spi_phy_tune.h
PACKAGE_SRCS_COMMON += src/flash/nor/ospi/nor_spi_patterns.bin

ifeq ($(BOARD),$(filter $(BOARD), am64x_svb))
PACKAGE_SRCS_COMMON += src/flash/nor/device/m35xu256.h
else
PACKAGE_SRCS_COMMON += src/flash/nor/device/m35xu512.h
endif
endif

ifeq ($(BOARD),$(filter $(BOARD), j7200_evm am64x_evm am64x_svb))
SRCDIR += src/flash/nor src/flash/nor/device src/flash/nor/ospi
INCDIR += src/flash/nor src/flash/nor/device src/flash/nor/ospi
SRCS_COMMON += nor_xspi.c nor.c nor_spi_patterns.c nor_spi_phy_tune.c
PACKAGE_SRCS_COMMON += src/flash/nor/nor.c src/flash/nor/nor.h
PACKAGE_SRCS_COMMON += src/flash/nor/ospi/nor_xspi.c src/flash/nor/ospi/nor_xspi.h
PACKAGE_SRCS_COMMON += src/flash/nor/device/s28hs512t.h
PACKAGE_SRCS_COMMON += src/flash/nor/ospi/nor_spi_patterns.c src/flash/nor/ospi/nor_spi_patterns.h
PACKAGE_SRCS_COMMON += src/flash/nor/ospi/nor_spi_phy_tune.c src/flash/nor/ospi/nor_spi_phy_tune.h
PACKAGE_SRCS_COMMON += src/flash/nor/ospi/nor_spi_patterns.bin
endif

ifeq ($(BOARD),$(filter $(BOARD), j721e_sim j721e_evm j7200_evm))
SRCDIR += src/flash/nor/hyperflash
INCDIR += src/flash/nor/hyperflash
SRCS_COMMON += nor_hyperflash.c nor_qspi.c
PACKAGE_SRCS_COMMON += src/flash/nor/ospi/nor_qspi.c src/flash/nor/ospi/nor_qspi.h
PACKAGE_SRCS_COMMON += src/flash/nor/hyperflash/nor_hyperflash.c src/flash/nor/hyperflash/nor_hyperflash.h
PACKAGE_SRCS_COMMON += src/flash/nor/device/s71ks512s.h
PACKAGE_SRCS_COMMON += src/flash/nor/device/mt25qu512abb.h
PACKAGE_SRCS_COMMON += src/flash/nor/device/s25fl256s.h
endif

ifeq ($(BOARD),$(filter $(BOARD), j721s2_evm j784s4_evm))
SRCDIR += src/flash/nor src/flash/nor/device src/flash/nor/ospi
SRCDIR += src/flash/nand src/flash/nand/device src/flash/nand/ospi
INCDIR += src/flash/nor src/flash/nor/device src/flash/nor/ospi
INCDIR += src/flash/nand src/flash/nand/device src/flash/nand/ospi
SRCS_COMMON += nor_xspi.c nor.c nor_spi_patterns.c nor_spi_phy_tune.c
SRCS_COMMON += nand.c nand_ospi.c
SRCS_COMMON += nor_qspi.c
PACKAGE_SRCS_COMMON += src/flash/nor/nor.c src/flash/nor/nor.h
PACKAGE_SRCS_COMMON += src/flash/nand/nand.c src/flash/nand/nand.h
PACKAGE_SRCS_COMMON += src/flash/nor/ospi/nor_xspi.c src/flash/nor/ospi/nor_xspi.h
PACKAGE_SRCS_COMMON += src/flash/nand/ospi/nand_ospi.c src/flash/nand/ospi/nand_ospi.h
PACKAGE_SRCS_COMMON += src/flash/nor/ospi/nor_qspi.c src/flash/nor/ospi/nor_qspi.h
PACKAGE_SRCS_COMMON += src/flash/nor/device/s28hs512t.h
PACKAGE_SRCS_COMMON += src/flash/nand/device/w35n01jwtbag.h
PACKAGE_SRCS_COMMON += src/flash/nor/device/mt25qu512abb.h
PACKAGE_SRCS_COMMON += src/flash/nor/ospi/nor_spi_patterns.c src/flash/nor/ospi/nor_spi_patterns.h
PACKAGE_SRCS_COMMON += src/flash/nor/ospi/nor_spi_phy_tune.c src/flash/nor/ospi/nor_spi_phy_tune.h
PACKAGE_SRCS_COMMON += src/flash/nor/ospi/nor_spi_patterns.bin
endif

ifeq ($(BOARD),$(filter $(BOARD), am64x_evm am64x_svb am640x_svb))
SRCS_COMMON += nor_qspi.c
PACKAGE_SRCS_COMMON += src/flash/nor/ospi/nor_qspi.c src/flash/nor/ospi/nor_qspi.h
ifeq ($(BOARD),$(filter $(BOARD), am64x_evm))
PACKAGE_SRCS_COMMON += src/flash/nor/device/s25fl256s.h
else
PACKAGE_SRCS_COMMON += src/flash/nor/device/mt25qu512abb.h
endif
endif

ifeq ($(BOARD),$(filter $(BOARD), tpr12_evm tpr12_qt awr294x_evm))
SRCDIR += src/flash/nor/qspi src/flash/nor
INCDIR += src/flash/nor/qspi src/flash/nor
SRCS_COMMON += nor_qspi_v1.c nor.c
PACKAGE_SRCS_COMMON += src/flash/nor/nor.c src/flash/nor/nor.h
PACKAGE_SRCS_COMMON += src/flash/nor/qspi/nor_qspi_v1.c src/flash/nor/qspi/nor_qspi.h
PACKAGE_SRCS_COMMON += src/flash/nor/device/mx25v1635f.h src/flash/nor/device/gd25b64cw2g.h src/flash/nor/device/gd25b16csag.h
endif

PACKAGE_SRCS_COMMON += src/flash/include/board_flash.h src/flash/board_flash.c src/flash/src_files_flash.mk
