#ifndef headfile_h
#define headfile_h

#include<iostream>
#include<stack>
#include<cmath>
#include<iomanip>
#include<algorithm>
#include<cstdio>
#include<string>
#include<cstring> 
#include<stack>
#include <cstdlib> 
#include<windows.h>

using namespace std;

static string input_exp,after_pre,RPN;//输入的表达式，预处理表达式，逆波兰表达式

static stack<char> _operator; //用于存放计算符的栈
static stack<double>cul;//声明一个用于计算的栈

int precedence(char _operator);//判断运算符优先级
double calculate(double former, char _operator, double latter);//计算每一项
int judge_mod(int former, char _operator, int latter);//计算取余

void preprocess(string expression);//预处理输入的表达式
bool judge();//判断表达式输入是否合法
void toRPN();//将处理好的表达式转化为逆波兰表达式
double calculate();//用逆波兰表达式计算结果
void print_stack(stack<char> temp);//输出转逆波兰时栈的变化
void print_stack(stack<double> temp);//输出计算时栈的变化

#endif // !headfile_h
