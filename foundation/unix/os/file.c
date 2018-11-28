/***********************************************************
* Author       : M_Kepler
* EMail        : m_kepler@foxmail.com
* Last modified: 2018-07-01 13:53:22
* Filename     : file.c
* Description  :
**********************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//int open(const char *pathname,int flags)
//int open(const char *pathname,int flags,mode_t mode);

#include <unistd.h>
//ssize_t read(int fd,void *buf,size_t count);

#define MAXSIZE 100
int main()
{
    int fd;
    ssize_t nr;
    unsigned long word;
    fd = open("filetest.txt",O_CREAT|O_RDONLY);
    nr = read(fd,&word,sizeof(unsigned long));
    if(fd == -1)
    {
        printf("open file error");
    }
    else
    {
        if(nr == -1)
        {
            printf ("read error");
        }
        else
        {
            printf ("success\n");
        }
    }


    getchar();
    return 0;
}



