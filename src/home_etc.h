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

/* HOME_ETC location fetcher */

const char *get_home_etc(char use_home_env);

/* pathname reconstructor */

const char *home_etc_path(const char *pathname);

/* nice macro */

#ifndef		H_E(x)
# define	H_E(x) home_etc_path(x)
#endif


/* if use_home_env is set to != 0 then the HOME		*/
/* environment variable will be used to obtain		*/
/* the location of the home directory			*/
/* if it won't succeed then the password database	*/
/* will be used						*/

