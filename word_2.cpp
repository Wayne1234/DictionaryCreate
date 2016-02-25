#include<iostream>
#include<fstream>
#include<windows.h>
#include<stdio.h>
using namespace std;
int NoToUni[6015];
int UniToNo[20902];
int dWord[6015][6015];
bool isCN(wchar_t wch){
	if (wch >= 19968 && wch <= 40869)
		return true;
	else
		return false;
}
struct Two{
	int i;
	int j;
	long times;
};
Two T[600000];

void Qsort(Two s[], int l, int r)
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
				Two tmp = s[i];
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

void main()
{
	cout << "运行本程序前先将data_51_100.txt文件转存为Unicode格式的文本文件" << endl;
	cout << "并且重命名为'dataUni.txt',路径为相对路径，放在同一文件夹即可" << endl;
	cout << "运行本程序还需要读取两个txt文件，NoToUni.txt，UniToNo.txt，用于编码映射" << endl;
	cout << "这两个文件可以在实验报告的压缩包中找到" << endl;
	LARGE_INTEGER startCount;
	LARGE_INTEGER endCount;
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&startCount);
	//初始化
	for (int i = 0; i < 6015; i++){
		for (int j = 0; j < 6015; j++){
			dWord[i][j] = 0;
		}
	}
	//建立映射表
	for (int i = 0; i < 20902; i++)
		UniToNo[i] = -1;
	ifstream fin1;
	fin1.open("NoToUni.txt");
	ifstream fin2;
	fin2.open("UniToNo.txt");
	int temp;
	for (int i = 0; i < 6015; i++){
		fin1 >> NoToUni[i];
		fin1 >> temp;
	}
	for (int i = 0; i < 20902; i++){
		fin2 >> temp;
		fin2 >> UniToNo[i];
	}
	fin1.close();
	fin2.close();
	//***************************************
	QueryPerformanceCounter(&endCount);
	double elapsed = (double)(endCount.QuadPart - startCount.QuadPart) / freq.QuadPart;
	cout << "初始化用时 : " << elapsed * 1000 << "ms" << endl;

	QueryPerformanceCounter(&startCount);
	wchar_t wch1;
	wchar_t wch2;
	wchar_t wch3;

	int file_size;
	FILE *fp;
	fopen_s(&fp, "dataUni.txt", "rb");
	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	wchar_t *a = (wchar_t *)malloc(file_size * sizeof(wchar_t));
	fread(a, file_size, sizeof(wchar_t), fp);
	fclose(fp);
	for (int i = 2; i <= file_size; i++){
		wch1 = a[i - 2];
		wch2 = a[i - 1];
		wch3 = a[i];
		if (isCN(wch1) && isCN(wch3) && wch2 == 32){
			dWord[UniToNo[wch1 - 19968]][UniToNo[wch3 - 19968]]++;
		}
	}

	QueryPerformanceCounter(&endCount);
	elapsed = (double)(endCount.QuadPart - startCount.QuadPart) / freq.QuadPart;
	cout << "读取文件用时 : " << elapsed * 1000 << "ms" << endl;
	QueryPerformanceCounter(&startCount);
	int count = 0;

	for (int i = 0; i < 6015; i++){
		for (int j = 0; j < 6015; j++){
			if (dWord[i][j] < 2)
				continue;
			else{
				T[count].i = i;
				T[count].j = j;
				T[count].times = dWord[i][j];
				count++;
			}
		}
	}
	Qsort(T, 0, count - 1);
	QueryPerformanceCounter(&endCount);
	elapsed = (double)(endCount.QuadPart - startCount.QuadPart) / freq.QuadPart;
	cout << "转移并排序用时 : " << elapsed * 1000 << "ms" << endl;

	QueryPerformanceCounter(&startCount);
	FILE *fpout;
	fopen_s(&fpout, "D:\\word_2.txt", "w");
	for (int k =0; k < count; k++){
		wchar_t wchout1;
		wchar_t wchout2;
		wchout1 = NoToUni[T[k].i];
		wchout2 = NoToUni[T[k].j];
		char Buf1[1024] = { 0 };
		char Buf2[1024] = { 0 };
		WideCharToMultiByte(CP_ACP, 0, &wchout1, sizeof(short int) / 2, Buf1, sizeof(Buf1), NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, &wchout2, sizeof(short int) / 2, Buf2, sizeof(Buf2), NULL, NULL);
		fprintf(fpout, "%s%s\t%d\n", Buf1, Buf2, T[k].times);
	}
	fclose(fpout);
	QueryPerformanceCounter(&endCount);
	elapsed = (double)(endCount.QuadPart - startCount.QuadPart) / freq.QuadPart;
	cout << "输出用时 : " << elapsed * 1000 << "ms" << endl;
}