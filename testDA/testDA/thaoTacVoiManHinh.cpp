#include"thaoTacVoiManHinh.h"

void gotoxy(int x, int y) {
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

void gotoxy2(int x, int y, int txt, int br)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
	textBgColor(txt, br);
}
void DrawAppNameTab(int TextColor, int BgColor)
{
	drawRectangle(51, 2, 27, 3, BgColor);
	gotoxy(56, 3);
	textBgColor(TextColor, BgColor);
	cout << "LIBRARY MANAGEMENT";
}

void drawRectangle(int X, int Y, int width, int height, int color)
{
	textBgColor(0, color);
	gotoxy(X, Y);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			gotoxy(X + x, Y + y);
			cout << ' ';
		}
	}
	gotoxy(44, 0);
}

void textBgColor(int colorText, int colorBG)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (colorBG << 4) | colorText);
}

int whereX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}

//Trả về tọa độ y của con trỏ vị trí hiện tại
int whereY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}

