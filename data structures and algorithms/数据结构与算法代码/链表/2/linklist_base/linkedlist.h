#ifndef LINKEDLIST_H_
#define LINKEDLSIT_H_

struct node
{
    unsigned char elem;
    struct node *next;
};

int search( unsigned char elem);
void print_linklist(void);
void delete_node(int pos);
void insert_node(int pos, char elem);// pos ��ʾλ�� ǰ����   elem��ʾҪ���������
void create_list(unsigned char elem);

#endif
