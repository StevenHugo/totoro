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
 * Contact Author, gimcuan <gimcuan@gmail.com>
 */
#ifndef _CONFIG_H
# define _CONFIG_H

/* er... ugly, maybe we need some config scripts */
#ifdef STM32F0
# include <board/soc/stm32f0_clock.h>
# include <board/soc/stm32f0_gpio.h>
#elif defined(NRF52)
# include <board/soc/nrf52_clock.h>
# include <board/soc/nrf52_gpio.h>
#elif defined(STM32F1)
# include <board/soc/stm32f1_clock.h>
# include <board/soc/stm32f1_gpio.h>
#else
# error "No soc specicify in config.h"
#endif

#endif
