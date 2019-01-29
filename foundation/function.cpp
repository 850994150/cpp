/***********************************************************
* Author       : M_Kepler
* EMail        : m_kepler@foxmail.com
* Last modified: 2017-07-28 14:35:05
* Filename     : function.cpp
* Description  : 函数
    * 匿名函数 lambda(C++11)表达式 
        * [capture list] (param list) mutable exception -> ret_type { body }
        * https://www.cnblogs.com/DswCnblog/p/5629165.html 
        * https://www.cnblogs.com/geloutingyu/p/8335230.html
        * 捕获列表和函数体必需包含
        * 如果函数体包含return, 则返回类型为对应return类型, 如果没有return语句,则返回类型为void
        * 这个捕获参数列表和参数列表不是重复了吗? 引用捕获和参数列表入参引用有什么不一样
        * 捕获列表为空表示该lambda不使用**它所在函数中的任何局部变量**
        * 捕获参数列表形式：[]、[=]、[&]、[=,&x]、[this]
        * 匿名函数不支持默认参数、不支持可变参数、所有参数必须有参数名
    * 尾置返回类型
        * 函数的返回值类型尾置，即放在函数的参数列表后面; 其基本形式为：在形参列表后面并以一个->符号开始。
    * 仿函数 functor
    * 值传递、引用传递、指针传递
        * 如果参数采用指针传递或引用传递，那么加上`const` 可以防止意外地改动该指针，起到保护作用 
        * 值传递和引用传递定义方式不一样
        * 引用传递和指针传递都不会改变实参的值
        * 指针传递在函数中要使用变量的话要用上解除引用运算符*。即(*p)
        * 引用
            * 作为函数参数
            * 可将结构、类对象的引用作为函数的形参
            * 返回值为引用
                * 传统的返回是将结果保存在一个临时的位置然后传递给变量
                * 引用返回是直接将值复制给变量，效率更高
    * 内联函数
        * ????:
            * 常规函数跳转到独立的函数去运行;内联函数用内联代码替换函数的调用。速度比常规函数快，代价是需要占用更多内存,
            * 对于内联代码,程序无需跳到另一个位置执行代码再跳回来.而是用相应的代码替换函数调用.
            * 如果程序在10个不同的地方调用同一个内联函数，则该程序将包含该函数代码的10个副本,所以作为内敛函数的运行时长越短越好(内联函数可不能递归)
            * 和常规函数一样，也是按值来传递参数的。[C++的内联、c的宏]
        * 定义方法:
            * 在函数声明/定义前加上关键字 inline
            * 内联函数也可以放到头文件中
        * [内联函数和宏(#define)的联系](http://ibillxia.github.io/blog/2014/05/17/insight-into-define-and-inline-function-in-c/)
            * https://www.cnblogs.com/yfanqiu/archive/2012/05/07/2488220.html
            * 宏定义是完全原封不动的替换，而内联函数则并非简单的文本替换，而是按函数调用的方式展开。
            * https://www.cnblogs.com/yfanqiu/archive/2012/05/07/2488220.html

    * 函数重载
        * 关键是函数的参数列表（参数的数目和类型、参数的排列顺序）
    * 函数模板（./other/func-template.cpp）
        * 比如我是一个接受和返回int类型的函数。如果数据是double类型的话，重复的代码就又要写一遍。用模板就可以解决这个问题
        * 使用方法和传统函数一样,模板不会减少执行程序的大小，在调用模板函数的时候，编译器都是根据调用时的参数类型进行了相应的实例化
        * 显式实例化、显式具体化
            * 显式实例化
                * 在使用模板前，编译器会根据实例化制定的类型生成模板实例。只需声明
                * template void swap<int>(int &a,int &b); //定义
                * cout << swap<>(m,n); //<>指出编译器应选择木板函数
                * cout << swap<int>(m,n); //显式实例化
            * 显式具体化
                * 就是在函数模板的基础上,对于某些特殊类型，可能不是和模板实现，需要重新定义实现，可以使用显式具体化（必须重新定义）

    * 重载 + 模板
        * 调用优先级：普通函数>显示具体化>显式实例化>普通模板

    * 类模板
        * 缺点: 编写的模板可能无法处理某些类型的运算。比如数组的大小比较
        *
    * 回调函数
        * 函数B在运行的时候调用以参数形式传递进来的函数A
    
    * 函数名前后有const、和const修饰函数从参数的情况
**********************************************************/

