#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int Status;

typedef struct BiTNode
{
    int data;
    struct BiTNode *lchild, *rchild;
}BiTNode,*BiTree;

Status SearchBST(BiTree T, int key, BiTree f, BiTree *p)
{
    if(!T)
    {
        *p =f;
        return FALSE;
    }
    else if( key == T->data )
    {
        *p = T;
        return TRUE;
    }
    else if( key < T->data )
    {
        return SearchBST(T->lchild,key,T,p);
    }
    else
    {
        return SearchBST(T->rchild,key,T,p);
    }   
}

Status InsertBNT(BiTree *T, int key)
{
    BiTree p,s;
    if(!SearchBST(*T,key,NULL,&p))
    {
        s = (BiTree)malloc(sizeof(BiTNode));
        s->data = key;
        s->lchild = s->rchild =NULL;
        
        if(!p)
        {
            *T = s;
        }
        else if(key < p->data)
        {
            p->lchild = s;
        }
        else if(key > p->data)
        {
            p->rchild = s;
        }
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
//如果是叶子结点，那么直接删除就好，
//如果只有一个自结点，那么直接接上去就好了
//如果既有左子树，又有右子树，删除的话需要其直接前驱或者直接后继替换上去就好了。

Status DeleteBST(BiTree *T, int key)
{
    if(!*T)
    {
        return 0;
    }
    else
    {
        if( key == (*T)->data )
        {
            Delete(T);
        }
        else if( key <(*T)->data )
        {
            return DeleteBST(&(*T)->lchild,key);
        }
        else if( key > (*T)->data)
        {
            return DeleteBST(&(*T)->rchild,key);
        }
    }
}
Status Delete(BiTree *p)
{
    BiTree q,s;
    if( (*p)->rchild == NULL)
    {
        q = *p;
        *p = (*p)->lchild;
        free(q); 
    }
    else if(  (*p)->lchild == NULL )
    {
        q = *p;
        *p = (*p)->rchild;
        free(q);   
    }
    else
    {
        q=*p;
        s=(*p)->lchild;
        while (s->rchild)
        {
            q=s;
            s = s->rchild;
        }
        (*p)->data = s->data;
        if(q!=*p)
        {
            q->rchild = s->lchild;
        }
        else
        {
            q->lchild = s->lchild; 
        }
        free(s);
    }    
}
