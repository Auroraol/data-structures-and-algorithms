#include <cstring>
#include <algorithm>
using namespace std;
#define NUM 5
int arr[NUM][NUM] = {0};
int maxArr[NUM][NUM] = {0};
int tempArr[NUM];
void initArr();
int getMax(int i, int j);

int main(void)
{
	/*
			   9
			 4   7
		   5   3   1
		 2   4   4   1
	   7   5   3   2  4

	  �� ���ϵ��� ���·���ĺ�  9 7 3 4 5

	*/

	initArr();
	printf("%d\n", getMax(0, 0));
	//getMax(0, 0);

	while (1);
	return 0;
}


int getMax(int i, int j)
{
	/*
		int sum = 0;
		int rMax = 0;
		for (int i = 0; i < NUM; i++)  // 5��
		{
			for (int j = 1; j <= i; j++)  // ûһ��
			{
				// �Ƚ����ڵ������Ǹ���
				rMax = max(arr[i][j - 1], arr[i][j]);
			}

		}

		�������鷳
	*/

	/*

	// strp1. �ݹ�
	if (i == NUM)
	{
		return 0;
	}

	int n = getMax(i + 1, j);      // 1,0   //2.0 2,1
	int m = getMax(i + 1, j + 1);  // 1,1   //2,1 2,2
	printf("i:%d,j:%d   n:%d,m:%d   arr[i][j]:%d\n", i, j, n, m, arr[i][j]);

	return arr[i][j] + max(n, m);   // ����Ľ��

	//*/

	/*
	// step2. �Ż����,���١�Щ��ν�ĵݹ�֮ǰ,������Ľ��ֱ�Ӵ洢��ֱ��ʹ��
	if (maxArr[i][j] != -1)
		return maxArr[i][j];
	if (i == NUM)
	{
		maxArr[i][j] = arr[i][j];
	}
	else
	{
		int n = getMax(i + 1, j);
		int m = getMax(i + 1, j + 1);
		maxArr[i][j] = arr[i][j] + max(n, m);
	}
	return maxArr[i][j];

	*/


	/*

	// step3.  ��άdb����

	//3.1����һ�㸳ֵ
	for (int i = 0; i < NUM; i++)
		maxArr[NUM - 1][i] = arr[NUM - 1][i];
	//3.2��������ȥ�����Ĳ��洢
	for (int i = NUM - 2; i >= 0; i--)
	{//��������
		for (int j = 0; j <= i; j++)
		{//�������ұ���
			maxArr[i][j] = arr[i][j] + max(maxArr[i + 1][j], maxArr[i + 1][j + 1]);

		}
	}
	return maxArr[0][0];
	*/

	///*
	// һάdp��ֵ,  �ռ����Ż�
	int tempArr[NUM];
	//4.1����һ�㺰ֵ
	for (int i = 0; i < NUM; i++)
		tempArr[i] = arr[NUM - 1][i];
	//4.2��������ȥ�����Ĳ��洢
	for (int i = NUM - 2; i >= 0; i--)
	{//��������
		for (int j = 0; j <= i; j++)
		{
			//�������ұ���
			tempArr[j] = arr[i][j] + max(tempArr[j], tempArr[j + 1]);
		}
	}
	return tempArr[0];
	//*/
}


void initArr()
{
	arr[0][0] = 9;
	arr[1][0] = 4; arr[1][1] = 7;
	arr[2][0] = 5; arr[2][1] = 3; arr[2][2] = 1;
	arr[3][0] = 2; arr[3][1] = 4; arr[3][2] = 4; arr[3][3] = 1;
	arr[4][0] = 7; arr[4][1] = 5; arr[4][2] = 3; arr[4][3] = 2; arr[4][4] = 4;

	for (int i = 0; i < NUM; i++)
	{
		for (int j = 0; j < NUM; j++)
		{
			maxArr[i][j] = -1;
		}
	}
}

