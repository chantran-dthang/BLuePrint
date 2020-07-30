#define _CRT_SECURE_NO_WARNINGS
#include"login.h"
#include <stdio.h>
#include"standardFunction.h"

int StatusLogin(char username[], char password[])
{
	FILE *f;
	f=fopen( "USER/admin/admin.bin", "rb");
	if (f)//Mở file thành công 
	{
		Accounts ad;
		fread(&ad, sizeof(Accounts), 1, f);
		fclose(f);
		//Tài khoản Admin luôn ở trạng thái ACTIVE
		if ((strcmp(username, ad.username) == 0) && (strcmp(password, ad.password) == 0))
			return 1;
	}
	else//không mở được file => phải tạo admin thủ công 
	{
		if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0)
		{
			Accounts admin;
			strcpy(admin.username, "admin");
			strcpy(admin.password, "admin");
			admin.active = true;
			strcpy(admin.fullname, "Dang Duc Thang");
			Day dob = { 01,01,2001 };
			admin.DoB = dob;
			strcpy(admin.ID, "123456789");
			strcpy(admin.address, "TP. Ho Chi Minh");
			admin.sex = 1;
			admin.classification = 1;
			createAccountFile("USER/admin/admin.bin", admin);
			return 1;
		}
	}

	char link[100] = "USER/managers/";
	strcat(link, username);
	strcat(link, ".bin");
	f= fopen(link, "rb");
	if (f)
	{
		Accounts member;
		while (fread(&member, sizeof(Accounts), 1, f) != NULL)
			if ((strcmp(username, member.username) == 0) && (strcmp(password, member.password) == 0))
				if (member.active) return 2;
		fclose(f);
	}

	strcpy(link, "USER/experts/");
	strcat(link, username);
	strcat(link, ".bin");
	f= fopen(link, "rb");
	if (f)
	{
		Accounts member;
		while (fread(&member, sizeof(Accounts), 1, f) != NULL)
			if ((strcmp(username, member.username) == 0) && (strcmp(password, member.password) == 0))
				if (member.active) return 3;
		fclose(f);
	}
	return -1;
}

void Login(char user[], char pass[])
{
	int status;
	do {
		Input(user, pass);
		status= StatusLogin(user, pass);
		if (status == -1)
		{
			printAlert(48, 9, 33, 2, 0, "XXXX LOGIN FAILED XXXX");
			/*drawRectangle(48, 9, 33, 2, 12);
			gotoxy(53, 10);
			printf("XXXX LOGIN FAILED XXXX");
			Sleep(1000);*/
		}
	} while (status == -1);
	FILE* f1 = fopen("STOREZONE/authority.txt", "w");
	fprintf(f1, "%d", status);
	fclose(f1);
	FILE* f2 = fopen("STOREZONE/account.txt", "w");
	fprintf(f2, "%s %s", user, pass);
	fclose(f2);
	OpenMenu(status);
}




