/* home-etc library: obtain user-decided configuration directory
 *
 * Copyright (C) 2003 Pawel Wilk <siefca@gnu.org>,
 *
 * This is free software; see the GNU Lesser General Public License version 2
 * or later for copying conditions.  There is NO warranty.
 *
 */

/* 
 * interface
 */

#include <stdio.h>

/* HOME_ETC location fetcher */

const char *get_home_etc(char use_home_env);

/* pathname reconstructor */

const char *home_etc_path(const char *pathname);

