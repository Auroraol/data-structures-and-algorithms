#pragma once
#include <stdio.h>

template <class T>
struct TreeNode
{
	T        data;    // ����
	TreeNode* pLeft;   // ����
	TreeNode* pRight;  // �Һ���
	int      height;  // �߶�

	TreeNode(const T& data) : data(data)  // Ϊ�˷���ʹ�ù�����
	{
		pLeft = pRight = NULL;
		height = 0;
	}
};


template <class T>
class AVLTree
{
private:
	TreeNode<T>* pRoot;  // ָ����ڵ��ָ��
	void _insertNodeToTree(TreeNode<T>*& root, const T& data);  // & rootĿ����Ϊ���޸��� // ˽�еĺ�ǰ����_�����˽�е�
	int _getHeight(TreeNode<T>* pRoot);

	//������Ӧ1 
	TreeNode<T>* RR(TreeNode<T>* root);
	//������Ӧ2 
	TreeNode<T>* LL(TreeNode<T>* root);
	//��������Ӧ3
	TreeNode<T>* LR(TreeNode<T>* root);
	//��������Ӧ4
	TreeNode<T>* RL(TreeNode<T>* root);

public:
	AVLTree() { pRoot = NULL; }   // ����һ������
	~AVLTree() {}

	void insert(const T& data);
	void pre_order(TreeNode<T>* root);
	TreeNode<T>* getTree();
};


template <class T>
void AVLTree<T>::insert(const T& data)
{
	_insertNodeToTree(pRoot, data);  // ���ƶԴ�һ����Ϊ�˰�ȫ
}

template <class T>
void AVLTree<T>::_insertNodeToTree(TreeNode<T>*& root, const T& data)
{
	//��Ϊһ��ƽ�������������һ�����������
	// 1. �������������ʽ����
	if (root == NULL)
	{
		root = new TreeNode<T>(data);    // ����ı������µĽڵ��滻NULL  // ����
	}


	// �ݹ�:  (���ʾ��ǰѸ��ӵ�������,ץס����������,���������_insertNodeToTree:������һ�����������һ���ڵ�,Īȥ��������)
	else if (data > root->data)
	{
		_insertNodeToTree(root->pRight, data);   // �ݹ����,����ȥ����root->PRight, ����pRoot����Զָ������ĸ��ڵ�

		// 2. ����Ƿ���Ҫ��ת����Ҫ����ת(�Ǹ���֮ǰ�����������߶��жϵ�)
		if (_getHeight(root->pRight) - _getHeight(root->pLeft) > 1)
		{ // 2.1 �ұ߱���߸�
			// 2.2 �ж������ֲ�ƽ��   2��4
			if (data > root->pRight->data)  // ����ƽ���ͼ
			{// 2
				printf("����\n");
				root = LL(root);  // ��rootΪ������
			}
			else
			{// 4
				printf("������\n");
				root = RL(root);
			}
		};
	}
	else
	{
		_insertNodeToTree(root->pLeft, data);

		// 2. ����Ƿ���Ҫ��ת����Ҫ����ת(�Ǹ���֮ǰ�����������߶��жϵ�)
		if (_getHeight(root->pLeft) - _getHeight(root->pRight) > 1)
		{// 2.1 ��߱��ұ߸�
			// 2.2 �ж������ֲ�ƽ�� 1��3
			if (data < root->pLeft->data)
			{// 1
				printf("����\n");
				root = RR(root);   // ��rootΪ������ Ȼ�� ����ֵ��ֵ��root�޸ĸ��ڵ�
			}
			else
			{// 3
				printf("������\n");
				root = LR(root);
			}
		}
	}

	// 3. ÿ����һ���ڵ�,���ø߶�9(���������1�����Բ���=���=�߶�)
	int lH = _getHeight(root->pLeft);
	int RH = _getHeight(root->pRight);
	root->height = lH > RH ? (lH + 1) : (RH + 1);
	printf("��ǰ�ڵ�ĸ߶�%d", root->height);
}

// �õ��߶�
template<class T>
inline int AVLTree<T>::_getHeight(TreeNode<T>* pRoot)
{
	if (pRoot)
		return pRoot->height;
	return 0;
}

//����
template<class T>
inline TreeNode<T>* AVLTree<T>::RR(TreeNode<T>* root)
{
	//1. pTemp��¼root������
	TreeNode<T>* pTemp = root->pLeft;

	//2. pTemp���Һ��ӳ�Ϊroot������
	root->pLeft = pTemp->pRight;

	//3. root��ΪpTemp���Һ���
	pTemp->pRight = root;

	//4. �������ø߶�
	int lH = _getHeight(root->pLeft);
	int RH = _getHeight(root->pRight);
	root->height = lH > RH ? (lH + 1) : (RH + 1);

	//5. pTemp���ػ�ȥ
	return pTemp;
}

// ����
template<class T>
inline TreeNode<T>* AVLTree<T>::LL(TreeNode<T>* root)
{
	//1. pTemp��¼root���Һ���
	TreeNode<T>* pTemp = root->pRight;

	//2. pTemp�����ӳ�Ϊroot���Һ���
	root->pRight = pTemp->pLeft;

	//3. root��ΪpTemp������
	pTemp->pLeft = root;

	//4. �������ø߶�
	int lH = _getHeight(root->pLeft);
	int RH = _getHeight(root->pRight);
	root->height = lH > RH ? (lH + 1) : (RH + 1);

	//5. pTemp���ػ�ȥ
	return pTemp;
}

//������
template<class T>
inline TreeNode<T>* AVLTree<T>::LR(TreeNode<T>* root)
{
	root->pLeft = LL(root->pLeft);  // ����root������Ϊ������
	return RR(root); // ����rootΪ������
}

//������
template<class T>
inline TreeNode<T>* AVLTree<T>::RL(TreeNode<T>* root)
{
	root->pLeft = RR(root->pLeft);  // ����root���Һ���Ϊ������
	return LL(root); // ����rootΪ������
}


template<class T>
inline void AVLTree<T>::pre_order(TreeNode<T>* root)
{
	if (root)
	{
		printf("%d  ", root->data);
		pre_order(root->pLeft);
		pre_order(root->pRight);
	}
}

template<class T>
inline TreeNode<T>* AVLTree<T>::getTree()
{
	return pRoot;
}