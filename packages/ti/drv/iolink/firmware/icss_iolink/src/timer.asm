	;	/* --COPYRIGHT--,BSD
; * Copyright (c) 2017, Texas Instruments Incorporated
; * All rights reserved.
; *
; * Redistribution and use in source and binary forms, with or without
; * modification, are permitted provided that the following conditions
; * are met:
; *
; * *  Redistributions of source code must retain the above copyright
; *    notice, this list of conditions and the following disclaimer.
; *
; * *  Redistributions in binary form must reproduce the above copyright
; *    notice, this list of conditions and the following disclaimer in the
; *    documentation and/or other materials provided with the distribution.
; *
; * *  Neither the name of Texas Instruments Incorporated nor the names of
; *    its contributors may be used to endorse or promote products derived
; *    from this software without specific prior written permission.
; *
; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
; * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
; * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
; * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
; * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
; * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
; * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
; * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
; * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
; * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
; * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
; * --/COPYRIGHT--*/
	
    ; version 0.1 10/23/2019
    ; version 0.2 11/04/2019
	; version 0.3 11/06/2020

    ; history
    ; 0.1: initial timer, straight forward solution without timing considerations
    ; 0.2: added wait states to ensure timing is always constant, independed if a channel is triggered or not
	; 0.3: added startup handling

    .retain                 ; Required for building .out with assembly file
    .retainrefs             ; Required for building .out with assembly file

    ;ICSS Data RAM  Address
    ;timerconfig    .set 0x00
    ; bit 0: port 0 timer enable
    ; bit 1: port 1 timer enable
    ; ...
	; bit 7: port 7 timer enable

	;wakeupconfig	.set 0x01
	; bit 0: port 0 start wakeup sequence; bit will be cleared after EstablishCom state machine has finished
	; bit 1: port 1 start wakeup sequence; bit will be cleared after EstablishCom state machine has finished
	; ...

	;wakeupstatus 	.set 0x02
	; bit 0: port 0 will be set if EstablishCom finished and got a response
	; bit 1: port 1 will be set if EstablishCom finished and got a response
	; ...

	;todo: add retry path and send event after statemachine cmpleted



    ;channel0cycle  .set 0x04       ; 16 bit compare value in 100 us steps
    ;channel0count  .set 0x06       ; 16 bit counter value
    ;channel1cycle  .set 0x08
    ;channel1count  .set 0x0A
    ;channel2cycle  .set 0x0C
    ;channel2count  .set 0x0E
    ;channel3cycle  .set 0x10
    ;channel3count  .set 0x12
    ;channel4cycle  .set 0x14
    ;channel4count  .set 0x16
    ;channel5cycle  .set 0x18
    ;channel5count  .set 0x1A
    ;channel6cycle  .set 0x1C
    ;channel6count  .set 0x1E
    ;channel7cycle  .set 0x20
    ;channel7count  .set 0x22

    ;channel0wakecounter, .set 0x24
    ;channel0wakestate, .set 0x26
    ;channel1wakecounter, .set 0x28
    ;channel1wakestate, .set 0x2a

    .asg "0x0", PRU_ICSS_IEP_TMR_GLB_CFG
    .asg "0x4", PRU_ICSS_IEP_TMR_GLB_STS
    .asg "0x40", PRU_ICSS_IEP_TMR_CMP_CFG
    .asg "0x44", PRU_ICSS_IEP_TMR_CMP_STS
    .asg "0x48", PRU_ICSS_IEP_TMR_CMP0

    .asg "0x10", PRU_ICSS_INTC_GER
    .asg "0x24", PRU_ICSS_INTC_SICR
    .asg "0x28", PRU_ICSS_INTC_EISR
    .asg "0x34", PRU_ICSS_INTC_HIEISR
    .asg "0x280", PRU_ICSS_INTC_SECR0
    .asg "0xD80", PRU_ICSS_INTC_SITR0

    .asg "R0", gp_r0    ;general purpose register
    .asg "R1", gp_r1    ;general purpose register
    .asg "R2", gp_r2    ;general purpose register
    .asg "R3", gp_r3    ;general purpose register

    .asg "R4.b0", timer_ch      ; currently active timer channel
    .asg "R4.b1", timer_addr    ; address of current timer channel
    .asg "R4.b2", enable_addr   ; address of the enable bit of the io-link channel
	.asg "R4.b3", timer_100us	; counter for generating 100 µs timing for cycle counter
    .asg "R5.w0", timer_cycle   ; cycle time of active channel
    .asg "R5.w2", timer_counter ; counter of active channel

	.asg "R6.w0", wakeup_counter ; counter for tDMT
	.asg "R6.b2", wakeup_state	 ; state machine for wakeup; lower 4 bit code state; upper 4 bit code retry counter
	.asg "R7.b0", wakeup_ch		 ; currently active channel
	.asg "R7.b1", wakeup_addr	 ; address of counter and state of active channel
	.asg "R7.b2", io_link_addr	 ; address of io-link channel

	.asg "0x0", state_idle
	.asg "0x1", state_wurq
	.asg "0x2", state_com_request_com3
	.asg "0x3", state_com_request_com2
	.asg "0x4", state_com_request_com1
	.asg "0x5", state_retry

    ;macro used to precisely wait for (P1 > 1) cycles
