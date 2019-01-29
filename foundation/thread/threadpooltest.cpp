#include <vector>
#include <chrono>
#include <iostream>
#include "ThreadPool.h"

#include <chrono>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;
std::vector<std::shared_future<string>> results;

void SignalHandler(int signal)
{
    int stat;
    pid_t sub_pid;
    while ((sub_pid = waitpid(-1, &stat, WNOHANG)) > 0)
    {
        printf("【Handler - waitpid】get sub process %d exited signal!\tstat:%d\n", sub_pid, stat);
    }
}

int test()
{
    // create thread pool with 4 worker threads before dosomething...
    ThreadPool pool(4);

    // enqueue and store future
    auto result = pool.enqueue([](int answer) { return answer; }, 42);

    // get result from future, print 42
    std::cout << result.get() << std::endl;
}

/*
 * @brief	: 子进程异步发送信息
 *            不可取, 因为消息是在父进程中产生的,多开一个进程反而多余
 */
int send_msg_by_process()
{
    cout << thread::hardware_concurrency() << endl;
    vector<int> ivecMsg{1, 2, 3, 4, 5, 6, 7, 8, 9};
    pid_t pid = fork();
    if (pid < 0)
    {
        printf("fork error");
    }
    else if (pid == 0)
    {
        ThreadPool pool(4);
        std::vector<std::future<int>> results;
        for (int i = 0; i < ivecMsg.size(); ++i)
        {
            results.emplace_back(
                pool.enqueue([ivecMsg, i] {
                    this_thread::sleep_for(std::chrono::seconds(2));
                    return ivecMsg[i];
                }));
        }
        /* child */
        // 每1秒轮询查看任务执行进度
        std::chrono::seconds tSpan(1);
        for (auto &&result : results) //通过future.get()获取返回值
        {
            while (result.wait_for(tSpan) != std::future_status::ready)
            {
                std::cout << "sub process " << getpid() << " is running..." << std::endl;
                continue;
            }
            // 获取执行结果
            std::cout << "sub process -- tasks is done, result: " << result.get() << std::endl;
        }
    }
    else if (pid > 0)
    {
        signal(SIGCHLD, SignalHandler);

        while (true)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            cout << "【parent process】 " << getpid() << " dosomething..." << endl;
            // 如果不用多进程的话, 程序会堵在future.get那里
            // 如果使用多进程的话, 因为 ivecMsg 消息是不断变化的, 消息一直来, 也要一直发, 场景不符合多进程啊
        }
    }

    return 0;
}



void recv_thread()
{
    // 每1秒轮询查看任务执行进度
    std::chrono::seconds tSpan(1);
    // for (auto &&result : results) //通过future.get()获取返回值
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        for (auto result = results.begin(); result != results.end();)
        {
            if (result->wait_for(tSpan) != std::future_status::ready)
            {
                std::cout << "sub thread result is not ready..." << std::endl;
                continue;
            }
            if (result->wait_for(tSpan) == std::future_status::ready)
            {
                // 获取执行结果
                std::cout << "【sub thread】tasks is done, result: " << result->get() << std::endl;
                result = results.erase(result);
            }
        }
    }
}

/*
 * @brief	: 线程异步接收消息
 *            主线程持续产生消息, 并通过线程池发消息, 开一个线程异步检测消息结果
 *            只要在整个程序结束之前把线程join回来就行了
 * @return	: 
 */
int async_send_msg()
{
    cout << thread::hardware_concurrency() << endl;
    ThreadPool pool(4);
    thread thread_recv(recv_thread);

    vector<string > ivecMsg{"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
    for (int i = 0; i < ivecMsg.size(); ++i)
    {
        results.emplace_back(
            pool.enqueue([ivecMsg, i] {
                this_thread::sleep_for(std::chrono::seconds(2));
                return ivecMsg[i];
            }));
    }
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cout << "【main thread】dosomething..." << endl;
    }
    // ...

    thread_recv.join();
    return 0;
}

int main(int argc, char const *argv[])
{
    async_send_msg();
    return 0;
}
