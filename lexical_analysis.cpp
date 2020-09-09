#include <algorithm>

#include "judge.h"
#include "statistics.h"
#include "process.h"

using namespace std;

map<string, int> Id;    //标识符集
map<string, int> Number;     //常数集

const vector<string> Keyword = { "auto", "break", "case", "char", "const", "continue",
								"default", "do", "double", "else", "enum", "extern",
								"float", "for", "goto", "if", "int", "long",
								"register", "return", "short", "signed", "sizeof", "static",
								"struct", "switch", "typedef", "union", "unsigned", "void",
								"volatile", "while"
};   //C语言保留字[32]

const vector<string> Operator = { "+", "-", "*", "/", "%", "++", "--", //算术运算符[7]
								 "<", "<=", ">", ">=", "!=", "==",  //关系运算符[6]
								 "&&", "||", "!",      //逻辑运算符[3]
								 "&", "|", "^", "~", "<<", ">>",    //位运算符[6]
								 "=", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=",  //赋值运算符[9]
								 ".", "->"//    其他运算符[2]
};  //运算符[33]

const vector<char> Bound = { '(', ')', '{', '}', '[', ']',
							';', ',', ':', '\?', '\"', '\'', '#','\\'
};     //分界符[14]

int state = 0;   //当前状态
string buffer = "";   //输入缓冲区
char character;      //当前读到的字符
string token;       //字符数组，存放当前正在识别的单词字符串
int ptr;        //字符指针，指向当前读取的字符

/*所有合法的符合(串)分为５类：标识符，常数，保留字，运算符，界符
 * 注释标记"//","/ *"，词法分析不需要处理这些(指内容被直接忽略)
 * 约定:　　(类别编码唯一)
 * 标识符类别编码为１，
 * 常数类别编码为２，
 * 保留字类别编码为i+10,其中i为Keyword序列中保留字对应的下标，如"auto"的类别编码为10，直到"while"的类别编码为41
 * 运算符类别编码为i+50，其中i为Operator序列中运算符对应的下标，如"+"的类别编码为50等等
 * 界符类别编码为i+100，其中i为Bound序列中界符对应的下标，如"("的类别编码为100，以此类推
 */

vector<Table> table;        //存储所有识别到的合法符号(串)
Statistics statistics;

