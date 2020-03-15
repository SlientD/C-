#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

void printStr()
{
	int normal = 0;
	static int stat = 0;        //this is a static local var
	printf("normal = %d ---- stat = %d\n", normal, stat);
	normal++;
	stat++;
}

int main()
{
	printStr();
	printStr();
	printStr();
	printStr();
	printf("call stat in main: %d\n", stat);
	return 0;
}