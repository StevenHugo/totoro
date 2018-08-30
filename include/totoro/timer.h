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
#ifndef _TIMER_H
#define _TIMER_H

#include <stdint.h>

struct timer {
	struct timer *next;
	uint8_t en;
	uint32_t v;
	void (*timer_handler)(void *arg);
};

extern struct timer *timer_alloc(void);
extern void timer_start(struct timer *t, uint32_t ms, void (*handler)(void *arg));
extern void timer_stop(struct timer *t);
extern int timer_init(void);
extern void timer_wakeup(void);

#endif
