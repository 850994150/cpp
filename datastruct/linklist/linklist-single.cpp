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
typedef struct Node *PNode;

struct Node
{
    DataType info;
    PNode link;
};
typedef struct Node *LinkList;

//创建空链表
LinkList createNullList_link()
{
    LinkList llist = (LinkList)malloc(sizeof(struct Node));
    if (llist != NULL)
        llist->link = NULL;
    else
        printf("Out of space !\n");
    return llist;
}

//判断链表是否为空
int isNullList_link(LinkList llist)
{
    return (llist->link == NULL);
}

//输出链表
void showLinkList(LinkList llist)
{
    PNode tmp = llist;
    while ((tmp != NULL) & (tmp->link != NULL))
    {
        tmp = tmp->link;
        cout << tmp->info << " ";
    }
    cout << endl;
}

//求某元素的储存位置
PNode locate_x(LinkList llist, DataType x)
{
    PNode p;
    if (llist == NULL)
    {
        return NULL;
    }
    p = llist->link;
    while (p != NULL && p->info != x)
    {
        p = p->link;
    }
    return p;
}

//单链表的插入
int insertPost_link(LinkList llist, PNode p, DataType x)
{
    PNode q = (PNode)malloc(sizeof(struct Node));
    if (q == NULL)
    {
        printf("Out of space\n");
        return 0;
    }
    else
    {
        q->info = x;
        q->link = p->link; //先右
        p->link = q;       //后左
        return 1;
    }
}

//在单链表中求p所指结点的前驱结点：
PNode locatePre_link(LinkList llist, PNode p)
{
    PNode p1;
    if (llist == NULL)
        return NULL;
    p1 = llist;
    while (p1 != NULL && p1->link != p) //p1->link指向的就是p
        p1 = p1->link;
    return p1;
}

//单链表的删除
int deleteValue(LinkList llist, DataType x)
{
    PNode p, q;

    //p和llist都是头结点
    p = llist;
    if (p == NULL)
        return 0;
    //寻找x所在的结点
    while (p->link != NULL && p->link->info != x)
        p = p->link;

    if (p->link == NULL)
    {
        printf("Not exist!\n");
        return 0;
    }
    else
    {
        q = p->link; //定q结点为x所在结点
        p->link = q->link;
        free(q);
        return 1;
    }
}

//删除下标为i的结点
void deletePosition(LinkList llist, int i)
{
    PNode p;
    p = llist;
    for (int j = 0; j < i; j++)
    {
        if (!p->link)
        {
            printf("Not exist\n");
            break;
        }
        else
            p = p->link;
    }
    p->link = p->link->link;
}


// 计算节点个数
int ListNodeNum(LinkList llist)
{
    int iNum = 0;
    if (llist->link == NULL)
    {
        return 0;
    }
    while (llist->link != NULL)
    {
        llist = llist->link; // llist一直是下一个结点
        iNum++;
    }
    return iNum;
}



/*
 * 翻转链表
 * 思路: 将1～n结点一个个插入到head结点后
 *       指针修改顺序从后往前, 想修改待插入的
 * h -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> NULL
 */
LinkList reverLinkList(LinkList llist)
{
    PNode pFirst;  // 反转前第一个结点
    PNode pInsert; // 待插入结点
    pFirst = llist->link;
    while (pFirst->link != NULL) // 待插入结点(例子中始终为1, 随着循环进行, 最后会把NULL赋值给1的link域)
    {
        pInsert = pFirst->link;
        pFirst->link = pInsert->link;
        pInsert->link = llist->link;
        llist->link = pInsert;
    }
    return llist;
}

// 插入排序---- 表排序
// 移动次数为0，比较次数为O(n*n)
// 空间复杂度O(n),(每个节点都附加了link字段)
/*
 * 插入排序和链表插入一样,只是插入的时候注意一下位置
 * 为什么不像之前那样,从后往前比呢? 因为单链表中, 像找前驱节点不容易啊
 * 为什么需要q, p 两个节点, 因为要把now节点插入,而插入的位置就在q,p中间,
 * q就指向now的父节点,p就是now的next节点,插入完后，q,p重新回到开头,下一个继续从头开始与now节点比较
 */
