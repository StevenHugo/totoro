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
#include <totoro/sem.h>
#include <totoro/kernel.h>
#include <totoro/err.h>

/* unlock a semaphore */
int sem_signal(sem_t *sem)
{
	if (!sem || !sem->tcb)
		return TTR_ERR_PARAM;

	sem->count++;

	sem->tcb->stat = TASK_READY;
	task_enqueue(sem->tcb);
	ttr_sched();

	return TTR_ERR_OK;
}

/* lock a semaphore */
int sem_wait(sem_t *sem, uint32_t timeout)
{
	// TODO: Atomic
	if (!sem->count) {
		ttr_sleep(timeout);
	}

	sem->count--;

	return TTR_ERR_OK;
}
