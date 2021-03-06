#pragma once
struct Day{
	int Date;
	int Month;
	int Year;
}; 

struct Accounts{
	char username[21];
	char password[21];
	bool active;
	char fullname[45];
	Day DoB;
	char ID[11];
	char address[101];
	int sex;
	int classification;
};

struct Books{
	char ISBN[14];
	char author[101];
	char name[101];
	char publisher[101];
	int published;
	char category[101];
	char bookshelf[11];
	int quantity;
	int prices;
	//int number;
	bool exist = true;
}; 

struct Readers
{
	long code;
	char fullname[45];
	char ID[11];
	Day DoB;
	int sex;
	char email[41];
	char address[101];
	Day createdDay;
	Day expirationDay;
	Books borrowedbook[5];
};

struct Node{
	Books Data;
	Node *pNext;
	Node *pPrev;
};

struct List{
	Node *pHead;
	Node *pTail;
};

struct Node_Reader{
	Readers Data;
	Node_Reader *pNext;
	Node_Reader *pPrev;
};

struct List_Reader{
	Node_Reader *pHead;
	Node_Reader *pTail;
};

struct BorrowBook{
	char ISBN[14];
	Day BorrowedDay;
	Day EndDay;
};
