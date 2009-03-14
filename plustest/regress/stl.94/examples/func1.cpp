// This example compiles using the new STL<ToolKit> from ObjectSpace, Inc.
// STL<ToolKit> is the EASIEST to use STL that works on most platform/compiler 
// combinations, including cfront, Borland, Visual C++, C Set++, ObjectCenter, 
// and the latest Sun & HP compilers. Read the README.STL file in this 
// directory for more information, or send email to info@objectspace.com.
// For an overview of STL, read the OVERVIEW.STL file in this directory.

#include <iostream.h>
#include <stl.h>

bool bigger (int i_)
{
  return i_ > 3;
}

int main ()
{
  vector<int>v;
  v.push_back (4);
  v.push_back (1);
  v.push_back (5);
  int n = 0;
  count_if (v.begin (), v.end (), bigger, n);
  cout << "Number greater than 3 = " << n << endl;
  return 0;
}
