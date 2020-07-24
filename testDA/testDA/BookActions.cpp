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
#include"BookActions.h"
#include"ReaderActions.h"
#include"LinkList.h"

void ManageBooks()
{
	int status = GetAuthority();
	FILE* f = fopen("STOREZONE/menuBooks.txt", "w");
	switch (status)
	{
	case 1:	//admin
		fprintf(f, "%d %s", 6, "ssssss");
		fclose(f);
		MenuBooks(6, "ssssss");
		break;
	case 2:	//manager
		fprintf(f, "%d %s", 6, "ssssss");
		fclose(f);
		MenuBooks(6, "ssssss");
		break;
	case 3:	//expert
		fprintf(f, "%d %s", 2, "hhhhss");
		fclose(f);
		MenuBooks(2, "hhhhss");
		break;
	}
}

void AddBooks()
{
	bool BACK = false;	//Biến kiểm tra có bấm 'Trở về' [F12] hay chưa?
	do
	{
		//Vẽ khung đăng nhập
		drawRectangle(39, 6, 50, 21, 3);
		//Ghi các thuộc tính của trường nhập
		gotoxy(41, 7);
		printf("ISBN[44]: ");
		gotoxy(41, 9);
		printf("BOOK NAME[11]: ");
		gotoxy(41, 11);
		printf("AUTHOR NAME[100]:");
		gotoxy(41, 13);
		printf("PUBLISHER[100]: ");
		gotoxy(41, 15);
		printf("PUBLISHED YEAR:");
		gotoxy(41, 17);
		printf("TYPE OF BOOK: ");
		gotoxy(41, 19);
		printf("BOOK SHELF:");
		gotoxy(41, 21);
		printf("QUANTITY OF BOOK:");
		//Vẽ các trường nhập
		drawRectangle(41, 8, 44, 1, 15);
		drawRectangle(41, 10, 44, 1, 15);
		drawRectangle(41, 12, 44, 1, 15);
		drawRectangle(41, 14, 44, 1, 15);
		drawRectangle(41, 16, 44, 1, 15);
		drawRectangle(41, 18, 44, 1, 15);
		drawRectangle(41, 20, 44, 1, 15);
		drawRectangle(41, 22, 44, 1, 15);


		//Vẽ nút điều hướng
		textBgColor(0, 7);
		gotoxy(61, 26);
		printf("ENTER to Add a book");
		gotoxy(61, 27);
		printf("F12 to Back");
		textBgColor(0, 15);

		
		Books A;
		/*f = fopen("BOOKS/List.bin", "rb");
		if (!f)
		{
			code = 1;
		}
		else
		{
			fread(&code, sizeof(long), 1, f);
			fclose(f);
			code++;
		}*/



		//Nhập
		//Nhập ISBN
	/*	if (!BACK)
		{
			
		}*/
		do
		{
			gotoxy(41, 8);
			int status = InputISBN2(A.ISBN);
			if (status == -1)
			{
				BACK = true;
			}
		} while (strlen(A.ISBN) == 0 && !BACK);

		//Nhập ten sach
		if (!BACK)
		{
			do
			{
				gotoxy(41, 10);
				int status = InputString100(A.name);
				if (status == -1)
				{
					BACK = true;
				}
			} while (strlen(A.name) == 0 && !BACK);
		}
		//Nhập ten tac gia
		if (!BACK)
		{
			do
			{
				gotoxy(41, 12);
				int status = InputFullname(A.author);
				if (status == -1)
				{
					BACK = true;
				}
			} while (strlen(A.author) == 0 && !BACK);
			
		}
		//Nhập ten nha xuat ban
		if (!BACK)
		{
			do
			{
				gotoxy(41, 14);
				int status = InputFullname(A.publisher);
				if (status == -1)
				{
					BACK = true;
				}
			} while (strlen(A.publisher) == 0 && !BACK);
			
		}
		//Nhập nam xuat ban
		if (!BACK)
		{
			do
			{
				gotoxy(45, 16);
				A.published = Input4Num();
				if (A.published == -1)
				{
					BACK = true;
				}
			} while (A.published == 0 && !BACK);
		}
		//Nhập the loai sach
		if (!BACK)
		{
			do
			{
				gotoxy(41, 18);
				int status = InputFullname(A.category);
				if (status == -1)
				{
					BACK = true;
				}
			} while (strlen(A.category) == 0 && !BACK);
		}
		//Nhap so ke sach
		if (!BACK)
		{
			do
			{
				gotoxy(41, 20);
				int status = InputAddress(A.bookshelf);
				if (status == -1)
				{
					BACK = true;
				}
			} while (strlen(A.category) == 0 && !BACK);
		}
		//Nhap so luong sach
		if (!BACK)
		{
			do
			{
				gotoxy(45, 22);
				A.quantity = Input4Num();
				if (A.published == -1)
				{
					BACK = true;
				}
			} while (A.published == 0 && !BACK);
		}
		int n;
		char list[11];
		ReadBooksMenuData(n, list);
		FILE* f;
		//Nếu chưa ấn 'Trở về' [F12]
		if (!BACK)
		{
			/*char link[128];
			strcpy(link, Path("BOOKS/", A.ISBN, ".bin"));
			f = fopen(link, "wb");
			if (f)
			{
				fwrite(&A, sizeof(Books), 1, f);
				fclose(f);
			}
			f = fopen("BOOKS/List.bin", "wb");
			if (f)
			{
				fwrite(&A.ISBN, sizeof(A.ISBN), 1, f);
				fclose(f);
			}*/

			//StoreInfoReader(A);
			//Tạo biến link chứa giá trị đường dẫn đến file dữ liệu sách
			char link[100] = "books/";
			strcat(link, A.ISBN);
			strcat(link, ".bin");

			FILE* f;
			errno_t err = fopen_s(&f, link, "rb");
			//Nếu chưa tồn tại file có ISBN vừa nhập (không mở được file ISBN.bin)
			if (err != 0)
			{
				//Ghi ISBN vào file 'List.dat'
				err = fopen_s(&f, "books/List.bin", "ab");
				if (err == 0)
				{
					fwrite(&A.ISBN, sizeof(A.ISBN), 1, f);
					fclose(f);
				}
				//Ghi dữ liệu sách vào file '<ISBN>.bin'
				err = fopen_s(&f, link, "wb");
				if (err == 0)
				{
					fwrite(&A, sizeof(Books), 1, f);
					fclose(f);
				}
			}
			//Nếu sách có ISBN đã tồn tại trong thư viện (mở được file ISBN.bin)
			else
			{
				Books B;
				fread(&B, sizeof(Books), 1, f);
				fclose(f);
				if (B.exist)
				{
					B.quantity += A.quantity;
					err = fopen_s(&f, link, "wb");
					if (err == 0)
					{
						fwrite(&B, sizeof(Books), 1, f);
						fclose(f);
					}
				}
				else
				{
					//Ghi dữ liệu sách vào file '<ISBN>.bin'
					err = fopen_s(&f, link, "wb");
					if (err == 0)
					{
						fwrite(&A, sizeof(Books), 1, f);
						fclose(f);
					}
				}
			}
			printAlert(42, 12, 46, 3, 10, "CREATE BOOKS SUCCESSFULL");

		}
		//Nếu đã ấn 'Trở về' [F12kj=o][]
		else
		{
			drawRectangle(39, 6, 50, 22, 15);
			MenuBooks(n, list);
			break;
		}
	} while (!BACK);
	gotoxy(44, 0);
}

