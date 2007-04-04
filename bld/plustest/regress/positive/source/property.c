#include "fail.h"

class A {
public:
  A():value(0){}
  A(int i):value(i){}
  
  A& operator++();
  A  operator++(int);
  
  int value;
};

A& A::operator++()
{
  value++;
  return *this;
}

A A::operator++(int)
{
  A rc;
  rc.value = value++;
  return rc;
}

class B {
public:
  B();
  
  __declspec(property(get=GetVal, put=SetVal))
  int value;
  
  __declspec(property(get=GetFVal, put=SetFVal))
  double fval;
  
  __declspec(property(get=GetCell, put=SetCell))
  int array[];
  
  __declspec(property(get=Get, put=Set))
  A  aval;
  
  int proc();
  
private:
  A      _aval;
  double _fval;
  int    _value;
  int    _array[20];
  
  A    Get() const { return _aval; }
  void Set(const A& a){ _aval = a; }
  
  int  GetCell(int i) const { return _array[i]; }
  void SetCell(int i, int v){ _array[i] = v; }
  
  int    GetVal() const { return _value; }
  void   SetVal(int i){ _value = i; }
  
  double GetFVal() const { return _fval; }
  void   SetFVal(double i){ _fval = i; }
  
};

class C {
public:
  C(B* b):_b(b){}
  B* operator->(){ return _b;}
private:
  B* _b;
};

B::B()
{
  _fval  = 0.0;
  _value = 0;
  
  for( int i = 0; i < 20; i++ )
    _array[i] = 0;
}

int B::proc()
{
  return aval.value + value;
}

int main()
{
  B b;
  C c = &b;
                                        
  b.value += 5;
  b.aval++;
  ++b.aval;
  ++b.value;
  b.value++;
  
  b.fval += 10;
  ++b.fval;    
  b.fval++;
  b.fval -= 10.0;
  
  for( int i = 0; i < 10; i++ )
    b.array[i] = i+1;
  
  c->array[3] += 10 + b.proc();
  
  if( b.fval != 2.0 )     fail(__LINE__);
  if( b.aval.value != 2 ) fail(__LINE__);
  if( b.value != 7 )      fail(__LINE__);
  if( b.array[3] != 23 )  fail(__LINE__);
  
  _PASS;
}

