/***********************************************************
* Author       : M_Kepler
* EMail        : m_kepler@foxmail.com
* Last modified: 2018-07-01 13:19:58
* Filename     : sys3.c
* Description  : 创建一个进程,父进程向子进程发送一个信号,然后
*                等待子进程终止;子进程接收信号,输出自己的状态
*                信息,最后终止自己
**********************************************************/

#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main( int argc, char **argv )
{
    pid_t pid;
    int fd;
    char * buf1 = (char*) malloc(20);
    char * buf2 = (char*) malloc(20);
    strcpy(buf1, "This is child process\n");
    strcpy(buf2, "This is parent process\n");
    fd = open("sys3_file.txt", O_CREAT|O_RDWR);
    pid = fork();
    if (fd < 0)
    {
        printf( "open file error" );
    }
    if (pid == 0)
    {
        if(write(fd, buf1, strlen(buf1)) < 0)
        {
            printf( "write error" );
        }
        exit(0);
    }
    else
    {
        if(write(fd, buf2, strlen(buf2)) < 0)
        {
            printf( "write error" );
        }
        exit(0);
    }
    close(fd);
    wait(NULL);
    printf( "ppid:%d", getppid());
    return 0;
}

