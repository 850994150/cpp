/***********************************************************
* Author       : M_Kepler
* EMail        : m_kepler@foxmail.com
* Last modified: 2018-07-04 18:30:04
* Filename     : file.c
* Description  : 
************************************************************/

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
// #include <limits.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int READ_BITS = 10;

int main()
{
    int fd = -1;
    char *write_buff = const_cast<char *>("Hello,I.am.writting.to.this.file!");
    size_t len = strlen(write_buff);
    char read_buff[64] = {0};
    char *p_buff = read_buff;

    // fd = open("./debug/test_sys5.txt", O_CREAT | O_TRUNC | O_RDWR, 0666);
    fd = open("./test_sys5.txt", O_CREAT | O_TRUNC | O_RDWR, 0666);
    if (fd < 0)
    {
        perror("open");
        return -1;
    }

    /*
    if (write(fd, write_buff, len) < 0)
    {
        perror("write");
        return -1;
    }
    */
    ssize_t write_ret;
    ssize_t remain_to_write = len;
    while (remain_to_write != 0 && (write_ret = write(fd, write_buff, len)) != 0)
    {
        if (write_ret == -1)
        {
            if (errno == EINTR)
                continue;
            perror("write");
            break;
        }
        remain_to_write -= write_ret;
        write_buff += write_ret;
    }

    // SEEK_SET 文件起始 SEE_CUR 当前位置 SEEK_END 文件结尾
    if (lseek(fd, 0, SEEK_SET) < 0)
    {
        perror("lseek");
        return -1;
    }
    /*
    if (read(fd, write_buff, READ_BITS) < 0)
    {
        perror("read");
        return -1;
    }
    */
    ssize_t read_ret;
    int remain_bits = READ_BITS;
    while (remain_bits != 0 && (read_ret = read(fd, p_buff, remain_bits)) != 0)
    {
        if (read_ret == -1)
        {
            if (errno == EINTR)
                continue;
            perror("read");
            break;
        } 
        remain_bits -= read_ret;
        p_buff += read_ret;
    }

    // 文件空洞
    long long ret = lseek(fd, 10, SEEK_END);
    if (ret == -1)
    {
        perror("lseek");
        return -1;
    }
    if (write(fd, "CHINA", 6) == -1)
    {
        perror("write");
    }

    printf("[%s]\n", read_buff);

    if (fd > 0)
    {
        close(fd);
        fd = -1;
    }
    return 0;
}
