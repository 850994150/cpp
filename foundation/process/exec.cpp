/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2018-12-16 09:59:57
 * Filename     : exec.cpp
 * Description  : 本进程启动另一个程序执行
    * 进程一旦调用exec族函数, 其本身的代码段、数据段、堆栈段都不
    * 是原来的了, 进程的结构全被替换掉了, 只有进程号还是本来的, 
    * 对系统而言还是同一个进程, 不过已经是另一个程序了.
    * 如果想让本程序和exec启动的程序都继续运行, 那就要结合fork了
 ***********************************************************
 */


#include <iostream>
#include <sys/wait.h>
#include <string.h>
// fork
#include <unistd.h>
#include <sys/types.h>

#define MAXLINE 4096
int main(int argc, char const *argv[])
{
    char buf[MAXLINE];
    pid_t pid;
    int status;
    printf("%% ");
    
    while(fgets(buf, MAXLINE, stdin) != NULL)
    {
        if (buf[strlen(buf) - 1] == '\n')
        {
            buf[strlen(buf) - 1] = 0;
        }
        
        if (( pid = fork()) < 0 )
        {
            std::cerr << "fork error" << std::endl;
        }
        else if ( pid == 0 )
        {
            // 子进程执行命令
            execlp(buf, buf, (char*) 0);
            std::cerr << "couldn't execute: " << buf << std::endl;
            exit(127);
        }
        // 父进程等待子进程结束, 并打印返回值
        if ((pid = waitpid(pid, &status, 0)) < 0)
        {
            std::cerr << "waitpid error" << std::endl;
        }
        printf("%% ");
    }
    // return 0;
    exit(0);
}
