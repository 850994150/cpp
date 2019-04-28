/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2019-04-24 13:40:39
 * Filename     : memleak.cpp
 * Description  : valgrind 内存泄漏工具检测
 *                g++ -g memleak.cpp -o memleak
 *                valgrind --leak-check=full ./memleak
 ***********************************************************
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const int Num = 20000000;
typedef struct stBigMemory
{
    int mem[Num];
} *pBigMemory;

void checkMemLeak()
{
    pBigMemory p_stBigMemory = NULL;
    while (1)
    {
        // ps aux
        // VSZ 虚拟内存
        p_stBigMemory = (pBigMemory)malloc(sizeof(struct stBigMemory));

        // RSS 实际分配内存
        for (size_t i = 0; i < Num; i++)
        {
            p_stBigMemory->mem[i] = 1;
        }

        // free(p_stBigMemory);
        usleep(5 * 1000);
    }
}

/*
 * @function: 几种内存问题
 * @brief	: 
 * @param	: 
 * @return	: 
 */
void checkAllKinds()
{
    // 内存越界 invalid write of size
    char *ptr = (char *)malloc(10);
    ptr[14] = 'a';

    // 内存覆盖 overlap
    memcpy(ptr + 1, ptr, 5);
    // memmove(ptr + 1, ptr, 5); // 没内存覆盖

    // 数组越界
    char a[10];
    a[12] = 'i'; 

    // 重复释放 invalid free
    free(ptr);
    free(ptr);

    // 使用未初始化内存 use of uninitialised value
    // 导致了core dump
    char *p1;
    *p1 = '1';
}

int main(int argc, char *argv[])
{
    // checkMemLeak();
    // printf("%d bytes\n", sizeof(struct stBigMemory));
    checkAllKinds();
    return 0;
}

