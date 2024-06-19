/*
 *
 * Copyright (c) 2023 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 * license under copyrights and patents it now or hereafter owns or controls to make,
 * have made, use, import, offer to sell and sell ("Utilize") this software subject to the
 * terms herein.  With respect to the foregoing patent license, such license is granted
 * solely to the extent that any such patent is necessary to Utilize the software alone.
 * The patent license shall not apply to any combinations which include this software,
 * other than combinations with devices manufactured by or for TI ("TI Devices").
 * No hardware patent is licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this license
 * (including the above copyright notice and the disclaimer and (if applicable) source
 * code license limitations below) in the documentation and/or other materials provided
 * with the distribution
 *
 * Redistribution and use in binary form, without modification, are permitted provided
 * that the following conditions are met:
 *
 * *       No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 *
 * *       any redistribution and use are licensed by TI for use only with TI Devices.
 *
 * *       Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 *
 * *       any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 *
 * *       any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its suppliers
 *
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * DISCLAIMER.
 *
 * THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
 
/* Linker Settings */
--retain="*(StartUp)"
--retain="*(.init)"
--retain="*(.fini)"
--retain="*(.preinit_array)"
--retain="*(.init_array)"
--retain="*(.fini_array)"
--retain="*(.ctors)"
--retain="*(.dtors)"
--retain="*(.jcr)"
--fill_value=0
--entry_point=Start

_start=_c_int00;
__etext=__data_start;

/* Memory Map */
MEMORY
{
    CORE_BOOT (X)    : origin=0x60000000 length=0x01000
    CORE_EXEC (RWIX) : origin=0x61000000 length=0x100000
    ATCM (RWIX)      : origin=0xee000000 length=0x20000
    BTCM (RWIX)      : origin=0xee100000 length=0x20000
    CTCM (RWIX)      : origin=0xee200000 length=0x20000
}

/* Section Configuration */
SECTIONS
{
    .vectors    : START(__code_start), {
                   *(VECTORS)
                   *(StartUp)
                   *(RESET)
                  } > CORE_BOOT
    .bootCode    : {} palign(8)      > CORE_EXEC
    .startupCode : {} palign(8)      > CORE_EXEC
    .startupData : {} palign(8)      > CORE_EXEC, type = NOINIT
    .init        : {*(.init)}  > CORE_EXEC
    .text        : END(__code_end), {*(.text*)} > CORE_EXEC
    .const   	 : {} palign(8)      > CORE_EXEC
    .fini        : {*(.fini)}  > CORE_EXEC
    .rodata      : {
                   *(.rodata)
                   *(.rodata.*)
                   *(.eh_frame)
                  }           > CORE_EXEC
    .preinit_array : {*(.preinit_array)} > CORE_EXEC
    .init_array : {
                   *(.init_array.*)
                   *(.init_array)
                  }           > CORE_EXEC
    .fini_array : {
                   *(.fini_array.*)
                   *(.fini_array)
                  }           > CORE_EXEC
    .ctors      : {
                   *(.ctors.*)
                   *(.ctors)
                  }           > CORE_EXEC
    .dtors      : {
                   *(.dtors.*)
                   *(.dtors)
                  }           > CORE_EXEC
    .jcr        : {*(.jcr)}   > CORE_EXEC
    .data       : {} palign(128), START(__data_start), END(__data_end) > CORE_EXEC
    .cinit      : {} palign(8), RUN_END(__cinit_end)                > CORE_EXEC
    .pinit      : {} palign(8)                                      > CORE_EXEC
    .bss        : {} align(4), START(__bss_start), END(__bss_end__) > CORE_EXEC
    atcm        : {} > ATCM
    btcm        : {} > BTCM
    ctcm        : {} > CTCM
    .stack      : {. = . + 0x8000;} align(64), RUN_END(__stack) > CORE_EXEC (HIGH)
    .sysmem     : {. = . + 0x20000;} palign(64), RUN_START(__heap_start), RUN_END(__end__) > CORE_EXEC (HIGH)
}
