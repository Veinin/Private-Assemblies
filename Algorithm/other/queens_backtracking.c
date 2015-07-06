#include <stdio.h>
#include <stdlib.h>
  
#define Max 20      //定义棋盘的最大值  
int a[Max];  
int show(int S)    //定义输出函数  
{  
    int i,p,q;  
    int b[Max][Max]={0};     //定义并初始化b[][]输出数组  
  
    for(i=1;i<=S;i++)    //按横列i顺序输出a[i]数组坐标  
    {  
        b[i][a[i]]=1;  
        printf("(%d,%d)\t",i,a[i]);  
    }  
    printf("\n");  
    for(p=1;p<=S;p++)     //按棋盘的横列p顺序标明皇后的位置  
    {  
        for(q=1;q<=S;q++)  
        {  
            if(b[p][q]==1)     //在第p行第q列放置一个皇后棋子  
                printf("●");  
            else  
                printf("○");  
        }  
        printf("\n");  
    }  
    return 0;  
}  
  
int check(int k)    //定义check函数  
{  
    int i;  
    for(i=1;i<k;i++)    //将第k行与前面的第1~~k-1行进行判断  
    {  
        if((a[i]==a[k]) || (a[i]-a[k]==k-i) || (a[i]-a[k]==i-k))    //检查是否有多个皇后在同一条直线上  
        {  
            return 0;  
        }  
    }  
    return 1;  
}  
  
void check_m(int num)    //定义函数  
{  
    int k=1,count=0;  
    printf("The possible configuration of N queens are:\n");  
    a[k]=1;  
    while(k>0)  
    {  
        if(k<=num && a[k]<=num)    //从第k行第一列的位置开始，为后续棋子选择合适位子  
        {  
            if(check(k)==0)    //第k行的a[k]列不能放置皇后  
            {  
                a[k]++;        //继续探测当前行的下一列：a[k]+1  
            }  
            else  
            {  
                k++;         //第K行的位置已经确定了，继续寻找第k+1行皇后的位置  
                a[k]=1;      //从第一列开始查找  
            }  
        }  
        else  
        {  
            if(k>num)     //若满足输出数组的要求则输出该数组  
            {  
                count++;  
                printf("[%d]:  ",count);  
                show(num);    //调用输出函数show()  
            }  
            //如果k>num会执行下面两行代码，因为虽然找到了N皇后问题的一个解，但是要找的是所有解，需要回溯，从当前放置皇后的下一列继续探测  
            //如果a[k]>num也会执行下面两行代码，就是说在当前行没有找到可以放置皇后的位置，于是回溯，从上一行皇后位置的下一列继续探测  
            k--;      //棋子位置不符合要求，则退回前一步  
            a[k]++;   //继续试探下一列位置  
        }  
    }  
    printf("The count is: %d \n",count);  
}  
  
int main(void)  
{  
    int N,d;  
    //system("color 2a");  
    do  
    {  
        printf("********************N皇后问题系统*********************\n\n");  
        printf("                  1. 四皇后问题                        \n");  
        printf("                  2. 八皇后问题                        \n");  
        printf("                  3. N 皇后问题(N<20)                  \n");  
        printf("                  4. 退出                              \n");  
        printf("******************************************************\n");  
        printf("\n    从数字1-4之间的数选择需要的操作\n\n"); /*提示输入选项*/  
        printf("      请输入你要选择的功能选项:__\n");  
        scanf("%d",&d);   
        switch(d)  
        {  
        case 1:  
            check_m(4);      //4皇后问题  
            break;   
        case 2:  
            check_m(8);     //8皇后问题  
            break;   
        case 3:  
            printf("请输入N的值：_");  
            fflush(stdin);      //清除缓冲  
            scanf("%d",&N);  
            printf("\n");  
            if(N>0&&N<20)  
            {  
                check_m(N);    //N皇后问题  
                break;  
            }  
            else  
            {  
                printf("输入错误，请从新输入：");  
                printf("\n\n");  
                break;   
            }  
        case 4:  
            exit(0);     //程序结束  
        }  
    }while(1);  
    system("pause");  
    return 0;  
}  