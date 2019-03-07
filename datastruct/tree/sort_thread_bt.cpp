/***********************************************************
* Author       : M_Kepler
* EMail        : hellohuangjinjie@gmail.com
* Last modified: 2016-07-03 14:42:46
* Filename     : sort_thread_bt.cpp
* Description  :
    * 线索二叉树:
        *
    * 查找:
    * 插入:
    * 删除:
        * 删除节点为叶节点
            *
        * 删除节点左子树空,右子树非空:
            * 该节点的右子树替换该节点的位置
            * 找到右子树里最小的节点替换删除的节点
            *
        * 删除节点左子树非空,右子树空:
            * 该节点的左子树替换该节点的位置
            * 找到左子树里最大的节点替换删除的节点
            *
        * 删除节点左右子树非空
            * 用该节点左子树最右/大节点替换该节点的位置
            * --------右------左/小--------------------
**********************************************************/

#include <iostream>
#include <stack>
using namespace std;
typedef int ELEMENT_TYPE;

typedef struct Node
{
    ELEMENT_TYPE data;
    struct Node *lchild, *rchild;
    int ltag, rtag;
    // 如果ltag=0，表示存在左子树，指向左子树；
    // 如果ltag=1，表示左子树为NULL,lchild指向前驱
} BNode;

//定义树的根节点，（全局变量）默认NULL
BNode *root;

// 向树中插入结点，构造二叉排序树
void InsertNodeToCreateTree(ELEMENT_TYPE element)
{
    //构造根节点
    if (root == NULL)
    {
        root = new BNode();
        root->data = element;
        root->rchild = NULL;
        root->lchild = NULL;
    }
    else
    {
        BNode *parentNode = root;  //当前结点的父结点
        BNode *currentNode = root; //当前结点
        //构造新的结点
        BNode *newNode = new BNode();
        newNode->data = element;
        newNode->lchild = NULL;
        newNode->rchild = NULL;
        while (currentNode != NULL)
        {
            parentNode = currentNode;
            if (currentNode->data > element)
            {
                currentNode = currentNode->lchild;
            }
            else
                currentNode = currentNode->rchild;
        }
        if (parentNode->data > element)
            parentNode->lchild = newNode;
        else
            parentNode->rchild = newNode;
    }
}

//先序递归遍历二叉树
void PreOrder(BNode *p)
{
    if (p != NULL)
    {
        cout << p->data << " ";
        PreOrder(p->lchild);
        PreOrder(p->rchild);
    }
}
//先序非递归遍历二叉树
void PreOrderF()
{
    BNode *p = root;
    stack<BNode *> stack; //定义存放结点的栈
    while (!(p == NULL && stack.empty()))
    {
        if (p != NULL)
        {
            cout << p->data << " ";
            if (p->rchild != NULL) //如果右子树不为空则进栈
                stack.push(p);
            p = p->lchild;
        }
        else
        {
            p = stack.top()->rchild;
            stack.pop();
        }
    }
    cout << endl;
}

//中序递归遍历二叉树
void MiddleOrder(BNode *p)
{
    if (p != NULL)
    {
        MiddleOrder(p->lchild);
        cout << p->data << "  ";
        MiddleOrder(p->rchild);
    }
}
//中序非递归遍历二叉树
void MiddleOrderF()
{
    BNode *p = root;
    stack<BNode *> stack;
    while (!(p == NULL && stack.empty()))
    {
        //当前结点不为空则进栈
        if (p != NULL)
        {
            stack.push(p);
            p = p->lchild;
        }
        else
        {
            p = stack.top();
            stack.pop();
            cout << p->data << "  ";
            p = p->rchild;
        }
    }
    cout << endl;
}

//后序递归遍历二叉树
void PostOrder(BNode *p)
{
    if (p != NULL)
    {
        PostOrder(p->lchild);
        PostOrder(p->rchild);
        cout << p->data << "  ";
    }
}
//后序非递归遍历二叉树
void PostOrderF()
{
    BNode *p = root;
    BNode *pre = NULL; //指向当前访问节点的前驱结点
    stack<BNode *> stack;
    while (!(p == NULL && stack.empty()))
    {

        if (p != NULL)
        {
            stack.push(p);
            pre = p;
            p = p->lchild;
        }
        else
        {
            p = stack.top(); //取得栈顶元素
            //如果p的右子树不为空并且没有访问过，则访问右子树
            if (p->rchild != NULL && p->rchild != pre)
            {
                pre = p;
                p = p->rchild;
            }
            //如果右子树为空或者已经访问过，则访问当前结点
            else
            {
                cout << p->data << "  ";
                stack.pop(); //右子树为空，或则已经访问过，则访问了当前结点后直接出栈
                pre = p;
                p = NULL; //为下一轮遍历准备
            }
        }
    }
}

