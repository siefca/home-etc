/* home-etc library: obtain user-decided configuration directory
 *
 * Copyright (C) 2003-2006 Pawel Wilk <siefca@gnu.org>,
 *
 * This is free software; see the GNU Lesser General Public License version 2
 * or later for copying conditions.  There is NO warranty.
 *
 */

#include "includes.h"

#ifndef	__CORE_H
#define	__CORE_H

#define	ENV_VAR		"HOME_ETC"
#define	HELPER_FILENAME	".home_etc"

const char *obtain_home_dir(char use_env);
const char *get_home_etc_core(char use_env);
const char *home_etc_path_core(const char *path, char use_env);

char *canonize_path(const char *path, char use_env, char expand_tilde);
const char *compare_paths(const char *a, const char *b);

inline static int isdir(const char *path)
{
  struct stat statbuf;

  if (stat(path, &statbuf) == -1 || !(S_ISDIR(statbuf.st_mode)))
    return 0;

  return 1;
}

#endif

/*
 Local Variables:
 mode: c
 c-set-style: "gnu"
 End:
*/
