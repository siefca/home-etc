/* home-etc library: obtain user-decided configuration directory
 *
 * Copyright (C) 2003 Pawel Wilk <siefca@gnu.org>,
 *
 * This is free software; see the GNU Lesser General Public License version 2
 * or later for copying conditions.  There is NO warranty.
 *
 */

#include <unistd.h>
#include <stdio.h>
#include <libgen.h>
#include <sys/param.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

#include "core.h"

/* fopen() wrapper */

FILE *home_etc_fopen_core(const char *path, const char *mode)
{
    char *p;
    
    p = home_etc_path_core(path);
    if (p == NULL)
	return fopen(path, mode);

    return fopen(p, mode);
}
