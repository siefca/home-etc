#include <stdio.h>
#include <sys/types.h>

#include "core.h"

int main (int argc, char *argv[])
{
    char b[MAXPATHLEN*2];
    int x;
    const char *a[] = { "aaaa/.muttrc", ".muttrc", "aaa/bbb/ccc/", "aaa/bbb/",
			"/home/users/siefca/.muttrc", "/home/users/siefca/.muttrc/xxx",
			"/home/users/siefca/.a", "/home/../home/users/siefca/hmm",
			"/home/../home/users/siefca/hmm/", "/home/users/siefca/.muttrc/",
			"tmp/.muttrc", "tmp/.muttrc/"
		      };

    printf("\nHOME_ETC:\t%s\n\n", get_home_etc_core(1));

    for (x = 0; x < sizeof(a) / sizeof(char *); x++)
    {
	printf(" path:\t\t%s\n result:\t%s\n----------------------------\n",
	        a[x],
		home_etc_path_core(a[x]));
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
		home_etc_path_core(b));

    printf("press any key...\n");
    (void) getc(stdin);

    for (x = 0; x <= MAXPATHLEN+8; x++)
	b[x] = 'a';
    b[x] = '\0';

    printf(" path:\t\t%s\n result:\t%s\n----------------------------\n",
	        b,
		home_etc_path_core(b));

    printf("press any key...\n");
    (void) getc(stdin);

    for (x = 0; x <= MAXPATHLEN-128; x++)
	b[x] = 'b';
    b[x] = '\0';

    printf(" path:\t\t%s\n result:\t%s\n----------------------------\n",
	        b,
		home_etc_path_core(b));

    return 0;
}
