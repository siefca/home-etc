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
 * compilation: gcc example2.c -lhome_etc -o example2
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <home_etc.h>

int main(int argc, char *argv[])
{
    const char *p;

    setenv("HOME_ETC", "/root/myconfigs", 1);
    p = H_E("/root/.myrc");
    printf("path: %s\n", p);

    exit(0);
}
