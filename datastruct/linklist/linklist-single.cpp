/***********************************************************
* Author       : M_Kepler
* EMail        : hellohuangjinjie@gmail.com
* Last modified: 2016-04-14 12:02:04
* Filename     : linklist-single.cpp
* Description  : 带头结点的单链表操作
    * 由于我使用0表示输入结束，所以尽量不要插入0
    * 单链表: 结点只有一个指针域
    * 头指针
        * 链表中第一个结点的存储位置叫做头指针
    * 头结点
        * 是为了操作的统一与方便而设立的，放在第一个元素结点之前，其数据域一般无意义
        * 有了头结点后，对在第一个元素结点前插入结点和删除第一个结点，其操作与对其它结点的操作统一了。
        LinkList llist; // 函数入参 llist 是入参头指针, 用 -> 访问符就可以访问头结点
***********************************************************/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

using namespace std;
typedef int DataType;
struct Node;
typedef struct Node* PNode;

struct Node
{
    DataType info;
    PNode link;
};
typedef struct Node* LinkList;

/*
 * @function: 创建带头结点的空链表
 * @brief	:
 *            llist(头指针)
 *              ↓
 *             [ ] -> [1] -> [2] -> NULL
 *                     ↑ llist = llist->link(头指针往后挪)
 * @param	:
 * @return	:
 */
LinkList createNullList_link()
{
    LinkList llist = NULL; // llist为链表头指针
    PNode head = (PNode)malloc(sizeof(struct Node)); // 指向头结点的指针head
    llist = head; // 头指针指向头结点
    if (head != NULL)
    {
        head->link = NULL; // 初始化头结点, 指针用->来访问指向的结构体
    }
    else
    {
        printf("Out of space !\n");
        abort();
    }
    return llist; // 头结点的地址, 所以后面的函数入参 llist 都是入参头指针
}

/*
 * @brief	: 销毁链表空间
 * @param	:
 * @return	:
 */
void DestroyLinkList(LinkList llist)
{
    PNode head = llist;
    while (head!= NULL)
    {
        llist = llist->link;
        free(head);
        head = llist;
    }
    llist = NULL;
}

/*
 * @brief	: 判断是否为空链表
 * @param	:
 * @return	:
 */
int isNullList_link(LinkList llist)
{
    return (llist->link == NULL);
}

/*
 * @brief	: 正序输出链表结点值
 * @param	:
 * @return	:
 */
void showLinkList(LinkList llist)
{
    PNode head = llist;
    while ((head != NULL) & (head ->link != NULL))
    {
        head = head->link;
        cout << head->info << " ";
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

/*
 * @brief	: 带头结点单链表的插入(前插)
 * @param	: 每次插入都是插入在head结点后面: h->1->null; h->2->1->null;
 * @return	:
 */
int insertPost_link(PNode head, DataType x)
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
        q->link = head->link; // 先右
        head->link = q;       // 后左
        return 1;
    }
}

/*
 * @function: 不带头结点的前插法 TODO
 * @brief	: 
 * @param	: 
 * @return	: 
 */
void insertPost_linkNoHead(PNode head, DataType x)
{
}

/*
 * @function: 单链表中求p所指结点的前驱结点：
 * @brief	: 遍历结点, 判断link域是否指向结点p
 * @param	:
 * @return	:
 */
PNode locatePre_link(LinkList llist, PNode p)
{
    PNode preNode;
    if (llist == NULL)
    {
        return NULL;
    }
    preNode = llist;
    while (preNode != NULL && preNode->link != p)
    {
        preNode= preNode->link;
    }
    return preNode;
}

/*
 * @function: 单链表的删除
 * @brief	: 遍历找到前驱结点preNode
 * @param	:
 * @return	:
 */
int deleteValue(LinkList llist, DataType x)
{
    PNode preNode, xNode;
    preNode = llist;
    if (preNode == NULL)
    {
        return -1;
    }
    // 遍历链表, 寻找x所在的结点的前驱结点p
    while (preNode->link != NULL && preNode->link->info != x)
        preNode = preNode->link;

    if (preNode->link == NULL)
    {
        printf("Not exist!\n");
        return -1;
    }
    else
    {
        xNode = preNode->link; // x 所在结点
        preNode->link = xNode->link;
        free(xNode);
        return 0;
    }
}

