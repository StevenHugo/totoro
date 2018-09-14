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
#include <totoro/kernel.h>
#include <totoro/timer.h>
#include <totoro/event.h>

extern void ttr_pend_sv(void);

/* idle thread */
DECLARE_TCB(idle);

struct ttr_tcb *ttr_next_task;
struct ttr_tcb *ttr_running_task;

static void ttr_idle_thread(void);

static void ttr_idle_thread(void)
{
	while(1) {
	}
}

void ttr_init(void)
{
	task_init();
	event_init();

	ttr_disable_irq();

	ttr_lowlevel_init();
}

/* erect totoro */
void ttr_start(void)
{
	timer_init();

	ttr_create_thread(&idle_tcb,
                          TASK_LOWEST_PRIORITY,
                          TASK_DEFAULT_STACK_SIZE,
                          &idle_stack[0],
                          ttr_idle_thread);
	
	ttr_running_task = &idle_tcb;
	ttr_next_task = NULL;

	ttr_unprivi(ttr_running_task->sp);

	ttr_enable_irq();

	ttr_running_task->stat = TASK_RUNNING;
	ttr_running_task->ttr_thread();
}

/* totoro scheduler */
void ttr_sched(void)
{
	ttr_next_task = task_next();

	if (ttr_next_task)
		ttr_next_task->stat = TASK_RUNNING;
	else
		ttr_next_task = &idle_tcb;

	ttr_pend_sv();
}

/* sleep for 't' seconds (has not implement yet :<)
 so, just sleeping, no wakeup on timeout */
void ttr_sleep(size_t t)
{
	ttr_running_task->stat = TASK_SUSPENDED;

	task_enqueue(ttr_running_task);

	ttr_sched();
}

/* wakeup the 'tcb' thread */
void ttr_post(struct ttr_tcb *tcb)
{
	tcb->stat = TASK_READY;

	task_enqueue(tcb);

	ttr_sched();
}

/* creator of all threads */
int ttr_create_thread(struct ttr_tcb *tcb,
                       uint8_t prior,
                       size_t stack_size,
                       void *stack_top,
                       void (*ttr_thread)(void))
{
	uint8_t *p_stacku8;
	uint32_t aligned_size, *p_stack;

	/* security checks */
	if (!tcb || !stack_top || !ttr_thread)
		return -1;

	if (stack_size < STACK_MIN_SIZE)
		return -2;

	/* stack initialize */
	aligned_size = STACK_ALIGN(stack_size);
	p_stacku8 = stack_top;
	p_stacku8 += aligned_size;
	p_stack = (uint32_t *)p_stacku8;

	/* init registers of thread context */
	TTR_CONTEXT_INIT(ttr_thread, ttr_idle_thread);

	/* thread params initialize */
	tcb->sp = p_stack;
	tcb->stat = TASK_READY;
	tcb->prior = prior;
	tcb->stack_size = aligned_size;
	tcb->stack = p_stack;
	tcb->ttr_thread = ttr_thread;

	/*
	 * TCB (thread control block) enqueue
	 * we make sure that idle thread living in the system forever,
	 * so, never push it into the task queue.
	 */
	if (&idle_tcb != tcb)
		return task_enqueue(tcb);
	else
		return TTR_ERR_OK;
}
