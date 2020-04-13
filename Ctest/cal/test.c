#include <stdio.h>
#include <stdlib.h>
static int pos=0;     /*pos作为判断PLC是否为零的标志*/
static int pot=0;    /*pot用来指示是否输入了指数相同的数*/

typedef struct term          /*定义数据的节点数*/
{
    float coef;              /*定义浮点数系数*/
    int   expn;              /*定义整型指数*/
}term;

typedef struct LNode         /*定义节点*/
{
    term data;
    struct LNode *next;
}LNode,*Linklist;

typedef Linklist polynomial;

void init_polyn(polynomial *p) /*初始化多项式*/
{
    *p = (Linklist)malloc(sizeof(LNode));
    (*p)->next = NULL;         /*建立头节点*/
    (*p)->data.coef = 0.0;     /*头节点数据域存储此链表的大小*/
    (*p)->data.expn = -1;
}

int locateitem( polynomial *p, term item) /*找到要插入的位置*/
{
    int location =0;
    Linklist t = *p;
    t = t->next;
    while ((t != NULL) && (t->data.expn <= item.expn))
    {
        if ( t->data.expn == item.expn )  /*如果同一个多项式指数相同 将其做和*/
		{
			t->data.coef+=item.coef;
			pot=1;
		}
		else
        location++;
        t = t->next;

    }
    return location;
}

void disply_list(Linklist *L)               /*显示链表中的所有数据*/
{
    Linklist t;
    t = *L;
    t = t->next;
    if (t != NULL)
        do
        {
            if (t->next==NULL)
                printf("%.1f*X^%d",t->data.coef,t->data.expn);
            else
                printf("%.1f*X^%d + ",t->data.coef,t->data.expn);
            t = t->next;
        }
        while (t != NULL);
}

int insert_list(Linklist *L,int i,term item)   /*将数据item插入到链表的i位置后面*/
{
    Linklist t;
    t = *L;
    int j = 0;
    if (i<0)                                    /*i小于0时读取终止给出错误提示*/
    {
        printf("wrong number!\n");
        return 1;
    }
    while (t && j<i)
    {
        t = t->next;
        j++;
    }
    Linklist s = (Linklist)malloc(sizeof(LNode));  /*若空间不足则申请空间*/
    s->data.coef = item.coef;
    s->data.expn = item.expn;
    s->next = t->next;
    t->next = s;
    return 0;
}


int creat_polyn( polynomial *p, char c)  /*创建多项式*/
{
    int exp = 1;
    term temp;
    int i=0,j;
    printf("请分别输入LP%c每一项的系数和指数，并用空格隔开\n", c); /*循环输入n项多项式的系数和指数*/
   while (exp >= 0)
    {
        printf("coef expn %d:",1+i++);
        scanf("%f %d",&temp.coef,&temp.expn);
        exp = temp.expn;
        j = locateitem(p,temp);
		if(temp.expn>0&&pot==0)
        insert_list(p,j,temp);
		pot=0;
    }
    return 0;
}

void merge_list(Linklist *L,Linklist *K) /*连接两个链表*/
{
    Linklist p = *L;
    Linklist q = *K;
    while (p->next != NULL)
        p = p->next;
    p->next = q;
}


int add_polyn(polynomial *p1, polynomial *p2)/*将输入的两个多项式进行加法运算*/
{
    int i = 0;
    term sum;
    Linklist pa = (*p1)->next;
    Linklist pb = (*p2)->next;
    polynomial pc;
    init_polyn(&pc);
    while ((pa != NULL) && (pb != NULL)) /*如果两个多项式多不为空就进行下列计算*/
    {
        if (pa->data.expn < pb->data.expn) /*如果a的指数小于b的指数*/
        {
            insert_list(&pc,i,pa->data); /*在线性表c中i的位置插入a的元素*/
            i++;
            pa = pa->next;               /*a指针指向a的下一个元素*/
			pos=1;
        }
        else if (pa->data.expn > pb->data.expn) /*如果a的指数大于b的指数*/
        {
            insert_list(&pc,i,pb->data);  /*在线性表c中i的位置插入b的元素*/
            i++;
            pb = pb->next;   /*b指针指向b的下一个元素*/
			pos=1;
        }
        else
        {
            sum.coef = pa->data.coef+pb->data.coef;   /*如果a、b的指数相等，则系数相加，指数不变*/
            sum.expn = pa->data.expn;
            if ((sum.coef) != 0)
            {
                insert_list(&pc,i,sum);
                i++;
				pos=1;
            }
            pa = pa->next;
            pb = pb->next;

        }
    }
    if (pa != NULL)
        merge_list(&pc,&pa);
    if (pb != NULL)
        merge_list(&pc,&pb);
    pa = *p1;
    pb = *p2;
    printf("多项式 LPA 是:\n");
    disply_list(&pa);
    printf("\n的多项式 LPB 是:\n");
    disply_list(&pb);
    printf("\nLPA与LPB相加的结果 LPC 是:\n");
    disply_list(&pc);
	if(pos==0)
		printf("0");
    return 0;
}

int main()
{
    polynomial poly1,poly2;
    init_polyn(&poly1);
    init_polyn(&poly2);
    creat_polyn(&poly1, 'A');
    creat_polyn(&poly2, 'B');
    add_polyn(&poly1,&poly2);
    return 0;
}