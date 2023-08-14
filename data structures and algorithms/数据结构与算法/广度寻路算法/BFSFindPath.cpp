#include <iostream>
#include <vector>

using namespace std;
// y
#define ROWS 10
// x
#define COLS 10

// ����
struct MyPoint
{
	int y;
	int x;
	/*bool operator==(const MyPoint& p)
	{
		if (p.x == this->x && p.y == this->y)
			return true;
		return false;
	}*/
	friend bool operator==(const MyPoint& p1, const MyPoint& p2);
};

bool operator==(const MyPoint& p1, const MyPoint& p2)
{
	if (p1.x == p2.x && p1.y == p2.y)
		return true;
	return false;
}

// Ѱ·˳��, �������ж����Ǹ�����ĵ�
enum  dirent { p_up, p_left, p_down, p_right };
// ������ͼ�ڵ�����
struct PathNode
{
	bool isFind;  // �Ƿ��߹�  0 false 1 true
};

// �Ĳ���
struct treeNode
{
	MyPoint   pos; // ����
	treeNode* pParent;
	vector<treeNode*> child;   // ָ������ ����ָ��ǰ�ڵ�ĺ���ָ��

	treeNode(int x, int y)
	{
		pos.x = x;
		pos.y = y;
		pParent = NULL;
	}

	treeNode(MyPoint p)
	{
		pos = p;
		pParent = NULL;
	}
};

bool canWalk(int map[ROWS][COLS], PathNode pathMap[ROWS][COLS], MyPoint pos);


int main(void)
{
	// 0. ��ͼ�����͸�����ͼ���͸�����ͼ
	int map[ROWS][COLS] = {

		{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 0, 0, 1, 0, 0, 1, 0, 1, 0, 1 },
		{ 0, 0, 1, 0, 1, 1, 0, 1, 0, 1 },
		{ 0, 0, 0, 0, 1, 1, 0, 0, 0, 1 },
		{ 0, 0, 1, 0, 1, 1, 0, 1, 1, 1 },
		{ 0, 0, 1, 0, 1, 1, 0, 1, 0, 1 },
		{ 0, 0, 1, 0, 1, 1, 0, 1, 0, 1 },
		{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

	};
	// 1.2 ������ͼ (��¼��ǰ��̽����,��¼��û���߹�)
	PathNode pathMap[ROWS][COLS] = {0};
	MyPoint begPos = {1,1};
	MyPoint endPos = {1,8};

	// 1. ����һ���Ĳ���:�洢Ѱ·���������еĽڵ�D�ҵ��յ���ҳ�·��
	treeNode* pRoot = NULL;
	// 1.1 ������߹�
	pathMap[begPos.y][begPos.x].isFind = true;
	// 1.2 ����Ϊ���ĸ��ڵ�
	pRoot = new treeNode(begPos);


	// 2. ׼��һ������:�洢��ǰ��Ľڵ�   // ����
	vector<treeNode*> current;  // ��ǰ��
	current.push_back(pRoot);

	vector<treeNode*> next;     // ��һ��

	// 3. Ѱ·
	MyPoint curPos;  // ��ǰ��
	MyPoint tempPos;  // ��ʱ��
	treeNode* pChild = NULL;   // �½ڵ�
	bool isFindEnd = false;
	while (true)
	{
		next.clear();  // ÿ�������һ������
		// 3.1 һ��һ����

		for (int i = 0; i < current.size(); i++)  // 3.2 ��ǰ��ÿһ��
		{
			curPos = current.at(i)->pos;
			for (int j = 0; j < 4; j++)  // ��ǰ�������ĸ���
			{
				switch (j)  // �ж����Ǹ�����ĵ� 
				{
				case p_up:
					tempPos.y = curPos.y - 1;
					tempPos.x = curPos.x;
					break;
				case p_down:
					tempPos.y = curPos.y + 1;
					tempPos.x = curPos.x;
					break;
				case p_left:
					tempPos.y = curPos.y;
					tempPos.x = curPos.x - 1;
					break;
				case p_right:
					tempPos.y = curPos.y;
					tempPos.x = curPos.x + 1;
					break;
				}

				if (canWalk(map, pathMap, tempPos))//canWalk() 3.2.2�ж�tempPos�ܲ�����
				{
					//����:
					//3.2.2.1�����½ڵ�
					pChild = new treeNode(tempPos);
					//3.2.2.2�½ڵ����� (�������N�����Ĳ���)
					current[i]->child.push_back(pChild);
					pChild->pParent = current[i];
					//3.2.2.3����߹�
					pathMap[tempPos.y][tempPos.x].isFind = true;

					//3.2.2.4 ������һ���������
					next.push_back(pChild);
				}
				// 3.3 �����һ�������յ㣬 ���Խ�����
				if (tempPos == endPos)
				{
					isFindEnd = true;
					break;
				}
			}//end of for(j)

			if (isFindEnd)
				break;
		}// end of for(i)

		// 3.4 ����µ�һ��ڵ���Ϊ0����ͼ�Ѿ���̽����ϣ�����Ѱ·���̽���
		if (next.size() == 0)
			break;

		current = next;  // �л�����һ��
		if (isFindEnd)
			break;
	}// end of while(1);


	if (isFindEnd)
	{
		cout << "\n�ҵ��յ� \n";
		cout << "path: ";
		while (pChild)
		{
			cout << "(" << pChild->pos.y << "��"
				<< pChild->pos.x << ") ";
			pChild = pChild->pParent;
		}
		cout << endl;
	}

	return 0;
}


bool canWalk(int map[ROWS][COLS], PathNode pathMap[ROWS][COLS], MyPoint pos)
{
	//���ڵ�ͼ��Χ��
	if (pos.y < 0 || pos.y >= ROWS || pos.x < 0 || pos.x >= COLS)
		return false;
	//�߹�
	if (pathMap[pos.y][pos.x].isFind)
		return false;
	// ���ϰ���
	if (map[pos.y][pos.x])
		return false;

	return true;
}