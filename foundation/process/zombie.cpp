/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2018-12-17 09:59:12
 * Filename     : zombie.cpp
 * Description  :
 * 僵尸进程: 父进程还在运行, 而子进程挂了, 但父进程没有使用wait来清理子进程的进程信息
    * 导致子进程虽然运行实体已消失, 但是仍在黑河进程表中占有数据, 造成资源浪费
    * wait
        * 主进程阻塞, 随便一个子进程结束就停止阻塞
    * waitpid
        * 非阻塞, 但需要用轮询的方式监控子进程
    * signal √
        * 其实是子进程退出时会给父进程一个信号, signal里用wait或waitpid都是非阻塞的
        * 只要父进程还在就都会监测子进程信号, 可以把所有子进程都回收

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
    while((sub_pid = waitpid(-1, &stat, WNOHANG)) > 0) // WNOHANG 表示非阻塞模式
    {
       printf("【Handler - waitpid】get sub process %d exited signal!\n", sub_pid);
    }
    */
}

int zombie_wait()
{

    int status;

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

        sleep(10);
        // 进程一旦调用了wait，就立即阻塞自己，由wait自动分析是否当前进程的某个子进程已经退出,
        // 如果让它找到了这样一个已经变成僵尸的子进程, wait就会收集这个子进程的信息, 并把它彻底销毁后返回;
        // 如果没有找到这样一个子进程，wait就会一直阻塞在这里，**直到有一个出现为止**(所以是任何一个出现僵尸进程)
        if (wait(NULL))
        {
            printf("【wait】 get sub process exited signal!\n");
        }
        printf("par process exited!\n");
    }
    return 0;
}


int zombie_wait_pid()
{

    int status;

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
        printf("sub process done! pid = %d, ppid=%d\n", getpid(), getppid());
        exit(0);
    }
    else
    {
        // parent process

        printf("parent job 1:  process pid is: %d\n", getpid());

        // 避免僵尸进程


        // 2. pid_t waitpid(pid_t pid, int* status, int options)
        // 从本质上讲，系统调用waitpid和wait的作用是完全相同的，但waitpid多出了两个可由用户控制的参数pid和options
        // 从而为我们编程提供了另一种更灵活的方式。

        pid_t sub_pid;
        int stat;
        sleep(10);
        // while((sub_pid = waitpid(-1, &stat, WNOHANG)) > 0)
        //    printf("【waitpid】 get sub process %d exited signal!\n", sub_pid);

        do
        {
            sub_pid = waitpid(-1, &stat, WNOHANG);
            // >0   只等待进程ID等于指定进程号的子进程，不管其它已经有多少子进程运行结束退出了，只要指定的子进程还没有结束 waitpid就会一直等下去。
            // =-1  等待任何一个子进程退出，没有任何限制，此时waitpid和wait的作用一模一样。 　　
            // =0   等待同一个进程组中的任何子进程，如果子进程已经加入了别的进程组，waitpid不会对它做任何理睬。
            // <-1  等待一个指定进程组中的任何子进程，这个进程组的ID等于pid的绝对值

            if (sub_pid == 0)
            {
                printf("no sub process exited! par process do something...\n");
                sleep(1);
            }
            else if(sub_pid > 0)
            {
                printf("【waitpid】 get sub process %d exited signal:%d!\n", sub_pid, stat);
            }
        } while (sub_pid > 0);

        printf("parent job 2:  process pid is: %d\n", getpid());
        printf("par process exited!\n");
    }
    return 0;
}


int zombie_signal()
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
    zombie_wait();
    // zombie_wait_pid();
    // zombie_signal();

    // orphan();

    return 0;
}


// linux 下查看僵尸进程：
/*
$ ps -aux | grep Z

USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
m_kepler   289  0.0  0.0      0     0 tty1     Z    13:42   0:00 [a.out] <defunct>
m_kepler   290  0.0  0.0      0     0 tty1     Z    13:42   0:00 [a.out] <defunct>
m_kepler   291  0.0  0.0      0     0 tty1     Z    13:42   0:00 [a.out] <defunct>
m_kepler   293  0.0  0.0  13084   912 tty2     S    13:42   0:00 grep --color=auto Z
*/