/* realpath: canonize the given pathnames
 *
 * Copyright (C) 2006 Pawel Wilk <siefca@gnu.org>,
 *
 * This is free software; see the GNU Lesser General Public License version 2
 * or later for copying conditions.  There is NO warranty.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <home_etc.h>

extern int errno;

int main(int argc, char *argv[])
{
  int er = 0;
  const char *r = NULL;
  char **p = NULL;
  
  _HE_LIKE_TILDE;
  
  if (argc < 2)
    {
      fprintf(stderr, "usage: realpath pathname [pathname ...]\n");
      exit(1);
    }

  p = argv;
  p++;
  while (p && *p)
    {
      if (**p == '\0')
        continue;
      r = path_canonize(*p, 1);
      if (r == NULL || *r == '\0')
        {
          er = errno;
          perror("realpath");
          fprintf(stdout, "-\n"); 
        }
      else
        {
          fprintf(stdout, "%s\n", r);
        }
      p++;
    }

  if (er)
    exit(er);

  exit(0);
}

/*
  Local Variables:
  mode: c
  c-set-style: "gnu"
  End:
*/
