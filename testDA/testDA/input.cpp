#include"input.h"
#include "windows.h"
#include"thaoTacVoiManHinh.h"
#include"stdio.h"

int InputPass(char pass[])
{
	char ch;
	for (int i = 0;i<21;)//infinite loop
	{
		ch = _getch();//stores char typed in a
		if (ValidPass(ch))//check if a is numeric or alphabet
		{
			pass[i] = ch;//stores a in pass
			++i;
			cout << "*";
		}
		if (ch == '\b'&&i >= 1)//if user typed backspace
			//i should be greater than 1.
		{
			cout << "\b \b";//rub the character behind the cursor.
			--i;
		}
		if (ch == 27) //if esc is pressed
		{
			system("cls");
			exit(0);
		}
		if (ch == '\r')//if enter is pressed
		{
			pass[i] = '\0';//null means end of string.
			break;//break the loop
		}
		if (ch == '†')return -1;
	}
	return 0;
}

int InputUser(char user[])
{
	char ch;
	for (int i = 0;i<21;)//infinite loop
	{
		ch = _getch();//stores char typed in a
		if (ValidUser(ch))//check if a is numeric or alphabet
		{
			user[i] = ch;//stores a in pass
			++i;
			printf("%c", ch);
		}
		if (ch == '\b'&&i >= 1)//if user typed backspace
			//i should be greater than 1.
		{
			cout << "\b \b";//rub the character behind the cursor.
			--i;
		}
		if (ch == 27) //if esc is pressed
		{
			system("cls");
			exit(0);
		}
		if (ch == '\r')//if enter is pressed
		{
			user[i] = '\0';//null means end of string.
			break;//break the loop
		}
		if (ch == '†')return -1;
	}
	return 0;
}

void Input(char user[], char pass[]) {
	drawRectangle(39, 1, 50, 28, 15);
	DrawAppNameTab(15, 4);
	drawRectangle(47, 6, 35, 10, 3);
	gotoxy(48, 7);
	printf("Username: ");
	gotoxy(48, 10);
	printf("Password: ");

	//vex khung input
	drawRectangle(48, 8, 33, 1, 15);
	drawRectangle(48, 11, 33, 1, 15);
	gotoxy(57, 14);
	printf("ENTER to login");

	//nhap
	//inputUser(user);
	gotoxy(48, 8);
	InputUser(user);
	//inputPass(pass);
	gotoxy(48, 11);
	InputPass(pass);
}

