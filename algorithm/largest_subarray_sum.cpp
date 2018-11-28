/***********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2017-07-27 17:11:22
 * Filename     : largest_subarray_sum.cpp
 * Description  : 最大子数组和
 * http://my.oschina.net/itblog/blog/267860
 **********************************************************/

#include <iostream>
using namespace std;

int max3(int i, int j, int k)
{
    if(i>=j && i>=k)
        return i;
    return max3(j, k, i);
}

int MaxSum(int *a, int n)
{
    int sum = 0;
    int max = 0;
    // 最大子序列第一个元素不可能为负数;
    // 不可能包含和为0或负数的子序列作为前缀;
    // 这样就避免了统一元素进行多次考虑
    for (int i = 0; i < n; ++i)
    {
        sum  += a[i];
        if(sum > max)
            max = sum;
        else if(sum < 0)
            sum = 0;
    }
    return max;
}

// 分治法
int maxsequence2(int a[], int l, int u)
{
    if (l > u) return 0;
    if (l == u) return a[l];
    int m = (l + u) / 2;
    //求横跨左右的最大连续子序列左半部分
    int lmax=a[m], lsum=0;
    //这个循环是求这个序列的最大值,把所有元素相加
    for (int i=m; i>=l; i--) {
        lsum += a[i];
        if (lsum > lmax)
            lmax = lsum;
    }
    //求横跨左右的最大连续子序列右半部分
    int rmax=a[m+1], rsum = 0;
    for (int i=m+1; i<=u; i++) {
        rsum += a[i];
        if (rsum > rmax)
            rmax = rsum;
    }
    //如果最大子序列跨越左半边和右半边的话,那么就是左半边的 lmax 和右半边的 rmax 的和。
    return max3(lmax + rmax, maxsequence2(a,1,m), maxsequence2(a,m + 1,u));
}


int main()
{

    int a[] = {-1, -2, -3, -4};
    cout << MaxSum(a,4) << endl;

    int b[10] = {1, -2, 3, 10, -4, 7, 2, -5};
    cout << MaxSum(b,8) << endl;
    cout << maxsequence2(b,0,8) << endl;

    return 0;
}