void sortLinkList(LinkList *plist)
{
    Node *now, *pre, *p, *q, *head;
    head = *plist;
    // pre指向已排序链表的最后一个节点,now指向下一个需要插入的节点
    if (head->link == NULL || head->link->link == NULL)
        return; /* 为空链表或链表中只有一个结点 */

    pre = head->link;
    now = pre->link;
    while (now != NULL)
    {
        // 每次插入新元素时,都把q,p重置回表头
        q = head;
        p = head->link;
        // 用p从头开始与now做比较,q是p的前驱节点,
        // 所以q也跟now比较过了,当循环退出,now该插入的地方肯定就在qp间
        // 如果p与now相等,还进行了一次循环,所以,now还是在qp之间
        while (p != now && p->info <= now->info)
        {
            q = p;
            p = p->link;
        } /* 本循环结束时，已经找到了now的插入位置 */
        // while退出,若是因p走到now那里(即已排序序列中找不到比now大的,
        // 那就把pre和now指向下一个就可以了,不需要插入

        if (p == now)
        { /* now应放在原位置 */
            pre = pre->link;
            now = pre->link;
            continue;
        }

        /* 使now记录脱链，将now记录插入链表中 */
        pre->link = now->link;
        q->link = now; // 把now插入到pq中间
        now->link = p;
        now = pre->link; // now还是指向下个需要插入的节点
    }
}

/*
 输出链表中倒数第K个结点
1. 先计算出总结点数n, 然后第n-k个就是倒数第k个结点了
2. 双指针联动，快指针先走K个节点，然后快慢指针一起走，
   快指针跑到尾节点时另一个指针恰好是倒数第K个结点
   其实快指针走了k, 慢指针才开始走,而且快指针走到结尾就停止,
   所以慢指针走了n-k个结点, 刚好是倒数第k个
 */
DataType Lastk(LinkList llist, int k)
{
    int i = 1;
    PNode head = llist;   //头结点
    PNode p = head->link; //链表第一个结点
    while (p && i < k)
    {
        p = p->link;
        i++;
    }
    if (p == NULL)
    {
        cout << "No Exit!\n";
    }
    while (p)
    {
        head = head->link; //这里需要head先跑, 顺序不同结果也是不同的
        p = p->link;
    }
    return head->info;
}

// 这种明显更直观
DataType LastKNode(LinkList llist, int k)
{
    LinkList fast, low;
    fast = llist;
    low = llist;

    while (k--)
    {
        fast = fast->link;
    }
    if (!fast)
    {
        cout << "不存在" << endl;
    }
    while (fast) // 因为最后一个结点也要算上, 所以如果是fast->link的话, 最后一个结点就没算上
    {
        fast = fast->link;
        low = low->link;
    }
    return low->info;
}


/*
 查找中间结点
 设置快慢指针, 都是从头开始走, 快指针走两步, 慢指针走一步
 当快指针走到结尾时, 慢指针刚好指在中间结点
 原理：
    快指针是慢指针的两倍
 这种方法求得的中间结点下标为: n/2 向上取整
*/
DataType MiddleNode(LinkList llist)
{
    LinkList fast, low;
    fast = llist;
    low = llist;
    //[h] 9 7 6 5 4 3 2 1 NULL .
    //    i i i i   j   j
    //[h] 8 6 5 4 3 2 1 NULL .
    //    i i i i   j   j

    // 如果是偶数个的话, fast最终落在n上，所以判断fast->link;
    // 如果是奇数个的话, fast最终落在末结点的link上(为NULL)
    // 为什么不合并起来只判断fast->link呢?
    // 因为是奇数个时, fast=末尾结点的link域(null), 所以fast的link是不确定的
    while (fast && fast->link)
    {
        fast = fast->link->link;
        low = low->link;
    }
    return low->info;
}

