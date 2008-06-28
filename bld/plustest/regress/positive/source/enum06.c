#include "fail.h"

enum A {
    c1 = 120
};

int f( const A &a )
{
    return 1;
}

int f( A &a )
{
    return 2;
}


int main()
{
    A a1 = c1;
    const A a2 = c1;

    if( f( a1 ) != 2 ) fail(__LINE__);
    if( f( a2 ) != 1 ) fail(__LINE__);

    _PASS;
}
