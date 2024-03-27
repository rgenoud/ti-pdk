/***************************************************************************
 * Copyright 1996-2023 Synopsys, Inc.
 *
 * This Synopsys software and all associated documentation are proprietary
 * to Synopsys, Inc. and may only be used pursuant to the terms and
 * conditions of a written license agreement with Synopsys, Inc.
 * All other use, reproduction, modification, or distribution of the
 * Synopsys software or the associated documentation is strictly prohibited.
 ***************************************************************************/

#include "uart.h"

#define CORE_ID  0
#define THIS_UART_BASE (UARTS_ADDRESS_BASE + (CORE_ID * 0x1000))


struct UART_PL011_Regs uart;

void Setup_UART_Reg_Address()
{
    uintptr_t this_uart_address = (uintptr_t)THIS_UART_BASE;
    uart.UARTDR =    (unsigned int *) (this_uart_address + 0x0000);
    uart.UARTFR =    (unsigned int *) (this_uart_address + 0x0018);
    uart.UARTIBRD =  (unsigned int *) (this_uart_address + 0x0024);
    uart.UARTFBRD =  (unsigned int *) (this_uart_address + 0x0028);
    uart.UARTLCR_H = (unsigned int *) (this_uart_address + 0x002C);
    uart.UARTCR =    (unsigned int *) (this_uart_address + 0x0030);
}

void Setup_UART()
{
    *(uart.UARTIBRD)  = 0x10;
    *(uart.UARTFBRD)  = 0x10;
    *(uart.UARTLCR_H) = 0x60;
    *(uart.UARTCR)    = 0x301;
}

// Queries whether the Tx Fifo is full or not
bool IsTxFifoFull()
{
    return ((*(uart.UARTFR)) & UART_PL011_TX_FIFO_FULL) == UART_PL011_TX_FIFO_FULL;
}

// Queries whether the Rx Fifo is empty or not
bool IsRxFifoEmpty()
{
    return ((*(uart.UARTFR)) & UART_PL011_RX_FIFO_EMPTY) == UART_PL011_RX_FIFO_EMPTY;
}

// Reads & returns one received character
char ReadFifoChar()
{
    return (*(uart.UARTDR)) & 0xFF;
}

// Writes one character to be transmitted
void WriteFifoChar(unsigned char ch)
{
    *(uart.UARTDR) = ch;
}

