#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STACK_INIT_SIZE 20
#define STACKINCREASEMENT 10

typedef char ElemType;
typedef struct
{
    ElemType *base;
    ElemType *top;
    int stackSize;
}sqStack;

void InitStack(sqStack *s){
    s->base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
    if(!s->base){
        exit(0);    
    }
    s->top = s->base;
    s->stackSize = STACK_INIT_SIZE; 
}

void Push(sqStack *s, ElemType e){
    if(s->top - s->base >= STACKINCREASEMENT){
        s->base = (ElemType *)realloc(s->base,(s->stackSize+STACKINCREASEMENT)*sizeof(ElemType));
        if(!s->base){
            exit(0);
        }
    }
    *(s->top) = e;
    s->top++;
} 

void Pop(sqStack *s, ElemType *e){
    if(s->top == s->base){
        return;
    }
    *e = *--(s->top);
}

int StackLen(sqStack s){
    return(s.top - s.base);
}
//如果我要对数据进行修改那么我就传入他的指针，如果我们不需要对其进行修改那么我就直接传入这个数据结构

int main(){
    ElemType c;
    sqStack s;
    InitStack(&s);
    printf("请输入一个后缀表达式,中间使用空格隔开，后面使用#结束。");
    scanf("%c",&c);
    while(c!='#')
    {
        
    }
    return 0;
}