List CreateBookList()
{
	FILE* f, * g;
	char ISBN[14];
	List L;
	Init(L);
	f= fopen("BOOKS/List.bin", "rb");
	if (f)
	{
		while (fread(&ISBN, sizeof(ISBN), 1, f) != 0)
		{
			char link[100] = "BOOKS/";
			strcat(link, ISBN);
			strcat(link, ".bin");
			g = fopen( link, "rb");
			if (g)
			{
				Books book;
				fread(&book, sizeof(Books), 1, g);
				fclose(g);
				if (book.exist)
				{
					Insert_first(L, book);
				}
			}
		}
		fclose(f);
	}
	return L;
}

void ViewBookList(List L, int fullheight)
{
	drawRectangle(39, 6, 50, 23, 24);
	drawRectangle(39, 6, 50, 1, 1);
	textBgColor(15, 1);
	gotoxy(42, 6); printf("ISBN");
	gotoxy(59, 6); printf("BOOK NAME");
	gotoxy(76, 6); printf("PUBLISHER");
	//VerticalLine(48, CurrentLine, 1, 15, 1);
	//VerticalLine(69, CurrentLine, 1, 15, 1);

	/*drawRectangle(36, CurrentLine + 1, 48, fullHeight - 1, 3);
	VerticalLine(48, CurrentLine + 1, fullHeight - 1, 15, 3);
	VerticalLine(69, CurrentLine + 1, fullHeight - 1, 15, 3);*/

	textBgColor(14, 24);
	Node* p = L.pHead;

	//int NumMonth = ReadNumMonth();
	int count = 0;
	for (int i = 0; i < fullheight - 1; i++)
	{
		if (p == NULL) break;
		gotoxy(42, 6 + 1 + i); printf("%s", p->Data.ISBN);
		if (strlen(p->Data.name) <= 20)
		{
			gotoxy(54, 6 + 1 + i);
			printf("%s", p->Data.name);
		}
		else
		{
			gotoxy(54, 6 + 1 + i);
			char fullname[18];
			fullname[17] = '\0';
			strncpy(fullname, p->Data.name, 17);
			printf("%s", fullname);
			printf("...");
		}
		gotoxy(76, 6 + 1 + i);
		cout << p->Data.publisher;
		count++;
		p = p->pNext;
		if (p == NULL) break;
	}
	if (count > 10)
	{
		gotoxy(42, fullheight + 6);  cout << "...";
		gotoxy(54, fullheight + 6); cout << "...";
		gotoxy(76, fullheight + 6); cout << "...";

	}
	drawRectangle(41, 25, 46, 2, 15);
	gotoxy(41, 26);
	cout << "(Press number 0 to exit)";
	gotoxy(41, 25);
	cout << "Enter reader code to get more information:";
	int code = Input9Num();
	FullBooksInfoID(3, 6, 42, 0, code);
}

