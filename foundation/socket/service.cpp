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
#define PORT 7000
#define QUEUE 20
int conn;
void thread_task()
{
}

int one_client()
{
    int ss = socket(AF_INET, SOCK_STREAM, 0); // 1. 创建套接字
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET; // IPV4协议族, IPV6:AF_INET6
    server_sockaddr.sin_port = htons(PORT); // htons 转化为网络字节序(大端) h表示host,n表示network,s表示short,l表示long
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(ss, (struct sockaddr *)&server_sockaddr, sizeof(server_sockaddr)) == -1) // 2. 绑定地址和端口
    {
        perror("bind");
        exit(1);
    }
    if (listen(ss, QUEUE) == -1) // 3. 设置套接字为监听模式, 准备接收客户端请求
    {
        perror("listen");
        exit(1);
    }

    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);
    conn = accept(ss, (struct sockaddr *)&client_addr, &length); // 4. 客户请求到来时接收, 返回一个该连接的套接字
    if (conn < 0)
    {
        perror("connect");
        exit(1);
    }

    char buffer[1024];
    //创建另外一个线程
    //std::thread t(thread_task);
    //t.join();
    //char buf[1024];
    //主线程
    while (1)
    {

        // memset(buf, 0 ,sizeof(buf));
        // if(fgets(buf, sizeof(buf),stdin) != NULL) {
        //     send(conn, buf, sizeof(buf), 0);
        // }

        memset(buffer, 0, sizeof(buffer));
        int len = recv(conn, buffer, sizeof(buffer), 0); // 5.1 用accept返回的套接字进行通信
        if (strcmp(buffer, "exit\n") == 0)
            break;
        printf("%s", buffer);
        //必须要有返回数据， 这样才算一个完整的请求
        send(conn, buffer, len, 0);     // 5.1 用accept返回的套接字进行通信
    }
    close(conn); // 6. 关闭套接字
    close(ss);
    return 0;
}

void multi_client()
{

}

void multi_client_select()
{

}

void multi_client_poll()
{

}

void multi_client_epoll()
{
}


int main(int argc, char *argv[])
{
    one_client();
    return 0;
}