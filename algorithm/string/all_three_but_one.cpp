/***********************************************************
 * Author       : M_Kepler
 * EMail        : hellohuangjinjie@gmail.com
 * Last modified: 2016-03-31 09:45:01
 * Filename     : all_three_but_one.cpp
 * Description  : 其他数字都出现了3次，唯有一个数字只出现了一次
 * 思想:
 *   现有序列 6 3 6 1 3 6 3
 *   因只有一个数只出现1次，其他都出现3次，对应的位置的1的个数应可以被3整除
 *   而不是3的倍数的位置都填1得到的二进制数对应的数就是所求了
 *   对应的二进制为：110 011 110 001 011 110 011
 *   对应位相加得到：364    所以应该是：001
 *
 *第二种是位运算
 *   对于除出现一次之外的所有的整数，其二进制表示中每一位1出现的次数是3的整数倍
 *   将所有这些1清零，剩下的就是最终的数。
 *   用ones记录到当前计算的变量为止，二进制1出现“1次”（mod 3 之后的 1）的数位。用twos记录到当前计算的变量为止，二进制1出现“2次”（mod 3 之后的 2）的数位。当ones和twos中的某一位同时为1时表示二进制1出现3次，此时需要清零。即用二进制模拟三进制计算。最终ones记录的是最终结果。
 *   时间复杂度：O（n）
***********************************************************/

#include <iostream>
#include <memory.h>
using namespace std;

int singleNumber(int A[], int n);
int singleNumber2(int A[], int n);

int main()
{
    //int len =sizeof(s)/sizeof(s[0]);
    int s[]={2,2,4,5,2,8,7,7,8,7,8,4,4};
    cout<<"s=2,2,4,5,2,8,7,7,8,7,8,4,4"<<endl;
    int len =sizeof(s)/sizeof(int);
    cout<<singleNumber(s,len)<<endl;
    cout<<singleNumber2(s,len)<<endl;
    return 0;
}

int singleNumber(int A[], int n)
{
    int ones = 0, twos = 0, xthrees = 0;
    for(int i = 0; i < n; ++i)
    {
        twos |= (ones & A[i]);
        ones ^= A[i];
        xthrees = ~(ones & twos);
        ones &= xthrees;
        twos &= xthrees;
    }
    return ones;
}

int singleNumber2(int A[], int n)
{
    int bits[32];
    memset(bits, 0, 32*sizeof(int));
    int i=0, j=0;
    for (i=0; i<n; i++)
    {
        for(j=0; j<32; j++)
        {
            int k=(A[i]>>j) & 1;
            bits[j] += k;
        }
    }
    int res=0;
    for(j=0; j<32; j++)
    {
        if(bits[j]%3 !=0)
            res += (1<<j);
    }
    return res;
}
