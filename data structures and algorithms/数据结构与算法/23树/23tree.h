#pragma once
#include <cstring>

template <class T>
class MyTwoThreeTree
{
	// �ڲ���
	struct Node
	{
		int    count;          // ��ǵ�ǰ��2�ڵ�(1)����3�ڵ�(2)����4�ڵ�(3)
		T      data[3];        // ����  // 2�ڵ�, 3�ڵ� , 4�ڵ�
		Node* pArray[4];       // �ڵ�ָ��

		Node()
		{
			count = 0;
			memset(data, 0, sizeof(T) * 3);
			memset(pArray, 0, sizeof(Node*) * 4);
		}
	};

	Node* pRoot;  // ָ����ڵ��ָ�����
public:
	//// ��ֹ�ڴ�й¶
	//static int newTimes;
	//static int deleteTimes; 

public:
	// ������
	MyTwoThreeTree()
	{
		pRoot = NULL;
	}
	// ����
	~MyTwoThreeTree()
	{
		_clear();
	}

	void insertNode(const T& data);  // ����

private:
	void _clear();
	void _clear(Node* pDel);
	void _insertNode(Node* node, Node* pParent, const T& data);
};

template<class T>
inline void MyTwoThreeTree<T>::insertNode(const T& data)
{
	if (pRoot)  // pRoot��Ϊ��
	{
		_insertNode(pRoot, NULL, data);
	}
	else
	{ // ��һ���ڵ��ǲ�һ����
		pRoot = new Node;
		pRoot->count = 1;
		pRoot->data[0] = data;
	}
}

template<class T>
inline void MyTwoThreeTree<T>::_insertNode(Node* node, Node* pParent, const T& data)
{
	if (0 == node->count)  // ��ǰ�ڵ�Ϊ��
	{
		node->data[0] = data;
		node->count++;
		return;
	}
	if (1 == node->count)  // 2�ڵ�
	{
		if (data > node->data[0])  //���ұ����
		{
			if (node->pArray[0]) // �к���
			{
				_insertNode(node->pArray[1], node, data);
			}
			else  // û�к���
			{     // ����ǰ�������
				node->data[1] = data;
				node->count++;

			}
		}
		else    //��������
		{
			if (node->pArray[0]) // �к���
			{
				_insertNode(node->pArray[0], node, data);

			}
			else // û�к���
			{
				node->data[1] = node->data[0];   // ������ߵķŵ��ұ�
				node->data[0] = data;
				node->count++;
			}
		}
	}
	else // 3�ڵ�
	{

		if (data < node->data[0])  //������߲���
		{
			if (node->pArray[0]) // �к���
			{
				_insertNode(node->pArray[0], node, data);

			}
			else // û�к���
			{
				node->data[2] = node->data[1];   // �����м�ķŵ��ұ�
				node->data[1] = node->data[0];   // ������ߵķŵ��м�
				node->data[0] = data;
				node->count++;
			}
		}
		else if (data < node->data[1]) // ���м����
		{
			if (node->pArray[1]) // �к���
			{
				_insertNode(node->pArray[1], node, data);

			}
			else // û�к���
			{
				node->data[2] = node->data[1];   // �����м�ķŵ��ұ�
				node->data[1] = data;
				node->count++;
			}
		}
		else // ���ұ߲���
		{
			if (node->pArray[2]) // �к���
			{
				_insertNode(node->pArray[2], node, data);

			}
			else // û�к���
			{
				node->data[2] = data;
				node->count++;
			}

		}

	}

	// 4�ڵ�
	if (3 == node->count)
	{

		//1. ���������½ڵ�
		Node* node1 = new Node;
		Node* node2 = new Node;
		// node1�ǵ�ǰ�ڵ������Ǹ�
		node1->data[0] = node->data[0];
		node1->count = 1;  // ���Ϊ2��
		node1->pArray[0] = node->pArray[0];
		node1->pArray[1] = node->pArray[1];

		// node2�ǵ�ǰ�ڵ���ұ��Ǹ�
		node2->data[0] = node->data[2];
		node2->count = 1;
		node2->pArray[0] = node->pArray[2];
		node2->pArray[1] = node->pArray[3];

		//  ��ʱ�Ĵ��浱ǰ�ڵ���м�ֵ
		T temp = node->data[1];

		if (pParent)  //�и��ڵ�
		{
			//��λ��
			if (temp < pParent->data[0])  // ���
			{
				if (pParent->pArray[2])  // ���ұ��к���
				{
					pParent->data[2] = pParent->data[1];
					pParent->data[1] = pParent->data[0];
					pParent->data[0] = temp;

					pParent->pArray[3] = pParent->pArray[2];
					pParent->pArray[2] = pParent->pArray[1];
					pParent->pArray[1] = node2;
					pParent->pArray[0] = node1;
				}
				else if (pParent->pArray[1]) // �м��к���
				{
					pParent->data[1] = pParent->data[0];
					pParent->data[0] = temp;

					pParent->pArray[2] = pParent->pArray[1];
					pParent->pArray[1] = node2;
					pParent->pArray[0] = node1;
				}
			}
			else if (pParent->count == 1
				|| (pParent->count > 1) && (temp < pParent->data[1]))  // �м�
			{
				if (pParent->pArray[2])  // ���ұ��к���
				{
					pParent->data[2] = pParent->data[1];
					pParent->data[1] = temp;

					pParent->pArray[3] = pParent->pArray[2];
					pParent->pArray[2] = node2;
					pParent->pArray[1] = node1;
				}
				else if (pParent->pArray[1]) // �м��к���
				{
					pParent->data[1] = temp;

					pParent->pArray[2] = node2;
					pParent->pArray[1] = node1;
				}

			}
			else if (pParent->count == 2
				|| (pParent->count > 2) && (temp < pParent->data[2]))  // �ұ�
			{
				if (pParent->pArray[2])  // ���ұ��к���
				{
					pParent->data[2] = temp;

					pParent->pArray[3] = node2;
					pParent->pArray[2] = node1;
				}

			}

			pParent->count++;
			delete node; //�����ͷŵ�ǰ�ڵ㣬��Ϊ�Ѿ����뵽���ڵ�֮��

		}
		else  // û�и��ڵ�
		{
			//2. ��ǰ�ڵ����ݸı�count���1 
			memset(node->data, 0, sizeof(T) * 3);  // ���
			node->data[0] = temp;
			node->count = 1;
			//3. pArray[o]��pArray[1]��ֵl  
			memset(node->pArray, 0, sizeof(Node*) * 4);  // ���
			node->pArray[0] = node1;
			node->pArray[1] = node2;
		}
	}

}

template<class T>
inline void MyTwoThreeTree<T>::_clear()
{
	// ���ô��ε�_clear��Ҷ�ӵ���ɾ��������
}

template<class T>
inline void MyTwoThreeTree<T>::_clear(Node* pDel)
{
	if (pDel)
		delete pDel;
}





