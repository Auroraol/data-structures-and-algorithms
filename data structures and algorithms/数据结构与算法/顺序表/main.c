#include<stdio.h>
#include"SeqList.h"
/*
* ���ݽṹ:�洢���ݵĽṹ ���Ա� �� ͼ
* ���Ա�:һ���ڵ�ֻ��һ��ǰ����һ�����
*	1,˳���:�ڴ���������		����
*	2,����:�ڴ��ǲ�������		�ṹ�� + ָ��
*	3,�������޵����Ա�: ջ ����
*
* ˳���:
*	1,��ʲô���洢����:����
*		1.1 ��̬���飺int arr[];
*		1.2 ��̬����: int *parr = calloc(size,sizeof(type));
*	2,��Ҫ֪��˳��������:capacity
*	3,��Ҫ֪����ЧԪ�ظ���:size
*/

int main()
{
	SeqList list = {0};
	seqList_init(&list);

	//seqList_destory(&list);	//�ͷ�ջ�����ڴ棬�ǲ��Ϸ���
	//SeqList* plist = seqList_create();
	//seqList_destory(plist);	//ֻ���ͷŶ������ڴ�

	for (int i = 0; i < 100; i++)
	{
		seqList_pushback(&list, i + 1);
	}

	//for (int i = 0; i < 10; i++)
	//{
	//	seqList_pushfront(&list, 8 +i);
	//}

	seqList_insert(&list, 2, 666);

	seqList_print(&list);

	printf("\n%d %d\n", seqList_size(&list), list.capacity);

	//seqList_popback(&list);
	//seqList_popfront(&list);
	//seqList_removeOne(&list, 666);
	//seqList_removePos(&list, 20);

	//seqList_print(&list);


	return 0;
}