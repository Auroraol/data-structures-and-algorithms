#include <stdio.h>
#include "linklist.h"
#include <stdlib.h>

int main(void)
{
	int n, k, m;   //
	int i;
	struct node *p, *q;

	printf("Please enter the number of person:");  //�������˵ĸ���
	scanf("%d", &n); //scanf����%d����&n ) ͷ�ļ�stdio.h  �û�������������������������ڱ���n   . gets()�����ַ���ʱ��

	for(i = 1; i <= n; i++)
		create_list(i);
	print_linklist(); //��ʾ
	p = head;

	printf("Please enter the start num:"); //��������ʼ�ı��
	scanf("%d", &k);

	while(--k) //����ѭ�� k-1��
		p = p->next;
	printf("p->elem = %d\n", p->elem);  //��ʾһ���ҵ����ǲ���Ŀ��ڵ�

	printf("Please enter the m:");   //��������еĺ��ı��
	scanf("%d", &m);
	
	if(1 == m)
	{
		for(i = 0; i < n; i++)
		{
			printf("%3d", p->elem);
			p = p->next;
		}
		printf("\n");
	}
	else
	{
		while(n--)  //ȫ������ѭ��
		{
			//��ǰ����
			for(i = 1; i < m - 1; i++)  //��ǰ����     �ұ��� mΪ3-->ѭ��1��   mΪ5-->3�� 
				p = p->next;  //p��ǰ����

			//����ͼ 	
			q = p;  // qȡ����ǰ����
			p = p->next; //�ҵ���һ���ڵ�
			printf("%3d", p->elem);
			q->next = p->next;
			free(p);
			p = p->next;
		}
		printf("\n");
	}
	return 0;
}
