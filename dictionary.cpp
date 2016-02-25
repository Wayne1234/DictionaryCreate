#include<iostream>
#include<fstream>
#include<windows.h>
#include<stdio.h>

#define MAX2(a,b) ((a)>=(b)? (a): (b))
#define MAX(a,b,c) MAX2(MAX2(a,b), MAX2(b,c))

using namespace std;
int NoToUni[6015];
int UniToNo[20902];

inline bool isCN(wchar_t wch){
	if (wch >= 19968 && wch <= 40869)
		return true;
	else
		return false;
}

struct One{
	int times;
	double rate;
};
One O[6015];

struct Two{
	int code1;
	int code2;
	int times;
	bool Right;
	double rate;
};
Two T[40000];//ѡȡ�����д���100�εĴ�

struct Three{
	int code1;
	int code2;
	int code3;
	int times;
	bool Right;
	double rate;
};
Three Tri[30000];

struct Four{
	int code1;
	int code2;
	int code3;
	int code4;
	int times;
	bool Right;
	double rate;
};
Four F[10000];

struct CorrectWord{
	char word[64];
	int times;
	bool Right;
};
CorrectWord CW[100000];

void Qsort(CorrectWord s[], int l, int r)
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
				CorrectWord tmp = s[i];
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


inline double getTwoRate(int c1, int c2){
	double rate = 0;
	for (int i = 0; i < 35948; i++){
		if ((T[i].code1 == c1) && (T[i].code2 == c2)){
			rate = T[i].rate;
		}
	}
	return rate;
}

