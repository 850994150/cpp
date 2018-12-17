/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2018-08-20 14:06:33
 * Filename     : customer.cpp
 * Description  : 
 * 功能: 读出文件内容, 若文件file_name有增长就输出最后一行
 * 使用: [exec.out] file_name
 ***********************************************************
 */

#include<iostream>
#include<fstream>
#include<string>
#include <unistd.h>

using namespace std;
static int last_position = 0; //记录当前已经处理掉的文件位置

void doSomething(string line)
{
    std::cout <<  line  << std::endl;
}


void find_last_line(ifstream &infile)
{
    infile.seekg(0, ios::end);
    int filesize = infile.tellg();
    for(int n = last_position; n < filesize; n++)
    {
        infile.seekg(last_position, ios::beg);
        string line;
        getline(infile, line);
        doSomething(line);      // 获取最新行的内容
        if(infile.tellg()>0)    // 这里必须加入这个判断，因为在频繁更新目标文件时，会导致该函数返回-1
        {
            n = last_position = infile.tellg();
        }
    }
}

int main(int argc, char *argv[])
{
    if(argc !=2 )
    {
        cout << "请输入待处理的文件. e.g.: ./main file"<<endl;
        return -1;
    }
    // int position = 0;
    while(true)
    {
        ifstream infile(argv[1]);
        find_last_line(infile);
    }
}

