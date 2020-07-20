#define _CRT_SECURE_NO_WARNINGS
#include"standardFunction.h"
#include "Actions.h"
#include "conio.h"
#include "stdio.h"
#include <cstring>
#include "ctime"
#include "thaoTacVoiManHinh.h"


void initSystemFolder()
{
	_mkdir("BOOKS");
	_mkdir("BORROWEDBOOKS");
	_mkdir("STOREZONE");
	_mkdir("parameterSYSTEM");
	_mkdir("READERS");
	_mkdir("USER");
	_mkdir("USER/admin");
	_mkdir("USER/experts");
	_mkdir("USER/managers");
	CreateFileCSV();
}

int GetAuthority()
{
	int n;
	FILE* f = fopen("STOREZONE/authority.txt", "r");
	if (f)
	{
		fscanf(f, "%d", &n);
		fclose(f);
		return n;
	}
	fclose(f);
	return -1;
}

Accounts GetAccountData(char link[])
{
	Accounts B;
	FILE* f = fopen(link, "rb");
	if (f)
	{
		fread(&B, sizeof(Accounts), 1, f);
		fclose(f);
		return B;
	}
}

int WriteAccount(char link[], Accounts user)
{
	FILE* f;
	errno_t err = fopen_s(&f, link, "wb");
	if (err == 0)
	{
		fwrite(&user, sizeof(Accounts), 1, f);
		fclose(f);
		return 1;
	}
	return 0;
}

void ReadMenuData(int& n, char list[])
{
	FILE* f = fopen("STOREZONE/menu.txt", "r");
	if (f)
	{
		fscanf(f, "%d %s", &n, list);
	}
	fclose(f);
}

int ReadCacheAccount(char user[], char pass[])
{
	int k;
	FILE* f = fopen("STOREZONE/account.txt", "r");
	if (f)
	{
		fscanf(f, "%s", user);
		fclose(f);
		return 1;
	}
	return -1;
		/*char link[256];
		if (k == 1)
		{
			strcpy(link, "USER/admin/");
		}
		if (k == 2)
		{
			strcpy(link, "USER/managers/");
		}
		if (k == 3)
		{
			strcpy(link, "USER/experts/");
		}
		strcat(link, user);
		strcat(link, ".bin\0");
		fclose(f);*/
}

void printAlert(int x, int y, int width, int height, int color, const char alert[])
{
	drawRectangle(x, y, width, height, color);
	gotoxy(53, y+1);
	printf("%s", alert);
	Sleep(1500);
}

//Readers
int ReadNumMonth()
{
	FILE* f;
	int n;
	errno_t err = fopen_s(&f, "parameterSYSTEM/ReaderMonthTimeoutExpired.txt", "r");
	if (err == 0)
	{
		fscanf(f, "%d", &n);
		fclose(f);
		return n;
	}
	//Trường hợp không có file sẽ mặc định 48 tháng
	else
	{
		err = fopen_s(&f, "parameterSYSTEM/ReaderMonthTimeoutExpired.txt", "w");
		if (err == 0)
		{
			fprintf(f, "%d", 48);
			fclose(f);
		}
		return 48;
	}
}

tm* MakeEndDay(int Date, int Month, int Year, int NumMonth)
{
	tm created;
	created.tm_mday = Date;
	created.tm_mon = Month + NumMonth;
	created.tm_year = Year;
	created.tm_hour = 0;
	created.tm_isdst = 0;
	created.tm_min = 0;
	created.tm_sec = 0;
	created.tm_wday = 0;
	created.tm_yday = 0;
	time_t endtime = mktime(&created);
	tm* ended = localtime(&endtime);
	return ended;
}
void ReadReadersMenuData(int& n, char list[])
{
	FILE* f = fopen("STOREZONE/menuReaders.txt", "r");
	if (f)
	{
		fscanf(f, "%d%s", &n, list);
	}
	fclose(f);
}

char* toStr(long n)
{
	char str[10];
	sprintf(str, "%ld", n);
	char S[10];
	S[0] = '\0';
	int count = 9 - strlen(str);
	while (count > 0)
	{
		strcat(S, "0");
		count--;
	}
	strcat(S, str);
	S[9] = '\0';
	return S;
}

char* Path(const char s1[], char s2[], const char s3[])
{
	char s[128];
	s[0] = '\0';
	strcpy(s, s1);
	strcat(s, s2);
	strcat(s, s3);
	s[strlen(s)] = '\0';
	return s;
}