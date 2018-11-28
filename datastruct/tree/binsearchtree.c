#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAXNUM 100

typedef int KeyType;
typedef int DataType;

typedef struct {
    KeyType key;                    /* 字典元素的关键码字段     */
    DataType value;                 /* 字典元素的属性字段    */
} DicElement;

typedef struct {
    int n;                          /* n<=MAXNUM，为字典中元素的个数 */
    DicElement element[MAXNUM];
} SeqDictionary;

struct BinTreeNode;
typedef struct BinTreeNode * PBinTreeNode;

struct BinTreeNode {
    KeyType key;                    /* 结点的关键码字段 */
    DataType value;                 /*    结点的属性字段 */
    PBinTreeNode llink, rlink;      /* 二叉树的左、右指针 */
};

typedef struct BinTreeNode * BinTree;
typedef BinTree * PBinTree;

int searchNode(PBinTree ptree, KeyType key, PBinTreeNode *position) {
    PBinTreeNode p = *ptree, q = p;
    while (p != NULL) {
        q = p;
        if (p->key == key) {        /* 检索成功时，由参数position指向查找到的结点 */
            *position=p; return(TRUE);
        }
        else if (p->key > key)      /* 进入左子树继续检索 */
            p = p->llink;
        else p = p->rlink;          /* 进入右子树继续检索 */
    }

    *position=q;
    return FALSE;     /* 检索失败时，position指向该结点应插入的父结点 */
}

void insertNode(PBinTree ptree, KeyType key) {
    PBinTreeNode p, position;
    if (searchNode(ptree,key,&position) == TRUE) return; /* 已存在关键码为key的结点 */
    p = (PBinTreeNode)malloc(sizeof(struct BinTreeNode));/* 申请新结点 */
    if (p == NULL) {    /* 申请空间出错 */
        printf("Out of Space!\n");
        return;
    }
    p->key = key;                        /* 忽略对p->value的赋值 */
    p->llink = p->rlink = NULL;
    if (position == NULL)                 /* 原树为空树 */
        *ptree = p;
    else if (key < position->key)
        position->llink = p;             /* 插入position的左子树 */
    else position->rlink = p;            /* 插入position的右子树 */
}

void creatTree(PBinTree ptree, SeqDictionary dic) {
    int i;
    *ptree = (BinTree)malloc(sizeof(struct BinTreeNode));
    if (*ptree == NULL) {
        printf("Out of Space!\n.");
        return;
    }
    (*ptree)->llink = (*ptree)->rlink = NULL;
    (*ptree)->key = dic.element[0].key;
    for(i = 1; i < dic.n; i++)
        insertNode(ptree, dic.element[i].key);      /* 将新结点插入树中 */
}

void deleteNode(PBinTree ptree, KeyType key) {
    PBinTreeNode parentp = NULL, p = *ptree, r;
    while (p != NULL) {
        if (p->key == key) break;             /* 找到了关键码为key的结点 */
        parentp = p;
        if (p->key > key) p = p->llink;        /* 进入左子树 */
        else p = p->rlink;                    /* 进入右子树 */
    }

    if (p == NULL)  return;                   /* 二叉排序树中无关键码为key的结点 */

    if (p->llink == NULL) {                   /* 结点*p无左子树 */
        if (parentp == NULL)
            *ptree = p->rlink;                /* 被删除的结点是原二叉排序树的根结点*/
        else if (parentp->llink == p)         /* *p是其父结点的左子女 */
            parentp->llink = p->rlink;        /* 将*p的右子树链到其父结点的左链上 */
        else  parentp->rlink = p->rlink;      /* 将*p的右子树链到其父结点的右链上 */
    }
    else {  /* 结点*p有左子树 */
        r = p->llink;
        while (r->rlink != NULL) r = r->rlink;   /* 在*p的左子树中找最右下结点*r */
        r->rlink = p->rlink;                     /* 用*r的右指针指向*p的右子女 */
        if (parentp == NULL) *ptree = p->llink;
        else if (parentp->llink == p)            /* 用*p的左子女代替*p */
            parentp->llink = p->llink;
        else parentp->rlink = p->llink;
    }
    free (p);                                     /* 释放被删除结点 */
}
int main(){
    return 0;
}
