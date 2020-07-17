#define _CRT_SECURE_NO_WARNINGS
#include"users.h"
#include "stdio.h"

int createAccountFile(const char link[], Accounts ac) {
	FILE *f;
	f=fopen(link, "wb");
	if (f)
	{
		fwrite(&ac, sizeof(Accounts), 1, f);
		fclose(f);
		return 1;
	}
	return 0;
}