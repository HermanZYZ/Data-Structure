#ifndef headfile_cpp
#define headfile_cpp

#include"headfile.h"


BinaryTree* ReadExpr(BinaryTree* Tree,string prefix)
{
	stack<BinaryTree*> temp_stack;
	for (int i = prefix.size()-1; i >= 0; i--)
	{
		BinaryTree* temp = new BinaryTree;
		Tree = temp;
		if (getOperOrder(prefix[i]) == 5)//���������������ֵ������Ӧ��������Ķ�������㣬��ַѹջ
		{
			temp->value = prefix[i] - '0';
			temp_stack.push(temp);
		}
		else if (prefix[i] == 'S' || prefix[i] == 'C' || prefix[i] == 'T')
		{
			temp->data = prefix[i];
			temp->right = temp_stack.top();
			temp_stack.pop();
			temp_stack.push(temp);
		}
		else if (!isOper(prefix[i]))
		{
			temp->data = prefix[i];
			temp_stack.push(temp);
		}
		else//���������������ֵ������Ӧ��������Ķ�����������ջ�е���������ַ��
		{   //�ֱ���Ϊ����ָ�����ָ�룬Ȼ���ٰ����ַѹջ�����һ����ַ��Ϊ�������ĸ�����ַ
			temp->data = prefix[i];
			temp->left = temp_stack.top();
			temp_stack.pop();
			temp->right = temp_stack.top();
			temp_stack.pop();
			temp_stack.push(temp);
		}
	}
	return Tree;
}

int getOperOrder(char op)//���������op����Ӧ�����ȼ�
{
	switch (op)
	{
	case '(':
		return 1;
	case '+':
	case '-':
		return 2;
	case '*':
	case '/':
		return 3;
	case '^':
		return 4;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return 5;
	case'#':return 6;
	default:
		//������ջ�е������ź�ջ���ַ������ȼ����
		return 0;
	}
}

bool isOper(char op)//�ж��Ƿ�Ϊ�����
{
	char oper[] = { '(',')','+','-','*','/','^' };
	for (int i = 0; i<sizeof(oper); i++)
	{
		if (op == oper[i])
		{
			return true;
		}
	}
	return false;
}

void WriteExpr(BinaryTree* root)//�������
{
	if (root)
	{
		if (root->left)
		{     //���������������ȼ�������������������ڴ�ӡ��Ӧ������֮ǰ�ȴ�ӡ������
			if (isOper(root->left->data) && getOperOrder(root->left->data) < getOperOrder(root->data))
			{
				cout << "(";
				WriteExpr(root->left);//�ڴ�ӡ��Ӧ����������ڴ�ӡһ��������
				cout << ")";
			}
			else {
				WriteExpr(root->left);
			}
		}

		if (getOperOrder(root->data) == 6)//����ǲ������������������
			cout << root->value;
		else if (root->data == 'S')
		{
			cout << "sin";
		}
		else if (root->data == 'C')
		{
			cout << "cos";
		}
		else if (root->data == 'T')
		{
			cout << "tan";
		}
		else
			cout << root->data;//����ǲ������������������

		if (root->right)
		{
			if (isOper(root->right->data) && getOperOrder(root->right->data) <= getOperOrder(root->data))
			{
				cout << "(";
				WriteExpr(root->right);
				cout << ")";
			}
			else {
				WriteExpr(root->right);
			}
		}
	}
}

BinaryTree* Assign(BinaryTree *& Tree, char V, int c)//�����������,��ֵ
{
	queue<BinaryTree*> q;
	q.push(Tree);
	while (!q.empty())
	{
		BinaryTree *r = q.front();
		q.pop();
		if (r->data == V)
		{
			r->data = '#';
			r -> value = c ;
		}
		if (r->left) q.push(r->left);
		if (r->right) q.push(r->right);
	}
	return Tree;
}

double calculate(char op, double left_num, double right_num)//������С�������������������������
{
	switch (op)
	{
	case '+':return (left_num) + (right_num);
	case '-':return (left_num) - (right_num);
	case '*':return (left_num) * (right_num);
	case '/':
		if (right_num == '0') throw logic_error("Error! The denominator is zero!");
		else return (left_num) / (right_num);
	case '^':return pow((left_num) , (right_num));
	default:
		break;
	}
	return 0.0;
}

double Value(BinaryTree * root)//���������ֵ
{
	if (!root) return 0;
	
		if (root->data == 'S')
		{
			return sin(root->right->value);
		}
		else if (root->data == 'C')
		{
			double temp = cos(root->right->value);
			return temp;
		}
		else if (root->data == 'T')
		{
			double temp = tan(root->right->value);
			return temp;
		}
		if (root->left && root->right)
			if (getOperOrder(root->left->data)==6 && getOperOrder(root->right->data)==6)
			{
				return calculate(root->data, root->left->value, root->right->value);
			}

		if (root->left) return calculate(root->data, Value(root->left), root->right->value);
	if (root->right) return calculate(root->data, Value(root->right), root->left->value);
	
	return 0.0;
}

