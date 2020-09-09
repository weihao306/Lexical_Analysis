#ifndef PROCESS_H_INCLUDED
#define PROCESS_H_INCLUDED

#include <iostream>
#include <fstream>
#include <map>
#include "judge.h"
#include "statistics.h"

extern char character;
extern int ptr;
extern string buffer;
extern string token;
extern int state;
extern map<string, int> Id;    //��ʶ����
extern map<string, int> Number;     //������

extern Statistics statistics;

typedef struct  t        //���ű�
{
	t(int c, int i, string v = "-")
	{
		category = c;
		index = i;
		value = v;
	}
	int category = 0;       //������
	int index = 0;          //����λ��
	string value = "-";             //����ֵ(��ʶ�����������������䱾�������������Ψһ)
} Table;

extern vector<Table> table;

using namespace std;

ifstream input_process();              //���봦��
void get_char();        //ÿ����һ�Σ���ǰָ��forward��buffer�ж�ȡһ���ַ����������ŵ�character�У�Ȼ���ƶ�forward��ָ����һ���ַ�
void get_nbc();         //ÿ�ε���ʱ���character�Ƿ�Ϊ�ո������򷴸�����get_char()��֪��character��һ���ǿ��ַ�δ֪
void retract();         //��ǰָ�����һ���ַ�

string insert_id();        //���ұ�ʶ�����������
string insert_num();            //���ҳ������������

void show_result();          //���ʶ����
void show_table();           //����Ǻű�
void show_stat();       //���ͳ�ƽ��

#endif // PROCESS_H_INCLUDED


