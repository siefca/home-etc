/* home-etc library: obtain user-decided configuration directory
 *
 * Copyright (C) 2003 Pawel Wilk <siefca@gnu.org>,
 *
 * This is free software; see the GNU Lesser General Public License version 2
 * or later for copying conditions.  There is NO warranty.
 *
 */

#include "includes.h"
#include "core.h"

/*********************************************************************/

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

const char *canonize_path(const char *path)
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

const char *obtain_home_dir(char use_env)
{
    struct passwd *pw;
    char *p = NULL;

    if (use_env)
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

