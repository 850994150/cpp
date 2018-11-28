/***********************************************************
* Author       : M_Kepler
* EMail        : hellohuangjinjie@gmail.com
* Last modified: 2018-07-02 09:35:35
* Filename     : sys2.c
* Description  : 利用fork创建子进程，父进程打开一个文件，父子
			 	 进程都向文件中写入信息(利用wait),表明是在哪个
				 进程中，每个进程都打印两个进程的ID号,最后父进
				 程执行wait()
***********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    pid_t pid;
    int fd;
    char *buf1=(char *)malloc(20);
    char *buf2=(char *)malloc(20);
    strcpy(buf1,"this is child process:\n");
    strcpy(buf2,"this is parent process:\n");

	fd=open("sys2_file.txt",O_CREAT|O_RDWR);
	pid = fork();
    if(fd < 0)
    {
        printf("open file error\n");
    }
    if(pid==0)
    {
        if(write(fd,buf1,strlen(buf1))<0)
        {
            printf("write error!\n");
            exit(0);
        }
        printf("pid:%d\n",getpid());
        close(fd);
    }
    else
    {
        if(write(fd,buf2,strlen(buf1))<0)
        {
            printf("write error!\n");
            exit(0);
        }
        close(fd);
        wait(0);
        printf("ppid:%d\n",getppid());
    }
    return 0;
}


