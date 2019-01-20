/***********************************************************
* Author       : M_Kepler
* EMail        : hellohuangjinjie@gmail.com
* Last modified: 2016-03-31 10:05:54
* Filename     : lcs.cpp
* Description  : 最长公共子序列
* dp问题
*   longest comment string
*   C[i,j]=0                     if i=0 || j=0
*         =C[i-1,j-1]+1          if i,j>0 & xi = yj
*         =max{C[i,j-1],C[i-1,j])if i,j>0 & xi != xj
***********************************************************/

#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

void print(int **A, int m, int n, const string &x, const string &y);
int my_lcs(int **A, string s1, string s2);
int main()
{
    // string x;
    // string y;
    // cout<<"输入字符串"<<endl;
    // cin>>x;
    // cin>>y;

    string x = "huangxxxxjinjie";
    string y = "hellohuang000jinjiezzz";
    int m = x.size();
    int n = y.size();
    int **A = new int *[m + 1];
    for (int i = 0; i <= m; i++)
    {
        A[i] = new int[n + 1];
    }
    cout << my_lcs(A, x, y) << endl;
    print(A, m, n, x, y);
    cout << endl;
    //release：
    for (int i = 0; i <= m; i++)
    {
        free(A[i]);
    }
    free(A);
}
int my_lcs(int **A, string s1, string s2)
{
    int len1 = s1.size();
    int len2 = s2.length();
    //initialize array:
    for (int i = 0; i < len1; i++)
    {
        A[i][0] = 0;
    }
    for (int j = 0; j < len2; j++)
    {
        A[0][j] = 0;
    }

    for (int i = 1; i <= len1; i++)
    {
        for (int j = 1; j <= len2; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                A[i][j] = A[i - 1][j - 1] + 1;
            }
            else
            {
                A[i][j] = max(A[i - 1][j], A[i][j - 1]);
            }
        }
    }
    return A[len1][len2];
}
void print(int **A, int m, int n, const string &x, const string &y)
{
    if (m == 0 || n == 0)
    {
        return;
    }
    if (x[m - 1] == y[n - 1]) //必须用递归，不然是倒序的，从A[m][n]开始向前
    {
        print(A, m - 1, n - 1, x, y);
        cout << x[m - 1] << " ";
    }
    else if (A[m - 1][n] >= A[m][n - 1])
    {
        print(A, m - 1, n, x, y);
    }
    else
    {
        print(A, m, n - 1, x, y);
    }
}
