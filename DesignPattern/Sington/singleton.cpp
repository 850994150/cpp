#include "singleton.h"
// #include <thread>

const int iThreadCount = 10;

Singleton *Singleton::m_pSingleton = NULL;

void run(int i)
{
    Singleton *p_single = Singleton::GetInstance();
    cout << "in thread: " << i << "\taddress: " << p_single << endl;
}

int main(int argc, char const *argv[])
{
    /* code */
    // Singleton single = Singleton::GetInstance();
    // cout << single << endl;

    Singleton *p_single2 = Singleton::GetInstance();
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


