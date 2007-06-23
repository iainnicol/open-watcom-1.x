class C;
template<class T> struct A {
struct B { };
  void f();
  void ff(C&);
};

class C {
friend void fff(int);
// yet not supported
//template<class T> friend struct A<T>::B;
template<class T> friend struct A;
template<class T> friend int f(T*, int=0, char* = 0); // #2
// yet not supported
//template<class T> friend void A<T>::f();

int v;
public:
  
};

template<class T> void A<T>::f()
{
  C c;
  c.v = 100;  
}

template<class T> void A<T>::ff(C& c)
{
  c.v = 10;
}

template<class T> int f(T* c, int, char*)
{
  return c->v;
}

void _ff(A<int>& a, C& c)
{
  a.ff(c);
  f(&c);
}


template< typename T1, typename T2 >
class X { };

class Y {
public:
   class nested { };
};

template< typename T1 >
class X< T1, typename T1::nested > { };  // Syntax error.

void foo(X<Y, Y::nested >&)
{
}

class BB {
};

template<class T, class P> class AA { // primary template
int x;
};

template<class T, template<class U, class T> class V> 
void ffT(T, V<T, int>&) 
{
}

void ffE()
{
  BB  b;
  AA<BB, int> a;
  
  ffT(b, a);
}


template <typename T>
char test(T*, int(T::*p)(const T&)const = &T::Compare);

template <typename T>
double test(T*, ...);
  
template <bool>
struct compare;

template <>
struct compare<false> {
  template <typename T>
  static  int                     Compare(const T&, const T&){ return -1; }
};

template <>
struct compare<true> {
  template <typename T>
  static  int                     Compare(const T& t1, const T& t2){ return t1.Compare(t2); }
};
  
template <typename T>
class adapter {
public:
  virtual int                     Compare(const void*, const void*) const;
};
  
template <class T>
int adapter<T>::Compare(const void* p1, const void* p2) const
{
  return compare<sizeof(test((T*)0)) == sizeof(char)>::Compare(*(T*)p1, *(T*)p2);  
}


class Tmp {
public:
                                    
          int                       Compare(const Tmp&) const { return -2; }
};

#include "fail.h"

int main()
{
  adapter<int> a;
  adapter<Tmp> t;
  
  if( a.Compare(0, 0) != -1 ) fail( __LINE__ );
  if( t.Compare(0, 0) != -2 ) fail( __LINE__ );
  _PASS
}    