void FullBooksInfoID(int posX, int posY, int TextColor, int BgColor, int ISBN)
{
	if (ISBN == 0)
	{
		drawRectangle(39, 6, 50, 23, 15);
		int n;
		char list[9];
		ReadBooksMenuData(n, list);
		drawRectangle(2, 5, 35, 11, 0);
		MenuBooks(n, list);
	}
	else
	{
		char link[128];
		char codetxt[10];
		sprintf(codetxt, "%d", ISBN);
		strcpy(link, Path("BOOKS/", codetxt, ".bin"));
		FILE* f = fopen(link, "rb");
		if (f)
		{
			drawRectangle(2, 5, 35, 11, 15);
			Books book;
			fread(&book, sizeof(Books), 1, f);
			drawRectangle(posX, posY, 33, 9, BgColor);
			textBgColor(TextColor, BgColor);
			gotoxy(posX, posY);
			printf("- ISBN: %s", book.ISBN);
			gotoxy(posX, posY + 1);
			printf("- Book name %s", book.name);
			gotoxy(posX, posY + 2);
			printf("- Author: %s", book.author);
			gotoxy(posX, posY + 3);
			printf("- Publisher: %s", book.publisher);
			gotoxy(posX, posY + 4);
			printf("- Published: %04d ", book.published);
			gotoxy(posX, posY + 5);
			printf("- Book type: %s", book.category);
			gotoxy(posX, posY + 6);
			printf("- Shelf: %s", book.bookshelf);
			gotoxy(posX, posY + 7);
			printf("- Quantity: %d", book.quantity);
			List L = CreateBookList();
			ViewBookList(L, 10);
		}
		else
		{
			printAlert(41, 9, 3, 46, 12, "READER NOT AVAILABLE");
			List L = CreateBookList();
			ViewBookList(L, 10);
		}
	}

	
}

