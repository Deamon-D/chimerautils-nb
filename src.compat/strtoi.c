#include <inttypes.h>
#include <errno.h>

#include "config-compat.h"

#ifndef HAVE_STRTOI
intmax_t
strtoi(const char *nptr, char **endptr, int base, intmax_t lo, intmax_t hi, int *rstatus)
{
	intmax_t in, ret = 0;
	int status = 0;
	int serrno;

	serrno = errno;
	errno = 0;

	in = strtoimax(nptr, endptr, base);

	if (errno != EINVAL)
		status = errno;

	errno = serrno;

	if (*endptr == nptr)
		status = ECANCELED;

	if (in < lo || in > hi) {
		status = ERANGE;
		ret = (in < lo) ? lo : hi;
	}

	if (**endptr != '\0')
		status = ENOTSUP;

	if (status && rstatus)
		*rstatus = status;

	return (status) ? ret : in;
}
#endif
