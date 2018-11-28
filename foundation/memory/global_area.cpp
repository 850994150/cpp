/***********************************************************
* Author       : M_Kepler
* EMail        : m_kepler@foxmail.com
* Last modified: 2018-07-02 15:55:43
* Filename     : global_area.cpp
* Description  :
************************************************************/

#include <iostream>
#include <string>
using namespace std;

// #define _CRT_SECURE_NO_WARNINGS

char * get_str1()
{
    char * p = "asdf"; //文字常量区
    return p;
}

char * get_str2()
{
    // char * q = "asdf"; //文字常量区
    char * q = "asdf2"; //文字常量区
    return q;
}

int main(int argc, const char *argv[])
{
    char  * p = NULL;
    char  * q = NULL;
    p = get_str1();
    printf("p=%s, p=%d\n", p, p);

    q = get_str2();
    printf("q=%s, q=%d", q , q);

    return 0;
}
