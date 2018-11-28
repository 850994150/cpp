/***********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2018-07-04 18:33:20
 * Filename     : sys6.c
 * Description  :
 * 首先建立一个守护进程，然后让该守护进程每隔10s在/tmp/dameon.log中写入一句话
 **********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define MAXFILE 65535

int main(void)
{
    pid_t p;
    int i,fd,len;
    char *buf="This is a Dameon\n";
    len=strlen(buf);
    p=fork();
    if(p<0)
    {
        printf("error fork\n");
        exit(1);
    }
    else if(p>0)
        exit(0);
    setsid(); //为新进程创建一个回话
    chdir("/tmp"); //
    umask(0);
    for(i=0;i<MAXFILE;i++)
        close(i);

    if((fd=open("dameon.log",O_CREAT|O_WRONLY|O_TRUNC,0600))<0)
    {
        perror("open:");
        exit(1);
    }else
    {
        while(1)
        {

            if(write(fd,buf,len)<=0)
            {
                perror("write error:");
                exit(1);
            }   
            sleep(10);
        }
    }
    return 0;
}

