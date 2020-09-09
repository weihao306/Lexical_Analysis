#ifndef JUDGE_H
#define JUDGE_H

#include <string>
#include <cstring>
#include <vector>

using namespace std;

extern const vector<string> Keyword;
extern const vector<string> Operator;
extern const vector<char> Bound;

bool is_letter(char ch);  //判断是否为字母

bool is_digit(char ch);   //判断是否为数字

int is_keyword(string str);  //判断是否是Ｃ语言保留字

bool is_operator(char ch);   //判断是否为运算符

bool is_bound(char ch);      //判断是否为界符

int get_op(string str);
int get_op(char ch);          //获得运算符类别编码

int get_bound(string str);      //获得界符类别编码

#endif // JUDGE_H
