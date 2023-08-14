#pragma once
#include <cstring>

// vector ��̬����
template <class T>
class MyStack
{
public:
	MyStack()
	{
		pBuff = NULL;
		len = 0;
		maxLen = 0;
	}
	~MyStack()
	{
		if (pBuff)
			delete[] pBuff;
		pBuff = NULL;
	}
	void push(const T& data);
	void pop()
	{
		len--;
	}
	T getTop()
	{
		return pBuff[len - 1];
	}
	bool isEmpty()
	{
		return len == 0;
	}
private:
	T* pBuff;
	size_t len;
	size_t 	maxLen;

};

template<class T>
inline void MyStack<T>::push(const T& data)
{
	/*
	//1. ÿ�ο��ڴ�  //��Լ�ռ䵱ʱ�˷�ʱ��
	maxLen = len + 1;
	T* pTemp = new T[maxLen];
	//2. ���ԭ�����ڴ����������
	if (pBuff)
	{
		memcpy(pTemp��pBuff��sizeof(T) * len);
		delete[] pBuff;
	}

	//3 �����ݽ���
	pBuff = pTemp;
	pBuff[len++] = data;
	*/
	// �Ľ�:
	// 1. �ж��Ƿ���Ҫ���ڴ� 
	if (len >= maxLen)
	{
		//1.1 ÿ�ο��ڴ�  
		// 1.1.1 �����¿����ڴ��С
		// �µ��ڴ�δ�С��ԭ����1����ԭ����1/2 ���� 1
		maxLen = maxLen + (((maxLen >> 1) > 1) ? (maxLen >> 1) : 1);
		// 1.1.2 ���ڴ�
		T* pTemp = new T[maxLen];
		//2. ���ԭ�����ڴ����������
		if (pBuff)
		{
			std::memcpy(pTemp, pBuff, sizeof(T) * len);
			delete[] pBuff;
		}
		pBuff = pTemp;
	}
	//3 �����ݽ���
	pBuff[len++] = data;
}
