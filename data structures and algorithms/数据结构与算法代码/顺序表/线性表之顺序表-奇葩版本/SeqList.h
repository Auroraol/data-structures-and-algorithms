//��ֹͷ�ļ��ظ�����
#ifndef _SEQLIST_H	//��
#define _SEQLIST_H	//��
#include<stdbool.h>
#define SEQLIST_INIT_SIZE 8	//˳���ĳ�ʼ��С

typedef struct Student
{
	int number;
	char name[20];
}Student;
//typedef Student Data;

typedef struct Girl
{
	int age;
	char name[20];
	int height;
}Girl;
typedef Girl Data;


//ADT������������
//typedef int Data;

typedef bool (*SEQLIST_FIND_CALLBACK)(void*, void*);

//����˳���ṹ��
typedef struct SeqList
{
	int capacity;		//����
	int size;			//��ЧԪ�صĸ���
	Data* data;			 //��������ָ��	

	bool isHeap;		//˳����Ƿ������ٶ���
}SeqList;

//��ʼ��˳���
void seqList_init(SeqList* list);
//����һ��˳���
SeqList* seqList_create();
//�ͷ�˳���
void seqList_destory(SeqList* list);
//β��
void seqList_pushback(SeqList* list, Data val);
//ͷ��
void seqList_pushfront(SeqList* list, Data val);
//ָ������
void seqList_insert(SeqList* list, int pos,Data val);

//βɾ
void seqList_popback(SeqList* list);
//ͷɾ
void seqList_popfront(SeqList* list);
//ɾ��ָ����Ԫ��
void seqList_removeOne(SeqList* list,Data val, SEQLIST_FIND_CALLBACK cmp);
//ָ��λ��ɾ��
void seqList_removePos(SeqList* list, int pos);


//�������Ԫ��
void transform(SeqList* list, void (*fun)(void*));


//���弸������ͺ���
//�ж�˳����Ƿ�Ϊnull
bool seqList_empty(SeqList* list);
bool seqList_full(SeqList* list);
bool seqList_size(SeqList* list);


int seqList_find(SeqList* list, Data val, SEQLIST_FIND_CALLBACK cmp);


#endif // !_SEQLIST_H	��

