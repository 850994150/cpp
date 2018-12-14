/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2018-12-14 15:58:09
 * Filename     :
 * Description  :
 * 僵尸进程: 父进程还在运行, 而子进程挂了, 但父进程没有使用wait来清理子进程的进程信息
    * 导致子进程虽然运行实体已消失, 但是仍在黑河进程表中占有数据, 造成资源浪费
    * wait
        * 主进程阻塞, 随便一个子进程结束就停止阻塞
    * waitpid
        * 非阻塞, 当需要用轮询的方式监控子进程
    * signal √
        * 其实是子进程退出时会给父进程一个信号, signal里用wait或waitpid都是非阻塞的
        * 只要父进程还在就都会监测子进程信号, 可以把所有子进程都回收
 * 
 * 孤儿进程: 子进程还在运行, 而父进程挂了, 子进程将由init进程收养
 * 
 ***********************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <sys/wait.h> // wait()

#include <unistd.h>
#include <sys/types.h>

const int SUB_PROCESS_NUM = 3;

void SignalHandler(int signal)
{
    int stat;
    pid_t sub_pid;
    if (wait(&stat))
    {
        printf("【Handler - wait】 get sub process exited signal!, status:%d\n", stat);
    }
    /*
    while((sub_pid = waitpid(-1, &stat, WNOHANG)) > 0)
    {
       printf("【Handler - waitpid】get sub process %d exited signal!\n", sub_pid);
    }
    */
}

int zombie()
{
    
    int status;
    
    // 3. signal 防止僵尸进程
    signal(SIGCHLD, SignalHandler);

    for(size_t i = 0; i < SUB_PROCESS_NUM ; i++)
    {
        status = fork();
        if (status == 0 || status == -1) break;
    }
    if (status == -1)
    {
        // error	
        printf("fork error\n");
    }
    else if (status == 0)
    {	
        // sub process
        printf("sub process pid is: %d\n", getpid());
        sleep(5);
        // 子进程先于父进程结束, 父进程没有对子进程做【清理工作】
        printf("sub process exited! pid = %d, ppid=%d\n", getpid(), getppid());
        exit(0);
    }
    else
    {
        // parent process
        
        printf("parent job 1:  process pid is: %d\n", getpid());

        // 避免僵尸进程

        // 1. pid_t wait(int* status)
        /*
        // sleep(10);
        if (wait(NULL)) // 阻塞在这里
        {
            printf("【wait】 get sub process exited signal!\n");
        }
        */

        // 2. pid_t waitpid(pid_t pid, int* status, int options)
        /*
        pid_t sub_pid;
        int stat;
        sleep(10);
        // while((sub_pid = waitpid(-1, &stat, WNOHANG)) > 0)
        //    printf("【waitpid】 get sub process %d exited signal!\n", sub_pid);

        do
        {
            sub_pid = waitpid(-1, &stat, WNOHANG);
            if (sub_pid == 0)
            {
                printf("no sub process exited! par process do something...\n");
                sleep(1);
            }
            else
            {
                printf("【waitpid】 get sub process %d exited signal:%d!\n", sub_pid, stat);
            }
        } while (sub_pid > 0);
        // 如果是 ==0 则是随便一个子进程结束, 循环就介素, > 0 会轮询所有子进程, 把所有子进程都回收
        */

        printf("parent job 2:  process pid is: %d\n", getpid());

        // 3. signal
        while(1)
        {
            printf("parent do something ... \n");
            sleep(1);
        }


        printf("par process exited!\n");
    }
    return 0;
}

int orphan()
{
    pid_t id = fork();
    
    if (id == -1)
    {
        printf("error while fork\n");
    }
    else if(id == 0)
    {
        // sub process
        printf("【sub process】 pid is: %d, par process pid is :%d\n", getpid(), getppid());
        sleep(2);
        printf("【sub process】 pid is: %d, par process pid is :%d\n", getpid(), getppid());
        printf("【sub process】 exited\n");
        exit(0);
    }
    else
    {
        // par process
        printf("【parent process running..., pid: %d】\n", getpid());
        sleep(1); // 父进程睡眠1s后退出, 此时子进程还没执行完
        printf("【parent process】 is exited\n");
        // 父进程先退出后, 孤儿进程被init进程收养, 所以此时子进程的父进程id=1
    }
    return 0;
    
}

int main(int argc, char const *argv[])
{
    zombie();

    // orphan();

    return 0;
}

