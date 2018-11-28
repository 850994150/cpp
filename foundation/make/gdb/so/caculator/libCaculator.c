
#include <stdio.h>

/*
extern "C" int add(int, int);
extern "C" int subtract(int, int);
extern "C" int multiply(int, int);
extern "C" int divide(int, int);
*/

int add(int a, int b)
{
    return (a + b);
}

int subtract(int a, int b)
{
    return (a - b);
}

int multiply(int a, int b)
{
    return (a * b);
}

int divide(int a, int b)
{
    return (a / b);
}

// 编译
// gcc -fPIC -shared libCaculator.c -o libCaculator.so
