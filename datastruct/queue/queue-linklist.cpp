/***********************************************************
* Author       : M_Kepler
* EMail        : hellohuangjinjie@gmail.com
* Last modified: 2016-04-15 19:18:01
* Filename     : queue-linklist.cpp
* Description  : 队列的链式表示
    * 与queue-seqlist不同的是：
        * r指向当前队定,而顺序队列中是指向下一个入队位置
        * f指向当前队低
    * 入队出队
        * 在queue-seqlist中不必考虑第一个入队的元素
        * 要是不考虑是不是第一个元素的话，由于r是指向当前队定
        * 而入队p将被放在plqueue->r->link的位置，既NULL
**********************************************************/

#include <iostream>
#include <malloc.h>
using namespace std;

typedef int DataType;
struct QNode
{
    DataType data;
    struct QNode *link;
};
typedef struct QNode *PNode;

//r为低 f为顶
struct LinkQueue
{
    PNode f;
    PNode r;
};
typedef struct LinkQueue * PLinkQueue;

PLinkQueue createEmptyQueue()
{
    PLinkQueue plqueue = (PLinkQueue) malloc (sizeof(struct LinkQueue));
    if(plqueue != NULL)
    {
        plqueue ->f = NULL;
        plqueue ->r =NULL;
    }
    else
        printf("Out of space\n");
    return plqueue;
}

int isEmptyQueue(PLinkQueue plqueue)
{
    return (plqueue ->f == NULL);
}

void enQueue( PLinkQueue plqueue, DataType x)
{
    PNode p = (PNode) malloc (sizeof(struct QNode));
    if(p!= NULL)
    {
        p->data = x;
        p->link = NULL;
        //第一个元素的话
        if(plqueue ->f == NULL)
            plqueue->f = p;
        else
            plqueue ->r -> link = p;
        plqueue->r =p;
    }
    else
        printf("Out of space\n");
}

void deQueue(PLinkQueue plqueue)
{
    PNode p = (PNode) malloc (sizeof(struct QNode));
    if(plqueue->f == NULL)
        printf("Empty Queue\n");
    else
    {
        p = plqueue ->f;
        plqueue -> f = p ->link;
        free(p);
    }

}

DataType getFront(PLinkQueue plqueue)
{
    if(plqueue ->f == NULL)
        printf("Empty Queue\n");
    else
        return (plqueue ->f ->data);
}
int main()
{
    PLinkQueue lqueue = createEmptyQueue();
    cout<<"创建一个n元素的队列\n输入n"<<endl;
    int n,t;
    cin>>n;
    t = n;
    while(n)
    {
        int data;
        cin>>data;
        enQueue(lqueue,data);
        n--;
    }
    cout<<"取队头并出队"<<endl;
    while(t)
    {
        cout<<getFront(lqueue)<<" ";
        deQueue(lqueue);
        t--;
    }
    cout<<endl;
    return 0;
}
