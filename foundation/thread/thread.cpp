/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2018-12-06 19:51:03
 * Filename     : thread.cpp
 * Description  :
	* 线程创建 * 线程参数 * mutex锁 * 线程管理 * 并发设计模式
 ***********************************************************
 */
#include <iostream>
#include <list>
#include <vector>
#include <algorithm> // for_each 头文件
#include <chrono>
#include <numeric>
// c++11 支持多线程的相关头文件
#include <thread>
#include <mutex> // lock、unlock、call_once
#include <atomic>
#include <future>         // std::promise, std::future
#include <condition_variable>

using namespace std;

volatile int g_counter(0);
std::atomic<int> g_atomic_counter(0); // atomic是一个类模板
mutex g_lock;
std::condition_variable iMsg;

// 线程锁
void func_mutex(void)
{
	for(size_t i = 0; i < 10000000; i++)
	{
		// mutex
		// mutex是一个类对象, 其中包含成员函数lock、unlock、try_lock
		// 有lock一定要有unlock, 否则会导致程序异常
		// try_lock: 尝试锁住互斥量, 如果互斥量已经被别的线程锁住了也不阻塞
		// 1. lock、unlock、try_lock
		/*
		g_lock.lock();
		++g_counter;
		// ... do_something
		g_lock.unlock();
		*/

		/*
		if (g_lock.try_lock()) // 适合定时执行一个job的场景, 一个线程执行就可以, 可以用更新时间戳辅助
		{
			++g_counter;
			g_lock.unlock();
		}
		*/

		// 2. lock_guard
		// 是一个类模板，可替代lock、unlock，有了guard就不能出现lock、unlock了，它会自动加解锁
		// 原理: 这是个类模板所以声明对象的时候会调用构造函数，构造函数里加锁; 在退出作用域的时候会自动调用析构函数来解锁
		// 不用自己写lock、unlock，但有个问题这个lock_guard只有在析构的时候（return的时候）才能解锁, 不够灵活。。
		// 或者用大括号把加锁和解锁的地方扩起来来达到限定作用域的作用
		/*
		{
			std::lock_guard<std::mutex>my_lock_guard(g_lock);
			++g_counter;
			// ... do_something
		}
		*/

		// 3. unique_lock
		// lock_guard限制得太死了, 只有构造时加锁和析构时解锁, 我们要尽可能的减小锁定的区域，也就是锁的颗粒度。
		// std:unique_lock模板类, 具有lock_guard的所有功能, 而且更加灵活地提供lock和unlock函数,能记录现在处于上锁还是没上锁状态,
		// 因此可以在适当的时候加解锁, 在析构的时候，会根据锁的状态来决定是否要进行解锁（lock_guard就一定会解锁)
		// unique_lock还支持同时锁定多个互斥量, 避免死锁问题
		// 参数 adopt_lock 表示构造函数不加锁, 但是必需在unique_lock之前上锁, 否则结果会错误;
		// 参数 defer_lock 表示不进行上锁的操作, unique_lock对象可以更灵活地控制加解锁

		// g_lock.lock(); // while args is adopt_lock
		std::unique_lock<std::mutex> my_unique_lock(g_lock, std::defer_lock);
		my_unique_lock.lock(); // while args is defer_lock
		++g_counter;
		my_unique_lock.unlock();


		// 死锁

		/*
		产生原因：
		陷入互相等待的状态
		A线程锁住了mutex1, 在想用mutex2锁住的变量时尝试锁mutex2, 发现mutex2被锁了, 等待mutex2释放
		B线程锁住了mutex2, 在想用mutex1锁住的变量时尝试锁mutex1, 发现mutex1被锁了, 等待mutex1释放
		解决：
		1. 原因是A、B线程锁互斥量的顺序不一致, 解锁顺序倒是不影响
		2. std:lock() 函数模板
		   std:lock(mutex1, mutex 2)
		   解锁还是要手工unlock()，解锁顺序不影响
		   可以一次锁住>=2个互斥量，不存在因锁的顺序问题而导致死锁的存在，会等所有都锁住才继续往下走
		   原理:
		   如果有一个互斥量没锁成功，则会释放掉已锁成功的互斥量，过段时间再去尝试，直到把所有互斥量都锁住为止
		   缺点:
		   lock()解决死锁的痛点在于存在忘记unlock的危险，而lock_guard刚好可以自动unlock，可否两者优点都有呢？
		3. lock() 和 lock_guard
		   使用lock_guard的adopt_lock参数可以做到，让lock_guard构造的时候不lock, 但是必需在lock_guard之前加锁
		   std:lock（mutex1,mutex2)
		   lock_guard<mutex>lock_guard(mutex1, adopt_lock)
		*/

		// 4. atomic 原子操作
		g_atomic_counter++; // 类模板atomic声明的对象确保了该操作是原子性的, 不需要加锁
	}
}


