/* === 单例模式 ===  */
/*
    * 目标: 使整个项目中只存在该类的唯一一个实例
    * 构造函数不能轻易被访问, 以免在某个地方又构造出一个实例
    * 既然不对外提供构造函数, 那意味着是在类内部进行实例化,
      而且确保只实例化一次, 还要提供一个public函数去获取这个实例
    * 多线程访问的时候是否线程安全？
    * 能否确保资源正常释放
    * https://study.163.com/course/courseLearn.htm?courseId=1006067356#/learn/video?lessonId=1053491360&courseId=1006067356
 */

#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

std::mutex resource_mutex;

class Singleton
{
  public:
    /* 写法 1 */
    static Singleton *GetInstance1()
    {
        if (m_pSingleton == NULL)
        {
            m_pSingleton = new Singleton(); // new
            static CGarbageCollection gc;   // 静态方法在全局区, 系统自动回收的时候会调用delete
        }
        return m_pSingleton;
    }

    // 写法2
    static Singleton *GetInstance2()
    {
        // 如果实在主线程获取单例, 则用写法1就够了
        // 如果在多线程函数里获取单例, 有可能多个线程同时运行到#1处, 则可能创建多个实例
        if (m_pSingleton == NULL) // 双重锁定
        {
            std::unique_lock<std::mutex> mymutex(resource_mutex);
            if (m_pSingleton == NULL) // #1
            {
                m_pSingleton = new Singleton(); // new
                static CGarbageCollection gc;   // 静态方法在全局区, 系统自动回收的时候会调用delete
            }
        }
        return m_pSingleton;
    }

    class CGarbageCollection
    {
      public:
        ~CGarbageCollection()
        {
            if (Singleton::m_pSingleton)
            {
                cout << "m_pSingleton deleted\n";
                delete Singleton::m_pSingleton; // delete
                Singleton::m_pSingleton = NULL;
            }
        }
    };

    /* 写法 3 */

    // 返回引用
    // Singleton single = Singleton::GetInstance();
    // Q1: 这里会有类拷贝的问题, 程序调用系统默认的类拷贝函数, 所以要么改一下这里，返回指针;要么自定义类拷贝函数
    /*
    static Singleton& GetInstance()
    {
        // static 静态变量存储在全局/静态存储区, 和普通函数不一样
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
