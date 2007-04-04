
void __declspec(property(get=Get, put=Set)) Decl();
 
class B {
public:
  B();
  
  __declspec(property())
  int value;
};

class C {
public:
  C();
  
  __declspec(property(get=GetVal, set=SetVal))
  int value;
  
  __declspec(property(get=GetFVal, get=SetFVal))
  double fval;
  
  __declspec(property(put=SetCell))
  int array[];
  
private:
  double _fval;
  int    _value;
  int    _array[20];
  
  int  GetCell(int i) const { return _array[i]; }
  void SetCell(int i, int v){ _array[i] = v; }
  
  int    GetVal() const { return _value; }
  void   SetVal(int i){ _value = i; }
  
  double GetFVal() const { return _fval; }
  void   SetFVal(double i){ _fval = i; }
  
};

void f(C& b)
{
  b.array[3] += 10;
}

