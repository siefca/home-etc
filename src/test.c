#include <stdio.h>
#include <sys/types.h>
#include <sys/param.h>

#include "home_etc.h"

int main (int argc, char *argv[])
{
  char b[MAXPATHLEN*2];
  int x;
  const char *a[] = { "aaaa/.muttrc", ".muttrc", "aaa/bbb/ccc/", "aaa/bbb/",
		      "/home/users/siefca/.muttrc", "/home/users/siefca/.muttrc/xxx",
		      "/home/users/siefca/.a", "/home/../home/users/siefca/hmm",
		      "/home/../home/users/siefca/hmm/", "/home/users/siefca/.muttrc/",
		      "tmp/.muttrc", "tmp/.muttrc/", "~/.muttrc", "~/muttrc/", "//.muttrc", "~noexpand",
		      "~", "~/", "/////", "/x"
  };

  home_etc_expand_tilde(1);

  getcwd(b, sizeof(b) - 1);
  b[MAXPATHLEN-1] = '\0';
  printf("\nHOME_ETC:\t%s\n", get_home_etc(1));
  printf("current directory: %s\n\n", b);

  printf("press any key...\n");
  (void) getc(stdin);


  for (x = 0; x < sizeof(a) / sizeof(char *); x++)
    {
      printf(" path:\t\t%s\n result:\t%s\n----------------------------\n",
	     a[x],
	     home_etc_path(a[x],1));
    }

  /* hard-core routines */

  printf("\n----------------------------\n"
	 "hard-core tests\n"
	 "----------------------------\n");

  printf("press any key...\n");
  (void) getc(stdin);

  for (x = 0; x <= MAXPATHLEN+8; x++)
    b[x] = '/';
  b[x] = '\0';

  printf(" path:\t\t%s\n result:\t%s\n----------------------------\n",
	 b,
	 home_etc_path(b,1));

  printf("press any key...\n");
  (void) getc(stdin);

  for (x = 0; x <= MAXPATHLEN+8; x++)
    b[x] = 'a';
  b[x] = '\0';

  printf(" path:\t\t%s\n result:\t%s\n----------------------------\n",
	 b,
	 home_etc_path(b,1));

  printf("press any key...\n");
  (void) getc(stdin);

  for (x = 0; x <= MAXPATHLEN-128; x++)
    b[x] = 'b';
  b[x] = '\0';

  printf(" path:\t\t%s\n result:\t%s\n----------------------------\n",
	 b,
	 home_etc_path(b,1));

  /* wrapper tests */

  printf("\n----------------------------\n"
	 "wrapper tests\n"
	 "----------------------------\n");

  printf("press any key...\n");
  (void) getc(stdin);

  for (x = 0; x < sizeof(a) / sizeof(char *); x++)
    {
      printf(" path:\t\t%s\n result:\t%s\n----------------------------\n",
	     a[x],
	     _HE(a[x]));
    }

  printf("\n----------------------------\n"
	 "wrapper hard-core tests\n"
	 "----------------------------\n");

  printf("press any key...\n");
  (void) getc(stdin);

  for (x = 0; x <= MAXPATHLEN+8; x++)
    b[x] = '/';
  b[x] = '\0';

  printf(" path:\t\t%s\n result:\t%s\n----------------------------\n",
	 b, _HE(b));

  printf("press any key...\n");
  (void) getc(stdin);

  for (x = 0; x <= MAXPATHLEN+8; x++)
    b[x] = 'a';
  b[x] = '\0';

  printf(" path:\t\t%s\n result:\t%s\n----------------------------\n",
	 b, _HE(b));

  printf("press any key...\n");
  (void) getc(stdin);

  for (x = 0; x <= MAXPATHLEN-128; x++)
    b[x] = 'b';
  b[x] = '\0';

  printf(" path:\t\t%s\n result:\t%s\n----------------------------\n",
	 b, _HE(b));

  printf("press any key...\n");
  (void) getc(stdin);

  printf("_HEdir: %s\n", _HEdir);
  printf("_HEndir: %s\n\n", _HEndir);

  printf("\n----------------------------\n"
	 "path_canonize tests\n"
	 "----------------------------\n");

  printf("press any key...\n");
  (void) getc(stdin);

  for (x = 0; x < sizeof(a) / sizeof(char *); x++)
    {
      printf(" path:\t\t%s\n result:\t%s\n----------------------------\n",
	     a[x],
	     path_canonize(a[x],1));
    }

  printf("press any key...\n");
  (void) getc(stdin);

  printf("\n----------------------------\n"
	 "path_canonize hard-core tests\n"
	 "------------------------------\n");

  printf("press any key...\n");
  (void) getc(stdin);

  for (x = 0; x <= MAXPATHLEN+8; x++)
    b[x] = '/';
  b[x] = '\0';

  printf(" path:\t\t%s\n result:\t%s\n----------------------------\n",
	 b,
	 path_canonize(b,1));

  printf("press any key...\n");
  (void) getc(stdin);

  for (x = 0; x <= MAXPATHLEN+8; x++)
    b[x] = 'a';
  b[x] = '\0';

  printf(" path:\t\t%s\n result:\t%s\n----------------------------\n",
	 b,
	 path_canonize(b,1));

  printf("press any key...\n");
  (void) getc(stdin);

  for (x = 0; x <= MAXPATHLEN-128; x++)
    b[x] = 'b';
  b[x] = '\0';

  printf(" path:\t\t%s\n result:\t%s\n----------------------------\n",
	 b,
	 path_canonize(b,1));

  printf("press any key...\n");
  (void) getc(stdin);

  getcwd(b, sizeof(b) - 1);
  b[MAXPATHLEN-1] = '\0';
  printf("\nHOME_ETC:\t%s\n", get_home_etc(1));
  printf("current directory: %s\n\n", b);

  printf("press any key...\n");
  (void) getc(stdin);

  return 0;
}

/*
  Local Variables:
  mode: c
  c-set-style: "gnu"
  End:
*/
