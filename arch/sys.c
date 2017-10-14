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
#include <totoro/drivers/clock.h>

void ttr_pend_sv(void);

void ttr_lowlevel_init(void)
{
	/* Bring up hardware */
	clock_init();

	/* Set Prioritys */
	NVIC_SetPriority(PendSV_IRQn, 0xff);
	NVIC_SetPriority(SysTick_IRQn, 0x00);	
}

void SysTick_Handler(void)
{
	/* Should we do schedule at this time? */
	ttr_sched();
}

void ttr_pend_sv(void)
{
	/* do pend service interrupt */
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

