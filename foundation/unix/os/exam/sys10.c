/***********************************************************
* Author       : M_Kepler
* EMail        : m_kepler@foxmail.com
* Last modified: 2018-07-01 13:34:52
* Filename     : sys10.c
* Description  :
* 先创建一个共享内存区，之后将其映射到本进程中，最后再解除这种映射关系
**********************************************************/
#include <sys/types.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFSZ 1024

int main( int argc, char **argv )
{
    /* 创建共享内存 */
    int shmid;
    void* shmadd;
    shmid = shmget(IPC_PRIVATE, BUFFSZ, 0666);
    if ( shmid < 0 )
    {
        perror("fail to shmget");
        exit(-1);
    }
    system("ipcs -m");

    /* 映射共享内存 */
    shmadd = shmat(shmid, 0, 0);
    if ( shmadd == NULL )
    {
        perror("faile to shmat");
        exit(-1);
    }
    system("ipcs -m");

    /* 删除共享内存 */
    if ( shmdt(shmadd) < 0 )
    {
        perror("fail to shmdt");
        exit(-1);
    }
    system("ipcs -m");
    
    if ( shmctl(shmid, IPC_RMID, NULL) < 0)
    {
        perror("fail to shmctl");
        exit(-1);
    }
    system("ipcs -m");
    return 0;
}

