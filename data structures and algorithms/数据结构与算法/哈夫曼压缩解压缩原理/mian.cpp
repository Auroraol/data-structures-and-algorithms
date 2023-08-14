//������ѹ������.cpp :�������̨Ӧ�ó������ڵ㡣
//
// ѹ��  ���
// ���
// ѹ��  ����ѹ�� ����ѹ��

/*
	��ֱ�Ӵ洢���ݱ����ĳЩ�����ʾ��������:

	aabbccddeeff  12B == 96bit
	a  b   c  d   e   f
	1  10  11 110 111 1000

	111010 11111101 10111111 10001000  30bit

	ѹ�������Ż� ---> ������ѹ��
	��������  ---> ���������
	���ݳ���: �еĳ��ֵö� �еĳ��ֵ���
		����:��ͬ����ȥ�����ַ�ʱ:
			aaaabbbccdef
			1111 1010 1011 1111 0111 1000   24bit

			1000 1000 1000 1000 1111 1111 111011011011101
	��:
	���ִ�����ı���λ����
	���ִ����ٵı���λ����
*/

/*
	������ѹ����ѹ��:  1. �����ʾ����  2. ���ִ��������̳��ִ����ٱ��볤
*/

/*
�ĸ��ֽ����� ���� RGB() ��Ϣ����ļ�

	1.ѹ������
		��ѹ���ļ�
		ѹ�����ļ�
		1.1������ѹ���ļ� ��ȡ�ļ��г��ֹ����ַ��ͳ��ִ���  ��ϳ��ֵ�(����)

		1.2�����ֵ䴴���������� ���ÿ���ַ��Ĺ��������� �������ֵ���
			1.2.0 ׼�������飬�洢�����ַ��ڵ�
			1.2.1 �������ִ�����С�Ľڵ�͵ڶ�С�Ľڵ�
			1.2.2 �����յĽڵ��Ϊ1.2.1�������ڵ�ĸ��ڵ�
			1.2.3   ������1.2.2�д����Ľڵ㸲��1.2.1�г��ִ�����С�Ľڵ㣬
					���������� 1.2.1�еڶ�С�Ľڵ��ÿ�
			1.2.4 ѭ��ֱ�����������нڵ㶼��������Ϊֹ
		1.3 �Ȱ��ֵ�д��ѹ�����ļ���
		1.4 �����ֵ��еı���Ѵ�ѹ���ļ��е�ÿ���ַ��Ĺ���������д��ѹ�����ļ���
		1.5 �ر������ļ�

	2. ��ѹ
		ѹ�����ļ�
		��ѹ�ļ�
			2.1 ���ֵ������
			2.2 �����ֵ����ɹ�������
			2.3	���Ŷ�һ�����ֽڶ� Ȼ��һ����������λ����
				�����Ҷ�ӽڵ㣬�ͰѶ�Ӧ�ַ�д���ѹ�ļ���
			2.4 �ر�
*/

#include <iostream>
#include <cstdio>

using namespace std;

// �ַ�
struct ZiFu
{
	unsigned char zf;    // �ַ�
	unsigned int count;  // �ַ����ֵĴ���
	char code[20];       // ������ѹ������
	int idx;             // ���ֵ��е��±�
};

// �ֵ�
struct allZiFu
{
	ZiFu zf_arr[256];
	int zf_count;         //zf_count�ֵ����ַ�����
};

//���������ڵ�����
struct treeNode
{
	ZiFu data;
	treeNode* pLeft;
	treeNode* pRight;
	treeNode* pParent;
};

// ���ݴ򿪹���
// .doc  ��office wPS
// .png .jpeg .jpg
// .txt
// .exe .lib
const char* srcFileName = "1src.txt";
const char* dstFileName = "2dst.txt";
const char* FileName = "2src.txt";
treeNode* pRoot = NULL;

//������ѹ���ļ�, ��ȡ�ֵ�
void analysisFile(const char* fileNaem, allZiFu* zd);
// �����ڵ�ĺ���
treeNode* createNode(ZiFu* pZf);
// �����ֵ䴴����������
treeNode* createHaffmanTree(allZiFu* pZd);
//���ݹ��������������������벢д���ֵ���
void createHaffmanCode(treeNode* root, allZiFu* pZd);  // ������
bool isLeaf(treeNode* root);
void setHaffmannCode(treeNode* root, char* pCodeStr);

