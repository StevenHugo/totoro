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
 * Written by, gimcuan <gimcuan@gmail.com>
 */
#include <arch/port.h>
#include <board/config.h>
#include <totoro/err.h>

void gpio_rst(int id)
{
	lowlevel_gpio_rst(id);	
}

void gpio_set(int id)
{
	lowlevel_gpio_set(id);
}
