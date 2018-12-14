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
            execlp(buf, buf, (char*) 0);
            std::cerr << "couldn't execute: " << buf << std::endl;
            exit(127);
        }
        if ((pid = waitpid(pid, &status, 0)) < 0)
        {
            std::cerr << "waitpid error" << std::endl;
        }
        printf("%% ");
    }
    // return 0;
    exit(0);
}
