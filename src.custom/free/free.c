/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2026 Deamon-D <daemondev00@gmail.com>
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

#include <sys/sysinfo.h>
#include <unistd.h>
#include <getopt.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <err.h>

#include "config.h"

/*
 * a reimplementation of the free command from procps-ng.
 * I won't implement: --si, --lohi, --line, --committed,
 * --seconds, --count and --wide
*/

extern char *__progname;

#define HUMAN_FLAG	0x01

/* the sizes of the arrays below */
#define RAM_SIZE 6
#define SWAP_SIZE 3

static const struct option gnuopts[] = {
	{ "bytes", no_argument, 0, 'b'},
	{ "kilobytes", no_argument, 0, 'K'},
	{ "megabytes", no_argument, 0, 'M'},
	{ "gigabytes", no_argument, 0, 'G'},
	{ "terabytes", no_argument, 0, 'T'},
	{ "petabytes", no_argument, 0, 'P'},
	{ "kibibytes", no_argument, 0, 'k'},
	{ "mebibytes", no_argument, 0, 'm'},
	{ "gibibytes", no_argument, 0, 'g'},
	{ "tebibytes", no_argument, 0, 't'},
	{ "pebibytes", no_argument, 0, 'p'},
	{ "human-readable", no_argument, 0, 'h'},
	{ "help", no_argument, 0, 'H'},
	{ "version", no_argument, 0, 'V'},
	{ 0, 0, 0, 0}
};

static enum avai_units {
	BYTES = 1UL,
	/* powers of 1024 */
	KIBIBYTES = BYTES * 1024UL,
	MEBIBYTES = KIBIBYTES * 1024UL,
	GIBIBYTES = MEBIBYTES * 1024UL,
	TEBIBYTES = GIBIBYTES * 1024UL,
	PEBIBYTES = TEBIBYTES * 1024UL,

	/* powers of 1000 */
	KILOBYTES = BYTES * 1000UL,
	MEGABYTES = KILOBYTES * 1000UL,
	GIGABYTES = MEGABYTES * 1000UL,
	TERABYTES = GIGABYTES * 1000UL,
	PETABYTES = TERABYTES * 1000UL,
} unit = KIBIBYTES;	/* kibibytes is the default */

uint64_t flags = 0;

static const char *unit_name(void);
static enum avai_units best_unit(unsigned long);

