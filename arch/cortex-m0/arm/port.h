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
#ifndef _PORT_H
#define _PORT_H

#if defined(STM32F072xB)
#include "stm32f0xx.h"
#elif defined(STM32F103xB)
#include "stm32f1xx.h"
#endif

#define STACK_ALIGN_SIZE 4

extern void ttr_unprivi(volatile void *sp);
extern void ttr_enable_irq(void);
extern void ttr_disable_irq(void);
extern void ttr_lowlevel_init(void);

#endif /* _PORT_H */
