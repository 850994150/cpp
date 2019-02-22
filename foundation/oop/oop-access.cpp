/***********************************************************
* Author       : M_Kepler
* EMail        : m_kepler@foxmail.com
* Last modified: 2018-02-05 21:58:47
* Filename     : access.cpp
* Description  : C++ 里类的访问控制 
    * 静态成员变量与静态成员函数见：note.md
    * http://www.cnblogs.com/ayanamistltz/archive/2012/11/22/2783033.html
**********************************************************/

#include <iostream>
#include <string>
using namespace std;

class PIG
{
public:
  PIG(int a)
  {
      A = a;
      B += a;
      m_strName = "hello pig";
  }
  static void f1(PIG m);
  // 静态成员的内存分配在全局/静态存储区
  // 程序运行结束的时候自动释放资源
  friend void f2(int x, PIG &m); // 友元(普通函数放在了类里面)允许访问内部成员
  void f3();

  static double C;

  string m_strName;

protected:
     int protect_var;
     void f4(PIG p);

private:
     int A;
     static int B;
};

// 静态成员函数不属于某个对象，而是属于整个类，因此没有this指针
// 既然不属于某个对象, 那么为什么要放在类里面呢? 和全局变量有什么区别
// 静态成员函数中，不能直接调用非静态成员变量, 因为非静态成员变量只有在对象创建时才分配内存, 而静态成员函数不需要类的实例就可以调用，即通过 class name::调用
// 但可以通过形参传递进来的对象来调用非静态成员变量
void PIG::f1(PIG m)
{
    cout << "A=" << m.A << endl;
    // cout << "A=" << A << endl; // err 静态成员函数只能访问静态的成员变量
    cout << "B=" << B << endl; // 非静态成员函数也可以访问静态成员变量
    // 静态成员函数访问静态成员
    cout << "C=" << C << endl;
    cout << "m.C=" << m.C  << endl;
    // cout << "C=" << this.C << endl;
    cout << "PIG::C=" << PIG::C << endl;
}


// 友元函数不是类的成员函数，不需要用::域引用
void f2(int x, PIG & m)
{
    // m.A = x;
    cout << "friend F2: " << m.A << endl << m.B << endl;
}


void PIG::f3()
{
    cout << "f3.A:" << A << endl;
    cout << "f3.B:" << B << endl;
}

void PIG::f4(PIG p)
{
    cout << p.A << endl;
    cout << p.B << endl;
}

int PIG::B = 0; // 静态数据成员初始化的格式<数据类型><类名>::<静态数据成员名>=<值>
double PIG::C = 0.11;

int main()
{
    PIG P(5), Q(10); // 在栈上实例对象

    PIG::f1(P); // 静态成员函数调用时不用对象名
    // PIG::f3();  // 不能通过类名调用非静态成员
    // cout << PIG::A << endl;
    cout << PIG::C;
    P.f1(P);
    f2(100, P);
    Q.f3();

    PIG *p = new PIG(8); // 在堆上实例对象
    cout << p->m_strName << endl;
    delete p; // 释放内存
    p = NULL;


    return 0;
}
