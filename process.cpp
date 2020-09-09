#include "process.h"

map<string, int>::iterator iter;
ifstream input_process()
{
	ifstream infile;
	int mode = -1;
	cout << "Please select input mode : " << endl
		<< "Enter '1' : Enter from the command line.(input '$' to end) " << endl
		<< "Enter '2' : Enter from file." << endl;         //ѡ������ģʽ��1:������������Դ���룬2:���ļ�����Դ����

	(cin >> mode).get();

	if (mode == 1)
	{
		cout << "Please enter the source code to be analyzed : " << endl;
		char intemp;
		ofstream tempfile;
		tempfile.open("temp.txt", ios::ate | ios::out);        //������������Ĵ�����ʱ�洢��temp.txt�ļ��У�����ͳһ����
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
	cout << "\n�ʷ�����������" << endl;
	cout << "\n----------------------------------ͳ�ƽ��----------------------------------\n"
		<< "������� : " << statistics.print_row() << endl
		<< "�ַ����� : " << statistics.print_ch() << endl
		<< "������ : " << statistics.print_key() << endl
		<< "����� : " << statistics.print_op() << endl
		<< "��� : " << statistics.print_bound() << endl
		<< "��ʶ�� : " << statistics.print_id() << endl
		<< "���� : " << statistics.print_num() << endl;

	ofstream outfile;
	outfile.open("result.txt", ios::app | ios::out);
	if (!outfile.is_open())
	{
		cout << "Could not open the output file !" << endl;
		exit(2);
	}
	outfile << "\n----------------------------------ͳ�ƽ��----------------------------------\n"
		<< "\n������� : " << statistics.print_row() << endl
		<< "�ַ����� : " << statistics.print_ch() << endl
		<< "������ : " << statistics.print_key() << endl
		<< "����� : " << statistics.print_op() << endl
		<< "��� : " << statistics.print_bound() << endl
		<< "��ʶ�� : " << statistics.print_id() << endl
		<< "���� : " << statistics.print_num() << endl;
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

	cout << "\n----------------------------------ʶ����----------------------------------\n";
	cout << "�Ǻ�\t\t����" << endl;

	outfile << "---------------------------------ʶ����---------------------------------" << endl;
	outfile << "�Ǻ�\t\t����" << endl;

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

	cout << "\n\n----------------------------------" << "���ţ�������ձ�" << "----------------------------------\n" << endl;
	outfile << "\n\n----------------------------------" << "���ţ�������ձ�" << "----------------------------------\n" << endl;

	cout << "==================" << "������" << "==================" << endl;
	outfile << "==================" << "������" << "==================" << endl;
	cout << "�����ַ�\t\t������" << endl;
	outfile << "�����ַ�\t\t������" << endl;
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

	cout << "\n==================" << "�����" << "==================" << endl;
	outfile << "\n==================" << "�����" << "==================" << endl;
	cout << "�����\t\t������" << endl;
	outfile << "�����\t\t������" << endl;
	for (int i = 0; i < int(Operator.size()); i++)
	{
		cout << Operator[i] << "\t\t" << i + 50 << endl;
		outfile << Operator[i] << "\t\t" << i + 50 << endl;
	}

	cout << "\n==================" << "���" << "==================" << endl;
	outfile << "\n==================" << "���" << "==================" << endl;
	cout << "���\t\t������" << endl;
	outfile << "���\t\t������" << endl;
	for (int i = 0; i < int(Bound.size()); i++)
	{
		cout << Bound[i] << "\t\t" << i +100 << endl;
		outfile << Bound[i] << "\t\t" << i + 100 << endl;
	}

	cout << "\n==================" << "��ʶ��" << "==================" << endl;
	outfile << "\n==================" << "��ʶ��" << "==================" << endl;
	cout << "��ʶ��\t\t������\t\t����λ��" << endl;
	outfile << "��ʶ��\t\t������\t\t����λ��" << endl;
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

	cout << "\n==================" << "������" << "==================" << endl;
	cout << "����ֵ\t\t������\t\t����λ��" << endl;
	outfile << "\n==================" << "������" << "==================" << endl;
	outfile << "����ֵ\t\t������\t\t����λ��" << endl;
	for (iter = Number.begin(); iter != Number.end(); iter++)
	{
		cout << iter->first << "\t\t2\t\t" << iter->second << endl;
		outfile << iter->first << "\t\t2\t\t" << iter->second << endl;
	}
}
