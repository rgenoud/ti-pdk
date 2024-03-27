/***************************************************************************
 * Copyright 1996-2023 Synopsys, Inc.
 *
 * This Synopsys software and all associated documentation are proprietary
 * to Synopsys, Inc. and may only be used pursuant to the terms and
 * conditions of a written license agreement with Synopsys, Inc.
 * All other use, reproduction, modification, or distribution of the
 * Synopsys software or the associated documentation is strictly prohibited.
 ***************************************************************************/

#ifndef __UART_H__
#define __UART_H__

#include <stdbool.h>
#include <stdint.h>


// Definitions
#define UARTS_ADDRESS_BASE      0x40000000

// FR REGISTER
#define		UART_PL011_TX_FIFO_FULL				0x0020
#define		UART_PL011_RX_FIFO_EMPTY			0x0010

// Register Structure
struct UART_PL011_Regs {
    volatile unsigned int *	UARTDR;
    volatile unsigned int *	UARTFR;
    volatile unsigned int *	UARTIBRD;
    volatile unsigned int *     UARTFBRD;
    volatile unsigned int *	UARTLCR_H;
    volatile unsigned int *	UARTCR;
    volatile unsigned int *	UARTIFLS;
};

void Setup_UART_Reg_Address();
void Setup_UART();
bool IsRxFifoEmpty();
bool IsTxFifoFull();
void WriteFifoChar(unsigned char ch);
char ReadFifoChar();



#endif
