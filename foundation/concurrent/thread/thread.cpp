/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2018-12-06 19:51:03
 * Filename     : thread.cpp
 * Description  :
 * 线程间通信
 ***********************************************************
 */
#include <iostream>
#include <vector>
#include <algorithm> // for_each 头文件
// c++11 多线程相关头文件
#include <thread>
#include <mutex>
#include <atomic>
#include <future>
#include <condition_variable>

using namespace std;


volatile int counter(0);
mutex g_lock;
const int NUM = 100;


void func_mutex(void)
{
    for(size_t i = 0; i < NUM; i++)
    {
        // mutex
        // mutex是一个类对象, 其中包含成员函数lock、unlock
        // 有lock一定要有unlock, 否则会导致程序异常
        // 1. lock、unlock
        g_lock.lock();
        ++counter;
        // ... do_something
        g_lock.unlock();

        // 2. lock_guard
        // 是一个类模板，可替代lock、unlock，有了guard就不能出现lock、unlock了，它会自动加解锁
        // 原理: 这是个类模板所以声明对象的时候会调用构造函数，构造函数里加锁; 在退出作用域的时候会自动调用析构函数来解锁
        // 不用自己写lock、unlock，但有个问题这个lock_guard只有在析构的时候（return的时候）才能解锁, 不够灵活。。
        // 或者用大括号把加锁和解锁的地方扩起来来达到限定作用域的作用
        /*
        {
            std::lock_guard<std::mutex>my_lock_guard(g_lock);
            ++counter;
            // ... do_something
        }
        */

        // 3. try_lock
        /*
        if (g_lock.try_lock())
        {
            ++counter;
            // ... do_something
            g_lock.unlock();
        }
        */

        // 死锁

        /*
        产生原因：
        陷入互相等待的状态
        A线程锁住了mutex1, 在想用mutex2锁住的变量时尝试锁mutex2, 发现mutex2被锁了, 等待mutex2释放
        B线程锁住了mutex2, 在想用mutex1锁住的变量时尝试锁mutex1, 发现mutex1被锁了, 等待mutex1释放
        解决：
        1. 原因是A、B线程锁互斥量的顺序不一致, 解锁顺序倒是不影响
        2. std:lock() 函数模板
           std:lock(mutex1, mutex 2)
           解锁还是要手工unlock()，解锁顺序不影响
           可以一次锁住>=2个互斥量，不存在因锁的顺序问题而导致死锁的存在，会等所有都锁住才继续往下走
           原理:
           如果有一个互斥量没锁成功，则会释放掉已锁成功的互斥量，过段时间再去尝试，直到把所有互斥量都锁住为止
           缺点:
           lock()解决死锁的痛点在于存在忘记unlock的危险，而lock_guard刚好可以自动unlock，可否两者优点都有呢？
        3. lock() 和 lock_guard
           使用lock_guard的adopt_lock参数可以做到，让guard构造的时候不lock
           std:lock（mutex1,mutex2)
           lock_guard<mutex>lock_guard(mutex1, adopt_lock)
        */

    }
}


void threadMutex()
{
    thread threads[NUM];
    
    for(size_t i = 0; i < NUM; ++i)
    {
        threads[i] = thread(func_mutex);
    }

    // 为什么这里要用引用？
    for (auto &th : threads)
    {
        th.join();
    }
    // 多次运行输出值不变才是正确的
    cout << "counter = " << counter << endl;
}


void threadMove(void)
{
    int a = 1;
    thread t([](int *pa) {
        for (;;)
        {
            *pa = (*pa * 33) % 0x7fffffff;
            if (((*pa) >> 30) & 1)
                break;
        }
    },
             &a);
    thread t2 = move(t); // 改为 t2 = t 将不能编译。
    t2.join();
    cout << "a=" << a << endl;
}


void threadSwap(void)
{
    int a = 1;
    thread t([](int *pa) {
        for (;;){
            *pa = (*pa * 33) % 0x7fffffff;
            if (((*pa) >> 30) & 1)
                break;
        }
    },
             &a);
    thread t2;
    cout << "before swap: t=" << t.get_id()
         << ", t2=" << t2.get_id() << endl;
    swap(t, t2);
    cout << "after swap : t=" << t.get_id()
         << ", t2=" << t2.get_id() << endl;
    t2.join();
    cout << "a=" << a << endl;
}


int main(int argc, char const *argv[])
{
    /*
    vector<int> vecTest;
    vecTest.push_back(1);
    vecTest.push_back(2);
    vecTest.push_back(3);
    vecTest.push_back(4);
    */
    vector<int> vecTest{1,2,3,4};
    
    for(auto i : vecTest)
    {
        cout << i <<endl;
    }

    cout << "================= move =================" << endl;
    threadMove();
    cout << "\n================= swap =================" << endl;
    threadSwap();
    cout << "\n================= mutex ================" << endl;
    threadMutex();

    return 0;
}