int main(void)
{
	Id.clear();
	Number.clear();
	character = ' ';          //进行必要的初始化

	ifstream infile;
	infile = input_process();
	cout << "Analysis start" << endl;
	ofstream outfile;
	outfile.open("result.txt", ios::out);

	while (getline(infile, buffer))    //从文件按行读入缓冲区
	{
		statistics.count_row();         //行数+1
		int category = -1;      //类别编码
		ptr = 0;
		token = "";
		string value;
		//cout << buffer << endl;
		if (buffer.length() == 0)		//空行不进行分析
			continue;
		else
		{
			while (buffer[ptr] != '\0')
			{
				get_char();
				//cout << character << endl;
				get_nbc();
				if (character == '\0')
					break;

				/*===============标识符识别=================*/

				if (is_letter(character) && state == 0) //开头为字母
				{
					state = 1;
					token += character;           //收集
					statistics.count_ch();          //字符总数+1,每收集一个token字符就重复此步骤
					get_char();
					while (is_letter(character) || is_digit(character)) //后跟字母或数字
					{
						token += character;    //收集
						statistics.count_ch();
						get_char();
					}
					retract();

					category = is_keyword(token); //判断token是否为保留字
					if (category != -1)          //如果是保留字
					{
						table.push_back(Table(category, 0));
						statistics.count_key();
					}
					else
					{
						value = insert_id();
						table.push_back(Table(1, Id[value], value)); //将识别到的标识符添加到table中
						statistics.count_id();
					}

					state = 0;      //标识符识别完成，复位状态
					token = "";
				}

				/*==================无符号数识别===================*/

				else if (is_digit(character) && state == 0) //开头为数字
				{
					state = 2;
					token += character;
					statistics.count_ch();
					get_char();
					while (is_digit(character))      //继续读入数字
					{
						token += character;
						statistics.count_ch();
						get_char();
					}
					retract();
				}
				else if (character == '.' && state == 2)            //已经读入数字又读到小数点
				{
					state = 3;
					token += character;           //将小数点加入token
					statistics.count_ch();
				}
				else if (is_digit(character) && state == 3)
				{
					state = 4;
					while (is_digit(character))      //此时token中应是xx.的形式，若接下读到数字
					{
						token += character;
						statistics.count_ch();
						get_char();
					}
					retract();
				}
				else if (state == 2 || state == 4) //已经识别到整数/小数，判断之后是否为数字结束的标志，如果后面是字母，则是错误
				{
					if (is_bound(character) || is_operator(character) || character == ' ')
					{
						statistics.count_num();
						value = insert_num();
						table.push_back(Table(2, Number[value], value));
						retract();      //回退
					}
					else
					{
						while (!(is_bound(character) || is_operator(character) || character == ' '))
						{
							statistics.count_ch();
							token += character;
							get_char();
						}
						retract();
						cout << "Error (line " << statistics.print_row() << ") : there is a illegal string " << "\"" << token << "\"" << endl;
						outfile << "Error (line " << statistics.print_row() << ") : there is a illegal string " << "\"" << token << "\"" << endl;
					}
					token = "";
					state = 0;
				}

				/*==================注释处理=====================*/

				else if (character == '/')		//注释可以在任何状态下出现，故不必判断状态
				{
					get_char();
					if (character == '/')			//识别到"//"，进入单行注释
						break;				//直接忽略这一行之后的所有内容
					else if (character == '*')			//识别到"/*"，进入多行注释
						state = 5;		//状态转移
					else
						retract();			//未识别到注释标志，回退指针
				}
				else if (state == 5)
				{
					if (character == '*')		//在注释状态(state=5)时，读到'*'
					{
						get_char();			//超前扫描
						if (character == '/')		//识别到"*/"，注释结束
							state = 0;
						else
							retract();
					}
				}

				/*=================运算符识别==================*/

				else if (is_operator(character) && state == 0) //识别到运算符
				{
					state = 6;
					token += character;
					statistics.count_ch();
					char chtemp = character;
					switch (chtemp)    //判断是否是二目运算符
					{
					case '+':
						get_char();
						if (character == '+' || character == '=')    //识别到"++"||"+="
						{
							token += character;
							statistics.count_ch();
							category = get_op(token);
							get_char();
						}
						else
							category = get_op(chtemp);
						retract();
						statistics.count_op();
						table.push_back(Table(category, 0));
						token = "";
						state = 0;
						break;

					case '-':
						get_char();
						if (character == '-' || character == '=' || character == '>') //识别到"--"||"-="||"->"
						{
							token += character;
							statistics.count_ch();
							category = get_op(token);
							get_char();
						}
						else
							category = get_op(chtemp);
						retract();
						statistics.count_op();
						table.push_back(Table(category, 0));
						token = "";
						state = 0;
						break;

					case '*':
						get_char();
						if (character == '=')        //识别到"*="
						{
							token += character;
							statistics.count_ch();
							category = get_op(token);
							get_char();
						}
						else
							category = get_op(chtemp);
						retract();
						statistics.count_op();
						table.push_back(Table(category, 0));
						token = "";
						state = 0;
						break;

					case '/':
						get_char();
						if (character == '=')        //识别到"/="
						{
							token += character;
							statistics.count_ch();
							category = get_op(token);
							get_char();
						}
						else
							category = get_op(chtemp);
						retract();
						statistics.count_op();
						table.push_back(Table(category, 0));
						token = "";
						state = 0;
						break;

					case '%':
						get_char();
						if (character == '=')        //识别到"%="
						{
							token += character;
							statistics.count_ch();
							category = get_op(token);
							get_char();
						}
						else
							category = get_op(chtemp);
						retract();
						statistics.count_op();
						table.push_back(Table(category, 0));
						token = "";
						state = 0;
						break;

					case '<':
						get_char();
						if (character == '=' || character == '<') //识别到"<="||"<<"
						{
							token += character;
							statistics.count_ch();
							category = get_op(token);
							get_char();
						}
						else
							category = get_op(chtemp);
						retract();
						statistics.count_op();
						table.push_back(Table(category, 0));
						token = "";
						state = 0;
						break;

					case '>':
						get_char();
						if (character == '=' || character == '>') //识别到">="||">>"
						{
							token += character;
							statistics.count_ch();
							category = get_op(token);
							get_char();
						}
						else
							category = get_op(chtemp);
						retract();
						statistics.count_op();
						table.push_back(Table(category, 0));
						token = "";
						state = 0;
						break;

					case '!':
						get_char();
						if (character == '=') //识别到"!="
						{
							token += character;
							statistics.count_ch();
							category = get_op(token);
							get_char();
						}
						else
							category = get_op(chtemp);
						retract();
						statistics.count_op();
						table.push_back(Table(category, 0));
						token = "";
						state = 0;
						break;

					case '=':
						get_char();
						if (character == '=') //识别到"=="
						{
							token += character;
							statistics.count_ch();
							category = get_op(token);
							get_char();
						}
						else
							category = get_op(chtemp);
						retract();
						statistics.count_op();
						table.push_back(Table(category, 0));
						token = "";
						state = 0;
						break;

					case '&':
						get_char();
						if (character == '&' || character == '=') //识别到"&&"||"&="
						{
							token += character;
							statistics.count_ch();
							category = get_op(token);
							get_char();
						}
						else
							category = get_op(chtemp);
						retract();
						statistics.count_op();
						table.push_back(Table(category, 0));
						token = "";
						state = 0;
						break;

					case '|':
						get_char();
						if (character == '|' || character == '=') //识别到"||"||"|="
						{
							token += character;
							statistics.count_ch();
							category = get_op(token);
							get_char();
						}
						else
							category = get_op(chtemp);
						retract();
						statistics.count_op();
						table.push_back(Table(category, 0));
						token = "";
						state = 0;
						break;

					case '^':
						get_char();
						if (character == '=') //识别到"^="
						{
							token += character;
							statistics.count_ch();
							category = get_op(token);
							get_char();
						}
						else
							category = get_op(chtemp);
						retract();
						statistics.count_op();
						table.push_back(Table(category, 0));
						token = "";
						state = 0;
						break;

					case '~':
						category = get_op(chtemp);
						statistics.count_op();
						table.push_back(Table(category, 0));
						token = "";
						break;

					case '.':
						category = get_op(chtemp);
						statistics.count_op();
						table.push_back(Table(category, 0));
						token = "";
						state = 0;
						break;

					default:
						break;
					}
				}

				/*==================界符识别==================*/

				else if (is_bound(character) && state == 0)
				{
					token += character;
					statistics.count_ch();
					statistics.count_bound();
					category = get_bound(token);
					table.push_back(Table(category, 0));
					token = "";
					state = 0;
				}
				/*==================错误处理(无法识别的符号)===================*/

				else if (character != '\t' && character != '\0')
				{
					token += character;
					statistics.count_ch();
					cout << "Error (line " << statistics.print_row() << ") : there is a unrecognizable character. " << "\"" << token << "\"" << endl;
					token = "";
					state = 0;
				}
			}
		}
	}
	outfile.close();

	show_stat();		//显示文本信息统计结果
	show_result();   //显示识别结果，同时输出到文件
	show_table();    //显示符号－编码对照表

	return 0;
}