nopx    .macro P1
    loop endloop?, P1 - 1
    NOP
endloop?:
    .endm

    .global main
    .sect   ".text"

main:
    zero &R0, 120 ;clear R0 to R29
	sbco &gp_r0, c24, 0, 68 ; clear data mem


	; clear standby_init bit to enable access to ocp master port
	lbco &R0, c4, 4, 4
    clr  r0.t4
    sbco &R0, c4, 4, 4

    ;configure iep timer
    ;reset iep count increment to 5 and disable it
    ldi gp_r0, 0x550
    sbco &gp_r0, c26, PRU_ICSS_IEP_TMR_GLB_CFG, 4       ; store content of r0 to c26 (IEP global timer cfg)
    ldi gp_r0, 0x1
    sbco &gp_r0, c26, PRU_ICSS_IEP_TMR_GLB_STS, 4       ; set glb_sts cnt_ovf to 1 to clear counter overflow
    ldi gp_r0, 0x3
    sbco &gp_r0, c26, PRU_ICSS_IEP_TMR_CMP_CFG, 4       ; enable event on compare 0, and enable counter reset
    ldi gp_r0, 0xff
    sbco &gp_r0, c26, PRU_ICSS_IEP_TMR_CMP_STS, 4       ; clear compare status
	ldi gp_r0, 0x2710
	;lsl gp_r0, gp_r0, 4									; load 10 000 to register r0
	sbco &gp_r0, c26, PRU_ICSS_IEP_TMR_CMP0, 4			; write 10 000 to cmp register 0
    ldi gp_r0, 0x551
    sbco &gp_r0, c26, PRU_ICSS_IEP_TMR_GLB_CFG, 4       ; start timer

    ; intc event system 7 to host 0
    ; map system event 2 to channel 0
    ; PRU_ICSS_INTC_CMR1 = 0x0;
    ; PRU_ICSS_INTC_HMR0  = 0x0

    ; PRU_ICSS_INTC_EISR = 7
    ; PRU_ICSS_INTC_HIEISR = 0
    ; PRU_ICSS_INTC_GER = 1

    ldi gp_r0, 0x80
    ldi gp_r1, PRU_ICSS_INTC_SITR0
    sbco &gp_r0, c0, gp_r1, 4                           ; set to edge detect
    ldi gp_r0, 7
    sbco &gp_r0, c0, PRU_ICSS_INTC_EISR, 4              ; enable event 7
    ldi gp_r0, 0
    sbco &gp_r0, c0, PRU_ICSS_INTC_HIEISR, 4            ; enable host channel 0
    ldi gp_r0, 1
    sbco &gp_r0, c0, PRU_ICSS_INTC_GER, 4               ; enable global

	ldi wakeup_addr, 0x24								; prepare state address to channel 0
	ldi io_link_addr, 4									; prepare io-link address to channel 0

