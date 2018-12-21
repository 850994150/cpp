/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2018-12-20 14:41:28
 * Filename     : IPC.cpp
 * Description  : inter process commutication 方式:
 *                管道(FIFO)、信号、共享内存、消息队列、信号量、套接字
 * IPC好像都是通过一个ID来让进程间通讯
 * 无名管道
    * int pipe(int filedis[2])
    * 参数 filedis 返回两个文件描述符：filedes[0] 为读而打开, filedes[1] 为写而打开.
    * filedes[1] 的输出是 filedes[0] 的输入
 * 有名管道
    * 管道都有同步和阻塞的问题, 读写有等待的情况; 而且当读写的数据大于最大长度时会阻塞等待
 * 消息队列
    * 和有名管道一样, 发送的数据都有一个最大长度限制 
 * 共享内存
 * 信号量 Pv：解决进程间同步与互斥问题的一种进程间通讯机制
 * 套接字
 * RPC
 ***********************************************************
 */

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/msg.h> // msg
#include <sys/shm.h> // share memory
#include <sys/sem.h> // Semaphore

#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <stdio.h>

using namespace std;

#define MAX_TEXT 512
#define INPUT 0
#define OUTPUT 1
#define PIPENAME "NamedPipe" // 有名管道名(路径)

// 无名管道 (适合父子进程间通信)
void NoneNamedPipe()
{
    int file_descriptors[2];
    pid_t pid;
    char buf[256];
    int returned_count;

    pipe(file_descriptors); // 创建无名管道

    if ((pid = fork()) == -1)
    {
        printf("Error in fork/n");
        exit(1);
    }
    if (pid == 0)
    {
        printf("in the spawned (child) process...\n");
        close(file_descriptors[INPUT]); // 子进程向父进程写数据, 关闭管道的读端
        write(file_descriptors[OUTPUT], "test data", strlen("test data") + 1);
        exit(0);
    }
    else
    {
        printf("in the spawning (parent) process...\n");
        close(file_descriptors[OUTPUT]); // 父进程从管道读取子进程写的数据, 关闭管道的写端
        returned_count = read(file_descriptors[INPUT], buf, sizeof(buf));
        printf("%d bytes of data received from spawned process: %s\n", returned_count, buf);
    }
}

// 有名管道(写)
int NamedPipeWrite()
{
    // window的文件系统不支持管道文件
    if (mkfifo(PIPENAME, 0666) < 0) // 创建管道
    {
        perror("mkfifo");
        return -1;
    }

    // 打开写管道
    int fd = open(PIPENAME, O_WRONLY);
    if (-1 == fd)
    {
        perror("open");
        return -1;
    }

    unlink(PIPENAME);

    int i = 0;
    for (i = 0; i < 10; i++)
    {
        write(fd, &i, sizeof(i));
        printf("%d\n", i);
        sleep(1); // 这个是以秒为单位挂起
    }
    // 关闭管道
    close(fd);
    return 0;
}

// 消息队列(写)
struct msg_st
{
    long int msg_type;
    char text[MAX_TEXT];
};

void MsgQueueWrite()
{
    int running = 1;
    struct msg_st data;
    char buffer[BUFSIZ];
    int msgid = -1;

    key_t key = ftok("./", 88); // 1. ftok 产生key
    printf("key:%x\n", key);

    msgid = msgget(key, 0666 | IPC_CREAT); // 2. 建立消息队列
    if (msgid == -1)
    {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }

    // 向消息队列中写消息，直到写入end
    while (running)
    {
        printf("Enter some text: ");
        fgets(buffer, BUFSIZ, stdin);
        data.msg_type = 1;
        strcpy(data.text, buffer);
        if (msgsnd(msgid, (void *)&data, MAX_TEXT, 0) == -1) // 3. 发送消息 0 阻塞 IPC_NOWAIT 非阻塞
        {
            fprintf(stderr, "msgsnd failed\n");
            exit(EXIT_FAILURE);
        }
        if (strncmp(buffer, "end", 3) == 0) // 输入end结束输入
            running = 0;
        sleep(1);
    }
    exit(EXIT_SUCCESS);


    /*
    if (-1 == shmctl(msgid, IPC_RMID, NULL)) // 4. msgctl 删除消息队列 remove id
    {
        perror("shmctl failed");
        exit(2);
    }
    */
    // return 0;
}

// 共享内存(写)
int SharedMemoryWrite()
{
    // 生成一个key
    key_t key = ftok("./", 66);

    // 创建共享内存，返回一个id
    int shmid = shmget(key, 8, IPC_CREAT | 0666 | IPC_EXCL);
    if (-1 == shmid)
    {
        perror("shmget failed");
        exit(1);
    }

    // 映射共享内存，得到虚拟地址
    void *p = shmat(shmid, 0, 0);
    if ((void *)-1 == p)
    {
        perror("shmat failed");
        exit(2);
    }

    // 写共享内存
    int *pp = (int *)p;
    *pp = 0x12345678;
    *(pp + 1) = 0xffffffff;

    // 解除映射
    if (-1 == shmdt(p))
    {
        perror("shmdt failed");
        exit(3);
    }
    printf("解除映射成功，点击回车销毁共享内存\n");
    getchar();

    // 销毁共享内存
    if (-1 == shmctl(shmid, IPC_RMID, NULL))
    {
        perror("shmctl failed");
        exit(4);
    }

    return 0;
}

int main(int argc, char const *argv[])
{
    /* code */
    // NoneNamedPipe();
    // NamedPipeWrite();
    MsgQueueWrite();
    // SharedMemoryWrite();

    return 0;
}

/*
 . 有名管道先运行 IPC-A.out 再另一终端运行 IPC-B.out

 Q1: 是先读还是先写呢? 如果读的进程还没等到写进程写入数据呢?
 Q2: 读写情况是怎样的, 管道大小与实际写内容大小联系, 阻塞?

*/
