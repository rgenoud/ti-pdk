/*
 * Copyright (c) 2017-2018, Texas Instruments Incorporated
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
#include <ti/csl/arch/a53/src/startup/aarch64/boot_defs.h>

//************************** Global symbols ************************************
        .global Entry
        .global _stack
        .global _bss_start
        .global _bss_end
        .global start_boot_diag
        .global ti_csl_arm_gicv3_vectors

.macro GICD_WRITE_LOOP x, y, offset
    str     w1, [x0, #\offset]
    .if \y-\x
    GICD_WRITE_LOOP "(\x+1)", \y, "(\offset+4)"
    .endif
.endm

.macro INIT_GICD_IGROUPR
    ldr     x0, =CSL_GIC_BASE_ADDR
    mvn     w1, wzr
    GICD_WRITE_LOOP 0, 31, 0x0080
.endm

.macro INIT_GICD_IGRPMODR
    ldr     x0, =CSL_GIC_BASE_ADDR
    mov     w1, wzr
    GICD_WRITE_LOOP 0, 31, 0x0D00
.endm


    .section .text.csl_a53_startup, "ax"
    .func Entry
Entry:
    mov     x21, sp   /* Store the SP in x21 */
    mov     x22, x30  /* Store the LR in x22 */
    mrs     x0, currentel
    cmp     x0, #0xC
    bne     2f
    ldr     x0, =ti_csl_arm_v8a_Core_disableCaches
    blr     x0

    /*
     * ----------------------
     * Switch from EL3 to EL2
     * ----------------------
     */
    mov     x0, #0x0531
    msr     scr_el3, x0
    msr     cptr_el3, xzr       /* Disable all trap bits */
    mov     x0, #0x33ff
    msr     cptr_el2, x0        /* Disable all trap bits */
    ldr     x0, =CSL_GIC_BASE_ADDR
    mov     w1, #0x37
    str     w1, [x0]            /* Enable GIC */
    mov     x0, #0xf
    msr     s3_6_c12_c12_5, x0     /* Enable GIC system register interface
                                   and disable IRQ/FIQ bypass */
    isb
    mov     x0, #0x1
    msr     s3_6_c12_c12_7, x0 /* Enable Non-secure group 1 interrupts */
    isb
    INIT_GICD_IGROUPR
    INIT_GICD_IGRPMODR
    ldr     x0, =CSL_GICR_BASE_ADDR
    ldr     x1, =ti_csl_arm_v8a_Core_getGicxAddr
    blr     x1
    ldr     w1, [x0, #0x14]
    mov     w2, #0x2
    bic     w1, w1, w2
    str     w1, [x0, #0x14]     /* wakeup GICR */
1:  ldr     w1, [x0, #0x14]
    and     w1, w1, #0x4
    cbnz    w1, 1b
    ldr     x0, =CSL_GICS_BASE_ADDR
    ldr     x1, =ti_csl_arm_v8a_Core_getGicxAddr
    blr     x1
    mvn     x1, xzr
    str     w1, [x0, #0x80]     /* Configure all SGIs & PPIs as Group 1 ints */
    str     wzr, [x0, #0xD00]   /* Clear GICR_IGRPMODR0 */
    mov     x0, #0xff
    msr     icc_pmr_el1, x0     /* Set priority mask */
    mov     x0, #0x0830
    movk    x0, #0x30c5, lsl #16
    msr     sctlr_el2, x0       /* Initialize sctlr_el2 to reset values */
    mrs     x0, actlr_el3
    orr     x0, x0, #0x2
    msr     actlr_el3, x0       /* Enable CPUECTLR_EL1 access from EL2 */
    /* TODO setup vbar */
    ldr     x0, =CSL_GTC_CNTCR_ADDR
    ldr     w1, [x0]
    orr     w1, w1, #0x1
    str     w1, [x0]            /* Enable system counter */
    isb
    bl      switch_to_el2

2:
    mrs     x0, currentel       /* Read again as currentEL may have changed */
    cmp     x0, #0x8
    bne     3f

    /*
     * ----------------------
     * Switch from EL2 to EL1
     * ----------------------
     */
    mrs     x0, cnthctl_el2
    orr     x0, x0, #0x3        /* Enable EL1/EL0 access to timers */
    msr     cnthctl_el2, x0
    msr     cntvoff_el2, xzr
    mov     x0, #0x33ff
    msr     cptr_el2, x0        /* Disable all trap bits */
    msr     hstr_el2, xzr       /* Disable all coprocessor trap bits */
    mov     x0, #0x0002         /* 64bit EL1, Disable hypervisor call (HVC)
                                   instruction, Set/Way Invalidation Override */
    movk    x0, #0xA000, lsl #16
    msr     hcr_el2, x0
    mov     x0, #0x0838
    movk    x0, #0x30d0, lsl #16
    msr     sctlr_el1, x0
    mrs     x0, actlr_el2
    orr     x0, x0, #2
    msr     actlr_el2, x0
    isb
    mov     x0, #0xF
    msr     icc_sre_el2, x0     /* Enable GIC system register interface
                                   and disable IRQ/FIQ bypass */
    bl      switch_to_el1
3:
    ldr     x0, =gnu_targets_arm_rtsv8A_startupAsm
    br      x0

switch_to_el1:
    mov     x0, #0x3c5
    msr     spsr_el2, x0
    msr     elr_el2, x30
    eret

switch_to_el2:
    mov     x0, #0x3c9
    msr     spsr_el3, x0
    msr     elr_el3, x30
    eret

    .endfunc

/*
 *  ======== Core_getGicxBaseAddr ========
 *
 *  Ptr Core_getGicxAddr(Ptr gicxBaseAddr)
 */
    .section .text.csl_startup, "ax"
    .func ti_csl_arm_v8a_Core_getGicxAddr

ti_csl_arm_v8a_Core_getGicxAddr:
    ldr     x1, =CSL_GICX_OFFSET
    mrs     x2, mpidr_el1
    ubfx    x3, x2, #8, #8      /* x3 = Cluster Id */
    and     x2, x2, #0xFF       /* x2 = Core Id */
    sub     x3, x3, #0
    mrs     x4, s3_1_c11_c0_2   /* Read L2CTLR_EL1 */
    ubfx    x4, x4, #24, #2     /* x4 = Number of cores per cluster */
    lsl     x3, x3, x4          /* x3 = clusterIdx * numCoresPerCluster */
    add     x2, x2, x3
    madd    x0, x1, x2, x0
    ret
    .endfunc


    .section .text.csl_a53_startup, "ax"
    .func gnu_targets_arm_rtsv8A_startupAsm
gnu_targets_arm_rtsv8A_startupAsm:
    /*
     * ---------------------
     * Boot code starts here
     * ---------------------
     */

    mov     x0, #0x3C0
    msr     daif, x0            /* Mask all interrupts */

#if defined(__ARM_FP)
    mov     x0, #(3 << 20)
    msr     cpacr_el1, x0       /* Enable FP/SIMD at EL1 */
#endif

    isb                         /* Synchronize processor context */

    /*
     * ------------------------
     * Initialize stack pointer
     * ------------------------
     */
    msr     spsel, #1           /* Use SP_ELx for ELx */
    ldr     x0, =__TI_STACK_BASE
    ldr     x1, =__TI_STACK_SIZE
    add     x0, x0, x1
    and     x0, x0, #(~0xf)     /* 16-byte align SP */
    mov     sp, x0              /* Initialize SP */

    /* Setup the vector table for all levels */
    ldr     x0, =ti_csl_arm_gicv3_vectors
    msr     vbar_el1, x0         /* Set vector table base address */

    stp     x21, x22, [sp, #-16]!  /* save SP and LR to stack */

    /* do more initialization in C, go to main() */
    bl      start_boot_diag
    mov     x20, x0
    ldp     x0, x1, [sp], #16  /* Load SP and LR to stack */
    mov     sp, x0
    mov     x30, x1
    ret
    .endfunc

/*
 * ======== Core_disableCaches ========
 */
        .section .text.ti_csl_arm_v8a_Core_disableCaches
        .func ti_csl_arm_v8a_Core_disableCaches

ti_csl_arm_v8a_Core_disableCaches:
    mrs     x0, clidr_el1
    and     w3, w0, #0x07000000     /* Get 2 x Level of Coherence */
    lsr     w3, w3, #23
    cbz     w3, 5f
    mov     w10, #0                 /* w10 = 2 x cache level */
    mov     w8, #1                  /* w8 = Constant 0b1 */
1:
    add     w2, w10, w10, lsr #1    /* Caclulate 3x cache level */
    lsr     w1, w0, w2              /* Extract cache type for this level */
    and     w1, w1, #0x7
    cmp     w1, #2
    blt     4f                      /* No data or unified cache */
    msr     csselr_el1, x10         /* Select this cache level */
    isb                             /* Synchronize change of csselr */
    mrs     x1, ccsidr_el1          /* Read ccsidr */
    and     w2, w1, #7              /* w2 = log2(linelen)-4 */
    add     w2, w2, #4              /* w2 = log2(linelen) */
    ubfx    w4, w1, #3, #10         /* w4 = max way number, right aligned */
    clz     w5, w4                  /* w5 = 32-log2(ways), bit position of
                                       way in dc operand */
    lsl     w9, w4, w5              /* w9 = max way number, aligned to
                                       position in DC operand */
    lsl     w16, w8, w5             /* w16 = amount to decrement way number
                                       per iteration */
2:
    ubfx    w7, w1, #13, #15        /* w7 = max set number, right aligned */
    lsl     w7, w7, w2              /* w7 = max set number, aligned to
                                       position in DC operand */
    lsl     w17, w8, w2             /* w17 = amount to decrement set number
                                           per iteration */
3:
    orr     w11, w10, w9            /* w11 = combine way num & cache ...*/
    orr     w11, w11, w7            /* ... num and set num for DC operand */
    dc      cisw, x11               /* Do data cache clean and invalidate
                                       by set and way */
    subs    w7, w7, w17             /* Decrement set number */
    bge     3b
    subs    x9, x9, x16             /* Decrement way number */
    bge     2b
4:
    add     w10, w10, #2            /* Increment 2 x cache level */
    cmp     w3, w10
    dsb     sy                      /* Ensure completion of previous cache
                                       maintenance operation */
    bgt     1b
5:
    mrs     x0, sctlr_el3            /* read SCTLR_EL3 */
    bic     x0, x0, #0x0004          /* clear C bit */
    msr     sctlr_el3, x0            /* DCache disabled */

    mrs     x0, sctlr_el3            /* read SCTLR_EL3 */
    bic     x0, x0, #0x1000          /* clear I bit */
    msr     sctlr_el3, x0            /* ICache disabled */
    ic      iallu                    /* invalidate all ICache */
    dsb     sy
    isb

    ret
    .endfunc

    .end
