#include "myStack.h"
#include <iostream>


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


// Ѱ·˳��
enum  dirent { p_up, p_left, p_down, p_right };
// ������ͼ�ڵ�����
struct PathNode
{
	int dir;      // ��ǰ��̽����
	bool isFind;  // �Ƿ��߹�  0 false 1 true
};


int main(void)
{
	// 1. Ѱ·ǰ��׼��
	// 1.1 ��ͼ
	int map[ROWS][COLS] = {

		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 1, 0, 1, 1, 0, 1, 0, 1 },
		{ 1, 0, 1, 0, 1, 0, 0, 1, 0, 1 },
		{ 1, 0, 1, 0, 1, 1, 0, 1, 0, 1 },
		{ 1, 0, 0, 0, 1, 1, 0, 0, 0, 1 },
		{ 1, 0, 1, 0, 1, 1, 0, 1, 1, 1 },
		{ 1, 0, 1, 0, 1, 1, 0, 1, 1, 1 },
		{ 1, 0, 1, 0, 1, 1, 0, 1, 1, 1 },
		{ 1, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },

	};

	// 1.2 ������ͼ (��¼��ǰ��̽����,��¼��û���߹�)
	PathNode pathMap[ROWS][COLS] = {0};

	// 1.3 ջ
	MyStack<MyPoint> stack;

	// 1.4 ���  �յ� �������߹� �����ջ
	MyPoint begPos = {1,1};
	MyPoint endPos = {1,8};
	// 1.4.1 �������߹� 
	pathMap[begPos.y][begPos.x].isFind = true;
	// 1.4.2�����ջ
	stack.push(begPos);

	// 2. Ѱ·
	MyPoint currentPos = begPos;
	MyPoint searchPos;  //��̽��
	bool isFindEnd = false;
	while (true)
	{
		// 2.1 ȷ����̽��
		searchPos = currentPos;
		//2.1.1 ���ݵ�ǰ��ĵ�ǰ��̽����ȷ����̽��
		switch (pathMap[currentPos.y][currentPos.x].dir)
		{
		case p_up:
			searchPos.y--;
			pathMap[currentPos.y][currentPos.x].dir++;
			// 2.2 �ж��ܲ�����(�߹��Ĳ�����)
			if (pathMap[searchPos.y][searchPos.x].isFind == false
				&& map[searchPos.y][searchPos.x] == 0)  // û�߹����Ҳ����ϰ���
			{
				// 2.3 ��
				currentPos = searchPos;

				// 2.4 ��ջ
				stack.push(searchPos);
				// 2.5 ����߹�
				pathMap[searchPos.y][searchPos.x].isFind = true;
			}
			break;
		case p_left:
			searchPos.x--;
			pathMap[currentPos.y][currentPos.x].dir++;
			// 2.2 �ж��ܲ�����
			if (pathMap[searchPos.y][searchPos.x].isFind == false
				&& map[searchPos.y][searchPos.x] == 0)  // û�߹����Ҳ����ϰ���
			{
				// 2.3 ��
				currentPos = searchPos;

				// 2.4 ��ջ
				stack.push(searchPos);
				// 2.5 ����߹�
				pathMap[searchPos.y][searchPos.x].isFind = true;
			}
			break;
		case p_down:
			searchPos.y++;
			pathMap[currentPos.y][currentPos.x].dir++;
			// 2.2 �ж��ܲ�����
			if (pathMap[searchPos.y][searchPos.x].isFind == false && map[searchPos.y][searchPos.x] == 0)  // û�߹����Ҳ����ϰ���
			{
				// 2.3 ��
				currentPos = searchPos;

				// 2.4 ��ջ
				stack.push(searchPos);
				// 2.5 ����߹�
				pathMap[searchPos.y][searchPos.x].isFind = true;
			}
			break;

		case p_right:
			searchPos.x++;
			/*pathMap[currentPos.y][currentPos.x].dir++;*/  // �����ڸķ�����
			// 2.2 �ж��ܲ�����
			if (pathMap[searchPos.y][searchPos.x].isFind == false
				&& map[searchPos.y][searchPos.x] == 0)  // û�߹����Ҳ����ϰ���
			{
				// 2.3 ��
				currentPos = searchPos;

				// 2.4 ��ջ
				stack.push(searchPos);
				// 2.5 ����߹�
				pathMap[searchPos.y][searchPos.x].isFind = true;
			}
			else // 2.6 �����߾ͱ������
			{
				stack.pop();  // ɾ��ջ��Ԫ��
				currentPos = stack.getTop(); // ������ǰջ��Ԫ��
			}
			break;
		default: break;
		}


		// ����ҵ��յ�
		if (currentPos == endPos)
		{
			isFindEnd = true;
			break;
		}

		// ���������ͼ�ж�û���յ�
		if (stack.isEmpty())
			break;
	}


	// �ж���ʲôԭ�����Ѱ·��
	if (isFindEnd)
	{
		cout << "\n�ҵ��յ� \n";
		cout << "path: ";
		while (!stack.isEmpty())
		{
			cout << "(" << stack.getTop().y << "��"
				<< stack.getTop().x << ") ";
			stack.pop();
		}
		cout << endl;
	}
	else
	{
		cout << "\nû���ҵ��յ�!\n";
	}

	return 0;
}

