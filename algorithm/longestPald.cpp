/***********************************************************
* Author       : M_Kepler
* EMail        : hellohuangjinjie@gmail.com
* Last modified: 2016-03-31 10:29:52
* Filename     : longestPald.cpp
* Description  : 最长回文子串（另一个算法:manacher）

定义:
    比如：abcdedcb，它的回文子串有：a,ded,cdedc,bcdecdb,其中,
    bcdecdb是其中最长的那一个。我们要求输出并求出其长度
问题:
    1. 字符串是奇偶的影响:
        在manacher中就不必要考虑,在填补辅助字符后,全变为奇数了
    2. 相邻字符相同的影响:
        譬如aodeggeddjaf这样的,在用中心轴那个方法时考虑相邻两个
        字符一样的情况
解法:
    暴力,中心轴,DP,Mmanacher(上面的问题都得到解决)
***********************************************************/

#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;
#define maxLen 100
#include <math.h>
#define max 1
/*======================= 穷举法 ============================
思路:
    1:判断一个串是不是回文串,
    2:调用这个判断函数,对所有子串进行校验
复杂度:
    O(n^3)
===========================================================*/
int isPalindrome(char *str, int begin, int end)
{
    //判断str[i..j]是否为回文串
    while (str[begin] == str[end] && begin <= end)
    {
        begin++;
        end--;
    }
    if (str[begin] != str[end])
        return 0;
    else
        return 1;
}
int longestPald_enum(char *str)
{
    int len = strlen(str);
    int i, j;
    int longest = 1;
    assert(str != NULL);
    if (len == 1)
        return 1;
    for (i = 0; i < len; i++)
    {
        for (j = i + 1; j < len; j++)
        {
            if (isPalindrome(str, i, j))
                longest = (longest < j - i + 1 ? j - i + 1 : longest);
        }
    }
    return longest;
}
/*======================= 中心轴 ============================
思想:
    回文串是左右对称的，如果从中心轴开始遍历，会减少一层循环。
    依次以母串的每一个字符为中心轴，得到回文串；然后通过比较
    得到最长的那一个。
注意:
    要考虑到像baccab这样的特殊子串，可以理解它的中心轴是cc。
复杂度:
    时间复杂度:O(n^2).
    空间复杂度:O(1).
===========================================================*/
int lr(char *str, int mid)
{
    int l = mid - 1, r = mid + 1;
    int len = strlen(str);
    //处理出现abccda这种相邻字符相同的情况
    while (str[r] == str[mid])
        r++;
    while (l >= 0 && r < len && str[l] == str[r])
    {
        l--;
        r++;
    }
    return r - l - 1;
}
int longestPald_cent(char *str)
{
    int i;
    int len = strlen(str);
    int longest = 1;
    assert(str != NULL);
    if (len == 1)
        return 1;
    for (i = 0; i<len; i++)
    {
        //发现这里就像递归算斐波那契额一样,多计算了一次lr(str,i-1)的结果
        if (lr(str, i) > longest)
            longest = lr(str, i);
    }
    return longest;
}
/*======================== DP ==============================
DP法:
    自底向上,用c[i, j] = 1表示子串s[i..j]为回文子串.
递推式:
    c[i,j] = 1             ( c[i+1,j-1]=1 && s[i]=s[j] )
    c[i,j] = 0             ( s[i]≠s[j] )
初始态:
    c[i][i] = 1
    c[i][i+1] = 1          (s[i] == s[i+1])
复杂度:
    时间复杂度:O(n^2);
    空间复杂度:O(n^2).
===========================================================*/
void judeg(int begin, int end, char *str)
{
    int len = strlen(str);
    while (begin >= 0 && end <= len && str[begin] == str[end])
    {
        if (end - begin + 1 > max)
            max = end - begin + 1;
        begin--;
        end++;
    }
}
int longestPald_dp(char *str)
{
    int low, high;
    int len = strlen(str);
    for (int i = 1; i < len; i++)
    {
        low = i - 1;
        high = i;
        judeg(low, high, str);
        low = i - 1;
        high = i + 1;
        judeg(low, high, str);
    }
    return max;
}

//这个无论字符串长度的奇偶,在验证 aaaaaaaa 时得到错误的答案.
/*
int longestPald_dp(char * str)
{
    bool dp[maxLen][maxLen];
    int mx = 0;
    int str_begin = 0;
    int maxlen = 1;
    int length = strlen(str);
    for (int i = 0; i < length; ++i)
        dp[i][i] = 1;
    for (int len = 1; len <= length; ++len) //长度
    {
        for (int begin = 0; begin < length + 1 - len; ++begin)
        {
            int end = begin + len; // 从长度为2开始，首尾
            if ((str[begin] == str[end]) && (dp[begin + 1][end - 1] == 1))
            {
                dp[begin][end] = 1;
                if (end - begin + 1 > mx)
                {
                    mx = end - begin + 1;
                    str_begin = begin;
                }
            }
        }
    }
    return mx;
}
*/
/*===================== manacher算法 ========================
思想:
    把奇数,偶数的回文串一起考虑了,每两个相邻字符中间插入一个
    不曾出现的分隔字符,这样回文串长度就都变奇数了.
    借用一个辅助数组P[id]来记录以str[id]为中心的回文串的
    半径长度(包括P[i]).
    原串: waabwswfd
    新串: #w#a#a#b#w#s#w#f#d#
    P[i]: 1 2 1 2 3 2 1 2 1 2 1 4 1 2 1 2 1 2 1
    P[id]-1 就是该回文子串在原串中的长度(包括'#')
复杂度:
    O(n)
===========================================================*/
//manacher算法

int main()
{
    string str1 = "abcacba";
    string str2 = "abqcacbabg";
    string str3 = "abcaeacba";
    string str4 = "zqweobbjbod";
    string str5 = "qeweqm.mmoiadfsdwneenn";
    string str6 = "waabwswfd";//奇
    string str7 = "waeabwswfd";//偶
    char *a = _strdup(str2.c_str());
    cout << a << endl;
    cout << "longestPald_enum  " << longestPald_enum(a) << endl;
    cout << "longestPald_cent  " << longestPald_cent(a) << endl;
    cout << "longestPald_dp    " << longestPald_dp(a) << endl;
//    cout << "longestPald_dp2   " << longestPald_dp2(a) << endl;
    cout << endl;
    return 0;
}
