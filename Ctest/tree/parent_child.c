typedef char ElemType;
#define MAX_TREE_SIZE 100

#include <stdio.h>

typedef struct CTNode
{
    int child;              //孩子结点的下标
    struct CTNode *next;    //指向下一个孩子结点的指针
}*childPtr;

//表头结构
typedef struct 
{
    ElemType data;          //存放在树中的结点的数据
    int parent;             //存放双亲结点的下标
    childPtr firstchild;    //指向下一个自结点的指针
}CTBox;

typedef struct 
{
    CTBox nodes[MAX_TREE_SIZE];     //结点数据
    int r,n;                        //根的位置和结点的数目。                     
}Tree;