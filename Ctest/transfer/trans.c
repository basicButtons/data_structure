#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STACK_INIT_SIZE 20
#define STACKINCREMENT 10

typedef char ElemType;
typedef struct{
     ElemType *base;
     ElemType *top;
     int stackSize;
}sqStack;

void InitStack(sqStack *s){
    s->base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
    if( !s->base )
    {
        exit(0);
    }

    s->top = s->base;
    s->stackSize = STACK_INIT_SIZE;
};

void Push(sqStack *s, ElemType e){
    *(s->top) = e;
    s->top++;
}