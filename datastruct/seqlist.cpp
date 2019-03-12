/***********************************************************
* Author       : M_Kepler
* EMail        : hellohuangjinjie@gmail.com
* Last modified: 2016-04-13 18:23:00
* Filename     : SeqList.cpp
* Description  :
        * 创建空顺序表
        * 根据元素输出下标
        * 在下标i前插入元素
        * 在下标j后插入元素
        * 删除特定下表的元素
        * 删除序列里的全部值为 key 的元素
**********************************************************/

#include <iostream>
#include <malloc.h>
using namespace std;

typedef int Datatype;

struct SeqList
{
    int MAXNUM; // 顺序表最大长度
    int n;      // 顺序表实际长度
    Datatype *element;
};

typedef struct SeqList *PSeqList;

PSeqList createEmptySeq(int m)
{
    PSeqList palist = (PSeqList)malloc(sizeof(struct SeqList));
    if (palist != NULL)
    {
        palist->element = (Datatype *)malloc(sizeof(Datatype) * m);
        if (palist->element)
        {
            palist->MAXNUM = m;
            palist->n = 0;
            return palist;
        }
        else
            free(palist);
    }
    cout << "out of space\n";
    return NULL;
}

int isNULLSeq(PSeqList palist)
{
    return (palist->n == 0);
}

void showSeq(PSeqList palist)
{
    int i;
    for (i = 0; i < palist->n; i++)
        cout << palist->element[i] << " ";
    cout << endl;
}

int locate_Seq(PSeqList palist, Datatype key)
{
    int i;
    for (i = 0; i < palist->n; i++)
        if (palist->element[i] == key)
            return i;
    return -1;
}
void insertItem(PSeqList palist, int p, Datatype x)
{
    palist->element[p] = x;
    palist->n = palist->n + 1;
}
void insertPre_seq(PSeqList palist, int p, Datatype key)
{
    if (p < 0 || p > palist->n)
        cout << "No this place\n";
    if (palist->n >= palist->MAXNUM)
        cout << "Over flow" << endl;

    int i;
    for (i = palist->n - 1; i >= p; i--)
        palist->element[i + 1] = palist->element[i];
    palist->element[p] = key;
    palist->n = palist->n + 1;
}

int insertPost_seq(PSeqList palist, int p, Datatype key)
{
    if (p < 0 || p > palist->n)
        cout << "No this place\n";
    if (palist->n >= palist->MAXNUM)
        cout << "Over flow" << endl;

    int i;
    for (i = palist->n - 1; i > p; i--)
        palist->element[i + 1] = palist->element[i];
    palist->element[i + 1] = key;
    palist->n = palist->n + 1;
    return 1;
}

int deleteP_seq(PSeqList palist, int p)
{
    int q;
    if (p < 0 || p > palist->n - 1)
    {
        cout << "Not exist\n";
        return 0;
    }
    for (q = p; q < palist->n - 1; q++)
        palist->element[q] = palist->element[q + 1];
    palist->n = palist->n - 1;
    return 1;
}

/*
 * 从顺序表中删除全部值为key的元素
 * 如果一个个删的话，会浪费大量时间在移动元素的过程中，可否只移动一次
 * 可以从头扫描一边palist，用k记录元素值等于key的个数,对于不等于key的元素
 * 前移k个位置
 */
int deleteV_seq(PSeqList palist, Datatype key)
{
    int count = 0, i;
    for (i = 0; i < palist->n; i++)
    {
        if (palist->element[i] == key)
            count++;
        else
            palist->element[i - count] = palist->element[i];
    }
    palist->n = palist->n - count;
    return 1;
}

/*
 * 另一种思路：
 * 把不等于key的都往前移动一位
 * 等于key的就不管它，这样它就会被覆盖掉
 */
void deleteV_seq_pro(PSeqList palist, Datatype key)
{
    int i, k = 0;
    for (i = 0; i < palist->n; i++)
    {
        if (palist->element[i] != key)
        {
            palist->element[k] = palist->element[i];
            k++;
        }
    }
    palist->n = k;
}

void reverSeq(PSeqList palist)
{
    int i;
    Datatype tmp;
    for (i = 0; i < palist->n / 2; i++)
    {
        tmp = palist->element[palist->n - 1];
        palist->element[palist->n - 1] = palist->element[i];
        palist->element[i] = tmp;
        // palist->n-1;
    }
}

int main()
{
    int m;
    cout << "input MAXNUM:\n";
    cin >> m;
    PSeqList palist = createEmptySeq(m);

    cout << "input items:\n";
    int count = 0;
    Datatype data;
    cin >> data;
    while (data)
    {
        insertItem(palist, count, data);
        // insertPost_seq(palist,count, data);
        count++;
        cin >> data;
    }

    cout << "show seqlist:\n";
    showSeq(palist);

    int loc;
    cout << "to find index, input data:\n";
    cin >> loc;
    cout << locate_Seq(palist, loc) << endl;

    int pre;
    Datatype data_pre;
    cout << "input insert pre_locate & data:\n";
    cin >> pre >> data_pre;
    insertPre_seq(palist, pre, data_pre);
    showSeq(palist);

    int pos;
    Datatype data_pos;
    cout << "input insert aft_locate & data:\n";
    cin >> pos >> data_pos;
    insertPost_seq(palist, pos, data_pos);
    showSeq(palist);

    int d_pos;
    cout << "input delete postion:\n";
    cin >> d_pos;
    deleteP_seq(palist, d_pos);
    showSeq(palist);

    Datatype data_delete;
    cout << "input item you want to del:\n";
    cin >> data_delete;
    //这个也行 deleteV_seq(palist, data_delete);
    deleteV_seq_pro(palist, data_delete);
    showSeq(palist);

    cout << "Reverse list:\n";
    reverSeq(palist);
    showSeq(palist);

    return 0;
}
