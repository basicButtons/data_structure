#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define STACK_INIT_SIZE 20
#define STACKINCREASEMENT 10

typedef char ElemType;
typedef struct
{
    ElemType *base;
    ElemType *top;
    int stackSize;
} sqStack;

void InitStack(sqStack *s)
{
    s->base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
    if (!s->base)
    {
        exit(0);
    }
    s->top = s->base;
    s->stackSize = STACK_INIT_SIZE;
}

void Push(sqStack *s, ElemType e)
{
    if (s->top - s->base >= STACKINCREASEMENT)
    {
        s->base = (ElemType *)realloc(s->base, (s->stackSize + STACKINCREASEMENT) * sizeof(ElemType));
        if (!s->base)
        {
            exit(0);
        }
    }
    *(s->top) = e;
    s->top++;
}

void Pop(sqStack *s, ElemType *e)
{
    if (s->top == s->base)
    {
        return;
    }
    *e = *--(s->top);
}

int StackLen(sqStack s)
{
    return (s.top - s.base);
}
//如果我要对数据进行修改那么我就传入他的指针，如果我们不需要对其进行修改那么我就直接传入这个数据结构

int main()
{
    ElemType c, e;
    sqStack s;
    InitStack(&s);
    printf("请输入一个中缀表达式");
    scanf("%c", &c);
    while (c != '#')
    {
        while (isdigit(c))
        {
            printf("%c", c);
            scanf("%c", &c);
        }
        if (')' == c)
        {
            while ('(' != c)
            {
                printf("%c", c);
                Pop(&s, &e);
            }
        }
        else if (' ' == c)
        {

        }
        else if ('+' == c || '-' == c)
        {
            if (!StackLen(s))
            {
                Push(&s, c);
            }
            else
            {
                do
                {
                    Pop(&s, &e);
                    if ('(' == c)
                    {
                        Push(&s, e);
                    }
                    else
                    {
                        printf("%c", e);
                    }
                } while (!StackLen(s) && '(' != e);
                Push(&s, c);
            }
        }
        else if ('*' == c || '/' == c || '(' == c)
        {
            Push(&s, c);
        }
        else if('#'==c)
        {
            break;
        }
        else
        {
            printf("%d", c);
            printf("\n出错，请输入正确的格式。\n");
            break;
        }
        scanf("%c", &c);
    }

    while (StackLen(s))
    {
        Pop(&s, &e);
        printf("%c",e);
    }
}
