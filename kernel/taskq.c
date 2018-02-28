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
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <totoro/taskq.h>

#define MALLOC_TASK_NODE(node, _tcb) \
	((node = (struct tasklist *)malloc(sizeof(struct tasklist))), \
	(!!node ? (node->tcb = _tcb, TTR_ERR_OK) : TTR_ERR_MEM))

#define DELETE_TASK_NODE(node) \
	if (node) { \
		free(node); \
		node->tcb = NULL; \
		node = NULL; \
	}

#define HIGH_PRIO(a,b) (a->tcb->prior > b->tcb->prior ? b : a)

/* queue for ready tasks */
static struct tasklist *ready_q;

/* queue for suspended tasks */
static struct tasklist *suspe_q;

/* node pointer for allocating memory */
static struct tasklist *node_ptr;

static struct tasklist *migrate(struct ttr_tcb *tcb,
                        struct tasklist **src,
                        struct tasklist **dst);

static void insert(struct tasklist *node,
                   struct tasklist **list);


void task_initqueue(void)
{
	ready_q = suspe_q = node_ptr = NULL;

	return;
}

/* migrate the node from 'src' list to 'dst' list */
static struct tasklist *migrate(struct ttr_tcb *tcb,
                        struct tasklist **src,
                        struct tasklist **dst)

{
	struct tasklist **tlpp, *mg = NULL;

	if (!tcb || !dst || !src)
		return NULL;

	/* does 'tcb' exist in 'dst' list ? */
	tlpp = dst;
	for (; *tlpp != NULL; tlpp = &((*tlpp)->next)) {
		if ((*tlpp)->tcb == tcb)
			/* found! just exit. */
			return NULL;
	}

	/* does 'tcb' exist in 'src' list ? */
	tlpp = src;
	for (; *tlpp != NULL; tlpp = &(*tlpp)->next) {
		if ((*tlpp)->tcb == tcb) {
			/* found! should be migrated. */
			mg = *tlpp;
			*tlpp = (*tlpp)->next;
			break;
		}
	}

	if (!!mg)
		insert(mg, dst);

	return mg;
}

static void insert(struct tasklist *node,
                   struct tasklist **list)
{
	struct tasklist **tlpp, *tlp;

	if (!list || !node)
		return;

	tlpp = list;
	tlp = *tlpp;

	/*
	 * find a proper tcb by priority.
	 * we do insert later.
	 */
	for (; *tlpp != NULL; tlpp = &(*tlpp)->next) {
		if (tlp->tcb->prior > node->tcb->prior)
			break;
		tlp = *tlpp;
	}

	/*
	 * deal with these cases:
	 * 1. empty queue case. (*tlpp = null)
	 * 2. 'prior' was lower than all of tcbs in the list. (*tlpp = null)
	 * 3. found a proper prior (in break case). (*tlpp = ?_tcb)
	 */
	tlp = *tlpp;
	*tlpp = node;
	node->next = tlp;
}

ttr_err_t task_enqueue(struct ttr_tcb *tcb)
{
	struct tasklist **tlpp;

	if (tcb->stat == TASK_SUSPENDED) {
		/* 'tcb' should be migrated to 'suspe_q' list */
		if (!!migrate(tcb, &ready_q, &suspe_q))
			return TTR_ERR_OK;

		tlpp = &suspe_q;
	} else if (tcb->stat == TASK_READY) {
		/* 'tcb' should be migrated to 'ready_q' list */
		if (!!migrate(tcb, &suspe_q, &ready_q))
			return TTR_ERR_OK;

		tlpp = &ready_q;
	} else {
		return TTR_ERR_STAT;
	}

	/* A new node should be created */
	if (TTR_ERR_OK != MALLOC_TASK_NODE(node_ptr, tcb))
		return TTR_ERR_MEM;

	insert(node_ptr, tlpp);

	return 	TTR_ERR_OK;
}

struct ttr_tcb *task_next(void)
{
	struct tasklist **tlpp;
	struct tasklist *low, *high;

	/* check out the most priority advanced task which gets ready */
	low = high = NULL;
	tlpp = &ready_q;
	for (; *tlpp != NULL; tlpp = &((*tlpp)->next)) {
		if ((*tlpp)->tcb->stat != TASK_READY)
			continue;

		low = *tlpp;
		high = (low && high) ? HIGH_PRIO(low, high) : low;
	}

	return !high ? NULL : high->tcb;
}
