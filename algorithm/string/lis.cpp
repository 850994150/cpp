/***********************************************************
* Author       : M_Kepler
* EMail        : hellohuangjinjie@gmail.com
* Last modified: 2016-03-31 10:20:57
* Filename     : lis.cpp
* Description  : 最长递增子序列

==========================================================
LIS :O(n^2)和O(nlogn)
    状态转移方程为 dp[i] = max(dp[j]+1,1)
    a[j]（j<i）进行遍历 ，如果a[i]>a[j]，就使用状态转移方程。
    第i个元素自己成为一个上升的队列或者自己是子序列的最后一个元素
    ，或者是由于前面的a[j]<a[i]  所以在
    dp[j]的基础之上形成了dp[i] = dp[j]+1  但前提是a[i]>a[j]
==========================================================
1 dp
2 quicksort + lcs
3 quicksort + lcs

***********************************************************/
/*
//LIS一:dp
#include <iostream>
#include <string>
using namespace std;
int dp[31]; // dp[i]记录到[0,i]数组的LIS
int maxx =1;
int LIS(int *s, int n)
{
    for( int i=0; i<n; i++)
    {
        dp[i]=1;
        for(int j = 0; j < i; j++)
        {
            if(s[i] > s[j])
            {
                if(dp[i] < dp[j]+1)
                    dp[i] = dp[j]+1;
            }
        }
        if( dp[i] > maxx )
            maxx = dp[i];
    }
    return maxx;
}
void output(int *a,int n)
{
    for(int i=n;i>=0;i--)
    {
        if(dp[i] == maxx)
        {
            cout<<a[i]<<" ";
            maxx--;
        }
    }
}
int main()
{
    int arr[] = {1, -1, 2, -3, 4, -5, 6, -7};
    int len = sizeof(arr)/sizeof(int);
    cout<<LIS(arr,len)<<endl;
    output(arr,len);cout<<endl;
    return 0;
}

//============================================================================
// LIS二:quicksort + LCS
#include <iostream>
using namespace std;
void swap(int * arr, int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}
void qsort(int * arr, int left, int right)
{
    if(left >= right)    return ;
    int index = left;
    for(int i = left+1; i <= right; ++i)
    {
        if(arr[i] < arr[left])
        {
            swap(arr,++index,i);
        }
    }
    swap(arr,index,left);
    qsort(arr,left,index-1);
    qsort(arr,index+1,right);
}
int dp[31][31];
int LCS(int * arr, int * arrcopy, int len)
{
    for(int i = 1; i <= len; ++i)
    {
        for(int j = 1; j <= len; ++j)
        {
            if(arr[i-1] == arrcopy[j-1])
            {
                dp[i][j] = dp[i-1][j-1] + 1;
            }else if(dp[i-1][j] > dp[i][j-1])
            {
                dp[i][j] = dp[i-1][j];
            }else
            {
                dp[i][j] = dp[i][j-1];
            }
        }
    }
    return dp[len][len];
}
void main()
{
    int arr[] = {1,-1,2,-3,4,-5,6,-7};
    int arrcopy [sizeof(arr)/sizeof(int)];
    memcpy(arrcopy,arr,sizeof(arr));
    qsort(arrcopy,0,sizeof(arr)/sizeof(int)-1);
    // 计算LCS，即LIS长度
    int len = sizeof(arr)/sizeof(int);
    printf("%d\n",LCS(arr,arrcopy,len));
}
//============================================================================
*/

// LIS三:quicksort + LCS
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;
//设数组长度不超过 30
int cmp ( const void *a , const void *b )
{
    return *(int *)a - *(int *)b;  //升序排序
    //return *(int *)b - *(int *)a; //降序排序
    //关于qsort，一定要看看:qsort函数、sort函数 (精心整理篇)
}
int dp[31][31];
int LCS(int * arr, int * arrcopy, int len)
{
    for(int i = 1; i <= len; i++)
    {
        for(int j = 1; j <= len; j++)
        {
            if(arr[i-1] == arrcopy[j-1])
            {
                dp[i][j] = dp[i-1][j-1] + 1;
            }
            else if(dp[i-1][j] > dp[i][j-1])
            {
                dp[i][j] = dp[i-1][j];
            }
            else
            {
                dp[i][j] = dp[i][j-1];
            }
        }
    }
    return dp[len][len];
}
int main()
{
    int arr[] = {1,-1,2,-3,4,-5,6,-7,9};
    int len =sizeof(arr)/sizeof(int);
    int arrcopy [sizeof(arr)/sizeof(int)];
    memcpy(arrcopy,arr,sizeof(arr));
    qsort(arrcopy,len,sizeof(arr[0]),cmp);
    //计算LCS，即LIS长度
    cout<<LCS(arr,arrcopy,len)<<endl;
    return 0;
}
