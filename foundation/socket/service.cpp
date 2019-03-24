#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <thread>
#include <iostream>
#include <signal.h>
#include "../thread/ThreadPool.h"

#define PORT 7000
#define QUEUE 20

/*
 * @function: 父进程退出时通知子信号
 * @brief	: 
 * @param	: 
 * @return	: 
 */
void signalHandler(int sig)
{
    printf("recv signal:%d\n", sig);
    printf("child exit\n");
    exit(0);
}


int one_client()
{
    int ss = socket(AF_INET, SOCK_STREAM, 0); // 1. 创建套接字

    struct sockaddr_in server_sockaddr;                  // socket结构体（16字节）
    memset(&server_sockaddr, 0, sizeof(server_sockaddr));
    server_sockaddr.sin_family = AF_INET;                // IPV4协议族, IPV6:AF_INET6
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY); // IP
    server_sockaddr.sin_port = htons(PORT);              // 端口
    // htons 转化为网络字节序(大端) h表示host,n表示network,s表示short,l表示long

    // 设置地址、端口重复利用，否则会因为TIME_WAIT状态而无法关闭后再立即开启
    int on = 1;
    if (setsockopt(ss, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
    {
        perror("setsockopt");
        exit(1);
    }

    // 2. 给监听套接字绑定地址和端口
    if (bind(ss, (struct sockaddr *)&server_sockaddr, sizeof(server_sockaddr)) == -1)
    {
        perror("bind");
        exit(1);
    }
    // 3. 设置套接字为被动模式, 准备接收客户端请求
    if (listen(ss, QUEUE) == -1)
    {
        perror("listen");
        exit(1);
    }

    struct sockaddr_in client_addr; // 客户端套接字
    socklen_t length = sizeof(client_addr);

    // 4. 从全连接队列返回一个连接请求，返回该连接的套接字，此时套接字（包含了服务端和客户端的ip和端口）
    int conn = accept(ss, (struct sockaddr *)&client_addr, &length);

    if (conn < 0)
    {
        perror("connect");
        exit(1);
    }

    char buffer[1024];

    while (1)
    {
        memset(buffer, 0, sizeof(buffer));

        // recv 同步阻塞模式
        int len = recv(conn, buffer, sizeof(buffer), 0); // 5.1 从内核协议栈的缓冲区拷贝数据到用户空间
        if (len >0)
        {
            if (strcmp(buffer, "exit\n") == 0)
                break;
            printf("%s", buffer);
            // send 同步阻塞模式
            send(conn, buffer, len, 0); // 5.2 拷贝数据到发送缓冲区
        }
        else
        {
            // 这几种错误码，认为连接是正常的，继续接收
            if ((len < 0) && (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR))
            {
                continue; // 继续接收数据
            }
            break; // 跳出接收循环
        }
    }
    close(conn); // 6. 关闭套接字
    close(ss);   // 7. 关闭监听
    return 0;
}


void do_service(int conn)
{
    char buffer[1024];
    while (1)
    {
        memset(buffer, 0, sizeof(buffer));
        int len = recv(conn, buffer, sizeof(buffer), 0);
        if (len == 0)
        {
            printf("client closed\n");
            exit(0);
        }
        printf("%s", buffer);
        send(conn, buffer, len, 0);
    }
}

/*
 * @function: 多进程处理多客户端连接
 * @brief	: 
 * @param	: 
 * @return	: 
 */
int multi_client_process()
{
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in service_addr;
    memset(&service_addr, 0, sizeof(service_addr));
    service_addr.sin_family = AF_INET;
    service_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    service_addr.sin_port = htons(PORT);

    if (bind(listenfd, (struct sockaddr *)&service_addr, sizeof(service_addr)) == -1)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    char buff[1024] = {0};
    pid_t pid;

    while (1)
    {
        if (listen(listenfd, QUEUE) == -1)
        {
            perror("listen");
            exit(1);
        }

        struct sockaddr_in client_sock;
        socklen_t length = sizeof(client_sock);
        int clientfd = accept(listenfd, (struct sockaddr *)&client_sock, &length);
        printf("[client connect] ip:%s\tport:%d\n", inet_ntoa(client_sock.sin_addr), ntohs(client_sock.sin_port));

        if (clientfd < 0)
        {
            perror("connect");
            exit(1);
        }

        pid = fork(); // 每有一个客户端连接进来就创建新进程处理
        if (pid == -1)
        {
            perror("fork");
            exit(1);
        }
        else if (pid == 0)
        {
            // 子进程
            printf("[pid: %d]\n", getpid());
            close(listenfd);
            do_service(clientfd);
            exit(0);
        }
        else
        {
            // 父进程
            close(clientfd);
        }
    }
    close(listenfd);

    return 0;
}


/*
 * @function: 多线程处理多个客户链接
 * @brief	: XXX 一个客户断掉服务器就断掉了
 * @param	: 
 * @return	: 
 */
int multi_client_thread()
{
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in service_addr;
    memset(&service_addr, 0, sizeof(service_addr));
    service_addr.sin_family = AF_INET;
    service_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    service_addr.sin_port = htons(PORT);

    if (bind(listenfd, (struct sockaddr *)&service_addr, sizeof(service_addr)) == -1)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    char buff[1024] = {0};
    pid_t pid;
    ThreadPool pool(4);

    while (1)
    {
        if (listen(listenfd, QUEUE) == -1)
        {
            perror("listen");
            exit(1);
        }

        struct sockaddr_in client_sock;
        socklen_t length = sizeof(client_sock);
        int clientfd = accept(listenfd, (struct sockaddr *)&client_sock, &length);
        printf("[client connect] ip:%s\tport:%d\n", inet_ntoa(client_sock.sin_addr), ntohs(client_sock.sin_port));

        if (clientfd < 0)
        {
            perror("connect");
            exit(1);
        }

        pool.enqueue(do_service, clientfd); // 用线程池
    }
    close(listenfd);

    return 0;
}

/*
 * @function: 点对点全双工通信
 * @brief	: 
 * @param	: 
 * @return	: 
 */
int peer2peer()
{
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in service_addr;
    memset(&service_addr, 0, sizeof(service_addr));
    service_addr.sin_family = AF_INET;
    service_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    service_addr.sin_port = htons(PORT);

    if (bind(listenfd, (struct sockaddr *)&service_addr, sizeof(service_addr)) == -1)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    char buff[1024] = {0};
    if (listen(listenfd, QUEUE) == -1)
    {
        perror("listen");
        exit(1);
    }

    struct sockaddr_in client_sock;
    socklen_t length = sizeof(client_sock);
    int clientfd = accept(listenfd, (struct sockaddr *)&client_sock, &length);
    printf("[client connect] ip:%s\tport:%d\n", inet_ntoa(client_sock.sin_addr), ntohs(client_sock.sin_port));

    if (clientfd < 0)
    {
        perror("connect");
        exit(1);
    }
    pid_t pid; // 因为要能发信息也能收信息，因为会阻塞, 所以要开一个进程开收或发
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) // 子进程做发送
    {
        signal(SIGUSR1, signalHandler); // 通过信号通知子进程，父进程已退出
        char sendbuff[1024] = {0};
        while (fgets(sendbuff, sizeof(sendbuff), stdin) != NULL)
        {
            // send(clientfd, sendbuff, sizeof(sendbuff), 0);
            write(clientfd, sendbuff, sizeof(sendbuff));
            memset(sendbuff, 0, sizeof(sendbuff));
        }
        exit(0);
        // close(clientfd);
    }
    else // 父进程做接收 ,, 父进程退出了，子进程还没退出
    {
        char recvbuff[1024] = {0};
        while (true)
        {
            memset(recvbuff, 0, sizeof(recvbuff));
            // int ret = recv(clientfd, recvbuff, sizeof(recvbuff), 0);
            int ret = read(clientfd, recvbuff, sizeof(recvbuff));
            if (ret == -1)
            {
                perror("read");
            }
            else if (ret == 0)
            {
                printf("client closed\n");
                break;
            }
            fputs(recvbuff, stdout);
        }
        printf("parent exit\n");
        kill(pid, SIGUSR1); // 向进程发送自定义信号SIGUSR
        exit(0);
        // close(clientfd);
    }

    return 0;
}


void multi_client_select()
{

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in service_addr;
    memset(&service_addr, 0, sizeof(service_addr));
    service_addr.sin_family = AF_INET;
    service_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    service_addr.sin_port = htons(PORT);

    if (bind(listenfd, (struct sockaddr *)&service_addr, sizeof(service_addr)) == -1)
    {
        perror("bind");
        exit(1);
    }

    if (listen(listenfd, QUEUE) == -1)
    {
        perror("listen");
        exit(1);
    }

    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);
    int clientfd = accept(listenfd, (struct sockaddr *)&client_addr, &length);

}

void multi_client_poll()
{

}

void multi_client_epoll()
{

}


int main(int argc, char *argv[])
{
    // one_client();
    // multi_client_process();
    // multi_client_thread();
    peer2peer();
    // multi_client_select();
    return 0;
}