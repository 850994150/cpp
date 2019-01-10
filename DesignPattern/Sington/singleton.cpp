#include "singleton.h"
// #include <thread>

const int iThreadCount = 10;

Singleton *Singleton::m_pSingleton = NULL;

void run(int i)
{
    // Singleton *p_single = Singleton::GetInstance();
    Singleton *p_single = Singleton::GetInstance2(); // 如果在这里获取单例的话, 会有多线程问题, 有可能多个线程同时运行到这里: if (m_pSingleton == NULL)
    cout << "in thread: " << i << "\taddress: " << p_single << endl;
}

int main(int argc, char const *argv[])
{
    /* code */
    // Singleton single = Singleton::GetInstance();
    // cout << single << endl;

    // 在主线程获取单例
    Singleton *p_single2 = Singleton::GetInstance2();
    cout << "address of p_single2 = " << p_single2 << endl;

    thread *threads = new thread[iThreadCount];

    for (int i = 0; i < iThreadCount; i++)
    {
        threads[i] = thread(run, i);
    }

    for (int i = 0; i < iThreadCount; i++)
    {
        threads[i].join();
    }

    return 0;
}


