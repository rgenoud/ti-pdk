/*
 * Copyright (c) 2004-2018, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
 *  \file bin2c.c
 *
 *  \brief Application to convert Binary to C Array
 *
 */
#include "util.h"
#include <stdint.h>
#include <ctype.h>
#include <string.h>

#define MAX_BUFFER_SIZE (1*KB*KB)

uint8_t buffer[MAX_BUFFER_SIZE];

uint8_t* get_file_name_from_path(uint8_t *fpath) {
	uint32_t i = 0;
	for(i = strlen(fpath) - 1; i >= 0; i--)  
	{
		/* '\' character for windows environment */
		if ((fpath[i] == '/') || (fpath[i] == '\\'))
		{
			return &fpath[i+1];
		}
	}
	return fpath;
}

STATUS bin2c( uint8_t *inName, uint8_t * filename, uint8_t * arrName) {
    STATUS status=E_PASS;
    uint32_t bytes=1, size, i, csize;
    FILE* fin, *fout;
    uint32_t  chunkSize = MAX_BUFFER_SIZE;

    /* Ensure arrName is upper case */
    char ch;
    uint32_t j = 0;
    while (arrName[j]) {
        ch = arrName[j];
        arrName[j] = (uint8_t)toupper(ch);
        j++;
    }

    uint8_t * fn = get_file_name_from_path(filename);
    uint16_t fs = strlen(fn)+1;
    char arrName2[fs];
    memcpy(arrName2,fn,fs);
    char ch2;
    uint32_t k = 0;

    while (arrName2[k] && k<fs) {
        ch2 = arrName2[k];
        if (ch2!='.'){
          arrName2[k] = (uint8_t)toupper(ch2);
        }
        else{
          arrName2[k]='_';
        }
        k++;
    }
    
    /* Print a non-error type message to stdout */
   	fprintf(stdout, "\r\n Converting binary file [%s] to C array \r\n", inName );

    fin = fopen( inName, "rb");
	fout = fopen( filename, "w");
    if(fin==NULL)
    {
		/* Print errors to stderr */
        fprintf(stderr, "\r\n ERROR: Input file [%s] not found \r\n", inName);
        status = E_DEVICE;
        goto error_stop;
    }
    fseek(fin, 0, SEEK_END); /* seek to end of file */
    csize = ftell(fin); /* get current file pointer */
    fseek(fin, 0, SEEK_SET); /* seek back to beginning of file */
    fprintf(fout, "/*\
\n *  Copyright (C) 2021 Texas Instruments Incorporated\
\n *\
\n *  Redistribution and use in source and binary forms, with or without\
\n *  modification, are permitted provided that the following conditions\
\n *  are met:\
\n *\
\n *    Redistributions of source code must retain the above copyright\
\n*    notice, this list of conditions and the following disclaimer.\
\n*\
\n*    Redistributions in binary form must reproduce the above copyright\
\n*    notice, this list of conditions and the following disclaimer in the\
\n*    documentation and/or other materials provided with the\
\n*    distribution.\
\n*\
\n*    Neither the name of Texas Instruments Incorporated nor the names of\
\n*    its contributors may be used to endorse or promote products derived\
\n*    from this software without specific prior written permission.\
\n*\
\n*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS\
\n*  \"AS IS\" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT\
\n*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR\
\n*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT\
\n*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,\
\n*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT\
\n*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,\
\n*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY\
\n*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT\
\n*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE\
\n*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.\
\n*\
\n*/\
\n\
\n/**\
\n*  \\file %s\
\n*\
\n*  \\brief File containing the Binary in a C array.\
\n*\
\n*/\
\n\
\n/* ========================================================================== */\
\n/*                             Include Files                                  */\
\n/* ========================================================================== */\
\n\
\n/* None */\
\n\
\n/* ========================================================================== */\
\n/*                           Macros & Typedefs                                */\
\n/* ========================================================================== */\
\n\
\n#ifndef %s_\
\n#define %s_\
\n\
\n\
\n#define %s_SIZE_IN_BYTES (%dU)\
\n\
\n/* ========================================================================== */\
\n/*                         Structure Declarations                             */\
\n/* ========================================================================== */\
\n\
\n/* None */\
\n\
\n/* ========================================================================== */\
\n/*                          Function Declarations                             */\
\n/* ========================================================================== */\
\n\
\n/* None */\
\n\
\n/* ========================================================================== */\
\n/*                            Global Variables                                */\
\n/* ========================================================================== */\
\n\
\n#define %s {",
get_file_name_from_path(filename),arrName2,arrName2,arrName, csize,arrName);
    size=0;
    csize=0;
    while(bytes) {
      bytes = fread(buffer, 1, chunkSize, fin );
      /* Print a non-error type message to stdout */
      fprintf(stdout, ".");
      for(i=0;i<bytes;i=i+4) {
        if((i%4) == 0)
          fprintf(fout, " ");
        if((i%16)==0)
          fprintf(fout, "\\\n");
        if((i+3)<bytes)
        {fprintf(fout, "    0x%02x", buffer[i+3]);csize++;}
        else
          fprintf(fout, "    0x00");
        if((i+2)<bytes)
        {fprintf(fout, "%02x", buffer[i+2]);csize++;}
        else
          fprintf(fout, "00");
        if((i+1)<bytes)
        {fprintf(fout, "%02x", buffer[i+1]);csize++;}
        else
          fprintf(fout, "00");
        fprintf(fout, "%02xU", buffer[i]);
        csize++;

        if(i<(bytes-4))
          fprintf(fout, ",");
      }
      size +=bytes;
    }
    fprintf(fout, "\\\n} /* %d bytes */", csize );
    fprintf(fout, "\n");
    fprintf(fout, "\n");
    fprintf(fout, "#endif");
    fprintf(fout, "\n");
	  /* Print a non-error type message to stdout */
    fprintf(stdout, " Done. (%d bytes)\r\n", size);

    if(csize!=size)
    {
		/* Print errors to stderr */
        fprintf(stderr, "\n ERROR: Check output file (byte diff %d)", size-csize);
    }
error_stop:
    fclose(fin);
	fclose(fout);

    return status;
}

void main(int argc, char **argv) {

	if(argc!=4) {
		printf("\r\n USAGE: bin2c <binary file name> <c file name> <array name>\n" );
		exit(0);
	}

	bin2c(argv[1], argv[2], argv[3]);
}
