/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2018-08-05 12:19:12
 * Filename     : io.cpp
 * Description  :
 * c++中对文件的操作主要运用了**文件流fstream**（即非标准的输入输出）的思想;
 * 文件的操作是通过类对象来调用方法完成的
 * 
 * ofstream: 输出, 从内存到硬盘
 * ifstream: 输入, 从硬盘到内存
 *
 ***********************************************************
 */

#include <iostream>
#include <fstream> //含文件流操作头文件
#include <stdlib.h>
using namespace std;
int main()
{
    int a, mymax = -9999;
    ofstream outfile("myfile.dat", ios::out); //创建写文件对象
    if (!outfile)                             //判断文件打开是否成功
    {
        cerr << "open wrong!\n";
        exit(1);
    }
    for (int i = 0; i < 10; i++) //向文件写入数据
    {
        cin >> a;
        outfile << a << endl;
    }
    outfile.close();                        //关闭文件
    ifstream infile("myfile.dat", ios::in); //创建文件读对象
    if (!infile)                            //判断文件打开是否成功</span>
    {
        cerr << "open wrong\n";
        exit(1);
    }
    while (infile >> a) //读取文件的数据
    {
        if (mymax < a) //找出文件数据中的最大者
            mymax = a;
    }
    cout << "Max=" << mymax << endl; //输出最大者
    infile.close();                  //关闭文件
    return 0;
}
