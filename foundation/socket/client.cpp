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
#include <signal.h>
#include <iostream>
using namespace std;
#define SERVER_ADDRESS "127.0.0.1"
#define PORT 7000
#define BUFFER_SIZE 1024
#define SEND_DATA       "helloworld"

/*
 * @function: 进程退出时通知信号
 * @brief	: 
 * @param	: 
 * @return	: 
 */
void signalHandler(int sig)
{
    printf("recv signal:%d\n", sig);
    printf("parent exit\n");
    exit(0);
}

/*
 * @function: 同步阻塞模式
 * @brief	: 
 * @param	: 
 * @return	: 
 */
void client_block( )
{
    // 创建sockfd(默认为主动模式)
    int sock_cli = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);                 // 服务器端口
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 服务器ip inet_addr 地址格式转化, 把点分十进制转为二进制

    // connect 同步阻塞模式
    // 2. 建立到达服务器的链接(三次握手)
    if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }

    char sendbuf[BUFFER_SIZE];
    char recvbuf[BUFFER_SIZE];
    while (fgets(sendbuf, sizeof(sendbuf), stdin) != NULL)
    {
        // send 同步阻塞模式
        send(sock_cli, sendbuf, strlen(sendbuf), 0);
        if (strcmp(sendbuf, "exit\n") == 0)
            break;
        // 同步阻塞模式
        recv(sock_cli, recvbuf, sizeof(recvbuf), 0);
        fputs(recvbuf, stdout);

        memset(sendbuf, 0, sizeof(sendbuf));
        memset(recvbuf, 0, sizeof(recvbuf));
    }

    close(sock_cli);
}

/*
 * @function: 同步非阻塞IO
 * @brief	: 
 * @param	: 
 * @return	: 
 */
void client_dontblock( )
{
    // 创建sockfd(默认为主动模式)
    int sock_cli = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);                 // 服务器端口
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 服务器ip inet_addr 地址格式转化, 把点分十进制转为二进制

    // connect 同步阻塞模式
    // 2. 建立到达服务器的链接(三次握手)
    if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }

    char sendbuf[BUFFER_SIZE];
    char recvbuf[BUFFER_SIZE];
    while (fgets(sendbuf, sizeof(sendbuf), stdin) != NULL)
    {

        if (strcmp(sendbuf, "exit\n") == 0)
            break;

        // send 同步非阻塞模式
        while (send(sock_cli, sendbuf, strlen(sendbuf), MSG_DONTWAIT) == -1)
        {
            sleep(10);
            printf("sleep\n");
        }

        // send 同步非阻塞模式
        while(recv(sock_cli, recvbuf, sizeof(recvbuf), MSG_DONTWAIT) == -1)
        {
            sleep(10);
            printf("sleep\n");
        }
        fputs(recvbuf, stdout);
        memset(sendbuf, 0, sizeof(sendbuf));
        memset(recvbuf, 0, sizeof(recvbuf));
    }

    close(sock_cli);
}

/*
 * @function: 点对点通信
 * @brief	: 
 * @param	: 
 * @return	: 
 */
void peer2peer( )
{
    int sock_cli = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }

    pid_t pid;
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }
    else if (pid == 0)  // 子进程接收数据
    {
        char recvbuf[BUFFER_SIZE];
        while (true)
        {
            memset(recvbuf, 0, sizeof(recvbuf));
            int ret = read(sock_cli, recvbuf, sizeof(recvbuf));
            if (ret == -1)
            {
                perror("read");
            }
            else if (ret == 0) // 服务端已关闭
            {
                printf("service closed\n");
                kill(pid, SIGUSR1);
                break;
            }
            fputs(recvbuf, stdout);
        }
        close(sock_cli);
    }
    else // 父进程发送数据
    {
        signal(SIGUSR1, signalHandler); // 处理信号
        char sendbuf[BUFFER_SIZE] = {0};
        while (fgets(sendbuf, sizeof(sendbuf), stdin) != NULL)
        {
            write(sock_cli, sendbuf, sizeof(sendbuf));
            memset(sendbuf, 0, sizeof(sendbuf));
        }
        close(sock_cli);
    }
}

/*
 * Linux 下正确的异步的connect写法
 */
int client_select( )
{
    //1.创建一个socket
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd == -1)
    {
        cout << "create client socket error." << endl;
        return -1;
    }

    //连接成功以后，我们再将 clientfd 设置成非阻塞模式，
    //不能在创建时就设置，这样会影响到 connect 函数的行为
    int oldSocketFlag = fcntl(clientfd, F_GETFL, 0);
    int newSocketFlag = oldSocketFlag | O_NONBLOCK;
    if (fcntl(clientfd, F_SETFL,  newSocketFlag) == -1)
    {
        close(clientfd);
        cout << "set socket to nonblock error." << endl;
        return -1;
    }

    //2.连接服务器
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    serveraddr.sin_port = htons(PORT);
    for (;;)
    {
        int ret = connect(clientfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
        if (ret == 0)
        {
            cout << "connect to server successfully." << endl;
            close(clientfd);
            return 0;
        } 
        else if (ret == -1) 
        {
            if (errno == EINTR)
            {
                //connect 动作被信号中断，重试connect
                cout << "connecting interruptted by signal, try again." << endl;
                continue;
            } else if (errno == EINPROGRESS)
            {
                //连接正在尝试中
                break;
            } else {
                //真的出错了，
                close(clientfd);
                return -1;
            }
        }
    }

    fd_set writeset;             // 一组文件描述字(fd)的集合，它用一位来表示一个fd
    FD_ZERO(&writeset);          // 将指定的文件描述符集清空，在对文件描述符集合进行设置前，必须对其进行初始化，如果不清空，由于在系统分配内存空间后，通常并不作清空处理，所以结果是不可知的
    FD_SET(clientfd, &writeset); // 在文件描述符集合中增加一个新的文件描述符。
    // FD_CLR(clientfd, &writeset); // 删除一个文件描述符夫
    // FD_ISSET(clientfd, &writeset); // 判断文件描述符是否存在集合中

    //可以利用tv_sec和tv_usec做更小精度的超时控制
    struct timeval tv;
    tv.tv_sec = 3;  
    tv.tv_usec = 0;
    if (select(clientfd + 1, NULL, &writeset, NULL, &tv) != 1)
    {
        cout << "[select] connect to server error." << endl;
        close(clientfd);
        return -1;
    }

    int err;
    socklen_t len = static_cast<socklen_t>(sizeof err);
    if (::getsockopt(clientfd, SOL_SOCKET, SO_ERROR, &err, &len) < 0)
    {
        close(clientfd);
        return -1;
    }

    if (err == 0)
        cout << "connect to server successfully." << endl;
    else
        cout << "connect to server error." << endl;

    //5. 关闭socket
    close(clientfd);

    return 0;
}

int main(int argc, char *argv[])
{
    client_block();
    // client_dontblock();
    // client_select();
    // peer2peer();
    return 0;
}