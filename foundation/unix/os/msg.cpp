/***********************************************************
* Author       : M_Kepler
* EMail        : m_kepler@foxmail.com
* Last modified: 2018-06-21 18:05:06
* Filename     : msg.cpp
* Description  : 信号量
**********************************************************/

#include <unistd.h>
#include <sys/types.h>
#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
using namespace std;

struct msgbuff
{
    long mtype;
    char mtext[100];
};

int main()
{
    int msgid = msgget(IPC_PRIVATE,IPC_CREAT|0777);
    if(msgid<0)
    {
        cout<<"create msg queue failed !" <<endl;
    }
    
    int cid = fork();
    if(cid>0)
    {
        msgbuff msg = {1,"hello!"};
        msgsnd(msgid,&msg,sizeof(msg),IPC_NOWAIT);
        
        sleep(2);
        msgrcv(msgid,&msg,sizeof(msg),1,IPC_NOWAIT);
        cout<<msg.mtext<<endl;
    }
    else if(cid == 0)//子进程先收消息
    {
        msgbuff msg;
        msgrcv(msgid,&msg,sizeof(msg),1,IPC_NOWAIT);
        cout<<msg.mtext<<endl; 
        
        strcpy(msg.mtext,"hello ,too!");
        msgsnd(msgid,&msg,sizeof(msg),IPC_NOWAIT);   
    }
    return 0;
}


