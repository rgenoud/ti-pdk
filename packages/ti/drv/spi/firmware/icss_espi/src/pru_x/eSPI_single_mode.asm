;
;  TEXAS INSTRUMENTS TEXT FILE LICENSE
; 
;  Copyright (c) 2018 Texas Instruments Incorporated
; 
;  All rights reserved not granted herein.
;  
;  Limited License.  
; 
;  Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive 
;  license under copyrights and patents it now or hereafter owns or controls to 
;  make, have made, use, import, offer to sell and sell ("Utilize") this software 
;  subject to the terms herein.  With respect to the foregoing patent license, 
;  such license is granted  solely to the extent that any such patent is necessary 
;  to Utilize the software alone.  The patent license shall not apply to any 
;  combinations which include this software, other than combinations with devices 
;  manufactured by or for TI ("TI Devices").  No hardware patent is licensed hereunder.
; 
;  Redistributions must preserve existing copyright notices and reproduce this license 
;  (including the above copyright notice and the disclaimer and (if applicable) source 
;  code license limitations below) in the documentation and/or other materials provided 
;  with the distribution.
;  
;  Redistribution and use in binary form, without modification, are permitted provided 
;  that the following conditions are met:
;  No reverse engineering, decompilation, or disassembly of this software is 
;  permitted with respect to any software provided in binary form.
;  Any redistribution and use are licensed by TI for use only with TI Devices.
;  Nothing shall obligate TI to provide you with source code for the software 
;  licensed and provided to you in object code.
;  
;  If software source code is provided to you, modification and redistribution of the 
;  source code are permitted provided that the following conditions are met:
;  Any redistribution and use of the source code, including any resulting derivative 
;  works, are licensed by TI for use only with TI Devices.
;  Any redistribution and use of any object code compiled from the source code
;  and any resulting derivative works, are licensed by TI for use only with TI Devices.
; 
;  Neither the name of Texas Instruments Incorporated nor the names of its suppliers 
;  may be used to endorse or promote products derived from this software without 
;  specific prior written permission.
; 
;  DISCLAIMER.
; 
;  THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR IMPLIED
;  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY 
;  AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI'S
;  LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
;  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
;  GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
;  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
;  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
;  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
; 
; file:   eSPI_single_mode.asm
;
; brief:  This files contains the bitbang states for Single Mode
;
;
;  (C) Copyright 2018, Texas Instruments, Inc
;

;;; INCLUDES ;;;
	.include "icss_defines.h"
	.include "eSPI_bitbang.h"
	.include "eSPI_state_table.h"
	.include "eSPI_pru_x_defines.h"
	.include "icss_ctrl_regs.h"

;;; GLOBAL DEFINES ;;;
	.global READ_STATE_SINGLE
	.global WRITE_STATE_SINGLE
	.global TAR_AND_WAIT_STATE_SINGLE
	.global ERROR_CS_DEASSERT
	.text
	

;-------------------------------------------------------------------
; Subroutine: READ_STATE
; Description: Read a byte and send the data to PRU1
;-------------------------------------------------------------------
	.sect	".text:read_state_single"
READ_STATE_SINGLE:
	LDI r_Data, 0
	READ_DATA_BIT r_Data, 7	
	ADD	r_Count, r_Count, 1
	READ_DATA_BIT r_Data, 6	
	READ_DATA_BIT r_Data, 5
	READ_DATA_BIT r_Data, 4
	READ_DATA_BIT r_Data, 3
	READ_DATA_BIT r_Data, 2
	XIN	BANK0, &r_NextState, 4
	READ_DATA_BIT r_Data, 1
	READ_DATA_BIT r_Data ,0	
	XOUT	BANK0, &r_Data, 8	
	JMP 	r_NextState.w0

;-------------------------------------------------------------------
; Subroutine: WRITE_STATE
; Description: Get a byte from PRU1 and write it out
;-------------------------------------------------------------------
	.sect	".text:write_state_single"
WRITE_STATE_SINGLE:	
	XIN	BANK0, &r_Data, 12 ; if we are in this state, PRU1 has data ready for us. Get it
	ADD	r_Count, r_Count, 1
	WRITE_DATA_BIT	r_Data, 7
	XOUT	BANK0, &r_Data, 8
	WRITE_DATA_BIT	r_Data, 6
	WRITE_DATA_BIT	r_Data, 5
	WRITE_DATA_BIT	r_Data, 4
	WRITE_DATA_BIT	r_Data, 3
	WRITE_DATA_BIT	r_Data, 2
	WRITE_DATA_BIT	r_Data, 1
	WRITE_DATA_BIT	r_Data, 0
	
	;; XOUT	BANK0, &r_Data, 8
	XIN	BANK0, &r_NextState, 4
	JMP	r_NextState.w0

;-------------------------------------------------------------------
; Subroutine: TAR_AND_WAIT_STATE_SINGLE
; Description: Hold for 2 clock cycles, then immeiately respond with WAIT_STATE
;-------------------------------------------------------------------
	.sect	".text:tar_state_single"
TAR_AND_WAIT_STATE_SINGLE:

	;; Second CC
	WAIT_SCL_HIGH_SINGLE
	CHECK_CS_ERROR

	;; Assert EN to enable writes
	CLR	R30, R30, g_EnPin

	;; Write WAIT_STATE
	LDI	r_Data, g_WaitStateResponseCode
	WRITE_DATA_BIT	r_Data, 7
	WRITE_DATA_BIT	r_Data, 6
	WRITE_DATA_BIT	r_Data, 5
	WRITE_DATA_BIT	r_Data, 4
	WRITE_DATA_BIT	r_Data, 3
	WRITE_DATA_BIT	r_Data, 2
	WRITE_DATA_BIT	r_Data, 1
	WRITE_DATA_BIT	r_Data, 0

	;; Jump to next state
	XIN	BANK0, &r_NextState, 4
	JMP_TO_STATE	r_NextState
