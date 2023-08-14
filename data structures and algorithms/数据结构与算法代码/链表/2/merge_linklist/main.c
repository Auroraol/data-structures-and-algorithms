#include <stdio.h>
#include "linkedlist.h"

int main(void)
{ 
    // ���������ṹ���ָ��ͷ
    struct node *head1 = NULL;  
    struct node *head2 = NULL;
    struct node *p = NULL;
    struct node *q = NULL;
    
    //������������:
    create_list(1);
    create_list(9);
    create_list(13);
    create_list(27);
    head1 = head; //��head1ָ��Ĭ�ϵ�ͷ
    print_linklist(head1);  //��ʾ

    head = NULL; //�ȸ���ͷ��ָ���ڽ��д���
    create_list(3);
    create_list(5);
    create_list(14);
    create_list(81);
    create_list(95);
    create_list(99);
    head2 = head;
    print_linklist(head2);
	
    
    //�ϲ�����,(���������)
    head = NULL;
    p = head1;
    q = head2;
     
    while (p && q)   // ֻҪ q , p ������������һ��ȡ����,���˳�
    {
        //��һ��,�ҵ�����ͷӦ����ʲô
        if (p->elem <= q->elem)
        {
            if (head == NULL)  // ͷ�ǲ����
                head = p;      // ͷ�ǲ����
            else
                tail->next = p; //β�ڵ����һ��β�ڵ� = ������
            tail = p;  //������ȫ������.  β,����ָ��׷�ӵ�β(��������next��ǰ��)
            p = p->next;  //����λ�� , p->nextָ�����һ��λ��   
        }
        else
        {
            if (head == NULL)
                head = q;
            else
                tail->next = q;   
            tail = q;
            q = q->next;   
        }
    }
    //��û�Ƚϵ�׷��ʣ�µ�
    tail->next = p == NULL ? p: q;  //pΪ�վ�ȡq // tail->next��ʾ���������
    print_linklist(head);  //�ϲ�֮���
    return 0;
}
