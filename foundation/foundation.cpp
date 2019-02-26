/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2019-02-11 21:47:32
 * Filename     : foundation.cpp
 * Description  :
 ***********************************************************
 */

#include <iostream>
using namespace std;

void func(int x)
{
    int countx = 0;
    while(x)
    {
        countx ++;
        x = x&(x-1);
    }
    cout << countx << endl;
}

void operator_test()
{
    /*
    【除号】的正负取舍和一般的算数一样，符号相同为正，相异为负
    【求余符号】的正负取舍和被除数符号相同
    -3/16=0     16/-3=-5     -3%16=-3      16%-3=1
    */
    int a = 5;
    int b = -5;
    printf(("%d,%d\n"), a % (-4), b % (-4));

    // 逗号表达式作为一个整体，它的值为最后一个表达式的值
    int c = (1, 2, 3, 4, 5);
    cout << c << endl;

    func(9999);

}


int main(int argc, char const *argv[])
{
    // operator_test();
    int a = 10, b = 20, c = 50;
    printf("%d,%d\n", a,b,c);
    return 0;

}