/*
 * TOTORO, the most effective scheduler designed for free.
 * Copyright (C) 2017  gimcuan
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
 * Contact Author, gimcuan <saks@opensir.org>
 */
#include <arch/port.h>
#include <board/config.h>
#include <totoro/err.h>

ttr_err_t clock_init(void)
{
	lowlevel_clock_init();

	/* Set the system tick granularity of totoro */
	SysTick_Config(SYS_CLK_PRES);

	/* always be ok! */
	return TTR_ERR_OK;
}
