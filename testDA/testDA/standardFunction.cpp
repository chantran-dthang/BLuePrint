#define _CRT_SECURE_NO_WARNINGS
#include"standardFunction.h"
#include "Actions.h"
#include "conio.h"
#include "stdio.h"
#include <cstring>
#include "ctime"
#include "thaoTacVoiManHinh.h"
#include"ReaderActions.h"
#include"RepayBooks.h"



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
void printAlert(int x, int y, int width, int height, int color, const char alert[])
{
	drawRectangle(x, y, width, height, color);
	gotoxy2(53, y + 1, 10, 0);
	printf("%s", alert);
	Sleep(1500);
}

Day GetToday()
{
	time_t now = time(0);
	tm* ltm = localtime(&now);
	Day TODAY;
	TODAY.Date = ltm->tm_mday;
	TODAY.Month = ltm->tm_mon + 1;
	TODAY.Year = ltm->tm_year + 1900;
	return TODAY;
}
//========================= ACCOUNT ============================
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
		fscanf(f, "%s%s", user, pass);
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


//========================== Readers =================================
void ReadReadersMenuData(int& n, char list[])
{
	FILE* f = fopen("STOREZONE/menuReaders.txt", "r");
	if (f)
	{
		fscanf(f, "%d%s", &n, list);
	}
	fclose(f);
}
Readers GetReaderData(char link[])
{
	Readers r;
	FILE* f = fopen(link, "rb");
	if (f)
	{
		fread(&r, sizeof(Readers), 1, f);
		fclose(f);
		return r;
	}
}

int WriteReader(char link[], Readers user)
{
	FILE* f;
	f = fopen( link, "wb");
	if (f)
	{
		fwrite(&user, sizeof(Readers), 1, f);
		fclose(f);
		return 1;
	}
	return 0;
}
//=========================== BOOKS ====================================
void ReadBooksMenuData(int& n, char list[])
{
	FILE* f = fopen("STOREZONE/menuBooks.txt", "r");
	if (f)
	{
		fscanf(f, "%d%s", &n, list);
	}
	fclose(f);
}
Books GetBooksData(char link[])
{
	Books r;
	FILE* f = fopen(link, "rb");
	if (f)
	{
		fread(&r, sizeof(Books), 1, f);
		fclose(f);
		return r;
	}
}
int WriteBook(char link[], Books book)
{
	FILE* f;
	f = fopen(link, "wb");
	if (f)
	{
		fwrite(&book, sizeof(Books), 1, f);
		fclose(f);
		return 1;
	}
	return 0;
}

Day BorrDayTimeoutEx(int Date, int Month, int Year)
{
	tm created;
	created.tm_mday = Date + BorrowedTimeoutExpired();
	created.tm_mon = Month - 1;
	created.tm_year = Year - 1900;
	created.tm_hour = 0;
	created.tm_isdst = 0;
	created.tm_min = 0;
	created.tm_sec = 0;
	created.tm_wday = 0;
	created.tm_yday = 0;
	time_t endtime = mktime(&created);
	tm* ended = localtime(&endtime);
	Day Timeout;
	Timeout.Date = ended->tm_mday;
	Timeout.Month = ended->tm_mon + 1;
	Timeout.Year = ended->tm_year + 1900;
	return Timeout;
}

int BorrowedTimeoutExpired()
{
	FILE* f;
	int n;
	errno_t err = fopen_s(&f, "parameterSYSTEM/BorrowedDayTimeoutExpired.txt", "r");
	if (err == 0)
	{
		fscanf(f, "%d", &n);
		fclose(f);
		return n;
	}
	else
	{
		err = fopen_s(&f, "parameterSYSTEM/BorrowedDayTimeoutExpired.txt", "w");
		if (err == 0)
		{
			fprintf(f, "%d", 7);
			fclose(f);
		}
		return 7;
	}
}

//=============================REPAY=====================================
void CreateBrBookList(char link[], char ListBook[][14], Day EndDay[], Day StartDay[])
{
	FILE* f;
	f = fopen(link, "rb");
	if (f)
	{
		int i = 0;
		BorrowBook BB_2;
		while (fread(&BB_2, sizeof(BorrowBook), 1, f) != 0)
		{
			strcpy(ListBook[i], BB_2.ISBN);
			EndDay[i] = BB_2.EndDay;
			StartDay[i] = BB_2.BorrowedDay;
			i++;
		}
		fclose(f);
	}
	else return;
}

void DeleteBrBooks(Readers A, char link[], char ListBook[][14], Books b, Day EndDay[], Day StartDay[], int& posList)
{
	FILE* f;
	f = fopen( link, "wb");
	if (f)
	{
		bool Found = false;
		BorrowBook ASD;
		for (int i = 0; i < NumBookBorrowed(A.code); i++)
		{
			if (strcmp(b.ISBN, ListBook[i]) != 0 || Found)
			{
				strcpy(ASD.ISBN, ListBook[i]);
				ASD.BorrowedDay = StartDay[i];
				ASD.EndDay = EndDay[i];
				fwrite(&ASD, sizeof(BorrowBook), 1, f);
			}

			if (strcmp(b.ISBN, ListBook[i]) == 0)
			{
				Found = true;
				if (posList == -1) posList = i;
			}
		}
		fclose(f);
	}
}