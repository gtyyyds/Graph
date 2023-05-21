#include<iostream>//输入，输出流
#include<string>//STL中的字符串容器
#include<queue>//STL中的队列容器（BFS使用）
#define MVNum 100//最大顶点数
typedef char VerTexType;//顶点的数据类型为char
typedef int ArcType;//边的数据类型为int
using namespace std;//使用标准命名空间
struct ArcNode//邻接表的边结点
{
	ArcNode()//默认构造函数
	{
		this->nextarc = NULL;
	}
	int adjvex;//指向顶点的位置
	ArcNode* nextarc;//指向下一条边的指针
};
struct VNode//邻接表的顶点
{
	VNode()
	{
		this->firstarc = NULL;
	}
	VerTexType data;//顶点的数据域
	ArcNode* firstarc;//指向第一条依附边的指针
};

class Graph//创建图类（含两者存储结果）
{
public:
	Graph() //图的无参构造函数
	{
		this->InitGraph();
	}
	~Graph() {};//图的析构函数
	void ShowMenu();//显示菜单
	string PrintStatus();//打印状态
	bool InitGraph();//图都初始化
	int Get_Status();//获取状态（接口）
	//关于邻接矩阵的成员函数
	void initAMGraph();//初始化邻接矩阵
	int LocateVex_AM(VerTexType vex);//在邻接矩阵查找顶点位置
	void CreateAMGraph();//创建顶点表和邻接矩阵
	void Init_visited();//初始化visited辅助数组，因为DFS遍历之后，若使用BFS遍历，需要初始化
	void DFS_TraverseAMGraph();//邻接矩阵的深度优先遍历
	void DFSAMGraph(int i);//DFS遍历递归函数
	void BFS_TraverseAMGraph();//邻接矩阵的广度优先遍历
	void Change_AMGraph_To_ALGraph();//改变存储结构（邻接矩阵->邻接表）
	void PrintAMGraph();//打印顶点表和邻接矩阵
	//关于邻接表的成员函数
	void initALGraph();//初始化邻接表
	int LocateVex_AL(VerTexType vex);//在邻接表中查找顶点位置
	void CreatALGraph();//创建邻接表
	void PrintALGraph();//打印邻接表
	void DFS_TraverseALMGraph();//邻接表的深度优先遍历
	void DFSALGraph(int i);//邻接表的深度优先递归函数
	void BFS_TraverseALGraph();//邻接表广度优先遍历
	void Change_ALGraph_To_AMGraph();//改变存储结构（邻接表->邻接矩阵）
private://采用动态存储
	//邻接矩阵存储区
	VerTexType* vexs;//邻接矩阵的顶点表
	ArcType** arcs;//邻接矩阵
	//邻接表存储区
	VNode* vertices;//邻接表
	//共有区域
	int vexnum;//顶点数
	int arcnum;//边数
	int storage_status;//存储状态：-1是无状态；0是邻接矩阵状态；1是邻接表状态
	bool* visited;//辅助数组
};
string Graph::PrintStatus()//打印状态
{
	if (this->storage_status == -1)
	{
		return "无";
	}
	else if (this->storage_status == 0)
	{
		return "邻接矩阵";
	}
	else if (this->storage_status == 1)
	{
		return "邻接表";
	}
}
void Graph::ShowMenu()//主菜单
{
	cout << "当前存储结构：" << PrintStatus() << endl;//采用函数方式，保证提示信息及时更新
	cout << "   *************************" << endl;
	cout << "   *  1、创建图（邻接矩阵）*" << endl;
	cout << "   *                       *" << endl;
	cout << "   *  2、创建图（邻接表）  *" << endl;
	cout << "   *                       *" << endl;
	cout << "   *  3、深度优先遍历图    *" << endl;
	cout << "   *                       *" << endl;
	cout << "   *  4、广度优先遍历图    *" << endl;
	cout << "   *                       *" << endl;
	cout << "   *  5、图的存储结构转换  *" << endl;
	cout << "   *                       *" << endl;
	cout << "   *  6、初     始     化  *" << endl;
	cout << "   *                       *" << endl;
	cout << "   *  0、退           出   *" << endl;
	cout << "   *************************" << endl;
	cout << "请输入您的选项：";
}
bool Graph::InitGraph()
{
	this->storage_status = -1;//默认状态为无状态
	this->arcnum = this->vexnum = 0;//顶点数和边数默认为0
	this->vexs = new VerTexType[MVNum];//创建新的顶点表
	this->visited = new bool[MVNum];//创建辅助DFS数组
	for (int i = 0; i < MVNum; i++)//初始化辅助数组（邻接矩阵和邻接表的DFS和BFS都会用到这个辅助数组，要注意及时初始化）
	{
		this->visited[i] = 0;
	}
	this->arcs = new ArcType * [MVNum];//创建新的邻接矩阵
	for (int i = 0; i < MVNum; i++)
	{
		this->arcs[i] = new ArcType[MVNum];//二级指针作为二维数组
	}
	this->vertices = new VNode[MVNum];//创建新的邻接表
	if (this->arcnum == 0 && this->vexnum == 0 && this->vexs != NULL && this->arcs[0][0] != NULL && this->vertices != NULL)//判断是否都申请了空间
	{
		return true;//初始化成功
	}
	else
	{
		return false;//初始化失败
	}

}
int Graph::Get_Status()
{
	return this->storage_status;//返回状态
}

