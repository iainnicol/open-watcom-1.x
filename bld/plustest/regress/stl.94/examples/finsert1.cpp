// This example compiles using the new STL<ToolKit> from ObjectSpace, Inc.
// STL<ToolKit> is the EASIEST to use STL that works on most platform/compiler 
// combinations, including cfront, Borland, Visual C++, C Set++, ObjectCenter, 
// and the latest Sun & HP compilers. Read the README.STL file in this 
// directory for more information, or send email to info@objectspace.com.
// For an overview of STL, read the OVERVIEW.STL file in this directory.

#include <iostream.h>
#include <stl.h>

char* array [] = { "laurie", "jennifer", "leisa" };

int main ()
{
  deque<char*> names;
  copy (array, array + 3, front_insert_iterator<deque <char*> > (names));
  deque<char*>::iterator i;
  for (i = names.begin (); i != names.end (); i++)
    cout << *i << endl;
  return 0;
}
