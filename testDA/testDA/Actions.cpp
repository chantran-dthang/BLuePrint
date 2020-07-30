#define _CRT_SECURE_NO_WARNINGS
#include"Actions.h"
#include "standardFunction.h"
#include"ctime"
#include"menu.h"
#include "input.h"
#include"stdio.h"
#include "struct.h"
#include"LinkList.h"
#include"iostream"




void Logout() {
	char username[21], password[21];
	Login(username, password);
}

void CreateUser()
{
	bool BACK = false;	//Biến kiểm tra có bấm 'Trở về' [F12] hay chưa?
	do
	{
		//Vẽ khung Background trang
		drawRectangle(39, 6, 50, 23, 0);
		//drawRectangle(39, 1, 50, 28, 15);
		//Ghi các thuộc tính của trường nhập
		gotoxy2(41, 7, 10, 0);
		printf("USERNAME[21]: ");
		 gotoxy2(41, 9, 10, 0);
		printf("PASSWORD[21]: ");
		 gotoxy2(41, 11, 10, 0);
		printf("FULLNAME[44]: ");
		gotoxy2(41, 13, 10, 0);
		printf("DAY OF BIRTH: dd/mm/yyyy");
		gotoxy2(41, 15, 10, 0);
		printf("NUMBER OF IDENTICAL CARD[11]: ");
		 gotoxy2(41, 17, 10, 0);
		printf("ADDRESS[100]: ");
		gotoxy2(41, 19, 10, 0);
		printf("GENDER: 1->Male ; 2-> Female");
		gotoxy2(41, 21, 10, 0);
		printf("CLASSIFICATION: 1->Manager ; 2->Expert");
		gotoxy(43, 14);
		printf("/  /");
		//Vẽ các trường nhập
		/*drawRectangle(41, 8, 44, 1, 15);
		drawRectangle(41, 10, 44, 1, 15);
		drawRectangle(41, 12, 44, 1, 15);
		drawRectangle(41, 14, 44, 1, 15);
		
		drawRectangle(41, 16, 44, 1, 15);
		drawRectangle(41, 18, 44, 1, 15);
		drawRectangle(41, 20, 44, 1, 15);
		drawRectangle(41, 22, 44, 1, 15);*/
		//Vẽ nút điều hướng
		textBgColor(0, 7);
		gotoxy2(60, 24, 10, 0);
		printf("ENTER to Creat account");
		gotoxy2(60, 25, 10, 0);
		printf("F12 to Back");
		textBgColor(0, 15);
		//Nhập <USERNAME>
		Accounts A;
		do
		{
			gotoxy2(41, 8, 10 ,0);
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
				gotoxy2(41, 10, 10, 0);
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
				gotoxy2(41, 12, 10, 0);
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
				gotoxy2(41, 14, 10, 0);
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
				gotoxy2(44, 14, 10, 0);
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
				gotoxy2(47, 14, 10, 0);
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
				gotoxy2(41, 16, 10, 0);
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
				gotoxy2(41, 18, 10, 0);
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
			gotoxy2(41, 20, 10, 0);
			A.sex = Input1Num();
			if (A.sex == -1)
			{
				BACK = true;
			}
		}
		//Nhập Phân quyền
		if (!BACK)
		{
			gotoxy2(41, 22, 10, 0);
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
				printAlert(42, 12, 46, 3, 0, "CREATE ACCOUNT SUCCESSFULL");
				/*drawRectangle(42, 12, 46, 3, 10);
				char Alert[100] = "CREATE ACCOUNT SUCCESSFULL";
				gotoxy(53, 13);
				printf("%s", Alert);
				Sleep(1500);*/
			}
			//Nếu username không khả dụng thì thông báo tài khoản đã được sử dụng
			else
			{
				printAlert(42, 12, 46, 3, 0, "USER NAME IS AVAILABLE");
				/*drawRectangle(42, 12, 46, 3, 12);
				gotoxy(46, 13);
				char Alert[100] = "USER NAME IS AVAILABLE";
				gotoxy(53, 13);
				printf("%s", Alert);
				Sleep(2000);*/
			}
		}
		//Nếu đã ấn 'Trở về' [F12]
		else
		{

			FILE *f = fopen("STOREZONE/menu.txt", "r");
			fscanf(f, "%d %s", &actions, menu);
			fclose(f);
			drawRectangle(39, 6, 50, 23, 0);
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
		drawRectangle(39, 6, 50, 21, 0);
		//Ghi các thuộc tính của trường nhập và Thông tin của tài khoản hiện hành

		gotoxy2(41, 7, 10, 0);
		printf("FULLNAME[44]: ");
		gotoxy2(41, 8, 10, 0);
		if (strlen(A.fullname) > 0)
		{
			printf("%s", A.fullname);
		}
		else
		{
			printf("<NULL>");
		}
		gotoxy2(41, 10, 10 ,0);
		printf("DAY OF BIRTH: ");
		gotoxy2(41, 11, 10, 0);
		printf("%02d/%02d/%02d", A.DoB.Date, A.DoB.Month, A.DoB.Year);
		gotoxy2(41, 13, 10, 0);
		printf("ID[44]: ");
		gotoxy2(41, 14, 10,0);
		if (strlen(A.ID) > 0)
		{
			printf("%s", A.ID);
		}
		else
		{
			printf("<NULL>");
		}
		gotoxy2(41, 16, 10, 0);
		printf("ADDRESS[100]:");
		gotoxy2(41, 17, 10, 0);
		if (strlen(A.address) > 0)
		{
			printf("%s", A.address);
		}
		else
		{
			printf("<NULL>");
		}
		gotoxy2(41, 19, 10, 0);
		printf("GENDER: 1->MALE ; 2-> FEMALE");
		gotoxy2(41, 20, 10, 0);
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
		drawRectangle(41, 9, 44, 1, 0);
		drawRectangle(41, 12, 44, 1, 0);
		gotoxy2(43, 12, 10,0);
		printf("/  /");
		/*drawRectangle(41, 15, 44, 1, 0);
		drawRectangle(41, 18, 44, 1, 0);
		drawRectangle(41, 21, 44, 1, 0);*/
		//Vẽ nút điều hướng
		//textBgColor(0, 7);
		gotoxy2(62, 23, 10, 0);
		printf("ENTER to Skip a step");
		gotoxy2(62, 24, 10, 0);
		printf("F12 to Back");
		//textBgColor(0, 15);

		Accounts B;
		//Nhập Họ tên
		if (!BACK)
		{
			gotoxy2(41, 9, 10, 0);
			int status = InputFullname(B.fullname);
			if (status == -1)
			{
				BACK = true;
			}
		}
		//Nhập Ngày sinh
		if (!BACK)
		{
			gotoxy2(41, 12, 10, 0);
			B.DoB.Date = Input2Num();
			if (B.DoB.Date == -1)
			{
				BACK = true;
			}
		}
		if (!BACK)
		{
			gotoxy2(44, 12, 10, 0);
			B.DoB.Month = Input2Num();
			if (B.DoB.Month == -1)
			{
				BACK = true;
			}
		}
		if (!BACK)
		{
			gotoxy2(47, 12, 10, 0);
			B.DoB.Year = Input4Num();
			if (B.DoB.Year == -1)
			{
				BACK = true;
			}
		}
		//Nhập CMND
		if (!BACK)
		{
			gotoxy2(41, 15, 10, 0);
			int status = InputIndentity(B.ID);
			if (status == -1)
			{
				BACK = true;
			}
		}
		//Nhập Địa chỉ
		if (!BACK)
		{
			gotoxy2(41, 18, 10, 0);
			int status = InputAddress(B.address);
			if (status == -1)
			{
				BACK = true;
			}
		}
		//Nhập Giới tính
		if (!BACK)
		{
			gotoxy2(41, 21, 10, 0);
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
			printAlert(39, 12, 48, 3, 0, "UPDATE SUCCESSFULLY");
			/*drawRectangle(39, 12, 48, 3, 0);
			gotoxy2(45, 13, 10, 0);
			printf("UPDATE SUCCESSFULLY");
			Sleep(1000);*/
		}
		//Nếu đã bấm 'Trở về' thì quay về Main Menu
		else
		{
			drawRectangle(39, 6, 50, 21, 0);
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
	drawRectangle(36, 6, 48, 11, 0);
	//In các tiêu đề của trường nhập
	gotoxy2(48, 7, 10, 0);
	printf("Enter password: ");
	gotoxy2(48, 9, 10, 0);
	printf("Enter new password: ");
	gotoxy2(48, 11, 10, 0);
	printf("Confirm new password: ");
	//Vẽ trường nhập
	/*drawRectangle(38, 8, 44, 1, 0);
	drawRectangle(38, 10, 44, 1, 0);
	drawRectangle(38, 12, 44, 1, 15);*/
	//Vẽ nút chức năng
	//textBgColor(0, 7);
	gotoxy2(58, 14, 10, 0);
	printf("ENTER to Change Password");
	gotoxy2(58, 15, 10, 0);
	printf("F12 to Back");
	//textBgColor(0, 15);

	//Thực thi
	bool BACK = false;
	char user[21], pass[21];
	ReadCacheAccount(user, pass);
	char currentPassword[21], newPassword[21], confirmPassword[21];
	int status;

	do
	{
		drawRectangle(36, 9, 48, 3, 0);
		gotoxy2(48, 9, 10, 0);
		printf("Enter new password: ");
		gotoxy2(48, 11, 10,0);
		printf("Confirm new password: ");
		/*drawRectangle(38, 8, 44, 1, 15);
		drawRectangle(38, 10, 44, 1, 15);
		drawRectangle(38, 12, 44, 1, 15);*/

		gotoxy2(48, 8, 10, 0);
		status = InputPass(currentPassword);
		if (status == -1)
		{
			BACK = true;
		}
		if (!BACK) {
			if (strcmp(currentPassword, pass) != 0)
			{
				printAlert(36, 9, 48, 3, 10, "INCORRECT PASSWORD");
				/*drawRectangle(36, 9, 48, 3, 10);
				gotoxy(51, 10);
				printf("NHAP SAI MAT KHAU");
				Sleep(1000);*/
			}
		}
		else
		{
			int n;
			char list[11];
			ReadMenuData(n, list);
			drawRectangle(36, 6, 48, 11, 0);
			Menu(n, list);
			break;
		}
	} while (strcmp(currentPassword, pass) != 0 || BACK);

	if (!BACK)
	{
		do
		{
			drawRectangle(36, 9, 48, 3, 0);
			gotoxy2(48, 9, 10, 0);
			printf("Enter new password: ");
			gotoxy2(48, 11, 10, 0);
			printf("Confirm new password: ");

			/*drawRectangle(38, 10, 44, 1, 15);
			drawRectangle(38, 12, 44, 1, 15);*/

			if (!BACK)
			{
				gotoxy2(48, 10, 10, 0);
				status = InputPass(newPassword);
				if (status == -1)
				{
					BACK = true;
				}
			}
			if (!BACK)
			{
				gotoxy2(48, 12, 10, 0);
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
					printAlert(36, 9, 48, 3, 0, "INCORRECT PASSWORD");
					/*drawRectangle(36, 9, 48, 3, 12);
					gotoxy(46, 10);
					printf("MAT KHAU XAC NHAN KHONG DUNG");
					Sleep(1000);*/
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

					printAlert(46, 9, 44, 3, 0, "CHANGED PASSWORD SUCCESSFULLY");
					/*drawRectangle(36, 9, 48, 3, 10);
					gotoxy(46, 10);
					printf("THAY DOI MAT KHAU THANH CONG");
					Sleep(1000);*/

					int n;
					char list[11];
					ReadMenuData(n, list);
					drawRectangle(39, 6, 48, 11, 0);
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
