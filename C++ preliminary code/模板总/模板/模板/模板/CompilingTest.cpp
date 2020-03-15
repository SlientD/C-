#define _CRT_SECURE_NO_WARNINGS 1
#include "CompilingTest.h"
template <class T>
T Add(T left, T right)
{
	return left + right;
}
void tmp(){
	Add(1, 2);
}
