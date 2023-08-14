#include <stdio.h>
#include <string.h>
#include <queue>
// ͼ�ṹ

#define WUXIANG 0
#define VERTEXS 6

struct Graph
{
	int vertexs;
	int edges;
	char* pVertex;
	//int* ppEdge;     // ����һά�����ʾ��ά����
	int** ppEdge;      // �ö�̬��ά����
};
// ����ͼ����
Graph* createGraph();
// ��ʼ��ͼ����
void initGraph(Graph* g);
// ��ʼ��ͼ����
void initGraph(Graph* g, int vertexs, int lines, char* str, int map[VERTEXS][VERTEXS]);
// �ͷ�ͼ����
void destroyGraph(Graph* g);
// ��ȡ�������ڵ��±�, ���û�뷵��-1
int _getIdx(Graph* g, char c);
// ��ʾͼ
//
void show(Graph* g);
// ͼ�ı���
void travers(Graph* g, char v, bool isDeep);
// ��ͼ��ĳ������ĵ�һ�����ڶ���, û�з���-1
int findFirstVertex(Graph* g, char v, bool isFind[VERTEXS]);
// ��ͼ��ĳ���������һ�����ڶ���, û�з���-1,��v�����idx�������һ������
int findNextVertex(Graph* g, char v, int idx);
// �����������
void dfs(Graph* g, char v, bool isFind[VERTEXS]);
// �����������
void bfs(Graph* g, char v, bool isFind[VERTEXS]);

int main(void)
{
	char buff[7] = "ABCDEF";
	int map[VERTEXS][VERTEXS] = {
		{0 ,0 ,1, 0, 0, 0},
		{0 ,0 ,1, 0, 0, 0},
		{1 ,1 ,0, 1, 1, 1},
		{0 ,0 ,1, 0, 0, 0},
		{0 ,0 ,1, 1, 0, 0},
		{0 ,0 ,1, 0, 0, 0},
	};

	// ����ͼ����
	Graph* g = createGraph();
	// ��ʼ��ͼ
//	initGraph(g);
	initGraph(g, VERTEXS, 6, buff, map);
	// ��ʾͼ
	show(g);
	//
	printf("\nDFS: ");
	travers(g, 'C', true);
	printf("\n");
	printf("BFS: ");
	travers(g, 'C', false);
	printf("\n");
	// �ͷ�ͼ����
	destroyGraph(g);
	//while (1);
	return 0;
}

//�ͷ�ͼ����
void destroyGraph(Graph* g)
{
	delete g;
}

//����ͼ����
Graph* createGraph()
{
	Graph* graph = new Graph;
	graph->edges = graph->vertexs = 0;
	graph->ppEdge = NULL;
	graph->pVertex = NULL;

	// ���� memset(grap, 0, sizeof(Graph))
	return graph;
}

// ��ʼ��ͼ����
void initGraph(Graph* g, int vertexs, int lines, char* str, int map[VERTEXS][VERTEXS])
{
	g->vertexs = vertexs;
	g->edges = lines;
	// ���ڴ�
	g->pVertex = new char[g->vertexs];  // ��Ŷ�����Ϣ��һά����

	// �ߵĶ�ά����
	g->ppEdge = new int* [g->vertexs];
	for (int i = 0; i < g->vertexs; i++)
	{
		g->ppEdge[i] = new int[g->vertexs];
		memset(g->ppEdge[i], 0, sizeof(int) * g->vertexs);
	}

	memcpy(g->pVertex, str, VERTEXS);
	for (int i = 0; i < VERTEXS; i++)
	{
		for (int j = 0; j < VERTEXS; j++)
		{
			g->ppEdge[i][j] = map[i][j];
		}
	}
}

