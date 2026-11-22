/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2021 Deamon-D <daemondev00@gmail.com>
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

#define HELP_OPT	1000
#define VERSION_OPT	1001

extern char *__progname;

static const struct option gnuopts[] = {
	{ "bytes", no_argument, 0, 'b'},
	{ "kibibytes", no_argument, 0, 'k'},
	{ "mebibytes", no_argument, 0, 'm'},
	{ "gibibytes", no_argument, 0, 'g'},
	{ "tebibytes", no_argument, 0, 't'},
	{ "pebibytes", no_argument, 0, 'p'},
	{ "help", no_argument, 0, HELP_OPT},
	{ "version", no_argument, 0, VERSION_OPT},
	{ 0, 0, 0, 0}
};

int human = 0;
uint64_t shift = 10;	/* kibibytes is the default */

int
main(int argc, char *argv[])
{
	int c;
	FILE *fp;
	char buf[128];
	struct sysinfo info;
#define C(x)	((x) * info.mem_unit >> shift)
	unsigned long sreclaimable;
	unsigned long cachedram, availableram;

	while ((c = getopt_long(argc, argv, "bghkm", gnuopts, NULL)) != -1) {
		switch (c) {
		case 'b':
			shift = 0;
			break;
		case 'g':
			shift = 30;
			break;
		case 'h':
			human = 1;
			break;
		case 'k':
			shift = 10;
			break;
		case 'm':
			shift = 20;
			break;
		case 't':
			shift = 40;
			break;
		case 'p':
			shift = 50;
			break;
		case HELP_OPT:
			printf(	"Usage: %s [OPTION]...\n"
				"Show memory and swap information.\n"
				"\n"
				"  -b, --bytes           show output in bytes\n"
				"  -k, --kibibytes       show output in kibibytes\n"
				"  -m, --mebibytes       show output in mebibytes\n"
				"  -g, --gibibytes       show output in gibibytes\n"
				"      --tebibytes       show output in tebibytes\n"
				"      --pebibytes       show output in pebibytes\n"
				"      --help            display this help and exit\n"
				"      --version         output version information and exit\n",
				__progname);
			return EXIT_SUCCESS;
		case VERSION_OPT:
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

	printf("%-10s %10s %10s %10s %10s %10s %10s\n",
		"", "total", "used", "free", "shared", "buff/cache", "available");

	printf("%-10s %10lu %10lu %10lu %10lu %10lu %10lu\n",
		"Mem:", C(info.totalram), C(info.totalram - availableram), C(info.freeram),
		C(info.sharedram), C(info.bufferram + cachedram + sreclaimable), C(availableram));

	printf("%-10s %10lu %10lu %10lu\n",
		"Swap:", C(info.totalswap), C(info.totalswap - info.freeswap), C(info.freeswap));
	return 0;
}