/*
 * @function: 删除所有值为x的结点
 * @brief	:
 * @param	:
 * @return	:
 */
void deleteAllValue(LinkList L, DataType x)
{
    if (L->link == NULL)
    {
        return;
	}
	PNode p, q;
	p = L;
    while (p->link != NULL)
    {
        if (p->link->info == x)
        {
            q = p->link;
            p->link = q->link;
            free(q);
        }
        else
        {
            p = p->link;
		}
    }
}


/*
 * @function: 删除第i个结点(不是下标)
 * @brief	:
 * @param	:
 * @return	:
 */
void deletebyIndex(LinkList llist, int index)
{
    PNode preNode;
    preNode = llist;
    // index += 1; // 下标和位置..
    while (preNode->link !=NULL && --index)
        preNode = preNode->link;

    preNode->link = preNode->link->link;
}

/*
 * @function: 删除下标为i的结点
 * @brief	:
 * @param	:
 * @return	:
 */
void deletePosition(LinkList llist, int i)
{
    PNode preNode;
    preNode = llist;
    for (int j = 0; j < i; j++)
    {
        if (!preNode->link)
        {
            printf("Not exist\n");
            break;
        }
        else
        {
            preNode = preNode->link;
        }
    }
    preNode->link = preNode->link->link;
}


/*
 * @function: 计算节点数
 * @brief	:
 * @param	:
 * @return	:
 */
int ListNodeNum(LinkList llist)
{
    int iNum = 0;
    if (llist->link == NULL)
    {
        return 0;
    }
    while (llist->link != NULL)
    {
        llist = llist->link; // llist(头指针)一直是下一个结点
        iNum++;
    }
    return iNum;
}

/*
 * @function: 带头结点的单链表翻转
 * @brief	: 头结点h不用动将2～n结点一个个插入到head结点后
              指针修改顺序从后往前, 想修改待插入的
              h -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> null
 * @param	:
 * @return	:
 */
LinkList reverLinkList(LinkList llist)
{
    PNode pFirst = llist->link; // 反转前第一个结点(头结点之后的第一个结点)
    PNode pInsert;              // 待插入结点(例子中始终为1, 随着循环进行, 最后会把NULL赋值给1的link域)
    while (pFirst->link != NULL)
    {
        pInsert = pFirst->link;
        pFirst->link = pInsert->link;
        pInsert->link = llist->link;
        llist->link = pInsert;
    }
    return llist;
}

// 插入排序
// 移动次数为0，比较次数为O(n*n)
// 空间复杂度O(n),(每个节点都附加了link字段)
/*
 * 插入排序和链表插入一样,只是插入的时候注意一下位置
 * 为什么不像之前那样,从后往前比呢? 因为单链表中, 像找前驱节点不容易啊
 * 为什么需要q, p 两个节点, 因为要把now节点插入,而插入的位置就在q,p中间,
 * q就指向now的父节点,p就是now的next节点,插入完后，q,p重新回到开头,下一个继续从头开始与now节点比较
 */
/*
 * @function: 链表排序
 * @brief	: 插入排序的优化, 插入排序要把元素一个个往后移动才能插入, 用链表来改善插入复杂度
 * @param	:
 * @return	:
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
 * @function: 链表排序
 * @brief	: 就像链表逆转一样, 把后面的结点一个个插入到前面
 * @param	:
 * @return	:
 */
