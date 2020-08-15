/******************************************************************************
* Copyright (c) 2020 Texas Instruments Incorporated - http://www.ti.com
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*
* Redistributions in binary form must reproduce the above copyright
* notice, this list of conditions and the following disclaimer in the
* documentation and/or other materials provided with the
* distribution.
*
* Neither the name of Texas Instruments Incorporated nor the names of
* its contributors may be used to endorse or promote products derived
* from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*****************************************************************************/
 
/**
 *  \file   gpio_test_header_config.c
 *
 *  \brief  expansion header config configuration file.
 *
 */

#include <stdio.h>
#include <ti/drv/gpio/GPIO.h>
#include <ti/csl/soc.h>
#include <ti/drv/gpio/soc/GPIO_soc.h>

#include <ti/board/board.h>

/* Port and pin number mask for PRG2 ETHERNET LED's.
   Bits 7-0: Pin number and Bits 15-8: Port number */

#define BOARD_DIAG_SYNC_IN_FE1    		(0x0024U)	/* GPIO0_36 */
#define BOARD_DIAG_MIBSPIA_HOST_INTR	(0x002AU)	/* GPIO0_42 */
#define BOARD_DIAG_SYNC_IN_FE2    		(0x0029U)	/* GPIO0_41 */
#define BOARD_DIAG_MIBSPIB_HOST_INTR	(0x002BU)	/* RCSS GPIO0_43 */


/* GPIO Driver board specific pin configuration structure */
GPIO_v2_PinConfig gpioPinConfigs[] = {
	/* Output pins */
	{BOARD_DIAG_SYNC_IN_FE1, GPIO_CFG_OUTPUT, NULL},
    {BOARD_DIAG_MIBSPIA_HOST_INTR, GPIO_CFG_OUTPUT, NULL},
    {BOARD_DIAG_SYNC_IN_FE2, GPIO_CFG_OUTPUT, NULL},
    {BOARD_DIAG_MIBSPIB_HOST_INTR, GPIO_CFG_OUTPUT, NULL}
};

/* GPIO Driver configuration structure */
GPIO_v2_Config GPIO_v2_config = {
    gpioPinConfigs,
    gpioCallbackFunctions,
};
