#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#define STACK_INIT_SIZE 20
#define STACKINCREASEMENT 10
#define MAXBUFFER 10
typedef double ElemType;
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
    if (s->top - s->base >= s->stackSize)
    {
        s->base = (ElemType *)realloc(s->base, (s->stackSize + STACKINCREASEMENT) * sizeof(ElemType));
        if (!s->base)
            exit(0);
        s->top = s->base + s->stackSize + STACKINCREASEMENT;
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
    sqStack s;
    char c;
    double d, e;
    char str[MAXBUFFER];
    int i = 0;
    InitStack(&s);
    printf("请按照逆波兰表达式来进行计算，数据和运算符之间用空格隔开！\n");
    scanf("%c", &c);
    while (c != '#')
    {
        while (isdigit(c) || c == '.')
        {
            i = 0;
            str[i++] = c;
            if (i >= 10)
            {
                printf("出错，数据过大");
                return -1;
            }
            scanf("%c", &c);
        }
        if (c == ' ')
        {
            if(strlen(str) != 0){
                d = atof(str);
                Push(&s, d);
                int j;
                for (j = 0; j < strlen(str); j++)
                {
                    str[j] = '\0';
                }
            }
        }

        switch (c)
        {
        case '+':
            Pop(&s, &e);
            Pop(&s, &d);
            Push(&s, d + e);
            break;
        case '-':
            Pop(&s, &e);
            Pop(&s, &d);
            Push(&s, d - e);
            break;
        case '*':
            Pop(&s, &e);
            Pop(&s, &d);
            Push(&s, d * e);
            break;
        case '/':
            Pop(&s, &e);
            Pop(&s, &d);
            if (e != 0)
            {
                Push(&s, d / e);
            }
            else
            {
                printf("除数为0");
            }
            break;
        }
        scanf("%c", &c);
    }
    Pop(&s, &d);
    printf("\n %f", d);
    return 0;
}
