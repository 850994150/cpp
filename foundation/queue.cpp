/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2019-03-20 16:35:09
 * Filename     : queue.cpp
 * Description  :  
 ***********************************************************
 */

#include <iostream>
#include <queue>
using namespace std;

/*
 * @function: 使用两个队实现一个栈
 * @brief	: 
 * @param	: 
 * @return	: 
 */
class CStack
{
  public:
    void push(int x);
    void pop();

  private:
    queue<int> _queue1;
    queue<int> _queue2;
};

void CStack::push(int m)
{
    _queue1.push(m);
}

void CStack::pop()
{
    // 把n-1个元素转移到队列2，则剩下的那个元素就是最后入队的元素
    int queue1size = _queue1.size();
    for (int i = 0; i < queue1size - 1; i++)
    {
        _queue2.push(_queue1.front());
        _queue1.pop();
    }
    int m = _queue1.front();
    _queue1.pop();

    // 把队列2的元素返回队列1
    int queue2size = _queue2.size();
    for (int j = 0; j < queue2size ; j++)
    {
        _queue1.push(_queue2.front());
        _queue2.pop();
    }
    cout << m << endl;
}


void CStackTtest()
{
    CStack clStack;
    clStack.push(1);
    clStack.push(2);
    clStack.push(3);
    clStack.push(4);

    clStack.pop();
    clStack.pop();
    clStack.pop();
    clStack.push(5);
    clStack.push(6);
    clStack.pop();
    clStack.pop();
    clStack.pop();

}

int main(int argc, char *argv[])
{
    CStackTtest();
    
    return 0;
}