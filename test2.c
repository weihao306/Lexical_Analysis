//设f(x)=1-x^2
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

double Darts(int n)
{
    double x,y;
    time_t t;
    int i,count=0;
    srand((unsigned)time(&t));
    for(i=0;i<n;i++)
    {
        x=rand()%100/100.0;
        y=rand()%100/100.0;
        if(y<=1-pow(x,2))
            count++;
    }
    return (double)count/(double)n;
}

int main(void)
{
    int n;
    printf("Please input the accuracy\n");
    scanf("%d",&n);
    printf("The result is about\n");
    printf("%f\n",Darts(n));
    return 0;
}
 
