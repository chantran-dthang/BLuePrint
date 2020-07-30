#define _CRT_SECURE_NO_WARNINGS
#include"struct.h"
#include"input.h"
#include"thaoTacVoiManHinh.h"
#include"standardFunction.h"
#include"menu.h"
#include"BorrowedBooks.h"

bool ReaderInUse(int Date, int Month, int Year)
{
	time_t now = time(0);
	tm* ltm = localtime(&now);
	//Năm hiện tại nhỏ hơn
	if (ltm->tm_year + 1900 < Year)
	{
		return true;
	}
	else
		//Năm hiện tại lớn hơn
		if (ltm->tm_year + 1900 > Year)
		{
			return false;
		}
		else
			//Năm hiện tại bằng
		{
			//Tháng hiện tại nhỏ hơn
			if (ltm->tm_mon + 1 < Month)
			{
				return true;
			}
			else
				//Tháng hiện tại lớn hơn
				if (ltm->tm_mon + 1 > Month)
				{
					return false;
				}
				else
					//Tháng hiện tại bằng
				{
					if (ltm->tm_mday <= Date)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
		}
}

int BookCanBorrowed(long code)
{
	FILE* f;
	char textcode[10];
	strcpy(textcode, toStr(code));
	char link[128];
	strcpy(link, Path("BORROWEDBOOKS/", textcode, ".bin"));
	errno_t err_o = fopen_s(&f, link, "rb");
	if (err_o != 0)
	{
		return 5;
	}
	else
	{
		int count = 0;
		BorrowBook BB;
		while (fread(&BB, sizeof(BorrowBook), 1, f) != 0)
		{
			count++;
		}
		if (5 - count > 0)
		{
			return 5 - count;
		}
		return 0;
	}
}
void ViewBorrowedBook(long code)
{
	drawRectangle(24, 19, 80, 11, 0);
	gotoxy2(25, 19, 10, 0);
	printf("READER CODE: %d", code);
	gotoxy2(56, 20, 10, 0);
	printf("BORROW-BILL");
	gotoxy2(29, 22, 10,0);
	printf("ISBN");
	gotoxy2(59, 22,10, 0);
	printf("BOOK NAME");
	gotoxy2(92, 22, 10, 0);
	printf("BORROW DAY");

	int CurrentLine = 24; //<29
	FILE* f;
	char codetxt[10];
	strcpy(codetxt, toStr(code));
	char link[128];
	strcpy(link, Path("BORROWEDBOOKS/", codetxt, ".bin"));
	f = fopen( link, "rb");
	if (f)
	{
		BorrowBook BB;
		while (fread(&BB, sizeof(BorrowBook), 1, f) != 0)
		{
			if (CurrentLine >= 29)
			{
				drawRectangle(24, CurrentLine, 80, 2, 0);
			}
			gotoxy2(25, CurrentLine, 10, 0);
			printf("%s", BB.ISBN);

			gotoxy2(91, CurrentLine, 10, 0);
			printf("%02d/%02d/%04d", BB.BorrowedDay.Date, BB.BorrowedDay.Month, BB.BorrowedDay.Year);

			Books tmp_book;
			FILE* g;
			char link[128];
			strcpy(link, Path("BOOKS/", BB.ISBN, ".bin"));
			g = fopen( link, "rb");
			if (g)
			{
				fread(&tmp_book, sizeof(Books), 1, g);
				fclose(g);
				gotoxy2(39, CurrentLine, 10,0);

				if (strlen(tmp_book.name) <= 49)
				{
					gotoxy2(39, CurrentLine, 10, 0);
					printf("%s", tmp_book.name);
				}
				else
				{
					gotoxy2(39, CurrentLine, 10, 0);
					char name[47];
					name[46] = '\0';
					strncpy(name, tmp_book.name, 56);
					printf("%s", name);
					printf("...");
				}
			}
			CurrentLine++;
		}
		fclose(f);
	}
}

void CreateBorrowedBill()
{
	DrawAppNameTab(10, 0);
	drawRectangle(39, 6, 50, 12, 0);
	bool BACK = false;
	drawRectangle(39, 6, 50, 7, 0);
	gotoxy2(41, 7, 10, 0);
	printf("Enter reader code: ");
	gotoxy2(41, 10, 10 , 0);
	printf("Number of book can be borrowed: ");
	gotoxy2(41, 13, 10, 0);
	printf("Enter ISBN: ");
	Readers A;
	errno_t err;

	//Nhập mã độc giả
	do
	{

		drawRectangle(39, 11, 50, 3, 0);
		gotoxy2(41, 13, 10, 0);
		printf("Enter ISBN: ");
		//Vẽ nút điều hướng
		gotoxy2(60, 15, 10, 0);
		printf("ENTER to Borrow a book");
		gotoxy2(60, 16, 10, 0);
		printf("F12 to Back");

		gotoxy2(41, 8, 10, 0);
		long code = Input9Num();
		if (code == -1)
		{
			BACK = true;
		}

		//Nếu chưa bấm 'Trở về' thì Xử lý dữ liệu
		if (!BACK)
		{
			char link[128];
			char codetxt[10];
			strcpy(codetxt, toStr(code));
			strcpy(link, Path("readers/", codetxt, ".bin"));

			FILE* f;
			f = fopen(link, "rb");
			//Nếu độc giả không tồn tại trước đó
			if (f==NULL) printAlert(39, 9, 50, 3, 0, "READER NOT AVAILABLE");
			//Nếu độc giả tồn tại
			else
			{
				fread(&A, sizeof(Readers), 1, f);
				fclose(f);
				//Nếu tài khoản còn hạn sử dụng
				if (ReaderInUse(A.expirationDay.Date, A.expirationDay.Month, A.expirationDay.Year))
				{
					gotoxy2(41, 10, 10,0);
					printf("Number of book can be borrowed: %d", BookCanBorrowed(A.code));
					Books aBook;
					//Nhập ISBN
					do
					{
						ViewBorrowedBook(A.code);

						gotoxy2(41, 13, 10, 0);
						printf("Enter ISBN:");
						gotoxy2(41, 14, 10, 0);
						int status = InputISBN2(aBook.ISBN);
						if (status == -1) BACK = true;
						//Nếu chưa bấm 'Trở về' thì Xử lý dữ liệu
						if (!BACK)
						{
							char link_book[128];
							strcpy(link_book, Path("BOOKS/", aBook.ISBN, ".bin"));
							FILE* f_book;
							f_book = fopen(link_book, "rb");
							//Nếu sách chưa bị xóa
							if (f_book)
							{
								fread(&aBook, sizeof(Books), 1, f_book);
								fclose(f_book);
								//Nếu số lượng sách còn lớn hơn 0
								if (aBook.quantity > 0)
								{
									if (BookCanBorrowed(A.code) > 0)
									{
										aBook.quantity--;
										FILE* f_x = fopen(link_book, "wb");
										if (f_x)
										{
											fwrite(&aBook, sizeof(Books), 1, f_x);
											fclose(f_x);
										}

										BorrowBook BB;
										strcpy(BB.ISBN, aBook.ISBN);
										BB.BorrowedDay = GetToday();
										BB.EndDay = BorrDayTimeoutEx(BB.BorrowedDay.Date, BB.BorrowedDay.Month, BB.BorrowedDay.Year);
										_fcloseall();
										char codetxt[10];
										strcpy(codetxt, toStr(A.code));
										char linkBB[128];
										strcpy(linkBB, Path("BORROWEDBOOKS/", codetxt, ".bin"));
										f_x =fopen(linkBB, "ab");
										if (f_x)
										{
											fwrite(&BB, sizeof(BorrowBook), 1, f_x);
											fclose(f_x);
										}
										fread(&A, sizeof(Readers), 1, f);	

										printAlert(39, 12, 50, 3, 0, "BORROW SUCCESSFULL");
										drawRectangle(39, 12, 50, 3, 0);
										gotoxy2(41, 10, 10, 0);
										printf("Number of book can be borrowed: %d", BookCanBorrowed(A.code));
									}
									else printAlert(39, 9, 50, 3, 0, "YOU CAN'T BORROW ANYMORE");
								}
								else printAlert(39, 9, 50, 3, 0, "BOOK OUT OF STOCK");
							}
							//Nếu sách đã bị xóa
							else printAlert(39, 9, 50, 3, 0, "BOOK NOT AVAILABLE");
						}
						else
						{
							//Trở về Menu
							int n;
							char list[10];
							drawRectangle(24, 19, 80, 11, 0);
							drawRectangle(39, 6, 50, 23, 0);
							ReadMenuData(n, list);
							Menu(n, list);
							break;
						}
					}while (!BACK);
				}
				//Tài khoản hết hạn sử dụng
				else printAlert(39, 9, 50, 3, 0, "READER WAS EXPRIED");
			}
		}
		//Nếu bấm 'Trở về'
		else
		{
			//Trở về BooksMenu
			int n;
			char list[10];
			drawRectangle(24, 19, 80, 11, 0);
			drawRectangle(39, 6, 50, 23, 0);
			ReadMenuData(n, list);
			Menu(n, list);
			break;
		}
	} while (!BACK);
}


