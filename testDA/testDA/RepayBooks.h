#pragma once
#include"struct.h"

int NumBookBorrowed(long code);
bool CorrectBook(int numCount, char List[][14], char ISBN[]);
int numDay(int d1, int m1, int y1, int d2, int m2, int y2);
void ViewRepayBill(long code);
void CreateRepayBill();