#include<iostream>//���룬�����
#include<string>//STL�е��ַ�������
#include<queue>//STL�еĶ���������BFSʹ�ã�
#define MVNum 100//��󶥵���
typedef char VerTexType;//�������������Ϊchar
typedef int ArcType;//�ߵ���������Ϊint
using namespace std;//ʹ�ñ�׼�����ռ�
struct ArcNode//�ڽӱ�ı߽��
{
	ArcNode()//Ĭ�Ϲ��캯��
	{
		this->nextarc = NULL;
	}
	int adjvex;//ָ�򶥵��λ��
	ArcNode* nextarc;//ָ����һ���ߵ�ָ��
};
struct VNode//�ڽӱ�Ķ���
{
	VNode()
	{
		this->firstarc = NULL;
	}
	VerTexType data;//�����������
	ArcNode* firstarc;//ָ���һ�������ߵ�ָ��
};

class Graph//����ͼ�ࣨ�����ߴ洢�����
{
public:
	Graph() //ͼ���޲ι��캯��
	{
		this->InitGraph();
	}
	~Graph() {};//ͼ����������
	void ShowMenu();//��ʾ�˵�
	string PrintStatus();//��ӡ״̬
	bool InitGraph();//ͼ����ʼ��
	int Get_Status();//��ȡ״̬���ӿڣ�
	//�����ڽӾ���ĳ�Ա����
	void initAMGraph();//��ʼ���ڽӾ���
	int LocateVex_AM(VerTexType vex);//���ڽӾ�����Ҷ���λ��
	void CreateAMGraph();//�����������ڽӾ���
	void Init_visited();//��ʼ��visited�������飬��ΪDFS����֮����ʹ��BFS��������Ҫ��ʼ��
	void DFS_TraverseAMGraph();//�ڽӾ����������ȱ���
	void DFSAMGraph(int i);//DFS�����ݹ麯��
	void BFS_TraverseAMGraph();//�ڽӾ���Ĺ�����ȱ���
	void Change_AMGraph_To_ALGraph();//�ı�洢�ṹ���ڽӾ���->�ڽӱ�
	void PrintAMGraph();//��ӡ�������ڽӾ���
	//�����ڽӱ�ĳ�Ա����
	void initALGraph();//��ʼ���ڽӱ�
	int LocateVex_AL(VerTexType vex);//���ڽӱ��в��Ҷ���λ��
	void CreatALGraph();//�����ڽӱ�
	void PrintALGraph();//��ӡ�ڽӱ�
	void DFS_TraverseALMGraph();//�ڽӱ��������ȱ���
	void DFSALGraph(int i);//�ڽӱ��������ȵݹ麯��
	void BFS_TraverseALGraph();//�ڽӱ������ȱ���
	void Change_ALGraph_To_AMGraph();//�ı�洢�ṹ���ڽӱ�->�ڽӾ���
private://���ö�̬�洢
	//�ڽӾ���洢��
	VerTexType* vexs;//�ڽӾ���Ķ����
	ArcType** arcs;//�ڽӾ���
	//�ڽӱ�洢��
	VNode* vertices;//�ڽӱ�
	//��������
	int vexnum;//������
	int arcnum;//����
	int storage_status;//�洢״̬��-1����״̬��0���ڽӾ���״̬��1���ڽӱ�״̬
	bool* visited;//��������
};
string Graph::PrintStatus()//��ӡ״̬
{
	if (this->storage_status == -1)
	{
		return "��";
	}
	else if (this->storage_status == 0)
	{
		return "�ڽӾ���";
	}
	else if (this->storage_status == 1)
	{
		return "�ڽӱ�";
	}
}
void Graph::ShowMenu()//���˵�
{
	cout << "��ǰ�洢�ṹ��" << PrintStatus() << endl;//���ú�����ʽ����֤��ʾ��Ϣ��ʱ����
	cout << "   *************************" << endl;
	cout << "   *  1������ͼ���ڽӾ���*" << endl;
	cout << "   *                       *" << endl;
	cout << "   *  2������ͼ���ڽӱ�  *" << endl;
	cout << "   *                       *" << endl;
	cout << "   *  3��������ȱ���ͼ    *" << endl;
	cout << "   *                       *" << endl;
	cout << "   *  4��������ȱ���ͼ    *" << endl;
	cout << "   *                       *" << endl;
	cout << "   *  5��ͼ�Ĵ洢�ṹת��  *" << endl;
	cout << "   *                       *" << endl;
	cout << "   *  6����     ʼ     ��  *" << endl;
	cout << "   *                       *" << endl;
	cout << "   *  0����           ��   *" << endl;
	cout << "   *************************" << endl;
	cout << "����������ѡ�";
}
bool Graph::InitGraph()
{
	this->storage_status = -1;//Ĭ��״̬Ϊ��״̬
	this->arcnum = this->vexnum = 0;//�������ͱ���Ĭ��Ϊ0
	this->vexs = new VerTexType[MVNum];//�����µĶ����
	this->visited = new bool[MVNum];//��������DFS����
	for (int i = 0; i < MVNum; i++)//��ʼ���������飨�ڽӾ�����ڽӱ��DFS��BFS�����õ�����������飬Ҫע�⼰ʱ��ʼ����
	{
		this->visited[i] = 0;
	}
	this->arcs = new ArcType * [MVNum];//�����µ��ڽӾ���
	for (int i = 0; i < MVNum; i++)
	{
		this->arcs[i] = new ArcType[MVNum];//����ָ����Ϊ��ά����
	}
	this->vertices = new VNode[MVNum];//�����µ��ڽӱ�
	if (this->arcnum == 0 && this->vexnum == 0 && this->vexs != NULL && this->arcs[0][0] != NULL && this->vertices != NULL)//�ж��Ƿ������˿ռ�
	{
		return true;//��ʼ���ɹ�
	}
	else
	{
		return false;//��ʼ��ʧ��
	}

}
int Graph::Get_Status()
{
	return this->storage_status;//����״̬
}

