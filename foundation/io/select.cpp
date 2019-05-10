#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define TIMEOUT 5    // select timeout in secends
#define BUF_LEN 1024 // read buff in bytes

int main(int argc, char *argv[])
{
    struct timeval tv;
    int ret;
    fd_set readfds;
    // wait on stdin for input.
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    // wait up to five seconds.
    tv.tv_sec = TIMEOUT;
    tv.tv_usec = 0;

    // int select (int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
    // block
    ret = select(STDERR_FILENO + 1, &readfds, NULL, NULL, &tv);
    if (ret == -1)
    {
        perror("select");
    }
    else if (!ret)
    {
        printf("%d seconds elapsed. \n", TIMEOUT);
        return 0;
    }
    /*
    * is our file descriptor ready to read?
    * (it must be, as it was the only fd that we provided and the call returned nonzero,
    * bur we will humor ourselves.)
    */
    if (FD_ISSET(STDIN_FILENO, &readfds))
    {
        char buf[BUF_LEN + 1];
        int len;
        // guaranteed to not block
        len = read(STDERR_FILENO, buf, BUF_LEN);
        if (len == -1)
        {
            perror("read");
            return 1;
        }
        if (len)
        {
            buf[len] = '\0';
            printf("read: %s\n", buf);
        }
        return 0;
    }
    fprintf(stderr, "This should not happend!\n");

    return 1;
}