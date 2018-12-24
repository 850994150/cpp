/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2018-12-21 14:24:51
 * Filename     : semaphore.cpp
 * Description  : 进程同步与互斥(信号量)
     * 保护共享资源, 确保资源在一个时刻只有一个进程独享
     * (多进程中全局变量起不到作用是否可通过信号量来完成?)
 ***********************************************************
 */

#include "sem_common.h"
#include <unistd.h>
#include <sys/types.h>

int main()
{
    int semid = CreatSemid(1);
    printf("%d\n", semid);
    InitSem(semid, 0, 1); // 初始化/获取信号量id
    pid_t id = fork();
    if (id == 0)
    {
        //child
        int semid = GetSemid(0);
        while (1)
        {
            P(semid, 0, -1); // P 操作
            printf("A");
            fflush(stdout);
            usleep(10000);
            printf("A");
            fflush(stdout);
            usleep(20000);
            V(semid, 0, 1); // V 发送信号
        }
    }
    else
    {
        //father
        while (1)
        {
            P(semid, 0, -1);
            usleep(30000);
            printf("B");
            fflush(stdout);
            usleep(8000);
            printf("B");
            fflush(stdout);
            usleep(20000);
            V(semid, 0, 1);
        }
        if (waitpid(id, NULL, 0) < 0)
        {
            perror("waitpid");
            return -1;
        }

    }
    Destory(semid); // 这里销毁有问题的,死循环的程序直接ctrl+c结束的话, 信号量还是存在,再次运行这个程序就会报错
    // 可以通过ipcs -s 查看信号量, 通过ipcrm -s xxxid 删除
    return 0;
}

// g++ -o semaphore.out sem_common.cpp semaphore.cpp
