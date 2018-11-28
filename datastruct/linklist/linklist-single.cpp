/***********************************************************
* Author       : M_Kepler
* EMail        : hellohuangjinjie@gmail.com
* Last modified: 2016-04-14 12:02:04
* Filename     : linklist-single.cpp
* Description  : 带头结点的单链表
    * 由于我使用0表示输入结束，所以尽量不要插入0
    * 带头结点？不带头结点？
***********************************************************/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

using namespace std;
typedef int DataType;
struct Node;
typedef struct Node * PNode;

struct Node{
    DataType info;
    PNode link;
};
typedef struct Node * LinkList;

//创建空链表
LinkList createNullList_link()
{
    LinkList llist = (LinkList)malloc (sizeof(struct Node));
    if (llist != NULL)
        llist->link = NULL;
    else
        printf("Out of space !\n");
    return llist;
}

//判断链表是否为空
int isNullList_link (LinkList llist){
    return (llist -> link == NULL);
}

//输出链表
void showLinkList(LinkList llist)
{
    PNode tmp = llist;
    while((tmp!=NULL) & (tmp->link != NULL))
    {
        tmp = tmp->link;
        cout<<tmp->info<<" ";
    }
    cout<<endl;
}

//求某元素的储存位置
PNode locate_x(LinkList llist, DataType x){
    PNode p;
    if ( llist == NULL )
        return NULL;
    p = llist -> link;
    while ( p!=NULL && p->info != x)
        p = p->link; //指针移动
    return p;
}

//单链表的插入
int insertPost_link (LinkList llist, PNode p, DataType x)
{
    PNode q = (PNode) malloc (sizeof(struct Node));
    if (q==NULL){
        printf("Out of space\n");
        return 0;
    }
    else{
        q ->info =x;
        q ->link =p->link; //先右
        p->link =q;  //后左
        return 1;
    }
}

//在单链表中求p所指结点的前驱结点：
PNode locatePre_link(LinkList llist,PNode p){
    PNode p1;
    if(llist ==NULL)
        return NULL;
    p1=llist;
    while( p1 != NULL && p1 ->link != p)//p1->link指向的就是p
        p1 = p1->link;
    return p1;
}

//单链表的删除
int deleteValue(LinkList llist,DataType x){
    PNode p,q;

    //p和llist都是头结点
    p =llist;
    if( p==NULL )
        return 0;
    //寻找x所在的结点
    while(p->link != NULL && p->link->info != x)
        p=p->link;

    if(p->link==NULL){
        printf("Not exist!\n");
        return 0;
    }
    else{
        q = p->link;  //定q结点为x所在结点
        p->link = q->link ;
        free(q);
        return 1;
    }
}

//删除下标为i的结点
void deletePosition(LinkList llist, int i) {
    PNode p;
    p=llist;
    for(int j=0; j<i; j++) {
        if(!p->link) {
            printf("Not exist\n");
            break;
        }
        else
            p=p->link;
    }
    p->link=p->link->link;
}


/*
 * 翻转链表
 * 将1～n结点一个个插入到head结点后
 * h 1 2 3 4 5 6
     * h 1 2 3 4 5 6
     * h 2 1 3 4 5 6
     * h 3 2 1 4 5 6
     * h 4 3 2 1 5 6
     * h 5 4 3 2 1 6
     * h 6 5 4 3 2 1
 */
LinkList reverLinkList(LinkList llist) {
    PNode tmp,q;
    tmp = llist->link;//第一个结点(llist是头结点)
    while(tmp->link!= NULL){
        q = tmp->link;//2
        tmp->link = q->link; //先把3和1接起
        q->link = llist->link; //把2和1接起
        llist->link = q;//把h和2接起
    }
    /*纠结着第6个结点
     *其实while循环处理的是tmp->link,而不是tmp
     *所以6是可以正常插入的
     */
    return llist;
}

//↑↓是一样的方法: 将后面的结点一个个插入到head结点后
/*
void reverse(LinkList llist){
    PNode p, q;
    p=llist->link;
    llist->link=NULL;
    while(p){
        q=p;
        //设置两个Node, q是要插入head后面的下一个结点, p为插入后剩下的链表的头结点
        p=p->link;
        // 把节点插入到头结点后面
        q->link=llist->link;
        llist->link=q;
    }
}
*/


// 插入排序---- 表排序
// 移动次数为0，比较次数为O(n*n)
// 空间复杂度O(n),(每个节点都附加了link字段)
/*
 * 插入排序和链表插入一样,只是插入的时候注意一下位置
 * 为什么不像之前那样,从后往前比呢? 因为单链表中, 像找前驱节点不容易啊
 * 为什么需要q, p 两个节点, 因为要把now节点插入,而插入的位置就在q,p中间,
 * q就指向now的父节点,p就是now的next节点,插入完后，q,p重新回到开头,下一个继续从头开始与now节点比较
 */
