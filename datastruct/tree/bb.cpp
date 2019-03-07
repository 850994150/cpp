// 链式二叉查找树的各种操作.cpp :
// Defines the entry point for the console application.
//
#include <iostream>
#include <malloc.h>
using namespace std;
struct BSTree
{
    int data;
    BSTree *left;
    BSTree *right;
};
//标记在插入时，如果已存在，则为true ，表示不需要插入，否则为false
bool flag = false;
int a[100];
//查找操作
BSTree *search(BSTree *r, int x)
{
    if (r == NULL)
        return NULL;
    else
    {
        if (r->data == x)
            return r;
        else if (r->data > x)
            return search(r->left, x);
        else
            return search(r->right, x);
    }
}
//返回最小值节点
BSTree *BSTMinNum(BSTree *r)
{
    BSTree *s = r;
    while (s->left != NULL)
    {
        s = s->left;
    }
    return s;
}
//返回最大值节点
BSTree *BSTMaxNum(BSTree *r)
{
    BSTree *s = r;
    while (s->right != NULL)
    {
        s = s->right;
    }
    return s;
}
//获得其父节点
BSTree *getFather(BSTree *r, BSTree *s)
{
    BSTree *sf;
    if (r == NULL || r == s)
        sf = NULL;
    else
    {
        if (s == r->left || s == r->right)
            sf = r;
        else if (s->data > r->data)
            sf = getFather(r->right, s);
        else
            sf = getFather(r->left, s);
    }
    return sf;
}
//获得节点中序的前趋节点
//此操作不需要遍历树
BSTree *searchPreMidOrder(BSTree *r, int val)
{
    BSTree *s = search(r, val);
    if (s == NULL)
        return NULL;
    else
    {
        //如果左儿子节点非空，则找到左子树的最大值节点
        if (s->left != NULL)
            return BSTMaxNum(s->left);
        //如果左儿子节点空，则找到第一个有右儿子节点的其祖辈节点
        BSTree *p = getFather(r, s);
        while (p != NULL && s == p->left)
        {
            s = p;
            p = getFather(r, s);
        }
        return p;
    }
}
//获得节点中序的后继节点
//此操作不需要遍历树
BSTree *searchPostMidOrder(BSTree *r, int val)
{
    BSTree *s = search(r, val);
    if (s == NULL)
        return NULL;
    else
    {
        //如果右儿子节点非空，则找到右子树的最小值节点
        if (s->right != NULL)
        {
            return BSTMinNum(s->right);
        }
        //如果右儿子节点为空，则找到第一个有左儿子节点的其祖辈节点
        BSTree *p = getFather(r, s);
        while (p != NULL && s == p->right)
        {
            s = p;
            p = getFather(r, s);
        }
        return p;
    }
}
//插入操作
BSTree *insert(BSTree *r, BSTree *s)
{
    //首先查找树中是否已存在此节点
    BSTree *p = search(r, s->data);
    if (p == NULL)
    {
        flag = false;
        if (r == NULL)
        {
            r = s;
        }
        else if (s->data < r->data)
            r->left = insert(r->left, s);
        else if (s->data > r->data)
            r->right = insert(r->right, s);
    }
    else
        flag = true;
    return r;
}

//建树
BSTree *createBSTree(BSTree *r, int *a, int n)
{
    int i;
    BSTree *t;
    t = r;
    for (i = 0; i < n; i++)
    {
        BSTree *s = (BSTree *)malloc(sizeof(BSTree));
        s->data = a[i];
        s->left = NULL;
        s->right = NULL;
        t = insert(t, s);
    }
    return t;
}

