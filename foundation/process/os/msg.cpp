/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2018-06-21 18:05:06
 * Filename     : msg.cpp
 * Description  : ��Ϣ����IPC
 **********************************************************
 */

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
    int msgid = msgget(IPC_PRIVATE, IPC_CREAT | 0777); // ����һ����Ϣ����, ������Ϣ����id
    if (msgid < 0)
    {
        cout << "create msg queue failed !" << endl;
    }

    int pid = fork();
    if (pid > 0)
    {
        msgbuff msg = {1, "hello!"};
        msgsnd(msgid, &msg, sizeof(msg), IPC_NOWAIT); // ����Ϣ���з�����Ϣ

        sleep(2);
        msgrcv(msgid, &msg, sizeof(msg), 1, IPC_NOWAIT); // ����Ϣ���н�����Ϣ
        cout << msg.mtext << endl;
    }
    else if (pid == 0) // �ӽ���������Ϣ
    {
        msgbuff msg;
        msgrcv(msgid, &msg, sizeof(msg), 1, IPC_NOWAIT);
        cout << msg.mtext << endl;

        strcpy(msg.mtext, "hello ,too!");
        msgsnd(msgid, &msg, sizeof(msg), IPC_NOWAIT);
    }
    else
    {
        printf("fork error");
    }
    
    return 0;
}


