#include<iostream>
#include<queue>
#include<stack>
#include<string>
#include <Windows.h>
using namespace std;

#define MAX 30
int visited[MAX] = { 0 };
int Mvisited[MAX] = { 0 };
//************************************************************
//换个颜色装个逼
void setyellow()
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);//黄色
	SetConsoleTextAttribute(hOut,
		FOREGROUND_RED |
		FOREGROUND_GREEN |
		FOREGROUND_INTENSITY);
}
void setred()
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);//红色
	SetConsoleTextAttribute(hOut,
		FOREGROUND_GREEN |
		FOREGROUND_BLUE |
		FOREGROUND_INTENSITY);
}
void setwhite()
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut,//白色
		FOREGROUND_RED |
		FOREGROUND_GREEN |
		FOREGROUND_BLUE);
}
//*************************************************************
//树的结构
typedef struct Tree {
	string data;
	int degree;
	Tree *parent;
	Tree *Child[MAX];
}Tree;

//**************************************************************
//邻接表的实现
typedef struct ArcNode//定义邻接表结构 ：表节点类型
{
	int adjvex;//邻接点的位置   
	int weight;//权重 
	struct ArcNode *nextarc;//指向下一条弧的指针 
}ArcNode;

typedef struct VNode//定义顶点结构类型 
{
	string data;//存放顶点信息 
				//int degree;//该点度数
	ArcNode *firstarc;//指向第一条依附于该定点的指针 
}VNode, Adjlist[MAX];

typedef struct Graph
{
	Adjlist vertices;
	int vexnum;
	int arcnum;
}Graph;

//*************************************************************
//Multi-list
typedef struct Edge
{

	int vertex_1;
	int vertex_2;
	int mark;//标记去访问哪条边
	bool mark_1, mark_2;//分别标记path_1,path_2是否访问过
	int cost;
	struct Edge* path_1, *path_2;
	struct Edge()
	{
		mark = 0;
		mark_1 = mark_2 = true;
		path_1 = path_2 = NULL;
	}
}Edge;

typedef struct Node
{
	string info;
	Edge *firstout;
}Node, MultiList[MAX];

typedef struct MGraph
{
	MultiList vertex;
	int vex;
	int arc;
}MGraph;

//****************************************************************

Graph G;//
MGraph MG;
Tree* D_Tree, *B_Tree, *MD_Tree, *MB_Tree;

int Locate(Graph G, string v)
{
	int i = 0;
	while (i<G.vexnum && v != G.vertices[i].data)
	{
		i++;
	}
	if (i < G.vexnum)
		return i;
}

void Create()
{
	setyellow();
	cout << "Please input the number of Graph's vertices and edges" << endl;
	setwhite();
	cin >> G.vexnum >> G.arcnum;//输入点数和边数

	MG.vex = G.vexnum;
	MG.arc = G.arcnum;

	string v1, v2;
	int v1_locate, v2_locate, v_weight;
	ArcNode *p1, *p2;
	setyellow();
	cout << "Please input the informations of Graph's vertices" << endl;
	setwhite();
	for (int i = 0; i < G.vexnum; i++)
	{
		//adjacency list
		cin >> G.vertices[i].data;//输入点的信息，初始化
		G.vertices[i].firstarc = NULL;
		//*****************************************************************
		MG.vertex[i].info = G.vertices[i].data;
		MG.vertex[i].firstout = NULL;
		//D_Tree.vertices[i].firstarc = B_Tree.vertices[i].firstarc = NULL;

	}
	setyellow();
	cout << "Please input the vertices of an edge from the begining point to end point,as well its weight." << endl;
	setwhite();
	for (int i = 0; i < G.arcnum; i++)
	{
		//adjacency list
		p1 = new ArcNode;//采用头插入法建立邻接表
		cin >> v1 >> v2 >> p1->weight;//输入边及权重
		v1_locate = Locate(G, v1);
		v2_locate = Locate(G, v2);

		p1->adjvex = v2_locate;
		p1->nextarc = G.vertices[v1_locate].firstarc;
		G.vertices[v1_locate].firstarc = p1;

		p2 = new ArcNode;//由于是无向图，所以再反向建一个
		p2->weight = p1->weight;
		p2->adjvex = v1_locate;
		p2->nextarc = G.vertices[v2_locate].firstarc;
		G.vertices[v2_locate].firstarc = p2;

		//adjacency multi-list
		Edge *edge1 = new Edge;//多重邻接表
		edge1->cost = p1->weight;
		edge1->vertex_1 = v1_locate;
		edge1->vertex_2 = v2_locate;
		edge1->path_1 = MG.vertex[v1_locate].firstout;
		MG.vertex[v1_locate].firstout = edge1;
		edge1->path_2 = MG.vertex[v2_locate].firstout;
		MG.vertex[v2_locate].firstout = edge1;

		//Edge *edge2 = new Edge;
		//edge2->cost = p2->weight;
		//edge2->vertex_1 = v2_locate;
		//edge2->vertex_2 = v1_locate;
		//edge2->path_1 = MG.vertex[v2_locate].firstout;
		//MG.vertex[v2_locate].firstout = edge2;
		//edge2->path_2 = MG.vertex[v1_locate].firstout;
		//MG.vertex[v1_locate].firstout = edge2;
	}
}