//删除操作
BSTree *deleteNode(BSTree *r, BSTree *s)
{
    //BSTNODE   *   temp,   *   tfather,   *   pf;
    BSTree *temp, *father, *sf;
    //pf   =   getfather(p,   r);
    sf = getFather(r, s);
    //被删除结点是叶子结点,   不是根结点
    if (s->left == NULL && s->right == NULL && sf != NULL)
        //
        if (sf->left == s)
            sf->left = NULL;
        //
        else
            sf->right = NULL;
    //被删除结点是叶子结点,又是根结点
    else if (s->left == NULL && s->right == NULL && sf == NULL)
        r = NULL;
    //被删除结点有右孩子,无左孩子.被删结点是根结点
    else if (s->left == NULL && s->right != NULL && sf != NULL)
        if (sf->left == s)
            sf->left = s->right;
        else
            sf->right = s->right;
    //被删除结点有右孩子,无左孩子.被删结点是根结点
    else if (s->left == NULL && s->right != NULL && sf == NULL)
        r = s->right;
    //被删结点有左孩子,无右孩子.被删结点不是根结点
    else if (s->left != NULL && s->right == NULL && sf != NULL)
        if (sf->left == s)
            sf->left = s->left;
        else
            sf->right = s->left;
    //被删结点有左孩子,无右孩子.被删结点是根结点
    else if (s->left != NULL && s->right == NULL && sf == NULL)
        r = s->left;
    else if (s->left != NULL && s->right != NULL)
    {
        temp = s->left;
        father = s;
        //找出左子树最大的节点
        while (temp->right != NULL)
        {
            father = temp;
            temp = temp->right;
        }
        s->data = temp->data;
        if (father != s)
            father->right = temp->left;
        else
            father->left = temp->left;
    }
    if (r == NULL)
        cout << "删除之后，二叉排序树为空！" << endl;
    else
        cout << "删除成功！" << endl;
    return r;
}
//前序输出
void preOrder(BSTree *r)
{
    if (r == NULL)
        return;
    else
    {
        cout << r->data << " ";
        preOrder(r->left);
        preOrder(r->right);
    }
}
//中序输出
void inOrder(BSTree *r)
{
    if (r == NULL)
        return;
    else
    {
        inOrder(r->left);
        cout << r->data << " ";
        inOrder(r->right);
    }
}
//后续输出
void postOrder(BSTree *r)
{
    if (r == NULL)
        return;
    else
    {
        postOrder(r->left);
        postOrder(r->right);
        cout << r->data << " ";
    }
}
int main()
{
    int cases;
    cout << "请输入案例个数：" << endl;
    cin >> cases;
    while (cases--)
    {
        // memset(a,0,sizeof(a));
        int n;
        flag = false;
        BSTree *root = NULL;
        cout << "请输入元素个数：" << endl;
        cin >> n;
        int i;
        cout << "请输入这些元素：" << endl;
        for (i = 0; i < n; i++)
            cin >> a[i];
        cout << "建立二叉排序树!" << endl;
        root = createBSTree(root, a, n);
        if (root != NULL)
            cout << "二叉排序树建立成功！" << endl;
        else
        {
            cout << "二叉排序树建立失败！" << endl;
            return 0;
        }
        cout << "此二叉树根的值为：" << endl;
        cout << root->data << endl;
        cout << "请选择您要进行的操作：" << endl;
        cout << "1.插入(I/i)" << endl;
        cout << "2.查找(S/s)" << endl;
        cout << "3.删除(D/d)" << endl;
        cout << "4.先序输出(P/p)" << endl;
        cout << "5.中序输出(M/m)" << endl;
        cout << "6.后序输出(L/l)" << endl;
        cout << "7.退出(E/e)" << endl;
        char s;
        cin >> s;
        while (1)
        {
            if (s == 'E' || s == 'e')
                break;
            else if (s == 'I' || s == 'i')
            {
                cout << "请输入您要插入的值：" << endl;
                int x;
                cin >> x;
                BSTree *p = (BSTree *)malloc(sizeof(BSTree));
                p->data = x;
                p->left = NULL;
                p->right = NULL;
                root = insert(root, p);
                if (flag == false)
                    cout << "插入成功！" << endl;
                else
                {
                    cout << "此二叉树中已存在此值！" << endl;
                    flag = false; //恢复原值
                }
            }
            else if (s == 'S' || s == 's')
            {
                cout << "请问您需要查询哪种信息？" << endl;
                cout << "1.此值的相关信息(1)：" << endl;
                cout << "2.二叉排序树最小值(2)：" << endl;
                cout << "3.二叉排序树最大值(3)：" << endl;
                cout << "4.此值的中序前趋节点值(4)：" << endl;
                cout << "5.此值的中序后继节点值(5)：" << endl;
                cout << "6.退出查询(6)：" << endl;
                int cs;
                cin >> cs;
                while (1)
                {
                    if (cs == 1)
                    {
                        cout << "请输入您要查找的值：" << endl;
                        int x;
                        cin >> x;
                        BSTree *p = search(root, x);
                        BSTree *pfather = getFather(root, p);
                        cout << "查找的值为：" << p->data << endl;
                        if (pfather != NULL)
                            cout << "其父节点的值为：" << pfather->data << endl;
                        else
                            cout << "它是根节点，没有父节点！" << endl;
                        if (p->left == NULL && p->right == NULL)
                            cout << "它是叶子节点，没有子节点" << endl;
                        else
                        {
                            if (p->left != NULL)
                                cout << "其左儿子节点的值为：" << p->left->data << endl;
                            else
                                cout << "其左儿子节点为空！" << endl;
                            if (p->right != NULL)
                                cout << "其右儿子的值为：" << p->right->data << endl;
                            else
                                cout << "其右儿子节点为空！" << endl;
                        }
                    }
                    else if (cs == 2)
                    {
                        BSTree *node = BSTMinNum(root);
                        cout << "此二叉排序树的最小值为：" << node->data << endl;
                    }
                    else if (cs == 3)
                    {
                        BSTree *node = BSTMaxNum(root);
                        cout << "此二叉排序树的最大值为：" << node->data << endl;
                    }
                    else if (cs == 4)
                    {
                        int val;
                        cout << "请输入一个值：" << endl;
                        cin >> val;
                        BSTree *node = searchPreMidOrder(root, val);
                        if (node == NULL)
                            cout << "不存在此其值为" << val << "的节点或其前趋节点" << endl;
                        else
                        {
                            cout << "此节点的值为：" << val << endl;
                            cout << "其中序前趋节点的值：" << node->data << endl;
                        }
                    }
                    else if (cs == 5)
                    {
                        int val;
                        cout << "请输入一个值：" << endl;
                        cin >> val;
                        BSTree *node = searchPostMidOrder(root, val);
                        if (node == NULL)
                            cout << "不存在此其值为" << val << "的节点或其后继节点" << endl;
                        else
                        {
                            cout << "此节点的值为：" << val << endl;
                            cout << "其中序后继节点的值：" << node->data << endl;
                        }
                    }
                    else if (cs == 6)
                        break;
                    else
                    {
                        cout << "输入的指令不对，请重新输入！" << endl;
                    }
                    cout << "请问您需要查询哪种信息？" << endl;
                    cin >> cs;
                }
            }
            else if (s == 'D' || s == 'd')
            {
                cout << "请输入您要删除的节点的值：" << endl;
                int value;
                cin >> value;
                cout << "你确定要删除吗？(Yy/Nn)" << endl;
                char order;
                cin >> order;
                while (1)
                {
                    if (order == 'Y' || order == 'y')
                    {
                        BSTree *node;
                        node = search(root, value);
                        if (node == NULL)
                            cout << "该节点不存在！" << endl;
                        else
                            BSTree *nodeDel = deleteNode(root, node);
                        break;
                    }
                    else if (order == 'N' || order == 'n')
                    {
                        break;
                    }
                    else
                    {
                        cout << "命令不正确，请重新输入！" << endl;
                        cin >> order;
                    }
                }
            }
            else if (s == 'P' || s == 'p')
            {
                cout << "其前序输出为：" << endl;
                preOrder(root);
                cout << endl;
            }
            else if (s == 'M' || s == 'm')
            {
                cout << "其中序输出为：" << endl;
                inOrder(root);
                cout << endl;
            }
            else if (s == 'L' || s == 'l')
            {
                cout << "其后序输出为：" << endl;
                postOrder(root);
                cout << endl;
            }
            else
            {
                cout << "命令有误，请重新输入！" << endl;
            }
            cout << "请选择您要进行的操作：" << endl;
            cin >> s;
        }
    }
    return 0;
}
