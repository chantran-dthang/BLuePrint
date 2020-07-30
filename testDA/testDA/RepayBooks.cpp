#define _CRT_SECURE_NO_WARNINGS
#include"struct.h"
#include"input.h"
#include"thaoTacVoiManHinh.h"
#include"standardFunction.h"
#include"menu.h"
#include"RepayBooks.h"
#include "input.h"
#include "conio.h"
#include "windows.h"
#include "menu.h"
#include "ReaderActions.h"
#include "BorrowedBooks.h"
#include"thaoTacVoiManHinh.h"

int NumBookBorrowed(long code)
{
	_fcloseall();
	FILE* f;
	char codetxt[10];
	//sprintf(textcode, "%ld", code);
	strcpy(codetxt, toStr(code));
	char link[128];
	strcpy(link, Path("BORROWEDBOOKS/", codetxt, ".bin"));
	f = fopen(link, "rb");
	if (f ==NULL)
	{
		return 0;
	}
	else
	{
		int count = 0;
		BorrowBook BB;
		while (fread(&BB, sizeof(BorrowBook), 1, f) != 0)
		{
			count++;
		}
		return count;
	}
}

bool CorrectBook(int numCount, char List[][14], char ISBN[])
{
	for (int i = 0; i < numCount; i++)
	{
		if (strcmp(List[i], ISBN) == 0)
			return true;
	}
	return false;
}

int numDay(int d1, int m1, int y1, int d2, int m2, int y2)
{
	tm p1;
	p1.tm_mday = d1;
	p1.tm_mon = m1 - 1;
	p1.tm_year = y1 - 1900;
	p1.tm_hour = 0;
	p1.tm_isdst = 0;
	p1.tm_min = 0;
	p1.tm_sec = 0;
	p1.tm_wday = 0;
	p1.tm_yday = 0;
	tm p2;
	p2.tm_mday = d2;
	p2.tm_mon = m2 - 1;
	p2.tm_year = y2 - 1900;
	p2.tm_hour = 0;
	p2.tm_isdst = 0;
	p2.tm_min = 0;
	p2.tm_sec = 0;
	p2.tm_wday = 0;
	p2.tm_yday = 0;

	time_t tp1 = mktime(&p1);
	time_t tp2 = mktime(&p2);
	int L = (tp1 - tp2) / 86400;
	return L;
}


void ViewRepayBill(long code)
{
	drawRectangle(20, 19, 80, 11, 0);
	gotoxy2(21, 19, 10, 0); printf("READER CODE: %ld", code);
	gotoxy2(52, 20, 10,0); printf("REPAY-BILL");
	gotoxy2(25, 22,10, 0); printf("ISBN");
	gotoxy2(36, 22, 10 ,0); printf("REPAY DATE");
	gotoxy2(56, 22, 10, 0);	printf("STATE");
	gotoxy2(79, 22, 10, 0); printf("PRICE");
	gotoxy2(89, 22, 10, 0); printf("TOTAL");
	
}

