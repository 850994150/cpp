/***********************************************************
* Author       : M_Kepler
* EMail        : hellohuangjinjie@gmail.com
* Last modified: 2016-04-11 16:24:57
* Filename     : queue-stl.cpp
* Description  :
    * push()\pop()\front()\back()\empty()\size()
**********************************************************/

#include <queue>
#include <iostream>
using namespace std;
int main()
{
    int n;
    double item;
    queue<double> queue_stl;
    cout<<"input length\n";
    cin>>n;

    cout<<"input items\n";
    for(int i=0; i<n; i++)
    {
        cin>>item;
        queue_stl.push(item);
    }
    cout<<endl;

    if (!queue_stl.empty())
        cout<<"size:"<<queue_stl.size()<<endl;

    cout<<"output item\n";
    while(!queue_stl.empty())
    {
        cout<<queue_stl.front()<<" ";
        queue_stl.pop();
    }
    cout<<endl;
    return 0;
}