void sortLinkList(LinkList * plist) {
    Node *now, *pre, *p, *q, *head; head=*plist;
    // pre指向已排序链表的最后一个节点,now指向下一个需要插入的节点
    if (head->link == NULL || head->link->link== NULL)
        return;  /* 为空链表或链表中只有一个结点 */

    pre = head->link; now = pre->link;
    while (now != NULL) {
        // 每次插入新元素时,都把q,p重置回表头
        q = head; p = head->link;
        // 用p从头开始与now做比较,q是p的前驱节点,
        // 所以q也跟now比较过了,当循环退出,now该插入的地方肯定就在qp间
        // 如果p与now相等,还进行了一次循环,所以,now还是在qp之间
        while(p != now && p->info <= now->info ) {
            q = p;  p = p->link;
        } /* 本循环结束时，已经找到了now的插入位置 */
        // while退出,若是因p走到now那里(即已排序序列中找不到比now大的,
        // 那就把pre和now指向下一个就可以了,不需要插入

        if (p == now) {                        /* now应放在原位置 */
            pre = pre->link; now = pre->link; continue;
        }

        /* 使now记录脱链，将now记录插入链表中 */
        pre->link= now->link; q->link= now; // 把now插入到pq中间
        now->link= p; now = pre->link; // now还是指向下个需要插入的节点
    }
}


/*
 * 输出链表中倒数第K个结点
 * 双指针联动，一个指针先跑K个节点，然后两个指针一起跑，
 * 一个指针跑到尾节点时另一个指针恰好是倒数第K个结点
 */
DataType Lastk(LinkList llist, int k){
    int i = 1;
    PNode head = llist;//头结点
    PNode p = head->link;//链表第一个结点
    while(p && i<k ){
        p = p->link;
        i++;
    }//p跑到第k个结点了
    if(p == NULL){
        cout<<"No Exit!\n";
    }
    while(p){ //这里需要head先跑, 顺序不同结果也是不同的
        head = head->link;
        p = p->link;
    }
    return head->info;
}


/*
 * 两个有序链表的合并
 */
LinkList sortedMerge(LinkList llist1, LinkList llist2){
    if(llist1==NULL)
        return llist2;
    else if(llist2==NULL)
        return llist1;
    PNode pMergedHead = NULL;
    if(llist1->info < llist2->info){
        pMergedHead = llist1;
        pMergedHead->link = sortedMerge(llist1->link, llist2);
    }else{
        pMergedHead = llist2;
        pMergedHead->link = sortedMerge(llist1, llist2->link);
    }
    return pMergedHead;
}

DataType HeadorNoHead(LinkList llist){
    // PNode head = llist; 头结点, head->link 为第一个结点
    // return head->info;

    PNode p = llist->link;//头结点的指针指向了第一个结点
    return p->info;
}

int main()
{
    LinkList llist = createNullList_link();
    PNode head=llist;
    PNode tmp;
    DataType data;
    cin>>data;
    while(data) {
        insertPost_link(llist, head, data);
        cin>>data;
    }


    cout<<"由于是前插，所以实际顺序与输入顺序相反\n";
    showLinkList(llist);

    if(!isNullList_link(llist))
        cout<<"栈非空\n";




    cout<<"test:\n";
    // cout<<test(llist);
    cout<<endl;



    DataType key;
    cout<<"locate_key:\n";
    cin>>key;
    tmp = locate_x(llist, key);
    cout<<tmp->info<<endl;

    cout<<"在input1后面插入input2:\n";
    DataType input1,input2;
    cin>>input1>>input2;
    tmp = locate_x(llist,input1);
    insertPost_link(llist, tmp, input2);
    showLinkList(llist);

    cout<<"locatePre_link,cin current data\n";
    cin>>data;
    tmp = locate_x(llist,data);
    PNode tmp2;
    tmp2 = locatePre_link(llist, tmp);
    cout<<tmp2->info<<endl;

    cout<<"delete value,cin data\n";
    cin>>data;
    deleteValue(llist, data);
    showLinkList(llist);

    cout<<"delete position,cin i\n";
    cin>>data;
    deletePosition(llist,data);
    showLinkList(llist);

    cout<<"输入k,输出倒数第k个结点\n";
    cin>>data;
    cout<<Lastk(llist, data)<<"\n";

    cout<<"reversal LinkList\n";
    LinkList tmp_link = reverLinkList(llist);
    showLinkList(tmp_link);

    /* // cout<<"reverse\n";
    // reverse(llist);
    // showLinkList(llist); */


    cout<<"sort LinkList\n";
    sortLinkList(&llist);
    showLinkList(llist);

    //FIXME 为什么会多了个0
    cout<<"两个有序链表合并\n输入链表2\n";
    LinkList llist2 = createNullList_link();
    PNode head2 = llist2;
    DataType data2;
    cin>>data2;
    while(data2) {
        insertPost_link(llist, head2, data2);
        cin>>data2;
    }
    sortLinkList(&llist2);
    showLinkList(sortedMerge(llist, llist2));

    return 0;
}
