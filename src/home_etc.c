/* home-etc library: obtain user-decided configuration directory
 *
 * Copyright (C) 2003-2006 Pawel Wilk <siefca@gnu.org>,
 *
 * This is free software; see the GNU Lesser General Public License version 2
 * or later for copying conditions.  There is NO warranty.
 *
 */

#include "includes.h"

#include "core.h"
#include "home_etc.h"

static char h_etc_expand_tilde = 0;
static char h_etc_path[MAXPATHLEN];

/****************************************************************/
/* HOME_ETC location fetcher */

const char *get_home_etc(char use_env)
{
  FILE *f;
  const char *p = NULL;
  size_t s, d;
  char home_dir[MAXPATHLEN];

  if (use_env)
    p = getenv(ENV_VAR); /* user's HOME - try the environment */
  if (p != NULL)
    {
      bzero(h_etc_path, sizeof(h_etc_path));
      strncpy(h_etc_path, p, (sizeof(h_etc_path)-2));
      return h_etc_path;
    }
  else			/* user's HOME - try the file */
    {
      p = obtain_home_dir(use_env);
      if (p != NULL)
	{
	  bzero(home_dir, sizeof(home_dir));
	  strncpy(home_dir, p, sizeof(home_dir));
	  s = (sizeof(h_etc_path)) - (sizeof(HELPER_FILENAME)) - 2;
	  d = strlen(home_dir);
	  if (s >= d)
	    {
	      bzero(h_etc_path, sizeof(h_etc_path));
	      strncpy(h_etc_path, home_dir, d);
	      strncat(h_etc_path, "/", 1);
	      strncat(h_etc_path, HELPER_FILENAME, sizeof(HELPER_FILENAME));
	      f = fopen(h_etc_path, "r");
	      if (f != NULL)
	        {
		  bzero(h_etc_path, sizeof(h_etc_path));
		  fgets(h_etc_path, (sizeof(h_etc_path)-2), f);
		  fclose(f);
		  if (*h_etc_path != '\0' && *h_etc_path != '\n' && *h_etc_path != '#')
		    {
		      d = strlen(h_etc_path) - 1;
		      if (d >= 0 && h_etc_path[d] == '\n')
		        {
			  h_etc_path[d] = '\0'; /* chop chop */
			}
		      if (*h_etc_path != '/') /* relative path? */
			{
			  d++;
			  if ((sizeof(h_etc_path)) > 4+d+strlen(home_dir))
			    {
			      strncat(home_dir, "/", 1);
			      strncat(home_dir, h_etc_path, d);
			      strncpy(h_etc_path, home_dir, strlen(home_dir));
			    }
			  else
			    {
			      return NULL; /* err: pathname too long */
			    }
			}
		      return h_etc_path;
		    } /* err: pathname commented or malformed */
		} /* err: file cannot be opened */
	    } /* err: pathname too long */
	} /* err: cannot obtain home directory */
    } /* eof: file try */

  return NULL; /* say noooo */
}

/****************************************************************/
/* pathname reconstructor */

const char *home_etc_path(const char *path, char use_env)
{
  char trailslash = 0;
  static char dirbuf[MAXPATHLEN];
  char pathbuf[MAXPATHLEN];
  char home_dir[MAXPATHLEN];
  const char *home_etc_dir, *p;
  size_t s;

  home_etc_dir = get_home_etc_static(use_env);
  p = obtain_home_dir(use_env);
  if (home_etc_dir == NULL || p == NULL || path == NULL ||
      *path == '\0' || *home_etc_dir == '\0' || *p == '\0')
    return NULL;

  s = strlen(path);
  if (strlen(path) > sizeof(pathbuf)-2)
    return NULL;

  /* memorize trailing slash */
  if (s > 0 && *(path+s-1) == '/')
    trailslash = 1;

  /* clean the buffers */
  bzero(home_dir, sizeof(home_dir));
  bzero(pathbuf, sizeof(pathbuf));
  bzero(dirbuf, sizeof(dirbuf));


  /* absolutize home directory name */
  strncpy(home_dir, p, sizeof(home_dir)-1);
  p = canonize_path(home_dir, use_env, 0);
  if (p == NULL || *p == '\0')
    return NULL;

  /* absolutize given pathname */
  p = canonize_path(path, use_env, h_etc_expand_tilde);
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
  strcpy(dirbuf, home_etc_dir);	/* HOME_ETC	*/
  strcat(dirbuf, "/");		/* slash 	*/
  if (*p != '\0')
    strcat(dirbuf, p);		/* rest of the dir */

  /* add or remove trailing slash as memorized before */
  s = strlen(dirbuf);
  if (s > 0)
    {
      if(trailslash && (*(dirbuf+s-1) != '/') && s < sizeof(dirbuf)-2)
        {
	  *(dirbuf+s) = '/';
	  *(dirbuf+s+1) = '\0';
	}
      if(!trailslash && (*(dirbuf+s-1) == '/'))
        *(dirbuf+s-1) = '\0';
    }

  return dirbuf;
}

/****************************************************************/
/* HOME_ETC location fetchers -- static buf */

const char *get_home_etc_static(char use_env)
{
  static const char *was = NULL;

  if (was == NULL || *was == '\0')
    was = get_home_etc(use_env);

  return was;
}

const char *get_home_etc_static_n(char use_env)
{
  static const char *was = NULL;

  if (was == NULL || *was == '\0')
    was = get_home_etc(use_env);

  if (was == NULL || *was == '\0')
    {
      was = obtain_home_dir(use_env);
      if ((strlen(was)) >= sizeof(h_etc_path))
	was = NULL;
      else
	{
	  strcpy(h_etc_path, was);
	  was = h_etc_path;
	}
    }

  return was;
}

/****************************************************************/
/* pathname reconstruction wrappers */

const char *_HE(const char *pathname)
{
  const char *p = home_etc_path(pathname, 1);

  if (p == NULL)
    return pathname;
	
  return p;
}

const char *_HEn(const char *pathname)
{
  const char *p = home_etc_path(pathname, 0);
    
  if (p == NULL)
    return pathname;
	
  return p;
}

/****************************************************************/
/* cleans cached HOME_ETC directory location string */

void home_etc_reset()
{
  *h_etc_path = '\0';
    
  return;
}

/****************************************************************/
/* cleans cached HOME_ETC directory location string */

void home_etc_expand_tilde(const char expand_tilde)
{
  h_etc_expand_tilde = expand_tilde;

  return;
}

/****************************************************************/
/* canonize pathname as it is possible */

const char *path_canonize(const char *path, char use_env)
{
    return canonize_path(path, use_env, h_etc_expand_tilde);
}

/*
  Local Variables:
  mode: c
  c-set-style: "gnu"
  End:
*/