#include <iostream>
#include <algorithm> // for_each
#include <stdarg.h>  // va_list
#include <assert.h>
#include <vector>

using namespace std;

#define END 0

//内联函数定义
inline double square(double x) { return x * x; }

// 函数模板定义
template <class T> //或者template <typename T>
void Swap(T &a, T &b)
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}

// https://blog.csdn.net/fengidea/article/details/30237233
//值传递函数操作的不是实际参数本身，所以没有改变实参的值 //使用的是程序的值的拷贝,显示的是拷贝的地址，而不是原地址
void change_val(int n)
{
    cout << "按值传递\t函数操作地址:" << &n << endl;
    n++;
}

//将实际参数的地址传递给函数，只是相当于实际参数的一个别名，会影响到实参 //允许被调用的函数能够访问调用函数中的变量
void change_quote(int &n)
{
    cout << "引用传递\t函数操作地址:" << &n << endl;
    n++;
}

//实际上是值传递的方式，传递的是一个地址值
void change_pointer(int *n)
{
    cout << "指针传递\t函数操作地址:" << n << endl;
    *n = *n + 1;
}

// 定义带参回调函数
void PrintfText(char *s)
{
    cout << s;
    cout << "函数调用函数dosomething()" << endl;
}

// 定义实现带参回调函数的"调用函数"
// 函数指针
typedef void (*callbackFunc)(char *);
void CallPrintfText(callbackFunc lpFunc, char *s)
{
    lpFunc(s);
}

bool cmp(int &a, int &b)
{
    return a > b;
}

// lambda表达式
void LambdaSample()
{
    vector<int> data;
    for (int i = 0; i < 10; ++i)
    {
        data.push_back(i);
    }
    // sort(data.begin(), data.end(), cmp);
    sort(data.begin(), data.end(), [](int &a, int &b) -> bool { return a > b; });

    for (int i = 0; i < data.size(); ++i)
    {
        cout << data[i] << "\t";
    }
    cout << endl;
}

int LambdaSample2()
{
    vector<int> data;
    vector<int> result;
    for (int i = 0; i < 10; ++i)
    {
        data.push_back(i);
    }

    for_each(data.begin(), data.end(), [&result](int &elem) {
        if (elem % 2 == 0)
            result.push_back(elem);
    });

    for_each(result.begin(), result.end(), [](int &elem) {
        cout << elem << "\t";
    });
    cout << endl;

    // 迭代器遍历
    for (int value : result)
    {
        cout << value << "\t";
    }
    cout << endl;

    int a = 123;

    // auto f = [&a]{cout << a << endl;};
    // a = 321;
    // f(); // 321

    // auto f = [](int&a){cout << a << endl;};
    // a = 321;
    // f(a); // 321

    // auto f = [a](){cout << a++ << endl;}; // error 值传递无法修改值

    return 0;
}

// 闭包?
// 体现了捕获列表的作用了, counterGreator函数的参数在GreatCounter里用上了
// 可以不通过传参获取调用者上下文环境(意思是通过传参也是可以的了,见下面注释部分)
template <typename U>
// int GreatCounter(vector<int>& vecNumber, int y, U filter)
int GreatCounter(vector<int> &vecNumber, U filter)
{
    int count = 0;
    // 用引用会改变 vecNumber 的值, 比如线程vector中, 就要用引用才能正常join
    for (auto &x : vecNumber)
    {
        // if (filter(x,y) == 1)
        if (filter(x) == 1)
        {
            count++;
        }
    }
    return count;
}

