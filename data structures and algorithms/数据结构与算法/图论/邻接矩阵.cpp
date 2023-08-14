#include <stdio.h>
#include <string.h>
// ͼ�ṹ

#define WUXIANG 0
#define VERTEXS 6

struct Graph
{
	int vertex_num;        // �������
	int edge_num;          // �߸���
	char* pVertex;
	//int* ppEdge;     // ����һά�����ʾ��ά����
	int** ppEdge;      // �ö�̬��ά����

};

// ����ͼ����
Graph* createGraph();
// ��ʼ��ͼ����
void initGraph(Graph* g);
// ��ʼ��ͼ����
void initGraph(Graph* g, int vertex_num, int lines, char* str, int map[VERTEXS][VERTEXS]);
// �ͷ�ͼ����
void destroyGraph(Graph* g);
// ��ȡ�������ڵ��±�, ���û�뷵��-1 
int _getIdx(Graph* g, char c);
// ��ʾͼ
void show(Graph* g);

#if 0
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
	// �ͷ�ͼ����
	destroyGraph(g);
	while (1);
	return 0;
}
#endif

//����ͼ����
Graph* createGraph()
{
	Graph* graph = new Graph;
	graph->edge_num = graph->vertex_num = 0;
	graph->ppEdge = NULL;
	graph->pVertex = NULL;

	// ���� memset(grap, 0, sizeof(Graph))
	return graph;
}

// ��ʼ��ͼ����
void initGraph(Graph* g, int vertexs, int lines, char* str, int map[VERTEXS][VERTEXS])
{
	g->vertex_num = vertexs;
	g->edge_num = lines;
	// ���ڴ�
	g->pVertex = new char[g->vertex_num];  // ��Ŷ�����Ϣ��һά����

	// �ߵĶ�ά����
	g->ppEdge = new int* [g->vertex_num];
	for (int i = 0; i < g->vertex_num; i++)
	{
		g->ppEdge[i] = new int[g->vertex_num];
		memset(g->ppEdge[i], 0, sizeof(int) * vertexs);
	}

	memcpy(g->pVertex, str, vertexs);
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
	scanf_s("%d", &(g->vertex_num));
	printf("������ߵĸ���: ");
	scanf_s("%d", &(g->edge_num));

	// ���ڴ�
	g->pVertex = new char[g->vertex_num + 1];  // ��Ŷ�����Ϣ��һά����

	// �ߵĶ�ά����
	g->ppEdge = new int* [g->vertex_num];
	for (int i = 0; i < g->vertex_num; i++)
	{
		g->ppEdge[i] = new int[g->vertex_num];
		memset(g->ppEdge[i], 0, sizeof(int) * g->vertex_num);
	}

	// ��ֵ
	printf("�����붥��: ");
	scanf("%s", g->pVertex);

	char buff[5] = {0};
	int srcIdx, dstIdx;
	for (int i = 0; i < g->edge_num; i++)
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

//�ͷ�ͼ����
void destroyGraph(Graph* g)
{


}

int _getIdx(Graph* g, char c)
{
	for (int i = 0; i < g->vertex_num; i++)
	{
		if (c == g->pVertex[i]) return i;
	}
	return -1;
}

void show(Graph* g)
{
	for (int i = 0; i <= g->vertex_num; i++)
	{
		for (int j = 0; j <= g->vertex_num; j++)
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