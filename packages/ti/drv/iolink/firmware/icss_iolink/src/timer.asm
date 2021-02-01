    ; version 0.1 10/23/2019
    ; version 0.2 11/04/2019

    ; history
    ; 0.1: initial timer, straight forward solution without timing considerations
    ; 0.2: added wait states to ensure timing is always constant, independed if a channel is triggered or not

    .retain                 ; Required for building .out with assembly file
    .retainrefs             ; Required for building .out with assembly file

    ;ICSS Data RAM  Address
    ;timerconfig    .set 0x00
    ; bit 0: port 0 timer enable
    ; bit 1: port 1 timer enable
    ; ...

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
    .asg "R5.w0", timer_cycle   ; cycle time of active channel
    .asg "R5.w2", timer_counter ; counter of active channel

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
    ldi gp_r0, 0x186A
    lsl gp_r0, gp_r0, 4                                 ; load 100 000 to register r0
    sbco &gp_r0, c26, PRU_ICSS_IEP_TMR_CMP0, 4          ; write 100 000 to cmp register 0
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

timer_loop:                                             ; always takes 189 cycles
    wbs r31, 30
    ldi gp_r0, 0x80
    ldi gp_r1, PRU_ICSS_INTC_SECR0
    sbco &gp_r0, c0, gp_r1, 4                           ; clear system event
    ldi gp_r0, 0x00
    sbco &gp_r0, c0, PRU_ICSS_INTC_SICR, 4              ; clear event status
    ldi gp_r0, 0x01
    sbco &gp_r0, c26, PRU_ICSS_IEP_TMR_CMP_STS, 4       ; clear compare status

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
