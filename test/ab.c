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
#include <totoro/drivers/gpio.h>

/* test thread 1 */
DECLARE_TCB(test1);
/* test thread 2 */
DECLARE_TCB(test2);

static void ttr_test1_thread(void);
static void ttr_test2_thread(void);

void ttr_test_sched(void)
{
	ttr_init();

	/* create thread1 */
	ttr_create_thread(&test1_tcb,
                          TASK_DEFAULT_PRIORITY,
                          TASK_DEFAULT_STACK_SIZE,
                          &test1_stack[0],
                          ttr_test1_thread);
	/* cretae thread2 */
	ttr_create_thread(&test2_tcb,
                          TASK_DEFAULT_PRIORITY,
                          TASK_DEFAULT_STACK_SIZE,
                          &test2_stack[0],
                          ttr_test2_thread);

	ttr_start();
}

static void ttr_test1_thread(void)
{
	while(1) {
		gpio_rst(0);
	}
}

static void ttr_test2_thread(void)
{
	while(1) {
		gpio_set(0);
	}
}

int main(void)
{
	/* Start testing tasks switch */
	ttr_test_sched();

	/* NEVER be reached */
	return 0;
}
