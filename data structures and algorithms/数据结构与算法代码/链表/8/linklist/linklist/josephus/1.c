#include <stdio.h>
#include "linklist.h"
#include <stdlib.h>


int main(void)
{
	int n, k, m, num;
	int i;
	struct node* p, * q;

	printf("�������˵ĸ���:");  //�������˵ĸ���
	scanf("%d", &n);

	for (i = 1; i <= n; i++)
	{
		printf("�������%d��������:", i); // �������������
		scanf("%d", &num);
		create_list(num); //��������ѭ������
	}
	print_linklist(); //��ʾ
	p = head;

	printf("��������еĺ��ı��m��ʼֵ:");   //��������еĺ��ı��
	scanf("%d", &m);
	if (1 == m)
	{
		for (i = 0; i < n; i++)
		{
			printf("%3d", p->elem);
			p = p->next;
		}
		printf("\n");
	}
	else
	{


		while (n--)  //(ֱ��û��Ԫ����)ȫ������ѭ��(1 �� n��)(ֻҪn����û����)
		{

			//��ǰ����(i = 0; i < m-2)
			for (i = 0; i < m - 2; i++)  //��ǰ����   mΪ3-->ѭ��1��   mΪ5-->3�� 
				p = p->next;  //  p��ǰ����

			//����ͼ 	
			q = p;  // qȡ����ǰ���� //p����������Ҫɾ���Ľڵ��
			p = p->next; //�ҵ���һ���ڵ�(Ҫɾ���Ľڵ�)
			m = p->elem;
			printf("%d", p->elem);
			q->next = p->next;   //   ɾ���ڵ�
			free(p);
			p = p->next; //����p��λ��

		}
		printf("\n");
	}

	return 0;
}


