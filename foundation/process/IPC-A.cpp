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
    * 其实就是依靠fork函数, 利用fork来和父进程公用一个管道
    * int pipe(int filedis[2])
    * 参数 filedis 返回两个文件描述符：filedes[0] 为读而打开, filedes[1] 为写而打开.
    * filedes[1] 的输出是 filedes[0] 的输入
 * 有名管道
    * 可以认为是通过文件来进行进程间通信, 写入读出的对象都是一个文件
    * 管道都有同步和阻塞的问题, 读写有等待的情况; 而且当读写的数据大于最大长度时会阻塞等待
 * 消息队列
    *
        #include<sys/msg.h>
        int msgget(key_t key,int msgflg);
        int msgctl(int magid,int cmd,struct msgid_ds *buf);
        int msgsnd(int msgid,void *msg_ptr,size_t msg_sz,int msgflag);
        int msgrcv(int msgid,void *msg_ptr,size_t msg_sz,long int msg_type,int msgflag);
    * 和有名管道一样, 发送的数据都有一个最大长度限制
    * 生命周期随内核，消息队列会一直存在，需要我们显式的调用接口或使用命令删除
    * 消息队列可以双向通信
    * 克服了管道只能承载无格式字节流的缺点
 * 共享内存
    *
        #include<sys/shm.h>
        int shmget(key_t key,size_t size,int shmflag);
        void *shmat(int shm_id,const void *shm_addr,int shm_flag);
        int shmctl(int shm_id,int cmd,struct shmid_ds *buf);
        int shmdt(const void *shm_addr);
    * 因为系统内核没有对访问共享内存进行同步，您必须提供自己的同步措施, 比如用信号量进行同步
 * 信号量 Pv：
    *
        #include<sys/sem.h>
        int semget(key_t key,int num_sems,int sem_flgs);
        int semctl(int sem_id,int sem_num,int command...);
        int semop(int sem_id,struct sembuf *sem_ops,size_t num_sem_ops);
    * 解决进程间同步与互斥问题的一种进程间通讯机制
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

#include <sys/mman.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>

// #include <pthread.h>

#include <fcntl.h>
#include <stdio.h>

#include <sys/wait.h>
#include <mutex>

using namespace std;

#define MAX_TEXT 512
#define INPUT 0
#define OUTPUT 1
#define PIPENAME "NamedPipe" // 有名管道名(路径)
#define SHM_SIZE 1024        //共享内存的大小

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

/*
 * @brief	: 有名管道(写)
 */
int NamedPipeWrite()
{
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

    unlink(PIPENAME); // 删除管道

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

/*
 * @brief	: 消息队列(写)
 */
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
    // IPC_CREAT 不存在则创建, 存在则返回已有id
    // IPC_EXCL  存在则返回错误
    if (msgid == -1)
    {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE); // exit(1);
        // exit(EXIT_SUCCESS); // exit(0);
    }

    // 向消息队列中写消息，直到写入end
    while (running)
    {
        printf("Enter some text: ");
        fgets(buffer, BUFSIZ, stdin); // 从标准输入获取一行到buffer中
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
    // 读端 4. msgctl 删除消息队列 remove id
}

/*
 * @brief	: 共享内存（写）
 */
int SharedMemoryWrite()
{
    key_t key = ftok("./", 66); // 1. 生成一个key

    int shmid = shmget(key, 8, IPC_CREAT | 0666 | IPC_EXCL); // 2. 创建指定大小的共享内存，返回一个id
    if (-1 == shmid)
    {
        perror("shmget failed");
        exit(1);
    }

    void *p = shmat(shmid, 0, 0); // 3. 映射共享内存，得到虚拟地址 p
    if ((void *)-1 == p)
    {
        perror("shmat failed");
        exit(2);
    }

    // 写共享内存
    int *pp = (int *)p;
    int a = 10;
    int b = 20;
    *pp = 0x12345678;
    *(pp + 1) = 0xffffffff;

    if (-1 == shmdt(p)) // 4. 解除映射
    {
        perror("shmdt failed");
        exit(3);
    }
    printf("解除映射成功，销毁共享内存\n");
    getchar();

    if (-1 == shmctl(shmid, IPC_RMID, NULL)) // 5. 销毁共享内存
    {
        perror("shmctl failed");
        exit(4);
    }

    return 0;
}

/*
 * @brief	: 信号量控制共享内存的同步问题
 */
