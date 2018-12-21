/***********************************************************
* Author       : M_Kepler
* EMail        : m_kepler@foxmail.com
* Last modified: 2018-07-01 13:10:18
* Filename     : ex8.c
* Description  : 创建子进程,让其子进程暂停5s(使用sleep函数)
* 接下来对原有的父进程使用waitpid函数， 并使用参数WNOHANG使该父进程不会阻塞。
* 若有子进程退出，则waitpid返回子进程号；若没有子进程退出，
* 则waitpid返回0,并且父进程每隔1s循环判断一次
**********************************************************/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int p,wp;
    p=fork();
    if(p<0)
    {
        printf("Error fork \n");
    }
    else if(0==p)
    {
        printf("i am child progress ,i am sleeping!\n");
        sleep(5);
        printf("e am the child progress , i am exit!\n");
        exit(0);
    }
    else
    {
        do
        {
            wp=waitpid(p,NULL,WNOHANG);
            if(0==wp)
            {
                printf("i am the father progress ,the child progress has not exit!\n");
                sleep(1);
            }
        }while(wp==0);
        if(p==wp)
        {
            printf("i am the father progress the child exit Pid:%d\n",p);
        }
        else
        {
            printf("some error occured\n");
        }
    }
    return 0;
}



