/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2018-08-05 12:19:12
 * Filename     : io.cpp
 * Description  :
    * c++中对文件的操作主要运用了**文件流fstream**（即非标准的输入输出）的思想
    * 文件的操作是通过类对象来调用方法完成的
    * 
    * ofstream: 输出, 从内存到硬盘
    * ifstream: 输入, 从硬盘到内存
    *
 ***********************************************************
 */
#include <vector>
#include <iostream>
#include <fstream> //含文件流操作头文件
#include <stdlib.h>
using namespace std;

/*
 * @brief       获取文件最后n行(兼容单行和行尾有空行的情况)
 * @param[in]   file			已打开的文件
 * @param[in]   iLineNu			需要获取的行数
 * @param[in]	vector<string>&	保存了从后往前的n行的vector
 * @return      错误码
 */
int TailLine(ifstream &file, int iLineNum, vector<string>& vecRetStr)
{
    int i;
    string strLine;
    streampos nCurentPos;

    if (!file)
    {
        return -1;
    }

    // file.seekg(-2, file.cur);
    file.seekg(-2, ios::end); //倒回最后两个字符处

    for (i = 0; i < iLineNum; i++)
    {
        while (file.peek() != file.widen('\n'))
        {
            nCurentPos = file.tellg();
            if (nCurentPos == 0)
            {
                break;
            }
            file.seekg(-1, file.cur);
        }
        //读到"\n"标识 ，表示已经有一行了
        if (nCurentPos != 0)//倒回文件的开头，停止倒退
        {
            file.seekg(-1, file.cur);
        }
        else
        {
            break;
        }
    }
    if (nCurentPos != 0)
    {
        file.seekg(2, file.cur);
    }

    while (getline(file, strLine))
    {
        vecRetStr.push_back(strLine);
    }
    return 0;
}

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
