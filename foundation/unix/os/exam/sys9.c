/***********************************************************
* Author       : M_Kepler
* EMail        : m_kepler@foxmail.com
* Last modified: 2018-07-01 13:33:56
* Filename     : sys9.c
* Description  : 
* 首先使用fork创建一个子进程，接着为了保证子进程不在父进程调用kill之前退出
* 在子进程中使用raise函数向子进程发送SIGSTOP信号，使子进程暂停
* 接下来，再在父进程中调用kill向子进程发送信号，请使用SIGKIL
**********************************************************/

#include<stdio.h>
#include <signal.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    int ret,status;
    pid=fork();
    if (pid<0)
    {
        printf("Fork error\n");
        exit(1);
    }
    else if(pid==0)
    {
        printf("I am child progress(Pid:%d) I am waiting for signal\n",getpid());
        raise(SIGSTOP);
        printf("I am child progress (pid:%d) i am killed by (pid:%d) \n",getpid(),getppid());
        exit(0);
    }
    else
    {
        sleep(2);
        if(waitpid(pid,NULL,WNOHANG)==0)
        {
            if(ret=kill(pid,SIGKILL)==0)
            {
                printf("I am parent progress (pid:%d),i kill progress (pid:%d)\n",getpid(),pid);
            }
        }
        waitpid(pid, &status, 0);
        exit(0);
    }
    return 0;
}








