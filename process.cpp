#include "process.h"

map<string, int>::iterator iter;
ifstream input_process()
{
	ifstream infile;
	int mode = -1;
	cout << "Please select input mode : " << endl
		<< "Enter '1' : Enter from the command line.(input '$' to end) " << endl
		<< "Enter '2' : Enter from file." << endl;         //选择输入模式，1:从命令行输入源代码，2:从文件导入源代码

	(cin >> mode).get();

	if (mode == 1)
	{
		cout << "Please enter the source code to be analyzed : " << endl;
		char intemp;
		ofstream tempfile;
		tempfile.open("temp.txt", ios::ate | ios::out);        //将命令行输入的代码暂时存储在temp.txt文件中，方便统一处理
		if (!tempfile.is_open())
		{
			cout << "Could not open the temp file !" << endl;
			exit(0);
		}
		intemp = cin.get();
		while (intemp != '$')
		{
			tempfile << intemp;
			intemp = cin.get();
		}
		tempfile.close();
		infile.open("temp.txt");
	}
	else if (mode == 2)
	{
		cout << "Please enter the source file path to be analyzed : " << endl;
		string filename;
		cin >> filename;
		infile.open(filename);
	}
	else
	{
		cout << "Select mode error, program will exit" << endl;
		exit(1);
	}

	if (!infile.is_open())
	{
		cout << "Could not open the input file !" << endl;
		exit(0);
	}

	return infile;
}

void get_char()
{
	character = buffer[ptr++];
}

void get_nbc()
{
	while (character == ' ')
		get_char();
}

void retract()
{
	character = ' ';
	ptr--;
}

string insert_id()
{
	iter = Id.find(token);
	if (iter != Id.end())
		return iter->first;
	else
	{
		Id[token] = Id.size();
		return token;
	}
}

string insert_num()
{
	iter = Number.find(token);
	if (iter != Number.end())
		return iter->first;
	else
	{
		Number[token] = Number.size();
		return token;
	}
}

void show_stat()
{
	cout << "\n词法分析结束！" << endl;
	cout << "\n----------------------------------统计结果----------------------------------\n"
		<< "语句行数 : " << statistics.print_row() << endl
		<< "字符总数 : " << statistics.print_ch() << endl
		<< "保留字 : " << statistics.print_key() << endl
		<< "运算符 : " << statistics.print_op() << endl
		<< "界符 : " << statistics.print_bound() << endl
		<< "标识符 : " << statistics.print_id() << endl
		<< "常数 : " << statistics.print_num() << endl;

	ofstream outfile;
	outfile.open("result.txt", ios::app | ios::out);
	if (!outfile.is_open())
	{
		cout << "Could not open the output file !" << endl;
		exit(2);
	}
	outfile << "\n----------------------------------统计结果----------------------------------\n"
		<< "\n语句行数 : " << statistics.print_row() << endl
		<< "字符总数 : " << statistics.print_ch() << endl
		<< "保留字 : " << statistics.print_key() << endl
		<< "运算符 : " << statistics.print_op() << endl
		<< "界符 : " << statistics.print_bound() << endl
		<< "标识符 : " << statistics.print_id() << endl
		<< "常数 : " << statistics.print_num() << endl;
}


void show_result()
{
	ofstream outfile;
	outfile.open("result.txt", ios::app | ios::out);
	if (!outfile.is_open())
	{
		cout << "Could not open the output file !" << endl;
		exit(2);
	}

	cout << "\n----------------------------------识别结果----------------------------------\n";
	cout << "记号\t\t属性" << endl;

	outfile << "---------------------------------识别结果---------------------------------" << endl;
	outfile << "记号\t\t属性" << endl;

	for (int i = 0; i < int(table.size()); i++)
	{
		cout << table[i].category << "\t\t" << table[i].value << endl;
		outfile << table[i].category << "\t\t" << table[i].value << endl;
	}

	outfile.close();
}

void show_table()
{
	ofstream outfile;
	outfile.open("result.txt", ios::app | ios::out);
	if (!outfile.is_open())
	{
		cout << "Could not open the output file !" << endl;
		exit(2);
	}

	cout << "\n\n----------------------------------" << "符号－编码对照表" << "----------------------------------\n" << endl;
	outfile << "\n\n----------------------------------" << "符号－编码对照表" << "----------------------------------\n" << endl;

	cout << "==================" << "保留字" << "==================" << endl;
	outfile << "==================" << "保留字" << "==================" << endl;
	cout << "保留字符\t\t类别编码" << endl;
	outfile << "保留字符\t\t类别编码" << endl;
	for (int i = 0; i < int(Keyword.size()); i++)
	{
		if (Keyword[i].size() >= 8)
		{
			cout << Keyword[i] << "\t" << i + 10 << endl;
			outfile << Keyword[i] << "\t" << i + 10 << endl;
		}
		else
		{
			cout << Keyword[i] << "\t\t" << i + 10 << endl;
			outfile << Keyword[i] << "\t\t" << i + 10 << endl;
		}
	}

	cout << "\n==================" << "运算符" << "==================" << endl;
	outfile << "\n==================" << "运算符" << "==================" << endl;
	cout << "运算符\t\t类别编码" << endl;
	outfile << "运算符\t\t类别编码" << endl;
	for (int i = 0; i < int(Operator.size()); i++)
	{
		cout << Operator[i] << "\t\t" << i + 50 << endl;
		outfile << Operator[i] << "\t\t" << i + 50 << endl;
	}

	cout << "\n==================" << "界符" << "==================" << endl;
	outfile << "\n==================" << "界符" << "==================" << endl;
	cout << "界符\t\t类别编码" << endl;
	outfile << "界符\t\t类别编码" << endl;
	for (int i = 0; i < int(Bound.size()); i++)
	{
		cout << Bound[i] << "\t\t" << i +100 << endl;
		outfile << Bound[i] << "\t\t" << i + 100 << endl;
	}

	cout << "\n==================" << "标识符" << "==================" << endl;
	outfile << "\n==================" << "标识符" << "==================" << endl;
	cout << "标识符\t\t类别编码\t\t表中位置" << endl;
	outfile << "标识符\t\t类别编码\t\t表中位置" << endl;
	for (iter = Id.begin(); iter != Id.end(); iter++)
	{
		if (iter->first.size() >= 8)
		{
			cout << iter->first << "\t1\t\t" << iter->second << endl;
			outfile << iter->first << "\t1\t\t" << iter->second << endl;
		}
		else
		{
			cout << iter->first << "\t\t1\t\t" << iter->second << endl;
			outfile << iter->first << "\t\t1\t\t" << iter->second << endl;
		}
	}

	cout << "\n==================" << "常数表" << "==================" << endl;
	cout << "常量值\t\t类别编码\t\t表中位置" << endl;
	outfile << "\n==================" << "常数表" << "==================" << endl;
	outfile << "常量值\t\t类别编码\t\t表中位置" << endl;
	for (iter = Number.begin(); iter != Number.end(); iter++)
	{
		cout << iter->first << "\t\t2\t\t" << iter->second << endl;
		outfile << iter->first << "\t\t2\t\t" << iter->second << endl;
	}
}
