#include<stdio.h>
int leapyear(int n)/*判断闰年*/
{
	if((n%4==0&&n/100!=0)||n%400==0)
	return 1;
	else return 0;
}

2348jafdfjdl;
开发第三;
127_dfas;

int getdays(int n,int m)/*求年月的天数*/
{
	switch(m)
	{
		case 1:case 3:case 5:case 7:case 8:case 10:case 12:
			return 31;break;
		case 4:case 6:case 9:case 11:
			return 30;break;
		default:
			{
				if(leapyear(n))
				return 29;
				else return 28;
			}
	}
}
 
