#ifndef LINKEDLIST_H_
#define LINKEDLSIT_H_

extern struct node *head;  // ����������һ��ȫ�ֱ�������ǰ����extern�ؼ��֣�
//���᳢���������ļ���Ѱ����������Ķ��塣����ǿ��ȫ���ҷǳ�����ԭ���ǣ�ȫ�ַǳ����ı���Ĭ�����ⲿ���ӵġ�
extern struct node *tail;

struct node
{
    unsigned int elem;
    struct node *next;
};

int search( unsigned int elem);
void print_linklist(struct node *linklist_head);
void delete_node(int pos);
void insert_node(int pos, int elem);// pos ��ʾλ�� ǰ����   elem��ʾҪ���������
void create_list(unsigned int elem);
int find_mid(struct node *head);
#endif
