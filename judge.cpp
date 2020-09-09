#include "judge.h"

bool is_letter(char ch)  //�ж��Ƿ�Ϊ��ĸ������C��������'_'��Ϊ��ʶ����һ����
{
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || ch == '_')
		return true;
	else
		return false;
}

bool is_digit(char ch)  //�ж��Ƿ�Ϊ����
{
	if (ch >= '0' && ch <= '9')
		return true;
	else
		return false;
}

int is_keyword(string str)   //�ж��Ƿ�ΪC���Ա�����
{
	for (int i = 0; i < 32; i++)                //���������ֱ�ƥ���ַ���
	{
		if (strcmp(Keyword[i].c_str(), str.c_str()) == 0)
			return i + 10;                   //���Ǳ����֣��򷵻ر��������кţ�ʶ���룩
	}
	return -1;                     //������ʧ�ܣ��򷵻�-1���������Ǳ�����
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




