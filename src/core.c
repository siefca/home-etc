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

/*********************************************************************/

inline const char *compare_paths(const char *a, const char *b)
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

/*********************************************************************/

inline static int canonize_dir(char *path, size_t s)
{
    char buff[MAXPATHLEN];
    
    if (! getcwd(buff, sizeof(buff)-2))
	return -1;
    buff[MAXPATHLEN-1] = '\0';
    if (chdir(path) == -1)
	return -1;
    if (! getcwd(path, s))
    {
	chdir(buff);
	return -1;
    }

    if (*path == '/' && *(path+1) == '\0')
	*path = '\0';

    chdir(buff);
    return 0;
}

/*********************************************************************/

static const char *canonize_path(const char *path)
{
    int counter = 254;
    size_t s;
    char *p = NULL, *q = NULL;
    char buff[MAXPATHLEN];
    static char pathbuf[MAXPATHLEN];

    bzero(buff, sizeof(buff));
    bzero(pathbuf, sizeof(pathbuf));

    s = strlen(path);
    if (s > sizeof(buff) - 2 || s <= 0)
	return NULL;

    if (*path != '/')
    {
	if (! getcwd(buff, sizeof(buff)))
	    return NULL;
	s += strlen(buff);
	if (s > sizeof(pathbuf) - 2)
	    return NULL;
	strcpy(pathbuf, buff);
	*buff = '\0';
    }

    strncat(buff, path, sizeof(buff)-1);
    p = buff;
    if (*p == '/') p++;
    s = strlen(pathbuf) - 2;

    while (s > 0 && counter > 0 && (q = strchr(p, (int)'/')))
    {
	if (*(q+1) != '\0')
	    *q = '\0';
	s -= strlen(p) + 1;
	if (s <= 0) return NULL;
	strcat(pathbuf, "/");
	strcat(pathbuf, p);
	p = q+1;
	if (canonize_dir(pathbuf, s) == -1)
	    break;
	counter--;
    }
    if (s <= 0 || counter <= 0) return NULL;
    
    if (p && *p != '\0')
    {
	s = sizeof(pathbuf) - strlen(pathbuf) - 2;
	if (strlen(p) > s) return NULL;
	strcat(pathbuf, "/");
	strcat(pathbuf, p);
    }

    return pathbuf;
}

/*********************************************************************/

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

/*********************************************************************/

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

/*********************************************************************/

const char *home_etc_path_core(const char *path, char use_home_env)
{
    static char dirbuf[MAXPATHLEN];
    char pathbuf[MAXPATHLEN];
    char home_dir[MAXPATHLEN];
    const char *home_etc_dir, *p;
    size_t s;

    home_etc_dir = get_home_etc_core(use_home_env);
    p = obtain_home_dir(use_home_env);
    if (home_etc_dir == NULL || p == NULL || path == NULL ||
        *path == '\0' || *home_etc_dir == '\0' || *p == '\0')
	return NULL;

    s = strlen(path);
    if (strlen(path) > sizeof(pathbuf)-2)
	return NULL;

    bzero(home_dir, sizeof(home_dir));
    bzero(pathbuf, sizeof(pathbuf));
    bzero(dirbuf, sizeof(dirbuf));

    /* absolutize home directory name */
    strncpy(home_dir, p, sizeof(home_dir)-1);
    p = canonize_path(home_dir);
    if (p == NULL || *p == '\0')
	return NULL;

    /* absolutize given pathname */
    p = canonize_path(path);
    if (p == NULL || *p == '\0')
	return NULL;

    /* make a difference test */
    p = compare_paths(home_dir, p);
    if (p == NULL)
	return NULL;

    /* now the p variable contains		*/
    /* the rest of the path, after homedir path	*/
    if (   (strlen(home_etc_dir))
         + (strlen(p)) 
	 + 4 > sizeof(dirbuf)    )
    	return NULL; /* pathname too long */

    bzero(dirbuf, sizeof(dirbuf));
    strcpy(dirbuf, home_etc_dir);	/* HOME_ETC		*/
    strcat(dirbuf, "/");		/* slash 		*/
    if (*p != '\0')
	strcat(dirbuf, p);		/* rest of the dir	*/

    return dirbuf;
}
