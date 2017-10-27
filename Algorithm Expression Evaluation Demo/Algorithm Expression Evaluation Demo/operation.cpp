#ifndef operation_cpp
#define operation_cpp

#include"headfile.h"

int precedence(char _operator)
{
	switch (_operator)
	{
	case '+':
	case '-': return 1;
	case '*':
	case '/': return 2;
	case '%': return 3;
	case '^': return 4;
	default: return 0;
	}
}

double calculate(double former, char _operator, double latter)//��ֵ����ÿһ��
{
	cout << "Push the result of " << setw(8) << right << former << " " << _operator << " " << setw(8) << left << latter << " :" << setw(4) << left << " ";
	if (_operator == '+')
		return 1.00*(former + latter);
	if (_operator == '-')
		return 1.00*(former - latter);
	if (_operator == '*')
		return 1.00*former*latter;
	if (_operator == '/')
		return 1.00*former / latter;
	if (_operator == '^')
		return 1.00*pow(former, latter);
	return 0;
}

int judge_mod(int former, char _operator, int latter)//��ģ
{
	cout << "Push " << "the result of " << setw(8) << right << former << " % " << setw(8) << left << latter << " :" << setw(4) << left << " ";
	return former%latter;
}

void preprocess(string expression)//Ԥ������ʽ
{
	after_pre.clear();
	for (int i = 0; i < expression.size(); i++)//Ԥ������ʽ
	{
		if ((expression[i] == '+' || expression[i] == '-') && i == 0)//��������
		{
			after_pre += '0';
			after_pre += expression[i];
		}
		else if (expression[i] == '(' && (expression[i + 1] == '+' || expression[i + 1] == '-'))//�����ź�����
		{
			after_pre += expression[i];
			after_pre += '0';
		}
		else if (expression[i] == ' ')//�����ո�
			continue;
		else
			after_pre += expression[i];
	}
	//	return after_pre;

}

bool judge()//�жϱ��ʽ�Ƿ�Ϸ�
{
	int left_par = 0, right_par = 0;//������������
	if (after_pre.size() == 2 && (after_pre[1]<'0' || after_pre[1]>'9'))//�жϱ��ʽ 
	{
		printf("Presentation Error\n");
		return false;
	}
	else
	{
		for (int i = 0; i < after_pre.size(); i++)
		{
			if (after_pre[i] >= '0' && after_pre[i] <= '9') continue;
			if (after_pre[i] == '+' || after_pre[i] == '-' || after_pre[i] == '*' \
				|| after_pre[i] == '/' || after_pre[i] == '%' || after_pre[i] == '^')//�ж��������
			{
				//���������
				if (after_pre[i + 1] == '+' || after_pre[i + 1] == '-' || after_pre[i + 1] == '*'  \
					|| after_pre[i + 1] == '/' || after_pre[i + 1] == ')' || after_pre[i + 1] == '%' || after_pre[i + 1] == '^')
				{
					printf("Presentation Error\n");
					cout << endl;
					return false;
				}
				if ((after_pre[i] == '/' && after_pre[i + 1] == 0))//��ĸΪ��
				{
					printf("Presentation Error\n");
					cout << endl;
					return false;
				}
			}
			else if (after_pre[i] == '(')//�������������������
			{
				if (after_pre[i + 1] == '*' || after_pre[i + 1] == '/' || after_pre[i + 1] == ')'\
					|| after_pre[i + 1] == '%' || after_pre[i + 1] == '^')
				{
					printf("Presentation Error\n");
					cout << endl;
					return false;
				}
			}
			else if (after_pre[i] == ')')//�������������Ż���������
			{
				if (after_pre[i + 1] == '(' || ('0' <= after_pre[i + 1] && after_pre[i + 1] >= '0'))
				{
					printf("Presentation Error\n");
					cout << endl;
					return false;
				}
			}
			else  //���ʽ���������ַ�
			{
				printf("Presentation Error\n");
				cout << endl;
				return false;
			}

			switch (after_pre[i])//�ж������Ƿ���� 
			{
			case '(': left_par++; break;
			case ')': right_par++; break;
			}
		}

	}
	if (left_par != right_par)
	{
		printf("Presentation Error\n");
		return false;
	}
	if (after_pre[after_pre.size() - 1]<'0' || after_pre[after_pre.size() - 1]>'9')
	{
		printf("Presentation Error\n");
		return false;
	}
		//�жϽ���

	return true;
}