void FieldModifyBook(List L, int fullheight)////chua xong : van dang la framework cua ModifyAccount
{
	drawRectangle(39, 6, 50, 23, 24);
	drawRectangle(39, 6, 50, 1, 1);
	textBgColor(15, 1);
	gotoxy(42, 6); printf("ISBN");
	gotoxy(59, 6); printf("BOOK NAME");
	gotoxy(76, 6); printf("PUBLISHER");
	//VerticalLine(48, CurrentLine, 1, 15, 1);
	//VerticalLine(69, CurrentLine, 1, 15, 1);

	/*drawRectangle(36, CurrentLine + 1, 48, fullHeight - 1, 3);
	VerticalLine(48, CurrentLine + 1, fullHeight - 1, 15, 3);
	VerticalLine(69, CurrentLine + 1, fullHeight - 1, 15, 3);*/

	textBgColor(14, 24);
	Node* p = L.pHead;

	//int NumMonth = ReadNumMonth();
	int count = 0;
	for (int i = 0; i < fullheight - 1; i++)
	{
		if (p == NULL) break;
		gotoxy(42, 6 + 1 + i); printf("%s", p->Data.ISBN);
		if (strlen(p->Data.name) <= 20)
		{
			gotoxy(54, 6 + 1 + i);
			printf("%s", p->Data.name);
		}
		else
		{
			gotoxy(54, 6 + 1 + i);
			char fullname[18];
			fullname[17] = '\0';
			strncpy(fullname, p->Data.name, 17);
			printf("%s", fullname);
			printf("...");
		}
		gotoxy(76, 6 + 1 + i);
		cout << p->Data.publisher;
		count++;
		p = p->pNext;
		if (p == NULL) break;
	}
	if (count > 10)
	{
		gotoxy(42, fullheight + 6);  cout << "...";
		gotoxy(54, fullheight + 6); cout << "...";
		gotoxy(76, fullheight + 6); cout << "...";

	}
	drawRectangle(41, 25, 46, 2, 15);
	gotoxy(41, 26);
	cout << "(Press number 0 to exit)";
	gotoxy(41, 25);
	cout << "Enter reader code to get more information:";
	int code = Input9Num();
	ModifyBook(code);
}