// дѹ�����ļ�(�ֵ�, ����������)
void writeCompressed(const char* srcFileName, const char* dstFileName, allZiFu* pZd);
void getHaffmanCode(unsigned char zf, allZiFu* zd, char* pCodeStr);

// �������� analysisFile����
void _testZd(allZiFu* pZd);

// ������ѹ��, ���ֵ������
void analydstFile(const char* fileNaem, allZiFu* zd);

int main(void)
{
	allZiFu zd;
	memset(&zd, 0, sizeof(struct allZiFu));
	analysisFile(srcFileName, &zd);
	//_testZd(&zd);

	pRoot = createHaffmanTree(&zd);

	createHaffmanCode(pRoot, &zd);
	_testZd(&zd);
	writeCompressed(srcFileName, dstFileName, &zd);
	while (1);
	return 0;
}

//������ѹ���ļ�
void analysisFile(const char* fileNaem, allZiFu* pZd)
{
	// 1���ļ�
	FILE* fp = fopen(fileNaem, "rb");
	if (NULL == fp)
	{
		printf("analysisFile �� ��ѹ���ļ� %s ʧ��!\n", fileNaem);
		return;
	}
	// 2ѭ����ȡһ�ֽڵ����ݣ������ļ�ĩβֹͣ
	char c;
	int r;
	bool is;
	int i;
	while (1)
	{// 2.1 ѭ������
		r = fread(&c, sizeof(char), 1, fp);  // ���ļ���ȡһ���ַ�
		if (1 != r) break;
		// 2.2 ͳ��
		is = false;  // �ַ�û�г��ֹ�
		for (i = 0; i < pZd->zf_count; i++)
		{// ���浽��һ��λ��
			if (c == pZd->zf_arr[i].zf)
			{
				is = true;
				break;
			}
		}// end of for(i)

		if (!is)  // ���û�г��ֹ�
		{
			pZd->zf_arr[i].zf = c;
			pZd->zf_count++;
		}
		pZd->zf_arr[i].count++;
	}// end of while(1)

	// 3�ر��ļ�
	fclose(fp);
}

// �����ڵ�ĺ���
treeNode* createNode(ZiFu* pZf)
{
	treeNode* pNew = new treeNode;
	if (NULL == pNew) return NULL;
	memset(pNew, 0, sizeof(treeNode));
	pNew->data = *pZf;
	// or
	/*memcpy(pNew->data.code, pZf->code, sizeof(char) * 20);
	pNew->data.count = pZf->count;
	pNew->data.zf = pZf->zf;
	*/
	return pNew;
}

// �����ֵ䴴����������
treeNode* createHaffmanTree(allZiFu* pZd)
{
	/*
			1.2.0 ׼�������飬�洢�����ַ��ڵ�
			1.2.1 �������ִ�����С�Ľڵ� �� �ڶ�С�Ľڵ�
			1.2.2 �����յĽڵ��Ϊ1.2.1�������ڵ�ĸ��ڵ�
			1.2.3 ������1.2.2�д����Ľڵ㸲��1.2.1�г��ִ�����С�Ľڵ�(��������) ����1.2.1 �����еڶ�С�Ľڵ��ÿ�
			1.2.4 ѭ��ֱ�����������нڵ㶼��������Ϊֹ
	*/

	// 1.2.0 ׼�������飬�洢�����ַ��ڵ�
	treeNode** pArray = new treeNode * [pZd->zf_count];
	treeNode* pTemp = NULL;
	for (int i = 0; i < pZd->zf_count; i++)
	{
		pArray[i] = createNode(&(pZd->zf_arr[i]));
		pArray[i]->data.idx = i;  // �����±�
	}

	// 1.2.1
	int minIdx, secMinIdx;
	int j;
	//1.2.1.0 ѭ������С�ĺ͵ڶ�С�� ѭ��n-1 ��
	for (int i = 0; i < pZd->zf_count - 1; i++)
	{
		//1.2.1.1 �ҳ���С�ĺ͵ڶ�С��
		// �ҳ���С��
		// �ҵ���һ���ǿ�
		j = 0;
		while (pArray[j] == NULL) j++;
		minIdx = j;
		for (j = 0; j < pZd->zf_count; j++)
		{
			if (pArray[j] &&
				pArray[j]->data.count < pArray[minIdx]->data.count)
				minIdx = j;
		}
		//�ҳ��ڶ�С�ģ��ܿ�minIdx
		j = 0;
		while (pArray[j] == NULL || j == minIdx) j++;
		secMinIdx = j;
		for (j = 0; j < pZd->zf_count; j++)
		{
			if (pArray[j] &&
				j != minIdx &&
				pArray[j]->data.count < pArray[secMinIdx]->data.count)
				secMinIdx = j;
		}

		//1.2.2 ������
		// 1.2.2.1 �����½ڵ�
		ZiFu tempZf = {0, pArray[minIdx]->data.count + pArray[secMinIdx]->data.count};
		tempZf.idx = -1;
		pTemp = createNode(&tempZf);
		// 1.2.2.2 �����յĽڵ��Ϊ1.2.1�������ڵ�ĸ��ڵ�
		pArray[minIdx]->pParent = pTemp;
		pArray[secMinIdx]->pParent = pTemp;

		pTemp->pLeft = pArray[minIdx];
		pTemp->pRight = pArray[secMinIdx];

		// 1.2.1.2.3 pTemp������������С��λ�� �����еڶ�С��λ���ÿ�
		pArray[minIdx] = pTemp;
		pArray[secMinIdx] = NULL;
	}

	return pTemp;
}

