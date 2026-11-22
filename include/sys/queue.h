/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2026 littlefly365
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef SYS_QUEUE_H
#define SYS_QUEUE_H

/*
 * LIST
*/

#define	LIST_HEAD(name, type)						\
struct name {								\
	struct type *lh_first;	/* first element */			\
}

#define	LIST_HEAD_INITIALIZER(head)					\
	{ NULL }

#define	LIST_ENTRY(type)						\
struct {								\
	struct type *le_next;	/* next element */			\
	struct type **le_prev;	/* address of previous next element */	\
}

#define	LIST_FIRST(head)		((head)->lh_first)
#define	LIST_END(head)			NULL
#define	LIST_EMPTY(head)		((head)->lh_first == LIST_END(head))
#define	LIST_NEXT(elm, field)		((elm)->field.le_next)

#define	LIST_FOREACH(var, head, field)					\
	for ((var) = ((head)->lh_first);				\
	    (var) != LIST_END(head);					\
	    (var) = ((var)->field.le_next))

#define	LIST_INIT(head) do {						\
	(head)->lh_first = LIST_END(head);				\
} while (0)


#define	LIST_INSERT_AFTER(listelm, elm, field) do {			\
	if (((elm)->field.le_next = (listelm)->field.le_next) != 	\
	    LIST_END(head))						\
		(listelm)->field.le_next->field.le_prev =		\
		    &(elm)->field.le_next;				\
	(listelm)->field.le_next = (elm);				\
	(elm)->field.le_prev = &(listelm)->field.le_next;		\
} while (0)

#define	LIST_INSERT_HEAD(head, elm, field) do {				\
	if (((elm)->field.le_next = (head)->lh_first) != LIST_END(head))\
		(head)->lh_first->field.le_prev = &(elm)->field.le_next;\
	(head)->lh_first = (elm);					\
	(elm)->field.le_prev = &(head)->lh_first;			\
} while (0)

#define	LIST_REMOVE(elm, field) do {					\
	if ((elm)->field.le_next != NULL)				\
		(elm)->field.le_next->field.le_prev = 			\
		    (elm)->field.le_prev;				\
	*(elm)->field.le_prev = (elm)->field.le_next;			\
} while (0)

/*
 * TAILQ
*/


#define	TAILQ_FIRST(head)		((head)->tqh_first)

#define	TAILQ_EMPTY(head)		(TAILQ_FIRST(head) == NULL)

#define	_TAILQ_HEAD(name, type, qual)					\
struct name {								\
	qual type *tqh_first;		/* first element */		\
	qual type *qual *tqh_last;	/* addr of last next element */	\
}
#define TAILQ_HEAD(name, type)	_TAILQ_HEAD(name, struct type,)

#define	_TAILQ_ENTRY(type, qual)					\
struct {								\
	qual type *tqe_next;		/* next element */		\
	qual type *qual *tqe_prev;	/* address of previous next element */\
}
#define TAILQ_ENTRY(type)	_TAILQ_ENTRY(struct type,)

#define	TAILQ_INIT(head) do {						\
	(head)->tqh_first = NULL;					\
	(head)->tqh_last = &(head)->tqh_first;				\
} while (0)

#define	TAILQ_FOREACH(var, head, field)					\
	for ((var) = ((head)->tqh_first);				\
	    (var) != NULL;						\
	    (var) = ((var)->field.tqe_next))

#define	TAILQ_INSERT_HEAD(head, elm, field) do {			\
	if (((elm)->field.tqe_next = (head)->tqh_first) != NULL)	\
		(head)->tqh_first->field.tqe_prev =			\
		    &(elm)->field.tqe_next;				\
	else								\
		(head)->tqh_last = &(elm)->field.tqe_next;		\
	(head)->tqh_first = (elm);					\
	(elm)->field.tqe_prev = &(head)->tqh_first;			\
} while (0)

#define	TAILQ_INSERT_TAIL(head, elm, field) do {			\
	(elm)->field.tqe_next = NULL;					\
	(elm)->field.tqe_prev = (head)->tqh_last;			\
	*(head)->tqh_last = (elm);					\
	(head)->tqh_last = &(elm)->field.tqe_next;			\
} while (0)

#define	TAILQ_REMOVE(head, elm, field) do {				\
	if (((elm)->field.tqe_next) != NULL)				\
		(elm)->field.tqe_next->field.tqe_prev = 		\
		    (elm)->field.tqe_prev;				\
	else								\
		(head)->tqh_last = (elm)->field.tqe_prev;		\
	*(elm)->field.tqe_prev = (elm)->field.tqe_next;			\
} while (0)

/*
 * STAILQ
*/


#define	STAILQ_FIRST(head)	((head)->stqh_first)

#define	STAILQ_HEAD(name, type)						\
struct name {								\
	struct type *stqh_first;	/* first element */		\
	struct type **stqh_last;	/* addr of last next element */	\
}

#define	STAILQ_HEAD_INITIALIZER(head)					\
	{ NULL, &(head).stqh_first }

#define	STAILQ_ENTRY(type)						\
struct {								\
	struct type *stqe_next;	/* next element */			\
}

#define	STAILQ_INSERT_TAIL(head, elm, field) do {			\
	(elm)->field.stqe_next = NULL;					\
	*(head)->stqh_last = (elm);					\
	(head)->stqh_last = &(elm)->field.stqe_next;			\
} while (0)

#define	STAILQ_REMOVE_HEAD(head, field) do {				\
	if (((head)->stqh_first = (head)->stqh_first->field.stqe_next) == NULL) \
		(head)->stqh_last = &(head)->stqh_first;			\
} while (0)

/*
 * SIMPLEQ
*/
#define	SIMPLEQ_HEAD(name, type)					\
struct name {								\
	struct type *sqh_first;	/* first element */			\
	struct type **sqh_last;	/* addr of last next element */		\
}

#define	SIMPLEQ_HEAD_INITIALIZER(head)					\
	{ NULL, &(head).sqh_first }

#define	SIMPLEQ_ENTRY(type)						\
struct {								\
	struct type *sqe_next;	/* next element */			\
}

#define	SIMPLEQ_FIRST(head)		((head)->sqh_first)
#define	SIMPLEQ_END(head)		NULL
#define	SIMPLEQ_EMPTY(head)		((head)->sqh_first == SIMPLEQ_END(head))

#define	SIMPLEQ_FOREACH(var, head, field)				\
	for ((var) = ((head)->sqh_first);				\
	    (var) != SIMPLEQ_END(head);					\
	    (var) = ((var)->field.sqe_next))

#define	SIMPLEQ_INSERT_TAIL(head, elm, field) do {			\
	(elm)->field.sqe_next = NULL;					\
	*(head)->sqh_last = (elm);					\
	(head)->sqh_last = &(elm)->field.sqe_next;			\
} while (0)

#define	SIMPLEQ_REMOVE_HEAD(head, field) do {				\
	if (((head)->sqh_first = (head)->sqh_first->field.sqe_next) == NULL) \
		(head)->sqh_last = &(head)->sqh_first;			\
} while (0)
#endif
