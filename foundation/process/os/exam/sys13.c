#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int signo)
{
    printf("this is child process,pid=%d ,parent id=%d \n",getpid(),getppid());
    
}

int main() 
{ 
    int pid;
    pid=fork();
    if (pid<0)
    {
       perror("fork error");
    }else if(pid==0)
    {
       signal(SIGUSR1,handler);
       pause();
       printf("child process exit\n");
       exit(0);
    }
    else
    {
       int status;
       printf("this is parent process,pid=%d ,parent id=%d \n",getpid(),getppid());
       printf("waiting for child process exit\n");
       kill(pid,SIGUSR1);
       wait(&status);
       printf("the child process exit,the return status is 0x%x\n",status); 
       pause();
    }

    
    return 0; 
} 
