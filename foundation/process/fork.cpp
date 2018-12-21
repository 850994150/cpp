/***********************************************************
* Author       : M_Kepler
* EMail        : m_kepler@foxmail.com
* Last modified: 2018-12-17 09:10:30
* Filename     : fork.c
* Description  : fork大于0的返回值实际上是子进程的进程编号 
* 进程创建个数(特别是fork在循环里的时候)
* 怎么fork多个子进程?
**********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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

/*
 * @brief   : 循环里fork时进程数量和关系
 * 
 * 运行结果:
 main process pid():291
 i       son/pa  ppid    pid     fpid
 0       parent     4     291     292
 0       child    291     292       0
 1       parent   291     292     293
 1       child    292     293       0
 1       parent     4     291     294
 1       child    291     294       0
 
 * 分析
 291 --------> fork1: 291、292

 291 --------> fork2: 291、294
 292 --------> fork2: 292、293

 for    i = 0           i = 1           i = 2
        father(291)     father(291)     father
                                        son
                        son(294)        father
                                        son
        son(292)        father(292)     father
                                        son
                        son(293)        father
                                        son
 * 总结: 
    * 父子进程各占一半
    * 创建父/子进程数都是: 1 + 2 + 4 + ... + 2^(n-1); 结果是等比数列前n项和 a1(1-q^n) / 1-q
 * @return	: 
 */
int fork2(int n)
{
   int i = 0;
   printf( "main process pid():%d\n", getpid() );
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

/*
 * @brief	: fork的理解和逻辑运算符特点
 * command1 && command2 || command3 运算顺序从左到右
 * 加个括号就清楚了( (command1 && command2) || command3 )
 * 再结合fork返回值大于等于0确定command的真假就可以
 * @return	: 
 */
int fork3()
{
    fork();
    fork() && fork() || fork();
    fork();
    printf("+\n");
    return 0;
}

/*
 * @brief	: 所有子进程都有一个父进程创建
 * @param	: 
 * @return	: 
 */
int fork4(int num = 4)
{
    int status, i;	
    for (i = 0; i < num; i++)
    {
        status = fork();
        // 每次循环时，假设发现是子进程就直接从创建子进程的循环中跳出来
        // 不让你进入循环，这样就保证了每次仅由父进程来做循环创建子进程的工作	
        // 直接fork() 2次的话, 最终会产生4个进程, 其中3个子进程
        if (status == 0 || status == -1) break;
    }
    if (status == -1)
    {
        printf("fork error\n");
    }
    else if (status == 0)
    {
        // every sub process will execute
        // 每次fork完成i会加一, 所以这里i就是要处理的那个文件的编号
        printf("sub process %d exited \t par process is: %d\ti = %d\n", getpid(), getppid(), i);
        exit(0);
    }
    else
    {
        // parent process
        printf("par process:%d\t i = %d\t\n", getpid(), i);
    }
    return 0;
}

int main( int argc, char **argv )
{
    // fork1();
    // fork2(atoi(argv[1]));
    fork3();
    // fork4();
    return 0;
}


