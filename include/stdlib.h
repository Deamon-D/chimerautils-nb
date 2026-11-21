/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2023 Daniel Kolesa
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

#ifndef STDLIB_H
#define STDLIB_H

#include_next <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "config-compat.h"

#ifndef HAVE_REALLOCF
void *reallocf(void *ptr, size_t size);
#endif

#ifndef HAVE_STRTONUM
long long strtonum(const char *, long long, long long, const char **);
#endif

#ifndef HAVE_STRTOQ
#define strtoq strtoll
#endif

static inline void setprogname(const char *name __attribute__((unused))) { }

static inline const char *getprogname(void) {
    extern char *__progname;
    return __progname;
}

/* Values for humanize_number(3)'s flags parameter. */
#define HN_DECIMAL              0x01
#define HN_NOSPACE              0x02
#define HN_B                    0x04
#define HN_DIVISOR_1000         0x08
#define HN_IEC_PREFIXES         0x10

/* Values for humanize_number(3)'s scale parameter. */
#define HN_GETSCALE             0x10
#define HN_AUTOSCALE            0x20

int	humanize_number(char *, size_t, int64_t, const char *, int, int);
char	*cgetcap(char *, const char *, int);
int	 cgetclose(void);
int	 cgetent(char **, const char * const *, const char *);
int	 cgetmatch(const char *, const char *);
int	 cgetnum(char *, const char *, long *);
int	 cgetset(const char *);
int	 cgetstr(char *, const char *, char **);
int	 cgetustr(char *, const char *, char **);
void	 csetexpandtc(int);
int	mergesort(void *, size_t, size_t, int (*)(const void *, const void *));
int	heapsort(void *, size_t, size_t, int (*)(const void *, const void *));
char	*getbsize(int *, long *);


#endif
