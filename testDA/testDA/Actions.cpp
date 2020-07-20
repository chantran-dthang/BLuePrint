#define _CRT_SECURE_NO_WARNINGS
#include"Actions.h"
#include "standardFunction.h"
#include"ctime"
#include"menu.h"
#include "input.h"
#include"stdio.h"
#include "struct.h"




void Logout() {
	char username[21], password[21];
	Login(username, password);
}

void CreateUser()
{
	bool BACK = false;	//Biến kiểm tra có bấm 'Trở về' [F12] hay chưa?
	do
	{
		//Vẽ khung đăng nhập
		drawRectangle(39, 6, 50, 21, 3);
		//Ghi các thuộc tính của trường nhập
		gotoxy(41, 7);
		printf("USERNAME[21]: ");
		gotoxy(41, 9);
		printf("PASSWORD[21]: ");
		gotoxy(41, 11);
		printf("FULLNAME[44]: ");
		gotoxy(41, 13);
		printf("DAY OF BIRTH: dd/mm/yyyy");
		gotoxy(41, 15);
		printf("NUMBER OF IDENTICAL CARD[11]: ");
		gotoxy(41, 17);
		printf("ADDRESS[100]: ");
		gotoxy(41, 19);
		printf("GENDER: 1->Male ; 2-> Female");
		gotoxy(41, 21);
		printf("CLASSIFICATION: 1->Manager ; 2->Expert");
		//Vẽ các trường nhập
		drawRectangle(41, 8, 44, 1, 15);
		drawRectangle(41, 10, 44, 1, 15);
		drawRectangle(41, 12, 44, 1, 15);
		drawRectangle(41, 14, 44, 1, 15);
		gotoxy(43, 14);
		printf("/  /");
		drawRectangle(41, 16, 44, 1, 15);
		drawRectangle(41, 18, 44, 1, 15);
		drawRectangle(41, 20, 44, 1, 15);
		drawRectangle(41, 22, 44, 1, 15);
		//Vẽ nút điều hướng
		textBgColor(0, 7);
		gotoxy(60, 24);
		printf("ENTER to Creat account");
		gotoxy(60, 25);
		printf("F12 to Back");
		textBgColor(0, 15);
		//Nhập <USERNAME>
		Accounts A;
		do
		{
			gotoxy(41, 8);
			int status = InputUser(A.username);
			if (status == -1)
			{
				BACK = true;	//Đã bấm 'Trở về' [F12]
			}
		} while (strlen(A.username) == 0 && !BACK);
		//Nhập Mật khẩu
		if (!BACK)
		{
			do
			{
				gotoxy(41, 10);
				int status = InputPass(A.password);
				if (status == -1)
				{
					BACK = true;
				}
			} while (strlen(A.password) == 0 && !BACK);
		}
		//Nhập Họ tên
		if (!BACK)
		{
			do
			{
				gotoxy(41, 12);
				int status = InputFullname(A.fullname);
				if (status == -1)
				{
					BACK = true;
				}
			} while (strlen(A.fullname) == 0 && !BACK);
		}
		//Nhập Ngày sinh
		if (!BACK)
		{
			do {
				gotoxy(41, 14);
				A.DoB.Date = Input2Num();
				if (A.DoB.Date == -1)
				{
					BACK = true;
				}
			} while (A.DoB.Date == 0 && !BACK);
		}
		if (!BACK)
		{
			do
			{
				gotoxy(44, 14);
				A.DoB.Month = Input2Num();
				if (A.DoB.Month == -1)
				{
					BACK = true;
				}
			} while (A.DoB.Month == 0 && !BACK);
		}
		if (!BACK)
		{
			do
			{
				gotoxy(47, 14);
				A.DoB.Year = Input4Num();
				if (A.DoB.Year == -1)
				{
					BACK = true;
				}
			} while (A.DoB.Year == 0 && !BACK);
		}
		//Nhập CMND
		if (!BACK)
		{
			do
			{
				gotoxy(41, 16);
				int status = InputIndentity(A.ID);
				if (status == -1)
				{
					BACK = true;
				}
			} while (strlen(A.ID) == 0 && !BACK);
		}
		//Nhập Địa chỉ
		if (!BACK)
		{
			do
			{
				gotoxy(41, 18);
				int status = InputAddress(A.address);
				if (status == -1)
				{
					BACK = true;
				}
			} while (strlen(A.address) == 0 && !BACK);
		}
		//Nhập Giới tính
		if (!BACK)
		{
			gotoxy(41, 20);
			A.sex = Input1Num();
			if (A.sex == -1)
			{
				BACK = true;
			}
		}
		//Nhập Phân quyền
		if (!BACK)
		{
			gotoxy(41, 22);
			A.classification = Input1Num();
			if (A.classification == -1)
			{
				BACK = true;
			}
		}
		char user[21], pass[21];
		int actions = 0;
		char menu[10];
		//Nếu chưa ấn 'Trở về' [F12]
		if (!BACK)
		{
			//Nếu username khả dụng thì tạo mới tài khoản kèm thông báo tạo thành công
			if (AcceptUser(A.username))
			{
				AddAccount(A);
				drawRectangle(42, 12, 46, 3, 10);
				char Alert[100] = "CREATE ACCOUNT SUCCESSFULL";
				gotoxy(53, 13);
				printf("%s", Alert);
				Sleep(1500);
			}
			//Nếu username không khả dụng thì thông báo tài khoản đã được sử dụng
			else
			{
				drawRectangle(42, 12, 46, 3, 12);
				gotoxy(46, 13);
				char Alert[100] = "USER NAME IS AVAILABLE";
				gotoxy(53, 13);
				printf("%s", Alert);
				Sleep(2000);
			}
		}
		//Nếu đã ấn 'Trở về' [F12]
		else
		{

			FILE *f = fopen("STOREZONE/menu.txt", "r");
			fscanf(f, "%d %s", &actions, menu);
			fclose(f);
			drawRectangle(39, 6, 50, 21, 15);
			Menu(actions, menu);
			break;
		}
	} while (!BACK);
}
void AddAccount(Accounts A)
{
	char LINK[100], link[100], listlink[100];
	if (A.classification == 1)
		strcpy(LINK, "USER/managers/");
	else
		strcpy(LINK, "USER/experts/");

	strcpy(link, LINK);
	strcat(link, A.username);
	strcat(link, ".bin");

	errno_t error;
	FILE *f;
	error = fopen_s(&f, link, "rb");
	if (error != 0)	//Không mở được file để đọc
	{
		strcpy(listlink, LINK);
		strcat(listlink, "List.txt");
		fopen_s(&f, listlink, "a");
		fprintf(f, "%s\n", A.username);
		fclose(f);
	}
	else
		fclose(f);

	A.active = true;

	fopen_s(&f, link, "wb");
	fwrite(&A, sizeof(Accounts), 1, f);
	fclose(f);
}
bool AcceptUser(char username[])
{
	if (strcmp(username, "admin") == 0) return false;	//Nếu tài khoản đăng kí mới trùng tên admin thì trả về false

	bool ACCEPT = true;

	//Kiểm tra các tài khoản thuộc nhóm Quản lý
	char link[100] = "USER/managers/";
	strcat(link, username);
	strcat(link, ".bin");
	errno_t error;
	FILE *f;
	error = fopen_s(&f, link, "rb");
	if (error == 0)	//Mở được file để đọc
	{
		Accounts A;
		fread(&A, sizeof(Accounts), 1, f);
		fclose(f);
		if (A.active)
			ACCEPT = false;	//ACCEPT bằng false chỉ khi tài khoản đã được tạo trước đó và vẫn còn đang trạng thái ACTIVE
	}

	//Kiểm tra các tài khoản thuộc nhóm Chuyên viên
	strcpy(link, "USER/experts/");
	strcat(link, username);
	strcat(link, ".bin");
	error = fopen_s(&f, link, "rb");
	if (error == 0)	//Mở được file để đọc
	{
		Accounts A;
		fread(&A, sizeof(Accounts), 1, f);
		fclose(f);
		if (A.active)
			ACCEPT = false;
	}
	return ACCEPT;
}

