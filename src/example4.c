/* home-etc library: obtain user-decided configuration directory
 *
 * Copyright (C) 2003-2006 Pawel Wilk <siefca@gnu.org>,
 *
 * This is free software; see the GNU Lesser General Public License version 2
 * or later for copying conditions.  There is NO warranty.
 *
 *
 * THIS IS AN EXAMPLE FILE, 
 * IT SHOWS HOW TO USE HOME-ETC IN APPLICATIONS BEING MODIFIED
 *
 * compilation: gcc example4.c -lhome_etc -o example4
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "home_etc.h"

int main(int argc, char *argv[])
{
  const char *p;

  setenv("HOME", "/tmp", 1);
  setenv("HOME_ETC", "/tmp/myconfigs", 1);

  _HE_LIKE_TILDE;
  p = _HE("~/.myrc");
  printf("original path: ~/.myrc\n");
  printf("modified path: %s\n", p);

  exit(0);
}

/*
  Local Variables:
  mode: c
  c-set-style: "gnu"
  End:
*/
