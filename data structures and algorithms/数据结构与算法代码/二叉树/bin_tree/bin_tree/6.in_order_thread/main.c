#include <stdio.h>
#include <stdlib.h>

struct BinTree_node
{
	unsigned char elem;
	struct BinTree_node *ltree, *rtree;
	int lflag, rflag;  // ��־λ
};

struct BinTree_node *pre = NULL;

void pre_order(struct BinTree_node *tree);
void in_order(struct BinTree_node *tree);
void pos_order(struct BinTree_node *tree);

struct BinTree_node *create_bintree(void); //ask_method
struct BinTree_node *Create_BinTree(void); //fill_blank_method
void In_order_Thread(struct BinTree_node *tree);
void Create_Inorder_Thread(struct BinTree_node *T);
void Traverse_Inorder_Thread(struct BinTree_node *tree);
struct BinTree_node *Search_Inorder_Thread(struct BinTree_node *tree, char ch);
struct BinTree_node *Prenode_Inorder_Thread(const struct BinTree_node *node);
struct BinTree_node *Succnode_Inorder_Thread(const struct BinTree_node *node);

int main(void)
{
	struct BinTree_node *mytree;
	char ch;
	struct BinTree_node *node, *precursor, *succeed;

	printf("Please input a preorder binary tree(with fill blank #):\n");
	mytree = Create_BinTree();  //ʹ�ò��շ�
	pre_order(mytree); //�������һ��,�鿴.
	printf("\n");

	Create_Inorder_Thread(mytree);  // ���ô���
	printf("Traverse Inorder_Thread Tree:");
	Traverse_Inorder_Thread(mytree);  // ���ñ�������������
	printf("\n");

	printf("Please enter the node that you want to find it's pre & succ node:\n");  // ������Ҫ�ҵĽڵ�
	while((ch = getchar()) == '\n');   // �ɵ��س�
	node = Search_Inorder_Thread(mytree, ch);

	precursor = Prenode_Inorder_Thread(node);  //  ������ǰ����ĺ���
	if(precursor == NULL) // �����
		printf("node %c has no precursor node\n", node->elem);// ��ӡһ���ҵ���node ��ǰ����
	else
		printf("Precursor node = %c\n", precursor->elem);

	succeed = Succnode_Inorder_Thread(node);
	if(succeed == NULL)
		printf("node %c has not succeed node\n", node->elem);
	else
		printf("Succeed node = %c\n", succeed->elem);

	return 0;
}

struct BinTree_node *create_bintree(void)
{
	unsigned char flag;
	struct BinTree_node *tree;

	tree = (struct BinTree_node *)malloc(sizeof(struct BinTree_node));
	printf("Please input the node elem:\n");
	while((tree->elem = getchar()) == '\n');
	printf("Do you want to insert l_tree for %c, (Y/N)?\n", tree->elem);
	while((flag = getchar()) == '\n');

	if(flag == 'Y')
		tree->ltree = create_bintree();
	else
		tree->ltree = NULL;

	printf("Do you want to insert r_tree for %c, (Y/N)?\n", tree->elem);
	while((flag = getchar()) == '\n');

	if(flag == 'Y')
		tree->rtree = create_bintree();
	else
		tree->rtree = NULL;

	return tree;
}

struct BinTree_node *Create_BinTree(void) //fill_blank_method
{
	char ch;
	struct BinTree_node *tree;

	scanf("%c", &ch);

	if(ch == '#')
		tree = NULL;
	else
	{
		tree = (struct BinTree_node *)malloc(sizeof(struct BinTree_node));
		tree->elem = ch;
		tree->ltree = Create_BinTree();
		tree->rtree = Create_BinTree();
	}

	return tree;
}

void pre_order(struct BinTree_node *tree)
{
	if(tree)
	{
		printf("%c", tree->elem);
		pre_order(tree->ltree);
		pre_order(tree->rtree);
	}
}

void in_order(struct BinTree_node *tree)
{
	if(tree)
	{
		in_order(tree->ltree);
		printf("%c", tree->elem);
		in_order(tree->rtree);
	}
}