timer_loop:												; always takes xyz cycles
    wbs r31, 30

    ldi gp_r0, 0x80
    ldi gp_r1, PRU_ICSS_INTC_SECR0
    sbco &gp_r0, c0, gp_r1, 4                           ; clear system event
    ldi gp_r0, 0x00
    sbco &gp_r0, c0, PRU_ICSS_INTC_SICR, 4              ; clear event status
    ldi gp_r0, 0x01
    sbco &gp_r0, c26, PRU_ICSS_IEP_TMR_CMP_STS, 4       ; clear compare status

	add timer_100us, timer_100us, 1						; increment 100 us counter
	lbco &gp_r0, c24, 1, 1								; load config register
	qbbc finish_wakeup_handling, gp_r0, wakeup_ch		; check if enable bit is cleared -> channel handling finished
	lbco &wakeup_counter, c24, wakeup_addr, 4			; channel is enabled, so load state and counters for this channel
	qblt decrement_writeback_finish, wakeup_counter, 0	; if counter is not zero go to decremnt and write back
	and gp_r2, wakeup_state, 0xF						; mask the retry counter
	and wakeup_state, wakeup_state, 0xF0				; remove old state information
	qbeq statehandling_send_wurq, gp_r2, state_idle					; jump to handler for sending wurq
	qbeq statehandling_send_com3, gp_r2, state_wurq					; jump to handler for ComRequestCOM3
	qbeq statehandling_send_com2, gp_r2, state_com_request_com3		; jump to handler for ComRequestCOM2
	qbeq statehandling_send_com1, gp_r2, state_com_request_com2		; jump to handler for ComRequestCOM1
	qbeq statehandling_retry, gp_r2, state_retry						; jump to handler for retry if COM1 failed

statehandling_undef:
	jmp statehandling_undef

statehandling_send_wurq:
	; we come from idle, and need to send WURQ, and set timer
	ldi gp_r0, 5										; load 5 to register to start wakeup request
	sbco &gp_r0, c25, io_link_addr, 1					; set bit 0 in memory of pru0 to start a new transmission
	ldi wakeup_counter, (8-1)							; set timer to tren + tdmt com3: 500 us + (117 bis 160 us) = 617 - 660 us; 7.7 - 8.25 cycles
	or wakeup_state, wakeup_state, state_wurq			; move state machine to next state
	jmp writeback_finish								; jump to end of statemachine and write back state and counter

statehandling_send_com3:
	; after WURQ and timeout if wkaeup_counter
	; send out 0xa202 with COM3 and restart timer
	ldi gp_r0.b0, 2										; prepare tx buffer
	ldi gp_r0.w1, 0xa202								; prepare tx buffer
	add gp_r1, wakeup_ch, 5								; prepare address
	lsl gp_r1, gp_r1, 8									; prepare address
	sbco &gp_r0, c25, gp_r1, 4							; copy data to tx buffer
	ldi gp_r0, 0x0301									; load 1 and COM3 to register to start transmission
	sbco &gp_r0, c25, io_link_addr, 2					; set bit 0 in memory of pru0 to start a new transmission
	ldi wakeup_counter, (10-1)							; set timer to tdmt com2 700 - 960 us; 8.7 - 12 cycles
	or wakeup_state, wakeup_state, state_com_request_com3			; move state machine to next state
	jmp writeback_finish								; jump to end of statemachine and write back state and counter