int main(){
	cout << "                   ע�⣺                       " << endl;
	cout << "����UniToNo��NoToUni����ӳ���������ʵ�鱨��ѹ�������ҵ�" << endl;
	cout << "����ͳ�Ƴ�����token.txt��word_2/3/4.txt���ĸ��ļ���" << endl;
	cout << "�����д������ڵ���100�εĴʶ��������µ�txt�ļ��У�" << endl;
	cout << "�ֱ�ΪAnsi1/2/3/4.txt,Uni1/2/3/4.txt��һ���˸��ļ���" << endl;
	cout << "Ansi1/2/3/4��Uni1/2/3/4������ͬ������ֱ���Ansi��Unicode��" << endl;
	cout << "��Щ�ļ�������ʵ�鱨���ѹ�������ҵ���·��Ϊ���·��" << endl;
	cout << "�������й����л�����TwoRight��TriRight��FourRight�ĸ�txt�ļ���" << endl;
	cout << "����ٶ�ȡ���ĸ��ļ��������յ�dictionary.txt�ļ�" << endl;

	LARGE_INTEGER startCount;
	LARGE_INTEGER endCount;
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&startCount);
	//��ʼ��
	for (int i = 0; i < 6015; i++){
		O[i].rate = 0;
		O[i].times = 0;
	}

	for (int i = 0; i < 40000; i++){
		T[i].code1 = 0;
		T[i].code2 = 0;
		T[i].rate = 0;
		T[i].Right = true;
		T[i].times = 0;
	}

	for (int i = 0; i < 30000; i++){
		Tri[i].code1 = 0;
		Tri[i].code2 = 0;
		Tri[i].code3 = 0;
		Tri[i].rate = 0;
		Tri[i].Right = true;
		Tri[i].times = 0;
	}

	for (int i = 0; i < 10000; i++){
		F[i].code1 = 0;
		F[i].code2 = 0;
		F[i].code3 = 0;
		F[i].code4 = 0;
		F[i].rate = 0;
		F[i].Right = true;
		F[i].times = 0;
	}

	//����ӳ���
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
		//cout << UniToNo[i]<<endl;
	}
	fin1.close();
	fin2.close();

	QueryPerformanceCounter(&endCount);
	double elapsed = (double)(endCount.QuadPart - startCount.QuadPart) / freq.QuadPart;
	cout << "��ʼ����ʱ : " << elapsed * 1000 << "ms" << endl;
	//*******************************************
	//�����ֵĴ������룬������rate
	QueryPerformanceCounter(&startCount);
	ifstream timeIn;
	timeIn.open("Ansi1.txt");
	char tempchar[4];
	for (int i = 0; i < 6015; i++){
		timeIn >> tempchar;
		timeIn >> O[i].times;
	}
	//31275191����
	//���㵥�ֵ�rate
	for (int i = 0; i < 6015; i++){
		O[i].rate = (double)O[i].times / (double)31275191;
	}

	//*******************************************
	//��˫�ֵ�times������
	ifstream TwoIn;
	TwoIn.open("Ansi2.txt");
	char tempchar2[8];
	int COUNT2 = 0;
	while (!TwoIn.eof()){
		TwoIn >> tempchar2;
		TwoIn >> T[COUNT2].times;
		COUNT2++;
	}
	//�����ֵ�times
	ifstream TriIn;
	TriIn.open("Ansi3.txt");
	char tempchar3[24];
	int COUNT3 = 0;
	while (!TriIn.eof()){
		TriIn >> tempchar3;
		TriIn >> Tri[COUNT3].times;
		COUNT3++;
	}
	//��ȡ���ֵ�times
	ifstream FourIn;
	FourIn.open("Ansi4.txt");
	char tempchar4[36];
	int COUNT4 = 0;
	while (!FourIn.eof()){
		FourIn >> tempchar4;
		FourIn >> F[COUNT4].times;
		COUNT4++;
	}

	int file_size2;
	wchar_t wch1;
	wchar_t wch2;
	FILE *fp;
	fopen_s(&fp, "Uni2.txt", "rb");
	fseek(fp, 0, SEEK_END);
	file_size2 = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	wchar_t *a = (wchar_t *)malloc(file_size2 * sizeof(wchar_t));
	fread(a, file_size2, sizeof(wchar_t), fp);
	fclose(fp);
	int NEWCOUNT = 0;
	for (int i = 1; i <= file_size2; i++){
		wch1 = a[i - 1];
		wch2 = a[i];
		if (isCN(wch1) && isCN(wch2)){
			T[NEWCOUNT].code1 = wch1;
			T[NEWCOUNT].code2 = wch2;
			NEWCOUNT++;
		}
	}

	int file_size3;

	wchar_t wch3;
	fopen_s(&fp, "Uni3.txt", "rb");
	fseek(fp, 0, SEEK_END);
	file_size3 = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	wchar_t *b = (wchar_t *)malloc(file_size3 * sizeof(wchar_t));
	fread(b, file_size3, sizeof(wchar_t), fp);
	fclose(fp);
	int NEWCOUNT2 = 0;
	for (int i = 2; i <= file_size3; i++){
		wch1 = b[i - 2];
		wch2 = b[i - 1];
		wch3 = b[i];
		if (isCN(wch1) && isCN(wch2) && isCN(wch3)){
			Tri[NEWCOUNT2].code1 = wch1;
			Tri[NEWCOUNT2].code2 = wch2;
			Tri[NEWCOUNT2].code3 = wch3;
			NEWCOUNT2++;
		}
	}

	int file_size4;
	wchar_t wch4;
	fopen_s(&fp, "Uni4.txt", "rb");
	fseek(fp, 0, SEEK_END);
	file_size4 = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	wchar_t *c = (wchar_t *)malloc(file_size4*sizeof(wchar_t));
	fread(c, file_size4, sizeof(wchar_t), fp);
	fclose(fp);
	int NEWCOUNT3 = 0;
	for (int i = 3; i <= file_size4; i++){
		wch1 = c[i - 3];
		wch2 = c[i - 2];
		wch3 = c[i - 1];
		wch4 = c[i];
		if (isCN(wch1) && isCN(wch2) && isCN(wch3)&&isCN(wch4)){
			F[NEWCOUNT3].code1 = wch1;
			F[NEWCOUNT3].code2 = wch2;
			F[NEWCOUNT3].code3 = wch3;
			F[NEWCOUNT3].code4 = wch4;
			NEWCOUNT3++;
		}
	}

	for (int i = 0; i < 27159; i++){
		Tri[i].rate = (double)Tri[i].times / (double)7714895;
	}

	for (int i = 0; i < 35948; i++){
		T[i].rate = (double)T[i].times / (double)21403377;
	}

	for (int i = 0; i < 9097; i++){
		F[i].rate = (double)F[i].times / (double)1811189;
	}

	QueryPerformanceCounter(&endCount);
	elapsed = (double)(endCount.QuadPart - startCount.QuadPart) / freq.QuadPart;
	cout << "��ȡ�ļ��ͼ���ÿ���ʵĸ���ʱ�� : " << elapsed * 1000 << "ms" << endl;
	//****************************************************************


	QueryPerformanceCounter(&startCount);
	for (int i = 0; i < 35948; i++){
		if (T[i].code1 == 30340 || T[i].code2 == 30340)//�ȰѺ����ġ��ų�
			T[i].Right = false;
	}

	for (int i = 0; i < 35948; i++){
		if (T[i].code1 == 20102 || T[i].code2 == 20102)//�Ѻ����ˡ��ų�
			T[i].Right = false;
	}

	double temprate = 0;
	for (int i = 0; i < 35948; i++){
		temprate = O[UniToNo[T[i].code1 - 19968]].rate*O[UniToNo[T[i].code2 - 19968]].rate;
		if ((T[i].rate / temprate) <= 12)
			T[i].Right = false;
	}

	for (int i = 0; i < 27159; i++){
		if (Tri[i].code1 == 30340 || Tri[i].code2 == 30340 || Tri[i].code3 == 30340)//�Ѻ����ġ��ų�
			Tri[i].Right = false;
	}

	for (int i = 0; i < 9097; i++){
		if (F[i].code1 == 30340 || F[i].code2 == 30340 || F[i].code3 == 30340 || F[i].code4 == 30340)//�Ѻ����ġ��ų�
			F[i].Right = false;
	}

	double TriRate1 = 0;
	double TriRate2 = 0;
	double TriRate3 = 0;
	double TriMaxRate = 0;
	for (int i = 0; i < 27159; i++){
		TriRate1 = O[UniToNo[Tri[i].code1 - 19968]].rate*O[UniToNo[Tri[i].code2 - 19968]].rate*O[UniToNo[Tri[i].code3 - 19968]].rate;
		TriRate2 = getTwoRate(Tri[i].code1, Tri[i].code2)*O[UniToNo[Tri[i].code3 - 19968]].rate;
		TriRate3 = O[UniToNo[Tri[i].code1 - 19968]].rate*getTwoRate(Tri[i].code2, Tri[i].code3);
		TriMaxRate = MAX(TriRate1, TriRate2, TriRate3);
		if ((Tri[i].rate / TriMaxRate) <= 20)
			Tri[i].Right = false;
	}

	double FRate1 = 0;
	double FRate2 = 0;
	double FMaxRate = 0;
	for (int i = 0; i < 9097; i++){
		FRate1 = O[UniToNo[F[i].code1 - 19968]].rate*O[UniToNo[F[i].code2 - 19968]].rate*O[UniToNo[F[i].code3 - 19968]].rate*O[UniToNo[F[i].code4 - 19968]].rate;
		FRate2 = getTwoRate(F[i].code1, F[i].code2)*getTwoRate(F[i].code3, F[i].code4);
		FRate1 = 0;
		FMaxRate = MAX2(FRate1, FRate2);
		if ((F[i].rate / FMaxRate) <= 100)
			F[i].Right = false;
	}

	QueryPerformanceCounter(&endCount);
	elapsed = (double)(endCount.QuadPart - startCount.QuadPart) / freq.QuadPart;
	cout << "�ж���ȷ�Ե�ʱ��: " << elapsed * 1000 << "ms" << endl;
	//****************************************************************************

	QueryPerformanceCounter(&startCount);
	FILE *fpout;
	fopen_s(&fpout, "TwoRight.txt", "w");
	for (int k = 0; k < 35948; k++){
		wchar_t wchout1;
		wchar_t wchout2;
		wchout1 = T[k].code1;
		wchout2 = T[k].code2;
		char Buf1[4] = { 0 };
		char Buf2[4] = { 0 };
		WideCharToMultiByte(CP_ACP, 0, &wchout1, sizeof(short int) / 2, Buf1, sizeof(Buf1), NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, &wchout2, sizeof(short int) / 2, Buf2, sizeof(Buf2), NULL, NULL);
		fprintf(fpout, "%s%s\t%d\t%d\n", Buf1, Buf2, T[k].times, T[k].Right);
	}
	fclose(fpout);

	FILE *fpout2;
	fopen_s(&fpout2, "TriRight.txt", "w");
	for (int k = 0; k < 27159; k++){
		wchar_t wchout1;
		wchar_t wchout2;
		wchar_t wchout3;
		wchout1 = Tri[k].code1;
		wchout2 = Tri[k].code2;
		wchout3 = Tri[k].code3;
		char Buf1[4] = { 0 };
		char Buf2[4] = { 0 };
		char Buf3[4] = { 0 };
		WideCharToMultiByte(CP_ACP, 0, &wchout1, sizeof(short int) / 2, Buf1, sizeof(Buf1), NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, &wchout2, sizeof(short int) / 2, Buf2, sizeof(Buf2), NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, &wchout3, sizeof(short int) / 2, Buf3, sizeof(Buf3), NULL, NULL);
		fprintf(fpout2, "%s%s%s\t%d\t%d\n", Buf1, Buf2, Buf3, Tri[k].times, Tri[k].Right);
	}
	fclose(fpout2);

	FILE *fpout3;
	fopen_s(&fpout3, "FourRight.txt", "w");
	for (int k = 0; k < 9097; k++){
		wchar_t wchout1=F[k].code1;
		wchar_t wchout2=F[k].code2;
		wchar_t wchout3=F[k].code3;
		wchar_t wchout4=F[k].code4;

		char Buf1[4] = { 0 };
		char Buf2[4] = { 0 };
		char Buf3[4] = { 0 };
		char Buf4[4] = { 0 };
		WideCharToMultiByte(CP_ACP, 0, &wchout1, sizeof(short int) / 2, Buf1, sizeof(Buf1), NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, &wchout2, sizeof(short int) / 2, Buf2, sizeof(Buf2), NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, &wchout3, sizeof(short int) / 2, Buf3, sizeof(Buf3), NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, &wchout4, sizeof(short int) / 2, Buf4, sizeof(Buf4), NULL, NULL);
		fprintf(fpout3, "%s%s%s%s\t%d\t%d\n", Buf1, Buf2, Buf3,Buf4, F[k].times, F[k].Right);
	}
	fclose(fpout3);

	QueryPerformanceCounter(&endCount);
	elapsed = (double)(endCount.QuadPart - startCount.QuadPart) / freq.QuadPart;
	cout << "���TwoRight,TriRight,FourRight��ʱ��: " << elapsed * 1000 << "ms" << endl;

	QueryPerformanceCounter(&startCount);
	//����
	ifstream IN1;
	IN1.open("TwoRight.txt");
	int INCOUNT = 0;
	while (INCOUNT<35948){//����35948��
		IN1 >> CW[INCOUNT].word;
		IN1 >> CW[INCOUNT].times;
		IN1 >> CW[INCOUNT].Right;
		INCOUNT++;
	}
	ifstream IN2;
	IN2.open("TriRight.txt");
	while (INCOUNT<63107){//����
		IN2 >> CW[INCOUNT].word;
		IN2 >> CW[INCOUNT].times;
		IN2 >> CW[INCOUNT].Right;
		INCOUNT++;
	}
	ifstream IN3;
	IN3.open("FourRight.txt");
	while (!IN3.eof()){//����
		IN3 >> CW[INCOUNT].word;
		IN3 >> CW[INCOUNT].times;
		IN3 >> CW[INCOUNT].Right;
		INCOUNT++;
	}
	INCOUNT--;

	Qsort(CW, 0, INCOUNT-1);
	ofstream DicOUT;
	DicOUT.open("D:\\dictionary.txt");
	int DicCount = 0;
	for (int i = 0; i < INCOUNT; i++){
		if (CW[i].Right == false){
			continue;
		}
		else{
			DicCount++;
			DicOUT << CW[i].word << "\t" << CW[i].times << endl;
		}
	}
	
	QueryPerformanceCounter(&endCount);
	elapsed = (double)(endCount.QuadPart - startCount.QuadPart) / freq.QuadPart;
	cout << "��������dictionary��ʱ��: " << elapsed * 1000 << "ms" << endl;

	cout << "�ֵ�ʻ�����" << DicCount << endl;
}