; ---------------------------------------------------------------------------
;
; Code common to all CPUs in the MPcore. This is the exception vector table,
; and subsequent code to figure out which core is running the code, and therefore
; where to jump to for each core's own handlers. There are low and high vectors
; defined in the code, and the scatter load file determines which are included
; in the final image. Code to count the number of times each exception vector
; is hit can be included if a macro is defined and set to the base address of
; the memory used to store the counters.
;
        AREA common_lo_exception_handlers, CODE, READONLY
        EXPORT common_entry_point

common_entry_point
        ENTRY

        ;; all cores will take lo vector exceptions through this table
common_lo_vector_table
        LDR pc, =common_lo_reset_exception
        LDR pc, =common_lo_undefined_exception
        LDR pc, =common_lo_svc_exception
        LDR pc, =common_lo_prefetch_exception
        LDR pc, =common_lo_abort_exception
        NOP ;reserved
        LDR pc, =common_lo_irq_exception
        LDR pc, =common_lo_fiq_exception
        LTORG

        ; Common reset handler, uses core ID to offset
        ALIGN
common_lo_reset_exception FUNCTION
        MRC p15, 0, r0, c0, c0, 5 ; Read MPIDR
        AND r0, r0, #0xf ; Mask the cpu id
        MOV r1, #0x00100000
        MUL r0, r0, r1
        MOV r1, #0x00 ; identity of the exception
        ADD pc, r0, #0x61000000
        ENDFUNC

        ; Common UNDEF handler routes execution to core-specific handler - does not return here
        ALIGN
common_lo_undefined_exception FUNCTION
        PUSH {r0-r3}
        MOV r1, #0x04
        LDR pc, =goto_core_vector
        ENDFUNC

        ; Common SVC handler routes execution to core-specific handler - does not return here
        ALIGN
common_lo_svc_exception FUNCTION
        PUSH {r0-r3}
        MOV r1, #0x08
        LDR pc, =goto_core_vector
        ENDFUNC

        ; Common PREFETCH handler routes execution to core-specific handler - does not return here
        ALIGN
common_lo_prefetch_exception FUNCTION
        PUSH {r0-r3}
        MOV r1, #0x0c
        LDR pc, =goto_core_vector
        ENDFUNC

        ; Common ABORT handler routes execution to core-specific handler - does not return here
        ALIGN
common_lo_abort_exception FUNCTION
        PUSH {r0-r3}
        MOV r1, #0x10
        LDR pc, =goto_core_vector
        ENDFUNC

        ; Common IRQ handler routes execution to core-specific handler - does not return here
        ALIGN
common_lo_irq_exception FUNCTION
        PUSH {r0-r3}
        MOV r1, #0x18
        LDR pc, =goto_core_vector
        ENDFUNC

        ; Common FIQ handler routes execution to core-specific handler - does not return here
        ALIGN
common_lo_fiq_exception FUNCTION
        PUSH {r0-r3}
        MOV r1, #0x1c
        LDR pc, =goto_core_vector
        ENDFUNC

        ALIGN