statehandling_send_com2:
	; check if we have not received 2 bytes --> continue with com2
	; else set bit for this channel in status register and stop state machine
	add gp_r1, wakeup_ch, 2								; prepare rx buffer address
	lsl gp_r1, gp_r1, 7									; rx buffer address
	lbco &gp_r0, c25, gp_r1, 1							; load number of received bytes to gp_r0
	qbeq com_found, gp_r0.b0, 2							; if rx bytes is 2, we have received something --> baud rate found
	ldi gp_r0.b0, 2										; prepare tx buffer
	ldi gp_r0.w1, 0xa202								; prepare tx buffer
	add gp_r1, wakeup_ch, 5								; prepare address
	lsl gp_r1, gp_r1, 8									; prepare address
	sbco &gp_r0, c25, gp_r1, 4							; copy data to tx buffer
	ldi gp_r0, 0x0201									; load 1 and COM2 to register to start transmission
	sbco &gp_r0, c25, io_link_addr, 2					; set bit 0 in memory of pru0 to start a new transmission
	ldi wakeup_counter, (90-1)							; set timer to tdmt com1 5625 - 7708 us; 70 - 96 cycles
	or wakeup_state, wakeup_state, state_com_request_com2			; move state machine to next state
	jmp writeback_finish								; jump to end of statemachine and write back state and counter

statehandling_send_com1:
	; check if we have not received 2 bytes --> continue with com1
	; else set bit for this channel in status register and stop state machine
	add gp_r1, wakeup_ch, 2								; prepare rx buffer address
	lsl gp_r1, gp_r1, 7									; rx buffer address
	lbco &gp_r0, c25, gp_r1, 1							; load number of received bytes to gp_r0
	qbeq com_found, gp_r0.b0, 2							; if rx bytes is 2, we have received something --> baud rate found
	ldi gp_r0.b0, 2										; prepare tx buffer
	ldi gp_r0.w1, 0xa202								; prepare tx buffer
	add gp_r1, wakeup_ch, 5								; prepare address
	lsl gp_r1, gp_r1, 8									; prepare address
	sbco &gp_r0, c25, gp_r1, 4							; copy data to tx buffer
	ldi gp_r0, 0x0101									; load 1 and COM1 to register to start transmission
	sbco &gp_r0, c25, io_link_addr, 2					; set bit 0 in memory of pru0 to start a new transmission
	ldi wakeup_counter, (211-1)							; set timer to 4*(11+3) tbit + tA = 56+25 = 16.9 ms; 211 timer ticks
	or wakeup_state, wakeup_state, state_retry						; move state machine to next state
	jmp writeback_finish								; jump to end of statemachine and write back state and counter

statehandling_retry:
	; check if we have not received 2 bytes --> stop state machine, clear startup bit but not set status bit
	; else set bit for this channel in status register and stop state machine
	add gp_r1, wakeup_ch, 2								; prepare rx buffer address
	lsl gp_r1, gp_r1, 7									; rx buffer address
	lbco &gp_r0, c25, gp_r1, 1							; load number of received bytes to gp_r0
	qbeq com_found, gp_r0.b0, 2							; if rx bytes is 2, we have received something --> baud rate found
	;lbco &gp_r0, c24, 1, 2								; load config register
	;clr gp_r0.b1, gp_r0.b1, wakeup_ch					; clear the channel coresponding status bit
	;clr gp_r0.b0, gp_r0.b0, wakeup_ch					; disable establish com on this channel
	;sbco &gp_r0, c24, 1, 2								; write back to memory
	;ldi wakeup_counter, 0								; set timer to 0
	;ldi wakeup_state, state_idle						; move state machine to idle
	; we havent received a response... increment retry counter; need to check retry counter; wait Tdwu and start over
	add wakeup_state, wakeup_state, 0x10				; increment wakeup retry counter
	qbeq no_response, wakeup_state, 0x30				; after 3 retries we stop
	ldi wakeup_counter, (625-1)							; wait 50 ms for retry
	or wakeup_state, wakeup_state, state_idle			; move state machine to idle
	jmp writeback_finish								; jump to end of statemachine and write back state and counter

no_response:
	lbco &gp_r0, c24, 1, 2								; load config register
	clr gp_r0.b1, gp_r0.b1, wakeup_ch					; clear the channel coresponding status bit
	clr gp_r0.b0, gp_r0.b0, wakeup_ch					; disable establish com on this channel
	sbco &gp_r0, c24, 1, 2								; write back to memory
	ldi wakeup_counter, 0								; set timer to 0
	ldi wakeup_state, state_idle						; move state machine to idle and clear retry counter
	ldi R31.b0, ((1<<5) | 0x1) 							; generate event
	jmp writeback_finish								; jump to end of statemachine and write back state and counter