void Graph::initAMGraph()//��ʼ���ڽӾ���
{
	this->vexs = new VerTexType[MVNum];//�����µĶ����
	this->arcs = new ArcType * [MVNum];//�����µ��ڽӾ���
	for (int i = 0; i < MVNum; i++)
	{
		this->arcs[i] = new ArcType[MVNum];
	}
}
int Graph::LocateVex_AM(VerTexType vex)//��ȡ�ڽӾ����ж����λ��
{
	for (int i = 0; i < this->vexnum; i++)
	{
		if (this->vexs[i] == vex)
			return i;//����λ��
	}
}
void Graph::CreateAMGraph()//�����ڽӾ���
{
	cout << "�������ܶ��������ܱ���" << endl;
	cin >> this->vexnum >> this->arcnum;//���붥��ͱߵĸ���
	cout << "��������������Ϣ�����������(���붥��)" << endl;
	for (int i = 0; i < this->vexnum; i++)//���붥�����Ϣ
	{
		cin >> this->vexs[i];//��ÿ���������뵽�������
	}
	for (int i = 0; i < this->vexnum; i++)//��ʼ���ڽӾ���
	{
		for (int j = 0; j < this->vexnum; j++)
		{
			this->arcs[i][j] = 0;//Ĭ�϶Ͽ���0
		}
	}
	for (int i = 0; i < this->arcnum; i++)//���Ӷ���
	{
		VerTexType v1, v2;
		cout << "�������" << i + 1 << "���������Ķ��㣨�����������㣩" << endl;
		cin >> v1 >> v2;
		int locv1 = this->LocateVex_AM(v1);
		int locv2 = this->LocateVex_AM(v2);//�������������λ��
		this->arcs[locv1][locv2] = 1;//�����������λ�ö�Ӧ���ڽӾ���1
		this->arcs[locv2][locv1] = this->arcs[locv1][locv2];//����ͼ�Խ��ߵ���һ��ҲҪ����
	}
	this->storage_status = 0;//����״̬���ڽӾ���
	cout << "�����ɹ���" << endl;
}
void Graph::Init_visited()
{
	for (int i = 0; i < MVNum; i++)//��ʼ��visited��������
	{
		this->visited[i] = 0;
	}
}
void Graph::PrintAMGraph()//��ӡ�ڽӾ���
{
	cout << "�����";
	for (int i = 0; i < this->vexnum; i++)//�ȴ�ӡ�����
	{
		cout << this->vexs[i] << " ";
	}
	cout << endl << "�ڽӾ���" << endl;
	for (int i = 0; i < this->vexnum; i++)//��ӡ�ڽӾ���
	{
		for (int j = 0; j < this->vexnum; j++)
		{
			cout << this->arcs[i][j] << " ";
		}
		cout << endl;
	}
}
void Graph::DFS_TraverseAMGraph()//�ڽӾ����DFS�㷨��������
{
	for (int i = 0; i < this->vexnum; i++)//�Զ�������ÿ�����㶼Ҫ����
	{
		if (!visited[i])//��֤���ظ�������ʹ��visited���飬��¼�������Ķ���
		{
			this->DFSAMGraph(i);//��ʼ��ÿ������ݹ�
		}
	}
}
void Graph::DFSAMGraph(int i)//�ڽӾ����DFS�㷨���ݹ麯��
{
	cout << this->vexs[i] << " ";//�ȴ�ӡ�ö���
	this->visited[i] = true;//���ҰѸö���Ķ�Ӧ��visited������true
	for (int j = 0; j < this->vexnum; j++)//���϶Ըö����������ıߵĶ������
	{
		if ((this->arcs[i][j] != 0) && (!this->visited[j]))//�����0,����Ͽ������һ����ܷ��ʹ������ܶԸö�����еݹ�
		{
			this->DFSAMGraph(j);//�����������
		}
	}
}
void Graph::BFS_TraverseAMGraph()//�ڽӾ����BFS�㷨
{
	queue<int>q;//������������
	this->visited[0] = 1;//������ӡ��һ�����㣬�ȰѸ��������visited[0]=1
	cout << this->vexs[0] << " ";//��ӡ��һ������
	q.push(0);//��һ���������
	while (!q.empty())//������в�Ϊ��
	{
		int v = q.front();//�Ѷ�ͷ�Ķ��㸳ֵ��v
		q.pop();//���ҳ���
		for (int i = 0; i < this->vexnum; i++)//�������ж���
		{
			if (this->arcs[v][i] == 1 && !visited[i])//����ߴ��ڣ���visited����û�м�¼�����Ǿʹ�ӡ
			{
				q.push(i);//����i���
				cout << this->vexs[i] << " ";//���ʶ���
				visited[i] = true;//���ʹ��ˣ�����
			}
		}
	}
	cout << endl;//����
}
void Graph::Change_AMGraph_To_ALGraph()//���ڽӾ���ת�����ڽӱ�
{
	this->initALGraph();//�ȳ�ʼ���ڽӱ�������ת���������ڳ��ռ�
	for (int i = 0; i < this->vexnum; i++)
	{
		this->vertices[i].data = this->vexs[i];//��ת�������
	}
	for (int i = 0; i < this->vexnum; i++)
	{
		for (int j = 0; j < this->vexnum; j++)
		{
			if (this->arcs[i][j] != 0)//�����ڽӾ���ıߣ����ڽӱ�ıߵ������������
			{
				ArcNode* s1 = new ArcNode;//������ͷ������������β��׷��
				s1->adjvex = j;
				s1->nextarc = this->vertices[i].firstarc;
				this->vertices[i].firstarc = s1;
			}
		}
	}
	this->storage_status = 1;//����״̬
}

