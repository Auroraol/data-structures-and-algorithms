#include <iostream>
#include <vector>

using namespace std;
// y
#define ROWS 10
// x
#define COLS 10

// ֱ�ߴ���
#define ZXDJ 10
// б�ߴ���
#define XXDJ 14
// ������
struct MyPoint
{
	int y;
	int x;
	int g;
	int f;
	int h;
	void setF() { f = g + h; }
	friend bool operator==(const MyPoint& p1, const MyPoint& p2);
};

bool operator==(const MyPoint& p1, const MyPoint& p2)
{
	if (p1.x == p2.x && p1.y == p2.y)
		return true;
	return false;
}

// Ѱ·˳��
enum  dirent { p_up, p_left, p_down, p_right, p_lup, p_ldown, p_rup, p_rdown };
// ������ͼ�ڵ�����
struct PathNode
{
	bool isFind;  // �Ƿ��߹�  0 false 1 true
};

// �˲���
struct treeNode
{
	MyPoint   pos;
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
int getH(MyPoint endPos, MyPoint Pos);


int main(void)
{
	// 0. ��ͼ�����͸�����ͼ���͸�����ͼ
	int map[ROWS][COLS] = {

		{ 0, 1, 1, 0, 1, 0, 0, 0, 0, 0  },
		{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 0  },
		{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 0  },
		{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 0  },
		{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 0  },
		{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 0  },
		{ 0, 0, 1, 1, 1, 0, 0, 0, 0, 0  },
		{ 0, 0, 0, 1, 1, 0, 0, 0, 0, 0  },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  },
		{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0  },

	};
	// 1.2 ������ͼ (��¼��ǰ��̽����,��¼��û���߹�)
	PathNode pathMap[ROWS][COLS] = {0};
	MyPoint begPos = {2,1};
	MyPoint endPos = {3,8};

	// 1. ����һ�Ű˲���: �洢Ѱ·���������еĽڵ�D�ҵ��յ���ҳ�·��
	treeNode* pRoot = NULL;
	// 1.1 ������߹�
	pathMap[begPos.y][begPos.x].isFind = true;
	// 1.2 ����Ϊ���ĸ��ڵ�
	pRoot = new treeNode(begPos);


	// 2. ׼��һ������: �洢���д������ĵ�   // ����
	vector<treeNode*> buff;
	vector<treeNode*>::iterator it;
	vector<treeNode*>::iterator itMin;

	// 3. Ѱ·
	// ��ǰ��
	treeNode* pCurrent = pRoot;
	// ��ʱ��
	treeNode* pChild = NULL;
	bool needFind = false;
	while (!needFind)
	{
		//3.1 һ���㴥��8����  // �������ֵg
		for (int i = 0; i < 8; i++)
		{
			pChild = new treeNode(pCurrent->pos);  // �Ե�ǰ�������ʱ��
			switch (i)
			{
			case p_up:
				pChild->pos.y--;
				pChild->pos.g += ZXDJ;
				break;
			case p_down:
				pChild->pos.y++;
				pChild->pos.g += ZXDJ;
				break;
			case p_left:
				pChild->pos.x--;
				pChild->pos.g += ZXDJ;
				break;
			case p_right:
				pChild->pos.x++;
				pChild->pos.g += ZXDJ;
				break;
			case p_lup:
				pChild->pos.x--;
				pChild->pos.y--;
				pChild->pos.g += XXDJ;
				break;
			case p_ldown:
				pChild->pos.x--;
				pChild->pos.y++;
				pChild->pos.g += XXDJ;
				break;
			case p_rup:
				pChild->pos.x++;
				pChild->pos.y--;
				pChild->pos.g += XXDJ;
				break;
			case p_rdown:
				pChild->pos.x++;
				pChild->pos.y++;
				pChild->pos.g += XXDJ;
				break;
			}

			// ����
			if (canWalk(map, pathMap, pChild->pos))
			{
				//�����ֵ �� ��������
				pChild->pos.h = getH(endPos, pChild->pos);
				pChild->pos.setF();
				// ����
				pCurrent->child.push_back(pChild);
				pChild->pParent = pCurrent;
				// ��������
				buff.push_back(pChild);
			}
			else
			{
				delete pChild;
			}
		} // end of for(i)


		//3.3 ��buff�������ҳ�fֵ��С����һ��
		itMin = buff.begin();
		for (it = buff.begin(); it != buff.end(); it++)
		{
			itMin = (*itMin)->pos.f < (*it)->pos.f ? itMin : it;
		}
		//3.4��ǰ����fֵ��С����һ�� // ����
		pCurrent = *itMin;
		// ����߹�
		pathMap[pCurrent->pos.y][pCurrent->pos.x].isFind = true;
		//3.5��fֵ��С����һ����buff�����иɵ�
		buff.erase(itMin);
		//3.6�ж��Ƿ��ҵ��յ�
		if (pCurrent->pos == endPos)
		{
			needFind = true;
			break;
		}
		//3.7���buff������ˣ�����ѭ����Ҫ����
		if (buff.size() == 0)
		{
			cout << "û�ҵ��յ�, û·��";
			needFind = true;
			break;
		}
	} // end of while(true)

	if (needFind)
	{
		cout << "\n�ҵ��յ� \n";
		cout << "path: ";
		while (pCurrent)
		{
			cout << "(" << pCurrent->pos.y << "��"
				<< pCurrent->pos.x << ") ";
			pCurrent = pCurrent->pParent;
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



int getH(MyPoint endPos, MyPoint Pos)
{
	int x = abs(endPos.x - Pos.x);
	int y = abs(endPos.y - Pos.y);

	return (x + y) * ZXDJ;
}
