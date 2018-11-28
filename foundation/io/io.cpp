/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2018-08-05 12:19:12
 * Filename     : io.cpp
 * Description  :
 * ofstream: 输出, 从内存到硬盘
 * ifstream: 输入, 从硬盘到内存
 * <<: 插入器, 向流输出数据;
 *     比如 cout << "Hello"; 把字符串输出到标准输出流cout
 * >>: 析取器, 向流中输入数据;
 *     比如 cin >> x;
 *
 ***********************************************************
 */

#include <iostream>
#include <fstream>
#include <unordered_map> // c++11 require
#include <time.h> 
#include <cstring>
#include <thread>
using namespace std;

int main( int argc, char **argv )
{
    const char* filename = "test.txt";
    ifstream file;
    file.open(filename, ios::binary | ios::in);
    if ( !file )
    {
        cout << "Error: file \"" << filename << "\" open fail" << endl;
    }

    return 0;
}