void ModifyAccount()
{
	bool BACK = false;
	//Title(">>CHINH SUA THONG TIN");
	do
	{
		int n;
		char list[9];
		char user[21], pass[21];
		ReadMenuData(n, list);
		ReadCacheAccount(user, pass);
		int k = GetAuthority();
		//Tạo đường dẫn đến file người dùng
		char link[256];
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

		Accounts A = GetAccountData(link);

		//Vẽ khung nhập thông tin
		drawRectangle(39, 6, 50, 21, 3);
		//Ghi các thuộc tính của trường nhập và Thông tin của tài khoản hiện hành

		gotoxy(41, 7);
		printf("FULLNAME[44]: ");
		gotoxy(41, 8);
		if (strlen(A.fullname) > 0)
		{
			printf("%s", A.fullname);
		}
		else
		{
			printf("<NULL>");
		}
		gotoxy(41, 10);
		printf("DAY OF BIRTH: ");
		gotoxy(41, 11);
		printf("%02d/%02d/%02d", A.DoB.Date, A.DoB.Month, A.DoB.Year);
		gotoxy(41, 13);
		printf("ID[44]: ");
		gotoxy(41, 14);
		if (strlen(A.ID) > 0)
		{
			printf("%s", A.ID);
		}
		else
		{
			printf("<NULL>");
		}
		gotoxy(41, 16);
		printf("ADDRESS[100]:");
		gotoxy(41, 17);
		if (strlen(A.address) > 0)
		{
			printf("%s", A.address);
		}
		else
		{
			printf("<NULL>");
		}
		gotoxy(41, 19);
		printf("GENDER: 1->MALE ; 2-> FEMALE");
		gotoxy(41, 20);
		if (A.sex == 1)
		{
			printf("Male");
		}
		else
		{
			if (A.sex == 2)
			{
				printf("Female");
			}
			else
			{
				printf("Non defined");
			}
		}
		//Vẽ khung input
		drawRectangle(41, 9, 44, 1, 15);
		drawRectangle(41, 12, 44, 1, 15);
		gotoxy(42, 12);
		printf("/  /");
		drawRectangle(41, 15, 44, 1, 15);
		drawRectangle(41, 18, 44, 1, 15);
		drawRectangle(41, 21, 44, 1, 15);
		//Vẽ nút điều hướng
		textBgColor(0, 7);
		gotoxy(62, 23);
		printf("ENTER to Skip a step");
		gotoxy(62, 24);
		printf("F12 to Back");
		textBgColor(0, 15);

		Accounts B;
		//Nhập Họ tên
		if (!BACK)
		{
			gotoxy(41, 9);
			int status = InputFullname(B.fullname);
			if (status == -1)
			{
				BACK = true;
			}
		}
		//Nhập Ngày sinh
		if (!BACK)
		{
			gotoxy(41, 12);
			B.DoB.Date = Input2Num();
			if (B.DoB.Date == -1)
			{
				BACK = true;
			}
		}
		if (!BACK)
		{
			gotoxy(44, 12);
			B.DoB.Month = Input2Num();
			if (B.DoB.Month == -1)
			{
				BACK = true;
			}
		}
		if (!BACK)
		{
			gotoxy(47, 12);
			B.DoB.Year = Input4Num();
			if (B.DoB.Year == -1)
			{
				BACK = true;
			}
		}
		//Nhập CMND
		if (!BACK)
		{
			gotoxy(41, 15);
			int status = InputIndentity(B.ID);
			if (status == -1)
			{
				BACK = true;
			}
		}
		//Nhập Địa chỉ
		if (!BACK)
		{
			gotoxy(41, 18);
			int status = InputAddress(B.address);
			if (status == -1)
			{
				BACK = true;
			}
		}
		//Nhập Giới tính
		if (!BACK)
		{
			gotoxy(41, 21);
			B.sex = Input1Num();
			if (B.sex == -1)
			{
				BACK = true;
			}
		}
		//Nếu chưa bấm 'Trở về' thì Xử lý
		if (!BACK)
		{
			//Cập nhật các trường mà người dùng có nhập thông tin chỉnh sửa
			//Các trường người Dùng không nhập và ấn Enter thì bỏ qua
			if (strlen(B.fullname) != 0)
			{
				strcpy(A.fullname, B.fullname);
			}
			if (B.DoB.Date != 0 && B.DoB.Month != 0 && B.DoB.Year != 0)
			{
				A.DoB.Date = B.DoB.Date;
				A.DoB.Month = B.DoB.Month;
				A.DoB.Year = B.DoB.Year;
			}
			if (strlen(B.ID) != 0)
			{
				strcpy(A.ID, B.ID);
			}
			if (strlen(B.address) != 0)
			{
				strcpy(A.address, B.address);
			}
			if (B.sex != 0)
			{
				A.sex = B.sex;
			}
			//Cập nhật dữ liệu
			WriteAccount(link, A);
			//Thông báo chỉnh sửa thành công
			drawRectangle(39, 12, 48, 3, 10);
			gotoxy(45, 13);
			printf("UPDATE SUCCESSFULLY");
			Sleep(1000);
		}
		//Nếu đã bấm 'Trở về' thì quay về Main Menu
		else
		{
			drawRectangle(39, 6, 50, 21, 15);
			Menu(n, list);
			break;
		}
	} while (!BACK);
	//gotoxy(44, 0);
}