// 获取单链表中间结点，若链表长度为n(n>0)
// 若n为偶数, 则返回第n/2个结点
// 若n为奇数, 则返回第n/2+1个结点
DataType GetMiddleNode(LinkList pHead)
{
    if(pHead == NULL || pHead->link == NULL) // 链表为空或只有一个结点，返回头指针
        return pHead->info;

    LinkList pAhead = pHead;
    LinkList pBehind = pHead;
    while(pAhead->link!= NULL) // 前面指针每次走两步，直到指向最后一个结点，后面指针每次走一步
    {
        pAhead = pAhead->link;
        pBehind = pBehind->link;
        if(pAhead->link!= NULL)
            pAhead = pAhead->link;
    }
    return pBehind->info; // 后面的指针所指结点即为中间结点
}

bool IsCircle(LinkList llist)
{
    LinkList fast, low;
    fast = llist;
    low = llist;

    while (fast && fast->link)
    {
        fast = fast->link->link;
        low = low->link;
        if (fast->info == low->info)
        {
            return true;
        }
    }
    return false;
}

/*
 * 两个有序链表的合并
 */
LinkList sortedMerge(LinkList llist1, LinkList llist2)
{
    if (llist1 == NULL)
        return llist2;
    else if (llist2 == NULL)
        return llist1;
    PNode pMergedHead = NULL;
    if (llist1->info < llist2->info)
    {
        pMergedHead = llist1;
        pMergedHead->link = sortedMerge(llist1->link, llist2);
    }
    else
    {
        pMergedHead = llist2;
        pMergedHead->link = sortedMerge(llist1, llist2->link);
    }
    return pMergedHead;
}

DataType HeadorNoHead(LinkList llist)
{
    // PNode head = llist; 头结点, head->link 为第一个结点
    // return head->info;

    PNode p = llist->link; //头结点的指针指向了第一个结点
    return p->info;
}

int main()
{
    LinkList llist = createNullList_link();
    PNode head = llist;
    PNode tmp;
    DataType data;
    cout << "输入结点,0表示输入完毕:\n";
    cin >> data;
    while (data)
    {
        insertPost_link(llist, head, data);
        cin >> data;
    }

    cout << "结点个数为: " << ListNodeNum(llist) << endl;

    cout << "由于是前插，所以实际顺序与输入顺序相反\n";
    showLinkList(llist);

    if (!isNullList_link(llist))
        cout << "栈非空\n";

    cout << endl;

    DataType key;
    cout << "输入data, 找到data:\n";
    // FIXME
    cin >> key;
    tmp = locate_x(llist, key);
    cout << tmp->info << endl;

    cout << "在input1后面插入input2:\n";
    DataType input1, input2;
    cin >> input1 >> input2;
    tmp = locate_x(llist, input1);
    insertPost_link(llist, tmp, input2);
    showLinkList(llist);

    cout << "查找前驱结点,cin current data\n";
    cin >> data;
    tmp = locate_x(llist, data);
    PNode tmp2;
    tmp2 = locatePre_link(llist, tmp);
    cout << tmp2->info << endl;

    cout << "按值删除,cin data\n";
    cin >> data;
    deleteValue(llist, data);
    showLinkList(llist);

    cout << "按位置删除,cin i\n";
    cin >> data;
    deletePosition(llist, data);
    showLinkList(llist);

    cout << "输入k,输出倒数第k个结点\n";
    cin >> data;
    cout << Lastk(llist, data) << "\n";
    cout << LastKNode(llist, data) << "\n";

    cout << "中间结点是:" << MiddleNode(llist) << endl;
    cout << "中间结点是:" << GetMiddleNode(llist) << endl;

    cout << "反转链表\n";
    LinkList tmp_link = reverLinkList(llist);
    showLinkList(tmp_link);

    /* // cout<<"reverse\n";
    // reverse(llist);
    // showLinkList(llist); */

    cout << "表排序\n";
    sortLinkList(&llist);
    showLinkList(llist);

    //FIXME 为什么会多了个0
    cout << "两个有序链表合并\n输入链表2\n";
    LinkList llist2 = createNullList_link();
    PNode head2 = llist2;
    DataType data2;
    cin >> data2;
    while (data2)
    {
        insertPost_link(llist, head2, data2);
        cin >> data2;
    }
    sortLinkList(&llist2);
    showLinkList(sortedMerge(llist, llist2));

    return 0;
}
