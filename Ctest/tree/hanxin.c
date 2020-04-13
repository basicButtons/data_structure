#include<stdio.h>
int main()
{
    int i;
    int result;
    for (i=0;;i++)
    {
        if((i*7+2)/3 == 2)
        {
            if((i*7+2)/5 == 3)
            {
                printf("%d",i*7+2);
                break;
            }
        }
    }
}