void LinkListInsertSort(LinkList llist)
{
    PNode head;
    PNode insertNode;        // 待插入结点
    PNode preInsertNode;     // 待插入结点的前驱结点
    PNode prePosition;       // 插入位置的前一个结点
    PNode afterPosition;     // 插入位置的后一个结点(第一个比插入结点大或相等的结点)
    head = llist;

    if (head->link == NULL || head->link->link == NULL)
        return;
    preInsertNode = head->link;
    insertNode = preInsertNode->link;
    while (insertNode != NULL)
    {
        prePosition = head;
        afterPosition = head->link; // 首个结点

        while (afterPosition != insertNode && afterPosition->info <= insertNode->info)
        {
            prePosition = afterPosition;
            afterPosition = afterPosition->link; // 遍历链表, 找到合适的位置
        }
        // printf("待插入前驱:%d\t待插入%d\n前位置%d\t后位置%d\n\n", preInsertNode->info, insertNode->info, prePosition->info, afterPosition->info);

        if (afterPosition == insertNode) // 待插入结点和有序序列中最大的结点相等时
        {
            preInsertNode = preInsertNode->link;
            insertNode = preInsertNode->link;
            continue;
        }

        preInsertNode->link = insertNode->link;
        prePosition->link = insertNode;
        insertNode->link = afterPosition;
        insertNode = preInsertNode->link;
    }
}

/*
 * @function: 链表冒泡排序
 * @brief	: 思想和普通冒泡排序一样, 普通是比较数组元素, 这里是比较结点值; 注意结点移动
 * @param	:
 * @return	:
 */
void LinkLisBubbleSort(LinkList llist)
{
    int len = ListNodeNum(llist);
    if (len == 0)
        return;
    int i, j;
    PNode p;
    DataType tmp;

    for (i = 0; i < len; i++)
    {
        p = llist->link; // 带头结点的链表, 从第一个结点开始
        for (j = 0; j < len - i - 1; j++)
        {
            if (p->info > p->link->info)
            {
				tmp = p->info;
                p->info = p->link->info;
                p->link->info= tmp;
			}
            p = p->link; // 结点移动
        }
	}
}


/*
 * @function: 输出倒数第k个结点
 * @brief	:
            1. 先计算出总结点数n, 然后第n-k个就是倒数第k个结点了
            2. 双指针联动，快指针先走K个节点，然后快慢指针一起走，
               快指针跑到尾节点时另一个指针恰好是倒数第K个结点
               其实快指针走了k, 慢指针才开始走,而且快指针走到结尾就停止,
               所以慢指针走了n-k个结点, 刚好是倒数第k个
 * @param	:
 * @return	:
 */