//*************************************************************************
//adjacency list
void DFS(const Graph G, int v)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		visited[i] = 0;
	}
	visited[v] = 1;
	cout << G.vertices[v].data << " ";
	stack <ArcNode*> dfs_stack;
	ArcNode *q;
	dfs_stack.push(G.vertices[v].firstarc);

	D_Tree = new Tree;//DFS建树
	Tree* Dtree = D_Tree;
	Dtree->data = G.vertices[v].data;
	Dtree->parent = NULL;
	Dtree->degree = 0;

	while (!dfs_stack.empty())
	{
		q = dfs_stack.top();
		while (q != NULL)
		{
			if (visited[q->adjvex])//如果该点被访问过了，就循着它的邻接点继续访问
				q = q->nextarc;
			else
				break;
		}
		if (q)
		{
			visited[q->adjvex] = 1;//访问该点
			cout << G.vertices[q->adjvex].data << " ";

			Dtree->Child[Dtree->degree] = new Tree;
			Tree *tmp = Dtree->Child[Dtree->degree];
			tmp->data = G.vertices[q->adjvex].data;
			tmp->parent = Dtree;
			Dtree->degree++;
			Dtree = tmp;
			Dtree->degree = 0;

			dfs_stack.push(G.vertices[q->adjvex].firstarc);//把该点的出度表压栈
		}
		else
		{
			dfs_stack.pop();//如果该点及邻接点都被访问过了，就pop掉
			Dtree = Dtree->parent;
		}
	}
}

void BFS(const Graph G, int v)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		visited[i] = 0;
	}
	queue<int> bfs_queue;
	queue<Tree*> Bfstree_queue;
	visited[v] = 1;
	cout << G.vertices[v].data << " ";

	B_Tree = new Tree;//BFS建树
	Tree* Btree = B_Tree;
	Btree->data = G.vertices[v].data;
	Btree->parent = NULL;
	Btree->degree = 0;

	bfs_queue.push(v);
	Bfstree_queue.push(Btree);
	while (!bfs_queue.empty())
	{
		int temp;
		temp = bfs_queue.front();//取队列头
		Btree = Bfstree_queue.front();//采用另一个队列，和BFS的队列同步
		bfs_queue.pop();
		Bfstree_queue.pop();
		for (ArcNode *p = G.vertices[temp].firstarc; p; p = p->nextarc)
		{//从该点的出度表，沿着它的邻接点进行访问
			if (!visited[p->adjvex])
			{//如果该点没有被访问过，就访问并压入队列
				visited[p->adjvex] = 1;
				cout << G.vertices[p->adjvex].data << " ";
				Btree->Child[Btree->degree] = new Tree;
				Tree *tmp = Btree->Child[Btree->degree];
				tmp->data = G.vertices[p->adjvex].data;
				tmp->parent = Btree;
				tmp->degree = 0;
				Bfstree_queue.push(tmp);
				Btree->degree++;

				bfs_queue.push(p->adjvex);
			}
		}
	}

}