bool ValidPass(char ch)	//Qui ước <PASSWORD> từ kí tự 33 đến 126
{
	return (ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z') || (ch >= '0'&&ch <= '9');
}

bool ValidUser(char ch)	//Qui ước <USERNAME> chỉ chứa dấu . _ và các kí tự 0-9, a-z, A-Z
{
	return (ch == '.' || ch == '_' || (ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z') || (ch >= '0'&&ch <= '9'));
}

bool ValidNumber(char x)
{
	return (x >= '0' &&x <= '9');
}

bool ValidName(char x)	//Qui ước <FULLNAME> chỉ chứa các kí tự A-Z, a-z
{
	return (x == ' ' || (x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z'));
}

int InputFullname(char fullname[])
{
	char ch;
	for (int i = 0;i<44;)//infinite loop
	{
		ch = _getch();//stores char typed in a
		if (ValidName(ch))//check if a is numeric or alphabet
		{
			fullname[i] = ch;//stores a in pass
			++i;
			printf("%c", ch);
		}
		if (ch == '\b'&&i >= 1)//if user typed backspace
			//i should be greater than 1.
		{
			cout << "\b \b";//rub the character behind the cursor.
			--i;
		}
		if (ch == 27) //if esc is pressed
		{
			system("cls");
			exit(0);
		}
		if (ch == '\r')//if enter is pressed
		{
			fullname[i] = '\0';//null means end of string.
			break;//break the loop
		}
		if (ch == '†')return -1;
	}
	return 0;
}

int Input1Num()
{
	char day[2];
	char ch;
	for (int i = 0; i < 1;)//infinite loop
	{
		ch = _getch();//stores char typed in a
		if (ch=='1'||ch=='2')
			//check if a is numeric or alphabet
		{
			day[i] = ch;//stores a in pass
			++i;
			cout << ch;
		}
		if (ch == '\b'&&i >= 1)//if user typed backspace
			//i should be greater than 1.
		{
			cout << "\b \b";//rub the character behind the cursor.
			--i;
		}
		if (ch == 27) //if esc is pressed
		{
			system("cls");
			exit(0);
		}
		if (ch == '\r')//if enter is pressed
		{
			day[i] = '\0';//null means end of string.
			break;//break the loop
		}
		if (ch == '†')return -1;
	}
	return atoi(day);
}

int Input2Num()
{
	char day[3];
	char ch;
	for (int i = 0; i < 2;)//infinite loop
	{
		ch = _getch();//stores char typed in a
		if (ValidNumber(ch))
			//check if a is numeric or alphabet
		{
			day[i] = ch;//stores a in pass
			++i;
			cout << ch;
		}
		if (ch == '\b'&&i >= 1)//if user typed backspace
			//i should be greater than 1.
		{
			cout << "\b \b";//rub the character behind the cursor.
			--i;
		}
		if (ch == 27) //if esc is pressed
		{
			system("cls");
			exit(0);
		}
		if (ch == '\r')//if enter is pressed
		{
			day[i] = '\0';//null means end of string.
			break;//break the loop
		}
		if (ch == '†')return -1;
	}
	return atoi(day);
}

int Input4Num()
{
	char year[5];
	char ch;
	for (int i = 0; i < 4;)//infinite loop
	{
		ch = _getch();//stores char typed in a
		if (ValidNumber(ch))
			//check if a is numeric or alphabet
		{
			year[i] = ch;//stores a in pass
			++i;
			cout << ch;
		}
		if (ch == '\b'&&i >= 1)//if user typed backspace
			//i should be greater than 1.
		{
			cout << "\b \b";//rub the character behind the cursor.
			--i;
		}
		if (ch == 27) //if esc is pressed
		{
			system("cls");
			exit(0);
		}
		if (ch == '\r')//if enter is pressed
		{
			year[i] = '\0';//null means end of string.
			break;//break the loop
		}
		if (ch == '†')return -1;
	}
	return atoi(year);
}

long Input9Num()
{
	char num9[11];
	char ch;
	for (int i = 0; i < 9;)//infinite loop
	{
		ch = _getch();//stores char typed in a
		if (ValidNumber(ch))
			//check if a is numeric or alphabet
		{
			num9[i] = ch;//stores a in pass
			++i;
			cout << ch;
		}
		if (ch == '\b'&&i >= 1)//if user typed backspace
			//i should be greater than 1.
		{
			cout << "\b \b";//rub the character behind the cursor.
			--i;
		}
		if (ch == 27) //if esc is pressed
		{
			system("cls");
			exit(0);
		}
		if (ch == '\r')//if enter is pressed
		{
			num9[i] = '\0';//null means end of string.
			break;//break the loop
		}
		if (ch == '†')return -1;
	}
	return atoi(num9);
}

int InputIndentity(char ID[])
{
	char ch;
	for (int i = 0; i < 10;)//infinite loop
	{
		ch = _getch();//stores char typed in a
		if (ValidNumber(ch))
			//check if a is numeric or alphabet
		{
			ID[i] = ch;//stores a in pass
			++i;
			cout << ch;
		}
		if (ch == '\b'&&i >= 1)//if user typed backspace
			//i should be greater than 1.
		{
			cout << "\b \b";//rub the character behind the cursor.
			--i;
		}
		if (ch == 27) //if esc is pressed
		{
			system("cls");
			exit(0);
		}
		if (ch == '\r')//if enter is pressed
		{
			ID[i] = '\0';//null means end of string.
			break;//break the loop
		}
		if (ch == '†')return -1;
	}
	return 0;
}

int InputAddress(char address[])
{
	char ch;
	for (int i = 0; i < 44;)//infinite loop
	{
		ch = _getch();//stores char typed in a
		if (ch>='!'&&ch<='~')//check if a is numeric or alphabet
		{
			address[i] = ch;//stores a in pass
			++i;
			printf("%c", ch);
		}
		if (ch == '\b'&&i >= 1)//if user typed backspace
			//i should be greater than 1.
		{
			cout << "\b \b";//rub the character behind the cursor.
			--i;
		}
		if (ch == 27) //if esc is pressed
		{
			system("cls");
			exit(0);
		}
		if (ch == '\r')//if enter is pressed
		{
			address[i] = '\0';//null means end of string.
			break;//break the loop
		}
		if (ch == '†')return -1;
	}
	return 0;
}


int InputString100(char string100[])
{
	char ch;
	for (int i = 0; i < 41;)//infinite loop
	{
		ch = _getch();//stores char typed in a
		if (ch >= '!' && ch <= '~')//check if a is numeric or alphabet
		{
			string100[i] = ch;//stores a in pass
			++i;
			printf("%c", ch);
		}
		if (ch == '\b' && i >= 1)//if user typed backspace
			//i should be greater than 1.
		{
			cout << "\b \b";//rub the character behind the cursor.
			--i;
		}
		if (ch == 27) //if esc is pressed
		{
			system("cls");
			exit(0);
		}
		if (ch == '\r')//if enter is pressed
		{
			string100[i] = '\0';//null means end of string.
			break;//break the loop
		}
		if (ch == '†')return -1;
	}
	return 0;
}

int InputISBN(char ISBN[])
{
	char ch;
	for (int i = 0; i < 10;)//infinite loop
	{
		ch = _getch();//stores char typed in a
		if (ValidNumber(ch))
			//check if a is numeric or alphabet
		{
			ISBN[i] = ch;//stores a in pass
			++i;
			cout << ch;
		}
		if (ch == '\b' && i >= 1)//if user typed backspace
			//i should be greater than 1.
		{
			cout << "\b \b";//rub the character behind the cursor.
			--i;
		}
		if (ch == 27) //if esc is pressed
		{
			system("cls");
			exit(0);
		}
		if (ch == '\r')//if enter is pressed
		{
			ISBN[i] = '\0';//null means end of string.
			break;//break the loop
		}
		if (ch == '†')return -1;
	}
	return 0;
}

int InputISBN2(char ISBN[])
{
	int len = 0;
	int ch = _getch();
	while (ch != 13)	//ENTER
	{
		if (ch == 0)	//Các phím từ F1-F10 kí tự đầu bằng 0
		{
			_getch();
		}
		else
		{
			if (ch == 224)	//Thuộc bộ mã ASCII mở rộng kí tự đầu bằng 224
			{
				ch = _getch();	//Đọc kí tự phía sau
				if (ch == 134)	//F12
				{
					return -1;
				}
			}
			//Thuộc bộ mã ASCII chuẩn
			else
			{
				//BACKSPACE
				if (ch == 8)
				{
					if (len > 0)
					{
						len--;
						gotoxy(whereX() - 1, whereY());
						printf(" ");
						gotoxy(whereX() - 1, whereY());
					}
				}
				else
				{
					//ESC
					if (ch == 27)
					{
						gotoxy(44, 0);
						textBgColor(15, 0);
						system("cls");
						exit(0);
					}
					//Nếu không phải ENTER, F2, BACKSPACE, ESC
					if (len < 13 && ValidNumber(ch))
					{
						printf("%c", ch);
						ISBN[len++] = ch;
					}
				}
			}
		}
		ch = _getch();
	}
	ISBN[len] = '\0';
	return 0;
}