DataType Lastk(LinkList llist, int k)
{
    int i = 1;
    PNode head = llist;   // 头结点
    PNode p = head->link;
    while (p && --k) // 这里p为第一个结点, 所以找第k个结点循环k-1次
        p = p->link;
    /* // ok
    while (p && i < k)
    {
        p = p->link;
        i++;
    }
    */
    // 循环退出, p指向第k个结点
    // cout << "顺数第k个结点为:" << p->info << endl;
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

/*
 * @function: 输出倒数第k个结点
 * @brief	: fast指针先走k个结点，然后low结点和他一起走，此时low初始应该是从第一个结点和他一起走的
 * @param	:
 * @return	:
 */
DataType LastKNode2(LinkList llist, int k)
{
    LinkList fast, low;
    fast = llist;
    low = llist->link; // 关注点

    while (k--)
    {
        fast = fast->link;
    }
    if (!fast)
    {
        cout << "不存在" << endl;
    }
    while (fast->link != NULL)
    {
        fast = fast->link;
        low = low->link;
    }
    return low->info;
}


/*
 * @function: 查找中间结点
 * @brief	:
            设置快慢指针, 都是从头开始走, 快指针走两步, 慢指针走一步
            当快指针走到结尾时, 慢指针刚好指在中间结点
            原理：
                快指针是慢指针的两倍
 * @param	:
 * @return	: 返回第n/2个结点(向上取整) 如6个结点则返回第3个,7个结点则返回第4个
 */
DataType MiddleNode(LinkList llist)
{
    LinkList fast, low;
    fast = llist;
    low = llist;

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

/*
 * @function: 判断链表是否有环
 * @brief	: 快慢指针, 快指针一次走两步, 慢指针一次走一步,
              如果有环, 肯定会相遇，快指针只要比慢指针快就行了，不管快多少步
 * @param	:
 * @return	:
 */
bool IsCircle(LinkList llist)
{
    LinkList fast, low;
    fast = llist;
    low = llist;

    while (fast && fast->link)
    {
        fast = fast->link->link;
        low = low->link;
        if (fast == low)
        {
            return true;
        }
    }
    return false;
}

/*
 * @function: 找出环入口
 * @brief	: 假如有快慢指针判断一个链表有局部环，链表起点是A，环的入口是B，快慢指针在环中的相遇点是C。那么按照原来的运动方向，有AB=CB，这是可以证明的结论
 *            做法就是先找到相遇点，然后把快指针重置会头结点，快慢指针继续同步走，如果再次相遇，则相遇点就是环的入口
 * @param	: 
 * @return	: 
 */

DataType GetCircleNode(LinkList llist)
{
    PNode fast = llist;
    PNode slow = llist;
    // while(fast && slow)
    while(fast && fast->link)
    {
        fast = fast->link->link;
        slow = slow->link;
        if (fast == slow)
        {
            // cout << "相遇点: " << fast->info << endl;
            fast = llist;
            break;
        }
    }
    while (fast->link != NULL)
    {
        fast = fast->link;
        slow = slow->link;
        if (fast == slow)
        {
            return fast->info;
        }
    }
    return -1;
}

/*
 * @function: 两个链表是否相交, 输出相交结点(结点相等包括data值和link域)
 * @brief	: 如果两个链表相交, 那肯定有一个相交的结点(这个结点的值和link域都一样)
 *            因为link域一样, 所以两个链表的相交结点后面的结点都是相同的(因为link保存的是地址是一样的)
 *            * 所以, 判断是否相交可以直接看尾结点是否一样, 如果一样, 则相交
 *            1->2->3->4->5->6->7->null(链表1)0->9->8->6->7->null(链表2), 相交如下图:
 *            1->2->3->4->5
 *                         ↘
 *                           6->7->null
 *                          ↗
 *                  3->9->8
 * @param	: 
 * @return	: 
 */
bool IsY(LinkList llist1, LinkList llist2)
{
    PNode head1 = llist1;
    PNode head2 = llist2;
    while (head1->link != NULL)
    {
        head1 = head1->link;
    }
    while (head2->link != NULL)
    {
        head2 = head2->link;
    }
    // if (head1->info == head2->info)
    if (head1 == head2)
    {
        return true;
    }
    return false;
}

/*
 * @function: 获取第一个相交结点
 * @brief	: 计算两个链表的长度差n, 长链表先走n, 然后长短链表同时往后走, 直到第一个相等的结点就是相交结点
 * @param	: 
 * @return	: 
 */
DataType GetYNode(LinkList llist1, LinkList llist2)
{
    if (!IsY(llist1, llist2))
    {
        return -1;
    }
    int len1 = ListNodeNum(llist1);
    int len2 = ListNodeNum(llist2);
    PNode head1 = llist1;
    PNode head2 = llist2;
    while (len1 > len2 && head1->link != NULL && --len1)
    {
        head1 = head1->link;
    }
    while (len2 > len1 && head2->link != NULL && --len2)
    {
        head2 = head2->link;
    }
    // 以上循环表示长链表先走n步(n为差值), 以下循环表示两链表一起走, 直到相等
    while (head1->link != NULL && head2->link != NULL)
    {
        head1 = head1->link;
        head2 = head2->link;
        // if (head1->info == head2->info)
        if (head1 == head2)
        {
            return head1->info;
        }
    }
}

/*
 * @function: 有序链表合并
 * @brief	:
 * @param	:
 * @return	:
 */
LinkList sortedMerge(LinkList llist1, LinkList llist2)
{
    if (llist1 == NULL)
    {
        return llist2;
    }
    else if (llist2 == NULL)
    {
        return llist1;
    }
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

void sort_test(LinkList llist)
{
    cout << "原始序列:" << endl;
    showLinkList(llist);
    cout << "插入排序:" << endl;
    LinkListInsertSort(llist);
    showLinkList(llist);
    cout << "冒泡排序排序:" << endl;
    LinkLisBubbleSort(llist);
    showLinkList(llist);
}

// 链表环测试
/*
// 测试用例:
                -----------------
               ↓                 ↓
[]->[1]->[2]->[3]->[4]->[5]->[6]-   // 尾结点指向3，制造一个环

输入为: 6 5 4 3 2 1 0
*/
int CircleTest( )
{
    LinkList llist = createNullList_link();
    PNode head = llist;
    PNode tmp;
    DataType data;

    cout << "【链表环测试】\n输入结点, 0表示输入完毕:\n";
    cin >> data;
    while (data)
    {
        insertPost_link(head, data);
        cin >> data;
    }
    cout << "结点个数为: " << ListNodeNum(llist) << endl;
    cout << "由于是前插，所以实际顺序与输入顺序相反\n";
    showLinkList(llist);

    PNode p = NULL;
    while (head->link != NULL)
    {
        head = head->link;
        if (head->info == 3)
        {
            p = head;
        }
    }
    head->link = p; // 创造一个环, 链表尾结点的link域指向结点3

    if (IsCircle(llist))
    {
        cout << "链表有环" << endl;
        cout << "环入口结点为：" << GetCircleNode(llist) << endl;
    }
    else
    {
        cout << "链表无环" << endl;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    LinkList llist = createNullList_link();
    PNode head = llist;
    PNode tmp;
    DataType data;

    cout << "输入结点, 0表示输入完毕:\n";
    cin >> data;
    while (data)
    {
        insertPost_link(head, data);
        cin >> data;
    }
    cout << "结点个数为: " << ListNodeNum(llist) << endl;
    cout << "由于是前插，所以实际顺序与输入顺序相反\n";
    showLinkList(llist);

    if (!isNullList_link(llist))
    {
        cout << "链表非空\n";
    }
    else
    {
        cout << "空链表" << endl;
        return 0;
    }

    cout << endl;

    DataType key;
    cout << "输入data, 找到data:\n";
    cin >> key;
    tmp = locate_x(llist, key);
    cout << tmp->info << endl;

    cout << "在input1后面插入input2:\n";
    DataType input1, input2;
    cin >> input1 >> input2;
    tmp = locate_x(llist, input1);
    insertPost_link(tmp, input2);
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
    deletebyIndex(llist, data);
    showLinkList(llist);

    cout << "按下标删除,cin i\n";
    cin >> data;
    deletePosition(llist, data);
    showLinkList(llist);

    cout << "删除所有值为x的结点\n";
    cin >> data;
    deleteAllValue(llist, data);
    showLinkList(llist);

    cout << "输入k,输出倒数第k个结点\n";
    cin >> data;
    cout << Lastk(llist, data) << "\n";
    cout << LastKNode2(llist, data) << "\n";

    cout << "中间结点是:" << MiddleNode(llist) << endl;
    cout << "中间结点是:" << GetMiddleNode(llist) << endl;

    cout << "反转链表\n";
    LinkList tmp_link = reverLinkList(llist);
    showLinkList(tmp_link);

    cout << "链表排序\n";
    sort_test(llist);

    cout << "创建链表2\n";
    //FIXME 为什么会多了个0
    LinkList llist2 = createNullList_link();
    PNode head2 = llist2;
    DataType data2;
    cin >> data2;
    while (data2)
    {
        insertPost_link(head2, data2);
        cin >> data2;
    }
    showLinkList(llist2);

    if(IsY(llist, llist2))
    {
        cout << "两个链表是否相交\n"; // 因为采用的是前插, 所以构造的时候注意点
        cout << "相交结点为\n";
        cout << GetYNode(llist, llist2) << endl;
    }
    else
    {
        cout << "两个链表不相交\n";
    }

    cout << "两个有序链表合并\n输入链表2\n";
    sortLinkList(&llist2);
    showLinkList(sortedMerge(llist, llist2));

    cout << "销毁链表空间" << endl;
    DestroyLinkList(llist);
    DestroyLinkList(llist2);

    return 0;
}

