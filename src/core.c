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
#include <stdlib.h>
#include <string.h>
#include <pwd.h>

#include "core.h"

const char *obtain_home_dir(char use_home_env)
{
    struct passwd *pw;
    char *p = NULL;

    if (use_home_env)
    {
        p = getenv("HOME");
    }
    if (p != NULL)
    {
        return p;
    }

    pw = getpwuid(geteuid());
    endpwent();
    if (pw != NULL && pw->pw_dir != NULL && *pw->pw_dir != '\0')
    {
	return pw->pw_dir;
    }
    
    return NULL;
}

const char *get_home_etc_core(char use_home_env)
{
    FILE *f;
    const char *p;
    size_t s, d;
    static char home_etc_path[MAXPATHLEN];
    char home_dir[MAXPATHLEN];

    p = getenv(ENV_VAR); /* try the environment */
    if (p != NULL)
    {
	bzero(home_etc_path, sizeof(home_etc_path));
	strncpy(home_etc_path, p, (sizeof(home_etc_path)-2));
	return home_etc_path;
    }
    else /* try the file */
    {
	p = obtain_home_dir(use_home_env);
	if (p != NULL)
	{
	    bzero(home_dir, sizeof(home_dir));
	    strncpy(home_dir, p, sizeof(home_dir));
	    s = (sizeof(home_etc_path)) - (sizeof(HELPER_FILENAME)) - 2;
	    d = strlen(home_dir);
	    if (s >= d)
	    {
		bzero(home_etc_path, sizeof(home_etc_path));
		strncpy(home_etc_path, home_dir, d);
		strncat(home_etc_path, "/", 1);
		strncat(home_etc_path, HELPER_FILENAME, sizeof(HELPER_FILENAME));
		f = fopen(home_etc_path, "r");
		if (f != NULL)
		{
		    bzero(home_etc_path, sizeof(home_etc_path));
		    fgets(home_etc_path, (sizeof(home_etc_path)-2), f);
		    fclose(f);
		    if (*home_etc_path != '\0' && *home_etc_path != '\n' && *home_etc_path != '#')
		    {
			d = strlen(home_etc_path) - 1;
			if (d >= 0 && home_etc_path[d] == '\n')
			{
			    home_etc_path[d] = '\0'; /* chop chop */
			}
			if (*home_etc_path != '/') /* relative path? */
			{
			    d++;
			    if ((sizeof(home_etc_path)) > 4+d+strlen(home_dir))
			    {
				strncat(home_dir, "/", 1);
				strncat(home_dir, home_etc_path, d);
				strncpy(home_etc_path, home_dir, strlen(home_dir));
			    }
			    else
			    {
				return NULL; /* err: pathname too long */
			    }
			}
			return home_etc_path;
		    } /* err: pathname commented or malformed */
		} /* err: file cannot be opened */
	    } /* err: pathname too long */
	} /* err: cannot obtain home directory */
    } /* eof: file try */

    return NULL; /* say noooo */
}
