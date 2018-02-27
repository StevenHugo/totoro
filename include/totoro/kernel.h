/*
 * TOTORO, the most effective scheduler designed for free.
 * Copyright (C) 2017  Gimcuan Hui
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Contact Author, Gimcuan Hui <gimcuan@gmail.com>
 */
#ifndef _KERNEL_H
#define _KERNEL_H

#include <stdint.h>
#include <stddef.h>

#include <arch/port.h>

#include <totoro/taskq.h>

/* system ticks in millsecond */
#define TTR_SYS_TICK 10

#define TASK_DEFAULT_STACK_SIZE 512

#define DECLARE_TCB(thread) \
	static uint8_t thread##_stack[TASK_DEFAULT_STACK_SIZE]; \
	static struct ttr_tcb thread##_tcb;

#define TTR_CONTEXT_INIT(thread, idle) \
	/* \
	 * Exception frame \
	 * this frame was stacked automatically. \
	 */ \
	*--p_stack = (uint32_t)0x01000000;        /* xPSR */ \
	*--p_stack = (uint32_t)thread;            /* pc   */ \
	*--p_stack = (uint32_t)idle;              /* lr   */ \
	*--p_stack = (uint32_t)0x00000012;        /* r12  */ \
	*--p_stack = (uint32_t)0x00000003;        /* r3   */ \
	*--p_stack = (uint32_t)0x00000002;        /* r2   */ \
	*--p_stack = (uint32_t)0x00000001;        /* r1   */ \
	*--p_stack = (uint32_t)0x00000000;        /* r0   */ \
	/* stacked by us */ \
	*--p_stack = (uint32_t)0x00000011;        /* r11  */ \
	*--p_stack = (uint32_t)0x00000010;        /* r10  */ \
	*--p_stack = (uint32_t)0x00000009;        /* r9   */ \
	*--p_stack = (uint32_t)0x00000008;        /* r8   */ \
	*--p_stack = (uint32_t)0x00000007;        /* r7   */ \
	*--p_stack = (uint32_t)0x00000006;        /* r6   */ \
	*--p_stack = (uint32_t)0x00000005;        /* r5   */ \
	*--p_stack = (uint32_t)0x00000004;        /* r4   */

#define STACK_ALIGN(stack_size) (stack_size & ~(STACK_ALIGN_SIZE - 1))

#define STACK_MIN_SIZE 128

extern void ttr_init(void);
extern void ttr_start(void);
extern void ttr_create_thread(struct ttr_tcb *tcb,
                       uint8_t prior,
                       size_t stack_size,
                       void *stack_top,
                       void (*ttr_thread)(void));

extern void ttr_sleep(size_t t);
extern void ttr_sched(void);

#endif /* _KERNEL_H */