int SharedMemoryWithSema()
{
    int ret;                                              //临时变量
    int pid;                                              //进程id
    int sme_id;                                           //保存信号量描述符
    int shm_id;                                           //保存共享内存描述符
    key_t sme_key;                                        //保存信号量键值
    key_t shm_key;                                        //保存共享内存键值
    char *shmp;                                           //指向共享内存的首地址
    struct shmid_ds dsbuf;                                //定义共享内存信息结构变量
    struct sembuf lock = {0, -1, SEM_UNDO};               //信号量上锁操作的数组指针
    struct sembuf unlock = {0, 1, SEM_UNDO | IPC_NOWAIT}; //信号量解锁操作的数组指针
    shm_key = ftok("./", 2);                              //获取信号量键值
    if (shm_key < 0)
    {
        perror("ftok");
        exit(0);
    }
    sme_id = semget(shm_key, 1, IPC_CREAT | 0666); //获取信号量ID
    if (sme_id < 0)
    {
        perror("semget");
        exit(0);
    }
    shm_key = ftok("./", 1); //获取共享内存键值
    if (shm_key < 0)
    {
        perror("ftok");
        exit(0);
    }
    shm_id = shmget(shm_key, SHM_SIZE, IPC_CREAT | 0666); //获取共享内存ID
    if (shm_id < 0)
    {
        perror("shmget");
        exit(0);
    }
    shmp = (char *)shmat(shm_id, NULL, 0); //映像共享内存
    if (shmp == (char *)-1)
    {
        perror("shmat");
        exit(0);
    }

    pid = fork(); // 创建子进程

    if (pid < 0)
    {
        perror("fork");
        exit(0);
    }
    else if (pid == 0) //子进程
    {
        ret = semctl(sme_id, 0, SETVAL, 1); //初始化信号量，初值设为1
        if (ret == -1)
        {
            perror("semctl");
            exit(0);
        }
        ret = semop(sme_id, &lock, 1); //申请访问共享资源，锁定临界资源
        if (ret == -1)
        {
            perror("semop lock");
            exit(0);
        }
        sleep(4);                    //让子进程睡眠4秒
        strcpy(shmp, "hello\n");     //往共享内存写入数据
        if (shmdt((void *)shmp) < 0) //使共享内存脱离进程地址空间
        {
            perror("shmdt");
        }
        ret = semop(sme_id, &unlock, 1); //解锁临界资源
        if (ret == -1)
        {
            perror("semop unlock");
            exit(0);
        }
    }
    else //父进程
    {
        sleep(1);                      //先让子进程运行
        ret = semop(sme_id, &lock, 1); //申请访问共享资源，锁定临界资源
        if (ret == -1)
        {
            perror("semop lock");
            exit(0);
        }
        if (shmctl(shm_id, IPC_STAT, &dsbuf) < 0) //获取共享内存信息
        {
            perror("shmctl");
            exit(0);
        }
        else /* 共享内存的状态信息获取成功 */
        {
            printf("Shared Memory Information:\n");
            printf("\tCreator PID: %d\n", dsbuf.shm_cpid);       /* 输出创建共享内存进程的标识符 */
            printf("\tSize(bytes): %d\n", dsbuf.shm_segsz);      /* 输出共享内存的大小 */
            printf("\tLast Operator PID: %d\n", dsbuf.shm_lpid); /* 输出上一次操作共享内存进程的标识符 */
            printf("Received message : %s\n", (char *)shmp);     /* 从共享内存中读取数据 */
        }
        if (shmdt((void *)shmp) < 0) // 使共享内存脱离进程地址空间
        {
            perror("shmdt");
            exit(0);
        }
        ret = semop(sme_id, &unlock, 1); // 解锁临界资源
        if (ret == -1)
        {
            perror("semop unlock");
            exit(0);
        }
        if (shmctl(shm_id, IPC_RMID, NULL) < 0) // 删除前面创建的共享内存
        {
            perror("shmctl");
            exit(0);
        }
        ret = semctl(sme_id, 0, IPC_RMID, NULL); // 删除信号量
        if (ret == -1)
        {
            perror("semctl");
            exit(0);
        }
    }
    return 0;
}

/*
 * @brief	: 用内存映射实现进程通讯
 */
typedef struct
{
    char name[4];
    int age;
} people;

