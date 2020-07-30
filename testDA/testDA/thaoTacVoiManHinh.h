#pragma once
#include<iostream>
#include "conio.h"
#include "windows.h"
using namespace std;

void gotoxy(int x, int y);
void gotoxy2(int x, int y, int txt, int br);

//Trả về tọa độ x của con trỏ vị trí hiện tại
int whereX();
//Trả về tọa độ y của con trỏ vị trí hiện tại
int whereY();

void textBgColor(int colorText, int colorBG);

void DrawAppNameTab(int TextColor, int BgColor);

void drawRectangle(int X, int Y, int width, int height, int color);