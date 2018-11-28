/***********************************************************
 * Author       : M_Kepler
 * EMail        : hellohuangjinjie@gmail.com
 * Last modified: 2016-07-04 20:55:04
 * Filename     : tree-sort.cpp
 * Description  :
 **********************************************************/

#include <iostream>
#include <malloc.h>
using namespace std;

typedef int DataType;
typedef struct BinSearchTree{
    DataType data;
    struct BinSearchTree *llink,*rlink;
}BinTNode, *BinTree;

bool searchNode(BinTree T, DataType key) {
    bool found;
    if(T == NULL){
        found = false;
    }
    while(T!=NULL){
        if(T->data == key){
            found = true;
        }
        else if (T->data < key){
            T = T->rlink;
        }
        else
            T = T->llink;
    }
    return found;
}

void insertNode(BinTree T, DataType key) {
    BinTNode *newNode = (BinTree)malloc(sizeof(BinTNode));
    newNode->data = key;
    newNode->llink = newNode->rlink = NULL;
    if(T == NULL){
        T = newNode;
    }else{
        BinTNode* parentNode =(BinTree)malloc(sizeof(BinTNode));
        BinTNode* currentNode=(BinTree)malloc(sizeof(BinTNode));
        currentNode = T;
        while(currentNode!=NULL){
            parentNode = currentNode;
            if(currentNode->data == key){
                cout<<"item already exist\n";
            }
            else if (currentNode->data < key)
                currentNode = currentNode->rlink;
            else
                currentNode = currentNode->llink;
        }
        if(currentNode->data < key)
            currentNode->rlink  = newNode;
        else
            currentNode->llink = newNode;
    }
}

void visit(BinTree T){
    if(T!=NULL){
        cout<<T->data<<" ";
    }
}
void MiddleOrder(BinTree T){
    if(T !=NULL){
        MiddleOrder(T->llink);
        visit(T);
        MiddleOrder(T->rlink);
    }
}
int main()
{
    BinTree T=NULL;
    insertNode(T, 12);
    insertNode(T, 2);
    insertNode(T, 22);
    insertNode(T, 11);
    insertNode(T, 14);
    insertNode(T, 8);
    insertNode(T, 7);
    cout<<T;
    return 0;
}
