/**
 *  \file   FATFS_log.c
 *
 *  \brief  This file contains the uart console print specific functions and
 *          macros.
 *
 */

/*
 * Copyright (C) 2019-2022 Texas Instruments Incorporated - http://www.ti.com/
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
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "ti/osal/osal.h"

#include <ti/csl/hw_types.h>
/* RTOS Header files */
#include <ti/drv/uart/UART.h>
#include <ti/drv/uart/UART_stdio.h>
#include <ti/csl/soc.h>
/**********************************************************************
 ************************** Macros ************************************
 **********************************************************************/
#define SOC_CORE_PAD_IO_REGISTERS_BASE                     (0x4a003400U)


/**********************************************************************
 ************************** Internal functions ************************
 **********************************************************************/
/* board init function */
void Board_initUART(void);

/**********************************************************************
 ************************** Global Variables **************************
 **********************************************************************/


/*
 *  ======== ConsoleUtilsInit ========
 */
void ConsoleUtilsInit(void)
{
    /* Call board init functions */
    Board_initUART();

    UART_stdioInit(0);
}

/*
 *  ======== Board_initUART ========
 */
void Board_initUART(void) {
#if !defined(SOC_J721E) && !defined(SOC_J7200) && !defined(SOC_J721S2) && !defined(SOC_J784S4) 
          HW_WR_REG32((SOC_CORE_PAD_IO_REGISTERS_BASE + CSL_CONTROL_CORE_PAD_IO_PAD_UART1_RXD),
            (CSL_CONTROL_CORE_PAD_IO_PAD_UART1_RXD_UART1_RXD_INPUTENABLE_MASK |
                    CSL_CONTROL_CORE_PAD_IO_PAD_UART1_RXD_UART1_RXD_SLEWCONTROL_MASK |
                    CSL_CONTROL_CORE_PAD_IO_PAD_UART1_RXD_UART1_RXD_PULLTYPESELECT_MASK));

        /* TXD */
        HW_WR_REG32((SOC_CORE_PAD_IO_REGISTERS_BASE + CSL_CONTROL_CORE_PAD_IO_PAD_UART1_TXD),
            (CSL_CONTROL_CORE_PAD_IO_PAD_UART1_TXD_UART1_TXD_INPUTENABLE_MASK |
                    CSL_CONTROL_CORE_PAD_IO_PAD_UART1_TXD_UART1_TXD_SLEWCONTROL_MASK |
                    CSL_CONTROL_CORE_PAD_IO_PAD_UART1_TXD_UART1_TXD_PULLTYPESELECT_MASK));

        /* RTSN */
        HW_WR_REG32((SOC_CORE_PAD_IO_REGISTERS_BASE + CSL_CONTROL_CORE_PAD_IO_PAD_UART1_RTSN),
            (CSL_CONTROL_CORE_PAD_IO_PAD_UART1_RTSN_UART1_RTSN_INPUTENABLE_MASK |
                    CSL_CONTROL_CORE_PAD_IO_PAD_UART1_RTSN_UART1_RTSN_PULLTYPESELECT_MASK));

        /* CTSN */
        HW_WR_REG32((SOC_CORE_PAD_IO_REGISTERS_BASE + CSL_CONTROL_CORE_PAD_IO_PAD_UART1_CTSN),
            (CSL_CONTROL_CORE_PAD_IO_PAD_UART1_CTSN_UART1_CTSN_INPUTENABLE_MASK |
                    CSL_CONTROL_CORE_PAD_IO_PAD_UART1_CTSN_UART1_CTSN_PULLTYPESELECT_MASK));
#endif
}


