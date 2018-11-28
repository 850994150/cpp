/***********************************************************
* Author       : M_Kepler
* EMail        : hellohuangjinjie@gmail.com
* Last modified: 2016-03-31 09:47:55
* Filename     : 最长回文子串
* Description  : test_file

===================== manacher算法 ========================
  思想:
  把奇数,偶数的回文串一起考虑了,每两个相邻字符中间插入
  一个不曾出现的分隔字符,这样回文串长度就都变奇数了.
  借用一个辅助数组P[id]来记录以str[id]为中心的回文串对折
  后的长度(包括P[i]).
  原串: 12212321
  新串: # 1 # 2 # 2 # 1 # 2 # 3 # 2 # 1 #
  P[i]: 1 2 1 2 5 2 1 4 1 2 1 6 1 2 1 2 1
  P[id]-1 是该回文子串在原串中的长度(包括'#'),所以最大的
  P[id]-1 既为所求。
  问题:
  怎么求P[i],怎么利用P[i]求下一个P[i]?
  引入两个辅助变量:id(扩展串的元素下标) 和 mx=id+P[id]
  mx 是以id为中心的最长子串的边界(不包含mx),
  关键点:
  如果 mx>i 那么 P[i] >= min(P[2*id-i], mx-i)
  .......................这个是怎么得到的呢?......................
  if mx-i>P[j] then 可以知道,分别以P[i]和P[j]为中心的串
  一定包含在以P[id]为中心的回文串中,且这两个串相等

  elif mx-i<P[i] then 以s[j]为中心的回文串已经超出以s[id]
  为中心的回文串串了,但是可以知道j到mx这一段半径的回文串
  是包含在里面的,而超出部分只能老老实实去匹配了.

  elif mx<i 这就无法去对P[i]做假设了,只能P[i]=1.
  fi
  j = 2*id-i;即j是i关于id的对称点
  复杂度:
  O(n)
  ===========================================================*/

#include <iostream>
using namespace std;
char s[200002];
char str[400010];
int p[400010];
int min(int a, int b)
{
    return a < b ? a : b;
}
//设置新串
int pre()
{
    int i, j = 0;
    str[j++] = '$';
    for (i = 0; s[i]; i++)
    {
        str[j++] = '#';
        str[j++] = s[i];
    }
    //在末尾放完#后放了个\0
    str[j++] = '#';
    str[j] = '\0';
    return j;
}
void longestPald_manacher(int n)
{
    int mx = 0, id, i;
    p[0] = 0;
    for (i = 1; i < n; i++)
    {
        if (mx > i)
            p[i] = min(mx - i, p[2 * id - i]);
        else
            p[i] = 1;
        while (str[i - p[i]] == str[i + p[i]])
            p[i]++;
        if (p[i] + i > mx) {
            mx = p[i] + i;
            id = i;
        }
    }
}
int main(int argc, char const *argv[])
{
    while (cin >> s)
    {
        int n = pre();
        longestPald_manacher(n);
        int ans = 0, i;
        for (i = 1; i < n; i++)
            if (p[i] > ans)
                ans = p[i];
        cout << ans - 1 << endl;
    }
    return 0;
}
