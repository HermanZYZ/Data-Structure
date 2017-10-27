#include"headfile.h"
#include<conio.h>

int main()
{
	cout << "Welcome! Input the expression you want to calculate derectly!" << endl;
	while (1)
	{
		cout << endl << "Input the expression." << endl;
		getline(cin, input_exp, '\n');
		if (input_exp.size() == 0)
			continue;
		preprocess(input_exp);
		
		if (judge())
		{
			toRPN();
			cout << "The final result is : "  << setprecision(5) << calculate() << endl;
		}
		input_exp.clear();
		cout << endl << "Any keys to continue.ESC to exit." << endl;
		if (_getch() == 27)
			break;
		system("CLS");
	}
	return 0;
}