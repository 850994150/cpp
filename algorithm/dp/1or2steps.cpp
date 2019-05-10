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

/*
 * @function: 跳台阶问题
 * @brief	: 每次可以跳1步或2步，问从0跳到100总共需要跳多少次
 *            假设f(100)表示跳100级台阶需要跳的次数
 *            只有两种走法，从第99阶跳1步 或者 从第98阶跳2步
 *            则通项公式为: f(n) = f(n-1) + f(n-2) (n>=2)
 * @param	: 
 * @return	: 
 */
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