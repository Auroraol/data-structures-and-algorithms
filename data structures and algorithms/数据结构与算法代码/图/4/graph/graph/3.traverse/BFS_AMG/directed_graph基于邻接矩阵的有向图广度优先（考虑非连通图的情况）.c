#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define MAX 100

struct AMG_Graph
{
	int vex_num, edge_num;

	char Vex[MAX];
	int Edge[MAX][MAX];
};

struct AMG_Graph *Create_AMG_Graph(void);
void Show_AMG_Graph(struct AMG_Graph *graph);
int search_vex(struct AMG_Graph *graph, char c);
void BFS_AMG(struct AMG_Graph *graph);

int main(void)
{
	struct AMG_Graph *d_graph;

	d_graph = Create_AMG_Graph();
	Show_AMG_Graph(d_graph);

	printf("Traverse the graph through BFS:\n");  // ��ʾ��bfs�ķ�ʽ���� 
	BFS_AMG(d_graph); // �����ڽӾ���ı�������

	return 0;
}

struct AMG_Graph *Create_AMG_Graph(void)
{
	int i, j;
	char u, v;

	struct AMG_Graph *graph;

	graph = (struct AMG_Graph *)malloc(sizeof(struct AMG_Graph));

	printf("Please enter the number of vex: ");
	scanf("%d", &graph->vex_num);
	printf("Please enter the number of edge: ");
	scanf("%d", &graph->edge_num);

	while(getchar() != '\n');

	printf("Please enter vertex:\n");
	for(i = 0; i < graph->vex_num; i++)
	{
		graph->Vex[i] = getchar();
		while(getchar() != '\n');
	}

	for(i = 0; i < graph->vex_num; i++)
	{
		for(j = 0; j < graph->vex_num; j++)
			graph->Edge[i][j] = 0;
	}

	while(graph->edge_num--)
	{
		printf("Please enter the vex that connect each other by edge:\n");
		u = getchar();
		while(getchar() != '\n');
		v = getchar();
		while(getchar() != '\n');

		i = search_vex(graph, u);
		j = search_vex(graph, v);

		if(i != -1 && j != -1)
			graph->Edge[i][j] = 1;
		else
		{
			printf("You have entered wrong vex, please enter again.\n");
			graph->edge_num++;
		}

	}

	return graph;
}

void Show_AMG_Graph(struct AMG_Graph *graph)
{
	int i, j;

	printf("Show the vex: \n");
	for(i = 0; i < graph->vex_num; i++)
		printf("%c ", graph->Vex[i]);
	printf("\n");

	printf("Show the adjacency matrices:\n");
	for(i = 0; i< graph->vex_num; i++)
	{
		for(j = 0; j < graph->vex_num; j++)
			printf("%d\t", graph->Edge[i][j]);
		printf("\n");
	}
}

int search_vex(struct AMG_Graph *graph, char c)
{
	int i;

	for(i = 0; i < graph->vex_num; i++)
	{
		if(c == graph->Vex[i])
			return i;
	}

	return -1;
}

void BFS_AMG(struct AMG_Graph *graph)   // �ڽӾ���������ʵ��
{
	int u;
	int i;
	int j;

	int visited[MAX] = {0}; //�����ʼ��Ϊȫ��ķ�ʽ

	for(j = 0; j < graph->vex_num; j++) //����һ��forѭ�� . ���η������е�.һ������
	{
  		if(visited[j] == 0) //���û�б����ʾ�ִ��
  		{
			printf("%c ", graph->Vex[j]);
			visited[j] = 1;
			enqueue(j);

			while(!is_empty())
			{
				u = dequeue();
				for(i = 0; i < graph->vex_num; i++)    // Ϊ�����ʹ����ڽӵ�
				{
					if((graph->Edge[u][i] == 1) && (visited[i] == 0))   // graph->Edge[u][i] == 1)��ÿһ����һ��һ�м��
					{
						visited[i] = 1;  // ���
						enqueue(i);  // �����
						printf("%c ", graph->Vex[i]);  // ��ʾ
					}
				}
			}
 		 }
	}
	printf("\n");
} 
