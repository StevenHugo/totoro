
    AREA    |.text|, CODE, READONLY

ttr_unprivi \
    PROC
    EXPORT    ttr_unprivi

    add       r0, r0, #36
    msr       psp, r0
    mov       r2, #0x02
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
    subs      r0, #32
    stmia     r0!, {r4 - r11}
    subs      r0, #32

    ; save current task's sp
    ldr       r2, =ttr_running_task
    ldr       r1, [r2]
    str       r0, [r1]

    ; update 'ttr_running_task'
    ldr       r1, =ttr_running_task
    ldr       r2, =ttr_next_task
    ldr       r3, [r2]
    str       r3, [r1]

    ; load next task's sp
    ldr       r2, =ttr_next_task
    ldr       r1, [r2]
    ldr       r0, [r1]

    ldmia     r0!, {r4 - r11}
    msr       psp, r0

    ldr       r0, =0xfffffffd
    cpsie     i
    bx        r0

    ENDP

    END
