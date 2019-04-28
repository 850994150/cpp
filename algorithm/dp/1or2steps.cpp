/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2019-03-20 15:14:33
 * Filename     : 1or2steps.cpp
 * Description  : 有n级台阶，一个人每次上一级或者两级，问有多少种走完n级台阶的方法
 * https://blog.csdn.net/qq_35556504/article/details/80113225
 ***********************************************************
 */

#include <iostream>
using namespace std;

// 动态规划: 一步两步上台阶
int step(int s)
{
    if (s <= 0)
        return 0;
    if (s <= 2)
        return s;                     // f(1) = 1, f(2) = 2
    return step(s - 1) + step(s - 2); // 状态转移方程 f(s) = f(s-1) + f(s-2)
}

int main(int argc, char *argv[])
{
    int steps = 6;
    cout << step(steps) << endl;

    return 0;
}