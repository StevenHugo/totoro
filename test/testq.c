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
#include "testq.h"

#include <totoro/kernel.h>
#include <totoro/taskq.h>


static struct ttr_tcb node0, node1, node2, node3, node4, node5;

/*
* Our Goal(Enqueue):
* [*]: struct tasklist *
* [*] -> [1|*] -> [2|*] -> [3|*] -> [4|*] -> [5|null]
* Test sequences:
* 1.
*/
void ttr_test_taskqueue(void)
{
	task_enqueue(&node1);
	task_enqueue(&node2);
	task_enqueue(&node3);
	task_enqueue(&node4);
	task_enqueue(&node5);
	task_dequeue(&node0);
}