//*************************************************************************
//adjacency multi-list

void DFS_Search(const MGraph mG, int v)
{
	//初始化每个节点
	for (int i = 0; i < MG.vex; i++)
	{
		Mvisited[i] = 0;
		MG.vertex[i].firstout->mark = 0;
		MG.vertex[i].firstout->mark_1 = true;
		MG.vertex[i].firstout->mark_2 = true;
	}
	cout << mG.vertex[v].info << "*";
	Mvisited[v] = 1;
	Edge* edge = mG.vertex[v].firstout;
	stack<Edge*> DFS_stack;
	DFS_stack.push(edge);

	MD_Tree = new Tree;
	Tree* Dtree = MD_Tree;
	Dtree->data = mG.vertex[v].info;
	Dtree->parent = NULL;
	Dtree->degree = 0;
	string tmpinfo, out;
	tmpinfo = Dtree->data;
	while (!DFS_stack.empty())
	{
		edge = DFS_stack.top();
		if (edge)
		{
			DFS_stack.pop();
			if (!DFS_stack.empty()) {
				Edge *top = DFS_stack.top();
				if (top == edge);
				else DFS_stack.push(edge);
			}
			else DFS_stack.push(edge);
			// ertex_1已经访问，另一点还没访问，则访问该点，并且以这点出发深搜下一步去访问path2
			if (Mvisited[edge->vertex_1] == 1 && !Mvisited[edge->vertex_2])//&& edge->mark == 0
			{
				cout << MG.vertex[edge->vertex_2].info << "*";
				out = MG.vertex[edge->vertex_2].info;
				tmpinfo = MG.vertex[edge->vertex_1].info;

				Mvisited[edge->vertex_2] = 1;
				edge->mark = 2;
				DFS_stack.push(MG.vertex[edge->vertex_2].firstout);

			} // ertex_2已经访问，另一点还没访问，则访问该点，并且以这点出发深搜下一步去访问path1
			else if (Mvisited[edge->vertex_2] == 1 && !Mvisited[edge->vertex_1])//&& edge->mark == 0
			{
				cout << MG.vertex[edge->vertex_1].info << "*";
				out = MG.vertex[edge->vertex_1].info;
				tmpinfo = MG.vertex[edge->vertex_2].info;

				Mvisited[edge->vertex_1] = 1;
				edge->mark = 1;
				DFS_stack.push(MG.vertex[edge->vertex_1].firstout);
			}//两点都已经被访问，需要访问path2并且path2还没被访问
			else if (edge->mark == 2 && edge->mark_2)//
			{
				edge->mark_2 = false;
				DFS_stack.push(edge->path_2);
			}//两点都已经被访问，需要访问path1并且path1还没被访问
			else if (edge->mark == 1 && edge->mark_1)//
			{
				edge->mark_1 = false;
				DFS_stack.push(edge->path_1);
			}//两点都已经被访问，path1还没被访问(回溯)********
			else if ((edge->mark_1 || edge->mark_2)
				&& Mvisited[edge->vertex_1] && Mvisited[edge->vertex_2]) {
				DFS_stack.pop();//两个点已经访问过 就没必要压栈了 直接delete
				if (DFS_stack.empty()) DFS_stack.push(edge);//以防空了，出现错误
				Edge* tmp = DFS_stack.top();
				int a = tmp->vertex_1;
				int b = tmp->vertex_2;
				if (a == edge->vertex_1 || b == edge->vertex_1) {
					if (edge->mark_1) {
						edge->mark_1 = false;
						edge->mark = 1;
						Edge* ttmp = edge->path_1;
						while (ttmp) {
							// 到其他跟他邻接的有效边
							if (ttmp->mark || Mvisited[ttmp->vertex_1] && Mvisited[ttmp->vertex_2]) {
								(edge->vertex_1 == ttmp->vertex_1) ? (ttmp = ttmp->path_1) : (ttmp = ttmp->path_2);
							}
							else break;
						}
						if (ttmp) DFS_stack.push(ttmp);
					}
					else edge->mark = 2;//不加这句 会死循环
				}
				else //if (a == edge->vertex_2 || b == edge->vertex_2)
				{
					if (edge->mark_2) {
						edge->mark_2 = false;
						edge->mark = 2;
						Edge* ttmp = edge->path_2;
						while (ttmp) {
							if (ttmp->mark) {
								(edge->vertex_2 == ttmp->vertex_1) ? (ttmp = ttmp->path_1) : (ttmp = ttmp->path_2);
							}
							else break;
						}
						if (ttmp) DFS_stack.push(ttmp);
					}
					else edge->mark = 1;
				}
			}
			else if (!DFS_stack.empty())
				DFS_stack.pop();
			while (Dtree&&Dtree->data != tmpinfo)//回溯
				Dtree = Dtree->parent;
			if (Dtree&&tmpinfo != out) {//插入
				Dtree->Child[Dtree->degree] = new Tree;
				Tree *tmp = Dtree->Child[Dtree->degree];
				tmp->data = out;
				tmpinfo = out;
				tmp->parent = Dtree;
				Dtree->degree++;
				Dtree = tmp;
				Dtree->degree = 0;
			}
		}
		else DFS_stack.pop();
	}
}

