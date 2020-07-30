#define _CRT_SECURE_NO_WARNINGS
#include"struct.h"
#include"thaoTacVoiManHinh.h"
#include"standardFunction.h"
#include"BookActions.h"
#include"ReaderActions.h"
#include"LinkList.h"
#include"Statics.h"
#include"RepayBooks.h"
#include"menu.h"



int StaticBookQuantity(char label[100][45],int countCategory[100], List L )
{
	Node *p;
	int count = 0;
	p = L.pHead;
	while (p != NULL)
	{
		bool Exist = false;
		for (int i = 0; i < count; i++)
		{
			if (strcmp(p->Data.category, label[i]) == 0)
			{
				Exist = true;
				countCategory[i] += p->Data.quantity;
				break;
			}
		}
		if (!Exist)
		{
			strcpy(label[count], p->Data.category);
			countCategory[count] += p->Data.quantity;
			count++;
		}
		p = p->pNext;
	}
	return count;
}

int StaticBrrBookQuantity(List_Reader& L_2)
{
	int bbcount = 0;
	//List_Reader L_2 = CreateReaderList();
	Node_Reader* p_reader = L_2.pHead;
	while (p_reader != NULL)
	{
		FILE* f;
		char code[10];
		strcpy(code, toStr(p_reader->Data.code));
		char link[128];
		strcpy(link, Path("BORROWEDBOOKS/", code, ".bin"));
		errno_t error = fopen_s(&f, link, "rb");
		if (error == 0)
		{
			BorrowBook BB;
			while (fread(&BB, sizeof(BorrowBook), 1, f) != 0)
			{
				bbcount++;
			}
			fclose(f);
		}
		p_reader = p_reader->pNext;
	}
	return bbcount;
}

void StaticLateReader(List_Reader L_2, int &line)
{
	int latecount = 0;
	Day NOW = GetToday();
	Node_Reader* p_reader = L_2.pHead;
	while (p_reader != NULL)
	{
		FILE* f;
		char code[10];
		strcpy(code, toStr(p_reader->Data.code));
		char link[128];
		strcpy(link, Path("BORROWEDBOOKS/", code, ".bin"));
		errno_t error = fopen_s(&f, link, "rb");
		if (error == 0)
		{
			bool isLate = false;
			BorrowBook BB;
			while (fread(&BB, sizeof(BorrowBook), 1, f) != 0)
			{
				int LengthDay = numDay(NOW.Date, NOW.Month, NOW.Year, BB.EndDay.Date, BB.EndDay.Month, BB.EndDay.Year);
				if (LengthDay > 0)
				{
					isLate = true;
					gotoxy2(55, line++, 10,0);
					printf("+ %09d", p_reader->Data.code);
					break;
				}
			}
			if (isLate) latecount++;
			fclose(f);
		}
		p_reader = p_reader->pNext;
	}
}
void Statics()
{
	int au = GetAuthority();
	system("cls");
	DrawAppNameTab(10, 0);

	int Line = 7;

	if (au != 3)
	{
		List L = CreateBookList();
		int countBook = 0;

		Node* p = L.pHead;
		while (p != NULL)
		{
			countBook += p->Data.quantity;
			p = p->pNext;
		}

		gotoxy2(55, Line++, 10, 0);
		printf("Book quantity: %d", countBook);

		gotoxy2(55, Line++, 10, 0);
		printf("Book quantity by category: ");
		char label[100][45];
		int countCategory[100] = { 0 };
		/*int count = 0;
		p = L.pHead;
		while (p != NULL)
		{
			bool Exist = false;
			for (int i = 0; i < count; i++)
			{
				if (strcmp(p->Data.category, label[i]) == 0)
				{
					Exist = true;
					countCategory[i] += p->Data.number;
					break;
				}
			}
			if (!Exist)
			{
				strcpy(label[count], p->Data.category);
				countCategory[count] += p->Data.number;
				count++;
			}
			p = p->pNext;
		}*/
		int count = StaticBookQuantity(label, countCategory, L);
		for (int i = 0; i < count; i++)
		{
			gotoxy2(57, Line++, 10, 0);
			printf("+ %s: %d", label[i], countCategory[i]);
		}

		List_Reader L_Reader = CreateReaderList();
		gotoxy2(55, Line++, 10, 0);
		printf("Number of reader: %d", Len_Reader(L_Reader));

		Node_Reader* p_reader = L_Reader.pHead;
		int countSex[3] = { 0 };
		while (p_reader != NULL)
		{
			if (p_reader->Data.sex == 1)
				countSex[1]++;
			else
				if (p_reader->Data.sex == 2)
					countSex[2]++;
				else
					countSex[0]++;
			p_reader = p_reader->pNext;
		}
		gotoxy2(57, Line++, 10, 0);
		printf("+ Male: %d", countSex[1]);
		gotoxy2(57, Line++, 10, 0);
		printf("+ Female: %d", countSex[2]);
		gotoxy2(57, Line++, 10, 0);
		printf("+ Another: %d", countSex[0]);
	}

	List_Reader L_2 = CreateReaderList();
	int bbcount = StaticBrrBookQuantity(L_2);
	/*List_Reader L_2 = CreateReaderList();
	Node_Reader* p_reader = L_2.pHead;
	while (p_reader != NULL)
	{
		FILE* f;
		char code[10];
		strcpy(code, toStr(p_reader->Data.code));
		char link[128];
		strcpy(link, Path("BORROWEDBOOKS/", code, ".bin"));
		errno_t error = fopen_s(&f, link, "rb");
		if (error == 0)
		{
			BorrowBook BB;
			while (fread(&BB, sizeof(BorrowBook), 1, f) != 0)
			{
				bbcount++;
			}
			fclose(f);
		}
		p_reader = p_reader->pNext;
	}*/
	gotoxy2(55, Line++, 10 ,0);
	printf("Borrowed book now:  %d", bbcount);

	gotoxy2(55, Line++, 10, 0);
	printf("Late reader: ");

	StaticLateReader(L_2, Line);
	gotoxy(55, 0);
	/*int latecount = 0;
	Day NOW = GetToday();
	Node_Reader* p_reader = L_2.pHead;
	while (p_reader != NULL)
	{
		FILE* f;
		char code[10];
		strcpy(code, toStr(p_reader->Data.code));
		char link[128];
		strcpy(link, Path("BORROWEDBOOKS/", code, ".bin"));
		errno_t error = fopen_s(&f, link, "rb");
		if (error == 0)
		{
			bool isLate = false;
			BorrowBook BB;
			while (fread(&BB, sizeof(BorrowBook), 1, f) != 0)
			{
				int LengthDay = numDay(NOW.Date, NOW.Month, NOW.Year, BB.EndDay.Date, BB.EndDay.Month, BB.EndDay.Year);
				if (LengthDay > 0)
				{
					isLate = true;
					gotoxy(7, Line++);
					printf("+ %09d", p_reader->Data.code);
					break;
				}
			}
			if (isLate) latecount++;
			fclose(f);
		}
		p_reader = p_reader->pNext;
	}*/
	char ch = _getch();
	while (ch != '†')
	{
		ch = _getch();
	}
	int n;
	char list[10];
	ReadMenuData(n, list);
	Menu(n, list);
}