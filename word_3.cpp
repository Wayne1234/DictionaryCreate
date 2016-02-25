#include<iostream>
#include<fstream>
#include<windows.h>
#include<stdio.h>
#define HASHSIZE 5000000
using namespace std;
int NoToUni[6015];
int UniToNo[20902];
struct Times{
	int code1;
	int code2;
	int code3;
	int times;
};

Times T[2400000];
struct Node{
	int count;
	int code1;
	int code2;
	int code3;
	int lenth;
	Node *next;
};

Node preNode[HASHSIZE];
void Qsort(Times s[], int l, int r)
{
	if (l < r)
	{
		int i = l, j = r;
		int x = s[l + rand() % (r - l + 1)].times;
		while (i <= j)
		{
			while (i <= j && s[j].times < x) j--;
			while (i <= j && s[i].times > x) i++;
			if (i <= j) {
				Times tmp = s[i];
				s[i] = s[j];
				s[j] = tmp;
				i++;
				j--;
			}
		}
		if (l < j) Qsort(s, l, j);
		if (i < r) Qsort(s, i, r);
	}
}
bool isCN(wchar_t wch){
	if (wch >= 19968 && wch <= 40869)
		return true;
	else
		return false;
}

void Init(){
	for (int i = 0; i < HASHSIZE; i++){
		preNode[i].count = -1;
		preNode[i].code1 = 0;
		preNode[i].code2 = 0;
		preNode[i].code3 = 0;
		preNode[i].lenth = 0;
		preNode[i].next = NULL;
	}
}

Node *q = new Node;//将q声明为全局变量可以有效提高速度
inline void Insert(int c1,int c2,int c3){
	int tempkey = (c1*c2 + c3) % HASHSIZE;//c1*c2+c3稳定在4400ms
	q = &preNode[tempkey];
	int Scan = 0;
	while (Scan<preNode[tempkey].lenth){
		q = q->next;
		Scan++;
		if ((c1==q->code1)&&(c2==q->code2)&&(c3==q->code3)){
			(q->count)++;
			return;
		}
	}
	Node *p = new Node;
	p->code1 = c1;
	p->code2 = c2;
	p->code3 = c3;
	p->count = 1;
	q->next = p;
	p->next = NULL;
	preNode[tempkey].lenth++;
}

bool compare(const Times &A, const Times &B){
	return A.times>B.times;
}

int main(){

	cout << "运行本程序前先将data_51_100.txt文件转存为Unicode格式的文本文件" << endl;
	cout << "并且重命名为'dataUni.txt',路径为相对路径，放在同一文件夹即可" << endl;

	LARGE_INTEGER startCount;
	LARGE_INTEGER endCount;
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&startCount);

	Init();
	wchar_t wch1;
	wchar_t wch2;
	wchar_t wch3;
	wchar_t wch4;
	wchar_t wch5;

	int file_size;
	FILE *fp;
	fopen_s(&fp, "dataUni.txt", "rb");
	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	wchar_t *a = (wchar_t *)malloc(file_size * sizeof(wchar_t));
	fread(a, file_size, sizeof(wchar_t), fp);
	fclose(fp);

	for (int i = 4; i <= file_size; i++){
		wch1 = a[i - 4];
		wch2 = a[i - 3];
		wch3 = a[i - 2];
		wch4 = a[i - 1];
		wch5 = a[i];
		if ((isCN(wch1)) && (isCN(wch3)) && (isCN(wch5))&&(wch2 == 32) && (wch4 == 32)){
			Insert(wch1, wch3, wch5);
		}
	}

	QueryPerformanceCounter(&endCount);
	double elapsed = (double)(endCount.QuadPart - startCount.QuadPart) / freq.QuadPart;
	cout << "初始化及建立哈希表用时 : " << elapsed * 1000 << "ms" << endl;

	QueryPerformanceCounter(&startCount);
	Times TEMPTIMES;
	Node *p = new Node;
	int SUM = 0;
	for (int i = 0; i < HASHSIZE; i++){
		p = &preNode[i];
		while (p->next != NULL){
			p = p->next;
			if (p->count<2){
				continue;
			}
			else{
				T[SUM].code1 = p->code1;
				T[SUM].code2 = p->code2;
				T[SUM].code3 = p->code3;
				T[SUM].times = p->count;
				SUM++;
			}
		}
	}
	Qsort(T, 0, SUM - 1);

	QueryPerformanceCounter(&endCount);
	elapsed = (double)(endCount.QuadPart - startCount.QuadPart) / freq.QuadPart;
	cout << "转移并排序用时 : " << elapsed * 1000 << "ms" << endl;

	QueryPerformanceCounter(&startCount);
	wchar_t wchout1;
	wchar_t wchout2;
	wchar_t wchout3;
	char Buf1[4] = { 0 };
	char Buf2[4] = { 0 };
	char Buf3[4] = { 0 };
	FILE *fpout;
	fopen_s(&fpout, "D:\\word_3.txt", "w");
	for (int k = 0; k < SUM; k++){
		wchout1 = T[k].code1;
		wchout2 = T[k].code2;
		wchout3 = T[k].code3;

		WideCharToMultiByte(CP_ACP, 0, &wchout1, 1, Buf1, 4, NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, &wchout2, 1, Buf2, 4, NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, &wchout3, 1, Buf3, 4, NULL, NULL);

		fprintf(fpout, "%s%s%s\t%d\n", Buf1, Buf2, Buf3,T[k].times);
	}

	fclose(fpout);
	QueryPerformanceCounter(&endCount);
	elapsed = (double)(endCount.QuadPart - startCount.QuadPart) / freq.QuadPart;
	cout << "输出用时 : " << elapsed * 1000 << "ms" << endl;
}
