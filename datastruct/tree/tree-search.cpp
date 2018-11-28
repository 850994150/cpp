#include <iostream>
#include <malloc.h>
using namespace std;

typedef int DataType;

typedef struct BiTNode{
    DataType info;
    struct BiTNode *llink, *rlink;
}BiTNode,*BiTree;

bool searchNode(BiTree root, DataType data) {
    bool found;
    if(root == NULL){
        cout<<"empty tree\n";
        found = false;
    }
    while(root != NULL) {
        if(root->info == data)
            found = true;
        else if(root->info < data)
            root = root->llink;
        else
            root = root->rlink;
    }
    return found;
}

void insertNode(BiTree root, DataType data) {
    // BiTNode* newNode = new BiTNode();
    BiTree newNode = (BiTree)malloc(sizeof(BiTNode));
    newNode->info = data;
    newNode->llink = newNode->rlink = NULL;
    if(root == NULL) {
        root = newNode;
    }
    else{
        BiTNode* parentNode = root;
        BiTNode* currentNode = root;
        while(currentNode != NULL) {
            parentNode = currentNode;
            if(currentNode->info > data)
                currentNode = currentNode->llink;
            else
                currentNode = currentNode->rlink;
        }
        if(parentNode->info < data)
            parentNode->rlink = newNode;
        else
            parentNode->llink = newNode;
    }
}

void deleteNode(BiTree root, DataType data) {

}

void MiddleOrder(BiTree root) {
    if(root != NULL){
        MiddleOrder(root->llink);
        cout<< root->info <<" ";
        MiddleOrder(root->rlink);
    }
}

int main()
{
    BiTree T=NULL;
    insertNode(T,36);
    insertNode(T,57);
    insertNode(T,25);
    insertNode(T,18);
    insertNode(T,30);
    insertNode(T,68);
    insertNode(T,60);
    insertNode(T,59);
    MiddleOrder(T);
    return 0;
}
