#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct AdjNode // �ڽӵ��
{
	int index; // ���������Ϣ
	struct AdjNode* next; // ָ����һ���ڽӵ��ָ��
};

struct VexNode  // �ڵ��
{
	char vertex;  // ������Ϣ
	struct AdjNode* first;  // ָ����һ���ڽӵ��ָ��(��һ���ڽӵ��)
};

struct ALG_Graph  // 
{
	int vertex_num;   //����ĸ����ͱߵĸ���
	int edge_num;
	struct VexNode Vex[MAX]; //�ṹ������(�ɶ������Ϣ��ָ���ڽӵ��ָ�빹��)
};

struct ALG_Graph* Create_ALG_Graph(void);
int search_vex(struct ALG_Graph* graph, char c);
void create_adj_node_list(struct ALG_Graph* graph, int i, int j);
void Show_ALG_Graph(struct ALG_Graph* graph);

#if 1

int main(void)
{
	struct ALG_Graph* d_graph;
	d_graph = Create_ALG_Graph();  //���ô����ڽӱ�ĺ���
	Show_ALG_Graph(d_graph);

	return 0;
}

#endif // 0

struct ALG_Graph* Create_ALG_Graph(void) //// �����ڽӱ�
{
	struct ALG_Graph* graph;

	graph = (struct ALG_Graph*)malloc(sizeof(struct ALG_Graph));

	printf("�����붥�����: ");
	scanf("%d", &graph->vertex_num);
	printf("������ߵĸ���: ");
	scanf("%d", &graph->edge_num);
	//while(getchar() != '\n');
	getchar();


	printf("��ȷ������: ");
	for (int i = 0; i < graph->vertex_num; i++)
	{
		//graph->Vex[i].node = getchar(); // Vex[i].node ¼�붥����Ϣ
		//while(getchar() != '\n');
		scanf(" %c", &graph->Vex[i].vertex); // Vex[i].node ¼�붥����Ϣ
	}

	// ����Ϊ�� 
	for (int i = 0; i < graph->vertex_num; i++)
	{
		graph->Vex[i].first = NULL;  // Vex[i].first ��ʼ��ָ����һ���ڽӵ��ָ��(��һ���ڽӵ��)����Ӧ���ǿ�ָ��
	}

	int count = 1;
	while (graph->edge_num--)  // ¼���ϵ
	{
		char buff[5] = {0};
		int srcIdx, dstIdx;
		printf("�������%d����(A->B): ", count++);
		scanf("%s", buff);
		srcIdx = search_vex(graph, buff[0]);
		dstIdx = search_vex(graph, buff[3]);

		if (dstIdx != -1 && srcIdx != -1)
		{ // �������, �ҵ���Ӧ�Ĺ�ϵ��ʼ�����ڽӵ����
			create_adj_node_list(graph, srcIdx, dstIdx); // srcIdx �� dstIdx �ǳ�������ڽӵ�
			//create_adj_node_list(graph, dstIdx, srcIdx);  //����ͼ 
		}

		else
		{
			printf("���벻���ڵĶ���,��������һ��.\n");
			graph->edge_num++;
		}
	}
	return graph;
}

int search_vex(struct ALG_Graph* graph, char c)  //�Ҷ�Ӧ��������
{
	int i;

	for (i = 0; i < graph->vertex_num; i++)
	{
		if (c == graph->Vex[i].vertex)
			return i;
	}

	return -1;
}
// �����ڽӵ��
void create_adj_node_list(struct ALG_Graph* graph, int i, int j)   // �Ƚϸ��ӵĺ���  //��ͼ
{
	struct AdjNode* s = (struct AdjNode*)malloc(sizeof(struct AdjNode));  // �����ڽӱ�
	s->index = j; // �������ڽӵ���������
	//�ڵ�������ڽӵ�
	s->next = graph->Vex[i].first;  // ����
	graph->Vex[i].first = s;        // ָ��ǰ��λ��  // firstָ����ƶ�
}

void Show_ALG_Graph(struct ALG_Graph* graph)
{
	int i;
	struct AdjNode* t; // �����ڽӵ��ָ��

	printf("��ʾALG Graph:\n");  // ��ʾ�ڽӱ�

	for (i = 0; i < graph->vertex_num; i++)
	{
		printf("%c: ", graph->Vex[i].vertex); //��ʾ�ڵ���Ϣ
		t = graph->Vex[i].first; // ָ���һ���ڽӵ�
		while (t != NULL)
		{
			printf("%d ", t->index);  // ���ڽӵ��������
			t = t->next;
		}
		printf("\n");
	}
}