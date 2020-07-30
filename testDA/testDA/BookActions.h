#pragma once
#pragma once
#include"thaoTacVoiManHinh.h"
#include"users.h"
#include "windows.h"
#include "stdio.h"
#include "conio.h"
#include "stdlib.h"

void ManageBooks();
void AddBooks();
List CreateBookList();
void ViewBookList(List L, int fullheight);
void FullBooksInfoID(int posX, int posY, int TextColor, int BgColor, int readercode);
void FieldModifyBook(List L, int fullheight);
void ModifyBook(int code);
void DeleteBook();
void SearchBookISBN();
void SearchBookName();