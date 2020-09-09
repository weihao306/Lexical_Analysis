#ifndef STATISTICS_H
#define STATISTICS_H

class Statistics
{
private:
	int ch;         //�ַ�����(ֻͳ�Ʒǿ�����������ַ�)
	int row;        //����
	int id, num, key, op, bound;    //���൥�ʵĸ���
public:
	Statistics()     //���캯��
	{
		ch = row = id = num = key = op = bound = 0;
	}
	~Statistics() {}    //��������
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