com_found:
	lbco &gp_r0, c24, 1, 2								; load config register
	set gp_r0.b1, gp_r0.b1, wakeup_ch					; set the channel coresponding bit, signaling that we have found a valid baudrate
	clr gp_r0.b0, gp_r0.b0, wakeup_ch					; disable establish com on this channel
	sbco &gp_r0, c24, 1, 2								; write back to memory
	ldi wakeup_counter, 0								; set timer to 0
	ldi wakeup_state, state_idle						; move state machine to idle and clear retry counter
	ldi R31.b0, ((1<<5) | 0x1) 							; generate event
	jmp writeback_finish								; jump to end of statemachine and write back state and counter

decrement_writeback_finish:
	sub wakeup_counter, wakeup_counter, 1				; decrement counter
writeback_finish:
	sbco &wakeup_counter, c24, wakeup_addr, 4			; write back state and counter to memory
finish_wakeup_handling:
	add wakeup_ch, wakeup_ch, 1							; increment channel to be processed
	add wakeup_addr, wakeup_addr, 4						; increment address to next channel
	add io_link_addr, io_link_addr, 8					; increment to next io-link channel address
	qblt clear_restart_wakeup_ch, wakeup_ch, 7			; we are on the last channel, clear and restart
	qblt cycle_counter_timer_loop, timer_100us, 9		; jump to cycyle counter handling when 10x 100us reached
	jmp timer_loop										; start again

clear_restart_wakeup_ch:
	and wakeup_ch, wakeup_ch, 0							; clear wakeup_ch to 0
	ldi wakeup_addr, 0x24								; prepare state address to channel 0
	ldi io_link_addr, 4									; prepare io-link address to channel 0
	qblt cycle_counter_timer_loop, timer_100us, 9		; jump to cycyle counter handling when 10x 100us reached
	jmp timer_loop										; start again

cycle_counter_timer_loop:
	and timer_100us, timer_100us, 0						; reset counter
    ldi timer_ch, 0                                     ; clear current channel index
    ldi timer_addr, 4                                   ; address of first channel
    ldi enable_addr, 4                                  ; address of first io-link channel
channel_loop:
    ; software timer
    ; r0 contains information which channel is active
    ; timer_ch contains which channel is currently processed
    ; timer_addr contains memeory address of current channel
    lbco &gp_r0, c24, 0, 4                              ; load config register
    qbbc wait_increment_and_restart, gp_r0, timer_ch    ; skip if active register bit is 0

    ; processing active channel
    ; load channel inforation
    lbco &timer_cycle, c24, timer_addr, 4               ; load info of active channel
    add timer_counter, timer_counter, 1                 ; increment timer counter
    qblt trigger_channel, timer_counter, timer_cycle    ; check if cnt value is reached and set trigger;
    nopx 5                                              ; we have not branched, so wait 5 cycle to have same timing as if channel was triggered

writeback_channel:
    sbco &timer_cycle, c24, timer_addr, 4               ; write back counter register
    jmp increment_and_restart

wait_increment_and_restart:
    nopx 13                                             ; if a channel is not counting, wait 13 cycles, as this is time for couting and triggering
increment_and_restart:
    add timer_ch, timer_ch, 1                           ; increment channel index by 1
    add timer_addr, timer_addr, 4                       ; every channel has 32 bit
    add enable_addr, enable_addr, 8                     ; channels are spaced in 8 byte/channel
    qblt timer_loop, timer_ch, 7                        ; if last channel processed restart timer loop
    jmp channel_loop

    halt ; should never reach this

trigger_channel:
    ; ch0 address 0x04 set bit 0 to start
    ; ch1 0x0c
    ; ch2 0x14 ...
    ldi gp_r0, 1                                        ; load 1 to register
    sbco &gp_r0, c25, enable_addr, 1                    ; set bit 0 in memory of pru0 to start a new transmission

reset_writeback:
    and timer_counter, timer_counter, 0                 ; set timer counter to 0
    jmp writeback_channel

    halt    ; should never reach this
