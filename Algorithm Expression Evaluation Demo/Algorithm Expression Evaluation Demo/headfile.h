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

static string input_exp,after_pre,RPN;//����ı��ʽ��Ԥ������ʽ���沨�����ʽ

static stack<char> _operator; //���ڴ�ż������ջ
static stack<double>cul;//����һ�����ڼ����ջ

int precedence(char _operator);//�ж���������ȼ�
double calculate(double former, char _operator, double latter);//����ÿһ��
int judge_mod(int former, char _operator, int latter);//����ȡ��

void preprocess(string expression);//Ԥ��������ı��ʽ
bool judge();//�жϱ��ʽ�����Ƿ�Ϸ�
void toRPN();//������õı��ʽת��Ϊ�沨�����ʽ
double calculate();//���沨�����ʽ������
void print_stack(stack<char> temp);//���ת�沨��ʱջ�ı仯
void print_stack(stack<double> temp);//�������ʱջ�ı仯

#endif // !headfile_h
