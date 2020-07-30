#define _CRT_SECURE_NO_WARNINGS
#include"menu.h"
#include"standardFunction.h"
#include"Actions.h"
#include"ReaderActions.h"
#include"BookActions.h"
#include"BorrowedBooks.h"
#include"RepayBooks.h"
#include"Statics.h"



void OpenMenu(int status) {
	FILE *f = fopen("STOREZONE/menu.txt", "w");
	switch (status)
	{
	case 1:	//admin
		fprintf(f, "%d %s", 9, "sssssssss");
		fclose(f);
		Menu(9, "sssssssss");
		break;
	case 2:	//manager
		fprintf(f, "%d %s", 8, "shsssssss");
		fclose(f);
		Menu(8, "shsssssss");
		break;
	case 3:	//expert
		fprintf(f, "%d %s", 8, "shsssssss");
		fclose(f);
		Menu(8, "shsssssss");
		break;
	}
}
void Menu(int Actions, const char numberAction[]) {
	char f[9][50] =
	{
		"Update Information  : press 1",
		"Create User         : press 2",
		"Manage readers      : press 3",
		"Manage books        : press 4",
		"Create borrow-bill  : press 5",
		"Create repay-bill   : press 6",
		"Statics             : press 7",
		"Change Password     : press 8",
		"Logout              : press 0"
	};
	drawRectangle(47, 6, 35, 10, 0);
	int line = 6;
	for (int i = 0; i < 9; i++) {
		if (numberAction[i] == 's') {
			drawRectangle(47, line, 35, 10, 0);
			gotoxy2(48, line,10, 0);
			cout << f[i];
			line++;
		}
	}
	choseAction();
}

void choseAction() {
	char ch = _getch();
	int num = GetAuthority();
	while (ch != 27) {
		if (ch == '1') ModifyAccount();
		if (ch == '2')
		{
			if (num == 1) CreateUser();
			else ch = _getch();
		}
		if (ch == '3') ManageReaders();
		if (ch == '4') ManageBooks();
		if (ch == '5') CreateBorrowedBill();
		if (ch == '6') CreateRepayBill();
		if (ch == '7') Statics();
		if (ch == '8') ChangePassword();
		if (ch == '0') Logout();
		ch = _getch();
	}
}

void MenuReaders(int numberActions, const char action[])
{
	char f[6][50] =
	{
		"Review readers list       : press 1",
		"Create reader             : press 2",
		"Modify reader information : press 3",
		"Delete reader             : press 4",
		"Search reader by ID       : press 5",
		"Search reader by name     : press 6",
	};
	
	drawRectangle(47, 6, 35, 10, 0);
	int line = 6;
	for (int i = 0; i < 6; i++)
	{
		if (action[i] == 's') 
		{
			drawRectangle(47, line, 35, 10, 0);
			gotoxy2(47, line, 10, 0);
			cout << f[i];
			line++;
		}
	}
	gotoxy2(61, 14, 10, 0);	printf("F12 to Back");
	choseReaderAction();
}

void choseReaderAction()
{
	int numAction;
	char action[10];
	ReadMenuData(numAction, action);
	int num = GetAuthority();
	char ch = _getch();
	/*while (ch < '1' || ch>'6' || ch != 27 || ch != '†')
	{
		ch = _getch();
	}
	if (ch == '1')
	{
		List_Reader L = CreateReaderList();
		ViewReaderList(L, 10);
	}
	if (ch == '2')
	{
		if (num != 3) CreateReader();
		else ch = _getch();
	}
	if (ch == '3')
	{
		List_Reader L = CreateReaderList();
		FieldModifyReader(L, 10);
	};
	if (ch == '4')
	{
		if (num != 3) DeleteReader();
		else ch = _getch();
	}
	if (ch == '5') SearchReaderID();
	if (ch == '6') SearchReaderName();
	//if (ch == '0') Logout();
	if (ch == 27)
	{
		system("cls");
		exit(0);
	}
	if (ch== '†') Menu(numAction, action);*/
	while (ch != 27) {
		if (ch == '1')
		{
			List_Reader L = CreateReaderList();
			ViewReaderList(L, 10);
		}
		if (ch == '2')
		{
			if (num != 3) CreateReader();
			//else ch = _getch();
		}
		if (ch == '3')
		{
			List_Reader L = CreateReaderList();
			FieldModifyReader(L, 10);
		};
		if (ch == '4')
		{
			if (num != 3) DeleteReader();
			//else ch = _getch();
		}
		if (ch == '5') SearchReaderID();
		if (ch == '6') SearchReaderName();
		if (ch == '†') Menu(numAction, action);
		/*if (ch == 27)
		{
			system("cls");
			exit(0);
		}*/
		ch = _getch();
	}
}

void MenuBooks(int numberActions, const char action[])
{
	char f[6][50] =
	{
		"Review books list         : press 1",
		"Add books                 : press 2",
		"Modify books informations : press 3",
		"Delete books              : press 4",
		"Search books by ISBN      : press 5",
		"Search books by name      : press 6",
	};
	drawRectangle(47, 6, 35, 10, 0);
	int line = 6;
	for (int i = 0; i < 6; i++)
	{
		if (action[i] == 's')
		{
			drawRectangle(47, line, 35, 10, 0);
			gotoxy2(47, line, 10, 0);
			cout << f[i];
			line++;
		}
	}
	gotoxy2(61, 14, 10, 0);	printf("F12 to Back");
	choseBooksAction();
}
void choseBooksAction()
{
	int numAction;
	char action[10];
	ReadMenuData(numAction, action);
	int num = GetAuthority();
	char ch = _getch();
	/*if (ch == '1')
	{
		if (num != 3)
		{
			List L = CreateBookList();
			ViewBookList(L, 10);
		}
		else ch = _getch();
		
	}
	if (ch == '2')
	{
		if (num != 3) AddBooks();
		else ch = _getch();
	}
	if (ch == '3')
	{
		if (num != 3)
		{
			List L = CreateBookList();
			FieldModifyBook( L,  10);
		}
	}
	if (ch == '4')
	{
		if (num != 3)DeleteBook();
		else ch = _getch();
	}
	if (ch == '5') SearchBookISBN();
	if (ch == '6') SearchBookName();
	if (ch == '0') Logout();
	if (ch == 27) exit(0);
	if (ch == '†') Menu(numAction, action);*/
	while (ch != 27) {
		if (ch == '1')
		{
			if (num != 3)
			{
				List L = CreateBookList();
				ViewBookList(L, 10);
			}
			//else ch = _getch();
		}
		if (ch == '2')
		{
			if (num != 3) AddBooks();
			else ch = _getch();
		}
		if (ch == '3')
		{
			if (num != 3)
			{
				List L = CreateBookList();
				FieldModifyBook(L, 10);
			}
		}
		if (ch == '4')
		{
			if (num != 3)DeleteBook();
			//else ch = _getch();
		}
		if (ch == '5') SearchBookISBN();
		if (ch == '6') SearchBookName();
		if (ch == 27) exit(0);
		if (ch == '†') Menu(numAction, action);
		ch = _getch();
	}
}