BinaryTree *& CompoundExpr(char P, BinaryTree * &Root, BinaryTree *&root1)//ֱ�������ö������ϼ��ϸ��ڵ�
{
	BinaryTree* node = new BinaryTree;
	node->data = P;
	node->left = Root;
	node->right = root1;
	return node;
}

bool Diff(BinaryTree *root, char V) //������,ʵ�ֵ���MergeConst����
{
	MergeConst(root);
	if(root)
	if (root->left && root->right)
	{
		Diff(root->left, V);
		Diff(root->right, V);
		if (root->data=='^' && root->left->data==V && root->right->data=='#' && root->right->value > 2)
		{   //ָ������2���ݣ����½����½ڵ�
			BinaryTree* left_node = new BinaryTree;
			BinaryTree* right_node = new BinaryTree;
			left_node->data = root->left->data;
			right_node->value = root->right->value - 1;
			root->right->left = left_node;
			root->right->right = right_node;

			root->data = '*';
			root->left->data = '#';
			root->left->value = root->right->value;
			root->right->data = '^';
			root->right->value = 0;
			return true;
		}

		if (root->data == '^' && root->left->data == V && root->right->data == '#' && root->right->data == 2)
		{ //ָ��Ϊ2����
			root->data = '*';
			return true;
		}

		if (root->data == '^' && root->left->data == V && !isOper(root->right->data) && root->right->data!='#')
		{//ָ��Ϊ��������������½����½ڵ�
			BinaryTree* left0_node = new BinaryTree;
			BinaryTree* right0_node = new BinaryTree;
			BinaryTree* left1_node = new BinaryTree;
			BinaryTree* right1_node = new BinaryTree;
			
			root->data = '*';
			root->left->data = root->right->data;
			root->right->data = '^';
			root->right->left = left0_node;
			left0_node->data = V;
			root->right->right = right0_node;
			right0_node->data = '-';
			right0_node->left = left1_node;
			left1_node->data = root->left->data;
			right0_node->right = right1_node;
			right1_node->value = 1;
			return true;
		}

		//if (Diff(root->left,V) && getOperOrder(root->data) == 3)
		//{
		//	return true;
		//}

		//if (Diff(root->right, V) && getOperOrder(root->data) == 3)
		//{
		//	return true;
		//}

		if (getOperOrder(root->data) == 2 && root->left->data == V)
		{  //������ı���
			root->left->data = '#';
			root->left->value = 1;
			//return false;
		}

		if (getOperOrder(root->data) == 2 && root->right->data == V)
		{
			root->right->data = '#';
			root->right->value = 1;
			//return false;
		}

		if (isOper(root->data) && !isOper(root->left->data) && !isOper(root->right->data))
		{//���������
			delete root->left, root->right;
			root->data = '#';
			root->value = 0;
			return false;
		}

		if (isOper(root->data) && root->left->data == '#' && root->right->data == '#')
		{//���������
			delete root->left, root->right;
			root->data = '#';
			root->value = 0;
			return false;
		}
		/*if (isOper(root->data) && !isOper(root->left->data) && root->left->data != V)
		{
			root->left->data = '#';
			root->left->value = 0;
		}*/
		if (isOper(root->data) && !isOper(root->right->data) && root->right->data != V && !isOper(root->left->data) && root->left->data != V)
		{
			root->right->data = '#';
			root->right->value = 0;
			root->left->data = '#';
			root->left->value = 0;
		}
	}
	return false;
}


//
//void Diff(BinaryTree *root, char V) //������
//{
//	if (root)
//	{
//		if (root->left && root->right)
//		{
//			if (root->left->left && root->left->right)
//			{
//				if (root->left->left->data == V && root->left->data == '^' && (root->left->right->value > 1 && root->left->right->value <= 9))
//				{
//					int coe = root->left->right->value;
//					root->left->right->value = coe - 1;
//					BinaryTree* node_op = new BinaryTree;
//					BinaryTree* node_num = new BinaryTree;
//					node_op->data = '*';
//					node_op->left = node_num;
//					node_num->value = coe;
//					node_op->right = root->left;
//					root->left = node_op;
//					Diff(root->right, V);
//					return;
//				}
//			}
//			if (root->left->data == V && root->data == '^' && root->right->value ==1 )
//			{
//				delete root->left, root->right;
//				root->left = root->right = NULL;
//				root->data = '#';
//				root->value = 1;
//				return;
//			}
//			if (root->left->data == V && root->data == '^' && root->right->value == 0)
//			{
//				delete root->left, root->right;
//				root->left = root->right = NULL;
//				root->value = 1;
//				root->data = '#';
//				return;
//			}
//			if (root->right->data == V)
//			{
//				root->right->data = '#';
//				root->right->value = 1;
//				return;
//
//			}
//			if (root->left->data != V && !isOper(root->right->data))
//			{
//				delete root->left, root->right;
//				root->left = root->right = NULL;
//				root->data = '#';
//				root->value = 0;
//				return;
//			}
//			
//			Diff(root->left, V);
//			Diff(root->right, V);
//		}
//		if (root->data == V)
//		{
//			root->data = '#';
//			root->value = 1;
//			return;
//		}
//		root->data = '#';
//		root->value = 0;
//		return;
//		
//	}
//	return;
//}