void ChangePassword()
{
	//Title(">>THAY DOI MAT KHAU");
	//Vẽ khung
	drawRectangle(36, 6, 48, 11, 3);
	//In các tiêu đề của trường nhập
	gotoxy(38, 7);
	printf("Nhap lai mat khau cu: ");
	gotoxy(38, 9);
	printf("Nhap mat khau moi: ");
	gotoxy(38, 11);
	printf("Xac nhan mat khau moi: ");
	//Vẽ trường nhập
	drawRectangle(38, 8, 44, 1, 15);
	drawRectangle(38, 10, 44, 1, 15);
	drawRectangle(38, 12, 44, 1, 15);
	//Vẽ nút chức năng
	textBgColor(0, 7);
	gotoxy(58, 14);
	printf("ENTER to Change Password");
	gotoxy(58, 15);
	printf("F12 to Back");
	textBgColor(0, 15);

	//Thực thi
	bool BACK = false;
	char user[21], pass[21];
	ReadCacheAccount(user, pass);
	char currentPassword[21], newPassword[21], confirmPassword[21];
	int status;

	do
	{
		drawRectangle(36, 9, 48, 3, 3);
		gotoxy(38, 9);
		printf("Nhap mat khau moi: ");
		gotoxy(38, 11);
		printf("Xac nhan mat khau moi: ");
		drawRectangle(38, 8, 44, 1, 15);
		drawRectangle(38, 10, 44, 1, 15);
		drawRectangle(38, 12, 44, 1, 15);

		gotoxy(38, 8);
		status = InputPass(currentPassword);
		if (status == -1)
		{
			BACK = true;
		}
		if (!BACK) {
			if (strcmp(currentPassword, pass) != 0)
			{
				drawRectangle(36, 9, 48, 3, 12);
				gotoxy(51, 10);
				printf("NHAP SAI MAT KHAU");
				Sleep(1000);
			}
		}
		else
		{
			int n;
			char list[11];
			ReadMenuData(n, list);
			drawRectangle(36, 6, 48, 11, 15);
			Menu(n, list);
			break;
		}
	} while (strcmp(currentPassword, pass) != 0 || BACK);

	if (!BACK)
	{
		do
		{
			drawRectangle(36, 9, 48, 3, 3);
			gotoxy(38, 9);
			printf("Nhap mat khau moi: ");
			gotoxy(38, 11);
			printf("Xac nhan mat khau moi: ");

			drawRectangle(38, 10, 44, 1, 15);
			drawRectangle(38, 12, 44, 1, 15);

			if (!BACK)
			{
				gotoxy(38, 10);
				status = InputPass(newPassword);
				if (status == -1)
				{
					BACK = true;
				}
			}
			if (!BACK)
			{
				gotoxy(38, 12);
				status = InputPass(confirmPassword);
				if (status == -1)
				{
					BACK = true;
				}
			}
			if (!BACK)
			{
				if (strcmp(newPassword, confirmPassword) != 0)
				{
					drawRectangle(36, 9, 48, 3, 12);
					gotoxy(46, 10);
					printf("MAT KHAU XAC NHAN KHONG DUNG");
					Sleep(1000);
				}
				else
				{
					int k = GetAuthority();

					//Tạo đường dẫn đến file người dùng
					char link[256];
					if (k == 1)
						strcpy(link, "USER/admin/");
					if (k == 2)
						strcpy(link, "USER/managers/");
					if (k == 3)
						strcpy(link, "USER/experts/");
					strcat(link, user);

					strcat(link, ".bin\0");

					Accounts A = GetAccountData(link);

					//Cập nhật mật khẩu mới
					strcpy(A.password, newPassword);

					WriteAccount(link, A);

					FILE* f = fopen("STOREZONE/account.txt", "w");
					if (f)
					{
						fprintf(f, "%s %s", user, newPassword);
						fclose(f);
					}


					drawRectangle(36, 9, 48, 3, 10);
					gotoxy(46, 10);
					printf("THAY DOI MAT KHAU THANH CONG");
					Sleep(1000);

					int n;
					char list[11];
					ReadMenuData(n, list);
					drawRectangle(36, 6, 48, 11, 15);
					Menu(n, list);
					break;
				}
			}
			else
			{
				int n;
				char list[11];
				ReadMenuData(n, list);
				//SetBG();
				Menu(n, list);
				break;
			}
		} while (strcmp(newPassword, confirmPassword) != 0 || BACK);
	}
	gotoxy(44, 0);
}


