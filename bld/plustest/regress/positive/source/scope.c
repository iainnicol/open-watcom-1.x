#include "fail.h"

struct AA {
    typedef int AAT;
    void f1(AAT);
    void f2(float);
};
struct B {
    typedef float BT;
    friend void AA::f1(AAT); // parameter type is AA::AAT
    friend void AA::f2(BT); // parameter type is B::BT
};

class YY {
public:
  static int i;
  class XX { 
    class I;
    int x;
  };
};

int YY::i;

class YY::XX::I {
public:
  void f(XX* px);
};


void YY::XX::I::f(XX* px)
{
  px->x = 0; i = 10;
} 

class test;

class E {
  int x;
  class B { };
  class I {
    B b; // OK
    int y;
    void ff(test* p);
    void f(E* p, int i)
    {
      p->x = i; // OK
    }
  };
  //int g(I* p)
  //{
    //return p->y; // error: I::y is private
  //} 
};

class test {
  int x;
  friend class A;
  friend class E::I;
};

void E::I::ff(test* t)
{
  t->x = 10;
} 

ALWAYS_PASS
