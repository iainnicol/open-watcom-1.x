// This example compiles using the new STL<ToolKit> from ObjectSpace, Inc.
// STL<ToolKit> is the EASIEST to use STL that works on most platform/compiler 
// combinations, including cfront, Borland, Visual C++, C Set++, ObjectCenter, 
// and the latest Sun & HP compilers. Read the README.STL file in this 
// directory for more information, or send email to info@objectspace.com.
// For an overview of STL, read the OVERVIEW.STL file in this directory.

#include <iostream.h>
#include <stl.h>

int input1 [4] = { 1, 6, 11, 8 };
int input2 [4] = { 1, 5, 2, 3 };

int main ()
{
  int total = 
    inner_product (input1, input1 + 4, input2, 0, plus<int> (), times <int> ());
  cout << "total = " << total << endl;
  return 0;
}
