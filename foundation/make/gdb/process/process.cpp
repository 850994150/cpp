#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
    pid_t pid = fork(); //创建子进程

    if(pid == -1)
    {
        perror("fork error");
        return -1;
    }
    else if(pid == 0) //child
    {
        printf("I am a child:my pid is %d,my father is %d\n",getpid(),getppid());
    }
    else //father
    {
        printf("I am a father:my pid is %d\n",getpid());
        wait(NULL);//等待子进程
    }
    return 0;
}
