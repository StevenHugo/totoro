    .syntax unified
    .arch armv7e-m

    .text
    .thumb
    .extern ttr_running_task
    .extern ttr_next_task
    .global ttr_unprivi
    .global ttr_disable_irq
    .global ttr_enable_irq

ttr_unprivi:
    add       r0, r0, #36
    msr       psp, r0
    mov       r2, #0x02
    msr       control, r2
    isb
    bx        lr

ttr_disable_irq:
    cpsid     i
    bx        lr

ttr_enable_irq:
    cpsie     i
    bx        lr

PendSV_Handler:
    cpsid     i
    mrs       r0, psp
    subs      r0, #32
    stmia     r0!, {r4 - r11}
    subs      r0, #32

    ldr       r2, =ttr_running_task
    ldr       r1, [r2]
    STR       r0, [r1]

    ldr       r1, =ttr_running_task
    ldr       r2, =ttr_next_task
    ldr       r3, [r2]
    str       r3, [r1]

    ldr       r2, =ttr_next_task
    ldr       r1, [r2]
    ldr       r0, [r1]

    ldmia     r0!, {r4 - r11}
    msr       psp, r0

    ldr       r0, =0xfffffffd
    cpsie     i
    bx        r0