void Graph::initALGraph()//��ʼ���ڽӱ�
{
	this->vertices = new VNode[MVNum];//�����µ��ڽӱ�
}
int Graph::LocateVex_AL(VerTexType vex)//�����ڽӱ�Ķ��㣨���ظö����ڶ�����λ�ã�
{
	for (int i = 0; i < this->vexnum; i++)
	{
		if (vex == this->vertices[i].data)
		{
			return i;
		}
	}
}
void Graph::PrintALGraph()//��ӡ�ڽӱ�
{
	ArcNode* s1;//s1����ĳ�����㣬Ҫ���Ϸ��ʸö��������ڵı�
	cout << "Vexnum\t�����\t�ߵ�����" << endl;
	for (int i = 0; i < this->vexnum; i++)//Ҫ�������ж����Ķ���
	{
		cout << i << "\tv" << i + 1 << "=" << this->vertices[i].data << "\t";//��ӡ�����ĵ�һ���ߵĶ���
		s1 = this->vertices[i].firstarc;//s1����ߵ�������ĵ�һ�����ڱ�
		while (s1 != NULL)//�����s1���ϵ�����ֱ��ΪNULL
		{
			cout << s1->adjvex << "->";//��ӡ���ڵĵ�
			s1 = s1->nextarc;//����
		}
		cout << "NULL" << endl;//����
	}
}
void Graph::CreatALGraph()//�����ڽӱ�
{
	cout << "�������ܶ��������ܱ���" << endl;
	cin >> this->vexnum >> this->arcnum;//���붥�����ͱ���
	cout << "��������������Ϣ�����������(���붥��)" << endl;
	for (int i = 0; i < this->vexnum; i++)//���붥���
	{
		cin >> this->vertices[i].data;
	}
	for (int i = 0; i < this->arcnum; i++)//���ӱ�
	{
		VerTexType v1, v2;
		cout << "�������" << i + 1 << "���������Ķ��㣨�����������㣩" << endl;
		cin >> v1 >> v2;
		int loc1 = this->LocateVex_AL(v1);
		int loc2 = this->LocateVex_AL(v2);//��ȡv1��v2�ڶ�����λ��
		ArcNode* s1 = new ArcNode;//�����߽��
		s1->adjvex = loc2;//�߽�����ڵĶ���λ��
		s1->nextarc = this->vertices[loc1].firstarc;
		this->vertices[loc1].firstarc = s1;//����
		//�����������ͼ������Ҫ������һ��
		ArcNode* s2 = new ArcNode;
		s2->adjvex = loc1;
		s2->nextarc = this->vertices[loc2].firstarc;
		this->vertices[loc2].firstarc = s2;
	}
	this->storage_status = 1;//����״̬
	cout << "�����ɹ���" << endl;
}
void Graph::DFSALGraph(int i)//�ڽӱ��DFS�㷨���ݹ麯��
{
	ArcNode* s;
	cout << this->vertices[i].data << " ";//����������ĵ�һ���Ķ���
	visited[i] = true;//���������¼
	s = this->vertices[i].firstarc;//s�����һ���������ڵĵ�һ����
	while (s != NULL)//���s���������У���Ϊ�գ���һֱ����
	{
		if (this->visited[s->adjvex] != true)//���������û�м�¼�����Դ�ӡ
		{
			this->DFSALGraph(s->adjvex);//�ݹ飬�������
		}
		s = s->nextarc;//����
	}
}
void Graph::DFS_TraverseALMGraph()//�ڽӱ��DfS�㷨
{
	for (int i = 0; i < this->vexnum; i++)//��ÿ�����㶼����һ�Σ�������������м�¼��������
	{
		if (this->visited[i] != true)
		{
			this->DFSALGraph(i);//�ݹ����
		}
	}
}
void Graph::BFS_TraverseALGraph()//�ڽӱ��BFS�㷨
{
	ArcNode* p;
	queue<int>q;//��������
	cout << this->vertices[0].data << " ";//�ȱ�����һ������
	this->visited[0] = true;//���������¼��һ������
	q.push(0);//�ѵ�һ���������
	while (!q.empty())//������в�Ϊ��
	{
		int u = q.front();//��ȡ��ͷ����
		q.pop();//������
		for (p = this->vertices[u].firstarc; p != NULL; p = p->nextarc)//����ÿ���������ڵı�
		{
			if (!this->visited[p->adjvex])//�����������û�м�¼���ʹ�ӡ
			{
				cout << this->vertices[p->adjvex].data << " ";//����
				this->visited[p->adjvex] = true;//��¼
				q.push(p->adjvex);//���
			}
		}
	}
	cout << endl;//����
}
void Graph::Change_ALGraph_To_AMGraph()//�ڽӱ�ת���ڽӾ���
{
	this->initAMGraph();//�ȳ�ʼ���ڽӾ��󣬸�Ҫת���������ڳ��ռ�
	ArcNode* s;
	for (int i = 0; i < this->vexnum; i++)// ͷ����ת������
	{
		this->vexs[i] = this->vertices[i].data;//��ֵ
	}
	for (int i = 0; i < this->vexnum; i++)//�ڽӾ���ߵĳ�ʼ��
	{
		for (int j = 0; j < this->vexnum; j++)
		{
			this->arcs[i][j] = 0;
		}
	}
	for (int i = 0; i < this->vexnum; i++)//���ϱ���ÿ���������ڱߵĶ��㣬���ϸ��ڽӾ���ֵ
	{
		s = this->vertices[i].firstarc;
		while (s != NULL)
		{
			int adjvex = s->adjvex;
			this->arcs[i][adjvex] = 1;//���ڱ�
			s = s->nextarc;//����
		}

	}
	this->storage_status = 0;//����״̬
}

