/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2018-12-15 09:59:33
 * Filename     : daemon.cpp
 * Description  : 守护进程
	* https://blog.csdn.net/u013485792/article/details/51507685
 	* 守护进程必须与其运行前的环境隔离开来; 这些环境包括未关闭的 文件描述符，
	* 控制终端，会话和进程组，工作目录以及文件创建掩模等
	* 因为这些环境通常是守护进程从执行它的父进程（特别是shell）中继承下来的
 1. 后台运行
 2. 脱离控制终端、登录会话和进程组 
 3. 禁止进程重新打开终端
 4. 关闭打开的文件描述符
 5. 改变当前工作目录
 6. 重设文件创建掩码
 7. 处理SIGCHLD信号
 ***********************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>

void init_daemon(void)
{
	int pid;
	int i;
	if(pid=fork())
	{
		exit(0);	// 1. 退出父进程
	}
	else if(pid< 0)
	{
		exit(1);
	}
	setsid(); // 2. 是第一子进程，后台继续执行; 第一子进程成为新的会话组长和进程组长, 并与控制终端分离
	if(pid=fork())
	{
		exit(0); // 3. 是第一子进程，结束第一子进程
	}
	else if(pid< 0)
	{
		exit(1);
	}

	// 是第二子进程，继续; 第二子进程不再是会话组长
	for(i=0; i< NOFILE; ++i)
	{
		close(i); 	// 4. 关闭打开的文件描述符
	}
	chdir("/tmp");  // 5. 改变工作目录到/tmp
	umask(0);		// 6. 重设 文件创建掩模
	return;
}

int main()
{
	FILE *fp;time_t t;
	init_daemon();	// 初始化为Daemon

	while (1)		// 每隔一分钟向test.log报告运行状态
	{
		sleep(4);
		if((fp=fopen("test.log","a")) >=0)
		{
			t=time(0);
			fprintf(fp,"Im here at %sn",asctime(localtime(&t)) );
			fclose(fp);
		}
	}
	return 0;
}
