/* home-etc library: obtain user-decided configuration directory
 *
 * Copyright (C) 2003 Pawel Wilk <siefca@gnu.org>,
 *
 * This is free software; see the GNU Lesser General Public License version 2
 * or later for copying conditions.  There is NO warranty.
 *
 */

#include <sys/param.h>
#include <sys/types.h>
#include <errno.h>

#ifndef	__CORE_H
#define	__CORE_H

#define	ENV_VAR		"HOME_ETC"
#define	HELPER_FILENAME	".home_etc"

const char *obtain_home_dir(char use_home_env);
const char *get_home_etc_core(char use_home_env);
const char *home_etc_path_core(const char *path, char use_home_env);

#endif