//���ݹ��������������������벢д���ֵ���  code
void createHaffmanCode(treeNode* root, allZiFu* pZd)
{
	int idx;
	if (root)
	{
		if (isLeaf(root))
		{ //���ֵ����������Ĺ���������
			idx = root->data.idx;
			setHaffmannCode(root, pZd->zf_arr[idx].code);
		}
		else
		{
			//����������
			createHaffmanCode(root->pLeft, pZd);
			//����������
			createHaffmanCode(root->pRight, pZd);
		}
	}
}

bool isLeaf(treeNode* root)
{
	if (root && NULL == root->pLeft && NULL == root->pRight)
	{
		return true;
	}
	return false;
}

void setHaffmannCode(treeNode* root, char* pCodeStr)
{
	treeNode* pTemp = root;
	// һ·����׷���ж����丸�ڵ�����ӻ����Һ��ӣ���¼����
	char buff[20] = {0};  // ��ʱ��ֵ
	int buffIdx = 0;      // buff��ֵ�±�
	while (pTemp->pParent)
	{
		if (pTemp == pTemp->pParent->pLeft)
		{//���丸�ڵ�����
			buff[buffIdx] = 1;
		}
		else
		{//���丸�ڵ��Һ���
			buff[buffIdx] = 2;
		}
		buffIdx++;
		pTemp = pTemp->pParent;
	}
	//����洢��pCodeStrָ����ڴ����
	char temp;
	for (int j = 0; j < buffIdx / 2; j++)
	{
		temp = buff[j];
		buff[j] = buff[buffIdx - j - 1];
		buff[buffIdx - j - 1] = temp;
	}
	// ��ֵ
	strcpy(pCodeStr, buff);
}

