/* home-etc library: obtain user-decided configuration directory
 *
 * Copyright (C) 2003-2006 Pawel Wilk <siefca@gnu.org>,
 *
 * This is free software; see the GNU Lesser General Public License version 2
 * or later for copying conditions.  There is NO warranty.
 *
 */

#include <stdio.h>

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

inline static int absolutize_dir(char *path, size_t s)
{
  /* change dir to path */
  if (chdir(path) == -1)
    return -1;

  /* get the result */
  if (! getcwd(path, s))
    {
      return -1;
    }

  return 0;
}

/*********************************************************************/

const char *canonize_path(const char *path, char use_env, char expand_tilde)
{
  char trailslash = 0;
  int counter = 256;
  size_t s;
  char *p = NULL;
  char *q = NULL;
  const char *home_d = NULL;
  static char pbuff[MAXPATHLEN+2];
  char buff[MAXPATHLEN];
  char intbuf[MAXPATHLEN];
  char prev[MAXPATHLEN];

  /* memorize CWD */
  prev[MAXPATHLEN-1] = '\0';
  if (! getcwd(prev, sizeof(prev)))
    return NULL;

  /* memorize trailing slash */
  s = strlen(path);
  if (s > 0 && *(path+s-1) == '/')
    trailslash = 1;

  bzero(buff, sizeof(buff));
  bzero(pbuff, sizeof(pbuff));

  /* if we have just tilde */
  if (expand_tilde && *path == '~' && *(path+1) == '\0')
    {
      home_d = obtain_home_dir(use_env);
      if (home_d == NULL ||
          strlen(home_d) + strlen(path) > sizeof(buff)-2)
        {
	  chdir(prev);
          return NULL;
        }
    }

  /* if we have leading tilde-slash or just tilde */
  if (expand_tilde && *path == '~' &&
      (*(path+1) == '/' || *(path+1) == '\0') )
    {
      home_d = obtain_home_dir(use_env);
      if (home_d == NULL ||
          strlen(home_d) + strlen(path) > sizeof(buff)-2)
        {
	  chdir(prev);
          return NULL;
        }
      strcpy(buff, home_d);      /* strcpy checked */
      if (*(path+1) != '\0')
        strcat(buff, path+1);    /* strcat checked */
      else
	trailslash = 0;
    }
    else /* or just copy path into buffer */
    {
      if (strlen(path) > sizeof(buff)-2)
        {
	  chdir(prev);
	  return NULL;
        }
      strcpy(buff, path); /* strcpy checked */
    }

  /* if we (still) have relative pathname */
  if (*buff != '/' && *buff != '\0')
    {
      intbuf[sizeof(intbuf)-1] = '\0';
      if (!getcwd(intbuf, (sizeof(intbuf) - 2)) ||
	   strlen(intbuf) + strlen(buff) > sizeof(pbuff) - 2)
        {
	  chdir(prev);
	  return NULL;
	}
      strcpy(pbuff, intbuf);/* strcpy checked */
      strcat(pbuff, "/");   /* strcpy checked */
      strcat(pbuff, buff);  /* strcat checked */
    }
  else /* or if we have absolute pathname */
    {
      if (strlen(buff) > sizeof(pbuff)-2)
	{
	  chdir(prev);
	  return NULL;
	}
      strcpy(pbuff, buff);   /* strcpy checked */
    }

  /* remember the original size */
  s = strlen(pbuff);

  /* travel from last slash to first and try to enter the dir */
  /* to split path into 2 pieces: resolvable and unresolvable */
  q = NULL;
  while((q = strrchr(pbuff, (int)'/')) && counter--
        && chdir(pbuff) == -1)
    *q = '\0';

  /* do we have strange traversal loops? */
  if(counter <= 0)
    {
      chdir(prev);
      return NULL;
    }

  /* do we have pure resolvable path? */
  if (q == NULL || q >= pbuff+s)
    q = pbuff+s;                   /* point q to \0 string  */
  else
    q += strlen(q);                /* point q to last char  */

  /* q pointer now keeps the borderline between resolvable    */
  /* and unresolvable part of the pathname                    */

  /* rebirth our paths by eliminating zeroes from prev. oper. */
  p = q;
  while(p < pbuff+s)
    {
      if(*p == '\0')
	*p = '/';
      p++;
    }

  /* keep unresolvable part of the path in intbuf */
  if(q && *q != '\0')
    {
      if(strlen(q) > sizeof(intbuf)-2)
        {
          chdir(prev);
          return NULL;
        }
      strcpy(intbuf, q); /* strcpy checked */
      *q = '\0';         /* keep split */
    }
  else
    *intbuf = '\0';	 /* if q was unnecessary */

  /* make the buffered, resolvable path absolute */
  if(absolutize_dir(pbuff, sizeof(pbuff)-1) == -1)
    {
      chdir(prev);
      return NULL;
    }

  /* do we have unresolvable part of path? */
  if(intbuf && *intbuf != '\0')
    {
      /* attach the unresolvable part to the absolutized part */
      if(strlen(pbuff)+strlen(intbuf) > sizeof(pbuff)-2)
        {
          chdir(prev);
          return NULL;
        }
      strcat(pbuff, intbuf);   /* strcat checked */
    }

  /* add or remove trailing slash as memorized before */
  s = strlen(pbuff);
  if (s > 0)
    {
      if(trailslash && (*(pbuff+s-1) != '/') && s < sizeof(pbuff)-2)
        {
	  *(pbuff+s) = '/';
	  *(pbuff+s+1) = '\0';
	}
      if(!trailslash && (*(pbuff+s-1) == '/'))
        *(pbuff+s-1) = '\0';
    }

  /* go back to the directory we were and return pointer to buffer */
  chdir(prev);
  return pbuff;
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

/*
  Local Variables:
  mode: c
  c-set-style: "gnu"
  End:
*/