//BinaryTree* Diff(string E, char V)
//{
//	BinaryTree* Root = new BinaryTree;
//	Root = ReadExpr(Root,E);
//	posOrderDiff(Root, V);
//	return Root;
//}

void MergeConst(BinaryTree * root)
{
	if (root)
	{
		if (root->left && root->right)
		{
			//if (getOperOrder(root->data) == 2)
			//{
			//	if (!isOper(root->right->data) && root->right->data != '#' && root->left->data == '#')
			//	{//����
			//		root->left->data = root->right->data;
			//		root->right->value = root->left->value;
			//		root->left->value = 0;
			//		root->right->data = '#';
			//	}
			//}
			
			while (getOperOrder(root->data) == getOperOrder(root->left->data) && root->left->right )
			{//�������ºϲ���������ȼ���ͬ����ϲ�
				if (root->right->data == '#' && root->left->right->data == '#')
				{
					double temp_result = calculate(root->data, root->left->right->value, root->right->value);
					BinaryTree* temp = root->left->left;
					root->data = root->left->data;
					root->right->value = temp_result;
					delete root->left;
					root->left = temp;
				}
				else if (root->left->data == '#' && root->right->left->data == '#')
				{
					double temp_result = calculate(root->data, root->right->left->value, root->left->value);
					BinaryTree* temp = root->right->right;
					root->data = root->right->data;
					root->left->value = temp_result;
					delete root->right;
					root->right = temp;
				}
				else if (root->right->data == '#' && root->left->left->data == '#')
				{
					double temp_result = calculate(root->data, root->left->left->value, root->right->value);
					BinaryTree* temp = root->left->right;
					root->data = root->left->data;
					root->right->value = temp_result;
					delete root->left;
					root->left = temp;
				}
				else if (root->left->data == '#' && root->right->right->data == '#')
				{
					double temp_result = calculate(root->data, root->right->right->value, root->left->value);
					BinaryTree* temp = root->right->left;
					root->data = root->right->data;
					root->left->value = temp_result;
					delete root->right;
					root->right = temp;
				}
				else
					break;
			}

			//if (isOper(root->data) && root->left->data == '#' && root->right->data == '#')
			//{
			//	root->value = calculate(root->data, root->left->value, root->right->value);
			//	root->data = '#';
			//	delete root->left, root->right;
			//	return;
			//}

			if (root->right->data == '#' && root->right->value == 0)
			{//ɾ��0����
				BinaryTree* temp_left = root->left->left;
				BinaryTree* temp_right = root->left->right;
				root->data = root->left->data;
				root->value = root->left->value;
				delete root->left, root->right;
				root->left = temp_left;
				root->right = temp_right;
			}
			if (root->left->data == '#' && root->left->value == 0)
			{//ɾ��0����
				BinaryTree* temp_left = root->right->left;
				BinaryTree* temp_right = root->right->right;
				root->data = root->right->data;
				root->value = root->right->value;
				delete root->left, root->right;
				root->left = temp_left;
				root->right = temp_right;
			}

			if (root->data == '*' && (root->left->data == '#' && root->left->value == 0 || root->right->data == '#' && root->right->value == 0))
			{//ɾ��0
				root->left->data = root->right->data = '#';
				root->left->value = root->right->value = 0;
			}

			if (isOper(root->data) && root->left->data == '#' && root->right->data == '#')
			{//�ϲ�
				root->value = calculate(root->data, root->left->value, root->right->value);
				root->data = '#';
				delete root->left, root->right;
				root->left = root->right = NULL;
				return;
			}
		}
		if (root->left) return MergeConst(root->left);
		if (root->right) return MergeConst(root->right);
	}
	return;
}
//
//BinaryTree* MergeConst(string E)
//{
//	BinaryTree* Root = new BinaryTree;
//	ReadExpr(Root, E);
//	preOrderMerge(Root);
//	return Root;
//}

//���ٶ�����     
void freeTree(BinaryTree*& p)
{
	if (p->left != NULL)
		freeTree(p->left);
	if (p->right != NULL)
		freeTree(p->right);
	delete(p);
}

#endif