// ��ʼ��ͼ����
void initGraph(Graph* g)
{
	printf("�����붥�����: ");
	scanf("%d", &(g->vertexs));
	printf("������ߵĸ���: ");
	scanf("%d", &(g->edges));

	// ���ڴ�
	g->pVertex = new char[g->vertexs + 1];  // ��Ŷ�����Ϣ��һά����

	// �ߵĶ�ά����
	g->ppEdge = new int* [g->vertexs];
	for (int i = 0; i < g->vertexs; i++)
	{
		g->ppEdge[i] = new int[g->vertexs];
		memset(g->ppEdge[i], 0, sizeof(int) * g->vertexs);
	}

	// ��ֵ
	printf("�����붥��: ");
	scanf("%s", g->pVertex);

	char buff[5] = {0};
	int srcIdx, dstIdx;
	for (int i = 0; i < g->edges; i++)
	{
		printf("�������%d����(A->B): ", i + 1);
		scanf("%s", buff);
		srcIdx = _getIdx(g, buff[0]);
		dstIdx = _getIdx(g, buff[3]);
		g->ppEdge[srcIdx][dstIdx] = 1;
#if WUXIANG
		// ���������ͼ,����һ�д���
		// g->ppEdge[dstIdx][srcIdx] = 1;
	}
#endif
	}
}

int _getIdx(Graph* g, char c)
{
	for (int i = 0; i < g->vertexs; i++)
	{
		if (c == g->pVertex[i]) return i;
	}
	return -1;
}

void show(Graph* g)
{
	for (int i = 0; i <= g->vertexs; i++)
	{
		for (int j = 0; j <= g->vertexs; j++)
		{
			if (i == 0 && j == 0)//���Ͻǿ���
				printf(" ");
			else if (i == 0)
			{
				printf("%c ", g->pVertex[j - 1]);
			}
			else if (j == 0)
				printf("%c ", g->pVertex[i - 1]);
			else
			{
				printf("%d ", g->ppEdge[i - 1][j - 1]);
			}
		}
		printf("\n");
	}
}

// ͼ����
void travers(Graph* g, char v, bool isDeep)
{
	bool isFind[VERTEXS] = {0};   // �洢�Ѿ��������Ķ���
	if (isDeep)
	{
		dfs(g, v, isFind);
	}
	else
	{
		bfs(g, v, isFind);
	}
	printf("\n");
}

// ��ͼ��ĳ������ĵ�һ�����ڶ���, û�з���-1  // cahr v ����
int findFirstVertex(Graph* g, char v, bool isFind[VERTEXS])
{
	int n = _getIdx(g, v);
	for (int i = 0; i < VERTEXS; i++)
	{
		if (isFind[i])
			continue;
		if (1 == g->ppEdge[n][i])
			return i;
	}
	return -1;
}

// ����;ĳ���������һ�����ڶ���, û�з���-1
//��v�����idx�������һ������
int findNextVertex(Graph* g, char v, int idx)
{
	int n = _getIdx(g, v);
	for (int i = idx + 1; i < VERTEXS; i++)
	{
		if (1 == g->ppEdge[n][i])
			return i;
	}
	return -1;
}

// �������
void dfs(Graph* g, char v, bool isFind[VERTEXS])
{
	//��v�ĵ�һ�����ڶ���x��������x�ĵ�һ�����ڶ���Dֱ��û�����ڶ���ͽ���
	int cur = _getIdx(g, v);
	isFind[cur] = true;  // ����ҹ�
	printf("%c", v);
	int nextIdx = findFirstVertex(g, v, isFind);  // ��ȡ��ǰ����ĵ�һ�����ڶ���

	// Ȼ��һ��·�ߵ���
	while (nextIdx != -1) //��·
	{
		if (!isFind[nextIdx]) //һ������û�б�����,��û���߹�
		{
			//printf("%c", g->pVertex[nextIdx]);
			//isFind[nextIdx] = true;
			dfs(g, g->pVertex[nextIdx], isFind);
		}
		// �߹�
		//��v����һ�����ڶ��㣬һֱ�����������
		nextIdx = findNextVertex(g, v, nextIdx);
	}
}

// �������(��������)
void bfs(Graph* g, char v, bool isFind[VERTEXS])
{
	using namespace std;
	queue <int> q;
	q.push(_getIdx(g, v));
	isFind[_getIdx(g, v)] = true;
	printf("%c", v);

	int headIdex;
	int idx;
	//  ȥ��
	while (!q.empty())
	{
		headIdex = q.front();
		q.pop();

		int idx = findFirstVertex(g, g->pVertex[headIdex], isFind);  // �ҵ�һ������
		while (idx != -1)
		{
			if (!isFind[idx])
			{
				isFind[idx] = true;
				printf("%c", g->pVertex[idx]);
				q.push(idx);
			}
			idx = findNextVertex(g, g->pVertex[headIdex], idx);  // ����һ��
		}
	}
}