void ModifyBook(int code)
{
	bool BACK = false;
	if (code == 0)
	{
		drawRectangle(39, 6, 50, 23, 15);
		int n;
		char list[11];
		ReadMenuData(n, list);
		drawRectangle(2, 5, 35, 11, 0);
		MenuReaders(n, list);
	}
	else
	{
		char link[128];
		char codetxt[10];
		sprintf(codetxt, "%d", code);
		strcpy(link, Path("BOOKS/", codetxt, ".bin"));
		Books A = GetBooksData(link);

		do
		{
			int n;
			char list[11];
			//char user[21], pass[21];
			ReadBooksMenuData(n, list);

			//Vẽ khung nhập thông tin
			drawRectangle(39, 6, 50, 21, 3);
			//Ghi các thuộc tính của trường nhập và Thông tin của tài khoản hiện hành

			gotoxy(41, 7);
			printf("NAME[44]: ");
			gotoxy(41, 8);
			if (strlen(A.name) > 0)
			{
				printf("%s", A.name);
			}
			else
			{
				printf("<NULL>");
			}
			gotoxy(41, 10);
			printf("AUTHOR: ");
			gotoxy(41, 11);
			if (strlen(A.author) > 0)
			{
				printf("%s", A.author);
			}
			else
			{
				printf("<NULL>");
			}
			
			//
			gotoxy(41, 13);
			printf("PUBLISHER: ");
			gotoxy(41, 14);
			if (strlen(A.publisher) > 0)
			{
				printf("%s", A.publisher);
			}
			else
			{
				printf("<NULL>");
			}
			gotoxy(41, 16);
			printf("PUBLISHED:");
			gotoxy(41, 17);
			if (A.published > 0)
			{
				printf("%04d", A.published);
			}
			else
			{
				printf("<NULL>");
			}
			gotoxy(41, 19);
			printf("TYPE: ");
			gotoxy(41, 20);
			if (strlen(A.category) > 0)
			{
				printf("%s", A.category);
			}
			else
			{
				printf("<NULL>");
			}
			gotoxy(41, 22);
			printf("SHELF: ");
			gotoxy(41, 23);
			if (strlen(A.bookshelf) > 0)
			{
				printf("%s", A.bookshelf);
			}
			else
			{
				printf("Non Defined");
			}
			gotoxy(41, 25);
			printf("QUANTITY: ");
			gotoxy(41, 26);
			if (A.quantity > 0)
			{
				printf("%d", A.quantity);
			}
			else
			{
				printf(0);
			}
			//Vẽ khung input
			drawRectangle(41, 9, 44, 1, 15);
			drawRectangle(41, 12, 44, 1, 15);
			drawRectangle(41, 15, 44, 1, 15);
			drawRectangle(41, 18, 44, 1, 15);
			drawRectangle(41, 21, 44, 1, 15);
			drawRectangle(41, 24, 44, 1, 15);
			drawRectangle(41, 27, 44, 1, 15);
			//Vẽ nút điều hướng
			textBgColor(0, 7);
			gotoxy(62, 23);
			printf("ENTER to Skip a step");
			gotoxy(62, 24);
			printf("F12 to Back");
			textBgColor(0, 15);

			Books B;
			//Nhập  tên
			if (!BACK)
			{
				gotoxy(41, 9);
				int status = InputFullname(B.name);
				if (status == -1)
				{
					BACK = true;
				}
			}
			//Nhập tac gia
			if (!BACK)
			{
				gotoxy(41, 12);
				int status = InputFullname(B.author);
				if (status == -1)
				{
					BACK = true;
				}
			}
			//Nhập nha xuat ban
			if (!BACK)
			{
				gotoxy(41, 15);
				int status = InputString100(B.publisher);
				if (status == -1)
				{
					BACK = true;
				}
			}
			//Nhập nam xuat ban
			if (!BACK)
			{
				gotoxy(41, 18);
				B.published = Input4Num();
				if (B.published == -1)
				{
					BACK = true;
				}
			}
			//Nhập loai sach
			if (!BACK)
			{
				gotoxy(41, 21);
				int status = InputFullname(B.category);
				if (status == -1)
				{
					BACK = true;
				}
			}
			if (!BACK)
			{
				gotoxy(41, 24);
				B.quantity = Input4Num();
				if (B.quantity == -1)
				{
					BACK = true;
				}
			}
			//Nếu chưa bấm 'Trở về' thì Xử lý
			if (!BACK)
			{
				//Cập nhật các trường mà người dùng có nhập thông tin chỉnh sửa
				//Các trường người Dùng không nhập và ấn Enter thì bỏ qua
				if (strlen(B.name) != 0)
				{
					strcpy(A.name, B.name);
				}
				if (B.published != 0 )
				{
					A.published = B.published;
				}
				if (strlen(B.author) != 0)
				{
					strcpy(A.author, B.author);
				}
				if (strlen(B.publisher) != 0)
				{
					strcpy(A.publisher, B.publisher);
				}
				if (B.quantity != 0)
				{
					A.quantity = B.quantity;
				}
				if (strlen(B.category) != 0)
				{
					strcpy(A.category, B.category);
				}
				if (strlen(B.bookshelf) != 0)
				{
					strcpy(A.bookshelf, B.bookshelf);
				}
				//Cập nhật dữ liệu
				WriteBook(link, A);
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
				MenuBooks(n, list);
				break;
			}
		} while (!BACK);
	}
}
void DeleteBook()
{
	bool BACK = false;
	drawRectangle(41, 6, 48, 7, 3);
	gotoxy(41, 7);
	printf("Nhap ma doc gia sach can xoa: ");
	drawRectangle(41, 8, 44, 1, 15);
	Books A;

	//Nhập ISBN
	do
	{
		drawRectangle(41, 9, 48, 3, 3);
		drawRectangle(41, 8, 44, 1, 15);
		//Vẽ nút điều hướng
		textBgColor(0, 7);
		gotoxy(58, 10);
		printf("ENTER to Delete a reader");
		gotoxy(58, 11);
		printf("F12 to Back");
		textBgColor(0, 15);

		gotoxy(41, 8);
		int ISBN = Input9Num();
		if (ISBN == -1)
		{
			BACK = true;
		}
		//Nếu chưa bấm 'Trở về' thì Xử lý dữ liệu
		if (!BACK)
		{

			char link[128];
			char codetxt[10];
			sprintf(codetxt, "%d", ISBN);
			strcpy(link, Path("BOOKS/", codetxt, ".bin"));
			int stt = remove(link);
			if (stt == 0) printAlert(41, 9, 48, 3, 10, "DELEETE SUCCESSFULL");
			else printAlert(41, 9, 48, 3, 12, "READER NOT AVAILABLE");
		}
		//Nếu bấm 'Trở về'
		else
		{
			//Trở về BooksMenu
			int n;
			char list[10];
			ReadBooksMenuData(n, list);
			drawRectangle(36, 6, 48, 7, 15);
			MenuBooks(n, list);
			break;
		}

	} while (!BACK);
}

