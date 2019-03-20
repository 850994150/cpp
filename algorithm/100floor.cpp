/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2019-03-20 15:11:46
 * Filename     : 100floor.cpp
 * Description  : 有一栋100层的大楼，该玻璃球从某一层楼扔下，刚好会碎。   
                  现给你两个球，问怎样找到在哪一层楼刚好会碎？
 https://blog.csdn.net/gendlee1991/article/details/52601484
 ***********************************************************
 */

#include <iostream>
using namespace std;
#define FloorNum 12 // 楼层数
int F[FloorNum] = {0};

void Floor()
{
    int temp;
    for (int loop1 = 2; loop1 < FloorNum; ++loop1)
    {
        F[loop1] = loop1;
        for (int loop2 = 1; loop2 < FloorNum; ++loop2)
        {
            temp = (loop2 >= (1 + F[loop1 - loop2])) ? loop2 : (1 + F[loop1 - loop2]);
            if (F[loop1] > temp)
            {
                F[loop1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    F[0] = 0;
    F[1] = 1;
    Floor();
    cout << F[FloorNum - 1] << endl;

    return 0;
}