int main()
{
	Graph G;//��������
	int select;//�����û�ѡ��
	while (true)
	{
		G.ShowMenu();//չʾ�˵�
		cin >> select;//����ѡ��
		switch (select)
		{
		case 1:
			G.InitGraph();//�����ڽӾ���ʱ���ȳ�ʼ�����ÿ�֮ǰ�����ݣ���ֹ��ͻ
			G.CreateAMGraph();//�����ڽӾ���
			cout << "--------------------------" << endl;
			G.PrintAMGraph();//��ӡ�ڽӾ���
			system("pause");
			system("cls");
			break;
		case 2:
			G.InitGraph();//�����ڽӱ�ʱ���ȳ�ʼ�����ÿ�֮ǰ�����ݣ���ֹ��ͻ
			G.CreatALGraph();//�����ڽӱ�
			cout << "--------------------------" << endl;
			G.PrintALGraph();//��ӡ�ڽӱ�
			system("pause");
			system("cls");
			break;
		case 3:
			if (G.Get_Status() == -1)//�����-1��˵����״̬�����ɱ���
			{
				cout << "���ȴ���ͼ" << endl;
			}
			else
			{
				if (G.Get_Status() == 0)//��ǰΪ�ڽӾ���״̬����Ҫʹ���ڽӾ����DFS����
				{
					G.PrintAMGraph();
					cout << "--------------------------" << endl;
					cout << "�ڽӾ����DFS����Ϊ��" << endl;
					G.DFS_TraverseAMGraph();
					cout << endl;
				}
				else//��ǰ״̬Ϊ�ڽӱ�״̬����Ҫʹ���ڽӱ��DFS�㷨
				{
					G.PrintALGraph();
					cout << "--------------------------" << endl;
					cout << "�ڽӱ�ͬ�������Ľ�����ܴ��ڲ���" << endl;
					cout << "�ڽӱ��DFS����Ϊ��" << endl;
					G.DFS_TraverseALMGraph();
					cout << endl;
				}
				G.Init_visited();//��֤�´α�����visited�����ʼ��
			}
			system("pause");
			system("cls");
			break;
		case 4:
			if (G.Get_Status() == -1)//�����-1��˵����״̬�����ɱ���
			{
				cout << "���ȴ���ͼ" << endl;
			}
			else if (G.Get_Status() == 0)//��ǰΪ�ڽӾ���״̬����Ҫʹ���ڽӾ����BFS����
			{
				G.PrintAMGraph();
				cout << "--------------------------" << endl;
				cout << "�ڽӾ����BFS�ı���Ϊ��" << endl;
				G.BFS_TraverseAMGraph();
				G.Init_visited();//��֤�´α�����visited�����ʼ��
			}
			else//��ǰ״̬Ϊ�ڽӱ�״̬����Ҫʹ���ڽӱ��BFS�㷨
			{
				G.PrintALGraph();
				cout << "--------------------------" << endl;
				cout << "�ڽӱ�ͬ�������Ľ�����ܴ��ڲ���" << endl;
				cout << "�ڽӱ��BFS����Ϊ��" << endl;
				G.BFS_TraverseALGraph();
				G.Init_visited();//��֤�´α�����visited�����ʼ��
			}
			system("pause");
			system("cls");
			break;
		case 5:
			if (G.Get_Status() == -1) // ����� - 1��˵����״̬��������ת��
			{
				cout << "���ȴ���ͼ" << endl;
			}
			else
			{
				if (G.Get_Status() == 0)
				{
					G.PrintAMGraph();
					G.Change_AMGraph_To_ALGraph();
					cout << "--------------�ɹ�ת��Ϊ--------------" << endl;
					G.PrintALGraph();
				}
				else if (G.Get_Status() == 1)
				{
					G.PrintALGraph();
					G.Change_ALGraph_To_AMGraph();
					cout << "--------------�ɹ�ת��Ϊ--------------" << endl;
					G.PrintAMGraph();

				}
			}
			system("pause");
			system("cls");
			break;
		case 6:

			if (G.InitGraph())//�жϳ�ʼ���Ƿ�ɹ�
			{
				cout << "��ʼ���ɹ���" << endl;
			}
			else
			{
				cout << "��ʼ��ʧ�ܣ�" << endl;
			}
			system("pause");
			system("cls");
			break;
		default:
			cout << "��ӭ�´�ʹ�ã�" << endl;
			return 0;
			break;
		}
	}
}
