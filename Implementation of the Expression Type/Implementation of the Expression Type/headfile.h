#pragma once
#ifndef headfile_h
#define headfile_h

#include<iostream>
#include<stack>
#include<string>
#include<queue>
#include<stdexcept>
#include<cmath>

using namespace std;

struct BinaryTree
{
	double value;
	char data;//operator
	BinaryTree* left;
	BinaryTree* right;
	BinaryTree()
	{
		data = '#';
		value = 0;
		left = NULL;
		right = NULL;
	}
};

BinaryTree* ReadExpr(BinaryTree* Tree,string prefix);//读入前缀表达式，建立树

int getOperOrder(char op);//判断运算符优先级
bool isOper(char op);//判断是否是运算符
void WriteExpr(BinaryTree* root);//输出中缀表达式

BinaryTree* Assign(BinaryTree* &Tree,char V, int c);//赋值

double calculate(char op, double left_num, double right_num);//计算
double Value(BinaryTree* root);//求值

BinaryTree * &CompoundExpr(char P, BinaryTree * &Root, BinaryTree *&root1);//表达式相加

bool Diff(BinaryTree *root, char V);//求偏导
//BinaryTree* Diff(string E, char V);

void MergeConst(BinaryTree *root);//合并
//BinaryTree* MergeConst(string E);

void freeTree(BinaryTree*& p);//删除树

#endif // !headfile_h
