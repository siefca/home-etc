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

/* HOME_ETC location fetcher */

const char *get_home_etc(char use_home_env)
{
    return get_home_etc_core(use_home_env);
}

/* pathname reconstructor */

const char *home_etc_path(const char *pathname)
{
    return home_etc_path_core(pathname);
}

/* HOME_ETC location fetcher -- static buf */

const char *get_home_etc_static()
{
    static const char *was = NULL;

    if (!was)
    {
	was = get_home_etc_core(1);
	if (!was)
	    was = obtain_home_dir(1);
    }

    return was;
}