// 二叉排序树上刪除元素
void DeleteNode(ELEMENT_TYPE element)
{
    int flag = 0;
    //0表示当前结点在其父结点的左子树上，1表示在其父结点的右子树上
    if (root == NULL)
    {
        cout << "错误，二叉树为空" << endl;
    }
    else
    {
        BNode *currentNode = root; //需要删除的节点
        BNode *parentNode = NULL;  //父节点
        //找到指定元素的结点,并记录父节点
        while (currentNode->data != element)
        {
            parentNode = currentNode;
            if (currentNode->data > element)
            {
                flag = 0;
                currentNode = currentNode->lchild;
            }
            else
            {
                flag = 1;
                currentNode = currentNode->rchild;
            }
        }
        if (currentNode->data == element)
        {
            //当前结点在其父节点的左子树上
            if (flag == 0)
            {
                //判断当前结点的子树的情况:
                //当前结点为叶子结点
                if (currentNode->lchild == NULL && currentNode->rchild == NULL)
                {
                    parentNode->lchild = NULL;
                }
                // 当前结点只有左子树
                if (currentNode->lchild != NULL && currentNode->rchild == NULL)
                {
                    parentNode->lchild = currentNode->lchild;
                }
                // 当前结点只有右子树
                if (currentNode->lchild == NULL && currentNode->rchild != NULL)
                {
                    parentNode->lchild = currentNode->rchild;
                }
                // 当前结点有左，右子树
                if (currentNode->lchild != NULL && currentNode->rchild != NULL)
                {
                    parentNode->lchild = currentNode->rchild;
                    BNode *rnode = currentNode->rchild;
                    BNode *lnode = currentNode->lchild;
                    //查找右子树的最左结点
                    while (rnode->lchild != NULL)
                        rnode = rnode->lchild;
                    rnode->lchild = lnode;
                }
            }
            //当前结点在其父节点的右子树上
            if (flag == 1)
            {
                //判断当前结点的子树的情况:
                //当前结点为叶子结点
                if (currentNode->lchild == NULL && currentNode->rchild == NULL)
                {
                    parentNode->rchild = NULL;
                }
                // 当前结点只有左子树
                if (currentNode->lchild != NULL && currentNode->rchild == NULL)
                {
                    parentNode->rchild = currentNode->lchild;
                }
                // 当前结点只有右子树
                if (currentNode->lchild == NULL && currentNode->rchild != NULL)
                {
                    parentNode->rchild = currentNode->rchild;
                }
                // 当前结点有左，右子树
                if (currentNode->lchild != NULL && currentNode->rchild != NULL)
                {
                    parentNode->rchild = currentNode->rchild;
                    BNode *rnode = currentNode->rchild;
                    BNode *lnode = currentNode->lchild;
                    //查找右子树的最左结点
                    while (rnode->lchild != NULL)
                        rnode = rnode->lchild;
                    rnode->lchild = lnode;
                }
            }
            delete currentNode;
        }
        // 如果没有找到指定元素的结点
        else
        {
            cout << "指定元素的结点不存在" << endl;
        }
    }
}

// 中序递归线索二叉树，注意第一个结点后最后一个结点（第一个没有前驱，最后一个没有后继）   这两个特殊情况
/*
 * pre 表示中序遍历事当前结点的前驱结点
 *
 */
BNode *order_pre = NULL;
void InorderLining(BNode *p)
{
    if (p != NULL)
    {
        InorderLining(p->lchild);
        if (p->lchild == NULL)
        {
            p->ltag = 1;
            p->lchild = order_pre; //左节点指向根节点
        }
        if (order_pre != NULL && order_pre->rchild == NULL)
        {
            order_pre->rtag = 1;
            order_pre->rchild = p;
        }
        order_pre = p;
        InorderLining(p->rchild);
    }
}