int IpcMmmp()
{
    int i;
    pid_t result;
    people *p_map;
    char temp;
    // 匿名内存映射
    p_map = (people *)mmap(NULL, sizeof(people) * 10, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    result = fork();

    if (result < 0)
    {
        perror("fork error");
        exit(0);
    }
    else if (result == 0)
    {
        sleep(2);

        for (size_t i = 0; i < 5; i++)
        {
            printf("子进程读取: 第 %d 个人的年龄是: %d\n", i + 1, (*(p_map + i)).age);
        }
        (*p_map).age = 110;
        // 解除映射关系
        munmap(p_map, sizeof(people) * 10);
        exit(0);
    }
    else
    {
        temp = 'a';

        for (size_t i = 0; i < 5; i++)
        {
            temp += 1;
            memcpy((*(p_map + i)).name, &temp, 1);
            (*(p_map + i)).age = 20 + i;

            printf("父进程写入: 第 %d 个人的姓名为:%s, 年龄是: %d\n", i + 1, (*(p_map + i)).name, (*(p_map + i)).age);
        }
        sleep(5);
        printf("父进程读取, 5个人年龄和为: %d\n", (*p_map).age);
        printf("解除内存映射...\n");
        munmap(p_map, sizeof(people) * 10);
        printf("解除内存映射成功...\n");
    }
}

/*
 * @brief	: 进程通过内存映射实现变量累加
 * g++ a.cpp -lpthread -lrt
 */
void SignalHandler(int signal)
{
    int stat;
    pid_t sub_pid;
    while((sub_pid = waitpid(-1, &stat, WNOHANG)) > 0)
    {
       printf("【Handler - waitpid】get sub process %d exited signal!\tstat:%d\n", sub_pid, stat);
    }
}

int IpcArgIncMmap()
{
    int *x;
    int rt;
    int shm_id;
    char *addnum = "myadd";
    char *ptr;
    int status;
    mutex g_lock;
    // pthread_mutex_t mutex;         //互斥对象
    // pthread_mutexattr_t mutexattr; //互斥对象属性

    // pthread_mutexattr_init(&mutexattr);                               //初始化互斥对象属性
    // pthread_mutexattr_setpshared(&mutexattr, PTHREAD_PROCESS_SHARED); //设置互斥对象为PTHREAD_PROCESS_SHARED共享，即可以在多个进程的线程访问,PTHREAD_PROCESS_PRIVATE为同一进程的线程共享
    rt = fork();
    if (rt == 0)
    {
        // 子进程完成x+1
        shm_id = shm_open(addnum, O_RDWR, 0);
        ftruncate(shm_id, sizeof(int));

        ptr = (char *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_id, 0); // 连接共享内存区
        x = (int *)ptr;

        for (int i = 0; i < 10; i++)
        {
            g_lock.lock();
            // pthread_mutex_lock(&mutex);
            (*x)++;
            printf("子进程+1: %d\n", *x);
            g_lock.unlock();
            // pthread_mutex_unlock(&mutex);
            // sleep(1);
        }
        printf("Sub Process Exit\n");
        exit(0);
    }
    else if (rt > 0)
    {
        signal(SIGCHLD, SignalHandler);

        // 父进程完成x+1 ...
        shm_id = shm_open(addnum, O_RDWR | O_CREAT, 0644);
        ftruncate(shm_id, sizeof(int));

        ptr = (char *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_id, 0); // 连接共享内存区
        x = (int *)ptr;

        for (int i = 0; i < 10; i++)
        {
            g_lock.unlock();
            // pthread_mutex_lock(&mutex);
            (*x)++;
            printf("父进程+1: %d\n", *x);
            g_lock.unlock();
            // pthread_mutex_unlock(&mutex);
            // sleep(1);
        }
        printf("Par Process Exit\n");
    }
    else
    {
        perror("fork failed!\n");
        exit(1);
    }

    shm_unlink(addnum);       //删除共享名称
    munmap(ptr, sizeof(int)); //删除共享内存
    return (0);
}

int main(int argc, char const *argv[])
{
    // NoneNamedPipe();
    // NamedPipeWrite(); // window的文件系统不支持管道文件
    // MsgQueueWrite();
    // SharedMemoryWrite();
    // SharedMemoryWithSema();
    // IpcMmmp();
    // IpcArgIncMmap(); // FIXME 多次运行有可能出现只有父进程运行 和 父进程+1后为1, 子进程+1后也为1的情况
    return 0;
}

// g++ a.cpp -lpthread -lrt
// g++ a.cpp -lrt

/*
 · linux查看:  ipcs
 . 有名管道先运行 IPC-A.out 再另一终端运行 IPC-B.out

 Q1: 是先读还是先写呢? 如果读的进程还没等到写进程写入数据呢?
 Q2: 读写情况是怎样的, 管道大小与实际写内容大小联系, 阻塞?

*/