void SearchBookISBN()
{
	bool BACK = false;
	Title(">>TIM KIEM SACH THEO ISBN");
	drawRectangle(36, 6, 48, 7, 3);
	gotoxy(38, 7);
	printf("Nhap ISBN: ");
	drawRectangle(38, 8, 44, 1, 15);
	Books A;
	errno_t err;

	//Nhập ISBN
	do
	{
		drawRectangle(36, 9, 48, 3, 3);
		drawRectangle(38, 8, 44, 1, 15);
		//Vẽ nút điều hướng
		textBgColor(0, 7);
		gotoxy(60, 10);
		printf("ENTER to Search a book");
		gotoxy(60, 11);
		printf("F12 to Back");
		textBgColor(0, 15);

		gotoxy(38, 8);
		int status = InputISBN(A.ISBN);
		if (status == -1)
		{
			BACK = true;
		}
		//Nếu chưa bấm 'Trở về' thì Xử lý dữ liệu
		if (!BACK)
		{
			char link[128];
			strcpy(link, Path("books/", A.ISBN, ".bin"));
			FILE* f;
			err = fopen_s(&f, link, "rb");
			//Nếu sách tồn tại trước đó
			if (err == 0)
			{
				Books book;
				fread(&book, sizeof(Books), 1, f);
				fclose(f);

				//Nếu sách chưa bị xóa
				if (book.exist)
				{
					FullBooksInfoISBN(0, 18, 0, 15, book);
				}
				//Nếu sách đã bị xóa
				else
				{
					//In thông báo
					drawRectangle(36, 9, 48, 3, 12);
					gotoxy(51, 10);
					printf("SACH KHONG TON TAI");
					Sleep(1000);
				}
			}
			//Nếu sách chưa tồn tại trước đó
			else
			{
				//In thông báo
				drawRectangle(36, 9, 48, 3, 12);
				gotoxy(51, 10);
				printf("SACH KHONG TON TAI");
				Sleep(1000);
			}
		}
		//Nếu bấm 'Trở về'
		else
		{
			//Trở về BooksMenu
			int n;
			char list[10];
			drawRectangle(0, 18, 112, 8, 15);
			ReadBooksMenuData(n, list);
			drawRectangle(36, 6, 48, 7, 15);
			BooksMenu(n, list);
			break;
		}

	} while (!BACK);
}
