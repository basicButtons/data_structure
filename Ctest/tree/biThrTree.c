#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

//Link(0),表示指向左右孩子的指针，
//Thread(1),表示指向前驱后继的线索
typedef enum {Link,Thread} PointerTag;



typedef struct BiThrNode
{
    ElemType data;
    struct BiThrNode *lchild, *rchild;
    PointerTag ltag;
    PointerTag rtag; 
}BiThrNode,*BiThrTree;

//全局变量始终指向刚刚访问过的结点
BiThrNode pre;

//前序遍历来建立二叉树。
void CreatBiThrTree(BiThrTree *T)
{
    ElemType c;
    scanf("%c",&c);
    if(' '==c)
    {
        *T = NULL; 
    }
    else
    {
        *T = (BiThrNode *)malloc(sizeof(BiThrNode));
        (*T)->data=c;
        (*T)->ltag = Link;
        (*T)->rtag = Link;
        CreatBiThrTree(&(*T)->lchild);
        CreatBiThrTree(&(*T)->rchild);
    }
}

void Inthreading(BiThrTree T)
{
    if(T)
    {
        InThreading(T->lchild); //递归左孩子线索化
        if(!T->lchild == NULL)  
        {
            T->lchild = Thread;
            T->lchild = pre;
        }
        if(!pre->rchild==NULL)
        {
            pre->rchild = Thread;
            pre->rchild = T;
        }
        pre = T;
        InThreading(T->rchild); //递归右孩子线索化
    }
    InOrderThreading(BiThrTree *p)
    {
        *p =(BiThrTree)malloc(sizeof(BiThrNode));
        (*p)->ltag = Link;
        (*p)->rtag = Thread;
        
    }

}
