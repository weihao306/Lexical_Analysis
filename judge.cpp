#include "judge.h"

bool is_letter(char ch)  //判断是否为字母，另外C语言允许'_'作为标识符的一部分
{
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || ch == '_')
		return true;
	else
		return false;
}

bool is_digit(char ch)  //判断是否为数字
{
	if (ch >= '0' && ch <= '9')
		return true;
	else
		return false;
}

int is_keyword(string str)   //判断是否为C语言保留字
{
	for (int i = 0; i < 32; i++)                //遍历保留字表，匹配字符串
	{
		if (strcmp(Keyword[i].c_str(), str.c_str()) == 0)
			return i + 10;                   //若是保留字，则返回保留字序列号（识别码）
	}
	return -1;                     //若查找失败，则返回-1，表明不是保留字
}

bool is_operator(char ch)
{
	for (int i = 0; i < int(Operator.size()); i++)
	{
		if (Operator[i][0] == ch)
			return true;
	}
	return false;
}

bool is_bound(char ch)
{
	for (int i = 0; i < int(Bound.size()); i++)
	{
		if (Bound[i] == ch)
			return true;
	}
	return false;
}


int get_op(string str)
{
	for (int i = 0; i < int(Operator.size()); i++)
	{
		if (strcmp(Operator[i].c_str(), str.c_str())==0)
			return i + 50;
	}
	return -1;
}

int get_op(char ch)
{
	for (int i = 0; i < int(Operator.size()); i++)
	{
		if (Operator[i][0] == ch)
			return i + 50;
	}
	return -1;
}

int get_bound(string str)
{
	for (int i = 0; i < int(Bound.size()); i++)
	{
		if (Bound[i] == str[0])
			return i + 100;
	}
	return -1;
}




