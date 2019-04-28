/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2019-04-28 09:53:36
 * Filename     : test.cpp
 * Description  : 分治算法 - 全排列问题
 *                有数字1 2 3 4，输出这几个数字可能的所有排列方法
 ***********************************************************
 */
 
#include <iostream>
using namespace std;

void swap(int &a,int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void fullSort(int arr[], int start, int end)
{
    if (start == end)
    {
        for (int i = 0; i < 4; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
        return;
    }
    for (size_t i = start; i <= end; i++)
    {
        swap(arr[i], arr[start]);
        fullSort(arr, start + 1, end);
        swap(arr[i], arr[start]);
    }
}

int main(int argc, char *argv[])
{
    int arr[] = {1, 2, 3, 4};
    int len = sizeof(arr) / sizeof(arr[0]);
    fullSort(arr, 0, len - 1);
    return 0;
}