//根据中序线索化之后查找某个元素值结点的前驱和后继
//需要注意的是，当对二叉树进行线索化之后，结点的指针域发生了变化，
//原来有效的指针的条件都是tag==0
void FindPreAndPost(ELEMENT_TYPE element)
{
    if (root == NULL)
    {
        cout << "二叉树为空" << endl;
    }
    else
    {
        BNode *currentNode = root;
        while (currentNode != NULL & currentNode->data != element)
        {
            if (currentNode->ltag == 1 && currentNode->rtag == 1) //实际上是原先的叶子结点
                break;
            if (currentNode->data > element && currentNode->ltag == 0)
                currentNode = currentNode->lchild;
            if (currentNode->data < element && currentNode->rtag == 0)
                currentNode = currentNode->rchild;
        }
        // 如果找到了指定元素的结点
        if (currentNode != NULL & currentNode->data == element)
        {
            cout << "当前结点的值：" << element << "   ";
            if (currentNode->ltag == 1)
            {
                if (currentNode->lchild != NULL)
                    cout << "前驱是：" << currentNode->lchild->data << "   ";
                else
                    cout << "前驱为空"
                         << "   ";
            }
            //如果左子树不为空的话，则当前结点的前驱为其左子树的“最右下方”结点
            else
            {
                BNode *lnode = currentNode->lchild;
                while (lnode->rchild != NULL && lnode->ltag == 0)
                    lnode = lnode->rchild;
                cout << "前驱是:" << lnode->data << "   ";
            }
            if (currentNode->rtag == 1)
            {
                if (currentNode->rchild != NULL)
                    cout << "后继是：" << currentNode->rchild->data << "   ";
            }
            //如果右子树不为空的话，则当前结点的后继为其右子树树的“最左下方”结点
            else
            {
                if (currentNode->rchild == NULL) //如果是中序遍历，线索化之后的最后一个结点没有后继
                    cout << "后继为空";
                else
                {
                    BNode *rnode = currentNode->rchild;
                    while (rnode->lchild != NULL && rnode->ltag == 0)
                        rnode = rnode->lchild;
                    cout << "后继是:" << rnode->data << "   ";
                }
            }
        }
        else
            cout << "该节点不存在" << endl;
    }
    cout << endl;
}

//注意，对于程序中对二叉树的遍历的时候并没有考虑线索化，所以针对排序二叉树的建立，结点删除，以及各种
//遍历可以单独测试

void test01()
{
    //插入结点创建排序二叉树
    InsertNodeToCreateTree(36);
    InsertNodeToCreateTree(57);
    InsertNodeToCreateTree(25);
    InsertNodeToCreateTree(18);
    InsertNodeToCreateTree(30);
    InsertNodeToCreateTree(68);
    InsertNodeToCreateTree(60);
    InsertNodeToCreateTree(59);
    InsertNodeToCreateTree(58);
    InsertNodeToCreateTree(65);
    InsertNodeToCreateTree(63);
    InsertNodeToCreateTree(67);
    InsertNodeToCreateTree(62);
    InsertNodeToCreateTree(64);

    cout << "先序遍历树:\n";
    PreOrder(root);
    cout << endl;
    PreOrderF();

    cout << "中序遍历树:\n";
    MiddleOrder(root);
    cout << endl;
    MiddleOrderF();

    cout << "后序遍历树:\n";
    PostOrder(root);
    cout << endl;
    PostOrderF();
    cout << endl;
    cout << "删除结点62:\n";
    DeleteNode(62);

    cout << "遍历树:\n";
    PreOrder(root);
    cout << endl;
    PreOrderF();

    MiddleOrder(root);
    cout << endl;
    MiddleOrderF();

    cout << "后序遍历树:\n";
    PostOrder(root);
    cout << endl;
    PostOrderF();
    cout << endl;
}
void test02()
{
    cout << "请输入二叉树节点\n";
    ELEMENT_TYPE data;
    cin >> data;
    while (data)
    {
        InsertNodeToCreateTree(data);
        cin >> data;
    }
    cout << "先序遍历树:\n";
    PreOrder(root);
    cout << endl;
    PreOrderF();

    cout << "中序遍历树:\n";
    MiddleOrder(root);
    cout << endl;
    MiddleOrderF();

    cout << "线索化二叉树:\n";
    InorderLining(root);

    cout << "输入需要寻找的前驱后继结点\n";
    ELEMENT_TYPE find;
    cin >> find;
    FindPreAndPost(find);
}

int main()
{
    test02();
    return 0;
}
