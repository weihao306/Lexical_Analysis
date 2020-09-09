#ifndef JUDGE_H
#define JUDGE_H

#include <string>
#include <cstring>
#include <vector>

using namespace std;

extern const vector<string> Keyword;
extern const vector<string> Operator;
extern const vector<char> Bound;

bool is_letter(char ch);  //�ж��Ƿ�Ϊ��ĸ

bool is_digit(char ch);   //�ж��Ƿ�Ϊ����

int is_keyword(string str);  //�ж��Ƿ��ǣ����Ա�����

bool is_operator(char ch);   //�ж��Ƿ�Ϊ�����

bool is_bound(char ch);      //�ж��Ƿ�Ϊ���

int get_op(string str);
int get_op(char ch);          //��������������

int get_bound(string str);      //��ý��������

#endif // JUDGE_H
