#include "binary_tree.h"

int main(void)
{
	struct BinTree_node *mytree;

	mytree = create_bintree();

	level_traverse(mytree);
	printf("\n");

	printf("depth = %d\n", depth(mytree));  //��ӡ���ֵ
	printf("leaf number = %d\n", leaf_num(mytree)); // ��ʾҶ�Ӹ���
	printf("node number = %d\n", node_num(mytree));  //��ʾ�ڵ����

	return 0;
}