//Manage Readers````````````````````````
void ManageReaders()
{
	int status = GetAuthority();
	FILE* f = fopen("STOREZONE/menuReaders.txt", "w");
	switch (status)
	{
	case 1:	//admin
		fprintf(f, "%d %s", 6, "ssssss");
		fclose(f);
		MenuReaders(6, "ssssss");
		break;
	case 2:	//manager
		fprintf(f, "%d %s", 6, "ssssss");
		fclose(f);
		MenuReaders(6, "ssssss");
		break;
	case 3:	//expert
		fprintf(f, "%d %s", 5, "ssshss");
		fclose(f);
		MenuReaders(5, "ssshss");
		break;
	}
}
void CreateReader()
{
	bool BACK = false;	//Biến kiểm tra có bấm 'Trở về' [F12] hay chưa?
	do
	{
		//Vẽ khung đăng nhập
		drawRectangle(39, 6, 50, 21, 3);
		//Ghi các thuộc tính của trường nhập
		gotoxy(41, 7);
		printf("FULLNAME[44]: ");
		gotoxy(41, 9);
		printf("IDENTICAL CARD[11]: ");
		gotoxy(41, 11);
		printf("DAY OF BIRTH: dd/mm/yyyy");
		gotoxy(41, 13);
		printf("ADDRESS[100]: ");
		gotoxy(41, 15);
		printf("EMAIL[100]: ");
		gotoxy(41, 17);
		printf("GENDER: 1->Male ; 2-> Female");
		gotoxy(41, 19);
		printf("DAY OF CREATION: dd/mm/yyyy");
		gotoxy(41, 21);
		printf("DAY OF EXSPIRATION: dd/mm/yyyy");
		//Vẽ các trường nhập
		drawRectangle(41, 8, 44, 1, 15);
		drawRectangle(41, 10, 44, 1, 15);
		drawRectangle(41, 12, 44, 1, 15);
		gotoxy(43, 12);
		printf("/  /");
		drawRectangle(41, 14, 44, 1, 15);
		drawRectangle(41, 16, 44, 1, 15);
		drawRectangle(41, 18, 44, 1, 15);
		drawRectangle(41, 20, 44, 1, 15);
		gotoxy(43, 20);
		printf("/  /");
		drawRectangle(41, 22, 44, 1, 15);
		gotoxy(43, 22);
		printf("/  /");

		//Vẽ nút điều hướng
		textBgColor(0, 7);
		gotoxy(61, 26);
		printf("ENTER to Add a reader");
		gotoxy(61, 27);
		printf("F12 to Back");
		textBgColor(0, 15);

		FILE* f;
		long code;
		Readers A;
		f=fopen( "readers/List.bin", "rb");
		if (!f)
		{
			code = 1;
		}
		else
		{
			fread(&code, sizeof(long), 1, f);
			fclose(f);
			code++;
		}
		A.code = code;

		time_t now = time(0);
		tm* ltm = localtime(&now);
		gotoxy(41, 20);
		printf("%02d/%02d/%04d", ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
		A.createdDay.Date = ltm->tm_mday;
		A.createdDay.Month = ltm->tm_mon + 1;
		A.createdDay.Year = ltm->tm_year + 1900;

		int NumMonth = ReadNumMonth();
		tm* endDay = MakeEndDay(ltm->tm_mday, ltm->tm_mon, ltm->tm_year, NumMonth);
		gotoxy(41, 22);
		printf("%02d/%02d/%04d", endDay->tm_mday, 1 + endDay->tm_mon, 1900 + endDay->tm_year);
		A.expirationDay.Date = endDay->tm_mday;
		A.expirationDay.Month = endDay->tm_mon + 1;
		A.expirationDay.Year = endDay->tm_year + 1900;

		//Nhập
		//Nhập Họ và tên
		if (!BACK)
		{
			do
			{
				gotoxy(41, 8);
				int status = InputFullname(A.fullname);
				if (status == -1)
				{
					BACK = true;
				}
			} while (strlen(A.fullname) == 0 && !BACK);
		}
		//Nhập CMND
		if (!BACK)
		{
			do
			{
				gotoxy(41, 10);
				int status = InputIndentity(A.ID);
				if (status == -1)
				{
					BACK = true;
				}
			} while (strlen(A.ID) == 0 && !BACK);
		}
		//Nhập Ngày sinh
		if (!BACK)
		{
			do {
				gotoxy(41, 12);
				A.DoB.Date = Input2Num();
				if (A.DoB.Date == -1)
				{
					BACK = true;
				}
			} while (A.DoB.Date == 0 && !BACK);
		}
		if (!BACK)
		{
			do
			{
				gotoxy(43, 12);
				A.DoB.Month = Input2Num();
				if (A.DoB.Month == -1)
				{
					BACK = true;
				}
			} while (A.DoB.Month == 0 && !BACK);
		}
		if (!BACK)
		{
			do
			{
				gotoxy(45, 12);
				A.DoB.Year = Input4Num();
				if (A.DoB.Year == -1)
				{
					BACK = true;
				}
			} while (A.DoB.Year == 0 && !BACK);
		}
		//Nhập địa chỉ 
		if (!BACK)
		{
			do
			{
				gotoxy(41, 14);
				int status = InputAddress(A.address);
				if (status == -1)
				{
					BACK = true;
				}
			} while (strlen(A.address) == 0 && !BACK);
		}
		//Nhập Email
		if (!BACK)
		{
			do
			{
				gotoxy(41, 16);
				int status = InputString100(A.email);
				if (status == -1)
				{
					BACK = true;
				}
			} while (strlen(A.email) == 0 && !BACK);
		}
		//Nhập Giới tính
		if (!BACK)
		{
			gotoxy(41, 18);
			A.sex = Input1Num();
			if (A.sex == -1)
			{
				BACK = true;
			}
		}
		int n;
		char list[11];
		ReadReadersMenuData(n, list);
		
		//Nếu chưa ấn 'Trở về' [F12]
		if (!BACK)
		{
			char link[128];
			char codetxt[10];
			sprintf(codetxt, "%d", code);
			strcpy(link, Path("readers/", codetxt, ".bin"));
			f = fopen( link, "wb");
			if (f)
			{
				fwrite(&A, sizeof(Readers), 1, f);
				fclose(f);
			}
			f=fopen("readers/List.bin", "wb");
			if (f)
			{
				fwrite(&A.code, sizeof(long), 1, f);
				fclose(f);
			}

			StoreInfoReader(A);
			printAlert(42, 12, 46, 3, 10, "CREATE READER SUCCESSFULL");

		}
		//Nếu đã ấn 'Trở về' [F12]
		else
		{
			drawRectangle(39, 6, 50, 22, 15);
			MenuReaders(n, list);
			break;
		}
	} while (!BACK);
	gotoxy(44, 0);
}
void ModifyReader()
{
	bool BACK = false;
	//Title(">>CHINH SUA THONG TIN");
	do
	{
		int n;
		char list[9];
		char user[21], pass[21];
		ReadMenuData(n, list);
		ReadCacheAccount(user, pass);
		int k = GetAuthority();
		//Tạo đường dẫn đến file người dùng
		char link[256];
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

		Accounts A = GetAccountData(link);

		//Vẽ khung nhập thông tin
		drawRectangle(39, 6, 50, 21, 3);
		//Ghi các thuộc tính của trường nhập và Thông tin của tài khoản hiện hành

		gotoxy(41, 7);
		printf("FULLNAME[44]: ");
		gotoxy(41, 8);
		if (strlen(A.fullname) > 0)
		{
			printf("%s", A.fullname);
		}
		else
		{
			printf("<NULL>");
		}
		gotoxy(41, 10);
		printf("DAY OF BIRTH: ");
		gotoxy(41, 11);
		printf("%02d/%02d/%02d", A.DoB.Date, A.DoB.Month, A.DoB.Year);
		gotoxy(41, 13);
		printf("ID[44]: ");
		gotoxy(41, 14);
		if (strlen(A.ID) > 0)
		{
			printf("%s", A.ID);
		}
		else
		{
			printf("<NULL>");
		}
		gotoxy(41, 16);
		printf("ADDRESS[100]:");
		gotoxy(41, 17);
		if (strlen(A.address) > 0)
		{
			printf("%s", A.address);
		}
		else
		{
			printf("<NULL>");
		}
		gotoxy(41, 19);
		printf("GENDER: 1->MALE ; 2-> FEMALE");
		gotoxy(41, 20);
		if (A.sex == 1)
		{
			printf("Male");
		}
		else
		{
			if (A.sex == 2)
			{
				printf("Female");
			}
			else
			{
				printf("Non defined");
			}
		}
		//Vẽ khung input
		drawRectangle(41, 9, 44, 1, 15);
		drawRectangle(41, 12, 44, 1, 15);
		gotoxy(42, 12);
		printf("/  /");
		drawRectangle(41, 15, 44, 1, 15);
		drawRectangle(41, 18, 44, 1, 15);
		drawRectangle(41, 21, 44, 1, 15);
		//Vẽ nút điều hướng
		textBgColor(0, 7);
		gotoxy(62, 23);
		printf("ENTER to Skip a step");
		gotoxy(62, 24);
		printf("F12 to Back");
		textBgColor(0, 15);

		Accounts B;
		//Nhập Họ tên
		if (!BACK)
		{
			gotoxy(41, 9);
			int status = InputFullname(B.fullname);
			if (status == -1)
			{
				BACK = true;
			}
		}
		//Nhập Ngày sinh
		if (!BACK)
		{
			gotoxy(41, 12);
			B.DoB.Date = Input2Num();
			if (B.DoB.Date == -1)
			{
				BACK = true;
			}
		}
		if (!BACK)
		{
			gotoxy(44, 12);
			B.DoB.Month = Input2Num();
			if (B.DoB.Month == -1)
			{
				BACK = true;
			}
		}
		if (!BACK)
		{
			gotoxy(47, 12);
			B.DoB.Year = Input4Num();
			if (B.DoB.Year == -1)
			{
				BACK = true;
			}
		}
		//Nhập CMND
		if (!BACK)
		{
			gotoxy(41, 15);
			int status = InputIndentity(B.ID);
			if (status == -1)
			{
				BACK = true;
			}
		}
		//Nhập Địa chỉ
		if (!BACK)
		{
			gotoxy(41, 18);
			int status = InputAddress(B.address);
			if (status == -1)
			{
				BACK = true;
			}
		}
		//Nhập Giới tính
		if (!BACK)
		{
			gotoxy(41, 21);
			B.sex = Input1Num();
			if (B.sex == -1)
			{
				BACK = true;
			}
		}
		//Nếu chưa bấm 'Trở về' thì Xử lý
		if (!BACK)
		{
			//Cập nhật các trường mà người dùng có nhập thông tin chỉnh sửa
			//Các trường người Dùng không nhập và ấn Enter thì bỏ qua
			if (strlen(B.fullname) != 0)
			{
				strcpy(A.fullname, B.fullname);
			}
			if (B.DoB.Date != 0 && B.DoB.Month != 0 && B.DoB.Year != 0)
			{
				A.DoB.Date = B.DoB.Date;
				A.DoB.Month = B.DoB.Month;
				A.DoB.Year = B.DoB.Year;
			}
			if (strlen(B.ID) != 0)
			{
				strcpy(A.ID, B.ID);
			}
			if (strlen(B.address) != 0)
			{
				strcpy(A.address, B.address);
			}
			if (B.sex != 0)
			{
				A.sex = B.sex;
			}
			//Cập nhật dữ liệu
			WriteAccount(link, A);
			//Thông báo chỉnh sửa thành công
			drawRectangle(39, 12, 48, 3, 10);
			gotoxy(45, 13);
			printf("UPDATE SUCCESSFULLY");
			Sleep(1000);
		}
		//Nếu đã bấm 'Trở về' thì quay về Main Menu
		else
		{
			drawRectangle(39, 6, 50, 21, 15);
			Menu(n, list);
			break;
		}
	} while (!BACK);
}

void CreateFileCSV()
{
	FILE* f = fopen("readers/ReaderList.txt", "w");
	char text[100];
	sprintf(text, "%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s", "code", ',', "fullname", ',', "ID", ',', "DoB", ',', "sex", ',', "email", ',', "address", ',', "createdDay", ',', "exspirationDay");
	fputs(text, f);
	fclose(f);
}
void StoreInfoReader(Readers r)
{
	FILE* f = fopen("readers/ReaderList.txt", "w");
	char text[100];
	sprintf(text, "%d%c%s%c%d%c%d%c%s%c%s%", r.code, ',', r.fullname, ',', r.ID, ',', r.sex, ',', r.email, ',',r.address);
	fputs(text, f);
	fclose(f);
}

void DeleteReader()
{
	bool BACK = false;
	drawRectangle(36, 6, 48, 7, 3);
	gotoxy(38, 7);
	printf("Nhap ma doc gia sach can xoa: ");
	drawRectangle(38, 8, 44, 1, 15);
	Readers A;
	errno_t err;

	//Nhập ISBN
	do
	{
		drawRectangle(36, 9, 48, 3, 3);
		drawRectangle(38, 8, 44, 1, 15);
		//Vẽ nút điều hướng
		textBgColor(0, 7);
		gotoxy(58, 10);
		printf("ENTER to Delete a reader");
		gotoxy(58, 11);
		printf("F12 to Back");
		textBgColor(0, 15);

		gotoxy(38, 8);
		A.code = Input9Num();
		if (A.code == -1)
		{
			BACK = true;
		}
		//Nếu chưa bấm 'Trở về' thì Xử lý dữ liệu
		if (!BACK)
		{
			char textcode[10];
			strcpy(textcode, toStr(A.code));
			char link[128];
			strcpy(link, Path("readers/", textcode, ".bin"));
			int stt = remove(link);
			if (stt == 0)
			{
				//In thông báo
				drawRectangle(36, 9, 48, 3, 10);
				gotoxy(51, 10);
				printf("XOA SACH THANH CONG");
				Sleep(1000);
			}
			else
			{
				//In thông báo
				drawRectangle(36, 9, 48, 3, 12);
				gotoxy(51, 10);
				printf("DOC GIA KHONG TON TAI");
				Sleep(1000);
			}
		}
		//Nếu bấm 'Trở về'
		else
		{
			//Trở về BooksMenu
			int n;
			char list[10];
			ReadReadersMenuData(n, list);
			drawRectangle(36, 6, 48, 7, 15);
			MenuReaders(n, list);
			break;
		}

	} while (!BACK);
}

