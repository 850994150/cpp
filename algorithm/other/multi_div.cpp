/***********************************************************
* Author       : M_Kepler
* EMail        : m_kepler@foxmail.com
* Last modified: 2017-07-27 17:41:54
* Filename     : multi_div.cpp
* Description  : 多约数问题(找到a到b之间约数个数最多的那个数字)
**********************************************************/


#include <iostream>
using namespace std;

int div(int n)
{
    int count = 0;
    for(int i=1; i<=n; i++)
        if (n%i == 0)
            count ++ ;
    return count;
}

int div2(int n)
{
    int sum = 0;
    if (n<=0) return 0;
    if (n==1) return 1;
    for (int i=0; i<=n/2; i++)
    {
        if(n%i==0)
            sum++;
    }
    return (sum + 1);
}


int main()
{
    int a,b;
    cin >> a >> b;
    int maxdiv = 1;
    int number = 0;
    for (int i=a; i<=b; i++)
    {
        if(maxdiv < div(i))
        {
            maxdiv = div(i);
            number = i;
        }
    }
    cout << maxdiv;
    return 0;
}

