#include "fail.h"

struct A
{ };

struct B
    : public A
{ };


template< class T >
int f( const T * const * a )
{
    return 1;
}


template< class T >
int f1( T a, T b )
{
    return 1;
}

template< class T >
int f2( const T * const *a, const T * const *b )
{
    return 1;
}


template< class T >
int f2( const T **a, const T **b )
{
    return 2;
}


template< class T >
int f3( const T &a, const A &b )
{
    return 1;
}

template< class T >
int f3( const T &a, const T &b )
{
    return 2;
}


int main()
{
    char **c = 0;

    if( f( c ) != 1 ) fail( __LINE__ );
    if( f( (char **) c ) != 1 ) fail( __LINE__ );
    if( f( (char * const *) c ) != 1 ) fail( __LINE__ );
    if( f( (const char **) c ) != 1 ) fail( __LINE__ );
    if( f( (const char * const *) c ) != 1 ) fail( __LINE__ );


    int *p = 0;

    if( f1( p, (int * const) p ) != 1 ) fail( __LINE__ );
    if( f1( p, p ) != 1 ) fail( __LINE__ );
    if( f1( (int * const) p, p ) != 1 ) fail( __LINE__ );
    if( f1( 0, 0 ) != 1 ) fail( __LINE__ );


    int * const *pp = 0;
    const int * const *qq = 0;
    const int **rr = 0;

    if( f2( pp, pp ) != 1 ) fail( __LINE__ );
    if( f2( qq, qq ) != 1 ) fail( __LINE__ );
    if( f2( rr, rr ) != 2 ) fail( __LINE__ );

    if( f3( A(), B()) != 1 ) fail( __LINE__ );
    if( f3( B(), A()) != 1 ) fail( __LINE__ );
    if( f3( B(), B()) != 2 ) fail( __LINE__ );


    _PASS;
}
