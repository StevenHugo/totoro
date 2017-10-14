/*
 * TOTORO, the most effective scheduler designed for free.
 * Copyright (C) 2017  SAKS XU
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
 * Contact Author, SAKS XU <saks@opensir.org>
 */

#include <totoro/kernel.h>
#include <totoro/sem.h>
#include <totoro/drivers/gpio.h>

/* thread A for testing semaphore */
DECLARE_TCB(threada);
/* thread B for testing semaphore */
DECLARE_TCB(threadb);

/* semaphore is on the way! */
static sem_t semaphore;

static void ttr_threada(void);
static void ttr_threadb(void);

void ttr_test_sem(void)
{
	ttr_init();

	/* create threada */
	ttr_create_thread(&threada_tcb,
                          1,
                          TASK_DEFAULT_STACK_SIZE,
                          &threada_stack[0],
                          ttr_threada);
	/* cretae threadb */
	ttr_create_thread(&threadb_tcb,
                          2,
                          TASK_DEFAULT_STACK_SIZE,
                          &threadb_stack[0],
                          ttr_threadb);

	ttr_start();
}

/* note: thread A has higher priority than thread B */
static void ttr_threada(void)
{
	/* Initialize thread context */
	SEM_INIT(semaphore, &threada_tcb);

	while(1) {
		gpio_rst(0);
		/* try to sleep forever */
		if (sem_wait(&semaphore, ~0) != TTR_ERR_OK)
			break;
	}
}

static void ttr_threadb(void)
{
	while(1) {
		gpio_set(0);
		/*
		 * for simplicity , we assume the fact that
		 * 'semaphore' has been initialized already.
		 * (thread A must be created at first.)
		 */
		if (sem_signal(&semaphore) != TTR_ERR_OK)
			break;
	}
}

int main(void)
{
	/* Start testing semaphore */
	ttr_test_sem();

	/* should never be reached */
	return 0;
}
