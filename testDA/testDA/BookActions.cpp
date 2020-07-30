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
		drawRectangle(39, 6, 50, 10, 0);
		//Ghi các thuộc tính của trường nhập
		gotoxy2(41, 7, 10,0);
		printf("ISBN[44]: ");
		gotoxy2(41, 9, 10, 0);
		printf("BOOK NAME[11]: ");
		gotoxy2(41, 11, 10, 0);
		printf("AUTHOR NAME[100]:");
		gotoxy2(41, 13, 10, 0);
		printf("PUBLISHER[100]: ");
		gotoxy2(41, 15, 10, 0);
		printf("PUBLISHED YEAR:");
		gotoxy2(41, 17, 10, 0);
		printf("TYPE OF BOOK: ");
		gotoxy2(41, 19, 10, 0);
		printf("BOOK SHELF:");
		gotoxy2(41, 21, 10, 0);
		printf("QUANTITY OF BOOK:");
		gotoxy2(41, 23, 10, 0);
		printf("PRICE OF BOOK:");

		Books A;
		do
		{
			gotoxy2(41, 8, 10, 0);
			int status = InputISBN2(A.ISBN);
			if (status == -1) BACK = true;
		} while (strlen(A.ISBN) == 0 && !BACK);

		//Nhập ten sach
		if (!BACK)
		{
			do
			{
				gotoxy2(41, 10, 10, 0);
				int status = InputString100(A.name);
				if (status == -1) BACK = true;
			} while (strlen(A.name) == 0 && !BACK);
		}
		//Nhập ten tac gia
		if (!BACK)
		{
			do
			{
				gotoxy2(41, 12, 10, 0);
				int status = InputFullname(A.author);
				if (status == -1) BACK = true;
			} while (strlen(A.author) == 0 && !BACK);
			
		}
		//Nhập ten nha xuat ban
		if (!BACK)
		{
			do
			{
				gotoxy2(41, 14, 10, 0);
				int status = InputFullname(A.publisher);
				if (status == -1) BACK = true;
			} while (strlen(A.publisher) == 0 && !BACK);
			
		}
		//Nhập nam xuat ban
		if (!BACK)
		{
			do
			{
				gotoxy2(41, 16, 10, 0);
				A.published = Input4Num();
				if (A.published == -1) BACK = true;
			} while (A.published == 0 && !BACK);
		}
		//Nhập the loai sach
		if (!BACK)
		{
			do
			{
				gotoxy2(41, 18, 10, 0);
				int status = InputFullname(A.category);
				if (status == -1)BACK = true;
			} while (strlen(A.category) == 0 && !BACK);
		}
		//Nhap so ke sach
		if (!BACK)
		{
			do
			{
				gotoxy2(41, 20, 10, 0);
				int status = InputAddress(A.bookshelf);
				if (status == -1) BACK = true;
			} while (strlen(A.category) == 0 && !BACK);
		}
		//Nhap so luong sach
		if (!BACK)
		{
			do
			{
				gotoxy2(41, 22, 10, 0);
				A.quantity = Input4Num();
				if (A.published == -1) BACK = true;
			} while (A.published == 0 && !BACK);
		}
		if (!BACK)
		{
			do
			{
				gotoxy2(41, 24, 10, 0);
				A.prices = Input9Num();
				if (A.prices == -1) BACK = true;
			} while (A.prices == 0 && !BACK);
		}
		int n;
		char list[11];
		ReadBooksMenuData(n, list);
		FILE* f;
		//Nếu chưa ấn 'Trở về' [F12]
		if (!BACK)
		{
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
			printAlert(42, 12, 46, 3, 0, "CREATE BOOKS SUCCESSFULL");

		}
		//Nếu đã ấn 'Trở về' [F12kj=o][]
		else
		{
			drawRectangle(39, 6, 50, 22, 0);
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
	drawRectangle(39, 6, 50, 23, 0);
	drawRectangle(39, 6, 50, 1, 0);
	textBgColor(15, 1);
	gotoxy2(42, 6, 10, 0); printf("ISBN");
	gotoxy2(59, 6, 10, 0); printf("BOOK NAME");
	gotoxy2(76, 6, 10, 0); printf("PUBLISHER");

	Node* p = L.pHead;

	//int NumMonth = ReadNumMonth();
	int count = 0;
	for (int i = 0; i < fullheight - 1; i++)
	{
		if (p == NULL) break;
		gotoxy2(42, 6 + 1 + i,10, 0); printf("%s", p->Data.ISBN);
		if (strlen(p->Data.name) <= 20)
		{
			gotoxy2(54, 6 + 1 + i, 10, 0);
			printf("%s", p->Data.name);
		}
		else
		{
			gotoxy2(54, 6 + 1 + i, 10 ,0);
			char fullname[18];
			fullname[17] = '\0';
			strncpy(fullname, p->Data.name, 17);
			printf("%s", fullname);
			printf("...");
		}
		gotoxy2(76, 6 + 1 + i, 10, 0);
		cout << p->Data.publisher;
		count++;
		p = p->pNext;
		if (p == NULL) break;
	}
	if (count > 10)
	{
		gotoxy2(42, fullheight + 6, 10 ,0);  cout << "...";
		gotoxy2(54, fullheight + 6, 10, 0); cout << "...";
		gotoxy2(76, fullheight + 6, 10, 0); cout << "...";

	}
	drawRectangle(41, 25, 46, 2, 0);
	gotoxy2(41, 26, 10, 0);
	cout << "(Press number 0 to exit)";
	gotoxy2(41, 25, 10, 0);
	cout << "Enter reader code to get more information:";
	int code = Input9Num();
	FullBooksInfoID(3, 6, 42, 0, code);
}

