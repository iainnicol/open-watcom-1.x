// strings have real '\0' embedded in them! don't edit this file
// without verifying their existence after editing (VI will remove '\0's!)
#include "fail.h"
#include <string.h>

char *p = "123 ";
char *q = "12?? ? ";

int main()
{
    if( strlen( p ) != 3 ) fail(__LINE__);
    if( strlen( q ) != 4 ) fail(__LINE__);
    _PASS;
}
