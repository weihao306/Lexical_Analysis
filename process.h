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
extern map<string, int> Id;    //标识符集
extern map<string, int> Number;     //常数集

extern Statistics statistics;

typedef struct  t        //符号表
{
	t(int c, int i, string v = "-")
	{
		category = c;
		index = i;
		value = v;
	}
	int category = 0;       //类别编码
	int index = 0;          //表中位置
	string value = "-";             //属性值(标识符，常数的属性是其本身，其他三类符号唯一)
} Table;

extern vector<Table> table;

using namespace std;

ifstream input_process();              //输入处理
void get_char();        //每调用一次，向前指针forward从buffer中读取一个字符，并把它放到character中，然后移动forward，指向下一个字符
void get_nbc();         //每次调用时检查character是否为空格，若是则反复调用get_char()，知道character是一个非空字符未知
void retract();         //向前指针后退一个字符

string insert_id();        //查找标识符表，添加新项
string insert_num();            //查找常数表，添加新项

void show_result();          //输出识别结果
void show_table();           //输出记号表
void show_stat();       //输出统计结果

#endif // PROCESS_H_INCLUDED