void BFS_Search(const MGraph mG, int v)
{
	for (int i = 0; i < MG.vex; i++)
	{
		Mvisited[i] = 0;
		MG.vertex[i].firstout->mark = 0;
		MG.vertex[i].firstout->mark_1 = true;
		MG.vertex[i].firstout->mark_2 = true;
	}
	queue<int> BFS_queue;
	queue<Tree*> Bfstree_queue;
	Mvisited[v] = 1;
	cout << MG.vertex[v].info << "*";

	MB_Tree = new Tree;
	Tree* Btree = MB_Tree;
	Btree->data = MG.vertex[v].info;
	Btree->parent = NULL;
	Btree->degree = 0;

	BFS_queue.push(v);
	Bfstree_queue.push(Btree);
	while (!BFS_queue.empty())
	{
		int temp;
		temp = BFS_queue.front();
		Btree = Bfstree_queue.front();
		BFS_queue.pop();
		Bfstree_queue.pop();

		Edge *next = MG.vertex[temp].firstout;
		while (next)
		{
			// 到依附temp点的边，访问另一点并压入队列，并顺着依附边不断找与temp点相关的边，直到依附边为NULL
			if (temp == next->vertex_1)//因为图是无向的，所以要判断该点在多重邻接表中是v1还是v2的位置
			{
				if (!Mvisited[next->vertex_2])//另一个点没有被访问，访问该点
				{
					Mvisited[next->vertex_2] = 1;
					cout << MG.vertex[next->vertex_2].info << "*";
					//cout << 12 << endl;
					Btree->Child[Btree->degree] = new Tree;
					Tree *tmp = Btree->Child[Btree->degree];
					tmp->data = MG.vertex[next->vertex_2].info;
					tmp->parent = Btree;
					tmp->degree = 0;
					Bfstree_queue.push(tmp);
					Btree->degree++;

					BFS_queue.push(next->vertex_2);
					next = next->path_1;
				}
				else
				{
					next = next->path_1;//就沿着该点进行访问
				}
			}
			else
			{
				if (!Mvisited[next->vertex_1])
				{
					Mvisited[next->vertex_1] = 1;
					cout << MG.vertex[next->vertex_1].info << "*";

					Btree->Child[Btree->degree] = new Tree;
					Tree *tmp = Btree->Child[Btree->degree];
					tmp->data = MG.vertex[next->vertex_1].info;
					tmp->parent = Btree;
					tmp->degree = 0;
					Bfstree_queue.push(tmp);
					Btree->degree++;

					BFS_queue.push(next->vertex_1);
					next = next->path_2;
				}
				else
				{
					next = next->path_2;
				}
			}
		}
	}
}

