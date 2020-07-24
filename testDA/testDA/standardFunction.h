#pragma once
#include<direct.h>
#include"struct.h"
#include"ctime"

//Tạo chuỗi mã độc giả
char* toStr(long n);
char* Path(const char s1[], char s2[], const char s3[]);

void printAlert(int x, int y, int width, int height, int color, const char alert[]);
void initSystemFolder();
//======================= Account ===============================
int GetAuthority();
Accounts GetAccountData(char link[]);
int WriteAccount(char link[], Accounts user);
void ReadMenuData(int &n, char list[]);
int ReadCacheAccount(char user[], char pass[]);

void printAlert(int x, int y, int height, int width, int color, const char alert[]);
//=================================================================

//======================= Readers ================================
int ReadNumMonth();
tm* MakeEndDay(int Date, int Month, int Year, int NumMonth);
void ReadReadersMenuData(int& n, char list[]);
Readers GetReaderData(char link[]);
int WriteReader(char link[], Readers user);



//=========================BOOK=================================
void ReadBooksMenuData(int& n, char list[]);
Books GetBooksData(char link[]);
int WriteBook(char link[], Books book);