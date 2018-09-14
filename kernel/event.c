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
#include <string.h>
#include <totoro/kernel.h>

#define EVENTS_MAX 3

struct events {
	int events;
	void *tcb;
};

static struct events evts[EVENTS_MAX];

int event_init(void)
{
	memset(evts, 0, sizeof(evts));
	return TTR_ERR_OK;
}

int event_cancel(void *task, int events)
{
	int i;
	char found;

	found = 0;
	for (i = 0; i < EVENTS_MAX; i++) {
		if (task == evts[i].tcb) {
			evts[i].events &= ~events;
			found = 1;
			break;
		}
	}
	if (found) return TTR_ERR_OK;
	else return TTR_ERR_STAT;
}

int event_notify(void *task, int events)
{
	int i;
	char found;

	found = 0;
	for (i = 0; i < EVENTS_MAX; i++) {
		if (task == evts[i].tcb) {
			if (evts[i].events & events)
				evts[i].events = events;
			ttr_post(evts[i].tcb);
			found = 1;
		}
	}
	if (found) return TTR_ERR_OK;
	else return TTR_ERR_STAT;
}

int event_wait(int events_wait, int *events_happens)
{
	int i;
	char found;
	int ret;

	found = 0;
	for (i = 0; i < EVENTS_MAX; i++) {
		if (TTR_TASK_CUR == evts[i].tcb) {
			if (!(evts[i].events & events_wait)) {
				evts[i].events |= events_wait;
				ttr_sleep(~0);
			} else {
				/* event happens already */
				return TTR_ERR_OK;
			}
			found = 1;
		}
	}
	ret = TTR_ERR_MEM;
	if (found) {
		/* ok */
		ret = TTR_ERR_OK;
	} else {
		for (i = 0; i < EVENTS_MAX; i++) {
			if (!evts[i].tcb) {
				evts[i].tcb = TTR_TASK_CUR;
				evts[i].events |= events_wait;
				ttr_sleep(~0);
				ret = TTR_ERR_OK;
				break;
			}
		}
	}
	*events_happens = evts[i].events;
	return ret;
}