void ThreadMutex()
{
	thread threads[2];
	
	for(size_t i = 0; i < 2; ++i)
	{
		threads[i] = thread(func_mutex);
	}

	for (auto &th : threads)
	{
		th.join();
	}
	// 多次运行输出值不变才是正确的
	cout << "g_counter = " << g_counter << endl;
}

// 将线程转移到另一个线程, 线程只能转移, 不能被复制
void ThreadSwap(void)
{
	int a = 1;
	thread t([](int *pa) {
		for (;;){
			*pa = (*pa * 33) % 0x7fffffff;
			if (((*pa) >> 30) & 1)
				break;
		}
	},
			 &a);
	thread t2;

	cout << "before: t=" << t.get_id() << ", t2=" << t2.get_id() << endl;
	// swap(t, t2);
	t2 = move(t);
	cout << "after: t=" << t.get_id() << ", t2=" << t2.get_id() << endl;
	t2.join();
	cout << "a=" << a << endl;
}

class CThread
{
  public:
	void showThread(int a, int b)
	{
		cout << "子线程2开始" << endl;
		cout << a + b << endl;
		cout << "子线程2结束" << endl;
	}

	void inMsgRecQueue()
	{
		for (int i = 0; i < m_iCommand; i++)
		{
			// m_mutexs.lock();
			std::unique_lock<std::mutex> my_unique_lock(m_mutexs);

			cout << "inMsgRecvQueue(): " << i << endl;
			msgRecvQueue.push_back(i);

			// m_mutexs.unlock();

			my_unique_lock.unlock();
			iMsg.notify_one();
		}
	}

	void outMsgRecvQueue()
	{
		for (int i = 0; i < m_iCommand; i++)
		{
			// m_mutexs.lock();
			std::unique_lock<std::mutex> my_unique_lock(m_mutexs);
			if (!msgRecvQueue.empty())
			{
				int command = msgRecvQueue.front();
				cout << "outMsgRecvQueue(): " << command << endl;
				msgRecvQueue.pop_front();
			}
			else
			{
				iMsg.wait(my_unique_lock); // 线程休眠 , 当队列中没有数据时用wait()让线程进入休眠状态,不继续循环;
				cout << "outMsgRecvQueue(), msgRecvQueue is empty" << endl;
				i--; // 为了保证全部输出, 如果queue没有数据要返回一次循环次数
			}
			my_unique_lock.unlock();

			// m_mutexs.unlock();
		}
	}
	list<int> msgRecvQueue; // 竞争资源
  private:
	mutex m_mutexs;
	const int m_iCommand = 10000;
};

void ThreadLock()
{
	CThread clThread;

	// 如果生产者产生得很慢, (比如消费者线程先执行)消费者的循环次数就会增加, 而且都在做无用功;
	// condition_variable可解决(配合unique_lock)
	// notify_once()唤醒处于wait中的其中一个条件变量（可能当时有很多条件变量都处于wait状态）
	thread myOutThread = thread(&CThread::outMsgRecvQueue, &clThread); // 消费
	thread myInThread = thread(&CThread::inMsgRecQueue, &clThread); // 生产

	myInThread.join();
	myOutThread.join();
}

