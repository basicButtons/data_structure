#include <stdio.h>

int count = 0;
// row 表示起始行
// n 表示列数
// (*chess)[8]表示指向棋盘每一行的指针。

int notDanger(int row,int j,int (*chess)[8])
{
    int i,k, flag1 = 0,flag2 = 0,flag3 = 0,flag4 = 0,flag5 = 0;
    for(i=0;i<8;i++)
    {
        if(*(*(chess+i)+j)!=0)
        {
            flag1 = 1;
            break;
        }
    }
    //左上方
    for(i=row,k=j;i>=0 && k>=0;i--,k--)
    {
        if(*(*(chess+i)+k)!=0)
        {
            flag2 = 1;
            break;
        }
    } 
    //右下方
    for(i=row,k=j;i<8 && k<8;i++,k++)
    {
        if(*(*(chess+i)+k)!=0)
        {
            flag3 = 1;
            break;
        }
    }
    //左下方
    for(i=row,k=j;i<8 && k>=0;i++,k--)
    {
        if(*(*(chess+i)+k)!=0)
        {
            flag4 = 1;
            break;
        }
    }
    //右上方
    for(i=row,k=j;i>=0 && k<8;i++,k--)
    {
        if(*(*(chess+i)+k)!=0)
        {
            flag5 = 1;
            break;
        }
    }
    if(flag1||flag2||flag3||flag4||flag5)
    {
        return 0;
    }
    else
    {
        return 1;
    }
    
}

void eightQueen(int row, int n, int (*chess)[8])
{
    int chess2[8][8],i,j;

    for(i=0;i<8;i++)
        for(j=0;j<8;j++) chess2[i][j] = chess[i][j];
    if(8==row)
    {
        printf("第%d种",count+1);
        for(i=0;j<8;i++)
        {
            for(j=0;j<8;j++)
            {
                printf("%d",*(*(chess2+i)+j));
            }
            printf("\n");
        }
        printf("\n");
        count++;
    }
    else
    {
        //判断这个位置是否有危险
        if(notDanger(row,j,chess))
        {
            for(i=0;i<8;i++)
            {
                *(*(chess2+row)) = 0;
            }
            *(*(chess2+row)+j) = 1;
            eightQueen(row+1, n, chess2);
        }
    }
}

int main()
{
    int chess[8][8], i, j;
    for(i = 0; i < 8; i++) 
        for (j = 0; j < 8; j++) chess[i][j] = 0;
    eightQueen(0,8,chess);
    printf("总共有%种解决办法！\n\")
    return 0;
}