void pos_order(struct BinTree_node *tree)
{
	if(tree)
	{
		pos_order(tree->ltree);
		pos_order(tree->rtree);
		printf("%c", tree->elem);
	}
}
//����������
void In_order_Thread(struct BinTree_node *tree)
{
	if(tree)
	{
		//1.Do_Inorder_Thread to ltree
		In_order_Thread(tree->ltree);  //����������������

		//2.Deal with current node, 
		if(!tree->ltree)  // û��������
		{
			tree->lflag = 1;  //���±�־λ
			//current node's ltree points to the pre node //��ǰ�ڵ����ָ��ǰ����
			tree->ltree = pre;
		}
		else
			tree->lflag = 0;


		if(pre)  // �����ǰ����
		{
			if(!pre->rtree)  // �����ǰ��ǰ����������
			{
				pre->rflag = 1;
				pre->rtree = tree; // ָ��ǰ�������ǵ�
			}
			else
				pre->rflag = 0;
		}
		pre = tree; // ����ǰ�����λ��,����ָ�����ĵ�.tree��λ��ͨ���ݹ�ķ�ʽ���µ�

		//3.Do_Inorder_Thread to rtree
		In_order_Thread(tree->rtree); //����������������
	}
}
//��������������������
void Create_Inorder_Thread(struct BinTree_node *T)
{
	if(T) // �ж϶���������
	{
		In_order_Thread(T);  //���򴴽�
		// ���սڵ��:
		pre->rtree = NULL;
		pre->rflag = 1;
	}
}
//��������������
void Traverse_Inorder_Thread(struct BinTree_node *tree)
{
	while(tree)
	{
		while(tree->lflag == 0)  // һֱ������������,��ǰ��������
			tree = tree->ltree;  //��������
		printf("%c ", tree->elem);  //��ӡһ��

		while((tree->rflag == 1) && (tree->rtree))  // tree->rtree��ʾ��̽ڵ�Ϊ��
		{
			tree = tree->rtree;  // �ҵ���̽ڵ�
			printf("%c ", tree->elem);
		}
		tree = tree->rtree;
	} 
}
//��������������
struct BinTree_node *Search_Inorder_Thread(struct BinTree_node *tree, char ch)
{
	while(tree)
	{	//��ǰ��������
		while(tree->lflag == 0)  // һֱ�����ҵ������µ�
			tree = tree->ltree;
		if(tree->elem == ch)  // �����ǰ�Ľڵ����Ҫ�ҵľ�ֱ�ӷ��ص�ǰ�ڵ�
			return tree;
		// �ں�̽ڵ���
		while((tree->rflag == 1) && (tree->rtree))
		{
			tree = tree->rtree;
			if(tree->elem == ch)  // �����ǰ�Ľڵ����Ҫ�ҵľ�ֱ�ӷ��ص�ǰ�ڵ�
				return tree;
		}
		tree = tree->rtree;
	} 	
}
//��ǰ����
struct BinTree_node *Prenode_Inorder_Thread(const struct BinTree_node *node)   // const �õ�ʱ���ܸ�,��Ϊ�������Һ�̾Ͳ�����
{
	struct BinTree_node *nd;

	if(node->lflag == 1) //������ָ�����ǰ����
		return node->ltree;  // ��Ϊ��ǰ��������ָ�������ָ��ǰ�����
	else
	{// û��ǰ������ǰ�ڵ������������µ�
		nd = node->ltree;
		while(nd->rflag == 0)
			nd = nd->rtree;
		return nd;
	}
}
//�Һ�̵�
struct BinTree_node *Succnode_Inorder_Thread(const struct BinTree_node *node)
{
	struct BinTree_node *nd;

	if(node->rflag == 1)  //������ָ����Ǻ�̵�
		return node->rtree;
	else
	{// û�к�̵���ǰ�ڵ������������µ�
		nd = node->rtree;
		while(nd->lflag == 0)
			nd = nd->ltree;
		return nd;
	}
}