// дѹ�����ļ�(�ֵ�, ����������)
void writeCompressed(const char* srcFileName, const char* dstFileName, allZiFu* pZd)
{
	//1�������ļ�
	FILE* fpSrc = fopen(srcFileName, "rb");
	FILE* fpDst = fopen(dstFileName, "wb");
	if (NULL == fpSrc || NULL == fpDst)
	{
		printf("���ļ�ʧ��!\n");
		return;
	}
	// 2. ��dstFileName�ļ���д���ֵ�
	fwrite(pZd, 1, sizeof(struct allZiFu), fpDst);
	// 3. ѭ����ȡsrcFileName�ļ��е��ֽ� �D �ҵ������������ �D ����˸�bitд��dstFileName�ļ���

	int r;  //fread��������ֵ
	char c; //��srcFileName�ж�ȡ���ֽڴ���ڴ�
	char charForwrite;  //�����洢д��dstFileName�е��ֽ�����
	int idxForwrite;    //д���ֽڵ�����
	int haffmanCodeIdx = 0;  //�����������±�code�����±�
	char haffmanCode[20] = {0}; // �洢����������
	bool isEnd = false;
	while (1)
	{
		if (haffmanCode[haffmanCodeIdx] == 0)
		{
			r = fread(&c, 1, 1, fpSrc);
			if (1 != r) break;
			getHaffmanCode(c, pZd, haffmanCode);   // ��ö�Ӧ�ַ��Ĺ���������
			haffmanCodeIdx = 0;
		}

#if 0
		// ���Դ��ֵ��л�ȡ�ַ��Ĺ���������
		printf("%c------------", c);
		for (int i = 0; i < 20; i++)
		{
			printf("%d", haffmanCode[i]);
		}
		printf("\n");
#endif // 0

		idxForwrite = 0;
		charForwrite = 0;

		while (idxForwrite < 8)  // ��������8ʱ�ͽ���д��
		{
			if (2 == haffmanCode[haffmanCodeIdx])
			{// ���ø�λ������λΪ0
				charForwrite &= ~(1 << (7 - idxForwrite));
				idxForwrite++;
				haffmanCodeIdx++;
			}
			else if (1 == haffmanCode[haffmanCodeIdx])
			{// ���ø�λ������λΪ1
				charForwrite |= (1 << (7 - idxForwrite));
				idxForwrite++;
				haffmanCodeIdx++;
			}
			else
			{//��Ϊ1 Ҳ��Ϊ2 ��ǰ�ַ����������������ϣ���ȡ��һ���ַ��Ĺ���������
				r = fread(&c, 1, 1, fpSrc);
				if (1 != r)
				{
					isEnd = true;
					break;
				}

				getHaffmanCode(c, pZd, haffmanCode);
				haffmanCodeIdx = 0;
			}
		}//end of while (idxForwrite < 8)

		fwrite(&charForwrite, 1, 1, fpDst);//���ļ���д��һ���ֽ�����

#if 1
		//����д�뵽Ŀ���ļ��е��ֽ��Ƿ���ȷ
		for (int i = 0; i < 8; i++)
		{
			if ((charForwrite & 0x80) == 0x80)
				printf("%d", 1);     //0x80: 10000000
			else
				printf("%d", 0);
			charForwrite <<= 1;
		}
		printf("\n");
#endif // 0
		if (isEnd)
			break;
	}// end of whiel(1)

	// 4. �ر������ļ�
	fclose(fpSrc);
	fclose(fpDst);
}

void getHaffmanCode(unsigned char zf, allZiFu* zd, char* pCodeStr)
{
	for (int i = 0; i < zd->zf_count; i++)
	{
		if (zf == zd->zf_arr[i].zf)
			strcpy(pCodeStr, zd->zf_arr[i].code);
	}
}

// �������� analysisFile����
void _testZd(allZiFu* pZd)
{
	printf(" ��ѹ���ļ��й���%d���ַ�\n", pZd->zf_count);
	//for (int i = 0; i < pZd->zf_count; i++)
	//{
	//	printf("%c :%d\n", pZd->zf_arr[i].zf, pZd->zf_arr[i].count);
	//}
	int j;
	for (int i = 0; i < pZd->zf_count; i++)
	{
		printf("%c: %d", pZd->zf_arr[i].zf, pZd->zf_arr[i].count);
		j = 0;
		printf(" : code: ");
		while (pZd->zf_arr[i].code[j])
		{
			printf("%d", pZd->zf_arr[i].code[j]);
			j++;
		}
		printf("\n");
	}
}

/*
2.1 ���ֵ������
2.2 �����ֵ����ɹ�������
2.3	���Ŷ�һ�����ֽڶ� Ȼ��һ����������λ����
�����Ҷ�ӽڵ㣬�ͰѶ�Ӧ�ַ�д���ѹ�ļ���
2.4 �ر�
*/
void analydstFile(const char* fileNaem, allZiFu* zd)
{
	//1�������ļ�
	FILE* fpSrc = fopen(dstFileName, "rb");
	FILE* fpDst = fopen(FileName, "wb");
	if (NULL == fpSrc || NULL == fpDst)
	{
		printf("���ļ�ʧ��!\n");
		return;
	}

	// �ر�
	fclose(fpDst);
	fclose(fpSrc);
}

/*
abcdefgaaaaabbdess ��ѹ���ļ��й���8���ַ�
a : 6
b : 3
c : 1
d : 2
e : 2
f : 1
g : 1
s : 2

00010110
11011001
10011100
00000000
01001010
11000110
11000000

*/