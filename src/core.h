/* home-etc library: obtain user-decided configuration directory
 *
 * Copyright (C) 2003-2006 Pawel Wilk <siefca@gnu.org>,
 *
 * This is free software; see the GNU Lesser General Public License version 2
 * or later for copying conditions.  There is NO warranty.
 *
 */

#include <sys/param.h>
#include <sys/types.h>

#ifndef	__CORE_H
#define	__CORE_H

#define	ENV_VAR		"HOME_ETC"
#define	HELPER_FILENAME	".home_etc"

extern int errno;

const char *obtain_home_dir(char use_env);
const char *get_home_etc_core(char use_env);
const char *home_etc_path_core(const char *path, char use_env);

char *canonize_path(const char *path, char use_env, char expand_tilde);
const char *compare_paths(const char *a, const char *b);

inline static int isdir(const char *path)
{
  char prev[MAXPATHLEN];

  prev[MAXPATHLEN-1] = '\0';
  if (! getcwd(prev, sizeof(prev)))
    return 0;

  if (chdir(path) == -1 && errno == ENOTDIR)
    return 0;

  chdir(prev);
  return 1;
}

#endif

/*
 Local Variables:
 mode: c
 c-set-style: "gnu"
 End:
*/
