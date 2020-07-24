#pragma once
#include"struct.h"

//====================READER======================
void Init_Reader(List_Reader& L);
int Isempty_Reader(List_Reader L);
int Len_Reader(List_Reader L);
Node_Reader* Make_Node_Reader(Readers x);
void Insert_first_Reader(List_Reader& L, Readers x);

//=======================BOOKS========================
void Insert_first(List& L, Books x);
void Init(List& L);
int Isempty(List L);
int Len(List L);
Node* Make_Node(Books x);