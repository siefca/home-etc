/* home-etc library: obtain user-decided configuration directory
 *
 * Copyright (C) 2003 Pawel Wilk <siefca@gnu.org>,
 *
 * This is free software; see the GNU Lesser General Public License version 2
 * or later for copying conditions.  There is NO warranty.
 *
 *
 * THIS IS AN EXAMPLE FILE, 
 * IT SHOWS HOW TO USE HOME-ETC IN APPLICATIONS BEING MODIFIED,
 * WHICH ARE USING automake/autoconf scripts to generate deps,
 *
 * compilation: gcc example3.c -lhome_etc -o example3
 *
 */

#include <stdio.h>

#define HAVE_HOME_ETC_H

/* above definition shouldn't be set here */
/* but in config.h			  */

/* 
 * define the _HE_DAEMON just _before_ including home_etc.h
 * if an application is a daemon which may keep a false   
 * environment while becoming a user (e.g. to make a mail delivery)
 *
 */

#ifdef HAVE_HOME_ETC_H
# define _HE_DAEMON
# include <home_etc.h>
# define __HE(x) ___HE(x)
#else
# define __HE(x) x
#endif

int main (int argc, char *argv[])
{
  printf("path: %s\n", __HE("/root/dupa"));
    
  exit(0);
}

/*
  Local Variables:
  mode: c
  c-set-style: "gnu"
  End:
*/