goto_core_vector FUNCTION
        ; on entry r0-r3 are on (current mode) stack
        ; r0-r2 are used here and will be restored before calling core handler
        ; r3 is not modified, and the stacked entry will be changed to core-specific handler address
        MOV r2, lr
        MRC p15, 0, r0, c0, c0, 5 ; Read MPIDR
        AND r0, r0, #0xf ; Mask the cpu id
        MOV lr, r2 ; restore lr for exception return
        MOV r2, #0x00100000
        MUL r0, r0, r2
        ADD r0, r0, #0x61000000
        ADD r0, r0, r1
        STR r0, [sp, #0x0c] ; replace pushed R3 with the address of the core's handler
        POP {r0-r2,pc}
        ENDFUNC


; ---------------------------------------------------------------------------
;
        AREA common_hi_exception_handlers, CODE, READONLY

        ;; all cores will take high vector exceptions through this table
common_hi_vector_table
        LDR pc, =common_hi_reset_exception
        LDR pc, =common_hi_undefined_exception
        LDR pc, =common_hi_svc_exception
        LDR pc, =common_hi_prefetch_exception
        LDR pc, =common_hi_abort_exception
        NOP ;reserved
        LDR pc, =common_hi_irq_exception
        LDR pc, =common_hi_fiq_exception
        LTORG

        ; Common reset handler, uses core ID to offset
        ALIGN
common_hi_reset_exception FUNCTION
        MRC p15, 0, r0, c0, c0, 5 ; Read MPIDR
        AND r0, r0, #0xf ; Mask the cpu id
        MOV r1, #0x00100000
        MUL r0, r0, r1
        MOV r1, #0x20 ; identity of the exception
        ADD pc, r0, #0x61000000
        ENDFUNC

        ; Common UNDEF handler routes execution to core-specific handler - does not return here
        ALIGN
common_hi_undefined_exception FUNCTION
        PUSH {r0-r3}
        MOV r1, #0x24
        LDR pc, =goto_core_vector
        ENDFUNC

        ; Common SVC handler routes execution to core-specific handler - does not return here
        ALIGN
common_hi_svc_exception FUNCTION
        PUSH {r0-r3}
        MOV r1, #0x28
        LDR pc, =goto_core_vector
        ENDFUNC

        ; Common PREFETCH handler routes execution to core-specific handler - does not return here
        ALIGN
common_hi_prefetch_exception FUNCTION
        PUSH {r0-r3}
        MOV r1, #0x2c
        LDR pc, =goto_core_vector
        ENDFUNC

        ; Common ABORT handler routes execution to core-specific handler - does not return here
        ALIGN
common_hi_abort_exception FUNCTION
        PUSH {r0-r3}
        MOV r1, #0x30
        LDR pc, =goto_core_vector
        ENDFUNC

        ; Common IRQ handler routes execution to core-specific handler - does not return here
        ALIGN
common_hi_irq_exception FUNCTION
        PUSH {r0-r3}
        MOV r1, #0x38
        LDR pc, =goto_core_vector
        ENDFUNC

        ; Common FIQ handler routes execution to core-specific handler - does not return here
        ALIGN
common_hi_fiq_exception FUNCTION
        PUSH {r0-r3}
        MOV r1, #0x3c
        LDR pc, =goto_core_vector
        ENDFUNC


; ---------------------------------------------------------------------------
;
; Exception handling which is separately located for each CPU. From this
; point there is no overlap - the CPUs all have completely independent code
; and data sections.
;
        AREA core_exception_handlers, CODE, READONLY

core_vector_table
        LDR pc, =core_reset_exception
        LDR pc, =core_undefined_exception
        LDR pc, =core_svc_exception
        LDR pc, =core_prefetch_exception
        LDR pc, =core_abort_exception
        NOP ;reserved
        LDR pc, =core_irq_exception
        LDR pc, =core_fiq_exception
        LTORG

        IMPORT |Image$$ARM_LIB_STACK$$ZI$$Limit|
        IMPORT |Image$$NON_USR_MODE_STACKS$$ZI$$Base|
        IMPORT |Image$$NON_USR_MODE_STACKS$$ZI$$Limit|
        IMPORT __main

        ALIGN
core_reset_exception FUNCTION




        ; ARMv8-R cores are in EL2 (hypervisor mode) after reset, and we need
        ; to first descend to EL1 (supervisor mode) before the traditional SP
        ; setting code can be run.
        LDR r6, =stack_init
        MSR ELR_hyp, r6
        MRS r5, cpsr
        BIC r5, r5, #0x1F
        ORR r5, r5, #0x0013
        MSR SPSR_hyp, r5
        ERET

stack_init
        ; Divide the non-USR mode stack area between the 5 non-USR modes
        ; ABT,UND get 1/8 each. SVC,FIQ,IRQ get 1/4 each.
        LDR r3, =|Image$$NON_USR_MODE_STACKS$$ZI$$Limit|
        LDR r2, =|Image$$NON_USR_MODE_STACKS$$ZI$$Base|
        SUB r2, r3, r2
        LSR r1, r2, #2
        AND r1, r1, #~0x0f
        LSR r2, r2, #3
        AND r2, r2, #~0x0f

        ; Setup the stack for supervisor mode (entered from reset)
        MOV SP, r3

        ; Go to FIQ mode and set stack (below the previous one)
        MRS r0, cpsr
        AND r0, r0, #~0x001F
        ORR r0, r0, #0x0011
        MSR cpsr_c, r0
        SUB r3, r3, r1
        MOV SP, r3

        ; Go to IRQ mode and set stack (below the previous one)
        MRS r0, cpsr
        AND r0, r0, #~0x001F
        ORR r0, r0, #0x0012
        MSR cpsr_c, r0
        SUB r3, r3, r1
        MOV SP, r3

        ; Go to ABORT mode and set stack (below the previous one)
        MRS r0, cpsr
        AND r0, r0, #~0x001F
        ORR r0, r0, #0x0017
        MSR cpsr_c, r0
        SUB r3, r3, r1
        MOV SP, r3

        ; Go to UNDEF mode and set stack (below the previous one)
        MRS r0, cpsr
        AND r0, r0, #~0x001F
        ORR r0, r0, #0x001b
        MSR cpsr_c, r0
        SUB r3, r3, r2
        MOV SP, r3

        ; Go to SYSTEM mode and set stack to the top of the reserved area
        ; This is also the stack for user mode, and is the
        MRS r0, cpsr
        AND r0, r0, #~0x001F
        ORR r0, r0, #0x001F
        MSR cpsr_c, r0
        LDR r3, =|Image$$ARM_LIB_STACK$$ZI$$Limit|
        MOV SP, r3

        ; Modify to Switch to supervisor mode instead of User mode to make writing testing easier for IP_testing
        MRS r0, cpsr
        AND r0, r0, #~0x001F
        ORR r0, r0, #0x0013
        MSR cpsr_c, r0

        ; Jump to main
        LDR r0, =__main
        BX r0
        LTORG
        ENDFUNC


        ALIGN
core_undefined_exception FUNCTION
        ; on entry all registers are unchanged from when the exception was taken



        PUSH {r0-r3,lr}
        LDR r0, =user_exception_handlers ; get address of registered UNDEF handler
        LDR r1, [r0,#0x04]
        CMP r1, #0
        BXNE r1 ; call UNDEF handler (if registered)
        POP {r0-r3,lr}
        SUBS pc, lr, #4
        ENDFUNC


        ALIGN
core_svc_exception
        ; on entry all registers are unchanged from when the exception was taken



        PUSH {r4-r7, r12, lr} ; Store registers
        MOV r1, sp ; Set pointer to parameters
        MRS r0, spsr ; Get spsr
        STMFD sp!, {r0, r3} ; Store spsr onto stack and another
                                            ; register to maintain 8-byte-aligned stack
        TST r0, #0x20 ; Occurred in Thumb state?
        LDRNEH r0, [lr,#-2] ; Yes: Load halfword and...
        BICNE r0, r0, #0xFF00 ; ...extract comment field
        LDREQ r0, [lr,#-4] ; No: Load word and...
        BICEQ r0, r0, #0xFF000000 ; ...extract comment field

        ; r0 now contains SVC number
        ; r1 now contains pointer to stacked registers

        LDR r3, =user_exception_handlers ; get address of registered SVC handler
        LDR r3, [r3,#0x08]
        CMP r3, #0
        BLXNE r3 ; call SVC handler (if registered)
        LDMFD sp!, {r1, r3} ; Recover spsr from stack
        MSR SPSR_cxsf, r1 ; Restore spsr
        POP {r4-r7, r12, pc}^ ; Restore registers and return


        ALIGN
core_prefetch_exception FUNCTION
        ; on entry all registers are unchanged from when the exception was taken



        PUSH {r0-r3,lr}
        LDR r0, =user_exception_handlers ; get address of registered UNDEF handler
        LDR r1, [r0,#0x0c]
        CMP r1, #0
        BXNE r1 ; call PREFETCH handler (if registered)
        POP {r0-r3,lr}
        SUBS pc, lr, #4
        ENDFUNC


        ALIGN
core_abort_exception FUNCTION
        ; on entry all registers are unchanged from when the exception was taken



        PUSH {r0-r3,lr}
        LDR r0, =user_exception_handlers ; get address of registered UNDEF handler
        LDR r1, [r0,#0x10]
        CMP r1, #0
        BXNE r1 ; call ABORT handler (if registered)
        POP {r0-r3,lr}
        SUBS pc, lr, #8
        ENDFUNC


        ALIGN
core_irq_exception FUNCTION
        ; on entry all registers are unchanged from when the exception was taken



        PUSH {r0-r3,lr}
        LDR r0, =user_exception_handlers ; get address of registered UNDEF handler
        LDR r1, [r0,#0x18]
        CMP r1, #0
        BXNE r1 ; call FIQ handler (if registered)
        POP {r0-r3,lr}
        SUBS pc, lr, #4
        ENDFUNC


        ALIGN
core_fiq_exception FUNCTION
        ; on entry all registers are unchanged from when the exception was taken



        PUSH {r0-r3,lr}
        LDR r0, =user_exception_handlers ; get address of registered UNDEF handler
        LDR r1, [r0,#0x1c]
        CMP r1, #0
        BXNE r1 ; call FIQ handler (if registered)
        POP {r0-r3,lr}
        SUBS pc, lr, #4
        ENDFUNC


; ---------------------------------------------------------------------------
;
; A data sections where the application program can write exception handlers,
; low and high exceptions are handled separately.

        AREA boot_data_section, DATA, READWRITE
        ALIGN
user_exception_handlers
        SPACE 32


        END
