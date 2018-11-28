#include <iostream>
#include "test.h"

int g_num = 0;   ///全局变量

extern "C" { Test* create();}

int Test::get()
{
    return g_num;
}

void Test::set(const int num)
{
    g_num = num;
}

Test* create()
{
    return new Test;
}
