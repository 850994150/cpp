/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2019-03-20 15:20:16
 * Filename     : stack.cpp
 * Description  : 栈的使用
 ***********************************************************
 */

#include <iostream>
#include <string>
#include <stack>
using namespace std;

void queue()
{

}

/*
 * @function: 判断是否是有效括号
 * @brief	: 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。
 *            括号必须以正确的顺序关闭，”()” 和 “()[]{}” 是有效的但是 “(]” 和 “([)]” 不是。 
 *            遇到左括号就入栈，遇到右括号就判断栈顶是否是对应的左括号, 是则出栈
 * @param	: 
 * @return	: 
 */
bool isValidBrackets(string str)
{
    stack<char> brackets;
    for(auto x : str)
    {
        if (x == '(' || x == '[' || x == '{')
        {
            brackets.push(x);
        }
        else if(brackets.empty())
        {
            return false;
        }
        else
        {
            if (x == ')' && brackets.top() != '(')
                return false;
            if (x == ']' && brackets.top() != '[')
                return false;
            if (x == '}' && brackets.top() != '{')
                return false;
            brackets.pop();
        }
    }
    return brackets.empty();
}


/*
 * @function: 两个栈实现一个队列
 * @brief	: 队列先进先出，栈先进后出
 *            方法一： 
 *            入队的时候全都入到stack1，出队的时候先把stack1全倒进stack2，然后stack2 pop顺序就是出队顺序了
 *            pop时直接把stack1倒到stack2会有个问题: 如果先入队1 2 3 4 5 ，再出队 1 2 3 ，再入队 6，如果继续出队应该是 4 5 6
 *            修改: 出队时, 如果stack2为空才把stack1倒进stack2，否则直接stack2.pop
 *                 这样的话, 等stack2出完了，再把stack1倒进来，还是可以保证正确出队顺序的
 * 
 * @param	:  https://www.cnblogs.com/tracyhan/p/5490775.html
 * @return	: 
 */
class CQueue
{
  public:
    int pop();
    void push(int x);
    bool empty();
    int size();

  private:
    stack<int> _stack1;
    stack<int> _stack2;
};

int CQueue::pop()
{
    int tmp;
    if (_stack2.empty())  // stack2的元素出完了再倒进去
    {
        while (!_stack1.empty())
        {
            // int tmp = _stack1.top();
            _stack2.push(_stack1.top());
            _stack1.pop();
        }
    }
    else
    {
        tmp = _stack2.top();
        _stack2.pop();
    }
    cout << tmp << endl;
    return tmp;
}

void CQueue::push(int x)
{
    _stack1.push(x);
}

bool CQueue::empty()
{
    return _stack1.empty() && _stack2.empty();
}

int CQueue::size()
{
    return _stack1.size() + _stack2.size();
}

void QueueTest()
{
    
    CQueue clqueue;
    for (size_t i = 0; i < 10; i++)
    {
        clqueue.push(i);
    }
    cout << "队长度: " << clqueue.size() << endl;
    for (size_t i = 0; i < 5; i++)
    {
        clqueue.pop();
    }
    cout << "队长度: " << clqueue.size() << endl;
    cout << "是否空: " << clqueue.empty() << endl;
    clqueue.push(100);
    cout << "队长度: " << clqueue.size() << endl;
    for (size_t i = 0; i < clqueue.size(); i++)
    {
        clqueue.pop();
    }
}

void bracketsTest()
{
    string str = "()[]{[(]})";
    string str2 = "{[]}";
    string str3 = "{[}]";
    cout << "括号是否匹配: " << isValidBrackets(str3) << endl;

}

int main(int argc, char *argv[])
{
    QueueTest();
    // bracketsTest();
    return 0;
}