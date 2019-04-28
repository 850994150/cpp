/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2019-04-28 14:04:34
 * Filename     : bitOpera.cpp
 * Description  : 位操作
 ***********************************************************
 */
 
#include <iostream>
#include <climits>
using namespace std;

// 计算x二进制中1的数目
int count1num(int x)
{
    int countx = 0;
    while (x > 0)
    {
        countx++;
        x = x & (x - 1); // 用来消除最后的1
    }
    return countx;
}

/*
 * @function: 判断是否是2的幂
 * @brief	: 如果是2的幂次，如4对应二进制为(100)2，肯定是只有一个1
 *            所以统计二进制中1的个数，看是否只有一个
 * @param	: 
 * @return	: 
 */
bool isPowerOfTwo(int x)
{
    int cnt = 0;
    /*
    while (x > 0)
    {
        cnt += (x & 1);
        x >>= 1;
    }
    return cnt == 1;
    */
    return count1num(x) == 1;
}

/*
 * @function: 判断是否是2的幂
 * @brief	: 如果是2的幂次，如4对应二进制为(100)2，肯定是除了最高位其他都是0
 *            判断是否除了最高位外其他都是0的方法是判断 n 和 n-1 先与是否为0
 * @param	: 
 * @return	: 
 */
bool isPowerOfTwo2(int x)
{
    return(x > 0) && (!(x & (x - 1)));
}

/*
 * @function: 求数字范围内所有数据按位与的结果
 * @brief	: 只要找到所有数字中二进制的左边1的公共部分就可以了
 *            [26, 30]:
 *            26: 11010
 *            27: 11011
 *            28: 11100
 *            29: 11101
 *            30: 11110
 *            二进制公共部分是: 11000
 * @param	: INT_MAX是int类型的最大值，即32个1
 * @return	: 
 */
int rangeBitwiseAnd(int m, int n)
{
    int d = INT_MAX; // 头文件 #include <climits>
    while ((m & d) != (n & d))
    {
        d <<= 1; // 左移一位表示开始比对倒数的下一个二进制数 // 因为左移后末尾是0，任何数与0都为0
    }
    return m & d;
}

/*
 * @function: 求数字范围内所有数据按位与的结果
 * @brief	: [m,n]范围内如果除了开始的 m 以外的数据这种有2的幂的话，那么这个范围内所有数的与操作肯定是0
 *            为什么要除了 m 以外? 
 *                因为如果是[4,7]的话还是需要计算的 100 101 110 111
 *            为什么 m 以外是2的幂就肯定是0?
 *                假设 k∈(m,n] 且为2的幂，则 k 除了最高位外，其他位都是0，0与任何数都是0；又因为 [m,k)之间
 *                的数是小于 k 的，所以对应的二进制就要在前面补0，这个0刚好与k的最高位与计算后变为0了
 *                所以最终结果就是0
 *                如 [6, 10]
 *                   110
 *                   111
 *                  1000 (8为2的幂，所以前面小于8的高位补0, 变为0110，0111)
 *                  1001
 *                  1010
 * 
 *  但是怎么确定范围 [m, n] 内是否有2的幂呢？
 *     取n的最高位的1其他位均为0即可，比如 [6, 10] 10=(1010)2 即比n小的第一个2的幂为1000对应的十进制8>6，所以区间内肯定有2的幂
 *  那么怎么取一个数的最高位呢?
 *  TODO
 * 
 * @param	: 
 * @return	: 
 */
int rangeBitwiseAnd2(int m, int n)
{
    int d = INT_MAX; // 头文件 #include <climits>
    if (m / n >= 2)
    {
        return 0;
    }
    while ((m & d) != (n & d))
    {
        d <<= 1;
    }
    return m & d;
}

int main(int argc, char *argv[])
{
    int data = 99;
    char data_bin[10];

    printf("二进制中1的位数: \n");
    // scanf("%d", &data);
    // printf("十进制为:%d，八进制为:%o，十六进制为:%x，二进制为:%d", data, data, data, data);
    printf("%d\n", count1num(data));

    printf("是否是2的倍数: %d\n", isPowerOfTwo(data));

    printf("[26, 30] 区间范围内所有数相与的结果:%d\n", rangeBitwiseAnd(26, 30));

    return 0;
}