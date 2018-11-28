/***********************************************************
* Author       : M_Kepler
* EMail        : m_kepler@foxmail.com
* Last modified: 2018-06-22 09:10:30
* Filename     : fork.c
* Description  : 子进程继承了父进程什么？
**********************************************************/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int fork1()
{
    int count = 0;
    printf("------------------\n");

    pid_t fpid = fork();
    if(fpid <0)
    {
        printf("ERROR IN FORK FUNC!");
    }
    else if(fpid == 0)
    {
        printf("pid:%d, I am the child process, my process id is %d, my parent process id is %d\n", fpid, getpid(), getppid());
        count++;
    }
    else
    {
        printf( "pid:%d, I am the parent process, my process id is %d, my parent process id is %d\n", fpid, getpid(), getppid());
        count++;
    }

    printf( "统计结果是：%d\n", count );
    return 0;
}

int fork2(int n)
{
   int i = 0;
   printf( "i\tson/pa\tppid\tpid\tfpid \n" );
   /*
     ppid 指向当前进程的父进程pid
     pid  指向当前进程的pid
     fpid 指向当前进程子进程pid
     创建的子进程数是 M = 2^0 + 2^1 + 2^2 + .... + 2^(N-1)
     可以看出 printf 函数的执行次数是 2 * M
   */
   for ( i = 0; i < n; i++ )
   {
       pid_t fpid = fork();
       if ( fpid==0 )
       {
           printf( "%d\tchild\t%4d\t%4d\t%4d\n", i, getppid(), getpid(), fpid );
       }
       else
       {
           printf( "%d\tparent\t%4d\t%4d\t%4d\n", i, getppid(), getpid(), fpid );
       }
   }
   return 0;

}

int fork3()
{
    fork();
    fork() && fork() || fork();
    fork();
    printf("+\n");
    return 0;
}

int main( int argc, char **argv )
{
    /* fork1(); */
    fork2(atoi(argv[1]));
    /* fork3(); */
    return 0;
}


