#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>


int main(int argc, char *argv[])
{
    int fd = open("./test.log", O_RDONLY|O_CREAT);
    if (fd < 0)
    {
        perror("open error");
    }
    return 0;
}