int counterGreator(vector<int> &vecNumber, int y)
{
    // 捕获列表捕获lambda所在函数体的局部变量y
    // return GreatCounter(vecNumber, y, [](int x, int &y){return x>y;});
    return GreatCounter(vecNumber, [=](int x) { return x > y; });
}

// const放在函数名前
// const int& constFunc(int a)
int &constFunc(int &a)
{
    return a;
}

void NullPtr(int a)
{
    cout << a << endl;
}

void NullPtr(int *ptr)
{
    assert(!ptr);
    cout << ptr << endl;
}

void va_sum(int &sum, ...)
{
    va_list ap;
    va_start(ap, sum);
    int temp = 0;
    while ((temp = va_arg(ap, int)) != END)
    {
        sum += temp;
    }
    va_end(ap);
}

int main()
{
    int n = 10;
    int &m = n;
    int *ptr = &n;
    vector<int> vecIntNumber;

    for (size_t i = 0; i < 10; i++)
    {
        vecIntNumber.push_back(i);
    }

    cout << " \n---------------- for_each -----------------\n";
    // c++98初始化 int a = 10;
    vector<int> vecInt = {1, 2, 3, 4, 5};
    // c++11初始化 int a(10);
    vector<int> vecIntNew{1, 2, 3, 4, 5};
    vector<int> vecIntNew2(3);    // 相当于三个0
    vector<int> vecIntNew3(3, 9); // 相当于三个9

    for_each(begin(vecIntNew), end(vecIntNew), [](int a) { cout << a << " "; });
    cout << endl;

    cout << " \n----------------参数传递-----------------\n";
    cout << "实参地址:\t" << &n << endl;
    change_val(n);
    cout << "按值传递:\tn=" << n << endl;
    change_quote(m);
    cout << "引用传递:\tn=" << n << endl;
    change_pointer(ptr);
    cout << "指针传递:\tn=" << n << endl;

    cout << " \n----------------内联函数----------------\n";
    double a, b;
    double c = 13.0;
    a = square(5.0);
    b = square(4.5 + 7.5);
    cout << "a = " << a << ", b = " << b;
    cout << ", c = " << c << endl;

    cout << " \n----------------回调函数----------------\n";
    CallPrintfText(PrintfText, (char *)"Hello World!\n");

    cout << " \n---------------- lambda ----------------\n";
    LambdaSample();
    LambdaSample2();
    cout << counterGreator(vecIntNumber, 5) << endl;

    // 这里是怎么给lambda形参入参的?
    // 相当与每个vecIntNumber的元素对lambda表达式入参
    // for_each里用的是逗号
    for_each(begin(vecIntNumber), end(vecIntNumber), [](int i) {
        std::cout << i << " ";
    });
    cout << endl;

    int total = 0;
    for_each(begin(vecIntNumber), end(vecIntNumber), [&total](int i) {
        total += i;
    });
    cout << total << endl;

    /*
    auto func = [&total](int i){total+=i;};
    for(size_t i = 0; i < vecIntNumber.size(); i++)
    {
        func(i);
    }
    cout << total << endl;
    */

    cout << " \n--------------- nullptr ---------------\n";
    int *p = nullptr;
    int *q = NULL;
    bool equal = (p == q); // nullptr 和 NULL 都可以定义空指针
    NullPtr(0);            // c++98编译失败, 存在二义性
    NullPtr(p);

    cout << " \n--------------- 变长参数 ---------------\n";
    int sum = 0;
    va_sum(sum, 1, 2, 3, 4, 5, 6, 7, 8, 9, END);
    cout << "va_sum:" << sum << endl;

    cout << " \n---------------const和函数---------------\n";
    // 见 const.cpp
    int iA = 10;
    constFunc(iA) = 100; // 不加const的话, 这里直接把iA给改了
    cout << iA << endl;

    return true;
}