void SonThread(int &a, int b)
{
	cout << "子线程1开始" << endl;
	a += 1;
	b += 1;
	cout << a + b << endl;
	cout << "子线程1退出"<<endl;
}

void ThreadCreate()
{
	// 默认情况下，所有的参数都将【拷贝】到新线程的内部存储中。

	cout << "主线程开始" << endl;
	int a(30), b(40);
	cout << "\n-------------1. 函数指针; 给函数传入引用------------\n" << endl;
	cout << "a: " << a << ", b: " << b << endl;
	thread funcThread(SonThread, std::ref(a), b);
	funcThread.join();
	cout << "a: " << a << ", b: " << b << endl;

	cout << "\n-------------2. lambda表达式---------------\n" << endl;
	thread LambdaFunc([]()
	{
		cout << "Thread Lambda Function\n";
	});
	LambdaFunc.join();

	cout << "\n--------------3. 类成员函数----------------\n" << endl;
	CThread clThread;
	thread ClassFuncThread(&CThread::showThread, &clThread, 3, 4);
	// 如果在类成员函数创建线程, 线程函数也是类成员, 则第二参数为this
	// Q: 为什么使用类成员函数作为线程函数入口就要传入一个对象?
	// A: 可以不传入对象, 把入口函数定义为静态成员函数就可以, 但是这样的话这个函数里面就不可以调用该类的其他非静态成员了
	//    之所以要传入对象, 和“A类中如何调用B类的成员函数"的问题是一样的; https://bbs.csdn.net/topics/390859834 
	// 至于为什么不能是非静态成员函数呢, 因为非静态成员函数都会在参数列表中加上一个this指针为为参数, 这样的话你写的线程
	// 函数就不符合调用规定了.


	ClassFuncThread.join();

	cout << "\n-------------4. 创建多个线程, 与vector结合----------------\n" << endl;
	vector<thread> vecThread;
	cout << "a: " << a << ", b: " << b << endl;
	for(size_t i = 0; i < 10; i++)
	{
		vecThread.push_back(thread(SonThread, std::ref(a), b));
	}
	for (auto &itor : vecThread) // 因为要让vecThread中的所有线程都执行完, 所以要用引用
	{
		itor.join();
	}
	cout << "a: " << a << ", b: " << b << endl;


	cout << "主线程结束" << endl;
}

// 线程管理
void ThreadManager(void)
{
}

void setValue(std::future<int> &fut, int value)
{
	std::promise<int> prom;				  // 用来包装数据, 将数据与 future对象 关联 
	fut = prom.get_future();
	int values = value +10;
	std::this_thread::sleep_for(chrono::seconds(5)); // 休眠线程, 观察future阻塞现象, 必须放在关联之后，否则会报异常
	prom.set_value(values);				  // 设置共享状态的值, 此处和线程print_thread保持同步.
}

void printValue(std::future<int> &fut)
{
	// future有三种操作: get：等待结果并返回; wait:等待异步操作完成; 没有返回值, wait_for超时等待返回future_status状态
	int x = fut.get(); // 等待异步操作并获取返回的值. 线程会阻塞在这里,直至promise执行set_value
	// 移动语义, 此处get后fut结果已经转移到x了,其他地方再get的话会报错(可改用shared_future)
	std::cout << "value: " << x << '\n';
}

/*
promise 对象可以保存某一类型 T 的值，该值可被 future 对象读取（可能在另外一个线程中）, 可以通过 get_future 来获取
与该 promise 对象相关联的 future 对象，调用该函数之后，两个对象共享相同的共享状态(shared state)
promise 对象是异步 Provider，它可以在某一时刻设置共享状态的值。
future 对象可以异步返回共享状态的值，或者在必要的情况下阻塞调用者并等待共享状态标志变为 ready，然后才能获取共享状态的值。
*/
// 线程同步
void ThreadFuture()
{
	// 虽然用 condition_variable 也可以做, 但是condition_variable 有诸多问题
	// 1. 不容易应付异常, notify之前给抛异常了, 另一边就会一直等.
	// 2. 每个”返回值”都需要一个mutex, 一个变量用于储存, 一个条件变量, 用的多了, 传参数就很麻烦, 也容易有重复代码.
	// 3. 没处理意外唤醒, 要处理还得加个flag, 问题2更严重了.

	cout << "线程同步开始" << endl;
	std::future<int> fut;								 // 异步结果的传输通道
	std::thread set_thread(setValue, std::ref(fut), 100);
	std::thread print_thread(printValue, std::ref(fut));

	for(size_t i = 0; i < 10; i++)
	{
		std::this_thread::sleep_for(chrono::seconds(1));
		cout << "主线程在运行..." << endl;
	}

    set_thread.join();
    print_thread.join();

	cout << "线程同步结束" << endl;
}


// 异步接口async
// 综合了线程创建和同步以及获取线程结果了
std::string fetchDataFromDB(int count, std::string recvData)
{
	// dosomething ...
	for(size_t i = 0; i < count; i++)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1)); // 处理时间为5s
		cout << "handling data from db..." << i << endl;
	}
	
	return "DB_" + recvData;
}

std::string fetchDataFromFile(int count, std::string recvData)
{
	// dosomething ...
	for(size_t i = 0; i < count; i++)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1)); // 处理时间为10s
		cout << "handling data from file..." << i << endl;
	}
	
	return "File_" + recvData;
}

void ThreadAsync()
{
	// 自动创建一个线程(或从内部线程池中挑选)和一个promise对象。
	// 然后将std::promise对象传递给线程函数，并返回相关的std::future对象
	// 当我们传递参数的函数退出时，它的值将被设置在这个promise对象中，所以最终的返回值将在std::future对象中可用

	int iFileTime = 5;
	int iDbTime = 10;
	cout << "处理开始" << endl;
	// std::launch::async，表示立即开启异步求值
	// std::launch::deferred，延迟开启，只有当返回的future实例调用get函数时才开启异步求值
	std::future<std::string> resultFromDB = std::async(std::launch::async, fetchDataFromDB, iDbTime, "Data");
	std::future<std::string> resultFromFile = std::async(std::launch::async, fetchDataFromFile, iFileTime, "Data");

	for(size_t i = 0; i < 20; i++)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		cout << "main thread dosomething..." << i << endl;
	}

	std::string dbData = resultFromDB.get();
	// 主线程从DB获取数据, 数据在future<std::string>对象中可获取之前将一直【阻塞】在此
	std::string fileData = resultFromFile.get();
	// Q: 还是要阻塞直到返回, 但是线程处理时间不可预知, 有没有方法像notify一下呢? 这样的话, 主线程可以及时知道
	// A: 解决方法: 使用单独线程去轮询future结果是否返回, 参考 threadpooltest.cpp

	cout << "处理结束" << endl;
}

// 能确保加减、读写是原子性的, 但对于需要复杂判断的就不方便使用了
void ThreadAutomic()
{
	thread threads[2];
	
	for(size_t i = 0; i < 2; ++i)
	{
		threads[i] = thread(func_mutex);
	}

	for (auto &th : threads)
	{
		th.join();
	}
	cout << "g_atomic_counter = " << g_atomic_counter << endl;
}

int main(int argc, char const *argv[])
{
	// ThreadCreate();
	// ThreadMutex();
	// ThreadAutomic();
	// ThreadLock();
	// ThreadFuture();
	// ThreadSwap();
	ThreadAsync();
	return 0;
}
