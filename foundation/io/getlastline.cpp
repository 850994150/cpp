/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2018-08-20 14:06:33
 * Filename     : getlastline.cpp
 * Description  : 
 * 功能: 获取file_name文件最后num行
 * 使用: [exec.out] file_name num
 ***********************************************************
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
using namespace std;

// new
void TailLine(ifstream &file, int iLineNum, vector<string>& vecRetStr)
{
    int i;
    string strLine;
    streampos nCurentPos;

    if (!file)
    {
        cout << "获取文件最后" << iLineNum << "行失败" << endl;
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
}

// old
// 这个好像是unix和windows下执行结果不一样的
void readback(string filename, int lineCount)
{
    std::ifstream  fin(filename.c_str(), std::ios::ate );
    if( !fin )
    {
        cerr<<"打开日志文件失败！";
    }

    // 先倒回文件末尾两个字符
    fin.seekg(-2, fin.cur);
    // 假定反向读取100行记录
    for(int i = 0; i < lineCount; i++)
    {       
        // 查看前一个字符是否为回车符
        while( fin.peek() != fin.widen('\n') )
        {
            fin.seekg(-1, fin.cur );
        }
        // 走到这里表示跳过一行了，所以继续跳直到够100行
        fin.seekg(-1, fin.cur);
    }

    fin.seekg(2, fin.cur);
    // 现在文件指针指向99行的末尾，可以读取了
    vector<string> result;
    std::string  line;
    while( getline(fin, line) )
    {
        cout <<"新入一行 : " << line << endl;
        result.push_back( line );
    }
    fin.clear();
    fin.close();
    // </string>
}

int main( int argc, char **argv )
{
    std::ifstream file(argv[1], std::ios::ate );
    // readback(argv[1], atoi(argv[2]));
    vector<string> vecRetStr;
    TailLine(file, atoi(argv[2]), vecRetStr);
    for(auto itor : vecRetStr)
    {
        cout << itor <<endl;
    }
    return 0;
}

// g++ --std=c++11 getlastline.cpp -o getlastline.out

