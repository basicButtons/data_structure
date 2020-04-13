#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;
typedef struct BiTNode
{
    ElemType data;
    struct BiTNode *lchild, *rchild;
}BiTNode,*BiTree;

//创建一颗二叉树
void CreatBiTree(BiTree *T)
{
    ElemType c;
    scanf("%c",&c);
    if(' '==c)
    {
        *T = NULL; 
    }
    else
    {
        *T = (BiTNode *)malloc(sizeof(BiTNode));
        (*T)->data=c;
        CreatBiTree(&(*T)->lchild);
        CreatBiTree(&(*T)->rchild);
    }
}
int visit(ElemType c,int level)
{
    printf("数据%c在第%d层\n",c,level);
    return 0;
}
//遍历二叉树
void PreOrderTraverse(BiTree T,int level)
{
    if(T)
    {
        visit(T->data, level);
        PreOrderTraverse(T->lchild,level+1);
        PreOrderTraverse(T->rchild,level+1);
    }
}


int main()
{
    int level = 1;
    BiTree T = NULL;
    CreatBiTree(&T);
    PreOrderTraverse(T,level);
    return 0;
}