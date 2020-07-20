#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"input.h"
#include"login.h"
#include"struct.h"
#include"thaoTacVoiManHinh.h"
#include"users.h"
#include "windows.h"
#include "stdio.h"
#include "conio.h"
#include "stdlib.h"

void Logout();
void CreateUser();
void AddAccount(Accounts A);
bool AcceptUser(char username[]);
void ModifyAccount();
void ChangePassword();

//Manege Readers
void ManageReaders();
void CreateReader();
int ReadNumMonth();
void ModifyReader();
void DeleteReader();
void ViewReaderList(List_Reader L, int fullheight);
List_Reader CreateReaderList();
void FullReadersInfoID(int posX, int posY, int TextColor, int BgColor, int readercode);
void CreateFileCSV();
void StoreInfoReader(Readers r);
void SearchReaderID();
void SearchReaderName();