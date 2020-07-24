#include "struct.h"
#include"stdlib.h"
#include"LinkList.h"

///======================READERS=============================
void Init_Reader(List_Reader& L)
{
	L.pHead = NULL;
	L.pTail = NULL;
}

//Kiểm tra Danh sách liên kết rỗng hay không?
int Isempty_Reader(List_Reader L)
{
	return (L.pHead == NULL);
}

//Hàm trả về độ dài của Danh sách liên kết
int Len_Reader(List_Reader L)
{
	Node_Reader* PH = L.pHead, * PT = L.pTail; //PH duyệt từ đầu danh sách, PT duyệt từ cuối danh sách
	int i = 0; //Biến đếm
	if (PH != NULL) i = 1;
	while (PH != NULL)
	{
		if (PH == PT) break;
		PH = PH->pNext;
		i++;
		if (PH == PT) break;
		PT = PT->pPrev;
		i++;
	}
	return i;
}

//Tạo một Node chứa thông tin <X>
Node_Reader* Make_Node_Reader(Readers x)
{
	Node_Reader* P = new Node_Reader;
	P->Data = x;
	P->pPrev = NULL;
	P->pNext = NULL;
	return P;
}

//Chèn <X> vào đầu Danh sách liên kết
void Insert_first_Reader(List_Reader& L, Readers x)
{
	Node_Reader* P;
	P = Make_Node_Reader(x);
	if (Isempty_Reader(L))
	{
		L.pHead = P;
		L.pTail = P;
	}
	else
	{
		P->pNext = L.pHead;
		L.pHead->pPrev = P;
		L.pHead = P;
	}
}

//======================== BOOKS ================================
void Init(List& L)
{
	L.pHead = NULL;
	L.pTail = NULL;
}

//Kiểm tra Danh sách liên kết rỗng hay không?
int Isempty(List L)
{
	return (L.pHead == NULL);
}

//Hàm trả về độ dài của Danh sách liên kết
int Len(List L)
{
	Node* PH = L.pHead, * PT = L.pTail; //PH duyệt từ đầu danh sách, PT duyệt từ cuối danh sách
	int i = 0; //Biến đếm
	if (PH != NULL) i = 1;
	while (PH != NULL)
	{
		if (PH == PT) break;
		PH = PH->pNext;
		i++;
		if (PH == PT) break;
		PT = PT->pPrev;
		i++;
	}
	return i;
}

//Tạo một Node chứa thông tin <X>
Node* Make_Node(Books x)
{
	Node* P = (Node*)malloc(sizeof(Node));
	P->Data = x;
	P->pPrev = NULL;
	P->pNext = NULL;
	return P;
}

//Chèn <X> vào đầu Danh sách liên kết
void Insert_first(List& L, Books x)
{
	Node* P;
	P = Make_Node(x);
	if (Isempty(L))
	{
		L.pHead = P;
		L.pTail = P;
	}
	else
	{
		P->pNext = L.pHead;
		L.pHead->pPrev = P;
		L.pHead = P;
	}
}