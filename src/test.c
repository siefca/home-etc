#include <stdio.h>
#include <sys/types.h>

#include "core.h"

int main (int argc, char *argv[])
{
    int x;
    const char *a[] = { "aaaa/.muttrc", ".muttrc", "aaa/bbb/ccc/", "aaa/bbb/",
			"/home/users/siefca/.muttrc", "/home/users/siefca/.muttrc/xxx",
			"/home/users/siefca/.a", "/home/../home/users/siefca/hmm",
			"/home/../home/users/siefca/hmm/", "/home/users/siefca/.muttrc/"
		      };
    
    printf("\nHOME_ETC:\t%s\n\n", get_home_etc_core(1));

    for (x = 0; x < sizeof(a) / sizeof(char *); x++)
    {
	printf(" path:\t\t%s\n result:\t%s\n----------------------------\n",
	        a[x],
		home_etc_path_core(a[x]));
    }
    return 0;
}
