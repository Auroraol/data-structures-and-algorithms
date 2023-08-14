#include "linklist.h"
#include <stdlib.h>

struct node *head = NULL;
struct node *tail = NULL;

void create_list(unsigned int elem)
{
	struct node *p = (struct node *)malloc(sizeof(struct node));
	p->elem = elem;
	p->pre = NULL;   // �γɽṹ���Ա
	p->next = NULL;

	//��ͼ1:
	if(head == NULL)  //��һ���¼���
		head = p;
	else
	{
		tail->next = p;
		p->pre = tail;   // ǰ����ָ��tail. ������
	}
	tail = p;
}

void insert_node(int pos, unsigned int elem)
{
	struct node *pre;
	pre = head;
	int i = 0;
	struct node *p = (struct node *)malloc(sizeof(struct node));
	// ��ͼ2:
	if(pos == 0)   //ͷ������
	{
		p->elem = elem;
		p->next = head;
		head->pre = p;
		p->pre = NULL;
		head = p;
	}
	else  
	{// ��ͼ3:
		while(i < pos - 1)
		{
			pre = pre->next;
			i++;
		}

		p->elem = elem;
		p->pre = pre;
		p->next = pre->next;
		//��Ҫ:(����)
		if(p->next != NULL)  //��ǰ�����p������β�ڵ�����,��Ϊ�ǵĻ��Ͳ���Ҫ�������������
			pre->next->pre = p; 
		pre->next = p;  // ����λ��

		if(p->next == NULL)
			tail = p;
	}
}

void delete_node(int pos)
{
	struct node *pre, *p;
	pre = head;
	int i = 0;
	
	//��ͼ4:
	if(pos == 0)
	{
		head = head->next;
		head->pre = NULL;  // ��ǰ��ǰ�����ͷ���NULL
		free(pre);    //ɾ��ԭ����ͷ
	}
	else
	{//��ͼ5:
		while(i < pos - 1)
		{
			pre = pre->next;
			i++;
		}
	
		p = pre->next;
		pre->next = p->next;
		//��Ҫ:(����)
		if(p->next != NULL)
			p->next->pre = pre;
		else//if(p->next == NULL)
			tail = pre;
		free(p);
	}
}

//���涼û���Ķ�:
void print_linklist(void)
{
	struct node *p;
	
	for(p = head; p; p = p->next)
		printf("%5d", p->elem);

	printf("\n");
}

int search(unsigned int elem)
{
	struct node *p;

	for(p = head; p; p = p->next)
		if(p->elem == elem)
			return 1;
	return 0;
}

void reverse_print_linklist(void)
{
	struct node *p;

	for(p = tail; p; p = p->pre)
		printf("%5d", p->elem);
	printf("\n");
}
