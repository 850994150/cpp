/***********************************************************
* Author       : M_Kepler
* EMail        : m_kepler@foxmail.com
* Last modified: 2017-07-27 14:48:22
* Filename     : a.cpp
* Description  : 按值传递
    * 传递给函数的值被称为实参;用于接收传地值的变量成为形参
    * 意味着函数定义中的形参是新的变量，他被初始化为函数调用所提供的值
    * C++将数组名参数视为数组地一个元素的地址,因为指针是原始地址的拷贝
**********************************************************/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
const int ArSize = 8;

int age = 39;
const int *pt = &age; //声明一个指向常量的指针pt,指向一个const int，这里不能通过pt来修改这个值，也就是说 *pt的值为const了，不能被就该。
// 但是age是常量。pt指向age，age不是const，可以通过age变量来修改age的值，但不能使用pt指针来修改它
// 所以可以考虑将const变量的地址赋值给const的指针
//
//函数和二维数组的两种写法
// int sum(int (*arr)[4],int size)
// int sum(int arr[][4],int size)
//
//方括号为空指出arr是一个可接受任何长度的数组该该函数，实际上arr实际上是一个指针,但在编写函数的其余部分时，可将arr看作是数组
//该函数接受的是数组第一个元素的地址,由于数组的元素类型为int，因此cookies的类型必须是int指针，即int*。在函数头或函数原型中，这两种表达是一样的
// int sum_arr(int arr[], int n)
//
int sum_arr(int *arr, int n)//都是地址,将实参的地址赋值给了指针变量arr
{
    int total = 0;
    int i;
    for (i = 0; i < n; ++i)
        total = total + arr[i];
    return total;
}

int sum_arr2(const int * begin, const int * end)
{
    const int *pt;
    int total = 0;
    for (pt = begin; pt != end; ++pt)
        total = total + *pt;
    return total;
}



int main()
{
    int cookies[ArSize] = {1,2,4,8,16,32,64,128};
    int sum = sum_arr(cookies,ArSize);//实际上并没有将数组内容传递给函数，而是将数组的地址、包含的元素类型和元素数目提交给函数
    cout << "Total cookies eaten: " << sum << endl;

    int sum2 = sum_arr2(cookies, cookies+ArSize);
    cout << "Total cookies eaten: " << sum2 << endl;
    sum2 = sum_arr2(cookies, cookies+3);
    cout << "First three eaters ate: " << sum2  << " cookies. \n";
    sum2 = sum_arr2(cookies+4, cookies+8);
    cout << "Last four eaters ate: " << sum2 << " cookies. \n";

    return 0;
}