void FullBooksInfoID(int posX, int posY, int TextColor, int BgColor, int ISBN)
{
	if (ISBN == 0||ISBN == -1)
	{
		drawRectangle(39, 6, 50, 23, 0);
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
			drawRectangle(2, 5, 35, 11, 0);
			Books book;
			fread(&book, sizeof(Books), 1, f);
			drawRectangle(posX, posY, 33, 9, BgColor);
			textBgColor(TextColor, BgColor);
			gotoxy2(posX, posY, 10, 0);
			printf("- ISBN: %s", book.ISBN);
			gotoxy2(posX, posY +1, 10, 0);
			printf("- Book name %s", book.name);
			gotoxy2(posX, posY+2, 10, 0);
			printf("- Author: %s", book.author);
			gotoxy2(posX, posY+3, 10, 0);
			printf("- Publisher: %s", book.publisher);
			gotoxy2(posX, posY+4, 10, 0);
			printf("- Published: %04d ", book.published);
			gotoxy2(posX, posY+5, 10, 0);
			printf("- Book type: %s", book.category);
			gotoxy2(posX, posY+6, 10, 0);
			printf("- Shelf: %s", book.bookshelf);
			gotoxy2(posX, posY+7, 10, 0);
			printf("- Quantity: %d", book.quantity);
			gotoxy2(posX, posY + 8, 10, 0);
			printf("- Price: %d", book.prices);
			List L = CreateBookList();
			ViewBookList(L, 10);
		}
		else
		{
			printAlert(41, 9, 3, 46, 0, "READER NOT AVAILABLE");
			List L = CreateBookList();
			ViewBookList(L, 10);
		}
	}

	
}

void FieldModifyBook(List L, int fullheight)////chua xong : van dang la framework cua ModifyAccount
{
	drawRectangle(39, 6, 50, 23, 0);
	drawRectangle(39, 6, 50, 1, 0);
	textBgColor(15, 1);
	gotoxy2(42, 6, 10,0); printf("ISBN");
	gotoxy2(59, 6, 10, 0); printf("BOOK NAME");
	gotoxy2(76, 6, 10, 0); printf("PUBLISHER");


	Node* p = L.pHead;

	int count = 0;
	for (int i = 0; i < fullheight - 1; i++)
	{
		if (p == NULL) break;
		gotoxy2(42, 6 + 1 + i, 10, 0); printf("%s", p->Data.ISBN);
		if (strlen(p->Data.name) <= 20)
		{
			gotoxy2(54, 6 + 1 + i, 10,0);
			printf("%s", p->Data.name);
		}
		else
		{
			gotoxy2(54, 6 + 1 + i, 10,0);
			char fullname[18];
			fullname[17] = '\0';
			strncpy(fullname, p->Data.name, 17);
			printf("%s", fullname);
			printf("...");
		}
		gotoxy2(76, 6 + 1 + i, 10, 0);
		cout << p->Data.publisher;
		count++;
		p = p->pNext;
		if (p == NULL) break;
	}
	if (count > 10)
	{
		gotoxy2(42, fullheight + 6, 10, 0);  cout << "...";
		gotoxy2(54, fullheight + 6, 10, 0); cout << "...";
		gotoxy2(76, fullheight + 6, 10, 0); cout << "...";

	}
	drawRectangle(41, 25, 46, 2, 0);
	gotoxy2(41, 26, 10, 0);
	cout << "(Press number 0 to exit)";
	gotoxy2(41, 25, 10 ,0);
	cout << "Enter reader code to get more information:";
	int code = Input9Num();
	ModifyBook(code);
}

