#include <iostream>
#include <vector>
#include <string>

using namespace std;

int searchE(vector<int>& nums, int target);     // ���� 
int searchBE(vector<int>& nums, int target);    // ���ڵ���
int searchB(vector<int>& nums, int target);     // ���� 
int searchLD(vector<int>& nums, int target);    // С�ڵ���
int searchL(vector<int>& nums, int target);     // С��


void showTestResult(string str, int (*pf)(vector<int>&, int))
{
	vector<int> arr = {1, 2, 3, 4, 8, 14, 32, 43, 223, 344, 362, 555, 1134 ,2312};
	cout << "\n  ���� [ ";
	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << "]";
	int anw = 43;
	cout << "\n  Ҫ����" << str << anw << "������" << endl;
	cout << "  ���ҽ��: ����";
	int reslut = pf(arr, anw);
	if (reslut != -1)
		cout << reslut << endl;
	else
		cout << "�����в�����Ҫ���ҵ�����" << endl;
}



int main(void)
{
	// ����
	showTestResult("����", searchE);
	// ���ڵ���
	showTestResult("���ڵ���", searchBE);
	// ����
	showTestResult("����", searchB);
	// С�ڵ���
	showTestResult("С�ڵ���", searchLD);
	// С��
	showTestResult("С��", searchL);

	return 0;
}

// ����
int searchE(vector<int>& nums, int target)
{
	int len = nums.size();
	int left = 0, right = len - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (nums[mid] < target)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return (left == len || nums[left] != target) ? -1 : left;
}

//���ڵ���
int searchBE(vector<int>& nums, int target)
{
	int len = nums.size();
	int left = 0, right = len - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (nums[mid] >= target)  // 
			right = mid - 1;
		else
			left = mid + 1;
	}
	return left == len ? -1 : left;
}

//����
int searchB(vector<int>& nums, int target)
{
	int len = nums.size();
	int left = 0, right = len - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (nums[mid] > target)  // 
			right = mid - 1;
		else
			left = mid + 1;
	}
	return left == len ? -1 : left;
}

//С�ڵ���
int searchLD(vector<int>& nums, int target)
{
	int len = nums.size();
	int left = 0, right = len - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (nums[mid] <= target)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return right;
}

//С��
int searchL(vector<int>& nums, int target)
{
	int len = nums.size();
	int left = 0, right = len - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (nums[mid] < target)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return right;
}