/***********************************************************
* Author       : M_Kepler
* EMail        : m_kepler@foxmail.com
* Last modified: 2018-07-01 13:28:53
* Filename     : sys7.c
* Description  : 在tmp目录下调用open函数，以可读可写的方式创建hello.c文件
* open函数带有3个flag参数：O_CREATE、O_TRUNC、O_WRONLY，文件权限设置为0600
**********************************************************/

#include <stdio.h>

// 调用 open()
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// int open(const char*pathname,int flags,mode_t mode);
int main()
{
    int fd;
    fd = open("/tmp/hello.c",O_CREAT|O_TRUNC|O_WRONLY,0600);
    if(fd<0)
	{
		printf("fail\n");
	}
   return 0;
} 
