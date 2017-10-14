
    AREA    |.text|, CODE, READONLY

ttr_unprivi \
    PROC
    EXPORT    ttr_unprivi

    adds      r0, r0, #36
    msr       psp, r0
    movs      r2, #0x02
    msr       control, r2
    isb
    bx        lr

    ENDP

ttr_disable_irq \
    PROC
    EXPORT    ttr_disable_irq

    cpsid     i
    bx        lr

    ENDP

ttr_enable_irq \
    PROC
    EXPORT    ttr_enable_irq

    cpsie     i
    bx        lr

    ENDP

PendSV_Handler \
    PROC
    EXPORT  PendSV_Handler
    IMPORT  ttr_running_task
    IMPORT  ttr_next_task

    cpsid     i
    mrs       r0, psp

    ; due to the restriction of cm0,
    ; register list of stmia were
    ; limited to r0-r7, so we do stmia(ldmia) twices.
    subs      r0, #32
    ; save r4-r7 on the stack
    stmia     r0!, {r4 - r7}
    mov       r4, r8
    mov       r5, r9
    mov       r6, r10
    mov       r7, r11
    ; save r8-r11 on the stack
    stmia     r0!, {r4 - r7}
    subs      r0, #32

    ; save current task's sp
    ldr       r2, =ttr_running_task
    ldr       r1, [r2]
    STR       r0, [r1]

    ; update 'ttr_running_task'
    ldr       r1, =ttr_running_task
    ldr       r2, =ttr_next_task
    ldr       r3, [r2]
    STR       r3, [r1]

    ; load next task's sp
    ldr       r2, =ttr_next_task
    ldr       r1, [r2]
    ldr       r0, [r1]

    ldmia     r0!, {r4 - r7}
    mov       r4, r8
    mov       r5, r9
    mov       r6, r10
    mov       r7, r11
    ldmia     r0!, {r4 - r7}

    msr       psp, r0

    ldr       r0, =0xfffffffd
    cpsie     i
    bx        r0

    ALIGN

    ENDP

    END
