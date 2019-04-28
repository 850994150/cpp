/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2019-04-28 09:48:12
 * Filename     : binSearch.cpp
 * Description  : 分治算法 - 二分查找
 ***********************************************************
 */

#include <iostream>
using namespace std;

int binSearch(int array[], int target, int len)
{
    int low = 0;
    // XXX 这个len不可以在函数内部通过sizeof(array)/sizeof(array[0])来计算, 因为数组已经退化为指针了
    int hight = len - 1;
    while (low <= hight)
    {
        int mid = (low + hight) / 2; //取中间值mid点位置
        if (array[mid] == target)    //寻找到目标数
            return mid;
        if (array[mid] > target) //如果中间值大于目标数，则将highr点位置移动mid位置左边
            hight = mid - 1;
        if (array[mid] < target) //如果中间值小于目标数，则将low点位置移动mid位置右边
            low = mid + 1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int len = sizeof(array) / sizeof(array[0]);
    int key = 5;
    cout << binSearch(array, key, len) << endl;

    return 0;
}
