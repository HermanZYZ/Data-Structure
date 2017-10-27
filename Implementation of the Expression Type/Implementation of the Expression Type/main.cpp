#include"headfile.h"

//using namespace std;

int main()
{

	int flag = 1;
	while (flag)
	{
		string prefix, infix;
		BinaryTree* Tree = new BinaryTree();
		cout << "Please input an expression with prefix form." << endl;
		cin >> prefix;
		Tree = ReadExpr(Tree,prefix);
		cout << "The infix form of your expression is :";
		WriteExpr(Tree);
		cout << endl;
		
		/*cout << "Diff : Input the variable" << endl;
		char variable;
		cin >> variable;
		Diff(Tree, variable);
		cout << "The result after operation: ";
		WriteExpr(Tree);
		cout << endl;
		MergeConst(Tree);
		cout << "The result after simplication: ";
		WriteExpr(Tree);
		cout << endl;

		cout << "Which variable do you choose to assign ? Input it and its value." << endl;
		int value;
		cin >> variable;
		cin >> value;
		Assign(Tree, variable, value);
		cout << "The result after operation: ";
		WriteExpr(Tree);
		cout << endl;
		MergeConst(Tree);
		cout << "The result after simplication: ";
		WriteExpr(Tree);
		cout << endl;

		cout << "Input another expression." << endl;
		string ano;
		cin >> ano;
		char ope;
		cout << "Input the operation." << endl;
		cin >> ope;
		BinaryTree* another = new BinaryTree;
		ReadExpr(another, ano);
		BinaryTree* another_Tree;
		another_Tree = CompoundExpr(ope, Tree, another);
		cout << "The result after operation: ";
		WriteExpr(Tree);
		cout << endl;
		MergeConst(Tree);
		cout << "The result after simplication: ";
		WriteExpr(Tree);
		cout << endl;

		cout << "The value of the expression is: ";
		cout << Value(Tree) << endl;*/
		int choose;
		cout << "Which operation will you choose :"\
			<< "1.Assign   2.Value   3.CompoundExpr   4.Diff " << endl;
		cin >> choose;
		switch (choose)
		{
		case 1: {
			cout << "Which variable do you choose to assign ? Input it and its value." << endl;
			char variable;
			int value;
			cin >> variable;
			cin >> value;
			Assign(Tree, variable, value);
			cout << "The result after operation: ";
			WriteExpr(Tree);
			cout << endl;
			MergeConst(Tree);
			free(Tree);

		} break;
		case 2: {
			cout << "The value of the expression is: ";
			cout << Value(Tree) << endl;
			free(Tree);
		} break;
		case 4: {
			cout << "Input the variable" << endl;
			char variable;
			cin >> variable;
			Diff(Tree, variable);
			cout << "The result after operation: ";
			WriteExpr(Tree);
			cout << endl;
			MergeConst(Tree);
			cout << "The result after simplication: ";
			WriteExpr(Tree);
			cout << endl;
			free(Tree);
		} break;
		case 3: {
			cout << "Input another expression." << endl;
			string ano;
			cin >> ano;
			char ope;
			cout << "Input the operation." << endl;
			cin >> ope;
			BinaryTree* another = new BinaryTree;
			another = ReadExpr(another, ano);
			BinaryTree* another_Tree;
			another_Tree = CompoundExpr(ope, Tree, another);
			cout << "The result after operation: ";
			WriteExpr(another_Tree);
			cout << endl;
			MergeConst(another_Tree);
			cout << "The result after simplication: ";
			WriteExpr(another_Tree);
			cout << endl;
			free(another_Tree);
			
		} break;
		default:
			break;
		}
		cout << "If continue ? 1/0" << endl;
		cin >> flag;
	}
	
}