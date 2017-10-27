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

double calculate(double former, char _operator, double latter)//传值计算每一项
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

int judge_mod(int former, char _operator, int latter)//求模
{
	cout << "Push " << "the result of " << setw(8) << right << former << " % " << setw(8) << left << latter << " :" << setw(4) << left << " ";
	return former%latter;
}

void preprocess(string expression)//预处理表达式
{
	after_pre.clear();
	for (int i = 0; i < expression.size(); i++)//预处理表达式
	{
		if ((expression[i] == '+' || expression[i] == '-') && i == 0)//首项正负
		{
			after_pre += '0';
			after_pre += expression[i];
		}
		else if (expression[i] == '(' && (expression[i + 1] == '+' || expression[i + 1] == '-'))//左括号后正负
		{
			after_pre += expression[i];
			after_pre += '0';
		}
		else if (expression[i] == ' ')//跳过空格
			continue;
		else
			after_pre += expression[i];
	}
	//	return after_pre;

}

bool judge()//判断表达式是否合法
{
	int left_par = 0, right_par = 0;//左括号右括号
	if (after_pre.size() == 2 && (after_pre[1]<'0' || after_pre[1]>'9'))//判断表达式 
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
				|| after_pre[i] == '/' || after_pre[i] == '%' || after_pre[i] == '^')//判断运算符号
			{
				//运算符相邻
				if (after_pre[i + 1] == '+' || after_pre[i + 1] == '-' || after_pre[i + 1] == '*'  \
					|| after_pre[i + 1] == '/' || after_pre[i + 1] == ')' || after_pre[i + 1] == '%' || after_pre[i + 1] == '^')
				{
					printf("Presentation Error\n");
					cout << endl;
					return false;
				}
				if ((after_pre[i] == '/' && after_pre[i + 1] == 0))//分母为零
				{
					printf("Presentation Error\n");
					cout << endl;
					return false;
				}
			}
			else if (after_pre[i] == '(')//左括号与非正负号相邻
			{
				if (after_pre[i + 1] == '*' || after_pre[i + 1] == '/' || after_pre[i + 1] == ')'\
					|| after_pre[i + 1] == '%' || after_pre[i + 1] == '^')
				{
					printf("Presentation Error\n");
					cout << endl;
					return false;
				}
			}
			else if (after_pre[i] == ')')//右括号与左括号或数字相邻
			{
				if (after_pre[i + 1] == '(' || ('0' <= after_pre[i + 1] && after_pre[i + 1] >= '0'))
				{
					printf("Presentation Error\n");
					cout << endl;
					return false;
				}
			}
			else  //表达式存在其他字符
			{
				printf("Presentation Error\n");
				cout << endl;
				return false;
			}

			switch (after_pre[i])//判断括号是否配对 
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
		//判断结束

	return true;
}

void toRPN()
{
	RPN.clear();
	cout << "Begin to convert expression." << endl;
	for (int i = 0; i < after_pre.size(); i++)//将中缀表达式转换为后缀表达式 
	{
		if (after_pre[i] >= '0' && after_pre[i] <= '9')//数字
		{
			if (after_pre[i + 1] >= '0' && after_pre[i + 1] <= '9')
				RPN += after_pre[i];
			else
			{
				RPN += after_pre[i];
				RPN += ' ';
			}
		}
		else if (after_pre[i] == '(')//左括号压栈
		{
			_operator.push(after_pre[i]);
			cout << "Push : " << after_pre[i] << setw(5) << " ";
			print_stack(_operator);
		}
		else if (after_pre[i] == ')')//右括号出栈
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
		else if (_operator.empty() || precedence(after_pre[i]) > precedence(_operator.top()))//栈空或者目前运算符大于栈顶运算符
		{
			_operator.push(after_pre[i]);
			cout << "Push : " << after_pre[i] << setw(5) << " ";
			print_stack(_operator);
		}
		else
		{
			while (precedence(after_pre[i]) <= precedence(_operator.top()))//目前运算符小于等于栈顶运算符
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
	while (!_operator.empty())//栈内余项依次出栈
	{
		RPN += _operator.top();
		cout << "Pop  : " << _operator.top() << setw(5) << " ";
		_operator.pop();
		print_stack(_operator);
	}//转换结束 
	cout << "The Reverse Polish expression conversion completes. " << endl;
	cout << "RPN : " << RPN << endl;

	Sleep(5000);
	system("CLS");
//	return RPN;
}

double calculate()
{
	//可以用sstream
	cout << "Begin to calculate." << endl << "The RPN : " << RPN << endl;
	for (int i = 0; i < RPN.size(); i++)//运算 
	{
		char toINT[80];//用于辅助字符转换成数字
		double num;
		if (RPN[i] >= '0' && RPN[i] <= '9')//数字
			toINT[i] = RPN[i];
		else if (RPN[i] == ' ')//空格为间断点
		{
			num = atoi(toINT);
			memset(toINT, ' ', 80);
			cul.push(num);
			cout << "Push " << setw(8) << left << setprecision(5) << num << " :" << setw(29) << left << " ";
			print_stack(cul);/////////////////
			num = 0;
		}//遇到运算符，数字出栈运算
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
	} //运算结束 

	double result = cul.top();
	cul.pop();
	return result;
}

void print_stack(stack<char> temp) //输出操作符栈
{
	string change,reverse;
	while (!temp.empty())
	{
		change += temp.top();
		temp.pop();
	}
	cout << "#" ;
	for (int i = change.size() - 1; i >= 0; i--) //反转字符串
		cout << " " << change[i];
	cout << " #" << endl;
	Sleep(1000);
}

void print_stack(stack<double> temp)//输出操作数栈
{
	int len = temp.size() - 1, save_len;
	save_len = temp.size();          //保存栈的初始长度
	double output[300] = { 0 };
	while (!temp.empty())           //保存栈的内容
	{
		output[len] = temp.top();
		temp.pop();
		len--;
	}
	cout << "# " << setprecision(5) << output[0];
	for (int i = 1; i < save_len; i++)//输出
		cout << " " << setprecision(5) << output[i];
	cout << " #" << endl;
	Sleep(1000);
}

#endif
