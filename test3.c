/*创建一个静态的顺序表存放整数，大小为10，完成以下操作:
1)输入6个整数，打印出顺序表中的内容，并显示表中剩余空间个数
2)在顺序表中的第3个位置插入元素0，打印出顺序表中的内容，并显示表中剩余的空间个数
3)再试图插入表中第11个位置元素0，程序提示超出范围
4)删除表中第6个元素，打印表中内容，并显示表中剩余空间个数
*/

#include<stdio.h>
#define MaxSize 10
//静态顺序表的各种操作

//向顺序表中插入元素
//参数Sqlist:表首地址
//参数*len:表的长度
//参数i:插入元素的位置
//参数x:待插入的元素值
void insertElem(int Sqlist[],int *len,int i,int x)
{
    int t;
    if(*len==MaxSize||i<1||i>*len+1)
    {
        printf("This insert is illegal\n");
        return;
    }              //非法插入
    for (t = *len - 1; t >= i - 1; t--)
        Sqlist[t+1]=Sqlist[t];
    Sqlist[i - 1] = x;                    //插入元素
    *len = *len + 1;                      //表长加1
}

//向顺序表中删除元素
//参数Sqlist:表首地址
//参数*len:表的长度
//参数i:插入元素的位置
void DelElem(int Sqlist[],int *len,int i)
{
    int j;
    if(i<1||i>*len)
    {
        printf("This insert is illegal");
        return;
    }                    //非法插入
    for (j = i; j < *len - 1; j++)
        Sqlist[j - 1] = Sqlist[j];        //将第i个元素之后的元素前移
    *len = *len - 1;                      //表长减1
}

//测试函数
int main(void)
{
    int Sqlist[MaxSize];          //定义一个静态顺序表
    int len;
    int i;
    for (i = 0; i < 6;i++)
        scanf("%d", &Sqlist[i]);         //输入6个整数
    len = 6;
    for (i = 0; i < len;i++)
        printf("%d ", Sqlist[i]);         //输入表中6个整数
    printf("\nThe spare length is %d\n", MaxSize - len);         
    insertElem(Sqlist, &len, 3, 0);      //在顺序表中的第3个位置插入元素0
    for (i = 0; i < len;i++)
        printf("%d ", Sqlist[i]);        //输出顺序表中的所有元素
    printf("\nThe spare length is %d\n", MaxSize - len);
    insertElem(Sqlist, &len, 11, 0);     //在表中第11位置插入整数0
    DelElem(Sqlist, &len, 6);            //删除顺序表中的第6个元素
    for (i = 0; i < len;i++)
        printf("%d ",Sqlist[i]);
    printf("\nThe spare length is %d\n",MaxSize-len);

    return 0;
}
 
