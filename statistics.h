#ifndef STATISTICS_H
#define STATISTICS_H

class Statistics
{
private:
	int ch;         //字符总数(只统计非空且有意义的字符)
	int row;        //行数
	int id, num, key, op, bound;    //各类单词的个数
public:
	Statistics()     //构造函数
	{
		ch = row = id = num = key = op = bound = 0;
	}
	~Statistics() {}    //析构函数
	void count_row()
	{
		row++;
	}
	void count_ch()
	{
		ch++;
	}
	void count_id()
	{
		id++;
	}
	void count_num()
	{
		num++;
	}
	void count_key()
	{
		key++;
	}
	void count_op()
	{
		op++;
	}
	void count_bound()
	{
		bound++;
	}

	int print_row()
	{
		return row;
	}
	int print_ch()
	{
		return ch;
	}
	int print_id()
	{
		return id;
	}
	int print_num()
	{
		return num;
	} int print_key()
	{
		return key;
	}
	int print_op()
	{
		return op;
	}
	int print_bound()
	{
		return bound;
	}
};

#endif // STATISTICS_H


