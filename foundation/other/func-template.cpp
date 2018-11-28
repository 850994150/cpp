/***********************************************************
* Author       : M_Kepler
* EMail        : m_kepler@foxmail.com
* Last modified: 2017-07-31 16:06:59
* Filename     : template.cpp
* Description  : 模板
    * 实例化、具体化
**********************************************************/


#include <iostream>
#include<string>
using namespace std;

#define MAXNAME 10

struct job
{
    char name[MAXNAME];
    int salary;
};

template <class T>
void swap(T &a, T &b)
{
    T temp;
    temp = a;
    a = b;
    b = temp;
};

template void swap<int> (int & a, int & b);

template<> void swap<job>(job &a, job &b)
{
    int salary;
    salary = a.salary;
    a.salary = b.salary;
    b.salary = salary;
}





//模板函数的定义
/*
   template <<typename AnyType>>
   <类型> <函数名> (<参数表>)
   {
   ......<函数体>
   }
*/

template<class T>
T Max(T a,T b)
{
    return a>b?a:b;
}


template<typename AnyType> //用typename或者class都行
void Swap(AnyType &a, AnyType &b)
{
    AnyType temp;
    temp = a;
    a = b;
    b = temp;
}


int main()
{
    int i1,i2;
    cout<<"Input the int number you wanner compare"<<endl;
    cin>>i1>>i2;
    cout<<"Type Max int:"<<Max(i1,i2)<<endl;

    double d1,d2;
    cout<<"Input the double number you wanner compare"<<endl;
    cin>>d1>>d2;
    cout<<"Type Max double:"<<Max(d1,d2)<<endl;

    string str1,str2;
    cout<<"Input the strings number you wanner compare"<<endl;
    cin>>str1>>str2;
    cout<<"Tpye Max string:"<<Max(str1,str2)<<endl;

    return 0;
}