void CreateRepayBill()
{
	DrawAppNameTab(10, 0);
	drawRectangle(39, 6, 48, 12, 0);

	bool BACK = false;
	drawRectangle(39, 6, 48, 7, 0);
	gotoxy2(41, 7, 10, 0);
	printf("Enter Reader code: ");

	gotoxy2(41, 10, 10, 0);
	printf("Number of borrowed books: ");
	gotoxy2(41, 12,10, 0);
	printf("Enter ISBN: ");

	Readers A;
	errno_t err;
	long cost = 0;
	//Nhập mã độc giả
	do
	{

		drawRectangle(41, 9, 50, 3, 0);
		gotoxy2(41, 10, 10, 0);
		printf("Number of borrowed books: ");
		gotoxy2(61, 15, 10, 0);
		printf("ENTER to Repay a book");
		gotoxy2(61, 16, 10, 0);
		printf("F12 to Back");
		//textBgColor(0, 15);

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
			strcpy(link, Path("READERS/", codetxt, ".bin"));

			/*char textcode[10];
			strcpy(textcode, toStr(code));
			char link[128];
			strcpy(link, Path("readers/", textcode, ".bin"));*/

			FILE* f;
			f = fopen(link, "rb");
			//Nếu độc giả không tồn tại trước đó
			if (f==NULL)//In thông báo
			{
				printAlert(39, 9, 50, 3, 0, "READER NOT AVAILABLE");
			}
			//Nếu độc giả tồn tại
			else
			{
				fread(&A, sizeof(Readers), 1, f);
				fclose(f);
				//_fcloseall();
				//textBgColor(0, 3);
				gotoxy2(41, 10, 10, 0);
				printf("Number of borrowed books: %d", NumBookBorrowed(A.code));
			
				ViewRepayBill(A.code);
				Books aBook;
				int CurrentLine = 24;
				//Nhập ISBN
				do
				{
					//ViewBorrowedBook(A.code);
					drawRectangle(39, 9, 48, 3, 0);
					//textBgColor(0, 3);
					gotoxy2(41, 10, 10, 0);
					printf("Number of borrowed books: %d", NumBookBorrowed(A.code));

					//NHẬP ISBN
					drawRectangle(41, 13, 50, 1, 0);
					gotoxy2(41, 13, 10,0);
					int status = InputISBN(aBook.ISBN);
					if (status == -1)
					{
						BACK = true;
					}

					//Đọc dữ liệu từ thư mục mượn sách ra 3 mảng ListBook, EndDay, StartDay
					//Số sách mượn tối đa tùy chỉnh không được vượt quá 100
					char ListBook[100][14];
					Day EndDay[100];
					Day StartDay[100];
					char textcodeA[10];
					strcpy(textcodeA, toStr(A.code));
					//sprintf(textcodeA, "%d", A.code);
					char linkA[128];
					strcpy(linkA, Path("BORROWEDBOOKS/", textcodeA, ".bin"));
					//CreateBrBookList(linkA, ListBook, EndDay, StartDay);
					err = fopen_s(&f, linkA, "rb");
					if (err == 0)
					{
						int i = 0;
						BorrowBook BB_2;
						while (fread(&BB_2, sizeof(BorrowBook), 1, f) != 0)
						{
							strcpy(ListBook[i], BB_2.ISBN);
							EndDay[i] = BB_2.EndDay;
							StartDay[i] = BB_2.BorrowedDay;
							i++;
						}
						fclose(f);
					}


					//Nếu chưa bấm 'Trở về' thì Xử lý dữ liệu
					if (!BACK)
					{
						//Nếu ISBN đúng với ISBN đã mượn
						if (CorrectBook(NumBookBorrowed(A.code), ListBook, aBook.ISBN))
						{
							//In thông báo
							drawRectangle(41, 9, 48, 3, 0);
							gotoxy2(46, 10, 10,0);
							printf("1 REPAY");
							gotoxy2(65, 10, 10, 0);
							printf("2 LOST REPORT");
							char ch = _getch();

							//Xóa sách mượn trong thư mục mượn sách
							char codetxt[10];
							int n = NumBookBorrowed(A.code);
							
							strcpy(codetxt, toStr(A.code));
							_fcloseall();
							int posList = -1;
							strcpy(link, Path("BORROWEDBOOKS/", codetxt, ".bin"));
							//DeleteBrBooks(A, link, ListBook, aBook, EndDay, StartDay, posList);
							err = fopen_s(&f, link, "wb");
							if (err == 0)
							{
								bool Found = false;
								BorrowBook ASD;
								for (int i = 0; i < n; i++)
								{
									if (strcmp(aBook.ISBN, ListBook[i]) != 0 || Found)
									{
										strcpy(ASD.ISBN, ListBook[i]);
										ASD.BorrowedDay = StartDay[i];
										ASD.EndDay = EndDay[i];
										fwrite(&ASD, sizeof(BorrowBook), 1, f);
									}

									if (strcmp(aBook.ISBN, ListBook[i]) == 0)
									{
										Found = true;
										if (posList == -1) posList = i;
									}
								}
								fclose(f);
							}
							//Đọc dữ liệu số lượng sách trong thư viện
							char link[128];
							strcpy(link, Path("BOOKS/", aBook.ISBN, ".bin"));
							FILE* f;
							err = fopen_s(&f, link, "rb");
							if (err == 0)
							{
								fread(&aBook, sizeof(Books), 1, f);
								fclose(f);
							}
							//In thông tin
							gotoxy2(21, CurrentLine, 10, 0);
							printf("%s", aBook.ISBN);
							gotoxy2(35, CurrentLine, 10, 0);
							Day NOW = GetToday();
							printf("%02d/%02d/%04d", NOW.Date, NOW.Month, NOW.Year);
							gotoxy2(78, CurrentLine, 10,0);
							printf("%d", aBook.prices);

							//Chức năng trả sách
							if (ch == '1')
							{
								//Tính khoảng thời gian giữa ngày trả dự kiến và thời gian hiện tại
								int LengthDay = numDay(NOW.Date, NOW.Month, NOW.Year, EndDay[posList].Date, EndDay[posList].Month, EndDay[posList].Year);
								if (LengthDay <= 0)
								{
									gotoxy2(50, CurrentLine, 10, 0);
									printf("In expected time");
								}
								else
								{
									gotoxy2(48, CurrentLine, 10, 0);
									printf("Late %d day(s) than expect", LengthDay);
								}

								//In số tiền thanh toán
								if (LengthDay > 0)
								{
					
									gotoxy2(89, CurrentLine, 10,0);
									printf("%ld", 5000 * LengthDay >= 2 * aBook.prices ? 2 * aBook.prices : 5000 * LengthDay);
									5000 * LengthDay >= 2 * aBook.prices ? cost += 2 * aBook.prices : cost += 5000 * LengthDay;
								}
								else
								{
									gotoxy2(89, CurrentLine, 10, 0);
									printf("0");
								}

								//Tăng số lượng sách trong thư viện nếu số tiền nộp phạt chưa quá 200% hoặc trả đúng hạn
								if ((LengthDay > 0 && (5000 * LengthDay < 2 * aBook.prices)) || LengthDay <= 0)
								{
									//Cập nhật số lượng
									aBook.quantity++;
									//Ghi dữ liệu sách
									err = fopen_s(&f, link, "wb");
									if (err == 0)
									{
										fwrite(&aBook, sizeof(Books), 1, f);
										fclose(f);
									}
								}
								CurrentLine++;
							}
							//Chức năng mất sách
							else if (ch == '2')
							{
								gotoxy2(46, CurrentLine, 10, 0);
								printf("Lost book");
								gotoxy2(89, CurrentLine, 10, 0);
								printf("%ld", 2 * aBook.prices);
								cost += 2 * aBook.prices;
								CurrentLine++;
							}
							//In tổng tiền
							if (CurrentLine <= 29)
							{
								gotoxy2(21, 29, 10, 0);
								printf("Total Pay: %d VND", cost);
							}
							else
							{
								gotoxy2(21, CurrentLine, 10, 0);
								printf("Total Pay: %d VND", cost);
							}
						}
						else//In thông báo
						{
							printAlert(39, 9, 50, 3, 0, "ISBN INCORRECT");
						}
					}
					//Nếu bấm 'Trở về'
					else
					{
						//Trở về Menu
						int n;
						char list[10];
						drawRectangle(39, 6, 50, 23, 0);
						drawRectangle(20, 19, 80, 11, 0);
						ReadMenuData(n, list);
						Menu(n, list);
						break;
					}

				} while (!BACK);
			}
		}
		//Nếu bấm 'Trở về'
		else
		{
			//Trở về BooksMenu
			int n;
			char list[10];
			drawRectangle(36, 10, 50, 23, 0);
			drawRectangle(20, 19, 80, 11, 0);
			ReadMenuData(n, list);
			Menu(n, list);
			break;
		}
	} while (!BACK);
}