void Graph::initAMGraph()//初始化邻接矩阵
{
	this->vexs = new VerTexType[MVNum];//创建新的顶点表
	this->arcs = new ArcType * [MVNum];//创建新的邻接矩阵
	for (int i = 0; i < MVNum; i++)
	{
		this->arcs[i] = new ArcType[MVNum];
	}
}
int Graph::LocateVex_AM(VerTexType vex)//获取邻接矩阵中顶点的位置
{
	for (int i = 0; i < this->vexnum; i++)
	{
		if (this->vexs[i] == vex)
			return i;//返回位置
	}
}
void Graph::CreateAMGraph()//创建邻接矩阵
{
	cout << "请输入总顶点数和总边数" << endl;
	cin >> this->vexnum >> this->arcnum;//输入顶点和边的个数
	cout << "请输入各顶点的信息（创建顶点表）(输入顶点)" << endl;
	for (int i = 0; i < this->vexnum; i++)//输入顶点表信息
	{
		cin >> this->vexs[i];//把每个顶点输入到顶点表中
	}
	for (int i = 0; i < this->vexnum; i++)//初始化邻接矩阵
	{
		for (int j = 0; j < this->vexnum; j++)
		{
			this->arcs[i][j] = 0;//默认断开，0
		}
	}
	for (int i = 0; i < this->arcnum; i++)//连接顶点
	{
		VerTexType v1, v2;
		cout << "请输入第" << i + 1 << "条边依附的顶点（输入两个顶点）" << endl;
		cin >> v1 >> v2;
		int locv1 = this->LocateVex_AM(v1);
		int locv2 = this->LocateVex_AM(v2);//查找两个顶点的位置
		this->arcs[locv1][locv2] = 1;//把两个顶点的位置对应的邻接矩阵赋1
		this->arcs[locv2][locv1] = this->arcs[locv1][locv2];//无向图对角线的另一半也要连接
	}
	this->storage_status = 0;//更新状态，邻接矩阵
	cout << "创建成功！" << endl;
}
void Graph::Init_visited()
{
	for (int i = 0; i < MVNum; i++)//初始化visited辅助数组
	{
		this->visited[i] = 0;
	}
}
void Graph::PrintAMGraph()//打印邻接矩阵
{
	cout << "顶点表：";
	for (int i = 0; i < this->vexnum; i++)//先打印顶点表
	{
		cout << this->vexs[i] << " ";
	}
	cout << endl << "邻接矩阵：" << endl;
	for (int i = 0; i < this->vexnum; i++)//打印邻接矩阵
	{
		for (int j = 0; j < this->vexnum; j++)
		{
			cout << this->arcs[i][j] << " ";
		}
		cout << endl;
	}
}
void Graph::DFS_TraverseAMGraph()//邻接矩阵的DFS算法，主函数
{
	for (int i = 0; i < this->vexnum; i++)//对顶点表表中每个顶点都要遍历
	{
		if (!visited[i])//保证不重复遍历，使用visited数组，记录遍历过的顶点
		{
			this->DFSAMGraph(i);//开始对每个顶点递归
		}
	}
}
void Graph::DFSAMGraph(int i)//邻接矩阵的DFS算法，递归函数
{
	cout << this->vexs[i] << " ";//先打印该顶点
	this->visited[i] = true;//并且把该顶点的对应的visited数组置true
	for (int j = 0; j < this->vexnum; j++)//不断对该顶点所相连的边的顶点访问
	{
		if ((this->arcs[i][j] != 0) && (!this->visited[j]))//如果是0,代表断开，而且还不能访问过，才能对该顶点进行递归
		{
			this->DFSAMGraph(j);//不断深入访问
		}
	}
}
void Graph::BFS_TraverseAMGraph()//邻接矩阵的BFS算法
{
	queue<int>q;//创建队列容器
	this->visited[0] = 1;//即将打印第一个顶点，先把辅助数组的visited[0]=1
	cout << this->vexs[0] << " ";//打印第一个顶点
	q.push(0);//第一个顶点入队
	while (!q.empty())//如果队列不为空
	{
		int v = q.front();//把队头的顶点赋值给v
		q.pop();//并且出队
		for (int i = 0; i < this->vexnum; i++)//访问所有顶点
		{
			if (this->arcs[v][i] == 1 && !visited[i])//如果边存在，且visited数组没有记录过，那就打印
			{
				q.push(i);//先让i入队
				cout << this->vexs[i] << " ";//访问顶点
				visited[i] = true;//访问过了，置真
			}
		}
	}
	cout << endl;//换行
}
void Graph::Change_AMGraph_To_ALGraph()//把邻接矩阵转换成邻接表
{
	this->initALGraph();//先初始化邻接表，给即将转换的数据腾出空间
	for (int i = 0; i < this->vexnum; i++)
	{
		this->vertices[i].data = this->vexs[i];//先转换顶点表
	}
	for (int i = 0; i < this->vexnum; i++)
	{
		for (int j = 0; j < this->vexnum; j++)
		{
			if (this->arcs[i][j] != 0)//根据邻接矩阵的边，对邻接表的边的链表进行链接
			{
				ArcNode* s1 = new ArcNode;//这里是头插入链表，不是尾部追加
				s1->adjvex = j;
				s1->nextarc = this->vertices[i].firstarc;
				this->vertices[i].firstarc = s1;
			}
		}
	}
	this->storage_status = 1;//更新状态
}