//**************************************************************************
//树的三种遍历方式
void Inorder(Tree* e) {
	if (e->degree == 0) {
		cout << e->data << " ";
		return;
	}
	if (e) {
		Inorder(e->Child[0]);
		cout << e->data << " ";
		for (int i = 1; i < e->degree; i++) {
			Inorder(e->Child[i]);
		}
	}
}
void Preorder(Tree* e) {
	if (e->degree == 0) {
		cout << e->data << " ";
		return;
	}
	if (e) {
		cout << e->data << " ";
		for (int i = 0; i < e->degree; i++) {
			Preorder(e->Child[i]);
		}
	}
}
void Postorder(Tree* e) {
	if (e->degree == 0) {
		cout << e->data << " ";
		return;
	}
	if (e) {
		for (int i = 0; i < e->degree; i++) {
			Postorder(e->Child[i]);
		}
		cout << e->data << " ";
	}
}
//输出边集
void EdgeSet(Tree *e)
{
	if (e->degree == 0)
		return;

	if (e) {
		for (int i = 0; i < e->degree; i++) {
			cout << "<" << e->data << "," << e->Child[i]->data << "> ";
		}
		for (int i = 0; i < e->degree; i++)
		{
			EdgeSet(e->Child[i]);
		}
	}
}

//Spanning Tree
void SDTS(Tree *e) {
	setred();
	cout << "      Inorder" << endl;
	setwhite();
	Inorder(e);
	cout << endl;
	setred();
	cout << "      Preorder" << endl;
	setwhite();
	Preorder(e);
	cout << endl;
	setred();
	cout << "      Postorder" << endl;
	setwhite();
	Postorder(e);
	cout << endl;
}
int main()
{
	Create();
	cout << "The first vertex:" << endl;
	string Start_Point;
	int n;
	cin >> Start_Point;
	n = Locate(G, Start_Point);
	setyellow();
	cout << "Implemented with Adjacency List : " << endl;
	setred();
	cout << "      Depth First Search:" << endl;
	setwhite();
	DFS(G, n);
	cout << endl;
	setred();
	cout << "      Breadth First Search:" << endl;
	setwhite();
	BFS(G, n);
	cout << endl << endl;

	setyellow();
	cout << "Depth Spanning tree:" << endl;
	setwhite();
	SDTS(D_Tree);
	cout << endl << endl;
	setyellow();
	cout << "Breadth Spanning tree:" << endl;
	setwhite();
	SDTS(B_Tree);
	cout << endl << endl;

	setyellow();
	cout << "Implemented with Adjacency Multi-List : " << endl;

	setred();
	cout << "      Depth First Search:" << endl;
	setwhite();
	DFS_Search(MG, n);
	cout << endl;

	setred();
	cout << "      Breadth First Search:" << endl;
	setwhite();
	BFS_Search(MG, n);
	cout << endl << endl << endl;

	setyellow();
	cout << "Depth Spanning tree:" << endl;
	setwhite();
	SDTS(MD_Tree);
	cout << endl;
	cout << endl;

	setyellow();
	cout << "Breadth Spanning tree:" << endl;
	setwhite();
	SDTS(MB_Tree);
	cout << endl << endl;

	setyellow();
	cout << "The DFS spanning tree's edge set:" << endl;
	setwhite();
	EdgeSet(MD_Tree);
	cout << endl << endl;

	setyellow();
	cout << "The BFS spanning tree's edge set:" << endl;
	setwhite();
	EdgeSet(MB_Tree);
	cout << endl << endl;


	system("PAUSE");
}
