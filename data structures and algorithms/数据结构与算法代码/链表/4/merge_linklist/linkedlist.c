#include "linkedlist.h"
#include <stdlib.h> // c������ malloc�ĺ���������ͷ�ļ�   //��c++��Ҫʹ�� rand() ��������,�ڳ����а��� <cstdlib> ͷ�ļ�
#include<stdio.h>

struct node *head = NULL; //ͷָ��  // ���Ĳ��뷽��һ���У�ͷ�巨��β�巨(����)
struct node *tail = NULL;

void create_list(unsigned int elem)
{
    struct node *p = (struct node *)malloc(sizeof(struct node)); // �����ڴ�ռ� malloc����void������ ͨ��(struct node *)����ǿ������ת��ָ��
    p->elem = elem;                                              // ������
    p->next = NULL;

    // ���ӽڵ�
    if (head == NULL) //��һ�β����һ���ڵ�ʱ //ͷ�ڵ����ָ���һ���ڵ�
        head = p;
    else // �ٲ��������������ڵ�   // ��ʱ��β�ڵ��ָ����Ӧ���л���������
        tail->next = p;
    tail = p; // ����
}

//����:
void insert_node(int pos, int elem) // pos ��ʾλ�� ǰ����   elem��ʾҪ���������
{
    struct node *pre; // ǰ����
    pre = head;       // ��ʼֵ(��Ҫ��ͷָ�뿪ʼ)

    int i;
    struct node *p = (struct node *)malloc(sizeof(struct node)); //  �����ڴ�ռ�

    if (pos == 0) // û��ǰ��������,��ͷ�ڵ�ʱ����
    {
        p->elem = elem;
        p->next = head;
        head = p; // ����ͷ
    }
    else
    {
        //(1)��ǰ����/����ͷ�ڵ�����:
        while (i < pos - 1) //��ȷ��ѭ��������while  // ѭ��������Ҫ�ҵĽڵ�λ����1(�ҵ�ǰ����)
        {
            pre = pre->next;   //��ǰ����Ĺ��̾���ǰ������ƶ��ƶ�//����per��λ��
            i++;
        }
        //�¿��ٵĽڵ�:
        p->elem = elem;
        p->next = pre->next; // �µĽڵ�ָ���� ָ��ǰ�������ڵ�ָ����(ԭ��λ�ýڵ��)
        pre->next = p;       // ���¸���ǰ�����ָ����.

        if (p->next == NULL) //��ĩβ����,����ĩβ��;û�ڵ�������
            tail = p;  //ֱ�Ӳ���
    }
}

//ɾ��:
void delete_node(int pos)
{
    struct node *pre, *p;  //*p ����Ҫɾ���ڵ�
    pre = head; 
    int i;
 
    if (pos == 0)
    {
        head = head->next;
        free(pre);    //ɾ��ͷ�ڵ�(��Ϊpreָ��ͷ�ڵ�
    }
    else
        {while (i < pos - 1)
        {
            pre = pre->next;
            i++;
        }

        p = pre->next;  //��ǰҪɾ���Ľڵ�
        pre->next = p->next;   //   p->next��ʾɾ���ڵ����һ���ڵ�, ��pre-nextֱ������ɾ���ڵ����һ���ڵ���ܴﵽĿ��
        if (p->next == NULL)
            tail = pre;   // ɾ��β�ڵ�,ǰ����ͳ�Ϊĩβ

        free(p);  //ɾ��
    }
}

//�������
void print_linklist(struct node *linklist_head)
{
    struct node *p;  //����һ���ṹ��ָ��p
    
    for (p = linklist_head; p; p = p->next)   // p��ʾ��Ϊ�վͽ���  // ע���������
        printf("%5d",p->elem);   // %5d ��ʾ��� ��c++��withһ�� ֻӰ����һ����Ŀ��
    printf("\n");  //ȫ��ѭ���껻��
    
}


//������û��ĳ���ڵ������:
int search( unsigned int elem)
{
    struct node *p;

    for (p = head; p; p = p->next)
        if(p->elem == elem)
            return 1;
    return 0;
}


//�ҵ��������� �ڵ������
int find_mid(struct node *head)
{
    struct node *p; //��ָ��
    struct node *q; // ��ָ��
    p = q = head;

    while (p != NULL && p ->next != NULL)   // ѭ������
    {
        p = p->next->next;  //��ָ��һ����2��
        q = q->next;       //��ָ��һ����1��
    }
    return q->elem;  //������ָ��պ��������м��.
}

