/***********************************************************
* Author       : M_Kepler
* EMail        : m_kepler@foxmail.com
* Last modified: 2018-07-02 15:55:11
* Filename     : heapStack_area.cpp
* Description  :
* new 和 malloc
* free 指针
* 自由存储区和堆区
************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

char *get_str()
{
    string ttmp = "asdfghjkl";
    // str分配在栈区，程序运行完就被释放了
    char *str = (char*)ttmp.c_str();
    return str;
}

char * get_str2()
{
    // new/delete
    /* c++ 的操作符
     * 操作符可重载
     * 自由存储区分配内存: 自由存储区包含但不限于堆区
     *     因为new可以被重载，改用其他内存存储
     * 自动计算所需大小,返回指定类型的指针
     * 内存申请失败会报异常
     * 内存释放: delete []ptr;
     */
    char* tmp = new char [100]; // 分配的大小为:sizeof(char) * 100

    // malloc/free
    /* C 的库函数
     * 堆区分配内存
     * 自己计算所需大小，返回 void *类型的指针, 需要强转为所需类型的指针
     * 内存分配失败，会返回 NULL
     * 内存释放 free(ptr);
     */

    // 堆区  分配100个char型的存储单元
    // char* tmp = (char *)malloc(sizeof(char)*100);

    // 在不同的编译环境, new失败后不会抛出异常,而是返回NULL,所以加个判断是为了更好兼容
    if(tmp == NULL)
    {
        printf( "申请内存失败" );
        return NULL;
    }
    strcpy(tmp,"asdfghjkl");
    return tmp;
}

int main(int argc, const char *argv[])
{
    /* 栈区 */
    cout<< "--------------栈区---------------"<<endl;

    // get_str()运行完毕，str空间自动回收，str的空间内容未知，可能还保留着原来的内容，有可能是乱码
    char buf[128] = {0};
    strcpy(buf, get_str());
    printf("buf = %s\n", buf); // 乱码，不确定

    char* p = NULL;
    p = get_str();
    printf("p = %s\n", p); // 乱码，不确定


    /* 堆区 */
    cout<< "--------------堆区---------------"<<endl;

    char * q = NULL;
    q = get_str2();
    // 释放内存
    delete []q;

    /*
    if(q!=NULL)
    {
        printf("q = %s\n", q);
        free(q);
        q = NULL;

        // 错误 https://zhidao.baidu.com/question/339553907.html
        // 释放空间，只是做个标志，表示p所在的空间可以被其他进程使用了
        // 没释放之前，使用权是当前进程的；而且还需把指针p赋为NULL
        // https://zhidao.baidu.com/question/577455633.html
        // 下面这个写法是错的：野指针
        // if(p!=NULL)
        // {
        //    free(p);
        // }
    }
    */

    cout << "释放内存后: " << &q << "\t" << q << endl;
    printf( "堆栈的增长方向：栈是低地址向高地址增长" );
    return 0;
}


