#ifndef __COMM_H__
#define __COMM_H__
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <error.h>

#define PATHNAME "."
#define PROJ_ID 0

union semun {
    int val;               // 信号量使用的值(计数器) 通常是1
    struct semid_ds *buf;  // IPC_STAT、IPC_SET 使用的缓存区
    unsigned short *arry;  // GETALL,、SETALL 使用的数组
    struct seminfo *__buf; // IPC_INFO(Linux特有) 使用的缓存区
};

//信号量是创建还是获取在于semget函数参数flag的设置
static int CommSemid(int nums, int flags);

//创建信号量
int CreatSemid(int nums);

//获取已经创建的信号量
int GetSemid(int nums);

//初始化信号量
int InitSem(int semid, int which, int _val);

//PV操作在于它_op的值
static int SemPV(int semid, int which, int _op);

//P操作
int P(int semid, int which, int _op);

//V操作
int V(int semid, int which, int _op);

//由于（System V通信方式）信号量生命周期随内核,所以要销毁信号量
int Destory(int semid);

#endif