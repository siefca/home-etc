/* home-etc library: obtain user-decided configuration directory
 *
 * Copyright (C) 2003 Pawel Wilk <siefca@gnu.org>,
 *
 * This is free software; see the GNU Lesser General Public License version 2
 * or later for copying conditions.  There is NO warranty.
 *
 */

#include <stdio.h>
#include <libgen.h>
#include <sys/param.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

#include "core.h"

/* fopen() wrapper */

FILE *home_etc_fopen_core(const char *path, const char *mode)
{
    char buf[MAXPATHLEN];
    const char *home_etc_dir, *home_dir;
    char *h, *b, *d;
    char wasdir=0;
    size_t s;
    
    home_etc_dir = get_home_etc_core(1);
    if (home_etc_dir == NULL || path == NULL || *path == '\0')
    {
	return fopen(path, mode);
    }
    
    s = strlen(path);    
    if (s <= 0 || *(path+s-1) == '/')
    {
	return fopen(path, mode);
    }
	
    home_dir = obtain_home_dir(1);
    if (home_dir == NULL || *home_dir == '\0')
    {
	return fopen(path, mode);
    }

    if (*path == '/')
    {
	/* try to guess if the dir component of the path is a homedir	*/
	/* if yes - substitute it using home_etc			*/
	d = dirname(path);
	if (d == NULL)
	{
	    return fopen(path, mode);
	}
	
	
	return fopen(path, mode);
    }
    else
    {
	/* we have here the relative path - try to guess if the current dir */
	/* is a home dir, and if yes, attach the home_etc dir		    */
	strncpy(home_etc_path, 
    }
}
