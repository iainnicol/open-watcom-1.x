#include "fail.h"

template< class T >
struct A
{
    typedef A AA;

    A();
    A( const AA &a );

    void f( const AA &a );
};


template< class T >
inline A< T >::A()
{ }

template< class T >
inline A< T >::A( const AA & )
{ }

template< class T >
inline void A< T >::f( const AA & )
{ }


int main()
{
    A< int > a1;
    a1.f( a1 );

    A< int > a2( a1 );
    a2.f( a2 );


    _PASS;
}
