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

BinaryTree* ReadExpr(BinaryTree* Tree,string prefix);//����ǰ׺���ʽ��������

int getOperOrder(char op);//�ж���������ȼ�
bool isOper(char op);//�ж��Ƿ��������
void WriteExpr(BinaryTree* root);//�����׺���ʽ

BinaryTree* Assign(BinaryTree* &Tree,char V, int c);//��ֵ

double calculate(char op, double left_num, double right_num);//����
double Value(BinaryTree* root);//��ֵ

BinaryTree * &CompoundExpr(char P, BinaryTree * &Root, BinaryTree *&root1);//���ʽ���

bool Diff(BinaryTree *root, char V);//��ƫ��
//BinaryTree* Diff(string E, char V);

void MergeConst(BinaryTree *root);//�ϲ�
//BinaryTree* MergeConst(string E);

void freeTree(BinaryTree*& p);//ɾ����

#endif // !headfile_h
