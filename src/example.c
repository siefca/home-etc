/* home-etc library: obtain user-decided configuration directory
 *
 * Copyright (C) 2003 Pawel Wilk <siefca@gnu.org>,
 *
 * This is free software; see the GNU Lesser General Public License version 2
 * or later for copying conditions.  There is NO warranty.
 *
 *
 * THIS IS AN EXAMPLE FILE, 
 * IT SHOWS HOW TO USE HOME-ETC IN APPLICATIONS BEING MODIFIED
 *
 * compilation: gcc example.c -lhome_etc -o example
 *
 * (note the lines marked by 3 asterixes)
 *
 */

#include <stdio.h>
#include <string.h>
#include <home_etc.h> 		/***/


int main(int argc, char *argv[])
{
    char *p;
    char path[2048];
    FILE *f;
    
    bzero(path, sizeof(path));
    p = getenv("HOME");
    if (p) strncpy(path, p, sizeof(path)-64);
    strcat(path, "/.myrcfile");
    
    /* was: f = fopen(path, "r"); */
    
    f = fopen(H_E(path), "r");	/***/

    fclose(f);

    exit(0);
}
