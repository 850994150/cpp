/***********************************************************
* Author       : M_Kepler
* EMail        : m_kepler@foxmail.com
* Last modified: 2018-06-21 18:03:45
* Filename     : printf_cache.c
* Description  : https://blog.csdn.net/a312024054/article/details/46946237
               : http://www.cnblogs.com/Franck/archive/2012/11/27/2782471.html
               : 只有stdout的缓冲区是通过‘\n’进行行刷新的，但是我开始的时候就把stdout就关闭了，就会像普通文件一样像文件中写
               : 所以‘\n’是不会行刷新的，所以要使用fflush(stdout)。
               : stderr无缓冲，不用经过fflush或exit，就直接打印出来 stdout行缓冲 遇到\n刷新缓冲区
**********************************************************/

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    int fd;
    close(STDOUT_FILENO);
    fd = open("cache.txt", O_CREAT|O_RDWR, 0644);
    if(fd < 0)
    {
        perror("open");
        exit(0);
    }
    printf("Nice to meet you!\n");
    //fflush(stdout);
    close(fd);
    return 0;
}

