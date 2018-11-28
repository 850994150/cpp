/***********************************************************
 * Author       : M_Kepler
 * EMail        : hellohuangjinjie@gmail.com
 * Last modified: 2016-03-21 14:13:30
 * Filename     : pid.c
 * Description  : test_file
 ***********************************************************/


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int a = 10;
int main(int argc,char* argv[])
{
    int b = 20;
    pid_t pid;
    pid=fork();
    if (pid < 0)
    {
        perror("fork error");
    }
    if (pid == 0)
    {
        a = 111;
        b = 222;
        printf("son:a = %d,b = %d\n",a,b);
    }
    else if (pid > 0)
    {
        sleep(1);
        printf("father:a= %d,b=%d\n",a,b);
    }
    return 0;
}
