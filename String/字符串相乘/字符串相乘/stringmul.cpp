#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
using namespace std;
class Solution {
public:
	string multiply(string num1, string num2) {
		if (num1 == "0")
		{
			return num1;
		}
		if (num2 == "0")
		{
			return num2;
		}
		int size1 = num1.size();
		int size2 = num2.size();
		int size = size1 + size2;
		int tmp, sizetmp, size1tmp;
		int flag = 0;
		string num(size, '0');
		while (size2--)
		{
			size1tmp = size1;
			size--;
			sizetmp = size;
			while (size1tmp--)
			{
				tmp = (num2[size2] - '0')*(num1[size1tmp] - '0');
				flag = tmp / 10;
				tmp = tmp % 10;
				num[sizetmp] += tmp;
				num[sizetmp - 1] += flag;
				if (num[sizetmp] >= (10 + '0'))
				{
					num[sizetmp - 1] += (num[sizetmp] - '0') / 10;
					num[sizetmp] = (num[sizetmp] - '0') % 10 + '0';

				}

				sizetmp--;
			}

		}
		while ('0' == num[0])
		{
			num.erase(num.begin());
		}

		return num;




	}
};