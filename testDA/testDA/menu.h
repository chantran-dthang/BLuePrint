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

//Main Menu
void OpenMenu(int status);
void Menu(int Actions, const char numberAction[]);
void choseAction();

//ReadersMenu
void MenuReaders(int numberActions, const char action[]);
void choseReaderAction();

//BooksMenu
void MenuBooks(int numberActions, const char action[]);
void choseBooksAction();