void ModifyBook(int code)
{
	bool BACK = false;
	if (code == 0||code==-1)
	{
		drawRectangle(39, 6, 50, 23, 0);
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
			ReadBooksMenuData(n, list);

			//Vẽ khung nhập thông tin
			drawRectangle(39, 6, 50, 23, 0);
			//Ghi các thuộc tính của trường nhập và Thông tin của tài khoản hiện hành

			gotoxy2(41, 7,10,0);
			printf("NAME[44]: ");
			gotoxy2(41, 8, 10, 0);
			if (strlen(A.name) > 0)
			{
				printf("%s", A.name);
			}
			else
			{
				printf("<NULL>");
			}
			gotoxy2(41, 10, 10, 0);
			printf("AUTHOR: ");
			gotoxy2(41, 11, 10, 0);
			if (strlen(A.author) > 0)
			{
				printf("%s", A.author);
			}
			else
			{
				printf("<NULL>");
			}
			
			//
			gotoxy2(41, 13, 10, 0);
			printf("PUBLISHER: ");

			gotoxy2(41, 14, 10, 0);
			if (strlen(A.publisher) > 0)printf("%s", A.publisher);
			else printf("<NULL>");
			
			gotoxy2(41, 16, 10, 0);
			printf("PUBLISHED:");

			gotoxy2(41, 17, 10, 0);
			if (A.published > 0) printf("%04d", A.published);
			else printf("<NULL>");
			
			gotoxy2(41, 19, 10, 0);
			printf("TYPE: ");
			gotoxy2(41, 20, 10, 0);

			if (strlen(A.category) > 0) printf("%s", A.category);
			else printf("<NULL>");
		
			gotoxy2(41, 22, 10, 0);
			printf("SHELF: ");

			gotoxy2(41, 23, 10, 0);
			if (strlen(A.bookshelf) > 0) printf("%s", A.bookshelf);
			else printf("Non Defined");
			
			gotoxy2(41, 25, 10, 0); printf("QUANTITY: ");

			gotoxy2(41, 26, 10, 0);
			if (A.quantity > 0) printf("%d", A.quantity);
			else printf("%d", 0);

			Books B;
			//Nhập  tên
			if (!BACK)
			{
				gotoxy2(41, 9, 10, 0);
				int status = InputFullname(B.name);
				if (status == -1) BACK = true;
			}
			//Nhập tac gia
			if (!BACK)
			{
				gotoxy2(41, 12, 10, 0);
				int status = InputFullname(B.author);
				if (status == -1) BACK = true;
			}
			//Nhập nha xuat ban
			if (!BACK)
			{
				gotoxy2(41, 15, 10, 0);
				int status = InputString100(B.publisher);
				if (status == -1) BACK = true;
			}
			//Nhập nam xuat ban
			if (!BACK)
			{
				gotoxy2(41, 18, 10, 0);
				B.published = Input4Num();
				if (B.published == -1) BACK = true;
			}
			//Nhập loai sach
			if (!BACK)
			{
				gotoxy2(41, 21, 10, 0);
				int status = InputFullname(B.category);
				if (status == -1) BACK = true;
			}
			if (!BACK)
			{
				gotoxy2(41, 24, 10, 0);
				int status = InputString100(B.bookshelf);
				if (status == -1) BACK = true;
			}
			if (!BACK)
			{
				gotoxy2(41, 27, 10, 0);
				B.quantity = Input4Num();
				if (B.quantity == -1) BACK = true;
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
				printAlert(39, 12, 50, 3, 0, "UPDATE SUCCESSFULLY");
			}
			//Nếu đã bấm 'Trở về' thì quay về Main Menu
			else
			{
				drawRectangle(39, 6, 50, 23, 0);
				MenuBooks(n, list);
				break;
			}
		} while (!BACK);
	}
}
void DeleteBook()
{
	bool BACK = false;
	drawRectangle(41, 6, 50, 7, 0);
	gotoxy(41, 7);
	printf("Enter ISBN to delete: ");
	drawRectangle(41, 8, 44, 1, 0);
	Books A;

	//Nhập ISBN
	do
	{
		drawRectangle(41, 9, 48, 3, 0);
		drawRectangle(41, 8, 44, 1, 0);
		//Vẽ nút điều hướng
		gotoxy2(58, 10,10 ,0);
		printf("ENTER to Delete book");
		gotoxy2(58, 11, 10, 0);
		printf("F12 to Back");

		gotoxy2(41, 8, 10, 0);
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
			drawRectangle(36, 6, 48, 7, 0);
			MenuBooks(n, list);
			break;
		}

	} while (!BACK);
}

