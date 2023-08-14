#pragma once
#include <stdbool.h>

typedef int Data;

// ����ڵ�ṹ
typedef struct linkNode
{
	Data data;
	struct linkNode* next;

}linkNode;

// ��������
linkNode* createList();

// �����ڵ�
linkNode* createNode(Data val);

// ����
//ͷ����
void pushfront(linkNode* list, Data val);
//β����
void push_back(linkNode* list, Data val);
//ָ��λ�ò���(�±�)
void insert_pos(linkNode* list, int pos, Data val);
//ָ��λ�ò���(��ָ��Ԫ��֮��)
void insert_item(linkNode* list, linkNode* item, Data val);
// ����Ԫ��
linkNode* find(linkNode* list, Data data);


// ɾ��
//ͷɾ
void pop_front(linkNode* list);
//βɾ
void pop_back(linkNode* list);
//ָ��Ԫ��ɾ��
void removeOne(linkNode* list, Data val);
void removeA1l(linkNode* list, Data val);  // ɾ������val
bool isempty(linkNode* list);

// ����
void show_list(linkNode* list);