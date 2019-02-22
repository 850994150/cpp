/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2018-12-06 09:51:12
 * Filename     : template.cpp
 * Description  : TODO
 * 模板
 * 隐式显式实例化、隐式显式调用、模板特化
 * 函数模板
    * 模板函数的定义
    template <typename AnyType> // 关键字用 typename 或 class 都可以
    <类型> <函数名> (<参数表>)
    {
        ...<函数体>
    }
 * 类模板
 ***********************************************************
 */

#include <iostream>
using namespace std;
#define MAXNAME 10

template<typename T1,typename T2>
class myClass
{
    private:
        T1 I;
        T2 J;
    public:
        myClass(T1 a, T2 b);//Constructor
        void show();
};

// 成员函数在类外面定义的语法规则
template <typename T1,typename T2>
myClass<T1,T2>::myClass(T1 a,T2 b):I(a),J(b){}

template <typename T1,typename T2>
void myClass<T1,T2>::show()
{
    cout<<"I="<<I<<", J="<<J<<endl;
}




//模板函数的定义
/*
   template <<typename AnyType>>
   <类型> <函数名> (<参数表>)
   {
       ...<函数体>
   }
*/

template<class T>
T Max(T a,T b)
{
    return a > b ? a : b;
}

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


int main()
{
    /* 函数模板 */
    /* 类模板 */

    // 不用模板时: myClass class1(3, 5);
    myClass<int,int> class1(3,5);
    class1.show();
    myClass<int,char> class2(3,'a');
    class2.show();
    myClass<double,int> class3(2.9,10);
    class3.show();
}