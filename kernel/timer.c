/*
 * TOTORO, the most effective scheduler designed for free.
 * Copyright (C) 2017, 2018  Gimcuan Hui
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
#include <stdlib.h>
#include <totoro/kernel.h>
#include <totoro/timer.h>

/* softirq thread */
DECLARE_TCB(ktimer);

static uint8_t init, awake;
static struct timer *timer_list, *t;

static void ttr_ktimer_thread(void)
{
	do {
		/* traverse timer list */
		for (t = timer_list; t != NULL; t = t->next) {
			if (!t->en)
				continue;
			if (t->v)
				t->v--;
			if (t->v == 0)
				t->timer_handler(NULL);
		}
		/* no task to do */
		awake = 0;
		ttr_sleep(~0);
		awake = 1;
	} while (!0);
}

int timer_init(void)
{
	if (init)
		return 0;
	init = 1;
	timer_list = NULL;

	return ttr_create_thread(&ktimer_tcb,
                          TASK_HIGHEST_PRIORITY,
                          TASK_DEFAULT_STACK_SIZE,
                          &ktimer_stack[0],
                          ttr_ktimer_thread);
}

struct timer *timer_alloc(void)
{
	struct timer *t;

	if (!init)
		return NULL;
	t = (struct timer *)malloc(sizeof(struct timer));
	if (!t)
		return NULL;
	/* Put the new timer into timer list */
	t->next = timer_list;
	timer_list = t;
	return t;
}

void timer_start(struct timer *t, uint32_t ms, void (*handler)(void *arg))
{
	if (!init)
		return;
	t->en = 1;
	t->v = ms;
	t->timer_handler = handler;

	/* if it's needed to wakeup timer thread */
	if (!awake)
		ttr_post(&ktimer_tcb);
}

void timer_stop(struct timer *t)
{
	if (!init)
		return;
	t->en = 0;	
}

void timer_wakeup(void)
{
	if (!init)
		return;
	if (!awake)
		ttr_post(&ktimer_tcb);
}
