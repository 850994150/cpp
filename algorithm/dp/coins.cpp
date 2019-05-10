/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2019-04-27 19:55:47
 * Filename     : CombinationsOfCoins.cpp
 * Description  : 有面值1,5,10，20,50,100的人民币，求凑10000块钱有多少种组成方法？
 *                https://www.zhihu.com/question/315108379
 ***********************************************************
 */

#include <cstdio>
// #define maxn 10001
#define maxn 6
long long dp[maxn];

int main(void)
{
    int i, j;
    // int num[] = {5, 10, 20, 50, 100};
    int num[] = {1, 2, 5};
    int len = sizeof(num) / sizeof(num[0]);
    for (i = 0; i < maxn; ++i)
    {
        dp[i] = 1;
    }
    for (i = 0; i < len; ++i)
    {
        for (j = num[i]; j < maxn; ++j)
        {
            dp[j] += dp[j - num[i]];
        }
    }
    printf("%lld", dp[maxn - 1]);
    return 0;
}
