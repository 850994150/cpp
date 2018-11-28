/***********************************************************
* Author       : M_Kepler
* EMail        : m_kepler@foxmail.com
* Last modified: 2018-07-04 18:30:04
* Filename     : sys5.c
* Description  :
************************************************************/

#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd=-1;
    fd = open("test_sys5.txt",O_CREAT|O_TRUNC|O_RDWR,0666);
    if(fd<0)
    {
        perror("open");
        return -1;
    }
    char buff[64];
    strcpy(buff,"Hello,I am writting to this file!");
    int count = strlen(buff);
    if(write(fd,buff,count)<0)
    {
        perror("write");
        return -1;
    }

    if(lseek(fd,0,SEEK_SET)<0)
    {
        perror("lseek");
        return -1;
    }
    if(read(fd,buff,10)<0)
    {
        perror("read");
        return -1;
    }

    buff[10]=0x00;
    printf("%s\n",buff);

    if(fd>0)
    {
        close(fd);
        fd=-1;
    }
    return 0;
}


