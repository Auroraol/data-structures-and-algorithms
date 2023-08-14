#include"SeqList.h"
#include<malloc.h>
#include<assert.h>
#include<stdio.h>

//����, ÿ������ԭ��������
bool inc(SeqList* list)
{
	//realloc ��ԭʼ�Ļ���������
	SeqList* newList = realloc(list->data, (list->capacity + list->capacity * 2) * sizeof(Data));
	if (!newList)
	{
		return false;
	}
	list->data = newList;
	list->capacity += list->capacity * 2;
	return true;
}

// ��ͨ
void seqList_init(SeqList* list)
{
	list->isHeap = false;
	list->size = 0;
	list->capacity = SEQLIST_INIT_SIZE;
	list->data = calloc(list->capacity, sizeof(Data));
	if (!list->data)
	{
		assert(list->data);	//����list->dataΪ�棬�����Ϊ�棬����жϳ���
	}
}

// ��̬
SeqList* seqList_create()
{
	SeqList* list = calloc(1, sizeof(SeqList));
	if (!list)
	{
		assert(list);
	}
	seqList_init(list);
	list->isHeap = true;
	return list;
}

void seqList_destory(SeqList* list)
{
	//���ͷ�����
	free(list->data);
	//���ͷ�˳���
	if (list->isHeap)
		free(list);
}

void seqList_pushback(SeqList* list, Data val)
{
	//list->size == list->capacity ��������ʧ�ܲ�������������
	if (seqList_full(list) && !inc(list))
	{
		printf("seqlist is full,can't insert!\n");
		return;
	}
	list->data[list->size++] = val;
}

void seqList_pushfront(SeqList* list, Data val)
{
	if (seqList_full(list))
	{
		printf("seqlist is full,can't insert!\n");
		return;
	}
	//���ƶ������Ԫ�أ�Ϊ�²����Ԫ���ڳ��ռ�
	for (int i = list->size; i > 0; i--)
	{
		list->data[i] = list->data[i - 1];
	}
	//����������
	list->data[0] = val;
	list->size++;
}

void seqList_insert(SeqList* list, int pos, Data val)
{
	if (seqList_full(list))
	{
		printf("seqlist is full,can't insert!\n");
		return;
	}
	//�ж�pos�Ƿ�Ϸ�
	if (pos < 0 || pos > list->size)
	{
		pos = list->size;
	}
	//�ƶ�
	for (int i = list->size; i > pos; i--)   // ����h
	{
		list->data[i] = list->data[i - 1];   // ����ı��ʾ��Ǹ���
	}
	list->data[pos] = val;
	list->size++;
}

void seqList_popback(SeqList* list)
{
	if (seqList_empty(list))
	{
		return;
	}
	list->size--;
}

void seqList_popfront(SeqList* list)
{
	if (seqList_empty(list))
	{
		return;
	}
	for (int i = 0; i < list->size - 1; i++)
	{
		list->data[i] = list->data[i + 1];
	}
	list->size--;
}

void seqList_removeOne(SeqList* list, Data val)
{
	if (seqList_empty(list))
	{
		return;
	}

	//ɾ��
	seqList_removePos(list, seqList_find(list, val));
}

void seqList_removePos(SeqList* list, int pos)
{
	if (seqList_empty(list))
	{
		return;
	}
	assert(pos > 0 && pos <= list->size);

	for (int k = pos; k < list->size - 1; k++)
	{
		list->data[k] = list->data[k + 1];
	}
	list->size--;
}

void seqList_print(SeqList* list)
{
	if (seqList_empty(list))
	{
		printf("seqList is empty!\n");
		return;
	}
	for (int i = 0; i < list->size; i++)
	{
		printf("%d ", list->data[i]);
	}
	printf("\n");
}

bool seqList_empty(SeqList* list)
{
	return list->size == 0;
}

bool seqList_full(SeqList* list)
{
	return list->size == list->capacity;
}

int seqList_size(SeqList* list)
{
	return list->size;
}

int seqList_find(SeqList* list, Data val)
{
	for (int i = 0; i < list->size; i++)
	{
		if (list->data[i] == val)
		{
			return i;
		}
	}
	return -1;
}