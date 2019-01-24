/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2018-12-06 19:51:03
 * Filename     : thread.cpp
 * Description  :
	* 线程创建 * 线程参数 * mutex锁 * 线程管理 * 异步同步
 ***********************************************************
 */
#include <iostream>
#include <list>
#include <vector>
#include <algorithm> // for_each 头文件
#include <chrono>
// c++11 多线程相关头文件
#include <thread>
#include <mutex>
#include <atomic>
#include <future>         // std::promise, std::future
#include <condition_variable>

using namespace std;


volatile int counter(0);
mutex g_lock;
const int NUM = 100;

/*
 * @brief	: 互斥锁
 * @param	: 
 * @return	: 
 */
void func_mutex(void)
{
	for(size_t i = 0; i < NUM; i++)
	{
		// mutex
		// mutex是一个类对象, 其中包含成员函数lock、unlock
		// 有lock一定要有unlock, 否则会导致程序异常
		// 1. lock、unlock
		g_lock.lock();
		++counter;
		// ... do_something
		g_lock.unlock();

		// 2. lock_guard
		// 是一个类模板，可替代lock、unlock，有了guard就不能出现lock、unlock了，它会自动加解锁
		// 原理: 这是个类模板所以声明对象的时候会调用构造函数，构造函数里加锁; 在退出作用域的时候会自动调用析构函数来解锁
		// 不用自己写lock、unlock，但有个问题这个lock_guard只有在析构的时候（return的时候）才能解锁, 不够灵活。。
		// 或者用大括号把加锁和解锁的地方扩起来来达到限定作用域的作用
		/*
		{
			std::lock_guard<std::mutex>my_lock_guard(g_lock);
			++counter;
			// ... do_something
		}
		*/

		// 3. try_lock?
		/*
		if (g_lock.try_lock())
		{
			++counter;
			// ... do_something
			g_lock.unlock();
		}
		*/

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
		   使用lock_guard的adopt_lock参数可以做到，让guard构造的时候不lock
		   std:lock（mutex1,mutex2)
		   lock_guard<mutex>lock_guard(mutex1, adopt_lock)
		*/

	}
}


void ThreadMutex()
{
	thread threads[NUM];
	
	for(size_t i = 0; i < NUM; ++i)
	{
		threads[i] = thread(func_mutex);
	}

	for (auto &th : threads)
	{
		th.join();
	}
	// 多次运行输出值不变才是正确的
	cout << "counter = " << counter << endl;
}


void ThreadMove(void)
{
	int a = 1;
	thread t([](int *pa) {
		for (;;)
		{
			*pa = (*pa * 33) % 0x7fffffff;
			if (((*pa) >> 30) & 1)
				break;
		}
	},
			 &a);
	thread t2 = move(t); // 改为 t2 = t 将不能编译。
	t2.join();
	cout << "a=" << a << endl;
}


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
	cout << "before swap: t=" << t.get_id() << ", t2=" << t2.get_id() << endl;
	swap(t, t2);
	cout << "after swap : t=" << t.get_id() << ", t2=" << t2.get_id() << endl;
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
			m_mutexs.lock();

			cout << "inMsgRecvQueue(): " << i << endl;
			msgRecvQueue.push_back(i);

			m_mutexs.unlock();
		}
	}

	void outMsgRecvQueue()
	{
		for (int i = 0; i < m_iCommand; i++)
		{
			m_mutexs.lock();
			if (!msgRecvQueue.empty())
			{
				int command = msgRecvQueue.front();
				cout << "outMsgRecvQueue(): " << command << endl;
				msgRecvQueue.pop_front();
			}
			else
			{
				cout << "outMsgRecvQueue(), msgRecvQueue is empty" << endl;
				i--; // 为了保证全部输出, 如果queue没有数据要返回一次循环次数
			}
			m_mutexs.unlock();
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
	thread myInThread = thread(&CThread::inMsgRecQueue, &clThread); // 生产
	thread myOutThread = thread(&CThread::outMsgRecvQueue, &clThread); // 消费
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
	std::promise<int> prom;				  // 生成一个 std::promise<int> 对象.
	fut = prom.get_future();			  // prom对象和 future 关联.
	std::this_thread::sleep_for(chrono::seconds(5)); // 休眠线程, 观察future阻塞现象, 必须放在关联之后，否则会报异常
	prom.set_value(value);				  // 设置共享状态的值, 此处和线程print_thread保持同步.
}

void printValue(std::future<int> &fut)
{
	int x = fut.get();					 // 获取共享状态的值. 线程会阻塞在这里,直至promise执行set_value
	std::cout << "value: " << x << '\n'; // 打印 value: 10.
}

// 线程同步
/*
promise 对象可以保存某一类型 T 的值，该值可被 future 对象读取（可能在另外一个线程中）, 可以通过 get_future 来获取
与该 promise 对象相关联的 future 对象，调用该函数之后，两个对象共享相同的共享状态(shared state)
promise 对象是异步 Provider，它可以在某一时刻设置共享状态的值。
future 对象可以异步返回共享状态的值，或者在必要的情况下阻塞调用者并等待共享状态标志变为 ready，然后才能获取共享状态的值。
*/
void ThreadFuture()
{
	cout << "线程同步开始" << endl;
	std::future<int> fut;								 // 共享状态
	std::thread set_thread(setValue, std::ref(fut), 10); // 将 future 交给另外一个线程set_thread.
	std::thread print_thread(printValue, std::ref(fut));

	for (;;)
	{
		std::this_thread::sleep_for(chrono::seconds(1));
		cout << "主线程在运行..." << endl;
	}

    set_thread.join();
    print_thread.join();

	cout << "线程同步结束" << endl;
}

int main(int argc, char const *argv[])
{
	// ThreadCreate();
	// ThreadLock();
	// ThreadMutex();
	// ThreadMove();
	// ThreadSwap();
	ThreadFuture();

	return 0;
}