void Graph::initALGraph()//初始化邻接表
{
	this->vertices = new VNode[MVNum];//创建新的邻接表
}
int Graph::LocateVex_AL(VerTexType vex)//查找邻接表的顶点（返回该顶点在顶点表的位置）
{
	for (int i = 0; i < this->vexnum; i++)
	{
		if (vex == this->vertices[i].data)
		{
			return i;
		}
	}
}
void Graph::PrintALGraph()//打印邻接表
{
	ArcNode* s1;//s1代表某个顶点，要不断访问该顶点所相邻的边
	cout << "Vexnum\t顶点表\t边的链表" << endl;
	for (int i = 0; i < this->vexnum; i++)//要遍历所有顶点表的顶点
	{
		cout << i << "\tv" << i + 1 << "=" << this->vertices[i].data << "\t";//打印顶点表的第一条边的顶点
		s1 = this->vertices[i].firstarc;//s1代表边的链表里的第一个相邻边
		while (s1 != NULL)//下面对s1不断迭代，直到为NULL
		{
			cout << s1->adjvex << "->";//打印相邻的点
			s1 = s1->nextarc;//迭代
		}
		cout << "NULL" << endl;//结束
	}
}
void Graph::CreatALGraph()//创建邻接表
{
	cout << "请输入总顶点数和总边数" << endl;
	cin >> this->vexnum >> this->arcnum;//输入顶点数和边数
	cout << "请输入各顶点的信息（创建顶点表）(输入顶点)" << endl;
	for (int i = 0; i < this->vexnum; i++)//输入顶点表
	{
		cin >> this->vertices[i].data;
	}
	for (int i = 0; i < this->arcnum; i++)//连接边
	{
		VerTexType v1, v2;
		cout << "请输入第" << i + 1 << "条边依附的顶点（输入两个顶点）" << endl;
		cin >> v1 >> v2;
		int loc1 = this->LocateVex_AL(v1);
		int loc2 = this->LocateVex_AL(v2);//获取v1，v2在顶点表的位置
		ArcNode* s1 = new ArcNode;//创建边结点
		s1->adjvex = loc2;//边结点相邻的顶点位置
		s1->nextarc = this->vertices[loc1].firstarc;
		this->vertices[loc1].firstarc = s1;//插入
		//由于是无向的图，所以要链接另一边
		ArcNode* s2 = new ArcNode;
		s2->adjvex = loc1;
		s2->nextarc = this->vertices[loc2].firstarc;
		this->vertices[loc2].firstarc = s2;
	}
	this->storage_status = 1;//更新状态
	cout << "创建成功！" << endl;
}
void Graph::DFSALGraph(int i)//邻接表的DFS算法，递归函数
{
	ArcNode* s;
	cout << this->vertices[i].data << " ";//先输出顶点表的第一个的顶点
	visited[i] = true;//辅助数组记录
	s = this->vertices[i].firstarc;//s代表第一个顶点相邻的第一条边
	while (s != NULL)//如果s迭代过程中，不为空，则一直迭代
	{
		if (this->visited[s->adjvex] != true)//辅助数组的没有记录，可以打印
		{
			this->DFSALGraph(s->adjvex);//递归，遍历深度
		}
		s = s->nextarc;//迭代
	}
}
void Graph::DFS_TraverseALMGraph()//邻接表的DfS算法
{
	for (int i = 0; i < this->vexnum; i++)//把每个顶点都遍历一次，如果辅助数组有记录，则跳过
	{
		if (this->visited[i] != true)
		{
			this->DFSALGraph(i);//递归遍历
		}
	}
}
void Graph::BFS_TraverseALGraph()//邻接表的BFS算法
{
	ArcNode* p;
	queue<int>q;//队列容器
	cout << this->vertices[0].data << " ";//先遍历第一个顶点
	this->visited[0] = true;//辅助数组记录第一个顶点
	q.push(0);//把第一个顶点入队
	while (!q.empty())//如果队列不为空
	{
		int u = q.front();//获取队头顶点
		q.pop();//并出队
		for (p = this->vertices[u].firstarc; p != NULL; p = p->nextarc)//遍历每个顶点相邻的边
		{
			if (!this->visited[p->adjvex])//如果辅助数组没有记录，就打印
			{
				cout << this->vertices[p->adjvex].data << " ";//遍历
				this->visited[p->adjvex] = true;//记录
				q.push(p->adjvex);//入队
			}
		}
	}
	cout << endl;//换行
}
void Graph::Change_ALGraph_To_AMGraph()//邻接表转换邻接矩阵
{
	this->initAMGraph();//先初始化邻接矩阵，给要转换的数据腾出空间
	ArcNode* s;
	for (int i = 0; i < this->vexnum; i++)// 头顶点转移数据
	{
		this->vexs[i] = this->vertices[i].data;//赋值
	}
	for (int i = 0; i < this->vexnum; i++)//邻接矩阵边的初始化
	{
		for (int j = 0; j < this->vexnum; j++)
		{
			this->arcs[i][j] = 0;
		}
	}
	for (int i = 0; i < this->vexnum; i++)//不断遍历每个顶点相邻边的顶点，不断给邻接矩阵赋值
	{
		s = this->vertices[i].firstarc;
		while (s != NULL)
		{
			int adjvex = s->adjvex;
			this->arcs[i][adjvex] = 1;//存在边
			s = s->nextarc;//迭代
		}

	}
	this->storage_status = 0;//更新状态
}

