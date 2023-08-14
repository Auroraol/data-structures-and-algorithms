#include <stdbool.h>
#ifndef SEQUENCE_LIST_H_
#define SEQUENCE_LIST_H_

/*
˳��� :
*1, ��ʲô���洢���� : ����
*   1.1 ��̬���飺int arr[];
*   1.2 ��̬����: int* parr = calloc(size, sizeof(type));
*2, ��Ҫ֪��˳��������:capacity
*3, ��Ҫ֪����ЧԪ�ظ��� : size
*/
#define SEQLIST_INIT_SIZE 8	//˳���ĳ�ʼ��С

typedef void* Data;

typedef struct
{
	int capacity;
	int size;
	Data* data;

	bool isHeap;		//˳����Ƿ������ٶ���(����ʹ��seqList_create()���Ƕ�������)
}Seqlist;

//��ʼ��˳���
void seqlist_init(Seqlist* list);

//����һ��˳���
Seqlist* seqList_create();

//�ͷ�˳���
void seqList_destory(Seqlist* list);


//β��
void seqList_pushback(Seqlist* list, Data val);

// ͷ��
void seqList_pushfront(Seqlist* list, Data val);

//ָ��λ��
void seqList_insert(Seqlist* list, int pos, Data val);

// βɾ
void seqList_popback(Seqlist* list);

//ͷɾ
void seqList_popfront(Seqlist* list);

//ɾ��ָ����Ԫ��
void seqList_removeOne(Seqlist* list, Data val);

//ָ��λ��ɾ��
void seqList_removePos(Seqlist* list, int pos);

//�������Ԫ��
void seqlist_print(Seqlist* list);

//�ж�˳����Ƿ�Ϊnull
bool seqlist_empty(Seqlist* list);
bool seqlist_full(Seqlist* list);
int seqlist_size(Seqlist* list);


//����
bool is_inc(Seqlist* list);

#endif // !SEQUENCE_LIST_H_
