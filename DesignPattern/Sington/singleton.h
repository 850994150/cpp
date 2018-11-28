/* === 单例模式 ===  */
/* 
    * 目标: 使整个项目中只存在该类的唯一一个实例
    * 构造函数不能轻易被访问, 以免在某个地方又构造出一个实例
   * 既然不对外提供构造函数, 那意味着是在类内部进行实例化,
     而且确保只实例化一次, 还要提供一个public函数去获取这个实例
   * 多线程访问的时候是否线程安全？
   * 能否确保资源正常释放
 */

#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>
#include <thread>
using namespace std;

// 非真正意义上的单例
class Singleton
{
public:
  // 返回引用
  // Singleton single = Singleton::GetInstance();
  // Q1: 这里会类拷贝的问题，调用系统默认的类拷贝函数, 所以要么改一下这里，返回指针；要么自定义类拷贝函数
  /*
  static Singleton& GetInstance()
  {
    // 静态变量存储在全局/静态存储区, 和普通函数不一样
    // 使用静态成员不用考虑资源释放的问题, 因为程序运行结束的时候，会自动释放
    static Singleton instance;
    return instance;
  }
  */
  // A1-1: 改为返回地址
  static Singleton *GetInstance()
  {
    static Singleton instance;
    return &instance;
  }

  static Singleton *GetInstance2()
  {
    if (m_pSingleton == NULL)
    {
      m_pSingleton = new Singleton();
    }
    return m_pSingleton;
  }

  void doSomething()
  {
    cout << "func in singleton.h" << endl;
  }

private:
  static Singleton *m_pSingleton;

  Singleton() {}
  ~Singleton() { cout << "~Singleton()" << endl; }

  // A1-2: 自定义拷贝构造函数和赋值运算符，不做实现，以免调系统默认的
  Singleton(const Singleton &);
  Singleton &operator=(const Singleton &);
};

#endif // SINGLETON_H
