#include <stdio.h>
#include <sys/types.h>

#include "core.h"

int main (int argc, char *argv[])
{
    int x;
    const char *a[] = { ".muttrc", "asdfasdf", "/home/.muttrc",
			"/home/users/siefca", "/home/users/siefca/", "/home/users/siefca/.muttrc",
			"/home/users/siefca.muttrc", "/", "", "/home/users/siefca/.muttrc",
			"/home/users/siefca/a/b", "/home/users/siefca/a/b/", "home/users/siefca/a",
			"a/b" };
    
    printf("\nHOME_ETC:\t%s\n\n", get_home_etc_core(1));

    for (x = 0; x < sizeof(a) / sizeof(char *); x++)
    {
	printf(" path:\t\t%s\n result:\t%s\n----------------------------\n",
	        a[x],
		home_etc_path_core(a[x]));
    }
    return 0;
}
