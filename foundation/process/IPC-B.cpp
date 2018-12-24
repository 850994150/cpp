/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2018-12-20 14:47:37
 * Filename     : IPC-B.cpp
 * Description  : 有名管道(读）
 ***********************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <sys/shm.h>

#define PIPENAME "NamedPipe"

// 有名管道
int NamedPipeRead()
{
	// 打开读管道
	int fd = open(PIPENAME, O_RDONLY);
	if (-1 == fd)
	{
		perror("open");
		return -1;
	}

	int num = 0;
	for (int i = 0; i < 10; i++)
	{
		read(fd, &num, sizeof(int));
		printf("%d\n", num);
		fflush(stdout); // 强制刷新输出缓冲区
	}

	printf("\n");
	close(fd);

	return 0;
}

// 消息队列

struct msg_st
{
	long int msg_type;
	char text[BUFSIZ];
};
int MsgQueueRead()
{
	int running = 1;
	int msgid = -1;
	struct msg_st data;
	long int msgtype = 0;

	key_t key = ftok("./", 88); // 1. ftok 产生key
	printf("key:%x\n", key);

	msgid = msgget(key, 0666 | IPC_CREAT); // 2. 建立消息队列
	if (msgid == -1)
	{
		fprintf(stderr, "msgget failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
	}
	// 从队列中获取消息，直到遇到end消息为止
	while (running)
	{
		if (msgrcv(msgid, (void *)&data, BUFSIZ, msgtype, 0) == -1) // 3.  接收消息类型为msgtype的消息
		{
			fprintf(stderr, "msgrcv failed with errno: %d\n", errno);
			exit(EXIT_FAILURE);
		}
		printf("You wrote: %s\n", data.text);
		// 遇到end结束
		if (strncmp(data.text, "end", 3) == 0)
			running = 0;
	}
	// 4. 删除消息队列
	if (msgctl(msgid, IPC_RMID, 0) == -1)
	{
		fprintf(stderr, "msgctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

// 共享内存
int SharedMemory()
{
	// 生成一个key
	key_t key = ftok("./", 66);
	printf("key:%x\n", key);

	// 获取共享内存，返回一个id
	int shmid = shmget(key, 0, 0);
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

	// 读共享内存
	int x = *(int *)p;
	int y = *((int *)p + 1);
	printf("从共享内存中都取了：0x%x 和 0x%x \n", x, y);

	// 解除映射
	if (-1 == shmdt(p))
	{
		perror("shmdt failed");
		exit(3);
	}

	return 0;
}

int main(int argc, char const *argv[])
{
	/* code */
	// NamedPipeRead();
	MsgQueueRead();
	// SharedMemory();
	return 0;
}