int main()
{
	Graph G;//创建对象
	int select;//保存用户选择
	while (true)
	{
		G.ShowMenu();//展示菜单
		cin >> select;//输入选项
		switch (select)
		{
		case 1:
			G.InitGraph();//创建邻接矩阵时，先初始化，置空之前的数据，防止冲突
			G.CreateAMGraph();//创建邻接矩阵
			cout << "--------------------------" << endl;
			G.PrintAMGraph();//打印邻接矩阵
			system("pause");
			system("cls");
			break;
		case 2:
			G.InitGraph();//创建邻接表时，先初始化，置空之前的数据，防止冲突
			G.CreatALGraph();//创建邻接表
			cout << "--------------------------" << endl;
			G.PrintALGraph();//打印邻接表
			system("pause");
			system("cls");
			break;
		case 3:
			if (G.Get_Status() == -1)//如果是-1，说明无状态，不可遍历
			{
				cout << "请先创建图" << endl;
			}
			else
			{
				if (G.Get_Status() == 0)//当前为邻接矩阵状态，就要使用邻接矩阵的DFS遍历
				{
					G.PrintAMGraph();
					cout << "--------------------------" << endl;
					cout << "邻接矩阵的DFS遍历为：" << endl;
					G.DFS_TraverseAMGraph();
					cout << endl;
				}
				else//当前状态为邻接表状态，就要使用邻接表的DFS算法
				{
					G.PrintALGraph();
					cout << "--------------------------" << endl;
					cout << "邻接表不同，遍历的结果可能存在差异" << endl;
					cout << "邻接表的DFS遍历为：" << endl;
					G.DFS_TraverseALMGraph();
					cout << endl;
				}
				G.Init_visited();//保证下次遍历，visited必须初始化
			}
			system("pause");
			system("cls");
			break;
		case 4:
			if (G.Get_Status() == -1)//如果是-1，说明无状态，不可遍历
			{
				cout << "请先创建图" << endl;
			}
			else if (G.Get_Status() == 0)//当前为邻接矩阵状态，就要使用邻接矩阵的BFS遍历
			{
				G.PrintAMGraph();
				cout << "--------------------------" << endl;
				cout << "邻接矩阵的BFS的遍历为：" << endl;
				G.BFS_TraverseAMGraph();
				G.Init_visited();//保证下次遍历，visited必须初始化
			}
			else//当前状态为邻接表状态，就要使用邻接表的BFS算法
			{
				G.PrintALGraph();
				cout << "--------------------------" << endl;
				cout << "邻接表不同，遍历的结果可能存在差异" << endl;
				cout << "邻接表的BFS遍历为：" << endl;
				G.BFS_TraverseALGraph();
				G.Init_visited();//保证下次遍历，visited必须初始化
			}
			system("pause");
			system("cls");
			break;
		case 5:
			if (G.Get_Status() == -1) // 如果是 - 1，说明无状态，不可以转换
			{
				cout << "请先创建图" << endl;
			}
			else
			{
				if (G.Get_Status() == 0)
				{
					G.PrintAMGraph();
					G.Change_AMGraph_To_ALGraph();
					cout << "--------------成功转换为--------------" << endl;
					G.PrintALGraph();
				}
				else if (G.Get_Status() == 1)
				{
					G.PrintALGraph();
					G.Change_ALGraph_To_AMGraph();
					cout << "--------------成功转换为--------------" << endl;
					G.PrintAMGraph();

				}
			}
			system("pause");
			system("cls");
			break;
		case 6:

			if (G.InitGraph())//判断初始化是否成功
			{
				cout << "初始化成功！" << endl;
			}
			else
			{
				cout << "初始化失败！" << endl;
			}
			system("pause");
			system("cls");
			break;
		default:
			cout << "欢迎下次使用！" << endl;
			return 0;
			break;
		}
	}
}