int
main(int argc, char *argv[])
{
	int c;
	FILE *fp;
	char buf[128];
	struct sysinfo info;
	unsigned long sreclaimable;
	unsigned long cachedram, availableram;

	while ((c = getopt_long(argc, argv, "bkmghV", gnuopts, NULL)) != -1) {
		switch (c) {
		case 'b':
			unit = BYTES;
			break;
		case 'K':
			unit = KILOBYTES;
			break;
		case 'M':
			unit = MEGABYTES;
			break;
		case 'G':
			unit = GIGABYTES;
			break;
		case 'T':
			unit = TERABYTES;
			break;
		case 'P':
			unit = PETABYTES;
			break;
		case 'k':
			unit = KIBIBYTES;
			break;
		case 'm':
			unit = MEBIBYTES;
			break;
		case 'g':
			unit = GIBIBYTES;
			break;
		case 't':
			unit = TEBIBYTES;
			break;
		case 'p':
			unit = PEBIBYTES;
			break;
		case 'h':
			flags |= HUMAN_FLAG;
			break;
		case 'H':
			printf(	"Usage: %s [OPTION]...\n"
				"Show memory and swap information.\n"
				"\n"
				"  -b, --bytes           show output in bytes\n"
				"      --kilobytes       show output in kilobytes\n"
				"      --megabytes       show output in megabytes\n"
				"      --gigabytes       show output in gigabytes\n"
				"      --terabytes       show output in terabytes\n"
				"      --petabytes       show output in petabytes\n"
				"  -k, --kibibytes       show output in kibibytes\n"
				"  -m, --mebibytes       show output in mebibytes\n"
				"  -g, --gibibytes       show output in gibibytes\n"
				"      --tebibytes       show output in tebibytes\n"
				"      --pebibytes       show output in pebibytes\n"
				"  -h, --human-readable  show human readable output\n"
				"      --help            display this help and exit\n"
				"  -V, --version         output version information and exit\n",
				__progname);
			return EXIT_SUCCESS;
		case 'V':
			printf(	"%s (" PROJECT_NAME ") " PROJECT_VERSION "\n"
				"Copyright (C) 2026 Deamon-D <daemondev00@gmail.com>\n"
				"SPDX-License-Identifier: BSD-2-Clause\n",
				__progname);
			return EXIT_SUCCESS;
		default:
			break;
		}
	}

	if (sysinfo(&info) != 0)
		err(1, "sysinfo");

	if (!(fp = fopen("/proc/meminfo", "r")))
		err(1, "/proc/meminfo");

	/* we need to get some values from /proc to match free output */
	while (fgets(buf, sizeof(buf), fp)) {
		if (!strncmp(buf, "MemAvailable:", 13)) {
			sscanf(buf + 13, "%ld", &availableram);
			availableram = (availableram * 1024) / info.mem_unit;
		} else if (!strncmp(buf, "Cached:", 7)) {
			sscanf(buf + 7, "%ld", &cachedram);
			cachedram = (cachedram * 1024) / info.mem_unit;
		} else if (!strncmp(buf, "SReclaimable:", 13)) {
			sscanf(buf + 13, "%ld", &sreclaimable);
			sreclaimable = (sreclaimable * 1024) / info.mem_unit;
		}
	}

	fclose(fp);

	/* create these arrays to print its values in a loop */
	unsigned long ram[RAM_SIZE] = {
		info.totalram * info.mem_unit,
		(info.totalram - availableram) * info.mem_unit,
		info.freeram * info.mem_unit,
		info.sharedram * info.mem_unit,
		(info.bufferram + cachedram + sreclaimable) * info.mem_unit,
		availableram * info.mem_unit
	};

	unsigned long swap[SWAP_SIZE] = {
		info.totalswap * info.mem_unit,
		(info.totalswap - info.freeswap) * info.mem_unit, 
		info.freeswap * info.mem_unit
	};

	printf("%-10s %10s %10s %10s %10s %10s %10s\n%-10s",
		"", "total", "used", "free", "shared", "buff/cache", "available", "Mem:");

	for (int i = 0; i < RAM_SIZE; i++) {
		unit = best_unit(ram[i]);
		if (flags & HUMAN_FLAG)
			printf(" %8.1f%s", (double)ram[i] / unit, unit_name());
		else 
			printf(" %10lu", ram[i] / unit);
	}

	printf("\n%-10s", "Swap:");
	for (int i = 0; i < SWAP_SIZE; i++) {
		unit = best_unit(swap[i]);
		if (flags & HUMAN_FLAG)
			printf(" %8.1f%s", (double)swap[i] / unit, unit_name());
		else 
			printf(" %10lu", swap[i] / unit);
	}
	putchar('\n');
	return 0;
}

static const char *
unit_name(void)
{
	switch (unit) {
	case BYTES: return "B";
	case KILOBYTES: return "K";
	case MEGABYTES: return "M";
	case GIGABYTES: return "G";
	case TERABYTES: return "T";
	case PETABYTES: return "P";
	case KIBIBYTES: return "Ki";
	case MEBIBYTES: return "Mi";
	case GIBIBYTES: return "Gi";
	case TEBIBYTES: return "Ti";
	case PEBIBYTES: return "Pi";
	}

	/* return 'UK' (unknown) to avoid compiler warnings */
	return "UK";
}

static enum avai_units
best_unit(unsigned long value)
{
	/* use the current unit when --human has not been passed */
	if ((flags & HUMAN_FLAG) == 0)
			return unit;

	if (value < KIBIBYTES)
		return BYTES;
	else if (value < MEBIBYTES)
		return KIBIBYTES;
	else if (value < GIBIBYTES)
		return MEBIBYTES;
	else if (value < TEBIBYTES)
		return GIBIBYTES;
	else if (value < PEBIBYTES)
		return TEBIBYTES;

	return PEBIBYTES;
}
