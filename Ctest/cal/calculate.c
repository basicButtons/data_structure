#include <stdio.h>
#include <stdlib.h>
static int pos=0;     /*pos作为判断PLC是否为零的标志*/
static int pot=0;    /*pot用来指示是否输入了指数相同的数*/

typedef struct data //define the data of node
{
    float coef;
    int exp;
}nodeData;

typedef struct LNode  //define the list node
{
    nodeData data;
    struct LNode* next;
}LNode,*Linklist;

typedef Linklist polynomial;

void init_poly(polynomial *p){
    *p = (Linklist)malloc(sizeof(LNode));
    (*p)->next = NULL;
    (*p)->data.coef = 0.0;
    (*p)->data.exp = -1;
};

int locateItem(polynomial *p, nodeData item){   //插入新的结点或者更改部分结点。
    int location = 0;
    Linklist t = *p;
    t = t->next;
    while((t != NULL) && ( t->data.coef <= item.coef)){
        if(item.exp == t->data.exp){
            t->data.coef += item.coef;
            pot = 1;
        }
        else{
            location++;
            t = t->next;
        }
    }
    return location;
};

void display_list(Linklist *L)
{
    Linklist t;
    t = *L;
    t = t->next;
    if(t != NULL){
        do{
            if(t->next == NULL){
                printf("%.1f*X^%d",t->data.coef,t->data.exp);
            }
            else{
                printf("%.1f*X^%d + ",t->data.coef,t->data.exp);
                t = t->next;
            }
        }while(t->next == NULL);
    }
}

int insert_list(Linklist *L, int i, nodeData item){
    Linklist t;
    t = *L;
    int j = 0;
    if(i<0){
        printf("wrong number.\n");
        return 1;
    }
    while(t && j < i){
        t = t->next;
        j++;
    }
    Linklist s = (Linklist)malloc(sizeof(nodeData));
    s->data.coef = item.coef;
    s->data.exp = item.exp;
    s->next = t->next; 
    t->next = s;
    return 0;
}

int creat_polyn(polynomial *p,char c){
    int exp = 1;
    nodeData temp;
    int i = 0,j;
    printf("请分别输入LP%c每一项的系数和指数，并用空格隔开\n",c);
    while(exp >= 0){
        printf("coef expn %d:",1+i++);
        scanf("%f %d",&temp.coef,&temp.exp);
        exp = temp.exp;
        j = locateItem(p,temp);
        if(temp.exp>0&&pot==0)
        insert_list(p,j,temp);
        pot = 0;
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
    nodeData sum;
    Linklist pa = (*p1)->next;
    Linklist pb = (*p2)->next;
    polynomial pc;
    init_poly(&pc);
    while ((pa != NULL) && (pb != NULL)) /*如果两个多项式多不为空就进行下列计算*/
    {
        if (pa->data.exp < pb->data.exp) /*如果a的指数小于b的指数*/
        {
            insert_list(&pc,i,pa->data); /*在线性表c中i的位置插入a的元素*/
            i++;
            pa = pa->next;               /*a指针指向a的下一个元素*/
			pos=1;
        }
        else if (pa->data.exp > pb->data.exp) /*如果a的指数大于b的指数*/
        {
            insert_list(&pc,i,pb->data);  /*在线性表c中i的位置插入b的元素*/
            i++;
            pb = pb->next;   /*b指针指向b的下一个元素*/
			pos=1;
        }
        else
        {
            sum.coef = pa->data.coef+pb->data.coef;   /*如果a、b的指数相等，则系数相加，指数不变*/
            sum.exp = pa->data.exp;
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
    display_list(&pa);
    printf("\n的多项式 LPB 是:\n");
    display_list(&pb);
    printf("\nLPA与LPB相加的结果 LPC 是:\n");
    display_list(&pc);
	if(pos==0)
		printf("0");
    return 0;
}

int main()
{
    polynomial poly1,poly2;
    init_poly(&poly1);
    init_poly(&poly2);
    creat_polyn(&poly1, 'A');
    creat_polyn(&poly2, 'B');
    add_polyn(&poly1,&poly2);
    
    printf("\n");
    return 0;
}
