#include <stdio.h>
#include "home_etc.h"

int main(int argc, char *argv[])
{
    printf ("katalog HOME_ETC: %s\n", get_home_etc(1));
    
    return 0;
}
