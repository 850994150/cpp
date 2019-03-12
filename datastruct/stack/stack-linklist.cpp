/***********************************************************
* Author       : M_Kepler
* EMail        : hellohuangjinjie@gmail.com
* Last modified: 2016-04-15 22:51:00
* Filename     : stack-linklist.cpp
* Description  : 用链表实现栈
    * 图解看我博客
    * 入栈的新节点 p 的指针域top的位置:p->link = plstack->top
        * 然后再把top指向新节点 p: plstack->top = p
    * 出栈,修改一下top然后释放空间: plstack->top = plstack->top->link
**********************************************************/

#include <malloc.h>
#include <iostream>
using namespace std;

typedef int DataType;
struct Node
{
    DataType data;
    struct Node *link;
};
typedef Node *PNode;

struct LinkStack
{
    PNode top;
};
typedef LinkStack *PLinkStack;

PLinkStack createEmptyStack()
{
    PLinkStack plstack = (PLinkStack)malloc(sizeof(struct LinkStack));
    if (plstack != NULL)
        plstack->top = NULL;
    else
        cout << "Out of spaces\n";
    return plstack;
}

int isEmpty(PLinkStack plstack)
{
    return plstack->top == NULL;
}

/*
top --->[data]-[link] 栈顶
                 ↓
        [data]-[link]
                 .
                 .
                 .
                 ↓
        [data]-[null] 栈底
*/
void push(PLinkStack plstack, DataType x)
{
    PNode p = (PNode)malloc(sizeof(struct Node));
    if (p != NULL)
    {
        p->data = x;
        //新元素的指针域指向原栈顶元素。
        p->link = plstack->top;
        //新加入的元素作为栈顶。
        plstack->top = p;
    }
    else
        cout << "Out of space\n";
}

void pop(PLinkStack plstack)
{
    PNode p = (PNode)malloc(sizeof(struct Node));
    if (p != NULL)
    {
        p = plstack->top;
        plstack->top = plstack->top->link;
        //栈顶元素的下一个元素作为新的栈顶。
        free(p);
    }
    else
        cout << "Empty stack\n";
}

DataType getTop(PLinkStack plstack)
{
    if (plstack->top == NULL)
        cout << "Stack is Empty" << endl;
    else
        return plstack->top->data;
}

//输出栈顶元素并出栈
void get_pop(PLinkStack plstack)
{
    PNode p = (PNode)malloc(sizeof(struct Node));
    if (isEmpty(plstack))
        cout << "Empty Stack" << endl;
    else
    {
        cout << plstack->top->data;
        p = plstack->top;
        plstack->top = plstack->top->link;
        free(p);
    }
}

int main()
{
    cout << "input stack length" << endl;
    int n;
    cin >> n;
    int t = n;
    int item;
    PLinkStack plstack = createEmptyStack();
    cout << "please input item\n";

    while (n)
    {
        cin >> item;
        push(plstack, item);
        n--;
    }
    cout << "output\n";
    while (t)
    {
        get_pop(plstack);
        cout << " ";
        t--;
    }
    return 0;
}
