/* home-etc library: obtain user-decided configuration directory
 *
 * Copyright (C) 2003 Pawel Wilk <siefca@gnu.org>,
 *
 * This is free software; see the GNU Lesser General Public License version 2
 * or later for copying conditions.  There is NO warranty.
 *
 */

/* 
 * interface
 */

#ifndef	__HOME_ETC_H
#define	__HOME_ETC_H

/* HOME_ETC location fetchers */

const char *get_home_etc(char use_env);
const char *get_home_etc_static(char use_env);
const char *get_home_etc_static_n(char use_env);

/* pathname reconstructor */

const char *home_etc_path(const char *pathname, char use_env);

/* a sweet wrappers */

const char *_HE(const char *pathname);
const char *_HEn(const char *pathname);

/* a sweetest wrappers */

#define	_HEdir get_home_etc_static_n(1)
#define	_HEndir get_home_etc_static_n(0)

/* reset cache */
void home_etc_reset();

/* for lazy programmers */

#ifdef _HE_DAEMON
# define ___HE _HEn
# define ___HEdir _HEndir
#else
# define ___HE _HE
# define ___HEdir _HEdir
#endif

#endif


/* if use_env is set to != 0 then the HOME and HOME_ETC	*/
/* environment variables will be used to obtain		*/
/* the location of the home directory and HOME_ETC	*/
/* directories.						*/

/*
 Local Variables:
 mode: c
 c-set-style: "gnu"
 End:
*/
