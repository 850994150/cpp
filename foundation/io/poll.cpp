#include <unistd.h>
#include <stdio.h>
#include <sys/poll.h>

#define TIMEOUT 5 // poll timeout in seconds

int main(int argc, char *argv[])
{
    struct pollfd fds[2];
    int ret;
    // watch stdin for input
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;

    // watch stdout for ability to write (almost always true)
    fds[1].fd = STDOUT_FILENO;
    fds[1].events = POLLOUT;

    // block
    ret = poll(fds, 2, TIMEOUT * 1000);
    if (ret == -1)
    {
        perror("poll");
        return 1;
    }
    if (!ret)
    {
        printf("%d seconds elapsed.\n", TIMEOUT);
        return 0;
    }

    // watch event happened
    if (fds[0].revents &POLLIN)
    {
        printf("stdin is readable\n");
    }
    if (fds[1].revents & POLLOUT)
    {
        printf("stdout is writable\n");
    }
    return 0;
}

/*
./poll.out
stdout is writable

./poll.out < test.txt
stdin is readable
stdout is writable
*/
