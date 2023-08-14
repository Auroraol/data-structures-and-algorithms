#include<stdio.h>
#include"SeqList.h"
#include<string.h>
/*
* ���ݽṹ:�洢���ݵĽṹ ���Ա� �� ͼ
* ���Ա�:һ���ڵ�ֻ��һ��ǰ����һ�����
*	1,˳���:�ڴ���������		����
*	2,����:�ڴ��ǲ�������		�ṹ�� + ָ��
*	3,�������޵����Ա�:ջ ����
* 
* ˳���:
*	1,��ʲô���洢����:����
*		1.1 ��̬���飺int arr[];
*		1.2 ��̬����: int *parr = calloc(size,sizeof(type));
*	2,��Ҫ֪��˳��������:capacity
*	3,��Ҫ֪����ЧԪ�ظ���:size
*/

void stu_print(Student* stu)
{
	printf("%d %s\n", stu->number, stu->name);
}

bool stu_cmp(Student* left, Student* right)
{
	if (left->number == right->number)
	{
		return true;
	}
	return false;
}

void girl_print(Girl* girl)
{
	printf("%d %s %d\n", girl->age, girl->name, girl->height);
}

bool girl_cmp(Girl* left, Girl* right)
{
	if (strcmp(left->name, right->name) == 0)
	{
		return true;
	}
	return false;
}




//int main1()
//{
//	SeqList list;
//	seqList_init(&list);
//
//	char name[20] = { 0 };
//	for (int i = 0; i < 3; i++)
//	{
//		sprintf(name, "maye_%d", i);
//		Student stu = { 100 + i};
//		strcpy(stu.name, name);
//		seqList_pushback(&list, stu);
//	}
//
//	transform(&list,stu_print);
//
//
//	//seqList_popback(&list);
//	Student stu = { .number = 100 };
//	seqList_removeOne(&list, stu,stu_cmp);
//
//	printf("\n");
//	transform(&list, stu_print);
//
//
//	seqList_destory(&list);
//	return 0;
//}

int main()
{
	SeqList list;
	seqList_init(&list);

	Girl girls[3] = { {18,"����",170},{18,"����",171},{20,"ƤƤ",168} };
	for (int i = 0; i < 3; i++)
	{
		seqList_pushback(&list,girls[i]);
	}

	transform(&list, girl_print);

	seqList_removeOne(&list, girls[0], girl_cmp);


	transform(&list, girl_print);


	seqList_destory(&list);
	return 0;
}