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
#include <sys/param.h>
#include <sys/types.h>

#define	ENV_VAR		"HOME_ETC"
#define	HELPER_FILENAME	".home_etc"

const char *get_home_etc(char use_home_env)
{
    FILE *f;
    char *p;
    size_t s, d;
    struct passwd *pw;
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
	if (use_home_env)
	{
	    p = getenv("HOME");
	}
	if (p == NULL)
	{
	    pw = getpwuid(geteuid());
	    if (pw != NULL && pw->pw_dir != NULL && *pw->pw_dir != '\0')
	    {
		p = pw->pw_dir;
	    }
	    else
	    {
		p = NULL;
	    }
	}
	if (p != NULL)
	{
	    bzero(home_dir, sizeof(home_dir));
	    strncpy(home_dir, p, sizeof(home_dir));
	    endpwent();
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

