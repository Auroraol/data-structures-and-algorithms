#include <stdio.h>
#include <stdlib.h>
#define MAX 100

struct AMG_Graph
{
    int vex_num, edge_num;   // ����ĸ����ͱߵĵĸ���
    char Vex[MAX];           //һά����(������Ϣ)
    int Edge[MAX][MAX];     // ��ά����(����֮��Ĺ�ϵ)
};

struct AMG_Graph *Create_AMG_Graph(void);
void show_AMG_Graph(struct AMG_Graph *graph);
int search_vex(struct AMG_Graph *graph, char c);

int main(void)
{
    
    struct AMG_Graph *ud_graph;
    ud_graph = Create_AMG_Graph(); //���ô���ͼ�ĺ���
    show_AMG_Graph(ud_graph);
    return 0;
}

// ����ͼ
struct AMG_Graph *Create_AMG_Graph(void)
{
    int i , j;
    char u, v; //����������й�ϵ�Ķ���

    struct AMG_Graph *graph;
    graph = (struct AMG_Graph *)malloc(sizeof(struct AMG_Graph));
     
    printf("Please  enter the number of vex: ");
    scanf("%d", &graph->vex_num);
    printf("Pease enter ten number of edge: ");
    scanf("%d", &graph->edge_num);
    getchar();
    /*
    while (getchar() != '\n');
    */

    printf("Please enter vertex: \n"); // ������һ���������Ϣ(���뵽һά������)
    for (i = 0; i < graph->vex_num; i++)
        scanf(" %c", &graph->Vex[i]);
    /*{
        graph->Vex[i] = getchar();
        while(getchar() != '\n');
    }*/   
    for (i = 0; i < graph->vex_num; i++)
    {
        for (j = 0; j < graph->vex_num; j++)
            graph->Edge[i][j] = 0;  //��ʼʱȫ����
    }

    while (graph->edge_num--) //¼�붥��֮��Ĺ�ϵ
    {
        printf("Please enter the that const each other by edge:\n"); //���������ӱ˴˵Ķ����ϵ
        scanf(" %c", &u); 
        scanf(" %c", &v);
            
        /*
        u = getchar();
		while(getchar() != '\n');
		v = getchar();
		while(getchar() != '\n');
        */

        // v��u�ǹ����ľ�Ҫ�Ѷ�Ӧ�ı�־λ��1
        // ����Ҫ�ҵ���Ӧ���������
        i = search_vex(graph, u);
		j = search_vex(graph, v);
        printf("%d", i);
        printf("  %d\n", j);

		if(i != -1 && j != -1)
            graph->Edge[i][j] = graph->Edge[j][i] = 1;  // ��Ϊ1
        else
        {
            printf("You have enter wrong vex, Please enter again.\n"); // ���Ҳ���,����Ķ�����Ϣ�д���
            graph->edge_num++;  //����˲�����Ҫ�ӻ���
        }
    }
    return graph;
}

void show_AMG_Graph(struct AMG_Graph *graph)
{
    int i, j;
    printf("Show the vex: \n");
    for (i = 0; i < graph->vex_num; i++)
        printf("%c", graph->Vex[i]);
    printf("\n");

    printf("Show the adjacency matrices: \n");
    for(i = 0; i < graph->vex_num; i++)
    {
        for (j = 0; j < graph->vex_num; j++)
            printf("%d\t", graph->Edge[i][j]);
        printf("\n");
    }

}

int search_vex(struct AMG_Graph *graph, char c)
{
    int i;

    for (i = 0; i < graph->vex_num; i++)
    {  //�ҵ���Ӧ���������
        if (c == graph->Vex[i])
            return i;
    }
    return -1; //�������Ӻ�����β����ʾ�ú���ʧ��.
}