/***********************************************************
* Author       : M_Kepler
* EMail        : hellohuangjinjie@gmail.com
* Last modified: 2016-04-15 19:17:25
* Filename     : queue-seqlist.cpp
* Description  : 头尾相连的环形队列
    * 创建:和创建顺序表一样，结构体需要包含两个指向队头尾的指针
        * floor 总是指队低既下一个要出队的位置
        * roof  总是指队顶即下一个要入队的位置
    * 初始化:f、r都指向0
    * 环形队列:
        * 假溢出:出队时f一直往r的方向挪动,f前的空间却没利用
        * 环形队列可以解决假溢出的问题
        * 构造:
            * 头尾相接就可以 当paqu->s[MAXNUM-1]!=NULL,paqu->r=0
        * 满队?:
            * 如果不是循环队列的话这样判断:paqu->r == MAXNUM-1
            * 如果已经有了MAXNUM-1个元素,可以再入一个,那么r将会指向0
            * 那就是paqu->r == paqu->f =0了,和空队混淆,解决方法是牺牲一个空间,
            * 当n = MAXNUM-1 即称满
        * 由于是环形，所以所求的下标要注意是:paqu->r%MAXNUM
**********************************************************/

#include <iostream>
#include <malloc.h>
#define MAXNUM 9999
using namespace std;
typedef int DataType;
struct SeqQueue
{
    int f;
    int r;
    //floor地板, roof屋顶
    DataType s[MAXNUM];
};
typedef struct SeqQueue* PSeqQueue;

PSeqQueue createEmptyQueue()
{
    PSeqQueue paqu = (PSeqQueue) malloc (sizeof(struct SeqQueue));
    if( paqu != NULL)
        paqu ->f = paqu->r = 0;
    else
        printf("Out of Space\n");
    return paqu;
}

int isEmptyQueue_seq(PSeqQueue paqu)
{
    return (paqu->r == paqu->f);
}

int isFullQueue_seq(PSeqQueue paqu)
{
    //试探r+1的位置是不是f
    return ((paqu->r+1) % MAXNUM == paqu->f);
}

void enQueue_seq(PSeqQueue paqu, DataType x)
{
    if(isFullQueue_seq(paqu))
        printf("Full queue.\n");
    else
    {
        paqu->s[paqu->r] = x;
        //是考虑到了到环形队列的假溢出
        paqu->r = (paqu->r+1) % MAXNUM;
    }
}

void deQueue_seq(PSeqQueue paqu)
{
    if(paqu->f == paqu->r)
        printf("Empty Queue\n");
    else
        paqu->f = (paqu->f+1) % MAXNUM;
}

DataType forntQueue_seq(PSeqQueue paqu)
{
    if(paqu->f == paqu->r)
        printf("Empty Queue\n");
    else
        return (paqu->s[paqu->f]);
}

int main()
{
    PSeqQueue paqu = createEmptyQueue();
    cout<<"创建一个n元素的队列\n输入n"<<endl;
    int n,t;
    cin>>n;
    t = n;
    while(n)
    {
        int data;
        cin>>data;
        enQueue_seq(paqu,data);
        n--;
    }
    cout<<isEmptyQueue_seq(paqu)<<endl;
    cout<<"取队头并出队"<<endl;
    while(t)
    {
        cout<<forntQueue_seq(paqu)<<" ";
        deQueue_seq(paqu);
        t--;
    }
    cout<<endl;
    return 0;
}
