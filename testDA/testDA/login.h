#pragma once
#include "windows.h"
#include "stdio.h"
#include "conio.h"
#include "stdlib.h"

#include"input.h"
#include"struct.h"
#include"thaoTacVoiManHinh.h"
#include"users.h"
#include"thaoTacVoiManHinh.h"
#include"struct.h"

int StatusLogin(char username[], char password[]);
void Login(char user[], char pass[]);
void OpenMenu(int status);
void Menu(int Actions, const char numberAction[]);
void choseAction();
void Logout();
void AdminAction();
void ManagerAction();
void ExpertAction();

void AddAccount(Accounts A);
bool AcceptUser(char username[]);
void CreateUser();