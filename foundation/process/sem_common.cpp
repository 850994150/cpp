#include "sem_common.h"

// #include <sys/sem.h>
// key_t _key = ftok(); // 获取键值
// int semget(key_t key, int nsems, int semflg); // 获取信号量id
// int semop(int semid, struct sembuf* sops, unsigned nsops); // 对信号量进行pv操作
// int semctl(int semid, int semnum, int cmd, union semnum arg); // 得到一个信号量集标识符，或创建一个信号量集对象并返回信号量集标识符

static int CommSemid(int nums, int flags)
{
    key_t _key = ftok(PATHNAME, PROJ_ID);
    if (_key > 0)
    {
        return semget(_key, nums, flags);
    }
    else
    {
        perror("CommSemid");
        return -1;
    }
}

int CreatSemid(int nums)
{
    return CommSemid(nums, IPC_CREAT | IPC_EXCL | 0666);
}
// int semctl(int semid, int semnum, int cmd, ...);

int GetSemid(int nums)
{
    return CommSemid(nums, IPC_CREAT);
}

int Destory(int semid)
{
    // 控制信号量 semid标识符, 0 编号, IPC_RMID 删除信号量 / SETVAL 设置初始值
    if (semctl(semid, 0, IPC_RMID) > 0)
    {
        return 0;
    }
    else
    {
        perror("Destory");
        return -1;
    }
}

int InitSem(int semid, int which, int _val)
{
    union semun _semun;
    _semun.val = _val;
    // p 这个值通过union semun中的val成员设置，其作用是在信号量第一次使用前对它进行设置
    if (semctl(semid, which, SETVAL, _semun) < 0)
    {
        perror("InitSem");
        return -1;
    }
    return 0;
}

static int SemPV(int semid, int which, int _op)
{
    struct sembuf _sf;

    _sf.sem_num = which; // 除非使用一组信号量，否则它为0
    _sf.sem_op = _op;    // 信号量在一次操作中需要改变的数据，通常是两个数，
                         // 一个是-1，即P（等待）操作，
                         // 一个是+1，即V（发送信号）操作。

    _sf.sem_flg = 0;     //通常为SEM_UNDO,使操作系统跟踪信号量，
                         //并在进程没有释放该信号量而终止时，操作系统释放信号量
    return semop(semid, &_sf, 1);
}

int P(int semid, int which, int _op)
{
    if (SemPV(semid, which, _op) < 0)
    {
        perror("P");
        return -1;
    }
    return 0;
}

int V(int semid, int which, int _op)
{
    if (SemPV(semid, which, _op) < 0)
    {
        perror("V");
        return -1;
    }
    return 0;
}