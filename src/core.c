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
#include <libgen.h>
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

const char *compare_paths(const char *a, const char *b)
{
    size_t s_a, s_b;
    register const char *p;

    if (a == NULL || b == NULL)
	return NULL;
    if (*a == '\0' || *b == '\0')
	return NULL;

    s_a = strlen(a);
    s_b = strlen(b);
    if (s_a > s_b)
	return NULL;

    if (strncmp(a, b, s_a))
	return NULL;    

    p = b;
    p += strlen(a);

    if (*p != '\0' && *p != '/')
	return NULL; /* strange, e.g.: /home/users/johnsomercfile */
	
    if (*p != '\0')
	p++;

    return p;
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

const char *home_etc_path_core(const char *path)
{
    static char dirbuf[MAXPATHLEN];
    char pathbuf[MAXPATHLEN];
    char buf[MAXPATHLEN];
    const char *home_etc_dir, *home_dir, *p;
    char *f, *d;
    char wasdir = 0;
    size_t s;

    home_etc_dir = get_home_etc_core(1);
    if (home_etc_dir == NULL || path == NULL || *path == '\0')
	return NULL;
    
    s = strlen(path);
    if (strlen(path) > sizeof(pathbuf)-2)
	return NULL;

    bzero(pathbuf, sizeof(pathbuf));
    strncpy(pathbuf, path, sizeof(pathbuf));

    /* is it a directory at the end?	*/
    /* if yes, mark it and remember	*/
    s--;
    if (!s) return NULL;
    if (s > 0 && *(pathbuf+s) == '/') /* was >= */
    {
	wasdir = 1;
	*(pathbuf+s) = '\0';
	s--;
	if (*(pathbuf+s) == '/')
	    return NULL;
    }

    /* fetch the home directory name */
    home_dir = obtain_home_dir(1);
    if (home_dir == NULL || *home_dir == '\0')
	return NULL;

    /* now, get the absolute path of the given directory */
    d = strdup(dirname(pathbuf));
    bzero(pathbuf, sizeof(pathbuf));
    strncpy(pathbuf, path, sizeof(pathbuf));
    f = strdup(basename(pathbuf));

    if (d == NULL && f == NULL)
        return NULL;

    /* remember current dir */
    bzero(dirbuf, sizeof(dirbuf));
    if ((getcwd(dirbuf, sizeof(dirbuf)-1)) == NULL)
    {
	free(f); free(d);
	return NULL;
    }

    /* ding dong! exception */
    /* if we are in home then we can allow empty dirpart of a path */
    /* we are also constructing everything here if te path was not absolute */
    if ((d != NULL && *d != '/') || d == NULL)
    {
	if (!strcmp(dirbuf, home_dir))
	{
	    if (  (strlen(home_etc_dir))
	        + (strlen(f))
		+ (d ? strlen(d) : 0)
		+ 4 > sizeof(dirbuf)
	       )
		{
		    free(d); free(f);
    		    return NULL; /* pathname too long */
		}
		bzero(dirbuf, sizeof(dirbuf));
		strcpy(dirbuf, home_etc_dir);	/* HOME_ETC		*/
		strcat(dirbuf, "/");		/* slash 		*/
		if (d != NULL && *d != '\0' && !(*d == '.' && *(d+1) == '\0'))
		{
			strcat(dirbuf, d);	/* dirname		*/
			strcat(dirbuf, "/");	/* slash 		*/
		}
		strcat(dirbuf, f);		/* filename		*/
		if (wasdir) strcat(dirbuf, "/");
	    return dirbuf;
	}
	else
	{
	    return NULL;
	}
    }

    /* try to enter the obtained dir */
    bzero(buf, sizeof(buf));
    if ((chdir(d)) == -1)
    {
	/* if we cannot enter it means the directory	*/
	/* may not exist yet - it's not an error	*/
	/* it may be a directory name part, appended	*/
	/* to home, e.g.: /home/users/siefca/xxx	*/
	/* in this case we can simply pass the given 	*/
	/* path in hope it will be useful, whithout  	*/
	/* resolving it using system calls..	 	*/
	strncpy(buf, d, sizeof(buf));
	/* todo: recursive from-front resolving in this case 	*/
	/*	 probably slow, but gives us a total effect	*/
    }
    else
    {
	/* fetch the absolute pathname and put it into the buf */
	if ((getcwd(buf, sizeof(buf)-1)) == NULL)
	{
	    free(f); free(d);
	    chdir(dirbuf); /* back */
		return NULL;
	}
	/* back to old dir */
	chdir(dirbuf);
    }

    /* check whether the path is a home directory path	*/
    /* or whether the path contains it			*/

    /* difference test */
    p = compare_paths(home_dir, buf);
    if (p == NULL)	/* buf does not contain home location */
    {
    	free(f); free(d);
	return NULL;
    }
    
    /* now the d variable contains		*/
    /* the rest of the path, after homedir path	*/
    
    if (   (strlen(home_etc_dir))
         + (strlen(p)) 
	 + (strlen(f))
	 + 4 > sizeof(dirbuf)    )
    {
    	free(f); free(d);
    	return NULL; /* pathname too long */
    }
    
    bzero(dirbuf, sizeof(dirbuf));
    strcpy(dirbuf, home_etc_dir);	/* HOME_ETC		*/
    strcat(dirbuf, "/");		/* slash 		*/
    if (p != NULL && *p != '\0')
    {
	strcat(dirbuf, p);		/* rest of the dir	*/
	strcat(dirbuf, "/");		/* slash 		*/
    }
    strcat(dirbuf, f);			/* the filename		*/
    if (wasdir) strcat(dirbuf, "/");

    free(f); free(d);
    return dirbuf;
}
