#define _CRT_SECURE_NO_WARNINGS
#include"input.h"
#include"login.h"
#include"standardFunction.h"
#include"thaoTacVoiManHinh.h"
#include"struct.h"
#include"users.h"


int main(int argc, char* argv[]) {
	
	char user[21], pass[21];
	initSystemFolder();
	Login(user, pass);
	//drawRectangle(39, 6, 50, 5, 0);
	//textBgColor(10, 0);
	//gotoxy2(53, 6 + 1, 10, 0);
	//cout << "hacked by chantran";
	//printf("%s", alert);
	/*char code[10];
	strcpy(code, toStr(18));
	cout << code;*/
	return 0;
}
