#include<iostream>
#include<fstream>
#include<windows.h>
using namespace std;

wchar_t wch[71366207];

//main函数
void main()
{
	cout << "运行本程序前先将data_51_100.txt文件转存为Unicode格式的文本文件" << endl;
	cout << "并且重命名为'dataUni.txt',路径为相对路径，放在同一文件夹即可" << endl;
	LARGE_INTEGER startCount;
	LARGE_INTEGER endCount;
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&startCount);
	
	long text[20902];//Unicode编码中一共有20902个汉字
	long max = 0;
	int num = 0;
	wchar_t wchtemp;
	for (int i = 0; i<20902; i++)
		text[i] = 0;
	ifstream fin;
	fin.open("dataUni.txt", ios::binary);
	fin.seekg(2, ios::beg);

	while (!fin.eof())
	{
		fin.read((char *)(&wch), 71366207*2);
		for (int i = 0; i < 71366207; i++){
			wchtemp = wch[i];
			if (wchtemp >= 19968 && wchtemp <= 40869)
				text[wchtemp - 19968]++;
		}
	}
	QueryPerformanceCounter(&endCount);
	double elapsed = (double)(endCount.QuadPart - startCount.QuadPart) / freq.QuadPart;
	cout << "读取文件用时 : " << elapsed*1000 << "ms"<<endl;

	QueryPerformanceCounter(&startCount);
	wfstream fout;
	fout.open("D:\\token.txt", ios::app | ios::out);
	for (int i = 0; i<6500; i++)
	{
		for (int j = 0; j<20902; j++)
		{
			if (max <= text[j])
			{
				max = text[j];
				num = j;
			}
		}
		wchar_t wch;
		wch = num + 19968;
		char cBuf[1024] = { 0 };
		WideCharToMultiByte(CP_ACP, 0, &wch, sizeof(short int) / 2, cBuf, sizeof(cBuf), NULL, NULL);
		if (max != 0)
			fout <<cBuf << "\t" << max << endl;
		else
			break;
		text[num] = -1;
		max = 0;
		num = 0;
	}
	fout.close();
	QueryPerformanceCounter(&endCount);
	elapsed = (double)(endCount.QuadPart - startCount.QuadPart) / freq.QuadPart;
	cout << "排序输出用时 : " << elapsed * 1000 << "ms" << endl;
}