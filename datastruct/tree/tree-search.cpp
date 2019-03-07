/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2016-03-17 18:22:36
 * Filename     : tree-search.cpp
 * Description  :
 ***********************************************************
 */

#include <iostream>
#include <malloc.h>
#include <queue>
using namespace std;

typedef int DataType;

typedef struct BiTNode
{
    DataType info;
    struct BiTNode *llink, *rlink;
} BiTNode, *BiTree;

bool searchNode(BiTree root, DataType data)
{
    if (root == NULL)
    {
        cout << "empty tree\n";
        return false;
    }
    while (root != NULL)
    {
        if (root->info == data)
            return true;
        else if (root->info < data)
            root = root->rlink;
        else
            root = root->llink;
    }
    return false;
}

void insertNode(BiTree &root, DataType data)
{
    BiTNode *parentNode = root; // 记录插入节点的父节点
    BiTNode *currentNode = root;

    BiTree newNode = (BiTree)malloc(sizeof(BiTNode));
    newNode->info = data;
    newNode->llink = newNode->rlink = NULL;

    if (root == NULL)
    {
        root = newNode;
    }
    else
    {
        while (currentNode != NULL)
        {
            parentNode = currentNode;
            if (currentNode->info > data) // 小的结点插入到左子树
                currentNode = currentNode->llink;
            else
                currentNode = currentNode->rlink;
        }
        // 循环结束找到待插入结点的父节点
        // 和二叉搜索不一样的是, 搜索找到就跳出了; 插入则是一直找，直到找到叶结点

        if (parentNode->info < data)
            parentNode->rlink = newNode;
        else
            parentNode->llink = newNode;
    }
}

void deleteNode(BiTree root, DataType data)
{
}

void MiddleOrder(BiTree root)
{
    if (root != NULL)
    {
        MiddleOrder(root->llink);
        cout << root->info << " ";
        MiddleOrder(root->rlink);
    }
}

void LevelOrder(BiTree T)
{
    BiTree p = T;
    queue<BiTree> queue;
    //根节点入队
    queue.push(p);
    //队列不空循环
    while (!queue.empty())
    {
        //对头元素出队
        p = queue.front();
        printf("%d ", p->info);
        queue.pop();
        //左子树不空，将左子树入队, 输出左子树结点
        if (p->llink!= NULL)
        {
            queue.push(p->llink);
        }
        //右子树不空，将右子树入队, 输出右子树结点
        if (p->rlink!= NULL)
        {
            queue.push(p->rlink);
        }
    }
}
//释放树空间
void DestroyBinTree(BiTree t)
{
    if (t == NULL)
        return;
    DestroyBinTree(t->llink);
    DestroyBinTree(t->rlink);
    t->llink= NULL;
    t->rlink= NULL;
    free(t);
}

int main()
{
    BiTree T = NULL;
    printf("            36                 \n");
    printf("        /         \\           \n");
    printf("    25              57         \n");
    printf("  /    \\              \\      \n");
    printf("18      29              68     \n");
    printf("          \\           /    \\ \n");
    printf("            30       60     69 \n");

    cout << "待插入序列:\n36 57 25 18 29 30 68 60 59\n" << endl;
    insertNode(T, 36);
    insertNode(T, 57);
    insertNode(T, 25);
    insertNode(T, 18);
    insertNode(T, 29);
    insertNode(T, 30);
    insertNode(T, 68);
    insertNode(T, 60);
    insertNode(T, 59);
    cout << "中序遍历:" << endl;
    MiddleOrder(T);
    cout << "\n\n层次遍历:" << endl;
    LevelOrder(T);
    cout << "\n\n搜索:" << endl;
    DataType key;
    cin >> key;
    if (searchNode(T, key))
        cout << "found" << endl;
    else
        cout << "not found" << endl;

    cout << "释放树空间" << endl;
    DestroyBinTree(T);
    return 0;
}

/*
                    36
                /         \
            25              57
          /    \              \
        18      29              68
                  \           /    \
                    30       60     69

*/
