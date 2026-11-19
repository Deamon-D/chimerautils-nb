/*	$chimerautils-nb: util.h,v 1.0 2026/11/17 12:57:54 littlefly365 Exp $	*/
/*	$NetBSD: efun.c,v 1.12 2019/10/03 20:29:19 tnn Exp $	*/

/*-
 * Copyright (c) 2006 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Christos Zoulas.
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
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _UTIL_H
#define _UTIL_H

#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <err.h>

/* Definitions for the strpct() functions rounding modes */
#define	STRPCT_RTN		0U	/* Round to nearest */
#define	STRPCT_RAZ		2U	/* Round away from zero */
#define	STRPCT_RTZ		3U	/* Round towards zero */
#define	STRPCT_RTI		6U	/* Round towards +Inf */
#define	STRPCT_RAI		7U	/* Round away from +Inf (to -Inf) */
/* Do not alter those 5 values, the implementation depends upon them */
#define	STRPCT_RQRY		8U	/* Any value not one of the above */

static inline void * __attribute__((unused))
erealloc(void *p, size_t n)
{
	void *q = realloc(p, n);
	if (q == NULL && n != 0)
		err(1, "Cannot re-allocate %zu bytes", n);
	return q;
}

static inline void * __attribute__((unused))
ecalloc(size_t n, size_t s)
{
	void *p = calloc(n, s);
	if (p == NULL && n != 0 && s != 0)
		err(1, "Cannot allocate %zu blocks of size %zu", n, s);
	return p;
}

static inline char * __attribute__((unused))
estrndup(const char *s, size_t len)
{
	char *d = strndup(s, len);
	if (d == NULL)
		err(1, "Cannot copy string");
	return d;
}

static inline void * __attribute__((unused))
emalloc(size_t n)
{
	void *p = malloc(n);
	if (p == NULL && n != 0)
		err(1, "Cannot allocate %zu bytes", n);
	return p;
}

static inline void __attribute__((unused))
ereallocarr(void *p, size_t n, size_t s)
{
	void *q = reallocarray(p, n, s);
	if (q == NULL && n != 0) {
		err(1, "Cannot re-allocate %zu * %zu bytes", n, s);
	}

	p = q;
}

static inline int __attribute__((unused))
easprintf(char ** __restrict ret, const char * __restrict format, ...)
{
	int rv;
	va_list ap;
	va_start(ap, format);
	if ((rv = vasprintf(ret, format, ap)) == -1)
		err(1, "Cannot format string");
	va_end(ap);
	return rv;
}

time_t		parsedate(const char *, const time_t *, const int *);
char 	       *strpct(char *, size_t, uintmax_t, uintmax_t, size_t);
char 	       *strspct(char *, size_t, intmax_t, intmax_t, size_t);
char 	       *strpct_r(char *, size_t, uintmax_t, uintmax_t, size_t, uint32_t);
char 	       *strspct_r(char *,size_t, intmax_t, intmax_t, size_t, uint32_t);
uint32_t	strpct_round(uint32_t);
int		compat_b64_ntop(unsigned char const *, size_t, char *, size_t);

#endif
