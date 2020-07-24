#pragma once
#include"thaoTacVoiManHinh.h"
#include"users.h"
#include "windows.h"
#include "stdio.h"
#include "conio.h"
#include "stdlib.h"

void ManageReaders();
void CreateReader();
int ReadNumMonth();
void FieldModifyReader(List_Reader l, int height);
void ModifyReader(int code);
void DeleteReader();
void ViewReaderList(List_Reader L, int fullheight);
List_Reader CreateReaderList();
void FullReadersInfoID(int posX, int posY, int TextColor, int BgColor, int readercode);
void CreateFileCSV();
void StoreInfoReader(Readers r);
void SearchReaderID();
void SearchReaderName();