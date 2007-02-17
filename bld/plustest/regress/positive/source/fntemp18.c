#include "fail.h"

template< class T >
struct A
{
    template< class U >
    struct B
    { };
};

template< class T >
const A< int >::B< T > *f( const A<int>::B<T> & )
{
    return 0;
}

template< class T, class U >
const typename A< T >::template B< U > *g( typename A< T >::template B< U > )
{
    return 0;
}

int main()
{
    A< int >::B< long > b;

    const A< int >::B< long > *fb = f( b );
    const A< int >::B< long > *gb = g< int >( b );

    _PASS;
}