void SearchBookISBN()
{
	bool BACK = false;
	drawRectangle(39, 6, 50, 23, 0);
	drawRectangle(39, 6, 50, 7, 0);
	gotoxy2(43, 8, 10,0);
	printf("Enter ISBN: ");
	//drawRectangle(43, 8, 36, 1, 0);
	Books A;

	//Nhập CMND
	do
	{
		drawRectangle(41, 9, 44, 3, 0);
		drawRectangle(43, 8, 40, 1, 0);
		//Vẽ nút điều hướng
		gotoxy2(58, 10, 10, 0);
		printf("ENTER to Search book");
		gotoxy2(58, 11, 10, 0);
		printf("F12 to Back");

		gotoxy2(41, 8, 10, 0);
		int status = InputISBN2(A.ISBN);
		if (status == -1)
		{
			BACK = true;
		}

		//Nếu chưa bấm 'Trở về' thì Xử lý dữ liệu
		if (!BACK)
		{
			List L = CreateBookList();
			List L2;
			Init(L2);
			Node* p;
			for (p = L.pTail; p != NULL; p = p->pPrev)
			{
				if (strcmp(p->Data.ISBN, A.ISBN) == 0)
				{
					Insert_first(L2, p->Data);
				}
			}
			if (Len(L2) > 0)
			{
				ViewBookList(L2, 10);
				break;
			}
			else printAlert(44, 9, 40, 3, 12, "BOOK NOT AVAILABLE");
		}
		//Nếu bấm 'Trở về'
		else
		{
			//Trở về BooksMenu
			int n;
			char list[10];
			ReadBooksMenuData(n, list);
			drawRectangle(39, 6, 50, 7, 0);
			MenuBooks(n, list);
			break;
		}

	} while (!BACK);
}

void SearchBookName()
{
	bool BACK = false;
	drawRectangle(39, 6, 50, 23, 0);
	drawRectangle(39, 6, 50, 7, 0);
	gotoxy2(43, 8, 10, 0);
	printf("Enter Name: ");
	drawRectangle(43, 8, 36, 1, 0);
	Books A;

	//Nhập tên sách
	do
	{
		drawRectangle(41, 9, 44, 3, 0);
		drawRectangle(43, 8, 40, 1, 0);
		//Vẽ nút điều hướng
		gotoxy2(58, 10, 10, 0);
		printf("ENTER to Search a book");
		gotoxy2(58, 11, 10, 0);
		printf("F12 to Back");

		gotoxy2(43, 8, 10, 0);
		int status = InputString100(A.name);
		if (status == -1)
		{
			BACK = true;
		}


		//Nếu chưa bấm 'Trở về' thì Xử lý dữ liệu
		if (!BACK)
		{
			List L = CreateBookList();
			List L2;
			Init(L2);
			Node* p;
			for (p = L.pTail; p != NULL; p = p->pPrev)
			{
				if (strstr(p->Data.name, A.name) != NULL)
				{
					Insert_first(L2, p->Data);
				}
			}
			if (Len(L2) > 0)
			{
				ViewBookList(L2, 10);
				break;
			}
			else printAlert(44, 9, 40, 3, 0, "BOOK NOT AVAILABLE");

		}
		//Nếu bấm 'Trở về'
		else
		{
			//Trở về BooksMenu
			int n;
			char list[10];
			ReadBooksMenuData(n, list);
			drawRectangle(39, 6, 50, 7, 0);
			MenuBooks(n, list);
			break;
		}

	} while (!BACK);
}
