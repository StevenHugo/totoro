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
#ifndef _TASK_Q_H
#define _TASK_Q_H

#include <totoro/err.h>

/* task states */
#define TASK_SUSPENDED  ( 0 )
#define TASK_READY      ( 1 )
#define TASK_RUNNING    ( 2 )

/* task's proritys */
#define TASK_HIGHEST_PRIORITY  ( 0 )
#define TASK_LOWEST_PRIORITY   (255)
#define TASK_DEFAULT_PRIORITY  ( 1 )

/* definition for Task(Thread) Control Block */
struct ttr_tcb
{
	/* stack pointer */
	volatile void *sp;
	/* current state of the thread */
	uint8_t stat;
	/* priority of the thread */
	uint8_t prior;
	/* thread's stack size */
	uint32_t stack_size;
	/* thread's stack */
	void *stack;
	/* thread function */
	void (*ttr_thread)(void);
};

struct tasklist {
	struct ttr_tcb *tcb;
	struct tasklist *next;
};

extern void task_initqueue(void);
extern ttr_err_t task_enqueue(struct ttr_tcb *tcb);
extern struct ttr_tcb *task_next(void);

#endif
