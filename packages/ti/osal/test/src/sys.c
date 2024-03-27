/***************************************************************************
 * Copyright 1996-2023 Synopsys, Inc.
 *
 * This Synopsys software and all associated documentation are proprietary
 * to Synopsys, Inc. and may only be used pursuant to the terms and
 * conditions of a written license agreement with Synopsys, Inc.
 * All other use, reproduction, modification, or distribution of the
 * Synopsys software or the associated documentation is strictly prohibited.
 ***************************************************************************/

#include <stdio.h>

#if defined(USE_SEMIHOSTING_INPUT) || defined(USE_SEMIHOSTING_OUTPUT)
#define USE_SEMIHOSTING
#endif

#ifndef USE_SEMIHOSTING_EXIT
__attribute__((noinline)) static void end_of_test_reached()
{
   while(1);
}
#endif

#ifndef USE_SEMIHOSTING

#include "uart.h"

struct __FILE
{
  int handle;
};

FILE __stdout;
FILE __stdin;
FILE __stderr;
 
int fputc(int ch, FILE *f) 
{
  while( IsTxFifoFull() ) { }
  WriteFifoChar((unsigned char)ch);

  //use carriage returns
  if('\n' == ch)
  {
    fputc('\r', f);
  }
  return ch;
}

int fgetc(FILE *f)
{
  while( IsRxFifoEmpty() ) {}
  return fputc(ReadFifoChar(), f);
}

int ferror(FILE *f)
{
  return 0;
}

int __backspace(FILE *f)
{
  return 0;
}

#endif

#ifndef USE_SEMIHOSTING_EXIT
void _sys_exit(int return_code)
{
  end_of_test_reached();  
  while (1);
}
#endif

