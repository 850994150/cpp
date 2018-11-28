
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <windows.h>

int main()
{
    char buf[1024] = "111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111\n";
    int fd;
    fd = open("test.txt", O_CREAT|O_RDWR); 
    if(fd < 0)
    {
        printf("fopen fail!\n");
        return -1;
    }
    DWORD dwBegin = GetTickCount();
    printf( "dwBegin:%ld", dwBegin );

    for(int i = 0; i < 100000; i++)
    {
        int nWriteNum = write(fd, buf, strlen(buf));
        if(nWriteNum != strlen(buf))
        {
            printf("write fail! %d\n", nWriteNum);
            return -1;
        }
        //_commit(fd);
    }
    DWORD dwEnd = GetTickCount();
    printf( "dwEnd:%ld", dwEnd);
    printf("consume:%ld\n", (dwEnd - dwBegin));
    close(fd);
    return 0;
}

