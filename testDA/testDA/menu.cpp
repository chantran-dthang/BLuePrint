#define _CRT_SECURE_NO_WARNINGS
#include"menu.h"
#include"standardFunction.h"
#include"Actions.h"

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
		"Manage reader       : press 3",
		"Manage book         : press 4",
		"Create borrowing    : press 5",
		"Create paying       : press 6",
		"Statics             : press 7",
		"Change Password     : press 8",
		"Logout              : press 0"
	};
	drawRectangle(47, 6, 35, 10, 6);
	int line = 6;
	for (int i = 0; i < 9; i++) {
		if (numberAction[i] == 's') {
			drawRectangle(47, line, 35, 1, 6);
			gotoxy(48, line);
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
		if (ch == '8') ChangePassword();
		if (ch == '0') Logout();
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
	drawRectangle(47, 6, 35, 10, 6);
	int line = 6;
	for (int i = 0; i < 6; i++)
	{
		if (action[i] == 's') 
		{
			drawRectangle(47, line, 35, 1, 6);
			gotoxy(47, line);
			cout << f[i];
			line++;
		}
	}
	choseReaderAction();
}

void choseReaderAction()
{
	int numAction;
	char action[10];
	ReadMenuData(numAction, action);
	int num = GetAuthority();
	char ch = _getch();
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
	if (ch == '3') ModifyReader();
	if (ch == '4') DeleteReader();
	if (ch == '5') SearchReaderID();
	if (ch == '6') SearchReaderName();
	if (ch == '0') Logout();
	if (ch == 27) exit(0);
	if (ch== '†') Menu(numAction, action);
}