void toRPN()
{
	RPN.clear();
	cout << "Begin to convert expression." << endl;
	for (int i = 0; i < after_pre.size(); i++)//����׺���ʽת��Ϊ��׺���ʽ 
	{
		if (after_pre[i] >= '0' && after_pre[i] <= '9')//����
		{
			if (after_pre[i + 1] >= '0' && after_pre[i + 1] <= '9')
				RPN += after_pre[i];
			else
			{
				RPN += after_pre[i];
				RPN += ' ';
			}
		}
		else if (after_pre[i] == '(')//������ѹջ
		{
			_operator.push(after_pre[i]);
			cout << "Push : " << after_pre[i] << setw(5) << " ";
			print_stack(_operator);
		}
		else if (after_pre[i] == ')')//�����ų�ջ
		{
			while (_operator.top() != '(')
			{
				RPN += _operator.top();
				cout << "Pop  : " << _operator.top() << setw(5) << " ";
				_operator.pop();
				print_stack(_operator);
			}
			cout << "Pop  : " << _operator.top() << setw(5) << " ";
			_operator.pop();
			print_stack(_operator);
		}
		else if (_operator.empty() || precedence(after_pre[i]) > precedence(_operator.top()))//ջ�ջ���Ŀǰ���������ջ�������
		{
			_operator.push(after_pre[i]);
			cout << "Push : " << after_pre[i] << setw(5) << " ";
			print_stack(_operator);
		}
		else
		{
			while (precedence(after_pre[i]) <= precedence(_operator.top()))//Ŀǰ�����С�ڵ���ջ�������
			{
				RPN += _operator.top();
				cout << "Pop  : " << _operator.top() << setw(5) << " ";
				_operator.pop();
				print_stack(_operator);
				if (_operator.empty())
					break;
			}
			_operator.push(after_pre[i]);
			cout << "Push : " << after_pre[i] << setw(5) << " ";
			print_stack(_operator);
		}
	}
	while (!_operator.empty())//ջ���������γ�ջ
	{
		RPN += _operator.top();
		cout << "Pop  : " << _operator.top() << setw(5) << " ";
		_operator.pop();
		print_stack(_operator);
	}//ת������ 
	cout << "The Reverse Polish expression conversion completes. " << endl;
	cout << "RPN : " << RPN << endl;

	Sleep(5000);
	system("CLS");
//	return RPN;
}

double calculate()
{
	//������sstream
	cout << "Begin to calculate." << endl << "The RPN : " << RPN << endl;
	for (int i = 0; i < RPN.size(); i++)//���� 
	{
		char toINT[80];//���ڸ����ַ�ת��������
		double num;
		if (RPN[i] >= '0' && RPN[i] <= '9')//����
			toINT[i] = RPN[i];
		else if (RPN[i] == ' ')//�ո�Ϊ��ϵ�
		{
			num = atoi(toINT);
			memset(toINT, ' ', 80);
			cul.push(num);
			cout << "Push " << setw(8) << left << setprecision(5) << num << " :" << setw(29) << left << " ";
			print_stack(cul);/////////////////
			num = 0;
		}//��������������ֳ�ջ����
		else if (RPN[i] == '+' || RPN[i] == '-' || RPN[i] == '*' || RPN[i] == '/' || RPN[i] == '%' || RPN[i] == '^')
		{
			double num1 = 0, num2 = 0;
			num1 = cul.top();
			cul.pop();
			cout << "Pop  " << setw(8) << left << setprecision(5) << num1 << " :" << setw(29) << left << " ";
			print_stack(cul);/////////////////
			num2 = cul.top();
			cul.pop();
			cout << "Pop  " << setw(8) << left << setprecision(5) << num2 << " :" << setw(29) << left << " ";
			print_stack(cul);/////////////////
			if (RPN[i] == '%')
				cul.push(1.00*judge_mod((int)num2, RPN[i], (int)num1));
			else
				cul.push(1.00*calculate(num2, RPN[i], num1));
			print_stack(cul);/////////////////
		}
	} //������� 

	double result = cul.top();
	cul.pop();
	return result;
}

void print_stack(stack<char> temp) //���������ջ
{
	string change,reverse;
	while (!temp.empty())
	{
		change += temp.top();
		temp.pop();
	}
	cout << "#" ;
	for (int i = change.size() - 1; i >= 0; i--) //��ת�ַ���
		cout << " " << change[i];
	cout << " #" << endl;
	Sleep(1000);
}

void print_stack(stack<double> temp)//���������ջ
{
	int len = temp.size() - 1, save_len;
	save_len = temp.size();          //����ջ�ĳ�ʼ����
	double output[300] = { 0 };
	while (!temp.empty())           //����ջ������
	{
		output[len] = temp.top();
		temp.pop();
		len--;
	}
	cout << "# " << setprecision(5) << output[0];
	for (int i = 1; i < save_len; i++)//���
		cout << " " << setprecision(5) << output[i];
	cout << " #" << endl;
	Sleep(1000);
}

#endif
