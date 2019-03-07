/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2016-03-07 18:22:17
 * Filename     : priority-queue-stl.cpp
 * Description  : ????
 ***********************************************************
 */

#include <iostream>
#include <queue>
using namespace std;

int main()
{
    priority_queue<int> pq;
    pq.push(1);
    pq.push(5);
    pq.push(2);
    pq.push(9);
    cout << pq.size() << endl;
    while (!pq.empty())
    {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;
    return 0;
}
