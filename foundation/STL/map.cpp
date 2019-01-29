/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2018-08-03 16:33:25
 * Filename     : map.cpp
 * Description  : map和unordered_map使用方法一样,内部实现不一样
 * https://www.cnblogs.com/fnlingnzb-learner/p/5833051.html
 ***********************************************************
 */
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;

int main( int argc, char **argv )
{

    // unordered_map<int, string> mapStudent;
     map<int, string> mapStudent;
    // mapStudent={{11,"11"}, {12, "12"}};
    //
    // 返回map的迭代器和插入是否成功bool
    pair<map<int, string>::iterator, bool> InsertPair;

    printf( "\n--------------------------------\n" );
    printf( "------------- 插入 -------------\n" );
    printf( "--------------------------------\n" );
    for ( int i = 0; i < 4; ++i )
    {
        // 插入方法1
        InsertPair=mapStudent.insert(pair<int, string>(i, "M_Kepler"));
        if(InsertPair.second == false)
        {
            cout<<"Insert error"<<endl;
        }
    }

    // 插入方法2
    
    for ( int i = 7; i < 10; ++i )
    {
        mapStudent.insert(map<int, string>::value_type(i, "M_Kepler"));
    }

    // 插入方法3 数组的方式
    // 前两种方式插入数据涉及集合唯一性的概念， 即如果已存在，不会再插入
    // 而数组的方式则会覆盖该关键字原本对应的值
    mapStudent[4] = "M_Kepler";
    mapStudent[5] = "M_Kepler";
    mapStudent[6] = "M_Kepler";


    printf( "\n--------------------------------\n" );
    printf( "------------- 遍历 -------------\n" );
    printf( "--------------------------------\n" );

    // 方法一：迭代器
    map<int, string>::iterator iter;
    for ( iter = mapStudent.begin(); iter != mapStudent.end(); ++iter )
    {
        // first表示key， second表示数据
        cout<<iter->first<< ' ' << iter->second <<endl;
    }

    int mSize = mapStudent.size();

    cout << endl << "map size " << mSize << endl << endl;

    // 方法二：反向迭代器
    map<int, string>::reverse_iterator riter;

    for ( riter = mapStudent.rbegin(); riter != mapStudent.rend(); riter++ )
    {
        cout << riter->first<< ' ' << riter->second <<endl;
    }

    // 方法三：数组的方式
    for ( int i = 0; i < mSize; ++i )
    {
        cout<<i<< ' ' << mapStudent[i]<<endl;
    }
    
    printf( "\n--------------------------------\n" );
    printf( "------------- 查找 -------------\n" );
    printf( "--------------------------------\n" );
    // find函数如果找到，返回数据所在位置的迭代器;
    // 如果没找到，返回的迭代器等于end函数返回的迭代器
    map<int, string>::iterator fiter, end;
    fiter = mapStudent.find(100);
    end = mapStudent.end();
    // unordered_map: if(mapStudent.find(100) != mapStudent.end())
    if ( fiter != end )
    {
        cout << fiter->first<< ' ' << fiter->second <<endl;
    }
    else
    {
        printf( "Not Found" );
    }

    printf( "\n--------------------------------\n" );
    printf( "------------- 删除 -------------\n" );
    printf( "--------------------------------\n" );
    mapStudent.clear();

    return 0;
}
