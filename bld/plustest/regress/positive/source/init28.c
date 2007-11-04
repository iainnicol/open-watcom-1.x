#include "fail.h"

struct A
{
    A()
    { }
};

struct B
{
    int i;
    A a[2];
} b = { 0, { A() } };

struct C
{
    int i;
    A a;
} c = { 0, A() };


int main()
{
    _PASS;
}
