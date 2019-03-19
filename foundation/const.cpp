/***********************************************************
* Author       : M_Kepler
* EMail        : m_kepler@foxmail.com
* Last modified: 2018-02-01 10:14:16
* Filename     : define.cpp
* Description  : const
* const
    1. 修饰函数名前后
    2. 修饰函数参数
    3. 修饰函数返回值
    4. 修饰指针变量
    5. 修饰类对象
    6. static、const修饰成员变量的差异
    7. 作用域为类的常量
* static
**********************************************************/

#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

#define SQR(y) ((y) * (y))

// 可以改为模板
/*
template <typename T>
inline int SQR(const T&a, const T&b) { return a*b; }
*/

class CConstTest
{
  private:
    static int iStatic;
        // 在类实现文件中定义并初始化, 初始化时不需要static关键字, 不能在构造函数初始化列表中初始化, 因为它不属于某个对象
    const int iConst;
        // 只能在构造函数初始化列表初始化, 因为const不能被改变, 所以只能在初始化时给初值
    static const int iStaticConst;
        // 与 const static 一样, 给静态成员变量赋值时，不需要加static， 但要加const
        // 和 static 不一样的是, 这变量可以在类内初始化
        // 不可以同时用const和static修饰成员函数。调用const成员函数时其实是有一个隐藏的const this*指针的, 但是static又不含this指针, 所以矛盾

    // 作用域为类的常量: static const 或 enum常量
    static const int iNumTurns = 5;
    int scores[iNumTurns];  // 如果你不希望别人得到你的常量成员的指针或引用
                            // 这里用到了iNumTurns, 但有的编译器不支持static变量类内初始化, 所以不初始化会报错的

    enum { iNum = 12 }; // 枚举常量, 尽量以const、enmu、inline替代define
    double counts[iNum];

    int i;
  public:
    CConstTest(/* args */);
    ~CConstTest();

    int &get();
    // const int &get() { return i; } //const修饰返回值

    int get_const() const; // const 修饰函数; 只有类成员函数才能这样用
                           // 修饰后，该函数不能对类的成员变量进行任何修改, 但可以访问, 而且只能调用const成员函数
                           // const 对象仅可访问const函数，这个好像是与this指针有关
    void StringCopy(char *dest, const char *src); // const 确保传入的src不会被StringCopy内部修改
};

int CConstTest::iStatic = 0;
const int CConstTest::iStaticConst = 30;

CConstTest::CConstTest() : iConst(0) // 初始化列表
{
    i = 0;
}

CConstTest::~CConstTest()
{
}


// const int &CConstTest::get()//  编译报错
int &CConstTest::get()
{
    return i;
}

int CConstTest::get_const() const
{
    // i = 233; // ERROR
    // assignment of member ‘CConstTest::i’ in read-only object
    return iConst;
}

/*
StringCopy函数体如果尝试改动strSource则会爆出错误
值传递是通过产生临时变量用于复制该参数的,所以无需保护
*/
void CConstTest::StringCopy(char *strDestination, const char *strSource)
{
    strcpy(strDestination, strSource);
}

int main(int argc, char const *argv[])
{
    int a = 4, b = 8;
    int iTest1 = 1, iTest2 = 2;
    SQR(a++); //得到的结果为20, 而不是期待的16

    CConstTest clConstTest;
    const CConstTest clConstTest_const; // const类对象

    cout << "===---===---===---===" << "const与变量" << "===---===---===---===" << endl;
    const int *p;   // 表示指针p指向的值常量
    p = &iTest1;    // p还是变量, 可修改
                    // *p = 4; // error
    iTest1 = 3;
    printf("const int*p; *p = %d\n", *p);

    int *const p2 = &iTest2; // 声明的时候就赋初值
    iTest2 = 100;
    // p = &iTets1;         // 报错， p是常量,p的值(地址）是不可改动的
    printf("int *const p2; *p2 = %d\n", *p2);

    cout << "===---===---===---==="
         << "const在类成员函数名前"
         << "===---===---===---===" << endl;

    cout << "before clConstTest.get() = 2: i = " << clConstTest.get() << endl;
    clConstTest.get() = 2333; // 居然直接把类的成员修改了
    cout << "after clConstTest.get() = 2: i = " << clConstTest.get() << endl;

    cout << "===---===---===---==="
         << "const在类成员函数名后"
         << "===---===---===---===" << endl;

    cout << "clConstTest.get_const()" << clConstTest.get_const() << endl;

    cout << "===---===---===---==="
         << "const修饰类成员函数参数"
         << "===---===---===---===" << endl;
    char *src = "Hello";
    char dest[20]; // 额...必须是char数组才行
    clConstTest.StringCopy(dest, src);
    cout << "dest = " << dest << endl;

    cout << "===---===---===---==="
         << "const类对象仅可调用cons函数"
         << "===---===---===---===" << endl;
    // ERROR clConstTest_const.get();
    cout << "clConstTest_const.get_const() = " << clConstTest_const.get_const() << endl;

    return 0;
}
