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
#include <libgen.h>
#include <sys/param.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

#include "core.h"

/* fopen() wrapper */

FILE *home_etc_fopen_core(const char *path, const char *mode)
{
    char pathbuf[MAXPATHLEN];
    char dirbuf[MAXPATHLEN];
    char buf[MAXPATHLEN];
    const char *home_etc_dir, *home_dir, *d;
    char wasdir = 0;
    size_t s;
    
    home_etc_dir = get_home_etc_core(1);
    if (home_etc_dir == NULL || path == NULL || *path == '\0')
	return fopen(path, mode);
    
    s = strlen(path);
    if (strlen(path) > sizeof(pathbuf)-2)
	return fopen(path, mode);

    bzero(pathbuf, sizeof(pathbuf));
    strncpy(pathbuf, path, sizeof(pathbuf));

    /* is it a directory at the end?	*/
    /* if yes, mark it and remember	*/
    s--;
    if (!s) return fopen(path, mode);
    if (s >= 0 && *(pathbuf+s) == '/')
    {
	wasdir = 1;
	*(pathbuf+s) = '\0';
	s--;
	if (!s || *(pathbuf+s) == '/')
	    return fopen(path, mode);
    }

    home_dir = obtain_home_dir(1);
    if (home_dir == NULL || *home_dir == '\0')
	return fopen(path, mode);

    /* now, get the absolute path of the given directory 	*/
    /* then check whether the path is a home directory path	*/

    d = dirname(pathbuf);
    if (d == NULL)
        return fopen(path, mode);

    /* remember current dir */
    bzero(dirbuf, sizeof(dirbuf));
    if ((getcwd(dirbuf, sizeof(dirbuf)-1)) == NULL)
	return fopen(path, mode);
    /* enter the dir */
    if ((chdir(d)) == -1)
        return fopen(path, mode);
    /* fetch the absolute name */
    bzero(buf, sizeof(buf));
    if ((getcwd(buf, sizeof(buf)-1)) == NULL)
    {
	chdir(dirbuf); /* back */
	return fopen(path, mode);
    }
    /* back to old dir */
    chdir(dirbuf);

    /* difference test */
    d = compare_paths(home_dir, d);
    
    if (d == NULL)	/* does not contain home location */
	return fopen(path, mode);

    /* compile output directory string	*/
    /* substitution:			*/
    /* HOME into HOME_ETC		*/
    /* rest into rest			*/
    /* add slash if there was any	*/

    

}
