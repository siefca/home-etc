/* home-etc library: obtain user-decided configuration directory
 *
 * Copyright (C) 2003 Pawel Wilk <siefca@gnu.org>,
 *
 * This is free software; see the GNU Lesser General Public License version 2
 * or later for copying conditions.  There is NO warranty.
 *
 */

#include <stdio.h>
#include <sys/param.h>
#include <sys/types.h>
#include <errno.h>

#include "core.h"
#include "wrap_fopen.h"

const char *get_home_etc(char use_home_env)
{
    return get_home_etc_core(use_home_env);
}

/* fopen() wrapper */

FILE *home_etc_fopen(const char *path, const char *mode)
{
    return home_etc_fopen_core(path, mode);
}

