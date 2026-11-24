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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <limits.h>
#include <err.h>

#include "config.h"

/*
 * A simplify version of the nproc command from
 * GNU coreutils for chimerautils-nb
*/

static const struct option gnuopts[] = {
	{ "all", no_argument, 0, 'a'},
	{ "ignore", required_argument, 0, 'i'},
	{ "help", no_argument, 0, 'h'},
	{ "version", no_argument, 0, 'V' },
	{ 0, 0, 0, 0}
};

extern char *__progname;

int
main(int argc, char *argv[])
{
	int c, all = 0;
	int processors, ignore = 0;
	while ((c = getopt_long(argc, argv, "", gnuopts, NULL)) != -1) {
		switch (c) {
		case 'a':
			all = 1;
			break;
		case 'i':
			int e;
			ignore = (int)strtoi(optarg, NULL, 0, 0, INT_MAX, &e);
			if (e)
				errx(EXIT_FAILURE, "invalid number: '%s'", optarg);
			break;
		case 'h':
			printf(	"Usage: %s [OPTION]...\n"
				"Print the number of processors.\n"
				"\n"
				"       --all           Print the number of installed processors\n"
				"       --ignore=N      if possible, exclude N number of processors\n"
				"       --help          display this help and exit\n"
				"       --version       output version information and exit\n",
				__progname);
			return EXIT_SUCCESS;
		case 'V':
			printf(	"%s (" PROJECT_NAME ") " PROJECT_VERSION "\n"
				"Copyright (C) 2026 Deamon-D <daemondev00@gmail.com>\n"
				"SPDX-License-Identifier: BSD-2-Clause\n",
				__progname);
			return EXIT_SUCCESS;
		default:
			fprintf(stderr, "Try '%s --help' for more information.\n",
				__progname);
			return EXIT_FAILURE;
		}
	}

	argc -= optind;
	argv += optind;

	if (argc != 0) {
		fprintf(stderr, "%s: extra operand '%s'\n"
				"Try '%s --help' for more information.\n",
				__progname, *argv, __progname);
		return EXIT_FAILURE;
	}

	switch (all) {
	case 1:
		processors = sysconf(_SC_NPROCESSORS_CONF);
		break;
	default:
		processors = sysconf(_SC_NPROCESSORS_ONLN);
		break;
	}

	if (processors <= 0)
		processors = 1;

	/*
	 * The result must be at least 1
	*/
	printf("%u\n", (ignore >= processors) ? 1 : processors - ignore);
	return 0;
}
