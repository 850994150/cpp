/***********************************************************
* Author       : M_Kepler
* EMail        : m_kepler@foxmail.com
* Last modified: 2018-07-01 12:53:00
* Filename     : sys1.c
* Description  : 把一个文件的内容复制到另一个文件上，实现简单copy功能
* 要求只用open()/read()/write()/close()系统调用，程序的第一个参数为源文件，第二个参数为目的文件。
**********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_SIZE 1024*8

int main( int argc, char **argv )
{
    int fds, fdd;
    char buf[BUF_SIZE];
    size_t hasread = 0;
    fds = open(argv[1], O_RDONLY);
    fdd = open(argv[2], O_WRONLY, O_CREAT);
    if(fds && fdd)
    {
        while((hasread = read(fds, buf, sizeof(buf))) > 0)
        {
            write(fdd, buf, hasread);
        }
        close(fds);
        close(fdd);
    }
}

