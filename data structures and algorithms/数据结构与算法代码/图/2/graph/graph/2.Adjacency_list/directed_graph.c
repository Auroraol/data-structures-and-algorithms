#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct AdjNode // �ڽӵ��
{
	int index; // ���������Ϣ
	struct AdjNode *next; // ָ����һ���ڽӵ��ָ��
};

struct VexNode  // �ڵ��
{
	char node;  // ������Ϣ
	struct AdjNode *first;  // ָ����һ���ڽӵ��ָ��(��һ���ڽӵ��)
};

struct ALG_Graph  // 
{
	int vex_num, edge_num;   //����ĸ����ͱߵĸ���
	struct VexNode Vex[MAX]; //�ṹ������(�ɶ������Ϣ��ָ���ڽӵ��ָ�빹��)
};

struct ALG_Graph *Create_ALG_Graph(void);
int search_vex(struct ALG_Graph *graph, char c);
void create_adj_node_list(struct ALG_Graph *graph, int i, int j);
void Show_ALG_Graph(struct ALG_Graph *graph);

int main(void)
{
	struct ALG_Graph *d_graph;
	d_graph = Create_ALG_Graph();  //���ô����ڽӱ�ĺ���
	Show_ALG_Graph(d_graph);

	return 0;
}

struct ALG_Graph *Create_ALG_Graph(void) //// �����ڽӱ�
{
	int i, j;
	char u, v;

	struct ALG_Graph *graph;

	graph = (struct ALG_Graph *)malloc(sizeof(struct ALG_Graph));

	printf("Please enter the number of vex: ");
	scanf("%d", &graph->vex_num);
	printf("Please enter the number of edge: ");
	scanf("%d", &graph->edge_num);
	//while(getchar() != '\n');
	getchar();
	 

	printf("Please enter vertex:\n");
	for(i = 0; i < graph->vex_num; i++)
	{
		//graph->Vex[i].node = getchar(); // Vex[i].node ¼�붥����Ϣ
		//while(getchar() != '\n');
		scanf(" %c", &graph->Vex[i].node); // Vex[i].node ¼�붥����Ϣ
	}

	for(i = 0; i < graph->vex_num; i++)
	{
		graph->Vex[i].first = NULL;  // Vex[i].first ��ʼ��ָ����һ���ڽӵ��ָ��(��һ���ڽӵ��)����Ӧ���ǿ�ָ��
	}

	while(graph->edge_num--)  // ��ϵ
	{
		printf("Please enter the vex that connect each other by edge:\n");
		u = getchar();
		while(getchar() != '\n');
		v = getchar();
		while(getchar() != '\n');

		i = search_vex(graph, u);
		j = search_vex(graph, v);

		if(i != -1 && j != -1)   // �ҵ���Ӧ�Ĺ�ϵ��ʼ�����ڽӵ����
			create_adj_node_list(graph, i, j); // i �� j �ǳ�������ڽӵ�
		else
		{
			printf("You have entered wrong vex, please enter again.\n");
			graph->edge_num++;
		}
	}
	return graph;
}

int search_vex(struct ALG_Graph *graph, char c)  //�Ҷ�Ӧ��������
{
	int i;

	for(i = 0; i < graph->vex_num; i++)
	{
		if(c == graph->Vex[i].node)
			return i;
	}

	return -1;
}
// �����ڽӱ�
void create_adj_node_list(struct ALG_Graph *graph, int i, int j)   // �Ƚϸ��ӵĺ���  //��ͼ
{
	struct AdjNode *s = (struct AdjNode *)malloc(sizeof(struct AdjNode));  // �����ڽӱ�
	s->index = j; // �������ڽӵ���������
	s->next = graph->Vex[i].first;  //����
	graph->Vex[i].first = s;  // ָ��ǰ��λ��
}

void Show_ALG_Graph(struct ALG_Graph *graph)
{
	int i;
	struct AdjNode *t; // �����ڽӵ��ָ��

	printf("Show the ALG Graph:\n");  // ��ʾ�ڽӱ�

	for(i = 0; i < graph->vex_num; i++)
	{
		printf("%c: ", graph->Vex[i].node); //��ʾ�ڵ���Ϣ
		t = graph->Vex[i].first; //ָ���һ���ڽӵ�
		while(t != NULL)
		{
			printf("%d ", t->index);  // ���ڽӵ��������
			t = t->next;
		}
		printf("\n");
	}
}












