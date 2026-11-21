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

#include <string.h>
#include <signal.h>
#include <limits.h>
#include <inttypes.h>

#if !defined(__GLIBC__) && !defined(__UCLIBC__) && defined(__linux__)
#define __MUSL__ 1
#endif

/*
 * sys_signame: Array with the signal names of Linux x86
*/
const char *sys_signame[] = {
	{ "ZERO" },
#if defined(__x86_64__) || defined(__i386__)
	{ "HUP" },
	{ "INT" },
	{ "QUIT" },
	{ "ILL" },
	{ "TRAP" },
	{ "ABRT" },
	{ "BUS" },
	{ "FPE" },
	{ "KILL" },
	{ "USR1" },
	{ "SEGV" },
	{ "USR2" },
	{ "PIPE" },
	{ "ALRM" },
	{ "TERM" },
	{ "STKFLT" },
	{ "CHLD" },
	{ "CONT" },
	{ "STOP" },
	{ "TSTP" },
	{ "TTIN" },
	{ "TTOU" },
	{ "URG" },
	{ "XCPU" },
	{ "XFSZ" },
	{ "VTALRM" },
	{ "PROF" },
	{ "WINCH" },
	{ "IO" },
	{ "PWR" },
	{ "SYS" },
 #if defined(SIGRTMIN)
	{ NULL },
	{ NULL },
  #if defined(__MUSL__)	/* In GlibC SIGRTMIN is 34 but in musl is 35 */
	{ NULL },
  #endif
	{ "RT0" },
	{ "RT1" },
	{ "RT2" },
	{ "RT3" },
	{ "RT4" },
	{ "RT5" },
	{ "RT6" },
	{ "RT7" },
	{ "RT8" },
	{ "RT9" },
	{ "RT10" },
	{ "RT11" },
	{ "RT12" },
	{ "RT13" },
	{ "RT14" },
	{ "RT15" },
	{ "RT16" },
	{ "RT17" },
	{ "RT18" },
	{ "RT19" },
	{ "RT20" },
	{ "RT21" },
	{ "RT22" },
	{ "RT23" },
	{ "RT24" },
	{ "RT25" },
	{ "RT26" },
	{ "RT27" },
	{ "RT28" },
	{ "RT29" },
	{ "RT30" },
	{ "RT31" },
	{ "RT32" },
 #endif	/* defined(SIGRTMIN) */
#endif	/* defined(__x86_64__) || defined(__i386__) */
};

/*
 * The size of the array sys_signame - 1
*/

const int sys_nsig = (sizeof(sys_signame) / sizeof(sys_signame[0]));

/*
 * signalnumber: Return the number associated with the signal 'sig'
*/

/* We should be able to emulate the quirks of kill(1) from here */
int
signalnumber(const char *sig)
{
	/* Remove the 'SIG' prefix */
	if (!strncasecmp(sig, "SIG", 3))
		sig += 3;

	/* We start in 1 to skip the first index */
	for (int i = 1; i < sys_nsig; i++) {
		if (sys_signame[i] == NULL)
			continue;
		if (strcasecmp(sig, sys_signame[i]) == 0)
			return i;
	}

	if (strncasecmp(sig, "RTM", 3) == 0) {
		sig += 3;	/* remove RTM */

		int n, e, maxs;
		char *endptr;

		if (strncasecmp(sig, "IN", 2) == 0)
			maxs = 0;
		else if (strncasecmp(sig, "AX", 2) == 0)
			maxs = 1;
		else
			return -1;

		sig+=2;

		/* Check if the signal name is only SIGRTMIN or SIGRTMAX */
		if (*sig == '\0')
			return (maxs) ? SIGRTMAX : SIGRTMIN;

		n = (int)strtoi(sig, &endptr, 10, -INT_MAX, INT_MAX, &e);
		if (e || *endptr != '\0' || endptr == sig) return -1;

		if ((n < 0 && !maxs) || (n > 0 && maxs))
			return -1;

		n += (maxs) ? SIGRTMAX : SIGRTMIN;

		if (n > SIGRTMAX || n < SIGRTMIN)
			return -1;

		return n;
	}

	return -1;
}

/*
 * signalname: Return the name associated with the signal 'nsig'
*/

const char *
signalname(int nsig)
{
	if (nsig <= 0 || nsig > sys_nsig || sys_signame[nsig] == NULL)
		return NULL;

	return sys_signame[nsig];
}

/*
 * signalnext: Return the number of the next valid signal
*/

int
signalnext(int nsig)
{
	if (nsig < 0 || nsig > sys_nsig)
		return -1;

	return (nsig == sys_nsig) ? 0 : ++nsig;
}
